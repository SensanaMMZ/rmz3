#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"
#include "metatile.h"
#include "physics.h"
#include "vfx.h"
#include "zero.h"
#include "overworld.h"

static const struct Collision sCollisions[8];

static const EnemyFunc sDeads[3];

struct Entity* FUN_08088b4c(s32 x, s32 y, u8 kind) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_METTAUR_SWIM);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    (p->coord).x = x, (p->coord).y = y;
    p->work[0] = kind;
  }
  return p;
}

u8 FUN_08088ba8(struct Enemy* p) {
  s32 val = PushoutToUp1((p->s).coord.x, (p->s).coord.y + PIXEL(8));
  if (val < 0) return TRUE;
  return FALSE;
}

// 0x08088bc8
s32 FUN_08088bc8(struct Enemy* p, s32 dx, s32 dy) {
  s32 y;
  if (dy != 0) {
    y = (p->s).coord.y + dy;
    (p->s).coord.y = y;
    if (dy < 0) {
      dy = PushoutToDown1((p->s).coord.x, y - PIXEL(16));
      if (dy > 0) {
        y = (p->s).coord.y;
        y += dy;
        (p->s).coord.y = y;
      }
    } else {
      dy = PushoutToUp1((p->s).coord.x, y);
      if (dy < 0) {
        y = (p->s).coord.y;
        y += dy;
        (p->s).coord.y = y;
      }
    }
  }
  if (dx != 0) {
    s32 x = (p->s).coord.x + dx;
    (p->s).coord.x = x;
    if (dx < 0) {
      dy = PushoutToRight1(x, (p->s).coord.y - PIXEL(8));
      if (dy > 0) {
        y = (p->s).coord.x;
        y += dy;
        (p->s).coord.x = y;
      }
    } else {
      dy = PushoutToLeft1(x, (p->s).coord.y - PIXEL(8));
      if (dy < 0) {
        y = (p->s).coord.x;
        y += dy;
        (p->s).coord.x = y;
      }
    }
  }
}

INCASM("asm/enemy/mettaur_swim_p1_pre_p1.inc");

bool8 FUN_08088cfc(struct Enemy* p) {
  u8 f[2];
  u8* b;
  u8* a;
  b = f;
  a = f;
  a[1] = 0;
  b[0] = 0;
  {
    register s32 x asm("r2") = (p->s).coord.x;
    register s32 c asm("r3");
    register s32 yl asm("r0");
    s32 y;
    yl = (p->s).coord.y;
    c = -PIXEL(16);
    asm("" : "+r"(c));
    y = yl + c;
    if (PushoutToDown1(x, y) > 0) {
      f[0] = 1;
    }
  }
  {
    register s32 x asm("r2") = (p->s).coord.x;
    register s32 c asm("r3");
    register s32 yl asm("r0");
    s32 y;
    yl = (p->s).coord.y;
    c = PIXEL(1);
    asm("" : "+r"(c));
    y = yl + c;
    if (PushoutToUp1(x, y) < 0) {
      f[1] = 1;
    }
  }
  return f[0] & f[1];
}

void CreateVFX62(struct Entity* e, struct Coord* c);

void FUN_08088d54(struct Enemy* p) {
  struct Coord c;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(20);
  CreateSmoke(2, &c);
  CreateVFX62(&p->s, &c);
}

static const u8 sInitModes[6];
static const motion_t sMotions[4];
static const EnemyFunc sInitializers[13];
static const EnemyFunc sUpdates[13];
void MettaurSwim_Update(struct Enemy* p);
void FUN_08089218(struct Body* body);

