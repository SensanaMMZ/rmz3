#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "mod.h"
#include "story.h"
#include "vfx.h"

struct GrandCannon {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct GrandCannonProps {
    struct VFX* elementEffect;
    u8 unk_004;
    u8 unk_005;
    u16 unk_006;
    bool8 is_right;
    u8 unk_009;
    u8 unk_00a;
    u8 unk_00b;
    u8 unk_00c[4];
  } props;
};
static_assert(sizeof(struct GrandCannon) == sizeof(struct Enemy));

static const struct Collision sCollisions[3];
static const struct Rect sSize;
static const motion_t sMotions[4];
static const struct Coord sElementCoord;
static const u8 sInitModes[2];

static const EnemyFunc sUpdates1[4];
static const EnemyFunc sUpdates2[4];
static const EnemyFunc sDeads[3];

static void GrandCannon_Init(struct GrandCannon* p);
static void GrandCannon_Update(struct Enemy* p);
static void GrandCannon_Die(struct Enemy* p);
static void GrandCannon_Dissappear(struct Entity* p);

// clang-format off
const EnemyRoutine gGrandCannonRoutine = {
    [ENTITY_INIT] =      (void*)GrandCannon_Init,
    [ENTITY_UPDATE] =    (void*)GrandCannon_Update,
    [ENTITY_DIE] =       (void*)GrandCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)GrandCannon_Dissappear,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// グランドキャノンの砲台の方を生成
void CreateGrandCannonBattery(struct Entity* e) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    p->unk_28 = e;
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_GRAND_CANNON);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = GRAND_CANNON_BATTERY;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = e->uniqueID;
  }
}

static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* e = (struct Entity*)body->enemy->parent;
    struct Enemy* self = (struct Enemy*)body->parent;
    if (*((u16*)&e->kind) == 0x304) {
      SET_ENEMY_ROUTINE(self, ENTITY_DIE);
      (self->s).mode[1] = 0;
    }
  }
}

static bool8 tryKillGrandCannon(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else {
      (p->s).mode[1] = 0;
    }
    GrandCannon_Die(p);
    return TRUE;
  }
  return FALSE;
}

static void nop_0806937c(struct Enemy* p);
static void grandcannon_08069380(struct GrandCannon* p);

static const EnemyFunc sUpdates1[4] = {
    (void*)nop_0806937c,
    (void*)nop_0806937c,
    (void*)nop_0806937c,
    (void*)grandcannon_08069380,
};

// --------------------------------------------

static void grandCannon_080693b4(struct Enemy* p);
void grandcannonMoveTurret(struct Enemy* p);
void grandcannonBombShot(struct Enemy* p);
void grandcannon_08069608(struct Enemy* p);

static const EnemyFunc sUpdates2[4] = {
    grandCannon_080693b4,
    grandcannonMoveTurret,
    grandcannonBombShot,
    grandcannon_08069608,
};

static bool8 FUN_08069098(struct GrandCannon* p) {
  if ((p->props).elementEffect == NULL) {
    switch ((p->s).mode[3]) {
      case 0: {
        if (IsFrozen((void*)p)) {
          (sUpdates1[(p->s).mode[1]])((void*)p);
          (sUpdates2[(p->s).mode[1]])((void*)p);
          (p->s).mode[3]++;
          UpdateMotionGraphic(&p->s);
          return TRUE;
        }
        break;
      }
      case 1: {
        if (IsFrozen((void*)p)) {
          return TRUE;
        }
        (p->s).mode[3] = 0;
        break;
      }
    }
  }
  return FALSE;
}

static void FUN_0806910c(struct GrandCannon* p) {
  if ((p->props).elementEffect == NULL) {
    if ((p->body).status & BODY_STATUS_WHITE) {
      (p->props).elementEffect = ApplyElementEffect(0, &p->s, &sElementCoord);
      if ((p->props).elementEffect != NULL) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
    }
  }
}

// --------------------------------------------

static void GrandCannon_Init(struct GrandCannon* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);

  if ((p->s).work[0] == GRAND_CANNON_TURRET) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    if (MOD_ENABLED(gSystemSavedataManager.mods, 105) && !FLAG(gCurStory.s.gameflags, DEMO_PLAY)) {
      struct Body* body;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 12);
      body->parent = (void*)p;
      body->fn = NULL;
    } else {
      struct Body* body;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 8);
      body->parent = (void*)p;
      body->fn = NULL;
    }
    {
      struct Body* body = &p->body;
      body->fn = onCollision;
    }
    CreateGrandCannonBattery((struct Entity*)p);
    (p->props).elementEffect = NULL;
  } else {
    (p->props).unk_004 = 0;
  }

  GrandCannon_Update((void*)p);
}

