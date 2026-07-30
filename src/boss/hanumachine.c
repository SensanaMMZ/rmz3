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

INCASM("asm/boss/hanumachine_p1_b_p2_p2b.inc");

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

INCASM("asm/boss/hanumachine_p1_b_p2_p2c.inc");

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

INCASM("asm/boss/hanumachine_p2_p1.inc");

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

INCASM("asm/boss/hanumachine_p2_p1b.inc");

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

INCASM("asm/boss/hanumachine_p2_p1d.inc");

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

INCASM("asm/boss/hanumachine_p2_p1e.inc");

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
