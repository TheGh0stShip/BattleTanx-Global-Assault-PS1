#!/usr/bin/env python3
"""Compile the tracked raw-unit recovery candidates and compare them to retail."""

import json
import re
import shutil
from pathlib import Path

from verify_matching_units import compile_unit, oracle_slice


ROOT = Path(__file__).resolve().parents[1]
CONFIG_PATH = ROOT / "config/us/matching_units.json"
EXECUTABLE_PATH = ROOT / "baseroms/us/SLUS_010.44"
CANDIDATE_ROOT = ROOT / "docs/research/candidates"


def candidate_symbols(source, entry):
    text = source.read_text()
    symbols = {}
    for address in set(re.findall(r"\b(?:func|D)_([0-9A-Fa-f]{8})\b", text)):
        function = "func_" + address.upper()
        data = "D_" + address.upper()
        symbols[function if function in text else data] = "0x" + address
    symbols.pop(entry, None)
    return symbols


def main():
    config = json.loads(CONFIG_PATH.read_text())
    executable = EXECUTABLE_PATH.read_bytes()
    units = {unit["name"]: unit for unit in config["units"]}
    work_root = ROOT / "build/research_candidates"
    shutil.rmtree(work_root, ignore_errors=True)
    work_root.mkdir(parents=True)

    failed = False
    exact = 0
    target_bytes = 0
    for source in sorted(CANDIDATE_ROOT.glob("*.c")):
        name = "func_" + source.stem.upper()
        if name not in units:
            failed = True
            print("%-15s missing matching-unit metadata" % name)
            continue

        unit = units[name].copy()
        unit["source"] = str(source.relative_to(ROOT))
        unit["symbols"] = candidate_symbols(source, name)
        work = work_root / name
        work.mkdir()
        target_size = int(unit["size"], 0)
        target_bytes += target_size
        try:
            generated = compile_unit(unit, config, "mipsel-linux-gnu-", work)
        except Exception as error:
            failed = True
            print("%-15s compile failed: %s" % (name, error))
            continue

        expected = oracle_slice(executable, int(unit["address"], 0), target_size)
        equal_bytes = sum(left == right for left, right in zip(generated, expected))
        is_exact = generated == expected
        exact += is_exact
        print(
            "%-15s generated %4d / target %4d (%+d), %4d equal bytes%s"
            % (
                name,
                len(generated),
                target_size,
                len(generated) - target_size,
                equal_bytes,
                " EXACT" if is_exact else "",
            )
        )

    print(
        "%d candidates cover %d target bytes; %d exact"
        % (len(list(CANDIDATE_ROOT.glob("*.c"))), target_bytes, exact)
    )
    return int(failed)


if __name__ == "__main__":
    raise SystemExit(main())
