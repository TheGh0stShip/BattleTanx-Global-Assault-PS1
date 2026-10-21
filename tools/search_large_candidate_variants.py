#!/usr/bin/env python3
"""Batch-compile and rank semantic source-shape variants for a large function.

The JSON specification contains independent literal replacement sites.  Every
combination is compiled with the real matching pipeline, allowing one command
to test a bounded source-shape search instead of hand-editing and rebuilding.

Example specification::

  {"sites": [{"old": "if (x) {", "variants": [
      {"name": "if", "text": "if (x) {"},
      {"name": "if-not", "text": "if (!x) {"}
  ]}]}
"""

import argparse
import concurrent.futures
import hashlib
import itertools
import json
import os
from pathlib import Path
import shutil

try:
    from .analyze_large_candidate import aligned_differences
    from .verify_large_candidates import (
        CANDIDATES, CONFIG_PATH, EXECUTABLE_PATH, candidate_symbols,
    )
    from .verify_matching_units import compile_unit, oracle_slice
except ImportError:
    from analyze_large_candidate import aligned_differences
    from verify_large_candidates import (
        CANDIDATES, CONFIG_PATH, EXECUTABLE_PATH, candidate_symbols,
    )
    from verify_matching_units import compile_unit, oracle_slice


ROOT = Path(__file__).resolve().parents[1]


def materialize_variants(source, specification, maximum):
    sites = specification.get("sites", [])
    choices = []
    for index, site in enumerate(sites):
        old = site["old"]
        count = source.count(old)
        if count != 1:
            raise ValueError("site %d occurs %d times, expected exactly once" % (index, count))
        variants = site.get("variants", [])
        if not variants:
            raise ValueError("site %d has no variants" % index)
        choices.append(variants)
    combinations = itertools.product(*choices) if choices else [()]
    for number, combination in enumerate(combinations):
        if number >= maximum:
            raise ValueError("variant count exceeds --max-variants=%d" % maximum)
        text = source
        names = []
        for site, variant in zip(sites, combination):
            text = text.replace(site["old"], variant["text"], 1)
            names.append(variant["name"])
        yield "+".join(names) if names else "baseline", text


def unique_source_variants(variants):
    """Keep the first name for each distinct generated source."""
    seen = set()
    unique = []
    for name, source in variants:
        digest = hashlib.sha256(source.encode()).digest()
        if digest in seen:
            continue
        seen.add(digest)
        unique.append((name, source))
    return unique


def actionable_cost(differences):
    cost = 0
    for difference in differences:
        kind = difference["kind"]
        if kind == "flow-target":
            continue
        if kind in ("candidate-missing", "candidate-extra", "content"):
            cost += max(
                difference.get("target_instructions", 1),
                difference.get("candidate_instructions", 1),
            )
        else:
            cost += 1
    return cost


def evaluate(item, name, unit, config, expected, prefix, root, compiler_flags_extra):
    variant_name, source_text = item
    digest = hashlib.sha256(source_text.encode()).hexdigest()[:16]
    directory = root / digest
    directory.mkdir(parents=True, exist_ok=True)
    source_path = directory / (name + ".c")
    source_path.write_text(source_text)
    candidate = unit.copy()
    candidate["source"] = str(source_path.relative_to(ROOT))
    candidate["symbols"] = candidate_symbols(source_path, name)
    if compiler_flags_extra is not None:
        candidate["compiler_flags_extra"] = compiler_flags_extra
    compile_directory = directory / "compile"
    compile_directory.mkdir()
    try:
        actual = compile_unit(candidate, config, prefix, compile_directory)
    except Exception as error:
        return {"name": variant_name, "digest": digest, "compile_error": str(error)}
    differences = aligned_differences(actual, expected)
    counts = {}
    for difference in differences:
        kind = difference["kind"]
        counts[kind] = counts.get(kind, 0) + 1
    equal_bytes = sum(left == right for left, right in zip(actual, expected))
    cost = actionable_cost(differences)
    return {
        "name": variant_name,
        "digest": digest,
        "candidate_size": len(actual),
        "size_delta": len(actual) - len(expected),
        "same_offset_equal_bytes": equal_bytes,
        "actionable_cost": cost,
        "difference_counts": counts,
        "exact": actual == expected,
        "score": [int(actual == expected), -cost, equal_bytes, -abs(len(actual) - len(expected))],
    }


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("name", choices=sorted(CANDIDATES))
    parser.add_argument("spec", type=Path)
    parser.add_argument("--jobs", type=int, default=max(1, min(8, os.cpu_count() or 1)))
    parser.add_argument("--max-variants", type=int, default=256)
    parser.add_argument("--keep", type=int, default=20)
    parser.add_argument("--json", action="store_true")
    parser.add_argument(
        "--compiler-flags-extra",
        help="replace the unit's extra cc1 flags with this whitespace-separated list",
    )
    parser.add_argument(
        "--binutils-prefix",
        default=os.environ.get("MIPSEL_PREFIX", "mipsel-linux-gnu-"),
    )
    args = parser.parse_args(argv)
    compiler_flags_extra = (
        args.compiler_flags_extra.split()
        if args.compiler_flags_extra is not None else None
    )

    config = json.loads(CONFIG_PATH.read_text())
    unit = next(item.copy() for item in config["units"] if item["name"] == args.name)
    if args.name == "func_80044C38":
        unit["maspsx_flags_extra"] = ["--expand-div"]
    source = (ROOT / CANDIDATES[args.name]).read_text()
    specification = json.loads(args.spec.read_text())
    variants = unique_source_variants(
        materialize_variants(source, specification, args.max_variants)
    )
    target_size = int(unit["size"], 0)
    expected = oracle_slice(
        EXECUTABLE_PATH.read_bytes(), int(unit["address"], 0), target_size
    )
    work = ROOT / "build/variant_search" / args.name
    shutil.rmtree(work, ignore_errors=True)
    work.mkdir(parents=True)

    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [
            pool.submit(
                evaluate, item, args.name, unit, config, expected,
                args.binutils_prefix, work, compiler_flags_extra,
            )
            for item in variants
        ]
        results = [future.result() for future in futures]
    results.sort(key=lambda item: item.get("score", [-1]), reverse=True)
    results = results[:args.keep]
    if args.json:
        print(json.dumps(results, indent=2, sort_keys=True))
    else:
        for result in results:
            if "compile_error" in result:
                print("FAIL %-32s %s" % (result["name"], result["compile_error"]))
                continue
            print(
                "%-32s cost=%4d equal=%5d size=%+5d %s"
                % (
                    result["name"], result["actionable_cost"],
                    result["same_offset_equal_bytes"], result["size_delta"],
                    result["difference_counts"],
                )
            )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
