#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "mission.h"
#include "physics.h"
#include "stagerun.h"
#include "story.h"

static const struct Collision sCollisions[];

struct EnemyLemmingles {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 unk_b4[4];
  s32 unk_b8_x;
  u8 unk_bc[8];
};
static_assert(sizeof(struct EnemyLemmingles) == sizeof(struct Enemy));

void Lemmingles_Init(struct Enemy* p);
void Lemmingles_Update(struct Enemy* p);
void Lemmingles_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gLemminglesRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Lemmingles_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Lemmingles_Update,
    [ENTITY_DIE] =       (EnemyFunc)Lemmingles_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_0806e590(struct Entity* e, u8 kind1, u8 kind2, u8 kind3) {
  struct EnemyLemmingles* p = (struct EnemyLemmingles*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_LEMMINGLES);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y;
    (p->s).unk_28 = (void*)e;
    (p->s).work[0] = kind1;
    (p->s).work[1] = kind3;
    (p->s).work[2] = kind2;
    p->unk_b8_x = e->coord.x;
  }
}

// 0x0806e600
static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) { return; }

bool8 FUN_0806e604(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    struct Entity* nest = (p->s).unk_28;
    if (nest != NULL) {
      *(u32*)((u8*)nest + 0xb4) &= ~(1 << (p->s).work[1]);
    }
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & 0x10000) {
      (p->s).mode[1] = 1;
    } else if ((p->body).status & 0x20000) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    Lemmingles_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const EnemyFunc sUpdates1[7];
static const EnemyFunc sUpdates2[7];

bool8 FUN_0806e674(struct Enemy* p) {
  if ((p->s).mode[1] != 6 && *(struct VFX**)&p->props[0] == NULL) {
    switch ((p->s).mode[3]) {
      case 0:
        if (IsFrozen(&p->s)) {
          (sUpdates1[(p->s).mode[1]])(p);
          (sUpdates2[(p->s).mode[1]])(p);
          (p->s).mode[3]++;
          UpdateMotionGraphic(&p->s);
          return TRUE;
        }
        break;
      case 1:
        if (IsFrozen(&p->s)) {
          if (((p->body).status & 0x20001) == 0x20001) {
            (p->s).mode[3] = 0;
          } else {
            return TRUE;
          }
        } else {
          (p->s).mode[3] = 0;
        }
        break;
    }
  }
  return FALSE;
}

static const struct Coord sElementCoord;

void FUN_0806e704(struct Enemy* p) {
  if (*(struct VFX**)&p->props[0] == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    if (((p->body).status & BODY_STATUS_RECOILED)) {
      (p->s).mode[1] = 6;
      (p->s).mode[2] = 0;
    } else {
      struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
      *(struct VFX**)&p->props[0] = e;
      if (e != NULL) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
    }
  }
}

INCASM("asm/enemy/lemmingles_p1_a_b.inc");

static const EnemyFunc sUpdates1[7];
static const EnemyFunc sUpdates2[7];
bool8 FUN_0806e604(struct Enemy* p);
void FUN_0806e704(struct Enemy* p);
bool8 FUN_0806e674(struct Enemy* p);
void Lemmingles_Die(struct Enemy* p);

void Lemmingles_Update(struct Enemy* p) {
  struct Entity* par = (p->s).unk_28;
  if (par != NULL) {
    if (par->mode[0] > 1) {
      (p->s).unk_28 = NULL;
    }
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000 ||
      (gCurStory.s.gameflags[4] & 0x42)) {
    if (par != NULL) {
      *(u32*)((u8*)par + 0xb4) &= ~(1 << (p->s).work[1]);
    }
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (FUN_0806e604(p)) {
    return;
  }
  FUN_0806e704(p);
  if (FUN_0806e674(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

static const EnemyFunc sDeads[3];

void Lemmingles_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0806e96c(struct Enemy* p) {}


void FUN_0806e970(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}


void FUN_0806e990(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, (p->s).work[0] > 1 ? &sCollisions[3] : &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 1;
      *((u8*)p + 0xbd) = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

void FUN_0806e9fc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 f = IsFrozen(&p->s);
      if (f != 0) {
        break;
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      {
        s32 r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (r < 0) {
          (p->s).d.y = f;
          (p->s).coord.y += r;
        }
      }
      break;
    }
  }
}

INCASM("asm/enemy/lemmingles_p2_p2_p2.inc");

// 0x0806ed08
void FUN_0806ed08(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      if ((p->s).work[0] == 1) {
        SetMotion(&p->s, MOTION(0x1D, 0x07));
      }
      if ((p->s).work[0] == 3) {
        SetMotion(&p->s, MOTION(0x1D, 0x0D));
      }
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 x;
      s32 r;
      if ((p->s).work[0] == 1 || (p->s).work[0] == 3) {
        UpdateMotionGraphic(&p->s);
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      x = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = x;
      if ((p->s).d.x > 0) {
        r = PushoutToLeft1(x + 0x400, (p->s).coord.y);
        if (r < 0) {
          (p->s).coord.x += r;
        }
      } else {
        r = PushoutToRight1(x - 0x400, (p->s).coord.y);
        if (r > 0) {
          (p->s).coord.x += r;
        }
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (r < 0) {
        u16 a = GetMetatileAttr((p->s).coord.x, (p->s).coord.y) & 0x10;
        if (a != 0) {
          struct Entity* q = (p->s).unk_28;
          if (q != NULL) {
            *(u32*)((u8*)q + 0xb4) &= ~(1 << (p->s).work[1]);
          }
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          (p->s).mode[1] = 0;
        } else {
          (p->s).coord.y += r;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = a;
        }
      }
      break;
    }
  }
}

// 0x0806ee0c
void FUN_0806ee0c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[0] == 1) {
        SetMotion(&p->s, MOTION(0x1D, 0x04));
      }
      if ((p->s).work[0] == 3) {
        SetMotion(&p->s, MOTION(0x1D, 0x0A));
      }
      (p->s).work[3] = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
      (p->s).work[2] = 0x12;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (u8)--(p->s).work[2];
      if (t != 0) {
        break;
      }
      if ((p->s).work[0] == 1 || (p->s).work[0] == 3) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = t;
      } else {
        u8 g;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 1;
        g = (p->s).work[3];
        if (g == 0) {
          *((u8*)p + 0xbd) = g;
        }
      }
      break;
    }
  }
}

