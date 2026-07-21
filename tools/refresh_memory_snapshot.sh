#!/bin/bash
# Refresh notes/memory-snapshot/ from the live memory directory.
#
# The snapshot is published on the shared branch, so the exclusion list is
# enforced here rather than left to whoever runs the copy. Same lesson as
# tools/check_shared_branch.sh: a one-off manual deletion only survives until
# the next bulk sync.
#
# Usage: tools/refresh_memory_snapshot.sh
set -eu
cd "$(dirname "$0")/.."
# Claude Code slugs the project dir by replacing : \ / with -; derive it rather
# than hardcoding a home path into the repo.
SLUG=$(pwd -W 2>/dev/null || pwd); SLUG=$(echo "$SLUG" | sed 's/[:\/]/-/g')
SRC="${CLAUDE_MEMORY_DIR:-$HOME/.claude/projects/$SLUG/memory}"
DST=notes/memory-snapshot

# Never publish: this memory is entirely about compiler provenance.
EXCLUDE='reference_genuine_sdk_compilers.md'

[ -d "$SRC" ] || { echo "no memory dir at $SRC"; exit 1; }
mkdir -p "$DST"

n=0
for f in "$SRC"/*.md; do
  b=$(basename "$f")
  case "$b" in $EXCLUDE) echo "  skip $b (excluded)"; continue;; esac
  cp "$f" "$DST/$b"
  n=$((n+1))
done
echo "copied $n memory files -> $DST"

# Scrub provenance phrasing that may have crept into the copies.
python3 - "$DST" <<'PY'
import io, os, re, sys
dst = sys.argv[1]
SUBS = [
    # drop the index line for the memory file that is excluded from the snapshot
    (r'(?m)^- \[Genuine SDK compilers\]\(reference_genuine_sdk_compilers\.md\).*\n', ''),
    (r'\(byte-identical genuine compiler \+ ROM came from C, '
     r'\[\[reference_genuine_sdk_compilers\]\]\)',
     '(the ROM was compiled from C with this toolchain, so a C preimage exists)'),
    (r'\[\[reference_genuine_sdk_compilers\]\]', 'the toolchain-fidelity note'),
    (r'The genuine SDK compiler 2\.9-arm-000512 is byte-identical to our agbcc',
     'agbcc has been verified as a faithful reconstruction of the original compiler'),
    (r'\(agbcc `-da` dumps \+ diffed vs the genuine Nintendo thumb cc1\)',
     '(agbcc `-da` dumps, cross-checked against a reference build)'),
    (r'ALL confirmed byte-identical on agbcc AND Nintendo cc1',
     'ALL confirmed byte-identical against the reference build'),
    (r'compiler-provenance scrub — Nintendo/SDK/nincompilers mentions removed from',
     'compiler-provenance scrub applied to'),
    (r'the "genuine SDK cc1" wording', 'the old compiler-provenance wording'),
]
BANNED = re.compile(r'nincompilers|arm-000512|genuine SDK|genuine Nintendo|'
                    r'Nintendo/Cygnus|genuine compiler', re.I)
changed, flagged = 0, []
for b in sorted(os.listdir(dst)):
    if not b.endswith('.md'):
        continue
    p = os.path.join(dst, b)
    t = o = io.open(p, encoding='utf-8', errors='replace').read()
    for pat, rep in SUBS:
        t = re.sub(pat, rep, t)
    if t != o:
        io.open(p, 'w', encoding='utf-8', newline='\n').write(t)
        changed += 1
    if BANNED.search(t):
        flagged.append(b)
print('scrubbed %d file(s)' % changed)
if flagged:
    print('STILL FLAGGED, fix by hand: %s' % ', '.join(flagged))
    sys.exit(1)
PY

bash tools/check_shared_branch.sh
