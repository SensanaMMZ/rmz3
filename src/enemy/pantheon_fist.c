#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"
#include "physics.h"
#include "story.h"
#include "metatile.h"
#include "stagerun.h"

static const struct Collision sCollisions[];

struct Enemy* createPantheonFistInElevator(s32 x, s32 y, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_FIST);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    p->props[5] = a2;
  }
  return p;
}

bool8 FUN_08094fa8(struct Enemy* p, s32 d) {
  s32 x = (p->s).coord.x;
  x -= PIXEL(14);
  if (d > 0) {
    x += PIXEL(28);
  }
  if (FUN_080098a4(x, (p->s).coord.y + PIXEL(10)) != 0) {
    return TRUE;
  }
  return FALSE;
}

bool8 FUN_08094fe0(struct Enemy* p, s32 dy) {
  if (dy > 0) {
    s32 diff;
    (p->s).coord.y += dy;
    diff = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - (p->s).coord.y;
    if (diff <= 0x7ff) {
      (p->s).coord.y = (p->s).coord.y + diff;
      return TRUE;
    }
  }
  return FALSE;
}

u32 FUN_08095014(struct Enemy* p, s32 d) {
  if (d != 0) {
    if (d < 0) {
      if (FUN_080098a4((p->s).coord.x - PIXEL(14), (p->s).coord.y - PIXEL(10)) != 0) {
        return 1;
      }
    } else {
      if (FUN_080098a4((p->s).coord.x + PIXEL(14), (p->s).coord.y - PIXEL(10)) != 0) {
        return 2;
      }
    }
    (p->s).coord.x += d;
  }
  return 0;
}

u32 FUN_08095074(struct Enemy* p, s32 dx) {
  if (dx == 0) {
    return 0;
  }
  if (dx < 0) {
    if (FUN_080098a4((p->s).coord.x - 0xE00, (p->s).coord.y - 0xA00) != 0) {
      return 1;
    }
  } else {
    if (FUN_080098a4((p->s).coord.x + 0xE00, (p->s).coord.y - 0xA00) != 0) {
      return 2;
    }
  }
  return 0;
}

void nop_080950cc(struct Enemy* p) {}

bool8 FUN_080950d0(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else if ((p->body).status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    return TRUE;
  }
  return FALSE;
}


extern const EnemyFunc sUpdates1[];
extern const EnemyFunc sUpdates2[];

