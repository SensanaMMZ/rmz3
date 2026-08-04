#include "physics.h"
#include "collision.h"
#include "mod.h"
#include "enemy.h"
#include "global.h"
#include "trig.h"
#include "story.h"
#include "zero.h"

static const struct Collision sCollisions[];

s32 FUN_0800a40c(s32 x, s32 y);

// 0x08075AA8
void FUN_08075aa8(struct Enemy* p) {
  s32 hit;
  s32 v;
  register s32 r asm("r2");
  hit = 0;
  r = FUN_0800a40c((p->s).coord.x, (p->s).coord.y + 0x200);
  if (r == 0) {
    goto zero;
  }
  if (r >= 0) {
    goto pos;
  }
  {
    s32 x;
    u16 mm;
    x = (p->s).coord.x;
    (p->s).coord.x = x - 0x80;
    mm = GetMetatileAttr(x - 0x280, (p->s).coord.y + 0x200) & 0x400;
    hit = mm != 0;
  }
  goto check;
pos:
  {
    s32 x = (p->s).coord.x;
    (p->s).coord.x = x + 0x80;
    if ((GetMetatileAttr(x + 0x280, (p->s).coord.y + 0x200) & 0x400) == 0) {
      goto check;
    }
  }
  goto bump;
zero:
  if (GetMetatileAttr((p->s).coord.x, (p->s).coord.y + 0x200) & 0x400) {
    hit = 1;
  }
check:
  if (hit == 0) {
    s32 g;
    register s32 d asm("r2");
    s32 cy;
    if (!((bool16 (*)(s32, s32))FUN_080098a4)((p->s).coord.x, (p->s).coord.y + 0x600)) {
      return;
    }
    g = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    d = g;
    asm("" : "+r"(d));
    cy = (p->s).coord.y;
    d -= cy;
    if ((u32)(d + 0x3FF) > 0x7FE) {
      return;
    }
    v = cy + d;
    goto store;
  }
bump:
  v = (p->s).coord.y + 0x80;
store:
  (p->s).coord.y = v;
}

#include "entity/macros.h"

void FUN_08075b74(struct Entity* e, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).unk_28 = e;
    p->props[5] = n;
  }
}

void FUN_08075bd0(struct Entity* e) {
  s32 i;

  for (i = 0; i <= 1; i++) {
    struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

    if (p != NULL) {
      (p->s).taskCol = 24;
      INIT_ENEMY_ROUTINE(p, 22);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = (p->s).uniqueID;
      (p->s).work[0] = 2;
      (p->s).work[1] = i;
      (p->s).coord.x = e->coord.x;
      (p->s).coord.y = e->coord.y;
      p->props[5] = 0;
    }
  }
}

// 0x08075C40
void FUN_08075c40(s32 x, s32 y, s32 dx, s32 dy) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    u32 one;
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    {
      u32 t = RNG_0202f388 * 0x343FD + 0x269EC3;
      t <<= 1;
      RNG_0202f388 = t >> 1;
      {
        u32 sh = t >> 0x11;
        one = 1;
        (p->s).work[1] = sh & one;
      }
    }
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = dx;
    (p->s).d.y = dy;
    *(u8*)((u8*)p + 0xb9) = one;
  }
}

#include "stagerun.h"
#include "camera.h"

void summonPurpleNerple(struct Entity* e, s32 x) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 22);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 3;
    (p->s).coord.x = x;
    (p->s).coord.y = (&gStageRun.vm.camera)->viewport.y - PIXEL(112);
    (p->s).unk_28 = e;
    *(s32*)&p->props[8] = e->coord.x;
  }
}

static void nop_08075d3c(struct Body* _a UNUSED, struct Coord* _b UNUSED, struct Coord* _c UNUSED) {}


void PurpleNerple_Die(struct Enemy* p);

// 0x08075d40
bool8 FUN_08075d40(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    switch ((p->s).work[0]) {
      case 0: {
        u32 st = (p->body).status;
        if (st & BODY_STATUS_SLASHED) {
          (p->s).mode[1] = 1;
        } else if (st & BODY_STATUS_RECOILED) {
          (p->s).mode[1] = 5;
        } else {
          (p->s).mode[1] = 0;
        }
        break;
      }
      case 1:
        if ((p->s).unk_28 != NULL) {
          *((u8*)(p->s).unk_28 + 0xb8) = 1;
        }
        (p->s).mode[1] = 2;
        break;
      case 2:
        (p->s).mode[1] = 4;
        break;
    }
    PurpleNerple_Die(p);
    return TRUE;
  }
  return FALSE;
}

