#include "collision.h"
#include "enemy.h"
#include "stagerun.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

static const struct Collision sCollisions[3];
static const u8 sInitModes[2];

void HeavyCannon_Die(struct Enemy* p);
void HeavyCannon_Update(struct Enemy* p);
void FUN_0807aae8(struct Body* body, struct Coord* r1, struct Coord* r2);

void CreateHeavyCannonBall(s32 x, s32 y, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HEAVY_CANNON_BALL);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).work[2] = a2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

void FUN_0807aae8(struct Body* body, struct Coord* r1, struct Coord* r2) {
  struct Enemy* atk = (struct Enemy*)((body->enemy)->parent);
  struct Enemy* self = (struct Enemy*)body->parent;
  if (body->hitboxFlags & 1) {
    self->props[0] = ((atk->s).coord.x - (self->s).coord.x) > 0 ? 1 : 0;
  }
  if (body->hitboxFlags & 4) {
    if ((atk->body).hp == 0) {
      (self->s).work[2] = 0xff;
    }
  }
}

static bool8 FUN_0807ab30(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    HeavyCannon_Die(p);
    return TRUE;
  }
  return FALSE;
}

void HeavyCannon_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 10, FUN_0807aae8);
  (p->s).taskCol = 30;
  HeavyCannon_Update(p);
}

static const EnemyFunc PTR_ARRAY_08367774[2];
static const EnemyFunc PTR_ARRAY_0836777c[2];
static const motion_t sMotions[3];

void FUN_080b7f70(struct Enemy* p, struct Coord* c, motion_t* m, s32 n);

void HeavyCannon_Update(struct Enemy* p) {
  if (gCurStory.s.gameflags[4] & 0x40) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else if (!FUN_0807ab30(p)) {
    PTR_ARRAY_08367774[(p->s).mode[1]](p);
    PTR_ARRAY_0836777c[(p->s).mode[1]](p);
  }
}

void HeavyCannon_Die(struct Enemy* p) {
  struct Coord c;
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  FUN_080b7f70(p, &c, (motion_t*)sMotions, 3);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_0807acd0(struct Enemy* p) {}

INCASM("asm/enemy/heavy_cannon_ball_p2.inc");

// 0x0807B008
void FUN_0807b008(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      u8* a = (u8*)p + 0x8c;
      *(u32*)a = m;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *(u32*)a = m;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *a = m;
      (p->s).flags &= 0xFB;
      (p->s).work[2] = m;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      s32 dy;
      s32 w;
      (p->s).coord.x += (p->s).d.x;
      dy = (p->s).d.y + 0x40;
      (p->s).d.y = dy;
      if (dy > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      w = (p->s).work[2] + 1;
      (p->s).work[2] = w;
      w &= 2;
      if (w != 0) {
        (p->s).flags |= 1;
      } else {
        (p->s).flags &= 0xFE;
      }
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000) {
        s32 z;
        {
          register u8 fv asm("r0");
          register u8 fl asm("r1");
          fl = (p->s).flags;
          asm("" : "+r"(fl));
          fv = 0xFE;
          fv &= fl;
          z = 0;
          fl = 0xFD;
          fv &= fl;
          (p->s).flags = fv;
        }
        {
          u8* b = (u8*)p + 0x8c;
          *(u32*)b = z;
          asm("" : "+r"(b));
          b += 4;
          asm("" : "+r"(b));
          *(u32*)b = z;
          asm("" : "+r"(b));
          b += 4;
          asm("" : "+r"(b));
          *b = z;
        }
        (p->s).flags &= 0xFB;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

void HeavyCannon_Init(struct Enemy* p);
void HeavyCannon_Update(struct Enemy* p);
void HeavyCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gHeavyCannonBallRoutine = {
    [ENTITY_INIT] =      HeavyCannon_Init,
    [ENTITY_UPDATE] =    HeavyCannon_Update,
    [ENTITY_DIE] =       HeavyCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0807acd0(struct Enemy* p);
void FUN_0807acd0(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08367774[2] = {
    FUN_0807acd0,
    FUN_0807acd0,
};

void FUN_0807acd4(struct Enemy* p);
void FUN_0807b008(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_0836777c[2] = {
    FUN_0807acd4,
    FUN_0807b008,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
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
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
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
};

static const u8 sInitModes[2] = {0, 0};

static const motion_t sMotions[3] = {
    MOTION(SM056_HEAVY_CANNON, 5),
    MOTION(SM056_HEAVY_CANNON, 5),
    MOTION(SM056_HEAVY_CANNON, 5),
};
