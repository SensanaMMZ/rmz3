#include "collision.h"
#include "global.h"
#include "stagerun.h"
#include "projectile.h"

static const ProjectileFunc* const sUpdates[5];

struct Projectile* createBat(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    p->work[1] = a2;
    p->work[2] = a3;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* createEchoWave(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a14dc(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a1538(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a1594(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

static const struct Collision sCollisions[9];
void Projectile15_Update(struct Projectile* p);

void Projectile15_Init(struct Projectile* p) {
  s32 z4;
  (p->s).work[2] = 0xFF;
  {
    register s32 w0 asm("r5");
    w0 = (p->s).work[0];
    if (w0 == 0) {
      struct Body* body;
      InitNonAffineMotion(&p->s);
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[0], &(p->s).coord, 4);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)(u32)w0;
    } else if (w0 == 1) {
      struct Body* body;
      s32 z5;
      InitNonAffineMotion(&p->s);
      z5 = 0;
      (p->s).work[2] = z5;
      *(u32*)((u8*)p + 0xbc) = z5;
      InitNonAffineMotion(&p->s);
      (p->s).angle = z5;
      ((p->s).spr).mag.x = 0x100;
      ((p->s).spr).mag.y = 0x100;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[5], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    } else if (w0 == 2) {
      struct Body* body;
      s32 z5;
      InitNonAffineMotion(&p->s);
      {
        register u8 f0 asm("r1");
        register s32 d4 asm("r0");
        f0 = (p->s).flags;
        d4 = COLLIDABLE;
        z5 = 0;
        d4 |= f0;
        (p->s).flags = d4;
      }
      body = &p->body;
      InitBody(body, &sCollisions[2], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    } else if (w0 == 3) {
      struct Body* body;
      s32 z5;
      InitScalerotMotion1(&p->s);
      {
        u8* aa = (u8*)p + 0x24;
        z5 = 0;
        *aa = z5;
      }
      ((p->s).spr).mag.x = 0x100;
      ((p->s).spr).mag.y = 0x100;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[3], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    } else if (w0 == 4) {
      struct Body* body;
      s32 z5;
      InitNonAffineMotion(&p->s);
      {
        register u8 f0 asm("r1");
        register s32 d4 asm("r0");
        f0 = (p->s).flags;
        d4 = COLLIDABLE;
        z5 = 0;
        d4 |= f0;
        (p->s).flags = d4;
      }
      body = &p->body;
      InitBody(body, &sCollisions[3], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    }
  }
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    z4 = 0;
    d0 |= f0;
    d0 |= FLIPABLE;
    (p->s).flags = d0;
  }
  ResetDynamicMotion(&p->s);
  {
    u32 tb = (u32)gProjectileFnTable;
    const ProjectileRoutine** ta = (const ProjectileRoutine**)(tb + (p->s).id * 4);
    s32 one = 1;
    *(u32*)&(p->s).mode[0] = one;
    (p->s).onUpdate = (void*)(**ta)[ENTITY_UPDATE];
    (p->s).mode[1] = one;
  }
  (p->s).mode[2] = z4;
  (p->s).mode[3] = z4;
  Projectile15_Update(p);
}

void Projectile15_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]][(p->s).mode[1]])(p);
}

