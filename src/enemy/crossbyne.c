#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "motion.h"
#include "story.h"
#include "syssav.h"

static const motion_t sMotions[19];

static const struct Collision sCollisions[5];

void Crossbyne_Init(struct Enemy* p);
void Crossbyne_Update(struct Enemy* p);
void Crossbyne_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gCrossbyneRoutine = {
    [ENTITY_INIT] =      Crossbyne_Init,
    [ENTITY_UPDATE] =    Crossbyne_Update,
    [ENTITY_DIE] =       Crossbyne_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Entity* FUN_0807cbf4(s32 x, s32 y, u8 n) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CROSSBYNE);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = n;
    (p->coord).x = x, (p->coord).y = y;
  }
  return p;
}

static const struct Coord16 Coord16_ARRAY_08367c14[4];

// 0x0807cc50
static void FUN_0807cc50(s32 x, s32 y) {
  s32 i;
  const struct Coord16* c = Coord16_ARRAY_08367c14;

  for (i = 0; i < (s32)ARRAY_COUNT(Coord16_ARRAY_08367c14); i++) {
    struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
    if (p != NULL) {
      p->taskCol = 24;
      INIT_ENEMY_ROUTINE(p, ENEMY_CROSSBYNE);
      p->tileNum = 0, p->palID = 0;
      p->flags2 |= WHITE_PAINTABLE;
      p->invincibleID = p->uniqueID;
      p->work[0] = 2, p->work[1] = i;
      (p->coord).x = x;
      (p->coord).x += c[i].x;
      (p->coord).y = y;
      (p->coord).y += c[i].y;
    }
  }
}

static const EnemyFunc sDeads[3];

static const struct Coord16 Coord16_ARRAY_08367c24[4];

void FUN_0807cce0(s32 x, s32 y) {
  s32 i;
  const struct Coord16* c = Coord16_ARRAY_08367c24;

  for (i = 0; i < (s32)ARRAY_COUNT(Coord16_ARRAY_08367c24); i++) {
    struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
    if (p != NULL) {
      p->taskCol = 24;
      INIT_ENEMY_ROUTINE(p, ENEMY_CROSSBYNE);
      p->tileNum = 0, p->palID = 0;
      p->flags2 |= WHITE_PAINTABLE;
      p->invincibleID = p->uniqueID;
      p->work[0] = 3, p->work[1] = i;
      (p->coord).x = x;
      (p->coord).x += c[i].x;
      (p->coord).y = y;
      (p->coord).y += c[i].y;
    }
  }
}

void nop_0807cd70(struct Enemy* p) {}


bool8 FUN_0807cd74(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->s).work[0] <= 1) {
      u32 t = (p->body).status & BODY_STATUS_SLASHED;
      if (t != 0) {
        (p->s).mode[1] = 1;
      } else {
        (p->s).mode[1] = t;
      }
    } else {
      (p->s).mode[1] = 2;
    }
    return 1;
  }
  return 0;
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void crossbyne_0807cdc4(struct Enemy* p) {
  struct VFX** slot;

  if ((p->s).work[0] <= 1 && (p->s).mode[1] == 2) {
    slot = (struct VFX**)&p->props[0];
    if (*slot == NULL && ((p->body).status & 1)) {
      *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
      if (*slot != NULL) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
    }
  }
}

static const u8 sInitModes[4];

void Crossbyne_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] > 1) {
    INIT_BODY(p, sCollisions, 2, NULL);
  } else if ((gSystemSavedataManager.mods[9] & 4) && !FLAG(gCurStory.s.gameflags, 6)) {
    INIT_BODY(p, sCollisions, 8, NULL);
  } else {
    INIT_BODY(p, sCollisions, 4, NULL);
  }
  SET_BODY_INTERSECT_HANDLER(p, nop_0807cd70);
  *(u32*)&p->props[0] = 0;
  p->props[4] = 1;
  (p->s).taskCol = 0x14;
  Crossbyne_Update(p);
}


extern const EnemyFunc sUpdates1[7];
extern const EnemyFunc sUpdates2[7];
bool8 FUN_0807cd74(struct Enemy* p);
void crossbyne_0807cdc4(struct Enemy* p);