extern const EnemyFunc PTR_ARRAY_083670d0[10];
extern const EnemyFunc PTR_ARRAY_083670f8[10];
void FUN_08075aa8(struct Enemy* p);

// 0x08075DC8
bool8 FUN_08075dc8(struct Enemy* p) {
  if ((p->s).mode[1] == 8) return FALSE;
  if (*(u32*)&p->props[0] != 0) return FALSE;
  switch ((p->s).mode[3]) {
    case 0:
      if ((p->s).work[0] == 1) return FALSE;
      if (!IsFrozen(&p->s)) return FALSE;
      (PTR_ARRAY_083670d0[(p->s).mode[1]])(p);
      (PTR_ARRAY_083670f8[(p->s).mode[1]])(p);
      (p->s).mode[3]++;
      UpdateMotionGraphic(&p->s);
      return TRUE;
    case 1:
      if ((p->s).work[0] == 0 || (p->s).work[0] == 3) {
        if (p->props[4] != 0) {
          FUN_08075aa8(p);
          SetMotion(&p->s, MOTION(0x2A, 0x04));
          UpdateMotionGraphic(&p->s);
        }
      }
      if (IsFrozen(&p->s)) {
        if (((p->body).status & 0x00020001) == 0x00020001) {
          (p->s).mode[3] = 0;
          return FALSE;
        }
        return TRUE;
      }
      (p->s).mode[3] = 0;
      return FALSE;
  }
  return FALSE;
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_08075e8c(struct Enemy* p) {
  struct VFX** slot;
  u32 frozen;

  if ((p->s).work[0] == 0) {
    slot = (struct VFX**)&p->props[0];
    if (*slot == NULL && ((p->body).status & 1)) {
      frozen = (p->body).status & 0x20000;
      if (frozen != 0) {
        (p->s).mode[1] = 8;
        (p->s).mode[2] = 0;
      } else {
        *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
        if (*slot != NULL) {
          (p->s).mode[1] = 0;
          (p->s).mode[2] = 0;
        }
      }
    }
  }
}

static const u8 sInitModes[4];

void PurpleNerple_Update(struct Enemy* p);

void PurpleNerple_Init(struct Enemy* p) {
  register s32 z5 asm("r5");
  register struct Body* body asm("r4");
  {
    u8 w0 = (p->s).work[0];
    if (w0 == 0) {
      p->props[5] = w0;
    }
  }
  if ((p->s).work[0] == 3) {
    u8* t = &p->props[5];
    u8 z1 = 0;
    *t = 1;
    (p->s).work[0] = z1;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  {
    u8 m1 = sInitModes[(p->s).work[0]];
    z5 = 0;
    (p->s).mode[1] = m1;
  }
  (p->s).flags |= FLIPABLE;
  body = NULL;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  *(s32*)&p->props[0] = z5;
  switch ((p->s).work[0]) {
    case 0:
      FUN_08075b74((struct Entity*)p, p->props[5]);
      if (MOD_ENABLED(gSystemSavedataManager.mods, 99) && !FLAG(gCurStory.s.gameflags, DEMO_PLAY)) {
        (p->s).flags |= COLLIDABLE;
        body = &p->body;
        InitBody(body, sCollisions, &(p->s).coord, 8);
        body->parent = (void*)p;
        body->fn = (BodyFunc)z5;
      } else {
        {
          register u8 f1 asm("r1");
          register s32 c4 asm("r0");
          f1 = (p->s).flags;
          c4 = 4;
          z5 = 0;
          asm("" : "+r"(z5));
          c4 |= f1;
          (p->s).flags = c4;
        }
        body = &p->body;
        InitBody(body, sCollisions, &(p->s).coord, 4);
        body->parent = (void*)p;
        body->fn = (BodyFunc)z5;
      }
      p->props[4] = 0;
      *(s32*)&p->props[12] = (p->s).coord.x;
      break;
    case 1:
      goto c12;
    case 2:
    c12: {
      {
        register s32 v0 asm("r0");
        register s32 c1 asm("r1");
        v0 = (p->s).flags;
        c1 = 4;
        v0 |= c1;
        (p->s).flags = v0;
      }
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 2);
      body->parent = (void*)p;
      body->fn = nop_08075d3c;
      break;
    }
  }
  PurpleNerple_Update(p);
}



extern const EnemyFunc PTR_ARRAY_083670d0[10];
extern const EnemyFunc PTR_ARRAY_083670f8[10];
bool8 FUN_08075d40(struct Enemy* p);
void FUN_08075e8c(struct Enemy* p);
bool8 FUN_08075dc8(struct Enemy* p);
void PurpleNerple_Die(struct Enemy* p);

void PurpleNerple_Update(struct Enemy* p) {
  if ((p->s).work[0] != 0) {
    u8 prop = *(u8*)((u8*)p + 0xb9);
    if (prop == 0 && (gCurStory.s.gameflags[4] & 0x40)) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      (p->body).status = prop;
      (p->body).prevStatus = prop;
      (p->body).invincibleTime = prop;
      (p->s).flags &= ~COLLIDABLE;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
  }
  if ((p->s).work[0] == 0) {
    if (*(u8*)((u8*)p + 0xb9) != 0) {
      if (((p->s).unk_28)->mode[0] > 1) {
        (p->s).unk_28 = NULL;
      }
    }
  }
  if (FUN_08075d40(p)) {
    return;
  }
  FUN_08075e8c(p);
  if (FUN_08075dc8(p)) {
    return;
  }
  (PTR_ARRAY_083670d0[(p->s).mode[1]])(p);
  (PTR_ARRAY_083670f8[(p->s).mode[1]])(p);
}

extern const EnemyFunc PTR_ARRAY_08367120[6];

void PurpleNerple_Die(struct Enemy* p) {
  u8 v = p->props[5];
  if (v == 0 && FLAG(gCurStory.s.gameflags, 38)) {
    u8 f = ~DISPLAY & (p->s).flags;
    f = f & ~FLIPABLE;
    (p->s).flags = f;
    (p->body).status = v;
    (p->body).prevStatus = v;
    (p->body).invincibleTime = v;
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (PTR_ARRAY_08367120[(p->s).mode[1]])(p);
  }
}

void FUN_08076140(struct Enemy* p) {}


void FUN_08076144(struct Enemy* p) {
  if (p->props[4] != 0) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}


void FUN_08076178(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

void FUN_08076198(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

void FUN_080761b8(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      if (p->props[4] != 0) {
        (p->s).mode[1] = 4;
      } else {
        (p->s).mode[1] = 2;
      }
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

// 0x08076220
void FUN_08076220(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      if (p->props[4] != 0) {
        SetMotion(&p->s, MOTION(0x2A, 0x04));
        (p->s).work[2] = 0;
      } else {
        SetMotion(&p->s, MOTION(0x2A, 0x02));
        (p->s).work[2] = 1;
      }
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 r;
      s32 dy;
      s32 push;
      if (p->props[4] != 0) {
        if ((p->s).work[2] != 0) {
          (p->s).work[2] = 0;
          SetMotion(&p->s, MOTION(0x2A, 0x04));
          UpdateMotionGraphic(&p->s);
        }
        FUN_08075aa8(p);
      }
      r = IsFrozen(&p->s);
      if (r != 0) break;
      dy = (p->s).d.y + 0x40;
      (p->s).d.y = dy;
      if (dy > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (push < 0 && push > -0x800) {
        (p->s).d.y = r;
        (p->s).coord.y += push;
      }
      break;
    }
  }
}

// 0x080762EC
void FUN_080762ec(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 xf asm("r2");
      SetDDP(&p->body, &sCollisions[1]);
      xf = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        xf = 1;
      }
      if (xf != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
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
      SetMotion(&p->s, 0x2A02);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register struct Camera* cam asm("r1");
      register s32 cx asm("r3");
      register s32 vx asm("r2");
      cam = &gStageRun.vm.camera;
      (p->s).coord.y = cam->viewport.y - 0x7000;
      cx = (p->s).coord.x;
      {
        register s32 t asm("r0");
        register s32 lim asm("r1");
        t = cx + 0x7800;
        vx = cam->viewport.x;
        t -= vx;
        lim = 0x2000;
        if (t > lim) {
          register s32 t2 asm("r0");
          register s32 lim2 asm("r1");
          t2 = cx + -0x77FF;
          t2 -= vx;
          lim2 = -0x2000;
          if (t2 < lim2) {
            goto adv;
          }
        }
      }
      if (*((u8*)p + 0xb9) == 0) {
        goto skip;
      }
    adv:
      (p->s).mode[2]++;
    skip:
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).d.y = 0x300;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      register s32 cy asm("r1");
      UpdateMotionGraphic(&p->s);
      {
        register s32 dy asm("r0");
        cy = (p->s).coord.y;
        dy = (p->s).d.y;
        cy += dy;
      }
      (p->s).coord.y = cy;
      if (cy > (pZero2->s).coord.y) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
    }
  }
}

