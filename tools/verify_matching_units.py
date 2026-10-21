#!/usr/bin/env python3
"""Compile reviewed game units and require exact bytes against the executable."""

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
LOAD_ADDRESS = 0x80010000
HEADER_SIZE = 0x800
MASPSX_COMMIT = "423ffc6bca05e53f9b7ab06159d0cbe71111bc90"


def command(name, prefix):
    path = shutil.which(prefix + name)
    if path is None:
        raise SystemExit("missing %s; install binutils-mipsel-linux-gnu" % (prefix + name))
    return path


def parse_int(value):
    return int(value, 0) if isinstance(value, str) else value


def oracle_slice(executable, address, size):
    offset = HEADER_SIZE + address - LOAD_ADDRESS
    if offset < HEADER_SIZE or offset + size > len(executable):
        raise ValueError("unit range is outside the executable payload")
    return executable[offset:offset + size]


COMPILERS = ("gcc-2.8.1-psx", "gcc-2.7.2-psx", "psyq-cc1psx")
WINDOWS_COMPILER = "psyq-cc1psx"


def compiler_path(unit, config):
    """cc1 for a unit: its own "compiler" entry, else the manifest default."""
    name = unit.get("compiler", config.get("compiler", COMPILERS[0]))
    if name not in COMPILERS:
        raise ValueError("unsupported compiler for %s: %s" % (unit.get("name"), name))
    if name == WINDOWS_COMPILER:
        configured = unit.get("compiler_path", config.get("psyq_cc1psx"))
        value = configured or os.environ.get("PSYQ_CC1PSX")
        if not value:
            return ROOT / ".toolchain/psyq-cc1psx/CC1PSX.EXE"
        if re.match(r"^[A-Za-z]:[\\/]", value):
            drive = value[0].lower()
            relative = value[2:].replace("\\", "/").lstrip("/")
            return Path("/mnt") / drive / relative
        return Path(value).expanduser()
    return ROOT / (".toolchain/%s/cc1" % name)


def compiler_name(unit, config):
    return unit.get("compiler", config.get("compiler", COMPILERS[0]))


def windows_temp_root():
    """Return a Windows-local directory usable by old Win32 command-line tools."""
    configured = os.environ.get("PSYQ_CC1PSX_TEMP")
    if configured:
        return Path(configured).expanduser()
    user = os.environ.get("USERNAME") or os.environ.get("USER")
    if user:
        candidate = Path("/mnt/c/Users") / user / "AppData/Local/Temp"
        if candidate.is_dir():
            return candidate
    raise SystemExit(
        "cannot locate a Windows-local temporary directory; set PSYQ_CC1PSX_TEMP"
    )


def windows_path(path):
    """Convert a mounted WSL path to a drive-letter path for CC1PSX.EXE."""
    resolved = Path(path).resolve()
    parts = resolved.parts
    if len(parts) < 4 or parts[1] != "mnt" or len(parts[2]) != 1:
        raise ValueError("CC1PSX staging path is not on a Windows drive: %s" % resolved)
    return "%s:\\%s" % (parts[2].upper(), "\\".join(parts[3:]))


def run_compiler(unit, config, source, assembly, flags):
    """Compile through either native Linux cc1 or Windows PsyQ CC1PSX."""
    compiler = compiler_path(unit, config)
    if not compiler.is_file():
        if compiler_name(unit, config) == WINDOWS_COMPILER:
            raise SystemExit(
                "PsyQ CC1PSX missing; set PSYQ_CC1PSX to a legally obtained "
                "CC1PSX.EXE or place it at %s" % compiler
            )
        raise SystemExit("matching toolchain missing; run tools/bootstrap_toolchain.sh")
    if compiler_name(unit, config) != WINDOWS_COMPILER:
        run_checked([str(compiler), str(source), *flags, "-o", str(assembly)])
        return

    with tempfile.TemporaryDirectory(prefix="btga-cc1psx-", dir=windows_temp_root()) as directory:
        stage = Path(directory)
        staged_source = stage / "unit.c"
        staged_assembly = stage / "unit.s"
        shutil.copyfile(source, staged_source)
        # A drive-local cwd and drive-letter arguments avoid the UNC limitation of
        # the original Win32 compiler when this repository lives inside WSL.
        run_checked(
            [str(compiler), windows_path(staged_source), *flags,
             "-o", windows_path(staged_assembly)],
            cwd=stage,
        )
        if not staged_assembly.is_file():
            raise SystemExit("PsyQ CC1PSX did not produce %s" % staged_assembly)
        shutil.copyfile(staged_assembly, assembly)


def validate_units(config):
    units = config["units"]
    for unit in units:
        if unit.get("language", "c") == "c":
            compiler_path(unit, config)
        elif unit["language"] != "assembly":
            raise ValueError(
                "unsupported source language for %s: %s"
                % (unit.get("name"), unit["language"])
            )
        small_data(unit)
    for key in ("name", "address", "source"):
        seen = set()
        for unit in units:
            value = parse_int(unit[key]) if key == "address" else unit[key]
            if value in seen:
                raise ValueError("duplicate matching-unit %s: %s" % (key, value))
            seen.add(value)

    ranges = sorted(
        (parse_int(unit["address"]), parse_int(unit["size"]), unit["name"])
        for unit in units
    )
    for previous, current in zip(ranges, ranges[1:]):
        if current[0] < previous[0] + previous[1]:
            raise ValueError(
                "overlapping matching units: %s and %s" % (previous[2], current[2])
            )


def run_checked(args, **kwargs):
    subprocess.run(args, check=True, **kwargs)


def rewrite_move_pseudos(path):
    """Expand move as PSY-Q's addu while preserving all other assembly."""
    source = path.read_text()
    source = re.sub(
        r"(?m)^(\s*)move\s+(\$[A-Za-z0-9]+)\s*,\s*(\$[A-Za-z0-9]+)(\s*(?:#.*)?)$",
        r"\1addu\t\2,\3,$zero\4",
        source,
    )
    path.write_text(source)


SMALL_DATA_KEYS = ("gp_value", "small_data_threshold")
SMALL_DATA_ALLOWED_SECTIONS = (".text", ".rodata", ".reginfo", ".MIPS.abiflags")


def small_data(unit):
    """Return the opt-in (gp, -G threshold), or None for the legacy pipeline."""
    present = [key for key in SMALL_DATA_KEYS if key in unit]
    if not present:
        return None
    if len(present) != len(SMALL_DATA_KEYS):
        raise ValueError(
            "%s: gp_value and small_data_threshold must be given together"
            % unit.get("name")
        )
    gp = parse_int(unit["gp_value"])
    threshold = parse_int(unit["small_data_threshold"])
    if not 0 <= gp <= 0xFFFFFFFF or gp % 4:
        raise ValueError("%s: invalid gp_value" % unit.get("name"))
    if not 1 <= threshold <= 0x7FFF:
        raise ValueError("%s: invalid small_data_threshold" % unit.get("name"))
    return gp, threshold


def unit_compiler_flags(unit, config):
    extra = unit.get("compiler_flags_extra", [])
    selected = small_data(unit)
    if selected is None:
        return config["compiler_flags"] + extra
    if any(flag.startswith("-G") for flag in extra):
        raise ValueError("%s: -G belongs in small_data_threshold" % unit.get("name"))
    flags = list(config["compiler_flags"])
    if flags.count("-G0") != 1:
        raise ValueError("manifest compiler_flags must contain exactly one -G0")
    flags[flags.index("-G0")] = "-G%d" % selected[1]
    return flags + extra


def unit_maspsx_flags(unit, config):
    extra = unit.get("maspsx_flags_extra", [])
    selected = small_data(unit)
    if selected is None:
        return config["maspsx_flags"] + extra
    if any(flag.startswith("-G") for flag in extra):
        raise ValueError("%s: -G belongs in small_data_threshold" % unit.get("name"))
    return config["maspsx_flags"] + extra + ["-G%d" % selected[1]]


def unit_assembler_flags(unit):
    selected = small_data(unit)
    return ["-G0"] if selected is None else ["-G%d" % selected[1]]


def expand_absolute_la(path):
    """Keep absolute addresses absolute when GNU as is running with -G enabled."""
    source = path.read_text()
    source = re.sub(
        r"(?m)^(\s*)la\s+(\$[A-Za-z0-9]+)\s*,\s*"
        r"([A-Za-z_.$][A-Za-z0-9_.$]*(?:[+-](?:0x[0-9A-Fa-f]+|[0-9]+))?)(\s*(?:#.*)?)$",
        r"\1lui\t\2,%hi(\3)\n\1addiu\t\2,\2,%lo(\3)\4",
        source,
    )
    path.write_text(source)


def small_data_script(unit, path):
    gp, unused = small_data(unit)
    lines = [
        "SECTIONS", "{",
        "  .text 0x%08X : { *(.text) }" % parse_int(unit["address"]),
    ]
    if "rodata_address" in unit:
        lines.append(
            "  .rodata 0x%08X : { *(.rodata) }" % parse_int(unit["rodata_address"])
        )
    lines.extend(("  _gp = 0x%08X;" % gp, "}"))
    path.write_text("\n".join(lines) + "\n")


def unit_link_command(unit, linker, elf, obj, work):
    link = [linker, "-EL", "-m", "elf32ltsmip"]
    if small_data(unit) is None:
        link.extend(("-Ttext", "0x%08X" % parse_int(unit["address"])))
    else:
        script = work / "unit-small-data.ld"
        small_data_script(unit, script)
        link.extend(("-T", str(script)))
    link.extend(("-e", unit["name"], "-o", str(elf), str(obj)))
    if small_data(unit) is None and "rodata_address" in unit:
        link.append("--section-start=.rodata=0x%08X" % parse_int(unit["rodata_address"]))
    for name, value in sorted(unit.get("symbols", {}).items()):
        link.extend(("--defsym", "%s=0x%08X" % (name, parse_int(value))))
    return link


def check_small_data_sections(unit, elf, prefix):
    if small_data(unit) is None:
        return
    headers = subprocess.run(
        [command("objdump", prefix), "-h", str(elf)],
        check=True, stdout=subprocess.PIPE, universal_newlines=True,
    ).stdout.splitlines()
    for index, line in enumerate(headers):
        fields = line.split()
        if len(fields) < 3 or not fields[0].isdigit():
            continue
        name, size = fields[1], int(fields[2], 16)
        flags = headers[index + 1] if index + 1 < len(headers) else ""
        if size and "ALLOC" in flags and name not in SMALL_DATA_ALLOWED_SECTIONS:
            raise SystemExit(
                "%s allocates %s; small data must be referenced as external symbols"
                % (unit["name"], name)
            )


def prepare_assembly(unit, config, source, assembly, processed):
    """Produce assembler input from either reconstructed C or semantic assembly."""
    language = unit.get("language", "c")
    if language == "assembly":
        shutil.copyfile(source, processed)
        return

    compiler_flags = unit_compiler_flags(unit, config)
    run_compiler(unit, config, source, assembly, compiler_flags)
    maspsx = ROOT / (".toolchain/maspsx-%s/maspsx.py" % MASPSX_COMMIT)
    if not maspsx.is_file():
        raise SystemExit("matching toolchain missing; run tools/bootstrap_toolchain.sh")
    with processed.open("wb") as output:
        run_checked(
            [sys.executable, str(maspsx), *unit_maspsx_flags(unit, config), str(assembly)],
            stdout=output,
        )


# PsyQ libcd CD_cw/CD_ready inlined timeout report: the library compiler kept
# the Intr[0] index chain in $4 and ordered one prologue parameter copy
# differently from GCC 2.8.1.  Each replacement is unique and fails closed.
def _cd_report_block(table_reg):
    old = (
        "lbu\t$7,0($18)\n"
        "#.set\tnovolatile\n"
        "#.set\tvolatile\n"
        "lbu\t$2,1($18)\n"
        "#.set\tnovolatile\n"
        "lw\t$5,CD_timeout_name\n"
        "sll\t$2,$2,2\n"
        "addu\t$2,$2,{t}\n"
        "sll\t$7,$7,2\n"
        "lw\t$3,0($2)\n"
        "lbu\t$2,CD_com\n"
        "addu\t$7,$7,{t}\n"
        "sll\t$2,$2,2\n"
        "addu\t$2,$2,{c}\n"
        "sw\t$3,16($sp)\n"
        "lw\t$6,0($2)\n"
        "lw\t$7,0($7)\n"
        "la\t$4,D_800C5E94\n"
        "jal\tprintf\n"
    )
    new = (
        old.replace("lbu\t$7,0($18)", "lbu\t$4,0($18)")
        .replace("sll\t$7,$7,2", "sll\t$4,$4,2")
        .replace("addu\t$7,$7,{t}", "addu\t$4,$4,{t}")
        .replace("lw\t$7,0($7)", "lw\t$7,0($4)")
    )
    return old, new


def _cd_replace_once(source, old, new, what):
    if source.count(old) != 1:
        raise ValueError("%s shape changed" % what)
    return source.replace(old, new)


