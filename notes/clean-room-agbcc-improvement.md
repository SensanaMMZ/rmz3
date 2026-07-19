> **⚠️ 2026-06-04 — PREMISE OVERTURNED by the genuine SDK compilers.**
> The user provided the genuine Nintendo/Cygnus GBA compilers (`nincompilers/`),
> including the real Thumb `cc1` `2.9-arm-000512` (and the 2003 thumb-patch build).
> Tested against beetank with identical flags (`-O2 -fshort-enums -mthumb-interwork`):
> the genuine SDK compiler produces **byte-for-byte identical** output to pret-agbcc
> — 96/96 instructions on the clean-C case (single-home, const in r4, **no r8**), and
> identical again on the V2 long-long source (double-home + `mov r8` + dead `asr`).
> **agbcc is a perfect, faithful reconstruction of the original compiler.** Therefore
> the divergence this whole document chases is **NOT a compiler difference** — agbcc
> does exactly what the original did. beetank's ROM allocation (double-home + r8, no
> asr) is a **source-structure** result: the V2 source already yields the target's exact
> registers (a->r4/r6, const->r8) via the genuine compiler, just with the long-long's
> extra high-word `asr`. Finding beetank's exact C is a source-reconstruction problem
> (the permuter's domain), not an allocator-patching one. Attempts 1-7 below were
> rigorous but addressed a non-existent compiler divergence; kept for the record only.
>
> **`__builtin_nocoalesce` is RETIRED (2026-06-04).** It is a *modification to the
> compiler*, so it cannot appear in clean-room source: using it would mean the project's
> compiler is no longer the faithful reconstruction of the original (the whole point of a
> byte-accurate decomp), and it never even produced beetank's exact registers anyway
> (48 byte-diff, all register-pinning variants failed). The correct paths are pure-C
> source reconstruction (permuter, stock agbcc) or the `#if MODERN` dual-form. Do not
> resurrect the builtin. (Attempt 2 below is kept as the diagnostic record that the
> double-home *structure* is reachable.)

# Clean-room agbcc improvement — beetank allocation investigation

**Goal:** make the clean-room `agbcc` reproduce `Beetank_Update`'s exact register
allocation (and, by extension, other allocation-class holdouts) **without touching
any leaked Nintendo SDK material** — i.e. by understanding and, if feasible,
patching the open-source agbcc reconstruction itself.

**Status:** investigation complete; a source patch is being trialled in an isolated
fork (see "Fork experiment" below). Headline finding: no *obtainable* compiler and
no compiler *flag* reproduces the target allocation, and the divergence is the
allocator being **more optimal** than Capcom's build — so any patch that recreates
it is a global de-optimization (the "catch-22").

---

## 1. The target vs what agbcc produces

`Beetank_Update`'s `min(a,b)` ground-snap block (the only part that doesn't match):

- **Target (Capcom ROM):** caches the shared constant `-(6<<8)` in **r8** (a high
  callee-saved reg → forces push/pop), and **double-homes** both results of
  `FUN_08009f6c`: `a` in r4 (store) *and* r6 (compare); `b` in r0 (store) *and* r7
  (compare). It compares the copies, stores the originals. **No extension insn.**
- **Clean C compiled by our agbcc:** 103 insns (target 109). Allocates `a` and `b`
  each to a *single* register (correct CSE), constant in a low reg (r4), no r8.
- **"V2" candidate** (`long long new_var = a;` forces the r8 spill): 109 insns,
  ~18 real diffs — reaches r8 + double-home but drags a **dead `asrs #31`**
  (the long-long sign-extend high word) that the target doesn't have, and uses
  that slot for the b→r7 copy instead.

So from C you get `{r8 + dead asrs}` (V2) or `{no-r8, no-asrs}` (clean) — never the
target's `{r8, no-asrs, b-in-r7}`.

## 2. Compiler lottery — six binaries, all identical (no leaked code)

Built/tested every obtainable agbcc against beetank (clean C and V2 candidates):