void FUN_080763f8(struct Enemy* p) {
  register s32 m asm("r4");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32 v;
      s32 c;
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0x2A, 0x02));
      c = -0x140;
      (p->s).d.x = c;
      v = c;
      if (((p->s).flags & X_FLIP) != 0) {
        v = 0x140;
      }
      (p->s).d.x = v;
      (p->s).d.y = m;
      *(s32*)((u8*)p + 0x64) = m;
      (p->s).unk_coord.y = (p->s).coord.y;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1:
      if ((u32)((p->s).coord.x - *(s32*)((u8*)p + 0xc0) + 0x16800) > 0x2D000) {
        (p->s).d.y -= 0x40;
        (p->s).coord.y += (p->s).d.y;
      } else {
        s32 t = *(s32*)((u8*)p + 0x64) + 1;
        *(s32*)((u8*)p + 0x64) = t;
        (p->s).coord.x += (p->s).d.x;
        (p->s).coord.y = (p->s).unk_coord.y;
        (p->s).coord.y = (p->s).unk_coord.y + SIN((t << 8) / 0x4C) * 24;
      }
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0xb9) != 0) {
        if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
          (p->s).flags &= ~DISPLAY;
          (p->s).flags &= ~FLIPABLE;
          EXIT_BODY(p);
          SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        }
      }
      break;
  }
}

