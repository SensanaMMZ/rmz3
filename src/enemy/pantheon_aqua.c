#include "collision.h"
#include "enemy.h"
#include "camera.h"
#include "global.h"
#include "overworld.h"
#include "stagerun.h"
#include "zero.h"
#include "overworld_terrain.h"

static const struct Collision sCollisions[];

struct Enemy* CreatePantheonAqua(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

void PantheonAqua_Update(struct Enemy* p);
void FUN_0807336c(struct Body* body, struct Coord* c);

void PantheonAqua_Init(struct Enemy* p) {
  u8 g40;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((gSystemSavedataManager.mods[10] & 1) && (g40 = gCurStory.s.gameflags[0] & 0x40) == 0) {
    INIT_BODY(p, sCollisions, 0x10, NULL);
  } else {
    INIT_BODY(p, sCollisions, 0xC, NULL);
  }
  if (gOverworld.sea > (p->s).coord.y) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  {
    u8 w0 = (p->s).work[0];
    if (w0 == 0) {
      (p->s).flags &= ~X_FLIP;
      (p->s).spr.xflip = w0;
      (p->s).spr.oam.xflip = w0;
    } else {
      SET_XFLIP(p, 1);
    }
  }
  SET_BODY_INTERSECT_HANDLER(p, FUN_0807336c);
  (p->s).d.y = 0;
  (p->s).d.x = 0;
  {
    u32* q = (u32*)&(p->s).unk_coord;
    *(u32*)((u8*)q + 4) = 0;
    (p->s).unk_coord.x = 0;
    {
      u8* qq = (u8*)q + 0x58;
      *(u32*)qq = 0;
      qq -= 3;
      *qq = 0;
      qq += 1;
      *qq = 0;
      qq -= 2;
      *qq = 0;
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  *(u32*)((u8*)p + 0xb4) = (p->s).coord.x;
  *(u32*)((u8*)p + 0xc0) = (p->s).coord.y;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, 0x2700);
    UpdateMotionGraphic(&p->s);
  }
  *((u8*)p + 0xbb) = 0;
  PantheonAqua_Update(p);
}

extern const EnemyFunc PTR_ARRAY_08366bd0[8];
extern const EnemyFunc PTR_ARRAY_08366bf0[8];
s32 FUN_08073368(struct Enemy* p);
void FUN_080731c4(struct Enemy* p);
void PantheonAqua_Die(struct Enemy* p);

void PantheonAqua_Update(struct Enemy* p) {
  u8 m;
  s32 sea;
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    if (FUN_08073368(p)) {
      goto alive;
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  PantheonAqua_Die(p);
  return;

alive:
  {
    s32* ppx = (s32*)((u8*)p + 0xb4);
    s32 cx = (p->s).coord.x;
    s32 d = cx - *ppx;
    if (d > 0) {
      if (d > 0x9400) {
        goto setmode;
      }
    } else {
      if (*ppx - cx > 0x9400) {
        goto setmode;
      }
    }
    goto dispatch;
  setmode:
    if ((p->s).mode[1] != 3) {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = 0;
    }
  }
dispatch:
  (PTR_ARRAY_08366bd0[(p->s).mode[1]])(p);
  FUN_080731c4(p);
  m = (p->s).mode[1];
  if (m == 4) goto water;
  if (m == 6) goto water;
  if (IsFrozen(&p->s)) {
    return;
  }
water:
  sea = gOverworld.sea;
  if (sea > (p->s).coord.y - 0x1E00) {
    u8 f = p->props[4];
    if (f == 0) {
      SetMotion(&p->s, 0x2700);
      UpdateMotionGraphic(&p->s);
      (p->s).d.y = f;
    }
    p->props[4] = 1;
    (p->s).d.y += 0x20;
    if ((p->s).d.y > 0x700) {
      (p->s).d.y = 0x700;
    }
    (p->s).coord.y += (p->s).d.y;
    return;
  } else {
    if (p->props[4] == 1) {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
    p->props[4] = 0;
    (PTR_ARRAY_08366bf0[(p->s).mode[1]])(p);
  }
}

INCASM("asm/enemy/pantheon_aqua_p1_p2_b.inc");

bool8 nop_080726a8(struct Enemy* p) { return TRUE; }

void FUN_08073610(struct Enemy* p);
void FUN_080733b4(struct Enemy* p, s32 r1);
s32 FUN_080735ac(struct Enemy* p);
u8 FUN_08073500(struct Enemy* p);

void FUN_080726ac(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      SetMotion(&p->s, 0x2700);
      (p->s).work[3] = 0;
      SetDDP(&p->body, sCollisions);
      (p->s).mode[2]++;
      // fallthrough
    case 2: {
      s32 dx = (p->s).d.x;
      s32 nd = -dx;
      s32 k11 = 0xB;
      s32 dy, nd2;
      nd = nd * k11;
      dx += nd >> 8;
      (p->s).d.x = dx;
      dy = (p->s).d.y;
      nd2 = -dy;
      nd2 = nd2 * k11;
      dy += nd2 >> 8;
      (p->s).d.y = dy;
      (p->s).coord.x += dx;
      (p->s).coord.y += dy;
      FUN_08073610(p);
      if ((p->s).coord.x > (pZero2->s).coord.x) {
        s32 z = 0;
        (p->s).flags &= 0xEF;
        (p->s).spr.xflip = z;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
      } else {
        s32 o = 1;
        (p->s).flags |= 0x10;
        (p->s).spr.xflip = o;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 c16 = 0x10;
          s32 ov, m11;
          asm("" : "+r"(c16));
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          *oa = m11 | c16;
        }
      }
      {
        s32 t = (p->s).work[3];
        s32 n = t + 1;
        u32 t2;
        (p->s).work[3] = n;
        t2 = (u32)t << 24;
        asm("" : "+r"(t2));
        t2 >>= 24;
        if ((s32)((t2 % 0x1C) << 24) == 0) {
          FUN_080733b4(p, 0);
        }
      }
      UpdateMotionGraphic(&p->s);
      {
        s32 r;
        u8* cb = (u8*)p + 0xba;
        if (*cb == 0) {
          r = FUN_080735ac(p);
        } else {
          *cb = *cb - 1;
          r = 0;
        }
        if (r == 2) {
          (p->s).mode[1] = r;
          (p->s).mode[2] = 0;
        } else if (r == 1) {
          u8 v = FUN_08073500(p);
          u8* a = (u8*)p + 0xb9;
          s32 z1 = 0;
          *a = v;
          (p->s).mode[1] = r;
          (p->s).mode[2] = z1;
        } else {
          if ((p->s).work[2] == 0) {
            goto go1;
          }
          (p->s).work[2]--;
        }
        if ((p->s).work[2] != 0) {
          break;
        }
      go1:
        {
          u8 v = FUN_08073500(p);
          u8* a = (u8*)p + 0xb9;
          s32 z1 = 0;
          *a = v;
          (p->s).mode[1] = 1;
          (p->s).mode[2] = z1;
        }
      }
      break;
    }
  }
}

bool8 FUN_08072800(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p3.inc");

bool8 FUN_080729e8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p4.inc");

bool8 FUN_08072e40(struct Enemy* p) { return TRUE; }

void FUN_08072e44(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32* pb4 = (s32*)((u8*)p + 0xb4);
      register s32 dx asm("r0");
      register s32 dy asm("r1");
      s32 s1, s2, dist;
      dx = *pb4;
      dx -= (p->s).coord.x;
      (p->s).d.x = dx;
      dy = *(s32*)((u8*)p + 0xc0);
      dy -= (p->s).coord.y;
      (p->s).d.y = dy;
      dx >>= 2;
      s1 = dx;
      s1 = s1 * dx;
      dy >>= 2;
      s2 = dy;
      s2 = s2 * dy;
      dist = (u16)Sqrt(s1 + s2) << 2;
      if (dist != 0) {
        (p->s).d.x = ((p->s).d.x << 8) / dist;
        (p->s).d.y = ((p->s).d.y << 8) / dist;
      }
      (p->s).unk_coord.x = ((p->s).d.x << 7) >> 8;
      (p->s).unk_coord.y = ((p->s).d.y << 7) >> 8;
      if ((p->s).coord.x > *pb4) {
        (p->s).flags &= 0xEF;
        (p->s).spr.xflip = m;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
      } else {
        s32 o = 1;
        (p->s).flags |= 0x10;
        (p->s).spr.xflip = o;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 c16 = 0x10;
          s32 ov, m11;
          asm("" : "+r"(c16));
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          *oa = m11 | c16;
        }
      }
      SetMotion(&p->s, 0x2701);
      {
        s32 z = 0;
        (p->s).work[2] = 0xF0;
        (p->s).work[3] = z;
      }
      SetDDP(&p->body, sCollisions);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      FUN_08073610(p);
      {
        s32 t = (p->s).work[3];
        s32 n = t + 1;
        u32 t2;
        (p->s).work[3] = n;
        t2 = (u32)t << 24;
        asm("" : "+r"(t2));
        t2 >>= 24;
        if ((s32)((t2 % 0xC) << 24) == 0) {
          FUN_080733b4(p, 0);
        }
      }
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[2];
        if (t != 0) {
          t -= 1;
          (p->s).work[2] = t;
          if ((t << 24) != 0) {
            goto skip1;
          }
        }
        {
          register s32 z asm("r1");
          z = 0;
          asm("" : "+r"(z));
          (p->s).mode[1] = 1;
          (p->s).mode[2] = z;
        }
      skip1:;
      }
      {
        u8* a = (u8*)p + 0xb4;
        s32 x = (p->s).coord.x;
        s32 tx = *(s32*)a;
        s32 d2 = x - tx;
        if (d2 > 0) {
          if (d2 <= 0x4FFF) {
            goto set2;
          }
          break;
        } else {
          if (tx - x > 0x4FFF) {
            break;
          }
        }
      set2:
        {
          s32 z = 0;
          (p->s).mode[1] = 1;
          (p->s).mode[2] = z;
        }
      }
      break;
    }
  }
}

