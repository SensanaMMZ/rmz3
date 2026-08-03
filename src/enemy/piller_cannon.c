#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "story.h"
#include "zero.h"
#include "vfx.h"

static const struct Collision sCollisions[14];
static const motion_t sMotions[7];

void PillerCannon_Init(struct Enemy* p);
void PillerCannon_Update(struct Enemy* p);
void PillerCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPillerCannonRoutine = {
    [ENTITY_INIT] =      PillerCannon_Init,
    [ENTITY_UPDATE] =    PillerCannon_Update,
    [ENTITY_DIE] =       PillerCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* CreatePillerCannon(struct Coord* c, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_PILLER_CANNON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

void FUN_08068f68(struct Body* body, struct Coord* c);

// 0x0806832C
void PillerCannon_Init(struct Enemy* p) {
  register struct Body* b4 asm("r4");
  register u8 f asm("r2");
  register s32 g40 asm("r5");
  register const struct Collision* coll asm("r1");
  register struct Coord* co asm("r2");
  register s32 hp asm("r3");
  register struct Body* a0 asm("r0");
  InitNonAffineMotion(&p->s);
  {
    register s32 one asm("r0");
    register s32 z asm("r3");
    u8 fl = (p->s).flags;
    one = 1;
    z = 0;
    f = one;
    f |= fl;
    one = 2;
    f |= one;
    asm("" : "+r"(z));
    f |= z;
    (p->s).flags = f;
  }
  if ((gSystemSavedataManager.mods[13] & 0x10) == 0) {
    goto elsearm;
  }
  {
    register s32 t asm("r0");
    register u8 sv asm("r1");
    sv = gCurStory.s.gameflags[0];
    t = 0x40;
    t &= sv;
    {
      register u32 t2 asm("r0");
      t2 = (u32)t << 24;
      asm("" : "+r"(t2));
      g40 = t2 >> 24;
    }
    if (g40 != 0) {
      goto elsearm;
    }
  }
  {
    register s32 four asm("r0");
    four = 4;
    f |= four;
    (p->s).flags = f;
  }
  b4 = &p->body;
  coll = (const struct Collision*)0x0836609C;
  co = &(p->s).coord;
  asm volatile("add %0, %1, #0" : "=&l"(a0) : "l"(b4));
  hp = 0xC;
  goto docall;
elsearm : {
  register u8 fl2 asm("r1");
  register s32 g asm("r0");
  fl2 = (p->s).flags;
  g = 4;
  g40 = 0;
  asm("" : "+r"(g40));
  g |= fl2;
  (p->s).flags = g;
}
  b4 = &p->body;
  coll = (const struct Collision*)0x0836609C;
  co = &(p->s).coord;
  asm volatile("add %0, %1, #0" : "=&l"(a0) : "l"(b4));
  hp = 8;
docall:
  ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(a0, coll, co, hp);

  b4->parent = (struct CollidableEntity*)p;
  b4->fn = (BodyFunc)g40;
  asm volatile("" ::: "memory");
  b4->fn = (BodyFunc)FUN_08068f68;
  *(s32*)((u8*)p + 0xb4) = (p->s).coord.x;
  (p->s).d = (p->s).coord;
  {
    u8* a = (u8*)p + 0xb8;
    s32 zz = 0;
    *a = zz;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *(u32*)a = zz;
    asm("" : "+r"(a));
    a -= 3;
    asm("" : "+r"(a));
    *a = zz;
    asm("" : "+r"(a));
    a += 2;
    asm("" : "+r"(a));
    *a = zz;
    asm("" : "+r"(a));
    a += 5;
    asm("" : "+r"(a));
    *a = zz;
    (p->s).coord.x += 0x80 * 16;
    if ((p->s).work[0] == 0) {
      SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
      (p->s).mode[1] = 1;
    } else {
      SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
      (p->s).mode[1] = 2;
    }
    (p->s).mode[2] = zz;
    (p->s).mode[3] = zz;
  }
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(0x08, 0x00));
    UpdateMotionGraphic(&p->s);
  }
  PillerCannon_Update(p);
}


