#include "collision.h"
#include "global.h"
#include "trig.h"
#include "projectile.h"

static const ProjectileFunc* const PTR_ARRAY_0836b4e4[4];

struct Projectile* createTretistaBreathGas(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 19);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* tretista_080a369c(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 19);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* tretista_080a36f4(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 19);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a374c(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 19);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

void TretistaProjectile_Update(struct Projectile* p);

// 0x080A37A4
void TretistaProjectile_Init(struct Projectile* p) {
  register s32 z5 asm("r5");
  register struct Body* body asm("r4");
  register const struct Collision* coll asm("r1");
  register s32 hp asm("r3");
  register struct Coord* co asm("r2");
  register struct Body* b0 asm("r0");
  z5 = (p->s).work[0];
  if (z5 == 0) {
    InitNonAffineMotion(&p->s);
    {
      register u8* a asm("r0");
      register s32 k asm("r1");
      a = (u8*)p + 0x24;
      *a = z5;
      asm("" : "+r"(a));
      a += 0x2c;
      asm("" : "+r"(a));
      k = 0x100;
      *(u16*)a = k;
      asm("" : "+r"(a));
      a += 2;
      asm("" : "+r"(a));
      *(u16*)a = k;
    }
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    coll = (const struct Collision*)0x0836B4F4;
    goto setup1;
  }
  if (z5 == 1) {
    {
      register u8* tc asm("r1");
      register s32 v19 asm("r0");
      tc = (u8*)p + 0x25;
      z5 = 0;
      v19 = 0x19;
      *tc = v19;
    }
    InitNonAffineMotion(&p->s);
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    coll = (const struct Collision*)0x0836B50C;
    co = &(p->s).coord;
    b0 = body;
    hp = 0x20;
    goto docall;
  }
  if (z5 == 2) {
    InitNonAffineMotion(&p->s);
    (p->s).unk_2c = NULL;
    goto after;
  }
  if (z5 != 3) {
    goto after;
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    asm("" : "+r"(fl));
    fv = 4;
    z5 = 0;
    fv |= fl;
    (p->s).flags = fv;
  }
  body = &p->body;
  coll = (const struct Collision*)0x0836B9A4;
setup1:
  co = &(p->s).coord;
  b0 = body;
  hp = 1;
docall:
  ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(b0, coll, co, hp);
  body->parent = (struct CollidableEntity*)p;
  body->fn = (BodyFunc)z5;
after : {
  register s32 z4 asm("r4");
  {
    register u8 fv2 asm("r0");
    register u8 fl2 asm("r1");
    fl2 = (p->s).flags;
    asm("" : "+r"(fl2));
    fv2 = 1;
    z4 = 0;
    fv2 |= fl2;
    fl2 = 2;
    fv2 |= fl2;
    (p->s).flags = fv2;
  }
  ResetDynamicMotion(&p->s);
  *(s32*)((u8*)p + 0xc0) = z4;
  (p->s).work[2] = 0xFF;
  {
    u32 tbl = (u32)gProjectileFnTable;
    EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
    *(u32*)((p->s).mode) = 1;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  (p->s).mode[1] = z4;
  (p->s).mode[2] = z4;
  (p->s).mode[3] = z4;
}
  TretistaProjectile_Update(p);
}

void TretistaProjectile_Update(struct Projectile* p) {
  (PTR_ARRAY_0836b4e4[(p->s).work[0]][(p->s).mode[1]])(p);
}

void TretistaProjectile_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/tretista_post_p2_p1.inc");

void FUN_080a4ef8(struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 20);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).unk_28 = e;
  }
}

void FUN_080bf438(s32 x, s32 y, u8 r2);

void FUN_080a4f3c(struct Projectile* p) {
  s32 i;
  for (i = 0; i < 4; i++) {
    register s32 x asm("r4");
    s32 y;
    x = ((p->s).coord).x - PIXEL(16);
    x += (RANDOM(RNG_0202f388) & 0x1FFF);
    y = FUN_08009f6c(x, ((p->s).coord).y);
    if (((y - ((p->s).coord).y) >= -PIXEL(24)) && ((y - ((p->s).coord).y) < PIXEL(24))) {
      FUN_080bf438(x, y, 1);
    }
  }
}

// 0x080a4fa4
void FUN_080a4fa4(struct Projectile* p) {
  register struct Projectile* pp asm("r3") = p;
  register struct Entity* q asm("r5") = (pp->s).unk_28;
  register s32 cx asm("r6");
  register u32 a asm("r4");
  register const s16* tbl asm("r2");
  const s16* tbl2;
  s32 t1;
  register s32 cy asm("r1");
  register u32 h asm("r2");
  a = *(u16*)((u8*)p + 0xb4);
  if ((q->flags & X_FLIP) != 0) {
    register s32 n asm("r0");
    n = -(s32)a;
    a = (u16)n;
  }
  cx = (q->coord).x;
  (pp->s).coord.x = cx;
  tbl = gSineTable;
  t1 = (tbl[a >> 8] * 3) << 11;
  t1 = -t1;
  asm("" : "+r"(t1));
  tbl2 = tbl;
  h = a >> 8;
  (pp->s).coord.x = cx + t1 / 0x100;
  asm volatile("" ::"r"(cx));
  if ((s16)(a - 0x4000) >= 0) {
    (pp->s).taskCol = 0x17;
  } else {
    (pp->s).taskCol = 0x19;
  }
  asm volatile("" ::"r"(a));
  cy = (q->coord).y;
  (pp->s).coord.y = cy;
  cy = cy + (tbl2[(u8)(*(s32*)((u8*)pp + 0xb8) >> 8)] << 2);
  (pp->s).coord.y = cy;
  (pp->s).coord.y = cy + (-(tbl2[(u8)(h + 0x40)] << 10)) / 0x100;
  asm volatile("" ::"r"(h), "r"(cy));
}



