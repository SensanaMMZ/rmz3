#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc* const sUpdates[4];

struct Projectile* FUN_080a5f00(struct Entity* e, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).unk_28 = e;
    p->work[2] = 0;
    p->work[1] = a1;
  }
  return p;
}

struct Projectile* FUN_080a5f54(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 5;
    (p->s).coord = *c;
    p->work[0] = a2;
    p->work[1] = a3;
    p->work[2] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a5fc4(struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    p->work[2] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a6014(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord = *c;
    p->work[1] = a3;
    p->work[2] = a2;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* cubit_080a6078(struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    p->work[2] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

#include "entity/macros.h"

struct Projectile* FUN_080a60c8(struct Entity* e, struct Coord* c, u8 a, u8 b) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).coord = *c;
    p->work[1] = b;
    p->work[2] = a;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* createFlameRain1(struct Entity* e, struct Coord* c, s32 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = 0;
    (p->s).coord = *c;
    p->work[1] = n;
    p->work[2] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* createFlameRain2(struct Entity* e, struct Coord* c, s32 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = 1;
    (p->s).coord = *c;
    p->work[1] = n;
    p->work[2] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

void CubitProjectile_Update(struct Projectile* p);
static const struct Collision sCollisions[16];

// 0x080a61fc -- parked (block-merge basin): retail keeps three
// byte-identical SET_PROJECTILE_ROUTINE blocks (cases 0/1/2) duplicated
// inline, while agbcc cross-jumps them into one copy under every tried
// shape (goto-chain, per-block opaque tbl, volatile-asm uniquifiers);
// the 5/6/3 InitBody tail-sharing does reproduce.
NON_MATCH void CubitProjectile_Init(struct Projectile* p) {
#if MODERN
  struct Body* bd;
  s32 z7;
  InitNonAffineMotion(&p->s);
  {
    register u32 fl asm("r0");
    register s32 c asm("r1");
    fl = (p->s).flags;
    c = 1;
    bd = NULL;
    z7 = 0;
    c |= fl;
    {
      register s32 two asm("r0");
      two = 2;
      c |= two;
    }
    (p->s).flags = c;
  }
  ResetDynamicMotion(&p->s);
  {
    u8 w = (p->s).work[0];
    register const struct Collision* col asm("r1");
    register struct Coord* cp asm("r2");
    register s32 cnt asm("r3");
    register struct Body* bda asm("r0");
    if (w != 0) goto t5;
    asm volatile("");
    {
      u32 tbl = (u32)(gProjectileFnTable);
      u32 id;
      EntityFunc** rt;
      id = ((p->s).id) << 2;
      rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)(*rt)[1];
      (p->s).mode[1] = z7;
    }
    goto zeros;
  t5:
    if (w != 5) goto t1;
    (p->s).work[0] = z7;
    (p->s).flags |= COLLIDABLE;
    bd = &p->body;
    col = &sCollisions[11];
    cp = &(p->s).coord;
    bda = bd;
    cnt = 0x40;
    goto docall;
  t1:
    if (w != 1) goto t4;
    asm volatile("" ::: "memory");
    {
      u32 tbl = (u32)(gProjectileFnTable);
      u32 id;
      EntityFunc** rt;
      id = ((p->s).id) << 2;
      rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = w;
      (p->s).onUpdate = (void*)(*rt)[1];
      (p->s).mode[1] = z7;
    }
    goto zeros;
  t4:
    if (w != 4) goto t2;
    {
      s32 o = 1;
      (p->s).work[0] = o;
      (p->s).flags |= COLLIDABLE;
      bd = &p->body;
      InitBody(bd, &sCollisions[0], &(p->s).coord, 6);
      bd->parent = (struct CollidableEntity*)p;
      bd->fn = (void*)z7;
      {
        u32 tbl = (u32)(gProjectileFnTable);
        u32 id;
        EntityFunc** rt;
        id = ((p->s).id) << 2;
        rt = (EntityFunc**)(tbl + id);
        *(u32*)((p->s).mode) = o;
        (p->s).onUpdate = (void*)(*rt)[1];
        (p->s).mode[1] = o;
      }
    }
    goto zeros;
  t2:
    if (w != 2) goto t6;
    {
      u32 tbl = (u32)(gProjectileFnTable);
      u32 id;
      EntityFunc** rt;
      id = ((p->s).id) << 2;
      rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)(*rt)[1];
      (p->s).mode[1] = z7;
    }
    goto zeros;
  t6:
    if (w != 6) goto t3;
    (p->s).work[0] = 2;
    (p->s).flags |= COLLIDABLE;
    bd = &p->body;
    col = &sCollisions[14];
    goto pre;
  t3:
    if (w != 3) goto skip;
    (p->s).flags |= COLLIDABLE;
    bd = &p->body;
    col = &sCollisions[12];
  pre:
    cp = &(p->s).coord;
    bda = bd;
    cnt = 1;
  docall:
    InitBody(bda, col, cp, cnt);
    bd->parent = (struct CollidableEntity*)p;
    bd->fn = (void*)z7;
    {
      u32 tbl = (u32)(gProjectileFnTable);
      u32 id;
      EntityFunc** rt;
      s32 o1;
      id = ((p->s).id) << 2;
      rt = (EntityFunc**)(tbl + id);
      o1 = 1;
      *(u32*)((p->s).mode) = o1;
      (p->s).onUpdate = (void*)(*rt)[1];
      (p->s).mode[1] = o1;
    }
  zeros:
    (p->s).mode[2] = z7;
    (p->s).mode[3] = z7;
  }
skip:
  (p->s).work[2] = 0xFF;
  CubitProjectile_Update(p);
#else
  INCCODE("asm/projectile/cubit_p3_init.inc");
#endif
}

void CubitProjectile_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]][(p->s).mode[1]])(p);
}