// 0x08076508
void FUN_08076508(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  u8 m;
  switch ((p->s).mode[2]) {
    case 0: {
      register u8 f asm("r0");
      register u8 t asm("r1");
      t = (p->s).flags;
      f = 0xFE;
      f &= t;
      (p->s).flags = f;
      asm volatile("" ::"r"(t));
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      (p->s).coord.x = (q->coord).x;
      (p->s).coord.y = (q->coord).y;
      break;
  }
  m = q->mode[0];
  if (m > 1) {
    register s32 z asm("r5");
    z = 0;
    (p->s).mode[1] = 5;
    (p->s).mode[2] = z;
  } else if (m == 4) {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    register s32 z asm("r2");
    u8* qq;
    t = (p->s).flags;
    f = 0xFE;
    f &= t;
    asm volatile("" ::"r"(t));
    z = 0;
    k2 = 0xFD;
    f &= k2;
    (p->s).flags = f;
    qq = (u8*)p + 0x8c;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *qq = z;
    {
      register u8 f3 asm("r0");
      register u8 t3 asm("r1");
      t3 = (p->s).flags;
      f3 = 0xFB;
      f3 &= t3;
      (p->s).flags = f3;
      asm volatile("" ::"r"(t3));
    }
    SET_ENEMY_ROUTINE(p, 3);
  }
}

#include "physics.h"

// 0x08076594
void FUN_08076594(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).d.y = m;
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0x2A, 0x04));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 v = (p->s).d.y + 0x40;
      s32 r;
      (p->s).d.y = v;
      if (v > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (r < 0) {
        if (r > -0x800) {
          (p->s).coord.y += r;
          if (*((u8*)p + 0xb9) != 0) {
            (p->s).mode[1] = 9;
          } else {
            (p->s).mode[1] = 6;
          }
          (p->s).mode[2] = 0;
        } else {
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          (p->s).mode[1] = 0;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x08076638
void FUN_08076638(struct Enemy* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).d.y = m;
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, 0x2A04);
      (p->s).work[2] = 0x64;
      (p->s).work[3] = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).work[2] = 0x3C;
      SetMotion(&p->s, 0x2A05);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = 3;
        FUN_08075bd0(&p->s);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
  {
    register s32 k asm("r5");
    register s32 gx asm("r0");
    register s32 gy asm("r1");
    {
      register s32 cx asm("r0");
      register s32 cy asm("r1");
      s32 r;
      cx = (p->s).coord.x;
      cy = (p->s).coord.y;
      k = 0x200;
      cy += k;
      r = FUN_0800a40c(cx, cy);
      asm volatile("add %0, %1, #0" : "=&l"(gy) : "l"(r));
    }
    if (gy == 0) {
      goto zero;
    }
    if (gy >= 0) {
      goto pos;
    }
    {
      register s32 cx2 asm("r0");
      register s32 nx asm("r1");
      cx2 = (p->s).coord.x;
      nx = cx2;
      nx -= 0x80;
      (p->s).coord.x = nx;
      gx = cx2 + -0x280;
      gy = (p->s).coord.y;
      asm("" : "+r"(gy));
      gy += k;
      goto call;
    }
  pos:
    {
      register s32 cx3 asm("r1");
      register s32 nx3 asm("r0");
      cx3 = (p->s).coord.x;
      nx3 = cx3;
      nx3 += 0x80;
      (p->s).coord.x = nx3;
      gx = cx3 + 0x280;
      gy = (p->s).coord.y + k;
      goto call;
    }
  zero:
    gx = (p->s).coord.x;
    gy = (p->s).coord.y + 0x200;
  call:
    if (GetMetatileAttr(gx, gy) & 0x400) {
      (p->s).work[3] = 1;
    }
  }
  m = (p->s).work[3];
  if (m != 0) {
    goto simple;
  }
  {
    s32 dy = (p->s).d.y + 0x40;
    s32 push;
    (p->s).d.y = dy;
    if (dy > 0x700) {
      (p->s).d.y = 0x700;
    }
    (p->s).coord.y += (p->s).d.y;
    push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
    if (push < 0) {
      (p->s).coord.y += push;
      (p->s).d.y = m;
    }
  }
  return;
simple:
  (p->s).coord.y += 0x80;
}