bool8 FUN_08072fac(struct Enemy* p) { return TRUE; }

void FUN_08072fb0(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[1]);
    (p->s).mode[2]++;
  }
  if (isKilled(*(struct Entity**)((u8*)p + 0xbc))) {
    SetDDP(&p->body, &sCollisions[0]);
    *(struct Entity**)((u8*)p + 0xbc) = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_08072ff8(struct Enemy* p) { return TRUE; }


void FUN_08072ffc(struct Enemy* p) {}

bool8 FUN_08073000(struct Enemy* p) { return TRUE; }

// 0x08073004
void FUN_08073004(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 dy = (p->s).d.y + 0x10;
      (p->s).d.y = dy;
      if (dy > 0x380) {
        (p->s).d.y = 0x380;
      }
      if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y + (p->s).d.y) << 16) != 0) {
        if ((p->s).coord.y - FUN_08009f6c((p->s).coord.x, (p->s).coord.y) > 0) {
          if ((p->s).coord.y - FUN_08009f6c((p->s).coord.x, (p->s).coord.y) <= 0x6FF) goto land;
          break;
        } else {
          if (FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - (p->s).coord.y > 0x6FF) break;
        }
      land:
        (p->s).d.y = 0;
        (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      } else {
        (p->s).coord.y += (p->s).d.y;
      }
      break;
    }
  }
  {
    struct Entity** slot = (struct Entity**)((u8*)p + 0xbc);
    if (isKilled(*slot)) {
      SetDDP(&p->body, &sCollisions[0]);
      *slot = NULL;
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
  }
}

