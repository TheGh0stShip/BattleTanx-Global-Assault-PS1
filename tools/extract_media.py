#!/usr/bin/env python3
"""Losslessly decode headerless PlayStation STR/PCK files with FFmpeg.

Decoded media is an explicitly local build artifact. The output directory must
not be inside the source corpus, and repository safety checks reject media files.
"""
import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from btga_ps1.media import wrap_mode2_sectors


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("extracted")
    ap.add_argument("output")
    args = ap.parse_args()
    source = os.path.abspath(args.extracted)
    output = os.path.abspath(args.output)
    if output == source or output.startswith(source + os.sep):
        raise SystemExit("refusing to write inside the extracted disc directory")
    ffmpeg = shutil.which("ffmpeg")
    if ffmpeg is None:
        raise SystemExit("FFmpeg with the psxstr demuxer is required")
    inputs = sorted(os.path.join(d, f) for d, _, fs in os.walk(source) for f in fs
                    if os.path.splitext(f)[1].upper() in (".STR", ".PCK"))
    os.makedirs(output, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="btga-psx-media-") as temp:
        for path in inputs:
            relative = os.path.relpath(path, source)
            stem, ext = os.path.splitext(relative)
            destination = os.path.join(output, stem + (".mkv" if ext.upper() == ".STR" else ".mka"))
            os.makedirs(os.path.dirname(destination), exist_ok=True)
            raw_path = os.path.join(temp, "wrapped.raw")
            with open(path, "rb") as fh:
                wrapped = wrap_mode2_sectors(fh.read(), relative)
            with open(raw_path, "wb") as fh:
                fh.write(wrapped)
            command = [ffmpeg, "-v", "error", "-y", "-f", "psxstr", "-i", raw_path,
                       "-map", "0", "-c:v", "ffv1", "-level", "3", "-c:a", "flac",
                       "-map_metadata", "-1", "-fflags", "+bitexact",
                       "-flags:v", "+bitexact", "-flags:a", "+bitexact", destination]
            subprocess.run(command, check=True)
            print("decoded %s -> %s" % (relative, destination))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