// 0x08095124
bool8 FUN_08095124(struct Enemy* p) {
  if ((p->s).mode[1] != 7) {
    s32 v = *(s32*)&p->props[0];
    if (v == 0) {
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
            if (((p->body).status & 0x00020001) == 0x00020001) {
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
  }
  return FALSE;
}

struct PantheonFistObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct VFX* elementEffect;
  u8 unk_004[12];
};
static_assert(sizeof(struct PantheonFistObject) == sizeof(struct Enemy));

static const struct Coord sElementCoord;

void FUN_080951b4(struct PantheonFistObject* p) {
  if (p->elementEffect == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    if (((p->body).status & BODY_STATUS_RECOILED)) {
      (p->s).mode[1] = 7;
      (p->s).mode[2] = 0;
    } else {
      p->elementEffect = ApplyElementEffect(0, &p->s, &sElementCoord);
      if (p->elementEffect != NULL) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
    }
  }
}

static const u8 sInitModes[2];
void PantheonFist_Update(struct Enemy* p);

// 0x08095200
void PantheonFist_Init(struct Enemy* p) {
  register s32 z6 asm("r6");
  u8 w0 = (p->s).work[0];
  if (w0 == 1) {
    (p->s).work[0] = 0;
    (p->s).work[1] = w0;
  } else {
    (p->s).work[1] = 0;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  {
    u8 v = sInitModes[(p->s).work[0]];
    z6 = 0;
    (p->s).mode[1] = v;
  }
  {
    register u8 fv asm("r0");
    register u8 k asm("r1");
    fv = (p->s).flags;
    k = 2;
    fv |= k;
    k = 1;
    fv |= k;
    (p->s).flags = fv;
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fl asm("r1");
    register u8 g asm("r0");
    fl = (p->s).flags;
    g = 4;
    g |= fl;
    (p->s).flags = g;
  }
  {
    struct Body* body = &p->body;
    InitBody(body, &sCollisions[0], &(p->s).coord, 8);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)nop_080950cc;
  }
  *(s32*)((u8*)p + 0xb4) = z6;
  if ((p->s).work[1] != 0) {
    *((u8*)p + 0xb8) = z6;
  } else {
    *((u8*)p + 0xb8) = 3;
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  }
  {
    register s32 f asm("r2");
    f = 0;
    if ((p->s).coord.x < (pZero2->s).coord.x) {
      f = 1;
    }
    {
      register u8 nf asm("r0");
      if (f != 0) {
        register u8 kk asm("r1");
        kk = (p->s).flags;
        nf = 0x10;
        nf |= kk;
      } else {
        register u8 fl2 asm("r1");
        fl2 = (p->s).flags;
        asm("" : "+r"(fl2));
        nf = 0xEF;
        nf &= fl2;
      }
      (p->s).flags = nf;
    }
    {
      register s32 x asm("r1");
      u8* a;
      s32 sh;
      u8 ov;
      s32 m;
      x = f;
      ((p->s).spr).xflip = x;
      a = (u8*)p + 0x4a;
      asm("" : "+r"(a));
      sh = x << 4;
      ov = *a;
      m = -0x11;
      m &= ov;
      m |= sh;
      *a = m;
    }
  }
  PantheonFist_Update(p);
}


void PantheonFist_Update(struct Enemy* p) {
  if (!FUN_080950d0(p)) {
    FUN_080951b4((struct PantheonFistObject*)p);
    if (!FUN_08095124(p)) {
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
}


static const EnemyFunc sDeads[3];

// 0x08095340
void PantheonFist_Die(struct Enemy* p) {
  if ((p->s).work[1] == 0 && IS_METTAUR) {
    u8 fl = (p->s).flags & ~DISPLAY;
    (p->s).flags = fl & ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (sDeads[(p->s).mode[1]])(p);
  }
}

void FUN_080953ac(struct Enemy* p) {}


void FUN_080953b0(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}


void FUN_080953d0(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

void FUN_0809542c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0xd4, 0x06));
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 f = IsFrozen(&p->s);
      if (f == 0) {
        (p->s).d.y += 0x40;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        {
          s32 r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
          if (r < 0) {
            (p->s).coord.y += r;
            (p->s).d.y = f;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080954A4
void FUN_080954a4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, (const struct Collision*)0x08369FEC);
      (p->s).work[2] = 0x1E;
      SetMotion(&p->s, MOTION(0xD4, 0x00));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register s32 v asm("r2");
      register s32 v5 asm("r5");
      s32 t;
      UpdateMotionGraphic(&p->s);
      v = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        v = 1;
      }
      asm volatile("add %0, %1, #0" : "=&l"(v5) : "l"(v));
      if (v5 != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
      {
        register s32 xf asm("r1");
        u8* oa;
        s32 sh4, ov, m11;
        asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(v));
        (p->s).spr.xflip = xf;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      t = (p->s).work[2];
      t--;
      (p->s).work[2] = t;
      t <<= 24;
      if (t == 0) {
        register s32 d asm("r5");
        register s32 r6 asm("r6");
        register s32 sh asm("r0");
        s32 rv;
        sh = v5 << 1;
        asm("" : "+r"(sh));
        d = sh - 1;
        rv = FUN_08095074(p, d);
        rv <<= 24;
        r6 = (u32)rv >> 24;
        if (r6 != 0 || (u8)FUN_08094fa8(p, d) == 0) {
          (p->s).work[2] = 0x10;
        } else {
          (p->s).mode[1] = 3;
          (p->s).mode[2] = r6;
        }
      }
      {
        register s32 rr asm("r1");
        s32 rw = FUN_08094fe0(p, 1);
        rw <<= 24;
        rr = (u32)rw >> 24;
        if (rr == 0) {
          (p->s).mode[1] = 2;
          (p->s).mode[2] = rr;
        }
      }
      break;
    }
  }
}

// 0x08095578
void FUN_08095578(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 r;
      s32 v;
      SetMotion(&p->s, MOTION(0xD4, 0));
      if (*((u8*)p + 0xb8) == 2) {
        s32 x0 = (p->s).coord.x;
        s32 nx = x0 - 0x80;
        s32 res;
        (p->s).coord.x = nx;
        res = nx;
        if (((p->s).flags & 0x10) != 0) {
          res = x0 + 0x80;
        }
        (p->s).coord.x = res;
      }
      v = (p->s).d.y + 0x40;
      (p->s).d.y = v;
      if (v > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (r < 0) {
        (p->s).coord.y += r;
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetMotion(&p->s, MOTION(0xD4, 1));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      register u8 st asm("r2");
      UpdateMotionGraphic(&p->s);
      st = *((u8*)p + 0x73);
      if (st == 3) {
        u8* q = (u8*)p + 0xb8;
        register u8 nm asm("r0");
        if (*q == 0) {
          *q = 1;
          nm = 8;
        } else {
          if (*q == 2) {
            *q = st;
          }
          nm = 1;
        }
        (p->s).mode[1] = nm;
        {
          register u8 z0 asm("r0");
          z0 = 0;
          (p->s).mode[2] = z0;
        }
      }
      FUN_08094fe0(p, 1);
      break;
    }
  }
}

void FUN_08095664(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 on = 0;
      u8 rv;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        on = 1;
      }
      rv = FUN_08094fa8(p, (on << 8) - 0x80);
      if (rv == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = rv;
        return;
      }
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xD4, 0x02));
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      s32 on3 = 0;
      s32 on;
      s32 d;
      u8 rv2;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        on3 = 1;
      }
      on = on3;
      {
        bool8 xf2 = on;
        if (on) {
          (p->s).flags |= X_FLIP;
        } else {
          (p->s).flags &= ~X_FLIP;
        }
        ((p->s).spr).xflip = xf2 & 1;
        ((p->s).spr).oam.xflip = xf2;
      }
      if ((u32)((pZero2->s).coord.x - (p->s).coord.x + 0x3200) <= 0x63FF) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
      d = (on << 8) - 0x80;
      if (FUN_08094fa8(p, d) == 0 || (u8)FUN_08095014(p, d) != 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      rv2 = FUN_08094fe0(p, 1);
      if (rv2 == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = rv2;
      }
      break;
    }
  }
}

