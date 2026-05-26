#!/bin/bash
# Run permuter on every set-up function directory, sequentially, with a
# per-function time budget. Each run stops as soon as a 0-score match is
# found (--stop-on-zero) or the budget elapses.
#
# Usage: ./run_all.sh [time_per_function_seconds]
# Default: 300s (5 min) per function.

set -u
BUDGET="${1:-300}"
HERE="$(cd "$(dirname "$0")" && pwd)"
REPO="$(cd "$HERE/../.." && pwd)"
PY=$(command -v py || command -v python3 || command -v python)
PERM="$REPO/tools/decomp-permuter/permuter.py"

mkdir -p "$HERE/logs"

for d in "$HERE"/*/; do
  fn=$(basename "$d")
  if [ ! -f "$d/compile.sh" ] || [ ! -f "$d/target.o" ] || [ ! -f "$d/base.c" ]; then
    continue
  fi
  echo "=== $fn  (budget: ${BUDGET}s) ==="
  LOG="$HERE/logs/$fn.log"
  timeout "$BUDGET" "$PY" "$PERM" "$d" -j2 --best-only --stop-on-zero >"$LOG" 2>&1 || true
  # Best score seen — last 'score = N' line in the log.
  best=$(grep -oE 'score = [0-9]+' "$LOG" | tail -1 || echo "score = ?")
  match=$(grep -c "score = 0\b" "$LOG" 2>/dev/null || echo 0)
  if [ "$match" -gt 0 ]; then
    echo "  MATCH found! see $LOG and $d/output-*.c"
  else
    echo "  no match. best $best — see $LOG"
  fi
done
