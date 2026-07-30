#include "collision.h"
#include "camera.h"
#include "cyberelf.h"
#include "metatile.h"
#include "stagerun.h"
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

u8 GetBeeAtkBoost(void);
static const struct Collision sCollisions[15];

void FUN_080e51b0(struct Elf* p) {
  register struct Entity* q asm("r4");
  struct Entity* z;
  q = *(struct Entity**)((u8*)p + 0xb4);
  z = *(struct Entity**)((u8*)p + 0xb8);
  SetMotion(&p->s, 0x200);
  {
    register s32 v asm("r1");
    register s32 one asm("r2");
    s32 v0 = q->flags >> 4;
    register u8* oa asm("r5");
    s32 sh4, ov, m11;
    one = 1;
    v0 &= one;
    (p->s).spr.xflip = v0;
    v = (q->flags >> 4) & one;
    oa = (u8*)&((p->s).spr).oam + 6;
    sh4 = v << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    *oa = m11 | sh4;
    if (v) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
  }
  if (q->mode[1] == 2) {
    register s32 mid asm("r1");
    register s32 mst asm("r0");
    mid = q->motionID << 8;
    mst = (q->motion).step;
    if ((mst | mid) == 0x500) {
      register u8* cp asm("r0");
      u8 ci;
      cp = (u8*)q + 0x71;
      asm("" : "+r"(cp));
      ci = *cp;
      asm("" : "+r"(ci));
      if ((s8)ci > 2) {
        register s32 v asm("r1");
        register s32 one asm("r2");
        s32 v0 = (p->s).flags >> 4;
        register u8* oa asm("r4");
        s32 sh4, ov, m11;
        one = 1;
        v0 ^= one;
        asm("" : "+r"(v0));
        v0 &= one;
        (p->s).spr.xflip = v0;
        v = (p->s).flags >> 4;
        v ^= one;
        asm("" : "+r"(v));
        v &= one;
        oa = (u8*)&((p->s).spr).oam + 6;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
        if (v) {
          (p->s).flags |= X_FLIP;
        } else {
          (p->s).flags &= ~X_FLIP;
        }
      }
    } else {
      register s32 v asm("r1");
      register s32 one asm("r2");
      s32 v0 = q->flags >> 4;
      register u8* oa asm("r4");
      s32 sh4, ov, m11;
      one = 1;
      v0 ^= one;
      asm("" : "+r"(v0));
      v0 &= one;
      (p->s).spr.xflip = v0;
      v = q->flags >> 4;
      v ^= one;
      asm("" : "+r"(v));
      v &= one;
      oa = (u8*)&((p->s).spr).oam + 6;
      sh4 = v << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh4;
      if (v) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
    }
  }
  UpdateMotionGraphic(&p->s);
  {
    u8 boost = GetBeeAtkBoost();
    s32 z5;
    struct Body* bd;
    {
      register u32 fl asm("r2");
      register s32 c4 asm("r1");
      fl = (p->s).flags;
      c4 = 4;
      z5 = 0;
      (p->s).flags = c4 | fl;
    }
    bd = &p->body;
    InitBody(bd, &sCollisions[boost * 2], &(p->s).coord, 1);
    bd->parent = (struct CollidableEntity*)p;
    bd->fn = (void*)z5;
    {
      s32 x = (z->coord).x;
      s32 y = (z->coord).y;
      (p->s).coord.x = x;
      (p->s).coord.y = y;
    }
    if ((p->s).flags & 0x10) {
      (p->s).d.x = 0x600;
    } else {
      (p->s).d.x = -0x600;
    }
  }
}

INCASM("asm/cyberelf/unk_11_p2a.inc");

u8 GetArchimAtkBoost(void);

void FUN_080e5608(struct Elf* p) {
  struct Entity* q = *(struct Entity**)((u8*)p + 0xb8);
  SetMotion(&p->s, 1);
  {
    register s32 v asm("r1");
    register s32 one asm("r2");
    s32 v0 = q->flags >> 4;
    register u8* oa asm("r4");
    s32 sh4, ov, m11;
    one = 1;
    v0 &= one;
    (p->s).spr.xflip = v0;
    v = (q->flags >> 4) & one;
    oa = (u8*)&((p->s).spr).oam + 6;
    sh4 = v << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    *oa = m11 | sh4;
    if (v) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
  }
  UpdateMotionGraphic(&p->s);
  {
    u8 boost = GetArchimAtkBoost();
    s32 z5;
    struct Body* bd;
    {
      register u32 fl asm("r2");
      register s32 c4 asm("r1");
      fl = (p->s).flags;
      c4 = 4;
      z5 = 0;
      (p->s).flags = c4 | fl;
    }
    bd = &p->body;
    InitBody(bd, &(&sCollisions[10])[boost], &(p->s).coord, 1);
    bd->parent = (struct CollidableEntity*)p;
    bd->fn = (void*)z5;
    {
      s32 x = (q->coord).x;
      s32 y = (q->coord).y;
      (p->s).coord.x = x;
      (p->s).coord.y = y;
    }
    PlaySound(0x27);
  }
}

bool8 FUN_080e586c(struct Elf* p);

void FUN_080e56a0(struct Elf* p) {
  (p->s).coord.x += (p->s).d.x;
  if (FUN_080e586c(p) || ((p->body).status & BODY_STATUS_B2)) {
    SET_ELF_ROUTINE(p, ENTITY_DIE);
    Elf11_Die(p);
  } else if ((p->body).status & BODY_STATUS_BLOCKED) {
    PlaySound(0x2B);
    SET_ELF_ROUTINE(p, ENTITY_DIE);
    Elf11_Die(p);
  }
}

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

void FUN_080e5818(struct Elf* p) {
  if ((p->body).status & BODY_STATUS_B2) {
    EXIT_BODY(p);
  }
  if ((p->s).motion.state == 3) {
    SET_ELF_ROUTINE(p, ENTITY_DIE);
    Elf11_Die(p);
  }
}


bool8 FUN_080e586c(struct Elf* p) {
  u16 a = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
  if ((u16)(a - 0x800E) <= 1) {
    a = 0;
  }
  if (a & 0xF) {
    return 1;
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x1000) {
    return 2;
  }
  return 0;
}

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
