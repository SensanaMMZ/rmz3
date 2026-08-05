#include "boss.h"
#include "collision.h"
#include "global.h"
#include "zero.h"
#include "physics.h"
#include "motion.h"
#include "physics.h"
#include "script.h"
#include "stagerun.h"

static const struct Collision sCollisions[];

void Cubit_Init(struct Boss* p);
void Cubit_Update(struct Boss* p);
void Cubit_Die(struct Boss* p);

// clang-format off
const BossRoutine gCubitRoutine = {
    [ENTITY_INIT] =      Cubit_Init,
    [ENTITY_UPDATE] =    Cubit_Update,
    [ENTITY_DIE] =       Cubit_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

struct Boss* CreateCubit(struct Coord* c, u8 n) {
  struct Boss* p = (struct Boss*)AllocEntityFirst(gBossHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_BOSS_ROUTINE(p, BOSS_CUBIT);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

static const BossFunc sDeads[2];

void FUN_08054530(struct Body* body, struct Coord* c1, struct Coord* c2);

void Cubit_Init(struct Boss* p) {
  s32 z7;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register u8 f1 asm("r1");
    register s32 fp asm("r0");
    f1 = (p->s).flags;
    fp = 0xFE;
    fp &= f1;
    z7 = 0;
    {
      register s32 c2v asm("r1");
      c2v = 2;
      fp |= c2v;
    }
    (p->s).flags = fp;
  }
  ((p->s).spr).xflip = z7;
  {
    u8* a = (u8*)p + 0x4a;
    register u8 b asm("r1");
    s32 msk;
    b = *a;
    msk = -0x11;
    msk &= b;
    *a = msk;
  }
  (p->s).flags &= 0xEF;
  ResetBossBody(p, sCollisions, 0x40);
  {
    register void* fv asm("r1");
    register u8* bb asm("r0");
    fv = (void*)FUN_08054530;
    bb = (u8*)p + 0x74;
    *(void**)(bb + 0x24) = fv;
    bb += 0x40;
    *bb = z7;
  }
  {
    u8* b5 = (u8*)p + 0xb5;
    *b5 = 0xFF;
    b5 += 1;
    *b5 = 0xFF;
  }
  {
    u8* c0 = (u8*)p + 0xc0;
    *(s32*)c0 = z7;
    c0 -= 9;
    *c0 = z7;
    c0 += 0x11;
    *c0 = z7;
    c0 += 4;
    *(s32*)c0 = z7;
  }
  {
    s32 g;
    {
      register u32 kc asm("r0");
      s32 cy;
      s32 ya;
      cy = (p->s).coord.y;
      kc = (u32)-0x4000;
      asm("" : "+r"(kc));
      ya = cy + kc;
      g = FUN_08009f6c((p->s).coord.x, ya);
    }
    (p->s).coord.y = g;
    *(s32*)((u8*)p + 0xb8) = g + -0x7C00;
    {
      s32 L;
      s32 R;
      s32 w;
      {
        register s32 x0 asm("r0");
        register u32 kc2 asm("r1");
        x0 = (p->s).coord.x;
        kc2 = (u32)-0x7400;
        asm("" : "+r"(kc2));
        g += kc2;
        L = FUN_0800a22c(x0, g);
      }
      R = FUN_0800a31c((p->s).coord.x, g);
      *(s32*)((u8*)p + 0xbc) = R;
      w = (L - R) / 3;
      {
        register volatile s32* dp asm("r2");
        s32 t2;
        dp = (volatile s32*)((u8*)p + 0xd4);
        R += w >> 1;
        *dp = R;
        asm("" : "+r"(dp));
        dp += 1;
        t2 = R + w;
        *dp = t2;
        asm("" : "+r"(dp));
        dp += 1;
        R += w << 1;
        *dp = R;
      }
      *(s32*)((u8*)p + 0xe0) = w;
    }
  }
  *((u8*)p + 0xca) = z7;
  if ((p->s).work[0] == 0) {
    SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = z7;
  } else {
    SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 3;
  }
  (p->s).mode[2] = z7;
  (p->s).mode[3] = z7;
  {
    u32 zz = 0;
    asm("" : "+r"(zz));
    (p->s).work[1] = zz;
  }
  Cubit_Update(p);
}


static const BossFunc sUpdates1[12];
static const BossFunc sUpdates2[12];
bool8 cubit_080544c0(struct Boss* p);

void Cubit_Update(struct Boss* p) {
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    if (*(s16*)((u8*)p + 0xa4) != 0) {
      goto alive;
    }
  }
  if (gStageRun.missionStatus & 8) {
    goto alive;
  }
  SET_BOSS_ROUTINE(p, ENTITY_DIE);
  PlaySound(0xd2);
  if ((p->body).status & 0x00010000) {
    (p->s).mode[3] = 1;
  } else {
    (p->s).mode[3] = 0;
  }
  Cubit_Die(p);
  return;

alive:
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
  cubit_080544c0(p);
}

void Cubit_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

// 0x080527FC
void cubitDeath0(struct Boss* p0) {
  register struct Boss* p asm("r6");
  p = p0;
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 one asm("r4");
      s32 z;
      register s32 z5 asm("r5");
      {
        struct StageRun* sr = &gStageRun;
        u16 ms = sr->missionStatus;
        s32 t;
        one = 1;
        asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one));
        t &= ms;
        if (t != 0) {
          u8 av = sr->vm.active;
          s32 t2;
          asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(one));
          t2 &= av;
          if (t2 == 0) {
            {
              register s32 mk asm("r0");
              register s32 k10 asm("r1");
              mk = 0xFFFE;
              mk &= ms;
              k10 = 0x10;
              mk |= k10;
              sr->missionStatus = mk;
            }
          }
        }
      }
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      {
        u8* ap = (u8*)p + 0x24;
        asm("" : "+r"(ap));
        z = 0;
        *ap = z;
      }
      {
        register u16* mg asm("r1");
        register s32 mv asm("r0");
        mg = (u16*)((u8*)p + 0x50);
        asm("" : "+r"(mg));
        z5 = 0;
        mv = 0x100;
        *mg = mv;
        asm("" : "+r"(mg));
        mg = (u16*)((u8*)mg + 2);
        asm("" : "+r"(mg));
        *mg = mv;
      }
      SetMotion(&p->s, 0xB01E);
      UpdateMotionGraphic(&p->s);
      {
        u8* a = (u8*)p + 0x8c;
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z5;
      }
      (p->s).flags &= 0xFB;
      {
        s32* dp = (s32*)((u8*)p + 0x5c);
        dp[1] = z;
        (p->s).d.x = z;
      }
      (p->s).work[2] = 1;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      s32 w = (p->s).work[2];
      if (w == 0) {
        break;
      }
      w--;
      (p->s).work[2] = w;
      if ((w << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      u8 z2 = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z2;
      break;
    }
  }
}