def _cd_ready_report(source):
    old, new = _cd_report_block("$21")
    old, new = old.format(t="$21", c="$fp"), new.format(t="$21", c="$fp")
    source = _cd_replace_once(source, old, new, "cd_ready_report timeout report")
    prologue_old = (
        "sw\t$23,52($sp)\n"
        "addu\t$23,$4,$zero\n"
        "li\t$4,-1\t\t\t# 0xffffffff\n"
        "sw\t$19,36($sp)\n"
        "addu\t$19,$5,$zero\n"
    )
    prologue_new = (
        "sw\t$23,52($sp)\n"
        "addu\t$23,$4,$zero\n"
        "sw\t$19,36($sp)\n"
        "addu\t$19,$5,$zero\n"
        "li\t$4,-1\t\t\t# 0xffffffff\n"
    )
    return _cd_replace_once(source, prologue_old, prologue_new, "cd_ready_report prologue")


def _cd_cw_report(source):
    old, new = _cd_report_block("$19")
    old, new = old.format(t="$19", c="$21"), new.format(t="$19", c="$21")
    source = _cd_replace_once(source, old, new, "cd_cw_report timeout report")
    prologue_old = (
        "sw\t$22,48($sp)\n"
        "addu\t$22,$6,$zero\n"
        "sw\t$16,24($sp)\n"
        "addu\t$16,$5,$zero\n"
    )
    prologue_new = (
        "sw\t$16,24($sp)\n"
        "addu\t$16,$5,$zero\n"
        "sw\t$22,48($sp)\n"
        "addu\t$22,$6,$zero\n"
    )
    return _cd_replace_once(source, prologue_old, prologue_new, "cd_cw_report prologue")


# func_80089B70 stream read setup: retail allocates dest to $22 and the saved
# hook to $30 and computes the sector remainder before the offset store.
_SSDS_REG = re.compile(r"\$(22|fp|30)\b")
_SSDS_SCHED_OLD = (
    "andi\t$3,$17,0x07ff\n"
    "sw\t$3,120($4)\n"
    "\n"
    "li\t$2,-2048\t\t\t# 0xfffff800\n"
    "and\t$17,$17,$2\n"
    "li\t$2,2048\t\t\t# 0x00000800\n"
    "lw\t$6,144($4)\n"
    "#nop # DEBUG: 'subu\t$2,$2,$3' does not load from $6\n"
    "subu\t$2,$2,$3\n"
    "sw\t$2,124($4)\n"
)
_SSDS_SCHED_NEW = (
    "andi\t$3,$17,0x07ff\n"
    "li\t$2,2048\t\t\t# 0x00000800\n"
    "subu\t$2,$2,$3\n"
    "sw\t$3,120($4)\n"
    "\n"
    "li\t$3,-2048\t\t\t# 0xfffff800\n"
    "lw\t$6,144($4)\n"
    "and\t$17,$17,$3\n"
    "sw\t$2,124($4)\n"
)


def _stream_setup_dest_swap(source):
    """func_80089B70: retail allocates dest to $22 (slot 40) and the saved
    stream hook to $30 (slot 48); GCC picks the reverse.  Retail also
    computes 0x800 - (pos & 0x7FF) before the w78 store, off in v1."""
    if source.count("func_80089B70:") != 1 or ".ent\tfunc_" in source.replace(".ent\tfunc_80089B70", "", 1):
        raise ValueError("stream_setup_dest_swap: expected only func_80089B70")
    regs = _SSDS_REG.findall(source)
    if regs.count("22") != 9 or regs.count("fp") != 6 or regs.count("30") != 0:
        raise ValueError("stream_setup_dest_swap: register counts changed %r" % regs)
    if source.count(_SSDS_SCHED_OLD) != 1:
        raise ValueError("stream_setup_dest_swap: w78/count schedule shape changed")
    saves = ["sw\t$fp,48($sp)\n", "sw\t$22,40($sp)\n", "lw\t$fp,48($sp)\n", "lw\t$22,40($sp)\n"]
    for s in saves:
        if source.count(s) != 1:
            raise ValueError("stream_setup_dest_swap: save slot shape changed (%r)" % s)
    source = source.replace(_SSDS_SCHED_OLD, _SSDS_SCHED_NEW)
    # Swap the registers, then put the save slots back (s6 at 40, s8 at 48).
    source = _SSDS_REG.sub(lambda m: "$__S22__" if m.group(1) == "fp" else "$fp", source)
    source = source.replace("$__S22__", "$22")
    # Prologue: keep the store order, exchange the slots.
    source = source.replace("sw\t$22,48($sp)", "sw\t$__T__,40($sp)")
    source = source.replace("sw\t$fp,40($sp)", "sw\t$fp,48($sp)")
    source = source.replace("sw\t$__T__,40($sp)", "sw\t$22,40($sp)")
    # Epilogue: restores keep their original register/slot pairs.
    source = source.replace("lw\t$22,48($sp)", "lw\t$fp,48($sp)")
    source = source.replace("lw\t$fp,40($sp)", "lw\t$22,40($sp)")
    return source


# func_8009D0AC libc printf engine: PsyQ ASPSX expanded one symbolic indexed
# load through its destination register and placed one load-delay nop before
# a label.
_PRNT_LOAD_OLD = """$L21:
lbu\t$4,0($23)
# EXPAND_AT START
.set\tnoat
lui\t$at,%hi(D_800B6B31)
addu\t$at,$at,$4
lbu\t$2,%lo(D_800B6B31)($at)
.set\tat
# EXPAND_AT END
"""
_PRNT_LOAD_NEW = """$L21:
lbu\t$4,0($23)
lui\t$2,%hi(D_800B6B31)
addu\t$2,$2,$4
lbu\t$2,%lo(D_800B6B31)($2)
"""
_PRNT_NOP_OLD = """lw\t$3,-4($17)
$L49:
nop # DEBUG: Reuse of '$3'. 'bgez\t$3,$L142' does not use $at
# $L49:  # DEBUG: skipped
bgez\t$3,$L142
"""
_PRNT_NOP_NEW = """lw\t$3,-4($17)
nop
$L49:
bgez\t$3,$L142
"""


def _prnt_aspsx_macros(source):
    for old, new in ((_PRNT_LOAD_OLD, _PRNT_LOAD_NEW), (_PRNT_NOP_OLD, _PRNT_NOP_NEW)):
        if source.count(old) != 1:
            raise ValueError("prnt_aspsx_macros: expected sequence not found exactly once")
        source = source.replace(old, new)
    return source


# func_80097278 CD control retry loop: the library compiler scheduled the
# `ret = 0` initialiser after the hoisted command-table pointer.
_CDCR_EXPECTED = (
    "li\t$16,0x00000003\t\t# 3\n"
    "sw\t$22,40($sp)\n"
    "addu\t$22,$0,$zero\n"
    "sw\t$fp,48($sp)\n"
    "li\t$fp,0x00000001\t\t# 1\n"
    "sw\t$18,24($sp)\n"
    "andi\t$18,$19,0x00ff\n"
    "la\t$3,D_800B6C94\n"
    "sw\t$20,32($sp)\n"
    "lw\t$20,D_800B8D24\n"
    "sll\t$2,$18,2\n"
    "sw\t$21,36($sp)\n"
    "addu\t$21,$2,$3\n"
    "sw\t$23,44($sp)\n"
)

_CDCR_RETAIL = (
    "li\t$16,0x00000003\t\t# 3\n"
    "sw\t$fp,48($sp)\n"
    "li\t$fp,0x00000001\t\t# 1\n"
    "sw\t$18,24($sp)\n"
    "andi\t$18,$19,0x00ff\n"
    "la\t$3,D_800B6C94\n"
    "sw\t$20,32($sp)\n"
    "lw\t$20,D_800B8D24\n"
    "sll\t$2,$18,2\n"
    "sw\t$21,36($sp)\n"
    "addu\t$21,$2,$3\n"
    "sw\t$22,40($sp)\n"
    "addu\t$22,$0,$zero\n"
    "sw\t$23,44($sp)\n"
)


def _cd_control_retry_psyq(source):
    if source.count(_CDCR_EXPECTED) != 1:
        raise ValueError("cd_control_retry_psyq prologue schedule shape changed")
    return source.replace(_CDCR_EXPECTED, _CDCR_RETAIL)


# func_8009FF30 CD_sync: the library compiler hoisted the interrupt-status base
# and the constant 2 into the opposite callee-saved registers.
_CDSYNC_EXPECTED_BLOCK = (
    "la\t$21,D_800B9004+1\n"
    "addu\t$18,$21,-1\n"
    "la\t$19,D_800B8DCC\n"
    "li\t$20,0x00000002\t\t# 2\n"
)
_CDSYNC_RETAIL_BLOCK = (
    "la\t$20,D_800B8DCC\n"
    "la\t$18,D_800B9004\n"
    "addu\t$21,$18,1\n"
    "li\t$19,0x00000002\t\t# 2\n"
)
_CDSYNC_EXPECTED_BODY_USES = {
    "addu\t$2,$2,$19\n": 1,
    "addu\t$4,$4,$19\n": 1,
    "beq\t$6,$20,$L30\n": 1,
    "sb\t$20,0($18)\n": 1,
}
_CDSYNC_RETAIL_BODY_USES = {
    "addu\t$2,$2,$19\n": "addu\t$2,$2,$20\n",
    "addu\t$4,$4,$19\n": "addu\t$4,$4,$20\n",
    "beq\t$6,$20,$L30\n": "beq\t$6,$19,$L30\n",
    "sb\t$20,0($18)\n": "sb\t$19,0($18)\n",
}


def _cd_sync_hoist_regs(source):
    if "func_8009FF30:" not in source:
        raise ValueError("cd_sync_hoist_regs: not func_8009FF30")
    if source.count(_CDSYNC_EXPECTED_BLOCK) != 1:
        raise ValueError("cd_sync_hoist_regs: hoisted block not found exactly once")
    for line, n in _CDSYNC_EXPECTED_BODY_USES.items():
        if source.count(line) != n:
            raise ValueError("cd_sync_hoist_regs: unexpected use count for %r" % line)
    if len(re.findall(r"\$19\b", source)) != 5 or len(re.findall(r"\$20\b", source)) != 5:
        raise ValueError("cd_sync_hoist_regs: unexpected $19/$20 reference count")
    source = source.replace(_CDSYNC_EXPECTED_BLOCK, _CDSYNC_RETAIL_BLOCK)
    for old, new in _CDSYNC_RETAIL_BODY_USES.items():
        source = source.replace(old, new)
    return source


# func_800684C0 primitive packet walk: retail orders four loop-invariant
# temporaries differently; the instruction stream is otherwise identical.
KID_WALK_TREGS_MAP = {"8": "10", "9": "11", "10": "8", "11": "9"}
KID_WALK_TREGS_COUNTS = {"8": 2, "9": 2, "10": 2, "11": 2}
_KWT_TREG = re.compile(r"\$(8|9|10|11)(?![0-9A-Za-z_])")


def _kid_walk_tregs(source):
    if len(re.findall(r"(?m)^func_800684C0:", source)) != 1:
        raise ValueError("kid_walk_tregs expects exactly one func_800684C0")
    if re.search(r"(?m)^func_(?!800684C0)[0-9A-F]{8}:", source):
        raise ValueError("kid_walk_tregs is restricted to func_800684C0")
    counts = {r: 0 for r in KID_WALK_TREGS_MAP}
    for m in _KWT_TREG.finditer(source):
        counts[m.group(1)] += 1
    if counts != KID_WALK_TREGS_COUNTS:
        raise ValueError("kid_walk_tregs register counts %r != %r"
                         % (counts, KID_WALK_TREGS_COUNTS))
    return _KWT_TREG.sub(lambda m: "$" + KID_WALK_TREGS_MAP[m.group(1)], source)


# func_80094E80 card finish callback: post-reload CSE turns the case-4 call
# argument immediate into a copy of the switch constant register.
_CFCA_OLD = (
    ".set\tnoreorder\n"
    ".set\tnomacro\n"
    "bne\t$3,$2,{label}\n"
    "addu\t$4,$2,$zero\n"
    ".set\tmacro\n"
    ".set\treorder\n"
    "\n"
    "la\t$16,D_800EF094+12\n"
)


def _card_finish_const_arg(source):
    pattern = re.compile(
        r"\.set\tnoreorder\n\.set\tnomacro\nbne\t\$3,\$2,(\$L\d+)\n"
        r"addu\t\$4,\$2,\$zero\n\.set\tmacro\n\.set\treorder\n\n"
        r"la\t\$16,D_800EF094\+12\n"
    )
    matches = pattern.findall(source)
    if len(matches) != 1:
        raise ValueError("card_finish_const_arg shape changed")
    old = _CFCA_OLD.format(label=matches[0])
    new = old.replace("addu\t$4,$2,$zero\n", "li\t$4,4\n")
    if source.count(old) != 1:
        raise ValueError("card_finish_const_arg shape changed")
    return source.replace(old, new)


