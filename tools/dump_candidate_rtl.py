#!/usr/bin/env python3
"""Generate GCC allocation/loop RTL dumps for one large candidate.

The source is copied under build/ before invoking cc1 because GCC 2.8.1 writes
dump files beside its input.  A second compile proves that the dump switches do
not change the emitted assembly before the dumps are accepted.
"""

import argparse
import json
from pathlib import Path
import shutil
import subprocess

try:
    from .verify_large_candidates import CANDIDATES, CONFIG_PATH
    from .verify_matching_units import compiler_path
except ImportError:
    from verify_large_candidates import CANDIDATES, CONFIG_PATH
    from verify_matching_units import compiler_path


ROOT = Path(__file__).resolve().parents[1]
DUMP_FLAGS = ("-dg", "-dl", "-dL")
DUMP_SUFFIXES = ("greg", "lreg", "loop")


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("name", choices=sorted(CANDIDATES))
    args = parser.parse_args(argv)

    config = json.loads(CONFIG_PATH.read_text())
    unit = next(item for item in config["units"] if item["name"] == args.name)
    flags = config["compiler_flags"] + unit.get("compiler_flags_extra", [])
    cc1 = compiler_path(unit, config)
    output = ROOT / "build/large_candidates" / args.name / "rtl"
    shutil.rmtree(output, ignore_errors=True)
    output.mkdir(parents=True)
    source = output / "candidate.c"
    shutil.copyfile(ROOT / CANDIDATES[args.name], source)
    plain = output / "plain.s"
    dumped = output / "dumped.s"
    subprocess.run([str(cc1), str(source), *flags, "-o", str(plain)], check=True)
    subprocess.run(
        [str(cc1), str(source), *flags, *DUMP_FLAGS, "-o", str(dumped)],
        check=True,
    )
    if plain.read_bytes() != dumped.read_bytes():
        raise SystemExit("RTL dump switches changed emitted assembly")
    paths = []
    for suffix in DUMP_SUFFIXES:
        path = source.with_suffix(source.suffix + "." + suffix)
        if not path.is_file():
            raise SystemExit("missing expected RTL dump: %s" % path)
        paths.append(path)
    print("verified dump switches preserve assembly")
    for path in paths:
        print("%s %d bytes" % (path.relative_to(ROOT), path.stat().st_size))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
