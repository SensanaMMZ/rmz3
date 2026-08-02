#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"
#include "vfx.h"
#include "mission.h"
#include "entity/macros.h"

static const EnemyFunc sDeads[3];

#include "entity/macros.h"

void FUN_0807b0d0(s32 x, s32 y) {
  struct Enemy* e = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (e != NULL) {
    (e->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(e, 29);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).work[0] = 0;
    (e->s).coord.x = x;
    (e->s).coord.y = y;
  }
}

void FUN_0807b124(s32 x, s32 y, s32 dx, s32 dy) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 29);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = dx;
    (p->s).d.y = dy;
  }
}

void FUN_0807b184(s32 x, s32 y) {
  struct Enemy* e = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (e != NULL) {
    (e->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(e, 29);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).work[0] = 1;
    (e->s).coord.x = x;
    (e->s).coord.y = y;
  }
}

void nop_0807b1dc(struct Enemy* p) {}

void WormerSnowBall_Die(struct Enemy* p);


static bool8 FUN_0807b1e0(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = (p->s).work[0];
    WormerSnowBall_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const u8 sInitModes[4];
static const struct Collision sCollisions[17];
void WormerSnowBall_Update(struct Enemy* p);

void WormerSnowBall_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] <= 1) {
    INIT_BODY(p, sCollisions, 2, NULL);
  } else {
    INIT_BODY(p, sCollisions, 6, NULL);
  }
  SET_BODY_INTERSECT_HANDLER(p, nop_0807b1dc);
  WormerSnowBall_Update(p);
}

extern const EnemyFunc sUpdates1[4];
extern const EnemyFunc sUpdates2[4];

void WormerSnowBall_Update(struct Enemy* p) {
  if (!FUN_0807b1e0(p)) {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

void WormerSnowBall_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_0807b308(struct Enemy* p) {}


void FUN_0807b30c(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_B2) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/wormer_snow_ball_p3_p2_p1.inc");

// 0x0807B408
void FUN_0807b408(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = m;
      SetMotion(&p->s, 0x4000);
      (p->s).mode[2]++;
    case 1:
      (p->s).work[2] += 6;
      (p->s).coord.x += gSineTable[(p->s).work[2]] / 4;
      (p->s).coord.y += 0x60;
      if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
        SET_ENEMY_ROUTINE(p, 2);
        (p->s).mode[1] = (p->s).work[0];
      } else {
        UpdateMotionGraphic(&p->s);
      }
      break;
  }
}

u8 makeZeroSlower(struct Zero* z, u8 val);
void CreateIceballParticle2(s32 x, s32 y);

void FUN_0807b494(struct Enemy* p) {
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0: {
      CreateIceballParticle2((p->s).coord.x, (p->s).coord.y);
      (p->s).taskCol = 0xF;
      (p->body).status = md;
      (p->body).prevStatus = md;
      (p->body).invincibleTime = md;
      (p->s).flags &= ~COLLIDABLE;
      makeZeroSlower(pZero2, 0x18);
      (p->s).work[2] = 0x80;
      (p->s).d.x = 0x18;
      {
        s32 dx = (p->s).coord.x - (pZero2->s).coord.x;
        (p->s).unk_coord.x = dx;
        if (dx < -0xA00) {
          (p->s).unk_coord.x = -0xA00;
        } else if (dx > 0xA00) {
          (p->s).unk_coord.x = 0xA00;
        }
      }
      {
        s32 dy = (p->s).coord.y - (pZero2->s).coord.y;
        (p->s).unk_coord.y = dy;
        if (dy < -0x1800) {
          (p->s).unk_coord.y = -0x1800;
        } else if (dy > 0) {
          (p->s).unk_coord.y = 0;
        }
      }
      SetMotion(&p->s, MOTION(0x40, 0x03));
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      struct Zero* z = pZero2;
      s32 nd;
      (p->s).coord.x = (z->s).coord.x + (p->s).unk_coord.x;
      (p->s).coord.y = (z->s).coord.y + (p->s).unk_coord.y;
      (p->s).work[2]--;
      nd = (p->s).d.x - CountButtonMashing(z);
      (p->s).d.x = nd;
      if ((p->s).work[2] == 0) {
        goto rel;
      }
      if (nd < 0) {
        goto rel;
      }
      {
        struct Zero* z2 = pZero2;
        if ((*(u32*)((u8*)z2 + 0x8c) & 0x200) != 0) {
          goto rel;
        }
        if (*(s16*)((u8*)z2 + 0xa4) != 0) {
          goto upd;
        }
      }
    rel:
      makeZeroFaster(pZero2, 0x18);
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      (p->s).mode[1] = (p->s).work[0];
      WormerSnowBall_Die(p);
      break;
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/enemy/wormer_snow_ball_p3_p2_p1_b.inc");

void CreateIceballParticle2(s32 x, s32 y);

void FUN_0807b7c0(struct Enemy* p) {
  EXIT_BODY(p);
  CreateIceballParticle2((p->s).coord.x, (p->s).coord.y);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
void CreateIceballParticle4(s32 x, s32 y);

void FUN_0807b800(struct Enemy* p) {
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  EXIT_BODY(p);
  CreateIceballParticle4((p->s).coord.x, (p->s).coord.y);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void WormerSnowBall_Init(struct Enemy* p);
void WormerSnowBall_Update(struct Enemy* p);
void WormerSnowBall_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gWormerSnowBallRoutine = {
    [ENTITY_INIT] =      WormerSnowBall_Init,
    [ENTITY_UPDATE] =    WormerSnowBall_Update,
    [ENTITY_DIE] =       WormerSnowBall_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0807b30c(struct Enemy* p);
void FUN_0807b308(struct Enemy* p);

static const EnemyFunc sUpdates1[4] = {
    FUN_0807b30c,
    FUN_0807b30c,
    FUN_0807b308,
    FUN_0807b308,
};

void FUN_0807b328(struct Enemy* p);
void FUN_0807b408(struct Enemy* p);
void FUN_0807b494(struct Enemy* p);
void FUN_0807b5b8(struct Enemy* p);

static const EnemyFunc sUpdates2[4] = {
    FUN_0807b328,
    FUN_0807b408,
    FUN_0807b494,
    FUN_0807b5b8,
};

void FUN_0807b7c0(struct Enemy* p);
void FUN_0807b800(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_0807b7c0,
    FUN_0807b7c0,
    FUN_0807b800,
};

// --------------------------------------------

static const struct Collision sCollisions[17] = {
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
      damage : 255,
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
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
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
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(22), PIXEL(22)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(22), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(24), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(24), PIXEL(24)},
    },
};

static const u8 sInitModes[4] = {0, 1, 3, 0};
