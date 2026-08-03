#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "zero.h"
#include "global.h"
#include "motion.h"
#include "projectile.h"
#include "sound.h"
#include "mission.h"
#include "story.h"
#include "vfx.h"

static const struct Collision sCollisions[3];

void EyeCannon_Init(struct Enemy* p);
s32 FUN_0800a134(s32 x, s32 y);
void EyeCannon_Update(struct Enemy* p);
void EyeCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gEyeCannonRoutine = {
    [ENTITY_INIT] =      EyeCannon_Init,
    [ENTITY_UPDATE] =    EyeCannon_Update,
    [ENTITY_DIE] =       EyeCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  // NOP
  return;
}

static bool8 FUN_08084708(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    EyeCannon_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const EnemyFunc sDeads[1];
static const EnemyFunc sUpdates1[6];
static const EnemyFunc sUpdates2[6];

void FUN_080847b8(struct Enemy* p);

bool8 FUN_08084744(struct Enemy* p) {
  if (*(struct VFX**)((u8*)p + 0xb4) == NULL) {
    switch ((p->s).mode[3]) {
      case 0: {
        if (IsFrozen((void*)p)) {
          (sUpdates1[(p->s).mode[1]])(p);
          (sUpdates2[(p->s).mode[1]])(p);
          (p->s).mode[3]++;
          UpdateMotionGraphic(&p->s);
          return TRUE;
        }
        break;
      }
      case 1: {
        if (IsFrozen((void*)p)) {
          return TRUE;
        }
        (p->s).mode[3] = 0;
        break;
      }
    }
  }
  return FALSE;
}

extern const struct Coord sElementCoord;

void FUN_080847b8(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xb4);
  if (*slot == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *slot = e;
    if (e != NULL) {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
  }
}

s32 FUN_0800a134(s32 x, s32 y);
void EyeCannon_Update(struct Enemy* p);

// 0x080847F0
void EyeCannon_Init(struct Enemy* p) {
  register s32 one asm("r3");
  register s32 z asm("r4");
  register u32 tbl asm("r5");
  tbl = (u32)gEnemyFnTable;
  {
    EntityFunc** rt = (EntityFunc**)((((p->s).id) << 2) + tbl);
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  z = 0;
  (p->s).mode[1] = one;
  if ((p->s).work[0] != 0) {
    register u8* gf asm("r1");
    register u32 v asm("r2");
    register s32 t asm("r0");
    {
      register const u8* tb asm("r2");
      register u32 idx asm("r0");
      gf = (u8*)&gCurStory;
      tb = (const u8*)0x08368358;
      asm volatile("" : "+r"(gf));
      asm volatile("" : "+r"(tb));
      idx = (p->s).work[0];
      idx -= 1;
      idx <<= 2;
      {
        register const u32* ta asm("r0");
        asm volatile("add %0, %1, %2" : "=l"(ta) : "l"(idx), "l"(tb));
        v = *ta;
      }
    }
    t = v >> 3;
    gf += 4;
    {
      register u8* ea asm("r0");
      asm volatile("add %0, %1, %2" : "=l"(ea) : "l"(t), "l"(gf));
      t = *ea;
    }
    {
      register u32 sev asm("r1");
      sev = 7;
      v &= sev;
    }
    t >>= v;
    t &= one;
    if (t != 0) {
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFE;
        g &= h;
        h = 0xFD;
        g &= h;
        (p->s).flags = g;
      }
      {
        u8* a = (u8*)p + 0x8c;
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z;
      }
      (p->s).flags &= 0xFB;
      {
        EntityFunc** rt2 = (EntityFunc**)((((p->s).id) << 2) + tbl);
        *(u32*)((p->s).mode) = 3;
        (p->s).onUpdate = (void*)((*rt2)[3]);
      }
      return;
    }
  }
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    register s32 z5 asm("r5");
    struct Body* body;
    fl = (p->s).flags;
    fv = FLIPABLE;
    z5 = 0;
    fv |= fl;
    fl = DISPLAY;
    fv |= fl;
    (p->s).flags = fv;
    InitNonAffineMotion(&p->s);
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x08368310, &(p->s).coord, 7);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)0x08084705;
    *(u32*)((u8*)p + 0xb4) = z5;
    (p->s).coord.y = FUN_0800a134((p->s).coord.x, (p->s).coord.y);
    EyeCannon_Update(p);
  }
}

