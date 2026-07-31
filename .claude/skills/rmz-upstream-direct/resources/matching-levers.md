# The matching-lever research library


Every technique below was discovered by byte-matching real functions in
the rmz3 decomp and verified through the full-ROM gate. Sections are
ordered roughly general -> specific. `[[name]]` cross-references point at
other sections in this file.


## rmz3-set-flip-macro-fold

*SET_XFLIP/SET_YFLIP macros + cse jump-equiv reproduce retail flip-arm dispatches exactly; plus the const-dest AND chain (pinned res r0 + barrier'd const + keep-alive on the value) and QI/SI split levers from the 2026-07-30 run*


From FUN_080bc200 / copyx_0805763c / FUN_0805c87c / FUN_0806ee94 /
FUN_080a9810 (all byte-matched 2026-07-30, 5-match run).

- **SET_XFLIP/SET_YFLIP macro fold** (include/entity/macros.h): a 4-arm
  w0 dispatch of SetMotion + flags-bit + spr/oam flip stores IS the
  macro, not hand-written stores. With a CONSTANT arg the internal
  `if (v)` folds (bool8 init first -> retail `movs r2,#N` before the
  flags ldrb; oam insert const derived from the bool web -> early
  `movs r2,#0x10/0x20`, addr in r3). With a VARIABLE arg guarded by
  `if (w0 == 0)`, cse record_jump_equiv knows w0==0 on the path: no
  bool init, `strb r5` direct, or-part folds away. Never hand-build
  fv/one vars for these arms - call the macro.
- **QI/SI split family**: `u8 w` stored to an s32 slot or compared after
  a later value-use makes TWO pseudos (the extra `adds rX, rY, #0`).
  To GET the copy when retail has it: `s32 tv = w2; asm("" : "+r"(tv));`
  (cross-mode + barrier; untied/tied transfer-asm and volatile transfer
  all coalesce). To KILL it: type the var u32/s32 (unk_36 case 4).
  For retail `ldrb r1; adds r0,r1,#K`: plain u8 + s32 sum coalesces;
  fix with `asm volatile("" :: "r"(w))` keep-alive placed AFTER the
  clamp/store (placement sets density -> who gets r0; before the add =
  wrong side wins). A "+r" barrier on a u8 var forces a REAL lsls/lsrs
  truncation pair (+4 bytes) - barrier only s32 copies.
- **Const-dest AND chain** (retail `movs r0,#K; ands r0,r1; cmp r0`):
  plain `& K` and a pinned-const both give value-dest. The working
  chain (unk_27): `s32 k = K; register s32 res asm("r0");
  asm("" : "+r"(k)); res = w & k; asm volatile("" :: "r"(w));
  if (res == 0)` - res pin forces dest r0, the w keep-alive stops
  res~w coalescing so res ties k instead.
- **Old-value increment** (`ldrb r1; adds r0,r1,#1; strb r0` then test
  old): `u8 w2 = f; s32 nx = w2 + 1; asm("" : "+r"(nx)); f = nx;` -
  the nx barrier's +refs put nx in r0/w2 in r1 (plain form swaps).
- **Sum-vs-load tie coin flips** (`adds r2,r0,r1` vs in-place): when a
  += sum must be r2 with both loads preserved, pin all three
  (`register s32 cy asm("r0"), dy asm("r1"), ny asm("r2")`) - all
  caller-saved, no call in range; write `dy += 0x40; f = dy;` so the
  in-place add stays on the pinned reg (hanumachine FUN_0805c87c).
- **Barrier'd store-pointer**: `T* st = ADDR; asm("" : "+r"(st));
  *st = v;` keeps the address insns AT THE DECL (retail addr-first
  r0/value-r1); un-barriered single-use pointers fold into the str
  and swap regs.
- sCollisions stride is 0x18: resolve DDP pool constants by ADDRESS
  (base comment + offset/0x18), never by guessing the index.
- copyx head: assign the result-holder pointer AFTER the call
  (`v = Create...; a = ADDR; *a = v;`) or it steals a callee-saved reg;
  `asm volatile("" ::: "memory")` after an s32 store forces the next
  deref's reload (actor.c sibling idiom).

Related: [[rmz3-xflip-triple-template]], [[rmz3-rmw-zero-mechanism]],
[[rmz3-twin-pushout-levers]], [[mmz-check-stubs-before-implementing]].


## rmz3-rmw-zero-mechanism

*retail's \"staged dead zeros\" are agbcc QI-store RMW mask zeros - write plain porter-style consecutive |=/&=/= statements and they all fall out; check a matched sibling file BEFORE inventing levers*


Discovered on Seimeran_Init (2026-07-30) after ~15 wasted lever rounds; the
plain rewrite matched first try.

**Mechanism:** agbcc expands EVERY QI struct-field store as a bitfield RMW:
`field = v` becomes `t = (field & QI0) | v; field = t` where QI0 is a fresh
QImode zero pseudo (visible in .rtl dump as `(and (subreg field) (reg:QI n))`
with `(set (reg:QI n) (const_int 0))`). CSE unifies these zeros across
extended BBs (even across calls); combine folds the &0/|0 away; the SHARED
zero's def survives as retail's famous "dead staged movs rX,#0" (often in a
callee-saved reg when its cse-uses crossed a call). The z4/z6/z2 staged
zeros, the mid-or-chain movs, the NULL-arg r6 store in Init bodies - ALL are
this, produced NATURALLY by plain porter-style code:

```c
SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
(p->s).mode[1] = sInitModes[(p->s).work[0]];   // its RMW zero becomes r6, reused by INIT_BODY's NULL fn store
(p->s).flags |= FLIPABLE;
(p->s).flags |= DISPLAY;                        // second RMW zero = the movs r4,#0 between movs#1 and orrs
InitNonAffineMotion(&p->s);
if (...) { INIT_BODY(p, sCollisions, 4, NULL); } else { INIT_BODY(p, sCollisions, 6, NULL); }
SET_BODY_INTERSECT_HANDLER(p, (void*)0x...);    // its own body-ptr var makes the fn overwrite non-provably-dead -> both strs kept
```
Kill-blocks likewise: `flags &= ~DISPLAY; flags &= ~FLIPABLE; EXIT_BODY(p);
SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);` inline per site (cannon_hopper.c) -
crossjump merges the common tails into the shared _68E-style block.

**Corollaries:**
- ALWAYS grep a matched sibling (crossbyne.c, cannon_hopper.c) for the idiom
  before hand-building zeros/barriers. The porter macros (INIT_BODY,
  SET_BODY_INTERSECT_HANDLER, EXIT_BODY) are DESIGNED to reproduce these shapes.
- A zero var with no use before its next def is deleted by
  delete_trivially_dead_insns BEFORE cse can wire it to anything - hand-staged
  `z = 0;` decoys do not work; barriers on them make the value opaque and
  PREVENT the beneficial cse; pinned vars are cse-exempt entirely.
- Byte-pointer stores `*((u8*)p+off) = v` bypass store_bit_field (no RMW
  zero) - use to DECOUPLE a site from the zero-web when a zombie movs in a
  callee-saved reg appears (dead movs r7,#0 + push r7 = cross-call zombie
  from cse-unified RMW zeros whose uses combine folded).
- agbcc -da dumps (esp. .rtl vs .cse2 vs .greg) pinpoint such pseudos fast:
  find the hard reg in "Register dispositions", then its pseudo's insns in .rtl.
- Update-side barrels that DID stay necessary on Seimeran_Update: kfe-style
  pinned const for `x & 0xFE` const-dest, k2/k40 barrier'd consts with pinned
  gf r3, tail `asm volatile("")` to unmerge killA/killB (crossjump DOES merge
  arbitrary same-target jump pairs at hard-reg level, contra the
  predecessor-only rule), a-keepalive inside the inner if, bls-polarity gotos.
  A future cleanup could likely go plain per this mechanism (untested).

Related: [[rmz3-crossjump-predecessor-rule]], [[rmz3-or-zero-barrier-lever]],
[[mmz-check-stubs-before-implementing]].


## rmz3-crossjump-predecessor-rule

*agbcc crossjump merges a jump's tail ONLY against the physical predecessor of its target label - write duplicated case bodies INLINE, never hand-share with gotos; solved FUN_0808f000, explains cubit park*


Discovered on FUN_0808f000 (claveker, 2026-07-30) after the same merge
mystery burned ~10 rounds on CubitProjectile_Init.

**The rule:** agbcc's cross-jump pass does NOT merge two arbitrary jumps
to the same label even when their tails are byte-identical (that is why
retail keeps duplicated SET_ROUTINE / SetMotion+state-check blocks per
case). It merges exactly ONE shape: a jump to label L whose preceding
insns match the code PHYSICALLY IN FRONT of L (the fallthrough
predecessor). The matched suffix is trimmed and the jump is redirected
into the predecessor block.

**How to apply when decompiling a switch with shared-looking tails:**
- Write every case body FULLY INLINE (its own `mode[2]++`, its own
  SetMotion, its own InitBody + parent/fn + routine tail). Do NOT create
  `goto shared_tail` scaffolding - hand-sharing produces jump-to-label
  from every site and agbcc trims none of them (or worse shapes).
- Sharing then emerges automatically wherever a case's inline tail
  matches the block that physically precedes the join label (usually the
  LAST case before the fallthrough join). E.g. `if (state == 3) {
  mode[2]++; } break;` compiles to `bne end; b shared_inc` because the
  shared inc is the predecessor of `end`.
- Source CASE BODY ORDER = retail BLOCK ORDER (reorder case labels
  textually to match the jump table's address order, e.g. 0,2,3,...,9,1/10,11).
- A cross-case entry like retail case-0 jumping into case-9's tail is
  written as a full inline body ending `goto tick;` where `tick:` labels
  the case-1 body - the merge against case-9 (tick's predecessor)
  happens automatically.
- [[mdiff-label-filter-trap]]: the `if (x == 3) { inc }` beq-form vs
  `if (x != 3) break;` produce inverted bne/beq layouts - pick the form
  whose taken-branch polarity matches retail.

This likely unparks CubitProjectile_Init (77d2371a): rewrite cases
0/1/2 with fully inline routine blocks (no goto zeros scaffolding) and
the InitBody cases inline too - retail's _080A630E/_080A6316 sharing is
the predecessor-merge of case-3's copy with 6/5 trimmed into it.

**Cubit retry result (same day):** the predecessor rule + tail
`asm volatile("")` uniquifiers DID keep cases 0/1 inline (the rule holds),
and w-r2/bd-r4/o-r5 pins + o-recycled mode store fixed most regs — but the
`bd = NULL` movs r4,#0 slot (retail: between movs r1,#1 and movs r7,#0)
could not be anchored: plain init sinks below the orrs pair, and every
fake-dep asm variant (dep on c, dep via z7) explodes allocation into an
r8 spill. Cubit stays parked on this single scheduling slot. A zero-emission
scheduling anchor that does not perturb regalloc is the missing lever.
**Tail-volatile lever (works):** `asm volatile("");` as the LAST statement
of an if-arm kills backward suffix-matching at zero bytes — use it to keep
duplicated chain arms inline instead of merged.

**Ghost-save basin (icebon_080ca154, FUN_080dc900, 2026-07-30):** agbcc
EXEMPTS explicit-register locals (`register ... asm("r7")`) from the
prologue save set — using a pinned callee-saved reg emits UNSOUND code
(caller's reg silently clobbered) and the 2-byte push/pop delta cannot be
closed: no zero-emission shape (clobber asm, dead pin, live-across-call
keep) forces the save. Retail's r7 saves come from NATURAL allocation
(pressure r0-r6). When a fn is byte-exact except the push/pop list and
retail uses r7 for a constant, it is this basin — park as dual-form.

**p/parent transposition basin (Projectile29_Init, 2026-07-30):** when a
fn caches BOTH the entity (p) and a parent/sibling pointer for the whole
body, the two can come out with swapped callee-saved homes (mine p=r6/
parent=r7, retail p=r7/parent=r6) while everything else matches. Priority
boosts (asm-use refs on either), pinned copies, and web isolation all
failed to flip the pair; pins are ghost-save-trapped. 155-byte pure
transposition -> park as dual-form rather than burn rounds. Useful working
shapes discovered en route (these DID land): routine-set modeID as a
variable reused for the xflip mask (`one = 1; ...mode = one; xf = (...)
& one;` -> ands rX,r4 web), `register u32 t asm("r0"); t = 1;
asm volatile("" : "+r"(t));` to force a FRESH movs #1 whose or keeps the
const-side dest, `f4 = 0; asm volatile("" : "+r"(f4));` to keep a dead
zero init alive, and barriered z8 to stop zero-web joins.

**Ghost-save EXCEPTION (FUN_080990d8, 2026-07-30):** a pinned callee-saved
var DOES get its prologue save when it has a volatile consuming asm-use:
`register s32 z5 asm("r5"); z5 = 0; asm volatile("" :: "r"(z5));` kept
push {r4,r5,lr} AND emitted the dead movs r5,#0 exactly like retail's
dead-kept staged zeros. The earlier "no zero-emission shape forces the
save" finding was tested without the consuming-use form. This is the
lever for retail's dead callee-saved constant inits. Also: per-arm zeros
that web with a dead staged zero need their own `asm("" : "+r"(z2))`
barrier or they recycle the staged reg.


## rmz3-xflip-triple-template

*Proven C template for the retail xflip double-eval triple (spr.xflip / oam byte6 ~0x11 RMW / flags bit) — unparked FUN_080e5608; also the InitBody bd-var and c4/fl staged-orr tails*


Proven on FUN_080e51b0 (matched) and FUN_080e5608 (UNPARKED first-try,
2026-07-30). The park comment blamed an unfixable "double eval / mask
register kept" tie — wrong again ([[mmz-porter-comments-untrustworthy]]);
the right pins reproduce it exactly.

**Triple template** (retail: v0=r0 scratch, v=r1, one=r2, sh4=r3, ov=r2,
m11=r0, oa=callee-saved):

```c
{
  register s32 v asm("r1");
  register s32 one asm("r2");
  s32 v0 = q->flags >> 4;
  register u8* oa asm("r5");   // r5 inst-1; r4 when parent q is dead (inst 2/3)
  s32 sh4, ov, m11;
  one = 1;
  v0 &= one;                   // inverted form: v0 ^= one; asm("":"+r"(v0)); v0 &= one;
  (p->s).spr.xflip = v0;
  v = (q->flags >> 4) & one;   // inverted: v = f>>4; v ^= one; asm("":"+r"(v)); v &= one;
  oa = (u8*)&((p->s).spr).oam + 6;
  sh4 = v << 4;
  ov = *oa;
  m11 = -0x11;
  m11 &= ov;                   // compound => ands rM11,rOV (dest = m11) like retail
  *oa = m11 | sh4;
  if (v) { flags |= X_FLIP; } else { flags &= ~X_FLIP; }
}
```
- XOR-then-AND needs the barrier between or agbcc folds to adds+bics (+1 insn).
- (s8) cast of a u8 field WITHOUT ldrsb: pin the addr `register u8* cp asm("r0");
  cp = base+off; asm("":"+r"(cp)); u8 ci = *cp; asm("":"+r"(ci)); if ((s8)ci > 2)`
  → retail's adds/adds/ldrb/lsls#24/asrs#24.
- motion-word check `(mst | mid) == 0x500` with `register mid asm("r1")` (=motionID<<8,
  computed FIRST) and `register mst asm("r0")` (=motion.step) → retail's
  ldrb r1/lsls/adds/ldrb r0/orrs r0,r1.
- flags|=4 + z5 staging: `register u32 fl asm("r2"); register s32 c4 asm("r1");
  fl = flags; c4 = 4; z5 = 0; flags = c4 | fl;`
- InitBody tail: `struct Body* bd = &p->body;` used for the call arg AND
  `bd->parent = p; bd->fn = (void*)z5;` → keeps &body in a callee-saved reg
  across the call (retail r4).
- Do NOT pin a pointer copy of the fn parameter (`register Elf* e asm("r6")`)
  — it creates a second pseudo, +copy chain and an extra callee-saved push.
  To move p/q/z/oa into retail's regs, pin the SHORT-lived locals (oa, v, one)
  and let p/q/z fall into place.
- De-alias rule: in an Init that uses both `q = (cast)p` and p, drop q and
  cast p inline at each use, or GCC gives q its own callee-saved reg (+4 bytes)
  — cost me r9 spill in NurseB_Init.

**Shift-pair laundering** (hanu_0805bdc0, 2026-07-30): when retail
re-truncates a value GCC knows is already u8-ranged (ldrb source) with a
`lsls #24 / lsrs #25`-style pair, a plain `(u8)(f >> 1)` folds to one lsrs
and a plain barrier on f gives asrs+pair (3 insns). Write the literal pair
with the barrier BETWEEN the shifts:
`u32 fv = (u32)f << 24; asm("":"+r"(fv)); sel = fv >> 25;` -> exactly 2 insns.
Also from that fn: u8 struct fields compared `> const` emit bls only if the
temp is u32 (`u32 rk = ...->rank`), s32 temp flips it to ble (byte diff);
and a pointer that must live in scratch-then-callee-saved split
(`adds r4, r1` copy) = two pinned vars (`fb1 asm("r1")`, `fb asm("r4")`)
with `fb = fb1; asm("":"+r"(fb1));` after the first use.

