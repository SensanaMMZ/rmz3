# zeroMinigamePhase1 (rmz3, agbcc) — 270/271 insns, two registers left

Byte-identical everywhere except two `movs rX,#8` scratch registers, in the
two arms of one if/else:

    retail arm A: movs r3,#8 ; ldrsh r0,[r4,r3] ... ldr r2,=0x2EE000
    retail arm B: movs r2,#8 ; ldrsh r0,[r4,r2] ... ldr r3,=0x2DF000
    mine    arm A: movs r2,#8 ... ldr r2,=0x2EE000   (temp shares the const's reg)
    mine    arm B: movs r3,#8 ... ldr r3,=0x2DF000

Background: the two arms are the same 11 instructions with one constant
swapped, so agbcc cross-jumps them into one unless they differ. Retail
escaped because its allocator happened to pick *different* registers per arm.
Pinning the constant per arm (`register s32 k asm("r2")` vs `asm("r3")`,
each with a zero-byte barrier so the pin actually binds on a pool constant)
stops the merge — but a hard-pinned local is not in the allocator's pool, so
the `ldrsh` reload temp then reuses that same hard register once the pin's
live range ends. Retail's temp is a pseudo and lands elsewhere.

Question: is there a way to influence the register chosen for the index
operand of `ldrsh rd,[rb,rIndex]` without adding instructions? Every attempt
to name it (a pinned `ix` used as `*(s16*)((u8*)g + ix)`) defeats the fold and
costs +2 per site.
