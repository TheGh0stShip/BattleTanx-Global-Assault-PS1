#!/bin/sh
set -eu

root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
dest="$root/.toolchain"
downloads="$dest/downloads"
mkdir -p "$downloads"

gcc_release=https://github.com/decompals/old-gcc/releases/download/0.13

maspsx_commit=423ffc6bca05e53f9b7ab06159d0cbe71111bc90
maspsx_url="https://github.com/mkst/maspsx/archive/$maspsx_commit.zip"
maspsx_archive="$downloads/maspsx-$maspsx_commit.zip"
maspsx_sha=3894086ee2c662f2cbc565a1b1fdd0e2231a2a90db132fe788eba1a6cb7d62d2

# Most units use 2.8.1; units whose retail code shows the older text epilogue
# (lw ra; addiu sp; jr ra; nop) select 2.7.2 through their manifest entry.
for spec in \
    gcc-2.8.1-psx:51e94d84906d5ac1fa58cf66b7eed43e2c995526ef71df6ff5562df0177117e3 \
    gcc-2.7.2-psx:aca64479041aa2d645dc52ebcaace276c0aa06f258c0e3f190ccf6d76701ffbc
do
    name=${spec%%:*}
    sha=${spec#*:}
    archive="$downloads/$name.tar.gz"
    if [ ! -f "$archive" ]; then
        curl -L --fail --output "$archive" "$gcc_release/$name.tar.gz"
    fi
    printf '%s  %s\n' "$sha" "$archive" | sha256sum -c -
    mkdir -p "$dest/$name"
    tar -xzf "$archive" -C "$dest/$name"
done

if [ ! -f "$maspsx_archive" ]; then
    curl -L --fail --output "$maspsx_archive" "$maspsx_url"
fi
printf '%s  %s\n' "$maspsx_sha" "$maspsx_archive" | sha256sum -c -
unzip -q -o "$maspsx_archive" -d "$dest"

test -x "$dest/gcc-2.8.1-psx/cc1"
test -x "$dest/gcc-2.7.2-psx/cc1"
test -f "$dest/maspsx-$maspsx_commit/maspsx.py"
printf 'toolchain ready in %s\n' "$dest"
