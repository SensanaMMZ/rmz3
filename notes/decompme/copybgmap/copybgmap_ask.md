One instruction short (39 vs 40). The target copies **both** arguments into safe registers in the prologue, before any use:

    mov ip, r0        @ dst
    adds r4, r1, #0   @ src
    ldrb r6, [r4, #4]
    ldrb r7, [r4, #6]

agbcc instead reads through r1 directly and only parks `dst` in `ip` later, after the address arithmetic:

    ldrb r6, [r1, #4]
    ldrb r7, [r1, #6]
    adds r4, r1, #0
    ...
    mov ip, r0

Tried: copying both args to locals at the top; an `s64` temp for the offset (adds a copy, but the wrong one — goes to 41); recomputing the row pointer from `dst` inside the loop (49). None reproduce the early prologue copies.

Is there a source shape that makes GCC 2.9 spill both incoming argument registers to `ip`/`r4` up front? agbcc, `-mthumb-interwork -O2 -fshort-enums`.
