#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "story.h"
#include "mission.h"

void CapsuleCannon_Init(struct Enemy* p);
void CapsuleCannon_Update(struct Enemy* p);
void CapsuleCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gCapsuleCannonRoutine = {
    [ENTITY_INIT] =      CapsuleCannon_Init,
    [ENTITY_UPDATE] =    CapsuleCannon_Update,
    [ENTITY_DIE] =       CapsuleCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* CreateCapsuleCannon(struct Coord* c, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CAPSULE_CANNON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

INCASM("asm/enemy/capsule_cannon_pre_p1_p1_a.inc");

extern const EnemyFunc sUpdates1[6];
extern const EnemyFunc sUpdates2[6];
extern const struct Collision sCollisions[4];
bool8 FUN_08085c4c(struct Enemy* p);
void CapsuleCannon_Die(struct Enemy* p);

void CapsuleCannon_Update(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    CapsuleCannon_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  FUN_08085c4c(p);
  if (*(struct Entity**)((u8*)p + 0xbc) == NULL) {
    if (IsFrozen(&p->s)) {
      return;
    }
    if (*(struct Entity**)((u8*)p + 0xbc) == NULL) {
      goto dispatch2;
    }
  }
  if (isKilled(*(struct Entity**)((u8*)p + 0xbc))) {
    if ((p->s).mode[1] == 2) {
      SetDDP(&p->body, &sCollisions[2]);
    } else {
      SetDDP(&p->body, &sCollisions[0]);
    }
    *(struct Entity**)((u8*)p + 0xbc) = NULL;
  }
  return;

dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

struct Entity* CreateSmoke(u8 kind, struct Coord* c);
struct VFX* CreateVFX60(struct Coord* c, u8 a1, u16 a2, s32 a3);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

void CapsuleCannon_Die(struct Enemy* p) {
  struct Coord c;
  struct Coord c2;
  if (gCurStory.s.gameflags[4] & 0x40) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  {
    u8 m2 = (p->s).mode[2];
    switch (m2) {
      case 0:
        (p->s).mode[2] = 1;
        (p->body).status = m2;
        (p->body).prevStatus = m2;
        (p->body).invincibleTime = m2;
        (p->s).flags &= ~COLLIDABLE;
        // fallthrough
      case 1:
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y;
        (p->s).mode[2]++;
        break;
      case 2: {
        s32 x;
        u32 r;
        struct Coord* pc;
        u8* pb8;
        if (((p->s).flags & X_FLIP) == 0) {
          x = (p->s).d.x + -0x800;
        } else {
          x = (p->s).d.x + 0x800;
        }
        c.x = x;
        c.y = (p->s).d.y;
        CreateSmoke(1, &c);
        r = RANDOM(RNG_0202f388) & 3;
        c2.x = (p->s).coord.x;
        c2.y = (p->s).coord.y;
        pb8 = (u8*)p + 0xb8;
        CreateVFX60(&c2, *pb8, 0x6803, r);
        CreateVFX60(&c2, *pb8, 0x6804, r);
        CreateVFX60(&c2, *pb8, 0x6805, r);
        PlaySound(0x2A);
        if (((p->s).flags & X_FLIP) == 0) {
          (p->s).coord.x += -0xC00;
        } else {
          (p->s).coord.x += 0xC00;
        }
        pc = &(p->s).coord;
        TryDropItem(3, pc);
        if (gMission.enemyCount <= 0x270E) {
          gMission.enemyCount++;
        }
        TryDropZakoDisk(p, pc);
        (p->s).flags &= ~DISPLAY;
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
        break;
      }
    }
  }
}

bool8 FUN_08085a08(struct Enemy* p) { return TRUE; }


void nop_08085a0c(struct Enemy* p) {}

bool8 FUN_08085a10(struct Enemy* p) { return TRUE; }

// 0x08085a14
void FUN_08085a14(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x68, 0x01));
      (p->s).work[2] = 0x50;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      *((u8*)p + 0xb9) = 0;
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      (p->s).mode[1] = 2, (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_08085a9c(struct Enemy* p) { return TRUE; }

struct Projectile* CreateLemon(struct Coord* c, s32 r1, u8 r2);
struct Entity* CreateSmoke(u8 kind, struct Coord* c);

void FUN_08085aa0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x6800);
      PlaySound(0x103);
      *((u8*)p + 0xb9) = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      *((u8*)p + 0xb9) = 1;
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).work[2] = 8;
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    case 4: {
      struct Coord c;
      register s32 k asm("r1");
      s32 x, y, a;
      register struct Coord* c0 asm("r0");
      register s32 s2 asm("r1");
      register s32 a2 asm("r2");
      x = (p->s).coord.x;
      c.x = x;
      y = (p->s).coord.y;
      c.y = y;
      if (!((p->s).flags & 0x10)) {
        a = 0x15;
        k = -0x1200;
      } else {
        a = 0x6B;
        k = 0x1200;
      }
      c.x = x + k;
      asm volatile("" :: "r"(k));
      c.y = y + -0xA00;
      s2 = 0x200;
      c0 = &c;
      a2 = a;
      CreateLemon(c0, s2, a2);
      CreateSmoke(3, &c);
      x = (p->s).coord.x;
      c.x = x;
      y = (p->s).coord.y;
      c.y = y;
      if (!((p->s).flags & 0x10)) {
        a = 0xEB;
        k = -0x1200;
      } else {
        a = 0x95;
        k = 0x1200;
      }
      c.x = x + k;
      asm volatile("" :: "r"(k));
      c.y = y + 0xA00;
      s2 = 0x200;
      c0 = &c;
      a2 = a;
      CreateLemon(c0, s2, a2);
      CreateSmoke(3, &c);
      PlaySound(0x2C);
      SetMotion(&p->s, 0x6802);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        s32 z;
        PlaySound(0x103);
        z = 0;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      break;
  }
}

