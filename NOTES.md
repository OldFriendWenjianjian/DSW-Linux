# DSWave 逆向工程笔记

目标：逆向 DSWave（DreamSourceLab 新一代上位机），在 Fedora 上原生重写对 DSCope M454 的支持。

## 基本信息

| 项 | 值 |
|---|---|
| 安装路径 | `C:\Program Files\DSWave\DSWave.exe` |
| 版本 | v1.2.1 x64（2026-08-05） |
| 格式 | PE32+ x86-64，13 个 section，`.text` ≈ 12.2MB，`.rdata` ≈ 4.6MB |
| 技术栈 | Qt 6（Widgets/Gui/Core/Multimedia/Network/Svg）+ MinGW GCC（libstdc++/libwinpthread） |
| 厂商 | DreamSourceLab（GlobalSign EV 代码签名） |
| 支持设备 | DSCope M252 / **DSCope M454（本机）** / DSCope U2P20 / DSCope U3P100 / DSLogic X1 / demoM454 演示模式 |
| 安装包 | `~/Downloads/DSWave_v1.2.1_x64_setup.exe` |

## USB 层（重写的关键）

- 驱动：WinUSB（`Drivers/dsl_usb_instruments.inf`，VID **2A0E**，PID 0x0001–0x001F 及 0x0080–0x008F）
- 导入表：`SETUPAPI.dll`（设备枚举）+ KERNEL32；**winusb.dll 为运行时 GetProcAddress 动态加载**（所以导入表里看不到）
- 动态解析的 WinUSB API：`WinUsb_Initialize / ControlTransfer / ReadPipe / WritePipe / QueryPipeEx / SetPipePolicy / GetPipePolicy / GetAssociatedInterface / SetCurrentAlternateSetting / ReadIsochPipeAsap / RegisterIsochBuffer / AbortPipe / FlushPipe / ResetPipe`
- **用到等时（isochronous）传输**，带运行时能力检测（"WinUSB DLL available (%s isoch support)"）
- 有热插拔（`WinUsbHotplug`）
- Linux 等价物：libusb（bulk/control/iso 全覆盖）

## 固件 / FPGA（Linux 驱动必须复刻的启动流程）

exe 内 BSP 层日志字符串揭示的启动序列：
1. `GetFirmwareVersion` → 读设备固件版本（`Firmware version: %04x`）
2. 版本校验：`Expected firmware version %04x, got %04x`，不符则 `Start firmware upgrade: %d bytes`（固件升级）
3. `IsFpgaDone` / `Fpga is already done` → 检查 FPGA 是否已配置
4. `Start FPGA configure: %d bytes` → 上传位流（Xilinx 流程：`INIT_B` 等待 → configure → done）
5. `get fpga bin version` → `Expected fpga bin version %04x`

- 未找到外部固件/位流文件（安装目录无 .bin/.bit/.fw），**大概率内嵌 exe 内（.rdata 或 Qt 资源，可能 zlib 压缩）**
- 全文件扫描 Xilinx 同步字 `AA995566` 无命中 → 位流应该是压缩存储或非原始格式
- 待办：Ghidra 定位 FPGA_CONFIG / FpgaConfig 函数及内嵌 blob

## 文件格式

- `.dswb` = "DSWave Binary"（采集数据，UI 过滤器字符串确认）
- `.dswc` = 配置文件（`AppData/DSCope M454/{OSC,DAQ,AWG}/Default*.dswc`）
  - 外层：ZIP，单一条目 `dsw_configs`
  - 内层：解压后仍是二进制（自定义序列化或加密）→ 需逆向其读写函数
- 设备三种模式：OSC（示波器）/ DAQ（数据采集）/ AWG（任意波形发生器）

## 工具链（本机已就绪）

- REA CLI：`rea-agents@6.5.0`（`~/AppData/Roaming/npm/rea`）
- Ghidra 12.1.4：`C:\Users\Administrator\Documents\dswave_re\tools\ghidra_12.1.4_PUBLIC`
- JDK 21：`C:\Users\Administrator\Documents\dswave_re\tools\jdk-21.0.12.1+1`
- 环境变量（每次命令需带）：`GHIDRA_INSTALL_DIR` + `JAVA_HOME` + PATH 前置 jdk/bin

## Fedora 移植候选架构（待分析结果确认）

1. **首选：libsigrok 设备驱动**（C）— 复刻 USB 协议 + 固件/FPGA 上传，UI 用现成 PulseView，解码器用 libsigrokdecode（DSWave 的 40 种解码器大部分已有对应物）
2. 参考：libsigrok 现有 dreamsourcelab 驱动（老 DSLogic/DSCope，GPL）+ DSView 源码，对比 M 系列协议差异
3. 备选：完整 Qt6 应用重写（工程量大一个数量级）

## 已提取的静态情报（待 Ghidra 确认字段语义）

