# Beetank_Update — the r8 / double-home holdout (precise characterization)

**Goal:** byte-match `Beetank_Update` (MMZ3 JP, `ff7a8017…`) compiled with **stock pret-agbcc**
(GCC 2.9-arm reconstruction). Verified this session: pret-agbcc is **byte-for-byte identical**
to the genuine Nintendo SDK `cc1` `2.9-arm-000512` on every test below (only hex-vs-decimal
asm rendering differs), so this is a faithful-compiler / source-reconstruction problem, **not** a
compiler bug. Patching agbcc is off-limits (breaks clean-room + reproducibility + other matches).

## The exact gap

The whole function matches except the `min(a,b)` clamp of `coord.y`:
```c
a = FUN_08009f6c(coord.x - 0x1000, coord.y - 0x600);   /* terrain probe, returns s32 */
b = FUN_08009f6c(coord.x + 0x1000, coord.y - 0x600);
coord.y = (a < b) ? a : b;
```

**Target (retail) codegen:**
```
ldr  r2,[pc] ; mov r8,r2 ; add r1,r8     @ -0x600 cached in r8 (HIGH reg), reused both calls
bl FUN_08009f6c ; adds r4,r0 ; adds r6,r4 @ a -> r4 (store copy) AND r6 (compare copy)
... bl FUN_08009f6c ; adds r7,r0          @ b -> r0 (store) AND r7 (compare copy)
cmp r6,r7 ; bge L ; str r4,[coord.y] ; L: str r0,[coord.y]   @ compare COPIES, store ORIGINALS
```
Key features: const `-0x600` in **r8**; **a and b each double-homed** (compare uses the copies
r6/r7, stores use the originals r4/r0); the copies are plain 32-bit `adds rD,rS,#0`; **no high-word
instruction anywhere**.

**Clean C codegen** (the `?:` above, and the *matched* helper `FUN_080e1394` in `pickup/disk.c`
which is the identical idiom): const in **r4** (low), a single-homed in r6, `cmp r6,r0` on originals,
**no r8** — agbcc is simply more register-efficient.

### Direct compile+diff sweep (2026-06-07, harness in Beetank_Update_v3/_try.sh)
Re-confirmed against the live `target.o`. Diff-lines = `diff` `<`+`>` count (≈2× per-side):

| form | diff-lines | r8 | dead asr | double-home structure |
|---|---|---|---|---|
| if/else (committed MODERN) | **74** | no | 0 | none (value-numbering collapses copies) |
| ternary `(a<b)?a:b` | 82 | no | 0 | none |
| boolean `c=(a<b); c?a:b` | 78 | no | 0 | none |
| store-first `y=a; if(b<a)y=b` | 82 | no | 0 | none |
| **V2 `long long new_var=a`** | **38** | **yes** | **1** | a only; **compare ORIGINALS, store COPY** |
| long-long *return* type | 84 | no | 0 | honest 64-bit compare (`bgt/bne/bhi`) |
| **TARGET** | 0 | yes | 0 | **both a,b; compare COPIES, store ORIGINALS** |

**New finding — V2 and the target are mirror images.** V2 (`cmp r4,r0` on originals, `str r6`
storing the `new_var.lo` copy) double-homes *only* a and reads originals at the compare. The TARGET
(`cmp r6,r7` on copies, `str r4`/`str r0` storing originals) double-homes *both* a and b and reads
*copies* at the compare. A source-level `new_var=a` can only ever produce V2's shape (the copy is the
*store* operand). The target's shape — copies that exist *solely for the compare* while the stored
values are the call-result originals — is not expressible as a named C copy; it is a **register-
allocator coloring artifact** (the allocator put a in r4 for the store and *additionally* in r6 for
the compare). This is why no 32-bit source construct reaches it: GCC 2.9-arm's CSE/value-numbering
collapses every `ca=a` SImode copy *before* allocation (so there is no copy to leave un-coalesced),
and only a DImode (`long long`) pseudo survives value-numbering as a second home — but that is the
*store* copy (V2 shape) and drags the dead high word.

## Mechanism (verified by standalone tests + RTL `-da` dumps)

- **r8 is pure register pressure.** agbcc fills callee-saved lowest-first r4→r5→r6→r7→**r8**.
  Exact cliff: **4 cross-call live values → r4-r7 (no r8); a 5th → r8.** Clean beetank has 4;
  the target has 5. The **5th value is the a/b double-home copy.**
- So the entire problem reduces to: **make agbcc double-home a (and b)** — keep each call result
  in two registers (one for the compare, one for the store) — which raises the cross-call count to
  5 and pushes the const into r8.

