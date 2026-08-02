#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "projectile.h"

// コピーXのチャージショットに関係?

static void Projectile28_Init(struct Entity* p);
static void Projectile28_Update(struct Entity* p);
static void Projectile28_Die(Object* p);

// clang-format off
const ProjectileRoutine gProjectile28Routine = {
    [ENTITY_INIT] =      (ProjectileFunc)Projectile28_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Projectile28_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Projectile28_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080a9aa0(struct Entity* e, u8 kind1, u8 kind2) {
  struct Entity* p = AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    p->taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 28);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = kind1, p->work[1] = kind2;
    p->unk_28 = (void*)e;
    p->coord = e->coord;
  }
}

// --------------------------------------------

void FUN_080a9b90(struct Projectile* p);
void FUN_080a9d88(struct Projectile* p);
void FUN_080a9e74(struct Projectile* p);
void FUN_080aa08c(struct Projectile* p);

static void Projectile28_Init(struct Entity* p) {
  static const ProjectileFunc PTR_ARRAY_0836c20c[4] = {
      (ProjectileFunc)FUN_080a9b90,
      (ProjectileFunc)FUN_080a9d88,
      (ProjectileFunc)FUN_080a9e74,
      (ProjectileFunc)FUN_080aa08c,
  };  // 0x0836c20c
  (PTR_ARRAY_0836c20c[p->work[0]])((void*)p);
}

void FUN_080a9c88(struct Projectile* p);
void FUN_080a9dcc(struct Projectile* p);
void FUN_080a9ef8(struct Projectile* p);
void FUN_080aa120(struct Projectile* p);

static void Projectile28_Update(struct Entity* p) {
  static const ProjectileFunc PTR_ARRAY_0836c21c[4] = {
      (ProjectileFunc)FUN_080a9c88,
      (ProjectileFunc)FUN_080a9dcc,
      (ProjectileFunc)FUN_080a9ef8,
      (ProjectileFunc)FUN_080aa120,
  };
  (PTR_ARRAY_0836c21c[p->work[0]])((void*)p);
}

static void Projectile28_Die(Object* p) {
  if ((p->s).work[0] > 1) {
    gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
    gWindowRegBuffer.winin[2] |= 0xFE;
    PALETTE16(0) = RGB_BLACK;
  }
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

INCASM("asm/projectile/unk_28_p1.inc");

void FUN_080a90a0(struct Entity* e, u8 a1, u8 a2);

// 0x080a9c88
void FUN_080a9c88(struct Projectile* p) {
  register s32* bx asm("r5");
  register u8 t asm("r1");
  UpdateMotionGraphic(&p->s);
  if ((p->s).flags & X_FLIP) {
    u8 a;
    const s16* tbl;
    bx = (s32*)((u8*)p + 0xb4);
    tbl = gSineTable;
    a = (p->s).work[2];
    (p->s).coord.x = *bx + tbl[(u8)(a + 0x40)] * 11;
    (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + tbl[*(vu8*)&(p->s).work[2]] * 22;
    (p->s).work[2] = a + 0x10;
    (p->s).d.x += 8;
    if ((p->s).d.x > 0x200) {
      (p->s).d.x = 0x200;
    }
  } else {
    u8 a;
    const s16* tbl;
    bx = (s32*)((u8*)p + 0xb4);
    tbl = gSineTable;
    a = (p->s).work[2];
    (p->s).coord.x = *bx + tbl[(u8)(a + 0x40)] * 11;
    (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + tbl[*(vu8*)&(p->s).work[2]] * 22;
    (p->s).work[2] = a - 0x10;
    (p->s).d.x -= 8;
    if ((p->s).d.x < -0x200) {
      (p->s).d.x = -0x200;
    }
  }
  t = (p->s).work[3];
  (p->s).work[3] = t + 1;
  if ((t & 3) == 0) {
    FUN_080a90a0(&p->s, 6, 0);
  }
  *bx += (p->s).d.x;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void FUN_080a9d88(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x5f, 1));
  (p->s).mode[2] = 1;
  Projectile28_Update(&p->s);
}

// 0x080A9DCC
void FUN_080a9dcc(struct Projectile* p) {
  struct Entity* o = *(struct Entity**)((u8*)p + 0x28);
  (p->s).coord = o->coord;
  SET_XFLIP(p, (o->flags >> 4) & 1);
  if (*((u8*)o + 0xc6) != 0) {
    if ((p->s).mode[2] != 0) {
      SetMotion(&p->s, MOTION(0x5f, 1));
    }
    (p->s).flags |= 1;
    (p->s).mode[2] = 0;
  } else {
    (p->s).flags &= ~1;
    (p->s).mode[2] = 1;
  }
  UpdateMotionGraphic(&p->s);
  if (o->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void FUN_080a9fe4(struct Sprite* t, struct DrawPivot* c);

void FUN_080a9e74(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  SetTaskCallback((void*)&(p->s).spr, FUN_080a9fe4);
  ((p->s).spr).sprites = (void*)p;
  (p->s).flags &= ~OAM_PRIO;
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  (p->s).coord = q->coord;
  gWindowRegBuffer.dispcnt |= DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[1] = WININ_WIN0_CLR | WININ_WIN0_OBJ | WININ_WIN0_BG0;
  gWindowRegBuffer.winin[2] |= WINOUT_WIN01_BG3 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG1;
  (*(u16*)(&gPaletteManager.buf[0])) = RGB_WHITE;
  (p->s).work[2] = (p->s).work[3] = 0;
  Projectile28_Update(&p->s);
}

INCASM("asm/projectile/unk_28_p2_p1b.inc");

void FUN_080aa15c(struct Sprite* spr, struct DrawPivot* dp);

// 0x080aa08c
void FUN_080aa08c(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  SetTaskCallback((struct RenderNode*)&(p->s).spr, FUN_080aa15c);
  (p->s).spr.sprites = (struct MetaspriteHeader*)p;
  {
    u8 f = (p->s).flags & ~8;
    f |= DISPLAY;
    f |= FLIPABLE;
    (p->s).flags = f;
  }
  {
    s32 x = (q->coord).x;
    s32 y = (q->coord).y;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
  {
    register u16 d asm("r2") = gWindowRegBuffer.dispcnt;
    register u16 r asm("r0");
    register u16 k asm("r3");
    register s32 v asm("r3");
    k = 0x4000;
    r = k;
    v = 0;
    r |= d;
    gWindowRegBuffer.dispcnt = r;
    gWindowRegBuffer.winin[1] = 0x31;
    gWindowRegBuffer.winin[2] |= 0xE;
    PALETTE16(0) = 0x7FFF;
    *(s32*)((u8*)p + 0xb4) = *(vs32*)&(p->s).coord.x;
    *(s32*)((u8*)p + 0xb8) = *(vs32*)&(p->s).coord.y;
    (p->s).work[3] = v;
    (p->s).work[2] = v;
  }
  Projectile28_Update(&p->s);
}

void FUN_080aa120(struct Projectile* p) {
  struct Entity* par = (p->s).unk_28;
  (p->s).coord = par->coord;
  (p->s).work[3]++;
  if (par->mode[1] != 0xf) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Projectile28_Die((Object*)p);
  }
}

INCASM("asm/projectile/unk_28_p2_p2.inc");

// --------------------------------------------

// 0x0836c22c
static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
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
      hitzone : 1,
      hardness : METAL,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(127), PIXEL(64), -PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(127), PIXEL(64), -PIXEL(1)},
    },
};
