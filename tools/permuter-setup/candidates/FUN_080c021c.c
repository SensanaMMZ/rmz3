// Sine-modulated coordinate animator. Orig has two interesting patterns:
//  1. `lsls r1, #26; lsrs r1, #23` for the (rng & 0x3F) << 3 index — agbcc
//     fuses mask-and-shift if the expression is bit-extract shaped.
//  2. Dead `cmp r2, #0; bge; adds r0, #0x40` branch in the signed `%`
//     for `phase + 1`. agbcc emits this when the input is signed and
//     could be negative; my u8/s32 rephrasings all let agbcc elide it.
void FUN_080c021c(struct VFX* vfx) {
  struct CyberelfParticle* p = (struct CyberelfParticle*)vfx;
  s32 r = p->rng;
  (p->s).coord.x = p->x + (s16)gSineTable[(r & 0x3F) * 4] * 2;
  p->rng = (p->rng + 1) % 64;
}
