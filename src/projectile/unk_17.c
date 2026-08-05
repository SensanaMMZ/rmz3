#include "collision.h"
#include "global.h"
#include "story.h"
#include "motion.h"
#include "projectile.h"
#include "gfx.h"
#include "anim_loader.h"
#include "constants/motion/static.h"
#include "entity/macros.h"

struct Projectile* FUN_080a2790(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = 1;
  }
  return p;
}

struct Projectile* FUN_080a27e4(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = 2;
  }
  return p;
}

struct Projectile* FUN_080a2838(struct Entity* e, struct Coord* c1, struct Coord* c2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a3;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
    (p->s).work[1] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

static const struct Collision sCollisions[4];
void Projectile17_Update(struct Projectile* p);

void Projectile17_Init(struct Projectile* p) {
  s32 w1;
  InitNonAffineMotion(&p->s);
  {
    register s32 r0v asm("r0");
    register s32 r1v asm("r1");
    register s32 r2v asm("r2");
    register s32 r3v asm("r3");
    r1v = (p->s).flags;
    r0v = DISPLAY;
    r3v = 0;
    asm("" : "+r"(r0v), "+r"(r3v));
    r2v = r0v;
    r2v |= r1v;
    r0v = FLIPABLE;
    asm("" : "+r"(r0v));
    r2v |= r0v;
    r2v |= r3v;
    (p->s).flags = r2v;
    r1v = (p->s).work[0];
    if (r1v == 0) {
      r2v &= 0xEF;
      (p->s).flags = r2v;
      r0v = (s32)((u8*)p + 0x4c);
      *(u8*)r0v = r1v;
      r2v = (s32)((u8*)p + 0x4a);
      r1v = *(u8*)r2v;
      r0v = ~X_FLIP;
      asm("" : "+r"(r0v));
      *(u8*)r2v = r0v & r1v;
      asm volatile("");
    } else {
      r1v = 1;
      asm("" : "+r"(r1v));
      r0v = X_FLIP;
      r2v |= r0v;
      (p->s).flags = r2v;
      r0v = (s32)((u8*)p + 0x4c);
      *(u8*)r0v = r1v;
      r3v = (s32)((u8*)p + 0x4a);
      r2v = X_FLIP;
      r1v = *(u8*)r3v;
      r0v = ~X_FLIP;
      asm("" : "+r"(r0v));
      *(u8*)r3v = (r0v & r1v) | r2v;
    }
  }
  (p->s).work[2] = 0xFF;
  w1 = (p->s).work[1];
  if (w1 == 0) {
    LOAD_STATIC_GRAPHIC(SM066_PUFFY_BUBBLE);
    INIT_BODY(p, &sCollisions[0], 4, (void*)(u32)w1);
    SET_PROJECTILE_ROUTINE(&p->s, 1);
    (p->s).mode[1] = w1;
    (p->s).mode[2] = w1;
    (p->s).mode[3] = w1;
  } else if (w1 == 1) {
    register s32 z2 asm("r5");
    struct Body* body;
    {
      register s32 fl2 asm("r1");
      register s32 c4 asm("r0");
      fl2 = (p->s).flags;
      c4 = COLLIDABLE;
      z2 = 0;
      c4 |= fl2;
      (p->s).flags = c4;
    }
    body = &p->body;
    InitBody(body, &sCollisions[2], &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)z2;
    SET_PROJECTILE_ROUTINE(&p->s, 1);
    (p->s).mode[1] = w1;
    (p->s).mode[2] = z2;
    (p->s).mode[3] = z2;
  } else if (w1 == 2) {
    register s32 z3 asm("r5");
    struct Body* body;
    {
      register s32 fl2 asm("r1");
      register s32 c4 asm("r0");
      fl2 = (p->s).flags;
      c4 = COLLIDABLE;
      z3 = 0;
      c4 |= fl2;
      (p->s).flags = c4;
    }
    body = &p->body;
    InitBody(body, &sCollisions[3], &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)z3;
    {
      register s32* t asm("r2");
      t = (s32*)0x080FF080;
      (p->s).coord.x += t[(p->s).work[0] * 2];
      {
        register s32 i asm("r1");
        i = (p->s).work[0] * 8;
        t = (s32*)((u8*)t + 4);
        i += (s32)t;
        (p->s).coord.y += *(s32*)i;
      }
    }
    SET_PROJECTILE_ROUTINE(&p->s, 1);
    (p->s).mode[1] = w1;
    (p->s).mode[2] = z3;
    (p->s).mode[3] = z3;
  }
  Projectile17_Update(p);
}

static const ProjectileFunc PTR_ARRAY_0836b3b4[3];

void Projectile17_Update(struct Projectile* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  (PTR_ARRAY_0836b3b4[(p->s).mode[1]])(p);
}

void Projectile17_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

s32 PushoutToUp1(s32 x, s32 y);
s32 PushoutToDown1(s32 x, s32 y);
struct Projectile* FUN_080a27e4(struct Coord* c, u8 n);

// 0x080A2ADC
void FUN_080a2adc(struct Projectile* p) {
  struct Coord c;
  {
    register u32* st asm("r3");
    register s32 z asm("r1");
    register u32 v asm("r0");
    st = (u32*)((u8*)p + 0x8c);
    v = *st;
    z = 0x80 << 2;
    z &= v;
    if (z != 0) {
      z = 0;
      goto clr;
    }
    {
      register s32 m2 asm("r2");
      m2 = 0x00400100;
      m2 &= v;
      if (m2 != 0) {
      clr : {
        u8* a;
        *st = z;
        a = (u8*)p + 0x90;
        asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("strb %0, [%1]" ::"l"(z), "l"(a) : "memory");
      }
        {
          register u8 fl asm("r1");
          register u32 f asm("r0");
          fl = (p->s).flags;
          f = 0xfb;
          f &= fl;
          (p->s).flags = f;
        }
        SetMotion(&p->s, 0x4201);
        (p->s).mode[2] = 4;
        goto dispatch;
      }
      {
        register s32 four asm("r4");
        four = 4;
        if ((v & four) != 0) {
          u8* a;
          *st = m2;
          a = (u8*)p + 0x90;
          asm volatile("str %0, [%1]" ::"l"(m2), "l"(a) : "memory");
          a += 4;
          asm("" : "+r"(a));
          asm volatile("strb %0, [%1]" ::"l"(m2), "l"(a) : "memory");
        } else {
          register s32 t asm("r0");
          register u32 t8 asm("r1");
          t = (p->s).work[2] - 1;
          (p->s).work[2] = t;
          t8 = (u32)(t << 24) >> 24;
          if (t8 != 0) {
            goto dispatch;
          }
          {
            u8* a;
            *st = t8;
            a = (u8*)p + 0x90;
            asm volatile("str %0, [%1]" ::"l"(t8), "l"(a) : "memory");
            a += 4;
            asm("" : "+r"(a));
            asm volatile("strb %0, [%1]" ::"l"(t8), "l"(a) : "memory");
          }
        }
        {
          register u8 fl asm("r1");
          register u32 f asm("r0");
          fl = (p->s).flags;
          f = 0xfb;
          f &= fl;
          (p->s).flags = f;
        }
        SetMotion(&p->s, 0x4201);
        (p->s).mode[2] = four;
      }
    }
  }
dispatch:
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x84 << 7);
      (p->s).work[3] = 0xc;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).coord.y = ((p->s).unk_28)->coord.y + -0xA00;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[3] != 0) {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    case 2: {
      s32 tx;
      if (((p->s).flags & 0x10) == 0) {
        register s32 k2 asm("r2");
        k2 = -0x4000;
        tx = (p->s).coord.x + k2;
        asm volatile("");
      } else {
        register s32 cx3 asm("r0");
        register s32 k3 asm("r3");
        cx3 = (p->s).coord.x;
        k3 = 0x80;
        k3 <<= 7;
        asm volatile("" : "+l"(k3));
        tx = cx3 + k3;
      }
      {
        register s32 z0 asm("r1");
        (p->s).unk_coord.x = 0x4c;
        (p->s).d.x = (tx - (p->s).coord.x) / 0x4c;
        z0 = 0;
        (p->s).d.y = -0x260;
        (p->s).unk_coord.x = 0x4b;
        (p->s).work[3] = z0;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      register s32 hit asm("r4");
      s32 dy = (p->s).d.y + 0x10;
      (p->s).d.y = dy;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += dy;
      UpdateMotionGraphic(&p->s);
      hit = 0;
      {
        register s32 cy asm("r1");
        register s32 px asm("r2");
        cy = (p->s).coord.y;
        if ((p->s).d.x < 0) {
          register s32 cx5 asm("r0");
          register s32 k5 asm("r3");
          cx5 = (p->s).coord.x;
          k5 = -0xA00;
          px = cx5 + k5;
        } else {
          register s32 cx5 asm("r0");
          register s32 k5 asm("r3");
          cx5 = (p->s).coord.x;
          k5 = 0xa0;
          k5 <<= 4;
          px = cx5 + k5;
        }
        {
          u32 rv = FUN_080098a4(px, cy);
          u32 sv = rv << 16;
          u32 tv = 0xf0 << 12;
          tv &= sv;
          if ((tv >> 16) == 1) {
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
              register u8 fl asm("r1");
              register u32 f asm("r0");
              fl = (p->s).flags;
              f = 0xfb;
              f &= fl;
              (p->s).flags = f;
            }
            SetMotion(&p->s, 0x4201);
            (p->s).mode[2] = 4;
            hit = 1;
          }
        }
      }
      if (hit != 0) {
        break;
      }
      {
        register s32 cx asm("r2");
        register s32 cy asm("r0");
        register s32 k asm("r3");
        s32 r;
        cx = (p->s).coord.x;
        cy = (p->s).coord.y;
        k = 0x80;
        k <<= 3;
        r = PushoutToUp1(cx, cy + k);
        if (r != 0) {
          (p->s).coord.y += r;
          (p->s).mode[2] = 2;
        }
      }
      {
        register s32 cx asm("r2");
        register s32 cy asm("r0");
        register s32 k asm("r3");
        s32 r;
        cx = (p->s).coord.x;
        cy = (p->s).coord.y;
        k = -0x400;
        asm volatile("" : "+l"(k));
        r = PushoutToDown1(cx, cy + k);
        if (r != 0) {
          (p->s).coord.y += r;
          (p->s).d.y = -(p->s).d.y;
        }
      }
      break;
    }
    case 4: {
      register s32 one asm("r5");
      register s32 k asm("r4");
      s32 i;
      (p->s).work[2] = 0xff;
      c.x = (p->s).coord.x;
      {
        register s32 cy asm("r0");
        register s32 kk asm("r1");
        cy = (p->s).coord.y;
        kk = -0xC00;
        c.y = cy + kk;
      }
      {
        register u32 fv asm("r1");
        fv = (u32)(p->s).flags >> 4;
        one = 1;
        fv &= one;
        FUN_080a2790(&c, fv);
      }
      {
        register s32 cx asm("r0");
        cx = (p->s).coord.x;
        k = 0xc0;
        k <<= 4;
        c.x = cx + k;
      }
      c.y = (p->s).coord.y + k;
      FUN_080a2790(&c, one & ~((u32)(p->s).flags >> 4));
      {
        register s32 cx asm("r0");
        register s32 kk asm("r2");
        cx = (p->s).coord.x;
        kk = -0xC00;
        c.x = cx + kk;
      }
      c.y = (p->s).coord.y + k;
      FUN_080a2790(&c, ((p->s).flags >> 4) & one);
      i = 0;
      do {
        FUN_080a27e4(&(p->s).coord, (u8)i);
        i += 1;
      } while (i <= 4);
      SetMotion(&p->s, 0x4201);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      PlaySound(0x31);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

void FUN_080a2d9c(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x42, 4));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void FUN_080a2dec(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x4202);
      (p->s).work[2] = 0x14;
      (p->s).d.y = 0x40;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.y -= (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SetMotion(&p->s, 0x4203);
      (p->s).work[2] = 0x14;
      (p->s).d.y = 0x20;
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      (p->s).coord.y -= (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void Projectile17_Init(struct Projectile* p);
void Projectile17_Update(struct Projectile* p);
void Projectile17_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile17Routine = {
    [ENTITY_INIT] =      Projectile17_Init,
    [ENTITY_UPDATE] =    Projectile17_Update,
    [ENTITY_DIE] =       Projectile17_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a2adc(struct Projectile* p);
void FUN_080a2d9c(struct Projectile* p);
void FUN_080a2dec(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836b3b4[3] = {
    FUN_080a2adc,
    FUN_080a2d9c,
    FUN_080a2dec,
};

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};