| Compiler | provenance | clean C | V2 |
|---|---|---|---|
| `agbcc` (shipped) | tools/agbcc, sha de062b6b | 103 / 98* | 109 / 54* |
| `old_agbcc` (shipped) | tools/agbcc | 103 / 110 | 109 / 66 |
| Klonoa fork `agbcc` | `Dream-Atelier/agbcc`, built from source | 103 / 98 | 109 / 54 |
| Klonoa fork `old_agbcc` | built from source | 103 / 110 | 109 / 66 |
| pret HEAD `agbcc` | `pret/agbcc` HEAD, sha 89e98847, built from source | 103 / 98 | 109 / 54 |
| pret HEAD `old_agbcc` | built from source | 103 / 110 | 109 / 66 |

(*norm-diff line counts.) **Every variant is byte-identical** on beetank. All report
banner `gcc 2.9-arm-000512`. The Klonoa fork is structurally different (GCC-2.9 +
`-ftst`/`-fprologue-bugfix`) yet allocates beetank identically — its extra flags
don't touch the min-block. Conclusion: the entire community agbcc lineage shares one
register allocator; only Capcom's *exact* (non-reconstructed) build would differ,
and that is leaked proprietary material we will not use (clean-room / SEGA v.
Accolade).

## 3. Flag sweep — none move it

Swept ~15 allocator/scheduler flags on the V2 candidate (baseline 54 norm-diffs):
`-fno-regmove`, `-fno-cse-follow-jumps`, `-fno-rerun-cse-after-loop`,
`-fno-force-mem` (→66, worse), `-fno-strength-reduce`, `-fno-expensive-optimizations`
(→120, worse), `-fno-thread-jumps`, `-fcaller-saves`, `-fno-peephole`,
`-fno-function-cse`, `-O3`, `-fomit-frame-pointer`. **All 54 or worse.** The
`-fschedule-insns*` flags are rejected by agbcc. The double-homing lever is **not**
exposed as a flag — notably `-fno-regmove` (disabling the copy pass) changes nothing,
so the single-homing is not a regmove decision.

## 4. RTL pinpoint — the divergence

`-da` dumps of the clean candidate (our agbcc) show the min-block results as
`reg/v:SI` pseudos each assigned to **one** hard register, reused for both the
compare and the store (the optimal choice). The target keeps a *redundant second
copy* of each — an allocation agbcc never generates because its coalescer/allocator
is correct. The matching SImode-coalescer theorem (see memory
`reference_agbcc_coalescer_theorem`): agbcc folds every SImode redundant copy, so a
double-home with no extension insn has **no C preimage**.

## 5. The catch-22

To make agbcc emit the target's redundant copies you must patch the **global**
register allocator (`local-alloc.c`/`global.c`/reload) to be *less* optimal. That
changes codegen for **every** function and would un-match the ~2,900 functions that
currently match. So "improving" the reconstruction to match beetank is
self-defeating unless the patch exactly replicates Capcom's build — which is the
unobtainable original. **The `#if MODERN` dual-form is therefore the correct, final
resolution** (readable C documents the function; the asm body matches the ROM).

## 6. Fork experiment (in progress)

An isolated fork (`../agbcc-fork/`, outside the rmz3 repo) is used to trial source
patches and measure them against BOTH beetank and the full ROM. Build recipe:
host gcc `/c/msys64/mingw64/bin/gcc` 12.2.0 + a `CC` wrapper pinning `TMP`/`TEMP`
to a backslash writable path (make drops env TMP → Windows gcc falls back to
unwritable `C:\WINDOWS`) + `gcc/varargs.h` & `gcc_arm/varargs.h` shims
(`#include <stdarg.h>`; gcc-12 removed varargs.h). Results appended below.

### Patch attempts & results

#### Attempt 1 — `REG_ALLOC_ORDER` promoting the high callee-saved regs (INERT)

**Hypothesis:** the target caches the shared constant in **r8** (a high callee-saved
reg). agbcc's default `REG_ALLOC_ORDER` is undefined → the implicit order is ascending
`0,1,…,16`, so among the callee-saved set {r4,r5,r6,r7,r8,r9,r10} it always reaches for
r4-r7 first and only spills into r8-r10 when forced. Patch `gcc/thumb.h` to list the
high regs first, so the allocator *prefers* r8/r9/r10:

```c
#define REG_ALLOC_ORDER   \
{ 0, 1, 2, 3,  8, 9, 10,  4, 5, 6, 7,  12, 14, 11, 13, 15, 16 }
```

