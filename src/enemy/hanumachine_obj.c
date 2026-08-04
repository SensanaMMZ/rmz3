#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "motion.h"
#include "zero.h"
#include "metatile.h"

void FUN_080866a4(struct Entity* e, u8 mode, u8 xflip) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HANUMACHINE_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).unk_28 = e;
    SET_XFLIP(&p->s, xflip);
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
  }
}

extern const struct Collision sCollisions[6];
void HanumachineObj_Update(struct Enemy* p);

// 0x08086740
void HanumachineObj_Init(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  register s32 z asm("r5");
  s32 dx;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitScalerotMotion2(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    fv |= fl;
    fl = FLIPABLE;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0x6a, 0x03));
  (p->s).flags |= COLLIDABLE;
  {
    struct Body* body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 8);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)z;
  }
  if ((p->s).flags & X_FLIP) {
    (p->s).coord.x = (q->coord).x + 0x1600;
    dx = 0x400;
  } else {
    (p->s).coord.x = (q->coord).x - 0x1600;
    dx = -0x400;
  }
  (p->s).d.x = dx;
  (p->s).coord.y = (q->coord).y - 0xF00;
  {
    register u8* a asm("r1");
    register s32 t2 asm("r2");
    register s32 t3 asm("r3");
    register s32 kk asm("r0");
    a = (u8*)p + 0xc0;
    t2 = 0;
    t3 = 0;
    kk = 0x258;
    *(u16*)a = kk;
    {
      register u8* b asm("r0");
      register s32 f asm("r1");
      b = (u8*)p + 0xbd;
      *b = t2;
      (p->s).d.y = t3;
      asm("" : "+r"(b));
      b -= 0x6d;
      asm("" : "+r"(b));
      f = 0x40;
      *(u16*)b = f;
      asm("" : "+r"(b));
      b += 2;
      asm("" : "+r"(b));
      *(u16*)b = f;
    }
  }
  HanumachineObj_Update(p);
}

extern const EnemyFunc sUpdates[8];
extern const struct Collision sCollisions[6];
void FUN_08086e34(struct Enemy* p);
void HanumachineObj_Die(struct Enemy* p);

