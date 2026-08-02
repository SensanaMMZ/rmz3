#include "collision.h"
#include "global.h"
#include "overworld.h"
#include "physics.h"
#include "solid.h"
#include "vfx.h"
#include "zero.h"

struct IcebonIceObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 y;
  u8 unk_04[12];
};
static_assert(sizeof(struct IcebonIceObject) == sizeof(struct Solid));

static const u8 sInitModes[2];
static const struct Collision sCollisions[5];
static const motion_t sMotions[4];

static void IcebonIce_Init(struct IcebonIceObject* p);
static void IcebonIce_Update(struct Solid* p);
static void IcebonIce_Die(Object* p);

// clang-format off
const SolidRoutine gIcebonIceRoutine = {
    [ENTITY_INIT] =      (SolidFunc)IcebonIce_Init,
    [ENTITY_UPDATE] =    (SolidFunc)IcebonIce_Update,
    [ENTITY_DIE] =       (SolidFunc)IcebonIce_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void icebon_080ca550(struct Entity* e, u8 n) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_ICEBON_ICE);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord.x = (e->coord).x;
    p->coord.y = (e->coord).y - PIXEL(21);
    p->work[0] = n;
    p->unk_28 = e;
  }
}

// --------------------------------------------

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  // nop
  return;
}

static void IcebonIce_Init(struct IcebonIceObject* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, &sCollisions[0], 8, onCollision);
  p->y = (p->s).coord.y;
  IcebonIce_Update((void*)p);
}

// --------------------------------------------

void FUN_080ca700(struct Solid* p);
static void nop_080ca6fc(struct Solid* p);
void FUN_080ca76c(struct Solid* p);

void FUN_080ca7d8(struct IcebonIceObject* p);
void FUN_080ca880(struct IcebonIceObject* p);
void FUN_080ca988(struct Solid* p);
void FUN_080caafc(struct Solid* p);
void FUN_080cab58(struct Solid* p);
void FUN_080cabe8(struct Solid* p);