NON_MATCH static void GrandCannon_Update(struct Enemy* p) {
#if MODERN
  if ((p->s).work[0] == GRAND_CANNON_BATTERY) {
    struct Entity* turret = (p->s).unk_28;
    if (!IS_METTAUR) {
      if (turret->mode[0] != ENTITY_EXIT) {
        if (turret->mode[0] > ENTITY_UPDATE) {
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          (p->s).mode[1] = 2;
          GrandCannon_Die(p);
          return;
        }
        goto _UPDATE;
      }
    }

    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    if (tryKillGrandCannon(p)) {
      return;
    }
    FUN_0806910c((void*)p);
    if (FUN_08069098((void*)p)) {
      return;
    }
  _UPDATE:
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
#else
  INCCODE("asm/wip/GrandCannon_Update.inc");
#endif
}

void explodeGrandCannon(struct Enemy* p);
void slashGrandCannon(struct Enemy* p);
void FUN_080697bc(struct Enemy* p);

static void GrandCannon_Die(struct Enemy* p) {
  static const EnemyFunc sDeads[3] = {
      explodeGrandCannon,
      slashGrandCannon,
      FUN_080697bc,
  };
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeads[(p->s).mode[1]])(p);
}

static void GrandCannon_Dissappear(struct Entity* p) {
  p->flags2 &= ~ENTITY_HAZARD;
  DeleteEnemy(p);
}

// --------------------------------------------

static void nop_0806937c(struct Enemy* p) { return; }

static void grandcannon_08069380(struct GrandCannon* p) {
  struct VFX* effect = (p->props).elementEffect;
  if (effect == NULL || isKilled(&effect->s)) {
    (p->props).elementEffect = NULL;
    SetDDP(&p->body, sCollisions);
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

// --------------------------------------------

static void grandCannon_080693b4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).flags2 |= ENTITY_HAZARD;
      (p->s).size = &sSize;
      (p->s).hazardAttr = 0x1001;
      SetMotion(&p->s, MOTION(SM007_GRAND_CANNON, 0x0));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(&p->s);
    }
  }
}

#include "camera.h"
#include "zero.h"
#include "trig.h"
#include "stagerun.h"

void grandcannonMoveTurret(struct Enemy* p) {
  register struct Entity* q asm("r4");
  q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      s32 qx;
      InitRotatableMotion(&p->s);
      SetMotion(&p->s, 0x0703);
      (p->s).work[2] = 0x78;
      qx = (q->coord).x;
      (p->s).coord.x = qx;
      (p->s).coord.y = (q->coord).y - 0x600;
      (p->s).unk_coord.x = (pZero2->s).coord.x - qx;
      (p->s).angle = 0x40;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      UpdateMotionGraphic(&p->s);
      if (*(s32*)((u8*)q + 0xb4) != 0) {
        break;
      }
      if (IsFrozen(q)) {
        break;
      }
      {
        register s32 qx asm("r1");
        register s32 d2 asm("r2");
        register s32 acc asm("r1");
        register u8* cb asm("r4");
        register s32 ang asm("r2");
        register s32 zx asm("r0");
        s32 v;
        qx = (q->coord).x;
        (p->s).coord.x = qx;
        (p->s).coord.y = (q->coord).y - 0x600;
        zx = (pZero2->s).coord.x;
        d2 = zx - qx;
        acc = (p->s).unk_coord.x;
        d2 = d2 - acc;
        {
          s32 t = d2;
          asm("" : "+r"(t));
          if (d2 < 0) {
            t += 15;
          }
          d2 = t >> 4;
        }
        d2 = acc + d2;
        (p->s).unk_coord.x = d2;
        {
          const s16* st = gSineTable;
          u8 i;
          cb = (u8*)p + 0xb8;
          i = *cb;
          v = d2 + (st[i] << 3);
          *cb = i + 4;
        }
        if (v > 0) {
          register s32 c40 asm("r1");
          if (v <= 0xFFF) {
            v = 0x1000;
          } else if (v > 0x7800) {
            v = 0x7800;
          }
          v -= 0x1000;
          {
            s32 dq = (v * 40) / 0x6800;
            c40 = 0x40;
            ang = c40 - dq;
          }
        } else {
          if (v > -0x1000) {
            v = -0x1000;
          } else if (v < -0x7800) {
            v = -0x7800;
          }
          v += 0x1000;
          ang = (v * 40) / -0x6800 + 0x40;
        }
        {
          register s32 na asm("r0");
          u8* aa;
          na = -ang;
          na -= 0x80;
          aa = (u8*)p + 0x24;
          *aa = na;
          {
            s32 t2 = (u8)--(p->s).work[2];
            if (t2 == 0) {
              if (CalcFromCamera(&gStageRun.vm.camera, (struct Coord*)(aa + 0x30)) <= 0xFFF) {
                (p->s).mode[1] = 2;
                (p->s).mode[2] = t2;
              }
            }
          }
        }
      }
      break;
    }
  }
}