// 0x08095778
void FUN_08095778(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xD4, 0x03));
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
    case 1: {
      s32 d;
      u8 t;
      UpdateMotionGraphic(&p->s);
      d = (p->s).work[2] - 1;
      (p->s).work[2] = d;
      t = d;
      if (t == 0) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = t;
      }
      FUN_08094fe0(p, 1);
      break;
    }
  }
}

void CreateSmoke(u8 n, struct Coord* c);

// 0x080957D4
void FUN_080957d4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 k;
      s32 v;
      PlaySound(0x109);
      SetDDP(&p->body, &sCollisions[3]);
      k = 0x10;
      (p->s).unk_coord.x = k;
      (p->s).work[2] = Sqrt(0x500);
      v = (p->s).work[2] * (p->s).unk_coord.x;
      (p->s).d.x = v;
      k &= (p->s).flags;
      if (k == 0) {
        (p->s).d.x = -v;
      } else {
        (p->s).unk_coord.x = -(p->s).unk_coord.x;
      }
      (p->s).work[3] = 0;
      SetMotion(&p->s, MOTION(0xD4, 0x04));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      u32 one;
      u32 four;
      u32 st;
      UpdateMotionGraphic(&p->s);
      st = (pZero2->body).status;
      one = 1;
      if ((st & one) == 0) {
        goto move;
      }
      {
        u32 st2 = (p->body).status;
        four = 4;
        if ((st2 & four) != 0 && (p->s).work[2] > 0x10) {
          u8 w3 = (p->s).work[3];
          if (w3 == 0) {
            PlaySound(0x52);
            (p->s).work[3] = one;
            *((u8*)pZero2 + 0x122) = one;
            (pZero2->s).mode[1] = four;
            (pZero2->s).mode[2] = w3;
          }
        }
      }
    move:
      (p->s).d.x += (p->s).unk_coord.x;
      (p->s).work[2]--;
      {
        u8 w = (p->s).work[2];
        if ((3 & w) == 0 && w > 8) {
          CreateSmoke(3, &(p->s).coord);
        }
      }
      if ((u8)FUN_08094fa8(p, (p->s).d.x) == 0) {
        goto reset;
      }
      if ((p->s).work[2] == 0) {
        goto reset;
      }
      if ((u8)FUN_08095014(p, (p->s).d.x) == 0) {
        goto tick;
      }
    reset : {
      u8 z2 = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z2;
    }
    tick:
      UpdateMotionGraphic(&p->s);
      if ((u8)FUN_08094fe0(p, 1) == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      FUN_08094fe0(p, 1);
      break;
    }
  }
}

void FUN_08095914(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xD4, 0x05));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      FUN_08094fe0(p, 1);
      break;
  }
}

