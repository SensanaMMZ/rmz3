#include "collision.h"
#include "physics.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "story.h"
#include "vfx.h"

struct Enemy* CreatePetatria(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_PETATRIA);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

INCASM("asm/enemy/petatria_p1_pre_p1_p2_a.inc");

extern const EnemyFunc sUpdates1[10];
extern const EnemyFunc sUpdates2[10];
bool8 FUN_08091188(struct Enemy* p);
void Petatria_Die(struct Enemy* p);

void Petatria_Update(struct Enemy* p) {
  struct Entity** slot;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Petatria_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  FUN_08091188(p);
  if (IsFrozen(&p->s)) {
    return;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (*slot != NULL) {
    if (!isKilled(*slot)) {
      return;
    }
    *slot = NULL;
  }
  (sUpdates2[(p->s).mode[1]])(p);
}

struct VFX* FUN_080c4914(struct Coord* c, u8 a1, u16 a2, s32 a3);
u32 TryDropItem(u32 table, struct Coord* c);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

void Petatria_Die(struct Enemy* p) {
  if (gCurStory.s.gameflags[4] & 0x40) {
    u32 z2;
    {
      u32 fl = (p->s).flags & 0xFE;
      z2 = 0;
      fl &= 0xFD;
      (p->s).flags = fl;
    }
    {
      u8* w = (u8*)p + 0x8c;
      *(u32*)w = z2;
      asm("" : "+r"(w));
      w += 4;
      *(u32*)w = z2;
      asm("" : "+r"(w));
      w += 4;
      asm("" : "+r"(w));
      *(u8*)w = z2;
    }
    (p->s).flags &= 0xFB;
    {
      u32 tbl = (u32)gEnemyFnTable;
      u32 id = ((p->s).id) << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = 3;
      (p->s).onUpdate = (void*)((*rt)[3]);
    }
    return;
  }
  {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0:
        (p->s).mode[2] = 0xA;
        {
          u8* w = (u8*)p + 0x8c;
          *(u32*)w = m;
          asm("" : "+r"(w));
          w += 4;
          *(u32*)w = m;
          asm("" : "+r"(w));
          w += 4;
          asm("" : "+r"(w));
          *(u8*)w = m;
        }
        (p->s).flags &= 0xFB;
        (p->s).d.y = m;
        (p->s).d.x = m;
        // fallthrough
      case 1:
      case 10:
        (p->s).mode[2]++;
        break;
      case 11: {
        struct Coord c;
        struct Coord c2;
        struct Coord* cp;
        u32 r;
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y;
        CreateSmoke(1, &c);
        PlaySound(0x2A);
        cp = &(p->s).coord;
        TryDropItem(4, cp);
        r = RANDOM(RNG_0202f388) & 3;
        c2.x = (p->s).coord.x;
        c2.y = (p->s).coord.y + -0xC00;
        FUN_080c4914(&c2, ((p->s).flags >> 4) & 1, 0x7E1A, r);
        FUN_080c4914(&c2, ((p->s).flags >> 4) & 1, 0x7E1B, r);
        FUN_080c4914(&c2, ((p->s).flags >> 4) & 1, 0x7E1C, r);
        if (gMission.enemyCount <= 0x270E) {
          gMission.enemyCount++;
        }
        TryDropZakoDisk(p, cp);
        (p->s).flags &= 0xFE;
        {
          u32 tbl = (u32)gEnemyFnTable;
          u32 id = ((p->s).id) << 2;
          EntityFunc** rt = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = 4;
          (p->s).onUpdate = (void*)((*rt)[4]);
        }
        break;
      }
    }
  }
}

bool8 FUN_080902a8(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_B3) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

INCASM("asm/enemy/petatria_p1_pre_p2.inc");

bool8 FUN_080906ec(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_B3) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

INCASM("asm/enemy/petatria_p1_pre_p3_p1.inc");