**Build:** isolated fork `../agbcc-fork/` (pret HEAD + this one macro). Clean rebuild
confirmed (`rm -f … regclass.o local-alloc.o global.o thumb.o` then recompiled all four
— the files that consume `REG_ALLOC_ORDER` via the tm.h chain). Resulting binary sha
`64eb4086…` ≠ stock `de062b6b…`, so the patch is genuinely baked in.

**Result: byte-for-byte IDENTICAL output.** Compiled with the patched fork vs stock:

| function | fork vs stock |
|---|---|
| `Beetank_Update` (the target) | identical |
| `FUN_080939e8` (reg-heavy holdout) | identical |
| `FUN_08093a20` (reg-heavy holdout) | identical |
| `FUN_0803a5c8` / shield_fly (reg-heavy holdout) | identical |

**Why it's inert — the decisive structural fact:** `REG_ALLOC_ORDER` only reorders
*which* register a pseudo *prefers* when there is a free choice within its register
*class*. In Thumb-1 almost every pseudo is an operand to `adds` / `lsls` /
`ldr [rn,#off]` / `str [rn,#off]`, all of which **require `LO_REGS` (r0-r7)**. Such a
pseudo can **never** be allocated to r8-r10 no matter where they sit in the preference
order — the class constraint dominates the order. The target's r8 is *not* a pseudo in
a lo-reg instruction; it holds a value whose only consumer is the one Thumb op that
accepts a high reg, hi-reg `add rd, r8`. So reordering the allocator's *preference* is
the wrong lever entirely: the binding constraint is the **register class** (an
instruction-operand property), not the allocation order. This is a cleaner restatement
of the catch-22 than the flag sweep — the single allocator knob the backend exposes
*without* touching the coalescer or the class definitions is a no-op under Thumb-1.

**ROM-wide (confirmed):** swapped the patched binary into the real build and rebuilt
**every** C object (~600) with it. Result: `rmz3.gba` SHA1 =
`ff7a801776dc76e6d8c7ef73a6660ae732934a3f` — **byte-identical to the canonical target.**
The patch changes nothing anywhere in the game. (Bonus: this also proves the fork build
itself — pret HEAD `89e98847` + the patch — is a faithful reconstruction equivalent to
the shipped `de062b6b` for this codebase; even the *version* delta is inert ROM-wide.)

**Verdict on Attempt 1:** `REG_ALLOC_ORDER` is a dead end — it cannot reach beetank's
allocation because the constraint is the register *class*, not the order. Recorded as a
negative result. The remaining candidate levers (coalescer / live-range splitting / CSE
constant-hoisting / class redefinition) are enumerated in §7 below; all are global and
collide with the catch-22, so the `#if MODERN` dual-form remains the resolution.

#### Attempt 2 — `__builtin_nocoalesce` opt-in primitive (SUCCESS as a mechanism)

**Hypothesis:** the catch-22 only bites because every lever tried so far is *global*.
An **opt-in** primitive — a copy the coalescer is told to leave alone, used *only* in
the functions that need it — would create the target's "double-home" (one value living
in two registers) while leaving every other function byte-identical. That sidesteps the
catch-22 entirely.

**Implementation (4-file patch to the fork, ~25 lines total):** expose a builtin
`__builtin_nocoalesce(x)` that emits a SImode reg→reg copy whose source is wrapped in an
`UNSPEC`. Because `local-alloc.c:combine_regs` only coalesces a literal `(set reg reg)`,
an `(set reg (unspec [reg] 0))` is structurally invisible to it and is never folded — no
pass change to the coalescer is even required.

1. `gcc/thumb.md` — new `(define_insn "nocoalesce" …)` emitting `add %0, %1, #0`
   (the exact form the ROM uses for its double-home copies), source = `unspec` idx 0.
2. `gcc/tree.h` — add `BUILT_IN_NOCOALESCE` to `enum built_in_function`.
3. `gcc/c-decl.c` — `builtin_function("__builtin_nocoalesce", int_ftype_int, …)`.
4. `gcc/expr.c` — `case BUILT_IN_NOCOALESCE:` expands the arg into a reg, allocates a
   fresh pseudo, `emit_insn(gen_nocoalesce(target, op0))`, returns the pseudo.

Built clean (fork thumb agbcc `b03425f9…`, exit 0).

