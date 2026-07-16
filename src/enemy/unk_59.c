#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "zero.h"

static const EnemyFunc sDeads[4];

void FUN_080c4c2c(s32 x, s32 y, s32 amplitude, u8 theta);

void FUN_08091280(struct Entity* p) {
  s32 x, y, amplitude;
  u8 theta;
  RNG_0202f388 = LCG(RNG_0202f388);
  x = (p->coord).x + PIXEL(((RNG_0202f388 >> 16) & 0x1F) - 16);
  RNG_0202f388 = LCG(RNG_0202f388);
  y = (p->coord).y - PIXEL((-(RNG_0202f388 >> 16)) % 48);
  amplitude = 0x100;
  RNG_0202f388 = LCG(RNG_0202f388);
  theta = 0x80 | ((RNG_0202f388 >> 16) & 0x7F);
  FUN_080c4c2c(x, y, amplitude, theta);
}

void FUN_0809130c(struct Entity* e, u8 idx) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_59);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    (p->coord).x = (e->coord).x, (p->coord).y = (e->coord).y;
    if (idx < 4) {
      s32 x = (idx - 2) * PIXEL(48) + PIXEL(24);
      (p->unk_coord).x = (e->coord).x + x;
    }
    if (idx > 4) {
      s32 x = (idx - 7) * PIXEL(48) + PIXEL(24);
      (p->coord).x = (e->coord).x + x;
    }
    p->unk_28 = e;
    InitNonAffineMotion(p);
    ResetDynamicMotion(p);
    (p->spr).sprites = (*(void**)&e->kind);
    {
      u8 palID = *((u8*)e + 0x15);
      (p->spr).oam.paletteNum = palID >> 4;
    }
    p->work[0] = idx;
  }
}

INCASM("asm/enemy/unk_59_pre_pre_p1b.inc");

void FUN_0809142c(struct Entity* e, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_59);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y - PIXEL(10);
    (p->s).work[0] = 12;
    (p->s).work[2] = a2;
    (p->s).unk_28 = e;
  }
}

INCASM("asm/enemy/unk_59_pre_pre_p2.inc");

void Enemy59_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_08091790(struct Body* body) {
  struct Enemy* atk = (struct Enemy*)(body->enemy->parent);
  struct Enemy* self = (struct Enemy*)(body->parent);
  if ((self->s).work[0] == 0xc) {
    if ((body->hitboxFlags & 8) &&
        (s8)(atk->s).kind == 2 &&
        (atk->s).mode[1] == 1 &&
        (u8)((atk->s).mode[2] - 1) <= 1 &&
        (atk->s).id == 0x15 &&
        ((*(u32*)&(self->s).mode[0]) & 0xffff00) == 0x30800) {
      *(s32*)((u8*)self + 0xb4) = (atk->s).coord.x - (self->s).coord.x;
      (self->s).mode[1] = 9;
      (self->s).mode[2] = 0;
    }
  } else {
    *(s32*)((u8*)self + 0xb4) = pZero2->s.coord.x - (self->s).coord.x;
  }
}

void FUN_08091810(struct Enemy* p) {}

INCASM("asm/enemy/unk_59_post_a.inc");

struct VFX* CreateGhost18(struct Coord* c, u8 r1, bool8 isRight, u8 r3);

// 0x080922e0
NON_MATCH void FUN_080922e0(struct Enemy* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      InitNonAffineMotion(&p->s);
      SET_XFLIP(p, (p->s).work[3]);
      SetMotion(&p->s, MOTION(SM019_PANTHEON_HUNTER, 3));  // 分身のハズレ枠
      (p->s).work[2] = 18;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if (((p->s).work[2] & 3) == 0) FUN_08091280(&p->s);
      if ((p->s).work[2] == 0) (p->s).mode[2]++;
      break;
    }
    case 2: {
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0) PlaySound(SE_ZAKO_EXPLODE);
      (p->s).work[2]++;
      {
        register struct Coord* c asm("r4") = &(p->s).coord;
        CreateGhost18(c, 0, ((p->s).flags & X_FLIP) != 0, (p->s).work[3]);
        {
          register const struct SlashedEnemy* tmp asm("r6") = &sSlashedEnemies[3];
          u8 work3 = (p->s).work[3];
          if ((p->s).flags & X_FLIP) work3 |= (p->s).flags & X_FLIP;
          CreateSlashedEnemy(c, tmp, 0, work3);
        }
      }
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      break;
    }
    default: {
      break;
    }
  }
#else
  INCCODE("asm/wip/FUN_080922e0.inc");
#endif
}

void FUN_080923ec(struct Enemy* p) {
  struct Coord c;
  EXIT_BODY(p);
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(8);
  CreateSmoke(1, &c);
  PlaySound(SE_ZAKO_EXPLODE);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void Enemy59_Init(struct Enemy* p);
void Enemy59_Update(struct Enemy* p);
void Enemy59_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gEnemy59Routine = {
    [ENTITY_INIT] =      Enemy59_Init,
    [ENTITY_UPDATE] =    Enemy59_Update,
    [ENTITY_DIE] =       Enemy59_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static const struct SlashedEnemy sSlashedEnemies[4] = {
    {
      m : 0x1306,
      unk_02 : {255, 17},
      c : {0x0000, 0x0000},
      d : {0x0080, -0x0500},
      unk_coord_0c : {0x00FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : 0x1307,
      unk_02 : {254, 17},
      c : {0x0000, 0x0000},
      d : {0x0080, -0x0200},
      unk_coord_0c : {0x007F, 0x007F},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : 0x1308,
      unk_02 : {254, 17},
      c : {0x0000, 0x0000},
      d : {0x0100, -0x0300},
      unk_coord_0c : {0x01FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : 0x1304,
      unk_02 : {16, 4},
      c : {0x0800, -0x1800},
      d : {-0x0080, -0x0100},
      unk_coord_0c : {0x0000, 0x0000},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
};

static const struct Collision sCollisions[14] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 5,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(2), PIXEL(22), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 3,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 2,
      range : {PIXEL(1), -PIXEL(2), PIXEL(22), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : 8,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {PIXEL(1), -PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : 8,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(1), -PIXEL(2), PIXEL(22), PIXEL(8)},
    },
};

// --------------------------------------------

void FUN_08091810(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
    FUN_08091810,
};
// clang-format on

void FUN_08091814(struct Enemy* p);
void FUN_080918ec(struct Enemy* p);
void FUN_08091980(struct Enemy* p);
void FUN_08091ab0(struct Enemy* p);
void FUN_08091b60(struct Enemy* p);
void FUN_08091c54(struct Enemy* p);
void FUN_08091d0c(struct Enemy* p);
void FUN_08091da4(struct Enemy* p);
void FUN_08091e58(struct Enemy* p);
void FUN_08091f00(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    FUN_08091814,
    FUN_080918ec,
    FUN_08091980,
    FUN_08091ab0,
    FUN_08091b60,
    FUN_08091c54,
    FUN_08091d0c,
    FUN_08091da4,
    FUN_08091e58,
    FUN_08091f00,
};
// clang-format on

// --------------------------------------------

void FUN_08091fa8(struct Enemy* p);
void FUN_080921c8(struct Enemy* p);
void FUN_080922e0(struct Enemy* p);
void FUN_080923ec(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_08091fa8,
    FUN_080921c8,
    FUN_080922e0,
    FUN_080923ec,
};

// --------------------------------------------

static const u8 u8_ARRAY_08369a14[16] = {
    1, 1, 1, 1, 2, 5, 5, 5, 5, 0, 1, 2, 6, 0, 0, 0,
};
