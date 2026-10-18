#!/usr/bin/env python3
"""Reject original or generated game material from tracked repository files."""

import subprocess
from pathlib import Path


FORBIDDEN_SUFFIXES = {
    ".bin", ".cue", ".dis", ".exe", ".iso", ".obj", ".png", ".wav", ".xa"
}
FORBIDDEN_MAGIC = (b"PS-X EXE",)


def tracked_files():
    output = subprocess.check_output(["git", "ls-files", "-z"])
    return [Path(item.decode("utf-8")) for item in output.split(b"\0") if item]


def main():
    errors = []
    files = tracked_files()
    for path in files:
        if path.suffix.lower() in FORBIDDEN_SUFFIXES:
            errors.append("forbidden tracked file type: %s" % path)
            continue
        data = path.read_bytes()
        if any(data.startswith(magic) for magic in FORBIDDEN_MAGIC):
            errors.append("original executable data: %s" % path)
    if errors:
        raise SystemExit("\n".join(errors))
    print("repository safety check passed (%d tracked files)" % len(files))


if __name__ == "__main__":
    main()