# func_80099DEC libsio control: with a zero-size frame GCC 2.8.1 turns each
# jump that stole the shared return copy into its own return; the library
# object keeps the six jumps to the single final return.
def _sio_control_shared_return(source):
    tail = (
        "$L2:\n"
        "addu\t$2,$7,$zero\n"
        "j\t$31\n"
        "nop  # DEBUG: branch/jump\n"
        ".end\tfunc_80099DEC"
    )
    if source.count(tail) != 1:
        raise ValueError("sio_control_shared_return final return block not found once")
    site = re.compile(r"(?m)^j\t\$31\naddu\t\$2,\$7,\$zero\n")
    if len(site.findall(source)) != 6:
        raise ValueError("sio_control_shared_return expected six stolen return copies")
    if source.count("j\t$31") != 7 or "$Lsio_ret" in source:
        raise ValueError("sio_control_shared_return unexpected return shape")
    source = site.sub("j\t$Lsio_ret\naddu\t$2,$7,$zero\n", source)
    source = source.replace(
        tail,
        "$L2:\n"
        "addu\t$2,$7,$zero\n"
        "$Lsio_ret:\n"
        "j\t$31\n"
        "nop  # DEBUG: branch/jump\n"
        ".end\tfunc_80099DEC",
    )
    return source


_CARD_DIR_BODY_COUNTS = {"16": 4, "18": 3, "17": 8, "21": 3}
_CARD_DIR_REG = re.compile(r"\$(16|17|18|21)(?![0-9A-Za-z_])")


def _card_directory_locals(source):
    """Restore the retail allocation of four card-directory locals."""
    if len(re.findall(r"(?m)^func_80095DB4:", source)) != 1:
        raise ValueError("card_directory_locals expects exactly one func_80095DB4")
    if re.search(r"(?m)^func_(?!80095DB4)[0-9A-F]{8}:", source):
        raise ValueError("card_directory_locals is restricted to func_80095DB4")
    start_marker = "addu\t$16,$0,$zero\n"
    end_marker = "$L7:\n"
    if source.count(start_marker) != 1 or source.count(end_marker) != 1:
        raise ValueError("card_directory_locals body markers changed")
    start = source.index(start_marker)
    end = source.index(end_marker, start)
    body = source[start:end]
    counts = {reg: 0 for reg in _CARD_DIR_BODY_COUNTS}
    for match in _CARD_DIR_REG.finditer(body):
        counts[match.group(1)] += 1
    if counts != _CARD_DIR_BODY_COUNTS:
        raise ValueError("card_directory_locals register counts %r != %r"
                         % (counts, _CARD_DIR_BODY_COUNTS))

    body = body.replace("$16", "$CARD_DIR_S0")
    body = body.replace("$18", "$16")
    body = body.replace("$CARD_DIR_S0", "$18")
    init_n = "addu\t$21,$0,$zero\n"
    init_i = "addu\t$17,$0,$zero\n"
    if body.count(init_n) != 1 or body.count(init_i) != 1:
        raise ValueError("card_directory_locals initializers changed")
    body = body.replace(init_n, "CARD_DIR_INIT\n", 1)
    body = body.replace(init_i, init_n, 1)
    body = body.replace("CARD_DIR_INIT\n", init_i, 1)
    source = source[:start] + body + source[end:]

    home = "sw\t$7,156($sp)\n"
    if source.count(home) != 1:
        raise ValueError("card_directory_locals count home changed")
    source = source.replace(home, "sw\t$7,92($sp)\n", 1)
    old_tail = (
        "$L7:\n"
        "lw\t$2,156($sp)\n"
        "#nop\n"
        "beq\t$2,$0,$L25\n"
        "sw\t$21,0($2)\n"
        "$L25:\n"
        "addu\t$2,$0,$zero\n"
    )
    new_tail = (
        "$L7:\n"
        "lw\t$8,92($sp)\n"
        "#nop\n"
        ".set\tnoreorder\n"
        "beq\t$8,$0,$L25\n"
        "addu\t$2,$0,$zero\n"
        ".set\treorder\n"
        "sw\t$21,0($8)\n"
        "$L25:\n"
    )
    if source.count(old_tail) != 1:
        raise ValueError("card_directory_locals tail changed")
    return source.replace(old_tail, new_tail, 1)


def _card_create_cse(source):
    """Restore three narrow code-generation choices in the card-create loop."""
    if len(re.findall(r"(?m)^func_80096138:", source)) != 1:
        raise ValueError("card_create_cse expects exactly one func_80096138")
    if re.search(r"(?m)^func_(?!80096138)[0-9A-F]{8}:", source):
        raise ValueError("card_create_cse is restricted to func_80096138")

    one_copy = "addu\t$2,$5,$zero\n"
    if source.count(one_copy) != 1:
        raise ValueError("card_create_cse constant copy changed")
    source = source.replace(one_copy, "li\t$2,1\n", 1)

    preheader = (
        "$L15:\n"
        "la\t$16,D_800EF094\n"
        "li\t$18,2\t\t\t# 0x00000002\n"
    )
    retail_preheader = (
        "$L15:\n"
        "addu\t$16,$18,$zero\n"
        "li\t$18,2\t\t\t# 0x00000002\n"
    )
    if source.count(preheader) != 1:
        raise ValueError("card_create_cse loop preheader changed")
    source = source.replace(preheader, retail_preheader, 1)

    retry = (
        "bne\t$3,$18,$L18\n"
        "addu\t$17,$17,1\n"
        ".set\tmacro\n"
        ".set\treorder\n"
        "\n"
        "slt\t$2,$17,16\n"
    )
    retail_retry = (
        "bne\t$3,$18,$L18\n"
        "nop\n"
        ".set\tmacro\n"
        ".set\treorder\n"
        "\n"
        "addu\t$17,$17,1\n"
        "slt\t$2,$17,16\n"
    )
    if source.count(retry) != 1:
        raise ValueError("card_create_cse retry branch changed")
    return source.replace(retry, retail_retry, 1)


def _font_advance_negative_layout(source):
    """Keep the first copy of one cross-jumped rounding tail, as retail did."""
    if len(re.findall(r"(?m)^func_80057420:", source)) != 1:
        raise ValueError("font_advance_negative_layout expects func_80057420")
    if re.search(r"(?m)^func_(?!80057420)[0-9A-F]{8}:", source):
        raise ValueError("font_advance_negative_layout is restricted to func_80057420")

    tail = (
        "$L66:\n"
        "addu\t$2,$3,-2048\n"
        "bgez\t$2,$L86\n"
        "sra\t$2,$2,12\n"
        "\n"
        "j\t$L123\n"
        "subu\t$2,$20,$3\n"
        "\n"
    )
    if source.count(tail) != 1:
        raise ValueError("font_advance_negative_layout rounding tail changed")
    if source.count("$L53:\n") != 1 or source.count("$L51:\n") != 1:
        raise ValueError("font_advance_negative_layout anchor labels changed")
    without_tail = source.replace(tail, "", 1)
    return without_tail.replace("$L53:\n", tail + "$L53:\n", 1)


def _vector_split_schedule(source):
    """Restore two local scheduling choices in func_80065710."""
    if len(re.findall(r"(?m)^func_80065710:", source)) != 1:
        raise ValueError("vector_split_schedule expects func_80065710")
    if re.search(r"(?m)^func_(?!80065710)[0-9A-F]{8}:", source):
        raise ValueError("vector_split_schedule is restricted to func_80065710")

    entry = (
        "sw\t$4,12($sp)\n"
        "sw\t$2,16($sp)\n"
        "sw\t$3,20($sp)\n"
        "addu\t$3,$4,$zero\n"
        "bgez\t$3,$L7\n"
        "subu\t$3,$0,$3\n"
    )
    retail_entry = (
        "sw\t$4,12($sp)\n"
        "sw\t$3,20($sp)\n"
        "addu\t$3,$4,$zero\n"
        "bgez\t$3,$L7\n"
        "sw\t$2,16($sp)\n"
        "subu\t$3,$0,$3\n"
    )
    tail = (
        "addu\t$2,$2,$4\n"
        "sw\t$2,4($7)\n"
        "addu\t$3,$3,$5\n"
    )
    retail_tail = (
        "addu\t$2,$2,$4\n"
        "addu\t$3,$3,$5\n"
        "sw\t$2,4($7)\n"
    )
    if source.count(entry) != 1 or source.count(tail) != 1:
        raise ValueError("vector_split_schedule code shape changed")
    return source.replace(entry, retail_entry, 1).replace(tail, retail_tail, 1)


