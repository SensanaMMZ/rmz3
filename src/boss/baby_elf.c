#include "boss.h"
#include "collision.h"
#include "entity.h"
#include "global.h"
#include "zero.h"
#include "palette_animation.h"
#include "overworld.h"

static const BossFunc sDeinitializers[2];

void FUN_08045b68(struct Boss* p);

// 0x08045b68
void FUN_08045b68(struct Boss* p) {
  if ((p->s).work[0] == 0) {
    u8* q = (u8*)p + 0xd0;
    switch (*q) {
      case 0:
        if (*((u8*)p + 0xcf) != 0) {
          StartPaletteAnimation(0x19, 0x320);
          StepPaletteAnimation(0x19);
          (*q)++;
        }
        break;
      case 1: {
        u8 t;
        StepPaletteAnimation(0x19);
        t = *((u8*)p + 0xcf);
        if (t == 0) {
          RemovePaletteAnimation(0x19);
          *q = t;
        }
        break;
      }
    }
  }
}

// 0x08045BC4
void babyelf_08045bc4(struct Boss* p0) {
  register struct Boss* p asm("ip");
  register u32* rp asm("r6");
  register const u8* tbl asm("r8");
  register u8* c5 asm("r5");
  register u8* c4 asm("r4");
  s32 idx;
  register struct Boss* pt asm("sb");
  register u32 b asm("r3");
  register s32 sh asm("r2");
  register const u8* q asm("r0");
  register u8 v asm("r1");
  p = p0;
  pt = *(struct Boss**)((u8*)p + 0x2c);
  idx = 0;
  if (*(s16*)((u8*)p + 0xa4) <= 0x2f) {
    idx = 1;
  }
  {
    register struct Boss* pp asm("r2");
    pp = p;
    idx += (pp->s).work[1] * 2;
  }
  c4 = (u8*)p + 0xcd;
  rp = &RNG_0202f388;
  asm("" : "+r"(rp));
  c5 = (u8*)p + 0xcc;
  tbl = (const u8*)0x083626D4;
  asm("" : "+r"(tbl));
  do {
    u32 rv;
    {
      register u32 rnd asm("r1");
      register u32 acc asm("r0");
      rnd = *rp;
      acc = 0x343FD;
      acc *= rnd;
      acc += 0x269EC3;
      rv = acc << 1;
      asm("" : "+r"(rv));
      *rp = rv >> 1;
    }
    {
      register s32 m asm("r0");
      b = rv >> 0x11;
      m = 0xF;
      b &= m;
    }
    asm("" : "+r"(idx));
    sh = idx << 4;
    q = (const u8*)(b + sh);
    asm volatile("add %0, %1" : "+l"(q) : "r"(tbl));
  } while (*c5 == *q && *c4 > 1);
  asm("" : "+r"(b), "+r"(sh));
  q = (const u8*)(b + sh);
  asm volatile("add %0, %1" : "+l"(q) : "r"(tbl));
  v = *q;
  if (*c5 == v) {
    *c4 = *c4 + 1;
  } else {
    register s32 zz asm("r0");
    zz = 0;
    *c5 = v;
    *c4 = zz;
  }
  asm("" : "+r"(b), "+r"(sh));
  q = (const u8*)(b + sh);
  asm volatile("add %0, %1" : "+l"(q) : "r"(tbl));
  v = *q;
  if (v == 1) {
    return;
  }
  {
    register struct Boss* pp asm("r2");
    pp = p;
    (pp->s).mode[1] = v;
  }
  {
    u8 w;
    w = *q;
    if (w == 5) {
      u8 six;
      register struct Boss* pr asm("r1");
      asm volatile("");
      six = 6;
      pr = pt;
      (pr->s).mode[1] = six;
    } else {
      register struct Boss* pq asm("r2");
      pq = pt;
      (pq->s).mode[1] = w;
    }
  }
  {
    register s32 z asm("r0");
    z = 0;
    {
      register struct Boss* pa asm("r1");
      pa = p;
      (pa->s).mode[2] = z;
    }
    {
      register struct Boss* pb asm("r2");
      pb = pt;
      (pb->s).mode[2] = z;
    }
  }
}


// 0x08045C84
NON_MATCH void babyelf_08045c84(struct Boss* p0) {
#if MODERN
  register struct Boss* p asm("ip");
  register u8* q asm("r0");
  register s32 x asm("r1");
  register s32 y asm("r4");
  register s32 a asm("r3");
  p = p0;
  q = (u8*)p + 0xbc;
  x = *(s32*)q;
  q = (u8*)p;
  *(s32*)(q + 0x54) = x;
  asm volatile("add %0, #0xc0" : "+r"(q));
  y = *(s32*)q;
  {
    register struct Boss* pp asm("r2");
    pp = p;
    (pp->s).coord.y = y;
  }
  asm volatile("add %0, #4" : "+r"(q));
  a = *(u16*)q & 0x1FF;
  if (a <= 0xFF) {
    register const s16* t asm("r2");
    t = gSineTable;
    asm("" : "+r"(t));
    (p->s).coord.x = x + (t[(u8)a] << 4);
    y += -0x1000;
    (p->s).coord.y = y;
    y += t[(u8)(a + 0x40)] << 4;
  } else {
    register const s16* t asm("r2");
    a += -0x100;
    t = gSineTable;
    asm("" : "+r"(t) : "r"(x));
    (p->s).coord.x = x + (t[(u8)a] << 4);
    y += 0x1000;
    (p->s).coord.y = y;
    y -= t[(u8)(a + 0x40)] << 4;
  }
  (p->s).coord.y = y;
#else
  INCCODE("asm/boss/babyelf_08045c84.inc");
#endif
}

void FUN_08045d28(struct Body* body) {
  struct Entity* self = (struct Entity*)body->parent;
  if (body->hitboxFlags & 1) {
    if (self->work[0] == 1) {
      struct Entity* par = self->unk_28;
      u16* pf = (u16*)((u8*)par + 0xa4);
      u16* sf;
      s32 v = *pf - 0x60;
      sf = (u16*)((u8*)self + 0xa4);
      *pf = v + *sf;
      *sf = 0x60;
    }
  }
}

void BabyElf_Die(struct Boss* p);

// 0x08045d54
bool8 FUN_08045d54(struct Boss* p) {
  if ((p->s).work[0] == 0 && (p->body).hp <= 0) {
    struct Boss* q;
    register s32 f asm("r5");
    u8 m1;
    u8 v;
    PlaySound(0x119);
    {
      register u16 st asm("r2");
      register s32 one asm("r5");
      register u8 av asm("r1");
      st = gStageRun.missionStatus;
      one = 1;
      if ((one & st) != 0) {
        register s32 res asm("r0");
        av = gStageRun.vm.active;
        res = one & av;
        asm volatile("" ::"r"(one));
        if (res == 0) {
          gStageRun.missionStatus = (st & 0xFFFE) | 0x10;
        }
      }
    }
    q = (struct Boss*)(p->s).unk_2c;
    f = 0;
    m1 = (p->s).mode[1];
    if ((u8)(m1 - 8) <= 2 || m1 == 0x10) {
      f = 1;
    }
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    SET_BOSS_ROUTINE(q, ENTITY_DIE);
    if (f != 0) {
      v = 0;
      asm("" : "+r"(v));
    } else {
      v = 1;
    }
    (p->s).mode[1] = v;
    (q->s).mode[1] = v;
    BabyElf_Die(p);
    return TRUE;
  }
  return FALSE;
}


