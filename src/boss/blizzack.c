#include "boss.h"
#include "collision.h"
#include "global.h"

void Blizzack_Init(struct Boss* p);
void Blizzack_Update(struct Boss* p);
void Blizzack_Die(struct Boss* p);

// clang-format off
const BossRoutine gBlizzackRoutine = {
    [ENTITY_INIT] =      (BossFunc)Blizzack_Init,
    [ENTITY_UPDATE] =    (BossFunc)Blizzack_Update,
    [ENTITY_DIE] =       (BossFunc)Blizzack_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

void CreateBlizzack(struct Coord* c) {
  struct Entity* p = AllocEntityFirst(gBossHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_BOSS_ROUTINE(p, BOSS_BLIZZACK);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = 0, p->work[1] = 0;
  }
}

// --------------------------------------------

static const BossFunc sDeads[3];

INCASM("asm/boss/blizzack_pre.inc");

void Blizzack_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

INCASM("asm/boss/blizzack_post_p1.inc");

void FUN_080aabd4(struct Boss* p);

void blizzackMode8(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    (p->s).mode[2] = 0;
    (p->s).work[2] = 0xb4;
    FUN_080aabd4(p);
  }
  UpdateMotionGraphic(&p->s);
  if ((u8)--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = 9;
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/boss/blizzack_post_p2_a.inc");

void FUN_0805af14(struct Boss* p) {
  if ((p->s).coord.x < *(s32*)((u8*)p + 0xb4) + 0x2000 ||
      (p->s).coord.x > *(s32*)((u8*)p + 0xd8) - 0x2000) {
    (p->s).coord.x = *(s32*)((u8*)p + 0xc0);
  }
  *(s32*)((u8*)p + 0xc0) = (p->s).coord.x;
}

void blizzackMode0(struct Boss* p);
void blizzackMode1(struct Boss* p);
void blizzackNeutral(struct Boss* p);
void blizzackPreAI(struct Boss* p);
void blizzackNextMode(struct Boss* p);
void blizzackJump(struct Boss* p);
void blizzackStamp(struct Boss* p);
void blizzackMode7(struct Boss* p);
void blizzackMode8(struct Boss* p);
void blizzackMode9(struct Boss* p);
void blizzackStartBlizzard(struct Boss* p);
void blizzackBlizzard(struct Boss* p);
void blizzackEndBlizzard(struct Boss* p);
void blizzackBombJump(struct Boss* p);
void blizzackBomb(struct Boss* p);
void blizzackBombFall(struct Boss* p);
void blizzackBombStamp(struct Boss* p);
void blizzackMode17(struct Boss* p);
void blizzackMode18(struct Boss* p);
void blizzackMode19(struct Boss* p);
void blizzackMode20(struct Boss* p);

// clang-format off
// 0x08364b50
static const BossFunc sUpdates[21] = {
    (BossFunc)blizzackMode0,
    (BossFunc)blizzackMode1,
    (BossFunc)blizzackNeutral,
    (BossFunc)blizzackPreAI,
    (BossFunc)blizzackNextMode,
    (BossFunc)blizzackJump,
    (BossFunc)blizzackStamp,
    (BossFunc)blizzackMode7,
    (BossFunc)blizzackMode8,
    (BossFunc)blizzackMode9,
    (BossFunc)blizzackStartBlizzard,
    (BossFunc)blizzackBlizzard,
    (BossFunc)blizzackEndBlizzard,
    (BossFunc)blizzackBombJump,
    (BossFunc)blizzackBomb,
    (BossFunc)blizzackBombFall,
    (BossFunc)blizzackBombStamp,
    (BossFunc)blizzackMode17,
    (BossFunc)blizzackMode18,
    (BossFunc)blizzackMode19,
    (BossFunc)blizzackMode20,
};
// clang-format on

// --------------------------------------------

void blizzack_0805ac5c(struct Boss* p);
void blizzack_0805ad2c(struct Boss* p);
void blizzack_0805add0(struct Boss* p);

static const BossFunc sDeads[3] = {
    (BossFunc)blizzack_0805ac5c,
    (BossFunc)blizzack_0805ad2c,
    (BossFunc)blizzack_0805add0,
};

// --------------------------------------------

// 0x08364bb0
static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      hitzone : 8,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(24), PIXEL(34), PIXEL(48)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(24), PIXEL(34), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      hitzone : 8,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(24), PIXEL(50), PIXEL(48)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 8,
      remaining : 0,
      range : {PIXEL(8), -PIXEL(24), PIXEL(50), PIXEL(48)},
    },
};

// 0x08364c10
static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(24)};
