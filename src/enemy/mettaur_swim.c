#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"
#include "physics.h"
#include "vfx.h"
#include "zero.h"

static const struct Collision sCollisions[8];

static const EnemyFunc sDeads[3];

struct Entity* FUN_08088b4c(s32 x, s32 y, u8 kind) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_METTAUR_SWIM);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    (p->coord).x = x, (p->coord).y = y;
    p->work[0] = kind;
  }
  return p;
}

u8 FUN_08088ba8(struct Enemy* p) {
  s32 val = PushoutToUp1((p->s).coord.x, (p->s).coord.y + PIXEL(8));
  if (val < 0) return TRUE;
  return FALSE;
}

// 0x08088bc8
s32 FUN_08088bc8(struct Enemy* p, s32 dx, s32 dy) {
  s32 y;
  if (dy != 0) {
    y = (p->s).coord.y + dy;
    (p->s).coord.y = y;
    if (dy < 0) {
      dy = PushoutToDown1((p->s).coord.x, y - PIXEL(16));
      if (dy > 0) {
        y = (p->s).coord.y;
        y += dy;
        (p->s).coord.y = y;
      }
    } else {
      dy = PushoutToUp1((p->s).coord.x, y);
      if (dy < 0) {
        y = (p->s).coord.y;
        y += dy;
        (p->s).coord.y = y;
      }
    }
  }
  if (dx != 0) {
    s32 x = (p->s).coord.x + dx;
    (p->s).coord.x = x;
    if (dx < 0) {
      dy = PushoutToRight1(x, (p->s).coord.y - PIXEL(8));
      if (dy > 0) {
        y = (p->s).coord.x;
        y += dy;
        (p->s).coord.x = y;
      }
    } else {
      dy = PushoutToLeft1(x, (p->s).coord.y - PIXEL(8));
      if (dy < 0) {
        y = (p->s).coord.x;
        y += dy;
        (p->s).coord.x = y;
      }
    }
  }
}

INCASM("asm/enemy/mettaur_swim_p1_pre_p1.inc");

bool8 FUN_08088cfc(struct Enemy* p) {
  u8 f[2];
  u8* b;
  u8* a;
  b = f;
  a = f;
  a[1] = 0;
  b[0] = 0;
  {
    register s32 x asm("r2") = (p->s).coord.x;
    register s32 c asm("r3");
    register s32 yl asm("r0");
    s32 y;
    yl = (p->s).coord.y;
    c = -PIXEL(16);
    asm("" : "+r"(c));
    y = yl + c;
    if (PushoutToDown1(x, y) > 0) {
      f[0] = 1;
    }
  }
  {
    register s32 x asm("r2") = (p->s).coord.x;
    register s32 c asm("r3");
    register s32 yl asm("r0");
    s32 y;
    yl = (p->s).coord.y;
    c = PIXEL(1);
    asm("" : "+r"(c));
    y = yl + c;
    if (PushoutToUp1(x, y) < 0) {
      f[1] = 1;
    }
  }
  return f[0] & f[1];
}

void CreateVFX62(struct Entity* e, struct Coord* c);

void FUN_08088d54(struct Enemy* p) {
  struct Coord c;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(20);
  CreateSmoke(2, &c);
  CreateVFX62(&p->s, &c);
}

INCASM("asm/enemy/mettaur_swim_p1_pre_p2.inc");

void MettaurSwim_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_08089218(struct Body* body) {
  struct Enemy* self = (struct Enemy*)body->parent;
  struct Entity* atkParent = (struct Entity*)(body->enemy)->parent;
  if (body->hitboxFlags & 8) {
    if (*(u16*)&atkParent->kind == 0x1206) {
      SET_ENEMY_ROUTINE(self, ENTITY_DIE);
      (self->s).mode[1] = 0;
    }
  }
  *(s32*)&self->props[0] = (pZero2->s).coord.x - (self->s).coord.x;
}

void nop_08089268(struct Enemy* p) {}

u8 FUN_08088ba8(struct Enemy* p);

void FUN_0808926c(struct Enemy* p) {
  if (FUN_08088ba8(p) == 0) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 0xc;
    (p->s).mode[2] = 0;
  }
}

void FUN_080892a4(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 0xc;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/mettaur_swim_p2_pre_p2_p1.inc");

void FUN_08089a00(struct Enemy* p) {
  struct Entity* par = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[4]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x = par->coord.x;
      (p->s).coord.y = par->coord.y;
      break;
  }
}

