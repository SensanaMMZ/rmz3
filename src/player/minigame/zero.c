#include "collision.h"
#include "entity.h"
#include "global.h"
#include "input.h"
#include "minigame.h"
#include "physics.h"
#include "weapon.h"
#include "zero.h"

static const struct Collision sCollisions[];

static void ZeroMini_Init(struct Zero* z);
static void ZeroMini_Update(struct Zero* z);
static void ZeroMini_Die(struct Zero* z);

// clang-format off
const ZeroRoutine gZeroMiniRoutine = {
  [ENTITY_INIT] =       ZeroMini_Init,
  [ENTITY_UPDATE] =     ZeroMini_Update,
  [ENTITY_DIE]  =       ZeroMini_Die,
  [ENTITY_DISAPPEAR] =  RemovePlayer,
  [ENTITY_EXIT] =       (ZeroFunc)DeleteEntity,
};
// clang-format on

struct Zero* CreateZeroMini(void* p, struct Coord* c, u8 n) {
  struct Zero* z = AllocPlayer();
  if (z != NULL) {
    (z->s).taskCol = 16;
    INIT_PLAYER_ROUTINE(z, 6);
    (z->s).coord = *c;
    (z->s).work[0] = n;
    (z->s).unk_28 = p;
  }
  return z;
}

// --------------------------------------------

static void ZeroMini_Init(struct Zero* z) {
  struct Coord* c;
  InitNonAffineMotion(&z->s);
  ResetDynamicMotion(&z->s);
  (z->s).flags |= DISPLAY;
  (z->s).flags |= FLIPABLE;
  {
    bool8 xflip = FALSE;
    (z->s).spr.xflip = xflip & 1;
    (z->s).spr.oam.xflip = xflip;
    if (xflip) {
      (z->s).flags |= X_FLIP;
    } else {
      (z->s).flags &= ~X_FLIP;
    }
  }
  INIT_BODY(z, &sCollisions[0], 32, NULL);
  (z->s).coord.y = FUN_0800a05c((z->s).coord.x, (z->s).coord.y);
  SET_PLAYER_ROUTINE(z, ENTITY_UPDATE);
  (z->s).mode[1] = 0;
  (z->s).mode[2] = 0;
  (z->s).mode[3] = 0;
  (z->mg).zero.unk_286 = 0;
  LoadZeroPalette((struct Entity*)z, BODY_CHIP_NONE);
  SetWeaponElement(WEAPON_BUSTER, 0);
  SetWeaponElement(WEAPON_SABER, 0);
  (z->mg).zero.unk_27c = 0;
  (z->mg).zero.unk_27d = 0;
  (z->s).work[3] = 0;
  (z->mg).zero.unk_284 = 0;
  (z->mg).zero.unk_285 = 0;

  {
    struct Coord* c;
    c = &(z->s).d;
    c->x = c->y = 0;
    c = &(z->s).unk_coord;
    c->x = c->y = 0;
  }

  ZeroMini_Update(z);
}

// --------------------------------------------

static bool32 nop_0803658c(struct Zero* z);
bool8 FUN_080365d8(struct Zero* z);
bool8 FUN_08036848(struct Zero* z);
bool8 FUN_08036904(struct Zero* z);
static bool32 FUN_08036b94(struct Zero* z);

static void zeroMini_08036590(struct Zero* z);
void FUN_080366fc(struct Zero* z);
void FUN_08036870(struct Zero* z);
void recoil_minigame_08036938(struct Zero* z);
static void zeroMini_08036b98(struct Zero* z);

#define STATE ((struct MinigameState*)(z->s).unk_28)

