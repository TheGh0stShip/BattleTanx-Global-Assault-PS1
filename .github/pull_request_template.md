## Summary

Describe the focused change and the affected functions, data, tooling, or
documentation.

## Verification

- [ ] Relevant unit or decoder tests pass
- [ ] `make check` passes
- [ ] Matching units reproduce their assigned retail bytes
- [ ] Link-sensitive changes preserve the exact executable build
- [ ] `git diff --check` passes
- [ ] No game image, executable, extracted asset, generated build product, or
      decoded media is included

## Review notes

List compiler flags, boundary evidence, inline assembly, hard-register choices,
or other details requiring special attention. Write “None” when there are none.