// 0x08076780
void FUN_08076780(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8 fv asm("r0");
      u8 t = (p->s).flags;
      fv = DISPLAY;
      fv |= t;
      (p->s).flags = fv;
      (p->s).d.y = m;
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, MOTION(0x2A, 0x03));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 v = (p->s).d.y - 0x20;
      (p->s).d.y = v;
      if (v < -0x700) {
        (p->s).d.y = -0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
        register u8 f asm("r0");
        register u8 t asm("r1");
        register u8 k2 asm("r1");
        register s32 z asm("r2");
        u8* qq;
        t = (p->s).flags;
        f = 0xFE;
        f &= t;
        asm volatile("" ::"r"(t));
        z = 0;
        k2 = 0xFD;
        f &= k2;
        (p->s).flags = f;
        qq = (u8*)p + 0x8c;
        asm("" : "+r"(qq));
        *(s32*)qq = z;
        asm("" : "+r"(qq));
        qq += 4;
        asm("" : "+r"(qq));
        *(s32*)qq = z;
        asm("" : "+r"(qq));
        qq += 4;
        asm("" : "+r"(qq));
        *qq = z;
        {
          register u8 f3 asm("r0");
          register u8 t3 asm("r1");
          t3 = (p->s).flags;
          f3 = 0xFB;
          f3 &= t3;
          (p->s).flags = f3;
          asm volatile("" ::"r"(t3));
        }
        SET_ENEMY_ROUTINE(p, 3);
      }
      break;
    }
  }
}