static void ZeroMini_Update(struct Zero* z) {
  // clang-format off
  static const ZeroFunc sUpdates1[5] = {
      (ZeroFunc)nop_0803658c,
      (ZeroFunc)FUN_080365d8,
      (ZeroFunc)FUN_08036848,
      (ZeroFunc)FUN_08036904,
      (ZeroFunc)FUN_08036b94,
  };
  // clang-format on

  // clang-format off
  static const ZeroFunc sUpdates2[5] = {
      zeroMini_08036590,
      FUN_080366fc,
      FUN_08036870,
      recoil_minigame_08036938,
      zeroMini_08036b98,
  };
  // clang-format on

  struct MinigameState* s = (struct MinigameState*)(z->s).unk_28;
  if (s->unk_04 != 2) {
    (sUpdates1[(z->s).mode[1]])(z);
    (sUpdates2[(z->s).mode[1]])(z);
  } else if (s->unk_0c == 0) {
    (sUpdates1[(z->s).mode[1]])(z);
    (sUpdates2[(z->s).mode[1]])(z);
  }

  if ((z->body).status & BODY_STATUS_WHITE) {
    PlaySound(SE_ZERO_STUN);
    if (((struct MinigameState*)(z->s).unk_28)->unk_0c != 0) {
      PlaySound(SE_NOT_ALLOWED);
      ((struct MinigameState*)(z->s).unk_28)->unk_0c--;
      if (((struct MinigameState*)(z->s).unk_28)->unk_0c == 0) {
        EXIT_BODY(z);
        (z->s).mode[1] = 4;
        (z->s).mode[2] = 0;
      }
    }
  }
  if ((z->body).invincibleTime != 0) {
    if (((z->mg).zero.unk_286 == 0) || (--(z->mg).zero.unk_286 == 0)) {
      (z->body).invincibleTime &= 0x7F;
    }
  }
}

// --------------------------------------------

static void ZeroMini_Die(struct Zero* z) {
  (z->s).flags &= ~DISPLAY;
  (z->s).flags &= ~FLIPABLE;
  EXIT_BODY(z);
  SET_PLAYER_ROUTINE(z, ENTITY_DISAPPEAR);
}

// --------------------------------------------

// 0x0803658c
static bool32 nop_0803658c(struct Zero* z) { return TRUE; }

