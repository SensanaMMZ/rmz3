#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "story.h"

INCASM("asm/enemy/snakecord_p1_p1_a_p1.inc");

void FUN_080740e4(struct Enemy* p);

void FUN_08074134(struct Body* body) {
  struct Enemy* parent = (struct Enemy*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_B3) {
    if ((parent->s).work[0] == 1) {
      if (body->hitboxFlags & BODY_STATUS_SLASHED) {
        FUN_080740e4(parent);
      }
    }
  }
}

INCASM("asm/enemy/snakecord_p1_p1_a_p2.inc");

static const EnemyFunc PTR_ARRAY_08366e30[12];
extern const EnemyFunc PTR_ARRAY_08366e60[12];
bool8 FUN_0807415c(struct Enemy* p);
void FUN_080742ec(struct Enemy* p);
bool8 FUN_08074208(struct Enemy* p);
void Snakecord_Die(struct Enemy* p);

void Snakecord_Update(struct Enemy* p) {
  if ((p->s).work[0] == 1) {
    struct Entity* par = (p->s).unk_2c;
    if (par != NULL) {
      u8 pm = par->mode[0];
      if (pm > 2) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
      if (pm > 1) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = (p->s).work[0];
        return;
      }
    }
  }
  if (FUN_0807415c(p)) {
    return;
  }
  FUN_080742ec(p);
  if (FUN_08074208(p)) {
    return;
  }
  (PTR_ARRAY_08366e30[(p->s).mode[1]])(p);
  (PTR_ARRAY_08366e60[(p->s).mode[1]])(p);
}

extern const EnemyFunc PTR_ARRAY_08366e90[3];

void Snakecord_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (PTR_ARRAY_08366e90[(p->s).mode[1]])(p);
}

void FUN_08074618(struct Enemy* p) {}

void FUN_0807461c(struct Enemy* p) {
  u32 status = (p->body).status;
  if (status & BODY_STATUS_WHITE) {
    if (status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 0xa;
      (p->s).mode[2] = 0;
    }
  }
  if ((p->body).status & BODY_STATUS_BINDING) {
    (p->s).mode[1] = 9;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/snakecord_p1_p2.inc");

void FUN_0807472c(struct Enemy* p) {
  u32 status = (p->body).status;
  if (status & BODY_STATUS_WHITE) {
    if (status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 0xa;
      (p->s).mode[2] = 0;
    }
  }
}

INCASM("asm/enemy/snakecord_p2.inc");

void Snakecord_Init(struct Enemy* p);
void Snakecord_Update(struct Enemy* p);
void Snakecord_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSnakecordRoutine = {
    [ENTITY_INIT] =      Snakecord_Init,
    [ENTITY_UPDATE] =    Snakecord_Update,
    [ENTITY_DIE] =       Snakecord_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080746c0(struct Enemy* p);
void FUN_08074618(struct Enemy* p);
void FUN_08074618(struct Enemy* p);
void FUN_0807472c(struct Enemy* p);
void FUN_0807461c(struct Enemy* p);
void FUN_0807465c(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_08366e30[12] = {
    FUN_080746c0,
    FUN_08074618,
    FUN_08074618,
    FUN_0807472c,
    FUN_0807472c,
    FUN_0807472c,
    FUN_0807472c,
    FUN_0807461c,
    FUN_0807461c,
    FUN_0807465c,
    FUN_08074618,
    FUN_0807472c,
};
// clang-format on

// --------------------------------------------

void snakecord_08074754(struct Enemy* p);
void FUN_080748a8(struct Enemy* p);
void FUN_0807484c(struct Enemy* p);
void FUN_08074ac0(struct Enemy* p);
void FUN_08074bac(struct Enemy* p);
void FUN_08074cb4(struct Enemy* p);
void FUN_08074d18(struct Enemy* p);
void FUN_08074d90(struct Enemy* p);
void FUN_08074e90(struct Enemy* p);
void FUN_08074f34(struct Enemy* p);
void FUN_08075154(struct Enemy* p);
void FUN_08074fcc(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366e60[12] = {
    snakecord_08074754,
    FUN_080748a8,
    FUN_0807484c,
    FUN_08074ac0,
    FUN_08074bac,
    FUN_08074cb4,
    FUN_08074d18,
    FUN_08074d90,
    FUN_08074e90,
    FUN_08074f34,
    FUN_08075154,
    FUN_08074fcc,
};
// clang-format on

// --------------------------------------------

void MaybeKillSnakecord(struct Enemy* p);
void FUN_080750f8(struct Enemy* p);
void FUN_08075154(struct Enemy* p);

const EnemyFunc PTR_ARRAY_08366e90[3] = {
    MaybeKillSnakecord,
    FUN_080750f8,
    FUN_08075154,
};

// --------------------------------------------

// 0x08366e9c
static const struct Collision sCollisions[] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(4), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : HARDNESS_B3,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(26), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(26), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      unk_0a : 0x21,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(8), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : 8,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(8), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      unk_0a : 0x21,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(5), -PIXEL(16), PIXEL(64), PIXEL(64)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(11), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(11), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(3), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : 8,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(3), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(26), PIXEL(11), PIXEL(10)},
    },
};

// --------------------------------------------

// 0x08366fec
static const u8 u8_ARRAY_08366fec[13] = {
    4, 4, 4, 4, 4, 4, 9, 9, 11, 11, 11, 11, 11,
};

static const struct Coord sElementCoords[2] = {
    {PIXEL(0), -PIXEL(24)},
    {PIXEL(0), -PIXEL(16)},
};

static const u8 sInitModes[4] = {1, 2, 0, 0};
