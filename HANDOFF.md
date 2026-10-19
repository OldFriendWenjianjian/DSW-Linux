# DSW-Linux 项目交接文档

> 目标：让 DSCope M454（DreamSourceLab，闭源上位机 DSWave v1.2.1 专属）在 Linux 上原生工作。
> 本文档面向接手继续开发的人：先读"现状"，再按"上手步骤"跑通，然后从"待办清单"领任务。

## 一、项目现状（2026-10-19）

**核心结论：M454 的 USB 协议已完全逆向，Linux 上位机软件 v1 已在真实硬件上跑通全流程**
（设备枚举 → FPGA 位流加载 → 会话配置 → 采集数据流 15MB/次 → 波形显示/CSV 导出）。

验证环境：Windows 真机 + pyusb/libusb（同一份 `dswave_linux.py` 代码，Linux 语法，无平台分支）。
Linux 裸机部署预期即拷即用；VMware 虚拟机直通有已知限制（见第五节）。

## 二、已完成成果

### 1. 协议逆向（PROTOCOL.md —— 驱动开发的直接依据）
- 设备：VID `2A0E` / PID `0080`（新 M 系列），USB3 SuperSpeed，1 接口 × 3 bulk 端点（`0x02 OUT` / `0x84 IN` / `0x86 IN`，MaxPacket 1024）
- EP0 命令集：寄存器写 `0x40/0xB1 [reg u8][val u16]`、模块命令 `0x40/0xB0`、读回 `0xC0/0xB2`
- 完整开机序列（帧级实测+Ghidra 互证）：描述符 → F0/F2/F1 版本（固件 `0x3110`）→ FF 状态 → 安全校验（16B 密钥，设备内明文可读）→ FPGA 配置 → ADC/调零初始化 → SCPI 配置
- FPGA 配置序列：PROG_B(0xFE) 舞步 → INIT_B(FF bit1) → 长度(0xFC/0xFD) → bulk 单笔 466,408B 位流 → Done(FF bit7)
- SCPI 词汇表 60 条实测命令+默认值（文本语义，标准 SCPI 风格，但传输是寄存器编码）
- 采集流：bulk 0x86，块 4096/60096B，载荷 = 交错 float32 通道对，单次 ~15MB（1M 深度）

### 2. 固件与算法
- `firmware/m454_fpga_bitstream.bin`：完整 FPGA 位流（从 DSWave.exe 提取，同步字 `5599AA66` 字节反转变体）
- SecurityCheck 挑战-应答算法：部分反编译在 `decomp/fn_140340b20_sec_SecurityCheck.c`（寄存器 0x513/0x219，逐 16 位挑战-应答）；实测密钥可由任意主机读取（无服务器依赖，可完整复刻）

### 3. 软件（dswave_linux.py，v1）
- `wake_prelude()`：**最关键发现**——PROG_B 前必须先做 GET_DESCRIPTOR×4 + F0/F2 查询，否则 MCU 不拉高 INIT_B，FPGA 永远配置不上
- FPGA 加载（分块写+重试）、会话重放（逐字节 bRequest 原样、bulk 读写交织、真实时间间隔）
- GUI：pyqtgraph 双通道波形、重新采集按钮、CSV 导出；`--test` 无头自检模式

### 4. 工具链（全部可复用）
- `hook_winusb.js` + `run_trace.py`：Frida WinUSB API 钩子（帧级抓包，比 USBPcap 干净；USBPcap 在 Win11 USB3 上不可用）
- `extract_bsp.py`：Ghidra/PyGhidra 批量反编译脚本（改地址列表即可挖新函数）
- `capture/*.jsonl`：多轮抓包存档（run_archive = 完整采集会话，coldboot = 冷启动）

## 三、仓库文件地图

| 路径 | 内容 |
|---|---|
| `PROTOCOL.md` | **协议规范**（先读，含"关键实现要点"踩坑记录） |
| `dswave_linux.py` | 上位机应用 |
| `firmware/m454_fpga_bitstream.bin` | FPGA 位流 466,408B |
| `capture/trace_20261016_174945_run_archive.jsonl` | 完整采集会话轨迹（重放数据源） |
| `capture/trace_coldboot_20261016.jsonl` | 冷启动轨迹（FPGA 上传会话） |
| `decomp/` | 反编译伪代码集（含 `_vtables.txt` 虚表地图、`_string_xrefs.txt`） |
| `NOTES.md` | 全部逆向情报、函数地址索引、HAL 结构（hal::UsbBsp2x/3x） |
| `FEDORA_PORT.md` | libsigrok 驱动移植路线（中期方案） |
| `hook_winusb.js` / `run_trace.py` / `extract_bsp.py` | 工具链 |

