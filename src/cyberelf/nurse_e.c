#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "vfx.h"

// コロップ、ソロップ(つまり、画面上を飛行するエルフ？)

#include "zero.h"

struct CyberElfNurseE {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};

struct Elf* CreateNurseEElf(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElfNurseE* p = (struct CyberElfNurseE*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 4);
    (p->s).tileNum = 0, (p->s).palID = 0;
    p->player = z;
    (p->s).work[0] = breed, (p->s).work[1] = availability, (p->s).work[2] = satelite_slot;
    if (satelite_slot == 0) {
      (p->s).work[3] = SATELITE_1;
    } else {
      (p->s).work[3] = SATELITE_2;
    }
  }
  return (struct Elf*)p;
}

INCASM("asm/cyberelf/nurse_e_p1_b.inc");

void NurseE_Update(struct Elf* p);

void NurseE_Init(struct Elf* p) {
  register struct Zero* par asm("r8");
  register u8* pb asm("r9");
  struct Rect rr;
  s32 z6;
  par = ((struct CyberElfNurseE*)p)->player;
  asm("" : "+r"(par));
  {
    register const struct Rect* zr asm("r1");
    zr = gZeroRanges;
    asm("" : "+r"(zr));
    pb = (u8*)par + 0xb4;
    asm("" : "+r"(pb));
    rr = zr[*((u8*)par + 0x147)];
  }
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register s32 c1 asm("r0");
    register s32 f1 asm("r1");
    f1 = (p->s).flags;
    c1 = 1;
    asm("" : "+r"(c1));
    z6 = 0;
    c1 = c1 | f1;
    c1 |= 2;
    (p->s).flags = c1;
  }
  SetMotion(&p->s, GetElfMotion(0));
  UpdateMotionGraphic(&p->s);
  ((p->s).spr).xflip = z6;
  {
    u8* oa = (u8*)&((p->s).spr).oam + 6;
    s32 ov = *oa;
    s32 m11 = -0x11;
    asm("" : "+r"(m11));
    *oa = m11 & ov;
    (p->s).flags &= 0xEF;
    oa -= 1;
    {
      s32 ov9 = *oa;
      s32 m13 = -0xD;
      asm("" : "+r"(m13));
      *oa = (m13 & ov9) | 4;
    }
  }
  {
    register struct Zero* pl asm("r2");
    s32 rx = rr.x;
    pl = par;
    (p->s).coord.x = (pl->s).coord.x + rx;
    (p->s).coord.y = (pl->s).coord.y + rr.y;
  }
  (p->s).unk_coord.x = z6;
  (p->s).unk_coord.y = z6;
  {
    s32* dst;
    s32 cx, cy;
    asm volatile("" ::: "memory");
    dst = (s32*)((u8*)p + 0xbc);
    cx = (p->s).coord.x;
    cy = (p->s).coord.y;
    dst[0] = cx;
    dst[1] = cy;
  }
  (p->s).d.x = z6;
  *((u8*)p + 0xb9) = z6;
  (p->s).d.y = 0x20;
  {
    u8 sel;
    if ((p->s).work[2] == 0) {
      register u8* t0 asm("r0");
      t0 = pb;
      sel = t0[0];
    } else {
      register u8* t2 asm("r2");
      t2 = pb;
      sel = t2[1];
    }
    if (ELF_AVABILITY(sel) & 4) {
      u16* ha = (u16*)((u8*)p + 0xba);
      register u32 hv asm("r0");
      hv = 0x258;
      *ha = hv;
    } else {
      u16* ha = (u16*)((u8*)p + 0xba);
      register u32 hv asm("r0");
      hv = 0x384;
      *ha = hv;
    }
  }
  {
    u32 v;
    register u32 one asm("r1");
    if ((p->s).work[2] != 0) {
      register struct Zero* b1 asm("r1");
      b1 = par;
      v = (b1->s).flags >> 4;
      one = 1;
      v ^= one;
    } else {
      register struct Zero* b2 asm("r2");
      b2 = par;
      v = (b2->s).flags >> 4;
      one = 1;
    }
    (p->s).mode[1] = v & one;
  }
  NurseE_Update(p);
}

INCASM("asm/cyberelf/nurse_e_p1_b2.inc");

void NurseE_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

s32 CalcAngle(s32 x, s32 y);
u32 FUN_080e964c(u32 a, s32 b, s32 c);
extern const s16 gSineTable[256];

// 0x080E3388
void FUN_080e3388(struct Coord* self, struct Coord* target, s32* spd, u8* ang, s32 a5, s32 a6, s32 a7,
                  s32 a8, s32 a9, s32 a10, s32 a11) {
  register s32 na asm("r6");
  register s32 sp0 asm("r4");
  register s32 res asm("r3");
  register s32 lim asm("r5");
  na = CalcAngle(target->x - self->x, target->y - self->y);
  sp0 = *spd;
  res = na;
  lim = a5;
  if (sp0 > 0) {
    res = *ang;
    if (((na - res + 0x3F) & 0xFF) <= 0x7E) {
      res = FUN_080e964c(na, res, a11);
    }
  }
  *ang = res;
  {
    register s32 t asm("r0");
    register s32 mk asm("r1");
    t = na - res;
    t += 0x3F;
    mk = 0xFF;
    t &= mk;
    if (t > 0x7E) {
      goto zero;
    }
    if (lim <= 0) {
      lim = a6;
    } else if (lim > a7) {
      lim = a7;
    }
    goto done;
  zero:
    lim = 0;
  done:;
  }
  if (sp0 != lim) {
    if (sp0 < lim) {
      sp0 += *(volatile s32*)&a9;
      if (sp0 > lim) {
        sp0 = lim;
      }
    } else {
      s32 d;
      register s32 v8 asm("r1");
      v8 = a8;
      if (v8 > 0) {
        if (sp0 > v8) {
          d = *(volatile s32*)&a10;
          goto haved;
        }
      }
      d = *(volatile s32*)&a9;
    haved:
      sp0 -= d;
      if (sp0 < lim) {
        sp0 = lim;
      }
    }
    {
      register s32* sp1 asm("r1");
      sp1 = spd;
      asm("" : "+r"(sp1));
      *sp1 = sp0;
    }
  }
  if (sp0 > 0) {
    s32 c = gSineTable[(u8)(res + 0x40)];
    self->x += (sp0 * c) >> 8;
    {
      s32 sv = gSineTable[(u8)res];
      self->y += (sp0 * sv) >> 8;
    }
  }
  asm volatile("" ::"r"(res));
}

void NurseE_Init(struct Elf* p);
void NurseE_Update(struct Elf* p);
void NurseE_Die(struct Elf* p);

// clang-format off
const ElfRoutine gNurseERoutine = {
    [ENTITY_INIT] =      NurseE_Init,
    [ENTITY_UPDATE] =    NurseE_Update,
    [ENTITY_DIE] =       NurseE_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on
