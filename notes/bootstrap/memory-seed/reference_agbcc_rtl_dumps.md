---
name: reference_agbcc_rtl_dumps
description: agbcc supports GCC2 -da RTL pass dumps — how to trace why a pass picks a register or emits an insn
metadata: 
  node_type: memory
  type: reference
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

agbcc (the in-repo `tools/agbcc/bin/agbcc`) is GCC 2.7.2.2-based and **supports
the `-da` "dump all passes" flag**. Add `-da` to the agbcc invocation and it
writes one file per RTL pass next to the `-o` target:

`<out>.rtl .jump .cse .loop .cse2 .gcse .flow .combine .regmove .lreg .greg .jump2 .mach .addressof`

Pass order (each is the RTL *after* that pass): rtl(gen) → jump → cse → loop →
cse2 → gcse → flow → combine → regmove → **lreg**(local alloc) → **greg**(global
alloc + reload) → jump2 → mach(final) → asm.

**How to use it** (this is how the beetank mechanism was cracked):
```
cpp <CPPFLAGS> file.c | tools/agbcc/bin/agbcc <CFLAGS> -da -o /scratch/out.s -
# then trace an instruction back to its birth pass:
for d in rtl cse2 combine lreg greg mach; do echo "$d: $(grep -c ashiftrt /scratch/out.i.$d)"; done
```
- An insn present in `.rtl` and surviving to `.mach` = born at RTL-generation
  (from the C itself), not introduced by optimization → no later pass removes it.
- Register *choice* (which hard reg a pseudo gets) is decided in `.lreg`/`.greg`;
  redundant *copies* are inserted/removed by `regmove` and the coalescer.

CPPFLAGS/CFLAGS to mirror the real build: see `tools/permuter-setup/*/compile.sh`
(`-DMODERN=0 -D__attribute__(x)=` for pycparser sources; `-O2 -fshort-enums
-fhex-asm -mthumb-interwork`). Dumps for the whole file are large — grep for the
target insn / `r8` / the callee name to find the relevant block.

Related: [[reference_agbcc_coalescer_theorem]] (the beetank/holdout-class result this technique produced), [[reference_agbcc_match_idioms]].

**2026-07-14 — RTL dump nailed the IsInHazard near-match root cause (definitive, no fix).** Compiled the direct-index reconstruction with `-da` (dumps land next to `-o`: pp.c.greg/.lreg/.mach/etc). The `.greg` prologue insn `(set (reg/v:SI 3 r3) (reg:SI 0 r0))` proves **z is allocated to caller-saved r3, not r4**. The `.greg` header shows WHY: **8 long-lived pseudos** (25=z live_length 88, 38, 30, 35, 24, 23, 78, 45 = z+x+y+gOverworld+sl+sb+count+**loop-invariant-hoisted z->hazard base**) compete for only **7 callee-saved regs (r4-r10)**. Allocation is priority-ordered (short-lived/high-ref first); z has the LONGEST live range so it's allocated late and the 7 callee-saved are already taken → z falls to r3. That freed callee-saved is exactly what lets loop.c hoist the z->hazard base. Self-reinforcing: hoist→z-to-r3→frees reg→hoist affordable. The target has only 7 long-lived values (recomputes z+0x15c each iter, no hoist) so z→r4. The hoist is a gcc2 loop-invariant-motion decision made BEFORE regalloc, on register-pressure estimates; agbcc has no per-function opt pragma and the file-wide flags are fixed at -O2, so there is NO C-level lever — verified across pin/count-local/inline/live-range variants (all cascade or re-trigger the hoist). **Takeaway: when a near-match differs only by which arg lands in a callee-saved reg, check `.greg` for N-long-lived-pseudos-vs-7-callee-saved; if the extra pseudo is a loop.c hoist you can't steer, it's an intrinsic tie — stop.** Reusable recipe: `cd <tmp>; cpp ... > pp.c; agbcc <flags> -da -o out.s pp.c; sed -n '/;; Function FN/,/;; Function/p' pp.c.greg`.
