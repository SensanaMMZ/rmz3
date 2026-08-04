#include "anim_loader.h"
#include "boss.h"
#include "collision.h"
#include "element.h"
#include "global.h"
#include "motion.h"
#include "zero.h"
#include "metatile.h"
#include "mission.h"
#include "story.h"
#include "physics.h"
#include "stagerun.h"

static const struct Collision sCollisions[];
static const struct Coord sElementCoord;

void Hanumachine_Update(struct Boss* p);
void FUN_0805d568(struct Body* body);

void Hanumachine_Init(struct Boss* p) {
  s32 z5;
  s32 g;
  LOAD_STATIC_GRAPHIC(0x6A);
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    z5 = 0;
    d0 |= f0;
    d0 |= FLIPABLE;
    (p->s).flags = d0;
  }
  SetMotion(&p->s, MOTION(0xB5, 0x00));
  ((p->s).spr).xflip = z5;
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
  *((u8*)p + 0xbd) = z5;
  *((u8*)p + 0xbe) = z5;
  ResetBossBody(p, sCollisions, 0x40);
  {
    register void* fv asm("r1");
    struct Body* body;
    fv = (void*)FUN_0805d568;
    body = &p->body;
    body->fn = fv;
  }
  {
    s32 y2 = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).coord.y = y2;
    g = FUN_0800a134((p->s).coord.x, y2);
  }
  *(s32*)((u8*)p + 0xb4) = FUN_0800a31c((p->s).coord.x, g);
  *(s32*)((u8*)p + 0xb8) = FUN_0800a22c((p->s).coord.x, g);
  *(s32*)((u8*)p + 0xc4) = z5;
  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = z5;
  Hanumachine_Update(p);
}

static const BossFunc sUpdates1[30];
static const BossFunc sUpdates2[30];
u16 FUN_0805d594(struct Boss* p, s32 a, s32 b);
void Hanumachine_Die(struct Boss* p);

void Hanumachine_Update(struct Boss* p) {
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    if (*(s16*)((u8*)p + 0xa4) != 0) {
      goto alive;
    }
  }
  if (gStageRun.missionStatus & 8) {
    goto alive;
  }
  SET_BOSS_ROUTINE(p, ENTITY_DIE);
  Hanumachine_Die(p);
  return;

alive:
  *(s32*)((u8*)p + 0xc8) = (p->s).coord.x;
  *(s32*)((u8*)p + 0xcc) = (p->s).coord.y;
  if ((p->s).mode[1] != 0x1d) {
    if (((p->body).status & 0x00020001) == 0x00020001) {
      if (FUN_0805d594(p, 0, 0) == 0) {
        (p->s).mode[1] = 0x1d;
        (p->s).mode[2] = 0;
      }
    }
  }
  if (((p->body).status & 1) && *(struct Entity**)((u8*)p + 0xc4) == NULL) {
    *(struct Entity**)((u8*)p + 0xc4) = (struct Entity*)ApplyElementEffect(0x1c, &p->s, &sElementCoord);
  }
  if (isKilled(*(struct Entity**)((u8*)p + 0xc4))) {
    *(struct Entity**)((u8*)p + 0xc4) = NULL;
  }
  if (sUpdates2[(p->s).mode[1]] != NULL) {
    (sUpdates2[(p->s).mode[1]])(p);
  }
  (sUpdates1[(p->s).mode[1]])(p);
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);
struct Enemy* CreateEnemy50(struct Boss* p);
struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);

void Hanumachine_Die(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    u32* ps;
    {
      u32* ps0 = (u32*)((u8*)p + 0x8c);
      u32 st = *ps0 & 0x10000;
      asm("" : "=r"(ps) : "0"(ps0));
      if (st != 0) {
        struct Coord c;
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y + -0x1000;
        FUN_080b2b40(0, &c, 0x200, *((u8*)p + 0xbc));
        SetMotion(&p->s, 0xB503);
        if ((p->s).flags & 0x10) {
          s32 v = 0x40;
          (p->s).d.x = v;
          v -= 0x41;
          (p->s).unk_coord.x = v;
        } else {
          (p->s).d.x = -0x40;
          (p->s).unk_coord.x = 1;
        }
        PlaySound(0x2F);
        CreateEnemy50(p);
        (p->s).mode[1] = 0;
        (p->s).mode[3] = 0;
      } else {
        SetMotion(&p->s, 0xB50F);
        (p->s).mode[1] = 1;
        (p->s).mode[3] = 1;
        (p->s).work[2] = 0x40;
      }
    }
    PlaySound(0x4E);
    {
      s32 z = 0;
      *ps = z;
      *(u32*)((u8*)p + 0x90) = z;
      *((u8*)p + 0x94) = z;
    }
    (p->s).flags &= 0xFB;
    {
      u32 v = gStageRun.missionStatus;
      register s32 one asm("r5");
      s32 t;
      one = 1;
      t = one;
      asm("" : "+r"(t));
      t &= v;
      asm volatile("" :: "r"(v));
      if (t != 0) {
        u32 a = gStageRun.vm.active;
        s32 t2 = one;
        asm volatile("" : "+r"(t2));
        t2 &= a;
        if (t2 == 0) {
          u32 m;
          asm volatile("" :: "r"(a));
          asm volatile("" :: "r"(a));
          m = 0xFFFE;
          m &= v;
          m |= 0x10;
          gStageRun.missionStatus = m;
        }
      }
      asm volatile("" :: "r"(one));
    }
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  switch ((p->s).mode[1]) {
    case 0: {
      s32 dx;
      (p->s).coord.x += (p->s).d.x;
      dx = (p->s).d.x + (p->s).unk_coord.x;
      (p->s).d.x = dx;
      if (dx != 0) {
        break;
      }
      goto inc01;
    }
    case 1:
      if (((u8*)(p->s).scriptEntity)[9] & 0x80) {
        struct Coord c2;
        register struct Coord* pc asm("r0");
        if ((p->s).mode[3] != 0) {
          c2.x = 0xC00;
        } else {
          c2.x = 0x1500;
        }
        {
          register s32 yv asm("r1");
          struct Coord* pc2;
          yv = -0x1200;
          pc = &c2;
          pc->y = yv;
          asm("" : "=r"(pc2) : "0"(pc));
          (p->s).unk_2c = CreateBossExplosion(&p->s, pc2);
        }
      inc01:
        (p->s).mode[1]++;
      }
      break;
    case 2:
      if (((struct Entity*)(p->s).unk_2c)->mode[0] > 1) {
        gStageRun.vm.active |= 2;
        (p->s).work[2] = 0x20;
        goto inc3;
      }
      break;
    case 3: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0xFF) {
        u32 fl = (p->s).flags;
        register u32 kfe asm("r1");
        kfe = 0xFE;
        asm volatile("" : "+r"(kfe));
        kfe &= fl;
        (p->s).flags = kfe;
      inc3:
        (p->s).mode[3]++;
      }
      break;
    }
  }
}

void FUN_0805bcdc(struct Boss* p) {
  s32 push = PushoutToUp1((p->s).coord.x, (p->s).coord.y + 1);
  if (push == 0) {
    (p->s).mode[1] = 0x19;
    (p->s).mode[2] = push;
  }
}

void hanu_0805bcfc(struct Boss* p) {
  u8 m = (p->s).mode[2];
  if (m == 0) {
    SetMotion(&p->s, MOTION(0xb5, 0));
    (p->s).mode[2]++;
    (p->s).mode[3] = m;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).scriptEntity->flags & 1) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

