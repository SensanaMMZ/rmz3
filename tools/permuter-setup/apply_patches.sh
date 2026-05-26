#!/bin/bash
# Apply local patches to the freshly-cloned tools/decomp-permuter/.
# Run once after `git clone https://github.com/simonlindholm/decomp-permuter`.
#
# Patches: see windows.patch in this directory.
#   - src/main.py    skip exec-bit check on Windows (os.stat doesn't see it)
#   - src/compiler.py wrap compile.sh in bash on Windows (CreateProcess
#                    doesn't honor shebangs)

set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
REPO="$(cd "$HERE/../.." && pwd)"
PERMUTER="$REPO/tools/decomp-permuter"

if [ ! -d "$PERMUTER" ]; then
  echo "tools/decomp-permuter not found — clone it first:" >&2
  echo "  git clone --depth 1 https://github.com/simonlindholm/decomp-permuter $PERMUTER" >&2
  exit 1
fi

cd "$PERMUTER"
if patch -p1 --dry-run < "$HERE/windows.patch" >/dev/null 2>&1; then
  patch -p1 < "$HERE/windows.patch"
  echo "Patches applied."
elif patch -p1 -R --dry-run < "$HERE/windows.patch" >/dev/null 2>&1; then
  echo "Patches already applied."
else
  echo "Patch doesn't apply cleanly — inspect $HERE/windows.patch manually." >&2
  exit 1
fi
