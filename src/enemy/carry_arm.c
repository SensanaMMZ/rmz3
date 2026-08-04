#include "collision.h"
#include "enemy.h"
#include "physics.h"
#include "global.h"
#include "trig.h"
#include "vfx.h"

const EnemyFunc PTR_ARRAY_08366b78[2];

struct Enemy* FUN_08071470(struct Entity* a, struct Entity* e, s32 x, s32 y, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).work[1] = n;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    if (e->unk_2c != NULL) {
      (p->s).unk_2c = NULL;
      p->props[4] = 1;
    } else {
      (p->s).unk_2c = e;
      p->props[4] = 0;
      e->unk_2c = (struct Entity*)p;
    }
    *(struct Entity**)&p->props[0] = a;
  }
  return p;
}

#include "entity/macros.h"

struct Enemy* FUN_08071508(struct Entity* e, s32 x, s32 y) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    *(struct Entity**)&p->props[0] = e;
  }
  return p;
}

void nop_08071568(struct Enemy* p) {}

void CarryArm_Die(struct Enemy* p);

static bool8 FUN_0807156c(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = (p->s).work[0];
    CarryArm_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const struct Collision sCollisions[2];
extern const u8 u8_ARRAY_08366bb0[2];
void CarryArm_Update(struct Enemy* p);

void CarryArm_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_08366bb0[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] == 1) {
    INIT_BODY(p, &sCollisions[1], 2, NULL);
    (p->s).unk_28 = NULL;
    (p->s).unk_2c = NULL;
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  } else {
    INIT_BODY(p, &sCollisions[0], 2, (void*)nop_08071568);
  }
  CarryArm_Update(p);
}

extern const EnemyFunc PTR_ARRAY_08366b48[6];
extern const EnemyFunc PTR_ARRAY_08366b60[6];

void CarryArm_Update(struct Enemy* p) {
  if (!FUN_0807156c(p)) {
    (PTR_ARRAY_08366b48[(p->s).mode[1]])(p);
    (PTR_ARRAY_08366b60[(p->s).mode[1]])(p);
  }
}

void CarryArm_Die(struct Enemy* p) {
  (PTR_ARRAY_08366b78[(p->s).mode[1]])(p);
}

void FUN_080716a8(struct Enemy* p) {}