void hanu_0805bd38(struct Boss* p) {
  motion_t m;
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0xB5, 0x10));
    PlaySound(0x50);
    (p->s).work[2] = 0xA0;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).mode[2] == 1) {
    if ((u8)--(p->s).work[2] == 0xFF) {
      m = MOTION(0xB5, 0x16);
      goto set;
    }
  } else if ((p->s).mode[2] == 2) {
    if ((p->s).motion.state == 3) {
      m = MOTION(0xB5, 0x00);
    set:
      SetMotion(&p->s, m);
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
    }
  }
  {
    u32 t = gStageRun.vm.active & 1;
    if (t == 0) {
      (p->s).mode[1] = 2;
      (p->s).mode[2] = t;
    }
  }
}

void hanu_0805bdc0(struct Boss* p) {
  UpdateMotionGraphic(&p->s);
  {
    register s32* w asm("r4");
    w = (s32*)((u8*)p + 0xb4);
    if (*w == FUN_0800a31c((p->s).coord.x, (p->s).coord.y)) {
      w += 1;
      if (*w == FUN_0800a22c((p->s).coord.x, (p->s).coord.y)) {
        goto ok;
      }
    }
    {
      s32 z = 0;
      (p->s).mode[1] = 0xD;
      (p->s).mode[3] = z;
      (p->s).mode[2] = z;
      return;
    }
  ok:;
  }
  {
    register u8* fb1 asm("r1");
    register u8* fb asm("r4");
    s32 f, t;
    s32 sel;
    struct Mission* ms;
    fb1 = (u8*)p + 0xbd;
    f = *fb1;
    t = 1;
    t &= f;
    fb = fb1;
    asm("" : "+r"(fb1));
    if (t != 0) {
      u32 rk = gMission.unk_00->rank;
      ms = &gMission;
      if (rk > 4) {
        sel = RANDOM(RNG_0202f388) & 7;
      } else {
        sel = (u8)(RANDOM(RNG_0202f388) % 7);
      }
    } else {
      u32 fv = (u32)f << 24;
      asm("" : "+r"(fv));
      sel = fv >> 25;
      ms = &gMission;
    }
    switch (sel) {
      case 0:
        (p->s).mode[1] = 0xD;
        (p->s).mode[3] = 1;
        break;
      case 1:
        (p->s).mode[1] = 8;
        break;
      case 2:
        (p->s).mode[1] = 0xA;
        break;
      case 3:
        if (*((u8*)p + 0xbe) != 0) {
          (p->s).mode[1] = 0x16;
        } else {
          (p->s).mode[1] = 4;
        }
        break;
      case 4: {
        s32 z = 0;
        (p->s).mode[1] = 0xD;
        (p->s).mode[3] = z;
        break;
      }
      case 5:
        (p->s).mode[1] = 0x16;
        break;
      case 6:
        (p->s).mode[1] = 0x19;
        break;
      case 7:
        (p->s).mode[1] = 0x13;
        break;
    }
    {
      u8* c = fb;
      s32 n = *c + 1;
      s32 z3 = 0;
      u32 rk2;
      *c = n;
      rk2 = ms->unk_00->rank;
      if (rk2 > 4) {
        if ((u8)n > 0xF) {
          *c = z3;
        }
      } else {
        if ((u8)n > 0xD) {
          *fb = z3;
        }
      }
    }
  }
  (p->s).mode[2] = 0;
}

void hanu_0805bf10(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0xB5, 0x00));
    SetDDP(&p->body, sCollisions);
    (p->s).mode[2]++;
    (p->s).work[2] = 0x20;
  }
  UpdateMotionGraphic(&p->s);
  if (--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

// 0x0805BF60
void hanu_0805bf60(struct Boss* p) {
  register s32 f asm("r5");
  register s32 cx asm("r3");
  if ((p->s).mode[2] == 0) {
    register struct Zero* zz asm("r2");
    register s32 v asm("r3");
    SetMotion(&p->s, 0xB501);
    SetDDP(&p->body, (const struct Collision*)0x08364E68);
    v = 0;
    zz = pZero2;
    if ((p->s).coord.x < (zz->s).coord.x) {
      v = 1;
    }
    *((u8*)p + 0x4c) = v;
    v = 0;
    if ((p->s).coord.x < (zz->s).coord.x) {
      v = 1;
    }
    {
      register u8* o0 asm("r0");
      register s32 k asm("r0");
      register u8* oa asm("ip");
      k = 0x4a;
      asm volatile("add %0, %0, %1" : "+l"(k) : "l"(p));
      o0 = (u8*)k;
      oa = o0;
      {
        register s32 sh asm("r2");
        register s32 ov asm("r1");
        register s32 m11 asm("r0");
        sh = v << 4;
        ov = *o0;
        m11 = 0x11;
        m11 = -m11;
        m11 &= ov;
        m11 |= sh;
        {
          register u8* o1 asm("r1");
          o1 = oa;
          *o1 = m11;
        }
      }
    }
    if (v != 0) {
      register u8 g asm("r0");
      register s32 k10 asm("r1");
      g = (p->s).flags;
      k10 = 0x10;
      g |= k10;
      (p->s).flags = g;
    } else {
      register u8 g2 asm("r0");
      register u8 h2 asm("r1");
      h2 = (p->s).flags;
      asm("" : "+r"(h2));
      g2 = 0xEF;
      g2 &= h2;
      (p->s).flags = g2;
    }
    {
      register s32 dv asm("r0");
      if (((p->s).flags & 0x10) != 0) {
        dv = 0xe0 << 2;
      } else {
        dv = 0xFFFFFC80;
      }
      (p->s).d.x = dv;
    }
    PlaySound(0x4e);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    {
      register s32 hv asm("r1");
      register s32 t asm("r0");
      hv = (p->s).flags;
      t = 0x10;
      t &= hv;
      f = (u8)t;
    }
  }
  if (f != 0) {
    register u16 r0v;
    {
      register s32 xx asm("r0");
      register s32 yy asm("r1");
      xx = (p->s).coord.x;
      f = 0x80 << 5;
      xx += f;
      yy = (p->s).coord.y;
      yy += f;
      r0v = (u16)FUN_080098a4(xx, yy);
    }
    if (r0v == 0) {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = r0v;
      *((u8*)p + 0xbe) = 1;
    }
    {
      register s32 t2 asm("r2");
      register s32 c1 asm("r1");
      register s32 lim asm("r0");
      c1 = (p->s).coord.x;
      t2 = c1 + f;
      lim = *(s32*)((u8*)p + 0xb8);
      cx = c1;
      if (t2 > lim) {
        register s32 zr2 asm("r1");
        zr2 = 0;
        (p->s).mode[1] = 5;
        (p->s).mode[2] = zr2;
        return;
      }
      {
        register s32 t3 asm("r1");
        register s32 kk asm("r2");
        kk = 0xFFFFE000;
        asm volatile("add %0, %1, %2" : "=l"(t3) : "l"(cx), "l"(kk));
        if (t3 > (pZero2->s).coord.x) {
          register s32 zr3 asm("r1");
          zr3 = 0;
          (p->s).mode[1] = 3;
          (p->s).mode[2] = zr3;
          return;
        }
      }
    }
  } else {
    if (((u16)FUN_080098a4((p->s).coord.x + 0xFFFFF000, (p->s).coord.y + (0x80 << 5)) << 16) == 0) {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = f;
      *((u8*)p + 0xbe) = 1;
    }
    {
      register s32 t4 asm("r2");
      register s32 c2 asm("r1");
      register s32 lim2 asm("r0");
      c2 = (p->s).coord.x;
      t4 = c2 + 0xFFFFF000;
      lim2 = *(s32*)((u8*)p + 0xb4);
      cx = c2;
      if (t4 < lim2) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = f;
        return;
      }
      {
        register s32 t5 asm("r1");
        t5 = cx + (0x80 << 6);
        if (t5 < (pZero2->s).coord.x) {
          (p->s).mode[1] = 3;
          (p->s).mode[2] = f;
          return;
        }
      }
    }
  }
  {
    register s32 nx asm("r0");
    nx = (p->s).d.x;
    nx = cx + nx;
    (p->s).coord.x = nx;
  }
}