void Crossbyne_Update(struct Enemy* p) {
  if (!FUN_0807cd74(p)) {
    crossbyne_0807cdc4(p);
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

void Crossbyne_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_0807cf5c(struct Enemy* p) {}

void FUN_0807cf60(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

void FUN_0807cf88(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}


void FUN_0807cfac(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x12b);
      SetMotion(&p->s, sMotions[(p->s).work[0]]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/crossbyne_p3_post_post.inc");

void FUN_0807d000(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x20;
      SetDDP(&p->body, &sCollisions[1]);
      {
        const motion_t* t = &sMotions[2];
        SetMotion(&p->s, t[(p->s).work[0]]);
      }
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((u8)--(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.cmdIdx == 3) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

void crossbyne_0807d080(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x2C);
      if ((p->s).work[0] == 0) {
        FUN_0807cc50((p->s).coord.x, (p->s).coord.y);
      } else {
        FUN_0807cce0((p->s).coord.x, (p->s).coord.y);
      }
      p->props[4] = 0;
      {
        const motion_t* t = &sMotions[4];
        SetMotion(&p->s, t[(p->s).work[0]]);
      }
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x0807d0f0
void FUN_0807d0f0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      const motion_t* t;
      SetDDP(&p->body, sCollisions);
      t = &sMotions[6];
      SetMotion(&p->s, t[(p->s).work[0]]);
    }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u8 f = ~DISPLAY & (p->s).flags;
        s32 z = 0;
        f = f & ~FLIPABLE;
        (p->s).flags = f;
        (p->body).status = z;
        (p->body).prevStatus = z;
        (p->body).invincibleTime = z;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

// 0x0807D178
void FUN_0807d178(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8 w0;
      SetDDP(&p->body, &sCollisions[3]);
      w0 = (p->s).work[1];
      if (w0 <= 1) {
        u32 z3;
        SetMotion(&p->s, MOTION(0x43, 0x13));
        SET_XFLIP(p, (p->s).work[1]);
        z3 = 0;
        (p->s).d.x = ((p->s).work[1] << 10) - 0x200;
        (p->s).d.y = z3;
      } else {
        u32 one;
        u32 m = 1;
        u32 z5;
        m &= w0;
        if (m != 0) {
          (p->s).flags |= 0x20;
        } else {
          (p->s).flags &= 0xDF;
        }
        one = 1;
        {
          u32 yv = one;
          yv &= m;
          ((p->s).spr).yflip = yv;
          z5 = 0;
          {
            u8* oa = (u8*)p + 0x4a;
            u32 sh5 = yv << 5;
            s32 ov = *oa;
            s32 m21 = -0x21;
            m21 &= ov;
            m21 |= sh5;
            *oa = m21;
          }
        }
        SetMotion(&p->s, MOTION(0x43, 0x12));
        (p->s).d.x = z5;
        one &= (p->s).work[1];
        (p->s).d.y = (one << 10) - 0x200;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x1000) {
        u32 z;
        register u8 t asm("r1");
        u8 fv;
        t = (p->s).flags;
        fv = 0xFE;
        fv &= t;
        asm volatile("" ::"r"(t));
        z = 0;
        fv &= 0xFD;
        (p->s).flags = fv;
        (p->body).status = z;
        (p->body).prevStatus = z;
        (p->body).invincibleTime = z;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

INCASM("asm/enemy/crossbyne_p3_post_postb.inc");

// 0x0807D2B8
void FUN_0807d2b8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 k;
      u32 a;
      u32 b;
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, MOTION(0x43, 0x14));
      k = -0x160;
      a = (p->s).work[1] & 1;
      (p->s).d.x = a * 0x2C0 + k;
      b = ((u8)(p->s).work[1] >> 1) & 1;
      (p->s).d.y = b * 0x2C0 + k;
      SET_XFLIP(p, a);
      SET_YFLIP(p, ((p->s).work[1] >> 1) & 1);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x1000) {
        u32 z;
        u8 t = (p->s).flags;
        register u8 fv asm("r0");
        fv = 0xFE;
        fv &= t;
        asm volatile("" ::"r"(t));
        z = 0;
        fv &= 0xFD;
        (p->s).flags = fv;
        (p->body).status = z;
        (p->body).prevStatus = z;
        (p->body).invincibleTime = z;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

extern void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

void MaybeKillCrossbyne(struct Enemy* p) {
  struct Coord c;
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  {
    u8 f = (p->s).flags & ~COLLIDABLE;
    f &= ~DISPLAY;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7ffc(&p->s, &c, (motion_t*)&sMotions[8], 3);
  TryDropItem(0, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/crossbyne_p3_post_postc.inc");

// 0x0807D5C4
void FUN_0807d5c4(struct Enemy* p) {
  struct Coord c;
  register u8* q asm("r0");
  u32 z;
  q = (u8*)p + 0x8c;
  z = 0;
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *q = z;
  (p->s).flags &= 0xFB;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  CreateSmoke(2, &c);
  SET_ENEMY_ROUTINE(p, 4);
}

// --------------------------------------------

void FUN_0807cf5c(struct Enemy* p);
void FUN_0807cf60(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    FUN_0807cf60,
    FUN_0807cf5c,
    FUN_0807cf5c,
    FUN_0807cf5c,
    FUN_0807cf5c,
    FUN_0807cf5c,
    FUN_0807cf5c,
};
// clang-format on

void FUN_0807cf88(struct Enemy* p);
void FUN_0807cfac(struct Enemy* p);
void FUN_0807d000(struct Enemy* p);
void crossbyne_0807d080(struct Enemy* p);
void FUN_0807d0f0(struct Enemy* p);
void FUN_0807d178(struct Enemy* p);
void FUN_0807d2b8(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    FUN_0807cf88,
    FUN_0807cfac,
    FUN_0807d000,
    crossbyne_0807d080,
    FUN_0807d0f0,
    FUN_0807d178,
    FUN_0807d2b8,
};
// clang-format on

void MaybeKillCrossbyne(struct Enemy* p);
void FUN_0807d478(struct Enemy* p);
void FUN_0807d5c4(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    MaybeKillCrossbyne,
    FUN_0807d478,
    FUN_0807d5c4,
};

// --------------------------------------------

static const struct Collision sCollisions[5] = {
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
      range : {PIXEL(0), PIXEL(0), PIXEL(28), PIXEL(28)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(28), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
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
};

static const struct Coord16 Coord16_ARRAY_08367c14[4] = {
    {-PIXEL(14), PIXEL(0)},
    {PIXEL(14), PIXEL(0)},
    {PIXEL(0), -PIXEL(14)},
    {PIXEL(0), PIXEL(14)},
};

static const struct Coord16 Coord16_ARRAY_08367c24[4] = {
    {-PIXEL(9), -PIXEL(9)},
    {PIXEL(9), -PIXEL(9)},
    {-PIXEL(9), PIXEL(9)},
    {PIXEL(9), PIXEL(9)},
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
static const u8 sInitModes[4] = {1, 1, 5, 6};

// clang-format off
static const motion_t sMotions[19] = {
    MOTION(SM067_CROSSBYNE, 0x00),
    MOTION(SM067_CROSSBYNE, 0x01),
    MOTION(SM067_CROSSBYNE, 0x04),
    MOTION(SM067_CROSSBYNE, 0x05),
    MOTION(SM067_CROSSBYNE, 0x10),
    MOTION(SM067_CROSSBYNE, 0x11),
    MOTION(SM067_CROSSBYNE, 0x02),
    MOTION(SM067_CROSSBYNE, 0x03),
    MOTION(SM067_CROSSBYNE, 0x15),
    MOTION(SM067_CROSSBYNE, 0x16),
    MOTION(SM067_CROSSBYNE, 0x17),
    MOTION(SM067_CROSSBYNE, 0x09),
    MOTION(SM067_CROSSBYNE, 0x07),
    MOTION(SM067_CROSSBYNE, 0x0D),
    MOTION(SM067_CROSSBYNE, 0x0B),
    MOTION(SM067_CROSSBYNE, 0x08),
    MOTION(SM067_CROSSBYNE, 0x06),
    MOTION(SM067_CROSSBYNE, 0x0C),
    MOTION(SM067_CROSSBYNE, 0x0A),
};
// clang-format on
