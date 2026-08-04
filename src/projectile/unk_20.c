#include "collision.h"
#include "global.h"
#include "physics.h"
#include "trig.h"
#include "projectile.h"
#include "vfx.h"
#include "zero.h"

static const struct Collision sCollisions[3];
static const u8 sInitModes[4];

void Projectile20_Update(struct Projectile* p);

static void nop_080a5048(struct Projectile* p) {}

void Projectile20_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_080a5048);
  Projectile20_Update(p);
}

static const ProjectileFunc PTR_ARRAY_0836ba50[10];
static const ProjectileFunc PTR_ARRAY_0836ba78[10];

void Projectile20_Update(struct Projectile* p) {
  struct Entity* parent = (p->s).unk_28;
  if (parent->mode[0] > 1 && (p->s).mode[1] != 7) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
  PTR_ARRAY_0836ba50[(p->s).mode[1]](p);
  PTR_ARRAY_0836ba78[(p->s).mode[1]](p);
}

void Projectile20_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(3, &(p->s).coord);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080a5144(struct Projectile* p) {}

void FUN_080a4fa4(struct Projectile* p);

// 0x080a5148
void FUN_080a5148(struct Projectile* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      *(s32*)((u8*)p + 0xb4) = m;
      *(s32*)((u8*)p + 0xb8) = 0x2000;
      (p->s).taskCol = 0x19;
      SetMotion(&p->s, MOTION(0x49, 0x00));
      (p->s).work[2] = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32* q = (s32*)((u8*)p + 0xb4);
      s32 v = *q + 0x100;
      *q = v;
      if (v > 0x3FFF) {
        s32 z = 0;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      FUN_080a4fa4(p);
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080A51B4
void FUN_080a51b4(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 xf asm("r2");
      SetDDP(&p->body, (const struct Collision*)0x0836BAD0);
      InitNonAffineMotion(&p->s);
      {
        register s32 qf asm("r0");
        register s32 one asm("r0");
        qf = q->flags;
        xf = qf >> 4;
        one = 1;
        xf &= one;
      }
      if (xf != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
      {
        register s32 v asm("r1");
        u8* oa;
        s32 sh4, ov, m11;
        asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(xf));
        ((p->s).spr).xflip = v;
        oa = (u8*)p + 0x4a;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      SetMotion(&p->s, 0x4900);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      u32* w;
      u8 z;
      *(s32*)((u8*)p + 0xb8) += 0x200;
      FUN_080a4fa4(p);
      UpdateMotionGraphic(&p->s);
      {
        u8* tc = (u8*)p + 0x25;
        z = 0;
        *tc = 0x17;
      }
      w = (u32*)((u8*)q + 0xc0);
      if (*w & 2) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = z;
      }
      if (*w & 8) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = z;
      }
      if (*w & 0x20) {
        (p->s).mode[1] = 7;
        (p->s).mode[2] = z;
      }
      if (*w & 0x80) {
        (p->s).mode[1] = 9;
        (p->s).mode[2] = z;
      }
      break;
    }
  }
}