// 0x0805C0D0
void hanu_0805c0d0(struct Boss* p) {
  s32 y;
  if ((p->s).mode[2] == 0) {
    s32 dy;
    InitRotatableMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, MOTION(0xB5, 0x01));
    SetDDP(&p->body, &sCollisions[4]);
    (p->s).angle = 0x40;
    dy = -0x380;
    (p->s).d.y = dy;
    if ((p->s).flags & X_FLIP) {
      s32 x = *(s32*)((u8*)p + 0xb8);
      (p->s).coord.x = x;
      (p->s).unk_coord.x = x - 0x1000;
    } else {
      s32 x = *(s32*)((u8*)p + 0xb4);
      (p->s).coord.x = x;
      (p->s).unk_coord.x = x + 0x1000;
      (p->s).d.y = dy;
    }
    (p->s).coord.y -= 0x1600;
    (p->s).work[2] = 0x80;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  y = (p->s).coord.y + (p->s).d.y;
  (p->s).coord.y = y;
  if ((u8)--(p->s).work[2] == 0xFF || ((u16)FUN_080098a4((p->s).unk_coord.x, y - 0x3000) << 16) != 0) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

// 0x0805C198
void hanu_0805c198(struct Boss* p) {
  register s32 m asm("r1");
  m = (p->s).mode[2];
  if (m == 0) {
    (p->s).angle = m;
    InitNonAffineMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, 0xB506);
    SetDDP(&p->body, &sCollisions[6]);
    {
      register s32 one asm("r2");
      register s32 xv asm("r1");
      register s32 t0 asm("r0");
      t0 = (u32)(p->s).flags >> 4;
      one = 1;
      t0 ^= one;
      asm("" : "+r"(t0));
      t0 &= one;
      ((p->s).spr).xflip = t0;
      xv = (u32)(p->s).flags >> 4;
      xv ^= one;
      asm("" : "+r"(xv));
      xv &= one;
      {
        register u8* oa asm("ip");
        s32 sh4, ov, m11;
        oa = (u8*)p + 0x4a;
        sh4 = xv << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      if (xv != 0) {
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
    }
    {
      s32 dx;
      if ((p->s).flags & 0x10) {
        register s32 k asm("r1");
        s32 cx = (p->s).coord.x;
        k = 0xA00;
        (p->s).coord.x = cx + k;
        (p->s).unk_coord.x = k;
        dx = 0x200;
      } else {
        register s32 k2 asm("r1");
        s32 cx2 = (p->s).coord.x;
        k2 = -0xA00;
        (p->s).coord.x = cx2 + k2;
        (p->s).unk_coord.x = k2;
        dx = -0x200;
      }
      (p->s).d.x = dx;
    }
    (p->s).d.y = -0x300;
    (p->s).coord.y += 0x1600;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  {
    register s32 dy asm("r1");
    {
      s32 cy = (p->s).coord.y;
      dy = (p->s).d.y;
      (p->s).coord.y = cy + dy;
    }
    dy += 0x40;
    (p->s).d.y = dy;
    if (dy > 0x700) {
      (p->s).d.y = 0x700;
    }
  }
  if ((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

void hanu_0805c2a4(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    if ((((p->s).motionID << 8) | (p->s).motion.step) == MOTION(0xB5, 0x14)) {
      SetMotion(&p->s, MOTION(0xB5, 0x15));
    } else {
      SetMotion(&p->s, MOTION(0xB5, 0x07));
    }
    SetDDP(&p->body, &sCollisions[8]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
}

void FUN_080866a4(struct Entity* e, u8 mode, u8 xflip);

// 0x0805C30C
void hanu_0805c30c(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0xB50A);
    {
      s32 onR = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        onR = 1;
      }
      ((p->s).spr).xflip = onR;
    }
    {
      s32 onR2 = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        onR2 = 1;
      }
      {
        register u8* t0 asm("r0");
        register u8* oa asm("ip");
        register u32 sh asm("r2");
        u32 off = 0x4a;
        asm("" : "+r"(off));
        off += (u32)p;
        t0 = (u8*)off;
        oa = t0;
        asm("" : "+r"(oa));
        sh = onR2 << 4;
        {
          s32 ov = *t0;
          s32 m11 = -0x11;
          u32 vv;
          register u8* fa asm("r1");
          asm("" : "+r"(m11));
          vv = (m11 & ov) | sh;
          fa = oa;
          asm("" : "+r"(fa));
          *fa = vv;
        }
      }
      if (onR2 != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
    }
    (p->s).work[2] = 0x14;
    (p->s).work[3] = 3;
    PlaySound(0x4f);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).work[2] == 0) {
    FUN_080866a4(&p->s, (p->s).work[3] - 1, ((p->s).flags >> 4) & 1);
    (p->s).work[2] = 8;
    (p->s).work[3]--;
  } else {
    (p->s).work[2]--;
  }
  {
    u8 w3 = (p->s).work[3];
    if (w3 == 0) {
      (p->s).mode[1] = 9;
      (p->s).mode[2] = w3;
    }
  }
}

void FUN_0805c3cc(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0xB50B);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
}

// 0x0805c404
void FUN_0805c404(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    register struct Zero* z asm("r2");
    register s32 v asm("r3");
    SetMotion(&p->s, MOTION(0xB5, 0x08));
    v = 0;
    z = pZero2;
    if ((p->s).coord.x < (z->s).coord.x) {
      v = 1;
    }
    (p->s).spr.xflip = v;
    v = 0;
    if ((p->s).coord.x < (z->s).coord.x) {
      v = 1;
    }
    {
      register u8* oa asm("ip");
      u32 k;
      s32 sh4, ov, m11;
      k = 0x4a;
      asm("" : "+r"(k));
      oa = (u8*)(k + (u32)p);
      sh4 = v << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      m11 |= sh4;
      *oa = m11;
    }
    if (v != 0) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
    (p->s).d.y = -0x480;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).motion.state == 3) {
    s32 zz = 0;
    (p->s).mode[1] = 0xb;
    (p->s).mode[2] = zz;
  }
}

void hanu_080ad598(struct Entity* e, u8 a1, u8 a2);

// 0x0805C4A4
void hanu_0805c4a4(struct Boss* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  if (m == 0) {
    InitRotatableMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, MOTION(0xB5, 0x09));
    (p->s).coord.y -= 0x1000;
    (p->s).work[2] = 0x30;
    (p->s).work[3] = m;
    SetDDP(&p->body, (const struct Collision*)0x08364F28);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).flags & X_FLIP) {
    u8 w = (p->s).work[2];
    if (w == 0x20) {
      hanu_080ad598(&p->s, 0, 0x50);
      PlaySound(0x51);
      goto after;
    }
    if (w == 0x10) {
      hanu_080ad598(&p->s, 0, 0x40);
      PlaySound(0x51);
      goto after;
    }
    if (w == 0) {
      hanu_080ad598(&p->s, 0, 0x30);
      PlaySound(0x51);
    }
    goto after;
  }
  {
    u8 w = (p->s).work[2];
    if (w == 0x20) {
      hanu_080ad598(&p->s, 0, 0xB0);
      PlaySound(0x51);
      goto after;
    }
    if (w == 0x10) {
      hanu_080ad598(&p->s, 0, 0xC0);
      PlaySound(0x51);
      goto after;
    }
    if (w == 0) {
      hanu_080ad598(&p->s, 0, 0xD0);
      PlaySound(0x51);
    }
  }
