#!/bin/sh
set -eu

root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
dest="$root/.toolchain"
downloads="$dest/downloads"
mkdir -p "$downloads" "$dest/gcc-2.8.1-psx"

gcc_url=https://github.com/decompals/old-gcc/releases/download/0.13/gcc-2.8.1-psx.tar.gz
gcc_archive="$downloads/gcc-2.8.1-psx.tar.gz"
gcc_sha=51e94d84906d5ac1fa58cf66b7eed43e2c995526ef71df6ff5562df0177117e3

maspsx_commit=423ffc6bca05e53f9b7ab06159d0cbe71111bc90
maspsx_url="https://github.com/mkst/maspsx/archive/$maspsx_commit.zip"
maspsx_archive="$downloads/maspsx-$maspsx_commit.zip"
maspsx_sha=3894086ee2c662f2cbc565a1b1fdd0e2231a2a90db132fe788eba1a6cb7d62d2

if [ ! -f "$gcc_archive" ]; then
    curl -L --fail --output "$gcc_archive" "$gcc_url"
fi
printf '%s  %s\n' "$gcc_sha" "$gcc_archive" | sha256sum -c -
tar -xzf "$gcc_archive" -C "$dest/gcc-2.8.1-psx"

if [ ! -f "$maspsx_archive" ]; then
    curl -L --fail --output "$maspsx_archive" "$maspsx_url"
fi
printf '%s  %s\n' "$maspsx_sha" "$maspsx_archive" | sha256sum -c -
unzip -q -o "$maspsx_archive" -d "$dest"

test -x "$dest/gcc-2.8.1-psx/cc1"
test -f "$dest/maspsx-$maspsx_commit/maspsx.py"
printf 'toolchain ready in %s\n' "$dest"