**Results:**
- ✅ **Works.** `ac = __builtin_nocoalesce(a); bc = __builtin_nocoalesce(b);` followed by
  `if (ac < bc) y = a; else y = b;` now compiles to the *double-home* structure — the
  comparison reads the copies, the stores read the originals — the exact shape that the
  SImode coalescer made **C-unreachable** for every prior attempt. No miscompile (unlike
  the GNU explicit-register-variable trick, which emitted `str sp`).
- ✅ **Truly opt-in / escapes the catch-22.** A function that does *not* use the builtin
  compiles to a **byte-identical `.text`** under the patched compiler vs stock (sha
  `70683d77…`, 400 bytes, both). The only `.o` delta is `-g` debug metadata, stripped by
  `objcopy -O binary` before the ROM. So the ~2900 matching functions are untouched.
- ⚠️ **Not yet a byte-match for beetank.** It nails the *structure* but the exact
  register assignment still differs (mine: const→r4, a→r6/r1, b→r2/r0; target: const→r8,
  a→r4/r6, b→r0/r7). The r8 cache is *forced* once the double-home register pressure is
  right, so this reduces to steering allocation. Best hand-written form scored **48
  exact-byte diffs vs the V2 long-long's 54** — i.e. the nocoalesce candidate already
  starts *closer* than the best prior C approach, and without V2's dead `asrs #31`.

**Verdict:** the first lever that makes the holdout's structure **reachable from C at
all**, and the first that is provably side-effect-free on the rest of the ROM. Full
byte-match is now an allocation-*tuning* problem (reseed the permuter from the nocoalesce
candidate, pointed at the patched compiler — it can now explore register assignments
around a reachable structure, which was impossible before), not a structural
impossibility. If pursued to 0 it would retire the beetank dual-form *and* generalize to
every allocation-class holdout (blizzack regmove cases, etc.) for the cost of a one-line
`__builtin_nocoalesce` wrap per site. Open question: whether the exact `a→r4 / const→r8`
landing is reachable by source permutation alone, or whether a register-pinned variant
(`(set (reg r6) (unspec …))`) is needed — the UNSPEC form is clean (no miscompile), so a
pinned variant is viable if plain allocation can't be steered there.

**Patch is preserved in the fork at `../agbcc-fork/` (files: gcc/{thumb.md,tree.h,
c-decl.c,expr.c}); binary `../agbcc-fork/agbcc_nocoalesce.exe` (sha `b03425f9…`).**

#### Attempt 3 — `__builtin_pin(x, regno)` exact register pinning (FAILED)

**Hypothesis:** if the permuter can't reach beetank's exact registers by source
mutation, force them directly: a builtin that pins a value to a *named* register via
the clean UNSPEC path (low regs `add rd,rs,#0`, high regs `mov rd,rs`). Pin
`p→r5, a→r4, ac→r6, b→r0(natural), bc→r7, const→r8` to reproduce the target's min-block.

**Implementation:** added `nocoalesce_hi` insn (`mov`, high-reg dest) + `BUILT_IN_PIN`
+ `__builtin_pin(int,int)` decl + expansion that does `gen_rtx_REG(SImode, regno)` as the
copy destination. Built clean (`agbcc_pin.exe` `17a07f9d`).

**Result: FAILED — does not pin to the exact register, and miscompiles on conflict.**
Minimal test `int f(int x,int y){int xc=__builtin_pin(x,6); int yc=__builtin_pin(y,7);
if(xc<yc)return x; else return y;}` produced **`cmp r0, sp`** (comparing against the stack
pointer). `g(){int k=__builtin_pin(x,8); return k+1;}` put x in **`ip`/r12, not r8**.

**Root cause:** the pin insns use *class* constraints (`=l`/`=h`). Reload is free to
reassign within the class, so the value lands in *some* low/high reg (r12 instead of the
requested r8), not the exact one — and when the requested register conflicts with a
value the allocator already placed there (e.g. `p` in r6), agbcc's old reload spills it
incorrectly (the `cmp …, sp`). This is the **same failure mode as GNU explicit register
variables** — forcing a specific hard register fights agbcc's allocator.