void Projectile15_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080a176c(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

struct Entity* CreateSmoke(u8 kind, struct Coord* c);
void FUN_080bddcc(struct Coord* c, s32 a1, s32 m, s32 a3);

// 0x080A1778
void FUN_080a1778(struct Projectile* p) {
  struct Coord c;
  if (((p->s).unk_28)->mode[0] > 1) {
    CreateSmoke(2, &(p->s).coord);
    goto die;
  }
  if ((*(u32*)((u8*)p + 0x8c) & (0x80 << 2)) != 0) {
    register s32 a asm("r4");
    {
      u32 v = RNG_0202f388;
      u32 r = v * 0x343FD;
      r += 0x269EC3;
      r <<= 1;
      RNG_0202f388 = r >> 1;
      a = (r >> 0x11) & 3;
    }
    c = (p->s).coord;
    CreateSmoke(2, &c);
    {
      register s32 m asm("r5");
      m = 0xAA02;
      FUN_080bddcc(&c, 0, m, a);
      FUN_080bddcc(&c, 1, m, a);
    }
    PlaySound(0x2a);
    goto die;
  }
  {
    s32 t = (p->s).work[2] - 1;
    (p->s).work[2] = t;
    if ((t << 24) != 0) {
      goto body;
    }
  }
die:
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  return;
body:
  switch ((p->s).mode[2]) {
    case 0: {
      register u8* b6 asm("r5");
      register s32 sp0 asm("r0");
      s32 dx;
      s32 st;
      {
        u8 k;
        (p->s).work[2] = 0x78;
        SetMotion(&p->s, 0xaa << 8);
        {
          register u8* b0 asm("r0");
          b0 = (u8*)p + 0xb6;
          k = *b0;
          asm volatile("add %0, %1, #0" : "=&l"(b6) : "l"(b0));
        }
        if (k == 0) {
          (p->s).work[3] = 0x12;
          sp0 = 0x80 << 7;
        } else if (k == 1) {
          (p->s).work[3] = 0x1a;
          sp0 = 0xc0 << 7;
        } else if (k == 2) {
          (p->s).work[3] = 0x22;
          sp0 = 0x80 << 8;
        } else {
          (p->s).work[3] = 0x2a;
          sp0 = 0xa0 << 8;
        }
        (p->s).unk_coord.x = sp0;
      }
      {
        register s32 bit asm("r4");
        register u32 v asm("r2");
        {
          register u8 ef asm("r1");
          register u32 t0 asm("r0");
          ef = ((p->s).unk_28)->flags;
          bit = 0x10;
          t0 = bit;
          t0 &= ef;
          t0 <<= 24;
          v = t0 >> 24;
        }
        if (v == 0) {
          u8* oa;
          s32 m11;
          dx = (p->s).coord.x - (p->s).unk_coord.x;
          {
            u8 fl = (p->s).flags;
            u32 f = 0xef;
            f &= fl;
            (p->s).flags = f;
          }
          *((u8*)p + 0x4c) = v;
          oa = (u8*)p + 0x4a;
          {
            register s32 ov asm("r1");
            ov = *oa;
            m11 = -0x11;
            m11 &= ov;
          }
          *oa = m11;
        } else {
          u8* oa;
          s32 m11;
          dx = (p->s).coord.x + (p->s).unk_coord.x;
          v = 1;
          {
            u8 fl = (p->s).flags;
            u32 f = fl;
            f |= 0x10;
            (p->s).flags = f;
          }
          *((u8*)p + 0x4c) = v;
          oa = (u8*)p + 0x4a;
          {
            register s32 ov asm("r1");
            ov = *oa;
            m11 = -0x11;
            m11 &= ov;
          }
          *oa = m11 | bit;
        }
      }
      (p->s).d.x = (dx - (p->s).coord.x) / (p->s).work[3];
      {
        register s32 kh asm("r0");
        register s32 w3 asm("r3");
        register s32 w2c asm("r2");
        kh = *b6;
        w3 = (p->s).work[3];
        if (kh == 0) {
          kh = 0x4c;
        } else if (kh == 1) {
          kh = 0x38;
        } else if (kh == 2) {
          kh = 0x26;
        } else {
          kh = 0x14;
        }
        (p->s).unk_coord.y = kh;
        {
          register s32 hv asm("r0");
          s32 half;
          hv = (s32)(*(volatile s32*)&(p->s).unk_coord.y << 8) >> 8;
          asm volatile("add %0, %1, #0" : "=&l"(w2c) : "l"(w3));
          half = (w2c + 1) >> 1;
          half *= w2c;
          hv *= half;
          st = hv;
        }
        {
          register s32 k2 asm("r1");
          register s32 q asm("r0");
          k2 = *((u8*)p + 0xb5);
          if (k2 == 0) {
            q = st / w2c;
            {
              k2 = q << 2;
              k2 += q;
              k2 <<= 2;
              k2 -= q;
              k2 <<= 4;
              asm volatile("");
            }
          } else if (k2 == 1) {
            q = st / w2c;
            {
              k2 = q << 1;
              k2 += q;
              k2 <<= 3;
              k2 -= q;
              k2 <<= 4;
            }
          } else if (k2 == 2) {
            q = st / w2c;
            {
              k2 = q << 3;
              k2 -= q;
              k2 <<= 2;
              k2 += q;
              k2 <<= 4;
            }
          } else {
            q = st / w3;
            {
              k2 = q << 2;
              k2 += q;
              k2 <<= 2;
              k2 -= q;
              k2 <<= 5;
            }
          }
          (p->s).d.y = k2 >> 8;
        }
      }
      (p->s).work[3]--;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 dy;
      dy = (p->s).d.y + ((s32)((-(p->s).unk_coord.y) << 8) >> 8);
      (p->s).d.y = dy;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += dy;
      if ((p->s).work[3] != 0) {
        (p->s).work[3]--;
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 2:
      SetMotion(&p->s, 0xAA01);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s32 dy;
      dy = (p->s).d.y + ((s32)((-(p->s).unk_coord.y) << 8) >> 8);
      (p->s).d.y = dy;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += dy;
      if ((p->s).work[3] != 0) {
        (p->s).work[3]--;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080a1a10(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

INCASM("asm/projectile/hellbat_p2_p1_p2.inc");

void FUN_080a1f10(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

void FUN_080a1f1c(struct Projectile* p) {
  s32 v, a, hit;
  if (((p->s).unk_28)->mode[0] <= 1) {
    if (--(p->s).work[2] == 0) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      return;
    }
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 t asm("r0");
      (p->s).unk_coord.x = 0;
      if ((((p->s).unk_28)->flags & 0x10) == 0) {
        t = -0x12;
      } else {
        t = 0x12;
      }
      (p->s).d.x = t;
    }
      (p->s).work[2] = 0xC8;
      SetMotion(&p->s, MOTION(0xA9, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      v = (p->s).unk_coord.x + (p->s).d.x;
      (p->s).unk_coord.x = v;
      a = v;
      if (v < 0) {
        a = -v;
      }
      if (a > 0x300) {
        (p->s).unk_coord.x = v - (p->s).d.x;
      }
      (p->s).coord.x += (p->s).unk_coord.x;
      if (((p->s).unk_28)->mode[0] > 1) {
        if ((p->s).unk_coord.x > 0) {
          hit = PushoutToLeft1((p->s).coord.x, (p->s).coord.y);
        } else {
          hit = PushoutToRight1((p->s).coord.x, (p->s).coord.y);
        }
        if (hit != 0) {
          SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        }
      } else {
        if ((p->s).unk_coord.x > 0) {
          hit = PushoutToLeft1((p->s).coord.x, (p->s).coord.y);
        } else {
          hit = PushoutToRight1((p->s).coord.x, (p->s).coord.y);
        }
        if (hit != 0) {
          (p->s).coord.x += hit;
          (p->s).unk_coord.x = -(p->s).unk_coord.x;
          (p->s).d.x = -(p->s).d.x;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_080a2020(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

s32 PushoutToUp1(s32 x, s32 y);
s32 PushoutToLeft1(s32 x, s32 y);
s32 PushoutToRight1(s32 x, s32 y);
struct VFX* createHellbatElectricBeam(struct Entity* e, struct Coord* c, u8 a2, u8 a3);

// 0x080A202C
void FUN_080a202c(struct Projectile* p) {
  struct Coord c1;
  struct Coord c2;
  if (((p->s).unk_28)->mode[0] > 1) {
    register u8* a asm("r0");
    register s32 z asm("r1");
    a = (u8*)p + 0x8c;
    z = 0;
    asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
    a += 4;
    asm("" : "+r"(a));
    asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
    a += 4;
    asm("" : "+r"(a));
    asm volatile("strb %0, [%1]" ::"l"(z), "l"(a) : "memory");
    {
      u8 fl = (p->s).flags;
      u32 f = 0xfb;
      f &= fl;
      (p->s).flags = f;
    }
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register u8 d5 asm("r2");
      d5 = *((u8*)p + 0xb5);
      if (d5 == 1) {
        u8 fl = (p->s).flags;
        u32 f = 0xfe;
        f &= fl;
        (p->s).flags = f;
        (p->s).work[3] = d5;
        (p->s).mode[2] = 3;
        break;
      }
      SetMotion(&p->s, 0xA903);
      {
        register s32 one asm("r2");
        register s32 z asm("r4");
        u8* yf;
        u8* oa;
        s32 ov;
        s32 m21;
        one = 1;
        {
          u8 fl = (p->s).flags;
          u32 f = 0x20;
          f |= fl;
          (p->s).flags = f;
        }
        yf = (u8*)p + 0x4d;
        z = 0;
        *yf = one;
        oa = (u8*)p + 0x4a;
        one = 0x20;
        ov = *oa;
        m21 = -0x21;
        m21 &= ov;
        *oa = m21 | one;
        UpdateMotionGraphic(&p->s);
        (p->s).coord.x += -0x100;
        (p->s).d.y = 0xe0 << 2;
        (p->s).d.x = z;
      }
      goto inc;
    }
    case 1: {
      s32 r;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y + (0x80 << 5));
      if (r == 0) {
        break;
      }
      (p->s).coord.y += r;
      c1.x = (p->s).coord.x;
      c1.y = (p->s).coord.y;
      createHellbatElectricBeam(&p->s, &c1, 0, 1);
      (p->s).work[3] = 0;
      (p->s).work[2] = 1;
      {
        u8 fl = (p->s).flags;
        u32 f = 0xfe;
        f &= fl;
        (p->s).flags = f;
      }
      goto inc;
    }
    case 2:
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      c2.x = (p->s).coord.x;
      c2.y = (p->s).coord.y;
      FUN_080a1538((p->s).unk_28, &c2, 1);
      {
        u8 fl = (p->s).flags;
        u32 f = 1;
        f |= fl;
        (p->s).flags = f;
      }
      goto inc;
    case 3: {
      register s32 z asm("r4");
      SetMotion(&p->s, 0xA905);
      SetDDP(&p->body, (const struct Collision*)0x0836B2C4);
      {
        register s32 zz asm("r2");
        u8* yf;
        u8* oa;
        s32 ov;
        s32 m21;
        zz = 0;
        {
          u8 fl = (p->s).flags;
          u32 f = 0xdf;
          f &= fl;
          (p->s).flags = f;
        }
        yf = (u8*)p + 0x4d;
        *yf = zz;
        oa = (u8*)p + 0x4a;
        ov = *oa;
        m21 = -0x21;
        m21 &= ov;
        *oa = m21;
      }
      if ((p->s).work[3] == 1) {
        (p->s).d.x = 0xc0 << 2;
      } else {
        (p->s).d.x = -0x300;
      }
      {
        u8 fl = (p->s).flags;
        u32 f = 1;
        z = 0;
        f |= fl;
        (p->s).flags = f;
      }
      {
        register s32 cx4 asm("r0");
        register s32 cy4 asm("r1");
        register s32 k4 asm("r2");
        cx4 = (p->s).coord.x;
        cy4 = (p->s).coord.y;
        k4 = -0x400;
        cy4 += k4;
        (p->s).coord.y = FUN_08009f6c(cx4, cy4);
      }
      (p->s).unk_coord.x = z;
      (p->s).work[2] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 4: {
      s32 cx = (p->s).coord.x;
      s32 dx = (p->s).d.x;
      s32 acc;
      s32 r;
      (p->s).coord.x = cx + dx;
      {
        register s32 a0 asm("r0");
        register s32 a1 asm("r1");
        a0 = (p->s).unk_coord.x + dx;
        (p->s).unk_coord.x = a0;
        asm volatile("add %0, %1, #0" : "=&l"(a1) : "l"(a0));
        if (a1 < 0) {
          a1 = -a1;
        }
        acc = a1;
      }
      if (acc > (0xa0 << 5)) {
        if ((p->s).work[2] == 0) {
          struct Projectile* q;
          (p->s).work[2] = 1;
          q = FUN_080a1594(&p->s, &(p->s).coord, 0);
          (q->s).d.x = (p->s).d.x;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[3] == 1) {
        r = PushoutToLeft1((p->s).coord.x + (0x80 << 3), (p->s).coord.y);
      } else {
        r = PushoutToRight1((p->s).coord.x + -0x400, (p->s).coord.y);
      }
      if (r == 0) {
        break;
      }
      (p->s).coord.x += r;
      (p->s).d.y = -0x300;
      goto inc;
    }
    case 5: {
      register s32 s asm("r2");
      s32 cy;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      s = 0;
      {
        const struct Camera* cam = &gStageRun.vm.camera;
        s32 lim = cam->viewport.y + -0x5000;
        cy = (p->s).coord.y;
        if (cy < lim) {
          s = 1;
        }
      }
      if (0) {
        s = 1;
      }
      if (s == 0) {
        break;
      }
      {
        register s32 ny asm("r0");
        ny = cy + s;
        (p->s).coord.y = ny;
      }
      (p->s).unk_coord.x = 0xff;
      {
        register u8* a asm("r0");
        register s32 z asm("r1");
        a = (u8*)p + 0x8c;
        z = 0;
        asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("strb %0, [%1]" ::"l"(z), "l"(a) : "memory");
      }
      {
        u8 fl = (p->s).flags;
        u32 f = 0xfb;
        f &= fl;
        (p->s).flags = f;
      }
    inc:
      (p->s).mode[2]++;
      break;
    }
    case 6: {
      s32 v;
      UpdateMotionGraphic(&p->s);
      {
        register u16* m asm("r1");
        register s32 v0 asm("r0");
        v0 = *(volatile s32*)&(p->s).unk_coord.x;
        m = (u16*)((u8*)p + 0x50);
        *m = v0;
        v0 = *(volatile s32*)&(p->s).unk_coord.x;
        m = (u16*)((u8*)m + 2);
        asm("" : "+r"(m));
        *m = v0;
      }
      v = *(volatile s32*)&(p->s).unk_coord.x;
      if (v > 0) {
        (p->s).unk_coord.x = v - 0x20;
      }
      if ((p->s).unk_coord.x > 0x20) {
        break;
      }
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
    }
  }
}

void FUN_080a22ec(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

void FUN_080a22f8(struct Projectile* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0:
        (p->s).flags |= 1;
        SetMotion(&p->s, 0xA905);
        SetDDP(&p->body, &sCollisions[4]);
        (p->s).flags &= 0xDF;
        *((u8*)p + 0x4d) = m;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m21 = -0x21;
          m21 &= ov;
          *oa = m21;
        }
        if ((p->s).d.x > 0) {
          (p->s).coord.x += -0x1400;
        } else {
          (p->s).coord.x += 0x1400;
        }
        (p->s).unk_coord.x = 0;
        (p->s).work[3] = 0;
        (p->s).mode[2]++;
        // fallthrough
      case 1: {
        (p->s).coord.x += (p->s).d.x;
        {
          s32 acc = (p->s).unk_coord.x + (p->s).d.x;
          (p->s).unk_coord.x = acc;
          if (*((u8*)p + 0xb5) == 0) {
            s32 a = acc;
            if (a < 0) {
              a = -a;
            }
            if (a > 0x1400) {
              if ((p->s).work[3] == 0) {
                struct Projectile* q;
                (p->s).work[3] = 1;
                q = FUN_080a1594(&p->s, &(p->s).coord, 1);
                (q->s).d.x = (p->s).d.x;
              }
            }
          }
        }
        UpdateMotionGraphic(&p->s);
        {
          s32 push;
          if ((p->s).d.x > 0) {
            push = PushoutToLeft1((p->s).coord.x + 0x400, (p->s).coord.y);
          } else {
            push = PushoutToRight1((p->s).coord.x - 0x400, (p->s).coord.y);
          }
          if (push != 0) {
            (p->s).coord.x += push;
            (p->s).d.y = -0x300;
            (p->s).mode[2]++;
          }
        }
        break;
      }
      case 2:
        (p->s).coord.y += (p->s).d.y;
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

void Projectile15_Init(struct Projectile* p);
void Projectile15_Update(struct Projectile* p);
void Projectile15_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gHellbatProjectileRoutine = {
    [ENTITY_INIT] =      Projectile15_Init,
    [ENTITY_UPDATE] =    Projectile15_Update,
    [ENTITY_DIE] =       Projectile15_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a176c(struct Projectile* p);
void FUN_080a1778(struct Projectile* p);

static const ProjectileFunc sUpdates1[2] = {
    FUN_080a176c,
    FUN_080a1778,
};

void FUN_080a1a10(struct Projectile* p);
void FUN_080a1a1c(struct Projectile* p);

static const ProjectileFunc sUpdates2[2] = {
    FUN_080a1a10,
    FUN_080a1a1c,
};

void FUN_080a1f10(struct Projectile* p);
void FUN_080a1f1c(struct Projectile* p);

static const ProjectileFunc sUpdates3[2] = {
    FUN_080a1f10,
    FUN_080a1f1c,
};

void FUN_080a2020(struct Projectile* p);
void FUN_080a202c(struct Projectile* p);

static const ProjectileFunc sUpdates4[2] = {
    FUN_080a2020,
    FUN_080a202c,
};

void FUN_080a22ec(struct Projectile* p);
void FUN_080a22f8(struct Projectile* p);

static const ProjectileFunc sUpdates5[2] = {
    FUN_080a22ec,
    FUN_080a22f8,
};

// clang-format off
static const ProjectileFunc*const sUpdates[5] = {
    sUpdates1,
    sUpdates2,
    sUpdates3,
    sUpdates4,
    sUpdates5,
};
// clang-format on

static const struct Collision sCollisions[9] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(0), -PIXEL(2), PIXEL(20), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(2), PIXEL(20), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      element : ELEMENT_THUNDER,
      remaining : 0,
      layer : 0x00000002,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(11), PIXEL(30)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(10)},
    },
};
