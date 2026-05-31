#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"

// Entity.work[0]
#define SEIMERAN_ROOT 0
#define SEIMERAN_CLONE 1
#define SEIMERAN_SEED 2

typedef struct EnemySeimeran {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct {
    struct Entity* elfx;  // 0xB4, Element Effect
    struct Coord c_b8;    // 0xB8
    u8 unk_c0;            // 0xC0
  } props;
} Seimeran;

static const struct Collision sCollisions[15];

void Seimeran_Die(struct Enemy* p);
extern const EnemyFunc sUpdates1[8];
extern const EnemyFunc sUpdates2[8];
extern const struct Coord sElementCoord;

INCASM("asm/enemy/seimeran_p1.inc");

static bool8 FUN_0808f348(Seimeran* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if (((p->s).work[0] != SEIMERAN_SEED) && ((p->body).status & BODY_STATUS_SLASHED) && ((p->props).unk_c0 > 9)) {
      (p->s).mode[1] = 1;
    } else {
      (p->s).mode[1] = 0;
    }
    Seimeran_Die((void*)p);
    return TRUE;
  }
  return FALSE;
}

static bool8 FUN_0808f3a8(Seimeran* p) {
  if (((p->s).work[0] != SEIMERAN_SEED) && (p->props).elfx == NULL) {
    switch ((p->s).mode[3]) {
      case 0: {
        if (IsFrozen((void*)p)) {
          (sUpdates1[(p->s).mode[1]])((void*)p);
          (sUpdates2[(p->s).mode[1]])((void*)p);
          (p->s).mode[3]++;
          UpdateMotionGraphic(&p->s);
          return TRUE;
        }
        break;
      }
      case 1: {
        if (IsFrozen((void*)p)) {
          return TRUE;
        }
        (p->s).mode[3] = 0;
        break;
      }
    }
  }
  return FALSE;
}

static void FUN_0808f424(Seimeran* p) {
  if ((p->props).elfx == NULL && ((p->s).work[0] != SEIMERAN_SEED) && ((p->s).mode[1] != 5) && ((p->s).mode[1] != 6) && ((p->body).status & BODY_STATUS_WHITE)) {
    (p->props).elfx = (void*)ApplyElementEffect(0, &p->s, &sElementCoord);
    if ((p->props).elfx != NULL) {
      (p->s).mode[1] = 0, (p->s).mode[2] = 0;
    }
  }
}

INCASM("asm/enemy/seimeran_p1b.inc");

void FUN_0808f728(struct Enemy* p) {}

INCASM("asm/enemy/seimeran_p2_p1.inc");

void FUN_0808f8e0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[11]);
      (p->s).work[2] = 0xa0;
      SetMotion(&p->s, MOTION(0x77, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (--(p->s).work[2] == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
  }
}

INCASM("asm/enemy/seimeran_p2_p2.inc");

void FUN_0808fa24(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x103);
      SetMotion(&p->s, MOTION(0x77, 4));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/seimeran_p2_p3.inc");

void Seimeran_Init(struct Enemy* p);
void Seimeran_Update(struct Enemy* p);
void Seimeran_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSeimeranRoutine = {
    [ENTITY_INIT] =      Seimeran_Init,
    [ENTITY_UPDATE] =    Seimeran_Update,
    [ENTITY_DIE] =       Seimeran_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0808f728(struct Enemy* p);
void FUN_0808f72c(struct Enemy* p);

// clang-format off
const EnemyFunc sUpdates1[8] = {
    FUN_0808f72c,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
};
// clang-format on

void FUN_0808f7ac(struct Enemy* p);
void FUN_0808f824(struct Enemy* p);
void FUN_0808f8e0(struct Enemy* p);
void FUN_0808f934(struct Enemy* p);
void FUN_0808fa24(struct Enemy* p);
void FUN_0808fa70(struct Enemy* p);
void FUN_0808fb10(struct Enemy* p);
void FUN_0808fc10(struct Enemy* p);

// clang-format off
const EnemyFunc sUpdates2[8] = {
    FUN_0808f7ac,
    FUN_0808f824,
    FUN_0808f8e0,
    FUN_0808f934,
    FUN_0808fa24,
    FUN_0808fa70,
    FUN_0808fb10,
    FUN_0808fc10,
};
// clang-format on

// --------------------------------------------

void maybeKillSeimeran(struct Enemy* p);
void FUN_0808fd88(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08369414[2] = {
    maybeKillSeimeran,
    FUN_0808fd88,
};

// --------------------------------------------

static const struct Collision sCollisions[15] = {
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
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(15), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(9), PIXEL(18), PIXEL(21)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(9), PIXEL(15), PIXEL(21)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(11), PIXEL(18), PIXEL(25)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(11), PIXEL(15), PIXEL(25)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(13), PIXEL(18), PIXEL(29)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(15), PIXEL(29)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(18), PIXEL(35)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(15), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(17), PIXEL(18), PIXEL(38)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(17), PIXEL(15), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(15), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(15), PIXEL(15)},
    },
};

static const u8 sCollisionIdxs[16] = {1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 11, 0, 0, 0};

const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};

static const u8 sInitModes[4] = {1, 5, 7, 0};

static const motion_t sMotions[1] = {
    MOTION(SM119_SEIMERAN, 5),
};