// Alloc-copy basin: retail keeps s2 in r2 with an adds-copy into r1 feeding
// the xflip store and the oam insert's shift; every pin/transfer/manual-insert
// spelling either loses the copy, blocks the &1 fold, or shifts the k1 web.
NON_MATCH void MettaurSwim_Init(struct Enemy* p) {
#if MODERN
  s32 one;
  if ((p->s).work[0] == 2 && (p->s).coord.y < gOverworld.sea + 0x1000) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  {
    u32 tbl = (u32)gEnemyFnTable;
    u32 id = (p->s).id << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
  }
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= COLLIDABLE;
  {
    struct Body* body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 2);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)FUN_08089218;
  }
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.x;
  *(s32*)((u8*)p + 0xbc) = (p->s).coord.y;
  {
    u16 w = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
    if (w != 0) {
      *((u8*)p + 0xc2) = one;
    } else {
      *((u8*)p + 0xc2) = w;
    }
  }
  if ((p->s).work[0] != 4) {
    InitNonAffineMotion(&p->s);
    {
      u32 s2 = 0;
      if (pZero2->s.coord.x - (p->s).coord.x > 0) {
        s2 = 1;
      }
      SET_XFLIP(p, s2);
      (p->s).flags |= DISPLAY;
    }
    SetMotion(&p->s, sMotions[(p->s).work[0]]);
  }
  if ((p->s).work[0] == 1) {
    struct Enemy* c = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
    if (c != NULL) {
      (c->s).taskCol = 0x18;
      INIT_ENEMY_ROUTINE(c, 0x30);
      (c->s).tileNum = 0;
      (c->s).palID = 0;
      (c->s).flags2 |= WHITE_PAINTABLE;
      (c->s).invincibleID = (c->s).uniqueID;
      (c->s).work[0] = 4;
      (c->s).unk_28 = &p->s;
    }
  }
  if ((p->s).work[0] == 0 || (p->s).work[0] == 3) {
    (p->s).coord.y += 0x7FF;
    if ((u32)(FUN_080098a4((p->s).coord.x, (p->s).coord.y) << 16) != 0) {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    }
  }
  if (IsFrozen(&p->s)) {
    (sInitializers[(p->s).mode[1]])(p);
    (sUpdates[(p->s).mode[1]])(p);
  }
  MettaurSwim_Update(p);
#else
  INCCODE("asm/enemy/mettaur_swim_init.inc");
#endif
}

INCASM("asm/enemy/mettaur_swim_p1_pre_p2.inc");

void MettaurSwim_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_08089218(struct Body* body) {
  struct Enemy* self = (struct Enemy*)body->parent;
  struct Entity* atkParent = (struct Entity*)(body->enemy)->parent;
  if (body->hitboxFlags & 8) {
    if (*(u16*)&atkParent->kind == 0x1206) {
      SET_ENEMY_ROUTINE(self, ENTITY_DIE);
      (self->s).mode[1] = 0;
    }
  }
  *(s32*)&self->props[0] = (pZero2->s).coord.x - (self->s).coord.x;
}

void nop_08089268(struct Enemy* p) {}

u8 FUN_08088ba8(struct Enemy* p);

void FUN_0808926c(struct Enemy* p) {
  if (FUN_08088ba8(p) == 0) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 0xc;
    (p->s).mode[2] = 0;
  }
}

void FUN_080892a4(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 0xc;
    (p->s).mode[2] = 0;
  }
}

s32 FUN_0800a40c(s32 x, s32 y);

// 0x080892C4
void FUN_080892c4(struct Enemy* p) {
  register s32 x asm("r3");
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).d.x = m;
      (p->s).work[2] = 0x3C;
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0xDD, 0x02));
      (p->s).mode[2]++;
    case 1:
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
        x = (p->s).coord.x;
        goto move;
      }
      {
        struct Zero* z = pZero2;
        s32 zx = (z->s).coord.x;
        s32 cx = (p->s).coord.x;
        s32 d;
        d = zx - cx;
        asm volatile("add %0, %1, #0" : "=&l"(x) : "l"(cx));
        if (d < 0) {
          goto neg;
        }
        {
          s32 k = 0x5FFF;
          asm("" : "+r"(k));
          if (d <= k) {
            goto set;
          }
        }
        goto move;
      neg:
        d = x - zx;
        {
          s32 k = 0x5FFF;
          asm("" : "+r"(k));
          if (d > k) {
            goto move;
          }
        }
      set:
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
    move:
      FUN_08088bc8(p, FUN_0800a40c(x, (p->s).coord.y + 0x400), 0x800);
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_080892c4(struct Enemy* p);
s32 FUN_0800a40c(s32 x, s32 y);

void FUN_08089364(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 onRight = 0;
      s32 v;
      s32 z6;
      if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
        onRight = 1;
      }
      v = onRight;
      if (v != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        s32 sv = onRight;
        bool8* xa;
        asm("" : "+r"(onRight));
        xa = &((p->s).spr).xflip;
        z6 = 0;
        *xa = sv;
        ((p->s).spr).oam.xflip = sv;
      }
      {
        s32 off = (v * 5 << 10) - 0xA00;
        if (FUN_080098a4((p->s).coord.x + off, (p->s).coord.y - 0x800) != 0) {
          (p->s).mode[1] = z6;
          (p->s).mode[2] = z6;
          FUN_080892c4(p);
          break;
        }
      }
      SetMotion(&p->s, 0xDD03);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        s32 d = (p->s).coord.x - *(s32*)((u8*)p + 0xb8);
        u32 neg = (u32)d >> 31;
        if ((p->s).flags & X_FLIP) {
          if (neg == 0) goto chk;
          goto rng;
        } else {
          if (neg == 0) goto rng;
        }
      chk:
        {
          s32 a = d;
          if (a < 0) {
            a = -a;
          }
          if (a > 0x7000) {
            (p->s).mode[1] = 4;
            (p->s).mode[2] = 0;
            break;
          }
        }
      rng:
        if ((RANDOM(RNG_0202f388) & 0xF) <= 9) {
          (p->s).mode[1] = 3;
          (p->s).mode[2] = 0;
        } else {
          (p->s).mode[1] = 4;
          (p->s).mode[2] = 0;
        }
      }
      FUN_08088bc8(p, FUN_0800a40c((p->s).coord.x, (p->s).coord.y + 0x400), 0x800);
      break;
  }
}