INCASM("asm/enemy/grand_cannon_pre_b.inc");

struct Entity* CreateGrandCannonBomb(struct Coord* c, s32 v, u8 ang);

// 0x08069560
void grandcannonBombShot(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0: {
      u8 ang;
      s32 x;
      s32 y;
      PlaySound(0x2D);
      ang = *(u8*)((u8*)p + 0x24) + 0x80;
      x = (p->s).coord.x;
      c.x = x;
      c.x = gSineTable[(u8)(ang + 0x40)] * 28 + x;
      y = (p->s).coord.y;
      c.y = y;
      c.y = gSineTable[ang] * 28 + y;
      PlaySound(0x2D);
      CreateGrandCannonBomb(&c, 0x500, ang);
      (p->s).work[2] = 4;
      SetMotion(&p->s, MOTION(0x07, 0x04));
      (p->s).mode[2]++;
    }
    case 1: {
      s32 d;
      u8 t;
      UpdateMotionGraphic(&p->s);
      d = (p->s).work[2] - 1;
      (p->s).work[2] = d;
      t = d;
      if (t == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = t;
      }
      break;
    }
  }
}

void grandcannon_08069608(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}

#include "mission.h"
#include "vfx.h"

void FUN_080b7f70(struct Enemy* p, struct Coord* c, const motion_t* m, s32 n);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x0806962c
void explodeGrandCannon(struct Enemy* p) {
  struct Coord c;
  struct Coord* co;
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    u8* q = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(q));
    z = 0;
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *q = z;
    t = (p->s).flags;
    f = 0xFB;
    f &= t;
    asm volatile("" ::"r"(t));
    k2 = 0xFE;
    f &= k2;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  FUN_080b7f70(p, &c, sMotions, 3);
  co = &(p->s).coord;
  TryDropItem(3, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
  {
    register u8 f2 asm("r0");
    register u8 t2 asm("r1");
    t2 = (p->s).flags2;
    f2 = 0xF7;
    f2 &= t2;
    asm volatile("" ::"r"(t2));
    (p->s).flags2 = f2;
  }
}

INCASM("asm/enemy/grand_cannon_post.inc");

// 0x080697BC
void FUN_080697bc(struct Enemy* p) {
  struct Entity* e = (struct Entity*)(p->s).unk_28;
  if (e->mode[0] == 4) {
    register u8* q asm("r0");
    u8 fl;
    u32 z;
    fl = (p->s).flags & 0xFE;
    z = 0;
    fl &= 0xFD;
    (p->s).flags = fl;
    q = (u8*)p + 0x8c;
    *(u32*)q = z;
    asm volatile("add %0, #4" : "+r"(q));
    *(u32*)q = z;
    asm volatile("add %0, #4" : "+r"(q));
    *q = z;
    (p->s).flags &= 0xFB;
    SET_ENEMY_ROUTINE(p, 3);
  }
}

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0400, 0x0000, 0x0800, 0x1000},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x0900, 0x1C00, 0x1600},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x04,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x0800, 0x1C00, 0x1800},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), 0xFFFFF000};

static const u8 sInitModes[2] = {0, 1};

static const struct Rect sSize = {0x0, 0x0, 0x1800, 0x2600};

static const motion_t sMotions[4] = {
    MOTION(SM007_GRAND_CANNON, 0x05),
    MOTION(SM007_GRAND_CANNON, 0x06),
    MOTION(SM007_GRAND_CANNON, 0x07),
    MOTION(SM007_GRAND_CANNON, 0x02),
};
