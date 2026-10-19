#!/usr/bin/env python3
"""DSWave-Linux: DSCope M454 (VID 2a0e PID 0080) native Linux host app.
Protocol from reverse engineering (PROTOCOL.md). v1: FPGA load + captured
startup register replay + bulk stream acquisition + pyqtgraph GUI."""
import sys, time, json, struct, os, threading

VID, PID = 0x2a0e, 0x0080
EP_OUT, EP_IN = 0x02, 0x86
REQ_REG = 0xB1      # vendor OUT: [reg u8][val u16]
REQ_MOD = 0xB0      # vendor OUT module cmd (FPGA ctrl uses this)
REQ_RD  = 0xB2      # vendor IN read
BITSTREAM = os.path.join(os.path.dirname(__file__), 'firmware', 'm454_fpga_bitstream.bin')

class M454:
    def __init__(self):
        import usb.core, usb.util
        self.dev = usb.core.find(idVendor=VID, idProduct=PID)
        if self.dev is None: raise RuntimeError('M454 not found (2a0e:0080)')
        self.dev.set_configuration()
        self.cfg = self.dev.get_active_configuration()
        usb.util.claim_interface(self.dev, 0)

    def wreg(self, req, reg, val, timeout=2000):
        data = struct.pack('<BH', reg, val)
        return self.dev.ctrl_transfer(0x40, req, 0, 0, data, timeout)

    def read(self, n, timeout=2000):
        return self.dev.ctrl_transfer(0xC0, REQ_RD, 0, 0, n, timeout)

    def status(self):
        self.wreg(REQ_REG, 0xFF, 2)
        return struct.unpack('<H', bytes(self.read(2)))[0]

    def fw_version(self):
        self.wreg(REQ_REG, 0xF0, 2)
        return struct.unpack('<H', bytes(self.read(2)))[0]

    def wake_prelude(self):
        """DSWave's pre-FPGA handshake: string descriptors + F0/F2 queries
        make the MCU raise FPGA INIT_B."""
        self.dev.ctrl_transfer(0x80, 0x06, 0x0300, 0x0000, 4, 2000)
        self.dev.ctrl_transfer(0x80, 0x06, 0x0301, 0x0409, 255, 2000)
        self.dev.ctrl_transfer(0x80, 0x06, 0x0300, 0x0000, 4, 2000)
        self.dev.ctrl_transfer(0x80, 0x06, 0x0302, 0x0409, 255, 2000)
        self.wreg(REQ_REG, 0xF0, 2); self.read(2)
        self.wreg(REQ_REG, 0xF2, 2); self.read(2)

    def fpga_load(self, path=BITSTREAM, force=False):
        self.wake_prelude()
        st = self.status()
        print(f'  fpga status after prelude: 0x{st:04x}')
        if st & 0x80 and not force: return f'already configured (0x{st:04x})'
        blob = open(path, 'rb').read()
        self.wreg(REQ_MOD, 0xFE, 0xFFFE); time.sleep(0.01)
        print('  fpga status after PROG_B=0: 0x%04x' % self.status())
        self.wreg(REQ_MOD, 0xFE, 0x0001)
        ok = False
        for _ in range(100):
            st = self.status()
            if st & 2: ok = True; break
            time.sleep(0.01)
        print(f'  fpga status after PROG_B=1: 0x{st:04x} INIT_B={"OK" if ok else "TIMEOUT"}')
        self.wreg(REQ_MOD, 0xFC, len(blob) & 0xFFFF)
        self.wreg(REQ_MOD, 0xFD, len(blob) >> 16)
        wrote = 0
        for off in range(0, len(blob), 32768):
            for attempt in range(3):
                try:
                    wrote += self.dev.write(EP_OUT, blob[off:off+32768], 10000); break
                except Exception as e:
                    if attempt == 2: print('  write fail @%d: %s' % (off, e))
                    time.sleep(0.2)
        print(f'  bulk wrote {wrote}/{len(blob)} B')
        for _ in range(60):
            st = self.status()
            if st & 0x80: return f'configured 0x{st:04x} ({len(blob)} B)'
            time.sleep(0.1)
        raise RuntimeError(f'FPGA configure timeout, status 0x{st:04x}')

    def replay_startup(self, trace_jsonl):
        """Replay captured OUT control transfers (register writes) in order."""
        n = 0
        for line in open(trace_jsonl):
            try: r = json.loads(line)
            except: continue
            tprev = getattr(self, '_t', None)
            td = 0
            if tprev is not None and r.get('t'):
                td = min(max(r['t'] - tprev, 0), 50) / 1000.0
            if r.get('t'): self._t = r['t']
            if td: time.sleep(td)
            api = r.get('api')
            if api == 'WinUsb_ControlTransfer':
                if r.get('dir') == 'out' and r.get('data') and r.get('setup'):
                    s = bytes.fromhex(r['setup'])
                    b = bytes.fromhex(r['data'])
                    if s[0] == 0x40 and len(b) >= 1:
                        self.dev.ctrl_transfer(s[0], s[1], s[2] | s[3] << 8, s[4] | s[5] << 8, b, 2000)
                        n += 1
                elif r.get('dir') == 'in' and r.get('len'):
                    try: self.read(r['len'])
                    except Exception: pass
            elif api == 'WinUsb_WritePipe':
                try:
                    if not getattr(self, '_fpga_sent', False):
                        blob = open(BITSTREAM, 'rb').read()
                        self.dev.write(EP_OUT, blob, 30000)
                        self._fpga_sent = True
                        n += 1
                except Exception as e:
                    print('  bitstream write:', e)
            elif api == 'WinUsb_ReadPipe':
                ep = int(r.get('ep', hex(EP_IN)), 16) if isinstance(r.get('ep'), str) else EP_IN
                remaining = r.get('len', 4096)
                try:
                    while remaining > 0:
                        chunk = min(remaining, 4096)
                        d = bytes(self.dev.read(ep, chunk, 3000))
                        if not d: break
                        if not hasattr(self, 'rx'): self.rx = []
                        self.rx.append(d)
                        remaining -= len(d)
                    if remaining == 0: n += 1
                except Exception:
                    pass
        return n

    def stream_read(self, n=60096, timeout=3000):
        return self.dev.read(EP_IN, n, timeout)