// 0x0806EE94
void FUN_0806ee94(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[0] == 1) {
        SetMotion(&p->s, MOTION(0x1D, 0x05));
      } else {
        SetMotion(&p->s, MOTION(0x1D, 0x0B));
      }
      (p->s).work[2] = 0;
      (p->s).d.y = -0x59C;
      (p->s).d.x = (p->s).d.x * 0xD0 / 256;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 r;
      if ((u8)++(p->s).work[2] == 0x12) {
        if ((p->s).work[0] == 1) {
          SetMotion(&p->s, MOTION(0x1D, 0x06));
        } else {
          SetMotion(&p->s, MOTION(0x1D, 0x0C));
        }
      }
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if ((p->s).work[3] == 0) {
        r = PushoutToDown1((p->s).coord.x, (p->s).coord.y);
        if (r > 0) {
          (p->s).coord.y += r;
        }
      }
      {
        s32 x = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = x;
        if ((p->s).work[3] == 0) {
          if ((p->s).d.x > 0) {
            r = PushoutToLeft1(x, (p->s).coord.y);
            if (r < 0) {
              (p->s).coord.x += r;
            }
          } else {
            r = PushoutToRight1(x, (p->s).coord.y);
            if (r > 0) {
              (p->s).coord.x += r;
            }
          }
        }
      }
      if ((p->s).d.y > 0) {
        s32 z = 0;
        (p->s).mode[1] = 2;
        (p->s).mode[2] = z;
      }
      if ((p->s).work[3] != 0) {
        (p->s).work[3] = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
      }
      break;
    }
  }
}

INCASM("asm/enemy/lemmingles_p2_p2_p2b.inc");

struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
static const motion_t sMotions[13];

// 0x0806f1dc
void FUN_0806f1dc(struct Enemy* p) {
  struct Coord c;
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  {
    u8 f = (p->s).flags & ~COLLIDABLE;
    f &= ~DISPLAY;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(16);
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[8], 3);
  TryDropItem(3, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/lemmingles_p2_p2_p2c.inc");

// --------------------------------------------

void FUN_0806e990(struct Enemy* p);
void FUN_0806e970(struct Enemy* p);
void nop_0806e96c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    FUN_0806e990,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    nop_0806e96c,
};
// clang-format on

void FUN_0806e9fc(struct Enemy* p);
void FUN_0806ea64(struct Enemy* p);
void FUN_0806ed08(struct Enemy* p);
void FUN_0806ee0c(struct Enemy* p);
void FUN_0806ee94(struct Enemy* p);
void FUN_0806efa4(struct Enemy* p);
void FUN_0806f07c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    FUN_0806e9fc,
    FUN_0806ea64,
    FUN_0806ed08,
    FUN_0806ee0c,
    FUN_0806ee94,
    FUN_0806efa4,
    FUN_0806f07c,
};
// clang-format on

// --------------------------------------------

void FUN_0806f1dc(struct Enemy* p);
void FUN_0806f274(struct Enemy* p);
void FUN_0806f07c(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_0806f1dc,
    FUN_0806f274,
    FUN_0806f07c,
};

// --------------------------------------------

static const struct Collision sCollisions[7] = {
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
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
static const u8 sInitModes[4] = {1, 1, 1, 1};

// clang-format off
static const motion_t sMotions[13] = {
    MOTION(SM029_LEMMINGLES, 1),
    MOTION(SM029_LEMMINGLES, 0),
    MOTION(SM029_LEMMINGLES, 3),
    MOTION(SM029_LEMMINGLES, 2),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 1),
    MOTION(SM029_LEMMINGLES, 5),
    MOTION(SM029_LEMMINGLES, 3),
    MOTION(SM029_LEMMINGLES, 11),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 22),
    MOTION(SM029_LEMMINGLES, 23),
    MOTION(SM029_LEMMINGLES, 24),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 19),
    MOTION(SM029_LEMMINGLES, 17),
};


