#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"

static const struct Collision sCollisions[5];

static const EnemyFunc sDeads[3];

void CreateGallisni(s32 x, s32 y, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_GALLISNI);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
  }
}

INCASM("asm/enemy/gallisni_p1_pre_p2.inc");

void Gallisni_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/gallisni_p1_post.inc");

void nop_0808737c(struct Enemy* p) {}

INCASM("asm/enemy/gallisni_p2_pre_pre_p1.inc");

void FUN_08087380(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/gallisni_p2_pre_pre_p2_p1.inc");

void FUN_080873a0(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[2]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/gallisni_p2_pre_pre_p2_p2.inc");

void FUN_080873fc(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x67, 3));
    UpdateMotionGraphic(&p->s);
    SetDDP(&p->body, &sCollisions[3]);
    (p->s).mode[2]++;
  }
}

INCASM("asm/enemy/gallisni_p2_pre_post.inc");

void FUN_080874ac(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x18;
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0x67, 2));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (p->props[4] != 0) p->props[4]--;
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        if (p->props[4] == 0) {
          (p->s).mode[1] = 1;
          (p->s).mode[2] = 0;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/enemy/gallisni_p2_post.inc");

void Gallisni_Init(struct Enemy* p);
void Gallisni_Update(struct Enemy* p);
void Gallisni_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gGallisniRoutine = {
    [ENTITY_INIT] =      Gallisni_Init,
    [ENTITY_UPDATE] =    Gallisni_Update,
    [ENTITY_DIE] =       Gallisni_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_080873a0(struct Enemy* p);
void nop_0808737c(struct Enemy* p);
void FUN_08087380(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    FUN_080873a0,
    nop_0808737c,
    nop_0808737c,
    FUN_08087380,
    FUN_08087380,
    FUN_08087380,
    FUN_08087380,
    nop_0808737c,
};
// clang-format on

void FUN_080873fc(struct Enemy* p);
void FUN_08087434(struct Enemy* p);
void FUN_080874ac(struct Enemy* p);
void FUN_08087518(struct Enemy* p);
void FUN_080875c8(struct Enemy* p);
void FUN_0808772c(struct Enemy* p);
void FUN_0808778c(struct Enemy* p);
void FUN_08087ab0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    FUN_080873fc,
    FUN_08087434,
    FUN_080874ac,
    FUN_08087518,
    FUN_080875c8,
    FUN_0808772c,
    FUN_0808778c,
    FUN_08087ab0,
};
// clang-format on

void FUN_080878f0(struct Enemy* p);
void FUN_08087988(struct Enemy* p);
void FUN_08087ab0(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_080878f0,
    FUN_08087988,
    FUN_08087ab0,
};

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(30), PIXEL(14), PIXEL(58)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(2), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(2), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(2), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
static const u8 sInitModes[2] = {1, 3};

static const motion_t sMotions[4] = {
    MOTION(103, 8),
    MOTION(103, 9),
    MOTION(103, 10),
    MOTION(103, 6),
};
