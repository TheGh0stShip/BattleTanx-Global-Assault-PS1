# Matching decompilation plan

The supported executable is `SLUS_010.44` from the US release. It is a
749,568-byte PS-X EXE consisting of a 2,048-byte header and 747,520 loaded text
bytes. The loaded range is `0x80010000..0x800C6800`; execution begins at
`0x800860B0`.

## Evidence gates

1. Verify the complete executable hash and every relevant header field before
   reading or splitting it.
2. Account for every byte in the loaded range without treating unknown bytes as
   matched C or understood data.
3. Identify the original compiler from code-generation evidence and library
   fingerprints before selecting matching flags or claiming a toolchain.
4. Give each function a reviewed, non-overlapping address range. Similar N64
   functions are useful evidence for boundaries and behavior, but do not prove
   identical ownership, names, or implementation on PlayStation.
5. Compile reconstructed units and compare their emitted bytes and relocations
   directly with the supported executable.
6. Track code, initialized data, SDK/library code, padding, and asset files as
   separate categories. A category advances only under its own exact verifier.
7. Rebuild the complete executable and require both supported hashes to match
   before declaring the executable complete.

## Initial map

| File range | Loaded range | Size | Classification |
|---|---|---:|---|
| `0x000000..0x000800` | not loaded | 2,048 | PS-X EXE header |
| `0x000800..0x0B7000` | `0x80010000..0x800C6800` | 747,520 | mixed code/data, pending segmentation |

The first split deliberately emits the entire loaded range for inspection. It
does not count unknown bytes as decompiled. The next milestones are broader
compiler corroboration, function-boundary recovery, and section ownership.

Six hundred thirty-one production source units compile with the PSX-patched GCC 2.8.1 at `-O2 -G0`
and match all 36,660 retail bytes after the pinned assembler compatibility pass.
The verifier links each unit at its retail address, resolves declared external
calls, extracts `.text`, permits only zero object-section tail padding, and
rejects the first differing byte.

The initial control-flow scan exposes 1,779 aligned call-target candidates.
`make function-inventory` records them in an ignored deterministic report. They
remain provisional until instruction flow, returns, jump tables, embedded data,
and callerless entry points are audited; the candidate count is not a completed
function count.

## Local resources

Original disc files, generated assembly, extracted textures, rendered models,
decoded audio, and rebuilt executables stay in ignored directories. The asset
inventory accepts an extracted disc tree and writes deterministic manifests and
previews to a separate local output directory. Repository checks reject common
original and generated binary types if they are accidentally staged.
