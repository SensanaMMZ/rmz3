#include "camera.h"
#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "physics.h"
#include "stagerun.h"
#include "zero.h"

struct Enemy* FUN_08098838(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CATTATANK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
    (p->s).work[1] = 1;
  }
  return p;
}

INCASM("asm/enemy/cattatank_p1_p2_a.inc");

extern const EnemyFunc sUpdates1[10];
extern const EnemyFunc sUpdates2[10];
bool8 cattatank_08099e20(struct Enemy* p);
void Cattatank_Die(struct Enemy* p);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

void Cattatank_Update(struct Enemy* p) {
  u8 m;
  if ((p->body).status & BODY_STATUS_DEAD) {
    if ((p->s).mode[1] == 6) {
      if (!IsFrozen(&p->s)) {
        goto dispatch1;
      }
    }
    (p->s).mode[3] = 0;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Cattatank_Die(p);
    return;
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x3000) {
    if (gStageRun.vm.camera.viewport.y + 0x4FFF < (p->s).coord.y + 0x2000) {
      if ((p->s).work[1] == 1) {
        (p->s).mode[3] = 1;
        PlaySound(0x2a);
        TryDropItem(1, &(p->s).coord);
        if (gMission.enemyCount <= 0x270E) {
          gMission.enemyCount++;
        }
        TryDropZakoDisk(p, &(p->s).coord);
        (p->s).flags &= ~DISPLAY;
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
        return;
      }
    }
  }
dispatch1:
  (sUpdates1[(p->s).mode[1]])(p);
  cattatank_08099e20(p);
  m = (p->s).mode[1];
  if (m == 6 || m == 7) goto dispatch2;
  if (m == 9) goto dispatch2;
  if (IsFrozen(&p->s)) {
    return;
  }
dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/cattatank_p1_p2_b.inc");

bool8 nop_08099090(struct Enemy* p) { return TRUE; }

void cattatank_08099094(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags &= ~DISPLAY;
      (p->s).work[2] = 0x32;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((p->s).work[2] != 0) {
        if (--(p->s).work[2] != 0) break;
      }
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 nop_080990d4(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[18];

void FUN_080990d8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      {
        u32 fl = (p->s).flags;
        register u32 t asm("r0");
        register s32 z5 asm("r5");
        t = 1;
        asm volatile("" : "+r"(t));
        z5 = 0;
        asm volatile("" :: "r"(z5));
        t |= fl;
        (p->s).flags = t;
      }
      SetMotion(&p->s, 0xD503);
      SetDDP(&p->body, &sCollisions[1]);
      if ((pZero2->s).coord.x < (p->s).coord.x) {
        s32 z2 = 0;
        asm("" : "+r"(z2));
        (p->s).flags &= 0xEF;
        ((p->s).spr).xflip = z2;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        *((u8*)p + 0xb8) = z2;
      } else {
        s32 o3 = 1;
        (p->s).flags |= 0x10;
        ((p->s).spr).xflip = o3;
        {
          register u8* oa asm("ip");
          u32 sh4;
          s32 ov, m11;
          oa = (u8*)p + 0x4a;
          sh4 = 0x10;
          asm("" : "+r"(sh4));
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          m11 |= sh4;
          *oa = m11;
        }
        *((u8*)p + 0xb8) = o3;
      }
      (p->s).d.x >>= 1;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 ny, nx, off, push;
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      nx = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = nx;
      if ((p->s).d.x > 0) {
        off = -0x800;
        asm volatile("");
      } else {
        off = 0x800;
        asm volatile("");
      }
      push = PushoutToUp1(nx + off, ny);
      if (push != 0) {
        (p->s).d.y = 0;
        (p->s).coord.y += push;
        goto inc34;
      }
      break;
    }
    case 2:
      (*((u8*)p + 0xbb))++;
      SetMotion(&p->s, 0xD504);
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
      inc34:
        (p->s).mode[2]++;
      }
      break;
    case 4:
      SetMotion(&p->s, 0xD500);
      (p->s).work[2] = 0x14;
      (p->s).mode[2]++;
      // fallthrough
    case 5: {
      s32 t;
      u32 t8;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t8 = (u8)t;
      if (t8 == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = t8;
      }
      break;
    }
  }
}