INCASM("asm/boss/baby_elf_p1_pre_p2_p1.inc");

extern const BossFunc sUpdates1[19];
extern const BossFunc sUpdates2[19];
bool8 FUN_08045d54(struct Boss* p);

void BabyElf_Update(struct Boss* p) {
  FUN_08045b68(p);
  if (!FUN_08045d54(p)) {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

void BabyElf_Die(struct Boss* p) {
  FUN_08045b68(p);
  (sDeinitializers[(p->s).mode[1]])(p);
}

void nop_08046150(struct Boss* p) {}

INCASM("asm/boss/baby_elf_p2_p1.inc");

static const struct Collision sCollisions[5];
u8 GetEntityPalID(struct Entity* p);
void babyelf_08045bc4(struct Boss* p);
void babyelf_08045c84(struct Boss* p);
void FUN_080bc594(s32 x1, s32 y1, s32 x2, s32 y2, u8 n);

// The palette-argument half of this park is SOLVED (2026-07-31): a transfer-asm
// copy of the 0x200 const plus a cast-call that drops the u16 truncation now
// reproduces retail's per-arm adds-copy - see rmz3-set-flip-macro-fold. What
// still differs is a separate defect in the table-index block near 0x080467A8:
// retail folds the pool base into the index arithmetic and keeps the sum in r4
// (`adds r4,r0,r1`), ours adds the base to the loaded halfword instead;
// 7 instructions short overall. Retry from here, not from scratch.
NON_MATCH void babyelf_0804662c(struct Boss* p) {
#if MODERN
  u8 m2 = (p->s).mode[2];
  u32 k2h;
  if (m2 == 0) {
    goto c0;
  }
  if (m2 == 1) {
    goto c1;
  }
  return;
c0:
  {
    SetMotion(&p->s, 0x3100);
    *(s32*)((u8*)p + 0xbc) = (p->s).coord.x;
    *(s32*)((u8*)p + 0xc0) = (p->s).coord.y;
    (p->s).work[2] = m2;
    *(u16*)((u8*)p + 0xc4) = m2;
    if ((p->s).work[0] == 0) {
      u32 v = GetEntityPalID(&p->s);
      u32 sv = ((u32)(u8)v) << 5;
      u32 k = 0x200;
      u32 kc;
      asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
      ((void (*)(u16, u32))StartPaletteAnimation)(0x14, sv | kc);
      *((u8*)p + 0xc6) = 0x14;
    } else {
      u32 v = GetEntityPalID(&p->s);
      u32 sv = ((u32)(u8)v) << 5;
      u32 k = 0x200;
      u32 kc;
      asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
      ((void (*)(u16, u32))StartPaletteAnimation)(0xF, sv | kc);
      *((u8*)p + 0xc6) = 0xF;
    }
    {
      u32 s2 = 0;
      if ((p->s).coord.x > *(s32*)((u8*)p + 0xb4)) {
        s2 = 1;
      }
      *((u8*)p + 0xc7) = s2;
    }
    (p->s).mode[2]++;
  }
c1:
  k2h = 0x200;
  asm("" : "+r"(k2h));
  SetDDP(&p->body, &sCollisions[1]);
  {
    u16* pc4 = (u16*)((u8*)p + 0xc4);
    u8* pc7 = (u8*)p + 0xc7;
    s32 d4 = (*pc7 * 6) + 0xFFFD + *pc4;
    *pc4 = d4;
    if ((p->s).work[0] == 0) {
      struct Zero* z = pZero2;
      if ((*(u32*)((u8*)z + 0x8c) & k2h) == 0 && *(s16*)((u8*)z + 0xa4) != 0) {
        u16 dd = (u16)d4;
        if ((dd <= 0xFDFF && *pc7 == 0) || (dd > k2h && *pc7 == 1)) {
          babyelf_08045bc4(p);
        }
      }
    }
  }
  babyelf_08045c84(p);
  (p->s).work[2]++;
  if ((u8)((p->s).work[2] % 7) == 0) {
    u32 a = RNG_0202f388;
    u32 r1v = (a * 0x343FD + 0x269EC3) << 1;
    u32 s1;
    s32 x;
    s32 y;
    u32 r2v;
    asm("" : "+r"(r1v));
    s1 = r1v >> 1;
    x = (p->s).coord.x + (s32)((r1v << 4) >> 21) + -0x400;
    r2v = (s1 * 0x343FD + 0x269EC3) << 1;
    asm("" : "+r"(r2v));
    RNG_0202f388 = r2v >> 1;
    y = (p->s).coord.y + (s32)((r2v << 5) >> 22) + 0x800;
    FUN_080bc594(x, y, 0, 0, (p->s).work[0]);
  }
  StepPaletteAnimation(*((u8*)p + 0xc6));
  UpdateMotionGraphic(&p->s);
#else
  INCCODE("asm/boss/baby_elf_662c.inc");
#endif
}

INCASM("asm/boss/baby_elf_67c4.inc");

void FUN_080bc5fc(struct Entity* e, u8 n);
void FUN_080bc660(s32 x, s32 y);
void FUN_0809f8fc(s32 x, s32 y, u8 n);
u8 GetEntityPalID(struct Entity* p);

// 0x08046A7C
void babyelf_08046a7c(struct Boss* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8* q asm("r6");
      u32 v, sv, k, kc;
      s32 n;
      q = (u8*)p + 0xc6;
      if (*q != 0) {
        RemovePaletteAnimation(*q);
        *q = m;
      }
      if ((p->s).work[0] == 0) {
        {
          register s32 rv asm("r0");
          rv = ((s32 (*)(struct Entity*))GetEntityPalID)(&p->s);
          asm volatile("add %0, %1, #0" : "=l"(v) : "l"(rv));
        }
        v <<= 24;
        sv = (u32)v >> 0x13;
        k = 0x80 << 2;
        asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
        ((void (*)(u16, u32))StartPaletteAnimation)(0x15, sv | kc);
        n = 0x15;
      } else {
        {
          register s32 rv asm("r0");
          rv = ((s32 (*)(struct Entity*))GetEntityPalID)(&p->s);
          asm volatile("add %0, %1, #0" : "=l"(v) : "l"(rv));
        }
        v <<= 24;
        sv = (u32)v >> 0x13;
        k = 0x80 << 2;
        asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
        ((void (*)(u16, u32))StartPaletteAnimation)(0x10, sv | kc);
        n = 0x10;
      }
      *q = n;
      *(u16*)((u8*)p + 0xc4) = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register u16* acc asm("r2");
      register u8* dir asm("r3");
      u32 nv;
      acc = (u16*)((u8*)p + 0xc4);
      dir = (u8*)p + 0xc7;
      {
        register u32 d asm("r1");
        register s32 step asm("r0");
        u32 t;
        d = *dir;
        step = (s32)((d * 2 + d) * 2) + 0xFFFD;
        t = step + *acc;
        *acc = t;
        nv = (u16)t;
      }
      if (nv <= 0xFF7F) {
        if (*dir == 0) {
          goto inc;
        }
      }
      if (nv > 0x80) {
        if (*dir == 1) {
        inc:
          (p->s).mode[2]++;
        }
      }
      babyelf_08045c84(p);
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      register u8* q asm("r5");
      register s32 z asm("r6");
      u32 v, sv, k, kc;
      s32 sx;
      s32 sy;
      PlaySound(0x8b << 1);
      {
        u8* c8 = (u8*)p + 0xc8;
        z = 0;
        *c8 = z;
      }
      FUN_080bc5fc(&p->s, 0);
      q = (u8*)p + 0xc6;
      if (*q != 0) {
        RemovePaletteAnimation(*q);
        *q = z;
      }
      *((u8*)p + 0x22) = z;
      SetMotion(&p->s, 0x3301);
      z = (p->s).work[0];
      if (z == 0) {
        {
          register s32 rv asm("r0");
          rv = ((s32 (*)(struct Entity*))GetEntityPalID)(&p->s);
          asm volatile("add %0, %1, #0" : "=l"(v) : "l"(rv));
        }
        v <<= 24;
        sv = (u32)v >> 0x13;
        k = 0x80 << 2;
        asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
        ((void (*)(u16, u32))StartPaletteAnimation)(0x18, sv | kc);
        {
          u8 pa = 0x18;
          *q = pa;
          StepPaletteAnimation(pa);
        }
        if (*q != 0) {
          RemovePaletteAnimation(*q);
          *q = z;
        }
      }
      if (*((u8*)p + 0xc7) == 0) {
        (p->s).d.x = ((gSineTable[0x50] * 7) << 7) / 256;
        sy = gSineTable[0x10];
      } else {
        (p->s).d.x = ((gSineTable[0xd8] * 7) << 7) / 256;
        sy = gSineTable[0x98];
      }
      (p->s).d.y = -(((sy * 7) << 7) / 256);
      (p->s).work[2] = 0xa;
      (p->s).work[3] = 0x1a;
      (p->s).unk_coord.x = 0x5a;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 t = (p->s).unk_coord.x - 1;
      (p->s).unk_coord.x = t;
      if (t == 0) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = t;
      }
      if ((p->s).work[0] == 0) {
        if ((p->s).work[2] != 0) {
          s32 a = (p->s).work[2] - 1;
          (p->s).work[2] = a;
          if ((a << 24) == 0) {
            FUN_080bc660(*(s32*)((u8*)p + 0xb4), *(s32*)((u8*)p + 0xb8) - 0x5000);
          }
        }
        if ((p->s).work[3] != 0) {
          s32 b = (p->s).work[3] - 1;
          (p->s).work[3] = b;
          if ((b << 24) == 0) {
            register s32 i asm("r5");
            s32* xp;
            s32* yp;
            i = 0;
            xp = (s32*)((u8*)p + 0xb4);
            yp = (s32*)((u8*)p + 0xb8);
            do {
              {
                s32 xv = *xp;
                s32 yv = *yp - 0x5000;
                ((void (*)(s32, s32, s32))FUN_0809f8fc)(xv, yv, (s32)((u32)(i << 29) >> 24));
              }
              i++;
            } while (i <= 7);
          }
        }
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}


u8 GetEntityPalID(struct Entity* p);

// 0x08046ccc -- baby elf: fly to the anchor point, then glow (palette anim
// 0x16/0x11 by variant) and hand off. Blocker (reassociation/materialization
// basin): the -0x5800 approach constant lands r1 vs r3, and the coord.y+0x5000
// sum keeps reassociating into a pooled -0x5000 with an early dereference;
// barriers and pins shuffle neighbors without converging.
NON_MATCH void FUN_08046ccc(struct Boss* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      u32 s4 = 0;
      s32* pb = (s32*)((u8*)p + 0xb4);
      u8* ps;
      if ((p->s).coord.x > *pb) {
        s4 = 1;
      }
      ps = (u8*)p + 0xc7;
      *ps = s4;
      {
        s32 v = *pb + -0xB000;
        (p->s).coord.x = v;
        v += *ps * 0x16000;
        (p->s).coord.x = v;
      }
      {
        s32 w = *(s32*)((u8*)p + 0xb8) + 0x3000;
        (p->s).coord.y = w;
        w -= *ps << 16;
        (p->s).coord.y = w;
      }
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 cx, cy, t, u;
      (p->s).flags |= 1;
      t = *(s32*)((u8*)p + 0xb4);
      cx = (p->s).coord.x;
      t -= cx;
      t += -0x5800;
      t += *((u8*)p + 0xc7) * 0xB000;
      cy = (p->s).coord.y;
      u = *(s32*)((u8*)p + 0xb8) - (cy + 0x5000);
      (p->s).coord.x = cx + t / 12;
      (p->s).coord.y = cy + u / 12;
      UpdateMotionGraphic(&p->s);
      {
        s32 t2 = (p->s).work[2] - 1;
        (p->s).work[2] = t2;
        if ((t2 << 24) == 0) {
          *((u8*)p + 0xc8) = 1;
          (p->s).mode[2]++;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).palID = (p->s).work[0];
      SetMotion(&p->s, 0x3100);
      if ((p->s).work[0] == 0) {
        StartPaletteAnimation(0x16, ((u32)GetEntityPalID(&p->s) << 5) | 0x200);
        *((u8*)p + 0xc6) = 0x16;
      } else {
        StartPaletteAnimation(0x11, ((u32)GetEntityPalID(&p->s) << 5) | 0x200);
        *((u8*)p + 0xc6) = 0x11;
      }
      (p->s).mode[2]++;
      // fallthrough
    case 3: {
      u8* pc6 = (u8*)p + 0xc6;
      if ((u8)StepPaletteAnimation(*pc6) == 3) {
        u32 v = *pc6;
        if (v != 0) {
          RemovePaletteAnimation(v);
          *pc6 = 0;
        }
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/boss/baby_elf_6ccc.inc");
#endif
}

INCASM("asm/boss/baby_elf_p2_p1_post.inc");

void babyelf_0809f9f0(struct Entity* parent, s32 x, s32 y, u8 n);

// 0x08047184
// Exactly retail's 436 bytes; ~12 instructions differ, all register-number ties
// clustered on the `0xc4`/`0xc7` props pointers and the `ldrsh` index register.
// The two things that DID have to be right: the pointers must be block-scoped
// per case (hoisting them to function scope costs 16 bytes), and the `0xFFFD`
// addend is CSE'd between case 0 and case 2 where retail loads it from two pool
// entries -- §6.178.  Making case 2's copy opaque fixes the size but rotates
// r2/r3 to r3/r4; making case 0's copy opaque instead rotates a different pair.
// The RNG/FUN_080bc594 tail and the `(*pc7 * 6) + 0xFFFD + *pc4` idiom are taken
// verbatim from the matched sibling babyelf_0804662c above -- reuse them.
NON_MATCH void babyelf_08047184(struct Boss* p) {
#if MODERN
  struct Entity* q = (p->s).unk_28;

  switch ((p->s).mode[2]) {
    case 0: {
      u16* c4;
      u32 kfd = 0xFFFD;
      *((u8*)p + 0xc9) = 0;
      c4 = (u16*)((u8*)p + 0xc4);
      asm("" : "+l"(kfd));
      *c4 = (*((u8*)p + 0xc7) * 6) + kfd + *c4;
      if (*((u8*)q + 0xc9) != 0) {
        (p->s).mode[2]++;
      }
      babyelf_08045c84(p);
      goto tail;
    }
    case 1: {
      u16* c4 = (u16*)((u8*)p + 0xc4);
      s32 a = *(s16*)c4;
      *c4 = a % 512;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 2: {
      u16* pc4 = (u16*)((u8*)p + 0xc4);
      u8* pc7 = (u8*)p + 0xc7;
      s32 d4;
      u16 dd;
      d4 = (*pc7 * 6) + 0xFFFD + *pc4;
      *pc4 = d4;
      dd = (u16)d4;
      if ((dd <= 0xFE7F && *pc7 == 0) || (dd > 0x80 && *pc7 == 1)) {
        (p->s).mode[2]++;
      }
      babyelf_08045c84(p);
      goto tail;
    }
    case 3:
      PlaySound(0x114);
      (p->s).unk_coord.x = 0;
      (p->s).work[3] = 8;
      (p->s).mode[2]++;
      /* fallthrough */
    case 4:
      (p->s).work[3]--;
      if (((p->s).work[3] << 24) != 0) {
        goto tail;
      }
      babyelf_0809f9f0(q, (p->s).coord.x, (p->s).coord.y, *((u8*)p + 0xc7));
      (p->s).work[3] = 8;
      (p->s).unk_coord.x++;
      if ((p->s).unk_coord.x <= 3) {
        goto tail;
      }
      *((u8*)p + 0xc9) = 1;
      (p->s).mode[2]++;
      break;
    case 5:
      if (q->mode[1] == 5) {
        goto tail;
      }
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 1;
      break;
  }
tail:
  (p->s).work[2]++;
  if ((u8)((p->s).work[2] % 7) == 0) {
    u32 a = RNG_0202f388;
    u32 r1v = (a * 0x343FD + 0x269EC3) << 1;
    u32 s1;
    s32 x;
    s32 y;
    u32 r2v;
    asm("" : "+r"(r1v));
    s1 = r1v >> 1;
    x = (p->s).coord.x + (s32)((r1v << 4) >> 21) + -0x400;
    r2v = (s1 * 0x343FD + 0x269EC3) << 1;
    asm("" : "+r"(r2v));
    RNG_0202f388 = r2v >> 1;
    y = (p->s).coord.y + (s32)((r2v << 5) >> 22) + 0x800;
    FUN_080bc594(x, y, 0, 0, (p->s).work[0]);
  }
  StepPaletteAnimation(*((u8*)p + 0xc6));
  UpdateMotionGraphic(&p->s);
#else
  INCCODE("asm/boss/baby_elf_47184.inc");
#endif
}

// 0x08047338
void babyelf_08047338(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      *(u16*)((u8*)p + 0xc4) = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register u16* acc asm("r2");
      register u8* dir asm("r3");
      register u32 nv asm("r1");
      acc = (u16*)((u8*)p + 0xc4);
      dir = (u8*)p + 0xc7;
      {
        register u32 d asm("r1");
        register s32 step asm("r0");
        register u32 av asm("r4");
        u32 t;
        d = *dir;
        step = d * 2;
        step += d;
        step *= 2;
        step += 0xFFFD;
        asm volatile("" : "+l"(step));
        av = *acc;
        t = step + av;
        *acc = t;
        nv = (u16)t;
      }
      {
        u32 lim = 0xFF7F;
        asm volatile("" : "+l"(lim));
        if (nv <= lim) {
          if (*dir == 0) {
            goto inc;
          }
        }
      }
      if (nv > 0x80) {
        if (*dir == 1) {
        inc:
          (p->s).mode[2]++;
        }
      }
      babyelf_08045c84(p);
      break;
    }
    case 2: {
      s32 cx;
      (p->s).work[3] = 0;
      (p->s).d.x = 0;
      cx = (p->s).coord.x;
      (p->s).unk_coord.x = cx;
      (p->s).unk_coord.x = cx - *(s32*)((u8*)p + 0xb4);
      {
        register s32 cy0 asm("r0");
        register s32 kk asm("r1");
        cy0 = (p->s).coord.y;
        (p->s).unk_coord.y = cy0;
        kk = 0xa0 << 7;
        asm volatile("" : "+l"(kk));
        cy0 += kk;
        kk = *(s32*)((u8*)p + 0xb8);
        cy0 -= kk;
        (p->s).unk_coord.y = cy0;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 a;
      register s32 nx asm("r3");
      register s32 ny asm("r2");
      register s32 ux asm("r4");
      register s32 uy asm("r2");
      register s32 cs asm("r5");
      register s32 sn asm("r1");
      register s32 pr asm("r0");
      s32 nx2;
      s32 ny2;
      if ((p->s).work[0] == 0) {
        u8 w = (p->s).work[3];
        w += 1;
        (p->s).work[3] = w;
        w = (p->s).work[3];
        w &= 0x1f;
        (p->s).work[3] = w;
        if (w <= 0xf) {
          (p->s).taskCol = 0x19;
        } else {
          (p->s).taskCol = 0x18;
        }
      }
      a = (p->s).d.x;
      {
        u32 sh = (u32)(a >> 8) << 24;
        register const s16* st asm("r2");
        st = gSineTable;
        asm("" : "+r"(st));
        sn = sh >> 24;
        cs = st[(sh + (0x80 << 23)) >> 24];
        ux = (p->s).unk_coord.x;
        {
          pr = cs * ux;
          if (pr < 0) {
            pr += 0xff;
          }
          nx = pr >> 8;
        }
        {
          register const s16* q asm("r0");
          q = (const s16*)((u8*)(sn << 1) + (s32)st);
          sn = *q;
        }
        uy = (p->s).unk_coord.y;
        {
          pr = sn * uy;
          if (pr < 0) {
            pr += 0xff;
          }
          nx += pr >> 8;
        }
        {
          s32 neg;
          pr = sn * ux;
          if (pr < 0) {
            pr += 0xff;
          }
          neg = -(pr >> 8);
          pr = cs * uy;
          if (pr < 0) {
            pr += 0xff;
          }
          ny = neg + (pr >> 8);
        }
      }
      (p->s).d.x = a + 0x14;
      (p->s).unk_coord.x = nx;
      (p->s).unk_coord.y = ny;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + nx;
      {
        s32* cp = (s32*)((u8*)p + 0xb8);
        s32 dy0 = ny + -0x5000;
        (p->s).coord.y = *cp + dy0;
      }
      nx2 = (((nx << 5) - nx) << 3) / 256;
      (p->s).unk_coord.x = nx2;
      ny2 = (((ny << 5) - ny) << 3) / 256;
      (p->s).unk_coord.y = ny2;
      if ((u32)(nx2 + (0x80 << 2)) > 0x3FF) {
        break;
      }
      if ((u32)(ny2 + (0x80 << 2)) > 0x3FF) {
        break;
      }
      {
        u8 w0 = (p->s).work[0];
        if (w0 == 0) {
          PlaySound(0x117);
          (p->s).mode[1] = 8;
          (p->s).mode[2] = w0;
        } else {
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 4: {
      register u8* q asm("r4");
      {
        u32 fv = (p->s).flags;
        u32 f = 0xfe;
        f &= fv;
        (p->s).flags = f;
      }
      SetDDP(&p->body, sCollisions);
      q = (u8*)p + 0xc6;
      if (*q != 0) {
        RemovePaletteAnimation(*q);
        *q = 0;
      }
      break;
    }
  }
  if ((p->s).mode[2] != 4) {
    (p->s).work[2]++;
    if ((u8)((p->s).work[2] % 7) == 0) {
      u32 a = RNG_0202f388;
      u32 r1v = (a * 0x343FD + 0x269EC3) << 1;
      u32 s1;
      s32 x;
      s32 y;
      u32 r2v;
      s32 rx;
      s32 ry;
      asm("" : "+r"(r1v));
      s1 = r1v >> 1;
      rx = (s32)((r1v << 4) >> 21) + -0x400;
      x = (p->s).coord.x + rx;
      r2v = (s1 * 0x343FD + 0x269EC3) << 1;
      asm("" : "+r"(r2v));
      RNG_0202f388 = r2v >> 1;
      ry = (s32)((r2v << 5) >> 22) + 0x800;
      y = (p->s).coord.y + ry;
      FUN_080bc594(x, y, 0, 0, (p->s).work[0]);
    }
    StepPaletteAnimation(*((u8*)p + 0xc6));
    UpdateMotionGraphic(&p->s);
  }
}

void FUN_080bc6ac(struct Entity* e, s32 x, s32 y, s32 speed, u8 angle);

// 0x080475A0
void babyelf_080475a0(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32 v, sv, k, kc;
      SetDDP(&p->body, (const struct Collision*)0x083626A4);
      (p->s).taskCol = 0x18;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4);
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) - 0x5000;
      SetMotion(&p->s, 0x3309);
      if (*((u8*)p + 0xc6) != 0) {
        RemovePaletteAnimation(*((u8*)p + 0xc6));
        *((u8*)p + 0xc6) = 0;
      }
      v = GetEntityPalID(&p->s);
      sv = ((u32)(u8)v) << 5;
      k = 0x200;
      asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
      ((void (*)(u16, u32))StartPaletteAnimation)(27, sv | kc);
      *((u8*)p + 0xc6) = 27;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      u32 v, sv, k, kc;
      SetMotion(&p->s, 0xd0 << 6);
      if (*((u8*)p + 0xc6) != 0) {
        RemovePaletteAnimation(*((u8*)p + 0xc6));
        *((u8*)p + 0xc6) = 0;
      }
      v = GetEntityPalID(&p->s);
      sv = ((u32)(u8)v) << 5;
      k = 0x200;
      asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
      ((void (*)(u16, u32))StartPaletteAnimation)(29, sv | kc);
      *((u8*)p + 0xc6) = 29;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
      if ((u8)StepPaletteAnimation(*((u8*)p + 0xc6)) == 3) {
        (p->s).mode[2]++;
      }
      goto upd;
    case 4: {
      u32 v, sv, k, kc;
      s32 i;
      (p->s).work[3] = 0x10;
      i = 0;
      do {
        ((void (*)(struct Entity*, s32, s32, s32, s32))FUN_080bc6ac)(
            &p->s, (p->s).coord.x, (p->s).coord.y, 0xe0 << 1, (s32)((u32)(i << 29) >> 24));
        i++;
      } while (i <= 7);
      if (*((u8*)p + 0xc6) != 0) {
        RemovePaletteAnimation(*((u8*)p + 0xc6));
        *((u8*)p + 0xc6) = 0;
      }
      v = GetEntityPalID(&p->s);
      sv = ((u32)(u8)v) << 5;
      k = 0x200;
      asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
      ((void (*)(u16, u32))StartPaletteAnimation)(30, sv | kc);
      *((u8*)p + 0xc6) = 30;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5: {
      s32 t;
      u8 tb;
      t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      tb = t;
      if (tb == 0) {
        if ((p->s).work[1] == 1) {
          (p->s).mode[1] = 0x10;
          (p->s).mode[2] = tb;
        } else {
          (p->s).mode[2]++;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 6: {
      s32 z = 0;
      (p->s).work[3] = 0x34;
      (p->s).d.y = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 7: {
      s32 t;
      u8 tb;
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      {
        u32 w3 = (p->s).work[3];
        if (w3 > 26) {
          (p->s).d.y -= 13;
        } else {
          (p->s).d.y += 13;
        }
      }
      t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      tb = t;
      if (tb == 0) {
        (p->s).mode[1] = 9;
        (p->s).mode[2] = tb;
      }
      (p->s).coord.y += (p->s).d.y;
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_0809fa44(struct Entity* parent, s32 x, s32 y, u8 n);

// 0x080477b8
void babyelf_080477b8(struct Boss* p) {
  register s32 m asm("r3");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      u16 h = (p->body).hp;
      s16* a = (s16*)((u8*)p + 0xca);
      s32 z = 0;
      *a = h;
      *(s32*)((u8*)p + 0xbc) = (p->s).coord.x;
      *(s32*)((u8*)p + 0xc0) = (p->s).coord.y;
      *(u16*)((u8*)p + 0xc4) = m;
      (p->s).work[2] = z;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      u16* ang = (u16*)((u8*)p + 0xc4);
      s32 bx;
      s32 by;
      s32 diff;
      (*ang)++;
      bx = *(s32*)((u8*)p + 0xbc);
      (p->s).coord.x = bx;
      by = *(s32*)((u8*)p + 0xc0);
      (p->s).coord.y = by;
      (p->s).coord.x = bx + gSineTable[*(u8*)ang] * 80;
      (p->s).coord.y = by - gSineTable[(u8)(*ang * 2)] * 16;
      (p->s).work[2]++;
      (p->s).work[2] = (p->s).work[2] % 0x60;
      diff = *(s16*)((u8*)p + 0xca) - (p->body).hp;
      if (diff > 0xF || ((pZero2->body).status & BODY_STATUS_DEAD) || (pZero2->body).hp == 0) {
        (p->s).mode[1] = 0xA;
        (p->s).mode[2] = 0;
      }
      if ((p->s).work[2] == 0) {
        PlaySound(0x118);
        FUN_0809fa44(&p->s, (p->s).coord.x, (p->s).coord.y, 0);
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080478B8
void FUN_080478b8(struct Boss* p) {
  register struct Entity* q asm("r6");
  register s32 z4 asm("r4");
  s32 z7;
  q = (p->s).unk_2c;
  z4 = (p->s).mode[2];
  switch (z4) {
    case 0: {
      register u8* pa asm("r6");
      pa = (u8*)p + 0xc6;
      if (*pa != 0) {
        RemovePaletteAnimation(*pa);
        *pa = z4;
      }
      {
        u32 v = GetEntityPalID(&p->s);
        u32 sv = ((u32)(u8)v) << 5;
        u32 k = 0x200;
        u32 kc;
        asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
        ((void (*)(u16, u32))StartPaletteAnimation)(0x1F, sv | kc);
      }
      *pa = 0x1F;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if ((u8)StepPaletteAnimation(*((u8*)p + 0xc6)) == 3) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2: {
      register s32 mo asm("r4");
      register u8* pa2 asm("r4");
      SetDDP(&p->body, (const struct Collision*)0x08362674);
      {
        u8* pp = (u8*)q + 0x22;
        z7 = 0;
        *pp = z7;
      }
      mo = MOTION(0x33, 0x0A);
      ((void (*)(struct Entity*, s32))SetMotion)(q, mo);
      ((void (*)(struct Entity*, s32))SetMotion)(&p->s, mo);
      pa2 = (u8*)p + 0xc6;
      if (*pa2 != 0) {
        RemovePaletteAnimation(*pa2);
        *pa2 = z7;
      }
      {
        u32 v = GetEntityPalID(&p->s);
        u32 sv = ((u32)(u8)v) << 5;
        u32 k = 0x200;
        u32 kc;
        asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
        ((void (*)(u16, u32))StartPaletteAnimation)(0x1C, sv | kc);
      }
      *pa2 = 0x1C;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      register u8* pa3 asm("r4");
      pa3 = (u8*)p + 0xc6;
      if ((u8)StepPaletteAnimation(*pa3) == 3) {
        register s32 z2 asm("r2");
        register s32 mv asm("r1");
        if (*pa3 != 0) {
          RemovePaletteAnimation(*pa3);
          *pa3 = 0;
        }
        z2 = 0;
        mv = 0xB;
        q->mode[1] = mv;
        q->mode[2] = z2;
        q->coord.x = (p->s).coord.x;
        q->coord.y = (p->s).coord.y;
        (p->s).mode[1] = mv;
        (p->s).mode[2] = z2;
      }
      UpdateMotionGraphic(&p->s);
      UpdateMotionGraphic(q);
      break;
    }
  }
  asm volatile("" ::"l"(z7));
}
INCASM("asm/boss/baby_elf_p2_p1b.inc");

// 0x08047e30
void babyelf_08047e30(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 z asm("r1");
      if ((RANDOM(RNG_0202f388) & 1) != 0) {
        PlaySound(0x8a << 1);
      } else {
        PlaySound(0x115);
      }
      z = 0;
      (p->s).work[3] = 0x30;
      (p->s).d.x = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 v asm("r1");
      v = (p->s).d.x - 0x10;
      (p->s).d.x = v;
      v += *((u8*)p + 0xc7) << 5;
      (p->s).d.x = v;
      (p->s).coord.x = (p->s).coord.x + v;
      {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) == 0) {
          (p->s).mode[2]++;
        }
      }
      (p->s).work[2]++;
      if ((u8)((p->s).work[2] % 7) == 0) {
        register u32* rp asm("r5");
        register u32 a asm("r0");
        register u32 k1 asm("r4");
        register u32 r1v asm("r1");
        register u32 k2 asm("r3");
        register u32 s1 asm("r2");
        register s32 x asm("r0");
        register s32 y asm("r1");
        rp = &RNG_0202f388;
        a = *rp;
        asm("" : "+r"(a));
        k1 = 0x343FD;
        r1v = a;
        r1v *= k1;
        k2 = 0x269EC3;
        r1v += k2;
        r1v <<= 1;
        s1 = r1v >> 1;
        r1v = (r1v << 4) >> 21;
        r1v += (u32)-0x400;
        x = (p->s).coord.x + (s32)r1v;
        s1 *= k1;
        s1 += k2;
        s1 <<= 1;
        *rp = s1 >> 1;
        s1 = (s1 << 5) >> 22;
        {
          register s32 k8 asm("r1");
          k8 = 0x80 << 4;
          asm volatile("add %0, %0, %1" : "+l"(s1) : "l"(k8));
        }
        y = (p->s).coord.y + (s32)s1;
        FUN_080bc594(x, y, 0, 0, (p->s).work[0]);
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetDDP(&p->body, sCollisions);
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + -0x2000;
      (p->s).work[3] = 0x30;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      register u32 u asm("r1");
      register s32 t asm("r0");
      t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      u = (u8)t;
      if (u == 0) {
        (p->s).mode[1] = 0xE;
        (p->s).mode[2] = u;
      }
      break;
    }
  }
}

// 0x08047F84
void FUN_08047f84(struct Boss* p) {
  register u8* q asm("r4");
  switch ((p->s).mode[2]) {
    case 0: {
      s32 v = 0xc0 << 2;
      u8 n;
      (p->s).d.x = v;
      q = (u8*)p + 0xc7;
      n = *q;
      v -= (n * 2 + n) << 9;
      (p->s).d.x = v;
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 nx = (p->s).coord.x + (p->s).d.x;
      q = (u8*)p + 0xc7;
      (p->s).coord.x = nx;
      if (*q == 0) {
        s32 lim = *(s32*)((u8*)p + 0xb4) - 0x5000;
        if (nx > lim) {
          (p->s).coord.x = lim;
          (p->s).mode[2]++;
        }
      }
      if (*q != 1) {
        break;
      }
      {
        s32 lim = *(s32*)((u8*)p + 0xb4) + (0xa0 << 7);
        if ((p->s).coord.x < lim) {
          (p->s).coord.x = lim;
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 2:
      (p->s).work[3] = 0x40;
      (p->s).unk_coord.x = 0x2a;
      {
        *(s32*)((u8*)p + 0xbc) = (p->s).coord.x;
        *(s32*)((u8*)p + 0xc0) = (p->s).coord.y - 0x1000;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s32 t = (p->s).unk_coord.x - 1;
      (p->s).unk_coord.x = t;
      if (t == 0) {
        (p->s).mode[2]++;
      }
      if (*((u8*)p + 0xc7) == 0) {
        (p->s).work[3] = (p->s).work[3] - 6;
      } else {
        (p->s).work[3] = (p->s).work[3] + 6;
      }
      {
        s32 bx = *(s32*)((u8*)p + 0xbc);
        (p->s).coord.x = bx;
        (p->s).coord.x = bx + gSineTable[(u8)((p->s).work[3] + 0x40)] * 16;
      }
      {
        s32 by = *(s32*)((u8*)p + 0xc0);
        (p->s).coord.y = by;
        (p->s).coord.y = by + gSineTable[(p->s).work[3]] * 16;
      }
      break;
    }
    case 4:
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5: {
      s32 nx = (p->s).coord.x + (p->s).d.x;
      u8* a;
      u8 n;
      (p->s).coord.x = nx;
      a = (u8*)p + 0xc7;
      n = *a;
      asm volatile("add %0, %1, #0" : "=&l"(q) : "l"(a));
      if (n == 0) {
        s32 lim = *(s32*)((u8*)a - 19) - 0x1000;
        if (nx > lim) {
          (p->s).coord.x = lim;
          (p->s).mode[1] = 0xf;
          (p->s).mode[2] = n;
        }
      }
      if (*q != 1) {
        break;
      }
      {
        register s32 base asm("r0");
        register s32 kc asm("r2");
        register s32 lim asm("r1");
        base = *(s32*)((u8*)p + 0xb4);
        kc = 0x80 << 5;
        asm volatile("" : "+l"(kc));
        lim = base + kc;
        asm volatile("" : : "l"(kc));
        if ((p->s).coord.x < lim) {
          s32 z;
          (p->s).coord.x = lim;
          z = 0;
          (p->s).mode[1] = 0xf;
          (p->s).mode[2] = z;
        }
      }
      break;
    }
  }
  (p->s).work[2]++;
  if ((u8)((p->s).work[2] % 7) == 0) {
    u32 a = RNG_0202f388;
    u32 r1v = (a * 0x343FD + 0x269EC3) << 1;
    u32 s1;
    s32 x;
    s32 y;
    u32 r2v;
    s32 rx;
    s32 ry;
    asm("" : "+r"(r1v));
    s1 = r1v >> 1;
    rx = (s32)((r1v << 4) >> 21) + -0x400;
    x = (p->s).coord.x + rx;
    r2v = (s1 * 0x343FD + 0x269EC3) << 1;
    asm("" : "+r"(r2v));
    RNG_0202f388 = r2v >> 1;
    ry = (s32)((r2v << 5) >> 22) + 0x800;
    y = (p->s).coord.y + ry;
    FUN_080bc594(x, y, 0, 0, (p->s).work[0]);
  }
  StepPaletteAnimation(*((u8*)p + 0xc6));
  UpdateMotionGraphic(&p->s);
}


// 0x08048190
void FUN_08048190(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      (p->s).work[3] = 0x40;
      (p->s).unk_coord.x = 0xa;
      *(s32*)((u8*)p + 0xbc) = (p->s).coord.x;
      *(s32*)((u8*)p + 0xc0) = (p->s).coord.y - 0x1000;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t = (p->s).unk_coord.x - 1;
      (p->s).unk_coord.x = t;
      if (t == 0) {
        (p->s).mode[2]++;
      }
      if (*((u8*)p + 0xc7) == 0) {
        (p->s).work[3] = (p->s).work[3] - 6;
      } else {
        (p->s).work[3] = (p->s).work[3] + 6;
      }
      {
        s32 bx = *(s32*)((u8*)p + 0xbc);
        (p->s).coord.x = bx;
        (p->s).coord.x = bx + gSineTable[(u8)((p->s).work[3] + 0x40)] * 16;
      }
      {
        s32 by = *(s32*)((u8*)p + 0xc0);
        (p->s).coord.y = by;
        (p->s).coord.y = by + gSineTable[(p->s).work[3]] * 16;
      }
      break;
    }
    case 2: {
      s32 ny = (p->s).coord.y - 0x300;
      (p->s).coord.y = ny;
      if (ny >= *(s32*)((u8*)p + 0xb8) - 0x5000) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 3: {
      u8* q = (u8*)p + 0xc7;
      s32* b;
      s32 v;
      u8 n;
      (p->s).work[3] = *q << 7;
      (p->s).unk_coord.x = 0x2a;
      b = (s32*)((u8*)p + 0xbc);
      v = (p->s).coord.x - 0x2C00;
      *b = v;
      n = *q;
      v += ((n * 2 + n) * 4 - n) << 11;
      *b = v;
      *(s32*)((u8*)p + 0xc0) = (p->s).coord.y;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 4: {
      s32 t = (p->s).unk_coord.x - 1;
      (p->s).unk_coord.x = t;
      if (t == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = t;
      }
      if (*((u8*)p + 0xc7) == 0) {
        (p->s).work[3] = (p->s).work[3] - 3;
      } else {
        (p->s).work[3] = (p->s).work[3] + 3;
      }
      {
        s32 bx = *(s32*)((u8*)p + 0xbc);
        (p->s).coord.x = bx;
        (p->s).coord.x = bx + gSineTable[(u8)((p->s).work[3] + 0x40)] * 0x2c;
      }
      {
        s32 by = *(s32*)((u8*)p + 0xc0);
        (p->s).coord.y = by;
        (p->s).coord.y = by + gSineTable[(p->s).work[3]] * 0x1D55 / 256;
      }
      break;
    }
  }
  (p->s).work[2]++;
  if ((u8)((p->s).work[2] % 7) == 0) {
    u32 a = RNG_0202f388;
    u32 r1v = (a * 0x343FD + 0x269EC3) << 1;
    u32 s1;
    s32 x;
    s32 y;
    u32 r2v;
    s32 rx;
    s32 ry;
    asm("" : "+r"(r1v));
    s1 = r1v >> 1;
    rx = (s32)((r1v << 4) >> 21) + -0x400;
    x = (p->s).coord.x + rx;
    r2v = (s1 * 0x343FD + 0x269EC3) << 1;
    asm("" : "+r"(r2v));
    RNG_0202f388 = r2v >> 1;
    ry = (s32)((r2v << 5) >> 22) + 0x800;
    y = (p->s).coord.y + ry;
    FUN_080bc594(x, y, 0, 0, (p->s).work[0]);
  }
  StepPaletteAnimation(*((u8*)p + 0xc6));
  UpdateMotionGraphic(&p->s);
}


void FUN_0809f8ac(struct Entity* e);

void FUN_0804839c(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[3] = 0x1E;
      *((u8*)p + 0xce) = 0;
      FUN_0809f8ac(&p->s);
      (p->s).mode[2]++;
    /* fallthrough */
    case 1: {
      s32 t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
    }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      {
        s32 v = (p->s).coord.x + -0x180;
        s32 l;
        (p->s).coord.x = v;
        l = *(s32*)((u8*)p + 0xb4) + -0x5000;
        if (v < l) {
          (p->s).coord.x = l;
          (p->s).mode[2]++;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 3:
      {
        s32 v = (p->s).coord.y + -0x180;
        s32 l;
        (p->s).coord.y = v;
        l = *(s32*)((u8*)p + 0xb8) + -0x7800;
        if (v < l) {
          (p->s).coord.y = l;
          (p->s).mode[2]++;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 4:
      {
        s32 v = (p->s).coord.x + 0x180;
        s32 l;
        (p->s).coord.x = v;
        l = *(s32*)((u8*)p + 0xb4) + 0x5000;
        if (v > l) {
          (p->s).coord.x = l;
          (p->s).mode[2]++;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 5:
      {
        s32 v = (p->s).coord.y + 0x180;
        s32 l;
        (p->s).coord.y = v;
        l = *(s32*)((u8*)p + 0xb8) + -0x3700;
        if (v > l) {
          (p->s).coord.y = l;
          (p->s).mode[2]++;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 6:
      {
        s32 v = (p->s).coord.x + -0x180;
        s32 l;
        (p->s).coord.x = v;
        l = *(s32*)((u8*)p + 0xb4) + -0x5000;
        if (v < l) {
          (p->s).coord.x = l;
          (p->s).mode[2]++;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 7:
      {
        s32 v = (p->s).coord.y + -0x180;
        s32 l;
        (p->s).coord.y = v;
        l = *(s32*)((u8*)p + 0xb8) + -0x7800;
        if (v < l) {
          (p->s).coord.y = l;
          (p->s).mode[2]++;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 8: {
      s32* pb;
      s32 v = (p->s).coord.x + 0x180;
      (p->s).coord.x = v;
      pb = (s32*)((u8*)p + 0xb4);
      if (v > *pb) {
        *((u8*)p + 0xce) = 1;
        (p->s).coord.x = *pb;
        (p->s).mode[2]++;
      }
    }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    case 9:
      (p->s).unk_coord.x = 0x12C;
      (p->s).mode[2]++;
    /* fallthrough */
    case 10: {
      s32 t = (p->s).unk_coord.x - 1;
      (p->s).unk_coord.x = t;
      if (t == 0) {
        (p->s).mode[1] = 0xA;
        (p->s).mode[2] = t;
      }
      StepPaletteAnimation(*((u8*)p + 0xc6));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/boss/baby_elf_p2_p1b_post839c.inc");

u16 FUN_080d08d0(struct Boss* p, motion_t m);

void FUN_0804874c(struct Boss* p) {
  s32 m = (p->s).mode[2];
  if (m != 1) {
    if (m > 1) {
      return;
    }
    if (m != 0) {
      return;
    }
    (p->s).mode[2] = 1;
  }
  if (FUN_080d08d0(p, 0x3000)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).mode[2]++;
  }
}

void FUN_08048788(struct Boss* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->body).status = m;
      (p->body).prevStatus = m;
      (p->body).invincibleTime = m;
      {
        u32 f = (p->s).flags & 0xFB;
        asm("" : "+r"(f));
        (p->s).flags = f | 1;
      }
      if ((p->s).work[0] == 1) {
        struct Entity* e = (p->s).unk_28;
        (p->s).coord.x = e->coord.x;
        (p->s).coord.y = e->coord.y;
      }
      (p->s).palID = m;
      SetMotion(&p->s, 0x330A);
      {
        u8* c6 = (u8*)p + 0xc6;
        if (*c6 != 0) {
          RemovePaletteAnimation(*c6);
          *c6 = m;
        }
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x1C, g | 0x200);
        }
        *c6 = 0x1C;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((u8)StepPaletteAnimation(*((u8*)p + 0xc6)) == 3) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2: {
      u8* c6;
      (p->s).palID = (p->s).work[0];
      SetMotion(&p->s, 0x3100);
      c6 = (u8*)p + 0xc6;
      if (*c6 != 0) {
        RemovePaletteAnimation(*c6);
        *c6 = 0;
      }
      if ((p->s).work[0] == 0) {
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x16, g | 0x200);
        }
        *c6 = 0x16;
      } else {
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x11, g | 0x200);
        }
        *c6 = 0x11;
      }
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 3:
      if ((u8)StepPaletteAnimation(*((u8*)p + 0xc6)) == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/boss/baby_elf_p2_p2b.inc");

void BabyElf_Init(struct Boss* p);
void BabyElf_Update(struct Boss* p);
void BabyElf_Die(struct Boss* p);

// clang-format off
const BossRoutine gBabyElfRoutine = {
    [ENTITY_INIT] =      BabyElf_Init,
    [ENTITY_UPDATE] =    BabyElf_Update,
    [ENTITY_DIE] =       BabyElf_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

void nop_08046150(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[19] = {
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
    nop_08046150,
};
// clang-format on

// --------------------------------------------

void babyelf_08046154(struct Boss* p);
void babyelf_0804662c(struct Boss* p);
void babyelf_080467c4(struct Boss* p);
void babyelf_08046a7c(struct Boss* p);
void FUN_08046ccc(struct Boss* p);
void babyelf_08046e5c(struct Boss* p);
void babyelf_08047184(struct Boss* p);
void babyelf_08047338(struct Boss* p);
void babyelf_080475a0(struct Boss* p);
void babyelf_080477b8(struct Boss* p);
void FUN_080478b8(struct Boss* p);
void babyelf_080479d4(struct Boss* p);
void babyelf_08047c70(struct Boss* p);
void babyelf_08047e30(struct Boss* p);
void FUN_08047f84(struct Boss* p);
void FUN_08048190(struct Boss* p);
void FUN_0804839c(struct Boss* p);
void FUN_08048548(struct Boss* p);
void FUN_0804874c(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[19] = {
    babyelf_08046154,
    babyelf_0804662c,
    babyelf_080467c4,
    babyelf_08046a7c,
    FUN_08046ccc,
    babyelf_08046e5c,
    babyelf_08047184,
    babyelf_08047338,
    babyelf_080475a0,
    babyelf_080477b8,
    FUN_080478b8,
    babyelf_080479d4,
    babyelf_08047c70,
    babyelf_08047e30,
    FUN_08047f84,
    FUN_08048190,
    FUN_0804839c,
    FUN_08048548,
    FUN_0804874c,
};
// clang-format on

// --------------------------------------------

void FUN_08048788(struct Boss* p);
void FUN_080488cc(struct Boss* p);

static const BossFunc sDeinitializers[2] = {
    FUN_08048788,
    FUN_080488cc,
};

// --------------------------------------------

// 0x0836265c
static const struct Collision sCollisions[5] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1000, 0x1000},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x1000, 0x1000},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1E00, 0x1E00},
    },
    [4] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x1E00, 0x1E00},
    },
};

const u8 u8_ARRAY_083626d4[64] = {
    1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 5, 5, 5, 5, 1, 1, 2, 2, 3, 3, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 1, 1, 1, 2, 2, 2, 12, 12, 12, 3, 3, 3, 13, 13, 13, 13, 1, 2, 12, 12, 3, 3, 13, 13, 7, 7, 7, 7, 7, 7, 7, 7,
};

static const u8 sInitModes[4] = {0, 0, 0, 0};