void EyeCannon_Update(struct Enemy* p) {
  if (!FUN_08084708(p)) {
    FUN_080847b8(p);
    if (!FUN_08084744(p)) {
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
}

void EyeCannon_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_08084930(struct Enemy* p) {}


void FUN_08084934(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_08084974(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x66, 0));
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}


// 0x080849B0
void FUN_080849b0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, 0x6601);
      (p->s).work[2] = 0x80;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      u8 xf = (p->s).flags & 0x10;
      if (xf == 0) {
        if ((u32)((pZero2->s).coord.x - (p->s).coord.x + 0x7800) <= 0x67FF &&
            (u32)((pZero2->s).coord.y - (p->s).coord.y) <= 0x6FFF) {
          (p->s).mode[1] = 5;
          (p->s).mode[2] = xf;
        }
      } else {
        if ((u32)((pZero2->s).coord.x - (p->s).coord.x - 0x1000) <= 0x67FF &&
            (u32)((pZero2->s).coord.y - (p->s).coord.y) <= 0x6FFF) {
          u8 z = 0;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = z;
        }
      }
      {
        s32 raw = (p->s).work[2] - 1;
        u8 t;
        (p->s).work[2] = raw;
        t = raw;
        if (t == 0) {
          (p->s).mode[1] = 2;
          (p->s).mode[2] = t;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x08084a80
void FUN_08084a80(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x66, 0x02));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      register u8 fl asm("r2");
      register s32 sh asm("r0");
      register s32 v asm("r1");
      register u8 fv asm("r0");
      u8* oa;
      s32 sh4, ov, m11;
      fl = (p->s).flags;
      sh = fl >> 4;
      v = 1;
      v &= ~sh;
      if (v != 0) {
        fv = 0x10;
        fv |= fl;
        (p->s).flags = fv;
      } else {
        fv = 0xEF;
        fv &= fl;
        (p->s).flags = fv;
      }
      (p->s).spr.xflip = v;
      oa = (u8*)p + 0x4a;
      sh4 = v << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      m11 |= sh4;
      *oa = m11;
      SetMotion(&p->s, MOTION(0x66, 0x00));
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      u8 t;
      UpdateMotionGraphic(&p->s);
      t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = t;
      }
      break;
    }
  }
}

static const u8 u8_ARRAY_08368370[4];

void FUN_08084b2c(struct Enemy* p) {
  struct Coord c;
  s32 x, x2;
  u8 f;
  s32 i;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (--(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      c.x = (p->s).coord.x - PIXEL(4);
      x = c.x;
      if ((p->s).flags & 0x10) {
        x = (p->s).coord.x + PIXEL(4);
      }
      c.x = x;
      c.y = (p->s).coord.y + 0x1500;
      CreateLemon(&c, 0x300, u8_ARRAY_08368370[((p->s).flags >> 4) & 1]);
      c.x = (p->s).coord.x - PIXEL(1);
      x2 = c.x;
      f = (p->s).flags & 0x10;
      if (f) {
        x2 = (p->s).coord.x;
      }
      c.x = x2;
      c.y = (p->s).coord.y + 0x1B00;
      i = 2;
      if (f) {
        i = 3;
      }
      CreateLemon(&c, 0x300, u8_ARRAY_08368370[i]);
      PlaySound(0x2C);
      SetMotion(&p->s, MOTION(0x66, 4));
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

#include "zero.h"

// 0x08084C30
void FUN_08084c30(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x60;
      (p->s).mode[2]++;
    case 1: {
      u8 z;
      s32 d = (p->s).work[2] - 1;
      struct Zero* zp;
      register s32 dx asm("r0");
      z = 0;
      (p->s).work[2] = d;
      if ((u8)d == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = z;
      }
      {
        register s32 k asm("r1");
        if (((p->s).flags & 0x10) == 0) {
          register s32 zx asm("r0");
          zp = pZero2;
          zx = (zp->s).coord.x;
          dx = zx - (p->s).coord.x;
          k = 0x7800;
        } else {
          register s32 zx asm("r0");
          zp = pZero2;
          zx = (zp->s).coord.x;
          dx = zx - (p->s).coord.x;
          k = -0x1000;
        }
        dx += k;
      }
      if ((u32)dx > 0x6800 || (u32)((zp->s).coord.y - (p->s).coord.y) > 0x7000) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_08084cbc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x8f << 1);
      SetMotion(&p->s, MOTION(0x66, 3));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = (p->s).motion.state;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

extern void FUN_080b7f70(struct Enemy* p, struct Coord* c, motion_t* m, s32 n);
extern void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
static const u32 u32_ARRAY_08368358[4];
static const motion_t sMotions[3];

void _killEyeCannon(struct Enemy* p) {
  struct Coord c;
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y + 0x1200;
  FUN_080b7f70(p, &c, (motion_t*)sMotions, 3);
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  TryDropItem(3, &(p->s).coord);
  if (gMission.enemyCount <= 0x270e) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
  if ((p->s).work[0] != 0) {
    SET_FLAG(gCurStory.s.gameflags, u32_ARRAY_08368358[(p->s).work[0] - 1]);
  }
}

void FUN_08084934(struct Enemy* p);
void FUN_08084930(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    FUN_08084934,
    FUN_08084930,
    FUN_08084930,
    FUN_08084930,
    FUN_08084930,
    FUN_08084930,
};
// clang-format on

void FUN_08084974(struct Enemy* p);
void FUN_080849b0(struct Enemy* p);
void FUN_08084a80(struct Enemy* p);
void FUN_08084b2c(struct Enemy* p);
void FUN_08084c30(struct Enemy* p);
void FUN_08084cbc(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    FUN_08084974,
    FUN_080849b0,
    FUN_08084a80,
    FUN_08084b2c,
    FUN_08084c30,
    FUN_08084cbc,
};
// clang-format on

void _killEyeCannon(struct Enemy* p);

static const EnemyFunc sDeads[1] = {
    _killEyeCannon,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
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
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(18), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(18), PIXEL(20), PIXEL(20)},
    },
};

static const u32 u32_ARRAY_08368358[4] = {
    45,
    46,
    47,
    48,
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(18)};

static const u8 u8_ARRAY_08368370[4] = {
    249,
    135,
    224,
    160,
};

static const motion_t sMotions[3] = {
    MOTION(102, 5),
    MOTION(102, 6),
    MOTION(102, 7),
};
