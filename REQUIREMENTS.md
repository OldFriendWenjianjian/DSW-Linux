# DSWave-Linux 功能需求规格（对照原版 DSWave v1.2.1）

> 目标：Linux 客户端**功能对等**复刻原版。本文档按原版用户手册（`screenshots/ug31_text.txt`，66 页官方手册全文提取）+ 实机 UI 拆解，每项功能标注：UI 位置 / 协议依赖 / Linux 端现状 / 实现建议。
> 原版主界面截图：`screenshots/main_window.png`。
> 协议能力对照：PROTOCOL.md；现有代码：dswave_linux.py。

## 状态图例
- ✅ 协议已逆向且代码已验证　🔶 协议已逆向待实现　⬜ 协议待破解（SCPI 编码）　🖥 纯 UI/本地计算，不依赖新协议

## 一、界面框架（手册 §1.4）

| 原版功能 | 说明 | 现状 | 建议 |
|---|---|---|---|
| 主窗口布局 | 左侧通道/触发 Dock、中央波形区、右侧解码/测量 Dock、底部解码列表 | 🖥 | PyQt QMainWindow + QDockWidget，已搭骨架（dsv 原版类名参考 NOTES.md） |
| 设备类型 | OSC 示波器 / DAQ 数据记录仪 / AWG 信号发生器 三模式切换 | 🔶（OSC 会话已通） | 模式切换=重放不同 SCPI 会话；DAQ/AWG 需各抓一次会话 |
| 语言切换 | 中文/英文 | 🖥 | Qt Linguist 或简单字典 |
| 主题风格 | 亮/暗 | 🖥 | QSS 两套 |

## 二、文件操作（手册 §2）

| 功能 | 说明 | 现状 | 建议 |
|---|---|---|---|
| 数据保存 | `.dswb` 会话保存 | ⬜ | 格式=ZIP+自定义序列化；短期可存自有格式（HDF5/npz），`.dswb` 兼容列为 P2（入口：搜 "DSWave Binary" 引用） |
| 数据打开 | 打开历史采集 | 🖥 | 同上 |
| 数据导出 | CSV/TXT/HTML | 🖥 | CSV 已实现，补 TXT/HTML |
| 快捷截图 | 波形区截图 | 🖥 | QWidget.grab() |

## 三、设备连接（手册 §3）

| 功能 | 现状 | 建议 |
|---|---|---|
| 设备枚举/热插拔 | ✅ | libusb 枚举 + udev；已实现 |
| 设备打开/初始化（版本→安全→FPGA→ADC） | ✅ | wake_prelude+FPGA 已验证；安全校验当前靠会话重放隐式通过 |
| 固件升级（ISP） | ⬜ | 低优先（设备固件 0x3110 已正常） |

## 四、示波器模式 OSC（手册 §4）——核心

### 4.1-4.3 设备配置与选项
| 功能 | 协议依赖 | 现状 |
|---|---|---|
| 模拟通道使能 CH0-3 | SCPI `:ANALOG:CHANNEL:Enable` | ⬜ SCPI 寄存器编码待破解（P1 任务，见 HANDOFF） |
| 通道选项：Vdiv/Offset/Coupling(AC/DC/GND)/BWlimit/Invert | 同上 | ⬜（词汇表全在 PROTOCOL.md §SCPI） |
| 数字通道使能 D0-15 + 阈值 | `:DIGITAL:CHANNEL:Enable`、`:DIGITAL:Threshold` | ⬜ |
| 水平参数：采样率/存储深度/时基 | `:SAMPLEtime`、`:STORAGEdepth`、`:AUTORATEModeEnable` | ⬜ |
| 其他：ACQ 模式、触发出板 | — | ⬜ |

### 4.4 触发
| 功能 | 协议 | 现状 |
|---|---|---|
| 触发类型/边沿/脉宽/码型、电平、HOLDoff、触发位置 | `:TRIGger:*` 全套词汇已录 | ⬜ 编码待破解 |

### 4.5-4.6 采集与波形查看
| 功能 | 现状 | 建议 |
|---|---|---|
| 开始/停止、单次 | ✅（重放方式） | P1 改 SCPI 直控后可参数化 |
| 波形渲染、缩放平移、跳转 | 🖥 | pyqtgraph 已有基础；补游标导航 |
| 采样率显示、复制虚拟文件 | 🖥/⬜ | — |

### 4.7 协议解码（原版 40 种）
CALIPER, COUNTER, GUESS-BITRATE, IR-JVC, IR-SHARP, MIPI-RFFE, SBUS, STEPPER-MOTOR, WIEGAND, LIN, PS2, 24C02, DALI, DHT11, MODBUS, PWM, SPDIF, XY2-100, IR-NEC, IR-SIRC, I2C, SPI, UART, CAN, USB, JTAG…（全表见 NEWS31）
**现状**：🖥 概念。**强烈建议直接接 libsigrokdecode（PulseView 同源解码库）**——上述 90% 已有现成 Python 解码器，规则同 GPL，无需重写。解码列表三级钻取（帧→项→数据）+ 搜索 + 导出用 Qt 表格实现。

### 4.8-4.13 分析功能
| 功能 | 现状 | 建议 |
|---|---|---|
| 频谱分析 FFT | 🖥 | numpy.fft + pyqtgraph（已有 FFT 区域占位） |
| 函数运算（+−×÷、FFT、积分等） | 🖥 | 符号表达式引擎 + numpy |
| 自动测量（Vpp/Vmax/Vmin/频率/周期/占空比/上升沿…30+ 项） | 🖥 | 纯数学，numpy 一批实现 |
| 时间/Y轴/区域/鼠标测量 | 🖥 | pyqtgraph 游标 + 事件 |
| XY 李萨茹图 | 🖥 | 双通道散点（原版 LissajousViewArea） |
| 余晖显示 | 🖥 | 多帧叠加渲染 |
| 直方图 | 🖥 | 统计绘制 |

## 五、数据记录仪 DAQ（手册 §5）
长时采集+低速滚动模式。功能面与 OSC 重叠（通道/测量/解码）。**现状**：⬜ 需一次 DAQ 模式会话抓包（SCPI `:LOOPModeEnable 1` 路径）。

## 六、信号发生器 AWG（手册 §6）
波形产生+预览：垂直/水平参数、任意波形下载。**现状**：⬜ AWG SCPI 词汇已在手册/日志（"AWG scpi command"），需抓一次 AWG 会话 + 波形下载格式逆向（bulk OUT 路径已通）。

## 七、实现里程碑建议（Linux 端）

1. **M1（1-2 周）**：P1 SCPI 编码破解 → 参数面板（采样率/深度/通道/触发）+ 直控采集；测量+游标+FFT
2. **M2（+1 周）**：接 libsigrokdecode 解码器 20+；解码列表 UI；导出三件套
3. **M3（+1 周）**：DAQ 模式（滚动+长时）、余晖/XY/直方图、主题/语言
4. **M4**：AWG（需波形下载格式逆向）、`.dswb` 兼容、libsigrok 驱动上游化

## 附：素材索引
- 官方手册全文：`screenshots/ug31_text.txt`（66 页，含每功能操作细节与图示页码）
- 原版主界面截图：`screenshots/main_window.png`（无设备态；带设备态截图待补：设备接 Windows 后启动原版截取 §4.6/§4.7/§4.10 各视图）
- 40 解码器全表：仓库 `NOTES.md` / NEWS31
- SCPI 词汇+默认值：`PROTOCOL.md`
- 原版 UI 类名（Dock/View 命名参考）：`qt_class_candidates.txt`
