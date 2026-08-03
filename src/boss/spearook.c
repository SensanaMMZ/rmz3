#include "boss.h"
#include "collision.h"
#include "global.h"
#include "stagerun.h"
#include "zero.h"
#include "vfx.h"
#include "physics.h"
#include "gfx.h"
#include "constants/motion/static.h"
#include "vfx.h"

static const BossFunc sDeads[5];


void FUN_08061b68(struct Boss* p, s32 dx, s32 dy) {
  struct Coord c;
  u32 a = *(u16*)&(p->props).raw[4] >> 8;
  s32 sinv, cosv;
  if ((p->s).flags & 0x10) {
    dx = -dx;
  }
  cosv = gSineTable[(u8)(a + 0x40)];
  c.x = dx * cosv / 256;
  sinv = gSineTable[a];
  c.x += -sinv * dy / 256;
  c.y = dx * sinv / 256;
  c.y += dy * cosv / 256;
  c.x = (p->s).coord.x + c.x;
  c.y = (p->s).coord.y + c.y;
  CreateSmoke(3, &c);
}

static const u8 u8_ARRAY_0836591c[16];

// 0x08061BF8
NON_MATCH void FUN_08061bf8(struct Boss* p0) {
#if MODERN
  register struct Boss* p asm("r5");
  u32* rng;
  const u8* tbl;
  register u8* b asm("ip");
  u8* a;
  s32 i;
  p = p0;
  rng = &RNG_0202f388;
  tbl = u8_ARRAY_0836591c;
  do {
    register u32 k asm("r4");
    u32 t = *rng * 0x343FD;
    k = 0x269EC3;
    t += k;
    t <<= 1;
    *rng = t >> 1;
    i = (t >> 0x11) & 0xF;
    a = (u8*)p + 0xc2;
    asm("" : "+r"(a));
    b = (u8*)p + 0xc3;
    asm("" : "+r"(b));
  } while (*a == tbl[i] && *b != 0);
  if (*a == tbl[i]) {
    (*b)++;
  } else {
    *a = tbl[i];
    *b = 0;
  }
  (p->s).mode[1] = tbl[i];
  (p->s).mode[2] = 0;
#else
  INCCODE("asm/boss/spearook_08061bf8.inc");
#endif
}

#include "entity/macros.h"

struct Boss* FUN_08061c74(struct Entity* e) {
  struct Boss* p = (struct Boss*)AllocEntityFirst(gBossHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_BOSS_ROUTINE(p, 24);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).unk_28 = e;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = e->uniqueID;
  }
  return p;
}

void FUN_08061ccc(struct Entity* e, struct Entity* e2) {
  struct Boss* p = (struct Boss*)AllocEntityFirst(gBossHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_BOSS_ROUTINE(p, 24);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).unk_28 = e;
    (p->s).unk_2c = e2;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = e->uniqueID;
  }
}

// 0x08061d24 -- parked (address-derivation basin): retail keeps the boss
// pointer live in r2 and derives +0xc0/+0xbc through a fresh temp with a
// subs #4 chain; agbcc either parks the pointer in ip (+3) or ties the
// derived address in place. Both RANDOM offsets and the hp doubling are
// decoded and verified.
NON_MATCH void FUN_08061d24(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
#if MODERN
  struct Boss* q = (struct Boss*)body->parent;
  u8 w0 = (q->s).work[0];
  if (w0 == 1) {
    if (body->hitboxFlags & 8) {
      s32 f = 0;
      u8* c0;
      if ((q->s).coord.x < (pZero2->s).coord.x) {
        f = 1;
      }
      c0 = (u8*)q + 0xc0;
      *c0 = f;
    }
  } else if (w0 == 0) {
    if (body->hitboxFlags & 1) {
      s32 f = 0;
      u16* hp;
      u8* c1;
      u8* c0;
      if ((q->s).coord.x < (pZero2->s).coord.x) {
        f = 1;
      }
      c0 = (u8*)q + 0xc0;
      *c0 = f;
      hp = (u16*)((u8*)q + 0xa4);
      c1 = (u8*)q + 0xc1;
      if (*(s32*)(c0 - 4) & 2) {
        struct Coord c;
        *hp = *hp * 2 - *c1;
        c.x = (q->s).coord.x - 0x800 + (RANDOM(RNG_0202f388) & 0x7FF);
        c.y = (q->s).coord.y - 0x1400 + (RANDOM(RNG_0202f388) & 0x7FF);
        CreateSmoke(1, &c);
        PlaySound(0x2A);
      }
      *c1 = *hp;
    }
  }
#else
  INCCODE("asm/boss/spearook_1d24.inc");
#endif
}

