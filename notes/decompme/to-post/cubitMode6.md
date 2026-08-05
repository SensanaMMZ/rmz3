# cubitMode6 (rmz3, agbcc) — 282/304 insns, one branch left

Everything matches except the marked conditional in case 5:

    retail:  cmp r0,#9 ; bls <epilogue> ; b <inc>
    mine:    cmp r0,#9 ; bhi <over> ; b <inc> ; over: b <epilogue>

The branch sits almost exactly on the Thumb +-254 conditional range boundary
(retail's displacement is 232; mine computes 236 because the long form itself
adds 2 bytes plus a 2-byte pool pad). Writing `if (x <= 9) break; goto inc;`
gives retail's polarity but the long-form fixup (+2 bytes); the mirrored
source gives the short form with the wrong mnemonic (-2 bytes). Removing
every inline-asm barrier between the branch and the epilogue did not move it,
so this is genuine shorten-branches pessimism rather than the usual
"asm counts as nonzero length" trap.

Question: is there a source form that makes agbcc emit `bls <far>` directly
here, or a way to shave 2 bytes elsewhere in the function without changing
the emitted bytes?

Also of note: the `if (bit) flags |= K; else flags &= ~K;` blocks needed a
plain (non-`register`) temp for the tested value or agbcc deletes the `else`
arm entirely.
