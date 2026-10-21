# BattleTanx: Global Assault (PlayStation)

Reverse-engineering and decompilation project for the US PlayStation release
(`SLUS-01044`). The project reproduces the retail executable exactly while
replacing encoded instructions with matching C and readable assembly. It also
includes bounds-checked decoders for the game's proprietary asset formats and a
deterministic corpus inventory tool.

No game image, executable, extracted asset, disassembly, or generated preview is
distributed by this repository. Supply files from a legally obtained copy.

## Progress

[![Verify](https://github.com/TheGh0stShip/BattleTanx-Global-Assault-PS1/actions/workflows/verify.yml/badge.svg)](https://github.com/TheGh0stShip/BattleTanx-Global-Assault-PS1/actions/workflows/verify.yml)
![Exact executable reconstruction: 100%](https://img.shields.io/badge/exact_reconstruction-100%25-brightgreen)
![Semantic decompilation: 100%](https://img.shields.io/badge/semantic_source-100%25-brightgreen)
![Asset files structurally decoded: 100%](https://img.shields.io/badge/asset_files_decoded-100%25-brightgreen)
![Decoder tests passing: 100%](https://img.shields.io/badge/decoder_tests-100%25-brightgreen)
[![ByteMatch](https://bytematch.dev/TheGh0stShip/BattleTanx-Global-Assault-PS1.svg?label=ByteMatch&measure=matched_code_percent)](https://bytematch.dev/TheGh0stShip/BattleTanx-Global-Assault-PS1)
[![decmp.dev](https://api.decmp.dev/badge/TheGh0stShip/BattleTanx-Global-Assault-PS1.svg?measure=matched_code_percent&label=decmp.dev)](https://decmp.dev/TheGh0stShip/BattleTanx-Global-Assault-PS1)

The ByteMatch percentage is the authoritative semantic decompilation measurement:
matching code emitted from reconstructed C, plus readable mnemonic assembly for
originally hand-written routines, divided by all executable code bytes. Raw encoded
instruction blobs do not receive semantic credit. Exact reconstruction is tracked
separately; all reconstructed source units assemble or compile and link to the retail
bytes. Asset research is also reported separately and never inflates either
executable measurement.

| Executable work | Complete | Remaining | Progress |
|---|---:|---:|---:|
| Exact reconstructed payload | 747,520 bytes | 0 bytes | 100% |
| Semantic matching source | 589,836 code bytes | 0 code bytes | 100% |
| Semantic functions | 1,794 functions | 0 raw instruction units | 100% |
| Reproducible target build | 1 | 0 | 100% |
| Executable segment map | 1 | 0 | 100% |
| Provisional function starts | 1,779 represented | 0 unrepresented | 100% exact-start coverage; classification continues |
| Exact SDK signature proposals | 142 candidate starts | conflict review required | no game-code credit |
| Reviewed source-unit boundaries | 1,898 | semantic naming and consolidation | byte coverage complete |
| Source units matched | 1,898 | 0 provisional candidates | all provisional starts represented |
| Classified data units | 38 ranges / 140,796 bytes | semantic field recovery | exact bytes verified |
| Classified zero padding | 66 ranges / 16,888 bytes | 0 bytes | 100% |

| Asset work | Complete | Remaining | Coverage |
|---|---:|---:|---:|
| Disc files structurally decoded | 737 files | 0 files | 100% |
| TEX | 256 files | 0 files | 100% |
| IMG | 71 files | 0 files | 100% |
| PLT | 71 files | 0 files | 100% |
| FUL | 7 files / 79 frames | 0 frames | 320x256 and 160x120 BGR555 frames completely decoded |
| MMM/3MDL | 76 files / 4,761 models | 0 models | geometry, bounds, named visibility groups, vertex grouping, flags, and command stream decoded |
| TTT | 76 files / 8,781 references | 0 files | 100% structural |
| FLB | 75 files / 307,200 RGB blocks | 0 cells | terrain cells, RGB plane, and tile-63 sentinel decoded |
| Level BIN | 75 files / 30,758 placements | Complete | all 5,462 object records have typed fields |
| Font BIN | 4 files / 324 glyphs and 4 metrics records | 0 records | glyph rectangles, height, fixed advance, and space width decoded |
| VAGS.SFX | 1 file / 57 entries | 0 entries | addresses, sizes, pitch, voice-slot state, ADPCM, and WAV decoding complete |
| STR/PCK | 20 files | 0 files | lossless local FFV1/FLAC decoding complete |
| Disc metadata | 5 files | 0 files | text, boot config, executable container, and licence sectors decoded |
| Validation tests | 63 tests | 0 tests | 100% passing with the local corpus and a native C compiler |
| Deliberate fault checks | 12 checks | 0 checks | 100% detected |

Every corpus file now has a bounds-checked structural decoder. This includes the
game executable container, boot configuration, both text files, and raw licence
sectors. “Structural” means the format tiles the file exactly; it does not mean
every field's gameplay meaning or encoded media sample is known.

One thousand eight hundred ninety-eight source units compile and link into all
747,520 retail payload bytes. The reconstructed header and linked payload form
a complete executable matching both supported hashes. Semantic naming,
consolidation, and compiler corroboration remain active decompilation work;
ignored reports are generated directly by the exact-byte verifiers.
CI also publishes an objdiff-compatible `SLUS_01044_report` artifact. It awards
matched-code credit only to semantic source while retaining exact totals for every
code and data unit.

For the current unit-by-unit status, use the live
[ByteMatch report](https://bytematch.dev/TheGh0stShip/BattleTanx-Global-Assault-PS1).
The checked-in totals are pinned by tests and updated with matching-source
milestones.

## Requirements

- Python 3.9 or newer
- GNU Make
- A legally obtained copy of the supported US executable

The inventory library has no runtime dependencies outside the Python standard
library. Executable splitting and decompilation use the pinned development
dependencies in `requirements.txt`; `make setup` installs the project toolchain.

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
make verify-matching
make verify-linked
make check
```

The initial split accounts for the entire file and writes generated assembly
under ignored paths. `make verify-linked` reconstructs and verifies a complete
executable under `build/us/`; that output remains local. See
[`docs/DECOMPILATION.md`](docs/DECOMPILATION.md) for the evidence gates and
current memory map. SDK and compiler evidence is tracked separately in
[`docs/SDK.md`](docs/SDK.md).

### Original PsyQ compiler on WSL

PsyQ library units can select the original Windows compiler by setting
`"compiler": "psyq-cc1psx"` in their matching-unit manifest entry. Supply a
legally obtained `CC1PSX.EXE` outside version control and point the build at it:

```sh
PSYQ_CC1PSX='/mnt/c/psyq/bin/CC1PSX.EXE' make verify-matching
```

The verifier runs the executable through Windows interoperability, not Wine.
It stages each translation unit in a Windows-local temporary directory so the
original compiler never receives a WSL UNC path. Set `PSYQ_CC1PSX_TEMP` to a
mounted Windows directory if the default user temp directory cannot be found.

## Tests

```sh
python3 -m unittest discover -s tests -t .
python3 mutation_check.py
```

When a native `cc` is available, the suite also compiles an interface regression
check for the node-allocation wrapper. This host-only check complements the
separate MIPS byte comparisons.

To include the optional corpus test, point the environment variable at the root
of the extracted disc filesystem:

```sh
BTGA_PS1_EXTRACTED=/path/to/extracted \
  python3 -m unittest tests.test_real_corpus -v
```

## Inventory

```sh
python3 -m btga_ps1.inventory /path/to/extracted out --previews --obj --wav
```

The tool refuses to place output inside the input tree. Generated manifests,
previews, models, and decoded sound-effect WAV files are deterministic.

Headerless streamed media can be losslessly decoded to local FFV1/FLAC files
with an FFmpeg build that includes the `psxstr` demuxer:

```sh
python3 tools/extract_media.py /path/to/extracted /path/to/local_media_dump
```

The extractor restores the missing 16-byte raw-sector prefix before decoding.
Decoded media remains a local artifact and is rejected by repository checks.

Technical format notes and executable evidence are recorded in
[`docs/formats.md`](docs/formats.md). Platform assumptions are recorded in
[`docs/platform.md`](docs/platform.md).

## Repository layout

| Path | Contents |
|---|---|
| `config/us/` | US executable layout and matching-unit metadata |
| `src/game/` | Matching game and linked-library source units |
| `src/data/` | Classified data, jump tables, and padding |
| `btga_ps1/` | Bounds-checked host-side asset decoders |
| `tools/` | Reproducible build, verification, reporting, and extraction tools |
| `tests/` | Portable regression, profile, and format tests |
| `docs/` | Platform, format, SDK, and decompilation documentation |

Third-party source-derived work and its licence text are recorded in
[`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md).

## Project policy

Keep original media and derived copyrighted data out of version control. Commit
only reconstruction source, tools, tests, documentation, and small synthetic
fixtures. Host-side success does not establish behavior on original hardware.

Contributions are welcome. Read [`CONTRIBUTING.md`](CONTRIBUTING.md) before
submitting source, tooling, documentation, or format research.
