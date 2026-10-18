#!/usr/bin/env python3
"""Inventory provisional function starts from a generated assembly split."""

import argparse
import json
import re
from pathlib import Path


TEXT_START = 0x80010000
TEXT_END = 0x800C6800
FUNCTION_RE = re.compile(r"^glabel func_([0-9A-Fa-f]{8})$")
NAMED_FUNCTIONS = {"glabel entrypoint": 0x800860B0}


def scan(text):
    addresses = []
    for line in text.splitlines():
        stripped = line.strip()
        match = FUNCTION_RE.match(stripped)
        if match:
            addresses.append(int(match.group(1), 16))
        elif stripped in NAMED_FUNCTIONS:
            addresses.append(NAMED_FUNCTIONS[stripped])
    if addresses != sorted(set(addresses)):
        raise ValueError("function candidates are duplicated or out of order")
    for address in addresses:
        if not TEXT_START <= address < TEXT_END:
            raise ValueError("candidate 0x%08X is outside loaded text" % address)
        if address & 3:
            raise ValueError("candidate 0x%08X is not word-aligned" % address)
    return addresses


def build_report(addresses):
    return {
        "schema": 1,
        "classification": "provisional call-target candidates",
        "loaded_range": [TEXT_START, TEXT_END],
        "count": len(addresses),
        "addresses": addresses,
        "warning": "Candidates are not reviewed boundaries and award no matching progress.",
    }


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("assembly")
    parser.add_argument("output")
    args = parser.parse_args(argv)
    addresses = scan(Path(args.assembly).read_text())
    report = build_report(addresses)
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print("inventoried %d provisional function starts" % len(addresses))


if __name__ == "__main__":
    main()
