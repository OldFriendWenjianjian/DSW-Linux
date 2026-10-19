# DSW-Linux — DreamSourceLab DSWave 逆向与 Linux 移植

目标：让 DSCope M454（DSWave v1.2.1 闭源上位机专属设备）在 Linux 上原生工作。

## 内容

- `PROTOCOL.md` — **完整 USB 协议规范**（实测+逆向互证）：VID 2A0E/PID 0080、EP0 命令集（0xB0/0xB1/0xB2）、端点表（bulk 0x02/0x84/0x86）、FPGA 配置序列（466,408B 位流，同步字 5599AA66）、SCPI 词汇表、安全密钥机制、采集流格式（float32 电压 + ns 时间戳块）
- `FEDORA_PORT.md` — libsigrok 驱动移植路线
- `NOTES.md` — 全部逆向情报（类结构 hal::UsbBsp2x/3x、虚表、函数地址索引）
- `firmware/m454_fpga_bitstream.bin` — 从 DSWave.exe 提取的完整 FPGA 位流
- `decomp/` — 关键函数伪代码（含 SecurityCheck 挑战-应答算法）
- `capture/` — Frida WinUSB 逐帧轨迹 + DSWave 会话日志
- `hook_winusb.js` / `run_trace.py` / `extract_bsp.py` — 可复用工具链

## 声明

仅用于互操作研究与教育目的（本人拥有的设备）。商标与版权归 DreamSourceLab 所有。

## DSWave-Linux 应用（v1）

`dswave_linux.py` — 原生 Linux M454 上位机（Python + pyusb + pyqtgraph）。

```bash
pip install --user pyusb pyqtgraph
python3 dswave_linux.py           # GUI（波形显示 + 重新采集 + CSV 导出）
python3 dswave_linux.py --test    # 无头自检（FPGA 加载 + 采集统计）
```

**实现要点**（详见 PROTOCOL.md"关键实现要点"）：
- `wake_prelude()`：GET_DESCRIPTOR×4 + F0/F2 版本查询，唤醒 MCU 拉高 INIT_B——缺这一步 FPGA 永远配置不上
- FPGA 位流加载（466,408B，PROG_B 时序 + bulk 写）
- 会话重放：按抓包时序逐字节重放（bRequest 原样、bulk 读写交织）
- 采集：单次 ~15MB（1M 深度），float32 交错通道对

**状态（2026-10-19）**：
- ✅ Windows 真机（WinUSB + pyusb/libusb）：全管线实测通过（FPGA 配置 + 15MB 采集）
- ⚠️ VMware 虚拟机直通：控制/FPGA 配置通过，但 VMware 会丢失 bulk URB 完成事件（写数据到达设备但超时返回；读流卡死）——属虚拟化层限制。建议：VM 设置 USB 控制器改为 USB 2.0 试一次，或用裸机 Linux（代码即拷即用）