after : {
  s32 a2 = (p->s).work[3] + 0x10;
  (p->s).work[3] = a2;
  (p->s).angle = a2;
}
  {
    s32 t = (p->s).work[2];
    t--;
    (p->s).work[2] = t;
    t = (u8)t;
    if (t == 0xFF) {
      (p->s).mode[1] = 0xC;
      (p->s).mode[2] = 0;
    }
  }
}

// 0x0805C580
void FUN_0805c580(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    register s32 one asm("r6");
    register s32 f asm("r3");
    register struct Zero* z asm("r2");
    {
      register s32 xb asm("r2");
      u32 t = (p->s).flags;
      xb = t >> 4;
      one = 1;
      xb &= one;
      hanu_080ad598(&p->s, 2, xb);
    }
    (p->s).angle = 0;
    InitNonAffineMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, MOTION(0xB5, 6));
    f = 0;
    z = pZero2;
    if ((p->s).coord.x < (z->s).coord.x) {
      f = 1;
    }
    ((p->s).spr).xflip = f;
    f = 0;
    if ((p->s).coord.x < (z->s).coord.x) {
      f = 1;
    }
    {
      register s32 x asm("r1");
      u8* a = (u8*)p + 0x4a;
      s32 sh;
      u8 ov;
      s32 m;
      x = one;
      x &= f;
      sh = x << 4;
      ov = *a;
      m = -0x11;
      m &= ov;
      m |= sh;
      *a = m;
      {
        register u8 nf asm("r0");
        if (x != 0) {
          register u8 k asm("r1");
          nf = (p->s).flags;
          k = 0x10;
          nf |= k;
        } else {
          register u8 fl asm("r1");
          fl = (p->s).flags;
          asm("" : "+r"(fl));
          nf = 0xEF;
          nf &= fl;
        }
        (p->s).flags = nf;
      }
    }
    (p->s).coord.y += 0x1000;
    {
      register s32 z0 asm("r0");
      z0 = 0;
      (p->s).d.y = z0;
    }
    SetDDP(&p->body, &sCollisions[6]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 y = (p->s).coord.y;
    s32 dy = (p->s).d.y;
    (p->s).coord.y = y + dy;
    dy += 0x40;
    (p->s).d.y = dy;
    if (dy > 0x700) {
      (p->s).d.y = 0x700;
    }
  }
  if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) << 16) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

// 0x0805C670
void hanu_0805c670(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    register s32 f asm("r3");
    register struct Zero* z asm("r2");
    SetMotion(&p->s, MOTION(0xB5, 6));
    f = 0;
    z = pZero2;
    if ((p->s).coord.x < (z->s).coord.x) {
      f = 1;
    }
    ((p->s).spr).xflip = f;
    f = 0;
    if ((p->s).coord.x < (z->s).coord.x) {
      f = 1;
    }
    {
      u8* a = (u8*)p + 0x4a;
      s32 sh = f << 4;
      u8 ov = *a;
      s32 m = -0x11;
      m &= ov;
      m |= sh;
      *a = m;
    }
    {
      register u8 nf asm("r0");
      if (f != 0) {
        register u8 kk asm("r1");
        nf = (p->s).flags;
        kk = 0x10;
        nf |= kk;
      } else {
        register u8 fl asm("r1");
        fl = (p->s).flags;
        asm("" : "+r"(fl));
        nf = 0xEF;
        nf &= fl;
      }
      (p->s).flags = nf;
    }
    {
      s32 v;
      register s32 k10 asm("r0");
      register u8 fv2 asm("r1");
      fv2 = *(volatile u8*)&(p->s).flags;
      k10 = 0x10;
      k10 &= fv2;
      if (k10 != 0) {
        (p->s).d.x = -0x180;
        v = -0x1000;
      } else {
        (p->s).d.x = 0xC0 << 1;
        v = 0x80 << 5;
      }
      (p->s).unk_coord.x = v;
    }
    (p->s).d.y = -0x3C0;
    (p->s).work[2] = 0xE;
    PlaySound(0x50);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (((u16)FUN_0805d594(p, (p->s).unk_coord.x, 0) << 16) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  {
    s32 cy = (p->s).coord.y;
    s32 dy = (p->s).d.y;
    (p->s).coord.y = cy + dy;
    (p->s).d.y = dy + 0x40;
  }
  if ((u8)--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 0xE;
    (p->s).mode[2] = 0;
  }
}

void FUN_0805c760(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    GotoMotion(&p->s, MOTION(0xb5, 0x0c), 2, 5);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_0805d594(p, (p->s).unk_coord.x, 0) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 0xf;
    (p->s).mode[2] = 0;
  }
}

u16 FUN_08010d70(s32 x, s32 y);
void FUN_08010dd8(s32 x, s32 y);