**Post-test zero-prop + fake-dep anchor** (shotcounter_0806697c, 2026-07-30,
~13 rounds): inside `if (x == 0) {...}` agbcc substitutes x's uses with any
OTHER known-zero reg (m, z vars) and then merges/hoists the stores � a
barrier on x does NOT stop it (the cmp itself re-proves zero). Fix: PIN x
to its retail reg (`register s32 fb asm("r2")`) � cse leaves hard-reg
pseudos alone. Same fn: a no-dep `z = 0` movs floats to a fixed scheduler
slot regardless of source position; anchor it with a fake-dependency asm
`asm("" : "+r"(z) : "r"(xa));` plus pinning both (`xa asm("r0")`,
`z asm("r3")`). WARNING: pinning two vars to the SAME reg with adjacent
ranges (fb r2 + v r2) made agbcc silently DELETE the if-test � broken
codegen, only the ROM gate caught it; never stack same-reg pins across a
value copy. The eors-const can be pinned via a var (`one1 asm("r1")`).


## rmz3-hdma-builder-template

*byte-matched the first landscape HDMA table builder (FUN_0800fa34 twilight_desert) - the exact variable structure that cracks the giv/pool basin holding five parked NAKED landscape builders*


FUN_0800fa34 (twilight_desert, 2026-07-30) is the FIRST landscape HDMA
scanline-table builder to byte-match. Five siblings are parked NON_MATCH
in this same basin (missile_factory FUN_0800f604, resistance_base,
area_x2, energy_facility, old_residential — "the five NAKED landscape
builders" per the missile_factory comment; anatre too). Retry them with
this exact template.

**The winning variable structure** (see src/stage/twilight_desert/landscape.c):

- `register s32 i asm("r2")` — scanline counter pinned to its retail
  home (caller-saved, no call crossing → no ghost-save risk). Without
  the pin, a fn-scope `base` var steals r2 and i lands r3.
- `register u32 hi asm("ip")` — the per-band 16-bit scroll value lives
  in ip retail-side. Pinning it frees r7, which lets l (the StageLayer
  param) take r8 naturally, cascading q→r6, mfff-const→r7, sh→r5 — the
  whole retail callee-saved map falls out.
- ONE fn-scope `s32 base;` REUSED by every band (retail home r3). Band
  1 assigns it from a local `c`; bands 2/3 assign `base = (s32)t >> 24`
  DIRECTLY (asrs r3,r0 in place, no copy). Per-band base locals instead
  produce wrong homes/copies.
- Inside each ramp loop's if: `s32 bc = base;` and loop condition on
  `bc` — this is the CSE copy `adds r4,r3,#0` (base's r3 is reused for
  the loop pointer while bc/r4 carries the bound).
- The saved shifted value: `u32 t; u32 sh;` (sh fn-scope, t per band):
  `t = cu << 24; base = (s32)t >> 24; sum = base + i;`
  `asm("" : "=r"(sh) : "0"(t));`   ← transfer-copy idiom
  `if (sum <= LIM) {...}`
  This emits retail's exact `lsls r0,#24; asrs r3,r0,#24; adds r1,r3,r2;
  adds r5,r0,#0; cmp r1,LIM`. A plain `sh = t;` (even with "+r" barriers
  on t or sh) gets COALESCED — the "=r"(sh):"0"(t) form is the only shape
  that kept two pseudos. Explicit `sum` BEFORE the transfer places the
  copy after the add, matching retail.
