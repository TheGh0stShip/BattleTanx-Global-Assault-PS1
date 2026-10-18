# BattleTanx: Global Assault (PlayStation)

Reverse-engineering and decompilation project for the US PlayStation release
(`SLUS-01044`). The current milestone provides bounds-checked decoders for the
game's proprietary asset formats and a deterministic corpus inventory tool.

No game image, executable, extracted asset, disassembly, or generated preview is
distributed by this repository. Supply files from a legally obtained copy.

## Status

- TEX, IMG, PLT and FUL image containers
- MMM/CM01/3MDL models and TTT texture tables
- FLB terrain grids and partially understood level BIN files
- font BIN files and VAGS.SFX metadata
- STR/PCK Mode-2 sector inventories
- deterministic PNG previews, OBJ exports and JSON manifests
- 30 synthetic-fixture tests plus an optional full-corpus test

This is not yet a matching C reconstruction of the main executable. Compiler
identification and executable segmentation are the next decompilation milestone.

## Requirements

- Python 3.9 or newer
- No runtime dependencies outside the Python standard library

## Tests

```sh
python3 -m unittest discover -s tests -t .
python3 mutation_check.py
```

To include the optional corpus test, point the environment variable at the root
of the extracted disc filesystem:

```sh
BTGA_PS1_EXTRACTED=/path/to/extracted \
  python3 -m unittest tests.test_real_corpus -v
```

## Inventory

```sh
python3 -m btga_ps1.inventory /path/to/extracted out --previews --obj
```

The tool refuses to place output inside the input tree. Generated manifests,
previews and models are deterministic.

Technical format notes and executable evidence are recorded in
[`docs/formats.md`](docs/formats.md). Platform assumptions are recorded in
[`docs/platform.md`](docs/platform.md).

## Project policy

Keep original media and derived copyrighted data out of version control. Commit
only reconstruction source, tools, tests, documentation, and small synthetic
fixtures. Host-side success does not establish behavior on original hardware.
