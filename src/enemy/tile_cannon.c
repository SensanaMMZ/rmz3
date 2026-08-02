#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "vfx.h"
#include "motion.h"
#include "projectile.h"
#include "story.h"
#include "syssav.h"

static const struct Collision sCollisions[9];

bool8 FUN_080780c4(struct Enemy* p) {
  struct Enemy* parent = (struct Enemy*)(p->s).unk_2c;
  if ((parent->s).mode[0] > 1) {
    if ((parent->body).hp == 0) {
      SetMotion(&p->s, (p->s).work[0] | 0x2f00);
      UpdateMotionGraphic(&p->s);
      (p->s).work[2] = 0x78;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
      return TRUE;
    }
  }
  return FALSE;
}

struct Enemy* FUN_08078108(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_TILE_CANNON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y;
    (p->s).unk_28 = e;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = e->uniqueID;
  }
  return p;
}

void FUN_08078170(struct Enemy* p) {}

void TileCannon_Die(struct Enemy* p);


static bool8 tilecannon_08078174(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    TileCannon_Die(p);
    return TRUE;
  }
  return FALSE;
}

extern const EnemyFunc sUpdates1[9];
extern const EnemyFunc sUpdates2[9];

bool8 tilecannon_08078198(struct Enemy* p) {
  switch ((p->s).mode[3]) {
    case 0:
      if (IsFrozen(&p->s)) {
        (sUpdates1[(p->s).mode[1]])(p);
        (sUpdates2[(p->s).mode[1]])(p);
        (p->s).mode[3]++;
        UpdateMotionGraphic(&p->s);
        return 1;
      }
      break;
    case 1: {
      s32 r;
      if ((p->s).mode[1] == 3) {
        FUN_080780c4(p);
      }
      r = IsFrozen(&p->s);
      if (r) {
        return 1;
      }
      (p->s).mode[3] = r;
      break;
    }
  }
  return 0;
}

static const struct Coord sElementCoord;

void tilecannon_08078210(struct Enemy* p) {
  if (*(struct VFX**)&p->props[0] == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *(struct VFX**)&p->props[0] = e;
    if (e != NULL) {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
  }
}

static const u8 sInitModes[3];
void TileCannon_Update(struct Enemy* p);

void TileCannon_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] != 2) {
    INIT_BODY(p, sCollisions, 1, NULL);
    (p->s).coord.x += PIXEL(8);
    (p->s).coord.y += PIXEL(9);
  } else {
    if ((gSystemSavedataManager.mods[14] & 2) && !FLAG(gCurStory.s.gameflags, 6)) {
      INIT_BODY(p, &sCollisions[7], 10, NULL);
    } else {
      INIT_BODY(p, &sCollisions[7], 6, NULL);
    }
  }
  SET_BODY_INTERSECT_HANDLER(p, FUN_08078170);
  *(u32*)&p->props[0] = 0;
  (p->s).work[2] = 0x28;
  (p->s).taskCol = 0x1F;
  TileCannon_Update(p);
}

extern const EnemyFunc sUpdates1[9];
extern const EnemyFunc sUpdates2[9];
bool8 tilecannon_08078198(struct Enemy* p);

void TileCannon_Update(struct Enemy* p) {
  if ((p->s).work[0] == 2) {
    if (((p->s).unk_28)->mode[0] > 1) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      EXIT_BODY(p);
      (p->s).flags &= ~COLLIDABLE;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
    tilecannon_08078210(p);
    if (tilecannon_08078174(p)) {
      return;
    }
  } else {
    if (tilecannon_08078198(p)) {
      return;
    }
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

static const motion_t sMotions[3];
struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x080783e8
void TileCannon_Die(struct Enemy* p) {
  struct Coord c;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  {
    u8 f = ~DISPLAY & (p->s).flags;
    s32 z = 0;
    (p->s).flags = f;
    (p->body).status = z;
    (p->body).prevStatus = z;
    (p->body).invincibleTime = z;
    (p->s).flags &= ~COLLIDABLE;
  }
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7f70(&p->s, &c, (motion_t*)sMotions, 3);
  TryDropItem(0, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_0807847c(struct Enemy* p) {}

void FUN_08078480(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[7]);
    *slot = NULL;
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

void FUN_080784b4(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[8]);
    (p->s).mode[2]++;
  }
}

void FUN_080784d8(struct Enemy* p) {
  u32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetDDP(&p->body, sCollisions);
      p->props[4] = m;
      (p->s).flags &= ~X_FLIP;
      (p->s).spr.xflip = m;
      (p->s).spr.oam.xflip = 0;
      SetMotion(&p->s, (p->s).work[0] | MOTION(0x2f, 0x00));
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((u8)--(p->s).work[2] == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

static const u8 u8_ARRAY_0836754a[6];

// 0x08078550
void FUN_08078550(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, (p->s).work[0] | MOTION(0x2F, 0x00));
      (p->s).mode[2]++;
    case 1: {
      u8 t;
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[u8_ARRAY_0836754a[(s8) * (u8*)((u8*)p + 0x71)]]);
      t = *(u8*)((u8*)p + 0x73);
      if (t == 3) {
        u8 z = 0;
        (p->s).mode[1] = t;
        (p->s).mode[2] = z;
      }
      break;
    }
  }
}

void FUN_080785bc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, sCollisions);
      (p->s).unk_2c = (struct Entity*)FUN_08078108(&p->s);
      SetMotion(&p->s, MOTION(0x2f, 0x04) + (p->s).work[0]);
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      u8 r = FUN_080780c4(p);
      if (r == 0 && p->props[4] != 0) {
        (p->s).mode[1] = 8;
        (p->s).mode[2] = r;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_08078624(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x2f, 6));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/tile_cannon_p3_post_post.inc");

