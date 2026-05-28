#include "collision.h"
#include "enemy.h"
#include "global.h"

void FUN_080866a4(struct Entity* e, u8 mode, u8 xflip) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HANUMACHINE_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).unk_28 = e;
    SET_XFLIP(&p->s, xflip);
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
  }
}

INCASM("asm/enemy/hanumachine_obj_pre_p2.inc");

void HanumachineObj_Die(struct Enemy* p) {
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/hanumachine_obj_post.inc");

void HanumachineObj_Init(struct Enemy* p);
void HanumachineObj_Update(struct Enemy* p);
void HanumachineObj_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gHanumachineObjRoutine = {
    [ENTITY_INIT] =      HanumachineObj_Init,
    [ENTITY_UPDATE] =    HanumachineObj_Update,
    [ENTITY_DIE] =       HanumachineObj_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0808693c(struct Enemy* p);
void FUN_080869a0(struct Enemy* p);
void FUN_080869f4(struct Enemy* p);
void FUN_08086a50(struct Enemy* p);
void FUN_08086b6c(struct Enemy* p);
void FUN_08086cbc(struct Enemy* p);
void FUN_08086dcc(struct Enemy* p);
void FUN_08086e34(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates[8] = {
    FUN_0808693c,
    FUN_080869a0,
    FUN_080869f4,
    FUN_08086a50,
    FUN_08086b6c,
    FUN_08086cbc,
    FUN_08086dcc,
    FUN_08086e34,
};
// clang-format on

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(26), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(26), PIXEL(28)},
    },
};
