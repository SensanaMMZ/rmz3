#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"
#include "story.h"

static const struct Collision sCollisions[25];

static const EnemyFunc sDeads[2];

struct Enemy* FUN_0808a0ec(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_BASE);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

void nop_0808a140(struct Enemy* p) {}

void PantheonBase_Die(struct Enemy* p);

bool8 FUN_0808a144(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    {
      u32 t = (p->body).status & BODY_STATUS_SLASHED;
      if (t != 0) {
        (p->s).mode[1] = 1;
      } else {
        (p->s).mode[1] = t;
      }
    }
    PantheonBase_Die(p);
    return 1;
  }
  return 0;
}

static const EnemyFunc sUpdates1[2];
static const EnemyFunc sUpdates2[2];

// 0x0808A194
bool32 pBase_0808a194(struct Enemy* p) {
  if (*(struct Entity**)((u8*)p + 0xb4) == NULL) {
    struct Entity* q = (p->s).unk_28;
    switch ((p->s).mode[3]) {
      case 0:
        if (IsFrozen(&p->s)) {
          (sUpdates1[(p->s).mode[1]])(p);
          (sUpdates2[(p->s).mode[1]])(p);
          (p->s).mode[3]++;
          UpdateMotionGraphic(&p->s);
          return 1;
        }
        break;
      case 1: {
        u32 fr;
        (p->s).coord.x = q->coord.x;
        (p->s).coord.y = q->coord.y;
        fr = IsFrozen(&p->s);
        if (fr) {
          return 1;
        }
        (p->s).mode[3] = fr;
        break;
      }
    }
  }
  return 0;
}

static const struct Coord sElementCoord;

void pBase_0808a210(struct Enemy* p) {
  if (*(struct VFX**)&p->props[0] == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *(struct VFX**)&p->props[0] = e;
    if (e != NULL) {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
  }
}

static const u8 sInitModes[1];
void PantheonBase_Update(struct Enemy* p);

// 0x0808A248
void PantheonBase_Init(struct Enemy* p) {
  u8 g40;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((gSystemSavedataManager.mods[9] & 8) && (g40 = gCurStory.s.gameflags[0] & 0x40) == 0) {
    INIT_BODY(p, sCollisions, 0x10, NULL);
  } else {
    INIT_BODY(p, sCollisions, 0xC, NULL);
  }
  SET_BODY_INTERSECT_HANDLER(p, nop_0808a140);
  *(u32*)&p->props[0] = 0;
  PantheonBase_Update(p);
}

INCASM("asm/enemy/pantheon_base_p2_pre_b.inc");

void PantheonBase_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0808a3f4(struct Enemy* p) {}


void pBase_0808a3f8(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[0]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void pBase_0808a438(struct Enemy* p) {
  struct Entity* parent = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x6d, 0));
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x = parent->coord.x;
      (p->s).coord.y = parent->coord.y;
      break;
  }
}

static const u8 sCollisionIdxs[9];

// 0x0808a47c
void pBase_0808a47c(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x6D, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t;
      SetDDP(&p->body, &sCollisions[sCollisionIdxs[(s8)(p->s).motion.cmdIdx]]);
      t = (q->flags >> 4) & 1;
      SET_XFLIP(p, t);
      (p->s).coord.x = (q->coord).x;
      (p->s).coord.y = (q->coord).y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

#include "mission.h"
#include "vfx.h"

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
static const motion_t sMotions[10];

// 0x0808a514
void pBase_0808a514(struct Enemy* p) {
  struct Coord c;
  struct Coord* co;
  u8* m;
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    u8* qq = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(qq));
    z = 0;
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *qq = z;
    t = (p->s).flags;
    f = 0xFB;
    f &= t;
    asm volatile("" ::"r"(t));
    k2 = 0xFE;
    f &= k2;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  m = (u8*)sMotions;
  FUN_080b7f70(&p->s, &c, (motion_t*)m, 3);
  FUN_080b7f70(&p->s, &c, (motion_t*)(m + 6), 3);
  m += 12;
  FUN_080b7f70(&p->s, &c, (motion_t*)m, 3);
  co = &(p->s).coord;
  TryDropItem(4, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
}

INCASM("asm/enemy/pantheon_base_p3_post.inc");

void PantheonBase_Init(struct Enemy* p);
void PantheonBase_Update(struct Enemy* p);
void PantheonBase_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonBaseRoutine = {
    [ENTITY_INIT] =      PantheonBase_Init,
    [ENTITY_UPDATE] =    PantheonBase_Update,
    [ENTITY_DIE] =       PantheonBase_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void pBase_0808a3f8(struct Enemy* p);
void nop_0808a3f4(struct Enemy* p);

static const EnemyFunc sUpdates1[2] = {
    pBase_0808a3f8,
    nop_0808a3f4,
};

void pBase_0808a438(struct Enemy* p);
void pBase_0808a47c(struct Enemy* p);

static const EnemyFunc sUpdates2[2] = {
    pBase_0808a438,
    pBase_0808a47c,
};

// --------------------------------------------

void pBase_0808a514(struct Enemy* p);
void FUN_0808a5c8(struct Enemy* p);

static const EnemyFunc sDeads[2] = {
    pBase_0808a514,
    FUN_0808a5c8,
};

// --------------------------------------------

static const struct Collision sCollisions[25] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(19), -PIXEL(53), PIXEL(24), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(1), -PIXEL(13), PIXEL(35), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(12), PIXEL(39)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {-PIXEL(1), -PIXEL(18), PIXEL(35), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(23), PIXEL(12), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(35), -PIXEL(53), PIXEL(24), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(1), -PIXEL(13), PIXEL(35), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(12), PIXEL(39)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {-PIXEL(1), -PIXEL(18), PIXEL(35), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(23), PIXEL(12), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(43), -PIXEL(56), PIXEL(24), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(1), -PIXEL(13), PIXEL(35), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(12), PIXEL(39)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {-PIXEL(1), -PIXEL(18), PIXEL(35), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(23), PIXEL(12), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(3), -PIXEL(56), PIXEL(24), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(1), -PIXEL(13), PIXEL(35), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(12), PIXEL(39)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {-PIXEL(1), -PIXEL(18), PIXEL(35), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(23), PIXEL(12), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {-PIXEL(5), -PIXEL(56), PIXEL(24), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(1), -PIXEL(13), PIXEL(35), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(12), PIXEL(39)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {-PIXEL(1), -PIXEL(18), PIXEL(35), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(23), PIXEL(12), PIXEL(31)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(16)};
static const u8 sInitModes[1] = {1};

static const u8 sCollisionIdxs[9] = {0, 5, 10, 5, 0, 15, 20, 15, 0};

// clang-format off
static const motion_t sMotions[10] = {
    MOTION(SM109_PANTHEON_BASE, 0x03),
    MOTION(SM109_PANTHEON_BASE, 0x04),
    MOTION(SM109_PANTHEON_BASE, 0x05),
    MOTION(SM109_PANTHEON_BASE, 0x06),
    MOTION(SM109_PANTHEON_BASE, 0x07),
    MOTION(SM109_PANTHEON_BASE, 0x08),
    MOTION(SM109_PANTHEON_BASE, 0x09),
    MOTION(SM109_PANTHEON_BASE, 0x0A),
    MOTION(SM109_PANTHEON_BASE, 0x0B),
    MOTION(SM109_PANTHEON_BASE, 0x02),
};
// clang-format on