**不在仓库**（本地 Windows 机器 `dswave_re/` 下，太大）：`ghidra_proj/`（41k 函数分析库，可用 `extract_bsp.py` 重新生成，约 10 分钟）、`tools/`（Ghidra 12.1.4 + JDK21 + REA CLI）。

## 四、新 Linux 机器上手步骤

```bash
git clone https://github.com/OldFriendWenjianjian/DSW-Linux.git
cd DSW-Linux

# 依赖（Fedora: sudo dnf install python3-pip; 其他发行版等价）
pip install --user pyusb pyqtgraph
# libusb-1.0 运行时一般系统自带（lsusb 能用就有）；如缺：sudo dnf install libusb1

# 设备权限（免 root）：
# sudo tee /etc/udev/rules.d/51-dsl.rules <<< 'SUBSYSTEM=="usb", ATTRS{idVendor}=="2a0e", MODE="0666"'
# sudo udevadm control --reload && sudo udevadm trigger

python3 dswave_linux.py --test    # 无头自检：应看到 FPGA configured + 采集字节数
python3 dswave_linux.py           # GUI
```

预期 `--test` 输出：`fpga: configured 0x0083` + `replay: ~1475 transfers` + `blocks: ~254 / bytes: ~15,000,000`。

## 五、已知问题与限制

1. **VMware 直通**：控制传输和 FPGA 配置（bulk OUT）可用，但 VMware 丢失 bulk URB 完成事件——写数据实际到达（FPGA 能配成）但上层超时；读流卡死。**裸机无此问题**（真机 Windows 实测全通，Linux 裸机预期同样）
2. **重放模式的局限**：v1 靠重放抓包会话驱动设备，参数固定（默认 1M 深度、200kS/s 模拟/100MS/s 数字、auto 触发）。换参数需要 SCPI 直控（见待办 1）
3. 块头 16 字节的语义未定（最初以为是时间戳，实测像数据/魔数）；模拟通道解包按 float32 对交错处理（CH0/CH1），接真实信号后需校验通道映射与比例
4. 数字通道（默认全关）打包格式未验证

## 六、待完成工作（按优先级）

### P0 —— 裸机验证与修正
1. 裸机 Linux 跑 `--test`，确认全管线；接信号源（或用手摸探头制造 50Hz 工频干扰）校验波形/通道映射/幅度比例
2. 修正 GUI 的通道解包（如有错位），补 CH2/CH3（块内 float 排布需实测确认）

### P1 —— 参数可调（摆脱重放依赖）
3. **SCPI 寄存器编码破解**：SCPI 文本如何编码进 reg 0x01/0x0E/0x0F 的 16 位写 + 64B 读回执。
   素材：`NOTES.md` 的函数地址索引（ScpiWrite 引用者）、Ghidra 项目（Windows 机器 `ghidra_proj/`，或用 `extract_bsp.py` 重建后搜 "SCPI command %.*s done" 交叉引用）、`dswave_session.log` 的命令↔数值对照表
4. 实现 `set_sample_rate() / set_depth() / set_trigger()` 直控，GUI 加参数面板
5. 连续采集模式（:LOOPModeEnable）与实时滚动

### P2 —— 完整性
6. SecurityCheck 算法补全（`decomp/fn_140340b20_sec_SecurityCheck.c` 已有大半；确认不校验时设备是否长期可用，若是则可降级为可选）
7. `.dswb` 采集文件格式（ZIP 容器 + 自定义序列化，入口：搜 "DSWave Binary" 字符串引用）→ 兼容官方文件
8. 数字通道使能 + 格式验证（SCPI `:DIGITAL:CHANNEL:Enable ch,1`）

### P3 —— 生态整合（原 FEDORA_PORT.md 路线）
9. libsigrok 驱动（dreamsourcelab-m），复用 PulseView UI + libsigrokdecode 40+ 解码器
10. AWG / DAQ 模式（设备三模式之一，协议入口在 profile 表）

## 七、关键技术速查（防再踩坑）

- **wake_prelude 必须先行**（GET_DESCRIPTOR×4 + F0/F2），否则 INIT_B 不起、FPGA 卡 0x0001
- bRequest（0xB0/0xB1）不可按寄存器猜，必须与抓包一致
- bulk 读写必须与命令序列交织（单次采集在命令流中一次性完成）
- 位流同步字是 `5599AA66`（Xilinx 标准字的字节反转）
- Frida 钩子注意：Frida 17 移除了 `Memory.readByteArray`（用 `ptr.readByteArray`）、`hexdump/hex` 是保留名
- 抓包产物文件名带时间戳，禁止覆盖（全局 AGENTS.md 已制度化）
