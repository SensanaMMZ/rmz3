#include "collision.h"
#include "cyberelf.h"
#include "global.h"

// Bee?

struct CyberElf11 {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 unk_b4;
  s32 unk_b8;
  u8 unk_bc[8];
};
static_assert(sizeof(struct CyberElf11) == sizeof(struct Elf));

struct Elf* FUN_080e5048(s32 a0, s32 a1, u8 mode) {
  struct CyberElf11* p = (struct CyberElf11*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 11);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    p->unk_b4 = a0;
    p->unk_b8 = a1;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
  }
  return (struct Elf*)p;
}

static const ElfFunc sInitializers[4];
void Elf11_Update(struct Elf* p);

void Elf11_Init(struct Elf* p) {
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  (p->s).palID = 1;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  (p->s).flags2 &= ~DYNAMIC;
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  (sInitializers[((p->s).work)[0]])(p);
  Elf11_Update(p);
}

static const ElfFunc sUpdates[4];

void Elf11_Update(struct Elf* p) {
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  UpdateMotionGraphic(&p->s);
  {
    u8 v = gPause;
    if (v == 0) {
      if (*((u8*)z + 0x232) != 0) {
        u8 f = ~DISPLAY & (p->s).flags;
        f = f & ~FLIPABLE;
        (p->s).flags = f;
        (p->body).status = v;
        (p->body).prevStatus = v;
        (p->body).invincibleTime = v;
        (p->s).flags &= ~COLLIDABLE;
        SET_ELF_ROUTINE(p, ENTITY_DISAPPEAR);
      } else {
        (sUpdates[(p->s).work[0]])(p);
      }
    }
  }
}

void Elf11_Die(struct Elf* p) {
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  (p->s).flags &= ~COLLIDABLE;
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/unk_11_p2.inc");

u8 GetArchimAtkBoost(void);
static const struct Collision sCollisions[15];

// 0x080e5608 -- parked (recompute basin): retail evaluates the parent
// xflip bit twice with the mask register kept (SET_PLAYER_XFLIP's double
// value eval, no cse across the spr store); agbcc either unifies the two
// evals (19 short) or overshoots with a hand-expanded reload (+4).
NON_MATCH void FUN_080e5608(struct Elf* p) {
#if MODERN
  struct Entity* q = *(struct Entity**)((u8*)p + 0xb8);
  SetMotion(&p->s, 1);
  {
    s32 one = 1;
    s32 v = (q->flags >> 4) & one;
    (p->s).spr.xflip = v;
    v = (q->flags >> 4) & one;
    ((p->s).spr).oam.xflip = v;
    if (v) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
  }
  UpdateMotionGraphic(&p->s);
  {
    u8 boost = GetArchimAtkBoost();
    s32 z = 0;
    (p->s).flags |= COLLIDABLE;
    InitBody(&p->body, &(&sCollisions[10])[boost], &(p->s).coord, 1);
    (p->body).parent = (struct CollidableEntity*)p;
    (p->body).fn = (void*)z;
    {
      s32 x = (q->coord).x;
      s32 y = (q->coord).y;
      (p->s).coord.x = x;
      (p->s).coord.y = y;
    }
    PlaySound(0x27);
  }
#else
  INCCODE("asm/cyberelf/unk_11_5608.inc");
#endif
}

INCASM("asm/cyberelf/unk_11_p2c.inc");

bool8 FUN_080e586c(struct Elf* p);
struct Elf* FUN_080e5048(s32 a0, s32 a1, u8 mode);

void FUN_080e5718(struct Elf* p) {
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  if (FUN_080e586c(p) || ((p->body).status & 4)) {
    SET_ELF_ROUTINE(p, ENTITY_DIE);
    Elf11_Die(p);
  } else if ((p->body).status & 0x1000) {
    PlaySound(0x2B);
    SET_ELF_ROUTINE(p, ENTITY_DIE);
    Elf11_Die(p);
  }
}

void FUN_080e5798(struct Elf* p) {
  struct Entity* q = *(struct Entity**)&p->buffer[0];
  u8 hit;
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  hit = FUN_080e586c(p);
  (p->s).work[2]--;
  if (hit == 1 || ((p->body).status & 0x1004) || (p->s).work[2] == 0) {
    FUN_080e5048((s32)q, (s32)p, 3);
    SET_ELF_ROUTINE(p, ENTITY_DIE);
    Elf11_Die(p);
  }
}

INCASM("asm/cyberelf/unk_11_p2b.inc");

static const ElfFunc sInitializers[4];
static const ElfFunc sUpdates[4];
static const struct Collision sCollisions[15];

void Elf11_Init(struct Elf* p);
void Elf11_Update(struct Elf* p);
void Elf11_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf11Routine = {
    [ENTITY_INIT] =      Elf11_Init,
    [ENTITY_UPDATE] =    Elf11_Update,
    [ENTITY_DIE] =       Elf11_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080e51b0(struct Elf* p);
void FUN_080e5300(struct Elf* p);
void FUN_080e54ac(struct Elf* p);
void FUN_080e5608(struct Elf* p);

// 0x08371df8
static const ElfFunc sInitializers[4] = {
    FUN_080e51b0,
    FUN_080e5300,
    FUN_080e54ac,
    FUN_080e5608,
};

// --------------------------------------------

void FUN_080e56a0(struct Elf* p);
void FUN_080e5718(struct Elf* p);
void FUN_080e5798(struct Elf* p);
void FUN_080e5818(struct Elf* p);

// 0x08371e08
static const ElfFunc sUpdates[4] = {
    FUN_080e56a0,
    FUN_080e5718,
    FUN_080e5798,
    FUN_080e5818,
};

// --------------------------------------------

// 0x08371e18
static const struct Collision sCollisions[15] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [3] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 4,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [5] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 5,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [7] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [8] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 6,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [9] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 3,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1600, 0x1600},
    },
    [11] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 4,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1600, 0x1600},
    },
    [12] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 5,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1600, 0x1600},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1600, 0x1600},
    },
    [14] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 7,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1600, 0x1600},
    },
};