// 0x0805C7C4
void hanu_0805c7c4(struct Boss* p) {
  s32 x;
  register s32 m asm("r0");
  if ((p->s).mode[2] == 0) {
    s32 v;
    SetMotion(&p->s, MOTION(0xB5, 0x0D));
    SetDDP(&p->body, &sCollisions[12]);
    if ((p->s).flags & X_FLIP) {
      (p->s).d.x = 0x400;
      v = 0x1000;
    } else {
      (p->s).d.x = -0x400;
      v = -0x1000;
    }
    *(s32*)((u8*)p + 0x64) = v;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  x = (p->s).coord.x + (p->s).d.x;
  (p->s).coord.x = x;
  if (FUN_080098a4(x + *(s32*)((u8*)p + 0x64), (p->s).coord.y) != 0) {
    if (FUN_08010d70((p->s).coord.x + *(s32*)((u8*)p + 0x64), (p->s).coord.y) != 0) {
      FUN_08010dd8((p->s).coord.x + *(s32*)((u8*)p + 0x64), (p->s).coord.y);
    }
    AppendQuake(5, &(p->s).coord);
    PlaySound(0x52);
    if ((p->s).mode[3] == 0) {
      m = 0x10;
      asm("" : "+r"(m));
    } else {
      m = 0x11;
      asm("" : "+r"(m));
    }
    (p->s).mode[1] = m;
    m = 0;
    asm("" : "+r"(m));
    (p->s).mode[2] = m;
  }
}

// 0x0805C87C
void FUN_0805c87c(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    u32 xf;
    u32 xf2;
    SetMotion(&p->s, MOTION(0xB5, 0x0E));
    SetDDP(&p->body, &sCollisions[6]);
    xf = (((p->s).flags >> 4) ^ 1) & 1;
    ((p->s).spr).xflip = xf;
    xf2 = (((p->s).flags >> 4) ^ 1) & 1;
    {
      u8* oa = (u8*)p + 0x4a;
      u32 sh4 = xf2 << 4;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      m11 |= sh4;
      *oa = m11;
    }
    if (xf2 != 0) {
      (p->s).flags |= 0x10;
    } else {
      (p->s).flags &= 0xEF;
    }
    (p->s).d.y = -0x480;
    (p->s).d.x = 0;
    {
      s32 wv;
      register s32* w asm("r4");
      w = (s32*)((u8*)p + 0xb4);
      if (*w == FUN_0800a31c((p->s).coord.x, (p->s).coord.y)) {
        w += 1;
        if (*w == FUN_0800a22c((p->s).coord.x, (p->s).coord.y)) {
          s32* st = (s32*)((u8*)p + 0xc0);
          asm("" : "+r"(st));
          *st = (p->s).coord.y;
          wv = 0xFF;
          goto st;
        }
      }
      wv = 0x1B;
    st:
      (p->s).work[2] = wv;
    }
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 cy asm("r0");
    register s32 dy asm("r1");
    register s32 ny asm("r2");
    cy = (p->s).coord.y;
    dy = (p->s).d.y;
    ny = cy + dy;
    (p->s).coord.y = ny;
    dy += 0x40;
    (p->s).d.y = dy;
    {
      u8 w2 = (p->s).work[2];
      s32 tv = w2;
      asm("" : "+r"(tv));
      if (tv == 0xFF) {
        if (*(s32*)((u8*)p + 0xc0) <= ny) {
          if ((u16)FUN_080098a4((p->s).coord.x, ny) != 0) {
            s32 z;
            (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
            z = 0;
            (p->s).mode[1] = 7;
            (p->s).mode[2] = z;
            *((u8*)p + 0xbe) = z;
          }
        }
      } else {
        if ((u8)--(p->s).work[2] == 0xFF) {
          (p->s).mode[1] = 0xE;
          (p->s).mode[2] = 0;
        }
      }
    }
  }
}

// 0x0805C98C
void hanu_0805c98c(struct Boss* p) {
  register s32 z asm("r5");
  z = (p->s).mode[2];
  if (z == 0) {
    InitRotatableMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, 0xB50D);
    (p->s).angle = 0x60;
    (p->s).d.x = -(p->s).d.x;
    (p->s).d.y = 0xFFFFFC00;
    (p->s).mode[3] = z;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x = (p->s).coord.x + (p->s).d.x;
  if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) << 16) != 0) {
    if (((u16)FUN_08010d70((p->s).coord.x, (p->s).coord.y) << 16) != 0) {
      FUN_08010dd8((p->s).coord.x, (p->s).coord.y);
    }
    PlaySound(0x52);
    AppendQuake(5, &(p->s).coord);
    {
      register s32 v asm("r1");
      register s32 one asm("r2");
      register u8* oa asm("ip");
      s32 v0 = (p->s).flags >> 4;
      one = 1;
      v0 ^= one;
      asm("" : "+r"(v0));
      v0 &= one;
      *((u8*)p + 0x4c) = v0;
      v = (p->s).flags >> 4;
      v ^= one;
      asm("" : "+r"(v));
      v &= one;
      {
        register u8* o0 asm("r0");
        register s32 k asm("r0");
        k = 0x4a;
        asm volatile("add %0, %0, %1" : "+l"(k) : "l"(p));
        o0 = (u8*)k;
        oa = o0;
        {
          register s32 sh asm("r3");
          register s32 ov asm("r2");
          register s32 m11 asm("r0");
          sh = v << 4;
          ov = *o0;
          m11 = 0x11;
          m11 = -m11;
          m11 &= ov;
          m11 |= sh;
          {
            register u8* o1 asm("r2");
            o1 = oa;
            *o1 = m11;
          }
        }
      }
      if (v != 0) {
        register u8 g asm("r0");
        register s32 k10 asm("r1");
        g = (p->s).flags;
        k10 = 0x10;
        g |= k10;
        (p->s).flags = g;
      } else {
        register u8 g2 asm("r0");
        register u8 h2 asm("r1");
        h2 = (p->s).flags;
        asm("" : "+r"(h2));
        g2 = 0xEF;
        g2 &= h2;
        (p->s).flags = g2;
      }
    }
    {
      register s32 cx asm("r0");
      register s32 dx asm("r1");
      cx = (p->s).coord.x;
      dx = (p->s).d.x;
      cx -= dx;
      (p->s).coord.x = cx;
      dx = -dx;
      (p->s).d.x = dx;
    }
  }
  {
    register s32 cy asm("r1");
    register s32 dy asm("r0");
    cy = (p->s).coord.y;
    dy = (p->s).d.y;
    cy += dy;
    (p->s).coord.y = cy;
  }
  if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) << 16) == 0) {
    goto done;
  }
  if (((u16)FUN_08010d70((p->s).coord.x, (p->s).coord.y) << 16) != 0) {
    FUN_08010dd8((p->s).coord.x, (p->s).coord.y);
  }
  PlaySound(0x52);
  AppendQuake(5, &(p->s).coord);
  {
    register s32 v2 asm("r1");
    register s32 one2 asm("r2");
    register u8* ob asm("ip");
    s32 v3 = (p->s).flags >> 5;
    one2 = 1;
    v3 ^= one2;
    asm("" : "+r"(v3));
    v3 &= one2;
    *((u8*)p + 0x4d) = v3;
    v2 = (p->s).flags >> 5;
    v2 ^= one2;
    asm("" : "+r"(v2));
    v2 &= one2;
    {
      register u8* o0 asm("r0");
      register s32 k2 asm("r0");
      k2 = 0x4a;
      asm volatile("add %0, %0, %1" : "+l"(k2) : "l"(p));
      o0 = (u8*)k2;
      ob = o0;
      {
        register s32 sh2 asm("r3");
        register s32 ov2 asm("r2");
        register s32 m21 asm("r0");
        sh2 = v2 << 5;
        ov2 = *o0;
        m21 = 0x21;
        m21 = -m21;
        m21 &= ov2;
        m21 |= sh2;
        {
          register u8* o1 asm("r2");
          o1 = ob;
          *o1 = m21;
        }
      }
    }
    if (v2 != 0) {
      register u8 g3 asm("r0");
      register s32 k20 asm("r1");
      g3 = (p->s).flags;
      k20 = 0x20;
      g3 |= k20;
      (p->s).flags = g3;
    } else {
      register u8 g4 asm("r0");
      register u8 h4 asm("r1");
      h4 = (p->s).flags;
      asm("" : "+r"(h4));
      g4 = 0xDF;
      g4 &= h4;
      (p->s).flags = g4;
    }
  }
  {
    register s32 cy2 asm("r0");
    register s32 dy2 asm("r1");
    cy2 = (p->s).coord.y;
    dy2 = (p->s).d.y;
    cy2 -= dy2;
    (p->s).coord.y = cy2;
    dy2 = -dy2;
    (p->s).d.y = dy2;
    if (dy2 < 0) {
      (p->s).mode[3]++;
    }
  }
done:
  if ((p->s).mode[3] > 1) {
    register s32 zr asm("r1");
    zr = 0;
    (p->s).mode[1] = 0x12;
    (p->s).mode[2] = zr;
  }
}


// 0x0805CB00
void FUN_0805cb00(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    register s32 f asm("r3");
    s32 v;
    (p->s).angle = 0;
    InitNonAffineMotion(&p->s);
    ResetDynamicMotion(&p->s);
    {
      register s32 t asm("r1");
      t = 0;
      if ((p->s).d.x > 0) {
        t = 1;
      }
      ((p->s).spr).xflip = t;
    }
    f = 0;
    if ((p->s).d.x > 0) {
      f = 1;
    }
    {
      u8* a = (u8*)p + 0x4a;
      s32 sh = f << 4;
      u8 ov = *a;
      s32 m = -0x11;
      m &= ov;
      m |= sh;
      *a = m;
    }
    {
      register u8 nf asm("r0");
      if (f != 0) {
        register u8 kk asm("r1");
        nf = (p->s).flags;
        kk = 0x10;
        nf |= kk;
      } else {
        register u8 fl asm("r1");
        fl = (p->s).flags;
        asm("" : "+r"(fl));
        nf = 0xEF;
        nf &= fl;
      }
      (p->s).flags = nf;
    }
    SetMotion(&p->s, MOTION(0xB5, 0x0E));
    SetDDP(&p->body, &sCollisions[6]);
    (p->s).d.y = -0x480;
    {
      register s32 k10 asm("r0");
      register u8 fv2 asm("r1");
      fv2 = *(volatile u8*)&(p->s).flags;
      k10 = 0x10;
      k10 &= fv2;
      if (k10 != 0) {
        (p->s).d.x = 0x80 << 2;
        v = 0x80 << 5;
      } else {
        (p->s).d.x = -0x200;
        v = -0x1000;
      }
    }
    (p->s).unk_coord.x = v;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (((u16)FUN_0805d594(p, (p->s).unk_coord.x, 0) << 16) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  {
    s32 cy = (p->s).coord.y;
    s32 dy = (p->s).d.y;
    (p->s).coord.y = cy + dy;
    (p->s).d.y = dy + 0x40;
  }
  if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) << 16) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