def apply_assembly_profile(path, profile):
    """Reproduce narrow PsyQ assembler choices that old GCC cannot express."""
    if profile == "tank_input_psyq":
        source = path.read_text()
        prologue_start = source.index("addu\t$5,$0,$zero")
        prologue_end = source.index("$L4:", prologue_start)
        prologue = source[prologue_start:prologue_end]
        expected_prologue = """addu\t$5,$0,$zero
sw\t$21,180($sp)
addu\t$21,$5,$zero
lui\t$2,%hi(D_800C60E8) # high
lui\t$3,%hi(D_800EE028) # high
addiu\t$3,$3,%lo(D_800EE028) # low
lui\t$8,%hi(D_800D2FE4+8) # high
sw\t$22,184($sp)
lw\t$22,%lo(D_800C60E8)($2) # DEBUG: leaving for assembler to expand
#nop # DEBUG: 'lbu\t$2,%lo(D_800D2FE4+8)($8)' does not load from $22
lbu\t$2,%lo(D_800D2FE4+8)($8) # DEBUG: leaving for assembler to expand
#nop # DEBUG: 'addiu\t$4,$8,%lo(D_800D2FE4+8) # low' does not load from $2
addiu\t$4,$8,%lo(D_800D2FE4+8) # low
sw\t$31,188($sp)
sw\t$20,176($sp)
sw\t$19,172($sp)
sw\t$18,168($sp)
sw\t$16,160($sp)
beq\t$2,$0,$L4
srl\t$22,$22,4

addu\t$6,$4,-8
lui\t$4,%hi(D_800A4D30) # high
addiu\t$4,$4,%lo(D_800A4D30) # low
$L5:
lhu\t$2,4($3)
nop # DEBUG: Reuse of '$2'. 'andi\t$2,$2,0x4000' does not use $at
andi\t$2,$2,0x4000
bne\t$2,$0,$L8
nop  # DEBUG: branch/jump
sw\t$0,0($4)
$L8:
addu\t$4,$4,4
addu\t$5,$5,1
lbu\t$2,%lo(D_800D2FE4+8)($8) # DEBUG: leaving for assembler to expand
nop # DEBUG: Reuse of '$2'. 'slt\t$2,$5,$2' does not use $at
slt\t$2,$5,$2
bne\t$2,$0,$L5
addu\t$3,$3,140

"""
        if prologue != expected_prologue:
            raise ValueError("tank_input_psyq prologue schedule shape changed")
        retail_prologue = """addu\t$5,$0,$zero
lui\t$2,%hi(D_800C60E8) # high
sw\t$21,180($sp)
addu\t$21,$5,$zero
lw\t$2,%lo(D_800C60E8)($2)
lui\t$3,%hi(D_800EE028) # high
sw\t$31,188($sp)
sw\t$22,184($sp)
sw\t$20,176($sp)
sw\t$19,172($sp)
sw\t$18,168($sp)
sw\t$16,160($sp)
srl\t$22,$2,4
lui\t$2,%hi(D_800D2FE4) # high
addiu\t$4,$2,%lo(D_800D2FE4) # low
lbu\t$2,8($4)
nop
beq\t$2,$0,$L4
addiu\t$3,$3,%lo(D_800EE028) # low

addu\t$6,$4,$zero
lui\t$2,%hi(D_800A4D30) # high
addiu\t$4,$2,%lo(D_800A4D30) # low
$L5:
lhu\t$2,4($3)
nop
andi\t$2,$2,0x4000
bne\t$2,$0,$L8
nop
sw\t$0,0($4)
$L8:
addiu\t$4,$4,4
lbu\t$2,8($6)
addiu\t$5,$5,1
slt\t$2,$5,$2
bne\t$2,$0,$L5
addiu\t$3,$3,140

"""
        source = source[:prologue_start] + retail_prologue + source[prologue_end:]
        source, count = re.subn(
            r"(?m)^swc2\s+\$31,([0-9]+)\(\$sp\)$",
            r"addiu\t$2,$sp,\1\nswc2\t$31,0($2)",
            source,
        )
        if count != 20:
            raise ValueError(
                "tank_input_psyq expected 20 GTE stack-store rewrites, found %d"
                % count
            )
        table_old = """lui\t$4,%hi(D_800D3034) # high
addiu\t$4,$4,%lo(D_800D3034) # low
lw\t$3,152($17)
nop # DEBUG: Reuse of '$3'. 'sll\t$2,$3,2' does not use $at
"""
        table_new = """lui\t$4,%hi(D_800D3034) # high
lw\t$3,152($17)
addiu\t$4,$4,%lo(D_800D3034) # low
"""
        if source.count(table_old) != 1:
            raise ValueError("tank_input_psyq table-base schedule shape changed")
        source = source.replace(table_old, table_new, 1)

        fixed_start = source.index("blez\t$3,$L13")
        fixed_end = source.index("$L24:", fixed_start)
        fixed = source[fixed_start:fixed_end]
        fixed_rewrites = (
            ("li\t$8,-2147483648", "li\t$2,-2147483648"),
            ("and\t$8,$3,$8", "and\t$8,$3,$2"),
            ("subu\t$6,$0,$3", "subu\t$6,$0,$6"),
            ("li\t$2,16777216", "li\t$3,16777216"),
            ("mflo\t$2\n.set\tat\n# EXPAND_DIVU END\n"
             "#nop # DEBUG: 'j\t$L22' does not load from $2\n"
             "j\t$L22\nsll\t$3,$2,$4",
             "mflo\t$3\n.set\tat\n# EXPAND_DIVU END\n"
             "#nop # DEBUG: 'j\t$L22' does not load from $3\n"
             "j\t$L22\nsll\t$3,$3,$4"),
            ("mflo\t$4\n.set\tat\n# EXPAND_DIVU END\n"
             "j\t$L23\nnop # DEBUG: mflo/mfhi with mult/div/rem and 1 instruction (branch)",
             "mflo\t$3\n.set\tat\n# EXPAND_DIVU END\n"
             "j\t$L23\naddu\t$4,$3,$zero"),
            ("divu\t$zero,$2,$6", "divu\t$zero,$3,$6"),
        )
        for old, new in fixed_rewrites:
            if fixed.count(old) != 1:
                raise ValueError("tank_input_psyq fixed-division shape changed")
            fixed = fixed.replace(old, new, 1)
        source = source[:fixed_start] + fixed + source[fixed_end:]

        signed_product = re.compile(
            r"(?m)^\$L(?P<join>[0-9]+):\n"
            r"nop\n"
            r"nop\n"
            r"mult\t\$3,\$18\n"
            r"# \$L(?P=join):  # DEBUG: skipped\n"
            r"# mult\t\$3,\$18  # DEBUG: skipped\n"
            r"\$L(?P<aux>[0-9]+):\n"
            r"mflo\t\$2\n"
            r"beq\t\$8,\$0,\$L(?P<done>[0-9]+)\n"
            r"nop  # DEBUG: branch/jump\n"
            r"subu\t\$2,\$0,\$3\n"
            r"mult\t\$2,\$18\n"
            r"mflo\t\$2\n"
            r"\$L(?P=done):$"
        )
        source, product_count = signed_product.subn(
            lambda match: (
                "$L%s:\n" % match.group("join")
                + "nop\n"
                + "addu\t$2,$3,$zero\n"
                + "$L%s:\n" % match.group("aux")
                + "beq\t$8,$0,$L%s\n" % match.group("done")
                + "mult\t$2,$18\n"
                + "subu\t$2,$0,$2\n"
                + "mult\t$2,$18\n"
                + "$L%s:\n" % match.group("done")
                + "mflo\t$2"
            ),
            source,
        )
        if product_count != 8:
            raise ValueError(
                "tank_input_psyq expected 8 signed-product rewrites, found %d"
                % product_count
            )
        product_entry = re.compile(
            r"(?m)^nop  # DEBUG: mflo/mfhi with mult/div/rem and 1 instruction \(noreorder\)\n"
            r"\.set\tnoreorder\n"
            r"j\t\$L(?P<aux>[0-9]+)\n"
            r"mult\t\$3,\$18$"
        )
        source, entry_count = product_entry.subn(
            lambda match: (
                ".set\tnoreorder\n"
                + "j\t$L%s\n" % match.group("aux")
                + "addu\t$2,$3,$zero"
            ),
            source,
        )
        if entry_count != 8:
            raise ValueError(
                "tank_input_psyq expected 8 product-entry rewrites, found %d"
                % entry_count
            )

        quotient = re.compile(
            r"(?m)^mflo\t\$2\n"
            r"\.set\tat\n"
            r"# EXPAND_DIVU END\n"
            r"#nop # DEBUG: 'j\t\$L(?P<join>[0-9]+)' does not load from \$2\n"
            r"j\t\$L(?P=join)\n"
            r"sll\t\$3,\$2,\$4$"
        )
        if len(quotient.findall(source)) != 9:
            raise ValueError("tank_input_psyq quotient source shape changed")
        source, quotient_count = quotient.subn(
            lambda match: (
                "mflo\t$3\n"
                + ".set\tat\n"
                + "# EXPAND_DIVU END\n"
                + "#nop # DEBUG: 'j\t$L%s' does not load from $3\n"
                  % match.group("join")
                + "j\t$L%s\n" % match.group("join")
                + "sll\t$3,$3,$4"
            ),
            source,
            count=8,
        )
        if quotient_count != 8:
            raise ValueError(
                "tank_input_psyq expected 8 quotient-register rewrites, found %d"
                % quotient_count
            )

        negative_shift = re.compile(
            r"(?m)^subu\t\$7,\$0,\$7\n"
            r"sra\t\$6,\$6,\$7\n"
            r"# EXPAND_DIVU START\n"
            r"\.set\tnoat\n"
            r"divu\t\$zero,\$3,\$6\n"
            r"bnez\t\$6,"
        )
        source, negative_count = negative_shift.subn(
            "subu\t$2,$0,$7\n"
            "sra\t$2,$6,$2\n"
            "# EXPAND_DIVU START\n"
            ".set\tnoat\n"
            "divu\t$zero,$3,$2\n"
            "bnez\t$2,",
            source,
        )
        if negative_count != 8:
            raise ValueError(
                "tank_input_psyq expected 8 negative-shift rewrites, found %d"
                % negative_count
            )

        nonnegative = re.compile(
            r"(?m)^sll\t\$4,\$4,12\n"
            r"# EXPAND_DIVU START\n"
            r"\.set\tnoat\n"
            r"divu\t\$zero,\$4,\$5$"
        )
        source, nonnegative_count = nonnegative.subn(
            "sll\t$3,$3,12\n"
            "# EXPAND_DIVU START\n"
            ".set\tnoat\n"
            "divu\t$zero,$3,$5",
            source,
        )
        if nonnegative_count != 8:
            raise ValueError(
                "tank_input_psyq expected 8 nonnegative-dividend rewrites, found %d"
                % nonnegative_count
            )

        owner_old = """lw\t$3,156($17)
nop # DEBUG: Reuse of '$3'. 'sll\t$2,$3,1' does not use $at
sll\t$2,$3,1
addu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$3
sll\t$2,$2,4
lui\t$3,%hi(D_800A4EF4) # high
addiu\t$3,$3,%lo(D_800A4EF4) # low
addu\t$7,$2,$3
"""
        owner_new = """lui\t$4,%hi(D_800A4EF4) # high
lw\t$3,156($17)
addiu\t$4,$4,%lo(D_800A4EF4) # low
sll\t$2,$3,1
addu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$3
sll\t$2,$2,4
addu\t$7,$2,$4
"""
        if source.count(owner_old) != 1:
            raise ValueError("tank_input_psyq owner-base schedule shape changed")
        source = source.replace(owner_old, owner_new, 1)

        signed_axis_pair = re.compile(
            r"(?m)^lw\t\$2,(?P<x>8|368)\(\$17\)\n"
            r"nop # DEBUG: Reuse of '\$2'. 'bgez\t\$2,\$L(?P<xjoin>[0-9]+)' does not use \$at\n"
            r"bgez\t\$2,\$L(?P=xjoin)\n"
            r"sra\t\$4,\$2,12\n\n"
            r"subu\t\$2,\$0,\$2\n"
            r"sra\t\$2,\$2,12\n"
            r"subu\t\$4,\$0,\$2\n"
            r"\$L(?P=xjoin):\n"
            r"lw\t\$2,(?P<y>16|376)\(\$17\)\n"
            r"nop # DEBUG: Reuse of '\$2'. 'bltz\t\$2,\$L(?P<yneg>[0-9]+)' does not use \$at\n"
            r"bltz\t\$2,\$L(?P=yneg)\n"
            r"nop  # DEBUG: branch/jump\n"
            r"j\t\$L(?P<yjoin>[0-9]+)\n"
            r"sra\t\$2,\$2,12\n\n"
            r"\$L(?P=yneg):\n"
            r"subu\t\$2,\$0,\$2\n"
            r"sra\t\$2,\$2,12\n"
            r"subu\t\$2,\$0,\$2\n"
            r"\$L(?P=yjoin):\n"
            r"sll\t\$4,\$4,16\n"
            r"sra\t\$4,\$4,16\n"
            r"sll\t\$5,\$2,16\n"
            r"sra\t\$5,\$5,16$"
        )

        def rewrite_signed_axes(match):
            return (
                "lw\t$2,%s($17)\n" % match.group("x")
                + "nop\n"
                + "bltz\t$2,$L%s\n" % match.group("xjoin")
                + "nop\n"
                + "j\t$L%s_pos\n" % match.group("xjoin")
                + "sra\t$2,$2,12\n"
                + "$L%s:\n" % match.group("xjoin")
                + "subu\t$2,$0,$2\n"
                + "sra\t$2,$2,12\n"
                + "subu\t$2,$0,$2\n"
                + "$L%s_pos:\n" % match.group("xjoin")
                + "sll\t$2,$2,16\n"
                + "lw\t$5,%s($17)\n" % match.group("y")
                + "nop\n"
                + "bltz\t$5,$L%s\n" % match.group("yneg")
                + "sra\t$4,$2,16\n"
                + "j\t$L%s\n" % match.group("yjoin")
                + "sra\t$2,$5,12\n"
                + "$L%s:\n" % match.group("yneg")
                + "subu\t$2,$0,$5\n"
                + "sra\t$2,$2,12\n"
                + "subu\t$2,$0,$2\n"
                + "$L%s:\n" % match.group("yjoin")
                + "sll\t$5,$2,16\n"
                + "sra\t$5,$5,16"
            )

        source, axes_count = signed_axis_pair.subn(rewrite_signed_axes, source)
        if axes_count != 2:
            raise ValueError(
                "tank_input_psyq expected 2 signed-axis rewrites, found %d"
                % axes_count
            )
        call_old = """addu\t$4,$17,$zero
jal\tfunc_80048F7C
addu\t$5,$sp,32
"""
        call_new = """jal\tfunc_80048F7C
addu\t$4,$17,$zero
"""
        if source.count(call_old) != 1:
            raise ValueError("tank_input_psyq update-call schedule shape changed")
        source = source.replace(call_old, call_new, 1)

        steering_start = source.index("lw\t$3,44($sp)")
        steering_end = source.index("$L49:", steering_start) + len("$L49:\n")
        steering = source[steering_start:steering_end]
        range_match = re.search(
            r"bne\t\$2,\$0,\$L([0-9]+)\n"
            r"slt\t\$2,\$3,-40",
            steering,
        )
        negative_alias = re.search(r"\$L54:\n(\$L[0-9]+:)\nlw", steering)
        if range_match is None or negative_alias is None or not all(
            label in steering for label in ("$L51:", "$L54:")
        ):
            raise ValueError("tank_input_psyq steering selection shape changed")
        retail_steering = """lw\t$3,44($sp)
nop
slt\t$2,$3,41
bne\t$2,$0,$LRANGE
slt\t$2,$3,-40

lui\t$2,%hi(D_800DE30C) # high
lw\t$21,%lo(D_800DE30C)($2)
slt\t$2,$3,-40
$LRANGE:
beq\t$2,$0,$L49
lui\t$2,%hi(D_800DE30C) # high

$L54:
{negative_alias}
lw\t$2,%lo(D_800DE30C)($2)
j\t$L49
subu\t$21,$0,$2
$L51:
addu\t$21,$0,$zero
$L49:
""".format(negative_alias=negative_alias.group(1))
        retail_steering = retail_steering.replace(
            "$LRANGE", "$L%s" % range_match.group(1)
        )
        source = source[:steering_start] + retail_steering + source[steering_end:]

        axis_preamble = re.compile(
            r"(?m)^lb\t\$3,(?P<slot>[0-9]+)\(\$sp\)\n"
            r"#nop[^\n]*\n"
            r"lbu\t\$4,(?P=slot)\(\$sp\)\n"
            r"#nop[^\n]*\n"
            r"slt\t\$2,\$3,(?P<limit>-40|41)\n"
            r"beq\t\$2,\$0,\$L(?P<skip>[0-9]+)\n"
            r"li\t\$5,327680[^\n]*\n\n"
            r"ori\t\$5,\$5,0x8000\n"
            r"li\t\$6,327680[^\n]*\n"
            r"ori\t\$6,\$6,0x8000\n"
            r"li\t\$3,-2147483648[^\n]*\n"
            r"(?P<adjust>addu|subu)\t\$2,\$4,(?P<amount>40)\n"
            r"sb\t\$2,(?P=slot)\(\$sp\)\n"
            r"sll\t\$2,\$2,24\n"
            r"sra\t\$2,\$2,12\n"
            r"(?P<maybe_neg>subu\t\$2,\$0,\$2\n)?"
            r"and\t\$8,\$2,\$3\n"
            r"bgez\t\$2,\$L(?P<join>[0-9]+)\n"
            r"addu\t\$3,\$2,\$zero\n\n"
            r"subu\t\$3,\$0,\$2\n"
            r"\$L(?P=join):$"
        )

        def rewrite_axis_preamble(match):
            neg = match.group("maybe_neg") or ""
            return (
                "lb\t$4,%s($sp)\n" % match.group("slot")
                + "lbu\t$3,%s($sp)\n" % match.group("slot")
                + "slt\t$2,$4,%s\n" % match.group("limit")
                + "beq\t$2,$0,$L%s\n" % match.group("skip")
                + "li\t$5,327680\n\n"
                + "ori\t$5,$5,0x8000\n"
                + "li\t$6,327680\n"
                + "ori\t$6,$6,0x8000\n"
                + "%s\t$2,$3,%s\n" % (match.group("adjust"), match.group("amount"))
                + "sb\t$2,%s($sp)\n" % match.group("slot")
                + "sll\t$2,$2,24\n"
                + "sra\t$2,$2,12\n"
                + neg
                + "li\t$3,-2147483648\n"
                + "and\t$8,$2,$3\n"
                + "bgez\t$2,$L%s\n" % match.group("join")
                + "addu\t$3,$2,$zero\n\n"
                + "subu\t$3,$0,$3\n"
                + "$L%s:" % match.group("join")
            )

        source, preamble_count = axis_preamble.subn(rewrite_axis_preamble, source)
        if preamble_count != 3:
            raise ValueError(
                "tank_input_psyq expected 3 axis-preamble rewrites, found %d"
                % preamble_count
            )

        store_after_load = re.compile(
            r"(?m)^mult\t\$2,\$22\n"
            r"sb\t\$3,34\(\$sp\)\n"
            r"lhu\t\$2,48\(\$17\)$"
        )
        source, store_count = store_after_load.subn(
            "mult\t$2,$22\n"
            "lhu\t$2,48($17)\n"
            "sb\t$3,34($sp)",
            source,
        )
        if store_count != 2:
            raise ValueError(
                "tank_input_psyq expected 2 axis-store schedules, found %d"
                % store_count
            )

        radius_old = """lhu\t$18,152($7)
nop # DEBUG: Reuse of '$18'. 'srl\t$18,$18,1' does not use $at
srl\t$18,$18,1
mult\t$18,$22
"""
        radius_new = """lhu\t$2,152($7)
nop
srl\t$2,$2,1
mult\t$2,$22
"""
        if source.count(radius_old) != 1:
            raise ValueError("tank_input_psyq radius-product shape changed")
        source = source.replace(radius_old, radius_new, 1)

        object_table_old = """addiu\t$3,$3,%lo(D_800D3034+76) # low
addu\t$2,$6,$4
sll\t$2,$2,3
subu\t$2,$2,$4
sll\t$2,$2,2
addu\t$2,$2,$3
lw\t$3,0($2)
"""
        object_table_new = """addiu\t$3,$3,%lo(D_800D3034) # low
addu\t$2,$6,$4
sll\t$2,$2,3
subu\t$2,$2,$4
sll\t$2,$2,2
addu\t$2,$2,$3
lw\t$3,76($2)
"""
        if source.count(object_table_old) != 1:
            raise ValueError("tank_input_psyq object-table address shape changed")
        source = source.replace(object_table_old, object_table_new, 1)

        magnitude_negate = re.compile(
            r"(?m)^subu\t\$3,\$0,\$2\n"
            r"(?P<label>\$L[0-9]+:)\n"
            r"mtc2 \$3,\$30$"
        )
        source, magnitude_count = magnitude_negate.subn(
            lambda match: (
                "subu\t$3,$0,$3\n"
                + match.group("label")
                + "\nmtc2 $3,$30"
            ),
            source,
        )
        if magnitude_count != 5:
            raise ValueError(
                "tank_input_psyq expected 5 magnitude-negate rewrites, found %d"
                % magnitude_count
            )

        positive_preamble = re.compile(
            r"(?m)^slt\t\$2,\$3,41\n"
            r"bne\t\$2,\$0,\$L(?P<skip>[0-9]+)\n"
            r"(?P<delay>[^\n]+)\n\n"
            r"(?P<prefix>li\t\$5,327680[^\n]*\nori\t\$5,\$5,0x8000\n)?"
            r"li\t\$6,327680[^\n]*\n"
            r"ori\t\$6,\$6,0x8000\n"
            r"li\t\$3,-2147483648[^\n]*\n"
            r"addu\t\$2,\$4,-40\n"
            r"sb\t\$2,(?P<slot>33|34)\(\$sp\)\n"
            r"sll\t\$2,\$2,24\n"
            r"sra\t\$2,\$2,12\n"
            r"and\t\$8,\$2,\$3$"
        )

        def rewrite_positive_preamble(match):
            return (
                "slt\t$2,$4,41\n"
                + "bne\t$2,$0,$L%s\n" % match.group("skip")
                + match.group("delay") + "\n\n"
                + (match.group("prefix") or "")
                + "li\t$6,327680\n"
                + "ori\t$6,$6,0x8000\n"
                + "addu\t$2,$3,-40\n"
                + "sb\t$2,%s($sp)\n" % match.group("slot")
                + "sll\t$2,$2,24\n"
                + "sra\t$2,$2,12\n"
                + "li\t$3,-2147483648\n"
                + "and\t$8,$2,$3"
            )

        source, positive_count = positive_preamble.subn(
            rewrite_positive_preamble, source
        )
        if positive_count != 3:
            raise ValueError(
                "tank_input_psyq expected 3 positive-axis rewrites, found %d"
                % positive_count
            )

        abs_pattern = re.compile(
            r"(?m)^addu\t\$2,\$21,\$zero\n"
            r"bgez\t\$21,\$L(?P<join>[0-9]+)\n"
            r"sll\t\$18,\$18,2\n\n"
            r"subu\t\$2,\$0,\$21$"
        )
        source, abs_count = abs_pattern.subn(
            lambda match: (
                "sll\t$18,$18,2\n"
                + "bgez\t$21,$L%s\n" % match.group("join")
                + "addu\t$2,$21,$zero\n\n"
                + "subu\t$2,$0,$2"
            ),
            source,
        )
        if abs_count != 1:
            raise ValueError("tank_input_psyq steering-absolute shape changed")

        square_old = """mult\t$4,$4
mflo\t$11
sra\t$2,$11,8
"""
        square_new = """mult\t$4,$4
mflo\t$8
sra\t$2,$8,8
"""
        if source.count(square_old) != 1:
            raise ValueError("tank_input_psyq squared-input shape changed")
        source = source.replace(square_old, square_new, 1)

        slot_search = re.compile(
            r"(?m)^lw\t\$5,596\(\$17\)\n"
            r"nop[^\n]*\n"
            r"beq\t\$5,\$0,\$L(?P<outer>[0-9]+)\n"
            r"addu\t\$4,\$5,(?P<step>12|14)\n\n"
            r"\$L(?P<loop>[0-9]+):\n"
            r"li\t\$2,-2004353024[^\n]*\n"
            r"ori\t\$2,\$2,0x8889\n"
            r"mult\t\$4,\$2\n"
            r"sra\t\$2,\$4,31\n"
            r"mfhi\t\$9\n"
            r"addu\t\$3,\$9,\$4\n"
            r"sra\t\$3,\$3,3\n"
            r"subu\t\$3,\$3,\$2\n"
            r"sll\t\$2,\$3,4\n"
            r"subu\t\$2,\$2,\$3\n"
            r"subu\t\$3,\$4,\$2\n"
            r"addu\t\$6,\$3,2\n"
            r"beq\t\$6,\$5,\$L(?P<found>[0-9]+)\n"
            r"sll\t\$2,\$6,1\n\n"
            r"addu\t\$2,\$2,\$17\n"
            r"lhu\t\$2,556\(\$2\)\n"
            r"nop[^\n]*\n"
            r"beq\t\$2,\$0,\$L(?P=loop)\n"
            r"addu\t\$4,\$3,(?P<next>14|16)\n\n"
            r"\$L(?P=found):\n"
            r"sll\t\$3,\$6,1\n"
            r"addu\t\$2,\$17,\$3\n"
            r"lhu\t\$2,556\(\$2\)\n"
            r"nop[^\n]*\n"
            r"bne\t\$2,\$0,\$L(?P<nonnull>[0-9]+)\n"
            r"addu\t\$2,\$3,556\n\n"
            r"addu\t\$4,\$0,\$zero\n"
            r"addu\t\$6,\$4,\$zero\n"
            r"j\t\$L(?P<join>[0-9]+)\n"
            r"sw\t\$0,596\(\$17\)\n\n"
            r"\$L(?P=nonnull):\n"
            r"addu\t\$4,\$17,\$2\n"
            r"sw\t\$6,596\(\$17\)\n"
            r"\$L(?P=join):\n"
            r"li\t\$7,-2004353024[^\n]*\n"
            r"lhu\t\$5,152\(\$17\)\n"
            r"#nop[^\n]*\n"
            r"jal\tfunc_80063C68\n"
            r"ori\t\$7,\$7,0x8889$"
        )

        def rewrite_slot_search(match):
            step = match.group("step")
            return (
                "lw\t$5,596($17)\n"
                + "nop\n"
                + "beq\t$5,$0,$L%s\n" % match.group("outer")
                + "addu\t$6,$5,$zero\n\n"
                + "li\t$8,%s\n" % step
                + "li\t$7,-2004353024\n"
                + "ori\t$7,$7,0x8889\n"
                + "addu\t$4,$6,$8\n"
                + "$L%s:\n" % match.group("loop")
                + "mult\t$4,$7\n"
                + "sra\t$2,$4,31\n"
                + "mfhi\t$9\n"
                + "addu\t$3,$9,$4\n"
                + "sra\t$3,$3,3\n"
                + "subu\t$3,$3,$2\n"
                + "sll\t$2,$3,4\n"
                + "subu\t$2,$2,$3\n"
                + "subu\t$4,$4,$2\n"
                + "addu\t$6,$4,2\n"
                + "beq\t$6,$5,$L%s\n" % match.group("found")
                + "sll\t$2,$6,1\n\n"
                + "addu\t$2,$17,$2\n"
                + "lhu\t$2,556($2)\n"
                + "nop\n"
                + "beq\t$2,$0,$L%s\n" % match.group("loop")
                + "addu\t$4,$6,$8\n\n"
                + "$L%s:\n" % match.group("found")
                + "sll\t$4,$6,1\n"
                + "addu\t$2,$17,$4\n"
                + "lhu\t$2,556($2)\n"
                + "nop\n"
                + "bne\t$2,$0,$L%s\n" % match.group("nonnull")
                + "addu\t$4,$4,556\n\n"
                + "addu\t$4,$0,$zero\n"
                + "lhu\t$5,152($17)\n"
                + "addu\t$6,$4,$zero\n"
                + "j\t$L%s\n" % match.group("join")
                + "sw\t$0,596($17)\n\n"
                + "$L%s:\n" % match.group("nonnull")
                + "lhu\t$5,152($17)\n"
                + "addu\t$4,$17,$4\n"
                + "sw\t$6,596($17)\n"
                + "$L%s:\n" % match.group("join")
                + "jal\tfunc_80063C68\n"
                + "nop"
            )

        outer_labels = [match.group("outer") for match in slot_search.finditer(source)]
        source, slot_count = slot_search.subn(rewrite_slot_search, source)
        if slot_count != 2:
            raise ValueError(
                "tank_input_psyq expected 2 slot-search rewrites, found %d"
                % slot_count
            )
        for outer_label in outer_labels:
            outer_pattern = re.compile(
                r"(?m)^\$L%s:\n(li\t\$4,[0-9]+[^\n]*\n)(\$L[0-9]+:)"
                % outer_label
            )
            source, outer_count = outer_pattern.subn(
                lambda match: match.group(1) + "$L%s:\n" % outer_label
                + match.group(2),
                source,
            )
            if outer_count != 1:
                raise ValueError(
                    "tank_input_psyq slot-search exit shape changed for L%s"
                    % outer_label
                )

        late_table_old = """lui\t$4,%hi(D_800D3034+76) # high

lw\t$3,152($17)
#nop # DEBUG: 'addiu\t$4,$4,%lo(D_800D3034+76) # low' does not load from $3
addiu\t$4,$4,%lo(D_800D3034+76) # low
sll\t$2,$3,2
addu\t$2,$2,$3
sll\t$2,$2,3
subu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$4
lw\t$3,0($2)
"""
        late_table_new = """lui\t$4,%hi(D_800D3034) # high

lw\t$3,152($17)
addiu\t$4,$4,%lo(D_800D3034) # low
sll\t$2,$3,2
addu\t$2,$2,$3
sll\t$2,$2,3
subu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$4
lw\t$3,76($2)
"""
        if source.count(late_table_old) != 1:
            raise ValueError("tank_input_psyq late object-table shape changed")
        source = source.replace(late_table_old, late_table_new, 1)

        final_div_start = source.index(
            "lw\t$7,%lo(D_800DE30C)($2)"
        )
        final_div_end = source.index("$L291:\n", final_div_start) + len("$L291:\n")
        final_div = source[final_div_start:final_div_end]
        if not all(
            label in final_div
            for label in ("$L250:", "$L251:", "$L252:", "$L254:",
                          "$L256:", "$L257:", "$L258:", "$L259:",
                          "$L260:")
        ):
            raise ValueError("tank_input_psyq final fixed-division shape changed")
        retail_final_div = """lw\t$3,%lo(D_800DE30C)($2)
nop
slt\t$2,$3,4097
bne\t$2,$0,$L250
li\t$5,2662

bne\t$3,$0,$L251
li\t$2,-2147483648
li\t$3,2
$L251:
and\t$8,$3,$2
li\t$5,2662
bgez\t$3,$L252
addu\t$6,$3,$zero

subu\t$6,$0,$6
$L252:
mtc2 $5,$30
nop
nop
addiu\t$2,$sp,148
swc2\t$31,0($2)
lw\t$4,148($sp)
nop
addu\t$7,$4,-12
bgez\t$7,$L254
li\t$3,10878976

sll\t$3,$5,$4
mtc2 $6,$30
nop
nop
addiu\t$2,$sp,152
swc2\t$31,0($2)
lw\t$5,152($sp)
nop
subu\t$4,$5,$4
bltz\t$4,$L256
li\t$2,12

subu\t$2,$2,$5
bltz\t$2,$L257
nop
j\t$L258
srav\t$2,$6,$2

$L257:
subu\t$2,$0,$2
sllv\t$2,$6,$2
$L258:
.set\tnoat
divu\t$zero,$3,$2
bnez\t$2,.L_NOT_DIV_BY_ZERO_2699
nop
break\t0x7
.L_NOT_DIV_BY_ZERO_2699:
mflo\t$3
.set\tat
j\t$L259
sllv\t$3,$3,$4

$L256:
subu\t$2,$0,$7
srav\t$2,$6,$2
.set\tnoat
divu\t$zero,$3,$2
bnez\t$2,.L_NOT_DIV_BY_ZERO_2709
nop
break\t0x7
.L_NOT_DIV_BY_ZERO_2709:
mflo\t$3
.set\tat
j\t$L260
addu\t$5,$3,$zero
$L254:
ori\t$3,$3,0x6000
.set\tnoat
divu\t$zero,$3,$6
bnez\t$6,.L_NOT_DIV_BY_ZERO_2714
nop
break\t0x7
.L_NOT_DIV_BY_ZERO_2714:
mflo\t$3
.set\tat
$L259:
nop
addu\t$5,$3,$zero
$L260:
beq\t$8,$0,$L291
li\t$9,-2457
j\t$L291
subu\t$5,$0,$5
$L250:
li\t$9,-2457
$L291:
"""
        source = (
            source[:final_div_start]
            + retail_final_div
            + source[final_div_end:]
        )

        actor_start = source.index("bne\t$3,$2,$L219")
        actor_end = source.index("$L225:\n", actor_start) + len("$L225:\n")
        actor_region = source[actor_start:actor_end]
        if not all(
            label in actor_region
            for label in ("$L218:", "$L219:", "$L220:", "$L223:", "$L292:")
        ):
            raise ValueError("tank_input_psyq actor-table shape changed")
        retail_actor = """bne\t$3,$2,$L219
lui\t$2,%hi(D_800A4EF4) # high

addiu\t$4,$2,%lo(D_800A4EF4) # low
lw\t$2,1452($4)
nop
lb\t$2,8($2)
li\t$5,-1
beq\t$2,$5,$L220
li\t$2,2816

sw\t$2,1360($17)
lw\t$3,156($17)
$L220:
nop
sll\t$2,$3,1
addu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$3
sll\t$2,$2,4
addu\t$2,$2,$4
lw\t$2,204($2)
nop
lb\t$2,12($2)
nop
beq\t$2,$5,$L225
li\t$2,2816

j\t$L225
sw\t$2,1376($17)

$L219:
addiu\t$5,$2,%lo(D_800A4EF4) # low
sll\t$2,$3,1
addu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$3
sll\t$2,$2,4
addu\t$2,$2,$5
lw\t$2,204($2)
nop
lb\t$2,8($2)
li\t$4,-1
beq\t$2,$4,$L223
li\t$2,12288

sw\t$2,1360($17)
$L223:
lw\t$3,156($17)
nop
sll\t$2,$3,1
addu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$3
sll\t$2,$2,4
addu\t$2,$2,$5
lw\t$2,204($2)
nop
lb\t$2,12($2)
nop
beq\t$2,$4,$L225
li\t$2,12288

j\t$L225
sw\t$2,1376($17)

$L218:
lui\t$2,%hi(D_800A4EF4) # high
lw\t$3,156($17)
addiu\t$5,$2,%lo(D_800A4EF4) # low
sll\t$2,$3,1
addu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$3
sll\t$2,$2,4
addu\t$2,$2,$5
lw\t$2,204($2)
nop
lb\t$2,8($2)
li\t$4,-1
beq\t$2,$4,$L292
sll\t$2,$3,1

sw\t$0,1360($17)
lw\t$3,156($17)
nop
sll\t$2,$3,1
$L292:
addu\t$2,$2,$3
sll\t$2,$2,2
addu\t$2,$2,$3
sll\t$2,$2,4
addu\t$2,$2,$5
lw\t$2,204($2)
nop
lb\t$2,12($2)
nop
beq\t$2,$4,$L290
li\t$4,7

sw\t$0,1376($17)
$L225:
"""
        source = source[:actor_start] + retail_actor + source[actor_end:]

        mode_pattern = re.compile(
            r"(?m)^beq\t\$3,\$2,\$L(?P<join>[0-9]+)\n"
            r"nop[^\n]*\n"
            r"bne\t\$3,\$8,\$L(?P<done>[0-9]+)$"
        )
        source, mode_count = mode_pattern.subn(
            lambda match: (
                "beq\t$3,$2,$L%s\n" % match.group("join")
                + "li\t$2,1\n"
                + "bne\t$3,$2,$L%s" % match.group("done")
            ),
            source,
        )
        if mode_count != 1:
            raise ValueError("tank_input_psyq secondary-mode shape changed")

        direction_match = re.search(
            r"(?m)^bgez\t\$16,\$L(?P<positive>[0-9]+)\n"
            r"nop[^\n]*\n"
            r"lw\t\$2,536\(\$17\)\n"
            r"#nop[^\n]*\n"
            r"j\t\$L(?P<join>[0-9]+)",
            source,
        )
        if direction_match is None:
            raise ValueError("tank_input_psyq direction-flag shape changed")
        direction_start = direction_match.start()
        direction_end = source.index("sw\t$2,536($17)\n", direction_start) + len(
            "sw\t$2,536($17)\n"
        )
        direction = source[direction_start:direction_end]
        positive_label = "$L%s" % direction_match.group("positive")
        join_label = "$L%s" % direction_match.group("join")
        if positive_label + ":" not in direction or join_label + ":" not in direction:
            raise ValueError("tank_input_psyq direction-flag shape changed")
        retail_direction = """bgez\t$16,{positive}
li\t$3,-2049

lw\t$2,536($17)
j\t{join}
ori\t$2,$2,0x800

{positive}:
lw\t$2,536($17)
nop
and\t$2,$2,$3
{join}:
sw\t$2,536($17)
lw\t$10,60($17)
nop
""".format(positive=positive_label, join=join_label)
        source = source[:direction_start] + retail_direction + source[direction_end:]

        tail_start = source.index("mult $6,$2", direction_start)
        tail_end = source.index("lw\t$31,188($sp)", tail_start)
        retail_tail = """mult $5,$2
mflo $9
mfhi $3
srl $9,$9,12
sll $3,$3,20
or $9,$9,$3
lui\t$3,%hi(D_800DE30C) # high
lw\t$3,%lo(D_800DE30C)($3)
addu\t$2,$9,$zero
sw\t$2,544($17)
mult $3,$2
mflo $4
mfhi $10
srl $4,$4,12
sll $10,$10,20
or $4,$4,$10
li\t$9,-2457
lw\t$2,540($17)
lw\t$10,548($17)
addu\t$2,$2,$4
sw\t$2,540($17)
mult $9,$10
mflo $4
mfhi $2
srl $4,$4,12
sll $2,$2,20
or $4,$4,$2
lw\t$2,552($17)
nop
addu\t$2,$2,$4
mult $5,$2
mflo $9
mfhi $4
srl $9,$9,12
sll $4,$4,20
or $9,$9,$4
addu\t$2,$9,$zero
sw\t$2,552($17)
mult $3,$2
mflo $10
mfhi $9
srl $10,$10,12
sll $9,$9,20
or $10,$10,$9
addu\t$3,$10,$zero
lw\t$2,548($17)
lw\t$4,536($17)
addu\t$2,$2,$3
sw\t$2,548($17)
andi\t$2,$4,0x200
bne\t$2,$0,$LTAIL_FLAGS
ori\t$2,$4,0x400
li\t$2,-1025
and\t$2,$4,$2
$LTAIL_FLAGS:
sw\t$2,536($17)
addu\t$4,$17,$zero
lw\t$2,536($4)
li\t$3,-513
and\t$2,$2,$3
jal\tfunc_80043454
sw\t$2,536($4)
$L3:
"""
        source = source[:tail_start] + retail_tail + source[tail_end:]
        path.write_text(source)
        return
    if profile == "callback_frame_setup":
        source = path.read_text()
        old = """lw\t$2,D_800B8C8C
#nop # DEBUG: 'subu\t$sp,$sp,24' does not load from $2
subu\t$sp,$sp,24
sw\t$16,16($sp)
"""
        new = """subu\t$sp,$sp,24
sw\t$16,16($sp)
lw\t$2,D_800B8C8C
"""
        if source.count(old) != 1:
            raise ValueError("callback_frame_setup shape changed")
        path.write_text(source.replace(old, new, 1))
        return
    if profile == "cd_error_string_address":
        source = path.read_text()
        replacements = (
            ("sll\t$7,$4,2", "sll\t$4,$4,2"),
            ("addu\t$7,$7,$16", "addu\t$4,$4,$16"),
            ("lw\t$7,0($7)", "lw\t$7,0($4)"),
        )
        for old, new in replacements:
            if source.count(old) != 1:
                raise ValueError("cd_error_string_address shape changed at %s" % old)
            source = source.replace(old, new, 1)
        path.write_text(source)
        return
    if profile == "sio_poll_frame32":
        source = path.read_text()
        replacements = (
            (".frame\t$sp,40,$31", ".frame\t$sp,32,$31"),
            ("subu\t$sp,$sp,40", "subu\t$sp,$sp,32"),
            ("sw\t$16,24($sp)", "sw\t$16,16($sp)"),
            ("sw\t$31,32($sp)", "sw\t$31,24($sp)"),
            ("sw\t$17,28($sp)", "sw\t$17,20($sp)"),
            ("lw\t$31,32($sp)", "lw\t$31,24($sp)"),
            ("lw\t$17,28($sp)", "lw\t$17,20($sp)"),
            ("lw\t$16,24($sp)", "lw\t$16,16($sp)"),
            ("addu\t$sp,$sp,40", "addu\t$sp,$sp,32"),
        )
        for old, new in replacements:
            if source.count(old) != 1:
                raise ValueError("sio_poll_frame32 shape changed at %s" % old)
            source = source.replace(old, new, 1)
        path.write_text(source)
        return
    if profile == "pad_read_default_layout":
        source = path.read_text()
        branch_old = """bltz\t$5,$L6
addu\t$2,$5,2
"""
        branch_new = """bltz\t$5,$L6
nop
"""
        default_old = """j\t$L22
$L6:
beq\t$2,$0,$L17
.set\tnoreorder
.set\tnomacro
j\t$L20
addu\t$2,$0,$zero
.set\tmacro
.set\treorder

$L17:
.set\tnoreorder
.set\tnomacro
beq\t$3,$0,$L20
li\t$2,0x00000042\t\t# 66
.set\tmacro
.set\treorder

andi\t$2,$3,0x00ff
"""
        default_new = """lw\t$2,44($4)
.set\tnoreorder
.set\tnomacro
j\t$L24
addu\t$2,$2,$5
.set\tmacro
.set\treorder

$L6:
addu\t$4,$5,2
.set\tnoreorder
.set\tnomacro
bne\t$4,$0,$L23
addu\t$2,$0,$zero
beq\t$3,$0,$L23
li\t$2,0x00000042\t\t# 66
.set\tmacro
.set\treorder

andi\t$2,$3,0x00ff
"""
        if source.count(branch_old) != 1 or source.count(default_old) != 1:
            raise ValueError("pad_read_default_layout shape changed")
        source = source.replace(branch_old, branch_new, 1)
        source = source.replace(default_old, default_new, 1)
        path.write_text(source)
        return
    if profile == "pad_port_advance_layout":
        source = path.read_text()
        prologue_old = """sw\t$19,28($sp)
li\t$19,-9\t\t\t# 0xfffffff7
sw\t$17,20($sp)
la\t$17,D_800EF2D8
"""
        prologue_new = """sw\t$17,20($sp)
la\t$17,D_800EF2D8
sw\t$19,28($sp)
li\t$19,-9\t\t\t# 0xfffffff7
"""
        tail_old = """bne\t$2,$0,$L30
addu\t$16,$0,$zero
.set\tmacro
.set\treorder

sll\t$4,$3,4
subu\t$4,$4,$3
sll\t$4,$4,4
.set\tnoreorder
.set\tnomacro
jal\tfunc_8009E5F4
addu\t$4,$4,$17
.set\tmacro
.set\treorder

beq\t$2,$0,$L29
$L30:
li\t$16,0x00000001\t\t# 1
$L29:
.set\tnoreorder
.set\tnomacro
beq\t$16,$0,$L20
li\t$5,0x0000ffff\t\t# 65535
.set\tmacro
.set\treorder
"""
        tail_new = """bne\t$2,$0,$L30
li\t$2,0x00000001\t\t# 1
.set\tmacro
.set\treorder

sll\t$4,$3,4
subu\t$4,$4,$3
sll\t$4,$4,4
.set\tnoreorder
.set\tnomacro
jal\tfunc_8009E5F4
addu\t$4,$4,$17
j\t$L29
li\t$5,0x0000ffff\t\t# 65535
$L30:
li\t$5,0x0000ffff\t\t# 65535
$L29:
beq\t$2,$0,$L20
nop
.set\tmacro
.set\treorder
"""
        if source.count(prologue_old) != 1 or source.count(tail_old) != 1:
            raise ValueError("pad_port_advance_layout shape changed")
        source = source.replace(prologue_old, prologue_new, 1)
        source = source.replace(tail_old, tail_new, 1)
        path.write_text(source)
        return
    if profile == "stream_open_failure_layout":
        source = path.read_text()
        branch_old = """beq\t$16,$0,$L20
li\t$4,11\t\t\t# 0x0000000b

addu\t$5,$16,$zero
"""
        branch_new = """bne\t$16,$0,$L20_success
li\t$4,11\t\t\t# 0x0000000b
j\t$L20
addu\t$16,$0,$zero

$L20_success:
addu\t$5,$16,$zero
"""
        failure_old = """$L20:
addu\t$16,$0,$zero
$L19:
"""
        failure_new = """$L20:
$L19:
"""
        if source.count(branch_old) != 1 or source.count(failure_old) != 1:
            raise ValueError("stream_open_failure_layout shape changed")
        source = source.replace(branch_old, branch_new, 1)
        source = source.replace(failure_old, failure_new, 1)
        path.write_text(source)
        return
    if profile == "debris_matrix_setup_schedule":
        source = path.read_text()
        old = """lw\t$11,8($2)
#nop # DEBUG: 'lw\t$20,4($2)' does not load from $11
lw\t$20,4($2)
#nop # DEBUG: 'addu\t$fp,$2,24' does not load from $20
addu\t$fp,$2,24
sw\t$11,68($sp)
sw\t$20,12($19)

addu\t$2,$sp,32
"""
        new = """addu\t$fp,$2,24
lw\t$20,4($2)
lw\t$11,8($2)
addu\t$2,$sp,32
sw\t$11,68($sp)
sw\t$20,12($19)

"""
        if source.count(old) != 1:
            raise ValueError("debris_matrix_setup_schedule shape changed")
        path.write_text(source.replace(old, new, 1))
        return
    if profile == "image_parse_loop_schedule":
        source = path.read_text()
        rewrites = 0
        for image_register, stack_offset in (("$20", 328), ("$16", 332)):
            pattern = re.compile(
                r"(?m)^(addu\t\$4,%s,\$zero\n)"
                r"(addu\t\$8,\$sp,%d\n)"
                r"(li\t\$11,1[^\n]*\n)"
                r"(li\t\$10,2[^\n]*\n)" % (re.escape(image_register), stack_offset)
            )
            source, count = pattern.subn(r"\2\3\4\1", source)
            if count != 1:
                raise ValueError(
                    "image_parse_loop_schedule shape changed for stack offset %d"
                    % stack_offset
                )
            rewrites += count
        if rewrites != 2:
            raise ValueError("image_parse_loop_schedule expected two rewrites")
        path.write_text(source)
        return
    if profile == "dual_axis_sum_registers":
        source = path.read_text()
        loads_old = """lbu\t$9,17($2)
#nop # DEBUG: 'lbu\t$4,25($2)' does not load from $9
lbu\t$4,25($2)
#nop # DEBUG: 'lbu\t$10,16($2)' does not load from $4
lbu\t$10,16($2)
#nop # DEBUG: 'lbu\t$8,26($2)' does not load from $10
lbu\t$8,26($2)
"""
        loads_new = """lbu\t$9,17($2)
#nop # DEBUG: 'lbu\t$8,26($2)' does not load from $9
lbu\t$8,26($2)
#nop # DEBUG: 'lbu\t$10,16($2)' does not load from $8
lbu\t$10,16($2)
#nop # DEBUG: 'lbu\t$4,25($2)' does not load from $10
lbu\t$4,25($2)
"""
        if source.count(loads_old) != 1:
            raise ValueError("dual_axis_sum_registers input-load shape changed")
        source = source.replace(loads_old, loads_new)
        source, moves = re.subn(
            r"(?m)^addu\t\$3,\$2,\$zero$", "addu\\t$4,$2,$zero", source
        )
        source, stores = re.subn(
            r"(?m)^sb\t\$3,0\(\$5\)$", "sb\\t$4,0($5)", source
        )
        final_load_old = """$L127:
lbu\t$9,0($5)
#nop # DEBUG: 'lb\t$2,0($5)' does not load from $9
lb\t$2,0($5)
#nop # DEBUG: 'lb\t$3,0($6)' does not load from $2
lb\t$3,0($6)
#nop # DEBUG: 'lbu\t$4,0($6)' does not load from $3
lbu\t$4,0($6)
"""
        final_load_new = final_load_old.replace("lbu\t$4,0($6)", "lbu\t$8,0($6)")
        loads = source.count(final_load_old)
        source = source.replace(final_load_old, final_load_new)
        source, shifts = re.subn(
            r"(?m)^sll\t\$3,\$4,24$", "sll\\t$3,$8,24", source
        )
        if (moves, stores, loads, shifts) != (2, 2, 1, 1):
            raise ValueError(
                "dual_axis_sum_registers expected 2/2/1/1 rewrites, found %s"
                % ((moves, stores, loads, shifts),)
            )
        path.write_text(source)
        return
    if profile == "stream_pad_base_schedule":
        source = path.read_text()
        old = """addu\t$5,$16,2
addu\t$9,$18,$zero
lui\t$2,%hi(D_800EE028) # high
addiu\t$6,$2,%lo(D_800EE028) # low
"""
        new = """addu\t$5,$16,2
lui\t$2,%hi(D_800EE028) # high
addiu\t$6,$2,%lo(D_800EE028) # low
addu\t$9,$18,$zero
"""
        if source.count(old) != 1:
            raise ValueError("stream_pad_base_schedule loop preheader changed")
        path.write_text(source.replace(old, new))
        return
    if profile == "sio_control_shared_return":
        path.write_text(_sio_control_shared_return(path.read_text()))
        return
    if profile == "card_directory_locals":
        path.write_text(_card_directory_locals(path.read_text()))
        return
    if profile == "card_create_cse":
        path.write_text(_card_create_cse(path.read_text()))
        return
    if profile == "font_advance_negative_layout":
        path.write_text(_font_advance_negative_layout(path.read_text()))
        return
    if profile == "vector_split_schedule":
        path.write_text(_vector_split_schedule(path.read_text()))
        return
    if profile == "card_finish_const_arg":
        path.write_text(_card_finish_const_arg(path.read_text()))
        return
    if profile == "kid_walk_tregs":
        path.write_text(_kid_walk_tregs(path.read_text()))
        return
    if profile == "cd_sync_hoist_regs":
        path.write_text(_cd_sync_hoist_regs(path.read_text()))
        return
    if profile == "cd_control_retry_psyq":
        path.write_text(_cd_control_retry_psyq(path.read_text()))
        return
    if profile == "prnt_aspsx_macros":
        path.write_text(_prnt_aspsx_macros(path.read_text()))
        return
    if profile == "stream_setup_dest_swap":
        path.write_text(_stream_setup_dest_swap(path.read_text()))
        return
    if profile == "cd_ready_report":
        path.write_text(_cd_ready_report(path.read_text()))
        return
    if profile == "cd_cw_report":
        path.write_text(_cd_cw_report(path.read_text()))
        return
    if profile == "ra_only_27_epilogue":
        source = path.read_text()
        old = """lw\t$31,16($sp)
#nop
.set\tnoreorder
.set\tnomacro
j\t$31
addu\t$sp,$sp,24
"""
        new = """lw\t$31,16($sp)
addu\t$sp,$sp,24
.set\tnoreorder
.set\tnomacro
j\t$31
nop
"""
        if source.count(old) != 1:
            raise ValueError("ra_only_27_epilogue return shape changed")
        path.write_text(source.replace(old, new))
        return
    if profile == "blip_player_schedule":
        source = path.read_text()
        old = """beq\t$2,$0,$L9
addu\t$16,$3,$zero

beq\t$2,$0,$L9
addu\t$17,$0,$zero

lui\t$2,%hi(D_800E4D70) # high
addiu\t$19,$2,%lo(D_800E4D70) # low
lui\t$2,%hi(D_800ABA6C) # high
addiu\t$18,$2,%lo(D_800ABA6C) # low
andi\t$2,$17,0x00ff
"""
        new = """beq\t$2,$0,$L9
nop

beq\t$2,$0,$L9
addu\t$17,$0,$zero

lui\t$2,%hi(D_800E4D70) # high
addiu\t$19,$2,%lo(D_800E4D70) # low
addu\t$16,$3,$zero
lui\t$2,%hi(D_800ABA6C) # high
addiu\t$18,$2,%lo(D_800ABA6C) # low
andi\t$2,$17,0x00ff
"""
        if source.count(old) != 1:
            raise ValueError("blip_player_schedule loop setup shape changed")
        path.write_text(source.replace(old, new))
        return
    if profile == "mask_copy_schedule":
        source = path.read_text()
        old = """addu\t$19,$16,$zero
lui\t$3,%hi(D_800AEC48) # high
"""
        new = """lui\t$3,%hi(D_800AEC48) # high
addu\t$19,$16,$zero
"""
        if source.count(old) != 1:
            raise ValueError("mask_copy_schedule setup shape changed")
        path.write_text(source.replace(old, new))
        return
    if profile == "particle_step_reload":
        source = path.read_text()
        old = """$L54:
lhu\t$2,32($sp)
#nop # DEBUG: 'addu\t$20,$20,-1' does not load from $2
addu\t$20,$20,-1
bgtz\t$20,$L55
addu\t$19,$19,$2
"""
        new = """$L54:
lhu\t$11,32($sp)
#nop # DEBUG: 'addu\t$20,$20,-1' does not load from $11
addu\t$20,$20,-1
bgtz\t$20,$L55
addu\t$19,$19,$11
"""
        if source.count(old) != 1:
            raise ValueError("particle_step_reload loop tail shape changed")
        path.write_text(source.replace(old, new))
        return
    if profile == "local_matrix_base":
        source = path.read_text()
        source, count = re.subn(
            r"(?m)^sw\t\$3,64\(\$sp\)$", "sw\\t$3,0($17)", source
        )
        if count != 1:
            raise ValueError(
                "local_matrix_base expected one folded frame store, found %d" % count
            )
        path.write_text(source)
        return
    if profile == "pio_bound_literal":
        source = path.read_text()
        source, count = re.subn(
            r"(?m)^addu\t\$3,\$2,\$zero$", "li\\t$3,-1", source
        )
        if count != 1:
            raise ValueError(
                "pio_bound_literal expected one copied loop bound, found %d" % count
            )
        path.write_text(source)
        return
    if profile == "offset_first_pointer_add":
        source = path.read_text()
        source, count = re.subn(
            r"(?m)^addu\t\$2,\$2,\$10$", "addu\\t$2,$10,$2", source
        )
        if count != 1:
            raise ValueError(
                "offset_first_pointer_add expected one pointer addition, found %d"
                % count
            )
        path.write_text(source)
        return
    if profile == "swap_t0_t1":
        source = path.read_text()
        source = source.replace("$8", "$__swap_t0__")
        source = source.replace("$9", "$8")
        source = source.replace("$__swap_t0__", "$9")
        path.write_text(source)
        return
    if profile == "event_callback_psyq":
        source = path.read_text()
        prologue = """addu\t$8,$6,$zero
addu\t$6,$7,$zero
sw\t$17,28($sp)
li\t$17,1\t\t\t# 0x00000001
lui\t$2,%hi(D_800EEC34) # high
lw\t$7,56($sp)
#nop # DEBUG: 'lw\t$3,%lo(D_800EEC34)($2)' does not load from $7
lw\t$3,%lo(D_800EEC34)($2) # DEBUG: leaving for assembler to expand
#nop # DEBUG: 'li\t$9,-3\t\t\t# 0xfffffffd' does not load from $3
li\t$9,-3\t\t\t# 0xfffffffd
sw\t$18,32($sp)
addu\t$18,$4,$zero
sw\t$31,36($sp)
sw\t$16,24($sp)
and\t$3,$3,$9
sw\t$3,%lo(D_800EEC34)($2)
"""
        retail_prologue = """sw\t$18,32($sp)
addu\t$18,$4,$zero
addu\t$8,$6,$zero
addu\t$6,$7,$zero
sw\t$17,28($sp)
li\t$17,1\t\t\t# 0x00000001
lui\t$4,%hi(D_800EEC34) # high
lw\t$2,%lo(D_800EEC34)($4) # DEBUG: leaving for assembler to expand
lw\t$7,56($sp)
li\t$3,-3\t\t\t# 0xfffffffd
sw\t$31,36($sp)
sw\t$16,24($sp)
and\t$2,$2,$3
sw\t$2,%lo(D_800EEC34)($4)
"""
        if source.count(prologue) != 1:
            raise ValueError("event_callback_psyq prologue shape changed")
        source = source.replace(prologue, retail_prologue)

        state_base = """lui\t$16,%hi(D_800EEC34) # high
addiu\t$16,$16,%lo(D_800EEC34) # low
"""
        retail_state_base = """lui\t$2,%hi(D_800EEC34) # high
addiu\t$16,$2,%lo(D_800EEC34) # low
"""
        if source.count(state_base) != 1:
            raise ValueError("event_callback_psyq state-base shape changed")
        source = source.replace(state_base, retail_state_base)

        sum_instruction = """lw\t$3,416($16)
nop # DEBUG: Reuse of '$3'. 'addu\t$2,$3,$2' does not use $at
addu\t$2,$3,$2
"""
        retail_sum_instruction = """lw\t$3,416($16)
nop # DEBUG: Reuse of '$3'. 'addu\t$2,$3,$2' does not use $at
addu\t$2,$2,$3
"""
        if source.count(sum_instruction) != 1:
            raise ValueError("event_callback_psyq buffer-end shape changed")
        source = source.replace(sum_instruction, retail_sum_instruction)

        callback_setup = """addu\t$7,$2,1
lui\t$2,%hi(func_8008E860) # high
addiu\t$2,$2,%lo(func_8008E860) # low
addu\t$4,$18,$zero
lw\t$6,412($16)
#nop # DEBUG: 'li\t$5,6\t\t\t# 0x00000006' does not load from $6
li\t$5,6\t\t\t# 0x00000006
"""
        retail_callback_setup = """addu\t$4,$18,$zero
li\t$5,6\t\t\t# 0x00000006
addu\t$7,$2,1
lui\t$2,%hi(func_8008E860) # high
lw\t$6,412($16)
addiu\t$2,$2,%lo(func_8008E860) # low
"""
        if source.count(callback_setup) != 1:
            raise ValueError("event_callback_psyq callback setup shape changed")
        source = source.replace(callback_setup, retail_callback_setup)
        path.write_text(source)
        return
    if profile == "route_probe_psyq":
        source = path.read_text()
        object_compare = """bne\t$2,$3,$L7
nop  # DEBUG: branch/jump
"""
        retail_object_compare = """bne\t$3,$2,$L7
nop  # DEBUG: branch/jump
"""
        if source.count(object_compare) != 1:
            raise ValueError("route_probe_psyq object comparison shape changed")
        source = source.replace(object_compare, retail_object_compare)

        state_call = """bne\t$3,$2,$L5
addu\t$5,$sp,24

addu\t$16,$sp,64
jal\tfunc_80049384
addu\t$4,$16,$zero
"""
        retail_state_call = """bne\t$3,$2,$L5
addu\t$16,$sp,64

addu\t$4,$16,$zero
jal\tfunc_80049384
addu\t$5,$sp,24
"""
        if source.count(state_call) != 1:
            raise ValueError("route_probe_psyq state call shape changed")
        source = source.replace(state_call, retail_state_call)
        path.write_text(source)
        return
    if profile == "wall_trigger_psyq":
        source = path.read_text()
        start = source.index("mult\t$2,$2\n", source.index("$L7:"))
        end = source.index("lw\t$4,20($6)\n", start)
        retail_range_test = """mult\t$2,$2
lhu\t$3,6($16)
nop
sll\t$2,$3,2
addu\t$2,$2,$3
sll\t$2,$2,3
lui\t$3,%hi(D_800C62B0) # high
addiu\t$3,$3,%lo(D_800C62B0) # low
addu\t$2,$2,$3
mflo\t$4
lh\t$2,34($2)
nop
mult\t$2,$2
lw\t$5,8($6)
addu\t$3,$7,$4
mflo\t$9
addu\t$2,$5,$9
slt\t$2,$2,$3
bne\t$2,$0,$L3
nop
"""
        source = source[:start] + retail_range_test + source[end:]

        waypoint_start = source.index("lbu\t$4,22($16)\n")
        waypoint_end = source.index("addu\t$2,$2,$4\n", waypoint_start)
        waypoint_prefix = source[waypoint_start:waypoint_end]
        labels = re.search(
            r"bne\t\$4,\$2,(\$L\d+).*?j\t(\$L\d+).*?\n(\$L\d+):\n",
            waypoint_prefix,
            re.S,
        )
        if labels is None or labels.group(1) != labels.group(3):
            raise ValueError("wall_trigger_psyq waypoint labels changed")
        non_null, joined = labels.group(1), labels.group(2)
        retail_waypoint = """lbu\t$3,22($16)
li\t$2,127
bne\t$3,$2,%s
addu\t$4,$3,$zero

j\t%s
addu\t$4,$0,$zero

%s:
sll\t$2,$4,4
""" % (non_null, joined, non_null)
        source = source[:waypoint_start] + retail_waypoint + source[waypoint_end:]
        path.write_text(source)
        return
    if profile != "gte_decoder_psyq":
        raise ValueError("unknown assembly profile %r" % profile)

    source = path.read_text()
    start = source.index("$L88:")
    end = source.index("$L235:", start)
    region = source[start:end]
    address_pattern = re.compile(
        r"(?m)^(lui|addiu)(\s+)\$9(,.*D_800B0A14\+(?:128|256).*)$"
    )
    region, address_count = address_pattern.subn(
        lambda match: match.group(0).replace("$9", "$3"), region
    )
    if address_count != 6:
        raise ValueError(
            "gte_decoder_psyq expected 6 table-base rewrites, found %d"
            % address_count
        )
    region, add_count = re.subn(
        r"(?m)^addu\s+\$2,\$2,\$9$", "addu\t$2,$2,$3", region
    )
    if add_count != 1:
        raise ValueError(
            "gte_decoder_psyq expected 1 indexed-base rewrite, found %d"
            % add_count
        )
    source = source[:start] + region + source[end:]

    class_zero_old = """$L92:

addiu\t$4,$22,%lo(D_800EC100) # low
lui\t$9,%hi(D_800B07C0) # high
srl\t$2,$8,26
andi\t$2,$2,0x0003
lui\t$5,%hi(D_800C4868) # high
srl\t$16,$8,16
andi\t$16,$16,0x001f
sw\t$2,16($sp)
sll\t$2,$16,2
addu\t$2,$2,$21
lw\t$7,%lo(D_800B07C0)($9) # DEBUG: leaving for assembler to expand
#nop # DEBUG: 'j\t$L238' does not load from $7
j\t$L238
addiu\t$5,$5,%lo(D_800C4868) # low
"""
    class_zero_new = """$L92:

lui\t$9,%hi(D_800B07C0) # high
srl\t$2,$8,26
andi\t$2,$2,0x0003
lui\t$5,%hi(D_800C4868) # high
srl\t$16,$8,16
andi\t$16,$16,0x001f
sw\t$2,16($sp)
sll\t$2,$16,2
addu\t$2,$2,$21
addiu\t$5,$5,%lo(D_800C4868) # low
lw\t$7,%lo(D_800B07C0)($9) # DEBUG: leaving for assembler to expand
j\t$L238_after_base
lui\t$3,%hi(D_800B0A14+128) # high
"""
    if source.count(class_zero_old) != 1:
        raise ValueError("gte_decoder_psyq class-zero setup shape changed")
    source = source.replace(class_zero_old, class_zero_new, 1)
    shared_base = """$L238:
lui\t$3,%hi(D_800B0A14+128) # high
lw\t$2,0($2)
"""
    shared_base_split = """$L238:
lui\t$3,%hi(D_800B0A14+128) # high
$L238_after_base:
lw\t$2,0($2)
"""
    if source.count(shared_base) != 1:
        raise ValueError("gte_decoder_psyq shared table-base shape changed")
    source = source.replace(shared_base, shared_base_split, 1)

    for immediate in (3583, 4031, 4095, 4607, 4479):
        pattern = re.compile(
            r"(?m)^(li\s+\$2,%d[^\n]*\n)"
            r"beq\s+\$3,\$2,\$L116\n"
            r"nop[^\n]*$" % immediate
        )
        replacement = (
            r"\1beq\t$3,$2,$L251\n"
            r"addiu\t$4,$22,%lo(D_800EC100) # low"
        )
        source, count = pattern.subn(replacement, source)
        if count != 1:
            raise ValueError(
                "gte_decoder_psyq expected one delay-slot rewrite for %d, found %d"
                % (immediate, count)
            )
    path.write_text(source)


