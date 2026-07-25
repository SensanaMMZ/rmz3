#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "story.h"
#include "motion.h"
#include "physics.h"
#include "metatile.h"

// 左右 0xA00 の位置に足場があるか (どちらか一方でもあれば TRUE)
bool8 FUN_08095d80(struct Enemy* p) {
  bool8 r = FALSE;
  s32 t;

  t = FUN_08009f6c((p->s).coord.x + 0xA00, (p->s).coord.y);
  if (t - (p->s).coord.y <= 0x43F) {
    r = TRUE;
  }
  t = FUN_08009f6c((p->s).coord.x - 0xA00, (p->s).coord.y);
  if (t - (p->s).coord.y <= 0x43F) {
    r = TRUE;
  }
  return r;
}

// 左右 0xA00 のうち高い方の足場に吸着する (0x400 以内なら)
bool8 FUN_08095dc8(struct Enemy* p) {
  bool8 r = FALSE;
  s32 a = PushoutToUp1((p->s).coord.x + 0xA00, (p->s).coord.y);
  s32 b = FUN_08009f6c((p->s).coord.x - 0xA00, (p->s).coord.y);

  if (a < b) {
    if (a < 0 && a > -0x400) {
      (p->s).coord.y += a;
      r = TRUE;
    }
  } else {
    if (b < 0 && b > -0x400) {
      (p->s).coord.y += b;
      r = TRUE;
    }
  }
  return r;
}

// 進行方向の壁を調べる (1: 壁で押し戻された, 0: 曲がり角, 2: 直進可)
u8 FUN_08095e28(struct Enemy* p) {
  s32 v;
  s32 dir;
  s32 dx;
  s32 push;

  v = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  if (v - (p->s).coord.y <= 0x43F) {
    (p->s).coord.y = v;
  }

  dir = 0;
  if ((p->s).d.x > 0) {
    dir = 1;
  }
  dx = dir * PIXEL(20) - PIXEL(10);
  v = (p->s).coord.y - PIXEL(8);

  if (dir != 0) {
    push = PushoutToLeft1((p->s).coord.x + dx, v);
    if (push < 0) {
      (p->s).coord.x += push;
      return 1;
    }
  } else {
    push = PushoutToRight1((p->s).coord.x + dx, v);
    if (push > 0) {
      (p->s).coord.x += push;
      return 1;
    }
  }

  v += PIXEL(16);
  if (FUN_080098a4((p->s).coord.x + dx, v) == 0) {
    return 2;
  }
  return 0;
}

INCASM("asm/enemy/shellcrawler_pre_p1_p1_a.inc");

static const EnemyFunc sDeads[4];

void Shellcrawler_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeads[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/shellcrawler_pre_p1_p1_b.inc");

void FUN_08096438(struct Enemy* p) {
  if (FUN_08095d80(p) == 0) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  } else if (*(u32*)((u8*)p + 0x8c) & 1) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
}

void FUN_08096468(struct Enemy* p) {
  if (FUN_08095d80(p) == 0) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

void FUN_08096484(struct Enemy* p) {
  if (FUN_08095d80(p) == 0) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
  if ((*(u32*)((u8*)p + 0x8c) & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 0xa;
    (p->s).mode[2] = 0;
  }
}

void FUN_080964bc(struct Enemy* p) {}

// 直進 (向きと進行方向が食い違うときは歩行モーションを差し替える)
void FUN_080964c0(struct Enemy* p) {
  s32 v;

  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x60;
      (p->s).d.x = -0x40;
      v = -0x40;
      if ((p->s).flags & X_FLIP) {
        v = 0x40;
      }
      (p->s).d.x = v;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      v = (p->s).d.x < 0;
      if ((((p->s).flags & X_FLIP) && v == 0) || (((p->s).flags & X_FLIP) == 0 && v != 0)) {
        SetMotion(&p->s, MOTION(0xdb, 0));
      } else {
        SetMotion(&p->s, MOTION(0xdb, 2));
      }
      (p->s).mode[2]++;
      // fallthrough
    case 2:
      if (--(p->s).work[2] == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
        break;
      }
      (p->s).coord.x += (p->s).d.x;
      if (FUN_08095e28(p)) {
        (p->s).d.x = -(p->s).d.x;
        (p->s).mode[2] = 1;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/enemy/shellcrawler_post_pre.inc");

void FUN_0809660c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0xdb, 3));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = (p->s).motion.state;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/shellcrawler_post_post.inc");

void Shellcrawler_Init(struct Enemy* p);
void Shellcrawler_Update(struct Enemy* p);
void Shellcrawler_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gShellcrawlerRoutine = {
    [ENTITY_INIT] =      Shellcrawler_Init,
    [ENTITY_UPDATE] =    Shellcrawler_Update,
    [ENTITY_DIE] =       Shellcrawler_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCollisions[16] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : BODY_NATURE_B2,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      priorityLayer : 0xFFFFFFDF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(10), -PIXEL(8), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(10), -PIXEL(8), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      priorityLayer : 0xFFFFFFDF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(10), -PIXEL(8), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(10), -PIXEL(8), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 2,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      priorityLayer : 0xFFFFFFDF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      priorityLayer : 0xFFFFFFDF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      priorityLayer : 0xFFFFFFDF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(20), PIXEL(20)},
    },
};

void FUN_08096438(struct Enemy* p);
void FUN_08096468(struct Enemy* p);
void FUN_08096484(struct Enemy* p);
void FUN_080964bc(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[11] = {
    FUN_08096438,
    FUN_080964bc,
    FUN_08096468,
    FUN_08096484,
    FUN_08096484,
    FUN_08096468,
    FUN_08096484,
    FUN_08096484,
    FUN_08096484,
    FUN_080964bc,
    FUN_080964bc,
};
// clang-format on

void FUN_080964c0(struct Enemy* p);
void FUN_08096570(struct Enemy* p);
void FUN_0809660c(struct Enemy* p);
void FUN_0809664c(struct Enemy* p);
void FUN_080966fc(struct Enemy* p);
void FUN_0809678c(struct Enemy* p);
void FUN_08096814(struct Enemy* p);
void FUN_08096950(struct Enemy* p);
void FUN_080969d0(struct Enemy* p);
void FUN_08096a90(struct Enemy* p);
void FUN_08096eac(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[11] = {
    FUN_080964c0,
    FUN_08096570,
    FUN_0809660c,
    FUN_0809664c,
    FUN_080966fc,
    FUN_0809678c,
    FUN_08096814,
    FUN_08096950,
    FUN_080969d0,
    FUN_08096a90,
    FUN_08096eac,
};
// clang-format on

void FUN_08096b84(struct Enemy* p);
void FUN_08096c28(struct Enemy* p);
void FUN_08096d84(struct Enemy* p);
void FUN_08096eac(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_08096b84,
    FUN_08096c28,
    FUN_08096d84,
    FUN_08096eac,
};