// 0x08076830
void FUN_08076830(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      motion_t m;
      u8 w1;
      SetDDP(&p->body, &sCollisions[4]);
      w1 = (p->s).work[1];
      m = MOTION(0x2A, 0x07);
      if (w1 == 0) {
        m = MOTION(0x2A, 0x06);
      }
      SetMotion(&p->s, m);
      if (*((u8*)p + 0xb9) == 0) {
        (p->s).d.x = (p->s).work[1] * 0x266 - 0x133;
        (p->s).d.y = -0x4E0;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 v;
      s32 y;
      (p->s).coord.x += (p->s).d.x;
      v = (p->s).d.y + 0x40;
      (p->s).d.y = v;
      if (v > 0x700) {
        (p->s).d.y = 0x700;
      }
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      if (FUN_080098a4((p->s).coord.x, y) != 0) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = 4;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_08076b30(struct Enemy* p);

// 0x080768E0
void FUN_080768e0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dx asm("r1");
      register s32 dy asm("r0");
      register s32 len asm("r5");
      struct Zero* z;
      SetDDP(&p->body, &sCollisions[6]);
      if (*((u8*)p + 0xb8) != 0) {
        SetMotion(&p->s, MOTION(0x2A, 4));
      } else {
        SetMotion(&p->s, MOTION(0x2A, 2));
      }
      z = pZero2;
      dx = (p->s).coord.x;
      dx -= (z->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).coord.y + -0x1800;
      dy -= (z->s).coord.y;
      (p->s).d.y = dy;
      dx >>= 8;
      len = dx * dx;
      dy >>= 8;
      {
        s32 u = dy * dy;
        len += u;
      }
      len = (u32)Sqrt(len) << 8;
      if (len != 0) {
        s32 a = ((p->s).d.x << 8) / len;
        s32 b;
        (p->s).d.x = a;
        b = ((p->s).d.y << 8) / len;
        (p->s).d.x = a * 6;
        (p->s).d.y = b * 6;
      } else {
        (p->s).d.x = 0xC0 << 3;
        (p->s).d.y = len;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 nx asm("r0");
      register s32 vx asm("r1");
      register s32 r asm("r5");
      s32 v;
      s32 cy;
      s32 vy;
      s32 ny;
      if (*((u8*)p + 0xb8) != 0) {
        SetMotion(&p->s, MOTION(0x2A, 4));
      } else {
        SetMotion(&p->s, MOTION(0x2A, 2));
      }
      UpdateMotionGraphic(&p->s);
      nx = (p->s).coord.x;
      vx = (p->s).d.x;
      nx += vx;
      (p->s).coord.x = nx;
      if (vx < 0) {
        r = PushoutToRight1(nx, (p->s).coord.y);
        if (r > 0) {
          (p->s).coord.x += r;
          asm volatile("" ::: "cc");
          goto hit;
        }
      } else {
        r = PushoutToLeft1(nx, (p->s).coord.y);
        if (r < 0) {
          (p->s).coord.x = (p->s).coord.x + r;
          asm volatile("" : "+r"(r));
          goto hit;
        }
      }
      if ((*(u32*)((u8*)p + 0x8c) & 4) == 0) {
        goto cont;
      }
    hit:
      FUN_08076b30(p);
      break;
    cont:
      v = (p->s).d.y + 0x40;
      (p->s).d.y = v;
      if (v > 0x700) {
        (p->s).d.y = 0x700;
      }
      cy = (p->s).coord.y;
      vy = (p->s).d.y;
      ny = cy + vy;
      (p->s).coord.y = ny;
      if (vy <= 0) {
        break;
      }
      r = PushoutToUp1((p->s).coord.x, ny);
      if (r >= 0) {
        break;
      }
      (p->s).coord.y += r;
      FUN_08076b30(p);
      break;
    }
  }
}