extern const EnemyFunc sUpdates1[9];
extern const EnemyFunc sUpdates2[9];
bool8 FUN_08068f08(struct Enemy* p);
void PillerCannon_Die(struct Enemy* p);

void PillerCannon_Update(struct Enemy* p) {
  struct Entity** slot;
  u8 m;
  u8* t;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    PillerCannon_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  FUN_08068f08(p);
  m = (p->s).mode[1];
  if (m == 6) goto check2;
  if (m == 8) goto check2;
  if (IsFrozen(&p->s)) {
    p->props[6] = (p->s).mode[1];
    return;
  }
check2:
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (*slot != NULL) {
    if (!isKilled(*slot)) {
      SetDDP(&p->body, &sCollisions[12]);
      return;
    }
    SetDDP(&p->body, &sCollisions[11]);
    *slot = NULL;
  }
  t = (u8*)((u8*)p + 0xc0);
  if (*t != 0) {
    *t = *t - 1;
    return;
  }
  (sUpdates2[(p->s).mode[1]])(p);
}

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x08068514
void PillerCannon_Die(struct Enemy* p) {
  struct Coord c;
  u8 m;
  if (gCurStory.s.gameflags[4] & 0x40) {
    register u8 g asm("r0");
    register u8 h asm("r1");
    register s32 z asm("r2");
    u8* a;
    h = (p->s).flags;
    asm("" : "+r"(h));
    g = 0xFE;
    g &= h;
    z = 0;
    h = 0xFD;
    g &= h;
    (p->s).flags = g;
    a = (u8*)p + 0x8c;
    *(s32*)a = z;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *(s32*)a = z;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *a = z;
    (p->s).flags &= ~4;
    SET_ENEMY_ROUTINE(p, 3);
    return;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      u8* a;
      (p->s).mode[2] = 1;
      a = (u8*)p + 0x8c;
      *(s32*)a = m;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *(s32*)a = m;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *a = m;
      (p->s).flags &= ~4;
      FALLTHROUGH;
    }
    case 1:
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y;
      (p->s).mode[2]++;
      break;
    case 2:
      c.x = (p->s).d.x;
      c.y = (p->s).d.y;
      CreateSmoke(1, &c);
      PlaySound(0x2a);
      TryDropItem(4, &(p->s).coord);
      if (gMission.enemyCount <= 0x270E) {
        gMission.enemyCount++;
      }
      TryDropZakoDisk(p, &(p->s).coord);
      (p->s).flags &= ~1;
      SET_ENEMY_ROUTINE(p, 4);
      break;
  }
}

bool8 FUN_0806860c(struct Enemy* p) { return TRUE; }


void FUN_08068610(struct Enemy* p) {}

bool8 FUN_08068614(struct Enemy* p) { return TRUE; }

// 0x08068618 -- parked (copy-coalescing basin): retail copies the 0xFE
// mask into a fresh reg before each AND (adds r0,r1; ands r0,r2); agbcc
// folds the copy and ANDs into the flags load in every form tried
// (mask-first expr, two-step temp, in-place mk chain, r3/r4 pins).
NON_MATCH void FUN_08068618(struct Enemy* p) {
#if MODERN
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register struct Entity** slot asm("r4");
      register struct Entity* v asm("r3");
      SetMotion(&p->s, MOTION(0x08, 0x00));
      *((u8*)p + 0xb9) = m;
      SetDDP(&p->body, &sCollisions[0]);
      slot = (struct Entity**)((u8*)p + 0xbc);
      v = *slot;
      if (v != NULL) {
        struct Entity* w;
        u8 mk = 0xFE;
        {
          u8 f = mk;
          f &= v->flags;
          v->flags = f;
        }
        w = *slot;
        mk &= w->flags;
        mk &= 0xFD;
        w->flags = mk;
        SET_VFX_ROUTINE(w, ENTITY_DISAPPEAR);
      }
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      u32 d;
      UpdateMotionGraphic(&p->s);
      d = (pZero2->s).coord.x + PIXEL(96) - (p->s).coord.x;
      if (d < 0xC000) {
        (p->s).mode[1] = 3, (p->s).mode[2] = 0;
      }
      break;
    }
  }