def compile_unit(unit, config, prefix, work):
    assembler = command("as", prefix)
    linker = command("ld", prefix)
    objcopy = command("objcopy", prefix)
    source = ROOT / unit["source"]
    assembly = work / "unit.s"
    processed = work / "unit.maspsx.s"
    obj = work / "unit.o"
    aligned_obj = work / "unit-aligned.o"
    elf = work / "unit.elf"
    binary = work / "unit.bin"

    prepare_assembly(unit, config, source, assembly, processed)
    if unit.get("rewrite_move_pseudos"):
        rewrite_move_pseudos(processed)
    if unit.get("assembly_profile"):
        apply_assembly_profile(processed, unit["assembly_profile"])
    if small_data(unit) is not None:
        expand_absolute_la(processed)
    run_checked([assembler, "-EL", "-march=r3000", "-mabi=32", *unit_assembler_flags(unit),
                 "-no-pad-sections", "-o", str(obj), str(processed)])
    alignment = ["--set-section-alignment", ".text=4"]
    if "rodata_address" in unit:
        alignment += ["--set-section-alignment", ".rodata=4"]
    run_checked([objcopy, *alignment, str(obj), str(aligned_obj)])
    run_checked(unit_link_command(unit, linker, elf, aligned_obj, work))
    check_small_data_sections(unit, elf, prefix)
    run_checked([objcopy, "-O", "binary", "--only-section=.text", str(elf), str(binary)])
    if "rodata_address" in unit:
        rodata = work / "unit.rodata.bin"
        run_checked([objcopy, "-O", "binary", "--only-section=.rodata", str(elf), str(rodata)])
    return binary.read_bytes()


