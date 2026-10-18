#!/usr/bin/env python3
"""Verify the supported US executable and its PS-X EXE memory contract."""

import argparse
import hashlib
import struct
from pathlib import Path


EXPECTED_SIZE = 0xB7000
EXPECTED_SHA1 = "5c3280f903d442922a7764a4d9f9f6f9fd0c0c34"
EXPECTED_SHA256 = "7bc99c17872dc244886ab85033be1596c206b298da450bea8c774851b4ab8f2f"
EXPECTED_FIELDS = {
    0x10: ("entry point", 0x800860B0),
    0x14: ("initial gp", 0x00000000),
    0x18: ("load address", 0x80010000),
    0x1C: ("text size", 0x000B6800),
    0x30: ("initial sp", 0x801FFFF0),
}


def verify(path):
    data = Path(path).read_bytes()
    errors = []
    if len(data) != EXPECTED_SIZE:
        errors.append("size 0x%X != 0x%X" % (len(data), EXPECTED_SIZE))
    if data[:8] != b"PS-X EXE":
        errors.append("missing PS-X EXE magic")
    if hashlib.sha1(data).hexdigest() != EXPECTED_SHA1:
        errors.append("SHA-1 does not match the supported release")
    if hashlib.sha256(data).hexdigest() != EXPECTED_SHA256:
        errors.append("SHA-256 does not match the supported release")
    for offset, (name, expected) in EXPECTED_FIELDS.items():
        if len(data) < offset + 4:
            errors.append("%s is truncated" % name)
            continue
        actual = struct.unpack_from("<I", data, offset)[0]
        if actual != expected:
            errors.append("%s 0x%08X != 0x%08X" % (name, actual, expected))
    if errors:
        raise SystemExit("verification failed:\n  " + "\n  ".join(errors))
    print("verified %s" % path)
    print("header: 0x800 bytes")
    print("loaded text: 0xB6800 bytes at 0x80010000")


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("executable")
    args = parser.parse_args(argv)
    verify(args.executable)


if __name__ == "__main__":
    main()
