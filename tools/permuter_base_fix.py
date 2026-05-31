#!/usr/bin/env python3
# Make a decomp-permuter base.c parseable by pycparser for this codebase's style:
#   - GNU colon designated-initializers  `field : value`  ->  `.field = value`
#     (rmz3 uses these in Collision/data tables; pycparser only accepts `.f = v`)
#   - varargs function-pointer typedefs   `(...)`          ->  `(void)`
# Carefully skips anonymous bitfields (`u8 : 8;`), labels, and `case`/`default`.
#
# Usage: python tools/permuter_base_fix.py nonmatchings/<Func>/base.c
import re, sys

TYPES = {
    "u8","u16","u32","u64","s8","s16","s32","s64","int","char","short","long",
    "unsigned","signed","void","float","double","bool","bool8","bool16","bool32",
    "vu8","vu16","vu32","vs8","vs16","vs32","size_t","u_8","u_16","u_32",
}

def fix(path):
    out = []
    for line in open(path, encoding="utf-8").read().split("\n"):
        # `(...)` varargs -> `(void)`
        line = line.replace(")(...)", ")(void)")
        # `  field : value` -> `  .field = value`, but not anonymous bitfields
        m = re.match(r'^(\s+)([A-Za-z_]\w*)[ \t]+:[ \t]+(\S.*)$', line)
        if m and m.group(2) not in TYPES and not m.group(3).rstrip().endswith(":"):
            # a value (not another label) follows; treat as designated initializer
            line = f"{m.group(1)}.{m.group(2)} = {m.group(3)}"
        out.append(line)
    open(path, "w", encoding="utf-8", newline="\n").write("\n".join(out))

if __name__ == "__main__":
    fix(sys.argv[1])
    print("fixed", sys.argv[1])
