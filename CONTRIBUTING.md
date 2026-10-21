# Contributing

Contributions should improve the matching decompilation, build tooling,
documentation, or asset-format research without distributing copyrighted game
data.

## Before starting

- Work from the US release identified in the README (`SLUS-01044`).
- Keep the retail executable, disc image, extracted files, generated assembly,
  object files, and decoded media outside version control.
- Check the matching-unit manifest before changing a function boundary or
  compiler profile. Boundary changes need control-flow evidence.
- Prefer meaningful C and readable mnemonic assembly. Encoded instruction words
  do not receive semantic-source credit.

## Verifying a change

Run the narrowest relevant check while iterating, then run the repository checks
before submitting:

```sh
make check
make verify-matching
make verify-linked
```

`make verify-matching` requires the supported executable at
`baseroms/us/SLUS_010.44`. A matching-source change must reproduce its assigned
bytes exactly. Changes affecting the linker, manifest, unit boundaries, or build
pipeline should also demonstrate that the linked executable remains identical to
the retail executable.

If the optional extracted-disc corpus is available, run:

```sh
BTGA_PS1_EXTRACTED=/path/to/extracted \
  python3 -m unittest tests.test_real_corpus -v
```

## Submitting work

Keep each pull request focused and describe:

- the functions, data, tooling, or documentation changed;
- the compiler and per-unit flags used for matching-source work;
- the verification commands run and their results;
- any function-boundary, inline-assembly, or hard-register decisions that need
  special review.

Do not include local absolute paths, temporary workspace names, generated build
products, or unrelated changes. Run `git diff --check` before submitting.
