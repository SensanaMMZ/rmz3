#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "zero.h"

static const ProjectileFunc sUpdates1[7];
static const ProjectileFunc sUpdates2[7];
static const struct Collision sCollisions[5];
static const u8 u8_0836b0c8[6];

void Projectile13_Update(struct Projectile* p);

void FUN_0809f8ac(struct Entity* e) {
  s32 i;
  for (i = 0; i <= 3; i++) {
    struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 8;
      INIT_PROJECTILE_ROUTINE(p, 13);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).work[0] = 5;
      (p->s).work[2] = i;
      (p->s).unk_28 = e;
    }
  }
}

void FUN_0809f8fc(s32 x, s32 y, u8 angle) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = COS(angle) * 2;
    (p->s).d.y = -(SIN(angle) * 2);
  }
}

void FUN_0809f970(s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[2] = n;
    (p->s).unk_coord.x = x;
    (p->s).unk_coord.y = y;
    (p->s).coord.x = x - 0x400 + (RANDOM(RNG_0202f388) & 0x7FF);
    (p->s).coord.y = y;
  }
}

#include "entity/macros.h"

void babyelf_0809f9f0(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    (p->s).unk_28 = parent;
  }
}


void FUN_0809fa44(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[2] = n;
    (p->s).unk_coord.x = x;
    (p->s).unk_coord.y = y;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = parent;
  }
}

void FUN_0809fa9c(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).work[2] = n;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = parent;
  }
}

void nop_0809faf0(struct Projectile* p) {}

void Projectile13_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_0836b0c8[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_0809faf0);
  Projectile13_Update(p);
}

