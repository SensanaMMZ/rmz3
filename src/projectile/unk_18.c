#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "vfx.h"
#include "physics.h"

static const ProjectileFunc PTR_ARRAY_0836b434[5];
static const ProjectileFunc PTR_ARRAY_0836b448[5];
static const struct Collision sCollisions[4];
static const u8 sInitModes[4];

void Projectile18_Update(struct Projectile* p);

#include "entity/macros.h"

void FUN_080a2ea0(void) {
  s32 i;

  for (i = 0; i < 5; i++) {
    struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

    if (p != NULL) {
      (p->s).taskCol = 8;
      INIT_PROJECTILE_ROUTINE(p, 18);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).work[0] = 2;
    }
  }
}

void FUN_080a2ee8(s32 x, s32 y) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 18);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

void FUN_080a2f34(s32 x, s32 y) {
  s32 i;

  for (i = 0; i <= 1; i++) {
    struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

    if (p != NULL) {
      (p->s).taskCol = 8;
      INIT_PROJECTILE_ROUTINE(p, 18);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).work[0] = 0;
      (p->s).coord.x = x - 0x1C00 + i * 0x3800;
      (p->s).coord.y = y + 0x800;
      (p->s).work[2] = i;
    }
  }
}

void FUN_080a2fa4(struct Enemy* p) {}

void Projectile18_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)FUN_080a2fa4);
  Projectile18_Update(p);
}

void Projectile18_Update(struct Projectile* p) {
  (PTR_ARRAY_0836b434[(p->s).mode[1]])(p);
  (PTR_ARRAY_0836b448[(p->s).mode[1]])(p);
}

void Projectile18_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(3, &(p->s).coord);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080a308c(struct Projectile* p) {}

void FUN_080a3090(struct Projectile* p) {}