// 0x08036590
static void zeroMini_08036590(struct Zero* z) {
  switch ((z->s).mode[2]) {
    case 0: {
      SetMotion(&z->s, MOTION(DM000_ZERO_NEUTRAL, 0));
      (z->s).work[2] = 60;
      (z->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(&z->s);
      if (((z->s).work[2] == 0) || (--(z->s).work[2] == 0)) {
        (z->s).mode[1] = 1;
        (z->s).mode[2] = 0;
      }
      break;
    }
  }
}

// --------------------------------------------

// Minigame-zero jump/attack chooser off the D-pad at bite windows. Logic
// verified; parked on an arm-orchestration tie: retail keeps the pooled
// 0x287/0x27D offsets alive in r4/r5 across all six arms and shares one strb
// per trio - reproducing the arm stores shifts the offset registers or the
// u16 truncation pairs (9 shapes tried).
#if MODERN
NON_MATCH bool8 FUN_080365d8(struct Zero* z) {
  if (*(s16*)((u8*)(z->s).unk_28 + 4) == 1) {
    if (gJoypad[0].pressed & B_BUTTON) {
      u32 h = gJoypad[0].input;
      if (h & DPAD_UP) {
        *((u8*)z + 0x287) = 2;
      } else if ((u16)(h & DPAD_DOWN)) {
        *((u8*)z + 0x287) = 4;
      } else {
        *((u8*)z + 0x287) = 0;
      }
      (z->s).mode[1] = 3;
      (z->s).mode[2] = 0;
    }
    {
      u8* f7d = (u8*)z + 0x27D;
      if (*f7d == 1) {
        u32 h = gJoypad[0].input;
        if ((u16)(h & B_BUTTON) != 0) {
          goto ret;
        }
        *((u8*)z + 0x27C) = 0;
        *f7d = 0;
        if (h & DPAD_UP) {
          *((u8*)z + 0x287) = 7;
        } else if (h & DPAD_DOWN) {
          *((u8*)z + 0x287) = 8;
        } else {
          *((u8*)z + 0x287) = 6;
        }
        goto setmode;
      } else {
        u8* f7c = (u8*)z + 0x27C;
        if (*f7c > 0xA) {
          u32 h = gJoypad[0].input;
          if ((u16)(h & B_BUTTON) != 0) {
            goto ret;
          }
          *f7c = 0;
          *f7d = 0;
          if (h & DPAD_UP) {
            *((u8*)z + 0x287) = 2;
          } else if ((u16)(h & DPAD_DOWN)) {
            *((u8*)z + 0x287) = 4;
          } else {
            *((u8*)z + 0x287) = 0;
          }
        setmode:
          (z->s).mode[1] = 3;
          (z->s).mode[2] = 0;
        }
      }
    }
  }
ret:
  return TRUE;
}
#else
NON_MATCH bool8 FUN_080365d8(struct Zero* z) {
  INCCODE("asm/player/zero_minigame_65d8.inc");
}
#endif

struct VFX* FUN_080c825c(struct Entity* e, struct Coord* c, u8 n);

// 0x080366FC
void FUN_080366fc(struct Zero* z) {
  u8 m;
  m = (z->s).mode[2];
  switch (m) {
    case 0: {
      register s32 off asm("r1");
      register u8* pp asm("r0");
      off = 0x9f << 2;
      pp = (u8*)z + off;
      *pp = m;
      asm volatile("add %0, #0x1" : "+l"(off));
      pp = (u8*)z + off;
      *pp = m;
      SetMotion(&z->s, 0);
      SetDDP(&z->body, sCollisions);
      *(u16*)((u8*)z + 0x288) = m;
      (z->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      register u16* cnt asm("r3");
      s32 zero;
      register s32 one asm("r6");
      cnt = (u16*)((u8*)z + 0x288);
      {
        u16 v = *cnt + 1;
        zero = 0;
        asm("" : "+r"(zero));
        *cnt = v;
      }
      one = *(s16*)((u8*)(z->s).unk_28 + 4);
      if (one != 1) {
        goto tail;
      }
      {
        register u32 h asm("r4");
        {
          register struct KeyState* jp asm("r4");
          register u32 h1 asm("r1");
          jp = gJoypad;
          h1 = jp[0].input;
          if (h1 & 0x20) {
            u8* q;
            register s32 k asm("r0");
            register s32 v asm("r1");
            *((u8*)z + 0x4c) = zero;
            q = (u8*)z + 0x4a;
            v = *q;
            k = 0x11;
            k = -k;
            asm("" : "+r"(k));
            k &= v;
            *q = k;
            v = (z->s).flags;
            k = 0xEF;
            k &= v;
            (z->s).flags = k;
          }
          h = jp[0].input;
        }
        if (h & 0x10) {
          u8* q2;
          register s32 k2 asm("r1");
          register s32 v2 asm("r0");
          *((u8*)z + 0x4c) = one;
          q2 = (u8*)z + 0x4a;
          v2 = *q2;
          k2 = 0x10;
          v2 |= k2;
          *q2 = v2;
          v2 = (z->s).flags;
          k2 |= v2;
          (z->s).flags = k2;
        }
        if (h & 2) {
          if (*((u8*)z + 0x27C) <= 0x27) {
            if ((u16)(*cnt % 0x14) == 0) {
              PlaySound(0x17);
            }
          } else {
            if ((u16)(*cnt % 0x14) == 0) {
              PlaySound(0x18);
            }
          }
          {
            register u8* g asm("r6");
            g = (u8*)z + 0x27C;
            if (*g == 0xa) {
              register struct Coord* c2 asm("r4");
              c2 = &(z->s).coord;
              FUN_080c825c(&z->s, c2, 0);
              FUN_080c825c(&z->s, c2, 1);
            }
            {
              u8 gv = *g;
              if (gv <= 0xc7) {
                *g = gv + 1;
              }
            }
          }
        } else {
          register s32 off2 asm("r1");
          register u8* pp2 asm("r0");
          off2 = 0x9f << 2;
          pp2 = (u8*)z + off2;
          *pp2 = zero;
          asm volatile("add %0, #0x1" : "+l"(off2));
          pp2 = (u8*)z + off2;
          *pp2 = zero;
        }
      }
    tail:
      if (*((u8*)z + 0x27C) > 0x28) {
        *((u8*)z + 0x27D) = 1;
      }
      UpdateMotionGraphic(&z->s);
      break;
    }
  }
}


bool8 FUN_08036848(struct Zero* z) {
  if ((z->s).mode[2] > 1 && (gJoypad[0].pressed & B_BUTTON)) {
    (z->s).mode[1] = 3;
    (z->s).mode[2] = 0;
  }
  return TRUE;
}

// 0x08036870
void FUN_08036870(struct Zero* z) {
  switch ((z->s).mode[2]) {
    case 0:
      SetMotion(&z->s, 0);
      (z->s).work[2] = 10;
      (z->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&z->s);
      if ((z->s).motion.state == 3) {
        goto reset;
      }
      if ((z->s).work[2] == 0) {
        goto advance;
      }
      if ((u8)--(z->s).work[2] != 0) {
        break;
      }
      goto advance;
    case 2:
      UpdateMotionGraphic(&z->s);
      if ((z->s).motion.state != 3) {
        break;
      }
    reset:
      (z->s).work[2] = 10;
    advance:
      (z->s).mode[2]++;
      break;
    case 3:
      UpdateMotionGraphic(&z->s);
      if ((z->s).work[2] != 0) {
        if ((u8)--(z->s).work[2] != 0) {
          break;
        }
      }
      (z->s).mode[1] = 1, (z->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_08036904(struct Zero* z) {
  if ((z->s).mode[2] == 1 && *(s8*)((u8*)z + 0x71) > 2 && (gJoypad[0].pressed & B_BUTTON) &&
      (z->s).mode[3] == 0) {
    (z->s).mode[3] = (z->s).mode[2];
  }
  return TRUE;
}

INCASM("asm/player/zero_minigame_p2_p2.inc");

// 0x08036b94
static bool32 FUN_08036b94(struct Zero* z) { return TRUE; }

// 0x08036b98
static void zeroMini_08036b98(struct Zero* z) {
  switch ((z->s).mode[2]) {
    case 0: {
      SetMotion(&z->s, MOTION(DM001_ZERO_DYING, 0));
      (z->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 dy;
      (z->s).d.y += PIXEL(1) / 4;
      if (PIXEL(7) < (z->s).d.y) {
        (z->s).d.y = PIXEL(7);
      }

      (z->s).coord.y += (z->s).d.y;
      dy = PushoutToUp2((z->s).coord.x, (z->s).coord.y);
      if (dy != 0) {
        (z->s).d.y = 0;
        (z->s).coord.y += dy;
      }
      UpdateMotionGraphic(&z->s);
      break;
    }
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

// 0x0835eca0
static const struct Collision sCollisions[7] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(20), PIXEL(26)},
    },

    [1] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 32,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(23), -PIXEL(56), PIXEL(26), PIXEL(56)},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 32,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(7), -PIXEL(76), PIXEL(36), PIXEL(23)},
    },
    [3] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(36), PIXEL(28), PIXEL(50)},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 32,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(23), -PIXEL(56), PIXEL(26), PIXEL(56)},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 32,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(7), -PIXEL(76), PIXEL(36), PIXEL(23)},
    },
    [6] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(36), PIXEL(28), PIXEL(50)},
    },
};

// --------------------------------------------

// clang-format off
// 0x0835ed48
const motion_t sZeroMiniMotions[10] = {
  MOTION(0x1E, 0x00),
  MOTION(0x1E, 0x01),
  MOTION(0x1F, 0x00),
  MOTION(0x1F, 0x01),
  MOTION(0x20, 0x00),
  MOTION(0x20, 0x01),
  MOTION(0x37, 0x00),
  MOTION(0x38, 0x00),
  MOTION(0x39, 0x01),
  MOTION(0x00, 0x00),
};
// clang-format on
