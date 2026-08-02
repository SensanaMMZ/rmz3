#include "zero.h"
#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "mod.h"
#include "physics.h"
#include "story.h"

static const struct Collision sCollisions[];
static const u8 sInitModes[4];
static const struct Rect sSize;

bool8 FUN_0808c3ec(struct Enemy* p);
bool8 FUN_0808c450(struct Enemy* p);
void FUN_0808c4e8(struct Enemy* p);
static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];

void GeneratorCannon_Init(struct Enemy* p);
void GeneratorCannon_Update(struct Enemy* p);
void GeneratorCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gGeneratorCannonRoutine = {
    [ENTITY_INIT] =      GeneratorCannon_Init,
    [ENTITY_UPDATE] =    GeneratorCannon_Update,
    [ENTITY_DIE] =       GeneratorCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// 0x0808c388
static void CreateGeneratorCannon(s32 x, s32 y, u8 n) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_GENERATOR_CANNON);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = 1, p->work[2] = n;
    (p->coord).x = x, (p->coord).y = y;
  }
}

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) { return; }

bool8 FUN_0808c3ec(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->s).work[0] != 0) {
      if ((p->body).status & 0x10000) {
        (p->s).mode[1] = 2;
      } else if ((p->body).status & 0x20000) {
        (p->s).mode[1] = 3;
      } else {
        (p->s).mode[1] = 1;
      }
    } else {
      (p->s).mode[1] = 0;
    }
    GeneratorCannon_Die(p);
    return TRUE;
  }
  return FALSE;
}

// 0x0808c450
bool8 FUN_0808c450(struct Enemy* p) {
  s32 v;
  if ((p->s).mode[1] == 7) {
    return FALSE;
  }
  v = *(s32*)((u8*)p + 0xb4);
  if (v != 0) {
    return FALSE;
  }
  switch ((p->s).mode[3]) {
    case 0:
      if (!IsFrozen(&p->s)) {
        return FALSE;
      }
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
      (p->s).mode[3]++;
      UpdateMotionGraphic(&p->s);
      return TRUE;
    case 1: {
      s32 f = IsFrozen(&p->s);
      if (f == 0) {
        goto clear;
      }
      if ((p->s).work[0] != 1) {
        return TRUE;
      }
      if (((p->body).status & 0x20001) != 0x20001) {
        return TRUE;
      }
      (p->s).mode[3] = v;
      return FALSE;
    clear:
      (p->s).mode[3] = f;
      return FALSE;
    }
  }
  return FALSE;
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_0808c4e8(struct Enemy* p) {
  struct VFX** slot;
  u32 frozen;

  if ((p->s).work[0] == 1) {
    slot = (struct VFX**)&p->props[0];
    if (*slot == NULL && ((p->body).status & 1)) {
      frozen = (p->body).status & 0x20000;
      if (frozen != 0) {
        (p->s).mode[1] = 7;
        (p->s).mode[2] = 0;
      } else {
        *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
        if (*slot != NULL) {
          (p->s).mode[1] = 0;
          (p->s).mode[2] = 0;
        }
      }
    }
  }
}

void GeneratorCannon_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  *(struct VFX**)&p->props[0] = NULL;
  if ((p->s).work[0] == 0) {
    (p->s).flags2 |= ENTITY_HAZARD;
    (p->s).size = (struct Rect*)&sSize;
    (p->s).hazardAttr = 0x801;
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    if (MOD_ENABLED(gSystemSavedataManager.mods, MOD_102) && !FLAG(gCurStory.s.gameflags, DEMO_PLAY)) {
      struct Body* body;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 0x18);
      body->parent = (void*)p;
      body->fn = NULL;
    } else {
      struct Body* body;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 0x14);
      body->parent = (void*)p;
      body->fn = NULL;
    }
  } else {
    struct Body* body;
    p->props[4] = 0;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 5);
    body->parent = (void*)p;
    body->fn = NULL;
  }
  {
    struct Body* body = &p->body;
    body->fn = onCollision;
  }
  GeneratorCannon_Update(p);
}

