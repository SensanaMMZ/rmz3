#include "collision.h"
#include "physics.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "story.h"
#include "vfx.h"
#include "zero.h"
#include "trig.h"
#include "projectile.h"

struct Enemy* CreatePetatria(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_PETATRIA);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

INCASM("asm/enemy/petatria_p1_pre_p1_p2_a.inc");

extern const EnemyFunc sUpdates1[10];
extern const EnemyFunc sUpdates2[10];
bool8 FUN_08091188(struct Enemy* p);
void Petatria_Die(struct Enemy* p);

void Petatria_Update(struct Enemy* p) {
  struct Entity** slot;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Petatria_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  FUN_08091188(p);
  if (IsFrozen(&p->s)) {
    return;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (*slot != NULL) {
    if (!isKilled(*slot)) {
      return;
    }
    *slot = NULL;
  }
  (sUpdates2[(p->s).mode[1]])(p);
}

struct VFX* FUN_080c4914(struct Coord* c, u8 a1, u16 a2, s32 a3);
u32 TryDropItem(u32 table, struct Coord* c);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

void Petatria_Die(struct Enemy* p) {
  if (gCurStory.s.gameflags[4] & 0x40) {
    u32 z2;
    {
      u32 fl = (p->s).flags & 0xFE;
      z2 = 0;
      fl &= 0xFD;
      (p->s).flags = fl;
    }
    {
      u8* w = (u8*)p + 0x8c;
      *(u32*)w = z2;
      asm("" : "+r"(w));
      w += 4;
      *(u32*)w = z2;
      asm("" : "+r"(w));
      w += 4;
      asm("" : "+r"(w));
      *(u8*)w = z2;
    }
    (p->s).flags &= 0xFB;
    {
      u32 tbl = (u32)gEnemyFnTable;
      u32 id = ((p->s).id) << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = 3;
      (p->s).onUpdate = (void*)((*rt)[3]);
    }
    return;
  }
  {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0:
        (p->s).mode[2] = 0xA;
        {
          u8* w = (u8*)p + 0x8c;
          *(u32*)w = m;
          asm("" : "+r"(w));
          w += 4;
          *(u32*)w = m;
          asm("" : "+r"(w));
          w += 4;
          asm("" : "+r"(w));
          *(u8*)w = m;
        }
        (p->s).flags &= 0xFB;
        (p->s).d.y = m;
        (p->s).d.x = m;
        // fallthrough
      case 1:
      case 10:
        (p->s).mode[2]++;
        break;
      case 11: {
        struct Coord c;
        struct Coord c2;
        struct Coord* cp;
        u32 r;
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y;
        CreateSmoke(1, &c);
        PlaySound(0x2A);
        cp = &(p->s).coord;
        TryDropItem(4, cp);
        r = RANDOM(RNG_0202f388) & 3;
        c2.x = (p->s).coord.x;
        c2.y = (p->s).coord.y + -0xC00;
        FUN_080c4914(&c2, ((p->s).flags >> 4) & 1, 0x7E1A, r);
        FUN_080c4914(&c2, ((p->s).flags >> 4) & 1, 0x7E1B, r);
        FUN_080c4914(&c2, ((p->s).flags >> 4) & 1, 0x7E1C, r);
        if (gMission.enemyCount <= 0x270E) {
          gMission.enemyCount++;
        }
        TryDropZakoDisk(p, cp);
        (p->s).flags &= 0xFE;
        {
          u32 tbl = (u32)gEnemyFnTable;
          u32 id = ((p->s).id) << 2;
          EntityFunc** rt = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = 4;
          (p->s).onUpdate = (void*)((*rt)[4]);
        }
        break;
      }
    }
  }
}

bool8 FUN_080902a8(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_B3) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

INCASM("asm/enemy/petatria_p1_pre_p2.inc");

bool8 FUN_080906ec(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_B3) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

INCASM("asm/enemy/petatria_p1_pre_p3_p1.inc");

