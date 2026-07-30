#include "boss.h"
#include "collision.h"
#include "entity.h"
#include "global.h"
#include "zero.h"
#include "palette_animation.h"
#include "overworld.h"

static const BossFunc sDeinitializers[2];

void FUN_08045b68(struct Boss* p);

INCASM("asm/boss/baby_elf_p1_pre_p1.inc");

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

// Same palette-anim basin as FUN_08046ccc below: the retail
// (palID<<5)|0x200 argument keeps its 0x200 web with an adds-copy feeding the
// or (two per-arm copies, 4 bytes) that no kc/barrier/k+0 spelling reproduces
// without also emitting a u16 truncation pair.
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
      u32 k = 0x200;
      StartPaletteAnimation(0x14, ((u32)GetEntityPalID(&p->s) << 5) | (k + 0));
      *((u8*)p + 0xc6) = 0x14;
    } else {
      u32 k = 0x200;
      StartPaletteAnimation(0xF, ((u32)GetEntityPalID(&p->s) << 5) | (k + 0));
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

INCASM("asm/boss/baby_elf_p2_p1b.inc");

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