void HanumachineObj_Update(struct Enemy* p) {
  struct Coord c1;
  struct Coord c2;
  u16* timer = (u16*)((u8*)p + 0xc0);
  s32 t;
  if (*timer == 0) {
    c1.x = (p->s).coord.x;
    c1.y = (p->s).coord.y - 0x800;
    PlaySound(0x2a);
    CreateSmoke(1, &c1);
    if (*(u8*)((u8*)p + 0xbd) != 0) {
      SetDDP(&p->body, &sCollisions[5]);
    } else {
      SetDDP(&p->body, &sCollisions[3]);
    }
    goto die;
  }
  if ((p->s).mode[1] != 7) {
    if (((p->body).status & 0x00020001) == 0x00020001) {
      (p->s).mode[1] = 7;
      (p->s).mode[2] = 0;
    }
    if ((p->s).mode[1] != 7) {
      goto cont;
    }
  }
  FUN_08086e34(p);
  return;

cont:
  if ((p->body).status & BODY_STATUS_DEAD) {
    c2.x = (p->s).coord.x;
    c2.y = (p->s).coord.y - 0x800;
    PlaySound(0x2a);
    CreateSmoke(1, &c2);
  die:
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    HanumachineObj_Die(p);
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
  t = *timer - 1;
  *timer = t;
  if ((u16)t > 0x3b) {
    return;
  }
  if ((t & 3U) <= 1) {
    PaintEntityWhite(&p->s);
  } else {
    UpdateEntityPaletteID(&p->s);
  }
}

void HanumachineObj_Die(struct Enemy* p) {
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_0808693c(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).work[2] = ((p->s).work[0] << 3) + 2;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  {
    u8 f = (p->s).flags & X_FLIP;
    s32 off = -0xA00;
    if (f) {
      off = 0xA00;
    }
    if ((u8)--(p->s).work[2] == 0xFF || FUN_080098a4((p->s).coord.x + off, (p->s).coord.y)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_080869a0(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).d.y = -0x300;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (((p->s).spr).mag.x <= 0xFF) {
    ((p->s).spr).mag.x += 0x10;
    ((p->s).spr).mag.y += 0x10;
  }
  if ((p->s).d.y > 0) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

// 0x080869f4
void FUN_080869f4(struct Enemy* p) {
  u16 r;
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x6A, 0x02));
    (p->s).work[2] = 0x10;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  r = FUN_080098a4((p->s).coord.x, (p->s).coord.y + 1);
  if (r == 0) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = r;
  } else if ((u8)--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
}

// 0x08086A50
void FUN_08086a50(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    register s32 xf asm("r2");
    SetMotion(&p->s, 0x6A03);
    xf = 0;
    if ((p->s).coord.x < (pZero2->s).coord.x) {
      xf = 1;
    }
    if (xf != 0) {
      (p->s).flags |= 0x10;
    } else {
      register u8 h asm("r1");
      register u8 g asm("r0");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g = 0xEF;
      g &= h;
      (p->s).flags = g;
    }
    {
      register s32 xv asm("r1");
      register u8* oa asm("r3");
      s32 sh4, ov, m11;
      xv = xf;
      *((u8*)p + 0x4c) = xv;
      oa = (u8*)p + 0x4a;
      sh4 = xv << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh4;
    }
    if ((p->s).flags & 0x10) {
      (p->s).d.x = 0x180;
    } else {
      (p->s).d.x = -0x180;
    }
    (p->s).d.y = -0x300;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 k4 asm("r1");
    register s32 t asm("r0");
    t = *(u32*)((u8*)p + 0x8c);
    k4 = 4;
    t &= k4;
    if (t != 0) {
      (p->s).mode[1] = k4;
      (p->s).mode[2] = 0;
      return;
    }
  }
  if ((u16)FUN_080098a4((p->s).coord.x + (p->s).d.x, (p->s).coord.y) != 0) {
    register s32 fl asm("r2");
    register s32 nf asm("r1");
    (p->s).d.x = -(p->s).d.x;
    fl = (p->s).flags;
    {
      register s32 sh asm("r0");
      sh = (u32)fl >> 4;
      nf = 1;
      nf &= ~sh;
    }
    if (nf != 0) {
      register s32 g asm("r0");
      g = 0x10;
      g |= fl;
      (p->s).flags = g;
    } else {
      register s32 g2 asm("r0");
      g2 = 0xEF;
      g2 &= fl;
      (p->s).flags = g2;
    }
    {
      register u8* oa asm("r3");
      s32 sh4, ov, m11;
      *((u8*)p + 0x4c) = nf;
      oa = (u8*)p + 0x4a;
      sh4 = nf << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh4;
    }
  }
  {
    register s32 cx asm("r0");
    register s32 cy asm("r1");
    register s32 dy asm("r2");
    cx = (p->s).coord.x;
    cx += (p->s).d.x;
    (p->s).coord.x = cx;
    cy = (p->s).coord.y;
    dy = (p->s).d.y;
    cy += dy;
    (p->s).coord.y = cy;
    dy += 0x40;
    (p->s).d.y = dy;
    if ((u16)FUN_080098a4(cx, cy) != 0) {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
    }
  }
}

// 0x08086B6C
void FUN_08086b6c(struct Enemy* p) {
  register s32 z asm("r4");
  z = (p->s).mode[2];
  if (z == 0) {
    SetMotion(&p->s, 0x6A04);
    {
      register u8* q asm("r2");
      register s32 ov asm("r1");
      register s32 m asm("r0");
      register s32 four asm("r1");
      q = (u8*)p + 0x49;
      ov = *q;
      m = 0xd;
      m = -m;
      m &= ov;
      four = 4;
      m |= four;
      *q = m;
      (p->s).work[2] = z;
      q += 0x6b;
      asm("" : "+r"(q));
      {
        register struct Zero* zz asm("r3");
        register s32 a asm("r0");
        register s32 b asm("r1");
        zz = pZero2;
        a = (p->s).coord.x;
        b = (zz->s).coord.x;
        a -= b;
        *(s32*)q = a;
        {
          register s32 rv asm("r0");
          register s32 lim asm("r1");
          z = (s32)((u8*)p + 0xb8);
          rv = RANDOM(RNG_0202f388) & 0x7FF;
          lim = 0xFFFFF800;
          lim -= rv;
          *(s32*)z = lim;
        }
        {
          register s32 f asm("r0");
          register s32 one asm("r1");
          register u8* d asm("r1");
          f = (zz->s).flags;
          f = (u32)f >> 4;
          one = 1;
          f &= one;
          d = (u8*)p + 0xbc;
          *d = f;
          d += 4;
          asm("" : "+r"(d));
          f = 0x3c;
          *(u16*)d = f;
        }
      }
    }
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 cur asm("r2");
    register struct Zero* zz asm("r3");
    register s32 fl asm("r0");
    register s32 nx asm("r1");
    cur = *((u8*)p + 0xbc);
    zz = pZero2;
    fl = (zz->s).flags;
    fl = (u32)fl >> 4;
    {
      register s32 one asm("r1");
      one = 1;
      fl &= one;
    }
    if (cur == fl) {
      register s32* o asm("r0");
      o = (s32*)((u8*)p + 0xb4);
      asm("" : "+r"(o));
      nx = (zz->s).coord.x;
      nx += *o;
    } else {
      register s32* o2 asm("r0");
      o2 = (s32*)((u8*)p + 0xb4);
      asm("" : "+r"(o2));
      nx = (zz->s).coord.x;
      nx -= *o2;
    }
    (p->s).coord.x = nx;
  }
  {
    register struct Zero* zz asm("r2");
    register s32 xf asm("r2");
    zz = pZero2;
    {
      register s32 cy asm("r0");
      register s32 oy asm("r1");
      oy = (s32)((u8*)p + 0xb8);
      cy = (zz->s).coord.y;
      oy = *(s32*)oy;
      cy += oy;
      (p->s).coord.y = cy;
    }
    {
      register s32 f asm("r4");
      f = 0;
      if ((p->s).coord.x < (zz->s).coord.x) {
        f = 1;
      }
      xf = f;
    }
    if (xf != 0) {
      register u8 h asm("r1");
      register u8 g asm("r0");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g = 0x10;
      g |= h;
      (p->s).flags = g;
    } else {
      register u8 h asm("r1");
      register u8 g asm("r0");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g = 0xEF;
      g &= h;
      (p->s).flags = g;
    }
    {
      register s32 xv asm("r1");
      register u8* oa asm("r3");
      s32 sh4, ov, m11;
      xv = xf;
      *((u8*)p + 0x4c) = xv;
      oa = (u8*)p + 0x4a;
      sh4 = xv << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh4;
    }
  }
  {
    register s32 r asm("r1");
    r = (s32)pZero2;
    if (r != 0) {
      register s32 v asm("r0");
      v = ((s32 (*)(s32))CountButtonMashing)(r);
      v += (p->s).work[2];
      (p->s).work[2] = v;
      if ((u8)v <= 0x18) {
        register struct Zero* z2 asm("r3");
        z2 = pZero2;
        if ((*(s32*)((u8*)z2 + 0x8c) & (0x80 << 2)) == 0) {
          register s16* hp asm("r0");
          hp = (s16*)((u8*)z2 + 0xa4);
          if (*hp != 0) {
            return;
          }
        }
      }
      r = 0;
    }
    (p->s).mode[1] = 5;
    (p->s).mode[2] = r;
  }
}


void FUN_08086cbc(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x6a, 0x03));
    ((p->s).spr).oam.priority = 2;
    SetDDP(&p->body, &sCollisions[2]);
    {
      u8 sh = (p->s).flags >> 4;
      u8 on = 1;
      on &= ~sh;
      SET_XFLIP(p, on);
    }
    {
      register s32 v asm("r0");
      if ((p->s).flags & X_FLIP) {
        v = 0x180;
      } else {
        v = -0x180;
      }
      (p->s).d.x = v;
    }
    (p->s).d.y = -0x300;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_080098a4((p->s).coord.x + (p->s).d.x, (p->s).coord.y) != 0) {
    (p->s).d.x = -(p->s).d.x;
    {
      u8 sh = (p->s).flags >> 4;
      u8 on = 1;
      on &= ~sh;
      SET_XFLIP(p, on);
    }
  }
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}