bool8 FUN_08090b20(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[];
void FUN_0809118c(struct Enemy* p, struct Coord* c);

// 0x08090B24
void FUN_08090b24(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[4]);
      SetMotion(&p->s, 0x7E0E);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
      break;
    case 2: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 3:
      SetMotion(&p->s, 0x7E0F);
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y - 0x1C00;
      FUN_0809118c(p, &c);
      PlaySound(0x2C);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 5:
      SetMotion(&p->s, 0x7E10);
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 6: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 7:
      SetMotion(&p->s, 0x7E11);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 8:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_08090c60(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[12];
void FUN_0809118c(struct Enemy* p, struct Coord* c);

void FUN_08090c64(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[7]);
      SetMotion(&p->s, 0x7E12);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).work[2] = 0x1E;
      goto adv;
    case 3:
      SetMotion(&p->s, 0x7E13);
      if (*(u8*)((u8*)p + 0xb8) == 1) {
        c.x = (p->s).coord.x + 0x400;
      } else {
        c.x = (p->s).coord.x - 0x400;
      }
      c.y = (p->s).coord.y - 0x1900;
      FUN_0809118c(p, &c);
      PlaySound(0x2c);
      (p->s).mode[2]++;
      /* fallthrough */
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    adv:
      (p->s).mode[2]++;
      break;
    case 5:
      SetMotion(&p->s, 0x7E14);
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      /* fallthrough */
    case 2:
    case 6: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 7:
      SetMotion(&p->s, 0x7E15);
      (p->s).mode[2]++;
      /* fallthrough */
    case 8:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08090da4(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[12];

void FUN_08090da8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[11]);
      (p->s).work[2] = 4;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2:
      SetDDP(&p->body, &sCollisions[10]);
      SetMotion(&p->s, 0x7E16);
      (p->s).work[2] = 0x60;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      (p->s).work[2]--;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      if ((p->s).work[2] != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 4:
      SetMotion(&p->s, 0x7E18);
      (p->s).work[2] = (u32)RANDOM(RNG_0202f388) % 0x14 + 0xA;
      (p->s).mode[2]++;
      /* fallthrough */
    case 5: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 6:
      SetMotion(&p->s, 0x7E19);
      (p->s).mode[2]++;
      /* fallthrough */
    case 7: {
      u8 z;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      z = 0;
      (p->s).mode[1] = z;
      (p->s).mode[2] = z;
      break;
    }
  }
}


bool8 FUN_08090edc(struct Enemy* p) { return TRUE; }

