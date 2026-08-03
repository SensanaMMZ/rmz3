#include "collision.h"
#include "enemy.h"
#include "global.h"

static const EnemyFunc sDeads[1];
static const s16 s16_ARRAY_0836773c[3];

#include "entity/macros.h"

void CreateDeathtanzRock(struct Entity* e, s32 x, s32 y, u8 n) {
  struct Enemy* rock = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  s32 i;

  if (rock != NULL) {
    (rock->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(rock, 27);
    (rock->s).tileNum = 0;
    (rock->s).palID = 0;
    (rock->s).flags2 |= WHITE_PAINTABLE;
    (rock->s).invincibleID = (rock->s).uniqueID;
    (rock->s).work[0] = 0;
    (rock->s).coord.x = x;
    (rock->s).coord.y = y;
    (rock->s).unk_28 = e;
    (rock->s).work[2] = n;
  }

  for (i = 0; i <= 2; i++) {
    struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

    if (p != NULL) {
      (p->s).taskCol = 24;
      INIT_ENEMY_ROUTINE(p, 27);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = (p->s).uniqueID;
      (p->s).work[0] = 1;
      (p->s).coord.x = x;
      (p->s).coord.y = y + s16_ARRAY_0836773c[i];
      (p->s).unk_28 = (struct Entity*)rock;
      (p->s).work[2] = n;
      (p->s).work[3] = i;
    }
  }
}

void nop_0807a5bc(struct Enemy* p) {}

void DeathtanzRock_Die(struct Enemy* p);


static bool8 FUN_0807a5c0(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    DeathtanzRock_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const u8 sInitModes[2];
static const struct Collision sCollisions[9];
void DeathtanzRock_Update(struct Enemy* p);

void DeathtanzRock_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] == 0) {
    INIT_BODY(p, sCollisions, 20, NULL);
    p->props[0] = 3;
  } else {
    INIT_BODY(p, sCollisions, 6, NULL);
  }
  SET_BODY_INTERSECT_HANDLER(p, nop_0807a5bc);
  DeathtanzRock_Update(p);
}
static const EnemyFunc sUpdates1[3];
static const EnemyFunc sUpdates2[3];

