#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "mod.h"
#include "motion.h"
#include "story.h"
#include "zero.h"

struct PantheonGuardianObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 x;
  u8 unk_b8[4];
  u8 unk_bc;
  u8 unk_bd;
  u8 unk_be;
  u8 unk_bf;
  struct Entity* unk_c0;
};
static_assert(sizeof(struct PantheonGuardianObject) == sizeof(struct Enemy));

static const struct Collision sCollisions[];
static const struct Coord Coord_08365b70;

void FUN_0806465c(struct Body* body, struct Coord* c1, struct Coord* c2);

// ------------------------------------------------------------------------------------------------------------------------------------

static void PantheonGuardian_Init(struct PantheonGuardianObject* p);
void PantheonGuardian_Update(struct Enemy* p);
void PantheonGuardian_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonGuardianRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)PantheonGuardian_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)PantheonGuardian_Update,
    [ENTITY_DIE] =       (EnemyFunc)PantheonGuardian_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void PantheonGuardian_Init(struct PantheonGuardianObject* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if (MOD_ENABLED(gSystemSavedataManager.mods, MOD_P_GUARDIAN_HP4) && !FLAG(gCurStory.s.gameflags, DEMO_PLAY)) {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 14);
    body->parent = (void*)p;
    body->fn = NULL;
  } else {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 10);
    body->parent = (void*)p;
    body->fn = NULL;
  }
  {
    struct Body* body = &p->body;
    body->fn = FUN_0806465c;
  }
  p->x = (p->s).coord.x;
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  (p->s).d.x = (p->s).d.y = 0;
  p->unk_c0 = NULL;
  p->unk_b8[0] = 0, p->unk_b8[1] = 0;

  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  if ((pZero2->s).coord.x - (p->s).coord.x < 0) {
    (p->s).mode[1] = 1, (p->s).mode[2] = 0;
  } else {
    (p->s).mode[1] = 2, (p->s).mode[2] = 0;
  }
  PantheonGuardian_Update((void*)p);
}

INCASM("asm/enemy/pantheon_guardian_pre_p1_a.inc");

void FUN_08063da0(struct Enemy* p) {
  if (*(u32*)((u8*)p + 0xbc) <= 0x2FFF) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  if (*(u32*)((u8*)p + 0x8c) & 1) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (*(u32*)((u8*)p + 0xc0) != 0) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x40) == 0) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
  if (IsFrozen(&p->s)) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void doNothing_08063e10(struct Enemy* p) {
  if (IsFrozen(&p->s)) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void FUN_08063e28(struct Enemy* p) {
  if ((p->body).status & 1) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (*(struct Entity**)((u8*)p + 0xc0) != NULL) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x40) == 0) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
  if (IsFrozen(&p->s)) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void FUN_08063e80(struct Enemy* p) {
  if ((p->body).status & 1) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x40) == 0) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
  if (IsFrozen(&p->s)) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void FUN_08063ec8(struct Enemy* p) {
  if (*(struct Entity**)((u8*)p + 0xc0) != NULL) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (IsFrozen(&p->s)) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void FUN_08063ef4(struct Enemy* p) {
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x40) == 0) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
  if (IsFrozen(&p->s)) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void FUN_08063f28(struct Enemy* p) {
  if ((p->s).mode[1] == 8) return;
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

// 0x08063f50
void FUN_08063f50(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(0x14, 0x00));
      SetDDP(&p->body, sCollisions);
      (p->s).d.y = m;
      (p->s).d.x = m;
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 f;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      UpdateMotionGraphic(&p->s);
      if ((u8)--(p->s).work[2] != 0) {
        break;
      }
      {
        register s32 one asm("r3");
        f = (p->s).flags >> 4;
        one = 1;
        f &= one;
        if (*(u32*)((u8*)p + 0xbc) <= 0x5FFF) {
          if (f != one) goto walk;
          goto faceaway;
        } else {
          if (f == 0) goto faceaway;
        }
      }
    walk:
      (p->s).mode[1] = 1, (p->s).mode[2] = 0;
      break;
    faceaway:
      (p->s).mode[1] = 2, (p->s).mode[2] = 0;
      break;
    }
  }
}

u32 FUN_0800a40c(s32 x, s32 y);

