#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "projectile.h"
#include "stagerun.h"

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

static const struct Collision sCollisions[];

// 0x080A9EF8
void FUN_080a9ef8(struct Projectile* p) {
  register s32 ms asm("r1");
  register s32 m asm("r6");
  {
    register s32 t0 asm("r0");
    register u16 raw asm("r1");
    raw = gStageRun.missionStatus;
    t0 = 8;
    t0 &= raw;
    asm("" : "+r"(t0));
    t0 <<= 16;
    ms = (u32)t0 >> 16;
  }
  if (ms != 0) {
    SET_PROJECTILE_ROUTINE(p, 2);
    Projectile28_Die((Object*)p);
    return;
  }
  m = (p->s).mode[1];
  switch (m) {
    case 0: {
      s32 t = (p->s).work[3] + 4;
      (p->s).work[3] = t;
      if ((u8)t <= 0x1F) {
        break;
      }
      (p->s).mode[1]++;
      (p->s).work[2] = 0x78;
      (p->s).flags |= 4;
      {
        struct Body* body = &p->body;
        InitBody(body, &sCollisions[2], &(p->s).coord, 1);
        body->parent = (struct CollidableEntity*)p;
        body->fn = (void*)m;
      }
      break;
    }
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t != 0xFF) {
        break;
      }
      (p->s).mode[1]++;
      {
        u8* a = (u8*)p + 0x8c;
        *(u32*)a = ms;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = ms;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = ms;
      }
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFB;
        g &= h;
        (p->s).flags = g;
      }
      break;
    }
    case 2: {
      s32 t = (p->s).work[3] - 4;
      (p->s).work[3] = t;
      if ((t << 24) != 0) {
        break;
      }
      {
        u32 tbl = (u32)gProjectileFnTable;
        EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
        *(u32*)((p->s).mode) = m;
        (p->s).onUpdate = (void*)((*rt)[2]);
      }
      Projectile28_Die((Object*)p);
      break;
    }
  }
  (p->s).mode[3]++;
}

// 0x080a9fe4
void FUN_080a9fe4(struct Sprite* s, struct DrawPivot* dp) {
  register struct Coord* lt asm("r3");
  register struct Entity* q asm("r2");
  register s32 x asm("r5");
  register s32 y asm("r4");
  register u32 lo asm("r6");
  lt = &dp->lefttop;
  q = (struct Entity*)s->sprites;
  if (q->mode[0] <= 1) {
    register u16* pal asm("r1");
    register s32 c asm("r3");
    u8 w;
    u32 d;
    s32 sd;
    {
      register s32 a asm("r0");
      register s32 b asm("r1");
      a = (q->coord).x;
      b = (dp->lefttop).x;
      a = a - b;
      x = a >> 8;
    }
    {
      register s32 a asm("r0");
      register s32 b asm("r1");
      a = (q->coord).y;
      b = lt->y;
      a = a - b;
      y = (a >> 8) + 2;
    }
    if ((q->mode[3] & 3) > 1) {
      pal = (u16*)&gPaletteManager;
      c = 0x7FFF;
    } else {
      pal = (u16*)&gPaletteManager;
      c = 0x7C00;
    }
    {
      register s32 cv asm("r0");
      asm volatile("add %0, %1, #0" : "=&l"(cv) : "l"(c));
      *pal = cv;
    }
    w = q->work[3];
    d = (u32)(x - w) << 16;
    x = (u32)((w + x) << 16) >> 16;
    lo = d >> 16;
    sd = (s32)d >> 16;
    if (sd < 0) {
      lo = 0;
    } else if (sd > 0xF0) {
      lo = 0xF0;
    }
    {
      s32 sh = (s32)(x << 16) >> 16;
      if (sh < 0) {
        x = 0;
      } else if (sh > 0xF0) {
        x = 0xF0;
      }
    }
    if (y < 0) {
      y = 0;
    } else if (y > 0xA0) {
      y = 0xA0;
    }
    {
      register struct WramWindowRegister* wb asm("r2");
      register s32 m3 asm("r3");
      register s32 hv asm("r1");
      register s32 mask asm("r0");
      register s32 lv asm("r0");
      wb = &gWindowRegBuffer;
      m3 = 0xFF;
      hv = (s32)(x << 16) >> 16;
      mask = 0xFF;
      hv &= mask;
      lv = (s32)(lo << 16) >> 8;
      hv |= lv;
      wb->winH.half[1] = hv;
      y &= m3;
      wb->winV.half[1] = y;
    }
  }
}

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

