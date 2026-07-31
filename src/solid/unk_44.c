#include "collision.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"
#include "stagerun.h"
#include "zero.h"

static const struct Collision sCollisions[2];

static void Solid44_Init(struct Solid* p);
static void Solid44_Update(struct Solid* p);
void Solid44_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid44Routine = {
    [ENTITY_INIT] =      Solid44_Init,
    [ENTITY_UPDATE] =    Solid44_Update,
    [ENTITY_DIE] =       Solid44_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid44_Init(struct Solid* p) {
  metatile_attr_t attr;

  if ((p->s).work[0] == 0) {
    attr = GetMetatileAttr((p->s).coord.x, (p->s).coord.y);
    if (attr == 0) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      EXIT_BODY(p);
      SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    } else {
      INIT_BODY(p, &sCollisions[0], 0, NULL);
      (p->s).coord.x += PIXEL(8);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
      Solid44_Update(p);
    }
  } else {
    (p->s).flags |= FLIPABLE;
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Solid44_Die(p);
  }
}

static void Solid44_Update(struct Solid* p) {
  // clang-format off
  if (
    (((p->body).status & BODY_STATUS_B2) && (BODY(pZero2) != BODY_CHIP_LIGHT)) || 
    (GetMetatileAttr((p->s).coord.x + PIXEL(17), (p->s).coord.y + 1) == 0) || 
    (GetMetatileAttr((p->s).coord.x - PIXEL(17), (p->s).coord.y + 1) == 0)
  ) {
    // clang-format on
    struct Solid* p2 = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
    if (p2 != NULL) {
      (p2->s).taskCol = 30;
      INIT_SOLID_ROUTINE(p2, SOLID_UNK_044);
      (p2->s).tileNum = 0;
      (p2->s).palID = 0;
      (p2->s).flags2 |= WHITE_PAINTABLE;
      (p2->s).invincibleID = (p2->s).uniqueID;
      (p2->s).work[0] = 1;
      (p2->s).work[1] = 0;
      (p2->s).coord.x = (p->s).coord.x + PIXEL(8);
      (p2->s).coord.y = (p->s).coord.y;
    }
    (p->s).coord.x -= PIXEL(8);
    EXIT_BODY(p);
    (p->s).flags |= FLIPABLE;
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Solid44_Die(p);
  }
}

struct Entity* FUN_080b2c28(motion_t m, struct Coord* c, bool8 xflip, bool8 yflip);
void FUN_080133e8(struct Coord* c);

// RNG-chain basin: the four chained draws match through the seed stores but
// the c.x volatile reload / -0x400 add and the b1 mask refuse retail's
// interleave (each reorder lever rotates the s3/b1 scratch pair), and the
// barrier'd rng copy sits two insns early. Everything else stream-matches.
NON_MATCH void Solid44_Die(struct Solid* p) {
#if MODERN
  struct Coord c;
  u8 m1 = (p->s).mode[1];
  switch (m1) {
    case 0: {
      u8 w1;
      (p->s).d.y = m1;
      (p->s).d.x = m1;
      w1 = (p->s).work[1];
      if (w1 != 0) {
        u32 v;
        (p->s).flags |= DISPLAY;
        InitNonAffineMotion(&p->s);
        *((u8*)p + 0x49) |= 0xc;
        v = (RNG_0202f388 * 0x343FD + 0x269EC3) << 1;
        RNG_0202f388 = v >> 1;
        SetMotion(&p->s, (((v >> 0x11) & 1) + 1) | 0x9D00);
        (p->s).mode[1] = 2;
        break;
      }
      (p->s).work[2] = w1;
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t = (p->s).work[2] + 1;
      (p->s).work[2] = t;
      if ((t & 7) == 0) {
        u32 v1 = (0x343FD * RNG_0202f388 + 0x269EC3) << 1;
        u32* rng;
        u32 v2, s2, v3, s3, v4;
        asm("" : "+r"(v1));
        RNG_0202f388 = v1 >> 1;
        c.y = (p->s).coord.y + ((v1 << 3) >> 0x14);
        rng = ({ u32* r_ = &RNG_0202f388; asm("" : "+r"(r_)); r_; });
        if (t & 8) {
          c.x = (p->s).coord.x + 0x900;
        } else {
          c.x = (p->s).coord.x + -0x900;
        }
        {
          register u32 M3 asm("r3");
          register u32 A3 asm("r4");
          register u32 one asm("r5");
          u32 b1, b2;
          M3 = 0x343FD;
          A3 = 0x269EC3;
          v2 = (*rng * M3 + A3) << 1;
          asm("" : "+r"(v2));
          s2 = v2 >> 1;
          c.x = *(volatile s32*)&c.x + -0x400 + ((v2 << 4) >> 0x15);
          v3 = (s2 * M3 + A3) << 1;
          asm("" : "+r"(v3));
          s3 = v3 >> 1;
          one = 1;
          b1 = (v3 >> 0x11) & one;
          asm volatile("" :: "r"(b1));
          v4 = (s3 * M3 + A3) << 1;
          asm("" : "+r"(v4));
          *rng = v4 >> 1;
          b2 = (v4 >> 0x11) & one;
          FUN_080b2c28(0x9D03, &c, b1, b2);
        }
        if (gSolidHeaderPtr->remaining > 8) {
          struct Solid* n = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
          if (n != NULL) {
            (n->s).taskCol = 30;
            INIT_SOLID_ROUTINE(n, SOLID_UNK_044);
            (n->s).tileNum = 0;
            (n->s).palID = 0;
            (n->s).flags2 |= WHITE_PAINTABLE;
            (n->s).invincibleID = (n->s).uniqueID;
            (n->s).work[0] = 1;
            (n->s).work[1] = 1;
            (n->s).coord.x = c.x;
            c.y = (p->s).coord.y;
            (n->s).coord.y = c.y;
          }
        }
      }
      if ((p->s).work[2] > 0x3B) {
        if ((p->s).work[0] == 0) {
          FUN_080133e8(&(p->s).coord);
        }
        (p->s).flags |= DISPLAY;
        InitNonAffineMotion(&p->s);
        SetMotion(&p->s, 0x9D00);
        (p->s).mode[1]++;
        FALLTHROUGH;
      } else {
        break;
      }
    }
    case 2: {
      s32 dyv;
      UpdateMotionGraphic(&p->s);
      dyv = (p->s).d.y;
      if (dyv <= 0x6FF) {
        (p->s).d.y = dyv + 0x20;
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).unk_coord.y = (p->s).coord.y;
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0xA00) {
        (p->s).flags &= ~DISPLAY;
        EXIT_BODY(p);
        (p->s).flags2 &= ~8;
        SET_SOLID_ROUTINE(p, ENTITY_EXIT);
      }
      break;
    }
  }
#else
  INCCODE("asm/solid/unk_44_die.inc");
#endif
}
static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(34), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};
