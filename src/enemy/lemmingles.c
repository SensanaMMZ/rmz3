#include "camera.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "mission.h"
#include "physics.h"
#include "stagerun.h"
#include "story.h"
#include "zero.h"

static const struct Collision sCollisions[];
static const motion_t sMotions[13];

struct EnemyLemmingles {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 unk_b4[4];
  s32 unk_b8_x;
  u8 unk_bc[8];
};
static_assert(sizeof(struct EnemyLemmingles) == sizeof(struct Enemy));

void Lemmingles_Init(struct Enemy* p);
void Lemmingles_Update(struct Enemy* p);
void Lemmingles_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gLemminglesRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Lemmingles_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Lemmingles_Update,
    [ENTITY_DIE] =       (EnemyFunc)Lemmingles_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_0806e590(struct Entity* e, u8 kind1, u8 kind2, u8 kind3) {
  struct EnemyLemmingles* p = (struct EnemyLemmingles*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_LEMMINGLES);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y;
    (p->s).unk_28 = (void*)e;
    (p->s).work[0] = kind1;
    (p->s).work[1] = kind3;
    (p->s).work[2] = kind2;
    p->unk_b8_x = e->coord.x;
  }
}

// 0x0806e600
static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) { return; }

bool8 FUN_0806e604(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    struct Entity* nest = (p->s).unk_28;
    if (nest != NULL) {
      *(u32*)((u8*)nest + 0xb4) &= ~(1 << (p->s).work[1]);
    }
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & 0x10000) {
      (p->s).mode[1] = 1;
    } else if ((p->body).status & 0x20000) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    Lemmingles_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const EnemyFunc sUpdates1[7];
static const EnemyFunc sUpdates2[7];

bool8 FUN_0806e674(struct Enemy* p) {
  if ((p->s).mode[1] != 6 && *(struct VFX**)&p->props[0] == NULL) {
    switch ((p->s).mode[3]) {
      case 0:
        if (IsFrozen(&p->s)) {
          (sUpdates1[(p->s).mode[1]])(p);
          (sUpdates2[(p->s).mode[1]])(p);
          (p->s).mode[3]++;
          UpdateMotionGraphic(&p->s);
          return TRUE;
        }
        break;
      case 1:
        if (IsFrozen(&p->s)) {
          if (((p->body).status & 0x20001) == 0x20001) {
            (p->s).mode[3] = 0;
          } else {
            return TRUE;
          }
        } else {
          (p->s).mode[3] = 0;
        }
        break;
    }
  }
  return FALSE;
}

static const struct Coord sElementCoord;

void FUN_0806e704(struct Enemy* p) {
  if (*(struct VFX**)&p->props[0] == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    if (((p->body).status & BODY_STATUS_RECOILED)) {
      (p->s).mode[1] = 6;
      (p->s).mode[2] = 0;
    } else {
      struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
      *(struct VFX**)&p->props[0] = e;
      if (e != NULL) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
    }
  }
}

void Lemmingles_Update(struct Enemy* p);