void FUN_08095b70(struct Enemy* p);

// 0x0809596C
void FUN_0809596c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dx asm("r1");
      register s32 dy asm("r0");
      register s32 q asm("r6");
      struct Zero* z;
      SetDDP(&p->body, &sCollisions[5]);
      SetMotion(&p->s, MOTION(0xD4, 6));
      UpdateMotionGraphic(&p->s);
      z = pZero2;
      dx = (p->s).coord.x;
      dx -= (z->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).coord.y + -0x1800;
      dy -= (z->s).coord.y;
      (p->s).d.y = dy;
      dx >>= 8;
      q = dx * dx;
      dy >>= 8;
      {
        s32 u = dy * dy;
        q += u;
      }
      q = (u32)Sqrt(q) << 8;
      if (q != 0) {
        s32 a = ((p->s).d.x << 8) / q;
        s32 b;
        (p->s).d.x = a;
        b = ((p->s).d.y << 8) / q;
        (p->s).d.x = a * 6;
        (p->s).d.y = b * 6;
      } else {
        (p->s).d.x = 0xC0 << 3;
        (p->s).d.y = q;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32* st asm("r6");
      register s32 zz asm("r4");
      s32 v;
      s32 pu;
      UpdateMotionGraphic(&p->s);
      if (((u8)FUN_08095014(p, (p->s).d.x) << 24) != 0) {
        FUN_08095b70(p);
        break;
      }
      st = (s32*)((u8*)p + 0x8c);
      zz = *st;
      zz &= 4;
      if (zz != 0) {
        FUN_08095b70(p);
        break;
      }
      v = (p->s).d.y + 0x40;
      (p->s).d.y = v;
      if (v > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      pu = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (pu < 0) {
        (p->s).coord.y += pu;
        FUN_08095b70(p);
      }
      if ((p->s).work[1] != 0) {
        if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000) {
          {
            register u8 fl asm("r1");
            register s32 g asm("r0");
            fl = (p->s).flags;
            g = 0xFE;
            g &= fl;
            fl = 0xFD;
            g &= fl;
            (p->s).flags = g;
          }
          *st = zz;
          *(s32*)((u8*)p + 0x90) = zz;
          *((u8*)p + 0x94) = zz;
          {
            register u8 fl2 asm("r1");
            register s32 g2 asm("r0");
            fl2 = (p->s).flags;
            g2 = 0xFB;
            g2 &= fl2;
            (p->s).flags = g2;
          }
          SET_ENEMY_ROUTINE(p, 3);
        }
      }
      break;
    }
  }
}

// 0x08095ac4
void FUN_08095ac4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register u8* pb asm("r2");
      register u8 w asm("r1");
      register s32 one asm("r0");
      register s32 v asm("r3");
      register u8* pb9 asm("r5");
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xD4, 0x02));
      pb = (u8*)p + 0xb9;
      w = *pb;
      one = 1;
      asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(one));
      v ^= w;
      pb9 = pb;
      if (v != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
      {
        register s32 xf asm("r1");
        u8* oa;
        s32 sh4, ov, m11;
        xf = 1;
        xf &= v;
        (p->s).spr.xflip = xf;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      {
        s32 d = 0x80;
        (p->s).d.x = d;
        (p->s).d.x = d - (*pb9 << 8);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      u8 r;
      FUN_08095014(p, (p->s).d.x);
      UpdateMotionGraphic(&p->s);
      r = FUN_08094fe0(p, 1);
      if (r == 0) {
        register u8* pb8 asm("r1");
        register s32 two asm("r0");
        pb8 = (u8*)p + 0xb8;
        asm("" : "+r"(pb8));
        two = 2;
        *pb8 = two;
        (p->s).mode[1] = two;
        (p->s).mode[2] = r;
      }
      break;
    }
  }
}

#include "mission.h"

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
void FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void FUN_080b7ffc(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
static const motion_t sMotions[4];

// 0x08095b70
void FUN_08095b70(struct Enemy* p) {
  struct Coord c;
  struct Coord* co;
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    u8* q = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(q));
    z = 0;
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *q = z;
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
  if ((p->s).work[1] == 0) {
    FUN_080b7f70(&p->s, &c, (motion_t*)sMotions, 3);
  } else {
    FUN_080b7ffc(&p->s, &c, (motion_t*)sMotions, 3);
  }
  co = &(p->s).coord;
  TryDropItem(4, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);
void FUN_080b834c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);
void FUN_080b83d4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);
void FUN_080b84f4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);
void FUN_080b857c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);
static const motion_t sMotions[];

