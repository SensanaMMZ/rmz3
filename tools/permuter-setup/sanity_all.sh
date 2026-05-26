#!/bin/bash
# Sanity-check that each per-function base.c compiles via its compile.sh.
# Run from repo root.
set -u
HERE="$(cd "$(dirname "$0")" && pwd)"
for d in "$HERE"/*/; do
  f=$(basename "$d")
  # Skip non-function dirs (candidates/, logs/).
  if [ ! -f "$d/compile.sh" ]; then
    continue
  fi
  echo "=== $f ==="
  cd "$HERE/$f"
  rm -f /tmp/check.o
  if ./compile.sh base.c -o /tmp/check.o 2>&1 | tail -3; then
    if [ -f /tmp/check.o ]; then
      echo "  OK: $(stat -c%s /tmp/check.o) bytes"
      rm -f /tmp/check.o
    else
      echo "  FAIL (no output file)"
    fi
  else
    echo "  FAIL (compile error)"
  fi
done