// 0x0806E750
void Lemmingles_Init(struct Enemy* p) {
  register s32 z asm("r4");
  struct Body* body;
  u8 g40;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  {
    register const u8* tbl asm("r1");
    register u32 idx asm("r0");
    register const u8* e2 asm("r0");
    tbl = (const u8*)0x0836691C;
    asm volatile("" : "+r"(tbl));
    idx = (p->s).work[0];
    asm volatile("add %0, %1, %2" : "=l"(e2) : "l"(idx), "l"(tbl));
    (p->s).mode[1] = *e2;
  }
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fv = (p->s).flags;
    fl = FLIPABLE;
    fv |= fl;
    fl = DISPLAY;
    z = 0;
    asm volatile("" : "+r"(z));
    fv |= fl;
    (p->s).flags = fv;
  }
  InitNonAffineMotion(&p->s);
  if ((gSystemSavedataManager.mods[13] & 0x80) && (g40 = gCurStory.s.gameflags[0] & 0x40) == 0) {
    register s32 hp asm("r3");
    {
      register u8 f asm("r0");
      register u8 k asm("r1");
      f = (p->s).flags;
      k = COLLIDABLE;
      f |= k;
      (p->s).flags = f;
    }
    {
      register const struct Collision* coll asm("r1");
      register struct Coord* co asm("r2");
      register u32 w0 asm("r0");
      coll = (const struct Collision*)0x0836686C;
      co = &(p->s).coord;
      w0 = (p->s).work[0];
      hp = 0xC;
      body = &p->body;
      if (w0 <= 1) {
        hp = 8;
      }
      ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(body, coll, co, hp);
    }
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)(u32)g40;
  } else {
    register s32 hp2 asm("r3");
    {
      register u8 f2 asm("r0");
      register u8 k2 asm("r1");
      f2 = (p->s).flags;
      k2 = COLLIDABLE;
      k2 |= f2;
      (p->s).flags = k2;
    }
    {
      register const struct Collision* coll2 asm("r1");
      register struct Coord* co2 asm("r2");
      register u32 w02 asm("r0");
      coll2 = (const struct Collision*)0x0836686C;
      co2 = &(p->s).coord;
      w02 = (p->s).work[0];
      hp2 = 8;
      body = &p->body;
      if (w02 <= 1) {
        hp2 = 4;
      }
      ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(body, coll2, co2, hp2);
    }
    body->parent = (struct CollidableEntity*)p;
    body->fn = NULL;
  }
  body->fn = onCollision;
  *(u32*)&p->props[0] = 0;
  p->props[8] = 1;
  Lemmingles_Update(p);
}

static const EnemyFunc sUpdates1[7];
static const EnemyFunc sUpdates2[7];
bool8 FUN_0806e604(struct Enemy* p);
void FUN_0806e704(struct Enemy* p);
bool8 FUN_0806e674(struct Enemy* p);
void Lemmingles_Die(struct Enemy* p);