// 0x08063fd8
void FUN_08063fd8(struct Enemy* p) {
  u8 m;
  if (FUN_080098a4((p->s).coord.x - 0xA80, (p->s).coord.y - 0x600) != 0 ||
      FUN_080098a4((p->s).coord.x - 0xA80, (p->s).coord.y + 0xA00) == 0 ||
      FUN_0800a40c((p->s).coord.x - 0xA80, (p->s).coord.y + 0xA00) != 0) {
    SET_XFLIP(p, 0);
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
    return;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(0x14, 0x01));
      SET_XFLIP(p, m);
      SetDDP(&p->body, sCollisions);
      (p->s).d.x = -0x80;
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 x = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = x;
      if (*(u32*)((u8*)p + 0xbc) > 0x5FFF) {
        if (*(s32*)((u8*)p + 0xb4) - x > 0x2800) {
          (p->s).mode[1] = 0;
          (p->s).mode[2] = 0;
        }
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080640dc
void FUN_080640dc(struct Enemy* p) {
  u8 m;
  if (FUN_080098a4((p->s).coord.x + 0xA80, (p->s).coord.y - 0x600) != 0 ||
      FUN_080098a4((p->s).coord.x + 0xA80, (p->s).coord.y + 0xA00) == 0 ||
      FUN_0800a40c((p->s).coord.x + 0xA80, (p->s).coord.y + 0xA00) != 0) {
    SET_XFLIP(p, 1);
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
    return;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(0x14, 0x01));
      SET_XFLIP(p, 1);
      SetDDP(&p->body, sCollisions);
      (p->s).d.x = 0x80;
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 x = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = x;
      if (*(u32*)((u8*)p + 0xbc) > 0x5FFF) {
        if (x - *(s32*)((u8*)p + 0xb4) > 0x2800) {
          (p->s).mode[1] = 0;
          (p->s).mode[2] = 0;
        }
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080641ec
void FUN_080641ec(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x14, 0x00));
      SetDDP(&p->body, sCollisions);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      u16 r;
      u16 mm;
      s32 v = (p->s).d.y;
      if (v <= 0x6FF) {
        (p->s).d.y = v + 0x40;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      r = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
      mm = r & 0x10;
      if (mm != 0) {
        (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        PantheonGuardian_Die(p);
      } else if (r != 0 && r != 0x800F && r != 0x800E) {
        (p->s).mode[1] = mm;
        (p->s).mode[2] = mm;
      }
      break;
    }
  }
}

// 0x0806429c
void FUN_0806429c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x14, 0x02));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SetMotion(&p->s, MOTION(0x14, 0x03));
        SetDDP(&p->body, &sCollisions[2]);
        PlaySound(0x3a);
        (p->s).work[2] = 0x40;
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      u8 t;
      UpdateMotionGraphic(&p->s);
      t = --(p->s).work[2];
      if (t == 0) {
        SetDDP(&p->body, sCollisions);
        SetMotion(&p->s, MOTION(0x14, 0x00));
        (p->s).mode[1] = t;
        (p->s).mode[2] = t;
      }
      break;
    }
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x40) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  }
}

// 0x08064354
void FUN_08064354(struct Enemy* p) {
  register s32 z5 asm("r5");
  z5 = (p->s).mode[2];
  switch (z5) {
    case 0:
      SetMotion(&p->s, MOTION(0x14, 4));
      SetDDP(&p->body, &sCollisions[4]);
      if (*((u8*)p + 0xb8) != 0) {
        register u8* a asm("r0");
        register u8* b asm("r2");
        register u8 ov asm("r1");
        register s32 m asm("r0");
        (p->s).d.x = 0x80;
        {
          register u8 g asm("r0");
          register u8 h asm("r1");
          h = (p->s).flags;
          asm("" : "+r"(h));
          g = 0xEF;
          g &= h;
          (p->s).flags = g;
        }
        a = (u8*)p + 0x4c;
        *a = z5;
        b = (u8*)p + 0x4a;
        ov = *b;
        m = 0x11;
        m = -m;
        m &= ov;
        *b = m;
      } else {
        register s32 one asm("r2");
        register u8* a2 asm("r0");
        register u8* b2 asm("r3");
        register s32 k10 asm("r2");
        register u8 ov2 asm("r1");
        register s32 m2 asm("r0");
        (p->s).d.x = -0x80;
        one = 1;
        {
          register u8 g2 asm("r0");
          register u8 h2 asm("r1");
          h2 = (p->s).flags;
          g2 = 0x10;
          g2 |= h2;
          (p->s).flags = g2;
        }
        a2 = (u8*)p + 0x4c;
        *a2 = one;
        b2 = (u8*)p + 0x4a;
        k10 = 0x10;
        ov2 = *b2;
        m2 = 0x11;
        m2 = -m2;
        m2 &= ov2;
        m2 |= k10;
        *b2 = m2;
      }
      {
        register s32 z asm("r1");
        z = 0;
        (p->s).work[2] = 0xC;
        (p->s).d.y = z;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 cx = (p->s).coord.x;
      s32 dx = (p->s).d.x;
      (p->s).coord.x = cx + dx;
      (p->s).d.x = ((dx << 1) + dx) >> 2;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      {
        register s32 fv asm("r1");
        register u8 nm asm("r0");
        {
          register s32 t2 asm("r0");
          register u8 h3 asm("r1");
          h3 = (p->s).flags;
          t2 = 0x10;
          t2 &= h3;
          asm("" : "+r"(t2));
          t2 <<= 24;
          fv = (u32)t2 >> 24;
        }
        if (fv == 0) {
          nm = 1;
        } else {
          fv = 0;
          nm = 2;
        }
        (p->s).mode[1] = nm;
        (p->s).mode[2] = fv;
      }
      break;
    }
  }
  if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x40) << 16) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  }
}