void Projectile13_Update(struct Projectile* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Projectile13_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(3, &(p->s).coord);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void nop_0809fbd8(struct Projectile* p) {}

void FUN_0809fbdc(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, sCollisions);
      (p->s).work[2] = 0x28;
      SetMotion(&p->s, MOTION(0x33, 0x08));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      EXIT_BODY(p);
      (p->s).work[2] = 0xA;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      u32 u;
      register s32 f asm("r0");
      register s32 tzp asm("r2");
      {
        register s32 w asm("r0");
        w = (p->s).work[2];
        asm("" : "+r"(w));
        u = w;
      }
      if (u > 4) {
        if (u & 1) {
          u8 fl2 = (p->s).flags;
          f = DISPLAY;
          asm("" : "+r"(f));
          f |= fl2;
        } else {
          goto off;
        }
        goto store;
      }
      if (u & 2) {
        u8 fl2 = (p->s).flags;
        f = DISPLAY;
        f |= fl2;
      } else {
      off: {
          u8 fl3 = (p->s).flags;
          f = 0xFE;
          f &= fl3;
        }
      }
    store:
      (p->s).flags = f;
      {
        register s32 t2p asm("r0");
        t2p = u - 1;
        (p->s).work[2] = t2p;
        tzp = (u8)t2p;
      }
      if (tzp == 0) {
        register u8 e1 asm("r1");
        e1 = *(volatile u8*)&(p->s).flags;
        f = 0xFE;
        f &= e1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f &= c2;
        }
        (p->s).flags = f;
        (p->body).status = tzp;
        (p->body).prevStatus = tzp;
        (p->body).invincibleTime = tzp;
        (p->s).flags &= ~COLLIDABLE;
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

u8 makeZeroSlower(struct Zero* z, u8 val);
void FUN_0809f970(s32 x, s32 y, u8 k);

// 0x0809FCFC
void FUN_0809fcfc(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[3] = 8;
      SetDDP(&p->body, (const struct Collision*)0x0836B068);
      {
        u32 r = RNG_0202f388 * 0x343FD + 0x269EC3;
        r <<= 1;
        RNG_0202f388 = r >> 1;
        SetMotion(&p->s, ((r >> 0x11) & 1) + 0x3203);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register u32* st asm("r6");
      {
        u8 w2 = (p->s).work[2];
        if (w2 <= 2) {
          s32 t = (p->s).work[3];
          if (t != 0) {
            t -= 1;
            (p->s).work[3] = t;
            if ((t << 24) == 0) {
              FUN_0809f970((p->s).unk_coord.x, (p->s).unk_coord.y, (u8)(w2 + 1));
            }
          }
        }
      }
      {
        u32* a = (u32*)((u8*)p + 0x8c);
        u32 f = *a & 4;
        asm volatile("add %0, %1, #0" : "=&l"(st) : "l"(a));
        if (f != 0) {
          struct Zero* z;
          if ((u8)makeZeroSlower(pZero2, 0) <= 0x5f) {
            z = pZero2;
            (p->s).unk_coord.x = (p->s).coord.x - (z->s).coord.x;
            (p->s).unk_coord.y = (p->s).coord.y - (z->s).coord.y;
            (p->s).mode[2]++;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      (p->s).coord.y += 0x100;
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) <= (0x80 << 6)) {
        break;
      }
      {
        register s32 f asm("r0");
        register s32 z2 asm("r2");
        register u8 e1 asm("r1");
        e1 = *(volatile u8*)&(p->s).flags;
        f = 0xFE;
        f &= e1;
        z2 = 0;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f &= c2;
        }
        (p->s).flags = f;
        *st = z2;
        (p->body).prevStatus = z2;
        (p->body).invincibleTime = z2;
        (p->s).flags &= ~COLLIDABLE;
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
    case 2: {
      register u8* a asm("r0");
      register s32 z1 asm("r1");
      a = (u8*)p + 0x8c;
      z1 = 0;
      asm volatile("str %0, [%1]" ::"l"(z1), "l"(a) : "memory");
      a += 4;
      asm("" : "+r"(a));
      asm volatile("str %0, [%1]" ::"l"(z1), "l"(a) : "memory");
      a += 4;
      asm("" : "+r"(a));
      asm volatile("strb %0, [%1]" ::"l"(z1), "l"(a) : "memory");
      (p->s).flags &= ~COLLIDABLE;
      makeZeroSlower(pZero2, 0xc);
      (p->s).work[2] = 0x80;
      (p->s).d.x = 0x18;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      struct Zero* z = pZero2;
      s32 d1;
      s32 t;
      (p->s).coord.x = (z->s).coord.x + (p->s).unk_coord.x;
      (p->s).coord.y = (z->s).coord.y + (p->s).unk_coord.y;
      d1 = (p->s).d.x - (u8)CountButtonMashing(z);
      (p->s).d.x = d1;
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0 && d1 >= 0) {
        struct Zero* z2 = pZero2;
        if ((*(u32*)((u8*)z2 + 0x8c) & (0x80 << 2)) == 0) {
          if (*(s16*)((u8*)z2 + 0xa4) != 0) {
            goto upd;
          }
        }
      }
      makeZeroFaster(pZero2, 0xc);
      (p->s).mode[2]++;
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 4:
      (p->s).work[2] = 8;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5: {
      register s32 tz asm("r2");
      {
        register s32 t2 asm("r0");
        t2 = (p->s).work[2] - 1;
        (p->s).work[2] = t2;
        tz = (u8)t2;
      }
      if (tz == 0) {
        register s32 f asm("r0");
        register u8 e1 asm("r1");
        register u8* a asm("r0");
        e1 = *(volatile u8*)&(p->s).flags;
        f = 0xFE;
        f &= e1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f &= c2;
        }
        (p->s).flags = f;
        a = (u8*)p + 0x8c;
        asm volatile("str %0, [%1]" ::"l"(tz), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("str %0, [%1]" ::"l"(tz), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("strb %0, [%1]" ::"l"(tz), "l"(a) : "memory");
        (p->s).flags &= ~COLLIDABLE;
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      {
        register s32 f2 asm("r0");
        u32 w = (p->s).work[2];
        u32 m = 1;
        asm volatile("" : "+l"(m));
        m &= w;
        if (m != 0) {
          f2 = (p->s).flags;
          f2 |= 1;
        } else {
          u8 fl = (p->s).flags;
          f2 = 0xFE;
          f2 &= fl;
        }
        (p->s).flags = f2;
      }
      {
        struct Zero* z = pZero2;
        s32 uy;
        s32 zy;
        (p->s).coord.x = (z->s).coord.x + (p->s).unk_coord.x;
        zy = (z->s).coord.y;
        uy = (p->s).unk_coord.y;
        (p->s).coord.y = zy + uy;
        (p->s).unk_coord.y = uy + 0x100;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/projectile/unk_13_p3a.inc");

s32 PushoutToUp1(s32 x, s32 y);
void FUN_080bc6ac(struct Entity* e, s32 x, s32 y, s32 speed, u8 angle);
void FUN_080bc758(s32 x, s32 y);

void FUN_080a025c(struct Projectile* p) {
  struct Entity* par = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).taskCol = 0x18;
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, 0x3401);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      (p->s).work[3] = 1;
      SetMotion(&p->s, 0x3402);
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      u8 w2 = (p->s).work[2];
      if (w2 <= 1) {
        u8 w3 = (p->s).work[3];
        if (w3 != 0) {
          s32 t = w3 - 1;
          (p->s).work[3] = t;
          if ((t << 24) == 0) {
            FUN_0809fa44(par, (p->s).unk_coord.x, (p->s).unk_coord.y, (u8)(w2 + 1));
          }
        }
      }
      (p->s).coord.y += 0x280;
      {
        s32 po = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (po < 0) {
          (p->s).coord.y += po;
          {
            u32 f = (p->s).flags & 0xFE;
            s32 z2 = 0;
            asm("" : "+r"(f));
            f &= 0xFD;
            (p->s).flags = f;
            (p->body).status = z2;
            (p->body).prevStatus = z2;
            (p->body).invincibleTime = z2;
          }
          (p->s).flags &= 0xFB;
          SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
          if ((p->s).work[2] == 0) {
            u32 ang = 0x20000000;
            s32 i = 2;
            do {
              FUN_080bc6ac(par, (p->s).coord.x, (p->s).coord.y, 0x100, ang >> 0x18);
              ang += 0x20000000;
              i--;
            } while (i >= 0);
            FUN_080bc758((p->s).coord.x, (p->s).coord.y);
          }
          FUN_0809fa9c(par, (p->s).coord.x, (p->s).coord.y, 0);
          FUN_0809fa9c(par, (p->s).coord.x, (p->s).coord.y, 1);
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080a03ac(struct Projectile* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).taskCol = 0x18;
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, 0x3403);
      (p->s).d.x = ((p->s).work[2] * 7 << 8) - 0x380;
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).coord.x += (p->s).d.x;
      {
        struct Camera* cam = &gStageRun.vm.camera;
        if (CalcFromCamera(cam, &(p->s).coord) > 0x2000) {
          register u8 e1 asm("r1");
          register s32 fp asm("r0");
          register s32 z2 asm("r2");
          e1 = (p->s).flags;
          fp = 0xFE;
          fp &= e1;
          z2 = 0;
          {
            register s32 c2 asm("r1");
            c2 = 0xFD;
            fp &= c2;
          }
          (p->s).flags = fp;
          (p->body).status = z2;
          (p->body).prevStatus = z2;
          (p->body).invincibleTime = z2;
          (p->s).flags &= ~COLLIDABLE;
          SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
  if (((p->s).unk_28)->mode[0] > 1) {
    register s32 f asm("r0");
    s32 t = (p->s).d.y + 1;
    (p->s).d.y = t;
    if (t > 0xf) {
      if ((t & 2) != 0) {
        goto fset;
      }
      goto fclear;
    }
    if ((t & 1) == 0) {
      goto fclear;
    }
  fset:
    {
      u8 fl2 = (p->s).flags;
      f = 1;
      f |= fl2;
      goto fst;
    }
  fclear:
    {
      u8 fl3 = (p->s).flags;
      f = 0xFE;
      f &= fl3;
    }
  fst:
    (p->s).flags = f;
    if ((p->s).d.y > 0x1e) {
      register u8 e1 asm("r1");
      register s32 fp asm("r0");
      register s32 z2 asm("r2");
      e1 = *(volatile u8*)&(p->s).flags;
      fp = 0xFE;
      fp &= e1;
      z2 = 0;
      {
        register s32 c2 asm("r1");
        c2 = 0xFD;
        fp &= c2;
      }
      (p->s).flags = fp;
      (p->body).status = z2;
      (p->body).prevStatus = z2;
      (p->body).invincibleTime = z2;
      (p->s).flags &= ~COLLIDABLE;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
}

INCASM("asm/projectile/unk_13_p3_b.inc");

extern struct Zero* pZero2;

// 0x080A06C0
void FUN_080a06c0(struct Projectile* p) {
  register struct Entity* par asm("sl");
  register u8* b8c asm("r6");
  register u32* b90 asm("r8");
  register u8* b94 asm("r9");
  register u32 ang asm("r5");
  register s32 i asm("r4");
  par = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      {
        register const s16* tb asm("r1");
        register s32 v asm("r0");
        const s16* bp;
        tb = (const s16*)0x0836B0D6;
        asm("" : "+r"(tb));
        bp = (const s16*)(((p->s).work[2] << 1) + (u32)tb);
        asm volatile("mov r1, #0\n\tldrsh %0, [%1, r1]" : "=l"(v) : "l"(bp) : "r1");
        (p->s).unk_coord.x = v;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).unk_coord.x - 1;
      (p->s).unk_coord.x = t;
      if (t == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      register s32 dx asm("r5");
      register s32 dy asm("r6");
      register s32 dist asm("r4");
      PlaySound(0x8C * 2);
      {
        register struct Zero* z asm("r1");
        register s32 cy asm("r0");
        z = pZero2;
        dx = (z->s).coord.x;
        dx -= (p->s).coord.x;
        cy = (p->s).coord.y;
        {
          register s32 k asm("r2");
          k = 0xC0 * 32;
          cy += k;
        }
        dy = (z->s).coord.y;
        dy -= cy;
      }
      {
        register s32 a asm("r0");
        register s32 t1 asm("r1");
        register s32 b asm("r1");
        register s32 t2 asm("r2");
        a = dx >> 8;
        asm volatile("add %0, %1, #0" : "=&l"(t1) : "l"(a));
        t1 *= a;
        asm volatile("add %0, %1, #0" : "=&l"(a) : "l"(t1));
        b = dy >> 8;
        asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(b));
        t2 *= b;
        asm volatile("add %0, %1, #0" : "=&l"(b) : "l"(t2));
        a += b;
        {
          register s32 sq asm("r0");
          sq = ((s32(*)(u32))Sqrt)(a);
          asm volatile("add %0, %1, #0" : "=&l"(dist) : "l"(sq));
        }
      }
      dist <<= 16;
      dist = (s32)(((u32)dist) >> 8);
      dx <<= 8;
      {
        register s32 q asm("r1");
        register s32 r asm("r0");
        r = dx / dist;
        q = (r << 2) + r;
        (p->s).d.x = q;
      }
      dy <<= 8;
      {
        register s32 q2 asm("r1");
        register s32 r2 asm("r0");
        r2 = dy / dist;
        q2 = (r2 << 2) + r2;
        (p->s).d.y = q2;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      register s32 cx asm("r0");
      register s32 cy2 asm("r1");
      asm volatile("ldr %0, [%2, #0x54]\n\tldr %1, [%2, #0x5c]\n\tadd %0, %0, %1\n\tstr %0, [%2, #0x54]\n\tldr %1, [%2, #0x58]\n\tldr r2, [%2, #0x60]\n\tadd %1, %1, r2\n\tstr %1, [%2, #0x58]" : "=&l"(cx), "=&l"(cy2) : "l"(p) : "r2", "memory");
      if (((u16)FUN_080098a4(cx, cy2) << 16) == 0) {
        goto upd;
      }
      b8c = (u8*)p + 0x8c;
      {
        register u32 t0 asm("r0");
        register u32 t1 asm("r1");
        asm volatile("mov %0, #0x90\n\tadd %0, %0, %1" : "=&l"(t0) : "l"(p));
        b90 = (u32*)t0;
        asm volatile("mov %0, #0x94\n\tadd %0, %0, %1" : "=&l"(t1) : "l"(p));
        b94 = (u8*)t1;
      }
      ang = 0x80 << 0x16;
      i = 2;
      do {
        register u32 st asm("r2");
        ((void (*)(struct Entity*, s32, s32, s32, s32))FUN_080bc6ac)(par, (p->s).coord.x, (p->s).coord.y, 0x80 * 2, ang >> 0x18);
        asm volatile("mov %0, #0x80\n\tlsl %0, %0, #0x16" : "=l"(st));
        ang += st;
        i--;
      } while (i >= 0);
      i = 3;
      {
        register u32 f asm("r0");
        register s32 z2 asm("r2");
        {
          register u32 fl asm("r1");
          fl = (p->s).flags;
          f = 0xFE;
          f &= fl;
        }
        z2 = 0;
        asm("" : "+r"(f));
        f &= 0xFD;
        (p->s).flags = f;
        *(u32*)b8c = z2;
        *b90 = z2;
        asm volatile("mov r1, r9\n\tstrb %0, [r1]" :: "l"(z2), "r"(b94) : "r1", "memory");
      }
      (p->s).flags &= 0xFB;
      {
        register u32 tbl asm("r1");
        EntityFunc** rt;
        tbl = (u32)gProjectileFnTable;
        asm("" : "+r"(tbl));
        rt = (EntityFunc**)((((p->s).id) << 2) + tbl);
        *(u32*)((p->s).mode) = i;
        (p->s).onUpdate = (void*)(*rt)[3];
      }
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
  {
    register u32 md asm("r0");
    asm volatile("mov r2, r10\n\tldrb %0, [r2, #0xc]" : "=l"(md) : "r"(par) : "r2");
    if (md <= 1) {
      return;
    }
  }
  b8c = (u8*)p + 0x8c;
  {
    register u32 u0 asm("r0");
    register u32 u1 asm("r1");
    asm volatile("mov %0, #0x90\n\tadd %0, %0, %1" : "=&l"(u0) : "l"(p));
    b90 = (u32*)u0;
    asm volatile("mov %0, #0x94\n\tadd %0, %0, %1" : "=&l"(u1) : "l"(p));
    b94 = (u8*)u1;
  }
  ang = 0x80 << 0x16;
  i = 3;
  do {
    register u32 st2 asm("r2");
    ((void (*)(struct Entity*, s32, s32, s32, s32))FUN_080bc6ac)(par, (p->s).coord.x, (p->s).coord.y, 0x80 * 2, ang >> 0x18);
    asm volatile("mov %0, #0x80\n\tlsl %0, %0, #0x17" : "=l"(st2));
    ang += st2;
    i--;
  } while (i >= 0);
  {
    register u32 f2 asm("r0");
    register s32 z3 asm("r2");
    {
      register u32 fl2 asm("r1");
      fl2 = (p->s).flags;
      f2 = 0xFE;
      f2 &= fl2;
    }
    z3 = 0;
    asm("" : "+r"(f2));
    f2 &= 0xFD;
    (p->s).flags = f2;
    *(u32*)b8c = z3;
    *b90 = z3;
    asm volatile("mov r1, r9\n\tstrb %0, [r1]" :: "l"(z3), "r"(b94) : "r1", "memory");
  }
  (p->s).flags &= 0xFB;
  SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
}


void Projectile13_Init(struct Projectile* p);
void Projectile13_Update(struct Projectile* p);
void Projectile13_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile13Routine = {
    [ENTITY_INIT] =      Projectile13_Init,
    [ENTITY_UPDATE] =    Projectile13_Update,
    [ENTITY_DIE] =       Projectile13_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_0809fbd8(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates1[7] = {
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
};
// clang-format on

// --------------------------------------------

void FUN_0809fbdc(struct Projectile* p);
void FUN_0809fcfc(struct Projectile* p);
void FUN_0809ff74(struct Projectile* p);
void FUN_080a025c(struct Projectile* p);
void FUN_080a03ac(struct Projectile* p);
void FUN_080a04d4(struct Projectile* p);
void FUN_080a06c0(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates2[7] = {
    FUN_0809fbdc,
    FUN_0809fcfc,
    FUN_0809ff74,
    FUN_080a025c,
    FUN_080a03ac,
    FUN_080a04d4,
    FUN_080a06c0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};

static const u8 u8_0836b0c8[6] = {0, 1, 2, 3, 4, 5};

static const motion_t sMotions[4] = {
    MOTION(0x30, 0x00),
    MOTION(0x20, 0x00),
    MOTION(0xE0, 0x00),
    MOTION(0xD0, 0x00),
};

static const s16 s16_ARRAY_0836b0d6[4] = {
    0x30,
    0x90,
    0xC0,
    0x60,
};
