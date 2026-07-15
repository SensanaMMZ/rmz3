#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mod.h"
#include "overworld_terrain.h"
#include "story.h"

struct SharksealX {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 x_b4;               // 0xB4
  u8 unk_b8[4];           // 0xB8
  u8 unk_bc;              // 0xBC
  u8 unk_bd;              // 0xBD
  u8 unk_be;              // 0xBE
  u8 unk_bf;              // 0xBF
  struct Entity* unk_c0;  // 0xC0
};
static_assert(sizeof(struct SharksealX) == sizeof(struct Enemy));

static const struct Collision sCollisions[5];

struct Enemy* CreateSharksealX(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_SHARKSEAL_X);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

void SharksealX_Update(struct Enemy* p);
void FUN_080711d8(struct Body* body, struct Coord* r1, struct Coord* r2);

// 0x08070084
void SharksealX_Init(struct SharksealX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if (FLAG(gSystemSavedataManager.mods, MOD_121) && !FLAG(gCurStory.s.gameflags, DEMO_PLAY)) {
    INIT_BODY(p, sCollisions, 10, NULL);
  } else {
    INIT_BODY(p, sCollisions, 6, NULL);
  }
  SET_BODY_INTERSECT_HANDLER(p, FUN_080711d8);

  if (gOverworld.sea > (p->s).coord.y) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  p->x_b4 = (p->s).coord.x;
  (&(p->s).d)->x = (&(p->s).d)->y = 0;
  p->unk_c0 = NULL;
  p->unk_bd = 0;
  p->x_b4 = (p->s).coord.x;
  (p->s).unk_coord.y = (p->s).coord.y;
  (&(p->s).d)->x = (&(p->s).d)->y = 0;
  p->unk_bc = 0;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(SM024_SHARKSEAL_X, 0));
    UpdateMotionGraphic(&p->s);
  }
  p->unk_bf = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  SharksealX_Update((struct Enemy*)p);
}

INCASM("asm/enemy/sharkseal_x_p2.inc");

bool8 FUN_080707d0(struct Enemy* p) { return TRUE; }


void nop_080707d4(struct Enemy* p) {}

bool8 FUN_080707d8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p3.inc");

bool8 FUN_080708dc(struct Enemy* p) { return TRUE; }

short forceWaterLanding(struct Entity* p);

void sharksealxMode2(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x1800);
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      SET_XFLIP(p, *(u8*)((u8*)p + 0xbc));
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0x100) {
        (p->s).d.y = 0x100;
      }
      (p->s).coord.y += (p->s).d.y;
      forceWaterLanding(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08070990(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p5.inc");

bool8 FUN_08070c68(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p6.inc");

bool8 FUN_08070f3c(struct Enemy* p) { return TRUE; }

void sharksealxMode5(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[4]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[0]);
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_08070f8c(struct Enemy* p) { return TRUE; }


void nop_08070f90(struct Enemy* p) {}

bool8 FUN_08070f94(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p9.inc");

bool8 nop_080711d4(struct Enemy* p) { return TRUE; }

void FUN_080711d8(struct Body* body, struct Coord* r1, struct Coord* r2) {
  u8 atk_type = (body->enemy->processing)->atkType;
  if (atk_type == 3 || atk_type == 0xe || atk_type == 0xf) {
    struct Enemy* self = (struct Enemy*)(body->parent);
    if ((self->body).status & BODY_STATUS_DEAD) {
      if ((self->s).coord.x < r1->x) {
        *(u8*)((u8*)self + 0xbf) = 0xff;
      } else {
        *(u8*)((u8*)self + 0xbf) = 0xfe;
      }
    }
  }
}

short forceWaterLanding(struct Entity* p) {
  s32 sea = gOverworld.sea;
  if (sea > p->coord.y) {
    p->coord.y = sea;
  }
}

void SharksealX_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSharksealXRoutine = {
    [ENTITY_INIT] =      (void*)SharksealX_Init,
    [ENTITY_UPDATE] =    SharksealX_Update,
    [ENTITY_DIE] =       SharksealX_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_080707d0(struct Enemy* p);
bool8 FUN_080707d8(struct Enemy* p);
bool8 FUN_080708dc(struct Enemy* p);
bool8 FUN_08070990(struct Enemy* p);
bool8 FUN_08070c68(struct Enemy* p);
bool8 FUN_08070f3c(struct Enemy* p);
bool8 FUN_08070f8c(struct Enemy* p);
bool8 FUN_08070f94(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_08366a04[8] = {
    (EnemyFunc)FUN_080707d0,
    (EnemyFunc)FUN_080707d8,
    (EnemyFunc)FUN_080708dc,
    (EnemyFunc)FUN_08070990,
    (EnemyFunc)FUN_08070c68,
    (EnemyFunc)FUN_08070f3c,
    (EnemyFunc)FUN_08070f8c,
    (EnemyFunc)FUN_08070f94,
};
// clang-format on

void nop_080707d4(struct Enemy* p);
void sharksealxMode1(struct Enemy* p);
void sharksealxMode2(struct Enemy* p);
void sharksealxMode3(struct Enemy* p);
void sharksealxMode4(struct Enemy* p);
void sharksealxMode5(struct Enemy* p);
void nop_08070f90(struct Enemy* p);
void sharksealxMode7(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366a24[8] = {
    nop_080707d4,
    sharksealxMode1,
    sharksealxMode2,
    sharksealxMode3,
    sharksealxMode4,
    sharksealxMode5,
    nop_08070f90,
    sharksealxMode7,
};
// clang-format on

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(5), PIXEL(0), PIXEL(30), PIXEL(9)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(5), PIXEL(0), PIXEL(32), PIXEL(11)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(1), PIXEL(18), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(5), PIXEL(1), PIXEL(18), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(5), PIXEL(0), PIXEL(32), PIXEL(11)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
