#!/bin/sh
# The byte gate. Usage (from the repo root):  scripts/gate.sh [jobs]
# Exit 0 only when the ROM is byte-identical to the reference.
# On failure, distinguishes "link overflowed -> ROM on disk is STALE,
# do not read byte diffs from it" from an ordinary mismatch.
JOBS="${1:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}"
LOG="$(mktemp)"
make -j"$JOBS" compare >"$LOG" 2>&1
STATUS=$?
tail -n 3 "$LOG"
if [ $STATUS -eq 0 ] && grep -q ": OK" "$LOG"; then
    echo "GATE: MATCH"
    rm -f "$LOG"
    exit 0
fi
if grep -qi "overflowed by" "$LOG"; then
    grep -i "overflowed by" "$LOG"
    echo "GATE: LINK OVERFLOW — the ROM image is STALE; diff the OBJECT"
    echo "stream (scripts/streamdiff.py), never the ROM bytes, until the"
    echo "size delta is fixed."
else
    echo "GATE: MISMATCH (build log: $LOG)"
fi
exit 1
