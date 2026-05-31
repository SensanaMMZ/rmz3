#!/bin/bash
# Compile a single C file to a .o exactly the way the rmz3 makefile does,
# for use with decomp-permuter. The permuter runs this from a scratch dir,
# so every path is absolute (rooted at the repo).
#
# Invoked by the permuter as:  permuter_compile.sh <input.c> -o <output.o>
#
# To create a scratch for a blocked function:
#   1. Build so expected/build has the target .o (tools/refresh-expected.sh).
#   2. Dump the target function's asm to a glabel-prefixed file, e.g.:
#        arm-none-eabi-objdump -d expected/build/rmz3/src/enemy/gallisni.o ...
#      (or hand the permuter the .o symbol).
#   3. tools/decomp-permuter/import.py src/enemy/gallisni.c Gallisni_Update
#      then point its compile.sh at this script.
set -e
REPO="C:/Users/user/MMZ5-X8-Base/rmz3"
DKA="C:/devkitPro/devkitARM"
AGBCC="$REPO/tools/agbcc/bin/agbcc"

INPUT="$1"
OUTPUT="$3"   # permuter passes: <input.c> -o <output.o>
SFILE="${OUTPUT%.o}.s"

# NOTE: -Werror is intentionally dropped — permuter mutations can introduce
# benign warnings that should not abort a candidate.
cpp -I "$REPO/tools/agbcc" -I "$REPO/tools/agbcc/include" -iquote "$REPO/include" \
    -nostdinc -std=gnu89 -DMODERN=0 "$INPUT" \
  | "$AGBCC" -mthumb-interwork -Wimplicit -Wparentheses -O2 -fshort-enums -fhex-asm -o "$SFILE"
printf '.text\n\t.align\t2, 0\n' >> "$SFILE"
"$DKA/bin/arm-none-eabi-as" -mcpu=arm7tdmi -march=armv4t -mthumb -mthumb-interwork -g "$SFILE" -o "$OUTPUT"