bool8 FUN_08085c14(struct Enemy* p) { return TRUE; }

void FUN_08085c18(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

bool8 FUN_08085c2c(struct Enemy* p) { return TRUE; }

void FUN_08085c30(struct Enemy* p) {}

bool8 FUN_08085c34(struct Enemy* p) { return TRUE; }


void FUN_08085c38(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

bool8 FUN_08085c4c(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)&p->props[8];
  u8 attr;

  if (*slot == NULL && ((p->body).status & 1)) {
    if ((p->s).flags & X_FLIP) {
      *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
    } else {
      *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
    }
    if (*(struct VFX**)&p->props[8] != NULL) {
      attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        SetDDP(&p->body, &sCollisions[3]);
      } else if (attr == 0x30) {
        SetDDP(&p->body, &sCollisions[3]);
      }
    }
  }
  return TRUE;
}

void FUN_08085cc4(struct Body* body, struct Coord* c) {
  u8 t = ((body->enemy)->processing)->atkType;
  if (t == 3 || t == 14 || t == 15) {
    struct CollidableEntity* parent = body->parent;
    if ((parent->body).status & BODY_STATUS_DEAD) {
      if ((parent->s).coord.x < c->x) {
        ((struct Enemy*)parent)->props[6] = 0xFF;
      } else {
        ((struct Enemy*)parent)->props[6] = 0xFE;
      }
    }
  }
}

bool8 FUN_08085a08(struct Enemy* p);
bool8 FUN_08085a10(struct Enemy* p);
bool8 FUN_08085a9c(struct Enemy* p);
bool8 FUN_08085c14(struct Enemy* p);
bool8 FUN_08085c2c(struct Enemy* p);
bool8 FUN_08085c34(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)FUN_08085a08,
    (EnemyFunc)FUN_08085a10,
    (EnemyFunc)FUN_08085a9c,
    (EnemyFunc)FUN_08085c14,
    (EnemyFunc)FUN_08085c2c,
    (EnemyFunc)FUN_08085c34,
};
// clang-format on

void nop_08085a0c(struct Enemy* p);
void FUN_08085a14(struct Enemy* p);
void FUN_08085aa0(struct Enemy* p);
void FUN_08085c18(struct Enemy* p);
void FUN_08085c30(struct Enemy* p);
void FUN_08085c38(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    nop_08085a0c,
    FUN_08085a14,
    FUN_08085aa0,
    FUN_08085c18,
    FUN_08085c30,
    FUN_08085c38,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(7), PIXEL(0), PIXEL(17), PIXEL(29)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {-PIXEL(7), PIXEL(0), PIXEL(17), PIXEL(29)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(7), PIXEL(0), PIXEL(17), PIXEL(29)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(7), PIXEL(0), PIXEL(17), PIXEL(29)},
    },
};

static const struct Coord sElementCoord = {-PIXEL(8), PIXEL(0)};
