// FUN_080ee328 near-miss seed (palette brightness LUT remap, -O2). Logic exact;
// off by register-allocation DIRECTION in the tight 8-reg loop: agbcc homes the
// loop-carried pal/length/mask into callee-saved regs (+arg copies +lr push)
// whereas the target keeps them in the arg regs r0/r1/r2 and uses r4-r7 for the
// per-iteration temps. Permuter target: shift that allocation.
static void FUN_080ee328(u32* pal, u32 length, u32 r2, u16* lut) {
  length >>= 1;
  do {
    u32 c = *pal;
    c = (c & r2) + ((c >> 0xA) & r2) + ((c >> 5) & r2);
    *pal = (lut[(c >> 0x10) & 0x7F] << 0x10) | lut[c & 0x7F];
    pal++;
  } while (--length != 0);
}