void Spearook_Die(struct Boss* p);

// 0x08061E24
bool8 FUN_08061e24(struct Boss* p) {
  register s32 w0 asm("r4");
  register s32 nm asm("r0");
  w0 = (p->s).work[0];
  switch (w0) {
    case 0:
      if ((*(u32*)((u8*)p + 0x8c) & 0x200) == 0) {
        if (*(s16*)((u8*)p + 0xa4) != 0) {
          return 0;
        }
      }
      if (gStageRun.missionStatus & 8) {
        return 0;
      }
      SET_BOSS_ROUTINE(p, ENTITY_DIE);
      (p->s).mode[1] = w0;
      goto die;
    case 1: {
      struct Entity* q = (p->s).unk_28;
      register s32 two asm("r4");
      if (q->mode[0] <= 1) {
        return 0;
      }
      {
        u32 tbl = (u32)gBossFnTable;
        u32 id = ((p->s).id) << 2;
        EntityFunc** rt = (EntityFunc**)(tbl + id);
        two = 2;
        *(u32*)((p->s).mode) = two;
        (p->s).onUpdate = (void*)(*rt)[ENTITY_DIE];
      }
      if (*(u32*)((u8*)q + 0xbc) & 0x100) {
        nm = 4;
        goto setm;
      }
      asm("" : "+r"(two));
      (p->s).mode[1] = two;
      asm volatile("" ::"r"(two));
      goto die;
    }
    case 2: {
      register struct Entity* q asm("r3");
      q = (p->s).unk_28;
      if (q->mode[0] <= 1) {
        return 0;
      }
      {
        u32 tbl = (u32)gBossFnTable;
        u32 id = ((p->s).id) << 2;
        EntityFunc** rt = (EntityFunc**)(tbl + id);
        *(u32*)((p->s).mode) = w0;
        (p->s).onUpdate = (void*)(*rt)[ENTITY_DIE];
      }
      nm = 3;
    setm:
      (p->s).mode[1] = nm;
    die:
      Spearook_Die(p);
      return 1;
    }
  }
  return 0;
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_08061ef0(struct Boss* p) {
  struct VFX** slot = (struct VFX**)&(p->props).raw[0];

  if (*slot == NULL && ((p->body).status & 1)) {
    *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
    if (*slot != NULL) {
      *(u32*)&(p->props).raw[8] &= ~4;
      (p->s).mode[1] = 15;
      (p->s).mode[2] = 0;
    }
  }
}

static const u8 sInitModes[4];
static const struct Collision sCollisions[17];

void Spearook_Update(struct Boss* p);
struct Boss* FUN_08061c74(struct Entity* e);
void FUN_08061ccc(struct Entity* e, struct Entity* e2);
void FUN_08061d24(struct Body* body, struct Coord* r1, struct Coord* r2);

void Spearook_Init(struct Boss* p) {
  s32 z4;
  {
    u32 tbl = (u32)gBossFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    register u32 one asm("r1");
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  {
    u8 m = sInitModes[(p->s).work[0]];
    z4 = 0;
    (p->s).mode[1] = m;
  }
  {
    u32 fl = (p->s).flags;
    fl |= 2;
    asm("" : "+r"(fl));
    fl |= 1;
    (p->s).flags = fl;
  }
  if ((p->s).work[0] == 1) {
    InitRotatableMotion(&p->s);
    {
      u16* w = (u16*)((u8*)p + 0xb8);
      *w = z4;
      asm("" : "+r"(w));
      w += 1;
      asm("" : "+r"(w));
      *w = z4;
    }
  } else if ((p->s).work[0] == 3) {
    InitRotatableMotion(&p->s);
  } else {
    InitNonAffineMotion(&p->s);
  }
  ResetBossBody(p, sCollisions, 0x60);
  {
    void* f = (void*)FUN_08061d24;
    u8* b = (u8*)p + 0x74;
    *(void**)(b + 0x24) = f;
    asm("" : "+r"(b));
    b += 0x40;
    asm("" : "+r"(b));
    *(u32*)b = 0;
  }
  if ((p->s).work[0] == 0) {
    struct Boss* q = FUN_08061c74(&p->s);
    FUN_08061ccc(&p->s, (struct Entity*)q);
    LOAD_STATIC_GRAPHIC(SM214_SPEAROOK);
    LOAD_STATIC_GRAPHIC(SM215_UNK);
    *(u32*)((u8*)p + 0xbc) = 0;
    *((u8*)p + 0xc1) = 0x60;
  }
  *((u8*)p + 0xc0) = 0;
  *((u8*)p + 0xc2) = 0xFF;
  {
    u8* w = (u8*)p + 0xc3;
    s32 z2 = 0;
    *w = z2;
    asm("" : "+r"(w));
    w += 1;
    asm("" : "+r"(w));
    *w = z2;
  }
  Spearook_Update(p);
}

INCASM("asm/boss/spearook_p1_pre_pre_b.inc");


void Spearook_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_08062264(struct Boss* p) {}

void FUN_08062268(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void FUN_0806228c(struct Boss* p) {
  if ((p->body).status & 8) {
    if ((p->body).status & 0x20000) {
      *(s16*)((u8*)p + 0xba) += 0x4000;
      *(s16*)((u8*)p + 0xba) -= *((u8*)p + 0xc0) << 15;
    } else {
      *(s16*)((u8*)p + 0xba) += 0x800;
      *(s16*)((u8*)p + 0xba) -= *((u8*)p + 0xc0) << 12;
    }
    if (*(s16*)((u8*)p + 0xba) < -0x4000) {
      u16 c = 0xC000;
      *(u16*)((u8*)p + 0xba) = c;
    } else if (*(s16*)((u8*)p + 0xba) > 0x4000) {
      *(s16*)((u8*)p + 0xba) = 0x4000;
    }
  }
}

void FUN_08062304(struct Boss* p) {
  u32 v = *(u32*)((u8*)p + 0x8c);
  if (v & 1) {
    if (v & 0x20000) {
      *(u32*)((u8*)p + 0xbc) &= ~4;
      (p->s).mode[1] = 14;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_08061bf8(struct Boss* p);

// 0x08062338
void FUN_08062338(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, (const struct Collision*)0x0836579C);
      (p->s).work[2] = 0x18;
      SetMotion(&p->s, MOTION(0xD6, 0x00));
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (u8)--(p->s).work[2];
      if (t == 0) {
        u8 v = *((u8*)p + 0xC4);
        u8* c = (u8*)p + 0xC4;
        if (v == 0) {
          FUN_08061bf8(p);
        } else {
          (p->s).mode[1] = 4;
          (p->s).mode[2] = t;
        }
        (*c)++;
        if (*c > 1) {
          *c = 0;
        }
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      break;
    }
  }
}

extern void __umodsi3();

// 0x080623BC
void FUN_080623bc(struct Boss* p) {
  struct Camera* cam;
  switch ((p->s).mode[2]) {
    case 0:
      cam = &gStageRun.vm.camera;
      (p->s).coord.y = cam->viewport.y - 0x9000;
      (p->s).flags &= ~1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      if (((p->s).scriptEntity)->flags & 1) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      (p->s).flags |= 1;
      cam = &gStageRun.vm.camera;
      (p->s).coord.y = cam->viewport.y - 0x9000;
      (p->s).d.y = 0;
      SetMotion(&(p->s), 0xD600);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s32 push;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (push < 0) {
        AppendQuake(3, &(p->s).coord);
        (p->s).coord.y += push;
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&(p->s));
      break;
    }
    case 4:
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      if ((gStageRun.vm.active & 1) == 0) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x080624B0
void FUN_080624b0(struct Boss* p) {
  struct Entity* q = (p->s).unk_28;
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).work[2] = m;
      SetMotion(&p->s, MOTION(0xD6, 0x01));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register u32* w asm("r2");
      register s32 cx asm("r6");
      s32 t;
      if (q->mode[1] != 1) {
        SetDDP(&p->body, (const struct Collision*)0x083657CC);
      }
      (p->s).work[2]++;
      t = ((s32 (*)(s32, s32))__umodsi3)((p->s).work[2], 15);
      (p->s).work[2] = t;
      asm("" : "+r"(t));
      t <<= 24;
      if (t == 0) {
        FUN_08061b68(p, 0x1400, -0x3100);
      }
      UpdateMotionGraphic(&p->s);
      cx = (q->coord).x;
      (p->s).coord.x = cx;
      (p->s).coord.y = (q->coord).y - 0x1200;
      w = (u32*)((u8*)q + 0xbc);
      if ((*w & 2) == 0) {
        register u32 one asm("r3");
        register u32 fl asm("r1");
        register u32 fv asm("r0");
        fv = (p->s).flags;
        fl = fv >> 4;
        one = 1;
        fl &= one;
        if (cx < (pZero2->s).coord.x) {
          if (fl != one) {
            goto turn;
          }
          goto chk;
        }
        if (fl == 0) {
          goto chk;
        }
      turn:
        *w |= 1;
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 0;
        break;
      }
    chk: {
      u32 v = *w;
      u32 a = 4;
      a &= v;
      if (a != 0) {
        (p->s).mode[1] = 8;
        (p->s).mode[2] = 0;
      } else {
        v &= 0x20;
        if (v != 0) {
          (p->s).mode[1] = 0xA;
          (p->s).mode[2] = a;
        }
      }
      break;
    }
    }
  }
}

// 0x08062588
void FUN_08062588(struct Boss* p) {
  struct Entity* e = (p->s).unk_28;
  struct Entity* q = (struct Entity*)(p->s).unk_2c;
  u8 m = (p->s).mode[2];
  u32* f;
  switch (m) {
    case 0:
      SetMotion(&(p->s), 0xD60D);
      (p->s).work[2] = m;
      (p->s).work[3] = 1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 x, y;
      u8* ap;
      const s16* tb;
      s32 a;
      if ((p->s).work[2] == 0) {
        u32* t;
        u32 v;
        if ((p->s).work[3] == 0 && (p->s).motion.state == 3) {
          SetMotion(&(p->s), 0xD60D);
          (p->s).work[3] = 1;
        }
        t = (u32*)((u8*)e + 0xbc);
        v = *t & 2;
        f = t;
        if (v != 0) {
          SetMotion(&(p->s), 0xD60E);
          (p->s).work[2] = 1;
        }
      } else {
        u32* r = (u32*)((u8*)e + 0xbc);
        u32 t = *r & 2;
        f = r;
        if (t == 0) {
          SetMotion(&(p->s), 0xD60F);
          (p->s).work[2] = t;
          (p->s).work[3] = t;
        }
      }
      UpdateMotionGraphic(&(p->s));
      if (*f & 1) {
        *f &= ~1;
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      }
      x = (q->coord).x;
      (p->s).coord.x = x;
      asm("" ::: "memory");
      tb = gSineTable;
      ap = (u8*)q + 0xb8;
      x += 11 * tb[*(u16*)ap >> 8];
      (p->s).coord.x = x;
      y = (q->coord).y;
      (p->s).coord.y = y;
      asm("" : "+r"(ap));
      a = (s8)(*(u16*)ap >> 8);
      asm("" : "+r"(a));
      y -= 11 * tb[(u8)(a + 0x40)];
      (p->s).coord.y = y;
      break;
    }
  }
}

// 0x0806267C
void FUN_0806267c(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((*(u32*)((u8*)p + 0xbc) & 0x20) == 0) {
        (p->s).mode[2] = 1;
      }
      break;
    case 1:
      (p->s).work[2] = 0x78;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 2: {
      register s32 hit asm("r5");
      register s32 zx asm("r3");
      register s32 px asm("r2");
      zx = (pZero2->s).coord.x;
      px = (p->s).coord.x;
      if ((u32)(zx - px + 0x6000) <= 0xBFFF) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
        break;
      }
      hit = 0;
      if (px > zx) {
        if (((bool16 (*)(s32, s32))FUN_080098a4)(px - 0x1600, (p->s).coord.y + 0x400)) {
          (p->s).coord.x -= 0x80;
        } else {
          hit = 1;
        }
      } else {
        if (((bool16 (*)(s32, s32))FUN_080098a4)(px + 0x1600, (p->s).coord.y + 0x400)) {
          (p->s).coord.x += 0x80;
        } else {
          hit = 1;
        }
      }
      {
        register s32 t asm("r0");
        register s32 zz asm("r1");
        t = (p->s).work[2] - 1;
        zz = 0;
        (p->s).work[2] = t;
        t <<= 24;
        if (t == 0 || hit != 0) {
          (p->s).mode[1] = zz;
          (p->s).mode[2] = zz;
        }
      }
      UpdateMotionGraphic(&p->s);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      break;
    }
  }
}