- Second block reads `(s32)sh >> 24` (CSE gives the cast temp + copy
  into base). Declare the loop pointer BEFORE assigning base there —
  retail orders ptr setup before the base copy.
- Pointer form for mid-table entry: `(u32*)((i << 2) + (u32)q)` —
  index-first operand order (`adds r3,r0,r6`); `&q[i]` emits q-first.
- Band-1 head `movs r2,#0` placement: split the expression
  `s32 c0 = (raw expr); i = 0; c = (s8)c0;` — the i=0 lands between the
  add and the sign-extend pair exactly as retail.
- Ramp value: `u32 val = (0x89 << 16) - ((u32)i << 16);` then
  `val += 0xFFFF0000;` in-loop (constant hoists to r7 naturally).

Struct facts: StageLayer phase@0xE, viewportCenterPixel@0x34 (.x)/0x38
(.y), scrollPower@0x44, scroll@0x4C, bgIdx@0x5C (derived from
FUN_0800f874 codegen). gIntrManager.reservedDma0[3]@+0x174 (system.h).

Related: [[rmz3-xflip-triple-template]], [[rmz3-or-zero-barrier-lever]],
[[rmz3-crossjump-predecessor-rule]].

**cse-seed lever (sunkenlib_08013930, same day):** when retail loads a
big struct-offset constant into a SPECIFIC reg (e.g. `ldr r4,=0x2C00C;
adds r0,r5,r4` for gOverworld.sea) and plain field access picks the
wrong temp (r1), seed cse:
```c
register u32 so asm("r4");
so = 0x2C00C;
sea = ow->sea;                 // reload finds 0x2C00C live in r4
asm volatile("" :: "r"(so));   // keep-alive AFTER the load (before it -> dead reg -> copy)
```
Base-first operand order (`adds r0,r5,r4`) comes from letting RELOAD
split the too-big address (plain `ow->field`); hand-writing `(u8*)ow+so`
with a pinned so puts the hard reg FIRST (`adds r0,r4,r5`) - pinned hard
regs always sort first in commutative operands, pseudo pointer bases
sort first among pseudos. Also from this fn: `asm("" : "+r"(x))`
barriers whose output is DEAD get deleted - use `asm volatile` for
keep-alive barriers; kc-style forced operand copies need the barrier
BETWEEN the copy and the use (`kc = k; asm("" : "+r"(kc)); v = sb|kc;`).

