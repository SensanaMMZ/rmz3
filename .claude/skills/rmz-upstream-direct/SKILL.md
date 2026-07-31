---
name: rmz-upstream-direct
description: Direct-to-upstream matching decompilation of mmzret/rmz3 on Linux or macOS — native build, local byte-gate, target selection, the matching-lever ladder, and upstream PR flow, with no private-fork or porter middle step. Use when contributing matches straight to the upstream repo from a POSIX machine.
---

# rmz3 upstream-direct matching decomp (Linux/macOS)

Work straight against `mmzret/rmz3`. On POSIX systems the upstream repo
builds natively (its CI is a Linux container), so the whole
fork-then-port pipeline — porter fixer chains, name reconciliation,
double bookkeeping — disappears. You write in upstream conventions from
the first line, gate locally in seconds, and PR directly.

## The one rule

**Only the ROM proves a match.** A function is done when
`make compare` prints the OK line for `rmz3.gba` (full-image SHA-1
against a verified retail dump). Compiling proves nothing about bytes;
assembling nothing about layout; linking nothing about the image.
When the link OVERFLOWS, the ROM on disk is STALE — any byte-diff you
read from it lies. Re-check the object stream, not the image.

## Setup (once)

```sh
# Debian/Ubuntu
sudo apt install build-essential git python3 libpng-dev binutils-arm-none-eabi
# macOS
brew install libpng arm-none-eabi-binutils   # or the gcc-arm-embedded cask

git clone https://github.com/pret/agbcc && cd agbcc
./build.sh
git clone https://github.com/mmzret/rmz3 ../rmz3
./install.sh ../rmz3
cd ../rmz3
# place your legally dumped retail ROM where the README says (baserom)
make -j"$(nproc)" compare        # must print the OK line on a clean tree
```

If the local build ever disagrees with CI, CI's container is the
reference environment — trust it, and fix your host to match.

- Never delete the build directory to "clean up" a weird state; you lose
  incremental objects and can mask a real regression. Investigate instead.
- Confirm which branch you are on before AND after any script or
  checkout; failed rebases move HEAD silently.
- Commit as soon as the gate passes. Uncommitted matched work is one
  stray reset away from gone.

## Picking a target

```sh
git grep -h thumb_func_start -- asm/ | awk '{print $2}' | sort > /tmp/live.txt
wc -l /tmp/live.txt
```

Beware: `NON_MATCH` / `NAKED` / `INCCODE` definitions in `src/` look like
C but are still assembly — a function counts as decompiled only when its
asm is gone from the incs AND it has a real C body. Cross off anything
already claimed by an open PR (check the repo's PR list by file before
starting; one entity per PR is the norm, so collisions are visible).

Work smallest-first: sort candidates by byte size (address delta between
consecutive `thumb_func_start` labels, or `arm-none-eabi-objdump` on the
built objects). Small functions teach the compiler's habits cheaply.

## The matching loop

1. **Read the asm** for the target from its `.inc`.
2. **Check siblings first.** Before inventing anything, grep `src/` for a
   matched function with the same shape (same macros, same field access
   pattern). The repo's existing C *is* the idiom dictionary — most
   "mysterious" codegen (staged dead zeros, merged flag stores, shared
   constants) falls out of plain porter-style statements.
3. **Draft the C in upstream conventions** (see below), inserted so that
   ROM order is preserved: split the `.inc` around the function if it
   sits mid-file, and keep every remaining asm function in its original
   order relative to the C.
4. **Gate**: `make -j"$(nproc)" compare`.
5. **On mismatch, diff the instruction stream** of your object against
   the original asm — never the ROM bytes (pool offsets shift):

```python
#!/usr/bin/env python3
# streamdiff.py OBJ SYMBOL INC — canonicalized insn diff
import subprocess, re, sys, difflib
obj, sym, inc = sys.argv[1:4]
d = subprocess.run(['arm-none-eabi-objdump','-d',obj],capture_output=True,text=True).stdout
i = d.find(f'<{sym}>:'); nxt = re.search(r'<[A-Za-z_0-9]+>:', d[i+len(sym)+3:])
body = d[i:i+len(sym)+3+nxt.start()] if nxt else d[i:]
mine = [m.group(1).split(';')[0].strip() for l in body.splitlines()[1:]
        if (m := re.match(r'\s*[0-9a-f]+:\s+[0-9a-f ]+\t(.*)', l)) and m.group(1).strip()]
g = open(inc).read(); seg = g[g.find(f'thumb_func_start {sym}'):]
end = re.search(r'thumb_func_start (?!'+sym+')', seg)
theirs = []
for ls in (seg[:end.start()] if end else seg).splitlines():
    ls = ls.strip()
    if not ls or ls[0] in '.@' or ls.startswith('thumb_func') or ls.endswith(':'): continue
    theirs.append(ls.split('@')[0].strip())
def canon(x):
    x = re.sub(r'@.*','',x); x = re.sub(r'\s+',' ',x).strip()
    x = re.sub(r'^adds (r\d+), #', r'add \1, #', x)
    x = re.sub(r'\bnegs (r\d+), (r\d+)\b', r'rsbs \1, \2, #0x0', x)
    x = re.sub(r'\bip\b','r12',x); x = re.sub(r'\bsb\b','r9',x); x = re.sub(r'\bsl\b','r10',x)
    x = re.sub(r'^muls (r\d+), (r\d+), \1$', r'muls \1, \2', x)
    m = re.match(r'^(b(?:l|x|eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le)?(?:\.n|\.w)?) (.*)$', x)
    if m and not x.startswith('bic'):
        op, tgt = m.group(1).replace('.n','').replace('.w',''), m.group(2)
        s = re.search(r'<([^>+]+)', tgt)
        x = f'bl {s.group(1)}' if op=='bl' and s else (f'bl {tgt}' if op=='bl' else f'{op} X')
    x = re.sub(r'\[pc, #\d+\].*','=POOL',x); x = re.sub(r'=\S+.*','=POOL',x)
    x = re.sub(r', \[(r\d+|sp), #0(?:x0)?\]', r', [\1]', x)
    x = re.sub(r'#0x([0-9a-f]+)', lambda m:'#'+str(int(m.group(1),16)), x)
    x = re.sub(r'#(\d+)', lambda m:'#'+hex(int(m.group(1))), x)
    return x.rstrip(', ')
A = [canon(x) for x in mine if not x.startswith(('.word','.short'))]
B = [canon(x) for x in theirs if not x.startswith('.4byte')]
sm = difflib.SequenceMatcher(None, A, B, autojunk=False)
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=='equal': continue
    print(f'--- {tag} mine[{i1}:{i2}] theirs[{j1}:{j2}]')
    for x in A[i1:i2]: print('  M', x)
    for x in B[j1:j2]: print('  T', x)
```