void Lemmingles_Update(struct Enemy* p) {
  struct Entity* par = (p->s).unk_28;
  if (par != NULL) {
    if (par->mode[0] > 1) {
      (p->s).unk_28 = NULL;
    }
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000 ||
      (gCurStory.s.gameflags[4] & 0x42)) {
    if (par != NULL) {
      *(u32*)((u8*)par + 0xb4) &= ~(1 << (p->s).work[1]);
    }
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (FUN_0806e604(p)) {
    return;
  }
  FUN_0806e704(p);
  if (FUN_0806e674(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

static const EnemyFunc sDeads[3];

void Lemmingles_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0806e96c(struct Enemy* p) {}


void FUN_0806e970(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}


void FUN_0806e990(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, (p->s).work[0] > 1 ? &sCollisions[3] : &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 1;
      *((u8*)p + 0xbd) = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

void FUN_0806e9fc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 f = IsFrozen(&p->s);
      if (f != 0) {
        break;
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      {
        s32 r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (r < 0) {
          (p->s).d.y = f;
          (p->s).coord.y += r;
        }
      }
      break;
    }
  }
}

// 0x0806EA64
void FUN_0806ea64(struct Enemy* p) {
  register struct Entity* par asm("r6");
  register s32 gy asm("r5");
  par = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      u8 w2;
      register u32 f asm("r0");
      *((u8*)p + 0xbd) = 8;
      w2 = (p->s).work[2];
      if (w2 != 0) {
        u8 fl = *(volatile u8*)&(p->s).flags;
        f = fl;
        f |= 0x10;
      } else {
        u8 fl = (p->s).flags;
        f = 0xef;
        f &= fl;
      }
      (p->s).flags = f;
      {
        u32 v = 1;
        u8* xf;
        u8* oa;
        s32 sh;
        s32 ov;
        s32 m11;
        v &= w2;
        xf = (u8*)p + 0x4c;
        *xf = v;
        oa = (u8*)p + 0x4a;
        sh = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register struct Body* bp asm("r2");
      const struct Collision* col;
      bp = &p->body;
      {
        u8 w0 = (p->s).work[0];
        col = (const struct Collision*)0x08366884;
        if (w0 > 1) {
          col = (const struct Collision*)((u8*)col + 0x30);
        }
      }
      SetDDP(bp, col);
      {
        register s32 d asm("r2");
        register s32 k asm("r0");
        k = -0x240;
        (p->s).d.x = k;
        asm volatile("add %0, %1, #0" : "=&l"(d) : "l"(k));
        if (((p->s).flags & 0x10) != 0) {
          d = 0x90 << 2;
        }
        (p->s).d.x = d;
      }
      {
        register const u16* mt asm("r1");
        mt = (const u16*)0x08366920;
        asm("" : "+r"(mt));
        SetMotion(&p->s, mt[(p->s).work[0]]);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 2: {
      s32 hit;
      (p->s).coord.x += (p->s).d.x;
      gy = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      hit = 0;
      {
        register s32 d asm("r2");
        register s32 s asm("r1");
        register s32 bb asm("r0");
        {
          register s32 cx0 asm("r1");
          s32* bp2 = (s32*)((u8*)p + 0xb8);
          cx0 = (p->s).coord.x;
          bb = *bp2;
          d = cx0 - bb;
        }
        {
        register s32 t1 asm("r1");
        bb = 0xf0 << 8;
        t1 = d + bb;
        bb = 0xf0 << 9;
        if ((u32)t1 > (u32)bb) {
          s = 0;
          if (d > 0) {
            s = 1;
          }
          if ((p->s).d.x < 0) {
            if (s == 0) {
              goto flip;
            }
          } else {
            if (s != 0) {
              goto flip;
            }
          }
        }
        {
          register s32 cx asm("r2");
          register s32 px asm("r3");
          cx = (p->s).coord.x;
          px = cx + -0xA00;
          if (((p->s).flags & 0x10) != 0) {
            px = cx + (0xa0 << 4);
          }
          {
            register s32 cy0 asm("r1");
            cy0 = (p->s).coord.y;
            cx = -0x800;
            asm volatile("" : "+l"(cx));
            cy0 += cx;
            if ((u16)FUN_080098a4(px, cy0) != 0) {
              hit = 1;
            }
          }
          if (0) {
            hit = 1;
          }
        }
        }
        if (hit == 0) {
          goto noflip;
        }
      }
    flip: {
      register u32 v asm("r1");
      u8 fl2;
      u32 f2;
      u8* xf;
      u8* oa;
      s32 sh;
      s32 ov;
      s32 m11;
      (p->s).d.x = -(p->s).d.x;
      {
        u32 sh0;
        fl2 = (p->s).flags;
        sh0 = (u32)fl2 >> 4;
        v = 1;
        v &= ~sh0;
      }
      if (v != 0) {
        f2 = 0x10;
        f2 |= fl2;
      } else {
        f2 = 0xef;
        f2 &= fl2;
      }
      (p->s).flags = f2;
      xf = (u8*)p + 0x4c;
      *xf = v;
      oa = (u8*)p + 0x4a;
      sh = v << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh;
    }
    noflip: {
      struct Zero* z = pZero2;
      register s32 zx asm("r3");
      s32 cx;
      zx = (z->s).coord.x;
      cx = (p->s).coord.x;
      if ((u32)((zx - cx) + (0xc0 << 6)) <= 0x5FFF) {
        register s32 s asm("r1");
        s = 0;
        if (cx < zx) {
          s = 1;
        }
        if ((p->s).d.x < 0) {
          if (s == 0) {
            goto clr;
          }
          goto setf;
        } else {
          if (s == 0) {
            goto setf;
          }
        }
      clr : {
        register u8* fp asm("r2");
        fp = (u8*)p + 0xbc;
        if (*fp != 0) {
          register u32 zz asm("r1");
          register u32 three asm("r0");
          zz = 0;
          *fp = zz;
          three = 3;
          (p->s).mode[1] = three;
          (p->s).mode[2] = zz;
        }
      }
        goto ydone;
      }
    setf : {
      register u8* fp asm("r1");
      register u32 one asm("r0");
      fp = (u8*)p + 0xbc;
      one = 1;
      *fp = one;
    }
    }
    ydone : {
      register s32 v asm("r0");
      register s32 lim asm("r1");
      v = (p->s).coord.y;
      v = gy - v;
      lim = 0x9FF;
      if (v > lim) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      } else {
        register u8* t asm("r1");
        register u32 v asm("r0");
        t = (u8*)p + 0xbd;
        v = *t;
        if (v == 0) {
          (p->s).coord.y = gy;
        } else {
          v -= 1;
          *t = v;
        }
      }
    }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
  if (par != NULL) {
    u8 pf;
    s32 s;
    {
      register s32 px2 asm("r1");
      register s32 cx2 asm("r0");
      px2 = (par->coord).x;
      cx2 = (p->s).coord.x;
      gy = px2 - cx2;
    }
    s = 0;
    if (gy > 0) {
      s = 1;
    }
    {
      register u32 pfr asm("r1");
      register u32 m asm("r0");
      pfr = par->flags;
      m = 0x10;
      m &= pfr;
      if (m != 0) {
        if (s == 0) {
          goto next1;
        }
        return;
      } else {
        if (s == 0) {
          return;
        }
      }
    next1 : {
      register s32 s2 asm("r2");
      s2 = 0;
      if ((p->s).d.x > 0) {
        s2 = 1;
      }
      m = 0x10;
      m &= pfr;
      if (m != 0) {
        if (s2 == 0) {
          goto next2;
        }
        return;
      } else {
        if (s2 == 0) {
          return;
        }
      }
    }
    }
  next2 : {
    register s32 cy asm("r1");
    register s32 py asm("r0");
    register s32 k asm("r2");
    cy = (p->s).coord.y;
    py = (par->coord).y;
    if (cy > py) {
      return;
    }
    k = -0x1800;
    py += k;
    if (cy <= py) {
      return;
    }
  }
    {
      register s32 v asm("r1");
      register s32 k asm("r0");
      k = 0xb0;
      k <<= 2;
      v = gy + k;
      k = 0x57F;
      if ((u32)v > (u32)k) {
        return;
      }
    }
    {
      register u32* m asm("r3");
      register u32 one asm("r2");
      register u32 sh asm("r0");
      register u32 v asm("r1");
      m = (u32*)((u8*)par + 0xb4);
      v = (p->s).work[1] + 4;
      one = 1;
      sh = one;
      sh <<= v;
      v = *m;
      v |= sh;
      *m = v;
      sh = (p->s).work[1] + 8;
      one <<= sh;
      v |= one;
      *m = v;
    }
    {
      register s32 f asm("r0");
      register s32 z2 asm("r2");
      register u8 e1 asm("r1");
      u8* a;
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
      a = (u8*)p + 0x8c;
      asm volatile("str %0, [%1]" ::"l"(z2), "l"(a) : "memory");
      a += 4;
      asm("" : "+r"(a));
      asm volatile("str %0, [%1]" ::"l"(z2), "l"(a) : "memory");
      a += 4;
      asm("" : "+r"(a));
      asm volatile("strb %0, [%1]" ::"l"(z2), "l"(a) : "memory");
      (p->s).flags &= ~COLLIDABLE;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
}

// 0x0806ed08
void FUN_0806ed08(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      if ((p->s).work[0] == 1) {
        SetMotion(&p->s, MOTION(0x1D, 0x07));
      }
      if ((p->s).work[0] == 3) {
        SetMotion(&p->s, MOTION(0x1D, 0x0D));
      }
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 x;
      s32 r;
      if ((p->s).work[0] == 1 || (p->s).work[0] == 3) {
        UpdateMotionGraphic(&p->s);
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      x = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = x;
      if ((p->s).d.x > 0) {
        r = PushoutToLeft1(x + 0x400, (p->s).coord.y);
        if (r < 0) {
          (p->s).coord.x += r;
        }
      } else {
        r = PushoutToRight1(x - 0x400, (p->s).coord.y);
        if (r > 0) {
          (p->s).coord.x += r;
        }
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (r < 0) {
        u16 a = GetMetatileAttr((p->s).coord.x, (p->s).coord.y) & 0x10;
        if (a != 0) {
          struct Entity* q = (p->s).unk_28;
          if (q != NULL) {
            *(u32*)((u8*)q + 0xb4) &= ~(1 << (p->s).work[1]);
          }
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          (p->s).mode[1] = 0;
        } else {
          (p->s).coord.y += r;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = a;
        }
      }
      break;
    }
  }
}

// 0x0806ee0c
void FUN_0806ee0c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[0] == 1) {
        SetMotion(&p->s, MOTION(0x1D, 0x04));
      }
      if ((p->s).work[0] == 3) {
        SetMotion(&p->s, MOTION(0x1D, 0x0A));
      }
      (p->s).work[3] = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
      (p->s).work[2] = 0x12;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (u8)--(p->s).work[2];
      if (t != 0) {
        break;
      }
      if ((p->s).work[0] == 1 || (p->s).work[0] == 3) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = t;
      } else {
        u8 g;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 1;
        g = (p->s).work[3];
        if (g == 0) {
          *((u8*)p + 0xbd) = g;
        }
      }
      break;
    }
  }
}

// 0x0806EE94
void FUN_0806ee94(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[0] == 1) {
        SetMotion(&p->s, MOTION(0x1D, 0x05));
      } else {
        SetMotion(&p->s, MOTION(0x1D, 0x0B));
      }
      (p->s).work[2] = 0;
      (p->s).d.y = -0x59C;
      (p->s).d.x = (p->s).d.x * 0xD0 / 256;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 r;
      if ((u8)++(p->s).work[2] == 0x12) {
        if ((p->s).work[0] == 1) {
          SetMotion(&p->s, MOTION(0x1D, 0x06));
        } else {
          SetMotion(&p->s, MOTION(0x1D, 0x0C));
        }
      }
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if ((p->s).work[3] == 0) {
        r = PushoutToDown1((p->s).coord.x, (p->s).coord.y);
        if (r > 0) {
          (p->s).coord.y += r;
        }
      }
      {
        s32 x = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = x;
        if ((p->s).work[3] == 0) {
          if ((p->s).d.x > 0) {
            r = PushoutToLeft1(x, (p->s).coord.y);
            if (r < 0) {
              (p->s).coord.x += r;
            }
          } else {
            r = PushoutToRight1(x, (p->s).coord.y);
            if (r > 0) {
              (p->s).coord.x += r;
            }
          }
        }
      }
      if ((p->s).d.y > 0) {
        s32 z = 0;
        (p->s).mode[1] = 2;
        (p->s).mode[2] = z;
      }
      if ((p->s).work[3] != 0) {
        (p->s).work[3] = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
      }
      break;
    }
  }
}

