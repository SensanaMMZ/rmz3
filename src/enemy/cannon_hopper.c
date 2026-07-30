#include "collision.h"
#include "physics.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"
#include "story.h"
#include "zero.h"

extern const EnemyFunc sDeads[4];

INCASM("asm/enemy/cannon_hopper_pre_p1.inc");

void FUN_08096ffc(struct Enemy* p, s32 a, s32 b) {
  s32 hit = 0;
  if (b != 0) {
    s32 uy = (p->s).unk_coord.y + b;
    s32 x3, y2, m;
    register s32 f asm("r4");
    register s32 r asm("r2");
    u32 fl;
    (p->s).unk_coord.y = uy;
    {
      s32 t2_ = 0;
      if ((p->s).d.y > 0) {
        t2_ = 1;
      }
      asm("" : "=r"(f) : "0"(t2_));
    }
    x3 = (p->s).unk_coord.x + -0x700;
    y2 = uy;
    {
      u32 fv;
      u32 k20 = 0x20;
      asm("" : "=r"(fv) : "0"((p->s).flags));
      asm("" : "+r"(k20));
      fl = (u8)(k20 & fv);
    }
    m = -0x2F00;
    if (!fl) goto melse1;
    m = 0x2F00;
    asm("" : "+r"(fl));
    if (fl) {
      s32 acc = m;
      asm("" : "+r"(acc));
      acc *= f;
      y2 += acc;
    } else {
    melse1:
      y2 += (1 ^ f) * m;
    }
    if (f != 0) {
      r = PushoutToUp1(x3, y2 + -0x100);
      if (r < 0) {
        s32 t2 = (p->s).unk_coord.y + 0x100;
        (p->s).unk_coord.y = t2 + r;
        hit |= 1;
      }
    } else {
      r = PushoutToDown1(x3, y2 + 0x100);
      if (r > 0) {
        s32 t2 = (p->s).unk_coord.y + -0x100;
        (p->s).unk_coord.y = t2 + r;
        hit |= 1;
      }
    }
    {
      s32 t2_ = 0;
      if ((p->s).d.y > 0) {
        t2_ = 1;
      }
      asm("" : "=r"(f) : "0"(t2_));
    }
    x3 = (p->s).unk_coord.x + 0x700;
    y2 = (p->s).unk_coord.y;
    {
      u32 fv;
      u32 k20 = 0x20;
      asm("" : "=r"(fv) : "0"((p->s).flags));
      asm("" : "+r"(k20));
      fl = (u8)(k20 & fv);
    }
    m = -0x2F00;
    if (!fl) goto melse2;
    m = 0x2F00;
    asm("" : "+r"(fl));
    if (fl) {
      s32 acc = m;
      asm("" : "+r"(acc));
      acc *= f;
      y2 += acc;
    } else {
    melse2:
      y2 += (1 ^ f) * m;
    }
    if (f != 0) {
      r = PushoutToUp1(x3, y2 + -0x100);
      if (r < 0) {
        s32 t2 = (p->s).unk_coord.y + 0x100;
        (p->s).unk_coord.y = t2 + r;
        hit |= 1;
      }
    } else {
      r = PushoutToDown1(x3, y2 + 0x100);
      if (r > 0) {
        s32 t2 = (p->s).unk_coord.y + -0x100;
        (p->s).unk_coord.y = t2 + r;
        hit |= 1;
      }
    }
  }
  if (a != 0) {
    s32 ux = (p->s).unk_coord.x + a;
    s32 x3, y2;
    register s32 f asm("r4");
    register s32 r asm("r3");
    s32 fl2;
    (p->s).unk_coord.x = ux;
    {
      s32 t2_ = 0;
      if ((p->s).d.x > 0) {
        t2_ = 1;
      }
      asm("" : "=r"(f) : "0"(t2_));
    }
    x3 = ux + -0x700;
    x3 += f * 0xE00;
    y2 = (p->s).unk_coord.y + -0x200;
    if (f != 0) {
      r = PushoutToLeft1(x3, y2);
      if (r < 0) {
        (p->s).unk_coord.x += r;
        hit = (u8)(hit | 2);
      }
    } else {
      r = PushoutToRight1(x3, y2);
      if (r > 0) {
        (p->s).unk_coord.x += r;
        hit = (u8)(hit | 2);
      }
    }
    {
      s32 t2_ = 0;
      if ((p->s).d.x > 0) {
        t2_ = 1;
      }
      asm("" : "=r"(f) : "0"(t2_));
    }
    x3 = (p->s).unk_coord.x;
    x3 += -0x700;
    x3 += f * 0xE00;
    y2 = (p->s).unk_coord.y;
    fl2 = (p->s).flags & 0x20;
    if (fl2 != 0) {
      y2 += 0x2D00;
    } else {
      y2 += -0x2D00;
    }
    if (f != 0) {
      r = PushoutToLeft1(x3, y2);
      if (r < 0) {
        (p->s).unk_coord.x += r;
        hit = (u8)(hit | 2);
      }
    } else {
      r = PushoutToRight1(x3, y2);
      if (r > 0) {
        (p->s).unk_coord.x += r;
        hit = (u8)(hit | 2);
      }
    }
  }
  if ((hit & 1) == 0 && (p->s).d.x != 0 && (p->s).d.y != 0) {
    s32* cnt = (s32*)((u8*)p + 0xc0);
    *cnt = *cnt + 1;
  } else {
    (p->s).d.x = 0;
    (p->s).d.y = 0;
  }
  if (hit & 2) {
    (p->s).d.x = -(p->s).d.x;
  }
}