// 0x0807874c -- parked (truncation-idiom basin): retail truncates the
// work[2] decrement with lsls/lsrs #24 into r1; agbcc emits movs #0xFF +
// ands in every spelling (u8 var, s32+(u8) cast, r1 pin), and keeps
// case 2's mode[2]++ store separate where retail shares case 4's strb.
NON_MATCH void FUN_0807874c(struct Enemy* p) {
#if MODERN
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 2;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      struct Coord c;
      u8 a = (p->s).angle;
      c.x = (p->s).coord.x;
      c.x = gSineTable[(u8)(a + 0x80)] * 14 + (p->s).coord.x;
      c.y = (p->s).coord.y;
      c.y = gSineTable[(u8)(a + 0x40)] * 14 + (p->s).coord.y;
      CreateLemon(&c, 0x200, a - 0x40);
      PlaySound(0x2C);
      SetMotion(&p->s, MOTION(0x2F, 0x08));
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 3:
      (p->s).work[3] = 4;
      (p->s).mode[2]++;
      /* fallthrough */
    case 4:
      if (IsFrozen(q)) {
        break;
      }
      {
        u8 t;
        if ((u8)--(p->s).work[3] != 0) {
          break;
        }
        t = --(p->s).work[2];
        if (t != 0) {
          (p->s).mode[2] = 1;
          break;
        }
        (p->s).mode[1] = 7;
        (p->s).mode[2] = t;
      }
      break;
  }
#else
  INCCODE("asm/enemy/tile_cannon_874c.inc");
#endif
}

INCASM("asm/enemy/tile_cannon_p3_post_post_b.inc");

static const u8 u8_ARRAY_08367550[6];

// 0x08078908
void FUN_08078908(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, 1);
      SetMotion(&p->s, MOTION(0x2F, 0x02) + (p->s).work[0]);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[u8_ARRAY_08367550[(s8)(p->s).motion.cmdIdx]]);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
        (p->s).work[2] = 0x3C;
      }
      break;
  }
}

void TileCannon_Init(struct Enemy* p);
void TileCannon_Update(struct Enemy* p);
void TileCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gTileCannonRoutine = {
    [ENTITY_INIT] =      TileCannon_Init,
    [ENTITY_UPDATE] =    TileCannon_Update,
    [ENTITY_DIE] =       TileCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_08078480(struct Enemy* p);
void FUN_0807847c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[9] = {
    FUN_08078480,
    FUN_0807847c,
    FUN_0807847c,
    FUN_0807847c,
    FUN_0807847c,
    FUN_0807847c,
    FUN_0807847c,
    FUN_0807847c,
    FUN_0807847c,
};
// clang-format on

void FUN_080784b4(struct Enemy* p);
void FUN_080784d8(struct Enemy* p);
void FUN_08078550(struct Enemy* p);
void FUN_080785bc(struct Enemy* p);
void FUN_08078624(struct Enemy* p);
void FUN_08078664(struct Enemy* p);
void FUN_0807874c(struct Enemy* p);
void FUN_0807884c(struct Enemy* p);
void FUN_08078908(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[9] = {
    FUN_080784b4,
    FUN_080784d8,
    FUN_08078550,
    FUN_080785bc,
    FUN_08078624,
    FUN_08078664,
    FUN_0807874c,
    FUN_0807884c,
    FUN_08078908,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[9] = {
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
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      hardness : METAL,
      remaining : 1,
      range : {PIXEL(1), PIXEL(0), PIXEL(10), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(8), PIXEL(0), PIXEL(13), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {-PIXEL(8), PIXEL(0), PIXEL(13), PIXEL(17)},
    },
    {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : METAL,
      remaining : 1,
      range : {PIXEL(10), PIXEL(0), PIXEL(10), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(1), PIXEL(0), PIXEL(13), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {-PIXEL(1), PIXEL(0), PIXEL(13), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};

static const u8 sInitModes[3] = {1, 1, 4};

static const motion_t sMotions[3] = {
    MOTION(SM047_TILE_CANNON, 9),
    MOTION(SM047_TILE_CANNON, 10),
    MOTION(SM047_TILE_CANNON, 11),
};

static const u8 u8_ARRAY_0836754a[6] = {
    0, 0, 0, 1, 4, 4,
};

static const u8 u8_ARRAY_08367550[6] = {
    4, 4, 1, 0, 0, 0,
};