#else
  INCCODE("asm/enemy/piller_cannon_8618.inc");
#endif
}

bool8 FUN_080686b0(struct Enemy* p) { return TRUE; }

// 0x080686B4
void FUN_080686b4(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      struct VFX** vp;
      struct VFX* v;
      register u8 k1 asm("r1");
      SetMotion(&p->s, 0x800);
      {
        u8* a = (u8*)p + 0xb9;
        *a = m;
        asm("" : "+r"(a));
        a -= 0x45;
        SetDDP((struct Body*)a, sCollisions);
      }
      vp = (struct VFX**)((u8*)p + 0xbc);
      v = *vp;
      if (v != NULL) {
        register u8 t asm("r0");
        u8 fv = (v->s).flags;
        k1 = 0xFE;
        asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(k1));
        t &= fv;
        (v->s).flags = t;
        {
          struct VFX* v2 = *vp;
          u8 f2 = (v2->s).flags;
          register u8 k2 asm("r0");
          k1 &= f2;
          k2 = 0xFD;
          k1 &= k2;
          (v2->s).flags = k1;
          SET_VFX_ROUTINE(v2, ENTITY_DISAPPEAR);
        }
      }
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      {
        s32 zx = (pZero2->s).coord.x;
        s32 k38 = 0x3800;
        s32 d;
        s32 k70;
        asm("" : "+r"(k38));
        zx += k38;
        d = zx - (p->s).coord.x;
        k70 = 0x7000;
        asm("" : "+r"(k70));
        if ((u32)d < (u32)k70) {
          (p->s).mode[2]++;
        }
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      {
        s32 zx2 = (pZero2->s).coord.x;
        s32 k38b = 0x3800;
        s32 d2;
        s32 k70b;
        asm("" : "+r"(k38b));
        zx2 += k38b;
        d2 = zx2 - (p->s).coord.x;
        k70b = 0x7000;
        asm("" : "+r"(k70b));
        if ((u32)d2 >= (u32)k70b) {
          u8 z = 0;
          (p->s).mode[1] = 3;
          (p->s).mode[2] = z;
        }
      }
      break;
  }
}

