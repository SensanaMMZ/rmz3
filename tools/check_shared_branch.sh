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

# Identity tells. The history rewrite removed these and required tool scripts to
# use relative paths; they crept back into 11 tool files, so check for them too.
BANNED_ID='SaroGamingPC|saro9564|lyleaigbedion|Saro_95'

if [ -n "$REF" ]; then
  list() { git ls-tree -r --name-only "$REF"; }
  content() { git grep -inE "$1" "$REF" -- "$2" 2>/dev/null; }
else
  # --untracked so a newly added, not-yet-committed file still gets checked;
  # plain `git grep` only looks at tracked paths and would miss it.
  list() { git ls-files; git ls-files --others --exclude-standard; }
  content() { git grep --untracked -inE "$1" -- "$2" 2>/dev/null; }
fi

echo "checking ${REF:-working tree}"

if list | grep -qE "^($BANNED_PATHS)$"; then
  echo "FAIL: banned path present:"
  list | grep -E "^($BANNED_PATHS)$" | sed 's/^/  /'
  fail=1
fi

# Exclusions: src/rom_header.s is a real GBA header field, the agbcc-debug
# dumps carry GCC 2.x's own "CYGNUS LOCAL" comments, and the two guard scripts
# necessarily contain the very patterns they search for.
# `git grep` prefixes the path with "ref:" only when given a ref, so anchor the
# exclusions with (^|:) to match both invocations.
hits=$(content "$BANNED_TEXT" '.' \
  | grep -vE '(^|:)src/rom_header\.s:' \
  | grep -vE '(^|:)tools/agbcc-debug/.*\.instrumented:' \
  | grep -vE '(^|:)tools/(check_shared_branch|refresh_memory_snapshot)\.sh:')
if [ -n "$hits" ]; then
  echo "FAIL: compiler-provenance text present:"
  echo "$hits" | cut -c1-140 | sed 's/^/  /'
  fail=1
fi

# The guard scripts name the identity strings they search for. The memory
# snapshot is NOT exempt: refresh_memory_snapshot.sh scrubs identity from the
# copies, so any hit there is a scrub gap that must be fixed, not waved off
# (an earlier exemption here let four identity lines onto the branch).
idhits=$(content "$BANNED_ID" '.' \
  | grep -vE '(^|:)tools/(check_shared_branch|refresh_memory_snapshot)\.sh:')
if [ -n "$idhits" ]; then
  echo "FAIL: identity path/handle present:"
  echo "$idhits" | cut -c1-140 | sed 's/^/  /'
  fail=1
fi

# Commit-message tells, on this branch's own commits only.
if [ -z "$REF" ]; then
  n=$(git log --format='%h' --grep='Claude-Session' main..HEAD 2>/dev/null | wc -l)
  [ "$n" -gt 0 ] && echo "NOTE: $n commit(s) ahead of main carry a Claude-Session trailer"
fi

[ $fail -eq 0 ] && echo "OK" || echo "-> fix before pushing"
exit $fail