// 0x08076A50
void FUN_08076a50(struct Enemy* p) {
  register struct Entity* q asm("r1");
  q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, (const struct Collision*)0x08367150);
      SetMotion(&p->s, MOTION(0x2A, 0x04));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 nx = (p->s).coord.x + 0x80;
      (p->s).coord.x = nx;
      (p->s).coord.y = FUN_08009f6c(nx, (p->s).coord.y);
      if ((p->s).coord.x > *(s32*)((u8*)p + 0xbc) - 0x1000) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 2:
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      register s32 t asm("r2");
      (p->s).coord.x += 0x80;
      (p->s).coord.y += 0x80;
      {
        register s32 u asm("r0");
        u = (p->s).work[2];
        u--;
        (p->s).work[2] = u;
        u <<= 24;
        t = (u32)u >> 24;
      }
      if (t == 0) {
        if (q != NULL) {
          *((u8*)q + 0xba) = 1;
        }
        {
          register u8 g asm("r0");
          register u8 h asm("r1");
          h = (p->s).flags;
          asm("" : "+r"(h));
          g = 0xFE;
          g &= h;
          h = 0xFD;
          g &= h;
          (p->s).flags = g;
        }
        {
          u8* a = (u8*)p + 0x8c;
          *(u32*)a = t;
          asm("" : "+r"(a));
          a += 4;
          asm("" : "+r"(a));
          *(u32*)a = t;
          asm("" : "+r"(a));
          a += 4;
          asm("" : "+r"(a));
          *a = t;
        }
        (p->s).flags &= 0xFB;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

#include "mission.h"

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
static const motion_t sMotions[9];

// 0x08076b30
void FUN_08076b30(struct Enemy* p) {
  struct Coord c;
  struct Coord* co;
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    u8* qq = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(qq));
    z = 0;
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *qq = z;
    t = (p->s).flags;
    f = 0xFB;
    f &= t;
    asm volatile("" ::"r"(t));
    k2 = 0xFE;
    f &= k2;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  if (*((u8*)p + 0xb9) != 0) {
    FUN_080b7ffc(&p->s, &c, (motion_t*)sMotions, 3);
  } else {
    FUN_080b7f70(&p->s, &c, (motion_t*)sMotions, 3);
  }
  co = &(p->s).coord;
  TryDropItem(3, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);
void FUN_080b84f4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);
void FUN_080b857c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);
void FUN_08076b30(struct Enemy* p);

// 0x08076BE4
void FUN_08076be4(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dir asm("r6");
      register s32 z4 asm("r4");
      {
        register s32 d3 asm("r3");
        d3 = 0;
        if (pZero2->s.coord.x - (p->s).coord.x > 0) {
          d3 = 1;
        }
        dir = d3;
      }
      {
        register s32 xf asm("r2");
        xf = dir;
        if (dir != 0) {
          register u8 fl asm("r1");
          register s32 f asm("r0");
          fl = (p->s).flags;
          f = 0x10;
          f |= fl;
          (p->s).flags = f;
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
          register s32 v asm("r1");
          register u8* oa asm("r3");
          s32 sh4, ov, m11;
          u8* xp;
          v = xf;
          xp = (u8*)p + 0x4c;
          z4 = 0;
          *xp = v;
          oa = (u8*)p + 0x4a;
          sh4 = v << 4;
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          m11 |= sh4;
          *oa = m11;
        }
      }
      (p->s).coord.x -= dir << 8;
      SetMotion(&p->s, MOTION(0x2A, 0x0C));
      {
        u8* a = (u8*)p + 0x8c;
        *(u32*)a = z4;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = z4;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z4;
      }
      (p->s).flags &= ~COLLIDABLE;
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y;
      ((void (*)(s32, struct Coord*, s32, s32))FUN_080b2b40)(0, &c, 0x80 * 4, dir);
      {
        register s32 k asm("r1");
        register s32 t asm("r0");
        k = 0x60;
        t = dir * 2 + dir;
        t <<= 6;
        t = k - t;
        c.x = t;
        c.y = k;
        (p->s).d.x = t >> 1;
      }
      if (*((u8*)p + 0xb9) != 0) {
        FUN_080b857c(&p->s, &(p->s).coord, &c, 0x40, (motion_t*)0x083671F2, 0x18);
      } else {
        FUN_080b84f4(&p->s, &(p->s).coord, &c, 0x40, (motion_t*)0x083671F2, 0x18);
      }
      {
        register s32 zz asm("r1");
        register s32 w asm("r0");
        zz = 0;
        w = 0x18;
        (p->s).work[2] = w;
        (p->s).d.y = zz;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t;
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0xE0 * 8) {
        (p->s).d.y = 0xE0 * 8;
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        goto hit;
      }
      if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) << 16) == 0) {
        break;
      }
    hit:
      FUN_08076b30(p);
      break;
    }
  }
}


extern const motion_t sMotions[9];
struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);

