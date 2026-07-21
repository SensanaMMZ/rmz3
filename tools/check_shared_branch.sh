#!/bin/bash
# Guard for the shared ai-research branch. Run before every push.
#
# Why this exists: notes/clean-room-agbcc-improvement.md was deliberately
# removed from the shared branch in 1d6860af, and a later bulk "Sync:" commit
# (ce0816ea) silently put it back -- the syncs copy notes/ wholesale from main,
# where that file legitimately lives as local-only. A deletion with no guard
# only lasts until the next sync, so the exclusion is enforced here instead.
#
# Usage: tools/check_shared_branch.sh [ref]      (default: working tree)
set -u
cd "$(dirname "$0")/.."
REF="${1:-}"
fail=0

# Paths that must never appear on the shared branch.
BANNED_PATHS='notes/clean-room-agbcc-improvement\.md'

# Provenance strings. src/rom_header.s (RomHeaderNintendoLogo, a real GBA header
# field) and tools/agbcc-debug/*.instrumented ("CYGNUS LOCAL", GCC 2.x's own
# source comments) are legitimate and excluded.
BANNED_TEXT='nincompilers|arm-000512|genuine SDK|genuine Nintendo|Nintendo/Cygnus|genuine compiler'

if [ -n "$REF" ]; then
  list() { git ls-tree -r --name-only "$REF"; }
  content() { git grep -inE "$1" "$REF" -- "$2" 2>/dev/null; }
else
  list() { git ls-files; }
  content() { git grep -inE "$1" -- "$2" 2>/dev/null; }
fi

echo "checking ${REF:-working tree}"

if list | grep -qE "^($BANNED_PATHS)$"; then
  echo "FAIL: banned path present:"
  list | grep -E "^($BANNED_PATHS)$" | sed 's/^/  /'
  fail=1
fi

hits=$(content "$BANNED_TEXT" '.' \
  | grep -vE ':src/rom_header\.s:' \
  | grep -vE 'tools/agbcc-debug/.*\.instrumented:')
if [ -n "$hits" ]; then
  echo "FAIL: compiler-provenance text present:"
  echo "$hits" | cut -c1-140 | sed 's/^/  /'
  fail=1
fi

# Commit-message tells, on this branch's own commits only.
if [ -z "$REF" ]; then
  n=$(git log --format='%h' --grep='Claude-Session' main..HEAD 2>/dev/null | wc -l)
  [ "$n" -gt 0 ] && echo "NOTE: $n commit(s) ahead of main carry a Claude-Session trailer"
fi

[ $fail -eq 0 ] && echo "OK" || echo "-> fix before pushing"
exit $fail
