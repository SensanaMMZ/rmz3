# decomp.me scratch: Beetank_Update (Mega Man Zero 3, agbcc)

Everything needed to post the holdout as a decomp.me scratch and ask the
matching community (the pret / GCC 2.9 crowd) the allocator question.

## How to post

1. https://decomp.me/new
2. Platform: **GBA**. Skip the game presets (they are just compiler+flag
   bundles named after games); set Compiler directly to **agbcc** — NOT
   "old agbcc" and NOT "agbcc++". This is the pret GCC 2.9 reconstruction,
   byte-identical to our tools/agbcc (verified against the genuine SDK
   2.9-arm-000512 cc1). Then paste our flags (step 3) over whatever the
   flags box contains.
3. Compiler flags: `-mthumb-interwork -Wimplicit -Wparentheses -O2 -fshort-enums`
4. Target asm: paste `beetank_target.s`
5. Context: paste `beetank_context.h`
6. Source: paste `beetank_source.c` (current best clean C — compiles ~103
   instrs vs target 109; the whole function matches except the min() block)
7. Sanity check: the scratch should compile to ~103 instructions and the
   first diff should be the missing `mov r7, r8` prologue pair. If output
   looks wildly different, the compiler picker is on the wrong agbcc.
8. In the scratch description, paste the question below.

## The question to post

> This function matches except the final `coord.y = min(a, b)` clamp.
> Retail codegen has three features clean C never reproduces with agbcc -O2:
>
> 1. the `-0x600` constant is cached in **r8** (a HIGH reg, costing an extra
>    `mov r7,r8`/`push {r7}` prologue pair),
> 2. both call results are **double-homed**: the compare reads copies
>    (`adds r6,r4,#0` / `adds r7,r0,#0`) while the stores use the originals,
> 3. no high-word instruction anywhere (so it isn't a long-long artifact —
>    a `long long` source form floors at 18 diffs with a dead `asr`).
>
> ~48h of decomp-permuter search floored at 18 instruction diffs. RTL dumps
> (`-da`) show clean C value-numbers the copies away in cse2. Our best theory
> is register-pressure spill-preference from a source form with extra live
> scalars, but every pressure-inflating variant we tried lands the constant in
> r4, not r8. Has anyone seen GCC 2.9 pick a HIGH reg for a reload base like
> this, and what source shape causes the compare-on-copies pattern?

## Fidelity check (already done)

The scratch context reproduces the in-repo codegen: compiled standalone with
our agbcc it gives the same 103-instr body and the same r8-less prologue
mismatch as the committed MODERN branch. Full analysis with the RTL-level
findings and the variant sweep table: `notes/beetank-r8-analysis.md`.

## Also worth posting (same question, smaller exhibit)

`readKeyInput` in src/input.c — a 68-instr function whose only mismatch is one
redundant `adds r1,r2,#0` from a live-range split of a CSE'd address; pins and
restructuring cascade the allocation instead of fixing it. If beetank gets
traction, this one is a cleaner minimal example of the same allocator-tie class.