void CubitProjectile_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/cubit_pre_post_p2.inc");

static const struct Coord sCoords[30];

// Multi-basin park: retail duplicates the sCoords[10] table arms with
// reg-alternated homes and pool reloads, keeps e2 as r1+r7 copy pair, and
// shares only the _E8A store tail via a 3-address subs; the arm-merge,
// e2-home, and countdown-tail shapes could not all be held simultaneously.
NON_MATCH void FUN_080a6d3c(struct Projectile* p) {
#if MODERN
  struct Entity* e = (p->s).unk_28;
  if (e->mode[0] > 1) {
    goto die;
  }
  if (*(u32*)((u8*)e + 0xc0) != 0) {
    goto die;
  }
  if (e->mode[1] == 0xB) {
    goto die;
  }
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags &= ~DISPLAY;
      (p->s).work[2] = 9;
      (p->s).work[3] = 1;
      *((u8*)p + 0xb5) = 0xFF;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((p->s).work[3] != 0) {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((u32)(t << 24) != 0) {
          break;
        }
      }
      {
        s32 idx = 9 - (p->s).work[2];
        struct Entity* e2 = (p->s).unk_28;
        struct Coord c;
        s32 cx;
        s32 cy;
        u32 one;
        u32 xf;
        u32 f2;
        struct Entity* e2k;
        u32 tst;
        cx = e2->coord.x;
        c.x = cx;
        cy = e2->coord.y;
        c.y = cy;
        tst = (e2->flags) & X_FLIP;
        asm("" : "=r"(e2k) : "0"(e2));
        if (tst == 0) {
          const struct Coord* tba = &sCoords[10];
          u32 off = idx << 3;
          asm("" : "+r"(tba));
          c.x = *(s32*)(off + (u32)tba) + cx;
          tba = (const struct Coord*)((u8*)tba + 4);
          c.y = *(s32*)(off + (u32)tba) + cy;
          asm volatile("");
        } else {
          const struct Coord* tbb = &sCoords[10];
          u32 off = (8 - idx) << 3;
          asm("" : "+r"(tbb));
          c.x = *(s32*)(off + (u32)tbb) + cx;
          tbb = (const struct Coord*)((u8*)tbb + 4);
          c.y = *(s32*)(off + (u32)tbb) + cy;
        }
        f2 = e2k->flags;
        one = 1;
        xf = (f2 >> 4) & one;
        FUN_080a6014(&p->s, &c, xf, (u8)idx);
        (p->s).work[3] = one;
        if ((p->s).work[2] != 0) {
          s32 t2 = (p->s).work[2] - 1;
          (p->s).work[2] = t2;
          if ((u32)(t2 << 24) != 0) {
            break;
          }
        }
        (p->s).mode[2]++;
        break;
      }
    case 2:
      (p->s).work[2] = 0xC;
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      if ((p->s).work[2] != 0) {
        s32 t3 = (p->s).work[2] - 1;
        (p->s).work[2] = t3;
        if ((u32)(t3 << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    case 4:
      (p->s).work[2] = 0x20;
      (p->s).work[3] = 0x20;
      *((u8*)p + 0xb5) = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 5:
      if ((p->s).work[3] != 0) {
        s32 t4 = (p->s).work[3] - 1;
        (p->s).work[3] = t4;
        if ((u32)(t4 << 24) != 0) {
          break;
        }
      }
      (*((u8*)p + 0xb5))++;
      {
        u8 w2 = (p->s).work[2];
        u32 w2v;
        (p->s).work[3] = w2;
        asm("" : "=r"(w2v) : "0"(w2));
        if ((u32)(w2v << 24) != 0) {
          s32 t5 = w2v - 1;
          (p->s).work[2] = t5;
          asm volatile("" :: "r"(w2v));
          if ((u32)(t5 << 24) != 0) {
            break;
          }
        }
      }
      (p->s).mode[2]++;
      break;
    case 6:
      (p->s).work[2] = 0x78;
      (p->s).mode[2]++;
      // fallthrough
    case 7:
      if ((p->s).work[2] != 0) {
        s32 t6 = (p->s).work[2] - 1;
        (p->s).work[2] = t6;
        if ((u32)(t6 << 24) != 0) {
          break;
        }
      }
    die:
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
#else
  INCCODE("asm/projectile/cubit_6d3c.inc");
#endif
}

INCASM("asm/projectile/cubit_post_6ed4.inc");

void FUN_080a7a70(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}


// 0x080A7A7C
void FUN_080a7a7c(struct Projectile* p) {
  register s32 y asm("r4");
  s32 v, k, cx;

  if (((p->s).unk_28)->mode[0] > 1) {
    goto die;
  }
  if (*(s32*)((u8*)(p->s).unk_28 + 0xc0) != 0 && (p->s).mode[2] != 3) {
    (p->s).mode[2] = 3;
  }
  if (((p->s).unk_28)->mode[1] == 0xB && (p->s).mode[2] != 3) {
    (p->s).mode[2] = 3;
  }
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[1] == 0) {
        y = FUN_0800a31c((p->s).coord.x, (p->s).coord.y);
        k = *((u8*)p + 0xb5);
        if (k == 0) {
          v = 0xC00;
          goto add;
        }
        if (k == 1) {
          v = 0x4C00;
          goto add;
        }
        if (k == 2) {
          v = 0x8C00;
          goto add;
        }
        if (k != 3) {
          goto noadd;
        }
        v = 0xCC00;
        goto add;
      }
      y = FUN_0800a31c((p->s).coord.x, (p->s).coord.y);
      k = *((u8*)p + 0xb5);
      if (k == 0) {
        v = 0x2C00;
        goto add;
      }
      if (k != 1) {
        goto noadd;
      }
      v = 0xAC00;
    add:
      y += v;
    noadd:
      SetMotion(&p->s, 0xB110);
      (p->s).work[2] = 0x32;
      cx = (p->s).coord.x;
      (p->s).d.x = (y - cx) / (s32)(p->s).work[2];
      y = 0x13880;
      y -= FUN_08009f6c(cx, (p->s).coord.y) - (p->s).coord.y;
      (p->s).d.y = -(y / (s32)(p->s).work[2]);
      (p->s).work[2]--;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).d.y += 0x40;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      if ((p->s).d.y > 0) {
        if ((p->s).work[3] == 0) {
          (p->s).work[3]++;
          SetMotion(&p->s, 0xB111);
        }
        if ((p->s).work[3] == 1 && (p->s).motion.state == 3) {
          (p->s).work[3]++;
          SetDDP(&p->body, &sCollisions[13]);
          SetMotion(&p->s, 0xB112);
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      (p->s).work[2] = 0x28;
      goto bump;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
    bump:
      (p->s).mode[2]++;
      break;
    case 3:
      SetMotion(&p->s, 0xB113);
      (p->s).mode[2]++;
      /* fallthrough */
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    die:
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

void CubitProjectile_Init(struct Projectile* p);
void CubitProjectile_Update(struct Projectile* p);
void CubitProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gCubitProjectileRoutine = {
    [ENTITY_INIT] =      CubitProjectile_Init,
    [ENTITY_UPDATE] =    CubitProjectile_Update,
    [ENTITY_DIE] =       CubitProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void cubit_080a63ac(struct Projectile* p);
void FUN_080a6718(struct Projectile* p);
void FUN_080a6d3c(struct Projectile* p);
void cubit_080a6ed4(struct Projectile* p);
void cubit_080a725c(struct Projectile* p);
void FUN_080a7478(struct Projectile* p);
void FUN_080a7a70(struct Projectile* p);
void FUN_080a7a7c(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_ARRAY_0836bb74[4][2] = {
    {cubit_080a63ac, FUN_080a6718},
    {FUN_080a6d3c,   cubit_080a6ed4},
    {cubit_080a725c, FUN_080a7478},
    {FUN_080a7a70,   FUN_080a7a7c},
};
// clang-format on

static const ProjectileFunc* const sUpdates[4] = {
    PTR_ARRAY_ARRAY_0836bb74[0],
    PTR_ARRAY_ARRAY_0836bb74[1],
    PTR_ARRAY_ARRAY_0836bb74[2],
    PTR_ARRAY_ARRAY_0836bb74[3],
};

// --------------------------------------------

static const struct Collision sCollisions[16] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 1,
      range : {PIXEL(3), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(3), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(3), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(3), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 4,
      layer : 0x00000004,
      range : {PIXEL(2), -PIXEL(51), PIXEL(36), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 3,
      layer : 0x00000004,
      range : {-PIXEL(11), -PIXEL(41), PIXEL(36), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 2,
      layer : 0x00000004,
      range : {PIXEL(10), -PIXEL(27), PIXEL(36), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 1,
      layer : 0x00000004,
      range : {-PIXEL(10), -PIXEL(20), PIXEL(36), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), -PIXEL(8), PIXEL(36), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), -PIXEL(9), PIXEL(30), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), -PIXEL(5), PIXEL(12), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : 0x02,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(22)},
    },
};

// clang-format off
static const struct Coord sCoords[30] = {
    {PIXEL(0), PIXEL(0)},
    {-PIXEL(13), -PIXEL(9)},
    {PIXEL(11), -PIXEL(17)},
    {-PIXEL(12), -PIXEL(28)},
    {PIXEL(0), -PIXEL(38)},
    {PIXEL(20), PIXEL(60)},
    {PIXEL(49), PIXEL(94)},
    {PIXEL(102), PIXEL(28)},
    {PIXEL(155), PIXEL(94)},
    {PIXEL(184), PIXEL(60)},
    {-PIXEL(16), -PIXEL(10)},
    {-PIXEL(25), -PIXEL(21)},
    {-PIXEL(22), -PIXEL(34)},
    {-PIXEL(12), -PIXEL(44)},
    {PIXEL(0), -PIXEL(48)},
    {PIXEL(12), -PIXEL(44)},
    {PIXEL(22), -PIXEL(34)},
    {PIXEL(25), -PIXEL(21)},
    {PIXEL(16), -PIXEL(10)},
    {-PIXEL(26), -PIXEL(36)},
    {PIXEL(26), -PIXEL(36)},
    {-PIXEL(16), -PIXEL(10)},
    {-PIXEL(25), -PIXEL(21)},
    {-PIXEL(22), -PIXEL(34)},
    {-PIXEL(12), -PIXEL(44)},
    {PIXEL(0), -PIXEL(48)},
    {PIXEL(12), -PIXEL(44)},
    {PIXEL(22), -PIXEL(34)},
    {PIXEL(25), -PIXEL(21)},
    {PIXEL(16), -PIXEL(10)},
};
// clang-format on

static const s32 s32_ARRAY_0836be14[9] = {
    0x7B, 0x7A, 0x79, 0x3F, 0x3E, 0x3D, 0x3, 0x2, 0x1,
};