struct Entity* FUN_080b2b40(u8 kind, struct Coord* c, s32 r2, u8 r3);
void FUN_0809c3b4(struct Entity* e, struct Coord* c, motion_t m, u8 dir);
struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);

// 0x080528C8
void cubitDeath1(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32* st;
      (p->s).angle = 0;
      {
        register u16* m asm("r0");
        u16 v;
        m = (u16*)((u8*)p + 0x50);
        asm volatile("" : "+l"(m));
        v = 0x80 << 1;
        *m = v;
        m += 1;
        asm("" : "+r"(m));
        *m = v;
      }
      SetMotion(&p->s, 0xB01E);
      {
        register u32* sp2 asm("r2");
        u32 f;
        sp2 = (u32*)((u8*)p + 0x8c);
        st = sp2;
        f = *st & (0x80 << 2);
        if (f == 0) {
          if (*(s16*)((u8*)p + 0xa4) != 0) {
            goto ten;
          }
        }
        if ((gStageRun.missionStatus & 8) != 0) {
          goto ten;
        }
        {
          u8 m3 = (p->s).mode[3];
          if (m3 == 1) {
            (p->s).mode[2] = m3;
            goto setm;
          }
        }
      ten:
        (p->s).mode[2] = 0xA;
        goto setm;
      }
    setm: {
      register s32 z asm("r1");
      register u8* a2 asm("r0");
      z = 0;
      *st = z;
      a2 = (u8*)p + 0x90;
      asm volatile("str %0, [%1]" ::"l"(z), "l"(a2) : "memory");
      a2 += 4;
      asm("" : "+r"(a2));
      asm volatile("strb %0, [%1]" ::"l"(z), "l"(a2) : "memory");
      {
        register u32 f2 asm("r0");
        register u8 fl asm("r2");
        fl = (p->s).flags;
        f2 = 0xFB;
        f2 &= fl;
        (p->s).flags = f2;
      }
      {
        s32* d = (s32*)((u8*)p + 0x5c);
        d[1] = z;
        (p->s).d.x = z;
      }
    }
      FALLTHROUGH;
    }
    case 1:
    case 10:
      UpdateMotionGraphic(&p->s);
      goto inc;
    case 2: {
      struct Coord c;
      s32 cx;
      s32 cy;
      (p->s).d.y = 0;
      cx = (p->s).coord.x;
      c.x = cx;
      cy = (p->s).coord.y;
      c.y = cy;
      if (((p->s).flags & 0x10) != 0) {
        *(volatile s32*)&c.x = cx;
      }
      c.y = cy + -0x2100;
      if ((p->s).work[1] == 0xff) {
        goto one;
      }
      if ((p->s).work[1] == 0xfe) {
        FUN_080b2b40(0, &c, 0x80 << 2, 0);
      } else {
        if ((pZero2->s).coord.x > cx) {
        one:
          FUN_080b2b40(0, &c, 0x80 << 2, 1);
        } else {
          FUN_080b2b40(0, &c, 0x80 << 2, 0);
        }
      }
      PlaySound(0x2f);
      goto inc;
    }
    case 3:
      ((void (*)(struct Entity*, struct Coord*, s32, s32))FUN_0809c3b4)(
          &p->s, &(p->s).coord, 0xB01C, ((p->s).flags >> 4) & 1);
      SetMotion(&p->s, 0xB01D);
      UpdateMotionGraphic(&p->s);
      (p->s).work[2] = 0x44;
      goto inc;
    case 4: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t != 0) {
        t -= 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      FALLTHROUGH;
    }
    case 11:
      if (((p->s).scriptEntity->flags & 0x80) == 0) {
        break;
      }
      (p->s).mode[2] = 0x14;
      break;
    case 20:
      (p->s).work[2] = 0x50;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 21:
      if (((p->s).scriptEntity->flags & 0x80) == 0) {
        break;
      }
      goto inc;
    case 22: {
      const struct Coord* ec;
      if ((p->s).mode[3] == 1) {
        if (((p->s).flags & 0x10) == 0) {
          ec = (const struct Coord*)0x08363A88;
          asm volatile("" : "+l"(ec));
        } else {
          ec = (const struct Coord*)0x08363A90;
          asm volatile("" : "+l"(ec));
        }
      } else {
        if (((p->s).flags & 0x10) == 0) {
          ec = (const struct Coord*)0x08363A78;
          asm volatile("" : "+l"(ec));
        } else {
          ec = (const struct Coord*)0x08363A80;
          asm volatile("" : "+l"(ec));
        }
      }
      *(struct Entity**)((u8*)p + 0xc0) = CreateBossExplosion(&p->s, (struct Coord*)ec);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 23:
      if ((*(struct Entity**)((u8*)p + 0xc0))->mode[0] <= 1) {
        break;
      }
    inc:
      (p->s).mode[2]++;
      break;
    case 24:
      (p->s).work[2] = 0x30;
      {
        u8 v = gStageRun.vm.active;
        u32 t = 2;
        t |= v;
        gStageRun.vm.active = t;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 25: {
      s32 t = (p->s).work[2];
      if (t != 0) {
        t -= 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      {
        u8 fl = (p->s).flags;
        u32 f2 = 0xFE;
        f2 &= fl;
        (p->s).flags = f2;
      }
      break;
    }
  }
}

bool8 FUN_08052b48(struct Boss* p) { return TRUE; }

void cubitMode0(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      SetMotion(&p->s, MOTION(0xb0, 2));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08052b98(struct Boss* p) { return TRUE; }

// 0x08052b9c
void cubitMode1(struct Boss* p) {
  motion_t m;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x3C;
      PlaySound(0xC9);
      m = MOTION(0xB0, 0x07);
      goto setmotion;
    case 2:
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      goto advance;
    case 3:
      m = MOTION(0xB0, 0x09);
    setmotion:
      SetMotion(&p->s, m);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    advance:
      (p->s).mode[2]++;
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 2, (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_08052c30(struct Boss* p) { return TRUE; }

void cubitMode2(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0xb0, 2));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (!(gStageRun.vm.active & 1)) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

bool8 FUN_08052c78(struct Boss* p) { return TRUE; }

INCASM("asm/boss/cubit_p5.inc");

bool8 FUN_08052f08(struct Boss* p) { return TRUE; }

INCASM("asm/boss/cubit_p6.inc");

bool8 FUN_080533bc(struct Boss* p) { return TRUE; }

void cubitMode5(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 push;
      (p->s).d.y += 0x40;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (push != 0) {
        (p->s).coord.y += push;
        (p->s).mode[2]++;
      }
      break;
    }
    case 2:
      SetMotion(&p->s, 0xb014);
      SetDDP(&p->body, &sCollisions[1]);
      *(u8*)((u8*)p + 0xc8) = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 nop_08053460(struct Boss* p) { return TRUE; }

INCASM("asm/boss/cubit_p8.inc");

bool8 FUN_08053724(struct Boss* p) { return TRUE; }

INCASM("asm/boss/cubit_p9.inc");

bool8 FUN_08053a08(struct Boss* p) { return TRUE; }

INCASM("asm/boss/cubit_p10.inc");

bool8 FUN_08053d08(struct Boss* p) { return TRUE; }

INCASM("asm/boss/cubit_p11.inc");

bool8 FUN_080542c8(struct Boss* p) { return TRUE; }

void cubitMode10(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      (p->s).angle = 0;
      (p->s).spr.mag.x = 0x100;
      (p->s).spr.mag.y = 0x100;
      PlaySound(0xd1);
      SetMotion(&p->s, MOTION(0xb0, 0x1e));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
  }
  if (isKilled(*(struct Entity**)((u8*)&(p->props) + 12))) {
    *(struct Entity**)((u8*)&(p->props) + 12) = NULL;
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0xff;
  }
}

bool8 FUN_0805433c(struct Boss* p) { return TRUE; }

void cubitKnockBackDamage(struct Boss* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u32 fl asm("r0");
      s32 z2;
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      {
        u8* w = (u8*)p + 0x24;
        u32 kk;
        *w = m;
        asm("" : "+r"(w));
        w += 0x2c;
        kk = 0x100;
        *(u16*)w = kk;
        asm("" : "+r"(w));
        w += 2;
        asm("" : "+r"(w));
        *(u16*)w = kk;
      }
      PlaySound(0xD1);
      SetMotion(&p->s, 0xB01E);
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        u32 k10;
        (p->s).d.x = -0x200;
        ((p->s).spr).xflip = 1;
        {
          u8* oa = (u8*)p + 0x4a;
          u32 ov = *oa;
          k10 = 0x10;
          ov |= k10;
          *oa = ov;
        }
        fl = (p->s).flags;
        fl |= k10;
      } else {
        u8* xa;
        u8 zv;
        (p->s).d.x = 0x200;
        xa = (u8*)p + 0x4c;
        zv = 0;
        asm("" : "+r"(zv));
        *xa = zv;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        {
          u32 flv = (p->s).flags;
          register u32 t asm("r0");
          t = 0xEF;
          asm("" : "+r"(t));
          t &= flv;
          fl = t;
        }
      }
      (p->s).flags = fl;
      {
        u32 fl2 = (p->s).flags;
        u32 t = 1;
        register s32 zp asm("r2");
        zp = 0;
        asm volatile("" :: "r"(zp));
        z2 = zp;
        t |= fl2;
        (p->s).flags = t;
      }
      *(u32*)((u8*)p + 0xc0) = z2;
      (p->s).work[2] = 0x28;
      (p->s).work[3] = z2;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 k;
      UpdateMotionGraphic(&p->s);
      {
        s32 dx = (p->s).d.x;
        (p->s).d.x = dx + ((-dx << 3) >> 8);
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      {
        s32 ny = (p->s).coord.y + (p->s).d.y;
        s32 nx;
        s32 dx2;
        (p->s).coord.y = ny;
        nx = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = nx;
        if ((p->s).d.x > 0) {
          s32 push = PushoutToLeft1(nx + 0x1C00, ny + -0xC00);
          if (push != 0) {
            (p->s).coord.x += push;
          }
        }
      }
      if ((p->s).d.x < 0) {
        s32 push2 = PushoutToRight1((p->s).coord.x + -0x1C00, (p->s).coord.y + -0xC00);
        if (push2 != 0) {
          (p->s).coord.x += push2;
        }
      }
      {
        s32 cx = (p->s).coord.x;
        s32 cy = (p->s).coord.y;
        s32 push3;
        k = -0x400;
        push3 = PushoutToUp1(cx, cy + k);
        if (push3 != 0) {
          (p->s).work[3] = 1;
          (p->s).coord.y += push3;
        }
      }
      if ((p->s).work[2] != 0) {
        (p->s).work[2] = (p->s).work[2] - 1;
      }
      if (*(u16*)((u8*)p + 0x12) == 0x100) {
        (p->s).coord.y += k;
        {
          u8* ac = (u8*)p + 0xc8;
          s32 z = 0;
          *ac = z;
          (p->s).mode[1] = 3;
          (p->s).mode[2] = z;
        }
        (p->s).mode[3] = 0xFF;
      }
      break;
    }
  }
}


