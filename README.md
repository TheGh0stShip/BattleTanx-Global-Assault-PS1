# BattleTanx: Global Assault (PlayStation)

Reverse-engineering and decompilation project for the US PlayStation release
(`SLUS-01044`). The current milestone provides bounds-checked decoders for the
game's proprietary asset formats and a deterministic corpus inventory tool.

No game image, executable, extracted asset, disassembly, or generated preview is
distributed by this repository. Supply files from a legally obtained copy.

## Progress

![Executable matching: 2.13%](https://img.shields.io/badge/executable_matching-2.13%25-red)
![Asset files structurally decoded: 99.46%](https://img.shields.io/badge/asset_files_decoded-99.46%25-brightgreen)
![Decoder tests passing: 100%](https://img.shields.io/badge/decoder_tests-100%25-brightgreen)

The executable percentage is the authoritative decompilation measurement. It is
`matched text bytes / 747,520 text bytes` from `SLUS_010.44`; asset research is
reported separately and never inflates it. A byte counts only after reconstructed
source compiles to identical machine code.

| Executable work | Complete | Remaining | Progress |
|---|---:|---:|---:|
| Matching C text | 15,956 bytes | 731,564 bytes | 2.13% |
| Original compiler identified | 0 | 1 | 0.00% |
| Reproducible target build | 0 | 1 | 0.00% |
| Executable segment map | 1 | 0 | 100% |
| Provisional function starts | 1,779 candidates | review required | no match credit |
| Exact SDK signature proposals | 142 candidate starts | conflict review required | no game-code credit |
| Reviewed function boundaries | 350 | candidate audit required | in progress |
| Functions matched | 350 | 1,430 provisional candidates | 349 provisional starts matched (19.62%); 1 additional entry |

| Asset work | Complete | Remaining | Coverage |
|---|---:|---:|---:|
| Disc files structurally decoded | 733 files | 4 opaque files | 99.46% |
| TEX | 256 files | 0 files | 100% |
| IMG | 71 files | 0 files | 100% |
| PLT | 71 files | 0 files | 100% |
| FUL | 7 files | 0 files | 100% structural; dimensions need code confirmation |
| MMM/3MDL | 76 files / 4,761 models | 0 files | 100% structural |
| TTT | 76 files / 8,781 references | 0 files | 100% structural |
| FLB | 75 files | 0 files | 100% structural; high byte and tile 63 unresolved |
| Level BIN | 75 files / 30,758 placements | sections 0, 3 and 4 | partial |
| Font BIN | 4 files / 328 records | glyph height semantics | partial |
| VAGS.SFX | 1 file / 57 entries | 4 words per entry | partial |
| STR/PCK | 20 files | media decoding | sector inventory only |
| Validation tests | 43 tests | 0 tests | 100% passing with the local corpus |
| Deliberate fault checks | 12 checks | 0 checks | 100% detected |

The four opaque corpus files are the game executable, boot configuration, text,
and license data. “Structural” means the format tiles the file exactly with
bounds-checked parsing; it does not mean every field's gameplay meaning is known.

This is an early matching C reconstruction of the main executable. Three hundred fifty
functions currently compile to 15,956 identical retail bytes. Compiler
corroboration and executable segmentation are the next decompilation milestones;
the ignored matching report is generated directly by the exact-byte verifier.

## Requirements

- Python 3.9 or newer
- No runtime dependencies outside the Python standard library

Executable splitting uses the pinned development dependencies in
`requirements.txt`.

## Executable setup

The supported US executable has SHA-1
`5c3280f903d442922a7764a4d9f9f6f9fd0c0c34` and SHA-256
`7bc99c17872dc244886ab85033be1596c206b298da450bea8c774851b4ab8f2f`.
Place it locally at `baseroms/us/SLUS_010.44`; that directory is ignored.

```sh
make setup
make verify
make split
make function-inventory
make check
```

The initial split accounts for the entire file and writes generated assembly
under ignored paths. It awards no matching progress. See
[`docs/DECOMPILATION.md`](docs/DECOMPILATION.md) for the evidence gates and
current memory map. SDK and compiler evidence is tracked separately in
[`docs/SDK.md`](docs/SDK.md).

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