void FUN_08090ee0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[11]);
      (p->s).work[2] = 4;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      s32 v;
      SetDDP(&p->body, &sCollisions[10]);
      SetMotion(&p->s, 0x7E17);
      (p->s).work[2] = 0x60;
      if (*((u8*)p + 0xb8) == 1) {
        s32 c = 0xCC;
        asm("" : "+r"(c));
        v = -c;
        goto vs;
      }
      v = 0xCC;
    vs:
      (p->s).d.x = v;
      (p->s).d.y = 0;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3: {
      s32 push;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (push == 0) {
        break;
      }
      (p->s).coord.y += push;
      (p->s).mode[2]++;
      break;
    }
    case 4:
      (p->s).work[2]--;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      if ((p->s).work[2] != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 5:
      SetMotion(&p->s, 0x7E18);
      (p->s).work[2] = (RANDOM(RNG_0202f388) % 0x14) + 0xA;
      (p->s).mode[2]++;
      // fallthrough
    case 6: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 7:
      SetMotion(&p->s, 0x7E19);
      (p->s).mode[2]++;
      // fallthrough
    case 8:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08091068(struct Enemy* p) { return TRUE; }

// 0x0809106C
void FUN_0809106c(struct Enemy* p) {
  register s32 m2 asm("r6");
  m2 = (p->s).mode[2];
  switch (m2) {
    case 0: {
      register s32 len asm("r5");
      s32 dx;
      s32 dy;
      dx = (p->s).unk_coord.x - (p->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).unk_coord.y - (p->s).coord.y;
      (p->s).d.y = dy;
      dx >>= 2;
      {
        s32 a = dx * dx;
        s32 b;
        dy >>= 2;
        b = dy * dy;
        len = (u32)Sqrt(a + b) << 2;
      }
      if (len != 0) {
        (p->s).d.x = ((p->s).d.x << 8) / len;
        (p->s).d.y = ((p->s).d.y << 8) / len;
      }
      (p->s).d.x = ((p->s).d.x << 9) >> 8;
      (p->s).d.y = ((p->s).d.y << 9) >> 8;
      *(s32*)((u8*)p + 0xb4) = len;
      if ((p->s).d.x > 0) {
        register s32 one asm("r2");
        register u8* a4c asm("r0");
        register u8* a4a asm("r3");
        register s32 k10 asm("r2");
        register u8 ov asm("r1");
        register s32 m asm("r0");
        one = 1;
        {
          register u8 fl asm("r1");
          register u8 g asm("r0");
          fl = (p->s).flags;
          g = 0x10;
          g |= fl;
          (p->s).flags = g;
        }
        a4c = (u8*)p + 0x4c;
        *a4c = one;
        a4a = (u8*)p + 0x4a;
        k10 = 0x10;
        ov = *a4a;
        m = 0x11;
        m = -m;
        m &= ov;
        m |= k10;
        *a4a = m;
      } else {
        register u8* b4c asm("r0");
        register u8* b4a asm("r2");
        register u8 ov2 asm("r1");
        register s32 m2b asm("r0");
        {
          register u8 fl2 asm("r1");
          register u8 g2 asm("r0");
          fl2 = (p->s).flags;
          asm("" : "+r"(fl2));
          g2 = 0xEF;
          g2 &= fl2;
          (p->s).flags = g2;
        }
        b4c = (u8*)p + 0x4c;
        *b4c = m2;
        b4a = (u8*)p + 0x4a;
        ov2 = *b4a;
        m2b = 0x11;
        m2b = -m2b;
        m2b &= ov2;
        *b4a = m2b;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32* q;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      q = (s32*)((u8*)p + 0xb4);
      *q += -0x200;
      break;
    }
  }
}

bool8 FUN_08091150(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/petatria_p1_pre_p3_p7.inc");

void FUN_08091154(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

bool8 FUN_08091168(struct Enemy* p) { return TRUE; }


void FUN_0809116c(struct Enemy* p) {}

bool8 FUN_08091170(struct Enemy* p) { return TRUE; }


void FUN_08091174(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

bool8 FUN_08091188(struct Enemy* p) { return TRUE; }

// 0x0809118C
void FUN_0809118c(struct Enemy* p, struct Coord* c) {
  register s32 dx asm("r4");
  register s32 dy asm("r5");
  register s32 len asm("r6");
  register s32 ang asm("r2");
  register struct Zero* z asm("r2");
  register struct Projectile* q asm("r1");
  z = pZero2;
  {
    register s32 t0 asm("r0");
    register s32 t1 asm("r1");
    t1 = (z->s).coord.x;
    t0 = c->x;
    dx = t1 - t0;
    t0 = c->y;
    t1 = 0x80 << 5;
    t0 = t0 + t1;
    t1 = (z->s).coord.y;
    dy = t1 - t0;
  }
  {
    register s32 sx asm("r0");
    register s32 sy asm("r1");
    register s32 px asm("r2");
    register s32 py asm("r3");
    sx = dx >> 2;
    px = sx * sx;
    asm("" : "+r"(px));
    sx = px;
    asm("" : "+r"(sx));
    sy = dy >> 2;
    py = sy * sy;
    asm("" : "+r"(py));
    sy = py;
    asm("" : "+r"(sy));
    sx = sx + sy;
    len = (u32)Sqrt(sx) << 2;
  }
  if (len != 0) {
    dx = (dx << 8) / len;
    dy = (dy << 8) / len;
  }
  {
  s32 a;
  if (dx > 0) {
    if (dy > 0) {
      register const s16* tb asm("r0");
      register s32 idx asm("r1");
      register const s16* e asm("r1");
      u16 sv;
      tb = gSineTable;
      asm("" : "+r"(tb));
      idx = ((u8)dy) * 2;
      asm volatile("add %0, %1, %2" : "=l"(e) : "l"(idx), "l"(tb));
      sv = *(const u16*)e;
      if (*e > 0) {
        a = 0x7E - sv;
        goto trunc;
      }
      a = sv;
      a = a + 0x7E;
      asm volatile("" : "+r"(a));
      goto trunc;
    }
    {
      register const s16* tb asm("r0");
      register s32 idx asm("r1");
      register const s16* e asm("r1");
      u16 sv;
      tb = gSineTable;
      asm("" : "+r"(tb));
      idx = ((u8)dy) * 2;
      asm volatile("add %0, %1, %2" : "=l"(e) : "l"(idx), "l"(tb));
      sv = *(const u16*)e;
      if (*e > 0) {
        a = sv;
        a += 0x7F;
        goto trunc;
      }
      a = -sv;
      a = a + 0x7F;
      asm volatile("" : "+r"(a));
      goto trunc;
    }
  }
  if (dy <= 0) {
    goto last;
  }
  {
    register const s16* tb2 asm("r0");
    register s32 idx2 asm("r1");
    register const s16* e2 asm("r1");
    tb2 = gSineTable;
    asm("" : "+r"(tb2));
    idx2 = ((u8)(dy + 0x40)) * 2;
    asm volatile("add %0, %1, %2" : "=l"(e2) : "l"(idx2), "l"(tb2));
    a = -*(const u8*)e2;
  trunc:
    a <<= 24;
    ang = (u32)a >> 24;
    goto done;
  }
last : {
    register const s16* tb3 asm("r1");
    register s32 idx3 asm("r0");
    register const s16* e3 asm("r0");
    tb3 = gSineTable;
    asm("" : "+r"(tb3));
    idx3 = ((u8)(dy + 0x40)) * 2;
    asm volatile("add %0, %1, %2" : "=l"(e3) : "l"(idx3), "l"(tb3));
    ang = *(const u8*)e3;
  }
done:;
  }
  q = ((struct Projectile * (*)(struct Coord*, s32, s32)) CreateLemon)(c, 0x80 << 2, ang);
  asm("" : "+r"(q));
  if (q != NULL) {
    register s32 t asm("r0");
    t = dx << 9;
    t >>= 8;
    (q->s).d.x = t;
    t = dy << 9;
    t >>= 8;
    (q->s).d.y = t;
  }
}

void nop_0809127c(struct Enemy* p) {}

void Petatria_Init(struct Enemy* p);
void Petatria_Update(struct Enemy* p);
void Petatria_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPetatriaRoutine = {
    [ENTITY_INIT] =      Petatria_Init,
    [ENTITY_UPDATE] =    Petatria_Update,
    [ENTITY_DIE] =       Petatria_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_080902a8(struct Enemy* p);
bool8 FUN_080906ec(struct Enemy* p);
bool8 FUN_08090b20(struct Enemy* p);
bool8 FUN_08090c60(struct Enemy* p);
bool8 FUN_08090da4(struct Enemy* p);
bool8 FUN_08090edc(struct Enemy* p);
bool8 FUN_08091068(struct Enemy* p);
bool8 FUN_08091150(struct Enemy* p);
bool8 FUN_08091168(struct Enemy* p);
bool8 FUN_08091170(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    (EnemyFunc)FUN_080902a8,
    (EnemyFunc)FUN_080906ec,
    (EnemyFunc)FUN_08090b20,
    (EnemyFunc)FUN_08090c60,
    (EnemyFunc)FUN_08090da4,
    (EnemyFunc)FUN_08090edc,
    (EnemyFunc)FUN_08091068,
    (EnemyFunc)FUN_08091150,
    (EnemyFunc)FUN_08091168,
    (EnemyFunc)FUN_08091170,
};
// clang-format on

void FUN_080902c8(struct Enemy* p);
void FUN_0809070c(struct Enemy* p);
void FUN_08090b24(struct Enemy* p);
void FUN_08090c64(struct Enemy* p);
void FUN_08090da8(struct Enemy* p);
void FUN_08090ee0(struct Enemy* p);
void FUN_0809106c(struct Enemy* p);
void FUN_08091154(struct Enemy* p);
void FUN_0809116c(struct Enemy* p);
void FUN_08091174(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    FUN_080902c8,
    FUN_0809070c,
    FUN_08090b24,
    FUN_08090c64,
    FUN_08090da8,
    FUN_08090ee0,
    FUN_0809106c,
    FUN_08091154,
    FUN_0809116c,
    FUN_08091174,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[12] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(0), -PIXEL(29), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(26), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(3), -PIXEL(25), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(22), -PIXEL(25), PIXEL(14), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
};

static const s32 s32_ARRAY_08369728[16] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};

// clang-format off
static const motion_t sMotions1[6] = {
    MOTION(SM126_PETATRIA, 0),
    MOTION(SM126_PETATRIA, 1),
    MOTION(SM126_PETATRIA, 2),
    MOTION(SM126_PETATRIA, 3),
    MOTION(SM126_PETATRIA, 4),
    MOTION(SM126_PETATRIA, 5),
};
// clang-format on

static const s32 s32_ARRAY_08369774[6] = {
    PIXEL(1), PIXEL(2), PIXEL(5), PIXEL(5), PIXEL(2), PIXEL(1),
};
static const s32 s32_ARRAY_0836978c[6] = {
    PIXEL(1), PIXEL(1), PIXEL(2), PIXEL(5), PIXEL(5), PIXEL(2),
};

// clang-format off
static const motion_t sMotions2[6] = {
    MOTION(SM126_PETATRIA, 6),
    MOTION(SM126_PETATRIA, 7),
    MOTION(SM126_PETATRIA, 8),
    MOTION(SM126_PETATRIA, 9),
    MOTION(SM126_PETATRIA, 10),
    MOTION(SM126_PETATRIA, 11),
};
// clang-format on

static const s32 s32_ARRAY_083697b0[6] = {
    -PIXEL(1), -PIXEL(2), -PIXEL(5), -PIXEL(5), -PIXEL(2), -PIXEL(1),
};
static const s32 s32_ARRAY_083697c8[6] = {
    -PIXEL(1), -PIXEL(1), -PIXEL(2), -PIXEL(5), -PIXEL(5), -PIXEL(2),
};