bool8 FUN_08068780(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/piller_cannon_p5.inc");

bool8 FUN_08068ad8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/piller_cannon_p6.inc");

bool8 FUN_08068c84(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/piller_cannon_p7.inc");

bool8 FUN_08068e60(struct Enemy* p) { return TRUE; }

void FUN_08068e64(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[12]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[11]);
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_08068eb0(struct Enemy* p) { return TRUE; }


void FUN_08068eb4(struct Enemy* p) {}

bool8 FUN_08068eb8(struct Enemy* p) { return TRUE; }

void FUN_08068ebc(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[12]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[11]);
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

#include "element.h"
#include "vfx.h"

extern const struct Coord Coord_083661ec;

bool8 FUN_08068f08(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)&p->props[8];

  if (*slot == NULL && ((p->body).status & 1)) {
    if ((p->s).flags & X_FLIP) {
      *slot = ApplyElementEffect(0, &p->s, &Coord_083661ec);
    } else {
      *slot = ApplyElementEffect(0, &p->s, &Coord_083661ec);
    }
    if (*(struct VFX**)&p->props[8] == NULL) {
      if ((*(u8*)((u8*)p + 0x97) & 0xf0) == 0x20) {
        if (p->props[12] == 0) {
          p->props[12] = 100;
        }
      }
    }
  }
  return TRUE;
}

// 0x08068F68
void FUN_08068f68(struct Body* body, struct Coord* c) {
  const struct Collision* pr = (body->enemy)->processing;
  struct Entity* e = (struct Entity*)body->parent;
  e->d = *c;
  if ((*(u32*)&pr->atkType & 0x200FF) == 0x20002) {
    struct Entity* q = (struct Entity*)body->parent;
    if (*(u8*)((u8*)q + 0xb9) != 0) {
      SET_ENEMY_ROUTINE(q, 2);
    }
  }
}

bool8 FUN_0806860c(struct Enemy* p);
bool8 FUN_08068614(struct Enemy* p);
bool8 FUN_080686b0(struct Enemy* p);
bool8 FUN_08068780(struct Enemy* p);
bool8 FUN_08068ad8(struct Enemy* p);
bool8 FUN_08068c84(struct Enemy* p);
bool8 FUN_08068e60(struct Enemy* p);
bool8 FUN_08068eb0(struct Enemy* p);
bool8 FUN_08068eb8(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[9] = {
    (EnemyFunc)FUN_0806860c,
    (EnemyFunc)FUN_08068614,
    (EnemyFunc)FUN_080686b0,
    (EnemyFunc)FUN_08068780,
    (EnemyFunc)FUN_08068ad8,
    (EnemyFunc)FUN_08068c84,
    (EnemyFunc)FUN_08068e60,
    (EnemyFunc)FUN_08068eb0,
    (EnemyFunc)FUN_08068eb8,
};
// clang-format on

void FUN_08068610(struct Enemy* p);
void FUN_08068618(struct Enemy* p);
void FUN_080686b4(struct Enemy* p);
void FUN_08068784(struct Enemy* p);
void FUN_08068adc(struct Enemy* p);
void FUN_08068c88(struct Enemy* p);
void FUN_08068e64(struct Enemy* p);
void FUN_08068eb4(struct Enemy* p);
void FUN_08068ebc(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[9] = {
    FUN_08068610,
    FUN_08068618,
    FUN_080686b4,
    FUN_08068784,
    FUN_08068adc,
    FUN_08068c88,
    FUN_08068e64,
    FUN_08068eb4,
    FUN_08068ebc,
};
// clang-format on

static const struct Collision sCollisions[14] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : 0x01,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0000, 0x1C00, 0x1C00},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1A00, 0x1A00},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : 0x01,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0000, 0x1C00, 0x1C00},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x1300, 0x0000, 0x1200, 0x1400},
    },
    [4] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : 0x01,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {-0x1300, 0x0000, 0x1200, 0x1400},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0F00, 0x0000, 0x2100, 0x1400},
    },
    [6] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : 0x01,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {-0x0F00, 0x0000, 0x2100, 0x1400},
    },
    [7] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0700, 0x0000, 0x2400, 0x1400},
    },
    [8] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : 0x01,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {-0x0700, 0x0000, 0x2400, 0x1400},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x2000, 0x1400},
    },
    [10] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : 0x01,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0000, 0x2000, 0x1400},
    },
    [11] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0C00, 0x0000, 0x1D00, 0x2000},
    },
    [12] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : 0x01,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {-0x0C00, 0x0000, 0x1D00, 0x2000},
    },
    [13] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      remaining : 0,
      range : {-0x1400, 0x0000, 0x0D00, 0x1000},
    },
};

const struct Coord Coord_083661ec = {0xFFFFF500, 0x0};

// clang-format off
static const motion_t sMotions[7] = {
    MOTION(SM008_PILLAR_CANNON, 0x01),
    MOTION(SM008_PILLAR_CANNON, 0x02),
    MOTION(SM008_PILLAR_CANNON, 0x03),
    MOTION(SM008_PILLAR_CANNON, 0x04),
    MOTION(SM008_PILLAR_CANNON, 0x03),
    MOTION(SM008_PILLAR_CANNON, 0x02),
    MOTION(SM008_PILLAR_CANNON, 0x01),
};
// clang-format on

static const s32 s32_ARRAY_08366204[7] = {
    3, 5, 7, 9, 7, 5, 3,
};
