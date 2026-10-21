# SDK and compiler evidence

SDK library identity and game-code compiler identity are separate questions.
Exact library-object matches establish which precompiled Sony objects were
linked. They do not establish which compiler built game-owned source.

## Embedded anchors

The executable contains these revision strings and notices:

| Loaded address | Evidence |
|---|---|
| `0x800B5A20` | Sony library copyright, 1993–1997 |
| `0x800C4AF0` | `sys.c` revision 1.135, 1997-09-02 |
| `0x800C5188` | `intr.c` revision 1.76, 1997-02-12 |
| `0x800C5F40` | `bios.c` revision 1.86, 1997-03-28 |

These prove source-member provenance and dates, not a complete SDK release.

## Exact signature sweep

`tools/psyq_signatures.py` consumes a separately obtained checkout of the
`psx_psyq_signatures` catalogue. Nothing is downloaded or vendored by the
project. It matches each complete object pattern with relocation bytes masked,
requires a unique word-aligned placement, and proposes meaningful labels only
at provisional function starts.

The initial cross-version sweep produced:

| Catalogue | Unique objects | Candidate starts | Unambiguous starts |
|---:|---:|---:|---:|
| 4.0 | 66 | 65 | 64 |
| 4.1 | 122 | 142 | 139 |
| 4.2 | 121 | 141 | 138 |
| 4.3 | 119 | 140 | 137 |
| 4.4 | 119 | 140 | 137 |
| 4.5 | 115 | 122 | 119 |
| 4.6 | 117 | 121 | 117 |
| 4.7 | 117 | 121 | 117 |

Psy-Q 4.1 is therefore the leading catalogue for linked-library provenance.
The one-object margin over 4.2 must be examined alongside the embedded revision
strings and per-object conflicts before pinning a release. No proposed name is
authoritative until its full provider set and local call contract are reviewed.

Example local command:

```sh
make psyq-report \
  PSYQ_VERSION=410 \
  PSYQ_SIGNATURES=/path/to/psx_psyq_signatures/410
```

The ignored JSON output records the catalogue digest, every unique object
range, all providers for each proposed label, and all ambiguous names.

## Compiler status

GCC 2.8.1 with the PSX patches, `-O2 -G0`, is the leading game-code compiler.
It produces exact matches, together with the documented per-unit compiler
profiles, for all 1,898 source units totaling all 747,520 payload bytes;
GCC 2.7.2 assigns the non-leaf function's saved registers differently, while
GCC 2.95.2 inserts argument sign-extension instructions absent from retail. The
additional matches corroborate basic expression and store scheduling,
branches, global-address construction, structure strides, and a non-leaf call.
Those units also survive one final retail-address link and reproduce the full
PS-X EXE, including its metadata-built header, at both supported hashes.
The compiler and final-link gates cover the complete executable.

The native-Windows `CC1PSX.EXE` backend was also checked directly from WSL,
without Wine, against the 4,788-byte `func_8007AE20` matching source. Psy-Q
4.3 and 4.4 both emitted the same text as the pinned Linux GCC 2.8.1 PSX
compiler before the function-specific assembler profile. Psy-Q 4.5 emitted
4,924 bytes and is excluded for this unit. The locally tested compiler
fingerprints are:

| Psy-Q bundle | `CC1PSX.EXE` SHA-256 | Candidate result |
|---|---|---|
| 4.3 | `17081b8e39a92078b16aa788f419306c0d77b28c30a02b9bb9c208cac172e5be` | identical to pinned GCC 2.8.1 output |
| 4.4 | `26eb8259fa3e077d1980eb1e0c942006752135953dd03173200bf99ef6f5b6c9` | identical to pinned GCC 2.8.1 output |
| 4.5 | `a24ed21b8d371ca57048721109506cdfabb40539178e436e21400245d9c4dd76` | excluded; wrong text size and allocation |

These executables remain ignored local toolchain inputs. A matching-unit entry
selects the backend with `"compiler": "psyq-cc1psx"`; `PSYQ_CC1PSX` names the
mounted Windows executable path.

Final compiler selection requires matching code-generation evidence from
additional representative game functions,
including stack layout, delay-slot scheduling, switch lowering, signed and
unsigned division, structure copies, and small-data behavior. Library version
counts alone are not sufficient.