#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoords[2];

bool8 cubit_080544c0(struct Boss* p) {
  struct VFX** slot = (struct VFX**)&(p->props).raw[12];

  if (*slot == NULL && ((p->body).status & 1)) {
    if ((((p->s).motionID << 8) | (p->s).motion.step) == MOTION(0xb0, 0x19)) {
      if ((p->s).mode[1] == 4 && (p->s).mode[2] != 6) {
        *slot = ApplyElementEffect(22, &p->s, &sElementCoords[1]);
      }
    } else {
      *slot = ApplyElementEffect(22, &p->s, &sElementCoords[0]);
    }
    if (*(struct VFX**)&(p->props).raw[12] != NULL) {
      *(struct VFX**)&(p->props).raw[12] = NULL;
    }
  }
  return TRUE;
}

INCASM("asm/boss/cubit_p13_p1_b.inc");

// 0x08054530
void FUN_08054530(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  const struct Collision* pr = (body->enemy)->processing;
  struct Entity* e;
  {
    u8 k = pr->atkType;
    if (k == 3 || k == 0xE || k == 0xF) {
      struct Entity* q;
      e = (struct Entity*)body->parent;
      q = (struct Entity*)(body->enemy)->parent;
      if ((*(u32*)((u8*)e + 0x8c) & 0x200) != 0) {
        goto chk;
      }
      if (*(s16*)((u8*)e + 0xa4) != 0) {
        goto skip;
      }
    chk:
      if ((gStageRun.missionStatus & 8) == 0) {
        s32 r;
        if (q->d.x < 0) {
          r = 0xFF;
          asm("" : "+r"(r));
        } else {
          r = 0xFE;
          asm("" : "+r"(r) : "r"(e));
        }
        e->work[1] = r;
      }
    }
  }
skip:
  pr = (body->enemy)->processing;
  {
    const struct Collision* mp = body->processing;
    if (mp->kind == 2) {
      return;
    }
    if (*(s32*)((u8*)mp + 0xc) == -1) {
      return;
    }
  }
  if ((*(u32*)&pr->atkType & 0x200FF) != 0x20002) {
    return;
  }
  e = (struct Entity*)body->parent;
  if ((u8)(e->mode[1] - 0xA) <= 1) {
    return;
  }
  {
    u8 z = 0;
    e->mode[1] = 0xB;
    e->mode[2] = z;
  }
}