def run_test(bitstream, trace):
    import threading
    m = M454()
    print('device open OK, fw 0x%04x' % m.fw_version())
    print('fpga:', m.fpga_load(bitstream, force=True))
    blocks = []
    n = m.replay_startup(trace)
    print('replayed %d transfers (incl. bulk reads)' % n)
    t0 = time.time()
    while time.time() - t0 < 8:
        try:
            b = bytes(m.dev.read(EP_IN, 60096, 4000))
            if b: blocks.append(b)
        except Exception:
            break
    total = sum(len(b) for b in blocks)
    print(f'post-replay blocks: {len(blocks)}  total: {total} B')
    for b in blocks[:4]:
        if len(b) >= 32:
            ts1, ts2 = struct.unpack('<QQ', b[:16])
            print(f'  block {len(b)}B ts={ts1}..{ts2} payload={b[16:40].hex()}')

def unpack_ch(rx):
    ch0, ch1 = [], []
    for b in rx:
        p = b[16:]
        n = len(p) // 8
        vals = struct.unpack('<%df' % (n * 2), p[:n * 8])
        ch0.extend(vals[0::2]); ch1.extend(vals[1::2])
    return ch0, ch1

def run_gui(bitstream, trace):
    import pyqtgraph as pg
    from pyqtgraph.Qt import QtWidgets
    m = M454()
    print('fpga:', m.fpga_load())
    n = m.replay_startup(trace)
    print('acquired %d transfers' % n)
    app = QtWidgets.QApplication(sys.argv)
    win = QtWidgets.QMainWindow(); win.setWindowTitle('DSWave-Linux — DSCope M454')
    cw = QtWidgets.QWidget(); win.setCentralWidget(cw)
    lay = QtWidgets.QVBoxLayout(cw)
    pw = pg.PlotWidget(title='CH0/CH1 (V)', labels={'left': 'V', 'bottom': 'sample'})
    lay.addWidget(pw)
    c0 = pw.plot(pen='y', name='CH0'); c1 = pw.plot(pen='c', name='CH1')
    bar = QtWidgets.QHBoxLayout()
    btn_run = QtWidgets.QPushButton('Run (重新采集)'); btn_csv = QtWidgets.QPushButton('导出 CSV')
    lbl = QtWidgets.QLabel(''); bar.addWidget(btn_run); bar.addWidget(btn_csv); bar.addWidget(lbl)
    lay.addLayout(bar)
    state = {'n': 0}
    def show():
        ch0, ch1 = unpack_ch(getattr(m, 'rx', []))
        c0.setData(ch0[-5000:]); c1.setData(ch1[-5000:])
        lbl.setText(f'CH0 {len(ch0)} samples | CH1 {len(ch1)}')
    def do_run():
        m.rx = []
        m.replay_startup(trace); show()
    def do_csv():
        ch0, ch1 = unpack_ch(getattr(m, 'rx', []))
        import csv
        with open('capture_out.csv', 'w', newline='') as f:
            w = csv.writer(f); w.writerow(['sample', 'CH0_V', 'CH1_V'])
            for i, (a, b2) in enumerate(zip(ch0, ch1)): w.writerow([i, a, b2])
        lbl.setText(f'saved capture_out.csv ({len(ch0)} rows)')
    btn_run.clicked.connect(do_run); btn_csv.clicked.connect(do_csv)
    show(); win.resize(1000, 620); win.show(); app.exec()

if __name__ == '__main__':
    base = os.path.dirname(os.path.abspath(__file__))
    bs = os.path.join(base, 'firmware', 'm454_fpga_bitstream.bin')
    import glob; _c = os.path.join(base, 'capture')
    _t = sorted(glob.glob(os.path.join(_c, 'trace_*_run_archive.jsonl')))
    tr = _t[-1] if _t else os.path.join(_c, 'winusb_trace.jsonl')
    if '--test' in sys.argv:
        run_test(bs, tr)
    else:
        run_gui(bs, tr)
