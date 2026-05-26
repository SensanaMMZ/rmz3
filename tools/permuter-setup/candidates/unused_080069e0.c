// Stuck at permuter score 70 across multiple runs. The diff: orig keeps
// inner ptr in r0 (computed via in-place add), counter in r1, "next y"
// in r2 — and computes "next y" BEFORE entering the inner loop. Mine
// puts inner ptr in r1, counter in r2, "next y" in r0 (or similar).
// `register asm("r4/r5/r6")` pins for a/b/dst don't fix it; the inner
// loop allocator chooses different regs each time. Needs permuter time
// or a structural rewrite that nudges agbcc's allocator.
static void unused_080069e0(u32* dst, u32* src, u16 idx) {
  register u32* d asm("r6") = dst;
  register u32 a asm("r5") = src[idx * 2];
  register u32 b asm("r4") = src[idx * 2 + 1];
  s32 y = 0;
  do {
    u32* p = (u32*)((u8*)d + y * 128);
    s32 x = 15;
    do {
      *p = a;
      *(u32*)((u8*)p + 0x40) = b;
      p++;
    } while (--x >= 0);
  } while (++y <= 15);
}