def unit_rodata(work):
    path = work / "unit.rodata.bin"
    if not path.exists():
        return None
    data = path.read_bytes().rstrip(b"\0")
    return data + b"\0" * ((-len(data)) % 4)


def verify(config_path, executable_path, output_path, prefix):
    config = json.loads(Path(config_path).read_text())
    validate_units(config)
    executable = Path(executable_path).read_bytes()
    results = []
    with tempfile.TemporaryDirectory() as directory:
        work_root = Path(directory)
        for index, unit in enumerate(config["units"]):
            unit_work = work_root / str(index)
            unit_work.mkdir()
            actual = compile_unit(unit, config, prefix, unit_work)
            address = parse_int(unit["address"])
            size = parse_int(unit["size"])
            expected = oracle_slice(executable, address, size)
            if len(actual) < size:
                actual += b"\0" * (size - len(actual))
            code = actual[:size]
            padding = actual[size:]
            if any(padding):
                raise SystemExit(
                    "%s emitted nonzero data after its expected 0x%X-byte extent"
                    % (unit["name"], size)
                )
            if code != expected:
                first = next(i for i, pair in enumerate(zip(code, expected)) if pair[0] != pair[1])
                raise SystemExit("%s differs at +0x%X" % (unit["name"], first))
            rodata = unit_rodata(unit_work)
            if rodata is not None:
                rodata_address = parse_int(unit["rodata_address"])
                if rodata != oracle_slice(executable, rodata_address, len(rodata)):
                    raise SystemExit(
                        "%s read-only data differs at 0x%08X" % (unit["name"], rodata_address)
                    )
            results.append({
                "name": unit["name"],
                "address": address,
                "size": size,
                "sha256": hashlib.sha256(actual).hexdigest(),
                "source_sha256": hashlib.sha256((ROOT / unit["source"]).read_bytes()).hexdigest(),
                "matched": True,
            })
            print("PASS %s: %d bytes" % (unit["name"], size))
    report = {
        "schema": 1,
        "compiler": config["compiler"],
        "matched_bytes": sum(item["size"] for item in results),
        "matched_functions": len(results),
        "units": results,
    }
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n")
    return report


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--config", default="config/us/matching_units.json")
    parser.add_argument("--executable", default="baseroms/us/SLUS_010.44")
    parser.add_argument("--output", default="build/us/matching_report.json")
    parser.add_argument("--binutils-prefix", default=os.environ.get("MIPSEL_PREFIX", "mipsel-linux-gnu-"))
    args = parser.parse_args(argv)
    verify(args.config, args.executable, args.output, args.binutils_prefix)


if __name__ == "__main__":
    main()