**Priority-boost levers (FUN_0801126c frostline, same day):** the r8-variant
builder (hi crosses __divsi3 calls so hi=r8 callee-saved, l=r9) matched with
the same template plus zero-emission `asm volatile("" :: "r"(x))` refs used
as ALLOCATION-PRIORITY boosts (+1 REG_N_REFS):
- `asm volatile("" :: "r"(hi));` at the `done:` label -> hi outranks l ->
  hi=r8, l=r9 (hi's range already spans the fn, so no range extension).
- retail's 0xFFFF0000 is ONE fn-scope `u32 mfff;` assigned per band
  (`mfff = 0xFFFF0000;` before each ramp loop) — a multi-block global
  pseudo (home r6) — NOT per-loop implicit temps (those localize to the
  leftover reg r7 and steal q's r7). Plus ONE boost asm-use after band2's
  ramp loop to outrank q.
- Do NOT pin hi to a callee-saved reg (r8) — ghost-save exemption would
  drop it from the push list. Pins are only safe on caller-saved regs
  (ip, r0-r3) with no call in range.
- CRITICAL: a boost ref placed where it JOINS two disjoint ranges of a
  var (e.g. sh used in band2 and band3, boost at done:) merges the webs
  into one long range and scrambles the whole allocation. Boost only
  inside an existing range. Over-boosting inverts neighbors (sh vs mfff
  vs q) — add/remove one ref at a time and re-gate; the ordering is
  sh(r5) > mfff(r6) > q(r7) > hi(r8) > l(r9) in this variant.


## rmz3-or-zero-barrier-lever

*Empty-asm barrier + pinned temps reproduce retail's dead-zero/or-zero flag chains — unlocked PantheonBomber_Init; retry the or-zero park basin*


Proven on PantheonBomber_Init (2026-07-29, commit 6c52864f), full-ROM gated.

Retail pantheon-family inits emit a flag chain with an OR-of-runtime-zero
(`movs r3,#0 … orrs r2,r3`) plus a constant-materialize-then-copy
(`movs r0,#1; adds r2,r0,#0`). agbcc folds both from clean C. The working
source shape:

```c
register u8 f0 asm("r1") = (p->s).flags;   // load temp, pin blocks copy-prop
register u8 d asm("r0") = DISPLAY;         // pin blocks coalescing -> keeps the adds copy
register s32 z asm("r3");                  // s32! (u8 z re-truncates after barrier)
s32 f;                                     // s32! (u8 f adds lsls/lsrs before strb)
z = 0;
asm("" : "+r"(z));                         // opacity barrier: keeps movs+orrs, emits nothing
f = d | f0;
f |= FLIPABLE;
f |= z;
(p->s).flags = f;
```

Key findings:
- `asm("" : "+r"(z))` is the only found way to stop 2.95 const-propping a
  literal 0 through an OR; a bare register pin does NOT stop const-prop.
- The barrier erases range info: any u8 in the chain then re-truncates
  (lsls/lsrs #24). Declare z and f as s32 to avoid it.
- Statement ORDER controls emission slots (movs r0 / movs r3 / adds):
  decl-order f0, d, then `z = 0;` gives retail's interleave.
- C89: `asm()` is a statement — it cannot sit between declarations.
  An asm between decls makes mdiff show an EMPTY diff from the failed
  compile ([[verify-at-the-artifact]] — always gate).
- `body->fn = NULL` after a `!FLAG(...)` guard emits `str r5` (the flag
  reg) via cse jump-equivalence — copy grand_cannon.c GrandCannon_Init
  verbatim for the hard-mode-HP if/else (MOD_ENABLED + !FLAG(DEMO_PLAY)).

Retry with this lever: Mothjiro_Init, blizzackJump, unk_32 FUN_080abec0,
phantom fdac movs-r2 ([[rmz3-pr-cleanup-plan]] basin 1), and the NAKED
PantheonHunter_Init (same init template as bomber).

**Update 2026-07-29 — the 0x64xx z-slot basin is CRACKED** (8 blizzack
unparks: Mode0/1/9/18/20, NextMode, Start/EndBlizzard, BombFall, Jump; commits
d55213aa..a39c425f). Recipe for the `mode[2]=0` + 0x64xx-store slotting:

```c
u16* t;
register s32 z asm("r2");
register s32 v asm("r1");
...
t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
z = 0;
v = 0x6403;   /* pool or movs/lsls - either works */
*t = v;
(p->s).mode[2] = z;
```
The z pin on r2 is what stops the scheduler hoisting the zero above the
SetMotion call (an unpinned z emits movs r2 twice: one dead pre-call).
No asm barrier needed for this variant. Retry next: Mothjiro_Init,
unk_32 FUN_080abec0, phantom fdac.

**Refinement (PantheonAquaModObj_Init):** for a COMPLETELY dead zero (no
later use at all), the barrier must be `asm volatile` — a non-volatile
asm whose output is dead gets DCE'd along with the movs. Recipe:
`register s32 z asm("r4"); z = 0; asm volatile("" : "+r"(z));`
Mellnet_Init needed no barrier at all: its z feeds a later props store,
so the plain z-slot positioning lever sufficed.

**Update 2026-07-29 (FUN_080bcc94, commit cef0595f) — three barrier corollaries:**
- **Anti-cross-jump barrier:** two duplicated flag arms (`f = flags|DISPLAY` in
  both an if-arm and an else-if-arm, retail keeps BOTH) get cross-jump-merged
  when the arms use identical register pins. Fix: pin both arms r1/r0 AND put
  `asm("" : "+r"(fr));` in exactly ONE arm — emits nothing but makes the RTL
  blocks non-identical, so pass-1 cross-jump skips them. Unpinned distinct
  pseudos avoid the merge but lose the or-direction AND let CSE share the
  `movs #1` constant across arms (retail rematerializes).
- **Volatile reload:** when retail RELOADS a field it already has in a reg
  (`ldrb` again at a block head), a barrier on the holding var does NOT force
  the reload — use `*(volatile u8*)&field` at the reload site instead.
- **w-temp entry copy:** retail `ldrb r0; adds r5, r0, #0` (load then copy to
  callee-saved) — a bare pin on the r5 var only sometimes yields the copy;
  robust shape: `register s32 w asm("r0"); w = field; asm("" : "+r"(w));
  u32 u = w;` (w s32, u u32 — keeps the unsigned cmp/bls and avoids
  re-truncation from the range-erasing barrier).

**Refinement (FUN_080c5c64, commit 68db472d) — barrier the CONST, not the value:**
any barrier/volatile on the arm's LOADED value re-truncates it (u8 or s32,
before or after the or — all four variants failed). The taint-free anti-merge
differentiator: pin both or-arms r0/r1 as usual and put the barrier on the
pinned CONST var in ONE arm:
`register s32 c1 asm("r1"); c1 = DISPLAY; asm("" : "+r"(c1)); fa |= c1;`
- erases only the constant's known-value (orrs unchanged), never the flags
  value's range -> no lsls/lsrs;
- f (the cross-arm result var) must be s32.
Also learned: duplicated or-arms assigned to the same f get PRE/GCSE-unified
even with distinct unpinned temps (not just cross-jump), and an arm that
stores flags DIRECTLY (own strb) never merges but costs an extra strb vs
retail's shared-store layout - wrong bytes. The const-barrier is the only
shape found that keeps retail's shared store AND both arms.

**Two more (FUN_0806f6cc, commit 8a604d45):**
- **Opaque-pointer barrier kills address-CSE:** when retail computes a struct
  offset fresh (`adds r0,r5,#0; adds r0,#0xc2`) but agbcc derives it from a
  neighboring address (`adds r1,#10`), copy the base into a temp and barrier
  it: `struct Enemy* p2 = p; asm("" : "+r"(p2)); u8* c = (u8*)p2 + 0xc2;`
  - fresh adds pair, zero emitted bytes.
- **Dead-zero in a callee-saved reg (retail r6 never used):** pin the dead
  var to the reg and keep it alive with an INPUT-only volatile asm at the END
  of the fn: `register s32 z6 asm("r6"); z6 = 0; ... asm volatile("" ::
  "r"(z6));` - the "+r" output form gets reallocated to r8 or DCE'd when
  pinned; the input form survives. NEVER pin r7 (agbcc reserves it; emits
  `mov r1,sp` garbage) - natural allocation still uses r7 for the second
  worker zero once r6 is occupied.

**Scoped-pin handoff (ModElf_Init, commit d3fa4fab):** when retail's
`movs r5,#0` sits right AFTER a bl (sched otherwise hoists the zero above
3 calls to the nearest pinned-block edge), no single lever works: a bare
r5 clobber fixes the slot but diverts RA (p→r7 or zero→r8); a plain
z5-pin r5 evacuates later uses through r8 (`mov r8,r5`) once the range
crosses a call; volatile empty asm and literal-0 CSE don't stop the
hoist at all. Working combo:
- `register struct Solid* q asm("r6"); q = p;` — defend the base ptr
  (any r5 manipulation otherwise bumps p off r6), use q everywhere;
- `{ register s32 z5 asm("r5"); z5 = 0; asm("" : "+r"(z5)); s32 z = z5; }`
  — pin+anchor place the def in the retail slot, the handoff copy
  coalesces (0 bytes), and CLOSING THE SCOPE before the later calls
  prevents the r8 evacuation; all later uses go through plain `z`.

**Paired-call results = s32 v[2] stack array (Beetank_Init, 23e9dbc5,
FIRST-TRY):** when two sibling calls each spill to sp[0]/sp[4] AND keep
register copies (str r5,[sp] after `adds r5,r0`, cmp on the reg copy but
adds/reads from the stack slot), the source is an ADDRESSABLE local array
`s32 v[2]; v[0] = f(..); v[1] = f(..);` — the array forces the stack
home, CSE supplies the register copies. Also: `}#else` glued mid-line
after a dual-form body makes cpp discard BOTH the body and the INCCODE
(fn assembles EMPTY, ROM shrinks by the fn size, first diff at the
0x080005D6 bl-shift) — `#else` must start its own line; hit twice
(gyro_cannon, tretista). Parked register-home ties this session:
gyroCannon_0806dccc (CreateSmoke arg-emission order; twin of the NAKED
FUN_0806ddfc) and FUN_0804ff5c (entity kept in r2; agbcc picks
r3/r5/ip under every pin combo).

**Grep matched callers BEFORE levering (FUN_080c065c, facd873b):** when a
call-argument expression resists shaping (staging copies, const-in-scratch,
trunc pairs), grep src/ for OTHER matched callers of the same callee first —
bee_server's `u32 g0 = GetEntityPalID(&p->s); u32 g = (u8)g0 << 5;
StartPaletteAnimation(n, g | 0x200);` reproduced the adds-copy + r2-staged
0x200 that 8 rounds of pin/barrier/keepalive experiments could not (every
volatile asm near the chain kills the range info and re-adds a u16 trunc
pair). The split-into-two-locals shape is load-bearing. Same session also
proved: volatile stores at a shared-tail label stop jump-threading from
duplicating a tiny store island (FUN_08093fe0, 9a49069a).

**Dead zero = NULL-initialized pointer (PurpleNerple_Init, 6382db95):** before
reaching for pinned dead-zero vars + keepalives, check whether the dead
`movs r4,#0` in an init's or-chain is simply `struct Body* body = NULL;`
declared at fn scope (pin it r4) and reassigned `body = &p->body` in the
arms — agbcc's flow-insensitive DCE keeps the NULL store, the placement
between the two `flags |=` statements lands the retail slot, and no
barrier/keepalive is needed at all. Keepalive forms on unpinned dead
zeros misfire: `:: "r"(z)` rematerializes a fresh `movs r0,#0`, `: "+r"(z)`
volatile evicts to r8. Also from the same fn: `case 1: goto c12; case 2:
c12: {...}` keeps three distinct case values in the dispatch tree (retail
`cmp #1 beq; bgt; cmp #2 beq` shape) where `case 1: case 2:` merged into
a range test; and a plain `flags |= C` arm that emits the wrong operand
roles is forced with a value-dest pinned pair (v0 r0 = flags; c1 r1 = C;
v0 |= c1).

**Pinned-copy elision (ReflectLaser_Init, commit 2989d25d):** retail's
redundant `mov r1,r9` (re-copying a high-pinned zero into a low reg that
STILL HOLDS the same 0 from the staging block) gets CSE-elided by agbcc
even when the destination is pinned r1 and even with a barrier on the
copy var — the barrier must go on the SOURCE pinned var to erase its
known value: `asm("" : "+r"(zb)); v1 = zb;` re-emits the mov. For
retail's addr-adds-THEN-mov order, materialize the address into an
unpinned var and anchor it first: `u8* a = (u8*)w + 0x4c;
asm("" : "+r"(a)); asm("" : "+r"(zb)); v1 = zb; *a = v1;`. Also from the
same fn: `movs rX,#1; ands rX,rY` const-dest AND via
`register s32 m1 asm("r0"); m1 = 1; m1 &= wk;`, and a shared high-reg
base copy (`mov r1,r8` once for two ldrs) via
`register struct Entity* e0 asm("r1"); e0 = pz;` then two field reads.

**Anchor-barrier (FUN_080817a8, commit 497ac979):** a bare `register s32 x
asm("rN")` pin is often IGNORED for expression intermediates (reload picks
r7 or whatever) - but an empty asm on the pinned var FORCES the allocation
at that point: `tt = c; asm("" : "+r"(tt)); tt *= dx;` reproduced retail's
`mov r0,r8; muls r0,r3` after 4 failed pin-only attempts. Same trick fixed
the zx load-ordering (`zx = load; asm barrier; qx = load2; dx = zx - qx`).
The asm emits nothing; s32 vars avoid re-truncation. This generalizes the
const-barrier: barrier ANY pinned var whose home register agbcc refuses.

## 2026-07-29 additions (Cubit/Solid18/Solid32/blazin5/childre18/copyx window)

- **Split-subtraction (reassociation defeat):** `(a - C) - b` gets rewritten
  by agbcc into `a - (b + C)` (synthesizable +C instead of pooled -C). Write
  `t = a - C; t -= b;` as two statements to keep retail's pooled negative
  constant (childreMode18 dy and rem).
- **Store-per-arm ladder:** an if/else-if constant ladder (`v=X` per arm then
  one store) gets the "preload + bls" transform (movs before cmp, inverted
  polarity). Writing the STORE inside every arm lets cross-jumping recreate
  retail's `cmp; bhi; movs r0,#X; b shared_strh` shape (copyx threshold ladder).
  goto-ladders do NOT stop the preload transform; duplicated stores do.
- **Split base+offset pools:** `*(u32*)((u8*)&gGlobal + BIG_OFS)` can fold to a
  single pool word `gGlobal+BIG_OFS`; retail often has [gGlobal][BIG_OFS] as two
  pool words + adds. Stage `u8* base = (u8*)&gGlobal;` + barriered `ofs` var,
  barrier BOTH to control which gets r1 vs r0 (copyx seed pointer).
- **Pinned-target coalescing trap:** pinning the RESULT var (rem asm("r6"))
  makes the intermediate accumulate coalesce into r6 (`ldr r6; adds r6`),
  diverging from retail's `ldr r0; adds r0; subs r6,r0,r1`. Pin the
  intermediate too (`register s32 tmp asm("r0")`) in a tight scope
  (childreMode18). And mdiff may compile differently from the real link -
  the byte-diff at fn base is the only truth for these.
- **Fresh post-normalize locals:** reusing dx/dy for the divide results extends
  their live ranges (extra temps + register swaps in the muls chain). Fresh
  nx/ny locals let dx/dy die in-place (`asrs r1,r1,#8` in place) matching
  retail (childreMode18).
- **Natural constant-CSE beats manual one-var:** for `status & 1` ... `1 << w`
  across calls, plain literals reproduce retail's callee-saved shared 1
  (movs r4,#1); a manual barriered `one` variable either re-propagates or
  mis-schedules. Try plain literals FIRST before staging vars (Solid32 case 1).
- **Body-pointer local across InitBody:** `struct Body* b = &p->body;` before
  InitBody + member stores after reproduces retail keeping &body in a
  callee-saved reg vs recomputed adds (Solid32 case 0).
- **u32 switch var elides cmp #0** (unsigned m<1 implies ==0); use `s32 m` when
  retail's compare tree keeps `cmp #0; beq` (Solid32 dispatch).
- **Address-first zero staging:** when `movs rZ,#0` must sit between an address
  computation and the str, stage `u32* sp0 = &field;` then barriered `z = 0`
  then `*sp0 = z;` (Solid32 case 2); the cubit variant (zz barrier after strb
  pair) covers the store-tail case.

## Deathlock_Init battle (2026-07-29) - cross-jump/known-zero levers

- **Known-zero register recycling symmetrizes arms:** on the path where a
  condition `(x & C) == 0` falls through, GCC KNOWS the ands-result register
  is 0 and reuses it as the NULL/zero source in that arm (even for volatile
  stores - volatile forces the store, not a fresh constant). This makes two
  if/else arms byte-identical after the InitBody call, and cross-jumping then
  merges them (one bl instead of retail's two). Barriered locals do NOT help -
  the zero still allocates into the same reg.
- **Cross-jump runs AFTER regalloc:** to keep duplicated arms separate, make
  the store operands land in DIFFERENT registers: pin one arm's zero
  (`register s32 z0 asm("r0"); z0 = 0; asm("" : "+r"(z0));`) while the other
  arm stages `s32 z = 0;` early (movs r5,#0). str r0 vs str r5 -> no merge,
  matches retail's asymmetric arms.
- **QImode narrowing of `u8_load & const`:** `FLAG(gameflags, n)`-style tests
  can emit a spurious lsls/lsrs #24 pair when the result pseudo goes QImode.
  Fix: stage the byte into `s32 sf` and AND with an OPAQUE SImode const
  (`c40 = 0x40; asm("" : "+r"(c40)); if (c40 & sf)`) - no trunc, and the
  or/and DEST coalesces into the dying const var (retail's `ands r0,r1` with
  dest=const-side). Same trick for `|`: `(p->s).flags = c4 | f` with pinned
  `c4 asm("r0")`, `f asm("r1")` reproduced [ldrb r1][movs r0,#4][movs r5,#0]
  [orrs r0,r1] including a z=0 def interleaved between const and orrs.
- **Generator-cannon Init family:** deathlock/generator share the
  MOD_ENABLED + !FLAG(DEMO_PLAY) + InitBody + fn=NULL template; generator
  avoided the trunc only because its mod-bit const (0x40) was CSE-shared with
  the story bit. When the bits differ, use the opaque-const trick.
- **b sharing into another case's tail** (`goto setnop`) + label before the
  shared block reproduces retail's _5E0-style shared fn-assign.

## 2026-07-30 additions (petatria/cattatank/unk_45/unk_47 window)

- **MOTION(a,b) macro vs literal:** `SetMotion(&p->s, MOTION(0x4c,0x05) + work)`
  produces retail's [ldr pool][adds r1,r0,#0][ldrb][adds r1,r1,rX]
  copy-accumulate, while the equivalent LITERAL `0x4C05 + work` merges into a
  single 3-op adds. When a motion-base+index arg mismatches, try the macro
  form first (tile_cannon precedent). The remaining ldrb SCRATCH-reg choice
  (r0 vs r2) is a pure allocation tie - parked FUN_080bfb54 on it after 22
  rounds; nothing (pins, barriers, volatile, statement-exprs) flips it
  without breaking the copy or adding truncs.
- **Pin the anchor var to displace the param:** when p lands r4 but retail
  wants r5, pin the per-case body/anchor pointer to r4
  (`register struct Body* b asm("r4")`) - p gets pushed to r5 (unk_45).
- **Pinned callee-saved switch var collapses zero-zoo:** `register s32 m
  asm("r6"); m = mode[2]; switch (m)` + `(void*)m` / `= m` for known-zero
  stores fixes both the r8 spill and the recycled-zero shape (unk_45, blazin
  family).
- **Seed anchors in LCG chains:** after each `seed = r0v >> 1;` add
  `asm("" : "+r"(seed));` or the def SINKS below the rand extraction and the
  rand steals seed's pinned reg (unk_47 triple-LCG).
- **q^=1 via opaque one:** XOR-then-shift against a pinned barriered
  `one1 asm("r1")` stops the shifted-domain fold AND avoids the QImode trunc
  that `asm("+r"(q))` adds when q's range fits u8 (unk_47 spin flip). Then
  the sh24 block (lsls24, barrier, >>23) gives retail's pair.
- **`(x >> 31)` sign-bit var + arm-specific polarity:** deathlock-style
  `u32 neg = (u32)d >> 31; if (flags & X_FLIP) { if (neg == 0) goto chk; goto rng; } else { if (neg == 0) goto rng; }`
  reproduces mettaur/cattatank facing tests.
- **Facing-update template (cattatank):** pinned `fl asm("r3")` + barriered
  c10 + per-arm barriered m11 = -0x11 masks + manual oam RMW
  (`*oa = (m11 & ov) | c10`) + `cc | fl` opaque const per arm; xflip/b8
  stores share the one/zz var. Store-then-truncate for u8 countdowns:
  `s32 raw = w - 1; work = raw; t = (u8)raw; if (t == 0)` puts strb before
  the lsls/lsrs pair (retail order).

## gyro_cannon family CLOSED (2026-07-30)

- gyroCannon_0806db8c matched, gyroCannon_0806dccc UNPARKED (real match now),
  NAKED FUN_0806ddfc converted to matching C - all three commits SensanaMMZ.
- **The park's own asymmetry barrier was the blocker:** the old k0-barrier
  CreateSmoke arm added a trunc pair (barrier near u8 call arg, the known
  catch-22). Retail's identical if/else arms survive cross-jump UNMERGED when
  the then-arm ends in `b` and the else falls through - GCC 2.95 does not
  merge that shape. Write PLAIN identical arms.
- **Park-review rule:** when a parked fn's C contains asymmetry barriers or
  arg-order staging, and a sibling later matches with plainer code, RETRY the
  park with the sibling's form before trusting the park comment
  ([[mmz-porter-comments-untrustworthy]] applies to my own parks - second
  confirmed case after autruche).
- CreateSlashedEnemy block template (4-call chain): fn-scope pinned a3(r3)/
  c-cache(r5 or r6)/pr8(r8); per-call blocks with pinned sip(ip)/pr2(r2)/
  pal(r5 or r6 per asm), UNPINNED c7/s7 (r7 trap!) with barrier on c7, cache
  handoffs (c5=c7; pr8=pr2) placed between t0&=fl and the if. TryDropItem
  adds-first via `register Coord* c1 asm("r1"); c1 = cache;` then literal 4.
  Flag mask via pinned cf(r0)&flv(r1) pair.

## Barrier branch-estimate inflation (2026-07-30, Enemy14_Update) - MAJOR

- **asm("" : "+r"(x)) statements count ~4 bytes in GCC 2.95's
  shorten_branches length estimates even though they emit ZERO bytes.** A
  conditional branch whose distance-to-target sits near the thumb bcond
  limit (~0xF8) gets INVERTED to beq+b (+2 real bytes) when a barrier
  anywhere between it and its target pushes the estimate over - and the +2
  keeps it over (self-fulfilling cascade; shows up as branch-offset diffs at
  the fn head plus ~30 ripple diffs). Diagnose: fn matches except one
  cond-branch became beq-over-b with SAME distance as retail's short form.
- **Fix: barrier-free pinned-const assignment.** `register u32 st asm("r0");
  ... st = 0x1503;` with NO barrier: pinned hard-reg values do not
  const-propagate (established), so the ldr lands at the assignment point
  anyway - placement control without the estimate inflation. Reusing an
  existing pinned temp for a later constant is free (no new pseudo).
- Corollary: when adding a barrier anywhere in a fn flips distant branch
  polarity, REMOVE a barrier (or convert to barrier-free pin) rather than
  restructure the branch.


## rmz3-ret-variable-lever

*Final early-return if gets branch-inverted by agbcc (pool migrates to end, ROM shrinks); fix with a ret-variable if/else — unparked autruche*


Proven on hirondelle_080da398 + autruche_080da768 (2026-07-28).

A function ending `if (x) return A; y; return B;` (A = pooled constant)
gets its final branch INVERTED by agbcc: the `ldr =A` moves next to the
end pool, the mid-function pool disappears, and the ROM is 4-6 bytes
shorter than retail. mdiff hides it behind the label filter
([[mdiff-label-filter-trap]] — the bne/beq lines contain label refs).

**Fix:** wrap the tail in a block:
`{ TextID ret; if (x) { ret = A; } else { y; ret = B; } return ret; }`
— keeps the then-arm inline with its own mid-function literal pool,
byte-identical to retail.

This unparked autruche_080da768 whose park comment blamed a "constant 1
kept in r3" — wrong diagnosis; it was layout inversion all along
([[mmz-porter-comments-untrustworthy]] applies to my own park comments
too). Retry any park whose unfiltered diff shows a bne-vs-beq flip near
the epilogue plus a migrated pool word.


## rmz3-oam-bitfield-lever

*oam attr1 flip RMW must be written as the bitfield insert spr.oam.xflip = v (s16 temp), NOT a raw byte RMW; plus 2D flip tables and the r7-pin trap*


Proven on mellnet FUN_0807dd24 (2026-07-28), parked at 2 ties after these
three levers eliminated ~50 diff lines:

1. **Bitfield insert**: the recurring `[p+0x4A] = (b & -0x11) | (v << 4)`
   sequence is `((p->s).spr).oam.xflip = v;` — EntityOamData byte 6 has
   named bitfields (unused:4/xflip:1/yflip:1/size:2). 2.95's
   store_bit_field emits the -0x11 SImode mask, the value copy, and the
   shift-before-load order natively. A raw `*(u8*)` RMW can NEVER match:
   known-zero high bits truncate the mask to 0xEF/0xEE. Feed `v` from an
   `s16 v = onLeft;` temp. Retry [[rmz3-pr-cleanup-plan]] parks vfx56
   FUN_080c15d4 and goldOmega1Laser with this.
2. **2D flip tables**: motion selects at base+0/+4/+8 with `(x!=0)*2`
   indexing = `motion_t tbl[N][2]` indexed `[k][(flags & 0x10) ? 1 : 0]`.
   1D `[2*k + sel]` forms go branchy or shift-extract; the 2D form keeps
   the scc branchless and pools the symbol with `adds #4/#8`.
3. **Function-scope load temp**: a per-case reloaded value (motion.cmdIdx)
   declared once at function scope unifies its register across all cases.

**Trap**: never `register ... asm("r7")` in thumb — produced
`mov r0, sp` wrong-code (r7 = frame alias). The r3-vs-r7 tie stays a tie;
give it to the permuter.


## rmz3-implicit-int-call-lever

*when retail lacks the u8-return mask after a bl, call through an (s32(*)(args))Fn cast - reproduces implicit-int declarations; agbcc still emits direct bl*


FUN_080abbb8 (2026-07-30): retail had no lsls/lsrs #24 pair after
bl CountButtonMashing (u8-returning) because the original TU compiled it as an
IMPLICIT declaration (int return). With the modern prototype in scope the cast
`((s32 (*)(struct Zero*))CountButtonMashing)(z)` suppresses the return mask and
agbcc still folds the constant fn address into a direct bl. Check for this when
a matched-looking call site is exactly +2 insns of return-cast. Related levers
from the same fn: pinned load reg + copy-after-ands via a t-split, s32 counters
with post-store `asm("" : "+r"(x))` to KEEP redundant cast pairs.


## rmz3-pool-island-basin

*park class where every insn matches but retail dumps literal pools in extra mid-function islands (duplicate entries, +4N bytes); seen on Elf7_Die*


Elf7_Die (2026-07-30): all code stream-matched yet ROM stayed 12 bytes short -
retail emits THREE literal-pool islands (after the txt-block branch, after the
mission block, at end) duplicating gMission and the 0x121 offset; agbcc from my
layout coalesced one end island. Pool placement follows branch barriers +
range pressure, so identical insns SHOULD give identical pools - a persistent
delta like this means some upstream branch/layout differs subtly even when the
canonicalized stream diff shows only label noise. Check for it when: size short
by exactly 4*N with zero insn hunks. No lever found; parked dual-form.
Related: [[rmz3-rmw-zero-mechanism]].


## rmz3-rng-table-loop-levers

*FUN_0808b938 omega_gold_sword lever set for RNG particle-spawn table loops - literal-asm add#2 opaque base, stmt-expr barrier'd rng pointer, high-reg pins + do-while, k-pin volatile use*


From FUN_0808b938 (omega_gold_sword, 2026-07-30, parked at 22 parity bytes
after 13 rounds — commit 447aad72). Levers that WORKED, for the next
RNG/table spawn loop (retail shape: sl=&RNG, sb=byte-idx, r7=coord-ptr,
r8=counter, r6=u16-ptr, &c spilled sp+0x10):

- **Literal-asm opaque base arithmetic** (kills the sym+2 pool fold): any
  `(u8*)ARRAY + 2 + j` gets tree-folded into a pool entry ARRAY+2, and a
  trailing +2 on a reg-sum always folds into the ldrh offset `[r0,#2]`.
  The ONLY form that reproduces retail `ldr =ARRAY; adds #2; add j;
  ldrh [r0]` is putting the add INSIDE the asm:
  `const u8* mb; asm volatile("add %0, #2" : "=r"(mb) : "0"((const u8*)ARRAY));`
  then `*(const motion_t*)(mb + j)`. Pool stays =ARRAY (shared with the
  t-pointer init), reloaded per iteration, output opaque.
- **Stmt-expr barrier'd pointer in a pinned reg**:
  `register u32* rng asm("r10") = ({ u32* r_ = &RNG_0202f388; asm("" : "+r"(r_)); r_; });`
  gives retail's `ldr r2,=RNG; mov sl,r2` at the DECL position (a plain var
  + later barrier sinks the ldr to the barrier), and per-use fresh low
  copies `mov r0,sl` / `mov r2,sl` (opaque pseudo = no cse of the copies;
  a plain &RNG movable cse's the store copy away).
- **Pins + do-while**: pinning loop vars to retail's callee-saved homes
  (`register u32 j asm("r9")`, `register s32 i asm("r8")`) fixes 3-way home
  permutations (priority rng>i>j vs retail i>j>rng could not be flipped by
  boost asms — in-loop tail boosts caused global carnage). Pins are
  cse-exempt so a `for (; i >= 0; i--)` grows a redundant HEAD test —
  convert to `do { ... i--; } while (i >= 0);`. Ghost-save exemption did
  NOT bite: pinned vars with real in-loop uses keep their prologue saves.
- **k-pin**: `k = (v >> 0x11) & 3; asm volatile("" :: "r"(k));` right after
  the mask keeps retail's eager `lsrs #17; movs r0,#3; ands` — without it
  the ands SINKS below the coord stores (sched drifts it toward first use
  when the const isn't anti-dep-pinned). A barrier'd `three` variable
  instead makes the value opaque and adds u8-extend pairs at call args.
- RNG draw source shape (baby_elf-compatible, no barrier needed in-loop):
  `u32 a = *rng; u32 v = (a * 0x343FD + 0x269EC3) << 1; *rng = v >> 1;
  k = (v >> 0x11) & 3;` — the <<1/>>1 pair survives naturally (canonical
  0x7FFFFFFF mask).
- Second loop of the pair used NO rng var (direct RNG_0202f388, address
  remat'd per use under pressure) and a PLAIN `struct Coord* pc = &c2;`
  first decl (homes r6, add r6,sp,#8 first) — asymmetry between twin loops
  is natural, don't force symmetry.
- **Park cause**: sched places the &c movable spill init AFTER the biv
  inits; retail has it between rng and j, rotating every later scratch pick
  (movs r1,#0 / movs r2,#3 / ldr r1 pool). No source form moved it: asm
  input "r"(&c) (plain or volatile), stmt-expr j-init consumer, volatile
  pc slot var all failed. 22 bytes pure register parity.
- Diagnosis tools that cracked it: agbcc -da `.loop` dump prints per-giv
  "not worth while, benefit vs threshold" (strength reduction of TBL[j+1]
  loses 30 vs 52 in call-bearing loops — retail byte-giv is SOURCE-level,
  not reduction); micro-testcases through tools/agbcc/bin/agbcc.exe with
  repo flags reproduce shapes in seconds vs full builds.

Related: [[rmz3-rmw-zero-mechanism]], [[rmz3-hdma-builder-template]],
[[rmz3-crossjump-predecessor-rule]], [[rmz3-or-zero-barrier-lever]].


## rmz3-twin-pushout-levers

*cannon_hopper FUN_08096ffc/FUN_08097224 twin X/Y pushout physics - full lever kit that byte-matched both (double-opaque u8 mask, manual-threaded ternary with fl barrier, acc-mult vs pinned hard reg, transfer-asm f)*


Both cannon_hopper pushout twins byte-matched 2026-07-30 (commits 2f8a2615,
35019c0e; second was FIRST-TRY from the first's template). The shape: a
(p, a, b) mover with two Y-halves (anchor x∓0x700) and two X-halves
(anchor via `f*0xE00` branch-free select), per-half direction flag f, four
Pushout calls, hit-bit accumulation. FUN_08096ffc uses unk_coord (0x64/0x68)
with a counter/zero tail; FUN_08097224 uses coord (0x54/0x58) and returns
hit, with every home shifted one register (p r5→r4, a r7→r6, hit r6→r7,
f r4→r5).

Levers (all zero-emission, compose freely):

- **u8-extend of a masked flag** (`ands; lsls#24; lsrs#24`): impossible from
  plain C — an AND with any constant or any ldrb operand is nonzero_bits
  provable and the (u8) cast folds away. BOTH operands must be laundered:
  `u32 fv; asm("" : "=r"(fv) : "0"((p->s).flags)); u32 k20 = 0x20;
  asm("" : "+r"(k20)); fl = (u8)(k20 & fv);` — gives retail's
  `ldrb r1; movs r0,#0x20; ands r0,r1; lsls; lsrs` with const-side dest.
- **Double-test ternary pair** (`ldr r1,=NEG; cmp; beq ELSE; movs r1,POS;
  cmp; beq ELSE; mult...`): plain `(fl ? A : -A) * (fl ? f : 1 ^ f)`
  COLLAPSES to one test; a volatile asm between blocks the jump-threading
  (beq1 lands on the second cmp, 2 bytes off). Retail = manual thread:
  `m = -A; if (!fl) goto melse; m = A; asm("" : "+r"(fl)); if (fl) { ... }
  else { melse: y2 += (1 ^ f) * m; }` — the fl barrier between the tests
  keeps cmp2 alive, the goto gives beq1 its far target.
- **Mult copy-side vs a pinned hard reg**: pinned `register f asm("rN")` is
  a hard reg and always sorts FIRST in commutative operands → `m * f` and
  `f * m` both copy f. Retail copies m: `s32 acc = m;
  asm("" : "+r"(acc)); acc *= f; y2 += acc;` (barrier stops combine from
  refolding to the canonical mult).
- **t→f with a real copy insn** (`movs r2,#1; adds r4,r2,#0`): plain
  `f = t` coalesces (no copy). Transfer-asm forces two pseudos:
  `{ s32 t2_ = 0; if (cond) t2_ = 1; asm("" : "=r"(f) : "0"(t2_)); }` —
  scope t2_ per half so each half's scratch rotates like retail (r2 then r1).
- **f pinned to its retail callee-saved home** also PUSHES p's param home
  one register up (f=r4 → p=r5 in ffc; f=r5 → p=r4 in 97224) — don't pin p,
  the pin on f does it; a pinned p param broke C89 (asm stmt before decls)
  and reordered the entry copies.
- **r (pushout result) pinned caller-saved** (r2 first block, r3 second) is
  safe — no call crossed after assignment; fixes the result-copy scratch.
- Anchor association: `x3 = base + -0x700; x3 += f * 0xE00;` as separate
  statements (single-expression forms reassociate to (const+f*K)+base);
  when the base is a fresh reload use `x3 = (p->s).coord.x; x3 += -0x700;`
  so the load targets x3's reg directly (2-op adds).
- Apply-arm tails: write both pushout arms fully inline; crossjump merges
  the [adds; str; orrs] suffix and keeps per-arm [ldr; const-load] exactly
  like retail (predecessor rule). The `+0x100` up-arm const is movs-built,
  the `-0x100` down-arm const is a pool load — identical adds encodings.
- Tail counter: `s32* cnt = (s32*)((u8*)p + 0xc0); *cnt = *cnt + 1;`
  (pointer var so load and store share one address computation).

Related: [[rmz3-rng-table-loop-levers]], [[rmz3-crossjump-predecessor-rule]],
[[rmz3-implicit-int-call-lever]], [[rmz3-or-zero-barrier-lever]].


## mdiff-label-filter-trap

*The mdiff grep filter (-vE \"_08|<fn>\\+\") hides branch-POLARITY inversions — a 'label-only' diff can still fail the ROM; always run the full compare before claiming*


FUN_0805fc1c looked like a first-try match — every hunk showed only `---`
after the label filter — but the full-ROM compare FAILED at 0x0805FC5A.

**Why:** the filter `grep -vE "_08|<fn>\+"` removes BOTH sides of a hunk
when target lines reference `_08...` labels and mine reference `FUN_x+0x..`
— which is exactly what branch instructions look like. A polarity inversion
(`ble → snap; b → end` vs `bgt → end; b → snap`) is invisible: same length,
both lines filtered.

**How to apply:**
- "All hunks label-only" is NOT a match claim — only `rmz3.gba: OK` is
  ([[verify-at-the-artifact]], [[compare-gate-pipe-trap]]).
- When hunks are all `---` but the gate fails, rerun mdiff UNFILTERED and
  read the branch mnemonics — look for inverted conditions with swapped
  targets.
- Fix pattern: rewrite the if with the TARGET's taken-branch polarity,
  using `goto snap`-style labels when the positive test jumps into the
  shared tail (`if (t <= 0xff) goto snap; return;`).


## compare-gate-pipe-trap

*`make compare | tail` eats the exit code — gate on the "rmz3.gba: OK" string, never the pipe status; and middle-carves must interleave two inc pieces in ROM order*


An unverified commit landed because `make compare 2>&1 | tail -1 && git
commit` gates on TAIL's exit code, not make's — the compare had FAILED and
the commit ran anyway (a97da80e, fixed by 6f317db6).

**Why:** in a bare pipe the chain sees only the last command's status; a
red compare looks green. The commit claimed "Match" on a broken ROM.

**How to apply:** gate on the OUTPUT, not the status:
`out=$(make ... compare 2>&1 | tail -1); [ "$out" = "rmz3.gba: OK" ] && ...`
(or `set -o pipefail`). Same class as [[verify-at-the-artifact]].

SECOND lesson from the same incident: a MIDDLE carve is not a tail carve.
Deleting a function from the middle of an .inc and appending the C after
the whole INCASM shifts everything after it (294 bytes of ROM drift, then
826 when the interleave order got scrambled). Middle carves must split the
inc into TWO pieces and the .c must read INCASM(a); C-function; INCASM(b)
in ROM address order — verify the INCASM sequence mirrors the address
order before building, and always end with the full compare.


## name-scope-is-function-scope

*In the rmz3 fixer scripts, resolving a variable's type file-wide silently picks the wrong declaration — scope every lookup to the enclosing function*


Any script that answers "what type is `p`?" must answer it **within the
enclosing function**, never file-wide. This has now caused three separate
bugs in the rmz3 port chain, each of which looked like the fix simply "did
nothing":

* `fix_arg_casts` took the first `X* p` in the file. That is invariably a
  PROTOTYPE at the top -- `bool8 FUN_08045d54(struct Boss* p);` -- so every `p`
  in the file resolved to `struct Boss*`, no call ever looked mismatched, and
  zero casts were added while the error stayed identical.
* Flattening `p->s` file-wide corrupted other functions; the error changed from
  "no member `s`" to "no member `mode`", which reads like progress.
* A capture that dropped `struct` rewrote `struct Enemy* p = (struct Enemy*)…`
  into `Enemy* p = …`, taking the broken-file count from 16 to 28.
* `fix_struct_fields.vsub` and `fix_buffer_offsets` both typed `p` from
  whichever `X* p` came first in the file, so a Projectile-specific rename was
  applied inside a function holding an `Entity*`.
* `fix_common`'s work→buffer pass collected variable NAMES file-wide, then
  rewrote every `name->work[`. In shotcounter_bullet.c that turned upstream's
  ALREADY-CORRECT `p->work[0]` (the entity's own work[] at 0x10) into
  `p->buffer[0]` (0xB4) -- the exact aliasing that function's own comment warns
  about. **Rewriting a neighbour's working code is worse than failing to port.**

A second rule follows: scope every rewrite to the function bodies actually being
LIFTED. `port_cluster.sh` passes `$fns` to fix_return_type, fix_struct_fields
and fix_field_offsets for this reason.

**And the restriction must FAIL CLOSED.** fix_field_offsets' `scoped_sub` read an
empty span list as "no restriction given" and rewrote the whole file, so every
time the lifted bodies were not located it quietly reverted to the unscoped
behaviour the restriction existed to prevent -- and the symptom was identical to
having no fix at all. An empty allow-list means do nothing, never do everything.

**Why:** these files declare every handler at the top and define them hundreds
of lines later, so file-wide "first match wins" is almost guaranteed to hit a
declaration rather than the definition in hand.

**How to apply:** iterate function definitions, brace-match each body, build the
name→type map from that body plus its parameter list, and rewrite only inside
it. When a rewrite pass reports 0 changes but the compiler error is unchanged,
suspect this before suspecting the pattern. See [[rmz3-pr-cleanup-plan]] and
[[rmz3-upstream-port-workflow]].


## rmz3-overflow-was-self-inflicted

*The rmz3 \"ROM overflow\" rejects were caused by my own fixer chain stripping NAKED from upstream's asm-bodied functions — all 15 matched once it stopped*


Fifteen rmz3 clusters were written off as unportable because CI reported
`region 'rom' overflowed by N bytes`. **Every one of them matched** once the
real cause was found, and it was not the ported code at all.

`align_protos.align_return_types` treated `NAKED` as a storage class while
aligning a definition's return type to its prototype, so it rewrote
`NAKED static void Hellbat_Init(...)` into `static void Hellbat_Init(...)`.
Those bodies are raw assembly; without the keyword the compiler emits a
prologue and epilogue around them. Three untouched neighbours in hellbat.c grew
4 bytes each, and the ported function got the blame.

**How it was found — the technique to reuse.** Comparing the built function
against the original `.inc` showed instruction-for-instruction identity, which
ruled out the ported function. Then dumping symbol offsets from both `.o` files
(`nm -n`, upstream vs branch) and printing where the delta first changes showed
the drift starting at `Hellbat_Update` — a function the port never touched. That
one command turned a dead end into a five-minute fix.

**Two lessons beyond the bug:**
* An overflow at the link says the FILE grew, not that your function grew.
  Locate the growth before concluding anything about the code you added.
* Testing every function individually "proved" the cost was structural, and that
  conclusion was wrong — because the damage was per-FILE, so every subset showed
  it. A confident negative result built on a false premise is still false.

Also fixed alongside: the chain sent every fixer's stderr to `/dev/null`, so when
a bad edit left `fix_field_offsets.py` unparseable it silently stopped working;
and a heredoc patch turned a regex `\b` into a literal backspace (0x08), which
matched nothing, silently. `port_cluster.sh` now aborts on `Traceback|SyntaxError`
in the fixer log. See [[name-scope-is-function-scope]] and
[[rmz3-pr-cleanup-plan]].


## verify-at-the-artifact

*Only the step that actually produces the artifact proves the artifact is right — compiling doesn't prove assembly, assembling doesn't prove linking, linking doesn't prove the ROM matches*


**Only the step that actually produces the artifact proves the artifact is
right. Compiling doesn't prove assembly; assembling doesn't prove linking;
linking doesn't prove the ROM matches.**

**Why:** each stage is blind to the class of defect the next one catches. Every
stage in the rmz3 pipeline produced at least one bug that the stage before it
reported as clean:

| A check that passed | The defect it structurally cannot see | Caught by |
| --- | --- | --- |
| byte-probe of one function | a call to the WRONG existing function — `BL` is a relocation, so it is byte-identical | link, or decoding the ROM's real target |
| compile (`cc_check.sh`) | a function defined twice, once in C and once in a carved `.inc` | assemble |
| compile + assemble | a symbol that exists nowhere, or a dropped `.inc` range | link |
| assemble | the lifted C is a different SIZE from the asm it replaced | link (`region 'rom' overflowed by N bytes`) |
| link | wrong bytes — the ROM builds fine and simply is not retail | `make compare` / sha1 |

That size row is worth its own note: a function that byte-matches in the fork
does **not** necessarily match once lifted into a different file upstream. Three
union merges compiled, assembled, and passed the BL-target check, then overflowed
the ROM by 8 bytes at link. Only a full build can tell you.

Concrete instances, all real: shellcrawler byte-verified 24/24 and the ROM
differed by one byte (`AllocEntityFirst`/`AllocEntityLast` are swapped between
fork and upstream); four `tail-batch-1` files passed every compile-only check
with functions defined twice; `lemmingles.inc` lost two functions in a split and
only the linker noticed.

**How to apply — two operational rules:**

**1. Never report something as verified by a check that runs EARLIER than the
failure mode being ruled out. Name the stage that actually ran.** "Byte-verified"
is not "builds"; "compiles" is not "assembles"; "links" is not "matches the
ROM". Use the cheap checks for fast iteration, but require the real build as the
gate before claiming anything works — for rmz3 that is CI running `make compare`
against `rmz3.sha1` ([[rmz3-upstream-build-blockers]]). When a cheap check is
the only one available, state that limit plainly instead of letting it stand in
for the real one.

**2. When adding a check, ask what it is blind to and what would catch that.**
Every check has a blind spot; the useful question is not "does this pass" but
"what could still be wrong after it passes". That question is what produced
`verify_calls.py` (decodes BL targets by ROM address), `check_carve.py`
(compares symbol sets so a dropped `.inc` range cannot hide), `check_incasm.py`
(every `INCASM` target exists and no carved `.inc` is orphaned), and the
assemble step now in `cc_check.sh`. See [[rmz3-upstream-port-workflow]] for the
concrete gates and [[rmz3-verify-names-before-pr]] for resolving symbols by
address.

A blind spot worth remembering: a check driven by `git diff --name-only` cannot
see a file whose `.c` matches upstream while its `.inc` was deleted — the file
is not in the diff at all. `pantheon_fist` broke CI exactly that way after every
local check passed. Scan the whole tree for structural invariants, not the diff.

**2b. "Found nothing" is a result that must be EARNED — check the exit code.**
`git grep -E` does not accept `\s`; it exits 128. Nothing checked the return
code, so a fork-declaration lookup returned `None` unconditionally from the
moment it was written, and read as "the fork does not declare these symbols"
for 13 files. A search that cannot run looks identical to a search that found
nothing. Related: `pat.replace('^', r'^\s*')` also rewrites the `^` INSIDE a
character class (`[^;{)]` becomes `[^\s*;{)]`), so even a working grep would
not have matched. Grep loosely (`-F` on the bare name), match precisely in the
host language.

**3. Never take a script's own stdout as evidence that it worked.** A batch
driver decided success by grepping the merge script for the words "merged OK"
and reported **29 of 40 merged**. Zero had persisted: a dirty tree made runs
abort, and the summary counted TEXT rather than committed state. Worse, the
merge script itself printed "merged OK" after lifting nothing, because a broken
`grep` pattern found no functions and the loop simply fell through.

Two rules from that:

* **Doing nothing is a failure, not a success.** Any step that can legitimately
  find nothing to do must say so and exit non-zero; otherwise a no-op is
  indistinguishable from a completed job.
* **Prove each result against the repository**: the symbol is in the file, the
  file compiles AND assembles, and `HEAD` actually moved. `union_batch.sh` does
  this; the version that trusted stdout produced a completely fictional report
  that was relayed to the user before it was caught.

**Stale-.o masking (2026-07-29, commit f9224c7d):** commit 6100d35c deleted
asm/vfx/unk_64_p3_b_b.inc without committing the C replacement - and ~100
subsequent full-ROM gates stayed green because make never rebuilt the stale
unk_64.o. The break only surfaced when an unrelated edit forced the rebuild.
A green compare only proves files make chose to rebuild; after any commit
that deletes an inc, touch the including .c (or make clean that object) to
prove the pairing actually builds.


## decompme-scratches-must-compile

*Never hand the user a decomp.me claim link unless the scratch compiles (success=True); fix context first*


decomp.me scratches posted by tools/scratch_up.py went out with
success=False (ldwqE had an EMPTY context; C3UWS had the raw
build/ctx.c which agbcc rejects — varargs fn-pointer typedefs, data
initializers referencing stripped statics). The user claimed them and
found they don't compile.

**Why:** a non-compiling scratch is useless to community solvers and
wastes the user's claim. `scratch_up.py` prints `compiled:
success=False` but publishes anyway — treat that line as a FAILURE.

**How to apply:** before giving the user any claim link, the scratch
must compile server-side. Recipe that works: preprocess the local
harness (`cpp -DMODERN=0` with repo includes), use the .i minus the
target function as the Context and the target function as the Source
(same trick as the permuter base.c repair, see
[[rmz3-decomp-reference-path]] project notes); verify locally with the
exact decomp.me preset flags (`-mthumb-interwork -Wimplicit
-Wparentheses -O2 -fshort-enums`, no -fhex-asm) before re-posting.
Fix scratch_up.py to abort on success=False. TWO extra traps found
fixing ldwqE: (1) verifying with agbcc alone is NOT enough — agbcc
copies `asm(".include ...")` text through to the .s and only the
ASSEMBLER fails, so always verify ctx+src through arm-none-eabi-as
too; (2) the source function name must exactly equal the scratch's
diff label (a `_TEST`-suffixed harness name breaks the diff).

THIRD trap (2026-07-27): **agbcc does not preprocess at all** — `//`
comments are syntax errors and `#define` silently no-ops, which turned
a macro call into an implicit extern function and produced a bogus
local "OK" (and bogus posted VGRlc/yt9Gj/GhyhM — dead, do not claim).
The faithful local gate is `arm-none-eabi-cpp -nostdinc -undef
-std=gnu89 | agbcc | arm-none-eabi-as`, mirroring the server. Reusable
agbcc+assembler-clean context: fork notes/decompme/ctx-agbcc-clean.c.
Independently verify with `POST /api/scratch/<slug>/compile` after
posting — don't trust the tool's own print.


## decomp-corpus-crossref

*Cross-reference the GBA decomp corpus (tools/decomp_crawl.py) before contorting a harness or posting to decomp.me; refresh weekly*


The user asked (2026-07-25) that the pokeruby_r8_report crawl be
generalised to every repo in notes/urls-of-gba-decomps/list-of-decomps.md,
that the generated files be dated, that the corpus be cross-referenced
BEFORE posting to decomp.me, and that upstreams be re-checked weekly.

**Why:** a scratch posted without checking the corpus spends a community
ask on a question the corpus can answer, and undated reports overwrite
each other so you lose the record of what a project looked like at crawl
time.

**How to apply:** `tools/decomp_crawl.py` in the rmz3 repo does all of it —
`clone` / `index` / `grep '<insn regex>'` / `check`. Corpus lives in
`../decomp-corpus/` with `manifest.json` (commit + crawl date per project);
dated reports in `notes/decompme/crawl/<proj>_<trait>_report_<date>.md`.
Run `grep` for the exact instruction the byte diff flagged (e.g. `mov r8`,
`and .*#0xff`) and read the corresponding C in the corpus clone before
trying more spellings. Weekly: run `check`, then re-clone+re-index only the
projects it lists as moved. See [[decompme-scratches-must-compile]] for the
posting rules that apply once the corpus has been consulted.


## permuter-background-policy

*Permuters run in background with explicit check/stop criteria — closeness, iterations-since-best, wall time — checked between functions*


Permuter runs always go to the background while decomp work continues; each
run gets checked between functions (or ~every 30 min) and CALLED against
these criteria (user directive 2026-07-28):

- **HARVEST** — score reached 0 (translate the winner into honest C and
  byte-verify), or the best output reveals a structural idea worth
  hand-translating even if nonzero.
- **KEEP RUNNING** — best score still improving within the last ~2,000
  iterations AND under ~2h wall time.
- **KILL & PARK** — no new best for 5,000+ iterations, or ~2h elapsed
  without a meaningful downtrend, or best still above ~50% of the base
  score after 10k+ iterations (the readKeyInput lesson: allocation ties
  never improve; the beetank lesson: copy-basins crawl but converge).

**How to apply:** run dir keeps output-<score>-N snapshots; read the task
output tail for iteration count and last new-best line; on KILL, record
the best score + shape delta in the function's dual-form comment and
notes, then move on. Kill the process tree properly (Windows: ps -ef |
grep permuter, kill, verify zero — TaskStop alone leaves zombies, see
[[never-lose-uncommitted-work]] postmortems).


## rmz3-digestible-prs

*Upstream PRs must be digestible — small, single-entity, self-explanatory; user directive 2026-07-28*


User directive (2026-07-28, during the unclaimed-asm goal): "Make sure when
you start making PRs they are digestible."

**Why:** the maintainer reviews by hand; a PR bundling many files or mixing
matches with parks and struct changes is hard to verify and stalls merges
(79 open PRs already queue-heavy).

**How to apply:** when the decomp batches go to mmzret/rmz3 —
- one entity/file per PR (e.g. "decompile blizzack blizzard modes"), never
  a grab-bag across subsystems;
- separate PRs for header/struct changes when they touch shared files;
- PR body: what matched, what is parked and why (blocker in one line),
  how it was verified (full-ROM sha1 + CI);
- follow [[rmz3-upstream-port-workflow]] and [[rmz3-upstream-decomp-policy]]
  for conversion, and [[rmz3-push-target-and-scrub]] before pushing.
