#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc sUpdates[2];

static const ProjectileFunc sInitializers[2];

static const struct Collision sCollisions[4];

void createCopyXSonicBoom(struct Entity* e, u8 w0, u8 w1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 24);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = w0;
    (p->s).work[1] = w1;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void CopyXProjectile_Init(struct Projectile* p) {
  (sInitializers[(p->s).work[0]])(p);
}

void CopyXProjectile_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]])(p);
}

void CopyXProjectile_Die(struct Projectile* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// 0x080a81d0
void initCopyXSlidingSonicBoom(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 one;
  {
    u32 tbl, id;
    EntityFunc** routine_table;
    tbl = (u32)gProjectileFnTable;
    id = ((p->s).id) << 2;
    routine_table = (EntityFunc**)(tbl + id);
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*routine_table)[ENTITY_UPDATE];
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register s32 z asm("r6");
    u8 t = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    asm("" : "+r"(z));
    asm volatile("" ::"r"(z));
    fv |= t;
    fv |= FLIPABLE;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0x5E, 0x00));
  UpdateMotionGraphic(&p->s);
  SET_XFLIP(&p->s, (q->flags >> 4) & one);
  INIT_BODY(p, &sCollisions[0], 0x40, NULL);
  (p->s).work[2] = 0x28;
  (p->s).mode[2] = 1;
  CopyXProjectile_Update(p);
}

// 0x080a8280
void moveSlidingSonicBoom(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x = ((p->s).flags & X_FLIP) ? ((q->coord).x + PIXEL(28)) : ((q->coord).x - PIXEL(28));
  if ((u8)--(p->s).work[2] == 0xff || q->mode[1] <= 5 || q->mode[1] > 8) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void CopyXProjectile_Update(struct Projectile* p);

// 0x080a82dc
void FUN_080a82dc(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 one;
  {
    u32 tbl, id;
    EntityFunc** routine_table;
    tbl = (u32)gProjectileFnTable;
    id = ((p->s).id) << 2;
    routine_table = (EntityFunc**)(tbl + id);
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*routine_table)[ENTITY_UPDATE];
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register s32 z asm("r6");
    u8 t = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    asm("" : "+r"(z));
    asm volatile("" ::"r"(z));
    fv |= t;
    fv |= FLIPABLE;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0x5E, 0x01));
  UpdateMotionGraphic(&p->s);
  SET_XFLIP(&p->s, (q->flags >> 4) & one);
  INIT_BODY(p, &sCollisions[2], 0x40, NULL);
  (p->s).work[2] = 0x28;
  (p->s).mode[2] = 1;
  CopyXProjectile_Update(p);
}

void moveNovaStrikeSonicBoom(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x = ((p->s).flags & X_FLIP) ? ((q->coord).x + PIXEL(24)) : ((q->coord).x - PIXEL(24));
  (p->s).coord.y = (q->coord).y - PIXEL(26);
  if (q->mode[1] != 15) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void CopyXProjectile_Init(struct Projectile* p);
void CopyXProjectile_Update(struct Projectile* p);
void CopyXProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gCopyXProjectileRoutine = {
    [ENTITY_INIT] =      CopyXProjectile_Init,
    [ENTITY_UPDATE] =    CopyXProjectile_Update,
    [ENTITY_DIE] =       CopyXProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void initCopyXSlidingSonicBoom(struct Projectile* p);
void FUN_080a82dc(struct Projectile* p);

static const ProjectileFunc sInitializers[] = {
    initCopyXSlidingSonicBoom,
    FUN_080a82dc,
};

// --------------------------------------------

void moveSlidingSonicBoom(struct Projectile* p);
void moveNovaStrikeSonicBoom(struct Projectile* p);

static const ProjectileFunc sUpdates[] = {
    moveSlidingSonicBoom,
    moveNovaStrikeSonicBoom,
};

// --------------------------------------------

static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x04,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(8), PIXEL(24), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x04,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(12), PIXEL(0), PIXEL(24), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};
