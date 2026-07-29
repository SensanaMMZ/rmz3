#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "story.h"

static const struct Collision sCollisions[];

INCASM("asm/enemy/purple_nerple_p1_a_a.inc");

#include "entity/macros.h"

void FUN_08075b74(struct Entity* e, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).unk_28 = e;
    p->props[5] = n;
  }
}

void FUN_08075bd0(struct Entity* e) {
  s32 i;

  for (i = 0; i <= 1; i++) {
    struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

    if (p != NULL) {
      (p->s).taskCol = 24;
      INIT_ENEMY_ROUTINE(p, 22);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = (p->s).uniqueID;
      (p->s).work[0] = 2;
      (p->s).work[1] = i;
      (p->s).coord.x = e->coord.x;
      (p->s).coord.y = e->coord.y;
      p->props[5] = 0;
    }
  }
}

INCASM("asm/enemy/purple_nerple_p1_a_c_a_b.inc");

#include "stagerun.h"
#include "camera.h"

void summonPurpleNerple(struct Entity* e, s32 x) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 3;
    (p->s).coord.x = x;
    (p->s).coord.y = (&gStageRun.vm.camera)->viewport.y - PIXEL(112);
    (p->s).unk_28 = e;
    *(s32*)&p->props[8] = e->coord.x;
  }
}

INCASM("asm/enemy/purple_nerple_d3c.inc");

void PurpleNerple_Die(struct Enemy* p);

// 0x08075d40
bool8 FUN_08075d40(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    switch ((p->s).work[0]) {
      case 0: {
        u32 st = (p->body).status;
        if (st & BODY_STATUS_SLASHED) {
          (p->s).mode[1] = 1;
        } else if (st & BODY_STATUS_RECOILED) {
          (p->s).mode[1] = 5;
        } else {
          (p->s).mode[1] = 0;
        }
        break;
      }
      case 1:
        if ((p->s).unk_28 != NULL) {
          *((u8*)(p->s).unk_28 + 0xb8) = 1;
        }
        (p->s).mode[1] = 2;
        break;
      case 2:
        (p->s).mode[1] = 4;
        break;
    }
    PurpleNerple_Die(p);
    return TRUE;
  }
  return FALSE;
}

INCASM("asm/enemy/purple_nerple_p1_a_c_b.inc");

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_08075e8c(struct Enemy* p) {
  struct VFX** slot;
  u32 frozen;

  if ((p->s).work[0] == 0) {
    slot = (struct VFX**)&p->props[0];
    if (*slot == NULL && ((p->body).status & 1)) {
      frozen = (p->body).status & 0x20000;
      if (frozen != 0) {
        (p->s).mode[1] = 8;
        (p->s).mode[2] = 0;
      } else {
        *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
        if (*slot != NULL) {
          (p->s).mode[1] = 0;
          (p->s).mode[2] = 0;
        }
      }
    }
  }
}

INCASM("asm/enemy/purple_nerple_p1_a_b.inc");

extern const EnemyFunc PTR_ARRAY_083670d0[10];
extern const EnemyFunc PTR_ARRAY_083670f8[10];
bool8 FUN_08075d40(struct Enemy* p);
void FUN_08075e8c(struct Enemy* p);
bool8 FUN_08075dc8(struct Enemy* p);
void PurpleNerple_Die(struct Enemy* p);

void PurpleNerple_Update(struct Enemy* p) {
  if ((p->s).work[0] != 0) {
    u8 prop = *(u8*)((u8*)p + 0xb9);
    if (prop == 0 && (gCurStory.s.gameflags[4] & 0x40)) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      (p->body).status = prop;
      (p->body).prevStatus = prop;
      (p->body).invincibleTime = prop;
      (p->s).flags &= ~COLLIDABLE;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
  }
  if ((p->s).work[0] == 0) {
    if (*(u8*)((u8*)p + 0xb9) != 0) {
      if (((p->s).unk_28)->mode[0] > 1) {
        (p->s).unk_28 = NULL;
      }
    }
  }
  if (FUN_08075d40(p)) {
    return;
  }
  FUN_08075e8c(p);
  if (FUN_08075dc8(p)) {
    return;
  }
  (PTR_ARRAY_083670d0[(p->s).mode[1]])(p);
  (PTR_ARRAY_083670f8[(p->s).mode[1]])(p);
}

extern const EnemyFunc PTR_ARRAY_08367120[6];