// 0x08095C20
void FUN_08095c20(struct Enemy* p) {
  register s32 m2 asm("r5");
  m2 = (p->s).mode[2];
  switch (m2) {
    case 0: {
      register s32 f asm("r6");
      struct Coord c;
      f = 0;
      if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
        f = 1;
      }
      SetMotion(&p->s, MOTION(0xD4, 8));
      {
        u8* a = (u8*)p + 0x8c;
        *(s32*)a = m2;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = m2;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = m2;
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
      {
        register s32 k60 asm("r1");
        k60 = 0x60;
        c.x = k60 - (((f << 1) + f) << 6);
        c.y = k60;
      }
      if (((u8)FUN_08094fe0(p, 1) << 24) == 0) {
        (p->s).unk_coord.y = 0x20;
        if ((p->s).work[1] == 0) {
          ((void (*)(struct Entity*, struct Coord*, struct Coord*, s32, motion_t*, s32))FUN_080b84f4)(&p->s, &(p->s).coord, &c, 0x15, (motion_t*)&sMotions[3], 0x18);
        } else {
          ((void (*)(struct Entity*, struct Coord*, struct Coord*, s32, motion_t*, s32))FUN_080b857c)(&p->s, &(p->s).coord, &c, 0x15, (motion_t*)&sMotions[3], 0x18);
        }
      } else {
        (p->s).unk_coord.y = m2;
        if ((p->s).work[1] == 0) {
          ((void (*)(struct Entity*, struct Coord*, struct Coord*, s32, motion_t*, s32))FUN_080b834c)(&p->s, &(p->s).coord, &c, 0, (motion_t*)&sMotions[3], 0x18);
        } else {
          ((void (*)(struct Entity*, struct Coord*, struct Coord*, s32, motion_t*, s32))FUN_080b83d4)(&p->s, &(p->s).coord, &c, 0, (motion_t*)&sMotions[3], 0x18);
        }
      }
      (p->s).d.x = c.x / 4;
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
        (p->s).d.y = v;
        if (v > 0x700) {
          (p->s).d.y = 0x700;
        }
        FUN_08094fe0(p, (p->s).d.y);
      }
      (p->s).coord.x += (p->s).d.x;
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) == 0) {
          FUN_08095b70(p);
        }
      }
      break;
    }
  }
}

void PantheonFist_Init(struct Enemy* p);
void PantheonFist_Update(struct Enemy* p);
void PantheonFist_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonFistRoutine = {
    [ENTITY_INIT] =      PantheonFist_Init,
    [ENTITY_UPDATE] =    PantheonFist_Update,
    [ENTITY_DIE] =       PantheonFist_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080953ac(struct Enemy* p);
void FUN_080953b0(struct Enemy* p);
void FUN_080953d0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[9] = {
    FUN_080953d0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953ac,
    FUN_080953b0,
};
// clang-format on

void FUN_0809542c(struct Enemy* p);
void FUN_080954a4(struct Enemy* p);
void FUN_08095578(struct Enemy* p);
void FUN_08095664(struct Enemy* p);
void FUN_08095778(struct Enemy* p);
void FUN_080957d4(struct Enemy* p);
void FUN_08095914(struct Enemy* p);
void FUN_0809596c(struct Enemy* p);
void FUN_08095ac4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[9] = {
    FUN_0809542c,
    FUN_080954a4,
    FUN_08095578,
    FUN_08095664,
    FUN_08095778,
    FUN_080957d4,
    FUN_08095914,
    FUN_0809596c,
    FUN_08095ac4,
};
// clang-format on

// --------------------------------------------

void FUN_08095b70(struct Enemy* p);
void FUN_08095c20(struct Enemy* p);
void FUN_0809596c(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_08095b70,
    FUN_08095c20,
    FUN_0809596c,
};

// --------------------------------------------

static const struct Collision sCollisions[6] = {
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
      damage : 3,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : BODY_NATURE_B2,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(22), -PIXEL(19), PIXEL(26), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(10), -PIXEL(13), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
static const u8 sInitModes[2] = {2, 0};

static const motion_t sMotions[4] = {
    MOTION(SM212_PANTHEON_FIST, 9),
    MOTION(SM212_PANTHEON_FIST, 10),
    MOTION(SM212_PANTHEON_FIST, 11),
    MOTION(SM212_PANTHEON_FIST, 7),
};
