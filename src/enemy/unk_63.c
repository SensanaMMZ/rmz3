#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "zero.h"

static const EnemyFunc sUpdates1[4];
static const EnemyFunc sUpdates2[4];
static const struct Collision sCollisions[3];
static const u8 sInitModes[6];
static const s16 s16_ARRAY_ARRAY_08369f44[4][2];
static const s8 s8_ARRAY_ARRAY_08369f5a[4][2];

void Enemy63_Update(struct Enemy* p);

#include "entity/macros.h"

void FUN_080949d4(s32 x, s32 y, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 63);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 4;
    (p->s).work[1] = n;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = s16_ARRAY_ARRAY_08369f44[n][0];
    (p->s).d.y = s16_ARRAY_ARRAY_08369f44[n][1];
    (p->s).unk_coord.x = 0x180;
  }
}

void FUN_08094a54(s32 x, s32 y, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 63);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 5;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = s16_ARRAY_ARRAY_08369f44[n][0] / 2;
    (p->s).d.y = s16_ARRAY_ARRAY_08369f44[n][1] / 2;
  }
}

void nop_08094ad8(struct Enemy* p) {}

void Enemy63_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_08094ad8);
  if ((p->s).work[0] <= 3) {
    (p->s).coord.x += s8_ARRAY_ARRAY_08369f5a[(p->s).work[0]][0] << 8;
    (p->s).coord.y += s8_ARRAY_ARRAY_08369f5a[(p->s).work[0]][1] << 8;
    (p->s).work[2] = 0x1e;
  }
  Enemy63_Update(p);
}

void Enemy63_Update(struct Enemy* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Enemy63_Die(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}


void nop_08094bcc(struct Enemy* p) {}


void FUN_08094bd0(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_BINDING) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
}

static const motion_t sMotions[4];

void FUN_08094bf0(struct Enemy* p) {
  if (!((p->body).status & BODY_STATUS_BINDING) || ((pZero2->body).status & BODY_STATUS_WHITE)) {
    struct Coord c;
    PlaySound(SE_ICE_BREAK);
    c.x = (p->s).coord.x, c.y = (p->s).coord.y - PIXEL(16);
    FUN_080b7ffc((void*)p, &c, (motion_t*)sMotions, 4);
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// 0x08094C80
void FUN_08094c80(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[3] = 2;
      (p->s).flags &= ~DISPLAY;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] != 0) {
        break;
      }
      goto inc;
    case 2:
      FUN_08094a54((p->s).coord.x, (p->s).coord.y, (p->s).work[0]);
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] != 0) {
        break;
      }
      (p->s).work[3]--;
      if ((u8)(p->s).work[3] != 0) {
        goto set2;
      }
    inc:
      (p->s).mode[2]++;
      break;
    set2:
      (p->s).mode[2] = 2;
      break;
    case 4:
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5: {
      s32 w;
      if ((p->s).work[2] % 9 == 0) {
        FUN_080949d4((p->s).coord.x, (p->s).coord.y, (p->s).work[0]);
      }
      w = (p->s).work[2] - 1;
      (p->s).work[2] = w;
      w = (u8)w;
      if (w == 0) {
        (p->s).mode[2] = w;
        (p->s).work[2] = 0x78;
      }
      break;
    }
  }
}

// 0x08094D48
void FUN_08094d48(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0xC800);
      (p->s).unk_coord.y = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 x;
      s32 y;
      s32 t;
      if (*((u8*)pZero2 + 0x94) != 0) {
        SetDDP(&p->body, &sCollisions[0]);
      } else {
        SetDDP(&p->body, &sCollisions[1]);
      }
      x = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = x;
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      t = (p->s).unk_coord.y + (p->s).unk_coord.x;
      (p->s).unk_coord.y = t;
      if (t > 0x3800) {
        register u8 f asm("r0");
        register u8 t1 asm("r1");
        register u8 k2 asm("r1");
        register s32 z asm("r2");
        FUN_08094a54(x, y, (p->s).work[1]);
        t1 = (p->s).flags;
        f = 0xFE;
        f &= t1;
        asm volatile("" ::"r"(t1));
        z = 0;
        k2 = 0xFD;
        f &= k2;
        (p->s).flags = f;
        *(u32*)((u8*)p + 0x8c) = z;
        *(u32*)((u8*)p + 0x90) = z;
        *(u8*)((u8*)p + 0x94) = z;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, 3);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_08094e0c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      SetMotion(&p->s, MOTION(SM200_SMOKE, 1));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == MOTION_END) (p->s).mode[2]++;
      break;
    }
    case 2: {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      EXIT_BODY(p);
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
    }
  }
}