void PurpleNerple_Die(struct Enemy* p) {
  u8 v = p->props[5];
  if (v == 0 && FLAG(gCurStory.s.gameflags, 38)) {
    u8 f = ~DISPLAY & (p->s).flags;
    f = f & ~FLIPABLE;
    (p->s).flags = f;
    (p->body).status = v;
    (p->body).prevStatus = v;
    (p->body).invincibleTime = v;
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (PTR_ARRAY_08367120[(p->s).mode[1]])(p);
  }
}

void FUN_08076140(struct Enemy* p) {}


void FUN_08076144(struct Enemy* p) {
  if (p->props[4] != 0) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}


void FUN_08076178(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

void FUN_08076198(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

void FUN_080761b8(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      if (p->props[4] != 0) {
        (p->s).mode[1] = 4;
      } else {
        (p->s).mode[1] = 2;
      }
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/purple_nerple_p2_p2_p4.inc");

extern const motion_t sMotions[9];
struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);

void FUN_08076df8(struct Enemy* p) {
  struct Coord c;
  {
    u8 z;
    (p->body).status = z = 0;
    (p->body).prevStatus = z;
    (p->body).invincibleTime = z;
    z = ~COLLIDABLE & (p->s).flags;
    z = z & ~DISPLAY;
    (p->s).flags = z;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  CreateSmoke(2, &c);
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[7], 2);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void PurpleNerple_Init(struct Enemy* p);
void PurpleNerple_Update(struct Enemy* p);
void PurpleNerple_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPurpleNerpleRoutine = {
    [ENTITY_INIT] =      PurpleNerple_Init,
    [ENTITY_UPDATE] =    PurpleNerple_Update,
    [ENTITY_DIE] =       PurpleNerple_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_08076140(struct Enemy* p);
void FUN_08076144(struct Enemy* p);
void FUN_08076178(struct Enemy* p);
void FUN_08076198(struct Enemy* p);
void FUN_080761b8(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_083670d0[10] = {
    FUN_080761b8,
    FUN_08076144,
    FUN_08076144,
    FUN_08076140,
    FUN_08076178,
    FUN_08076140,
    FUN_08076198,
    FUN_08076140,
    FUN_08076140,
    FUN_08076178,
};
// clang-format on

// --------------------------------------------

void FUN_08076220(struct Enemy* p);
void FUN_080762ec(struct Enemy* p);
void FUN_080763f8(struct Enemy* p);
void FUN_08076508(struct Enemy* p);
void FUN_08076594(struct Enemy* p);
void FUN_08076780(struct Enemy* p);
void FUN_08076638(struct Enemy* p);
void FUN_08076830(struct Enemy* p);
void FUN_080768e0(struct Enemy* p);
void FUN_08076a50(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_083670f8[10] = {
    FUN_08076220,
    FUN_080762ec,
    FUN_080763f8,
    FUN_08076508,
    FUN_08076594,
    FUN_08076780,
    FUN_08076638,
    FUN_08076830,
    FUN_080768e0,
    FUN_08076a50,
};
// clang-format on

// --------------------------------------------

void FUN_08076b30(struct Enemy* p);
void FUN_08076be4(struct Enemy* p);
void FUN_08076d30(struct Enemy* p);
void FUN_08076d9c(struct Enemy* p);
void FUN_08076df8(struct Enemy* p);
void FUN_080768e0(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08367120[6] = {
    FUN_08076b30,
    FUN_08076be4,
    FUN_08076d30,
    FUN_08076d9c,
    FUN_08076df8,
    FUN_080768e0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(5), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(18), PIXEL(22), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(14), PIXEL(14)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};

static const u8 sInitModes[4] = {1, 3, 7, 0};

// clang-format off
static const motion_t sMotions[9] = {
    MOTION(SM042_PURPLE_NERPLE, 0x11),
    MOTION(SM042_PURPLE_NERPLE, 0x12),
    MOTION(SM042_PURPLE_NERPLE, 0x11),
    MOTION(SM042_PURPLE_NERPLE, 0x0D),
    MOTION(SM042_PURPLE_NERPLE, 0x0E),
    MOTION(SM042_PURPLE_NERPLE, 0x0F),
    MOTION(SM042_PURPLE_NERPLE, 0x10),
    MOTION(SM042_PURPLE_NERPLE, 0x11),
    MOTION(SM042_PURPLE_NERPLE, 0x12),
};
// clang-format on
