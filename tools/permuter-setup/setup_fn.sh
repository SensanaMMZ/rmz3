#!/bin/bash
# Bootstrap a decomp-permuter directory for one function.
#
# Usage:
#   ./setup_fn.sh <function_name> <src_file_relative> <inc_file_relative> [<candidate_c_file>]
#
# When <candidate_c_file> is supplied, that file's contents are appended to
# base.c — the candidate becomes the seed source permuter mutates from.
# When omitted, base.c is the preprocessed src/foo.c (which usually has a
# NAKED stub for the target — fine if you'll edit base.c by hand).
#
# Example:
#   ./setup_fn.sh unused_080069e0 src/overworld_layer.c \
#                 asm/unused/unused_080069e0.inc candidates/unused_080069e0.c
#
# Produces:
#   tools/permuter-setup/<fn>/
#     ├─ base.c       — seed source with the candidate body
#     ├─ target.o     — original .inc assembled into a .o with symbol <fn>
#     └─ compile.sh   — symlink to ../compile.sh

set -e

FN="$1"
SRC="$2"
INC="$3"
CAND="$4"   # optional

if [ -z "$FN" ] || [ -z "$SRC" ] || [ -z "$INC" ]; then
  echo "usage: $0 <function_name> <src_file> <inc_file> [<candidate_c_file>]" >&2
  exit 1
fi

HERE="$(cd "$(dirname "$0")" && pwd)"
REPO="$(cd "$HERE/../.." && pwd)"
OUTDIR="$HERE/$FN"

PY=$(command -v py || command -v python3 || command -v python || echo "")
if [ -z "$PY" ]; then
  echo "no python found; permuter requires it" >&2; exit 1
fi

mkdir -p "$OUTDIR"
# Write a per-function compile.sh with REPO hardcoded — `ln -s` on this
# MSYS produces copies not real symlinks, so a template+sed approach is
# more reliable than computing the path at runtime.
sed "s|@@REPO@@|$REPO|g" "$HERE/compile.sh.template" > "$OUTDIR/compile.sh"
chmod +x "$OUTDIR/compile.sh"

# Pin objdump to the devkitARM toolchain — permuter calls it directly via
# subprocess and PATH lookup is fragile under the Windows Python launcher.
cat > "$OUTDIR/settings.toml" <<EOF
func_name = "$FN"
compiler_type = "gcc"
objdump_command = "C:/devkitPro/devkitARM/bin/arm-none-eabi-objdump.exe -drz"
EOF

# Preprocess the containing .c file to get all typedefs/structs/externs.
# We DON'T strip __attribute__ here — packed structs in include/entity/player.h
# need it to get the right size. Compile.sh leaves __attribute__ alone too;
# pycparser inside permuter handles it via perm_pycparser's fake-attr support.
cpp -P \
  -I "$REPO/tools/agbcc" -I "$REPO/tools/agbcc/include" \
  -iquote "$REPO/include" -nostdinc -std=gnu89 -DMODERN=0 \
  -DNAKED= -DNON_MATCH= -DWIP= \
  -DEWRAM_DATA= -DIWRAM_DATA= -DUNUSED= -DNORETURN= \
  "$REPO/$SRC" 2>/dev/null > "$OUTDIR/preproc.c"

if [ -n "$CAND" ] && [ -f "$REPO/$CAND" ]; then
  # Drop:
  #   1. ALL NAKED stubs that .include an asm fragment — the assembler
  #      can't find those .inc paths when it runs from a tmp dir, and we
  #      only need ONE function (the candidate) to compile cleanly.
  #   2. `extern char assertion[...]` — static_assert expansions on packed
  #      struct sizes; harmless to skip in the permuter sandbox.
  # NAKED stubs preprocess in two shapes:
  #  - single-line `NAKED foo(...) { INCCODE("asm/..."); }` → one line
  #  - multi-line `NON_MATCH foo(...) { #if MODERN ... #else INCCODE("..."); #endif }`
  #    becomes three lines: header / asm(...) / }
  # The .include-d path can be anywhere — asm/, sound/, sprites/. Match
  # any `.include "` followed by a quoted path ending in .inc.
  # Also strip extern char assertion[...] (packed static_assert expansions).
  awk '
    /__attribute__\(\(naked\)\)/ && /\{[[:space:]]*$/ { pending = $0; next }
    pending != "" {
      if ($0 ~ /\.include[^.]*\.inc"/) { getline _next; pending = ""; next }
      else { print pending; pending = "" }
    }
    /\.include[^.]*\.inc"/ { next }
    /extern char assertion\[/ { next }
    { print }
  ' "$OUTDIR/preproc.c" > "$OUTDIR/base.c"
  echo >> "$OUTDIR/base.c"
  cat "$REPO/$CAND" >> "$OUTDIR/base.c"
else
  cp "$OUTDIR/preproc.c" "$OUTDIR/base.c"
  echo "WARN: no candidate file given — base.c contains the NAKED stub."
  echo "      Edit $OUTDIR/base.c to replace the asm stub with C before permuting."
fi

# Inline the .inc contents into target.s.
{
  echo '	.syntax unified'
  echo '	.text'
  echo '	.thumb'
  echo '	.thumb_func'
  echo "	.global $FN"
  echo "	.type $FN, %function"
  echo "$FN:"
  cat "$REPO/$INC"
} > "$OUTDIR/target.s"

/opt/devkitpro/devkitARM/bin/arm-none-eabi-as \
  -mcpu=arm7tdmi -march=armv4t -mthumb -mthumb-interwork \
  "$OUTDIR/target.s" -o "$OUTDIR/target.o"

echo
echo "Setup complete: $OUTDIR"
echo "  base.c       $(wc -l < "$OUTDIR/base.c") lines"
echo "  target.o     $(stat -c%s "$OUTDIR/target.o") bytes"
echo
echo "Sanity check:"
echo "  cd $OUTDIR && ./compile.sh base.c -o /tmp/check.o && echo OK"
echo
echo "Run permuter:"
echo "  $PY $REPO/tools/decomp-permuter/permuter.py $OUTDIR"