bool8 FUN_080730cc(struct Enemy* p) { return TRUE; }

void FUN_08073610(struct Enemy* p);

// 0x080730D0
void FUN_080730d0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8 xf;
      s32 v;
      SetDDP(&p->body, &sCollisions[6]);
      xf = ((pZero2->s).flags >> 4) & 1;
      (p->s).mode[3] = xf;
      if (xf == 0) {
        (p->s).d.x = -0x280;
        v = 0x80 << 1;
      } else {
        (p->s).d.x = 0xA0 << 2;
        v = -0x100;
      }
      (p->s).unk_coord.x = v;
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 dx;
      s32 nx;
      s32 ny;
      s32 gy;
      {
        register s32 att asm("r0");
        register s32 mask asm("r1");
        att = FUN_080098a4((p->s).coord.x + (p->s).d.x, (p->s).coord.y + (p->s).d.y);
        att <<= 16;
        mask = 0xF0000;
        mask &= att;
        mask = (u32)mask >> 16;
        if (mask != 1) {
          goto rest;
        }
      }
      {
        SET_ENEMY_ROUTINE(p, 2);
        break;
      }
    rest:
      nx = (p->s).coord.x;
      dx = (p->s).d.x;
      nx += dx;
      (p->s).coord.x = nx;
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      {
        s32 t = ((p->s).unk_coord.x - dx) << 3;
        t >>= 8;
        (p->s).d.x = dx + t;
      }
      gy = FUN_08009f6c(nx, ny + -0x2000);
      if (gy - (p->s).coord.y <= 0x40) {
        (p->s).coord.y = gy;
      }
      FUN_08073610(p);
      {
        u8 m3 = (p->s).mode[3];
        if (m3 == 0) {
          if ((p->s).d.x >= 0) {
            (p->s).mode[1] = m3;
            (p->s).mode[2] = m3;
          }
        } else {
          if ((p->s).d.x <= 0) {
            (p->s).mode[1] = 0;
            (p->s).mode[2] = 0;
          }
        }
      }
      break;
    }
  }
}