static const u16 u16_ARRAY_ARRAY_08363a98[2][4];

// 0x080545CC
u16 cubit_080545cc(struct Boss* p, s32 v, s32 mode) {
  register s32 i asm("r2");
  register s32 idx asm("r0");
  register const u16* t asm("r3");
  register const u16* base asm("r5");
  if (*(u8*)((u8*)p + 0xc8) != 0) {
    if (mode != 1) {
      goto b;
    }
    i = 0;
    base = u16_ARRAY_ARRAY_08363a98[1];
    t = base;
    do {
      if (*t == v) {
        goto found3;
      }
      t++;
      i++;
    } while (i <= 2);
    goto end;
  b:
    i = 0;
    base = u16_ARRAY_ARRAY_08363a98[1];
    t = base;
    do {
      if (*t == v) {
        goto found3;
      }
      t++;
      i++;
    } while (i <= 2);
    goto end;
  }
  if (mode != 1) {
    goto d;
  }
  i = 0;
  base = u16_ARRAY_ARRAY_08363a98[0];
  t = base;
  do {
    if (*t == v) {
      register s32 n asm("r1");
      n = i + 1;
      idx = n;
      if (n < 0) {
        idx = i + 4;
      }
      idx = n - ((idx >> 2) << 2);
      goto ret;
    }
    t++;
    i++;
  } while (i <= 3);
  goto end;
found3:
  idx = (i + 1) % 3;
ret:
  return base[idx];
d:
  i = 0;
  base = u16_ARRAY_ARRAY_08363a98[0];
  t = base;
  do {
    if (*t == v) {
      goto found3;
    }
    t++;
    i++;
  } while (i <= 3);
end:;
}