bool8 nop_0809925c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/cattatank_p4.inc");

bool8 nop_080994e8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/cattatank_p5.inc");

bool8 nop_0809973c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/cattatank_p6.inc");

bool8 nop_08099950(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[18];

void FUN_08099954(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0xD50C);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0x18;
      if ((pZero2->s).coord.x < (p->s).coord.x) {
        (p->s).d.x = 0x60;
      } else {
        (p->s).d.x = -0x60;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 ny;
      s32 v = (p->s).d.x;
      v += (-v << 4) >> 8;
      (p->s).d.x = v;
      (p->s).coord.x += v;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      {
        s32 po;
        if ((p->s).d.x > 0) {
          po = PushoutToUp1((p->s).coord.x - 0xA00, ny);
        } else {
          po = PushoutToUp1((p->s).coord.x + 0xA00, ny);
        }
        if (po != 0) {
          u8* bb = (u8*)p + 0xbb;
          u8 nv = *bb + 1;
          s32 z = 0;
          *bb = nv;
          (p->s).coord.y += po;
          (p->s).d.y = z;
        }
      }
      {
        register s32 fl asm("r3");
        s32 c10;
        fl = (p->s).flags;
        c10 = 0x10;
        asm("" : "+r"(c10));
        if (!(c10 & fl)) {
          if ((pZero2->s).coord.x > (p->s).coord.x) {
            s32 one = 1;
            u8* oa;
            s32 ov;
            {
              s32 cc = 0x10;
              asm("" : "+r"(cc));
              (p->s).flags = cc | fl;
              asm("" : "+r"(fl));
            }
            ((p->s).spr).xflip = one;
            oa = (u8*)&((p->s).spr).oam + 6;
            ov = *oa;
            {
              s32 m11 = -0x11;
              asm("" : "+r"(m11));
              *oa = (m11 & ov) | c10;
            }
            *(u8*)((u8*)p + 0xb8) = one;
          }
        } else {
          if ((pZero2->s).coord.x < (p->s).coord.x) {
            s32 zz = 0;
            u8* oa;
            s32 ov;
            {
              s32 cc = 0xEF;
              asm("" : "+r"(cc));
              (p->s).flags = cc & fl;
              asm("" : "+r"(fl));
            }
            ((p->s).spr).xflip = zz;
            oa = (u8*)&((p->s).spr).oam + 6;
            ov = *oa;
            {
              s32 m11 = -0x11;
              asm("" : "+r"(m11));
              *oa = m11 & ov;
            }
            *(u8*)((u8*)p + 0xb8) = zz;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      {
        s32 raw = (p->s).work[2] - 1;
        u8 t;
        (p->s).work[2] = raw;
        t = raw;
        if (t == 0) {
          (p->s).mode[1] = 1;
          (p->s).mode[2] = t;
        }
      }
      break;
    }
  }
}

bool8 nop_08099a94(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/cattatank_p8.inc");

bool8 nop_08099ce0(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[18];

// 0x08099ce4
void FUN_08099ce4(struct Enemy* p) {
  s32 r;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[6]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if ((r = PushoutToUp1((p->s).coord.x - PIXEL(10), (p->s).coord.y)) != 0 ||
          (r = PushoutToUp1((p->s).coord.x + PIXEL(10), (p->s).coord.y)) != 0) {
        (p->s).coord.y += r;
        (p->s).d.y = 0;
      }
      break;
  }
  if (isKilled(*(struct Entity**)&p->props[8])) {
    p->props[12] = 0;
    *(struct Entity**)&p->props[8] = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 nop_08099d7c(struct Enemy* p) { return TRUE; }


void nop_08099d80(struct Enemy* p) {}

bool8 nop_08099d84(struct Enemy* p) { return TRUE; }

// 0x08099d88
void FUN_08099d88(struct Enemy* p) {
  s32 r;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[6]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if ((r = PushoutToUp1((p->s).coord.x - PIXEL(10), (p->s).coord.y)) != 0 ||
          (r = PushoutToUp1((p->s).coord.x + PIXEL(10), (p->s).coord.y)) != 0) {
        (p->s).coord.y += r;
        (p->s).d.y = 0;
      }
      break;
  }
  if (isKilled(*(struct Entity**)&p->props[8])) {
    p->props[12] = 0;
    *(struct Entity**)&p->props[8] = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoords[1];

bool8 cattatank_08099e20(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)&p->props[8];
  struct VFX* e;
  u8 attr;

  if (*slot == NULL && ((p->body).status & 1)) {
    e = ApplyElementEffect(0, &p->s, sElementCoords);
    *slot = e;
    if ((p->s).mode[1] != 6) {
      if (e != NULL) {
        attr = *(u8*)((u8*)p + 0x97) & 0xf0;
        if (attr == 0x10) {
          p->props[12] = 1;
          (p->s).mode[1] = 7;
          (p->s).mode[2] = 0;
        } else if (attr == 0x30) {
          p->props[12] = 2;
          (p->s).mode[1] = 9;
          (p->s).mode[2] = 0;
        }
      }
    } else if (e != NULL) {
      attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        p->props[12] = 1;
      } else if (attr == 0x30) {
        p->props[12] = 2;
      }
    }
  }
  return TRUE;
}

INCASM("asm/enemy/cattatank_p11_b.inc");

void Cattatank_Init(struct Enemy* p);
void Cattatank_Update(struct Enemy* p);
void Cattatank_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gCattatankRoutine = {
    [ENTITY_INIT] =      Cattatank_Init,
    [ENTITY_UPDATE] =    Cattatank_Update,
    [ENTITY_DIE] =       Cattatank_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

bool8 nop_08099090(struct Enemy* p);
bool8 nop_080990d4(struct Enemy* p);
bool8 nop_0809925c(struct Enemy* p);
bool8 nop_080994e8(struct Enemy* p);
bool8 nop_0809973c(struct Enemy* p);
bool8 nop_08099950(struct Enemy* p);
bool8 nop_08099a94(struct Enemy* p);
bool8 nop_08099ce0(struct Enemy* p);
bool8 nop_08099d7c(struct Enemy* p);
bool8 nop_08099d84(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    (EnemyFunc)nop_08099090,
    (EnemyFunc)nop_080990d4,
    (EnemyFunc)nop_0809925c,
    (EnemyFunc)nop_080994e8,
    (EnemyFunc)nop_0809973c,
    (EnemyFunc)nop_08099950,
    (EnemyFunc)nop_08099a94,
    (EnemyFunc)nop_08099ce0,
    (EnemyFunc)nop_08099d7c,
    (EnemyFunc)nop_08099d84,
};
// clang-format on

void cattatank_08099094(struct Enemy* p);
void FUN_080990d8(struct Enemy* p);
void FUN_08099260(struct Enemy* p);
void FUN_080994ec(struct Enemy* p);
void FUN_08099740(struct Enemy* p);
void FUN_08099954(struct Enemy* p);
void FUN_08099a98(struct Enemy* p);
void FUN_08099ce4(struct Enemy* p);
void nop_08099d80(struct Enemy* p);
void FUN_08099d88(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    cattatank_08099094,
    FUN_080990d8,
    FUN_08099260,
    FUN_080994ec,
    FUN_08099740,
    FUN_08099954,
    FUN_08099a98,
    FUN_08099ce4,
    nop_08099d80,
    FUN_08099d88,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[18] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 1,
      priorityLayer : 0xFFFFFFFF,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(12), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(16), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(37), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(49), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
};

static const struct Coord sElementCoords[1] = {
    {PIXEL(0), -PIXEL(18)},
};