// 0x080AA15C
void FUN_080aa15c(struct Sprite* spr, struct DrawPivot* dp) {
  register struct Coord* lt asm("r3");
  struct Entity* e;
  register s32 cx asm("r4");
  register s32 ay asm("r6");
  register u16 x1 asm("r5");
  register u16 x2 asm("r2");
  register u16 y1 asm("r6");
  register u16 y2 asm("r4");
  register s32 t asm("r0");
  lt = &dp->lefttop;
  e = (struct Entity*)spr->sprites;
  if (e->mode[0] > 1) {
    return;
  }
  t = e->coord.x;
  t -= dp->lefttop.x;
  asm("" : "+r"(t));
  cx = t >> 8;
  t = *(s32*)((u8*)e + 0xb8);
  t -= lt->y;
  asm("" : "+r"(t));
  t >>= 8;
  asm("" : "+r"(t));
  ay = t;
  ay -= 0x20;
  if (((e->work[3]) & 3) > 1) {
    PALETTE16(0) = 0x7FFF;
  } else {
    PALETTE16(0) = 0x3FF;
  }
  t = *(s32*)((u8*)e + 0xb4);
  t -= lt->x;
  t <<= 8;
  x1 = ((u32)t) >> 16;
  t = cx << 16;
  asm("" : "+r"(t));
  x2 = ((u32)t) >> 16;
  {
    s32 a = x1 << 16;
    s32 b = x2 << 16;
    if (a > b) {
      x1 = ((u32)b) >> 16;
      x2 = ((u32)a) >> 16;
    }
  }
  {
    s32 v = (s16)x1;
    if (v < 0) {
      x1 = 0;
    } else if (v > 0xf0) {
      x1 = 0xf0;
    }
  }
  {
    s32 v = (s16)x2;
    if (v < 0) {
      x2 = 0;
    } else if (v > 0xf0) {
      x2 = 0xf0;
    }
  }
  {
    register s32 c1 asm("r1");
    register s32 c2 asm("r0");
    c1 = ay - 8;
    asm("" : "+r"(c1));
    c1 <<= 16;
    c2 = ay + 8;
    asm("" : "+r"(c2));
    c2 <<= 16;
    y2 = ((u32)c2) >> 16;
    y1 = ((u32)c1) >> 16;
    c1 >>= 16;
    if (c1 < 0) {
      y1 = 0;
    } else if (c1 > 0xa0) {
      y1 = 0xa0;
    }
  }
  {
    s32 v = (s16)y2;
    if (v < 0) {
      y2 = 0;
    } else if (v > 0xa0) {
      y2 = 0xa0;
    }
  }
  {
    register struct WramWindowRegister* w asm("r3");
    register s32 msk asm("r2");
    w = &gWindowRegBuffer;
    {
      register s32 h asm("r1");
      register s32 sh asm("r0");
      h = (s16)x2;
      msk = 0xff;
      h &= msk;
      sh = (s16)x1 << 8;
      h |= sh;
      w->winH.half[1] = h;
    }
    {
      register s32 h2 asm("r0");
      register s32 sh2 asm("r1");
      h2 = (s16)y2;
      h2 &= msk;
      sh2 = (s16)y1 << 8;
      h2 |= sh2;
      w->winV.half[1] = h2;
    }
  }
}

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