bool8 cubit_08054674(struct Boss* p) {
  if (*(u8*)((u8*)p + 0xc8) != 0) {
    return TRUE;
  }
  return FALSE;
}

// 0x08054688
void cubit_08054688(struct Boss* p) {
  u32 mv;
  u32 m;
  mv = ((u16)(p->s).motionID << 8) | (p->s).motion.step;
  m = MOTION(0xB0, 0x03);
  if (mv == m) {
    if ((p->s).motion.state == 3) {
      u8 fl = (p->s).flags;
      register s32 k10 asm("r3");
      s32 msk;
      k10 = 0x10;
      asm("" : "+r"(k10));
      msk = 0x10;
      msk &= fl;
      if (msk == 0) {
        u8* xp = (u8*)p + 0x4c;
        *xp = 1;
        xp -= 2;
        *xp |= k10;
        (p->s).flags |= k10;
      } else {
        u8* xp;
        u8* oa;
        s32 ov;
        register s32 z asm("r0");
        xp = (u8*)p + 0x4c;
        z = 0;
        *xp = z;
        oa = (u8*)p + 0x4a;
        ov = *oa;
        z -= 0x11;
        z &= ov;
        *oa = z;
        (p->s).flags &= 0xEF;
      }
      if (*((u8*)p + 0xc8) != 0) {
        SetMotion(&p->s, MOTION(0xB0, 0x01));
      } else {
        SetMotion(&p->s, MOTION(0xB0, 0x02));
      }
    }
  } else if ((pZero2->s).coord.x > (p->s).coord.x) {
    if (((p->s).flags & 0x10) == 0) {
      SetMotion(&p->s, m);
    }
  } else {
    if (((p->s).flags & 0x10) != 0) {
      SetMotion(&p->s, m);
    }
  }
}