// 0x0805CBFC
void hanu_0805cbfc(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0xB510);
    {
      s32 onR = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        onR = 1;
      }
      ((p->s).spr).xflip = onR;
    }
    {
      s32 onR2 = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        onR2 = 1;
      }
      {
        register u8* t0 asm("r0");
        register u8* oa asm("ip");
        register u32 sh asm("r2");
        u32 off = 0x4a;
        asm("" : "+r"(off));
        off += (u32)p;
        t0 = (u8*)off;
        oa = t0;
        asm("" : "+r"(oa));
        sh = onR2 << 4;
        {
          s32 ov = *t0;
          s32 m11 = -0x11;
          u32 vv;
          register u8* fa asm("r1");
          asm("" : "+r"(m11));
          vv = (m11 & ov) | sh;
          fa = oa;
          asm("" : "+r"(fa));
          *fa = vv;
        }
      }
      if (onR2 != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
    }
    PlaySound(0x50);
    {
      u8 z = 0;
      (p->s).work[2] = 0x28;
      (p->s).mode[3] = z;
    }
    (p->s).mode[2]++;
  }
  if ((p->s).mode[3] == 0) {
    s32 raw = (p->s).work[2] - 1;
    (p->s).work[2] = raw;
    if ((u8)raw == 0xFF) {
      SetMotion(&p->s, 0xB511);
      (p->s).mode[3]++;
    }
  } else if (*(u8*)((u8*)p + 0x73) == 3) {
    u8 z = 0;
    (p->s).mode[1] = 0x14;
    (p->s).mode[2] = z;
  }
  UpdateMotionGraphic(&p->s);
}

u16 FUN_08010d70(s32 x, s32 y);
void FUN_08010dd8(s32 x, s32 y);

// 0x0805CCC0
void hanu_0805ccc0(struct Boss* p) {
  register s32 z6 asm("r6");
  register s32 k20 asm("r5");
  if ((p->s).mode[2] == 0) {
    s32 v;
    SetMotion(&p->s, MOTION(0xB5, 0x12));
    SetDDP(&p->body, &sCollisions[14]);
    if (((p->s).flags & 0x10) != 0) {
      (p->s).coord.x += -0x1000;
      (p->s).d.x = 0x80 << 3;
      v = 0xC0 << 6;
    } else {
      register s32 cx asm("r0");
      register s32 k2 asm("r2");
      cx = (p->s).coord.x;
      k2 = 0x80 << 5;
      asm("" : "+r"(k2));
      (p->s).coord.x = cx + k2;
      (p->s).d.x = -0x400;
      v = -0x3000;
    }
    (p->s).unk_coord.x = v;
    (p->s).d.y = -0x400;
    (p->s).work[2] = 0x14;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 t = (p->s).work[2] - 1;
    z6 = 0;
    (p->s).work[2] = t;
    t <<= 24;
    t = (u32)t >> 24;
    if (t == 0xFF) {
      goto done;
    }
  }
  if (((u16)FUN_0805d594(p, (p->s).unk_coord.x, 0) << 16) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  {
    s32 ny = (p->s).coord.y + (p->s).d.y;
    (p->s).coord.y = ny;
    {
      s32 ax = (p->s).coord.x + (p->s).unk_coord.x;
      k20 = -0x2000;
      if (((u16)FUN_080098a4(ax, ny + k20) << 16) == 0) {
        return;
      }
    }
    if (((u16)FUN_08010d70((p->s).coord.x + (p->s).unk_coord.x, (p->s).coord.y + k20) << 16) != 0) {
      FUN_08010dd8((p->s).coord.x + (p->s).unk_coord.x, (p->s).coord.y + k20);
    }
    PlaySound(0x52);
    AppendQuake(5, &(p->s).coord);
  }
done:
  (p->s).mode[1] = 0x15;
  (p->s).mode[2] = z6;
}

// 0x0805cdbc
void FUN_0805cdbc(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0xB5, 0x13));
    SetDDP(&p->body, &sCollisions[6]);
    if ((p->s).flags & X_FLIP) {
      (p->s).d.x = 0x200;
    } else {
      (p->s).d.x = -0x200;
    }
    (p->s).d.y = 0;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_0805d594(p, (p->s).unk_coord.x, 0) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 7, (p->s).mode[2] = 0;
  }
}

// Hop toward the pillar nearest Zero (props[0] anchor + n*0x3000 lanes),
// with X/Y pushout probes via FUN_0805d594. Everything reproduces except a
// register tie: retail keeps the xflip flag in r3 with the oam byte address
// in callee-saved r4; agbcc swaps them (allocation-cascade basin) and every
// pin either follows the swap or adds a &1 truncation at the bitfield insert.
NON_MATCH void FUN_0805ce50(struct Boss* p) {
#if MODERN
  if ((p->s).mode[2] == 0) {
    s32 on;
    SetMotion(&p->s, MOTION(0xB5, 0x06));
    on = 0;
    if ((p->s).coord.x < (pZero2->s).coord.x) {
      on = 1;
    }
    ((p->s).spr).xflip = on;
    on = 0;
    if ((p->s).coord.x < (pZero2->s).coord.x) {
      on = 1;
    }
    ((p->s).spr).oam.xflip = on;
    if (on != 0) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
    {
      s32 base = *(s32*)&p->props.raw[0];
      s32 t = ((pZero2->s).coord.x - base) / 0x3000;
      base += (t * 3 << 12) + 0x1800;
      (p->s).d.x = (base - (p->s).coord.x) / 0x18;
    }
    (p->s).d.y = -0x600;
    if ((p->s).d.x > 0) {
      (p->s).unk_coord.x = 0x1000;
    } else {
      (p->s).unk_coord.x = -0x1000;
    }
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_0805d594(p, (p->s).unk_coord.x, 0) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  if (FUN_0805d594(p, 0, (p->s).d.y) == 0) {
    (p->s).coord.y += (p->s).d.y;
  }
  (p->s).d.y += 0x40;
  if ((p->s).d.y >= 0) {
    (p->s).mode[1] = 0x17;
    (p->s).mode[2] = 0;
  }
#else
  INCCODE("asm/boss/hanumachine_ce50.inc");
#endif
}


void hanu_0805cf58(struct Boss* p) {
  u8 md = (p->s).mode[2];
  if (md == 0) {
    SetMotion(&p->s, MOTION(0xB5, 0x14));
    PlaySound(0x4E);
    (p->s).d.y = 0x300;
    (p->s).mode[3] = md;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).mode[3] == 0) {
    if ((s8)(p->s).motion.cmdIdx > 2) {
      (p->s).mode[3]++;
    }
  } else {
    s32 st;
    (p->s).coord.y += (p->s).d.y;
    (p->s).d.y += 0x40;
    st = (p->body).status & 4;
    if (st != 0) {
      (p->s).mode[1] = 0x18;
      (p->s).mode[2] = 0;
    } else if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1] = 7;
      (p->s).mode[2] = st;
    }
  }
}