// 0x0806EFA4
void FUN_0806efa4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 8;
      if ((p->s).work[0] == 1) {
        SetMotion(&p->s, MOTION(0x1D, 0x08));
      }
      if ((p->s).work[0] == 3) {
        SetMotion(&p->s, MOTION(0x1D, 0x0E));
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t <<= 24;
      if (t == 0) {
        (p->s).mode[2]++;
      }
      if ((p->s).work[0] == 1 || (p->s).work[0] == 3) {
        UpdateMotionGraphic(&p->s);
      }
      break;
    }
    case 2:
      (p->s).work[2] = 0x10;
      if ((p->s).work[0] == 1) {
        GotoMotion(&p->s, MOTION(0x1D, 0x09), 1, 8);
      }
      if ((p->s).work[0] == 3) {
        GotoMotion(&p->s, MOTION(0x1D, 0x0F), 1, 8);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      register s32 t asm("r0");
      register s32 u asm("r1");
      if ((p->s).work[0] == 1 || (p->s).work[0] == 3) {
        UpdateMotionGraphic(&p->s);
      }
      t = (p->s).work[2];
      t--;
      (p->s).work[2] = t;
      t <<= 24;
      u = (u32)t >> 24;
      if (u == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 1;
        *((u8*)p + 0xbd) = u;
      }
      break;
    }
  }
}

