"""Apply one source mutation at a time to a temp copy and require the unit tests to FAIL."""
import os, shutil, subprocess, sys, tempfile
HERE = os.path.dirname(os.path.abspath(__file__))
MUTATIONS = [
    ("endian u32", "btga_ps1/binio.py", 'struct.unpack_from("<I", self.data, off)[0]', 'struct.unpack_from(">I", self.data, off)[0]'),
    ("bounds check removed", "btga_ps1/binio.py", "if off < 0 or size < 0 or off + size > len(self.data):", "if False:"),
    ("4bpp nibble order", "btga_ps1/textures.py", "out.append((b >> 4) if (i & 1) else (b & 0xF))", "out.append((b & 0xF) if (i & 1) else (b >> 4))"),
    ("PLT stride ignores clut_count", "btga_ps1/textures.py", "off += 8 + 32 * n", "off += 8 + 32"),
    ("BGR555 channel swap", "btga_ps1/binio.py", "r = (v & 0x1F) << 3", "r = ((v >> 10) & 0x1F) << 3"),
    ("engine 4-byte cursor floor dropped", "btga_ps1/textures.py", "engine_cur = pix_off + (npix & ~3)", "engine_cur = pix_off + npix"),
    ("quad OBJ order Z-pattern", "btga_ps1/models.py", 'order = [0, 1, 2, 3] if prim["corners"] == 4', 'order = [0, 1, 3, 2] if prim["corners"] == 4'),
    ("vertex pair hi/lo swapped", "btga_ps1/models.py", 'state["vert"][a], state["vert"][b] = hi, lo', 'state["vert"][a], state["vert"][b] = lo, hi'),
    ("vertex index bound removed", "btga_ps1/models.py", "if lo >= nverts or hi >= nverts:", "if False:"),
    ("TTT texture bound removed", "btga_ps1/models.py", 'if textured and (state["texture"] is None or state["texture"] >= ntex):', "if False:"),
    ("FLB size check removed", "btga_ps1/level.py", "if len(r) != 4 + 4 * w * h:", "if False:"),
    ("TEX trailing-bytes check removed", "btga_ps1/textures.py", 'raise FormatError("%s: %d trailing/missing bytes after last entry" % (name, len(r) - off))', "pass"),
]
fails = 0
for label, rel, old, new in MUTATIONS:
    with tempfile.TemporaryDirectory() as tmp:
        dst = os.path.join(tmp, "pkg")
        shutil.copytree(HERE, dst, ignore=shutil.ignore_patterns("__pycache__", "*.pyc", "out*"))
        p = os.path.join(dst, rel)
        with open(p) as fh:
            src = fh.read()
        if old not in src:
            print("NOT APPLIED  %s" % label); fails += 1; continue
        with open(p, "w") as fh:
            fh.write(src.replace(old, new, 1))
        r = subprocess.run([sys.executable, "-m", "unittest", "discover", "-s", "tests", "-t", "."], cwd=dst,
                           capture_output=True, text=True)
        killed = r.returncode != 0
        print("%-8s %s" % ("KILLED" if killed else "SURVIVED", label))
        fails += not killed
print("mutations: %d, survived/not-applied: %d" % (len(MUTATIONS), fails))
sys.exit(1 if fails else 0)