// 0x08062754
void FUN_08062754(struct Boss* p) {
  struct Entity* e = (p->s).unk_28;
  (p->s).coord.x = (e->coord).x;
  (p->s).coord.y = (e->coord).y - 0x1200;
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&(p->s), 0xD605);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&(p->s));
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      u8 v;
      (p->s).spr.xflip = (((p->s).flags >> 4) ^ 1) & 1;
      v = (((p->s).flags >> 4) ^ 1) & 1;
      (p->s).spr.oam.xflip = v;
      if (v) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= ~0x10;
      }
      if ((p->s).flags & 0x10) {
        *(u32*)((u8*)e + 0xbc) |= 8;
      } else {
        *(u32*)((u8*)e + 0xbc) &= ~8;
      }
      SetMotion(&(p->s), 0xD606);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
      UpdateMotionGraphic(&(p->s));
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/spearook_p1_post_p2_a1_c.inc");

void FUN_0806293c(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32* w = (u32*)((u8*)p + 0xbc);
      u32 v = *w;
      v |= 4;
      v |= 0x10;
      *w = v;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1:
      if ((*(u32*)((u8*)p + 0xbc) & 0x12) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 2:
      if (*(u32*)((u8*)p + 0xbc) & 8) {
        (p->s).unk_coord.x = 0x20;
      } else {
        (p->s).unk_coord.x = -0x20;
      }
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 3: {
      s32 done = 0;
      s32 d = (p->s).d.x;
      if ((u32)(d + 0x300) < 0x600) {
        (p->s).d.x = d + (p->s).unk_coord.x;
      }
      if ((p->s).d.x < 0) {
        if (FUN_080098a4((p->s).coord.x - 0x1600, (p->s).coord.y + 0x400) == 0) {
          goto inc;
        }
        goto move;
      }
      if (FUN_080098a4((p->s).coord.x + 0x1600, (p->s).coord.y + 0x400) != 0) {
      move:
        (p->s).coord.x += (p->s).d.x;
      } else {
        done = 1;
      }
      if (done != 0) {
      inc:
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 4: {
      register s32 dv asm("r0");
      register s32 nd asm("r1");
      s32 nv;
      dv = (p->s).d.x;
      nd = -dv;
      (p->s).d.x = nd;
      nv = -0xC;
      (p->s).unk_coord.x = nv;
      if (nd < 0) {
        nv = 0xC;
      }
      (p->s).unk_coord.x = nv;
      {
        register u32 sg asm("r0");
        sg = (u32)nd >> 31;
        (p->s).work[2] = sg;
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 5: {
      s32 d2;
      u8 w2;
      (p->s).coord.x += (p->s).d.x;
      d2 = (p->s).d.x + (p->s).unk_coord.x;
      (p->s).d.x = d2;
      w2 = (p->s).work[2];
      if (d2 < 0) {
        if (w2 != 1) {
          goto clear;
        }
        break;
      } else {
        if (w2 == 0) {
          break;
        }
      }
    clear:
      *(u32*)((u8*)p + 0xbc) &= ~4;
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
      break;
    }
  }
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
}

// 0x08062A94
void FUN_08062a94(struct Boss* p) {
  struct Entity* q = (p->s).unk_28;
  (p->s).coord.x = q->coord.x;
  (p->s).coord.y = q->coord.y - 0x1200;
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0xD602);
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 w = (p->s).work[2] - 1;
      (p->s).work[2] = w;
      w &= 3;
      if (w == 0) {
        FUN_08061b68(p, 0xF00, -0x3100);
      }
      if ((p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      u32* st = (u32*)((u8*)q + 0xbc);
      *st &= -0x11;
      SetMotion(&p->s, 0xD601);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 3: {
      s32 w2 = (p->s).work[2] - 1;
      s32 f;
      (p->s).work[2] = w2;
      w2 &= 3;
      if (w2 == 0) {
        FUN_08061b68(p, 0xF00, -0x3100);
      }
      f = *(u32*)((u8*)q + 0xbc) & 4;
      if (f == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = f;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}


// 0x08062b70
void FUN_08062b70(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      *(u32*)&(p->props).raw[8] |= 0x20;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      u32 f = *(u32*)&(p->props).raw[8] & 0x20;
      if (f == 0) {
        (p->s).mode[1] = f;
        (p->s).mode[2] = f;
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      break;
    }
  }
}

static const u8 u8_ARRAY_08365938[16];

// 0x08062BB4
void FUN_08062bb4(struct Boss* p) {
  struct Entity* q = (p->s).unk_28;
  (p->s).coord.x = (q->coord).x;
  (p->s).coord.y = (q->coord).y - 0x1200;
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x103);
      (p->s).work[2] = u8_ARRAY_08365938[RANDOM(RNG_0202f388) & 0xF];
      (p->s).work[3] = 0xFF;
      (p->s).unk_coord.x = 0;
      SetMotion(&p->s, MOTION(0xD6, 0x03));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SetDDP(&p->body, &sCollisions[9]);
        if ((RANDOM(RNG_0202f388) & 1) != 0) {
          (p->s).mode[1] = 0xC;
        } else {
          (p->s).mode[1] = 0xB;
        }
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/spearook_p1_post_p2_b.inc");

void FUN_08061b68(struct Boss* p, s32 dx, s32 dy);

// 0x08062fe0
void FUN_08062fe0(struct Boss* p) {
  struct Entity* q = (p->s).unk_28;
  u8 m;
  (p->s).coord.x = (q->coord).x;
  (p->s).coord.y = (q->coord).y - 0x1200;
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetDDP(&p->body, (const struct Collision*)0x083657CC);
      SetMotion(&p->s, MOTION(0xD6, 0x04));
      (p->s).d.x = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).d.x++;
      (p->s).d.x %= 15;
      if ((p->s).d.x == 0) {
        FUN_08061b68(p, 0xF00, -0x3100);
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        *(u32*)((u8*)q + 0xbc) &= ~0x20;
        (p->s).mode[1] = 2, (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/spearook_p1_post_p2_c.inc");

void nop_0806316c(struct Boss* p) {}

void nop_08063170(struct Boss* p) {}

INCASM("asm/boss/spearook_p3.inc");

void FUN_080632a0(struct Boss* p0) {
  register struct Boss* p asm("r2") = p0;
  if ((p->s).mode[2] == 0) {
    register struct StageRun* sr asm("r4");
    register u32 st asm("r3");
    register s32 one asm("r5");
    register u32 av asm("r1");
    sr = &gStageRun;
    st = sr->missionStatus;
    one = 1;
    if (one & st) {
      register s32 chk asm("r0");
      av = sr->vm.active;
      chk = one & av;
      if (chk == 0) {
        sr->missionStatus = (st & 0xFFFE) | MISSION_SUCCESS;
      }
    }
    EXIT_BODY(p);
    (p->s).mode[2]++;
  }
}

INCASM("asm/boss/spearook_p3b.inc");

void nop_08063510(struct Boss* p) {}

void FUN_08063514(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      EXIT_BODY(p);
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      {
        s32 push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (push < 0) {
          (p->s).coord.y += push;
          CreateSmoke(1, &(p->s).coord);
          PlaySound(0x2a);
          (p->s).flags &= ~DISPLAY;
          (p->s).flags &= ~FLIPABLE;
          EXIT_BODY(p);
          SET_BOSS_ROUTINE(p, ENTITY_DISAPPEAR);
        }
      }
      break;
  }
}

void Spearook_Init(struct Boss* p);
void Spearook_Update(struct Boss* p);
void Spearook_Die(struct Boss* p);

// clang-format off
const BossRoutine gSpearookRoutine = {
    [ENTITY_INIT] =      Spearook_Init,
    [ENTITY_UPDATE] =    Spearook_Update,
    [ENTITY_DIE] =       Spearook_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_08062304(struct Boss* p);
void FUN_08062264(struct Boss* p);
void FUN_0806228c(struct Boss* p);
void FUN_08062268(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[17] = {
    FUN_08062304,
    FUN_08062264,
    FUN_0806228c,
    FUN_08062264,
    FUN_08062304,
    FUN_0806228c,
    FUN_08062264,
    FUN_08062304,
    FUN_0806228c,
    FUN_08062304,
    FUN_0806228c,
    FUN_0806228c,
    FUN_0806228c,
    FUN_0806228c,
    FUN_08062304,
    FUN_08062268,
    FUN_08062264,
};
// clang-format on

void FUN_08062338(struct Boss* p);
void FUN_080623bc(struct Boss* p);
void FUN_080624b0(struct Boss* p);
void FUN_08062588(struct Boss* p);
void FUN_0806267c(struct Boss* p);
void FUN_08062754(struct Boss* p);
void FUN_08062848(struct Boss* p);
void FUN_0806293c(struct Boss* p);
void FUN_08062a94(struct Boss* p);
void FUN_08062b70(struct Boss* p);
void FUN_08062bb4(struct Boss* p);
void FUN_08062c78(struct Boss* p);
void FUN_08062e30(struct Boss* p);
void FUN_08062fe0(struct Boss* p);
void FUN_08063074(struct Boss* p);
void nop_0806316c(struct Boss* p);
void nop_08063170(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[17] = {
    FUN_08062338,
    FUN_080623bc,
    FUN_080624b0,
    FUN_08062588,
    FUN_0806267c,
    FUN_08062754,
    FUN_08062848,
    FUN_0806293c,
    FUN_08062a94,
    FUN_08062b70,
    FUN_08062bb4,
    FUN_08062c78,
    FUN_08062e30,
    FUN_08062fe0,
    FUN_08063074,
    nop_0806316c,
    nop_08063170,
};
// clang-format on

// --------------------------------------------

void FUN_08063174(struct Boss* p);
void FUN_080632a0(struct Boss* p);
void FUN_080632f8(struct Boss* p);
void FUN_08063514(struct Boss* p);
void nop_08063510(struct Boss* p);

// clang-format off
static const BossFunc sDeads[5] = {
    FUN_08063174,
    FUN_080632a0,
    FUN_080632f8,
    FUN_08063514,
    nop_08063510,
};
// clang-format on

// --------------------------------------------

// 0x08365784
static const struct Collision sCollisions[17] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(42), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(20), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 5,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 2,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 7,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(64), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 6,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 5,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 3,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(64), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 2,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
};

static const u8 u8_ARRAY_0836591c[16] = {
    7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9,
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(16)};
static const u8 sInitModes[4] = {1, 2, 3, 16};

static const u8 u8_ARRAY_08365938[16] = {
    3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7,
};