INCASM("asm/enemy/mettaur_swim_p2_pre_p2_p1b.inc");

struct Projectile* CreateLemon(struct Coord* c, s32 r1, u8 r2);

// 0x080898BC -- swimming mettaur figure-eight: ride a sine path around the
// stored anchor, flipping half-phase each wrap, and fire a lemon pair on a
// 0x78-frame timer. Blocker (sine-path register rotation): retail threads
// {x accumulator, gSineTable base, phase copy} through r4/r3/r3 with a
// three-operand base add, ours rotates them and adds in place. An explicit
// table-pointer variable and an r3 pin each fixed part of it; pinning both
// the accumulator and the table did not close the remaining 23 bytes.
NON_MATCH void FUN_080898bc(struct Enemy* p) {
#if MODERN
  struct Coord c;
  s32 yb;
  s32 sv;
  u8 m2 = (p->s).mode[2];
  switch (m2) {
    case 0:
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0xDD, 0x06));
      (p->s).work[2] = m2;
      (p->s).work[3] = m2;
      *(u16*)((u8*)p + 0xc0) = 0x78;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      u8 t;
      (p->s).work[2]++;
      t = (p->s).work[2];
      if (t == 0) {
        (p->s).work[3] ^= 1;
      }
      if ((p->s).work[3] != 0) {
        s32 base = *(s32*)((u8*)p + 0xb8);
        s32 x = base + 0x1800;
        const s16* st = gSineTable;
        s32 a = 0x80 - t;
        x += st[(u8)(a + 0x40)] * 3 << 3;
        (p->s).coord.x = x;
        yb = *(s32*)((u8*)p + 0xbc);
        sv = st[(u8)a];
      } else {
        s32 base = *(s32*)((u8*)p + 0xb8);
        s32 x = base - 0x1800;
        const s16* st = gSineTable;
        x += st[(u8)(t + 0x40)] * 3 << 3;
        (p->s).coord.x = x;
        yb = *(s32*)((u8*)p + 0xbc);
        sv = st[t];
      }
      (p->s).coord.y = yb + (sv << 5);
      {
        u16* tp = (u16*)((u8*)p + 0xc0);
        *tp = *tp - 1;
        if ((u16)*tp == 0) {
          *tp = 0x78;
          PlaySound(0x2C);
          c.x = (p->s).coord.x - 0x800;
          c.y = (p->s).coord.y + 0x400;
          CreateLemon(&c, 0x200, 0xE0);
          c.x = (p->s).coord.x + 0x800;
          c.y = (p->s).coord.y + 0x400;
          CreateLemon(&c, 0x200, 0xA0);
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/enemy/mettaur_swim_898bc.inc");
#endif
}

void FUN_08089a00(struct Enemy* p) {
  struct Entity* par = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[4]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x = par->coord.x;
      (p->s).coord.y = par->coord.y;
      break;
  }
}

void FUN_08089a34(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 z = 0;
      (p->s).work[0] = z;
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0xdd, 0x7));
      (p->s).d.x = z;
      (p->s).d.y = z;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1:
      FUN_08088bc8(p, 0, (p->s).d.y);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      SetMotion(&p->s, MOTION(0xdd, 0x8));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      FUN_08088bc8(p, 0, (p->s).d.y);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (FUN_08088ba8(p) != 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 4:
      SetMotion(&p->s, MOTION(0xdd, 0xe));
      (p->s).mode[2]++;
      /* fallthrough */
    case 5:
      UpdateMotionGraphic(&p->s);
      FUN_08088bc8(p, 0, (p->s).d.y);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/mettaur_swim_p2_pre_p2_p2.inc");


void FUN_08089e60(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0xdd, 0xc));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 9;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/mettaur_swim_p2_post.inc");