INCASM("asm/enemy/pantheon_aqua_p9.inc");

s32 FUN_08073368(struct Enemy* p) { return TRUE; }

void FUN_0807336c(struct Body* body, struct Coord* c) {
  u8 t = ((body->enemy)->processing)->atkType;
  if (t == 3 || t == 14 || t == 15) {
    struct CollidableEntity* parent = body->parent;
    if ((parent->body).status & BODY_STATUS_DEAD) {
      if ((parent->s).coord.x < c->x) {
        ((struct Enemy*)parent)->props[7] = 0xFF;
      } else {
        ((struct Enemy*)parent)->props[7] = 0xFE;
      }
    }
  }
}

INCASM("asm/enemy/pantheon_aqua_p10.inc");

u8 FUN_08073500(struct Enemy* p) {
  register struct Zero* z asm("r3");
  register s32 dx asm("r4");
  register s32 dy asm("r5");
  register s32 norm asm("r6");
  register s32 t asm("r0");
  register s32 zx asm("r2");
  register s32 px asm("r1");
  register s32 zy asm("r1");
  s32 a, b, s1, s2;
  s32 ret;
  z = pZero2;
  zx = (z->s).coord.x;
  px = (p->s).coord.x;
  dx = zx - px;
  t = (p->s).coord.y + 0xC00;
  zy = (z->s).coord.y;
  dy = zy - t;
  a = dx >> 2;
  s1 = a;
  s1 = s1 * a;
  b = dy >> 2;
  s2 = b;
  s2 = s2 * b;
  norm = Sqrt(s1 + s2) << 2;
  if (norm != 0) {
    dx = (dx << 8) / norm;
    dy = (dy << 8) / norm;
  }
  if (dx > 0) {
    s32 a = dy;
    asm("" : "+r"(a));
    if (a < 0) {
      a = -a;
    }
    if (a > 0xEC) {
      ret = 0;
      if (dy > 0) {
        ret = 4;
      }
    } else {
      s32 b = dy;
      asm("" : "+r"(b));
      if (b < 0) {
        b = -b;
      }
      ret = 2;
      if (b > 0x60) {
        ret = 1;
        if (dy > 0) {
          ret = 3;
        }
      }
    }
  } else {
    s32 a = dy;
    asm("" : "+r"(a));
    if (a < 0) {
      a = -a;
    }
    if (a > 0xEC) {
      ret = 0;
      if (dy > 0) {
        ret = 4;
      }
    } else {
      s32 b = dy;
      asm("" : "+r"(b));
      if (b < 0) {
        b = -b;
      }
      ret = 6;
      if (b > 0x60) {
        ret = 7;
        if (dy > 0) {
          ret = 5;
        }
      }
    }
  }
  return ret;
}

