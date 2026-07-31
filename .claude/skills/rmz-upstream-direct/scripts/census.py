#!/usr/bin/env python3
"""List remaining asm functions smallest-first.

Run from the repo root. Emits TSV: size_bytes<TAB>name<TAB>inc_path.
A function counts as remaining when its thumb_func_start label is still
present under asm/ AND no NON_MATCH/NAKED/INCCODE claim for it exists in
src/ (those are dual-forms: decompiled but intentionally kept as asm).
Sizes are address deltas between consecutive labels across the whole ROM,
so they include the function's literal pools.
"""
import re
import subprocess
import sys


def run(args):
    return subprocess.run(args, capture_output=True).stdout.decode(
        "utf-8", errors="replace"
    )


def main():
    grep = run(["git", "grep", "-n", "thumb_func_start", "--", "asm/"])
    labels = []  # (file, lineno, name)
    for line in grep.splitlines():
        m = re.match(r"([^:]+):(\d+):\s*thumb_func_start\s+(\S+)", line)
        if m:
            labels.append((m.group(1), int(m.group(2)), m.group(3)))
    if not labels:
        print("no thumb_func_start labels found; run from the repo root",
              file=sys.stderr)
        return 1

    # Resolve each label's ROM address from the `name: @ 0x08......` line.
    addr = {}
    by_file = {}
    for f, ln, name in labels:
        by_file.setdefault(f, []).append((ln, name))
    for f, entries in by_file.items():
        text = open(f, encoding="utf-8", errors="replace").read().splitlines()
        for ln, name in entries:
            for probe in range(ln, min(ln + 3, len(text) + 1)):
                m = re.search(r"@\s*(0x[0-9A-Fa-f]{8})", text[probe - 1])
                if m:
                    addr[name] = int(m.group(1), 16)
                    break

    claimed = run(
        ["git", "grep", "-h", "-e", "NON_MATCH", "-e", "NAKED",
         "-e", "INCCODE", "--", "src/"]
    )

    ordered = sorted((a, n) for n, a in addr.items())
    sizes = {}
    for i, (a, n) in enumerate(ordered):
        nxt = ordered[i + 1][0] if i + 1 < len(ordered) else a
        sizes[n] = max(0, nxt - a)

    incof = {name: f for f, _, name in labels}
    rows = sorted(
        (sizes[n], n, incof[n])
        for n in addr
        if n not in claimed and sizes[n] > 0
    )
    for size, name, inc in rows:
        print(f"{size}\t{name}\t{inc}")
    print(f"# {len(rows)} functions remaining", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
