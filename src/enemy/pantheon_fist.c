#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "story.h"
#include "metatile.h"

static const struct Collision sCollisions[];

struct Enemy* createPantheonFistInElevator(s32 x, s32 y, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_FIST);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    p->props[5] = a2;
  }
  return p;
}

bool8 FUN_08094fa8(struct Enemy* p, s32 d) {
  s32 x = (p->s).coord.x;
  x -= PIXEL(14);
  if (d > 0) {
    x += PIXEL(28);
  }
  if (FUN_080098a4(x, (p->s).coord.y + PIXEL(10)) != 0) {
    return TRUE;
  }
  return FALSE;
}

bool8 FUN_08094fe0(struct Enemy* p, s32 dy) {
  if (dy > 0) {
    s32 diff;
    (p->s).coord.y += dy;
    diff = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - (p->s).coord.y;
    if (diff <= 0x7ff) {
      (p->s).coord.y = (p->s).coord.y + diff;
      return TRUE;
    }
  }
  return FALSE;
}

u32 FUN_08095014(struct Enemy* p, s32 d) {
  if (d != 0) {
    if (d < 0) {
      if (FUN_080098a4((p->s).coord.x - PIXEL(14), (p->s).coord.y - PIXEL(10)) != 0) {
        return 1;
      }
    } else {
      if (FUN_080098a4((p->s).coord.x + PIXEL(14), (p->s).coord.y - PIXEL(10)) != 0) {
        return 2;
      }
    }
    (p->s).coord.x += d;
  }
  return 0;
}

INCASM("asm/enemy/pantheon_fist_pre_p1_p2_p2.inc");

void nop_080950cc(struct Enemy* p) {}

bool8 FUN_080950d0(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else if ((p->body).status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    return TRUE;
  }
  return FALSE;
}


extern const EnemyFunc sUpdates1[];
extern const EnemyFunc sUpdates2[];

// 0x08095124
bool8 FUN_08095124(struct Enemy* p) {
  if ((p->s).mode[1] != 7) {
    s32 v = *(s32*)&p->props[0];
    if (v == 0) {
      switch ((p->s).mode[3]) {
        case 0:
          if (IsFrozen(&p->s)) {
            (sUpdates1[(p->s).mode[1]])(p);
            (sUpdates2[(p->s).mode[1]])(p);
            (p->s).mode[3]++;
            UpdateMotionGraphic(&p->s);
            return TRUE;
          }
          break;
        case 1:
          if (IsFrozen(&p->s)) {
            if (((p->body).status & 0x00020001) == 0x00020001) {
              (p->s).mode[3] = 0;
            } else {
              return TRUE;
            }
          } else {
            (p->s).mode[3] = 0;
          }
          break;
      }
    }
  }
  return FALSE;
}

struct PantheonFistObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct VFX* elementEffect;
  u8 unk_004[12];
};
static_assert(sizeof(struct PantheonFistObject) == sizeof(struct Enemy));

static const struct Coord sElementCoord;

void FUN_080951b4(struct PantheonFistObject* p) {
  if (p->elementEffect == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    if (((p->body).status & BODY_STATUS_RECOILED)) {
      (p->s).mode[1] = 7;
      (p->s).mode[2] = 0;
    } else {
      p->elementEffect = ApplyElementEffect(0, &p->s, &sElementCoord);
      if (p->elementEffect != NULL) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
    }
  }
}

INCASM("asm/enemy/pantheon_fist_pre_p2_a_b.inc");


void PantheonFist_Update(struct Enemy* p) {
  if (!FUN_080950d0(p)) {
    FUN_080951b4((struct PantheonFistObject*)p);
    if (!FUN_08095124(p)) {
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
}


static const EnemyFunc sDeads[3];

// 0x08095340
void PantheonFist_Die(struct Enemy* p) {
  if ((p->s).work[1] == 0 && IS_METTAUR) {
    u8 fl = (p->s).flags & ~DISPLAY;
    (p->s).flags = fl & ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (sDeads[(p->s).mode[1]])(p);
  }
}

void FUN_080953ac(struct Enemy* p) {}


void FUN_080953b0(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}


void FUN_080953d0(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/pantheon_fist_post_p2_p2.inc");

void PantheonFist_Init(struct Enemy* p);
void PantheonFist_Update(struct Enemy* p);
void PantheonFist_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonFistRoutine = {
    [ENTITY_INIT] =      PantheonFist_Init,
    [ENTITY_UPDATE] =    PantheonFist_Update,
    [ENTITY_DIE] =       PantheonFist_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080953ac(struct Enemy* p);
void FUN_080953b0(struct Enemy* p);
void FUN_080953d0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[9] = {
    FUN_080953d0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953ac,
    FUN_080953b0,
};
// clang-format on

void FUN_0809542c(struct Enemy* p);
void FUN_080954a4(struct Enemy* p);
void FUN_08095578(struct Enemy* p);
void FUN_08095664(struct Enemy* p);
void FUN_08095778(struct Enemy* p);
void FUN_080957d4(struct Enemy* p);
void FUN_08095914(struct Enemy* p);
void FUN_0809596c(struct Enemy* p);
void FUN_08095ac4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[9] = {
    FUN_0809542c,
    FUN_080954a4,
    FUN_08095578,
    FUN_08095664,
    FUN_08095778,
    FUN_080957d4,
    FUN_08095914,
    FUN_0809596c,
    FUN_08095ac4,
};
// clang-format on

// --------------------------------------------

void FUN_08095b70(struct Enemy* p);
void FUN_08095c20(struct Enemy* p);
void FUN_0809596c(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_08095b70,
    FUN_08095c20,
    FUN_0809596c,
};

// --------------------------------------------

static const struct Collision sCollisions[6] = {
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
      damage : 3,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : BODY_NATURE_B2,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(22), -PIXEL(19), PIXEL(26), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(10), -PIXEL(13), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
static const u8 sInitModes[2] = {2, 0};

static const motion_t sMotions[4] = {
    MOTION(SM212_PANTHEON_FIST, 9),
    MOTION(SM212_PANTHEON_FIST, 10),
    MOTION(SM212_PANTHEON_FIST, 11),
    MOTION(SM212_PANTHEON_FIST, 7),
};
