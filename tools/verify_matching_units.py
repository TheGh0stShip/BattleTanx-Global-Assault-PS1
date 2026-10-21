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
        compiler_path(unit, config)
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
    maspsx = ROOT / (".toolchain/maspsx-%s/maspsx.py" % MASPSX_COMMIT)
    if not maspsx.is_file():
        raise SystemExit("matching toolchain missing; run tools/bootstrap_toolchain.sh")
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

    compiler_flags = config["compiler_flags"] + unit.get("compiler_flags_extra", [])
    run_compiler(unit, config, source, assembly, compiler_flags)
    with processed.open("wb") as output:
        run_checked(
            [sys.executable, str(maspsx), *config["maspsx_flags"],
             *unit.get("maspsx_flags_extra", []), str(assembly)],
            stdout=output,
        )
    if unit.get("rewrite_move_pseudos"):
        rewrite_move_pseudos(processed)
    if unit.get("assembly_profile"):
        apply_assembly_profile(processed, unit["assembly_profile"])
    run_checked([assembler, "-EL", "-march=r3000", "-mabi=32", "-G0",
                 "-no-pad-sections", "-o", str(obj), str(processed)])
    alignment = ["--set-section-alignment", ".text=4"]
    if "rodata_address" in unit:
        alignment += ["--set-section-alignment", ".rodata=4"]
    run_checked([objcopy, *alignment, str(obj), str(aligned_obj)])
    address = parse_int(unit["address"])
    link = [
        linker, "-EL", "-m", "elf32ltsmip", "-Ttext", "0x%08X" % address,
        "-e", unit["name"], "-o", str(elf), str(aligned_obj),
    ]
    if "rodata_address" in unit:
        link.append("--section-start=.rodata=0x%08X" % parse_int(unit["rodata_address"]))
    for name, value in sorted(unit.get("symbols", {}).items()):
        link.extend(("--defsym", "%s=0x%08X" % (name, parse_int(value))))
    run_checked(link)
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