void FUN_0806f1dc(struct Enemy* p);

// 0x0806F07C
void FUN_0806f07c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dx asm("r1");
      register s32 dy asm("r0");
      register s32 len asm("r5");
      struct Zero* z;
      struct Entity* q = (p->s).unk_28;
      if (q != NULL) {
        u32* f = (u32*)((u8*)q + 0xb4);
        *f &= ~(1 << (p->s).work[1]);
      }
      {
        struct Body* b = &p->body;
        u32 w0 = (p->s).work[0];
        const struct Collision* c = &sCollisions[5];
        if (w0 > 1) {
          c = &sCollisions[6];
        }
        SetDDP(b, c);
      }
      {
        const motion_t* mb = &sMotions[4];
        asm("" : "+r"(mb));
        SetMotion(&p->s, mb[(p->s).work[0]]);
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
      UpdateMotionGraphic(&p->s);
      nx = (p->s).coord.x;
      vx = (p->s).d.x;
      nx += vx;
      (p->s).coord.x = nx;
      if (vx > 0) {
        r = PushoutToLeft1(nx, (p->s).coord.y);
        if (r < 0) {
          (p->s).coord.x += r;
          asm volatile("" ::: "cc");
          goto hit;
        }
      } else {
        r = PushoutToRight1(nx, (p->s).coord.y);
        if (r > 0) {
          (p->s).coord.x = (p->s).coord.x + r;
          asm volatile("" : "+r"(r));
          goto hit;
        }
      }
      if ((*(u32*)((u8*)p + 0x8c) & 4) != 0) {
        goto hit;
      }
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
        goto down;
      }
      r = PushoutToUp1((p->s).coord.x, ny);
      if (r >= 0) {
        break;
      }
      (p->s).coord.y += r;
    hit:
      FUN_0806f1dc(p);
      break;
    down:
      r = PushoutToDown1((p->s).coord.x, ny);
      if (r > 0) {
        (p->s).coord.y += r;
      }
      break;
    }
  }
}

struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
static const motion_t sMotions[13];

// 0x0806f1dc
void FUN_0806f1dc(struct Enemy* p) {
  struct Coord c;
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  {
    u8 f = (p->s).flags & ~COLLIDABLE;
    f &= ~DISPLAY;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(16);
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7f70(&p->s, &c, (motion_t*)&sMotions[8], 3);
  TryDropItem(3, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);
void FUN_080b834c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);
void FUN_080b84f4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);

// 0x0806F274
// Blocker: agbcc emits the two-case dispatch as `cmp #1 / bne .+2 / b case1`
// where retail has `cmp #1 / beq case1` -- a conditional-branch range
// decision, not something the source controls. Instruction counts and the
// ROM size otherwise match exactly. 8 lever rounds (switch vs if/else vs
// goto; the if/else form drags in r8).
NON_MATCH void FUN_0806f274(struct Enemy* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      s32 f;
      register s32 k asm("r6");
      register s32 z5 asm("r5");
      struct Coord c;
      {
        register s32 t3 asm("r3");
        t3 = 0;
        if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
          t3 = 1;
        }
        f = t3;
        asm("" : "+l"(f));
      }
      k = 0;
      {
        u8 w0 = (p->s).work[0];
        if (w0 == 1) {
          goto setk;
        }
        if (w0 != 3) {
          goto donek;
        }
      setk:
        k = 1;
      donek:;
      }
      {
        register s32 mv asm("r1");
        mv = MOTION(0x1D, 0x12);
        if (k != 0) {
          mv -= 2;
        }
        ((void (*)(struct Entity*, s32))SetMotion)(&p->s, mv);
      }
      {
        u8* a = (u8*)p + 0x8c;
        z5 = 0;
        *(s32*)a = z5;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = z5;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z5;
      }
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFB;
        g &= h;
        (p->s).flags = g;
      }
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y;
      ((void (*)(s32, struct Coord*, s32, s32))FUN_080b2b40)(0, &c, 0x80 << 2, f);
      c.x = (p->s).d.x / 4;
      c.y = z5;
      {
        register s32 g0 asm("r0");
        register s32 g1 asm("r1");
        g0 = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
        g1 = g0;
        asm("" : "+r"(g1));
        g0 = (p->s).coord.y;
        g0 = g1 - g0;
        if (g0 <= 0x3FF) {
          goto low;
        }
      }
      {
        (p->s).unk_coord.y = 0x20;
        asm volatile("" ::: "memory");
        {
          register s32 idx asm("r0");
          register const motion_t* base asm("r2");
          register struct Coord* cp asm("r1");
          register motion_t* mp asm("r0");
          cp = &(p->s).coord;
          asm("" : "+r"(cp));
          idx = k << 1;
          base = &sMotions[11];
          asm volatile("add %0, %1, %2" : "=l"(mp) : "l"(idx), "l"(base));
          ((void (*)(struct Entity*, struct Coord*, struct Coord*, s32, motion_t*, s32))FUN_080b84f4)(&p->s, cp, &c, 0x15, mp, 0x18);
        }
        goto done0;
      }
    low : {
        (p->s).unk_coord.y = z5;
        asm volatile("" ::: "memory");
        {
          register s32 idx2 asm("r0");
          register const motion_t* base2 asm("r2");
          register struct Coord* cp2 asm("r1");
          register motion_t* mp2 asm("r0");
          cp2 = &(p->s).coord;
          asm("" : "+r"(cp2));
          idx2 = k << 1;
          base2 = &sMotions[11];
          asm volatile("add %0, %1, %2" : "=l"(mp2) : "l"(idx2), "l"(base2));
          ((void (*)(struct Entity*, struct Coord*, struct Coord*, s32, motion_t*, s32))FUN_080b834c)(&p->s, cp2, &c, 0, mp2, 0x18);
        }
      }
    done0:
      (p->s).d.x = (p->s).d.x / 10;
      (p->s).d.y = 0;
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 uy;
      UpdateMotionGraphic(&p->s);
      uy = (p->s).unk_coord.y;
      if (uy != 0) {
        s32 v = (p->s).d.y + uy;
        s32 r;
        (p->s).d.y = v;
        if (v > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (r < 0) {
          (p->s).coord.y += r;
        }
      }
      (p->s).coord.x += (p->s).d.x;
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) == 0) {
          FUN_0806f1dc(p);
        }
      }
      break;
    }
  }