void FUN_08089eb0(struct Enemy* p);

void FUN_08089f60(struct Enemy* p) {
  s32 dx, dy, q2, dist;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[6]);
      SetMotion(&p->s, MOTION(0xDD, 0x02));
      dx = (p->s).coord.x - (pZero2->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).coord.y - PIXEL(24);
      dy -= (pZero2->s).coord.y;
      (p->s).d.y = dy;
      dist = (dx >> 8) * (dx >> 8);
      dist += (dy >> 8) * (dy >> 8);
      dist = Sqrt(dist) << 8;
      if (dist != 0) {
        q2 = ((p->s).d.x << 8) / dist;
        (p->s).d.x = q2;
        dy = ((p->s).d.y << 8) / dist;
        (p->s).d.x = q2 * 6;
        (p->s).d.y = dy * 6;
      } else {
        (p->s).d.x = 0x600;
        (p->s).d.y = dist;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 y;
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      if (FUN_080098a4((p->s).coord.x, y) || ((p->body).status & 4)) {
        (p->s).mode[2] = 0;
        FUN_08089eb0(p);
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      }
      break;
    }
  }
}

void FUN_0808a068(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      struct Coord c;
      (p->s).flags &= ~DISPLAY;
      EXIT_BODY(p);
      c.x = (p->s).coord.x, c.y = (p->s).coord.y - PIXEL(8);
      CreateSmoke(1, &c);
      if ((p->s).work[0] == 2) {
        PlaySound(SE_UNK_31);
      } else {
        PlaySound(SE_ZAKO_EXPLODE);
      }
      (p->s).mode[2]++;
      break;
    }
    case 1: {
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      break;
    }
  }
}

void MettaurSwim_Init(struct Enemy* p);
void MettaurSwim_Update(struct Enemy* p);
void MettaurSwim_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gMettaurSwimRoutine = {
    [ENTITY_INIT] =      MettaurSwim_Init,
    [ENTITY_UPDATE] =    MettaurSwim_Update,
    [ENTITY_DIE] =       MettaurSwim_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCollisions[8] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(24), PIXEL(16), PIXEL(6)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(24), PIXEL(16), PIXEL(6)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(6), PIXEL(16), PIXEL(16)},
    },
};

// --------------------------------------------

void FUN_0808926c(struct Enemy* p);
void FUN_080892a4(struct Enemy* p);
void nop_08089268(struct Enemy* p);

// clang-format off
static const EnemyFunc sInitializers[13] = {
    FUN_0808926c,
    FUN_0808926c,
    FUN_0808926c,
    FUN_0808926c,
    FUN_0808926c,
    FUN_080892a4,
    FUN_080892a4,
    nop_08089268,
    FUN_080892a4,
    nop_08089268,
    nop_08089268,
    nop_08089268,
    nop_08089268,
};
// clang-format on

// --------------------------------------------

void FUN_080892c4(struct Enemy* p);
void FUN_08089364(struct Enemy* p);
void FUN_080894a4(struct Enemy* p);
void FUN_0808959c(struct Enemy* p);
void FUN_08089694(struct Enemy* p);
void FUN_08089790(struct Enemy* p);
void FUN_080898bc(struct Enemy* p);
void FUN_08089a00(struct Enemy* p);
void FUN_08089a34(struct Enemy* p);
void FUN_08089b48(struct Enemy* p);
void FUN_08089c94(struct Enemy* p);
void FUN_08089e60(struct Enemy* p);
void FUN_08089f60(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates[13] = {
    FUN_080892c4,
    FUN_08089364,
    FUN_080894a4,
    FUN_0808959c,
    FUN_08089694,
    FUN_08089790,
    FUN_080898bc,
    FUN_08089a00,
    FUN_08089a34,
    FUN_08089b48,
    FUN_08089c94,
    FUN_08089e60,
    FUN_08089f60,
};
// clang-format on

// --------------------------------------------

void FUN_08089eb0(struct Enemy* p);
void FUN_08089f60(struct Enemy* p);
void FUN_0808a068(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_08089eb0,
    FUN_08089f60,
    FUN_0808a068,
};

// --------------------------------------------

static const u8 sInitModes[6] = {0, 6, 9, 0, 7, 0};

static const motion_t sMotions[4] = {
    MOTION(SM221_METTAUR, 0),
    MOTION(SM000_BATTLE_EFFECT, 6),
    MOTION(SM000_BATTLE_EFFECT, 9),
    MOTION(SM221_METTAUR, 0),
};