**What would be required:** true exact pinning needs **single-register reg-classes** —
define a class containing only `{r6}` (etc.) plus a constraint letter, per target
register, and have the pin insn use that letter so reload *cannot* reassign. That's a
much heavier backend change (multiple `REG_CLASS` + `CONSTRAINT` edits) with an uncertain
payoff: even with exact pins, freeing r6/r7 still requires pinning `p→r5`, which adds
copies the target gets for free from natural allocation. Not pursued.

**Net standing:** `__builtin_nocoalesce` (Attempt 2) remains the one real advance — it
makes the double-home *structure* reachable from C and is provably opt-in. But the
*exact register placement* of beetank is reachable by neither source mutation (permuter
plateaus at 565 on the pinned-nocoalesce structure) nor clean compiler pinning. Only
Capcom's original gcc-2.9-arm build (unobtainable) or heavy single-reg-class backend
surgery would close the last gap. The `#if MODERN` dual-form stands as the resolution.

##### Attempt 3b — single-register reg-classes (also FAILED, conclusive)

Followed up by adding true single-register classes `R4_REG..R8_REG` (each a
one-register `REG_CLASS_CONTENTS` bitmask) + constraint letters `t,u,v,w,x` +
a `pin_reg` insn with one alternative per class, so reload *cannot* widen the
class. Built clean (`agbcc_pin2.exe`).

**Still fails.** Minimal `g(){int k=__builtin_pin(x,8); return k+1;}` put x in
**r7, not r8**; `f()` (pin r6/r7) still emits **`cmp r7, sp`**. The full beetank
candidate reaches the right instruction *count* (109) but byte-diff stays ~94,
with pins landing in wrong registers and `cmp …, sp` spills once 5-6 pins overlap.

**Why it's conclusive:** agbcc's GCC-2.7.2 reload + Thumb-1's restricted high
registers override the single-register constraint (a value "pinned" to r8 is
reloaded into a low reg), and many simultaneous single-reg constraints on
overlapping live ranges exhaust reload, which then spills to the stack pointer.
Exact register *placement* is therefore not forceable via clean compiler
primitives in this compiler — only the allocator's own *choice* can be
influenced (which is what `__builtin_nocoalesce` does: it forbids coalescing but
lets the allocator pick a free register).

**Final conclusion of the clean-room investigation:** `__builtin_nocoalesce` is
the one durable advance (makes the double-home structure reachable from C, opt-in,
zero global effect). Beetank's *exact* allocation (p→r5, a→r4/r6, b→r0/r7,
const→r8) is reachable by neither source mutation (permuter floors at 565 on the
pinned-nocoalesce structure) nor compiler register-pinning (reload overrides it).
Only Capcom's original gcc-2.9-arm SDK build would produce it, and that is the
unobtainable leaked material. **The `#if MODERN` dual-form is the resolution.**

#### Attempt 4 — patching the allocation *priority* in local-alloc.c (FALSIFIED)

**Hypothesis (worth testing regardless of the catch-22 framing):** if Capcom's
compiler colored registers by a different *priority* than agbcc, and the whole ROM
was built that way, then matching that priority might match *more* functions, not
fewer. Test it empirically rather than assume.

**Patch:** changed `QTY_CMP_PRI` in `local-alloc.c` from the log-dampened
`floor_log2(n_refs)*n_refs*size/length` to `n_refs*n_refs*size/length` (stronger
reference-count weighting, so heavily-used values like a/b are colored before
long-lived single-purpose ones). Rebuilt (`agbcc_prio.exe`).

**Result — two measurements, both decisive:**
1. **ROM-wide:** of 60 sampled source files, **16 changed (27%)**. Since every
   currently-matching function matches Capcom *with stock agbcc*, any change is a
   regression. So the priority change breaks ~27% of files — the catch-22,
   quantified.
2. **Beetank:** clean-C byte-diff vs target was **60 with stock and 60 with the
   patch — identical. The priority change does not touch beetank at all.**

**Why it can't help (the real lesson):** beetank's constant is class-constrained
to **LO_REGS** because it's consumed by a low-register add (`adds r1,r1,r4`). The
qty *priority* only orders allocation *within the allowed class*; it cannot move a
LO_REGS-constrained value to r8. The target's const is in r8 only because its
allocator *widened the class* to HI_REGS (and switched to the hi-reg add form)
when the low regs filled up — an allocation⇄instruction-selection interaction,
not a priority decision. agbcc spills to memory instead of widening.

