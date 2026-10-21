#!/usr/bin/env python3
"""Compile one large candidate and summarize MIPS instruction differences.

The exact verifier remains authoritative.  This report is an iteration aid: it
separates branch/jump displacement noise from instruction-content mismatches and
groups nearby mismatches into actionable regions.
"""

import argparse
import difflib
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

try:
    from .verify_large_candidates import (
        CANDIDATES, CONFIG_PATH, EXECUTABLE_PATH, candidate_symbols,
    )
    from .verify_matching_units import compile_unit, oracle_slice
except ImportError:
    from verify_large_candidates import (
        CANDIDATES, CONFIG_PATH, EXECUTABLE_PATH, candidate_symbols,
    )
    from verify_matching_units import compile_unit, oracle_slice


ROOT = Path(__file__).resolve().parents[1]
FLOW_OPCODES = frozenset((1, 2, 3, 4, 5, 6, 7))


def words(data):
    """Return complete little-endian MIPS words from *data*."""
    return [item[0] for item in struct.iter_unpack("<I", data[:len(data) & ~3])]


def opcode(word):
    return word >> 26


def normalized_word(word):
    """Mask only PC-relative/absolute control-flow target fields."""
    op = opcode(word)
    if op in (1, 4, 5, 6, 7):
        return word & 0xFFFF0000
    if op in (2, 3):
        return word & 0xFC000000
    return word


def classify_pair(actual, expected):
    if actual == expected:
        return "exact"
    actual_op = opcode(actual)
    expected_op = opcode(expected)
    if actual_op == expected_op and actual_op in FLOW_OPCODES:
        mask = 0xFC000000 if actual_op in (2, 3) else 0xFFFF0000
        if actual & mask == expected & mask:
            return "flow-target"
    if actual_op != expected_op:
        return "opcode"
    if actual_op == 0:
        if actual & 0x3F != expected & 0x3F:
            return "opcode"
        if actual & 0x7FF == expected & 0x7FF:
            return "register"
        return "operand"
    if actual & 0xFFFF == expected & 0xFFFF:
        return "register"
    if actual & 0x03FFFFFF == expected & 0x03FFFFFF:
        return "register"
    return "immediate-or-register"


def aligned_differences(actual, expected):
    actual_words = words(actual)
    expected_words = words(expected)
    matcher = difflib.SequenceMatcher(
        None,
        [normalized_word(word) for word in expected_words],
        [normalized_word(word) for word in actual_words],
        autojunk=False,
    )
    differences = []
    for tag, expected_start, expected_end, actual_start, actual_end in matcher.get_opcodes():
        if tag == "equal":
            for expected_index, actual_index in zip(
                range(expected_start, expected_end), range(actual_start, actual_end)
            ):
                kind = classify_pair(actual_words[actual_index], expected_words[expected_index])
                if kind != "exact":
                    differences.append({
                        "kind": kind,
                        "target_offset": expected_index * 4,
                        "candidate_offset": actual_index * 4,
                        "target_word": "%08x" % expected_words[expected_index],
                        "candidate_word": "%08x" % actual_words[actual_index],
                    })
            continue
        differences.append({
            "kind": {"replace": "content", "delete": "candidate-missing",
                     "insert": "candidate-extra"}[tag],
            "target_offset": expected_start * 4,
            "candidate_offset": actual_start * 4,
            "target_instructions": expected_end - expected_start,
            "candidate_instructions": actual_end - actual_start,
        })
    return differences


def group_regions(differences, distance=0x20):
    regions = []
    for difference in differences:
        offset = difference["target_offset"]
        if not regions or offset - regions[-1]["end"] > distance:
            regions.append({"start": offset, "end": offset + 4, "differences": []})
        region = regions[-1]
        region["end"] = max(region["end"], offset + 4)
        region["differences"].append(difference)
    for region in regions:
        counts = {}
        for difference in region["differences"]:
            kind = difference["kind"]
            counts[kind] = counts.get(kind, 0) + 1
        region["counts"] = counts
    return regions


def analyze(name, prefix):
    config = json.loads(CONFIG_PATH.read_text())
    units = {unit["name"]: unit for unit in config["units"]}
    unit = units[name].copy()
    source = ROOT / CANDIDATES[name]
    unit["source"] = CANDIDATES[name]
    unit["symbols"] = candidate_symbols(source, name)
    if name == "func_80044C38":
        unit["maspsx_flags_extra"] = ["--expand-div"]

    work = ROOT / "build/large_candidates" / name
    work.mkdir(parents=True, exist_ok=True)
    actual = compile_unit(unit, config, prefix, work)
    size = int(unit["size"], 0)
    expected = oracle_slice(EXECUTABLE_PATH.read_bytes(), int(unit["address"], 0), size)
    differences = aligned_differences(actual, expected)
    exact_bytes = sum(left == right for left, right in zip(actual, expected))
    result = {
        "name": name,
        "candidate_size": len(actual),
        "target_size": len(expected),
        "size_delta": len(actual) - len(expected),
        "same_offset_equal_bytes": exact_bytes,
        "exact": actual == expected,
        "difference_counts": {},
        "regions": group_regions(differences),
    }
    for difference in differences:
        kind = difference["kind"]
        result["difference_counts"][kind] = result["difference_counts"].get(kind, 0) + 1
    actionable = [item for item in differences if item["kind"] != "flow-target"]
    result["first_actionable"] = actionable[0] if actionable else None
    return result


def print_text(result, limit):
    print(
        "%s: %d/%d bytes (%+d), %d equal at the same offsets%s"
        % (
            result["name"], result["candidate_size"], result["target_size"],
            result["size_delta"], result["same_offset_equal_bytes"],
            " EXACT" if result["exact"] else "",
        )
    )
    print("difference classes: %s" % json.dumps(result["difference_counts"], sort_keys=True))
    first = result["first_actionable"]
    if first:
        print(
            "first actionable: target +0x%X, candidate +0x%X (%s)"
            % (first["target_offset"], first["candidate_offset"], first["kind"])
        )
    for region in result["regions"][:limit]:
        print(
            "  +0x%04X..+0x%04X %s"
            % (region["start"], region["end"], json.dumps(region["counts"], sort_keys=True))
        )


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("name", choices=sorted(CANDIDATES))
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--regions", type=int, default=12)
    parser.add_argument(
        "--binutils-prefix",
        default=os.environ.get("MIPSEL_PREFIX", "mipsel-linux-gnu-"),
    )
    args = parser.parse_args(argv)
    result = analyze(args.name, args.binutils_prefix)
    if args.json:
        json.dump(result, sys.stdout, indent=2, sort_keys=True)
        print()
    else:
        print_text(result, args.regions)
    return int(not result["exact"])


if __name__ == "__main__":
    raise SystemExit(main())
