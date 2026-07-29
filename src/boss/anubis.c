#include "boss.h"
#include "collision.h"
#include "element.h"
#include "global.h"
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
