#!/bin/sh
# Search the GBA decomp corpus for an instruction shape or source idiom.
#   corpus-grep.sh 'ands r0, r1'          # asm shape: who matched this?
#   corpus-grep.sh -c 'SET_XFLIP'         # C idiom: how do siblings write it?
# Env: CORPUS_DIR (default ~/decomp/corpus)
set -eu
DIR="${CORPUS_DIR:-$HOME/decomp/corpus}"
MODE=asm
if [ "${1:-}" = "-c" ]; then MODE=src; shift; fi
PAT="${1:?usage: corpus-grep.sh [-c] PATTERN}"
[ -d "$DIR" ] || { echo "corpus not found at $DIR — run setup.sh --corpus"; exit 1; }
for repo in "$DIR"/*/; do
  name="$(basename "$repo")"
  if [ "$MODE" = asm ]; then
    hits="$(grep -rn --include='*.s' --include='*.inc' -F "$PAT" "$repo" 2>/dev/null | head -5 || true)"
  else
    hits="$(grep -rn --include='*.c' --include='*.h' -F "$PAT" "$repo" 2>/dev/null | head -5 || true)"
  fi
  [ -n "$hits" ] && { echo "=== $name"; echo "$hits"; }
done