INCASM("asm/enemy/cannon_hopper_pre_p1b.inc");

void CannonHopper_Die(struct Enemy* p) {
  if (gCurStory.s.gameflags[4] & 0x40) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (sDeads[(p->s).mode[1]])(p);
  }
}

void FUN_080978c8(struct Enemy* p) {
  struct Enemy* parent = (struct Enemy*)(p->s).unk_2c;
  *(s32*)((u8*)parent + 0xb4) = pZero2->s.coord.x - (parent->s).coord.x;
}

void FUN_080978e0(struct Enemy* p) {}


void FUN_080978e4(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
}


void FUN_08097904(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/cannon_hopper_post_pre_p3.inc");

void FUN_08097cc8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0xdc, 3));
      (p->s).work[2] = 0xc;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).work[2]--;
      if ((p->s).work[2] == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/enemy/cannon_hopper_post_post.inc");

void CannonHopper_Init(struct Enemy* p);
void CannonHopper_Update(struct Enemy* p);
void CannonHopper_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gCannonHopperRoutine = {
    [ENTITY_INIT] =      CannonHopper_Init,
    [ENTITY_UPDATE] =    CannonHopper_Update,
    [ENTITY_DIE] =       CannonHopper_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCollisions[14] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(9), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(14), PIXEL(14), PIXEL(28)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(14), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(24), PIXEL(32), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(24), PIXEL(32), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(34), PIXEL(32), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(34), PIXEL(32), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(40), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(40), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(9), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(9), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(9), PIXEL(16), PIXEL(16)},
    },
};

void FUN_080978e4(struct Enemy* p);
void FUN_08097904(struct Enemy* p);
void FUN_080978e0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    FUN_080978e4,
    FUN_08097904,
    FUN_08097904,
    FUN_080978e4,
    FUN_080978e4,
    FUN_080978e0,
};
// clang-format on

void FUN_08097924(struct Enemy* p);
void cannonHopper_08097a14(struct Enemy* p);
void cannonHopper_08097af8(struct Enemy* p);
void FUN_08097cc8(struct Enemy* p);
void cannonHopper_08097d10(struct Enemy* p);
void FUN_0809860c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    FUN_08097924,
    cannonHopper_08097a14,
    cannonHopper_08097af8,
    FUN_08097cc8,
    cannonHopper_08097d10,
    FUN_0809860c,
};
// clang-format on

// --------------------------------------------

void FUN_08097f3c(struct Enemy* p);
void FUN_08098110(struct Enemy* p);
void FUN_08098414(struct Enemy* p);
void FUN_0809860c(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_08097f3c,
    FUN_08098110,
    FUN_08098414,
    FUN_0809860c,
};

// --------------------------------------------

static const u8 sInitModes[4] = {0, 0, 0, 0};
static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(19)};

static const u8 u8_ARRAY_0836a424[14] = {
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x16, 0x2B, 0x40, 0x55, 0x6A,
};

static const s32 s32_ARRAY_0836a434[10] = {
    -PIXEL(8), -PIXEL(6), PIXEL(0), PIXEL(6), PIXEL(8), -PIXEL(18), -PIXEL(18), -PIXEL(20), -PIXEL(18), -PIXEL(18),
};
