# 逆向环境重建指南（按需）

Linux 端开发**大多数情况不需要原版软件**：协议规范（PROTOCOL.md）、关键函数伪代码（decomp/）、
帧级抓包轨迹（capture/）、FPGA 位流（firmware/）都已在仓库中。

需要**继续深度逆向**以下内容时，才需要重建 Ghidra 分析环境：
- M1：SCPI 寄存器编码（reg 0x01/0x0E/0x0F 逐字编码 + 64B 回执）
- `.dswb` / `.dswc` 文件格式
- AWG 波形下载格式、DAQ 长采集模式
- SecurityCheck 算法补全

## 原版软件获取（自行下载，勿入仓库）

DSWave 是 DreamSourceLab 闭源软件，**请从官方渠道自行下载**（本仓库不再分发）：

- 版本：DSWave **v1.2.1 x64**（Windows）
- 官网下载页：www.dreamsourcelab.cn / dreamsourcelab.com（产品 DSCope M454 的软件栏目）
- 安装后核对主程序 SHA256，确保与逆向数据同版本：

```
a21a1d410593c4981f1d10309e7a819e60bbaca2558563249ee939bb37eca42c   DSWave.exe (v1.2.1, 18,449,472 B)
```

（Windows: `Get-FileHash DSWave.exe`；Linux/Wine: `sha256sum DSWave.exe`）

## 重建 Ghidra 项目（约 10 分钟）

```bash
# 1. 装 JDK 21 与 Ghidra 12.1.x（或最新），pip install pyghidra
# 2. 用仓库工具导入并分析（extract_bsp.py 会自动建项目）：
#    修改脚本顶部 TARGET 指向你安装的 DSWave.exe 路径，然后先运行其中的导入分支
#    或直接用 Ghidra GUI: File > Import File > DSWave.exe > 分析全部默认选项
# 3. 之后用 extract_bsp.py 的 want 列表加地址批量反编译（修改地址后重跑，项目秒级复用）
```

## 常用入口地址（详见 NOTES.md）

| 目标 | 入口 |
|---|---|
| SCPI 写函数 | 搜字符串 "ScpiWrite" 的引用（decomp/_string_xrefs.txt 有现成映射） |
| SCPI 命令表构造 | 搜 "SCPI command %.*s done" 引用链 |
| 寄存器队列 | `FUN_14034b8c0`（RegQueueThread）、`FUN_140340fd0`（写原语） |
| 安全校验 | `FUN_1403407d0`（编排）、`0x140340b20`（挑战-应答，已半解） |
| 文件保存 | 搜 "DSWave Binary" / "dsw_configs" 引用 |

## 动态验证（可选，Windows 或 Wine）

- Frida 钩子工具已在仓库：`hook_winusb.js` + `run_trace.py`（依赖 `pip install frida-tools`）
- 用途：改参数（如换采样率）后抓原版行为，与逆向结论互验；Linux 端可用 Wine + Frida 试试，或借 Windows 机器