// --------------------------------------------

bool8 FUN_08052b48(struct Boss* p);
bool8 FUN_08052b98(struct Boss* p);
bool8 FUN_08052c30(struct Boss* p);
bool8 FUN_08052c78(struct Boss* p);
bool8 FUN_08052f08(struct Boss* p);
bool8 FUN_080533bc(struct Boss* p);
bool8 nop_08053460(struct Boss* p);
bool8 FUN_08053724(struct Boss* p);
bool8 FUN_08053a08(struct Boss* p);
bool8 FUN_08053d08(struct Boss* p);
bool8 FUN_080542c8(struct Boss* p);
bool8 FUN_0805433c(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[12] = {
    (BossFunc)FUN_08052b48,
    (BossFunc)FUN_08052b98,
    (BossFunc)FUN_08052c30,
    (BossFunc)FUN_08052c78,
    (BossFunc)FUN_08052f08,
    (BossFunc)FUN_080533bc,
    (BossFunc)nop_08053460,
    (BossFunc)FUN_08053724,
    (BossFunc)FUN_08053a08,
    (BossFunc)FUN_08053d08,
    (BossFunc)FUN_080542c8,
    (BossFunc)FUN_0805433c,
};
// clang-format on

void cubitMode0(struct Boss* p);
void cubitMode1(struct Boss* p);
void cubitMode2(struct Boss* p);
void cubitNeutral(struct Boss* p);
void cubitMode4(struct Boss* p);
void cubitMode5(struct Boss* p);
void cubitMode6(struct Boss* p);
void cubitMode7(struct Boss* p);
void cubitMode8(struct Boss* p);
void cubitEX(struct Boss* p);
void cubitMode10(struct Boss* p);
void cubitKnockBackDamage(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[12] = {
    cubitMode0,
    cubitMode1,
    cubitMode2,
    cubitNeutral,
    cubitMode4,
    cubitMode5,
    cubitMode6,
    cubitMode7,
    cubitMode8,
    cubitEX,
    cubitMode10,
    cubitKnockBackDamage,
};
// clang-format on

// --------------------------------------------

void cubitDeath0(struct Boss* p);
void cubitDeath1(struct Boss* p);

static const BossFunc sDeads[2] = {
    cubitDeath0,
    cubitDeath1,
};

// --------------------------------------------

// 0x083639d8
static const struct Collision sCollisions[6] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(18), PIXEL(36), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(23), PIXEL(26), PIXEL(48)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(23), PIXEL(26), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(13), PIXEL(26), PIXEL(48)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(0), PIXEL(13), PIXEL(26), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(30), PIXEL(40), PIXEL(60)},
    },
};

static const struct Coord sElementCoords[2] = {
    {PIXEL(0), -PIXEL(24)},
    {PIXEL(0), PIXEL(10)},
};

static const struct Coord sExplosionCoords[4] = {
    {PIXEL(6), -PIXEL(33)},
    {PIXEL(6), -PIXEL(33)},
    {PIXEL(10), -PIXEL(33)},
    {PIXEL(10), -PIXEL(33)},
};

// 0x08363a98
static const u16 u16_ARRAY_ARRAY_08363a98[2][4] = {
    {4, 6, 7, 9},
    {5, 6, 8, 0},
};