void hanu_080ad598(struct Entity* e, u8 a1, u8 a2);

// 0x0805cfe8
void FUN_0805cfe8(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    if ((p->s).flags & X_FLIP) {
      (p->s).d.x = -0x180;
      (p->s).unk_coord.x = -0x1000;
    } else {
      (p->s).d.x = 0x180;
      (p->s).unk_coord.x = 0x1000;
    }
    (p->s).d.y = -0x3C0;
    hanu_080ad598(&p->s, 3, 0);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_0805d594(p, (p->s).unk_coord.x, 0) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 7, (p->s).mode[2] = 0;
  }
}

// 0x0805D080 -- leap toward Zero, clamped to the arena edge stored at +0xB8.
// The flip pair (one reused flag variable recomputed twice, r5-pinned oam
// pointer) is byte-exact. Blocker (aim-math register rotation): retail keeps
// the Zero-delta in r2 and copies it to r0 for the divide, then builds the
// clamp bound in r2 as well, so {delta, scaled, bound} rotate through
// r0/r1/r2; ours computes the delta in place and loads the +0xB8 bound before
// the scaled value. Statement splits and a keep-alive moved the rotation
// without landing it; 62 bytes.
NON_MATCH void FUN_0805d080(struct Boss* p) {
#if MODERN
  if ((p->s).mode[2] == 0) {
    s32 base;
    s32 t;
    SetMotion(&p->s, MOTION(0xB5, 0x06));
    {
      u32 xf = 0;
      struct Zero* z = pZero2;
      if ((p->s).coord.x < (z->s).coord.x) {
        xf = 1;
      }
      ((p->s).spr).xflip = xf;
      xf = 0;
      if ((p->s).coord.x < (z->s).coord.x) {
        xf = 1;
      }
      {
        register u8* oa asm("r5");
        u32 sh4;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        {
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          m11 |= sh4;
          *oa = m11;
        }
      }
      if (xf != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
    }
    {
      struct Zero* z = pZero2;
      s32* bp = (s32*)((u8*)p + 0xb4);
      s32 zx = (z->s).coord.x;
      base = *bp;
      t = zx - base;
    }
    {
      s32 u = t / 0x3000;
      s32 v = ((u * 3) << 12) + 0x1800;
      if ((p->s).flags & X_FLIP) {
        s32 lim;
        v = base + v;
        v += -0x4800;
        lim = *(s32*)((u8*)p + 0xb8) - 0x1800;
        if (v > lim) {
          v = lim;
        }
      } else {
        s32 lim = base + 0x1800;
        v = base + v + 0x4800;
        if (v < lim) {
          v = lim;
        }
      }
      (p->s).d.x = (v - (p->s).coord.x) / 0x1C;
    }
    if ((p->s).d.x > 0) {
      (p->s).unk_coord.x = 0x1000;
    } else {
      (p->s).unk_coord.x = -0x1000;
    }
    (p->s).d.y = -0x700;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_0805d594(p, (p->s).unk_coord.x, 0) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  if (FUN_0805d594(p, 0, (p->s).d.y) == 0) {
    (p->s).coord.y += (p->s).d.y;
  }
  (p->s).d.y += 0x40;
  if ((p->s).d.y >= 0) {
    u8 z2 = 0;
    (p->s).mode[1] = 0x1A;
    (p->s).mode[2] = z2;
  }
#else
  INCCODE("asm/boss/hanumachine_5d080.inc");
#endif
}

// 0x0805D1C4
void FUN_0805d1c4(struct Boss* p) {
  u8 m = (p->s).mode[2];
  if (m == 0) {
    GotoMotion(&p->s, MOTION(0xb5, 0x0c), 2, 5);
    (p->s).d.x = m;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (*(u8*)((u8*)p + 0x73) == 3) {
    u8 z = 0;
    (p->s).mode[1] = 0x1B;
    (p->s).mode[2] = z;
  }
}

u16 FUN_08010d70(s32 x, s32 y);
void FUN_08010dd8(s32 x, s32 y);

// 0x0805d210
void FUN_0805d210(struct Boss* p) {
  s32 hit;
  if ((p->s).mode[2] == 0) {
    InitRotatableMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, MOTION(0xB5, 0x0D));
    (p->s).angle = 0xE0;
    SetDDP(&p->body, &sCollisions[12]);
    if ((p->s).flags & X_FLIP) {
      (p->s).d.x = 0x400;
    } else {
      (p->s).d.x = -0x400;
    }
    (p->s).d.y = 0x400;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  hit = (u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y);
  if (hit != 0) {
    if (FUN_08010d70((p->s).coord.x, (p->s).coord.y) != 0) {
      FUN_08010dd8((p->s).coord.x, (p->s).coord.y);
    }
    PlaySound(0x52);
    AppendQuake(5, &(p->s).coord);
    (p->s).coord.x -= (p->s).d.x;
    (p->s).mode[1] = 0x1C;
    (p->s).mode[2] = 0;
    return;
  }
  (p->s).coord.y += (p->s).d.y;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    if (FUN_08010d70((p->s).coord.x, (p->s).coord.y) != 0) {
      FUN_08010dd8((p->s).coord.x, (p->s).coord.y);
    }
    PlaySound(0x52);
    AppendQuake(5, &(p->s).coord);
    (p->s).coord.y -= (p->s).d.y;
    (p->s).mode[1] = 0x1C;
    (p->s).mode[2] = hit;
  }
}

// 0x0805d310
void FUN_0805d310(struct Boss* p) {
  u8 m = (p->s).mode[2];
  if (m == 0) {
    (p->s).angle = m;
    InitNonAffineMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, MOTION(0xB5, 0x06));
    SetDDP(&p->body, sCollisions);
    if (((p->s).flags & X_FLIP) != 0) {
      (p->s).d.x = -0x180;
      (p->s).unk_coord.x = -0x1000;
    } else {
      (p->s).d.x = 0x180;
      (p->s).unk_coord.x = 0x1000;
    }
    (p->s).d.y = -0x3C0;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_0805d594(p, (p->s).unk_coord.x, 0) == 0) {
    (p->s).coord.x += (p->s).d.x;
  }
  {
    s32 y = (p->s).coord.y + (p->s).d.y;
    (p->s).coord.y = y;
    (p->s).d.y += 0x40;
    if (FUN_080098a4((p->s).coord.x, y) == 0) {
      return;
    }
  }
  {
    s32 z;
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    z = 0;
    (p->s).mode[1] = 7;
    (p->s).mode[2] = z;
  }
}

// 0x0805D3C8
void FUN_0805d3c8(struct Boss* p) {
  register s32 z asm("r1");
  register s32 nx asm("r4");
  z = (p->s).mode[2];
  if (z == 0) {
    register u8* f asm("r4");
    register s32 one asm("r2");
    *((u8*)p + 0x24) = z;
    InitNonAffineMotion(&p->s);
    ResetDynamicMotion(&p->s);
    SetMotion(&p->s, 0xB502);
    SetDDP(&p->body, &sCollisions[0]);
    f = (u8*)p + 0xbc;
    {
      register s32 v asm("r0");
      register s32 fv asm("r1");
      fv = *f;
      one = 1;
      v = one;
      v &= fv;
      *((u8*)p + 0x4c) = v;
    }
    {
      register u8* oa asm("ip");
      register s32 v2 asm("r1");
      register s32 fv2 asm("r0");
      fv2 = *f;
      oa = (u8*)p + 0x4a;
      v2 = one;
      v2 &= fv2;
      v2 <<= 4;
      {
        register s32 ov asm("r3");
        register s32 m asm("r0");
        ov = *oa;
        m = -0x11;
        m &= ov;
        m |= v2;
        *oa = m;
      }
    }
    {
      register s32 fv3 asm("r0");
      fv3 = *f;
      one &= fv3;
    }
    if (one != 0) {
      register s32 g asm("r0");
      register s32 k asm("r1");
      g = (p->s).flags;
      asm("" : "+r"(g));
      k = 0x10;
      g |= k;
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
    if (((p->s).flags & X_FLIP) != 0) {
      if ((u16)FUN_080098a4((p->s).coord.x + -0x1200, (p->s).coord.y + -0x800)) {
        (p->s).coord.x = FUN_0800a31c((p->s).coord.x + -0x1200, (p->s).coord.y + -0x800) + (0x90 << 5);
      }
      (p->s).d.x = -0x200;
      (p->s).unk_coord.x = -0x1000;
    } else {
      if ((u16)FUN_080098a4((p->s).coord.x + (0x90 << 5), (p->s).coord.y + -0x800)) {
        (p->s).coord.x = FUN_0800a22c((p->s).coord.x + (0x90 << 5), (p->s).coord.y + -0x800) + -0x1200;
      }
      (p->s).d.x = 0x80 << 2;
      (p->s).unk_coord.x = 0x80 << 5;
    }
    (p->s).d.y = -0x400;
    (p->s).work[2] = 0x10;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 a asm("r0");
    register s32 b asm("r1");
    a = (p->s).coord.x;
    b = (p->s).d.x;
    a += b;
    b = (p->s).unk_coord.x;
    nx = a + b;
  }
  if ((u16)FUN_080098a4(nx, (p->s).coord.y) == 0) {
    if (((p->s).flags & X_FLIP) != 0) {
      if (nx <= *(s32*)((u8*)p + 0xb4)) {
        goto skip;
      }
      goto move;
    } else {
      if (nx < *(s32*)((u8*)p + 0xb8)) {
      move:
        (p->s).coord.x += (p->s).d.x;
      }
    }
  }
skip:;
  {
    register s32 cy asm("r1");
    register s32 dy asm("r0");
    cy = (p->s).coord.y;
    dy = (p->s).d.y;
    cy += dy;
    (p->s).coord.y = cy;
    dy += 0x40;
    (p->s).d.y = dy;
    if ((u16)FUN_080098a4((p->s).coord.x, cy)) {
      register s32 zz asm("r1");
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      zz = 0;
      (p->s).mode[1] = 3;
      (p->s).mode[2] = zz;
    }
  }
}


void FUN_0805d568(struct Body* body) {
  if (body->hitboxFlags & 1) {
    struct Boss* atk = (struct Boss*)((body->enemy)->parent);
    struct Boss* self = (struct Boss*)body->parent;
    u8 r = 0;
    if ((atk->s).coord.x > (self->s).coord.x) {
      r = 1;
    }
    *(u8*)((u8*)self + 0xbc) = r;
  }
}

u16 FUN_0805d594(struct Boss* p, s32 a, s32 b) {
  u16 r = FUN_080098a4((p->s).coord.x + a, (p->s).coord.y);
  if (r != 0) {
    return r;
  }
  r = FUN_080098a4((p->s).coord.x + a, (p->s).coord.y - 0x2000);
  if (r != 0) {
    return r;
  }
  return 0;
}

void Hanumachine_Init(struct Boss* p);
void Hanumachine_Update(struct Boss* p);
void Hanumachine_Die(struct Boss* p);

// clang-format off
const BossRoutine gHanumachineRoutine = {
    [ENTITY_INIT] =      (BossFunc)Hanumachine_Init,
    [ENTITY_UPDATE] =    (BossFunc)Hanumachine_Update,
    [ENTITY_DIE] =       (BossFunc)Hanumachine_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void hanu_0805bcfc(struct Boss* p);
void hanu_0805bd38(struct Boss* p);
void hanu_0805bdc0(struct Boss* p);
void hanu_0805bf10(struct Boss* p);
void hanu_0805bf60(struct Boss* p);
void hanu_0805c0d0(struct Boss* p);
void hanu_0805c198(struct Boss* p);
void hanu_0805c2a4(struct Boss* p);
void hanu_0805c30c(struct Boss* p);
void FUN_0805c3cc(struct Boss* p);
void FUN_0805c404(struct Boss* p);
void hanu_0805c4a4(struct Boss* p);
void FUN_0805c580(struct Boss* p);
void hanu_0805c670(struct Boss* p);
void FUN_0805c760(struct Boss* p);
void hanu_0805c7c4(struct Boss* p);
void FUN_0805c87c(struct Boss* p);
void hanu_0805c98c(struct Boss* p);
void FUN_0805cb00(struct Boss* p);
void hanu_0805cbfc(struct Boss* p);
void hanu_0805ccc0(struct Boss* p);
void FUN_0805cdbc(struct Boss* p);
void FUN_0805ce50(struct Boss* p);
void hanu_0805cf58(struct Boss* p);
void FUN_0805cfe8(struct Boss* p);
void FUN_0805d080(struct Boss* p);
void FUN_0805d1c4(struct Boss* p);
void FUN_0805d210(struct Boss* p);
void FUN_0805d310(struct Boss* p);
void FUN_0805d3c8(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[30] = {
    hanu_0805bcfc,
    hanu_0805bd38,
    hanu_0805bdc0,
    hanu_0805bf10,
    hanu_0805bf60,
    hanu_0805c0d0,
    hanu_0805c198,
    hanu_0805c2a4,
    hanu_0805c30c,
    FUN_0805c3cc,
    FUN_0805c404,
    hanu_0805c4a4,
    FUN_0805c580,
    hanu_0805c670,
    FUN_0805c760,
    hanu_0805c7c4,
    FUN_0805c87c,
    hanu_0805c98c,
    FUN_0805cb00,
    hanu_0805cbfc,
    hanu_0805ccc0,
    FUN_0805cdbc,
    FUN_0805ce50,
    hanu_0805cf58,
    FUN_0805cfe8,
    FUN_0805d080,
    FUN_0805d1c4,
    FUN_0805d210,
    FUN_0805d310,
    FUN_0805d3c8,
};
// clang-format on

void FUN_0805bcdc(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[30] = {
    NULL,
    NULL,
    FUN_0805bcdc,
    FUN_0805bcdc,
    FUN_0805bcdc,
    NULL,
    NULL,
    FUN_0805bcdc,
    FUN_0805bcdc,
    FUN_0805bcdc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    FUN_0805bcdc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
// clang-format on

// --------------------------------------------

// 0x08364e38
static const struct Collision sCollisions[22] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(13), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(2), -PIXEL(12), PIXEL(31), PIXEL(22)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(2), -PIXEL(12), PIXEL(31), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(4), -PIXEL(14), PIXEL(23), PIXEL(34)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(4), -PIXEL(14), PIXEL(23), PIXEL(34)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(2), -PIXEL(18), PIXEL(19), PIXEL(46)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(2), -PIXEL(18), PIXEL(19), PIXEL(46)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(10), PIXEL(36), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(10), PIXEL(36), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(42), PIXEL(42)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(0), PIXEL(42), PIXEL(42)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(2), PIXEL(22), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(2), PIXEL(22), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(18), -PIXEL(50), PIXEL(11), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(40), -PIXEL(41), PIXEL(11), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(11), -PIXEL(44), PIXEL(47), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(2), -PIXEL(13), PIXEL(21), PIXEL(33)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(2), -PIXEL(13), PIXEL(21), PIXEL(33)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(10), -PIXEL(16), PIXEL(8), PIXEL(65)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(22), PIXEL(26), PIXEL(33)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(22), PIXEL(26), PIXEL(33)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(14)};