// 0x080716AC
void FUN_080716ac(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dx asm("r2");
      (p->s).taskCol = 0x17;
      {
        register s32 wv asm("r1");
        register s32 t3 asm("r0");
        dx = 0x3000;
        asm("" : "+r"(dx));
        wv = (p->s).work[1];
        t3 = wv << 1;
        t3 += wv;
        t3 <<= 13;
        dx -= t3;
        (p->s).d.x = dx;
        dx /= 16;
        (p->s).d.x = dx;
      }
      {
        register s32 g asm("r1");
        register s32 h asm("r0");
        g = -0x20;
        (p->s).unk_coord.y = g;
        h = 0x100;
        asm("" : "+r"(h));
        g <<= 3;
        h -= g;
        (p->s).d.y = h;
      }
      {
        register s32 v asm("r1");
        register s32 v2 asm("r2");
        v = 0;
        if (dx > 0) {
          v = 1;
        }
        asm volatile("add %0, %1, #0" : "=&l"(v2) : "l"(v));
        if (v2 != 0) {
          (p->s).flags |= X_FLIP;
        } else {
          (p->s).flags &= ~X_FLIP;
        }
        {
          register s32 xf asm("r1");
          u8* oa;
          s32 sh4, ov, m11;
          asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(v2));
          (p->s).spr.xflip = xf;
          oa = (u8*)p + 0x4a;
          sh4 = xf << 4;
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          *oa = m11 | sh4;
        }
      }
      (p->s).work[2] = 0x10;
      GotoMotion(&p->s, MOTION(0x22, 0x01), 6, 3);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 t asm("r0");
      (p->s).coord.x += (p->s).d.x;
      {
        s32 ny = (p->s).d.y + (p->s).unk_coord.y;
        (p->s).d.y = ny;
        (p->s).coord.y += ny;
      }
      t = (p->s).work[2];
      t--;
      (p->s).work[2] = t;
      t <<= 24;
      {
        register s32 u asm("r1");
        u = (u32)t >> 24;
        if (u == 0) {
          (p->s).mode[1] = 1;
          (p->s).mode[2] = u;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_08071778(struct Enemy* p) {
  struct Entity* q = (p->s).unk_2c;
  u8 m;
  if (q != NULL && q->mode[0] > 1) {
    q = NULL;
    (p->s).unk_2c = q;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).work[2] = m;
      (p->s).work[3] = ((RANDOM(RNG_0202f388) & 3) << 6) + 0x20;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      register s32 w asm("r2");
      const s16* tbl;
      s32 v;
      tbl = gSineTable;
      w = (p->s).work[2];
      v = tbl[(u8)(w * 2 + 64)] * 4;
      (p->s).d.x = v;
      if ((p->s).work[1] == 1) {
        (p->s).d.x = -v;
      }
      (p->s).d.y = tbl[(u8)(w * 2)] >> 1;
      asm volatile("" :: "r"(w));
      {
        bool8 on = 0;
        if ((p->s).d.x > 0) {
          on = 1;
        }
        SET_XFLIP(p, on);
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      {
        s32 t = (p->s).work[2] + 1;
        (p->s).work[2] = t;
        if ((u8)t >= (p->s).work[3]) {
          u8 bv = *((u8*)p + 0xb8);
          if (bv != 0 || q == NULL) {
            (p->s).mode[1] = 5;
            (p->s).mode[2] = 0;
          } else {
            (p->s).mode[1] = 2;
            (p->s).mode[2] = bv;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

extern void __divsi3();
void FUN_08071b88(struct Enemy* p);

// 0x08071888
void FUN_08071888(struct Enemy* p) {
  register struct Entity* q asm("r6");
  q = (p->s).unk_2c;
  if (q != NULL && q->mode[0] > 1) {
    q = NULL;
    (p->s).unk_2c = q;
    (p->s).mode[1] = 5;
    asm volatile("strb %0, [%1, #0xe]" ::"l"(q), "l"(p) : "memory");
    FUN_08071b88(p);
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dx asm("r4");
      {
        s32 t = (q->coord).x - (p->s).coord.x;
        (p->s).d.x = t;
        dx = ((s32 (*)(s32, s32))__divsi3)(t, 0x28);
        (p->s).d.x = dx;
      }
      (p->s).unk_coord.y = -0x20;
      {
        register s32 cy asm("r0");
        register s32 kc asm("r1");
        s32 u;
        cy = (q->coord).y;
        kc = -0x2200;
        asm volatile("" : "+r"(kc));
        cy += kc;
        kc = (p->s).coord.y;
        u = cy - kc;
        (p->s).d.y = u;
        (p->s).d.y = ((s32 (*)(s32, s32))__divsi3)(u, 0x28) + 0x280;
      }
      {
        register s32 v asm("r1");
        register s32 v2 asm("r2");
        v = 0;
        if (dx > 0) {
          v = 1;
        }
        asm volatile("add %0, %1, #0" : "=&l"(v2) : "l"(v));
        if (v2 != 0) {
          (p->s).flags |= X_FLIP;
        } else {
          (p->s).flags &= ~X_FLIP;
        }
        {
          register s32 xf asm("r1");
          u8* oa;
          s32 sh4, ov, m11;
          asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(v2));
          ((p->s).spr).xflip = xf;
          oa = (u8*)p + 0x4a;
          sh4 = xf << 4;
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          *oa = m11 | sh4;
        }
      }
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 t asm("r1");
      (p->s).coord.x += (p->s).d.x;
      {
        s32 ny = (p->s).d.y + (p->s).unk_coord.y;
        (p->s).d.y = ny;
        (p->s).coord.y += ny;
      }
      {
        register s32 u asm("r0");
        u = (p->s).work[2];
        u--;
        (p->s).work[2] = u;
        u <<= 24;
        t = (u32)u >> 24;
      }
      if (t == 0) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = t;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x08071964
void FUN_08071964(struct Enemy* p) {
  struct Entity* q;
  struct Entity* r;
  s32 v;
  if (((p->s).unk_2c)->mode[0] > 1) {
    (p->s).unk_2c = NULL;
  }
  q = (p->s).unk_28;
  if (q->mode[0] > 1) {
    (p->s).unk_28 = NULL;
    q = NULL;
  }
  r = *(struct Entity**)((u8*)p + 0xb4);
  switch ((p->s).mode[2]) {
    case 0: {
      u8 z = (p->s).mode[2];
      (p->s).work[2] = z;
      (p->s).work[3] = z;
      (p->s).d.y = z;
      SetMotion(&p->s, 0x2300);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      if (q == NULL) {
        s32 dy = (p->s).d.y + 0x40;
        (p->s).d.y = dy;
        if (dy > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        v = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (v < 0) {
          if ((p->s).work[2] == 0) {
            PlaySound(0x91);
            (p->s).work[2] = 1;
          }
          (p->s).d.y = (s32)q;
          (p->s).coord.y += v;
        } else {
          (p->s).work[2] = (s32)q;
          if (*(u8*)((u8*)r + 0x2f) == 0) {
            {
              register u8 w3 asm("r0");
              register s32 k3 asm("r1");
              w3 = (p->s).work[3];
              k3 = 3;
              w3 &= k3;
              if (w3 == 0) {
                *(s32*)((u8*)r + 0x20) += 4;
              }
            }
            (p->s).work[3]++;
          }
        }
      } else {
        s32 z2 = 0;
        (p->s).work[2] = z2;
        (p->s).work[3] = 4;
        (p->s).d.y = z2;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// 0x08071A28
void FUN_08071a28(struct Enemy* p) {
  register struct Entity* q asm("r5");
  q = (p->s).unk_2c;
  if (q != NULL && q->mode[0] > 1) {
    {
      register u8 g asm("r0");
      register u8 h asm("r1");
      register s32 zr asm("r2");
      u8* a;
      h = (p->s).flags;
      asm("" : "+r"(h));
      g = 0xFE;
      g &= h;
      zr = 0;
      h = 0xFD;
      g &= h;
      (p->s).flags = g;
      a = (u8*)p + 0x8c;
      *(s32*)a = zr;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *(s32*)a = zr;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *a = zr;
    }
    (p->s).flags &= 0xFB;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x34);
      if (q != NULL) {
        if ((q->unk_28) == NULL && q->coord.y - (p->s).coord.y <= 0x27FF) {
          q->unk_28 = (void*)p;
          SetMotion(&p->s, 0x88 << 6);
        } else {
          q = NULL;
          (p->s).unk_2c = q;
        }
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      (p->s).coord.y = (p->s).coord.y + 0xFFFFFEC0;
      {
        register s32 cx asm("r1");
        register s32 lim asm("r0");
        cx = (p->s).coord.x;
        lim = 0x00267FFF;
        if (cx <= lim) {
          lim += 1;
          (p->s).coord.x = lim;
        }
      }
      {
        register s32 cx2 asm("r0");
        register s32 lim2 asm("r1");
        cx2 = (p->s).coord.x;
        lim2 = 0x00275000;
        if (cx2 > lim2) {
          (p->s).coord.x = lim2;
        }
      }
      UpdateMotionGraphic(&p->s);
      if (q != NULL) {
        q->coord.x = (p->s).coord.x;
        q->coord.y = (p->s).coord.y + (0x88 << 6);
      }
      if ((p->s).coord.y > 0x00019FFF) {
        break;
      }
      {
        register s32 m1 asm("r8");
        s32 m3;
        s32 m2;
        register s32 zr asm("r2");
        register u32 tbl asm("ip");
        register s32 three asm("r3");
        u8* a;
        {
          register u8 g asm("r0");
          register u8 h asm("r1");
          h = (p->s).flags;
          asm("" : "+r"(h));
          g = 0xFE;
          asm volatile("mov %0, %1" : "=r"(m1) : "l"(g));
          g &= h;
          zr = 0;
          m2 = 0xFD;
          asm("" : "+r"(m2));
          g &= m2;
          (p->s).flags = g;
        }
        a = (u8*)p + 0x8c;
        *(s32*)a = zr;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = zr;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = zr;
        {
          register u8 g2 asm("r0");
          register u8 h2 asm("r1");
          h2 = (p->s).flags;
          asm("" : "+r"(h2));
          m3 = 0xFB;
          asm("" : "+r"(m3));
          g2 = m3;
          g2 &= h2;
          (p->s).flags = g2;
        }
        {
          register u32 t1 asm("r1");
          t1 = (u32)gEnemyFnTable;
          asm volatile("mov %0, %1" : "=r"(tbl) : "l"(t1));
        }
        {
          EntityFunc** rt = (EntityFunc**)((((p->s).id) << 2) + tbl);
          three = 3;
          *(u32*)((p->s).mode) = three;
          (p->s).onUpdate = (void*)((*rt)[3]);
        }
        if (q == NULL) {
          break;
        }
        {
          register u8 g3 asm("r0");
          register u8 h3 asm("r1");
          h3 = q->flags;
          asm("" : "+r"(h3));
          g3 = m1;
          g3 &= h3;
          g3 &= m2;
          q->flags = g3;
        }
        a = (u8*)q + 0x8c;
        *(s32*)a = zr;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = zr;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = zr;
        {
          register u8 g4 asm("r0");
          register u8 h4 asm("r1");
          h4 = q->flags;
          asm("" : "+r"(h4));
          g4 = m3;
          g4 &= h4;
          q->flags = g4;
        }
        asm("" :: "l"(m2));
        {
          EntityFunc** rt2 = (EntityFunc**)(((q->id) << 2) + tbl);
          *(u32*)(q->mode) = three;
          q->onUpdate = (void*)((*rt2)[3]);
        }
      }
      break;
    }
  }
}


void FUN_08071b88(struct Enemy* p) {
  (p->s).d.y -= 0x10;
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  if ((p->s).coord.y <= 0x19FFF) {
    u8 f = ~DISPLAY & (p->s).flags;
    s32 z = 0;
    f = f & ~FLIPABLE;
    (p->s).flags = f;
    (p->body).status = z;
    (p->body).prevStatus = z;
    (p->body).invincibleTime = z;
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
  UpdateMotionGraphic(&p->s);
}

struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
static const motion_t sMotions[4];

void FUN_08071bf0(struct Enemy* p) {
  struct Coord c;
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  (p->s).flags &= ~COLLIDABLE;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(16);
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7f70(&p->s, &c, (motion_t*)sMotions, 4);
  {
    struct Entity* q = *(struct Entity**)&p->props[0];
    if (*((u8*)q + 0x2f) == 0) {
      *(s32*)((u8*)q + 0x20) += 5;
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/carry_arm_p3_p1b.inc");

void FUN_08071c70(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void CarryArm_Init(struct Enemy* p);
void CarryArm_Update(struct Enemy* p);
void CarryArm_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gCarryArmRoutine = {
    [ENTITY_INIT] =      CarryArm_Init,
    [ENTITY_UPDATE] =    CarryArm_Update,
    [ENTITY_DIE] =       CarryArm_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_080716a8(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366b48[6] = {
    FUN_080716a8,
    FUN_080716a8,
    FUN_080716a8,
    FUN_080716a8,
    FUN_080716a8,
    FUN_080716a8,
};
// clang-format on

void FUN_080716ac(struct Enemy* p);
void FUN_08071778(struct Enemy* p);
void FUN_08071888(struct Enemy* p);
void FUN_08071964(struct Enemy* p);
void FUN_08071a28(struct Enemy* p);
void FUN_08071b88(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366b60[6] = {
    FUN_080716ac,
    FUN_08071778,
    FUN_08071888,
    FUN_08071964,
    FUN_08071a28,
    FUN_08071b88,
};
// clang-format on

void FUN_08071bf0(struct Enemy* p);
void FUN_08071c70(struct Enemy* p);

const EnemyFunc PTR_ARRAY_08366b78[2] = {
    FUN_08071bf0,
    FUN_08071c70,
};

// --------------------------------------------

static const struct Collision sCollisions[] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
};

const u8 u8_ARRAY_08366bb0[2] = {0, 3};

static const motion_t sMotions[4] = {
    MOTION(SM034_CARRYARM, 0x02),
    MOTION(SM034_CARRYARM, 0x03),
    MOTION(SM034_CARRYARM, 0x04),
    MOTION(SM034_CARRYARM, 0x05),
};
