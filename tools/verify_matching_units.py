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
