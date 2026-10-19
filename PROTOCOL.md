# DSCope M454 USB 协议规范（实测 + 逆向交叉验证）

来源：Frida WinUSB API 钩子实录（capture/winusb_trace.jsonl）+ Ghidra 静态逆向。
设备：VID 0x2A0E / **PID 0x0080**，"USB-based DSL Instrument v3"，SuperSpeed（speed=4，MaxPacket 1024）。
字符串描述符：iProduct="DreamSourceLab"，iSerial="USB-based DSL Instrument v3"，LANGID 0x0409。

## 端点布局（QueryPipeEx 实测）

- 9 个接口（WinUsb_Initialize ×9），每接口 3 个 bulk 端点：**OUT 0x02、IN 0x84、IN 0x86**
- 控制 EP0 承载全部命令/配置阶段；bulk 承载数据流（FPGA 位流、采集数据）
- 等时能力有运行时检测（WinUsb_ReadIsochPipeAsap），采集流可能切 iso（待采流时验证）

## EP0 控制传输命令集

| 类型 | bmRequestType | bRequest | 语义 |
|---|---|---|---|
| 寄存器写 | 0x40 (vendor OUT) | **0xB1** | data = `[reg:u8][value:u16 LE]`（3 字节） |
| 寄存器读/数据读 | 0xC0 (vendor IN) | **0xB2** | wLength = 期望字节数，异步完成后取响应 |
| 模块命令 | 0x40 (vendor OUT) | **0xB0** | ADC/调零/流控等（与 0xB1 格式同，语义组不同） |

## 实测开机序列（帧级）

1. `GET_DESCRIPTOR`(标准) String0/1/2
2. 版本查询（写 0xB1 reg=2 → 读 0xB2 2 字节）：
   - reg **0xF0** → `0x3110`（固件版本，日志 "Firmware version: %04x"）
   - reg **0xF2** → `0x3100`（FPGA bin 版本）
   - reg **0xF1** → `0x3100`（面板/固件2版本）
   - reg **0xFF** → `0x0083`（HW_STATUS：bit1=INIT_B，bit0/bit7=done/ready）
3. 安全校验：
   - `0xB0 fb 0010`、`0xB1 fb 1000`（设定读取长度）
   - `0xB2` 读 16 字节 → **设备安全密钥**（本机：`c7a38ed4515b6b35d8505835e3902f36`，随机、按设备存储）
   - 之后 16 字节厂商 OUT（首轮实录 `0031 00…`）= SecurityCheck 请求载荷（算法待 Ghidra 还原，见 NOTES 待办）
   - 后续 `0xB2` 读 2 字节 `0x0002` ×N = 校验状态
4. FPGA 配置（**实测完整序列**，冷启动）：
   - `0xB1 ff0200` + `0xB2` → `0x0003`（未配置）
   - `0xB0 fefeff`（PROG_B=0）、`0xB0 fe0100`（PROG_B=1，中间 1ms）
   - 轮询 `0xFF` 等 INIT_B
   - `0xB0 fce81d` + `0xB0 fd0700`（长度 = 0x071DE8 = 466,408）
   - **单笔 bulk OUT EP0x02 写全部 466,408 字节**；位流头部 `FFFF...FFFF 5599AA66`（Xilinx 同步字的字节反转序）
   - `0xB1 ff0200` + `0xB2` → `0x0083` = 配置完成
   - ⚠️ 驱动需要完整位流文件：追踪只留了前 512B，后续用钩子整包落盘一次即得（或从 exe 提取，注意同步字是 5599AA66 变体）
5. 模块初始化（0xB0/0xB1 组合）：ADC init、MSO Zero info（含 0xFB 设长度 + 0xB2 读数据）、流暂停/停止命令
6. SCPI 配置流（封装在这些 EP0 请求内，文本见 capture/dswave_session.log 60 条）

## SCPI 词汇（实测默认值）

命令：`:LOOPModeEnable`、`:SAMPLEtime`、`:STORAGEdepth`、`:AUTORATEModeEnable`、`:DIGITAL:Threshold`、`:ANALOG:CHANNEL:{Enable|Invert|Coupling|BWlimit|Vdiv|Offset|TRIGGERlevel}`、`:DIGITAL:CHANNEL:Enable`、`:TRIGger:{Mode|Channel|Type|PULSEtime|Margin|HOLDtime|SAMPLEindex}`、`:Sync:Word`、`:Device:Index`
查询：`:ANALOG:SAMPLE:{Depth?|Rate?}`、`:DIGITAL:SAMPLE:{Depth?|Rate?}`
默认：1M 深度（0x3D0900）、数字 100 MS/s、模拟 200 kS/s 起步、Vdiv=0x30D40(200000)/0xF4240(1000000)、阈值 0x16E360(1500000µV=1.5V)

## 关键实现要点（实测踩坑记录）

1. **wake_prelude 必须先行**：PROG_B 前必须完成 GET_DESCRIPTOR(string×4) + F0/F2 版本查询——这些"家常"通信让 MCU 拉高 FPGA INIT_B（状态从 0x0001 → 0x0003）。直接 PROG_B 会永远卡 0x0001（2026-10-19 实测确认）
2. bulk 读必须与命令序列**交织执行**（重放完整轨迹），采集是单次的：Run 命令簇发出后 254×60KB 块一次性流出（~15MB = 1M 深度）
3. 块头 16 字节不是时间戳（实测为数据/魔数），有效载荷 = 交错 float32 通道对（CH0/CH1）
4. 重放必须逐字节使用抓包的 bRequest（0xB0/0xB1 不可按寄存器猜测）

## Linux 驱动映射（libusb）

| Windows (WinUSB) | libusb |
|---|---|
| SetupAPI 枚举 | `libusb_get_device_list` + VID/PID 过滤 |
| 0x40/0xB1 寄存器写 | `libusb_control_transfer(dev, 0x40, 0xB1, 0, 0, buf, 3, timeout)` |
| 0xC0/0xB2 读 | `libusb_control_transfer(dev, 0xC0, 0xB2, 0, 0, buf, N, timeout)` |
| bulk OUT 0x02 / IN 0x84/0x86 | `libusb_bulk_transfer` / async `libusb_submit_transfer` |
| iso（如启用） | `LIBUSB_TRANSFER_TYPE_ISOCHRONOUS` |
| 接口 ×9 | `libusb_claim_interface` 逐个（对照 GetAssociatedInterface 调用序） |

## 已解密钥与校验（安全评估）

密钥可由任意主机经 `0xC0/0xB2` 读出（无认证、无服务器参与）。SecurityCheck 载荷与密钥的关系算法在 DSWave.exe 内（虚表 +0x198 槽实现），待反编译——**无外部依赖，纯本地算法，可完整复刻**。

## 采集数据流（实测，Run 单次采集）

- 通道：**bulk IN EP 0x86**（264 块/次会话）；EP 0x84 偶发（3 次，疑状态）
- 无 bulk OUT——采集期间全部配置/状态轮询走 EP0（1268 次控制传输）
- 块结构：
  - 首块 4096B：含 float32 序列（实测 3.95/3.37V 交替，疑通道标定或首段采样）+ 零填充
  - 数据块 60096B：`[u64 ts_start (ns)][u64 ts_end (ns)][载荷...]`；等触发时载荷全零
- 采样格式：float32 电压（模拟通道）；数字通道打包格式待有信号时补验
- ReadPipe 均为异步（overlapped），长度 4096/60096 两种
