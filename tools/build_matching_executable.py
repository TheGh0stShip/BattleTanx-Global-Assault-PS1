#!/usr/bin/env python3
"""Build one linked image from the exact source-unit manifest."""

import argparse
import concurrent.futures
import hashlib
import json
import os
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

try:
    from .verify_matching_units import (
        HEADER_SIZE, LOAD_ADDRESS, MASPSX_COMMIT, ROOT, command, compiler_path, parse_int,
        rewrite_move_pseudos, validate_units,
    )
except ImportError:
    from verify_matching_units import (
        HEADER_SIZE, LOAD_ADDRESS, MASPSX_COMMIT, ROOT, command, compiler_path, parse_int,
        rewrite_move_pseudos, validate_units,
    )


def run(args, **kwargs):
    result = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, **kwargs)
    if result.returncode:
        sys.stderr.buffer.write(result.stdout)
        sys.stderr.buffer.write(result.stderr)
        raise subprocess.CalledProcessError(result.returncode, args)
    return result


def build_header(metadata):
    header = bytearray(HEADER_SIZE)
    magic = metadata["magic"].encode("ascii")
    marker = metadata["region_marker"].encode("ascii") + b"\0"
    if magic != b"PS-X EXE" or len(marker) > HEADER_SIZE - 0x4C:
        raise ValueError("invalid executable header metadata")
    header[:len(magic)] = magic
    fields = (
        "entrypoint", "global_pointer", "load_address", "payload_size",
        "data_address", "data_size", "bss_address", "bss_size",
        "stack_address", "stack_size",
    )
    struct.pack_into("<10I", header, 0x10, *(parse_int(metadata[key]) for key in fields))
    header[0x4C:0x4C + len(marker)] = marker
    return bytes(header)


def compile_object(item, config, prefix, work_root):
    index, unit = item
    cc1 = compiler_path(unit, config)
    maspsx = ROOT / (".toolchain/maspsx-%s/maspsx.py" % MASPSX_COMMIT)
    assembler = command("as", prefix)
    linker = command("ld", prefix)
    objcopy = command("objcopy", prefix)
    work = work_root / ("unit-%04d" % index)
    work.mkdir()
    assembly = work / "unit.s"
    processed = work / "unit.maspsx.s"
    obj = work / "unit.o"
    aligned = work / "unit-aligned.o"
    resolved = work / "unit-resolved.elf"
    wrapped = work / "unit-wrapped.o"
    placed = work / "unit-placed.o"
    binary = work / "unit.bin"
    trimmed = work / "unit-trimmed.bin"
    wrapper = work / "unit-wrapper.s"
    section = ".unit%04d" % index
    flags = config["compiler_flags"] + unit.get("compiler_flags_extra", [])

    run([str(cc1), str(ROOT / unit["source"]), *flags, "-o", str(assembly)])
    with processed.open("wb") as output:
        result = subprocess.run(
            [sys.executable, str(maspsx), *config["maspsx_flags"],
             *unit.get("maspsx_flags_extra", []), str(assembly)],
            stdout=output,
            stderr=subprocess.PIPE,
        )
    if result.returncode:
        sys.stderr.buffer.write(result.stderr)
        raise subprocess.CalledProcessError(result.returncode, result.args)
    if unit.get("rewrite_move_pseudos"):
        rewrite_move_pseudos(processed)
    run([assembler, "-EL", "-march=r3000", "-mabi=32", "-G0",
         "-no-pad-sections", "-o", str(obj), str(processed)])
    alignment = ["--set-section-alignment", ".text=4"]
    if "rodata_address" in unit:
        alignment += ["--set-section-alignment", ".rodata=4"]
    run([objcopy, *alignment, str(obj), str(aligned)])
    address = parse_int(unit["address"])
    link = [
        linker, "-EL", "-m", "elf32ltsmip", "-Ttext", "0x%08X" % address,
        "-e", unit["name"], "-o", str(resolved), str(aligned),
    ]
    if "rodata_address" in unit:
        link.append("--section-start=.rodata=0x%08X" % parse_int(unit["rodata_address"]))
    for name, value in sorted(unit.get("symbols", {}).items()):
        link.extend(("--defsym", "%s=0x%08X" % (name, parse_int(value))))
    run(link)
    run([objcopy, "-O", "binary", "--only-section=.text", str(resolved), str(binary)])
    actual = binary.read_bytes()
    expected_size = parse_int(unit["size"])
    if len(actual) < expected_size:
        actual += b"\0" * (expected_size - len(actual))
    if any(actual[expected_size:]):
        raise SystemExit(
            "%s emitted invalid bytes outside its 0x%X-byte extent (object size 0x%X)"
            % (unit["name"], expected_size, len(actual))
        )
    trimmed.write_bytes(actual[:expected_size])
    wrapper.write_text(
        '.section %s, "ax"\n.incbin "%s"\n' % (section, trimmed)
    )
    run([assembler, "-EL", "-march=r3000", "-mabi=32", "-G0",
         "-no-pad-sections", "-o", str(wrapped), str(wrapper)])
    run([objcopy, "--set-section-alignment", "%s=4" % section, str(wrapped), str(placed)])
    return index, unit, section, placed


