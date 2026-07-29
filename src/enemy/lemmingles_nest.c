#include "camera.h"
#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "stagerun.h"
#include "story.h"
#include "zero.h"

void LemminglesNest_Init(struct Enemy* p);
void LemminglesNest_Update(struct Enemy* p);
void LemminglesNest_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gLemminglesNestRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)LemminglesNest_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)LemminglesNest_Update,
    [ENTITY_DIE] =       (EnemyFunc)LemminglesNest_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

static void FUN_0806df3c(struct Entity* e) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_LEMMINGLES_NEST);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    (p->coord).x = (e->coord).x, (p->coord).y = (e->coord).y;
    p->unk_28 = (void*)e;
    if (e->work[0] == 0) {
      p->work[0] = 2;
    } else {
      p->work[0] = 3;
    }
  }
}

// --------------------------------------------

void nop_0806e284(struct Enemy* p);

static const EnemyFunc sUpdates1[4] = {
    nop_0806e284,
    nop_0806e284,
    nop_0806e284,
    nop_0806e284,
};

void FUN_0806e288(struct Enemy* p);
static void FUN_0806e518(struct Entity* p);
void FUN_0806e3b0(struct Enemy* p);
void FUN_0806e4bc(struct Enemy* p);

static const EnemyFunc sUpdates2[4] = {
    (void*)FUN_0806e288,
    (void*)FUN_0806e518,
    (void*)FUN_0806e3b0,
    (void*)FUN_0806e4bc,
};

static bool8 FUN_0806dfa4(struct Entity* p) {
  switch (p->mode[3]) {
    case 0: {
      if (IsFrozen((void*)p)) {
        (sUpdates1[p->mode[1]])((void*)p);
        (sUpdates2[p->mode[1]])((void*)p);
        p->mode[3]++;
        UpdateMotionGraphic(p);
        return TRUE;
      }
      break;
    }
    case 1: {
      if (IsFrozen((void*)p)) {
        return TRUE;
      }
      p->mode[3] = 0;
      break;
    }
  }
  return FALSE;
}

// --------------------------------------------

static const u8 sInitModes[];

INCASM("asm/enemy/lemmingles_nest_p1_a.inc");

void LemminglesNest_Update(struct Enemy* p) {
  bool8 r;
  if ((p->s).work[0] > 3 && (gCurStory.s.gameflags[4] & 0x40)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    goto tail;
  }
  {
    u8 m = (p->s).work[0] - 2;
    if (m <= 1) {
      if (((p->s).unk_28)->mode[0] <= 1) {
        goto dispatch;
      }
    } else {
      if (!((p->body).status & BODY_STATUS_DEAD)) {
        goto dispatch;
      }
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  LemminglesNest_Die(p);
  return;

dispatch:
  r = FUN_0806dfa4(&p->s);
  if (r) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x19000) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    (p->body).status = r;
    (p->body).prevStatus = r;
    (p->body).invincibleTime = r;
  tail:
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

INCASM("asm/enemy/lemmingles_nest_p1_b.inc");

void nop_0806e284(struct Enemy* p) {}

static const struct Collision sCollisions[3];

void FUN_0806e288(struct Enemy* p) {
  s32 xf;
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[0] > 3) {
        s32 v;
        SetDDP(&p->body, &sCollisions[2]);
        {
          u8 fl3 = (p->s).flags;
          register s32 m2 asm("r2");
          m2 = 0xFE;
          m2 &= fl3;
          (p->s).flags = m2;
          {
            register s32 x3 asm("r3");
            {
              register s32 x1 asm("r1");
              x1 = 0;
              if ((p->s).work[0] == 5) {
                x1 = 1;
              }
              x3 = x1;
            }
            if (x3) {
              register s32 c1 asm("r1");
              register s32 vv asm("r0");
              c1 = 0x10;
              vv = m2;
              vv |= c1;
              v = vv;
            } else {
              register s32 vv2 asm("r0");
              vv2 = 0xEF;
              vv2 &= m2;
              v = vv2;
            }
            (p->s).flags = v;
            xf = x3;
          }
        }
      } else {
        s32 v;
        SetMotion(&p->s, 0x1E14);
        {
          register s32 x2 asm("r2");
          {
            register s32 x1b asm("r1");
            x1b = 0;
            if ((p->s).work[0] == 1) {
              x1b = 1;
            }
            x2 = x1b;
          }
          if (x2) {
            register u8 lf asm("r1");
            register s32 vv asm("r0");
            lf = (p->s).flags;
            vv = 0x10;
            vv |= lf;
            v = vv;
          } else {
            register u8 lf2 asm("r1");
            register s32 vv2 asm("r0");
            lf2 = (p->s).flags;
            vv2 = 0xEF;
            vv2 &= lf2;
            v = vv2;
          }
          (p->s).flags = v;
          xf = x2;
        }
      }
      {
        register s32 xr asm("r1");
        xr = xf;
        ((p->s).spr).xflip = xr;
        {
          u8* a = (u8*)p + 0x4a;
          s32 sh = xr << 4;
          u8 b = *a;
          s32 msk = -0x11;
          msk &= b;
          msk |= sh;
          *a = msk;
        }
      }
      (p->s).taskCol = 0x17;
      (p->s).work[2] = 1;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
      } else {
        u32 zf;
        s32 fl;
        {
          register u32 one asm("r6");
          register u8 flr asm("r1");
          u32 zf0 = (pZero2->s).flags >> 4;
          one = 1;
          zf = zf0 & one;
          flr = (p->s).flags;
          {
            register s32 t0 asm("r0");
            t0 = 0x10;
            t0 &= flr;
            fl = flr;
            if (t0 != 0) {
              if (zf != one) {
                goto chase;
              }
              goto upd;
            }
          }
        }
        if (zf == 0) {
          goto upd;
        }
      chase:
        {
          s32 dx = (pZero2->s).coord.x - (p->s).coord.x;
          u8 t2;
          {
            register s32 tc asm("r0");
            tc = 0x10;
            tc &= fl;
            t2 = (u8)tc;
          }
          if (t2 == 0) {
            if (dx >= 0) {
              goto upd;
            }
            if (dx <= -0x7800) {
              goto upd;
            }
            (p->s).mode[1] = 2;
            (p->s).mode[2] = t2;
          } else {
            dx -= 1;
            if ((u32)dx > 0x77FE) {
              goto upd;
            }
            (p->s).mode[1] = 2;
            (p->s).mode[2] = 0;
          }
        }
      }
    upd:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/enemy/lemmingles_nest_p2.inc");

// --------------------------------------------

static void FUN_0806e518(struct Entity* p) {
  struct Entity* q = (void*)p->unk_28;
  switch (p->mode[2]) {
    case 0: {
      p->flags2 |= WHITE_PAINTABLE;
      p->invincibleID = q->uniqueID;
      SetMotion(p, MOTION(SM030_LEMMINGLES_NEST, 21));
      SET_XFLIP(p, p->work[0] == 3);
      p->mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(p);
      break;
    }
  }
}

// --------------------------------------------

// 0x083667c4
static const struct Collision sCollisions[3] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(24), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      range : {PIXEL(0), -PIXEL(12), PIXEL(24), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
};

// 0x0836680c
static const u8 sInitModes[8] = {0, 0, 1, 1, 0, 0, 0, 0};
