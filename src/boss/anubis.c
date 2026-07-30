#include "boss.h"
#include "collision.h"
#include "element.h"
#include "global.h"
#include "gfx.h"
#include "constants/motion/static.h"
#include "zero.h"

static const BossFunc sDeads[2];
static const struct Coord sElementCoord;

// Does not match: agbcc holds p in ip/r12 and emits a redundant coord.y store
// that the natural C doesn't. Logic is faithful in the MODERN branch; the
// INCCODE asm body matches the ROM.
NON_MATCH void FUN_08050090(struct Boss* p) {
#if MODERN
  s32 base;
  *(u16*)((u8*)p + 0xc8) += 0x200;
  base = *(s32*)((u8*)p + 0xc4);
  (p->s).coord.y = base + (SIN(*(u16*)((u8*)p + 0xc8) >> 8) << 2);
#else
  INCCODE("asm/boss/anubis_08050090_body.inc");
#endif
}

void FUN_080500c8(struct Body* body) {
  struct Boss* atk = (struct Boss*)((body->enemy)->parent);
  struct Boss* self = (struct Boss*)body->parent;
  if (body->hitboxFlags & 1) {
    u8 r = 0;
    if ((self->s).coord.x < (atk->s).coord.x) {
      r = 1;
    }
    *(u8*)((u8*)self + 0xcc) = r;
  }
}

INCASM("asm/boss/anubis_p1_pre_p2_a.inc");

static const u8 sInitModes[4];
static const struct Collision sCollisions[3];
void Anubis_Update(struct Boss* p);

void Anubis_Init(struct Boss* p) {
  s32 z5;
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
    z5 = 0;
    (p->s).mode[1] = m;
  }
  {
    u32 fl = (p->s).flags;
    fl |= 2;
    asm("" : "+r"(fl));
    fl |= 1;
    (p->s).flags = fl;
  }
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  ResetBossBody(p, sCollisions, 0x40);
  {
    void* f = (void*)FUN_080500c8;
    u8* b = (u8*)p + 0x74;
    *(void**)(b + 0x24) = f;
    asm("" : "+r"(b));
    b += 0x40;
    asm("" : "+r"(b));
    *(u32*)b = z5;
  }
  if ((p->s).work[0] != 1) {
    {
      s32* pb = (s32*)((u8*)p + 0xb8);
      s32 cx = (p->s).coord.x >> 8;
      s32 q;
      *pb = cx;
      q = cx / 0xF0;
      *pb = (((q << 4) - q) << 12) + 0x7800;
      asm("" : "+r"(pb));
      pb += 1;
      {
        s32 cy = (p->s).coord.y >> 8;
        s32 q2;
        *pb = cy;
        q2 = cy / 0xA0;
        q2 += 1;
        *pb = ((q2 << 2) + q2) << 13;
      }
    }
    {
      u8* w = (u8*)p + 0xc0;
      s32 z1;
      *(u32*)w = z5;
      asm("" : "+r"(w));
      w += 8;
      z1 = 0;
      *(u16*)w = z5;
      asm("" : "+r"(w));
      w += 2;
      *w = z1;
      asm("" : "+r"(w));
      w += 1;
      *w = z1;
      *((u8*)p + 0xcd) = 0x40;
      {
        u8* w2 = (u8*)p + 0xce;
        *w2 = z1;
        asm("" : "+r"(w2));
        w2 += 1;
        *w2 = z1;
      }
    }
    LOAD_STATIC_GRAPHIC(SM073_ANUBIS_ROD);
    LOAD_STATIC_GRAPHIC(SM074_ANUBIS_SAND);
    {
      u16* a2 = (u16*)((u8*)p + 0xd0);
      register u32 v asm("r0");
      v = 0xFFFF;
      *a2 = v;
    }
    *((u8*)p + 0xd2) = 1;
  }
  Anubis_Update(p);
}

static const BossFunc sUpdates1[11];
static const BossFunc sUpdates2[11];
bool8 FUN_080500f4(struct Boss* p);

