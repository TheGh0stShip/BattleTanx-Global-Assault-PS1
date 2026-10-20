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


COMPILERS = ("gcc-2.8.1-psx", "gcc-2.7.2-psx")


def compiler_path(unit, config):
    """cc1 for a unit: its own "compiler" entry, else the manifest default."""
    name = unit.get("compiler", config.get("compiler", COMPILERS[0]))
    if name not in COMPILERS:
        raise ValueError("unsupported compiler for %s: %s" % (unit.get("name"), name))
    return ROOT / (".toolchain/%s/cc1" % name)


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


def compile_unit(unit, config, prefix, work):
    cc1 = compiler_path(unit, config)
    maspsx = ROOT / (".toolchain/maspsx-%s/maspsx.py" % MASPSX_COMMIT)
    if not cc1.is_file() or not maspsx.is_file():
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
    run_checked([str(cc1), str(source), *compiler_flags, "-o", str(assembly)])
    with processed.open("wb") as output:
        run_checked(
            [sys.executable, str(maspsx), *config["maspsx_flags"],
             *unit.get("maspsx_flags_extra", []), str(assembly)],
            stdout=output,
        )
    if unit.get("rewrite_move_pseudos"):
        rewrite_move_pseudos(processed)
    run_checked([assembler, "-EL", "-march=r3000", "-mabi=32", "-G0", "-o", str(obj), str(processed)])
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
                raise SystemExit(
                    "%s emitted only 0x%X bytes, expected 0x%X"
                    % (unit["name"], len(actual), size)
                )
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