void FUN_08064444(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x14, 4));
    SetDDP(&p->body, &sCollisions[0]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
}

void FUN_0806447c(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x14, 0x00));
    (p->s).unk_coord.x = (p->s).d.x / 32;
    (p->s).work[2] = 0x1F;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).d.x -= (p->s).unk_coord.x;
  if ((u8)--(p->s).work[2] == 0xFF ||
      !(FUN_080098a4((p->s).coord.x, (p->s).coord.y + PIXEL(8)) & 0x1000)) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  } else {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  }
}

// 0x080644FC
void FUN_080644fc(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    register struct Zero** zp asm("r4");
    register s32 dist asm("r6");
    s32 dx, dy;
    SetMotion(&p->s, MOTION(0x14, 0x04));
    zp = &pZero2;
    {
      register struct Zero* z asm("r2");
      z = *zp;
      dx = (p->s).coord.x - (z->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).coord.y - (z->s).coord.y;
      dy += -0x1800;
      (p->s).d.y = dy;
    }
    {
      register s32 a asm("r1");
      register s32 t1 asm("r6");
      register s32 b asm("r0");
      register s32 t2 asm("r1");
      a = dx >> 8;
      asm volatile("add %0, %1, #0" : "=&l"(t1) : "l"(a));
      t1 *= a;
      b = dy >> 8;
      asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(b));
      t2 *= b;
      asm volatile("add %0, %1, #0" : "=&l"(b) : "l"(t2));
      dist = t1 + b;
    }
    {
      register s32 sq asm("r0");
      sq = ((s32(*)(u32))Sqrt)(dist);
      sq <<= 16;
      dist = (s32)(((u32)sq) >> 16);
    }
    if (dist == 0) {
      goto zerodist;
    }
    {
      register s32 nx asm("r4");
      register s32 ny asm("r0");
      nx = (p->s).d.x / dist;
      (p->s).d.x = nx;
      ny = (p->s).d.y / dist;
      {
        register s32 q asm("r1");
        q = (nx * 2 + nx) * 2;
        (p->s).d.x = q;
        q = (ny * 2 + ny) * 2;
        (p->s).d.y = q;
      }
    }
    goto haddir;
  zerodist : {
    register s32 v asm("r0");
    if (((*zp)->s.flags & 0x10) == 0) {
      goto negv;
    }
    v = 0xC0 * 8;
    goto stdx;
  negv:
    v = -0x600;
  stdx:
    (p->s).d.x = v;
    (p->s).d.y = 0;
  }
  haddir:;
    if ((p->s).d.x <= 0) {
      goto flipon;
    }
    {
      register s32 zz asm("r2");
      u8* oa;
      s32 m11, ov;
      zz = 0;
      {
        register u8 h asm("r1");
        register u8 g asm("r0");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xEF;
        g &= h;
        (p->s).flags = g;
      }
      *((u8*)p + 0x4c) = zz;
      oa = (u8*)p + 0x4a;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11;
      goto flipdone;
    }
  flipon : {
      register s32 one asm("r2");
      register u8* oa2 asm("r3");
      s32 sh4, ov2, m112;
      one = 1;
      {
        register u8 fl asm("r1");
        register s32 fv asm("r0");
        fl = (p->s).flags;
        fv = 0x10;
        fv |= fl;
        (p->s).flags = fv;
      }
      *((u8*)p + 0x4c) = one;
      oa2 = (u8*)p + 0x4a;
      one = 0x10;
      ov2 = *oa2;
      m112 = -0x11;
      m112 &= ov2;
      m112 |= one;
      *oa2 = m112;
    }
  flipdone:
    {
      register u8* a2 asm("r1");
      register s32 v2 asm("r0");
      a2 = (u8*)p + 0xb9;
      v2 = 1;
      *a2 = v2;
    }
    SetDDP(&p->body, &sCollisions[6]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 cx asm("r0");
    register s32 dxv asm("r3");
    register s32 cy asm("r1");
    register s32 dyv asm("r2");
    cx = (p->s).coord.x;
    dxv = (p->s).d.x;
    cx += dxv;
    (p->s).coord.x = cx;
    cy = (p->s).coord.y;
    dyv = (p->s).d.y;
    cy += dyv;
    (p->s).coord.y = cy;
    dyv += 0x40;
    (p->s).d.y = dyv;
    cx += dxv;
    if (((u16)FUN_080098a4(cx, cy) << 16) != 0) {
      goto die;
    }
  }
  {
    register s32 bx asm("r0");
    register s32 by asm("r1");
    register s32 k2 asm("r2");
    {
      register s32 t asm("r1");
      bx = (p->s).coord.x;
      t = (p->s).d.x;
      bx += t;
    }
    by = (p->s).coord.y;
    k2 = -0x1800;
    by += k2;
    if (((u16)FUN_080098a4(bx, by) << 16) == 0) {
      return;
    }
  }