// 0x080A5290
void FUN_080a5290(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 xf asm("r2");
      register s32 z asm("r4");
      SetDDP(&p->body, &sCollisions[1]);
      {
        u8* tc = (u8*)p + 0x25;
        *tc = 0x17;
      }
      InitRotatableMotion(&p->s);
      {
        register s32 qf asm("r0");
        register s32 one asm("r0");
        qf = q->flags;
        xf = qf >> 4;
        one = 1;
        xf &= one;
      }
      if (xf != 0) {
        register s32 g asm("r0");
        register s32 k asm("r1");
        g = (p->s).flags;
        asm("" : "+r"(g));
        k = 0x10;
        g |= k;
        (p->s).flags = g;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
      {
        register s32 v asm("r1");
        register u8* xp asm("r0");
        u8* oa;
        s32 sh4, ov, m11;
        asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(xf));
        xp = (u8*)p + 0x4c;
        z = 0;
        *xp = v;
        oa = (u8*)p + 0x4a;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      SetMotion(&p->s, 0x4901);
      (p->s).work[2] = z;
      (p->s).work[3] = 0x10;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 dx asm("r6");
      register s32 dy asm("r5");
      register s32 cx asm("r4");
      register s32 cy asm("r8");
      s32 sp;
      if ((u8)--(p->s).work[3] == 0) {
        (p->s).mode[2]++;
      }
      {
        register s32 t asm("r0");
        t = (q->coord).x;
        cx = (p->s).coord.x;
        dx = t - cx;
        t = (q->coord).y;
        {
          register s32 u asm("r1");
          u = (p->s).coord.y;
          cy = u;
          dy = t - u;
        }
      }
      {
        register s32 num asm("r0");
        num = dx << 8;
        sp = 0xe0 << 1;
        cx += num / sp;
        (p->s).coord.x = cx;
        num = dy << 8;
        (p->s).coord.y = (num / sp) + cy;
      }
      {
        register s32 a asm("r0");
        a = (p->s).work[2];
        a += 0x10;
        (p->s).work[2] = a;
        {
          register u8* ap asm("r1");
          ap = (u8*)p + 0x24;
          *ap = a;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      register s32 dx asm("r6");
      register s32 dy asm("r5");
      register s32 a asm("r2");
      {
        register s32 zx asm("r0");
        register s32 t asm("r1");
        zx = (pZero2->s).coord.x;
        t = (p->s).coord.x;
        dx = zx - t;
        t = (p->s).coord.y;
        dy = FUN_08009f6c(zx, t);
        t = (p->s).coord.y;
        dy -= t;
      }
      {
        register s32 t asm("r0");
        t = ArcTan2(dx >> 8, dy >> 8) >> 8;
        asm("" : "+r"(t));
        a = t;
      }
      a += 0x40;
      (p->s).work[2] = a;
      if (((p->s).flags & X_FLIP) != 0) {
        register s32 n asm("r0");
        n = -a;
        (p->s).work[2] = n;
      }
      {
        register s32 av asm("r1");
        register u8* ap asm("r0");
        av = (p->s).work[2];
        ap = (u8*)p + 0x24;
        *ap = av;
      }
      (p->s).work[3] = 20;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      register s32 r asm("r1");
      {
        register s32 t asm("r0");
        t = (p->s).work[3];
        t -= 1;
        (p->s).work[3] = t;
        r = (u8)t;
      }
      if (r == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = r;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}


void FUN_080a53e8(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0: {
      u8 a;
      u8 b;
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0x49, 0x01));
      a = (p->s).work[2];
      if ((p->s).flags & X_FLIP) {
        a = -a;
      }
      b = a - 0x40;
      (p->s).d.x = (COS(b) * 0x2C0) / 256;
      (p->s).d.y = (SIN(b) * 0x2C0) / 256;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      if (PushoutToUp1((p->s).coord.x, (p->s).coord.y + 0x1000) < 0) {
        (p->s).mode[2]++;
      }
      {
        s32 t = (p->s).work[2] + 0x10;
        (p->s).work[2] = t;
        (p->s).angle = t;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      (p->s).work[3] = 0x3C;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      {
        s32 t = (p->s).work[2] + 0x10;
        (p->s).work[2] = t;
        (p->s).angle = t;
      }
      UpdateMotionGraphic(&p->s);
      if (*(u32*)((u8*)q + 0xc0) & 4) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

void FUN_080a4fa4(struct Projectile* p);

// 0x080A54F8
void FUN_080a54f8(struct Projectile* p) {
  register struct Entity* e asm("r5");
  e = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 k asm("r6");
      s32 arg;
      s32 dxv;
      SetDDP(&p->body, (const struct Collision*)0x0836BAB8);
      {
        u32 fv = *(u32*)((u8*)e + 0xc0);
        k = 0x10;
        if ((fv & k) != 0) {
        register s32 dy asm("r3");
        register u32 t asm("r3");
        register s32 ex asm("r5");
        register s32 v asm("r2");
        {
          register s32 py asm("r3");
          register s32 ey asm("r0");
          py = (p->s).coord.y;
          ey = e->coord.y;
          dy = py - ey;
        }
        {
          s32 dq = dy;
          if (dy < 0) {
            dq = dy + 7;
          }
          dq >>= 3;
          t = (u16)Sqrt(dq);
        }
        (p->s).d.y = -(s32)(t << 4);
        (p->s).unk_coord.y = k;
        (p->s).work[3] = t;
        ex = e->coord.x;
        {
          s32 v0 = ex - 0x1800;
          u32 tf;
          u32 fl;
          (p->s).d.x = v0;
          asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(v0));
          fl = (p->s).flags;
          asm volatile("add %0, %1, #0" : "=&l"(tf) : "l"(k));
          tf &= fl;
          if (tf != 0) {
            v = ex + (0xc0 << 5);
          }
        }
        {
          register s32 cxx asm("r0");
          cxx = (p->s).coord.x;
          asm volatile("sub %0, %1, %0" : "+l"(cxx) : "l"(v));
          (p->s).d.x = cxx;
          dxv = cxx;
        }
        arg = t;
      } else {
        register s32 dy asm("r3");
        register u32 t asm("r3");
        register s32 bx asm("r2");
        register s32 v asm("r3");
        {
          register s32 py asm("r3");
          register s32 ey asm("r0");
          py = (p->s).coord.y;
          ey = e->coord.y;
          dy = py - ey;
        }
        {
          s32 dq = dy;
          if (dy < 0) {
            dq = dy + 7;
          }
          dq >>= 3;
          t = (u16)Sqrt(dq);
        }
        (p->s).d.y = -(s32)(t << 4);
        (p->s).unk_coord.y = k;
        (p->s).work[3] = t;
        bx = *(s32*)((u8*)e + 0xb8);
        asm volatile("" : : "l"(e));
        {
          s32 v0 = bx - 0x4C00;
          u32 tf;
          u32 fl;
          (p->s).d.x = v0;
          asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(v0));
          fl = (p->s).flags;
          asm volatile("add %0, %1, #0" : "=&l"(tf) : "l"(k));
          tf &= fl;
          if (tf != 0) {
            v = bx + (0x98 << 7);
          }
        }
        {
          register s32 cxx asm("r0");
          cxx = (p->s).coord.x;
          asm volatile("sub %0, %1, %0" : "+l"(cxx) : "l"(v));
          (p->s).d.x = cxx;
          dxv = cxx;
        }
        arg = (p->s).work[3];
      }
      }
      (p->s).d.x = dxv / arg;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t = (p->s).work[3] - 1;
      s32 w2;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      w2 = (p->s).work[2] + 0x10;
      (p->s).work[2] = w2;
      (p->s).angle = w2;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      (p->s).d.y += (p->s).unk_coord.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      register s32 d asm("r3");
      {
        register s32* q asm("r1");
        register s32 val asm("r0");
        q = (s32*)((u8*)p + 0xb8);
        val = 0;
        *q = val;
        q = (s32*)((u8*)q - 4);
        val = 0x80 << 7;
        *q = val;
      }
      {
        register s32 dyv asm("r0");
        register s32 kk asm("r1");
        dyv = (p->s).work[2] << 8;
        (p->s).d.y = dyv;
        kk = 0x80 << 10;
        d = kk - dyv;
      }
      {
        register s32 dq2 asm("r0");
        asm volatile("add %0, %1, #0" : "=&l"(dq2) : "l"(d));
        if (d < 0) {
          dq2 += 63;
        }
        dq2 >>= 6;
        (p->s).d.x = (u32)((u32)Sqrt(dq2) << 16) >> 9;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 v;
      (p->s).d.y += (p->s).d.x;
      v = (p->s).d.x - 0x80;
      (p->s).d.x = v;
      if (v < 0) {
        register s32 c asm("r1");
        register u32* f asm("r2");
        u32 fv;
        c = 0;
        (p->s).d.y = c;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = c;
        f = (u32*)((u8*)e + 0xc0);
        asm volatile("" : : "l"(e));
        fv = *f;
        c -= 5;
        fv &= c;
        c -= 12;
        fv &= c;
        *f = fv;
      }
      (p->s).angle = (p->s).d.y >> 8;
      FUN_080a4fa4(p);
      (p->s).taskCol = 23;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080a569c(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0: {
      u8 on;
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).taskCol = 0x17;
      InitRotatableMotion(&p->s);
      on = (q->flags >> 4) & 1;
      SET_XFLIP(p, on);
      SetMotion(&p->s, MOTION(0x49, 0x01));
      (p->s).work[2] = 0;
      (p->s).work[3] = 0x10;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      s32 t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      {
        s32 dx;
        s32 px;
        s32 dy;
        s32 py;
        dx = q->coord.x;
        px = (p->s).coord.x;
        dx -= px;
        dy = q->coord.y;
        py = (p->s).coord.y;
        dy -= py;
        (p->s).coord.x = px + dx / 6;
        (p->s).coord.y = py + dy / 6;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).work[2] = 0;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      s32 t = (p->s).work[3] + 1;
      (p->s).work[3] = t;
      if ((u8)t > 0x13) {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      }
      if ((p->s).work[3] > 0x10) {
        (p->s).work[2] += 0x10;
      } else {
        (p->s).work[2] += (p->s).work[3];
      }
      (p->s).angle = (p->s).work[2];
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080a57ac(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 a, b, dy, v;

  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).d.y = 0x2C0;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).coord.y += (p->s).d.y;
      if ((p->s).d.y > 0) {
        a = PushoutToUp1((p->s).coord.x - 0x1000, (p->s).coord.y + 0x1000);
        b = PushoutToUp1((p->s).coord.x + 0x1000, (p->s).coord.y + 0x1000);
        if (a != 0 || b != 0) {
          (p->s).mode[2]++;
        }
      } else {
        if ((p->s).flags & X_FLIP) {
          a = PushoutToLeft1((p->s).coord.x + 0x1000, (p->s).coord.y + 0x1000);
        } else {
          a = PushoutToRight1((p->s).coord.x - 0x1000, (p->s).coord.y + 0x1000);
        }
        if (a == 0) {
          (p->s).mode[2]++;
        }
      }
      (p->s).work[2] += 0x10;
      (p->s).angle = (p->s).work[2];
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      (p->s).d.x = -0x2C0;
      v = (p->s).d.x;
      if ((p->s).flags & X_FLIP) {
        v = 0x2C0;
      }
      (p->s).d.x = v;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      (p->s).coord.x += (p->s).d.x;
      if ((p->s).flags & X_FLIP) {
        a = FUN_08009f6c((p->s).coord.x + 0x1000, (p->s).coord.y + 0x1000);
        b = FUN_08009f6c((p->s).coord.x - 0x1000, (p->s).coord.y + 0x1000);
      } else {
        a = FUN_08009f6c((p->s).coord.x - 0x1000, (p->s).coord.y + 0x1000);
        b = FUN_08009f6c((p->s).coord.x + 0x1000, (p->s).coord.y + 0x1000);
      }
      dy = a - (p->s).coord.y;
      if (dy < -0x1800) {
        (p->s).d.y = -0x2C0;
        (p->s).mode[2] = 1;
      } else if (dy > 0x1800 && b - (p->s).coord.y > 0x1800) {
        (p->s).d.y = 0x2C0;
        (p->s).mode[2] = 1;
      } else {
        a = FUN_08009f6c((p->s).coord.x, (p->s).coord.y + 0x1000);
        if (a - (p->s).coord.y <= 0x17FF) {
          (p->s).coord.y = a - 0x1000;
        }
      }
      (p->s).work[2] += 0x10;
      (p->s).angle = (p->s).work[2];
      UpdateMotionGraphic(&p->s);
      break;
  }
  v = (p->s).coord.x - *(s32*)((u8*)q + 0xb8);
  if ((v < -0x5800 && !((p->s).flags & X_FLIP)) || (v > 0x5800 && ((p->s).flags & X_FLIP))) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
}

void FUN_080a4f3c(struct Projectile* p);

// 0x080A598C
void FUN_080a598c(struct Projectile* p) {
  struct Entity* e = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      u32 xf;
      u8 z;
      SetDDP(&p->body, &sCollisions[1]);
      InitRotatableMotion(&p->s);
      xf = (e->flags >> 4) & 1;
      if (xf != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        u32 xf2;
        asm volatile("add %0, %1, #0" : "=&l"(xf2) : "l"(xf));
        ((p->s).spr).xflip = xf2;
        z = 0;
        xf = xf2;
      }
      {
        u8* oa = (u8*)p + 0x4a;
        u32 sh4 = xf << 4;
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      SetMotion(&p->s, MOTION(0x49, 0x01));
      (p->s).taskCol = 0x17;
      (p->s).work[2] = z;
      (p->s).work[3] = z;
      (p->s).d.y = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 a;
      s32 dy;
      {
        s32 w2 = (p->s).work[2] + 1;
        (p->s).work[2] = w2;
        a = (p->s).work[3] + w2;
      }
      (p->s).work[3] = a;
      (p->s).angle = a;
      dy = (p->s).d.y + 0x40;
      (p->s).d.y = dy;
      (p->s).coord.y += dy;
      if (PushoutToUp1((p->s).coord.x, (p->s).coord.y) < 0) {
        FUN_080a4f3c(p);
        (p->s).mode[2]++;
      }
      break;
    }
    case 2: {
      u8 k;
      u8 z2;
      SetDDP(&p->body, &sCollisions[0]);
      {
        register u8 t asm("r1");
        u8 fv;
        t = (p->s).flags;
        k = 0xFE;
        fv = k;
        fv &= t;
        asm volatile("" ::"r"(t));
        z2 = 0;
        (p->s).flags = fv;
      }
      if (*(u32*)((u8*)e + 0xc0) & 0x40) {
        (p->s).mode[1] = 8;
        (p->s).mode[2] = z2;
      }
      if (e->mode[0] > 1) {
        register u8 t asm("r1");
        u8 fv;
        t = (p->s).flags;
        fv = k;
        fv &= t;
        asm volatile("" ::"r"(t));
        fv &= 0xFD;
        (p->s).flags = fv;
        (p->body).status = z2;
        (p->body).prevStatus = z2;
        (p->body).invincibleTime = z2;
        (p->s).flags &= ~COLLIDABLE;
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

void FUN_080a4f3c(struct Projectile* p);

void FUN_080a5ac0(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      FUN_080a4f3c(p);
      (p->s).flags |= DISPLAY;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      u8 t;
      (p->s).coord.y -= (p->s).d.y;
      (p->s).d.y -= 0x40;
      (p->s).work[3] -= (p->s).work[2];
      t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = t;
      }
      (p->s).angle = (p->s).work[3];
      break;
    }
  }
}

void FUN_080a4fa4(struct Projectile* p);

// 0x080A5B28
void FUN_080a5b28(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32* r;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).d.x = ((u32)((u16)Sqrt(0x400)) << 16) >> 11;
      *(s32*)((u8*)p + 0xb4) = 0x4000;
      (p->s).mode[2]++;
    case 1:
      r = (s32*)((u8*)p + 0xb4);
      *r += (p->s).d.x;
      if (*r > 0x30000) {
        (p->s).d.x -= 0x20;
      }
      if ((p->s).d.x <= 0) {
        s32* w = (s32*)((u8*)q + 0xc0);
        *w &= ~0x80;
        *r = 0x4000;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 1;
      }
      FUN_080a4fa4(p);
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void Projectile20_Init(struct Projectile* p);
void Projectile20_Update(struct Projectile* p);
void Projectile20_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile20Routine = {
    [ENTITY_INIT] =      Projectile20_Init,
    [ENTITY_UPDATE] =    Projectile20_Update,
    [ENTITY_DIE] =       Projectile20_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a5144(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836ba50[10] = {
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
};
// clang-format on

void FUN_080a5148(struct Projectile* p);
void FUN_080a51b4(struct Projectile* p);
void FUN_080a5290(struct Projectile* p);
void FUN_080a53e8(struct Projectile* p);
void FUN_080a54f8(struct Projectile* p);
void FUN_080a569c(struct Projectile* p);
void FUN_080a57ac(struct Projectile* p);
void FUN_080a598c(struct Projectile* p);
void FUN_080a5ac0(struct Projectile* p);
void FUN_080a5b28(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836ba78[10] = {
    FUN_080a5148,
    FUN_080a51b4,
    FUN_080a5290,
    FUN_080a53e8,
    FUN_080a54f8,
    FUN_080a569c,
    FUN_080a57ac,
    FUN_080a598c,
    FUN_080a5ac0,
    FUN_080a5b28,
};
// clang-format on

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(46)},
    },
};

static const u8 sInitModes[4] = {0, 0, 0, 0};
