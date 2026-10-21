#!/usr/bin/env python3
"""Generate an objdiff-compatible progress report from the exact unit manifest."""

import argparse
import json
from pathlib import Path


MEASURE_KEYS = (
    "fuzzy_match_percent", "total_code", "matched_code",
    "matched_code_percent", "total_data", "matched_data",
    "matched_data_percent", "total_functions", "matched_functions",
    "matched_functions_percent", "complete_code", "complete_code_percent",
    "complete_data", "complete_data_percent", "total_units", "complete_units",
)


def percent(matched, total):
    return 100 * matched / total if total else 0


def measures(code=0, matched_code=0, data=0, matched_data=0,
             functions=0, matched_functions=0, units=0, complete_units=0):
    return {
        "fuzzy_match_percent": percent(matched_code, code),
        "total_code": code,
        "matched_code": matched_code,
        "matched_code_percent": percent(matched_code, code),
        "total_data": data,
        "matched_data": matched_data,
        "matched_data_percent": percent(matched_data, data),
        "total_functions": functions,
        "matched_functions": matched_functions,
        "matched_functions_percent": percent(matched_functions, functions),
        "complete_code": matched_code,
        "complete_code_percent": percent(matched_code, code),
        "complete_data": matched_data,
        "complete_data_percent": percent(matched_data, data),
        "total_units": units,
        "complete_units": complete_units,
    }


def add_measures(items):
    return measures(
        code=sum(item["total_code"] for item in items),
        matched_code=sum(item["matched_code"] for item in items),
        data=sum(item["total_data"] for item in items),
        matched_data=sum(item["matched_data"] for item in items),
        functions=sum(item["total_functions"] for item in items),
        matched_functions=sum(item["matched_functions"] for item in items),
        units=sum(item["total_units"] for item in items),
        complete_units=sum(item["complete_units"] for item in items),
    )


def is_semantic_source(path, unit=None):
    source = Path(path).read_text().lstrip()
    if unit and unit.get("language") == "assembly":
        return ".word" not in source
    return not source.startswith(("asm(", "__asm__("))


def generate(config):
    config = Path(config).resolve()
    root = config.parents[2]
    manifest = json.loads(config.read_text())
    report_units = []
    for unit in sorted(manifest["units"], key=lambda item: int(item["address"], 0)):
        size = int(unit["size"], 0)
        address = int(unit["address"], 0)
        is_data = unit.get("kind") in ("data", "padding")
        semantic = not is_data and is_semantic_source(root / unit["source"], unit)
        if is_data:
            unit_measures = measures(
                data=size, matched_data=size, units=1, complete_units=1
            )
        else:
            unit_measures = measures(
                code=size,
                matched_code=size if semantic else 0,
                functions=1,
                matched_functions=1 if semantic else 0,
                units=1,
                complete_units=1 if semantic else 0,
            )
        functions = [] if is_data else [{
            "name": unit["name"],
            "size": size,
            "fuzzy_match_percent": 100 if semantic else 0,
            "metadata": {"virtual_address": address},
            "address": 0,
        }]
        report_units.append({
            "name": unit["name"],
            "measures": unit_measures,
            "sections": [],
            "functions": functions,
            "metadata": {
                "complete": is_data or semantic,
                "source_path": unit["source"],
                "progress_categories": ["executable"],
            },
        })
    total = add_measures([unit["measures"] for unit in report_units])
    return {
        "measures": total,
        "units": report_units,
        "version": 2,
        "categories": [{"id": "executable", "name": "Executable", "measures": total}],
    }


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--config", default="config/us/matching_units.json")
    parser.add_argument("--output", default="build/us/report.json")
    args = parser.parse_args(argv)
    report = generate(args.config)
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n")
    print(
        "reported %d/%d code bytes and %d/%d data bytes"
        % (
            report["measures"]["matched_code"], report["measures"]["total_code"],
            report["measures"]["matched_data"], report["measures"]["total_data"],
        )
    )


if __name__ == "__main__":
    main()
