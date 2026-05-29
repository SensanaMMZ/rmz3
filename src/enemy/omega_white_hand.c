#include "collision.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "motion.h"

struct OmegaWhiteHandObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Coord unk_b4;  // オメガ本体からの距離?
  u8 unk_bc[8];
};
static_assert(sizeof(struct OmegaWhiteHandObject) == sizeof(struct Enemy));

static const struct Collision sCollisions[];

static void OmegaWhiteHand_Init(struct OmegaWhiteHandObject* p);
static void OmegaWhiteHand_Update(Object* p);
static void OmegaWhiteHand_Die(struct Entity* p);

// clang-format off
const EnemyRoutine gOmegaWhiteHandRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)OmegaWhiteHand_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)OmegaWhiteHand_Update,
    [ENTITY_DIE] =       (EnemyFunc)OmegaWhiteHand_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateOmegaWhiteHand(struct Coord* c, bool8 isLeftHand, struct Entity* omega) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 8);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = isLeftHand;
    p->unk_28 = omega;
  }
  return p;
}

// --------------------------------------------

static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

static void OmegaWhiteHand_Init(struct OmegaWhiteHandObject* p) {
  InitScalerotMotion1(&p->s);
  (p->s).angle = 0;
  SET_XFLIP(p, FALSE);
  (p->s).flags &= ~DISPLAY;
  (p->s).flags |= FLIPABLE;
  INIT_BODY(p, &sCollisions[0], 1, onCollision);
  {
    struct Coord* d = &(p->s).d;
    d->x = d->y = 0;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 1;
  if ((p->s).work[0] == 0) {  // 右手
    (p->s).spr.oam.priority = 3;
    (p->unk_b4).x = -PIXEL(19);
    (p->unk_b4).y = -PIXEL(58);
  } else {                // 左手
    (p->s).taskCol = 23;  // 重なったら、右手の方が見えるようにする
    (p->unk_b4).x = PIXEL(21);
    (p->unk_b4).y = -PIXEL(56);
    SET_YFLIP(p, FALSE);  // 左手は上下反転させない
  }
  (p->s).flags2 |= WHITE_PAINTABLE;
  (p->s).invincibleID = ((p->s).unk_28)->uniqueID;  // オメガが白くなったら、手も白くするで

  OmegaWhiteHand_Update((void*)p);
}

// --------------------------------------------

bool8 FUN_0806aa9c(struct Enemy* p);
bool8 FUN_0806ae90(struct Enemy* p);
void FUN_0806af24(struct Enemy* p);
bool8 FUN_0806b094(struct Enemy* p);
bool8 FUN_0806b120(struct Enemy* p);
bool8 FUN_0806b8cc(struct Enemy* p);

void FUN_0806aaa0(struct Enemy* p);
void FUN_0806ae94(struct Enemy* p);
void FUN_0806af40(struct Enemy* p);
void FUN_0806b098(struct Enemy* p);
void FUN_0806b124(struct Enemy* p);
void FUN_0806b8d0(struct Enemy* p);

void FUN_0806ac98(struct Enemy* p);
void FUN_0806aedc(struct Enemy* p);
void FUN_0806afdc(struct Enemy* p);
void FUN_0806b0dc(struct Enemy* p);
void FUN_0806b4cc(struct Enemy* p);
void FUN_0806bb8c(struct Enemy* p);

static void OmegaWhiteHand_Update(Object* p) {
  // clang-format off
  static const EnemyFunc sUpdates[6] = {
      (EnemyFunc)FUN_0806aa9c,
      (EnemyFunc)FUN_0806ae90,
      (EnemyFunc)FUN_0806af24,
      (EnemyFunc)FUN_0806b094,
      (EnemyFunc)FUN_0806b120,
      (EnemyFunc)FUN_0806b8cc,
  }; // 0x083663e0
  // clang-format on

  // clang-format off
  static const EnemyFunc sUpdateRights[6] = {
      (EnemyFunc)FUN_0806aaa0,
      (EnemyFunc)FUN_0806ae94,
      (EnemyFunc)FUN_0806af40,
      (EnemyFunc)FUN_0806b098,
      (EnemyFunc)FUN_0806b124,
      (EnemyFunc)FUN_0806b8d0,
  }; // 0x083663f8
  // clang-format on

  // clang-format off
  static const EnemyFunc sUpdateLefts[6] = {
      (EnemyFunc)FUN_0806ac98,
      (EnemyFunc)FUN_0806aedc,
      (EnemyFunc)FUN_0806afdc,
      (EnemyFunc)FUN_0806b0dc,
      (EnemyFunc)FUN_0806b4cc,
      (EnemyFunc)FUN_0806bb8c,
  }; // 0x08366410
  // clang-format on

  struct Boss* omega = (struct Boss*)(p->s).unk_28;
  if ((omega->s).mode[0] >= ENTITY_DISAPPEAR) {
    // 本体が消えるときは、手も消える
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  if (((omega->props).omegaWhite.unk_d4 & 2) && ((p->s).mode[1] != 5)) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  (sUpdates[(p->s).mode[1]])((void*)p);

  if ((p->s).work[0] == 0) {  // 右手
    (sUpdateRights[(p->s).mode[1]])((void*)p);
  } else {  // 左手
    (sUpdateLefts[(p->s).mode[1]])((void*)p);
  }
}

// --------------------------------------------

void FUN_0806a8fc(struct Enemy* p);
void FUN_0806aa54(struct Enemy* p);

static void OmegaWhiteHand_Die(struct Entity* p) {
  static const EnemyFunc sDeinitializers[2] = {
      (EnemyFunc)FUN_0806a8fc,
      (EnemyFunc)FUN_0806aa54,
  };  // 0x08366428
  (sDeinitializers[(p->mode)[1]])((void*)p);
}

// --------------------------------------------

INCASM("asm/enemy/omega_white_hand_p1.inc");

bool8 FUN_0806aa9c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/omega_white_hand_p2.inc");

bool8 FUN_0806ae90(struct Enemy* p) { return TRUE; }

void FUN_0806ae94(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      (p->s).coord.y = ((struct Enemy*)(p->s).unk_28)->s.coord.y;
      (p->s).coord.x = ((struct Enemy*)(p->s).unk_28)->s.coord.x;
      SetMotion(&p->s, MOTION(0x9, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

void FUN_0806aedc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      (p->s).coord.y = ((struct Enemy*)(p->s).unk_28)->s.coord.y;
      (p->s).coord.x = ((struct Enemy*)(p->s).unk_28)->s.coord.x;
      SetMotion(&p->s, MOTION(0x9, 1));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

INCASM("asm/enemy/omega_white_hand_p3_p3.inc");

bool8 FUN_0806b094(struct Enemy* p) { return TRUE; }

void FUN_0806b098(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_0806b0dc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

bool8 FUN_0806b120(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/omega_white_hand_p5.inc");

bool8 FUN_0806b8cc(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/omega_white_hand_p6.inc");

// 0x0806be0c
static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {}

// 0x08366430
static const struct Collision sCollisions[7] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0100, 0x1800, 0x2B00},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0100, 0x1600, 0x2900},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0100, 0x1800, 0x2B00},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0100, 0x1600, 0x2900},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0100, 0x1800, 0x2B00},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0400, 0x0200, 0x1E00, 0x2800},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0400, 0x0200, 0x2000, 0x2A00},
    },
};
