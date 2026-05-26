#!/bin/bash
# Run permuter on a specific list of function dirs (not all).
# Usage: ./run_some.sh <budget_seconds> <fn> [<fn>...]
set -u
HERE="$(cd "$(dirname "$0")" && pwd)"
REPO="$(cd "$HERE/../.." && pwd)"
PY=$(command -v py || command -v python3 || command -v python)
PERM="$REPO/tools/decomp-permuter/permuter.py"

BUDGET="$1"
shift

mkdir -p "$HERE/logs"

for fn in "$@"; do
  d="$HERE/$fn"
  if [ ! -f "$d/compile.sh" ]; then
    echo "=== $fn === (not set up — skipping)"
    continue
  fi
  echo "=== $fn  (budget: ${BUDGET}s) ==="
  LOG="$HERE/logs/$fn.log"
  timeout "$BUDGET" "$PY" "$PERM" "$d" -j2 --best-only --stop-on-zero >"$LOG" 2>&1 || true
  best=$(ls "$d" 2>/dev/null | grep -oE 'output-[0-9]+-' | grep -oE '[0-9]+' | sort -n | head -1)
  if [ -z "$best" ]; then
    echo "  no improvement over baseline — see $LOG"
  elif [ "$best" = "0" ]; then
    echo "  MATCH found! see $d/output-0-*/source.c"
  else
    echo "  best score = $best — see $d/output-$best-*/"
  fi
done
