import os, sys, time
os.environ['GHIDRA_INSTALL_DIR'] = r'C:\Users\Administrator\Documents\dswave_re\tools\ghidra_12.1.4_PUBLIC'
os.environ['USE_BUNDLED_JDK'] = 'true'

import pyghidra
pyghidra.start()

from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.app.cmd.function import CreateFunctionCmd
from ghidra.program.model.symbol import RefType
from ghidra.util.task import ConsoleTaskMonitor

TARGET = r"C:\Program Files\DSWave\DSWave.exe"
OUT = r"C:\Users\Administrator\Documents\dswave_re\decomp"
os.makedirs(OUT, exist_ok=True)
mon = ConsoleTaskMonitor()

print("[1] opening program (analyze if new)...", flush=True)
t0 = time.time()
PROJ_DIR = r"C:\Users\Administrator\Documents\dswave_re\ghidra_proj"
os.makedirs(PROJ_DIR, exist_ok=True)
from ghidra.base.project import GhidraProject
gp = GhidraProject.openProject(PROJ_DIR, "dswave", True)
program = gp.openProgram("/", "DSWave.exe", False)
print("    opened program: %s" % program, flush=True)
fm = program.getFunctionManager()
listing = program.getListing()
print("    done in %.0fs, functions=%d" % (time.time()-t0, fm.getFunctionCount()), flush=True)

def toAddr(v): return program.getAddressFactory().getAddress(hex(v))

# ---------- force function creation at code-gap addresses ----------
GAP_REFS = [0x14034ba31, 0x14034bba6, 0x14034c3da]
def find_entry_near(ref):
    addr = toAddr(ref)
    f = fm.getFunctionContaining(addr)
    if f is not None:
        return f.getEntryPoint()
    # walk back to a terminator (ret / unconditional jmp / int3) then function starts after
    cur = listing.getInstructionBefore(addr)
    for _ in range(4000):
        if cur is None:
            return None
        mn = cur.getMnemonicString()
        ftype = cur.getFlowType()
        if mn in ("RET", "INT3", "UD2") or ftype.isTerminal():
            nxt = listing.getInstructionAfter(cur.getAddress())
            if nxt is not None:
                return nxt.getAddress()
            return None
        f2 = fm.getFunctionContaining(cur.getAddress())
        if f2 is not None:
            return None  # inside an existing function already
        cur = listing.getInstructionBefore(cur.getAddress())
    return None

entries = set()
for ref in GAP_REFS:
    e = find_entry_near(ref)
    print("    gap %x -> entry %s" % (ref, e), flush=True)
    if e is not None:
        cmd = CreateFunctionCmd(e)
        if cmd.applyTo(program, mon):
            entries.add(e.getOffset())
        else:
            print("      create failed at %s" % e, flush=True)

# ---------- collect target functions ----------
want = set(entries) | {0x1403bb4d0, 0x1403bad60, 0x1403bad90,
                       0x140340720, 0x140340920, 0x140340a80, 0x140340ca0}

# find code refs to marker strings; add containing functions (or forced entries)
MARKERS = ["ScpiWrite", "DSWave Binary", "dsw_configs", "Start FPGA configure",
           "Queue set %s(0x%02X)=0x%04X", "Failed to get security key",
           "Failed to get firmware version", "FPGA_CONFIG",
           "Wait FPGA INIT_B", "IspWriteData failed"]
mem = program.getMemory()
refmgr = program.getReferenceManager()
for m in MARKERS:
    a = mem.findBytes(mem.getMinAddress(), m.encode('utf-8'), None, True, mon)
    if a is None:
        # try unicode search fallback: skip
        print("    marker not found: %r" % m, flush=True)
        continue
    refs = list(refmgr.getReferencesTo(a))
    print("    marker %r @ %s refs=%d" % (m, a, len(refs)), flush=True)
    for r in refs[:12]:
        src = r.getFromAddress()
        f = fm.getFunctionContaining(src)
        if f is not None:
            want.add(f.getEntryPoint().getOffset())
        else:
            e = find_entry_near(src.getOffset())
            if e is not None:
                CreateFunctionCmd(e).applyTo(program, mon)
                want.add(e.getOffset())

# ---------- decompile everything ----------
print("[2] decompiling %d functions..." % len(want), flush=True)
dec = DecompInterface()
dec.setOptions(DecompileOptions())
dec.openProgram(program)
index = []
for va in sorted(want):
    f = fm.getFunctionAt(toAddr(va))
    if f is None:
        f = fm.getFunctionContaining(toAddr(va))
    if f is None:
        continue
    res = dec.decompileFunction(f, 180, mon)
    if res.decompileCompleted():
        code = res.getDecompiledFunction().getC()
        path = os.path.join(OUT, "fn_%x.c" % f.getEntryPoint().getOffset())
        open(path, "w", encoding="utf-8").write("// %s\n%s" % (f.getName(), code))
        index.append((f.getEntryPoint().getOffset(), f.getName(), len(code)))
    else:
        print("    decompile failed: %x" % va, flush=True)
open(os.path.join(OUT, "_index.txt"), "w").write(
    "\n".join("%x %s %d" % r for r in index))
print("    wrote %d files" % len(index), flush=True)

# ---------- vtable scan in .rdata ----------
print("[3] vtable scan...", flush=True)
blocks = [b for b in mem.getBlocks() if b.getName() in (".rdata", ".data")]
text = [b for b in mem.getBlocks() if b.getName() == ".text"][0]
t0v, t1v = text.getStart().getOffset(), text.getEnd().getOffset()
from ghidra.program.model.mem import MemoryAccessException
vt_out = open(os.path.join(OUT, "_vtables.txt"), "w")
for b in blocks:
    cur = b.getStart()
    end = b.getEnd()
    cluster = []
    cluster_start = None
    while cur.compareTo(end) < 0:
        try:
            q = mem.getLong(cur)
        except MemoryAccessException:
            q = None
        if q is not None and t0v <= q < t1v and (q & 7) == 0:
            if cluster_start is None:
                cluster_start = cur.getOffset()
            cluster.append(q)
        else:
            if len(cluster) >= 6:
                vt_out.write("vtable @ %x entries=%d\n" % (cluster_start, len(cluster)))
                for i, v in enumerate(cluster[:80]):
                    fn = fm.getFunctionAt(toAddr(v))
                    vt_out.write("  +0x%03x: %x %s\n" % (i * 8, v, fn.getName() if fn else ""))
            cluster = []
            cluster_start = None
        cur = cur.add(8)
vt_out.close()

# ---------- save string xref map for BSP layer ----------
print("[4] string xref map...", flush=True)
sx = open(os.path.join(OUT, "_string_xrefs.txt"), "w")
di = listing.getDefinedData(True)
for d in di:
    v = d.getValue()
    if isinstance(v, str) and ("BSP:" in v or "SCPI" in v or "scpi" in v or "FPGA" in v or "firmware" in v.lower()):
        refs = list(refmgr.getReferencesTo(d.getAddress()))
        for r in refs[:6]:
            f = fm.getFunctionContaining(r.getFromAddress())
            sx.write("%x %r <- %x in %s\n" % (d.getAddress().getOffset(), v[:70], r.getFromAddress().getOffset(), f.getName() if f else "?"))
sx.close()
print("ALL DONE", flush=True)
