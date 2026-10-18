#!/usr/bin/env python3
"""Compile reviewed game units and require exact bytes against the executable."""

import argparse
import hashlib
import json
import os
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


def run_checked(args, **kwargs):
    subprocess.run(args, check=True, **kwargs)


def compile_unit(unit, config, prefix, work):
    cc1 = ROOT / ".toolchain/gcc-2.8.1-psx/cc1"
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

    run_checked([str(cc1), str(source), *config["compiler_flags"], "-o", str(assembly)])
    with processed.open("wb") as output:
        run_checked(
            [sys.executable, str(maspsx), *config["maspsx_flags"], str(assembly)],
            stdout=output,
        )
    run_checked([assembler, "-EL", "-march=r3000", "-mabi=32", "-G0", "-o", str(obj), str(processed)])
    run_checked([objcopy, "--set-section-alignment", ".text=4", str(obj), str(aligned_obj)])
    address = parse_int(unit["address"])
    link = [
        linker, "-EL", "-m", "elf32ltsmip", "-Ttext", "0x%08X" % address,
        "-e", unit["name"], "-o", str(elf), str(aligned_obj),
    ]
    for name, value in sorted(unit.get("symbols", {}).items()):
        link.extend(("--defsym", "%s=0x%08X" % (name, parse_int(value))))
    run_checked(link)
    run_checked([objcopy, "-O", "binary", "--only-section=.text", str(elf), str(binary)])
    return binary.read_bytes()


def verify(config_path, executable_path, output_path, prefix):
    config = json.loads(Path(config_path).read_text())
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