die:
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  PantheonGuardian_Die(p);
}


void FUN_0806465c(struct Body* body, struct Coord* c1, struct Coord* c2) {
  if (body->hitboxFlags & 1) {
    struct Enemy* self = (struct Enemy*)body->parent;
    u8 r = 0;
    if ((pZero2->s).coord.x < (self->s).coord.x) {
      r = 1;
    }
    *(u8*)((u8*)self + 0xb8) = r;
  }
}

void FUN_08063da0(struct Enemy* p);
void doNothing_08063e10(struct Enemy* p);
void FUN_08063e28(struct Enemy* p);
void FUN_08063e80(struct Enemy* p);
void FUN_08063ec8(struct Enemy* p);
void FUN_08063ef4(struct Enemy* p);
void FUN_08063f28(struct Enemy* p);

// clang-format off
// 0x08365a80
const EnemyFunc sPantheonGuardianUpdates1[9] = {
    (EnemyFunc)FUN_08063da0,
    (EnemyFunc)FUN_08063da0,
    (EnemyFunc)FUN_08063da0,
    (EnemyFunc)doNothing_08063e10,
    (EnemyFunc)FUN_08063e28,
    (EnemyFunc)FUN_08063e80,
    (EnemyFunc)FUN_08063ec8,
    (EnemyFunc)FUN_08063ef4,
    (EnemyFunc)FUN_08063f28,
};
// clang-format on

void FUN_08063f50(struct Enemy* p);
void FUN_08063fd8(struct Enemy* p);
void FUN_080640dc(struct Enemy* p);
void FUN_080641ec(struct Enemy* p);
void FUN_0806429c(struct Enemy* p);
void FUN_08064354(struct Enemy* p);
void FUN_08064444(struct Enemy* p);
void FUN_0806447c(struct Enemy* p);
void FUN_080644fc(struct Enemy* p);

// clang-format off
// 0x08365aa4
static const EnemyFunc sPantheonGuardianUpdates2[9] = {
    (EnemyFunc)FUN_08063f50,
    (EnemyFunc)FUN_08063fd8,
    (EnemyFunc)FUN_080640dc,
    (EnemyFunc)FUN_080641ec,
    (EnemyFunc)FUN_0806429c,
    (EnemyFunc)FUN_08064354,
    (EnemyFunc)FUN_08064444,
    (EnemyFunc)FUN_0806447c,
    (EnemyFunc)FUN_080644fc,
};
// clang-format on

// --------------------------------------------

// 0x08365ac8
static const struct Collision sCollisions[7] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0200, -0x1000, 0x1000, 0x1000},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0200, -0x1000, 0x1000, 0x2000},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x1000, -0x1000, 0x3000, 0x1000},
    },
    [3] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0200, -0x1000, 0x1000, 0x2000},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1000, 0x1000, 0x1000},
    },
    [5] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x1000, 0x1000, 0x2000},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {-0x0200, -0x1000, 0x1000, 0x1000},
    },
};

static const struct Coord Coord_08365b70 = {0, -PIXEL(16)};