// 0x080A3094
void FUN_080a3094(struct Projectile* p) {
  register u32* st asm("r5");
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 w2 asm("r2");
      SetDDP(&p->body, &sCollisions[1]);
      w2 = (p->s).work[2];
      if (w2 != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        register s32 xv asm("r1");
        register u8* oa asm("r3");
        s32 sh4, ov, m11;
        xv = 1;
        xv &= w2;
        *((u8*)p + 0x4c) = xv;
        oa = (u8*)p + 0x4a;
        sh4 = xv << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      {
        s32 k = -0x200;
        (p->s).d.x = ((p->s).work[2] << 10) + k;
        (p->s).d.y = k;
      }
      SetMotion(&p->s, 0x4604);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 dx asm("r2");
      s32 push;
      {
        s32 cx = (p->s).coord.x;
        dx = (p->s).d.x;
        (p->s).coord.x = cx + dx;
      }
      {
        s32 dy = (p->s).d.y + 0x20;
        (p->s).d.y = dy;
        if (dy > 0x700) {
          (p->s).d.y = 0x700;
        }
      }
      (p->s).coord.y += (p->s).d.y;
      if (dx < 0) {
        push = PushoutToRight1((p->s).coord.x - 0x800, (p->s).coord.y);
        if (push <= 0) {
          goto upd;
        }
      } else {
        push = PushoutToLeft1((p->s).coord.x + 0x800, (p->s).coord.y);
        if (push >= 0) {
          goto upd;
        }
      }
      (p->s).coord.x += push;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
  st = (u32*)((u8*)p + 0x8c);
  if (*st & 4) {
    register u8 g asm("r0");
    register u8 h asm("r1");
    register s32 zr asm("r2");
    u8* a;
    FUN_080a2ea0();
    FUN_080a2ee8((p->s).coord.x, (p->s).coord.y);
    h = (p->s).flags;
    asm("" : "+r"(h));
    g = 0xFE;
    g &= h;
    zr = 0;
    h = 0xFD;
    g &= h;
    (p->s).flags = g;
    *st = zr;
    a = (u8*)p + 0x90;
    *(s32*)a = zr;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *a = zr;
    (p->s).flags &= ~4;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

// 0x080A31C0
void FUN_080a31c0(struct Projectile* p) {
  register u32* ps asm("r5");
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 cx asm("r3");
      register s32 v asm("r0");
      register s32 v2 asm("r2");
      SetDDP(&p->body, (const struct Collision*)0x0836B48C);
      cx = (p->s).coord.x;
      v = cx - 0x800;
      (p->s).coord.x = v;
      asm volatile("add %0, %1, #0" : "=&l"(v2) : "l"(v));
      if ((p->s).flags & 0x10) {
        v2 = cx + 0x800;
      }
      (p->s).coord.x = v2;
      (p->s).coord.y += 0x800;
      SetMotion(&p->s, MOTION(0x46, 0x05));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 ny = (p->s).coord.y + 0x80;
      s32 r;
      (p->s).coord.y = ny;
      r = PushoutToUp1((p->s).coord.x, ny);
      if (r < 0) {
        (p->s).coord.y += r;
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
  ps = (u32*)((u8*)p + 0x8c);
  if (*ps & 4) {
    s32 z2b;
    FUN_080a2ea0();
    FUN_080a2ee8((p->s).coord.x, (p->s).coord.y);
    {
      u32 fl = (p->s).flags & 0xFE;
      z2b = 0;
      fl &= 0xFD;
      (p->s).flags = fl;
    }
    *ps = z2b;
    {
      u8* w = (u8*)p + 0x90;
      *(u32*)w = z2b;
      asm("" : "+r"(w));
      w += 4;
      asm("" : "+r"(w));
      *(u8*)w = z2b;
    }
    (p->s).flags &= 0xFB;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

void FUN_080a3298(struct Projectile* p) {
  u32* ps;
  switch ((p->s).mode[2]) {
    default:
      ps = (u32*)((u8*)p + 0x8c);
      goto tail;
    case 0:
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, 0x4606);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      {
        u32 st = (p->s).motion.state;
        ps = (u32*)((u8*)p + 0x8c);
        if (st == 3) {
          (p->s).mode[2]++;
        }
      }
      goto tail;
    case 2:
      SetDDP(&p->body, sCollisions);
      (p->s).work[2] = 0xFF;
      (p->s).work[3] = 0;
      InitScalerotMotion1(&p->s);
      GotoMotion(&p->s, 0x4606, 3, 1);
      (p->s).d.x = 0x20;
      {
        s32 v = 0x20;
        asm("" : "+r"(v));
        if ((p->s).flags & 0x10) {
          v -= 0x40;
        }
        (p->s).d.x = v;
      }
      (p->s).mode[2]++;
      // fallthrough
    case 3: {
      s32 z2;
      {
        s32 t = (p->s).work[3] + 1;
        (p->s).work[3] = t;
        if (t & 2) {
          (p->s).flags |= 1;
        } else {
          (p->s).flags &= 0xFE;
        }
      }
      (p->s).coord.x += (p->s).d.x;
      {
        s32 t2 = (p->s).work[2] - 4;
        z2 = 0;
        (p->s).work[2] = t2;
      }
      ((p->s).spr).mag.x = (p->s).work[2];
      ((p->s).spr).mag.y = (p->s).work[2];
      {
        u32 w2 = (p->s).work[2];
        ps = (u32*)((u8*)p + 0x8c);
        if (w2 <= 7) {
          {
            u32 fl = (p->s).flags & 0xFE;
            fl &= 0xFD;
            (p->s).flags = fl;
          }
          *ps = z2;
          *(u32*)((u8*)p + 0x90) = z2;
          {
            u8* a94 = (u8*)p + 0x94;
            s32 z0 = 0;
            *a94 = z0;
          }
          (p->s).flags &= 0xFB;
          {
            u32 tbl = (u32)gProjectileFnTable;
            u32 id = ((p->s).id) << 2;
            EntityFunc** rt = (EntityFunc**)(tbl + id);
            *(u32*)((p->s).mode) = 3;
            (p->s).onUpdate = (void*)((*rt)[3]);
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      goto tail;
    }
  }
tail:
  if (*ps & 4) {
    s32 z2b;
    FUN_080a2ea0();
    FUN_080a2ee8((p->s).coord.x, (p->s).coord.y);
    {
      u32 fl = (p->s).flags & 0xFE;
      z2b = 0;
      fl &= 0xFD;
      (p->s).flags = fl;
    }
    *ps = z2b;
    {
      u8* w = (u8*)p + 0x90;
      *(u32*)w = z2b;
      asm("" : "+r"(w));
      w += 4;
      asm("" : "+r"(w));
      *(u8*)w = z2b;
    }
    (p->s).flags &= 0xFB;
    {
      u32 tbl = (u32)gProjectileFnTable;
      u32 id = ((p->s).id) << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = 3;
      (p->s).onUpdate = (void*)((*rt)[3]);
    }
  }
}

#include "motion.h"
#include "zero.h"

void FUN_080a3418(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x46, 0x07));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x = (pZero2->s).coord.x;
      (p->s).coord.y = (pZero2->s).coord.y - 0x1000;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

INCASM("asm/projectile/unk_18_p2_p2_p2_p3_b.inc");

static const struct Collision sCollisions[4];
static const u8 sInitModes[4];

void Projectile18_Init(struct Projectile* p);
void Projectile18_Update(struct Projectile* p);
void Projectile18_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile18Routine = {
    [ENTITY_INIT] =      Projectile18_Init,
    [ENTITY_UPDATE] =    Projectile18_Update,
    [ENTITY_DIE] =       Projectile18_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080a3090(struct Projectile* p);
void FUN_080a308c(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836b434[5] = {
    FUN_080a3090,
    FUN_080a3090,
    FUN_080a3090,
    FUN_080a308c,
    FUN_080a308c,
};
// clang-format on

void FUN_080a3094(struct Projectile* p);
void FUN_080a31c0(struct Projectile* p);
void FUN_080a3298(struct Projectile* p);
void FUN_080a3418(struct Projectile* p);
void FUN_080a34a0(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836b448[5] = {
    FUN_080a3094,
    FUN_080a31c0,
    FUN_080a3298,
    FUN_080a3418,
    FUN_080a34a0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[4] = {
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
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(5), -PIXEL(8), PIXEL(8), PIXEL(21)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(6), -PIXEL(3), PIXEL(8), PIXEL(9)},
    },
};

static const u8 sInitModes[4] = {0, 3, 4, 0};