static void IcebonIce_Update(struct Solid* p) {
  // clang-format off
  static const SolidFunc sUpdates1[6] = {
      FUN_080ca700,
      nop_080ca6fc,
      nop_080ca6fc,
      FUN_080ca76c,
      nop_080ca6fc,
      nop_080ca6fc,
  };
  // clang-format on

  // clang-format off
  static const SolidFunc sUpdates2[6] = {
      (SolidFunc)FUN_080ca7d8,
      (SolidFunc)FUN_080ca880,
      FUN_080ca988,
      FUN_080caafc,
      FUN_080cab58,
      FUN_080cabe8,
  };
  // clang-format on

  if ((p->body).status & BODY_STATUS_DEAD) {
    (p->s).flags2 &= ~ENTITY_HAZARD;
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    IcebonIce_Die((void*)p);
    return;
  }

  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void IcebonIce_Die(Object* p) {
  struct Coord c;

  PlaySound(SE_ICE_BREAK);
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;

  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y + PIXEL(16);
  FUN_080b81a0((struct Entity*)p, &c, (motion_t*)sMotions, 4);
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void nop_080ca6fc(struct Solid* p) {
  // nop
  return;
}

// --------------------------------------------

extern const struct Rect Rect_0836fd58;

// 0x080ca700
void FUN_080ca700(struct Solid* p) {
  struct Entity* icebon = (p->s).unk_28;
  if (icebon->mode[0] >= ENTITY_DISAPPEAR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (icebon->mode[0] >= ENTITY_DIE) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
  }
}

// 0x080ca700 と全く同じ
void FUN_080ca76c(struct Solid* p) {
  struct Entity* icebon = (p->s).unk_28;
  if (icebon->mode[0] >= ENTITY_DISAPPEAR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (icebon->mode[0] >= ENTITY_DIE) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
  }
}

// 0x080ca7d8
void FUN_080ca7d8(struct IcebonIceObject* p) {
  if ((p->body).hp >= 5) {
    SetMotion(&p->s, MOTION(SM017_ICEBON_ICE, 0));
  } else {
    SetMotion(&p->s, MOTION(SM017_ICEBON_ICE, 2));
  }
  UpdateMotionGraphic(&p->s);

  switch ((p->s).mode[2]) {
    case 0: {
      p->y = (p->s).coord.y;
      (p->s).unk_coord.y = (p->s).coord.y;
      (p->s).flags2 |= ENTITY_HAZARD;
      (p->s).size = (struct Rect*)&Rect_0836fd58;
      (p->s).hazardAttr = 0x801;
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 y;
      p->y -= PIXEL(1) / 2;
      y = p->y - (p->s).coord.y;
      if (y < 0) y += 7;
      (p->s).coord.y += y >> 3;
      if ((p->s).coord.y - (p->s).unk_coord.y <= -PIXEL(15)) (p->s).mode[1] = 1, (p->s).mode[2] = 0;
      break;
    }
  }
}

// 0x080ca880
void FUN_080ca880(struct IcebonIceObject* p) {
  if ((p->body).hp >= 5) {
    SetMotion(&p->s, MOTION(SM017_ICEBON_ICE, 1));
  } else {
    SetMotion(&p->s, MOTION(SM017_ICEBON_ICE, 3));
  }
  UpdateMotionGraphic(&p->s);

  {
    s32 md = (p->s).mode[2];
    switch (md) {
      case 0: {
        (p->s).flags2 |= ENTITY_HAZARD;
        (p->s).size = (struct Rect*)&Rect_0836fd58;
        (p->s).hazardAttr = 0x801;
        SetDDP(&p->body, &sCollisions[1]);
        (p->s).work[2] = 0x30;
        (p->s).unk_coord.y = md;
        (p->s).mode[2]++;
        FALLTHROUGH;
      }
      case 1: {
        s32 hit;
        s32 grounded;
        s32 cy;
        register s32 vel asm("r0");
        p->y -= 0x80;
        grounded = 0;
        {
          struct Overworld* ow = &gOverworld;
          if (p->y < ow->sea) {
            p->y = ow->sea;
            grounded = 1;
          }
        }
        hit = PushoutToDown1((p->s).coord.x, p->y);
        if (hit > 0) {
          p->y += hit;
          grounded = 1;
        }
        {
          s32 st = (p->body).status & 4;
          cy = (p->s).coord.y;
          if (st && cy > (pZero2->s).coord.y) {
          vel = 0x800;
          } else {
            vel = 0;
          }
        }
        (p->s).unk_coord.y = vel;
        if (grounded != 0) {
          u8 t = --(p->s).work[2];
          if (t == 0) {
            (p->s).mode[1] = 2;
            (p->s).mode[2] = t;
          }
        }
        {
          s32 dy = p->y + (p->s).unk_coord.y - cy;
          if (dy < 0) dy += 7;
          (p->s).coord.y = cy + (dy >> 3);
        }
        break;
      }
    }
  }
}

void FUN_080b98ac(s32 x, s32 y);

// 0x080ca988 -- melting ice block: shrink, dust, sea-clamped float, fade out.
// Blocker (formation-home basin): retail forms the p+0xb4 pointer in r2 and
// copies to its r4 home after the sea loads; every source shape tried either
// forms r4-directly (no copy), loads in the wrong order, or collapses the
// gOverworld.sea address insns; two pool-scratch picks (r1 vs r3) ride on it.
NON_MATCH void FUN_080ca988(struct Solid* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0:
      InitScalerotMotion1(&p->s);
      if ((p->body).hp > 4) {
        SetMotion(&p->s, 0x1101);
      } else {
        SetMotion(&p->s, 0x1103);
      }
      (p->s).work[2] = 0xFF;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32* py;
      u32 st;
      s32 y;
      s32 lift;
      s32 t = (p->s).work[3] + 1;
      (p->s).work[3] = t;
      if ((t & 3) == 0) {
        FUN_080b98ac((p->s).coord.x + ((s32)(RANDOM(RNG_0202f388) % 0x1800) - 0xE00),
                     (p->s).coord.y + (RANDOM(RNG_0202f388) & 0xFFF));
      }
      UpdateMotionGraphic(&p->s);
      ((p->s).spr).mag.y = (p->s).work[2];
      (p->s).work[2] -= 8;
      py = (s32*)((u8*)p + 0xb4);
      if (*py < gOverworld.sea) {
        *py = gOverworld.sea;
      }
      st = *(u32*)((u8*)p + 0x8c) & 4;
      y = (p->s).coord.y;
      if (st && y > ((pZero2->s).coord.y)) {
        lift = 0x800;
      } else {
        lift = 0;
      }
      (p->s).unk_coord.y = lift;
      (p->s).coord.y = y + ((*py + (p->s).unk_coord.y - y) / 8);
      {
        u32 w2 = (p->s).work[2];
        if (w2 <= 0x9F) {
          (p->s).flags2 &= 0xF7;
        }
        if (w2 <= 8) {
          (p->s).flags &= 0xFC;
          (p->body).status = 0;
          (p->body).prevStatus = 0;
          (p->body).invincibleTime = 0;
          (p->s).flags &= 0xFB;
          SET_SOLID_ROUTINE(p, ENTITY_DIE);
        }
      }
      break;
    }
  }
#else
  INCCODE("asm/solid/icebon_ca988.inc");
#endif
}
// 0x080CAAFC
void FUN_080caafc(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x11, 0x04));
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
    case 1: {
      s32 d;
      u8 t;
      d = (p->s).work[2] - 1;
      (p->s).work[2] = d;
      t = d;
      if (t == 0) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = t;
      }
      (p->s).coord.y -= 0x80;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080cab58(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, MOTION(0x11, 0x05));
      (p->s).work[2] = 0x30;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 hit;
      s32 rise;
      (p->s).coord.y -= 0x80;
      rise = 0;
      {
        struct Overworld* ow = &gOverworld;
        if ((p->s).coord.y < ow->sea) {
          (p->s).coord.y = ow->sea;
          rise = 1;
        }
      }
      hit = PushoutToDown1((p->s).coord.x, (p->s).coord.y);
      if (hit > 0) {
        (p->s).coord.y += hit;
        rise = 1;
      }
      if (rise != 0) {
        u8 t = --(p->s).work[2];
        if (t == 0) {
          (p->s).mode[1] = 5;
          (p->s).mode[2] = t;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080CABE8 -- shattered-ice disappear: shrink both mags, dust every 4th
// tick, kill body and route to DISAPPEAR. Blocker (home-transposition basin):
// the staged RMW zero and the staged 3 (shared by the &3 mask and the mode
// word) come out r10/r9; retail has them r9/r10. Everything else is
// byte-exact (asm-def k3 + rowp split + index-first cast reproduce the whole
// tail); no ref/range/birth-order shape flipped the pair.
NON_MATCH void FUN_080cabe8(struct Solid* p) {
#if MODERN
  u8 m2 = (p->s).mode[2];
  switch (m2) {
    case 0:
      InitScalerotMotion1(&p->s);
      SetMotion(&p->s, MOTION(0x11, 0x05));
      (p->s).work[2] = 0xFF;
      (p->s).work[3] = m2;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 k3;
      s32 t = (p->s).work[3] + 1;
      (p->s).work[3] = t;
      asm("movs %0, #3" : "=l"(k3));
      if ((t & k3) == 0) {
        s32 xo = (s32)(RANDOM(RNG_0202f388) % 0x1800) - 0xE00;
        s32 x = (p->s).coord.x + xo;
        FUN_080b98ac(x, (p->s).coord.y + (RANDOM(RNG_0202f388) & 0xFFF));
      }
      UpdateMotionGraphic(&p->s);
      ((p->s).spr).mag.x = (p->s).work[2];
      ((p->s).spr).mag.y = (p->s).work[2];
      {
        if ((u8)((p->s).work[2] -= 8) <= 8) {
          (p->s).flags &= ~DISPLAY;
          (p->s).flags &= ~FLIPABLE;
          (p->body).status = 0;
          (p->body).prevStatus = 0;
          (p->body).invincibleTime = 0;
          (p->s).flags &= ~COLLIDABLE;
          {
            const SolidRoutine* const* base = gSolidFnTable;
            const SolidRoutine* const* rowp;
            asm("" : "+r"(base));
            rowp = (const SolidRoutine* const*)(((u32)(p->s).id << 2) + (u32)base);
            *(u32*)((p->s).mode) = k3;
            (p->s).onUpdate = (void*)(**rowp)[ENTITY_DISAPPEAR];
          }
        }
      }
      break;
    }
  }
#else
  INCCODE("asm/solid/icebon_cabe8.inc");
#endif
}

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x0700, 0x1C00, 0x0800},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0400, 0x1C00, 0x1800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0200, 0x1400, 0x1400},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0200, 0x1400, 0x1400},
    },
};

const struct Rect Rect_0836fd58 = {PIXEL(0), -PIXEL(3), PIXEL(24), PIXEL(16)};

static const u8 sInitModes[2] = {0, 3};

static const motion_t sMotions[4] = {
    MOTION(SM017_ICEBON_ICE, 6),
    MOTION(SM017_ICEBON_ICE, 7),
    MOTION(SM017_ICEBON_ICE, 8),
    MOTION(SM017_ICEBON_ICE, 6),
};