void GeneratorCannon_Update(struct Enemy* p) {
  u8 sf = (u8)(gCurStory.s.gameflags[4] & 2);
  if (sf) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if ((p->s).work[0] == 1 && (gCurStory.s.gameflags[4] & 0x40)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    (p->body).status = sf;
    do {
      (p->body).prevStatus = sf;
    } while (0);
    (p->body).invincibleTime = sf;
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (FUN_0808c3ec(p)) {
    return;
  }
  FUN_0808c4e8(p);
  if (FUN_0808c450(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

static const EnemyFunc sDeads[4];

void GeneratorCannon_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_0808c760(struct Enemy* p) {}


void FUN_0808c764(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}


void FUN_0808c784(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 6;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

// 0x0808c7e0
void generatorcannon_0808c7e0(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(0x72, 0x00));
      UpdateMotionGraphic(&p->s);
      (p->s).d.y = m;
      (p->s).work[2] = m;
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 r;
      if (IsFrozen(&p->s)) {
        break;
      }
      if ((p->s).work[2] == 0) {
        (p->s).d.y += 0x40;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
      }
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (r < 0) {
        (p->s).work[2] = 1;
        if (r > -PIXEL(8)) {
          (p->s).coord.y += r;
        }
      }
      break;
    }
  }
}

struct Projectile* CreateLemon(struct Coord* c, s32 r1, u8 r2);

// 0x0808c868
void generatorcannon_0808c868(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[13]);
      (p->s).work[2] = 0x30;
      SetMotion(&p->s, MOTION(0x71, 0x06));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      u8 w = (p->s).work[2];
      s32 t = w;
      asm("" : "+r"(t));
      if (t == 0) {
        struct Camera* cam = &gStageRun.vm.camera;
        if (CalcFromCamera(cam, &(p->s).coord) <= 0xFFF) {
          (p->s).mode[1] = 2;
          (p->s).mode[2] = t;
        }
      } else {
        (p->s).work[2] = w - 1;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

static const u8 sCollisionIdxs1[4];

// 0x0808c8d4
void generatorcannon_0808c8d4(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).work[2] = 0x30;
      (p->s).work[3] = m;
      SetMotion(&p->s, MOTION(0x71, 0x00));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      u8 t;
      if ((u8)((p->s).work[2] % 12) == 0 && (p->s).work[3] <= 2) {
        CreateGeneratorCannon((p->s).coord.x, (p->s).coord.y - 0x1000, (p->s).work[3]);
        (p->s).work[3]++;
      }
      t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = t;
      }
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[sCollisionIdxs1[(s8)(p->s).motion.cmdIdx]]);
      break;
    }
  }
}

INCASM("asm/enemy/generator_cannon_post_p2_p2.inc");

// 0x0808ca28
void generatorcannon_0808ca28(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 3;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      struct Coord c;
      PlaySound(0x2c);
      c.x = (p->s).coord.x - 0x2500;
      c.y = (p->s).coord.y - 0xE00;
      CreateLemon(&c, 0x300, 0);
      c.x = (p->s).coord.x + 0x2500;
      c.y = (p->s).coord.y - 0xE00;
      CreateLemon(&c, 0x300, 0x80);
      SetMotion(&p->s, MOTION(0x71, 0x02));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u8 t = --(p->s).work[2];
        if (t == 0) {
          (p->s).mode[1] = 1;
          (p->s).mode[2] = t;
        } else {
          (p->s).mode[2] = 1;
        }
      }
      break;
  }
}

void generatorcannon_0808cad8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).taskCol = 0x19;
      (p->s).work[3] = ((2 - (p->s).work[2]) << 3) + 0x10;
      SetMotion(&p->s, 0x7200);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 xf = 0;
      s32 v;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        xf = 1;
      }
      if (xf != 0) {
        register u8 lf asm("r1");
        register s32 vv asm("r0");
        lf = (p->s).flags;
        vv = 0x10;
        vv |= lf;
        v = vv;
      } else {
        register u8 lf2 asm("r1");
        register s32 vv2 asm("r0");
        lf2 = (p->s).flags;
        vv2 = 0xEF;
        vv2 &= lf2;
        v = vv2;
      }
      (p->s).flags = v;
      {
        register s32 x1 asm("r1");
        u8* a;
        u8 b;
        s32 msk;
        s32 sh;
        x1 = xf;
        asm("" : "+r"(x1));
        ((p->s).spr).xflip = x1;
        a = (u8*)p + 0x4a;
        sh = x1 << 4;
        b = *a;
        msk = -0x11;
        msk &= b;
        msk |= sh;
        *a = msk;
      }
      (p->s).coord.y += -0x300;
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) == 0) {
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 2:
      (p->s).work[3] = (p->s).work[2] * 12 + 0x18;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      s32 xf;
      s32 v;
      {
        register s32 t asm("r0");
        register u8 t8 asm("r1");
        u32 sh24;
        t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        sh24 = t << 24;
        asm("" : "+r"(sh24));
        t8 = sh24 >> 24;
        if (t8 == 0) {
          (p->s).mode[1] = 6;
          (p->s).mode[2] = t8;
        }
      }
      xf = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        xf = 1;
      }
      if (xf != 0) {
        register s32 vf asm("r0");
        register u32 c10 asm("r1");
        vf = (p->s).flags;
        c10 = 0x10;
        vf |= c10;
        v = vf;
      } else {
        register u8 lf2 asm("r1");
        register s32 vv2 asm("r0");
        lf2 = (p->s).flags;
        vv2 = 0xEF;
        vv2 &= lf2;
        v = vv2;
      }
      (p->s).flags = v;
      {
        register s32 x1 asm("r1");
        u8* a;
        u8 b;
        s32 msk;
        s32 sh;
        x1 = xf;
        asm("" : "+r"(x1));
        ((p->s).spr).xflip = x1;
        a = (u8*)p + 0x4a;
        sh = x1 << 4;
        b = *a;
        msk = -0x11;
        msk &= b;
        msk |= sh;
        *a = msk;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/enemy/generator_cannon_post_p2_p2_b.inc");

static const motion_t sMotions[7];
struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
struct Entity* CreateSmoke(u8 kind, struct Coord* c);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x0808CE4C
void FUN_0808ce4c(struct Enemy* p) {
  struct Coord c;
  struct Coord* co;
  register u8* q asm("r0");
  u8 fl;
  u32 z;
  (p->s).flags2 &= 0xF7;
  z = 0;
  q = (u8*)p + 0x8c;
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *q = z;
  fl = (p->s).flags & 0xFB;
  fl &= 0xFE;
  (p->s).flags = fl;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[0], 3);
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[0], 3);
  co = &(p->s).coord;
  TryDropItem(3, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
}


struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
static const motion_t sMotions[7];

// 0x0808cefc
void FUN_0808cefc(struct Enemy* p) {
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
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[3], 3);
  TryDropItem(0, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/generator_cannon_post_p2_p2c.inc");

void FUN_0808c760(struct Enemy* p);
void FUN_0808c764(struct Enemy* p);
void FUN_0808c784(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    FUN_0808c784,
    FUN_0808c760,
    FUN_0808c760,
    FUN_0808c760,
    FUN_0808c760,
    FUN_0808c764,
    FUN_0808c764,
    FUN_0808c760,
};
// clang-format on

void generatorcannon_0808c7e0(struct Enemy* p);
void generatorcannon_0808c868(struct Enemy* p);
void generatorcannon_0808c8d4(struct Enemy* p);
void generatorcannon_0808c970(struct Enemy* p);
void generatorcannon_0808ca28(struct Enemy* p);
void generatorcannon_0808cad8(struct Enemy* p);
void generatorcannon_0808cc08(struct Enemy* p);
void generatorcannon_0808cd60(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    generatorcannon_0808c7e0,
    generatorcannon_0808c868,
    generatorcannon_0808c8d4,
    generatorcannon_0808c970,
    generatorcannon_0808ca28,
    generatorcannon_0808cad8,
    generatorcannon_0808cc08,
    generatorcannon_0808cd60,
};
// clang-format on

// --------------------------------------------

void FUN_0808ce4c(struct Enemy* p);
void FUN_0808cefc(struct Enemy* p);
void FUN_0808cf94(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_0808ce4c,
    FUN_0808cefc,
    FUN_0808cf94,
    generatorcannon_0808cd60,
};

// --------------------------------------------

static const struct Collision sCollisions[18] = {
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
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(16), -PIXEL(37), PIXEL(17), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(16), -PIXEL(37), PIXEL(17), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(66), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(66), PIXEL(34)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(19), -PIXEL(35), PIXEL(13), PIXEL(11)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(19), -PIXEL(35), PIXEL(13), PIXEL(11)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(66), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(66), PIXEL(34)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(66), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(66), PIXEL(34)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(36), PIXEL(51), PIXEL(11)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(40), PIXEL(23), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(66), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(66), PIXEL(34)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(21), PIXEL(12)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};

static const u8 sInitModes[4] = {1, 5, 0, 0};

static const struct Rect sSize = {PIXEL(0), -PIXEL(13), PIXEL(60), PIXEL(36)};

static const u8 sCollisionIdxs1[4] = {3, 7, 11, 11};
static const u8 sCollisionIdxs2[4] = {11, 7, 3, 0};

// clang-format off
static const motion_t sMotions[7] = {
    MOTION(SM113_GENERATOR_CANNON, 3),
    MOTION(SM113_GENERATOR_CANNON, 4),
    MOTION(SM113_GENERATOR_CANNON, 5),
    MOTION(SM113_GENERATOR_CANNON, 3),
    MOTION(SM113_GENERATOR_CANNON, 4),
    MOTION(SM113_GENERATOR_CANNON, 5),
    MOTION(SM114_KEATON, 3),
};
// clang-format on
