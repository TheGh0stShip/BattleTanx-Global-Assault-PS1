#!/usr/bin/env python3
"""Compile a large candidate and print comparable target/candidate regions."""

import argparse
import json
import os
from pathlib import Path
import subprocess

try:
    from .analyze_large_candidate import analyze
    from .verify_large_candidates import CANDIDATES, CONFIG_PATH, EXECUTABLE_PATH
    from .verify_matching_units import oracle_slice
except ImportError:
    from analyze_large_candidate import analyze
    from verify_large_candidates import CANDIDATES, CONFIG_PATH, EXECUTABLE_PATH
    from verify_matching_units import oracle_slice


ROOT = Path(__file__).resolve().parents[1]


def disassemble(path, base, prefix):
    command = [
        prefix + "objdump", "-D", "-b", "binary", "-m", "mips:3000", "-EL",
        "--adjust-vma=0x%x" % base, str(path),
    ]
    output = subprocess.run(command, check=True, text=True, stdout=subprocess.PIPE).stdout
    return [line for line in output.splitlines() if ":\t" in line]


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("name", choices=sorted(CANDIDATES))
    parser.add_argument("offset", type=lambda value: int(value, 0))
    parser.add_argument("--length", type=lambda value: int(value, 0), default=0x100)
    parser.add_argument("--binutils-prefix", default=os.environ.get("MIPSEL_PREFIX", "mipsel-linux-gnu-"))
    args = parser.parse_args(argv)

    config = json.loads(CONFIG_PATH.read_text())
    unit = next(item for item in config["units"] if item["name"] == args.name)
    result = analyze(args.name, args.binutils_prefix)
    base = int(unit["address"], 0)
    target = oracle_slice(EXECUTABLE_PATH.read_bytes(), base, int(unit["size"], 0))
    work = ROOT / "build" / "large_candidates" / args.name
    candidate = (work / "unit.bin").read_bytes()
    start = args.offset & ~3
    end = min(max(len(target), len(candidate)), start + args.length)
    target_path = work / "region.target.bin"
    candidate_path = work / "region.candidate.bin"
    target_path.write_bytes(target[start:end])
    candidate_path.write_bytes(candidate[start:end])

    print("%s: candidate %d, target %d, delta %+d" % (
        args.name, result["candidate_size"], result["target_size"], result["size_delta"]))
    print("TARGET")
    print("\n".join(disassemble(target_path, base + start, args.binutils_prefix)))
    print("CANDIDATE")
    print("\n".join(disassemble(candidate_path, base + start, args.binutils_prefix)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
