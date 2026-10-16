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
