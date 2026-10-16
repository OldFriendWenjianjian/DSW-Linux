# DSCope M454 Fedora 移植方案

目标：在 Fedora 上原生驱动 DSCope M454（当前仅官方 Windows/macOS 上位机 DSWave 支持）。
方法：REA + Ghidra 逆向 DSWave.exe，还原 USB 协议，在 Linux 生态内实现。

## 结论先行（当前证据下的推荐架构）

**首选：给 libsigrok 写 `dreamsourcelab-m` 设备驱动（C，GPL 兼容）**，UI 复用 PulseView，协议解码复用 libsigrokdecode。理由：

1. DSWave 的 40 个协议解码器与 libsigrokdecode/PulseView 高度重合（MODBUS/LIN/IR-NEC/SPDIF/WIEGAND/DALI/PS2/SBUS…均有现成实现），无需重写
2. 波形显示、触发、测量、导出（CSV/HTML）PulseView 全有
3. 真正要写的只有：M454 的 USB 设备驱动（枚举/配置/采集流），这是唯一没有现成物的部分
4. DSWave 的 HAL 本来就是 libusb 形状（`m_libusb`、libusb 错误码、libusb_device_handle 语义），Linux 端用真 libusb 一比一映射

**备选**（若 sigrok 路线受阻，如解码器/交互与官方差异过大）：Qt6 自写上位机，参照 `dsv::device` 会话架构。

## 驱动需要实现的协议栈（自底向上）

| 层 | 内容 | 逆向状态 |
|---|---|---|
| USB 传输 | WinUSB（bulk+control+iso）→ libusb 等价；端点表待插机 lsusb 确认 | ✅ API 清单已还原（动态 GetProcAddress 的 WinUsb_* 全集） |
| 设备初始化 | GetFirmwareVersion → (必要时) ISP 固件升级 → FPGA 位流配置（INIT_B/DONE 握手）→ 版本校验 | 🔶 流程已知（BSP 日志序列），字节级格式待反编译确认 |
| 安全校验 | 16 字节密钥（8×uint16）：Get → Check → (全 0xFFFF 时) Set 新钥 | 🔶 外层流程已还原（FUN_1403407d0），密钥生成/校验算法待解 |
| 寄存器队列 | `Queue set reg(0x%02X)=0x%04X`，三段握手 Prepare→Wait Ready→Done，RegBulkIn 批量读 | 🔶 待反编译（函数在 0x14034ba31/0x14034bba6 附近代码空洞，已定位） |
| SCPI | 文本命令，设备端解析，回执命令号；MSO/AWG/DAQ 三模式 | 🔶 传输格式待解（ScpiWrite），语义为标准 SCPI |
| 数据流 | 等时/bulk 采集流 → 通道打包格式 | ⬜ 待解 |
| 文件格式 | `.dswb` 采集文件（ZIP 容器 + 自定义序列化）、`.dswc` 配置（ZIP + `dsw_configs` 条目，内容为二进制序列化） | ⬜ 待解 |

## 已确认事实

- 硬件：DSCope M454 = DreamSourceLab 混合信号仪器（OSC+DAQ+AWG），VID 2A0E，PID ∈ {0x0004–0x001F, 0x0080–0x008F}（老驱动已占 0001/0002/0003/0020/0021，M454 具体 PID 插机即知）
- DSWave v1.2.1（2026-08）闭源，与开源 DSView（GPLv3，止于 2024 v1.3.2）无直接代码继承（全新 `dsv::`/`hal::` 命名空间）
- 采样率表（profile 静态数据）：[1k, 2k, 5k, 10k, 20k, 50k, 100k, 200k, 500k, 1M, 2M, 5M] Hz，另有 100 MHz 常量（逻辑通道满速？）、16 通道字段
- HAL 类族：`hal::UsbBsp2x`（USB2）/ `hal::UsbBsp3x`（USB3），各自 `RegQueueThread()`
- 源码布局（assert 泄漏）：`hal/usb/usbbsp.cpp` 等

## 实施步骤

### 阶段 0：硬件情报（插上设备后，Windows 或 Linux 均可）
- Windows：USBPcap 抓 DSWave 完整开机+采集+各功能一次，得到协议 ground truth（比纯静态逆向快一个量级）
- `lsusb -v -d 2a0e:` 确认 PID、端点表、接口/alt setting
- 对照静态逆向结果验证

### 阶段 1：补齐逆向（工具已就绪）
- 本机 Ghidra 项目：`ghidra_proj/dswave`（41k 函数已分析）；批量提取脚本 `extract_bsp.py`；产出在 `decomp/`
- 待办清单见 NOTES.md；优先级：安全密钥算法 > 寄存器队列帧格式 > FPGA 位流来源与格式 > SCPI 传输封装 > 数据流打包

### 阶段 2：libsigrok 驱动（Fedora 上开发）
```
libsigrok/src/hardware/dreamsourcelab-m/
├── api.c        # 扫描/打开/配置/启停（libusb）
├── protocol.c   # 寄存器队列 + SCPI + 流解析
└── protocol.h   # 命令/寄存器/帧结构定义（从逆向结果翻译）
```
- 参考现有 `dreamsourcelab-dslogic` 驱动骨架（GPL，同厂商旧协议）
- dnf 依赖：`gcc make autoconf automake libtool libusb1-devel libzip-devel glib2-devel check-devel`
- 单测：sigrok-cli + PulseView 对拍官方 DSWave 的采集结果

### 阶段 3：联调
- demoM454 模式的期望波形可当测试向量
- `.dswb` 兼容（可选）：解 ZIP + 自定义序列化 → sigrok 会话

## 风险

1. **安全密钥算法**：若校验是 HMAC(序列号+challenge) 之类且密钥由厂商服务器签发，第三方驱动可能无法通过 → 届时需完整复现配对流程（首次 Set 新密钥路径），或在设备已配对状态下复用既有密钥（读设备回显）
2. 固件/FPGA 位流若不在 exe 内嵌（已初步排除两个 zlib blob），可能按需从网络拉取或由设备自带 → 插机抓包即知
3. USB3 路径（UsbBsp3x）协议可能与 USB2 不同，M454 走哪条待确认（M454 为 USB2 高速概率大，U3P100 显然 USB3）