def build(config_path, metadata_path, executable_path, output_path, report_path, prefix, jobs):
    config = json.loads(Path(config_path).read_text())
    metadata = json.loads(Path(metadata_path).read_text())
    validate_units(config)
    units = sorted(config["units"], key=lambda unit: parse_int(unit["address"]))
    retail = Path(executable_path).read_bytes()
    header = build_header(metadata)
    if retail[:HEADER_SIZE] != header:
        raise SystemExit("reconstructed executable header differs from retail")
    payload_size = parse_int(metadata["payload_size"])
    if len(retail) != HEADER_SIZE + payload_size:
        raise SystemExit("retail executable size disagrees with metadata")
    if not units or parse_int(units[0]["address"]) != LOAD_ADDRESS:
        raise SystemExit("manifest does not begin at the executable load address")
    cursor = LOAD_ADDRESS
    for unit in units:
        address = parse_int(unit["address"])
        if address != cursor:
            raise SystemExit("manifest gap before %s" % unit["name"])
        cursor += parse_int(unit["size"])
    if cursor != LOAD_ADDRESS + payload_size:
        raise SystemExit("manifest does not cover the complete executable payload")

    compilers = {compiler_path(unit, config) for unit in units}
    maspsx = ROOT / (".toolchain/maspsx-%s/maspsx.py" % MASPSX_COMMIT)
    if not all(cc1.is_file() for cc1 in compilers) or not maspsx.is_file():
        raise SystemExit("matching toolchain missing; run tools/bootstrap_toolchain.sh")
    linker = command("ld", prefix)
    objcopy = command("objcopy", prefix)

    with tempfile.TemporaryDirectory() as directory:
        work = Path(directory)
        indexed = list(enumerate(units))
        with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
            built = list(pool.map(lambda item: compile_object(item, config, prefix, work), indexed))
        built.sort()
        script = work / "layout.ld"
        lines = ["SECTIONS", "{"]
        for index, unit, section, unused in built:
            address = parse_int(unit["address"])
            lines.append("  %s 0x%08X : { KEEP(*(%s)) }" % (section, address, section))
        lines.extend(("  /DISCARD/ : { *(*) }", "}"))
        script.write_text("\n".join(lines) + "\n")
        elf = work / "matching.elf"
        payload = work / "matching.bin"
        link = [
            linker, "-EL", "-m", "elf32ltsmip", "-T", str(script),
            "--entry=0x800860B0", "-o", str(elf),
        ]
        link.extend(str(item[3]) for item in built)
        run(link)
        run([objcopy, "-O", "binary", str(elf), str(payload)])
        rebuilt_payload = payload.read_bytes()

    retail_payload = retail[HEADER_SIZE:]
    if rebuilt_payload != retail_payload:
        if len(rebuilt_payload) != len(retail_payload):
            raise SystemExit(
                "linked payload size is 0x%X, expected 0x%X"
                % (len(rebuilt_payload), len(retail_payload))
            )
        first = next(i for i, pair in enumerate(zip(rebuilt_payload, retail_payload)) if pair[0] != pair[1])
        start = max(0, first - 8)
        end = min(len(retail_payload), first + 24)
        raise SystemExit(
            "linked payload differs at +0x%X\nexpected: %s\nactual:   %s"
            % (first, retail_payload[start:end].hex(), rebuilt_payload[start:end].hex())
        )

    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    rebuilt = header + rebuilt_payload
    output.write_bytes(rebuilt)
    if rebuilt != retail:
        raise SystemExit("rebuilt executable differs from retail")
    sha1 = hashlib.sha1(rebuilt).hexdigest()
    sha256 = hashlib.sha256(rebuilt).hexdigest()
    if sha1 != metadata["sha1"] or sha256 != metadata["sha256"]:
        raise SystemExit("rebuilt executable hash disagrees with metadata")
    report = {
        "schema": 1,
        "units": len(units),
        "payload_bytes": len(rebuilt_payload),
        "payload_sha256": hashlib.sha256(rebuilt_payload).hexdigest(),
        "executable_sha1": sha1,
        "executable_sha256": sha256,
        "matched": True,
    }
    report_output = Path(report_path)
    report_output.parent.mkdir(parents=True, exist_ok=True)
    report_output.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n")
    print("linked %d units into %d exact payload bytes" % (len(units), len(rebuilt_payload)))
    print("verified %s" % output)
    return report


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--config", default="config/us/matching_units.json")
    parser.add_argument("--metadata", default="config/us/executable.json")
    parser.add_argument("--executable", default="baseroms/us/SLUS_010.44")
    parser.add_argument("--output", default="build/us/SLUS_010.44.linked")
    parser.add_argument("--report", default="build/us/linked_report.json")
    parser.add_argument("--binutils-prefix", default=os.environ.get("MIPSEL_PREFIX", "mipsel-linux-gnu-"))
    parser.add_argument("--jobs", type=int, default=max(1, min(8, os.cpu_count() or 1)))
    args = parser.parse_args(argv)
    build(
        args.config, args.metadata, args.executable, args.output,
        args.report, args.binutils_prefix, args.jobs,
    )


if __name__ == "__main__":
    main()