- **内部命名空间**：`dsv::device::*`（`UsbAnalyzerSessionControl`、`DeviceSession`、`ISession`）、`dsv::qtui::*`、`dsv::config::*`、`dsv::com::SingleShotTimer`。RTTI 已剥，仅存 27 处 std::bind 残片
- **Qt 类锚点**：`GetDevicePath`、`AddDevice`、`RefreshDevices`、`DeviceMode/DeviceParam`、`TriggerDock`、`MathDock`、`TimeViewArea`、`FftViewArea`、`LissajousViewArea` 等（`qt_class_candidates.txt`）
- **内嵌 blob**（`blobs/`，zlib 流，文件内偏移）：
  - `bin_a`@0xCA1489、`bin_b`@0xCAFD4A：各 172,160 字节，稀疏（大量零），互差 12,865 字节——疑似两型号的 FPGA 位流/固件（非 Xilinx 原始格式，无 AA995566 同步字）
  - xml_a..d：嵌入式 SVG 图标（含厂商中文主体名"深圳市梦源格物科技有限公司"）
- **设备 profile 表**（.rdata，名字后跟结构）：采样率列表 `[1k,2k,5k,10k,20k,50k,100k,200k,500k,1M,2M,5M]`，其后字段含 `100 MHz`、`16`（通道数?）；X1 与 M454 仅一处字段不同（3,1 vs 2,1，疑为设备类别/通道配置）
- **开源对照**：libsigrok `dreamsourcelab-dslogic` 老协议（GPL）：`.fw` FPGA 位流、`dslogic_profile{vid,pid,fw,caps,mem_depth}`、`dslogic_version/mode/trigger_pos` 结构、重枚举等待 3s
- **REA 超时参数**：`REA_GHIDRA_STARTUP_TIMEOUT_MS`（默认 330s，本机 12MB PE 需 >5.5min，已设 3600000）

## HAL 层结构（反编译确认）

- 源码路径（assert 泄漏）：`..\..\..\hal\usb\usbbsp.cpp`
- **HAL 是 libusb API 形状的封装**：成员 `m_libusb`、`m_usb_handle`，日志字面量 `libusb_device_handle is null`，错误码 `-5 (0xFFFFFFFB)` 即 libusb 错误码风格 → Windows 底层 WinUSB（动态 GetProcAddress），**Linux 移植时 HAL 可直接对接真 libusb**
- 类族：`hal::UsbBsp2x`（USB2.0 设备）/ `hal::UsbBsp3x`（USB3.0 设备），各有 `RegQueueThread()`；同一安全方法装在 3 张虚表（0xfef868/0xfefa58/0xfefc48 文件偏移处）
- 安全握手（`FUN_1403407d0`，设备打开流程的一部分）：
  1. `m_libusb` 虚表 `+0x1A0` GetSecurityKey(this, uint16 buf[8])（16 字节密钥）
  2. 逐个检查 8 个 16 位字是否 `0xFFFF`（未配对状态）
  3. 虚表 `+0x198` SecurityCheck(buf,8) 校验；失败报 "security check of usb device (%s)"
  4. 虚表 `+0x1A8` SetSecurityKey 写入新密钥（首次配对）
- 协议函数入口（Ghidra VA）：
  - 设备 Open：`0x140340720`；Close：`0x140340920`；安全握手：`0x1403407d0`
  - 寄存器写（"Queue set 0x%02X=0x%04X"）：引用点 `0x14034ba31`（2x）/`0x14034bba6`（3x）
  - FPGA 配置（"Start FPGA configure"）：引用点 `0x14034c3da`
  - WinUSB API 装载器：`FUN_1403c86a0`
- SCPI 为文本协议，运行时拼装后经 `ScpiWrite` 发送，**设备端解析**并回执命令号（"scpi command %d handled"）
- blobs/bin_a、bin_b 已排除固件嫌疑（172,160 字节中仅 ~6-8K 非零，疑为校准/演示数据）

- 老驱动 PID 对照（libsigrok dreamsourcelab-dslogic，全 FX2）：`0x0001` DSLogic、`0x0002` DSCope、`0x0003` DSLogic Pro、`0x0020` Plus、`0x0021` Basic；inf 的 `0001–001F/0080–008F` 为新老系列预留，M454 具体 PID 待插机确认（老表未覆盖的即新设备）

## 已还原的协议细节（反编译确认，伪代码在 decomp/）

**FPGA 配置序列**（`FUN_14034c3b0` = UsbBsp3x::FpgaConfigure，虚表 +0x58）：
1. `WriteReg(0xFE, 0xFFFE, "PROG_B=0")` → 休眠 1ms → `WriteReg(0xFE, 0x0001, "PROG_B=1")`
2. `FUN_14035c020` 校验/暂存位流（失败 = "Invalid FPGA bin file"，错误码 -6）
3. 轮询 `ReadReg(0xFF, "HW_STATUS")` 最多 11 次，等 `status & 2`（INIT_B 置位）
4. `WriteReg(0xFC, size&0xFFFF, "SET_BULK_SIZE_LOW")`、`WriteReg(0xFD, size>>16, "SET_BULK_SIZE_HIGH")`
5. `FUN_140341270(..., "FPGA_CONFIG")` 推送位流数据
6. 轮询 `IsFpgaDone`（虚表 +0x50）11 次 × 50ms → "FPGA configure done"