bool8 FUN_08090b20(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/petatria_p1_pre_p3_p2.inc");

bool8 FUN_08090c60(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[12];
void FUN_0809118c(struct Enemy* p, struct Coord* c);

void FUN_08090c64(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[7]);
      SetMotion(&p->s, 0x7E12);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).work[2] = 0x1E;
      goto adv;
    case 3:
      SetMotion(&p->s, 0x7E13);
      if (*(u8*)((u8*)p + 0xb8) == 1) {
        c.x = (p->s).coord.x + 0x400;
      } else {
        c.x = (p->s).coord.x - 0x400;
      }
      c.y = (p->s).coord.y - 0x1900;
      FUN_0809118c(p, &c);
      PlaySound(0x2c);
      (p->s).mode[2]++;
      /* fallthrough */
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    adv:
      (p->s).mode[2]++;
      break;
    case 5:
      SetMotion(&p->s, 0x7E14);
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      /* fallthrough */
    case 2:
    case 6: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 7:
      SetMotion(&p->s, 0x7E15);
      (p->s).mode[2]++;
      /* fallthrough */
    case 8:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08090da4(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[12];

void FUN_08090da8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[11]);
      (p->s).work[2] = 4;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2:
      SetDDP(&p->body, &sCollisions[10]);
      SetMotion(&p->s, 0x7E16);
      (p->s).work[2] = 0x60;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      (p->s).work[2]--;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      if ((p->s).work[2] != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 4:
      SetMotion(&p->s, 0x7E18);
      (p->s).work[2] = (u32)RANDOM(RNG_0202f388) % 0x14 + 0xA;
      (p->s).mode[2]++;
      /* fallthrough */
    case 5: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 6:
      SetMotion(&p->s, 0x7E19);
      (p->s).mode[2]++;
      /* fallthrough */
    case 7: {
      u8 z;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      z = 0;
      (p->s).mode[1] = z;
      (p->s).mode[2] = z;
      break;
    }
  }
}


bool8 FUN_08090edc(struct Enemy* p) { return TRUE; }