// 0x08094EA0
NON_MATCH void FUN_08094ea0(struct Enemy* p0) {
#if MODERN
  register struct Enemy* p asm("r4");
  u8 m;
  p = p0;
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      *(u8*)((u8*)p + 0x25) = 0xF;
      PlaySound(0x40);
      (p->s).work[2] = m;
      SetDDP(&p->body, &sCollisions[2]);
      SetMotion(&p->s, MOTION(0x58, 0x00));
      (p->s).mode[2]++;
    case 1: {
      u8 one;
      u8 t;
      {
        u8* q = (u8*)pZero2 + 0x143;
        s32 mv;
        asm("" : "+r"(q));
        mv = -0x10;
        mv &= *q;
        one = 1;
        mv |= one;
        *q = mv;
      }
      {
        u8* q = (u8*)pZero2 + 0x143;
        asm("" : "+r"(q));
        *q = 0xF & *q;
      }
      t = (p->s).work[2] + 1;
      (p->s).work[2] = t;
      if ((t & 1) != 0) {
        (p->s).flags |= one;
      } else {
        (p->s).flags &= 0xFE;
      }
      (p->s).coord.x = (pZero2->s).coord.x;
      (p->s).coord.y = (pZero2->s).coord.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/enemy/unk63_08094ea0.inc");
#endif
}



void Enemy63_Init(struct Enemy* p);
void Enemy63_Update(struct Enemy* p);
void Enemy63_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gEnemy63Routine = {
    [ENTITY_INIT] =      Enemy63_Init,
    [ENTITY_UPDATE] =    Enemy63_Update,
    [ENTITY_DIE] =       Enemy63_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_08094bcc(struct Enemy* p);
void FUN_08094bd0(struct Enemy* p);
void FUN_08094bf0(struct Enemy* p);

static const EnemyFunc sUpdates1[4] = {
    nop_08094bcc,
    FUN_08094bd0,
    nop_08094bcc,
    FUN_08094bf0,
};

void FUN_08094c80(struct Enemy* p);
void FUN_08094d48(struct Enemy* p);
void FUN_08094e0c(struct Enemy* p);
void FUN_08094ea0(struct Enemy* p);

static const EnemyFunc sUpdates2[4] = {
    FUN_08094c80,
    FUN_08094d48,
    FUN_08094e0c,
    FUN_08094ea0,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
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
      damage : 255,
      unk_0a : 0x41,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      unk_0a : 0x41,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(64), PIXEL(64)},
    },
};

static const s16 s16_ARRAY_ARRAY_08369f44[4][2] = {
    {-0x0180, 0x0000},
    {0x0180, 0x0000},
    {0x0000, -0x0180},
    {0x0000, 0x0180},
};

static const u8 sInitModes[6] = {
    0, 0, 0, 0, 1, 2,
};

static const s8 s8_ARRAY_ARRAY_08369f5a[4][2] = {
    {8, 0},
    {-8, 0},
    {0, 8},
    {0, -8},
};

static const motion_t sMotions[4] = {
    MOTION(SM088_LOCOMO_IF_ICE, 1),
    MOTION(SM088_LOCOMO_IF_ICE, 2),
    MOTION(SM088_LOCOMO_IF_ICE, 3),
    MOTION(SM088_LOCOMO_IF_ICE, 4),
};