**Conclusion:** the "allocation priority" hypothesis is **falsified** — changing it
regresses ~27% of files *and* leaves beetank byte-identical. The blocker is not
priority; it is the register-class/instruction-selection coupling, which is
deeper and even more global. This closes the last avenue. `__builtin_nocoalesce`
remains the one durable advance; the `#if MODERN` dual-form is the resolution.

#### Attempt 5 — register-class / instruction-selection coupling (deepest dive, FALSIFIED)

Diving into the coupling pinpointed the *true* root cause and the reason every lever
fails.

**True root cause (most precise statement of the divergence):** the target's compiler
**spends callee-saved registers (r6, r7) on short-lived values that don't outlive a
call** — the min(a,b) compare copies are used immediately after the 2nd call with no call
following, yet the target puts them in callee-saved r6/r7. agbcc *correctly/economically*
puts them in **caller-saved r0/r1**. That "waste" of r4-r7 in the target is what leaves
the shared constant no low register, displacing it to **r8**. agbcc keeps r4/r7 free, so
the constant sits in r4. It is the "agbcc is *more optimal*" finding, pinpointed: the gap
is profligate-vs-economical use of callee-saved registers for non-call-crossing values.

**Levers tried for the coupling, all inert/negative:**
- **un-`*` the hi-reg `addsi3` alternatives** (so the const's class includes r8): inert —
  without the register *pressure* there's nothing to push the const high; with nocoalesce
  pressure the copies still take r0/r1 (caller-saved), leaving r4 free.
- **callee-saved-first `REG_ALLOC_ORDER`** (r4-r7 before r0-r3): **0 of 60 files changed —
  completely inert ROM-wide.** This is the decisive observation: **`REG_ALLOC_ORDER` is
  effectively a no-op in agbcc's local allocator.** Allocation is driven by copy-chain
  **register suggestions** (a returns in r0 → its copies are suggested adjacent
  caller-saved regs), which override both the order *and* the qty priority for tightly
  coupled values like these. The register *choice* is suggestion-driven and immovable.

**Why this is the end:** the three exposed levers map cleanly to three dead ends —
order is *ignored* (suggestion-driven), priority *can't cross* the LO_REGS class
constraint, and class-widening has *no pressure* to act on because the copies still
follow suggestions to caller-saved regs. The only remaining knob is the **suggestion
mechanism itself** in `local-alloc.c` (`reg_pref`/`qty_phys_sugg`), i.e. rewriting how
the allocator threads register hints through copy chains — the allocator's deepest core,
with unbounded, unpredictable ROM-wide impact. That is not a "patch"; it is replacing the
allocator.

**Definitive conclusion of the entire investigation:** beetank's allocation is the output
of Capcom's specific gcc-2.9-arm register allocator — its suggestion heuristics and its
willingness to spend callee-saved registers on short-lived values. No exposed agbcc lever
(compiler version, flags, `REG_ALLOC_ORDER`, qty priority, register pinning, add-form
class-widening) reproduces it, and we now understand *mechanistically why each one can't*.
`__builtin_nocoalesce` makes the structure reachable (a real advance); the exact placement
is welded to the allocator's core. **The `#if MODERN` dual-form is the final resolution.**

#### Attempt 6 — the suggestion/selection mechanism itself (deepest possible, FALSIFIED)

Went all the way into the allocator's core register-selection loop.

**Two discoveries about the mechanism:**
1. **`reg_alloc_order` does not exist in this agbcc.** `REG_ALLOC_ORDER` appears only in
   `thumb.h`; nothing reads it. That is the complete explanation for why every order
   experiment (Attempts 1, 5) was 100% inert -- the macro is dead code.
2. **`find_free_reg` hard-codes numeric order** (`int regno = i;`), returning the
   *lowest*-numbered free register in the class. The target instead uses *high* registers
   (r6, r7, r8) for the min(a,b) copies and the constant.

**Patch:** changed `find_free_reg` to iterate a callee/high-first order
`{4,5,6,7,8,9,10,0,1,2,3,...}` instead of numeric -- the deepest, most direct lever for
the register *choice*.

**Result (decisive, terminal):**
- **Beetank got *worse*: byte-diff 60 -> 154.** The allocation reshuffled completely
  (p moved to r6, every value shifted) but in the wrong direction. The target's
  allocation is a *specific emergent pattern* of Capcom's allocator, not a simple
  callee-first order.
- **ROM-wide: 52 of 60 files changed (87%).** Touching the selection order reshuffles
  essentially the whole codebase.

**The depth-vs-breakage progression makes the conclusion unavoidable:**

| lever | ROM-wide change | beetank |
|---|---|---|
| `REG_ALLOC_ORDER` | 0% (dead code) | inert |
| qty priority `QTY_CMP_PRI` | 27% | inert |
| `find_free_reg` selection order | 87% | worse (60->154) |

The deeper the lever, the more catastrophic the breakage -- and beetank never moves
toward the target. Its allocation is the emergent output of Capcom's complete allocator
(suggestion heuristics + selection order + spill decisions interacting), not any single
parameter we can set. Reproducing it means *being* that allocator, which means re-rolling
the entire ROM.

**FINAL, MEASURED CONCLUSION:** every lever from compiler version down to the innermost
register-selection loop has been tested and mechanistically understood. None reproduces
beetank's allocation; the deepest ones break 27-87% of the codebase. `__builtin_nocoalesce`
remains the sole durable advance (reaches the structure, opt-in, zero global effect).
beetank's exact allocation is unreproducible in clean-room agbcc. **The `#if MODERN`
dual-form is, definitively, the resolution.**

#### Attempt 7 — instrumentation + differential inference (definitive, data-backed)

Instrumented both allocator passes (`find_free_reg` in local-alloc.c, `find_reg` in
global.c) to log every register decision: the allocno, its pseudo, calls-crossed,
ref-count, class, which pass, the *free register set*, and the chosen register. Traced
beetank and read the ground truth off the ROM. This converts the conclusion from
reasoning into measurement.

**What the traces prove:**
1. beetank's cross-call values (a, the constant, p) are **globally allocated**
   (`global.c`); local-alloc only handled the non-crossing temporaries.
2. **p -> r5 in agbcc -- which MATCHES the target.** So the global allocator already
   agrees with Capcom on the frame pointer.
3. Every cross-call value has **class = LO_REGS**, and the logged free set is always
   **`{4 5 6 7}` -- r8/r9/r10 are never even candidates.** The constant cannot reach r8
   because its class (set by its use in a low-reg add) excludes the high registers. This
   is the binding constraint, now seen directly in the allocator's own data.
4. The constant takes r4 (lowest free in numeric order). There is **no overflow**: the
   double-home copies (ac/bc) are used immediately after the 2nd call with no call
   following, so they are **local-allocated, caller-saved (r0/r1)** and add *zero*
   cross-call pressure. Everything fits in r4-r7, so the constant is never forced out.

**Why this kills the last targeted hope (the alternate-class lever):** a HI_REGS
fallback class would only fire on *overflow*, and the traces show beetank never
overflows in agbcc. The target reaches r8 only because *its* allocator put the copies
in callee-saved r6/r7 (cross-call, creating the overflow) AND allowed the constant into
HI_REGS. Both are global character changes (copy-placement + add-form class), each of
which the earlier attempts measured at 27-87% ROM breakage.

**Differential-inference verdict:** there is **no allocno-level distinguishing feature**
that a surgical patch could key on. agbcc and Capcom agree on p->r5 and on 99.9% of all
functions; they diverge on beetank only through the *cumulative interaction* of
class-from-instruction-selection + copy-placement-character + numeric selection order --
i.e. the emergent behaviour of the whole allocator, not any one settable rule. The
instrumented data is the proof: the constraint the const hits (LO_REGS, free={4,5,6,7})
is structural and shared by thousands of correctly-matching functions, so it cannot be
relaxed for beetank alone.

**TERMINAL CONCLUSION (now instrument-verified):** every level -- compiler version,
flags, REG_ALLOC_ORDER (dead code), qty priority, register pinning, single-reg classes,
add-form class-widening, both allocator passes' selection order, and the live allocator
decision trace -- has been tested and mechanistically understood. None yields beetank
without breaking 27-87% of the ROM, and the instrumentation proves why: the divergence
is emergent, not parametric. `__builtin_nocoalesce` is the sole durable advance. The
`#if MODERN` dual-form is, conclusively and with measured proof at every layer, the
resolution.