// 0x0807a6a4
void DeathtanzRock_Update(struct Enemy* p) {
  if (!FUN_0807a5c0(p)) {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

void DeathtanzRock_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0807a6f8(struct Enemy* p) {}

INCASM("asm/enemy/deathtanz_rock_p3.inc");

// 0x0807A89C
void FUN_0807a89c(struct Enemy* p) {
  register struct Entity* q asm("r5");
  q = (p->s).unk_28;
  if (q->mode[0] > 1) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    return;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 k10 asm("r3");
      register s32 z asm("r1");
      register s32 w2 asm("r2");
      {
        register u8 f2 asm("r0");
        f2 = (p->s).flags2;
        k10 = 0x10;
        z = 0;
        asm volatile("" : "+r"(z));
        f2 |= k10;
        (p->s).flags2 = f2;
      }
      (p->s).invincibleID = q->uniqueID;
      w2 = (p->s).work[2];
      if (w2 != 0) {
        register u8 g asm("r0");
        g = (p->s).flags;
        g |= k10;
        (p->s).flags = g;
      } else {
        register u8 fl asm("r1");
        register u8 g2 asm("r0");
        fl = (p->s).flags;
        asm("" : "+r"(fl));
        g2 = 0xEF;
        g2 &= fl;
        (p->s).flags = g2;
      }
      {
        register s32 xf asm("r1");
        u8* oa;
        s32 sh4, ov, m11;
        xf = 1;
        xf &= w2;
        *((u8*)p + 0x4c) = xf;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      {
        register const u16* tb asm("r1");
        register u32 ix asm("r0");
        tb = (const u16*)0x08367748;
        asm volatile("" : "+r"(tb));
        ix = (p->s).work[3];
        ix <<= 1;
        {
          register const u16* e asm("r0");
          asm volatile("add %0, %1, %2" : "=l"(e) : "l"(ix), "l"(tb));
          SetMotion(&p->s, *e);
        }
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register u8* b4 asm("r3");
      register u32 w3 asm("r2");
      {
        register u32 bv asm("r0");
        b4 = (u8*)q + 0xb4;
        bv = *b4;
        w3 = (p->s).work[3];
        if (bv == w3) {
          (p->s).mode[1] = 2;
          (p->s).mode[2] = 0;
        }
      }
      {
        register s32 tc asm("r0");
        register u8* tp asm("r1");
        register u32 bv2 asm("r3");
        bv2 = *b4;
        if (w3 >= bv2) {
          tp = (u8*)p + 0x25;
          tc = 0x17;
        } else {
          tp = (u8*)p + 0x25;
          tc = 0x19;
        }
        *tp = tc;
      }
      {
        register s32 cy asm("r1");
        (p->s).coord.x = (q->coord).x;
        cy = (q->coord).y;
        (p->s).coord.y = cy;
        {
          register const s16* tb2 asm("r2");
          register u32 ix2 asm("r0");
          tb2 = (const s16*)0x0836774E;
          ix2 = (p->s).work[3];
          ix2 <<= 1;
          {
            register const s16* e2 asm("r0");
            asm volatile("add %0, %1, %2" : "=l"(e2) : "l"(ix2), "l"(tb2));
            cy += *e2;
          }
        }
        (p->s).coord.y = cy;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

static const u16 u16_ARRAY_08367754[3];

// 0x0807A97C
void FUN_0807a97c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      const s16* st;
      const u16* tb;
      s32 v;
      SetDDP(&p->body, &sCollisions[7]);
      st = gSineTable;
      tb = u16_ARRAY_08367754;
      v = st[(u8)((u8)tb[(p->s).work[3]] + 0x40)] * 3;
      (p->s).d.x = v;
      if ((p->s).work[2] != 0) {
        (p->s).d.x = -v;
      }
      {
        s32 w = -st[(u8)tb[(p->s).work[3]]];
        (p->s).d.y = w * 3;
      }
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = (p->s).uniqueID;
      (p->s).mode[2]++;
    }
      FALLTHROUGH;
    case 1: {
      s32 x = (p->s).coord.x + (p->s).d.x;
      s32 y;
      (p->s).coord.x = x;
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      if (((u16)FUN_080098a4(x, y) << 16) != 0) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

static const motion_t sMotions2[3];
void FUN_080b7ffc(struct Entity* p, struct Coord* c, motion_t* m, s32 n);

void FUN_0807aa34(struct Enemy* p) {
  EXIT_BODY(p);
  if ((p->s).work[0] == 1) {
    struct Coord c;
    c.x = (p->s).coord.x;
    c.y = (p->s).coord.y;
    FUN_080b7ffc(&p->s, &c, (motion_t*)sMotions2, 3);
  }
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void DeathtanzRock_Init(struct Enemy* p);
void DeathtanzRock_Update(struct Enemy* p);
void DeathtanzRock_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gDeathtanzRockRoutine = {
    [ENTITY_INIT] =      DeathtanzRock_Init,
    [ENTITY_UPDATE] =    DeathtanzRock_Update,
    [ENTITY_DIE] =       DeathtanzRock_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void nop_0807a6f8(struct Enemy* p);

static const EnemyFunc sUpdates1[3] = {
    nop_0807a6f8,
    nop_0807a6f8,
    nop_0807a6f8,
};

void FUN_0807a6fc(struct Enemy* p);
void FUN_0807a89c(struct Enemy* p);
void FUN_0807a97c(struct Enemy* p);

static const EnemyFunc sUpdates2[3] = {
    FUN_0807a6fc,
    FUN_0807a89c,
    FUN_0807a97c,
};

// --------------------------------------------

void FUN_0807aa34(struct Enemy* p);

static const EnemyFunc sDeads[1] = {
    FUN_0807aa34,
};

// --------------------------------------------

static const struct Collision sCollisions[9] = {
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
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(18), PIXEL(32), PIXEL(44)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(18), PIXEL(32), PIXEL(44)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(32), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(32), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(16)},
    },
};

static const s16 s16_ARRAY_0836773c[3] = {
    -0xC00,
    -0x1800,
    -0x2000,
};

static const u8 sInitModes[2] = {0, 1};
static const u8 u8_ARRAY_08367744[4] = {0, 5, 3, 1};

static const motion_t sMotions1[3] = {
    MOTION(SM054_DEATHTANZ_ROCK, 2),
    MOTION(SM054_DEATHTANZ_ROCK, 1),
    MOTION(SM054_DEATHTANZ_ROCK, 0),
};

static const s16 s16_ARRAY_0836774e[3] = {
    -0xC00,
    -0x1800,
    -0x2000,
};

static const u16 u16_ARRAY_08367754[3] = {104, 128, 152};

static const motion_t sMotions2[3] = {
    MOTION(SM054_DEATHTANZ_ROCK, 4),
    MOTION(SM054_DEATHTANZ_ROCK, 5),
    MOTION(SM054_DEATHTANZ_ROCK, 5),
};
