#!/usr/bin/env python3
"""Compile and size the current large-function research candidates."""

import json
import re
import shutil
from pathlib import Path

from verify_matching_units import compile_unit, oracle_slice


ROOT = Path(__file__).resolve().parents[1]
CONFIG_PATH = ROOT / "config/us/matching_units.json"
EXECUTABLE_PATH = ROOT / "baseroms/us/SLUS_010.44"
CANDIDATES = {
    "func_80044C38": "docs/research/80044C38_candidate.c",
    "func_80065920": "docs/research/80065920_candidate.c",
    "func_8007AE20": "docs/research/8007AE20_candidate.c",
    "func_8008BF7C": "docs/research/8008BF7C_candidate.c",
    "func_800940C4": "docs/research/800940C4_candidate.c",
}


def candidate_symbols(source, entry):
    text = source.read_text()
    addresses = set(re.findall(r"\b(?:func|D)_([0-9A-Fa-f]{8})\b", text))
    symbols = {}
    for address in addresses:
        function = "func_" + address
        name = function if function in text else "D_" + address
        symbols[name] = "0x" + address
    symbols.pop(entry, None)
    return symbols


def main():
    config = json.loads(CONFIG_PATH.read_text())
    executable = EXECUTABLE_PATH.read_bytes()
    units = {unit["name"]: unit for unit in config["units"]}
    work_root = ROOT / "build/large_candidates"
    shutil.rmtree(work_root, ignore_errors=True)
    work_root.mkdir(parents=True)

    failed = False
    for name, relative_source in CANDIDATES.items():
        unit = units[name].copy()
        unit["source"] = relative_source
        unit["symbols"] = candidate_symbols(ROOT / relative_source, name)
        if name == "func_80044C38":
            unit["maspsx_flags_extra"] = ["--expand-div"]

        work = work_root / name
        work.mkdir()
        target_size = int(unit["size"], 0)
        try:
            generated = compile_unit(unit, config, "mipsel-linux-gnu-", work)
        except Exception as error:
            failed = True
            print("%-15s compile failed: %s" % (name, error))
            continue

        delta = len(generated) - target_size
        expected = oracle_slice(executable, int(unit["address"], 0), target_size)
        compared = min(len(generated), target_size)
        equal_bytes = sum(
            generated[index] == expected[index] for index in range(compared)
        )
        exact = len(generated) == target_size and generated == expected
        first_difference = next(
            (
                index
                for index in range(compared)
                if generated[index] != expected[index]
            ),
            compared,
        )
        print(
            "%-15s generated %5d / target %5d (%+d), "
            "%5d equal bytes, first difference +0x%X%s"
            % (
                name,
                len(generated),
                target_size,
                delta,
                equal_bytes,
                first_difference,
                " EXACT" if exact else "",
            )
        )

    return int(failed)


if __name__ == "__main__":
    raise SystemExit(main())
