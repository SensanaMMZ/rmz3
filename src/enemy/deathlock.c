#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "story.h"

static const EnemyFunc sDeads[4];

void FUN_0808d0b0(s32 x, s32 y, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_DEATHLOCK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = mode;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

void FUN_0808d10c(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_DEATHLOCK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 9;
    (p->s).unk_28 = e;
  }
}

// Wall probe: shifts by dx, takes three pushouts at y/-0xF00/-0x1E00,
// sorts them (descending left-arm, ascending right-arm) and applies the
// extreme. Retail keeps the sort index i in r0 (disjoint from the pj
// walker) while agbcc coalesces i into the pi register (allocation tie;
// pins/barriers shift but never split them).
NON_MATCH s32 FUN_0808d160(struct Enemy* p, s32 dx) {
#if MODERN
  s32 r[3];
  s32 i;
  (p->s).coord.x += dx;
  if (dx < 0) {
    r[0] = PushoutToRight1((p->s).coord.x - 0x1200, (p->s).coord.y);
    r[1] = PushoutToRight1((p->s).coord.x - 0x1200, (p->s).coord.y - 0xF00);
    r[2] = PushoutToRight1((p->s).coord.x - 0x1200, (p->s).coord.y - 0x1E00);
    i = 0;
    while (i <= 1) {
      s32 j0 = i + 1;
      s32 j = j0;
      if (j0 <= 2) {
        s32* pi = &r[i];
        s32* pj = &r[j0];
        for (; j <= 2; j++, pj++) {
          s32 a = *pi;
          s32 b = *pj;
          if (a < b) {
            *pi = b;
            *pj = a;
          }
        }
      }
      i = j0;
    }
    if (r[0] > 0) {
      (p->s).coord.x += r[0];
      return 1;
    }
  } else {
    r[0] = PushoutToLeft1((p->s).coord.x + 0x1200, (p->s).coord.y);
    r[1] = PushoutToLeft1((p->s).coord.x + 0x1200, (p->s).coord.y - 0xF00);
    r[2] = PushoutToLeft1((p->s).coord.x + 0x1200, (p->s).coord.y - 0x1E00);
    i = 0;
    while (i <= 1) {
      s32 j0 = i + 1;
      s32 j = j0;
      if (j0 <= 2) {
        s32* pi = &r[i];
        s32* pj = &r[j0];
        for (; j <= 2; j++, pj++) {
          s32 a = *pi;
          s32 b = *pj;
          if (a > b) {
            *pi = b;
            *pj = a;
          }
        }
      }
      i = j0;
    }
    if (r[0] < 0) {
      (p->s).coord.x += r[0];
      return 2;
    }
  }
  return 0;
#else
  INCCODE("asm/enemy/deathlock_d160.inc");
#endif
}

INCASM("asm/enemy/deathlock_pre_p1_p3.inc");

void nop_0808d2f4(struct Enemy* p) {}

void Deathlock_Die(struct Enemy* p);

bool8 FUN_0808d2f8(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->s).work[0] == 9) {
      (p->s).mode[1] = 0;
    } else if ((p->body).status & 0x10000) {
      p->props[7] = 1;
      (p->s).mode[1] = 2;
    } else {
      p->props[7] = 0;
      if ((p->body).status & 0x20000) {
        (p->s).mode[1] = 3;
      } else {
        (p->s).mode[1] = 1;
      }
    }
    Deathlock_Die(p);
    return TRUE;
  }
  return FALSE;
}