#else
  INCCODE("asm/enemy/lemmingles_p2_p2_p2c.inc");
#endif
}

// --------------------------------------------

void FUN_0806e990(struct Enemy* p);
void FUN_0806e970(struct Enemy* p);
void nop_0806e96c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    FUN_0806e990,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    nop_0806e96c,
};
// clang-format on

void FUN_0806e9fc(struct Enemy* p);
void FUN_0806ea64(struct Enemy* p);
void FUN_0806ed08(struct Enemy* p);
void FUN_0806ee0c(struct Enemy* p);
void FUN_0806ee94(struct Enemy* p);
void FUN_0806efa4(struct Enemy* p);
void FUN_0806f07c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    FUN_0806e9fc,
    FUN_0806ea64,
    FUN_0806ed08,
    FUN_0806ee0c,
    FUN_0806ee94,
    FUN_0806efa4,
    FUN_0806f07c,
};
// clang-format on

// --------------------------------------------

void FUN_0806f1dc(struct Enemy* p);
void FUN_0806f274(struct Enemy* p);
void FUN_0806f07c(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_0806f1dc,
    FUN_0806f274,
    FUN_0806f07c,
};

// --------------------------------------------

static const struct Collision sCollisions[7] = {
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
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
static const u8 sInitModes[4] = {1, 1, 1, 1};

// clang-format off
static const motion_t sMotions[13] = {
    MOTION(SM029_LEMMINGLES, 1),
    MOTION(SM029_LEMMINGLES, 0),
    MOTION(SM029_LEMMINGLES, 3),
    MOTION(SM029_LEMMINGLES, 2),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 1),
    MOTION(SM029_LEMMINGLES, 5),
    MOTION(SM029_LEMMINGLES, 3),
    MOTION(SM029_LEMMINGLES, 11),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 22),
    MOTION(SM029_LEMMINGLES, 23),
    MOTION(SM029_LEMMINGLES, 24),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 19),
    MOTION(SM029_LEMMINGLES, 17),
};