void TretistaProjectile_Init(struct Projectile* p);
void TretistaProjectile_Update(struct Projectile* p);
void TretistaProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gTretistaProjectileRoutine = {
    [ENTITY_INIT] =      TretistaProjectile_Init,
    [ENTITY_UPDATE] =    TretistaProjectile_Update,
    [ENTITY_DIE] =       TretistaProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a38e8(struct Projectile* p);
void FUN_080a3c58(struct Projectile* p);
void FUN_080a44c0(struct Projectile* p);
void FUN_080a4d0c(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836b4d4[4] = {
    FUN_080a38e8,
    FUN_080a3c58,
    FUN_080a44c0,
    FUN_080a4d0c,
};

static const ProjectileFunc* const PTR_ARRAY_0836b4e4[4] = {
    &PTR_ARRAY_0836b4d4[0],
    &PTR_ARRAY_0836b4d4[1],
    &PTR_ARRAY_0836b4d4[2],
    &PTR_ARRAY_0836b4d4[3],
};

static const struct Collision sCollisions[53] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(22), PIXEL(22)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {PIXEL(8), -PIXEL(11), PIXEL(50), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {PIXEL(8), -PIXEL(11), PIXEL(50), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(11), PIXEL(6), PIXEL(11), PIXEL(47)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(11), PIXEL(6), PIXEL(11), PIXEL(47)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {PIXEL(8), PIXEL(0), PIXEL(18), PIXEL(58)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {PIXEL(8), PIXEL(0), PIXEL(18), PIXEL(58)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(7), PIXEL(1), PIXEL(12), PIXEL(35)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(7), PIXEL(1), PIXEL(12), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {-PIXEL(11), -PIXEL(9), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {-PIXEL(11), -PIXEL(9), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(9), PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(9), PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {PIXEL(0), PIXEL(9), PIXEL(28), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {PIXEL(0), PIXEL(9), PIXEL(28), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(0), -PIXEL(9), PIXEL(60), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(9), PIXEL(60), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {PIXEL(12), -PIXEL(9), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {PIXEL(12), -PIXEL(9), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(9), PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(9), PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {-PIXEL(8), PIXEL(0), PIXEL(18), PIXEL(58)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {-PIXEL(8), PIXEL(0), PIXEL(18), PIXEL(58)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(7), PIXEL(1), PIXEL(12), PIXEL(35)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(7), PIXEL(1), PIXEL(12), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {-PIXEL(9), -PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {-PIXEL(9), -PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(12), PIXEL(8), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(12), PIXEL(8), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 3,
      layer : 1,
      range : {PIXEL(0), -PIXEL(9), PIXEL(28), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 2,
      range : {PIXEL(0), -PIXEL(9), PIXEL(28), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(0), PIXEL(9), PIXEL(60), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), PIXEL(9), PIXEL(60), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(0), -PIXEL(9), PIXEL(28), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(9), PIXEL(60), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(9), -PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {PIXEL(12), PIXEL(8), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(8), PIXEL(0), PIXEL(18), PIXEL(58)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {PIXEL(7), PIXEL(1), PIXEL(12), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(12), -PIXEL(9), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(9), PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(0), PIXEL(9), PIXEL(28), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), -PIXEL(9), PIXEL(60), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(11), -PIXEL(9), PIXEL(13), PIXEL(49)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {PIXEL(9), PIXEL(12), PIXEL(48), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(8), PIXEL(0), PIXEL(18), PIXEL(58)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(7), PIXEL(1), PIXEL(12), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 1,
      range : {PIXEL(8), -PIXEL(11), PIXEL(50), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(11), PIXEL(6), PIXEL(11), PIXEL(47)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {PIXEL(29), -PIXEL(38), PIXEL(22), PIXEL(54)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      comboLv : 0,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(47), -PIXEL(34), PIXEL(90), PIXEL(26)},
    },
};

// clang-format off
static const struct Coord sCoords[10] = {
    {PIXEL(28), PIXEL(24)},
    {-PIXEL(28), -PIXEL(24)},
    {PIXEL(14), PIXEL(10)},
    {-PIXEL(14), -PIXEL(10)},
    {PIXEL(28), -PIXEL(24)},
    {-PIXEL(28), PIXEL(24)},
    {-PIXEL(14), PIXEL(10)},
    {PIXEL(14), -PIXEL(10)},
    {PIXEL(0), PIXEL(0)},
    {PIXEL(0), PIXEL(0)},
};
// clang-format on