extern const u8 u8_ARRAY_080ff00c[80];

s32 FUN_080735ac(struct Enemy* p) {
  s32 dy = (p->s).coord.y - (pZero2->s).coord.y;
  if (dy < 0) {
    dy = -dy;
  }
  if (dy <= 0x1FFF) {
    s32 i = RANDOM(RNG_0202f388) & 0xF;
    if (u8_ARRAY_080ff00c[i] == 1) {
      return 2;
    }
    return 1;
  }
  return 0;
}

// Sea-surface clamp for the aqua pantheon: rise with the water line while it
// is on screen, sink slowly once it is not. Retail carries all three large
// constants (0x4FFF/-0x2600/0x2600) through one callee-saved r4 temp and its
// scratch assignment cascades (p=r3, sea=r2, y=r1); pins reproduce the roles
// but not the head ordering (allocation-cascade basin).
NON_MATCH void FUN_08073610(struct Enemy* p) {
#if MODERN
  struct Overworld* ow = &gOverworld;
  struct Camera* cam = &gStageRun.vm.camera;
  s32 sea = ow->sea;
  if (sea < cam->viewport.y + 0x4FFF) {
    if (sea > (p->s).coord.y - 0x2600) {
      (p->s).coord.y = sea + 0x2600;
    }
  } else {
    (p->s).coord.y += 0x200;
  }
#else
  INCCODE("asm/enemy/pantheon_aqua_3610.inc");
#endif
}

void PantheonAqua_Init(struct Enemy* p);
void PantheonAqua_Update(struct Enemy* p);
void PantheonAqua_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonAquaRoutine = {
    [ENTITY_INIT] =      PantheonAqua_Init,
    [ENTITY_UPDATE] =    PantheonAqua_Update,
    [ENTITY_DIE] =       PantheonAqua_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_080726a8(struct Enemy* p);
bool8 FUN_08072800(struct Enemy* p);
bool8 FUN_080729e8(struct Enemy* p);
bool8 FUN_08072e40(struct Enemy* p);
bool8 FUN_08072fac(struct Enemy* p);
bool8 FUN_08072ff8(struct Enemy* p);
bool8 FUN_08073000(struct Enemy* p);
bool8 FUN_080730cc(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366bd0[8] = {
    (EnemyFunc)nop_080726a8,
    (EnemyFunc)FUN_08072800,
    (EnemyFunc)FUN_080729e8,
    (EnemyFunc)FUN_08072e40,
    (EnemyFunc)FUN_08072fac,
    (EnemyFunc)FUN_08072ff8,
    (EnemyFunc)FUN_08073000,
    (EnemyFunc)FUN_080730cc,
};
// clang-format on

void FUN_080726ac(struct Enemy* p);
void FUN_08072804(struct Enemy* p);
void FUN_080729ec(struct Enemy* p);
void FUN_08072e44(struct Enemy* p);
void FUN_08072fb0(struct Enemy* p);
void FUN_08072ffc(struct Enemy* p);
void FUN_08073004(struct Enemy* p);
void FUN_080730d0(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366bf0[8] = {
    FUN_080726ac,
    FUN_08072804,
    FUN_080729ec,
    FUN_08072e44,
    FUN_08072fb0,
    FUN_08072ffc,
    FUN_08073004,
    FUN_080730d0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(28), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(28), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 2,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(21), -PIXEL(29), PIXEL(19), PIXEL(9)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(21), -PIXEL(29), PIXEL(19), PIXEL(9)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(28), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(23)};