// 0x08076D30
void FUN_08076d30(struct Enemy* p) {
  struct Coord c;
  register u8* q asm("r0");
  u8 fl;
  u32 z;
  q = (u8*)p + 0x8c;
  z = 0;
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *q = z;
  fl = (p->s).flags & 0xFB;
  fl &= 0xFE;
  (p->s).flags = fl;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(2, &c);
  PlaySound(0x2A);
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[4], 3);
  SET_ENEMY_ROUTINE(p, 4);
}

// 0x08076D9C
void FUN_08076d9c(struct Enemy* p) {
  struct Coord c;
  register u8* q asm("r0");
  u8 fl;
  u32 z;
  q = (u8*)p + 0x8c;
  z = 0;
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *q = z;
  fl = (p->s).flags & 0xFB;
  fl &= 0xFE;
  (p->s).flags = fl;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x800;
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  SET_ENEMY_ROUTINE(p, 4);
}

extern const motion_t sMotions[9];
struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);

void FUN_08076df8(struct Enemy* p) {
  struct Coord c;
  {
    u8 z;
    (p->body).status = z = 0;
    (p->body).prevStatus = z;
    (p->body).invincibleTime = z;
    z = ~COLLIDABLE & (p->s).flags;
    z = z & ~DISPLAY;
    (p->s).flags = z;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  CreateSmoke(2, &c);
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[7], 2);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void PurpleNerple_Init(struct Enemy* p);
void PurpleNerple_Update(struct Enemy* p);
void PurpleNerple_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPurpleNerpleRoutine = {
    [ENTITY_INIT] =      PurpleNerple_Init,
    [ENTITY_UPDATE] =    PurpleNerple_Update,
    [ENTITY_DIE] =       PurpleNerple_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_08076140(struct Enemy* p);
void FUN_08076144(struct Enemy* p);
void FUN_08076178(struct Enemy* p);
void FUN_08076198(struct Enemy* p);
void FUN_080761b8(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_083670d0[10] = {
    FUN_080761b8,
    FUN_08076144,
    FUN_08076144,
    FUN_08076140,
    FUN_08076178,
    FUN_08076140,
    FUN_08076198,
    FUN_08076140,
    FUN_08076140,
    FUN_08076178,
};
// clang-format on

// --------------------------------------------

void FUN_08076220(struct Enemy* p);
void FUN_080762ec(struct Enemy* p);
void FUN_080763f8(struct Enemy* p);
void FUN_08076508(struct Enemy* p);
void FUN_08076594(struct Enemy* p);
void FUN_08076780(struct Enemy* p);
void FUN_08076638(struct Enemy* p);
void FUN_08076830(struct Enemy* p);
void FUN_080768e0(struct Enemy* p);
void FUN_08076a50(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_083670f8[10] = {
    FUN_08076220,
    FUN_080762ec,
    FUN_080763f8,
    FUN_08076508,
    FUN_08076594,
    FUN_08076780,
    FUN_08076638,
    FUN_08076830,
    FUN_080768e0,
    FUN_08076a50,
};
// clang-format on

// --------------------------------------------

void FUN_08076b30(struct Enemy* p);
void FUN_08076be4(struct Enemy* p);
void FUN_08076d30(struct Enemy* p);
void FUN_08076d9c(struct Enemy* p);
void FUN_08076df8(struct Enemy* p);
void FUN_080768e0(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08367120[6] = {
    FUN_08076b30,
    FUN_08076be4,
    FUN_08076d30,
    FUN_08076d9c,
    FUN_08076df8,
    FUN_080768e0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[] = {
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
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(5), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(18), PIXEL(22), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(14), PIXEL(14)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};

static const u8 sInitModes[4] = {1, 3, 7, 0};

// clang-format off
static const motion_t sMotions[9] = {
    MOTION(SM042_PURPLE_NERPLE, 0x11),
    MOTION(SM042_PURPLE_NERPLE, 0x12),
    MOTION(SM042_PURPLE_NERPLE, 0x11),
    MOTION(SM042_PURPLE_NERPLE, 0x0D),
    MOTION(SM042_PURPLE_NERPLE, 0x0E),
    MOTION(SM042_PURPLE_NERPLE, 0x0F),
    MOTION(SM042_PURPLE_NERPLE, 0x10),
    MOTION(SM042_PURPLE_NERPLE, 0x11),
    MOTION(SM042_PURPLE_NERPLE, 0x12),
};
// clang-format on