6. **Micro-test** a shape without a full build (fast error text and
   codegen probes):

```sh
cpp -I tools/agbcc -I tools/agbcc/include -iquote include -nostdinc \
    -std=gnu89 -DMODERN=0 src/path/file.c \
  | tools/agbcc/bin/agbcc -mthumb-interwork -Wimplicit -Wparentheses \
    -O2 -fshort-enums -fhex-asm -o /tmp/probe.s
```

Always check the makefile for per-file flag overrides before trusting
the base flags. Missing prototypes change codegen (implicit-int return
masks); fix warnings, don't suppress them.

## Upstream conventions (write them from the start)

- Flattened object header fields — no nested `p->s` indirection; use the
  upstream struct names and the `SpriteAnimation` naming family.
- Use the repo's wrapper macros and typedefs; grep an existing matched
  file in the same subsystem and mirror it exactly.
- Resolve every symbol by ADDRESS against the asm, never by guessing
  from a name — similarly named helpers exist with swapped meanings.
- One entity/file per PR. Struct/header changes go in their own PR.
  PR body: which functions matched, which are parked and on what
  blocker, and how it was verified (the compare gate + CI run).
- Honest parking: if a function resists after a bounded effort
  (~4–8 lever rounds), commit it as a `NON_MATCH` dual-form — full C
  body under the modern define, original asm via `INCCODE` for the
  matching build — with a comment naming the EXACT blocker
  (e.g. "register home transposition r9/r10, layout-only"). A parked
  dual-form keeps the ROM byte-identical and is honest, reviewable
  progress; never ship a "close enough" body as matched.

## The lever ladder (escalate in this order)

1. **Plain porter-style C** — consecutive `|=`/`&=`/`=` statements,
   struct FIELD access (not byte-pointer casts: byte-pointer stores
   bypass the compiler's read-modify-write path and kill the staged-zero
   pattern retail shows). The famous "dead" `movs rX, #0` staged zeros
   ARE the unified RMW zeros of nearby u8 field stores.
2. **House idioms**: `(u8)--field == 0xFF` / `(u8)++field == K` for
   decrement/increment tests; `MOTION(hi, lo)`; value-join variables for
   shared stores; a `u8` loop/test var vs `u32` decides whether a
   QImode/SImode split (an extra `adds rX, rY, #0` copy) exists — type
   the variable to match retail, don't fight the copy.
3. **Statement order & re-reads**: assign pointer/holder vars AFTER a
   call so they don't steal callee-saved homes; re-read a just-stored
   field (`x = obj->f;` after `obj->f = expr;`) to materialize retail's
   working copy — CSE serves it from the register, zero loads emitted.
4. **Keep-alives** `asm volatile("" :: "r"(v));` — placement controls
   allocation priority and blocks operand-tie coalescing. After a
   store: splits a pseudo. At a block end: extends a range so another
   web can't share the register.
5. **Barriers** `asm("" : "+r"(k));` on a copy or const make it opaque
   (no const-prop, no rematerialization). For a const the compiler keeps
   deriving from a neighbor, define it with a literal asm
   (`asm("movs %0, #N" : "=l"(k));` — divided syntax: `lsl`, not
   `lsls`, inside asm templates).
6. **Pins** `register s32 v asm("rN");` — safe on caller-saved regs
   (r0–r3, ip) with no call in the live range. Pinning a callee-saved
   reg silently DROPS it from the prologue push (ghost-save) unless the
   register also carries a real allocated web — verify the push list
   after every pin. A pinned var also sorts first in commutative
   operands and cannot be clobbered by a 2-op result — use `k *= x;`
   compound forms to steer the destination onto the right operand.
7. **Control-flow shape**: write duplicated case bodies fully inline —
   the compiler's crossjump pass only merges a tail against the physical
   predecessor of its target label; hand-shared `goto` scaffolding
   produces worse shapes. A trailing `asm volatile("");` in an arm
   blocks an unwanted suffix merge. Branch polarity (`beq` vs `bne`
   layout) follows which arm is written first — flip the condition, not
   the logic.
8. **Park** (see above) when the remaining delta is layout-only and the
   round budget is spent. Batches of parked functions sharing one basin
   are re-attempted together when a new lever lands — record the basin
   name in the comment so they're findable.

Label-filter trap: an instruction-stream diff that only shows branch
target "labels" differing can hide an inverted branch polarity — the
ROM gate is the only truth.

## Community escalation

For a function that resists locally, post a decomp.me scratch (family:
agbcc / GBA) with the repo's context header and the target asm — but
verify the scratch actually compiles against the posted context before
sharing the link. `MATCHING_IDIOMS.md` in the repo collects
project-specific levers; read it before inventing, extend it after
discovering.