## Everything tried to induce the double-home (all fail)

| Attempt | Result |
|---|---|
| `long long nv = a` (V2) | DOES double-home a + r8, but the 64-bit assign emits a **dead high-word `asr r,r,#31`** (coord.y is 32-bit, only low word stored; survives because DImode→2×SImode split runs *after* DCE). Permanent **18-diff floor**. `unsigned long long`→`movs#0`, still 1 dead insn. |
| Source copy `ca=a; cmp ca,..; store a` | agbcc **value-coalesces** `ca==a` regardless of use → no double-home (no r8). |
| `s32 d=a-b; if(d<0)...` (earlier a/b use) | agbcc reuses the same reg for both uses → no split, +1 insn, no r8. |
| regmove `copy_src_to_dest` (two-address dup) | Thumb register arithmetic is **3-operand** → no matching constraint → never fires. |
| caller-save (global.c:1104 path) | saves to **memory** (`regno_save_mem`), not a register → not a reg-copy double-home. |
| pure-pressure permuter (long-long blocked) | **reaches clean r8, no asr** — but via pointer-alias pressure (`new_var=p; &p->s`) whose extra insns floor it at **310** (worse than V2's 225). Never bridged to the overhead-free a/b double-home. |
| cx/cy caching | gives clean r8 standalone, but **no r8** in the full beetank (different surrounding pressure). |
| embedded assignment in compare operands `if((a=f(..))<(b=f(..))){y=a;}else{y=b;}` | **value-coalesced** — GCC 2.9-arm value-numbers the assignment-expression pseudo identical to the later `a`/`b` use; CSE/coalescer fold compare-operand and store-operand onto one pseudo *before* register allocation, so there is no live range to split. Both standalone (`emb.c`) and full beetank (`base_emb.c`): r8=0, dead-asr=0, reg-copies=0; min block emits `adds r6,r0,#0` / `cmp r6,r0` (single-home, compare reads originals). 76-diff in full context. Aimed exactly at the target's split signature but never fires in this compiler. |

## Pressure sweep (controlled, on the matched helper FUN_080e1394) — REFUTES the pressure hypothesis

Took the matched clean idiom and added k cross-call live values (k=0..6), measuring r8 + reg-copies:
| k | cross-call vals | push | r8 | reg-copies |
|---|---|---|---|---|
| 0 | 3 | r4-r6 | no | 0 |
| 1 | 4 | r4-r7 | no | 0 |
| 2 | 5 | r4-r7 | YES | **0** |
| 3-6 | 6-9 | r4-r7 | YES | **0** |
So: the r8 cliff is exactly the 5th cross-call value, AND **pure pressure NEVER double-homes the
call results** — at every level agbcc fills r8 with the *extra* values and keeps y1/y2 single-homed.
This **eliminates "reload-under-pressure" as the double-home cause.**

## The precise open question (for a GCC 2.9-arm internals expert)

Compiler under test: **GCC 2.9-arm (`2.9-arm-000512`, Thumb-1)** — the genuine Nintendo GBA SDK
`cc1`, byte-reproduced by pret-agbcc (verified identical this session). Everything below is specific
to *this* compiler/allocator; it does not necessarily hold for other GCC 2.x ports.

The target's a/b double-home is a reg-to-reg copy of a call result (`adds r6,r4,#0`) that puts the
compare-use in `r6` and the store-use in `r4`. **Every identified mechanism has been ruled out:**
NOT a source copy (value-coalesced), NOT an embedded assignment in the compare operands
(value-coalesced — see table), NOT regmove copy_src_to_dest (Thumb 3-operand → no two-address
matching constraint), NOT caller-save (saves to memory), and **NOT register pressure (sweep above:
0 reg-copies at any pressure level).** The ONLY construct that produces a double-home of a call
result in GCC 2.9-arm is `long long`, which inseparably drags a dead high-word insn (the 18-diff
floor).

**What source-level construct makes GCC 2.9-arm's allocator split a call result's live range into two
hard registers (compare-copy + store-original) — without a 64-bit type (which drags a dead high word)
and without extra pressure instructions?** Equivalently: what pushes the clean beetank from 4 to 5
cross-call callee-saved values where the 5th is an a/b reload-copy? The recurring wall is GCC 2.9-arm's
value coalescer: every pure-32-bit attempt that *names* the split (extra var, source copy, embedded
assignment) is value-numbered back to a single pseudo before allocation.

A C preimage provably exists (Capcom compiled it with this exact compiler). It is reachable neither by
the permuter (from any seed tried) nor by hand. Currently parked as a `#if MODERN` dual-form
(readable C + INCCODE asm body; ROM matches).