void FUN_08086dcc(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    InitNonAffineMotion(&p->s);
    SetMotion(&p->s, MOTION(0x6a, 0x03));
    SetDDP(&p->body, &sCollisions[1]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

// 0x08086E34
void FUN_08086e34(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    register s32 dx asm("r1");
    register s32 dy asm("r0");
    register s32 len asm("r5");
    struct Zero* z;
    SetMotion(&p->s, MOTION(0x6A, 3));
    z = pZero2;
    dx = (p->s).coord.x;
    dx -= (z->s).coord.x;
    (p->s).d.x = dx;
    dy = (p->s).coord.y;
    dy -= (z->s).coord.y;
    dy += -0x1800;
    (p->s).d.y = dy;
    dx >>= 8;
    len = dx * dx;
    dy >>= 8;
    {
      s32 u = dy * dy;
      len += u;
    }
    len = (u16)Sqrt(len);
    if (len != 0) {
      s32 a = (p->s).d.x / len;
      s32 b;
      (p->s).d.x = a;
      b = (p->s).d.y / len;
      (p->s).d.x = a * 6;
      (p->s).d.y = b * 6;
    } else {
      register s32 nv asm("r0");
      register s32 zy asm("r0");
      if (((pZero2->s).flags & 0x10) != 0) {
        nv = 0xC0 << 3;
      } else {
        nv = -0x600;
      }
      (p->s).d.x = nv;
      zy = 0;
      asm volatile("" : "+r"(zy));
      (p->s).d.y = zy;
    }
    if ((p->s).d.x > 0) {
      register s32 zc asm("r2");
      register u8* a4c asm("r0");
      register u8* a4a asm("r2");
      register u8 ov asm("r1");
      register s32 m asm("r0");
      zc = 0;
      {
        register u8 fl asm("r1");
        register s32 g asm("r0");
        fl = (p->s).flags;
        g = 0xEF;
        g &= fl;
        (p->s).flags = g;
      }
      a4c = (u8*)p + 0x4c;
      *a4c = zc;
      a4a = (u8*)p + 0x4a;
      ov = *a4a;
      m = 0x11;
      m = -m;
      m &= ov;
      *a4a = m;
    } else {
      register s32 one asm("r2");
      register u8* b4c asm("r0");
      register u8* b4a asm("r3");
      register s32 k10 asm("r2");
      register u8 ov2 asm("r1");
      register s32 m2 asm("r0");
      one = 1;
      {
        register u8 fl2 asm("r1");
        register s32 g2 asm("r0");
        fl2 = (p->s).flags;
        g2 = 0x10;
        g2 |= fl2;
        (p->s).flags = g2;
      }
      b4c = (u8*)p + 0x4c;
      *b4c = one;
      b4a = (u8*)p + 0x4a;
      k10 = 0x10;
      ov2 = *b4a;
      m2 = 0x11;
      m2 = -m2;
      m2 &= ov2;
      m2 |= k10;
      *b4a = m2;
    }
    *((u8*)p + 0xbd) = 1;
    SetDDP(&p->body, &sCollisions[4]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 cx = (p->s).coord.x;
    s32 vx = (p->s).d.x;
    s32 nx = cx + vx;
    s32 cy;
    s32 vy;
    s32 ny;
    (p->s).coord.x = nx;
    cy = (p->s).coord.y;
    vy = (p->s).d.y;
    ny = cy + vy;
    (p->s).coord.y = ny;
    (p->s).d.y = vy + 0x40;
    if ((*(u32*)((u8*)p + 0x8c) & 4) != 0 || ((u16)FUN_080098a4(nx + vx, ny) << 16) != 0 ||
        ((u16)FUN_080098a4((p->s).coord.x + (p->s).d.x, (p->s).coord.y + -0x1000) << 16) != 0) {
      *(u16*)((u8*)p + 0xc0) = 0;
    }
  }
}

void HanumachineObj_Init(struct Enemy* p);
void HanumachineObj_Update(struct Enemy* p);
void HanumachineObj_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gHanumachineObjRoutine = {
    [ENTITY_INIT] =      HanumachineObj_Init,
    [ENTITY_UPDATE] =    HanumachineObj_Update,
    [ENTITY_DIE] =       HanumachineObj_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0808693c(struct Enemy* p);
void FUN_080869a0(struct Enemy* p);
void FUN_080869f4(struct Enemy* p);
void FUN_08086a50(struct Enemy* p);
void FUN_08086b6c(struct Enemy* p);
void FUN_08086cbc(struct Enemy* p);
void FUN_08086dcc(struct Enemy* p);
void FUN_08086e34(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates[8] = {
    FUN_0808693c,
    FUN_080869a0,
    FUN_080869f4,
    FUN_08086a50,
    FUN_08086b6c,
    FUN_08086cbc,
    FUN_08086dcc,
    FUN_08086e34,
};
// clang-format on

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(26), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(26), PIXEL(28)},
    },
};