**寄存器队列**（`FUN_14034b8c0` = RegQueueThread）：
- 队列节点 0x28 字节：`+0` 寄存器地址(u8)、`+2` 值(u16)、`+8` 名称字符串、`+0x10` 长度
- 握手：`FUN_14034ae50` ×2（Prepare / Wait Ready），处理完再一次（Done）
- 单笔写 = `FUN_140340fd0(dev, 3字节包头, 3, name)`；日志 "Queue set %s(0x%02X)=0x%04X"

**BSP 类虚表**（`_vtables.txt`，2x/3x 各一张，59 槽）：`+0x10 Open(0x140340720) / +0x18 Close(0x140340920) / +0x20 ?(0x140340a80) / +0x50 IsFpgaDone / +0x58 FpgaConfigure(2x:0x140343b30 / 3x:0x14034c3b0) / +0x78 安全校验编排(0x1403407d0) / +0x120 WriteReg / +0x138 ReadReg`

**下一步逆向入口**：`FUN_140340fd0`（寄存器写 USB 帧）、`FUN_140349e30`（WriteReg 公共路径）、`FUN_14035c020`（位流校验，含文件头格式）、ScpiWrite 引用者（`_string_xrefs.txt`）、安全密钥三槽实现（m_libusb 虚表 +0x198/+0x1a0/+0x1a8，在 `_vtables.txt` 中找）

## 实机运行情报（PID 0x0080 已确认，日志在 capture/dswave_session.log）

- **PID = 0x0080**，设备名 "USB-based DSL Instrument v3"，WinUSB 绑定，位置：USB3 根集线器 Port 7
- **open 时 speed: 4**（libusb SUPER=5Gbps）→ 走 `hal::UsbBsp3x` 路径
- **FPGA 位流 466,408 字节**（开机每次上传，~110ms 完成）
- 开机状态机：INIT → OPEN → FPGA configure → READY → ADC init → Zero info → flow pause/stop → SCPI 配置
- 默认采样配置：存储深度 1,000,000（0x3D0900），数字 100 MS/s，模拟默认 200 kS/s（可到 100M 时基字段）
- 通道：模拟 CH0-3（Vdiv 默认 0x30D40=200000、0xF4240=1000000，单位疑似 µV/div）、数字 CH0-7+（触发通道字段）

**SCPI 命令词汇表（实测）**：
`命令`：`:LOOPModeEnable u64`、`:SAMPLEtime u64`、`:STORAGEdepth u64`、`:AUTORATEModeEnable`、`:DIGITAL:Threshold`、`:ANALOG:CHANNEL:{Enable|Invert|Coupling|BWlimit|Vdiv|Offset|TRIGGERlevel}`（首参通道号）、`:DIGITAL:CHANNEL:Enable`、`:TRIGger:{Mode|Channel|Type|PULSEtime|Margin|HOLDtime|SAMPLEindex}`、`:Sync:Word`、`:Device:Index`
`查询`：`:ANALOG:SAMPLE:{Depth?|Rate?}`、`:DIGITAL:SAMPLE:{Depth?|Rate?}`
- SCPI 传输仍是私有封装（ScpiWrite 的 USB 帧格式待抓包确认）；设备端解析并回执
- 其他日志行：`BSP: Set loop mode`、`Sent flow pause/stop command`、`MSO ZERO: Zero info loaded`、`AddDevice: Add device`

## 抓包状态

- USBPcap 1.5.4 已装（winget，仓库已迁 github.com/desowin/usbpcap），**过滤器需重启后挂载根集线器**（UpperFilters 现为空，`\\.\USBPcapN` 不存在）
- 重启后流程：4 根集线器各起一个 `-A --inject-descriptors -s 256` 捕获 → 启动 DSWave ~40s → tshark 分析（tshark 已有：`C:\Program Files\Wireshark\tshark.exe`）
- 描述符/端点表/安全密钥字节流/FPGA_CONFIG 帧格式均从该抓包获取

## 待办

- [ ] REA/Ghidra 分析：USB 命令帧格式、端点布局、初始化序列
- [ ] 定位并导出内嵌固件 + FPGA 位流（从 "Start FPGA configure" 日志函数反查 blob 引用）
- [ ] `.dsw_configs` 序列化格式；`.dswb` 格式
- [ ] 插上设备确认具体 PID / 字符串描述符 / 端点表（lsusb）
- [ ] 对比老协议，圈定 M454 新增部分
