#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"

static const EnemyFunc sUpdates1[3];
static const EnemyFunc sUpdates2[3];

struct Enemy* createGlacierleAtkHand(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_GLACIERLE_ARM);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    InitRotatableMotion(&p->s);
    (p->s).unk_2c = NULL;
    (p->s).unk_28 = e;
    (p->s).d.x = 0;
    (p->s).d.y = 0;
    p->props[1] = 1;
    p->props[0] = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = e->uniqueID;
  }
  return p;
}

INCASM("asm/enemy/glacierle_arm_p1_p2.inc");

void nop_080828dc(struct Enemy* p) {}

INCASM("asm/enemy/glacierle_arm_p2_p1.inc");

void GlacierleAtkArm_Update(struct Enemy* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/glacierle_arm_p2_p2.inc");

void nop_08082a1c(struct Enemy* p) {}

INCASM("asm/enemy/glacierle_arm_p3_pre.inc");

void FUN_08082aa0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      InitNonAffineMotion(&p->s);
      SetMotion(&p->s, MOTION(0x59, 1));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
  }
  if ((*(struct Entity**)&p->props[8])->mode[0] > 1) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/enemy/glacierle_arm_p3_post.inc");

void GlacierleAtkArm_Init(struct Enemy* p);
void GlacierleAtkArm_Update(struct Enemy* p);
void GlacierleAtkArm_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gGlacierleAtkArmRoutine = {
    [ENTITY_INIT] =      GlacierleAtkArm_Init,
    [ENTITY_UPDATE] =    GlacierleAtkArm_Update,
    [ENTITY_DIE] =       GlacierleAtkArm_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void nop_08082a1c(struct Enemy* p);

static const EnemyFunc sUpdates1[3] = {
    nop_08082a1c,
    nop_08082a1c,
    nop_08082a1c,
};

void FUN_08082a20(struct Enemy* p);
void FUN_08082aa0(struct Enemy* p);
void FUN_08082af8(struct Enemy* p);

static const EnemyFunc sUpdates2[3] = {
    FUN_08082a20,
    FUN_08082aa0,
    FUN_08082af8,
};

// --------------------------------------------

static const struct Collision sCollisions[2] = {
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
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(12), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
};

static const u8 sInitModes[3] = {0, 1, 2};