void Anubis_Update(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  struct Entity* e;
  u8* t;
  s32 v;
  if (*slot != NULL) {
    if (!isKilled(*slot)) {
      goto next;
    }
    e = NULL;
  } else {
    if (!((p->body).status & 1)) {
      goto next;
    }
    e = (struct Entity*)ApplyElementEffect(0x14, &p->s, &sElementCoord);
  }
  *slot = e;
next:
  t = (u8*)((u8*)p + 0xca);
  if (*t != 0) {
    v = *t - 1;
  } else {
    if (!((pZero2->body).status & 1)) {
      goto skip;
    }
    v = 0x60;
  }
  *t = v;
skip:
  if (FUN_080500f4(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Anubis_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_080503c8(struct Boss* p) {}

INCASM("asm/boss/anubis_p2.inc");

void FUN_08050090(struct Boss* p);

void anubisMode3(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x3C;
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 2: {
      u32 sv;
      u32 xf;
      u32 xf2;
      s32 k16;
      {
        u32* st = (u32*)((u8*)p + 0xc0);
        *st |= 4;
      }
      sv = (u16)Sqrt(0x680);
      (p->s).work[2] = sv;
      (p->s).d.x = sv << 4;
      xf = (((p->s).flags >> 4) ^ 1) & 1;
      ((p->s).spr).xflip = xf;
      xf2 = (((p->s).flags >> 4) ^ 1) & 1;
      {
        register u8* oa asm("r5");
        u32 sh4;
        s32 ov, m11;
        oa = (u8*)p + 0x4a;
        sh4 = xf2 << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      if (xf2 != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        u32 fl2 = (p->s).flags;
        register u32 res asm("r0");
        k16 = 0x10;
        asm("" : "+r"(k16));
        res = k16;
        asm volatile("" : "+r"(res));
        res &= fl2;
        if (res == 0) {
          goto arm2;
        }
      }
      if (1) {
        (p->s).coord.x = *(s32*)((u8*)p + 0xb8) - 0x9800;
        (p->s).unk_coord.x = -0x10;
      } else {
      arm2:
        (p->s).coord.x = *(s32*)((u8*)p + 0xb8) + 0x9800;
        (p->s).d.x = -(p->s).d.x;
        (p->s).unk_coord.x = k16;
      }
      SetMotion(&p->s, 0xAF01);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.x += (p->s).unk_coord.x;
      FUN_08050090(p);
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 4:
      FUN_08050090(p);
      UpdateMotionGraphic(&p->s);
      if ((*(u32*)((u8*)p + 0xc0) & 4) == 0) {
        s16* snd = (s16*)((u8*)p + 0xd0);
        register s32 v asm("r1");
        v = *snd;
        if (v != -1) {
          u32 mv;
          StopSound(v);
          mv = 0xFFFF;
          asm("" : "+r"(mv));
          *snd = mv;
        }
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 1;
      }
      break;
  }
}

INCASM("asm/boss/anubis_p2_m4.inc");

static const struct Collision sCollisions[3];

void anubisMode5(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if (((p->props).anubis).unk_cc[2] != 0) {
        UpdateMotionGraphic(&p->s);
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 2;
        (p->s).work[2] = 2;
        break;
      }
      SetDDP(&p->body, sCollisions);
      {
        u32 v = ((p->props).anubis).unk_c0;
        v |= 0x100;
        asm("" : "+r"(v));
        v |= 0x20;
        v &= ~0x40;
        ((p->props).anubis).unk_c0 = v;
      }
      SetMotion(&p->s, MOTION(0xAF, 0x08));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        ((p->props).anubis).unk_c0 &= ~0x100;
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/anubis_p2c.inc");

// 0x08050c68
void anubisMode7(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x60;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((u8)--(p->s).work[2] != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 2:
      ((p->props).anubis).unk_c0 = (((p->props).anubis).unk_c0 & ~0x20) | 0x40;
      (p->s).flags |= DISPLAY;
      SetMotion(&p->s, MOTION(0xAF, 0x0E));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u16 h = (p->body).hp;
        u8* a = &((p->props).anubis).unk_cc[1];
        s32 z = 0;
        *a = h;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      break;
  }
}

INCASM("asm/boss/anubis_p2b.inc");

void Anubis_Init(struct Boss* p);
void Anubis_Update(struct Boss* p);
void Anubis_Die(struct Boss* p);

// clang-format off
const BossRoutine gAnubisRoutine = {
    [ENTITY_INIT] =      Anubis_Init,
    [ENTITY_UPDATE] =    Anubis_Update,
    [ENTITY_DIE] =       Anubis_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080503c8(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[11] = {
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
};
// clang-format on

void anubisMode0(struct Boss* p);
void anubisNeutral(struct Boss* p);
void anubisMode2(struct Boss* p);
void anubisMode3(struct Boss* p);
void anubisMode4(struct Boss* p);
void anubisMode5(struct Boss* p);
void anubisMode6(struct Boss* p);
void anubisMode7(struct Boss* p);
void anubisMode8(struct Boss* p);
void FUN_08050e44(struct Boss* p);
void anubis_08050f38(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[11] = {
    anubisMode0,
    anubisNeutral,
    anubisMode2,
    anubisMode3,
    anubisMode4,
    anubisMode5,
    anubisMode6,
    anubisMode7,
    anubisMode8,
    FUN_08050e44,
    anubis_08050f38,
};
// clang-format on

// --------------------------------------------

void anubis_08051018(struct Boss* p);
void anubis_080510f0(struct Boss* p);

static const BossFunc sDeads[2] = {
    anubis_08051018,
    anubis_080510f0,
};

// --------------------------------------------

// 0x0836356c
static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
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
      damage : 3,
      atkType : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(52)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 6,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(52)},
    },
};

static const u8 sInitModes[4] = {0, 9, 0, 0};
static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};

static const u8 u8_ARRAY_083635c0[9] = {5, 2, 10, 4, 5, 8, 2, 10, 4};
static const u8 u8_ARRAY_083635c9[8] = {2, 2, 2, 2, 3, 3, 3, 3};
static const u8 u8_ARRAY_083635d1[8] = {2, 2, 3, 3, 3, 4, 4, 4};

static const struct Coord sExplosionCoords[2] = {
    {PIXEL(2), -PIXEL(8)},
    {PIXEL(4), -PIXEL(6)},
};
