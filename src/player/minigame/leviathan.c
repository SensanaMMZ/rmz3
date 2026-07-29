#include "collision.h"
#include "entity.h"
#include "global.h"
#include "minigame.h"
#include "zero.h"

extern const ZeroFunc sLeviathanUpdates1[3];
extern const ZeroFunc sLeviathanUpdates2[3];

static const struct Collision sCollisions[3];
static const u8 sInitModes[4];

static void Leviathan_Init(struct Zero* z);
void Leviathan_Update(struct Zero* z);
void Leviathan_Die(struct Zero* z);

// clang-format off
const ZeroRoutine gLeviathanRoutine = {
  [ENTITY_INIT] =       Leviathan_Init,
  [ENTITY_UPDATE] =     Leviathan_Update,
  [ENTITY_DIE]  =       Leviathan_Die,
  [ENTITY_DISAPPEAR] =  RemovePlayer,
  [ENTITY_EXIT] =       (ZeroFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_08035e48(struct Entity* p) {
  if ((p->d).x >= 1) {
    (p->d).x -= 4;
    if ((p->d).x < 0) {
      return TRUE;
    }
  } else {
    (p->d).x += 4;
    if ((p->d).x > 0) {
      return TRUE;
    }
  }
  return FALSE;
}

void FUN_08035e6c(struct Zero* p) {
  s32 dx, x, y;
  x = (p->s).unk_coord.x;
  y = (p->s).unk_coord.y;
  if (x > y) {
    dx = (y - x) * 12;
    if (dx < 0) {
      dx += 0xFF;
    }
    (p->s).unk_coord.x += (dx >> 8);
    if ((p->s).unk_coord.x < y) {
      (p->s).unk_coord.x = y;
    }
  }
}

struct Zero* CreatePlayerLeviathan(void* p, s32 x, s32 y) {
  struct Zero* z = AllocPlayer();
  if (z != NULL) {
    (z->s).taskCol = 16;
    INIT_PLAYER_ROUTINE(z, 5);
    (z->s).work[0] = 0;
    (z->s).coord.x = x;
    (z->s).coord.y = y;
    (z->s).unk_28 = p;
  }
  return z;
}

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) { return; }

static void Leviathan_Init(struct Zero* z) {
  SET_PLAYER_ROUTINE(z, ENTITY_UPDATE);
  (z->s).mode[1] = sInitModes[(z->s).work[0]];

  (z->s).flags |= FLIPABLE;
  (z->s).flags |= DISPLAY;
  InitNonAffineMotion(&z->s);
  ResetDynamicMotion(&z->s);
  (z->s).spr.xflip = TRUE;
  (z->s).spr.oam.xflip = TRUE;
  (z->s).flags |= X_FLIP;
  INIT_BODY(z, &sCollisions[0], 6, onCollision);
  (z->mg).leviathan.x = (z->s).coord.x;
  (z->s).unk_coord.y = (z->s).coord.y;
  (z->s).work[3] = 0;
  (z->s).d.x = 0;
  (z->s).d.y = 0;
  Leviathan_Update(z);
}

void Leviathan_Update(struct Zero* z) {
  struct MinigameState* s = (struct MinigameState*)(z->s).unk_28;
  if (s->unk_30[1] == 0) {
    (sLeviathanUpdates1[(z->s).mode[1]])(z);
    (sLeviathanUpdates2[(z->s).mode[1]])(z);
  }

  {
    s32 min_x, max_x;
    min_x = (z->mg).leviathan.x - PIXEL(108);
    if ((z->s).coord.x <= min_x) {
      (z->s).coord.x = min_x, (z->s).d.x = 0;
    }
    max_x = (z->mg).leviathan.x + PIXEL(108);
    if ((z->s).coord.x >= max_x) {
      (z->s).coord.x = max_x, (z->s).d.x = 0;
    }
  }
}

void Leviathan_Die(struct Zero* z) {
  SET_PLAYER_ROUTINE(z, ENTITY_EXIT);
}

void leviathanMode0Pre(struct Zero* p) {
  struct Entity* e = (p->s).unk_28;
  if (*(u16*)((u8*)e + 0x10) & 0x30) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
  if (*(u16*)((u8*)e + 0x12) & 2) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

void leviathanMode1Pre(struct Zero* p) {
  struct Entity* e = (p->s).unk_28;
  if (*(u16*)((u8*)e + 0x12) & 2) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

void nop_08036044(struct Zero* z) {}

INCASM("asm/player/leviathan_p2.inc");

void leviathanMode1(struct Zero* p) {
  struct Entity* e = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, 0xBD02);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      register s32 mv asm("r5");
      FUN_08035e6c(p);
      (p->s).coord.y = (p->s).unk_coord.x;
      mv = 0;
      {
      register u16 in asm("r1");
      in = *(u16*)((u8*)e + 0x10);
      if (in & 0x20) {
        (p->s).d.x -= 0x10;
        if ((p->s).d.x < -0x300) {
          (p->s).d.x = -0x300;
        }
        {
          u8* a;
          u8 b;
          u8* xa;
          register s32 z asm("r0");
          mv = 1;
          xa = (u8*)p + 0x4c;
          z = 0;
          asm("" : "+r"(z));
          *xa = z;
          a = (u8*)p + 0x4a;
          b = *a;
          z -= 0x11;
          z &= b;
          *a = z;
          (p->s).flags &= 0xEF;
        }
      } else if (in & 0x10) {
        (p->s).d.x += 0x10;
        if ((p->s).d.x > 0x300) {
          (p->s).d.x = 0x300;
        }
        mv = 1;
        ((p->s).spr).xflip = mv;
        {
          register s32 v0 asm("r0");
          register u32 ten asm("r1");
          u8* a = (u8*)p + 0x4a;
          v0 = *a;
          ten = 0x10;
          v0 |= ten;
          *a = v0;
          {
            register u8 fl asm("r0");
            fl = (p->s).flags;
            ten |= fl;
            (p->s).flags = ten;
          }
        }
      }
      }
      if (((FUN_08035e48(&p->s) << 24) != 0) && mv == 0) {
        (p->s).d.x = mv;
        (p->s).mode[2]++;
      }
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetMotion(&p->s, 0xBD01);
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      u32 m;
      FUN_08035e6c(p);
      (p->s).coord.y = (p->s).unk_coord.x;
      UpdateMotionGraphic(&p->s);
      {
        u16 iv = *(u16*)((u8*)e + 0x10);
        m = 0x30;
        m &= iv;
      }
      if (m != 0) {
        (p->s).mode[2] = 0;
      } else if ((p->s).motion.state == 3) {
        (p->s).mode[1] = m;
        (p->s).mode[2] = m;
      }
      break;
    }
  }
}

INCASM("asm/player/leviathan_p2_b.inc");


// --------------------------------------------

void leviathanMode0Pre(struct Zero* z);
void leviathanMode1Pre(struct Zero* z);
void nop_08036044(struct Zero* z);

const ZeroFunc sLeviathanUpdates1[3] = {
    leviathanMode0Pre,
    leviathanMode1Pre,
    nop_08036044,
};

void leviathanMode0(struct Zero* z);
void leviathanMode1(struct Zero* z);
void leviathanMode2(struct Zero* z);

const ZeroFunc sLeviathanUpdates2[3] = {
    leviathanMode0,
    leviathanMode1,
    leviathanMode2,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : 0,
      damage : 1,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0A00, 0x1600, 0x0C00, 0x0900},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : 0,
      damage : 1,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {-0x0A00, 0x1F00, 0x0800, 0x1B00},
    },
};

static const u8 sInitModes[4] = {0, 0, 0, 0};
