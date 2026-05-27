#include "collision.h"
#include "global.h"
#include "mission.h"
#include "weapon.h"

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 4,
      atkType : 7,
      element : ELEMENT_ICE,
      comboLv : 1,
      remaining : 1,
      layer : 0x00000010,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
};

// --------------------------------------------

void BlizzardArrow_Init(struct Weapon* w);
void BlizzardArrow_Update(struct Weapon* w);
void BlizzardArrow_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gBlizzardArrowRoutine = {
    [ENTITY_INIT] =      BlizzardArrow_Init,
    [ENTITY_UPDATE] =    BlizzardArrow_Update,
    [ENTITY_DIE] =       BlizzardArrow_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

// --------------------------------------------

void MenuExit_BlizzardArrow(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (((&z->unk_b4)->status).element != ELEMENT_ICE) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }
  if (z->unk_136 & (1 << 0)) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

INCASM("asm/weapon/blizzard_arrow_pre.inc");

void BlizzardArrow_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

void hitBlizzardArrow(struct Body* body) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    struct CollidableEntity* p = body->parent;
    if (gMission.weaponCount[WEAPON_BUSTER] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_BUSTER]++;
    }
    if (!(body->enemy->status & BODY_STATUS_DEAD) || (p->s).work[0] == 0) {
      (p->s).work[3] = 1;
    }
  }
}

// --------------------------------------------

static const s32 sBulletYCoords[3] = {0x000, -0x400, 0x400};
