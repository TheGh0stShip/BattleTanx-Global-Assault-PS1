#!/usr/bin/env python3
"""Match an external Psy-Q signature catalogue against the local executable."""

import argparse
import hashlib
import json
import re
import struct
from pathlib import Path


HEADER_SIZE = 0x800
PLACEHOLDER = re.compile(
    r"^(?:text|data|rdata|bss|sbss|sdata|loc|locret|sub|unk|byte|word|dword"
    r"|qword|off|asc|stru|flt|dbl|jpt|def)_[0-9A-Fa-f]+$"
)


def parse_signature(signature):
    pattern = bytearray()
    mask = bytearray()
    for token in signature.split():
        if token == "??":
            pattern.append(0)
            mask.append(0)
        elif re.fullmatch(r"[0-9A-Fa-f]{2}", token):
            pattern.append(int(token, 16))
            mask.append(0xFF)
        else:
            raise ValueError("invalid signature token %r" % token)
    if not pattern:
        raise ValueError("empty signature")
    return bytes(pattern), bytes(mask)


def longest_anchor(mask):
    best = (0, 0)
    start = 0
    while start < len(mask):
        if not mask[start]:
            start += 1
            continue
        end = start
        while end < len(mask) and mask[end]:
            end += 1
        if end - start > best[1] - best[0]:
            best = (start, end)
        start = end
    return best


def find_masked(payload, pattern, mask):
    anchor_start, anchor_end = longest_anchor(mask)
    if anchor_end - anchor_start < 4:
        return None
    anchor = pattern[anchor_start:anchor_end]
    matches = []
    cursor = 0
    while True:
        found = payload.find(anchor, cursor)
        if found < 0:
            return matches
        cursor = found + 1
        offset = found - anchor_start
        if offset < 0 or offset & 3 or offset + len(pattern) > len(payload):
            continue
        window = payload[offset:offset + len(pattern)]
        if all(not mask[i] or window[i] == pattern[i] for i in range(len(pattern))):
            matches.append(offset)


def catalogue_digest(directory):
    digest = hashlib.sha256(b"btga-psyq-catalogue-v1\0")
    paths = sorted(Path(directory).glob("*.json"))
    for path in paths:
        data = path.read_bytes()
        digest.update(path.name.encode("utf-8") + b"\0")
        digest.update(len(data).to_bytes(8, "big"))
        digest.update(data)
    return digest.hexdigest()


def load_executable(path):
    image = Path(path).read_bytes()
    if image[:8] != b"PS-X EXE":
        raise ValueError("input is not a PS-X EXE")
    load_address, size = struct.unpack_from("<II", image, 0x18)
    payload = image[HEADER_SIZE:HEADER_SIZE + size]
    if len(payload) != size:
        raise ValueError("truncated executable payload")
    return load_address, payload


def load_candidates(path):
    report = json.loads(Path(path).read_text())
    return set(report["addresses"])


def scan(executable, candidates, signatures, version):
    load_address, payload = load_executable(executable)
    starts = load_candidates(candidates)
    paths = sorted(Path(signatures).glob("*.json"))
    if not paths:
        raise ValueError("signature directory has no JSON catalogues")
    counts = {"unique": 0, "multiple": 0, "absent": 0, "unanchored": 0}
    proposals = {}
    objects = []
    for path in paths:
        library = path.name.removesuffix(".json")
        entries = json.loads(path.read_text())
        for entry in entries:
            if "sig" not in entry:
                continue
            pattern, mask = parse_signature(entry["sig"])
            matches = find_masked(payload, pattern, mask)
            if matches is None:
                counts["unanchored"] += 1
                continue
            if not matches:
                counts["absent"] += 1
                continue
            if len(matches) != 1:
                counts["multiple"] += 1
                continue
            counts["unique"] += 1
            object_address = load_address + matches[0]
            provider = "%s/%s" % (library, entry["name"])
            objects.append({
                "provider": provider,
                "start": object_address,
                "end": object_address + len(pattern),
            })
            for label in entry.get("labels", []):
                name = label["name"]
                address = object_address + label["offset"]
                if PLACEHOLDER.match(name) or address not in starts:
                    continue
                names = proposals.setdefault(address, {})
                names.setdefault(name, []).append(
                    "%s+0x%X" % (provider, label["offset"])
                )
    rows = []
    for address, names in sorted(proposals.items()):
        rows.append({
            "address": address,
            "names": sorted(names),
            "providers": {
                name: sorted(providers) for name, providers in sorted(names.items())
            },
            "unambiguous": len(names) == 1,
        })
    return {
        "schema": 1,
        "psyq_version": version,
        "catalogue_sha256": catalogue_digest(signatures),
        "object_counts": counts,
        "candidate_start_proposals": len(rows),
        "unambiguous_start_proposals": sum(row["unambiguous"] for row in rows),
        "proposals": rows,
        "objects": sorted(objects, key=lambda item: (item["start"], item["provider"])),
        "warning": "Exact object matches are provenance evidence, not compiler identification.",
    }


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--executable", required=True)
    parser.add_argument("--candidates", required=True)
    parser.add_argument("--signatures", required=True)
    parser.add_argument("--version", required=True)
    parser.add_argument("--output", required=True)
    args = parser.parse_args(argv)
    report = scan(
        args.executable, args.candidates, args.signatures, args.version
    )
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n")
    print(
        "matched %d unique objects; %d starts proposed (%d unambiguous)"
        % (
            report["object_counts"]["unique"],
            report["candidate_start_proposals"],
            report["unambiguous_start_proposals"],
        )
    )


if __name__ == "__main__":
    main()
