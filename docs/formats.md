# Asset format evidence

All multibyte fields described here are little-endian. Findings were checked
against all 737 files in the US disc corpus, and every file is structurally
decoded with exact bounds checks.

## Disc metadata

The two TXT files are strict ASCII, preserving their original line endings and
whether the final line is terminated. SYSTEM.CNF is parsed as unique `KEY=VALUE`
records; its `BOOT` value is separated into the disc path and ISO version.

The PS-X executable is split into its 0x800-byte header and the text extent named
by the header. Entry point, load address, initial register values, data/BSS/stack
ranges, and the ASCII header marker are exposed by the inventory. The decoder
requires the complete file to equal the header plus the declared text size.

`license_data.dat` contains twelve 2,336-byte Mode 2 sectors. Each is split into
the duplicated eight-byte subheader and a 2,328-byte payload; differing subheader
copies or trailing bytes are rejected. Per-sector hashes identify the local
payloads without placing them in the repository.

## Executable references

| Address | Role |
|---|---|
| `0x8003BF88` | MMM loader and table rebasing |
| `0x8003CB80` | TEX entry reader |
| `0x8003CCE8` | TEX loader |
| `0x8003D5B8` | level asset loader |
| `0x8003C8C8` | FLB loader |
| `0x8003AF64` | FLB ground renderer |
| `0x8003DE58` | level BIN loader |
| `0x8002429C` | level BIN parser |
| `0x800245B4` | placement spawn loop |
| `0x80069D68` | model job queue |
| `0x8007D708` | 3MDL interpreter |
| `0x8007DC30` | 64-entry command table |
| `0x8007DD78` | 16-entry primitive table |
| `0x8007E570` | vertex transform loop |
| `0x80054B10` | VAGS.SFX upload |

## Images and palettes

TEX starts with `3TEX` or `3PAL` and a `u32` count. Each record contains width,
height and mode as `u32`, followed by pixels and a CLUT. Mode 0 is 4bpp, mode 1
is 8bpp, and mode 2 is direct 16bpp. In 4bpp data, the low nibble is the left
texel. Colours are BGR555. The engine floors its pixel cursor to a multiple of
four before reading the CLUT; the decoder reports the two known files where
that differs from the authored layout.

IMG uses `3IMG` and contains the same image records without CLUTs. PLT uses
`3PLT`; each record has a reserved word, a CLUT count, and that many 16-colour
BGR555 palettes. IMG record *i* pairs with PLT record *i*.

FUL stores sequential one-based frame numbers followed by raw BGR555 frames.
Observed geometry is 320x256, except TK_BMP at 160x120. These dimensions remain
inference-backed because the renderer has not yet been located.

## Models

MMM uses `MM01`, a count, and 12-byte table records. Each record begins with a
signed blob offset or `-1`; its other two words are zero on disc. The loader
rebases the record to the CM01 header and its following 3MDL chunk.

CM01 is 0x24 bytes. It stores divided bounding minima and maxima, opaque words,
and a signed cull radius at offset 0x22. The 3MDL header contains its magic,
an unresolved word, vertex count, primitive count, flags, and chunk size.
Vertices are four signed 16-bit words: x, y, z, and a preserved pad value.

The command stream dispatches on `word & 0xFC`; `word >> 8` is the payload. Its
commands set corner colours, normals, UVs, vertex indices, texture slots,
primitive type, semitransparency, and guarded regions. Tag `0x68` ends the
stream. Quad emission maps stored corners to GPU slots as c0, c1, c3, c2.

TTT uses `TT01`, followed by one `LBTX` texture-index list per model. Every index
selects a record in the same-named IMG/PLT set. Texture-slot bounds are relevant
only to textured primitives.

Corpus totals are 4,761 models, 163,804 vertices, and 115,599 primitives. Every
command stream ends at its declared chunk boundary. Primitive counts match all
but ENUMS model 64, whose guarded blocks yield 147 primitives against 149 in the
header.

## Terrain and levels

FLB is `u16 width`, `u16 height`, then `width * height` `u32` cells. Cell bits
0-14 are BGR555 colour, bit 15 controls corner/UV order, bits 16-17 select UV
rotation, bits 18-23 select a terrain tile, and bits 24-31 remain opaque. A cell
spans 512 model units. The grid is centered at the origin.

Level BIN begins with five section offsets and three zero words. Section 0 is a
`u32` group count. Section 1 contains that many 16-byte records:
`{u16 placement_count, u16 first_placement, s16 x0,y0,z0,x1,y1,z1}`. These are
the same group bounds and placement ranges used by the N64 engine. Placement
records in section 2 are 12 bytes: signed x/y/z, unsigned yaw, and an offset
into section 3. Section 3 is a packed object-constructor stream. Its first byte
is an opcode dispatched through the 44-slot table at `0x800CD6A4`; 28 opcodes
occur on disc, and their fixed record sizes tile all 75 files exactly. Every
placement offset is checked against a decoded record boundary. Section 4 begins
with absolute file offsets to NUL-terminated ASCII model names; all 4,656 table
entries are decoded. The still-unidentified fields within object records are
preserved.

Font BIN files contain 82 records of three `u16` values: x, y, and width.
All-zero records indicate absent glyphs.

## Audio and media

VAGS.SFX uses `1SFX`, with data offset, data byte count, table byte count, and
entry count. Each 20-byte table entry is `{u32 SPU offset, u32 sample bytes,
u32 flags, u32 volume, u16 pitch, s16 sentinel}`. All samples are contiguous;
the final sample ends at the declared data size. The corpus uses flag 1, maximum
SPU volume `0x3FFF`, sentinel `-1`, and three base pitches. STR and PCK files
contain raw 2,336-byte Mode-2 sectors and are inventoried by sector kind and
channel.

## Coordinate rules

Model +Y is up. OBJ export writes `(x, y, -z)` and reverses emit-mode-1 faces.
Terrain cells and level placements use the same world-unit scale. UV values are
texel coordinates and normalize as `(u + 0.5) / width` and
`1 - (v + 0.5) / height`.

## Next executable work

1. Name the remaining fields in the section-3 object records handled by `0x80025094`.
2. Trace writes to model scratch state used by guarded blocks.
3. Recover construction of the terrain tile table at `0x800DDFF8`.
4. Trace SPU voice setup to identify the remaining SFX entry words.
5. Identify the original compiler before creating the matching C build.