INCASM("asm/enemy/deathlock_pre_p2_pre_a.inc");

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_0808d4a0(struct Enemy* p) {
  struct VFX** slot;
  u32 frozen;

  if ((p->s).work[0] != 8 && (p->s).work[0] != 9) {
    slot = (struct VFX**)&p->props[0];
    if (*slot == NULL && ((p->body).status & 1)) {
      frozen = (p->body).status & 0x20000;
      if (frozen != 0) {
        (p->s).mode[1] = 6;
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

INCASM("asm/enemy/deathlock_pre_p2_pre_a_b.inc");

static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];
bool8 FUN_0808d2f8(struct Enemy* p);
void FUN_0808d4a0(struct Enemy* p);
bool8 FUN_0808d370(struct Enemy* p);

void Deathlock_Update(struct Enemy* p) {
  if ((p->s).work[0] != 8 && (gCurStory.s.gameflags[4] & 2)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (FUN_0808d2f8(p)) {
    return;
  }
  FUN_0808d4a0(p);
  if (FUN_0808d370(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Deathlock_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_0808d6f4(struct Enemy* p) {}

extern const struct Collision sCollisions[15];
extern const u8 sCollisionIdxs1[6];

void FUN_0808d6f8(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[sCollisionIdxs1[*(u8*)((u8*)p + 0xb9)]]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x20001) == 0x20001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

void FUN_0808d76c(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/deathlock_post_p2.inc");

void Deathlock_Init(struct Enemy* p);
void Deathlock_Update(struct Enemy* p);
void Deathlock_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gDeathlockRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Deathlock_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Deathlock_Update,
    [ENTITY_DIE] =       (EnemyFunc)Deathlock_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_0808d6f8(struct Enemy* p);
void FUN_0808d76c(struct Enemy* p);
void FUN_0808d6f4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    FUN_0808d6f8,
    FUN_0808d76c,
    FUN_0808d76c,
    FUN_0808d6f4,
    FUN_0808d76c,
    FUN_0808d6f4,
    FUN_0808d6f4,
    FUN_0808d6f4,
};
// clang-format on

void FUN_0808d78c(struct Enemy* p);
void FUN_0808d898(struct Enemy* p);
void FUN_0808da24(struct Enemy* p);
void FUN_0808db64(struct Enemy* p);
void FUN_0808dd7c(struct Enemy* p);
void FUN_0808deb8(struct Enemy* p);
void FUN_0808e01c(struct Enemy* p);
void FUN_0808e18c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    FUN_0808d78c,
    FUN_0808d898,
    FUN_0808da24,
    FUN_0808db64,
    FUN_0808dd7c,
    FUN_0808deb8,
    FUN_0808e01c,
    FUN_0808e18c,
};
// clang-format on

// --------------------------------------------

void FUN_0808e228(struct Enemy* p);
void maybeKillDeathlock(struct Enemy* p);
void FUN_0808e358(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_0808e228,
    maybeKillDeathlock,
    FUN_0808e358,
    FUN_0808e01c,
};

// --------------------------------------------

// 0x08369198
static const struct Collision sCollisions[15] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(14), PIXEL(34), PIXEL(33)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(14), PIXEL(34), PIXEL(33)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(9), -PIXEL(24), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {PIXEL(9), -PIXEL(24), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(4), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(4), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(8), PIXEL(19), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(8), -PIXEL(8), PIXEL(19), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(14), PIXEL(34), PIXEL(33)},
    },
};

// clang-format off
static const motion_t sMotions1[6] = {
    MOTION(SM116_DEATHLOCK, 1),
    MOTION(SM116_DEATHLOCK, 4),
    MOTION(SM116_DEATHLOCK, 5),
    MOTION(SM116_DEATHLOCK, 6),
    MOTION(SM116_DEATHLOCK, 7),
    MOTION(SM116_DEATHLOCK, 8),
};
// clang-format on

static const u8 sCollisionIdxs1[6] = {2, 4, 8, 10, 10, 12};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(12)};

static const u8 sCollisionIdxs2[6] = {3, 6, 9, 11, 11, 13};

static const motion_t sMotions2[4] = {
    MOTION(SM116_DEATHLOCK, 17),
    MOTION(SM116_DEATHLOCK, 18),
    MOTION(SM116_DEATHLOCK, 19),
    MOTION(SM116_DEATHLOCK, 14),
};
