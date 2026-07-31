#include "collision.h"
#include "global.h"
#include "zero.h"
#include "projectile.h"
#include "vfx.h"

static const ProjectileFunc sUpdates1[5];
static const ProjectileFunc sUpdates2[5];

void FUN_080a0888(s32 x, s32 y, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
    (p->s).work[3] = a3;
  }
}

void FUN_080a08e0(struct Entity* e, s32 x, s32 y, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a3;
    (p->s).unk_28 = e;
  }
}

struct DeathtanzProjectile {
  OBJECT_HDR;
  u8 work[4];    // 0xB4
  u8 unk_b8[4];  // 0xB8
  u8 unk_bc;     // 0xBC
};

void deathtanz_080a0934(struct Entity* e, s32 x, s32 y, u8 a3, u8 a4) {
  struct DeathtanzProjectile* p = (struct DeathtanzProjectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a3;
    (p->s).unk_28 = e;
    p->unk_bc = a4;
  }
}

#include "entity/macros.h"

void deathtanz_080a09a0(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    (p->s).unk_28 = parent;
  }
}

void deathtanz_080a09f4(struct Entity* e, s32 x, s32 y, u8 a3, u8 a4) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a3;
    (p->s).work[3] = a4;
    (p->s).unk_28 = e;
  }
}

static const u8 u8_ARRAY_0836b20c[5];
static const struct Collision sCollisions[10];
void Projectile14_Update(struct Projectile* p);

static void nop_080a0a5c(struct Body* body, struct Coord* c) {}

void Projectile14_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836b20c[(p->s).work[0]];
  {
    u8 f = (p->s).flags;
    f |= FLIPABLE;
    f |= DISPLAY;
    (p->s).flags = f;
  }
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_080a0a5c);
  {
    u8* src = (u8*)(p->s).unk_28;
    s32* dst = (s32*)&p->work[0];
    *dst = *(s32*)(src + 0xb4);
  }
  {
    s32* q = (s32*)((u8*)&p->body + 0x44);
    *q = (p->s).coord.y >> 8;
    *q = *q / 0xA0 * 5 << 13;
  }
  Projectile14_Update(p);
}

void Projectile14_Update(struct Projectile* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Projectile14_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(1, &(p->s).coord);
  PlaySound(0x2a);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void nop_080a0b6c(struct Projectile* p) {}

void FUN_080a0b70(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).unk_coord.y = (p->s).coord.y;
      SetDDP(&p->body, sCollisions);
      (p->s).d.x = 0x80;
      SetMotion(&p->s, 0x3701);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 lim;
      if ((p->s).work[2] != 0) {
        s32 nx = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + 0x6800;
        if (nx > lim) {
          asm volatile("");
          goto clampx1;
        }
      } else {
        s32 nx = (p->s).coord.x - (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + -0x6800;
        if (nx < lim) {
        clampx1:
          (p->s).coord.x = lim;
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 2: {
      u8 t2 = 0;
      if ((pZero2->s).coord.y > (p->s).coord.y) {
        t2 = 1;
      }
      (p->s).work[3] = t2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 lim;
      if ((p->s).work[3] != 0) {
        s32 ny = (p->s).coord.y + (p->s).d.x;
        (p->s).coord.y = ny;
        lim = *(s32*)((u8*)p + 0xb8) + 0x9000;
        if (ny > lim) {
          (p->s).coord.y = lim;
          asm volatile("");
          goto inc3;
        }
      } else {
        s32 ny = (p->s).coord.y - (p->s).d.x;
        (p->s).coord.y = ny;
        lim = *(s32*)((u8*)p + 0xb8) + -0x9000;
        if (ny < lim) {
          (p->s).coord.y = lim;
        inc3:
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 4: {
      u32 v = (RNG_0202f388 * 0x343FD + 0x269EC3) << 1;
      RNG_0202f388 = v >> 1;
      (p->s).d.x = ((v >> 0x11) & 1) * (p->s).d.x;
      (p->s).work[2] ^= 1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5: {
      s32 lim;
      if ((p->s).work[2] != 0) {
        s32 nx = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + 0x5800;
        if (nx <= lim) {
          break;
        }
        goto clampx5;
      } else {
        s32 nx = (p->s).coord.x - (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + -0x5800;
        if (nx < lim) {
        clampx5:
          (p->s).coord.x = lim;
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 6:
      (p->s).work[3] ^= 1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 7:
      if ((p->s).work[3] != 0) {
        s32 ny = (p->s).coord.y + (p->s).d.x;
        (p->s).coord.y = ny;
        if (ny <= (p->s).unk_coord.y) {
          break;
        }
        goto hitset;
      } else {
        s32 ny = (p->s).coord.y - (p->s).d.x;
        (p->s).coord.y = ny;
        if (ny < (p->s).unk_coord.y) {
        hitset:
          (p->s).mode[2]++;
          *((u8*)q + 0xbe) = 1;
        }
      }
      break;
    case 8:
      (p->s).work[2] = 2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 9: {
      s32 t = (p->s).work[2] - 1;
      u8 t2;
      (p->s).work[2] = t;
      t2 = t;
      if (t2 == 0) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
      break;
    }
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 d = (p->s).d.x + 0x30;
    (p->s).d.x = d;
    if (d > 0x800) {
      (p->s).d.x = 0x800;
    }
  }
  if (q->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/projectile/unk_14_p2.inc");

void Projectile14_Init(struct Projectile* p);
void Projectile14_Update(struct Projectile* p);
void Projectile14_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile14Routine = {
    [ENTITY_INIT] =      Projectile14_Init,
    [ENTITY_UPDATE] =    Projectile14_Update,
    [ENTITY_DIE] =       Projectile14_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080a0b6c(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates1[5] = {
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
};
// clang-format on

// --------------------------------------------

void FUN_080a0b70(struct Projectile* p);
void FUN_080a0dc0(struct Projectile* p);
void FUN_080a0fa8(struct Projectile* p);
void FUN_080a1280(struct Projectile* p);
void FUN_080a133c(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates2[5] = {
    FUN_080a0b70,
    FUN_080a0dc0,
    FUN_080a0fa8,
    FUN_080a1280,
    FUN_080a133c,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[10] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(40), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(50), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(26), PIXEL(50)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(2), PIXEL(40), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(20), PIXEL(19), PIXEL(8), PIXEL(51)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(60)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(57), -PIXEL(24), PIXEL(36), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(35), -PIXEL(11), PIXEL(37), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(57), -PIXEL(39), PIXEL(36), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(35), -PIXEL(53), PIXEL(37), PIXEL(13)},
    },
};

static const u8 u8_ARRAY_0836b20c[5] = {0, 1, 2, 3, 4};
static const u8 u8_ARRAY_0836b211[2] = {6, 8};