void FUN_08089a34(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 z = 0;
      (p->s).work[0] = z;
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0xdd, 0x7));
      (p->s).d.x = z;
      (p->s).d.y = z;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1:
      FUN_08088bc8(p, 0, (p->s).d.y);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      SetMotion(&p->s, MOTION(0xdd, 0x8));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      FUN_08088bc8(p, 0, (p->s).d.y);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (FUN_08088ba8(p) != 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 4:
      SetMotion(&p->s, MOTION(0xdd, 0xe));
      (p->s).mode[2]++;
      /* fallthrough */
    case 5:
      UpdateMotionGraphic(&p->s);
      FUN_08088bc8(p, 0, (p->s).d.y);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/mettaur_swim_p2_pre_p2_p2.inc");


void FUN_08089e60(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0xdd, 0xc));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 9;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/mettaur_swim_p2_post.inc");

void FUN_08089eb0(struct Enemy* p);

void FUN_08089f60(struct Enemy* p) {
  s32 dx, dy, q2, dist;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[6]);
      SetMotion(&p->s, MOTION(0xDD, 0x02));
      dx = (p->s).coord.x - (pZero2->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).coord.y - PIXEL(24);
      dy -= (pZero2->s).coord.y;
      (p->s).d.y = dy;
      dist = (dx >> 8) * (dx >> 8);
      dist += (dy >> 8) * (dy >> 8);
      dist = Sqrt(dist) << 8;
      if (dist != 0) {
        q2 = ((p->s).d.x << 8) / dist;
        (p->s).d.x = q2;
        dy = ((p->s).d.y << 8) / dist;
        (p->s).d.x = q2 * 6;
        (p->s).d.y = dy * 6;
      } else {
        (p->s).d.x = 0x600;
        (p->s).d.y = dist;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 y;
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      if (FUN_080098a4((p->s).coord.x, y) || ((p->body).status & 4)) {
        (p->s).mode[2] = 0;
        FUN_08089eb0(p);
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      }
      break;
    }
  }
}

void FUN_0808a068(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      struct Coord c;
      (p->s).flags &= ~DISPLAY;
      EXIT_BODY(p);
      c.x = (p->s).coord.x, c.y = (p->s).coord.y - PIXEL(8);
      CreateSmoke(1, &c);
      if ((p->s).work[0] == 2) {
        PlaySound(SE_UNK_31);
      } else {
        PlaySound(SE_ZAKO_EXPLODE);
      }
      (p->s).mode[2]++;
      break;
    }
    case 1: {
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      break;
    }
  }
}

void MettaurSwim_Init(struct Enemy* p);
void MettaurSwim_Update(struct Enemy* p);
void MettaurSwim_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gMettaurSwimRoutine = {
    [ENTITY_INIT] =      MettaurSwim_Init,
    [ENTITY_UPDATE] =    MettaurSwim_Update,
    [ENTITY_DIE] =       MettaurSwim_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCollisions[8] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(24), PIXEL(16), PIXEL(6)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(24), PIXEL(16), PIXEL(6)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
};

// --------------------------------------------

void FUN_0808926c(struct Enemy* p);
void FUN_080892a4(struct Enemy* p);
void nop_08089268(struct Enemy* p);

// clang-format off
static const EnemyFunc sInitializers[13] = {
    FUN_0808926c,
    FUN_0808926c,
    FUN_0808926c,
    FUN_0808926c,
    FUN_0808926c,
    FUN_080892a4,
    FUN_080892a4,
    nop_08089268,
    FUN_080892a4,
    nop_08089268,
    nop_08089268,
    nop_08089268,
    nop_08089268,
};
// clang-format on

// --------------------------------------------

void FUN_080892c4(struct Enemy* p);
void FUN_08089364(struct Enemy* p);
void FUN_080894a4(struct Enemy* p);
void FUN_0808959c(struct Enemy* p);
void FUN_08089694(struct Enemy* p);
void FUN_08089790(struct Enemy* p);
void FUN_080898bc(struct Enemy* p);
void FUN_08089a00(struct Enemy* p);
void FUN_08089a34(struct Enemy* p);
void FUN_08089b48(struct Enemy* p);
void FUN_08089c94(struct Enemy* p);
void FUN_08089e60(struct Enemy* p);
void FUN_08089f60(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates[13] = {
    FUN_080892c4,
    FUN_08089364,
    FUN_080894a4,
    FUN_0808959c,
    FUN_08089694,
    FUN_08089790,
    FUN_080898bc,
    FUN_08089a00,
    FUN_08089a34,
    FUN_08089b48,
    FUN_08089c94,
    FUN_08089e60,
    FUN_08089f60,
};
// clang-format on

// --------------------------------------------

void FUN_08089eb0(struct Enemy* p);
void FUN_08089f60(struct Enemy* p);
void FUN_0808a068(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_08089eb0,
    FUN_08089f60,
    FUN_0808a068,
};

// --------------------------------------------

static const u8 sInitModes[6] = {0, 6, 9, 0, 7, 0};

static const motion_t sMotions[4] = {
    MOTION(SM221_METTAUR, 0),
    MOTION(SM000_BATTLE_EFFECT, 6),
    MOTION(SM000_BATTLE_EFFECT, 9),
    MOTION(SM221_METTAUR, 0),
};