void FUN_08090ee0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[11]);
      (p->s).work[2] = 4;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      s32 v;
      SetDDP(&p->body, &sCollisions[10]);
      SetMotion(&p->s, 0x7E17);
      (p->s).work[2] = 0x60;
      if (*((u8*)p + 0xb8) == 1) {
        s32 c = 0xCC;
        asm("" : "+r"(c));
        v = -c;
        goto vs;
      }
      v = 0xCC;
    vs:
      (p->s).d.x = v;
      (p->s).d.y = 0;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3: {
      s32 push;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (push == 0) {
        break;
      }
      (p->s).coord.y += push;
      (p->s).mode[2]++;
      break;
    }
    case 4:
      (p->s).work[2]--;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      if ((p->s).work[2] != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 5:
      SetMotion(&p->s, 0x7E18);
      (p->s).work[2] = (RANDOM(RNG_0202f388) % 0x14) + 0xA;
      (p->s).mode[2]++;
      // fallthrough
    case 6: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 7:
      SetMotion(&p->s, 0x7E19);
      (p->s).mode[2]++;
      // fallthrough
    case 8:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08091068(struct Enemy* p) { return TRUE; }

// 0x0809106C
void FUN_0809106c(struct Enemy* p) {
  register s32 m2 asm("r6");
  m2 = (p->s).mode[2];
  switch (m2) {
    case 0: {
      register s32 len asm("r5");
      s32 dx;
      s32 dy;
      dx = (p->s).unk_coord.x - (p->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).unk_coord.y - (p->s).coord.y;
      (p->s).d.y = dy;
      dx >>= 2;
      {
        s32 a = dx * dx;
        s32 b;
        dy >>= 2;
        b = dy * dy;
        len = (u32)Sqrt(a + b) << 2;
      }
      if (len != 0) {
        (p->s).d.x = ((p->s).d.x << 8) / len;
        (p->s).d.y = ((p->s).d.y << 8) / len;
      }
      (p->s).d.x = ((p->s).d.x << 9) >> 8;
      (p->s).d.y = ((p->s).d.y << 9) >> 8;
      *(s32*)((u8*)p + 0xb4) = len;
      if ((p->s).d.x > 0) {
        register s32 one asm("r2");
        register u8* a4c asm("r0");
        register u8* a4a asm("r3");
        register s32 k10 asm("r2");
        register u8 ov asm("r1");
        register s32 m asm("r0");
        one = 1;
        {
          register u8 fl asm("r1");
          register u8 g asm("r0");
          fl = (p->s).flags;
          g = 0x10;
          g |= fl;
          (p->s).flags = g;
        }
        a4c = (u8*)p + 0x4c;
        *a4c = one;
        a4a = (u8*)p + 0x4a;
        k10 = 0x10;
        ov = *a4a;
        m = 0x11;
        m = -m;
        m &= ov;
        m |= k10;
        *a4a = m;
      } else {
        register u8* b4c asm("r0");
        register u8* b4a asm("r2");
        register u8 ov2 asm("r1");
        register s32 m2b asm("r0");
        {
          register u8 fl2 asm("r1");
          register u8 g2 asm("r0");
          fl2 = (p->s).flags;
          asm("" : "+r"(fl2));
          g2 = 0xEF;
          g2 &= fl2;
          (p->s).flags = g2;
        }
        b4c = (u8*)p + 0x4c;
        *b4c = m2;
        b4a = (u8*)p + 0x4a;
        ov2 = *b4a;
        m2b = 0x11;
        m2b = -m2b;
        m2b &= ov2;
        *b4a = m2b;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32* q;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      q = (s32*)((u8*)p + 0xb4);
      *q += -0x200;
      break;
    }
  }
}

bool8 FUN_08091150(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/petatria_p1_pre_p3_p7.inc");

void FUN_08091154(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

bool8 FUN_08091168(struct Enemy* p) { return TRUE; }


void FUN_0809116c(struct Enemy* p) {}

bool8 FUN_08091170(struct Enemy* p) { return TRUE; }


void FUN_08091174(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

bool8 FUN_08091188(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/petatria_p4_p1.inc");

void nop_0809127c(struct Enemy* p) {}

void Petatria_Init(struct Enemy* p);
void Petatria_Update(struct Enemy* p);
void Petatria_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPetatriaRoutine = {
    [ENTITY_INIT] =      Petatria_Init,
    [ENTITY_UPDATE] =    Petatria_Update,
    [ENTITY_DIE] =       Petatria_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_080902a8(struct Enemy* p);
bool8 FUN_080906ec(struct Enemy* p);
bool8 FUN_08090b20(struct Enemy* p);
bool8 FUN_08090c60(struct Enemy* p);
bool8 FUN_08090da4(struct Enemy* p);
bool8 FUN_08090edc(struct Enemy* p);
bool8 FUN_08091068(struct Enemy* p);
bool8 FUN_08091150(struct Enemy* p);
bool8 FUN_08091168(struct Enemy* p);
bool8 FUN_08091170(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    (EnemyFunc)FUN_080902a8,
    (EnemyFunc)FUN_080906ec,
    (EnemyFunc)FUN_08090b20,
    (EnemyFunc)FUN_08090c60,
    (EnemyFunc)FUN_08090da4,
    (EnemyFunc)FUN_08090edc,
    (EnemyFunc)FUN_08091068,
    (EnemyFunc)FUN_08091150,
    (EnemyFunc)FUN_08091168,
    (EnemyFunc)FUN_08091170,
};
// clang-format on

void FUN_080902c8(struct Enemy* p);
void FUN_0809070c(struct Enemy* p);
void FUN_08090b24(struct Enemy* p);
void FUN_08090c64(struct Enemy* p);
void FUN_08090da8(struct Enemy* p);
void FUN_08090ee0(struct Enemy* p);
void FUN_0809106c(struct Enemy* p);
void FUN_08091154(struct Enemy* p);
void FUN_0809116c(struct Enemy* p);
void FUN_08091174(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    FUN_080902c8,
    FUN_0809070c,
    FUN_08090b24,
    FUN_08090c64,
    FUN_08090da8,
    FUN_08090ee0,
    FUN_0809106c,
    FUN_08091154,
    FUN_0809116c,
    FUN_08091174,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[12] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(0), -PIXEL(29), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(26), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(3), -PIXEL(25), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(22), -PIXEL(25), PIXEL(14), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
};

static const s32 s32_ARRAY_08369728[16] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};

// clang-format off
static const motion_t sMotions1[6] = {
    MOTION(SM126_PETATRIA, 0),
    MOTION(SM126_PETATRIA, 1),
    MOTION(SM126_PETATRIA, 2),
    MOTION(SM126_PETATRIA, 3),
    MOTION(SM126_PETATRIA, 4),
    MOTION(SM126_PETATRIA, 5),
};
// clang-format on

static const s32 s32_ARRAY_08369774[6] = {
    PIXEL(1), PIXEL(2), PIXEL(5), PIXEL(5), PIXEL(2), PIXEL(1),
};
static const s32 s32_ARRAY_0836978c[6] = {
    PIXEL(1), PIXEL(1), PIXEL(2), PIXEL(5), PIXEL(5), PIXEL(2),
};

// clang-format off
static const motion_t sMotions2[6] = {
    MOTION(SM126_PETATRIA, 6),
    MOTION(SM126_PETATRIA, 7),
    MOTION(SM126_PETATRIA, 8),
    MOTION(SM126_PETATRIA, 9),
    MOTION(SM126_PETATRIA, 10),
    MOTION(SM126_PETATRIA, 11),
};
// clang-format on

static const s32 s32_ARRAY_083697b0[6] = {
    -PIXEL(1), -PIXEL(2), -PIXEL(5), -PIXEL(5), -PIXEL(2), -PIXEL(1),
};
static const s32 s32_ARRAY_083697c8[6] = {
    -PIXEL(1), -PIXEL(1), -PIXEL(2), -PIXEL(5), -PIXEL(5), -PIXEL(2),
};
