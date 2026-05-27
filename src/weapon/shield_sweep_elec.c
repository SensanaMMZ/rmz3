#include "global.h"
#include "mission.h"
#include "weapon.h"

// クロールシールドの電気びりびり

// 0x08361724
static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 4,
      element : ELEMENT_THUNDER,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 1,
      remaining : 1,
      layer : 0x00000004,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
};

void ElecShieldSweep_Init(struct Weapon* w);
void ElecShieldSweep_Update(struct Weapon* w);
void ElecShieldSweep_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gElecShieldSweepRoutine = {
    [ENTITY_INIT] =      ElecShieldSweep_Init,
    [ENTITY_UPDATE] =    ElecShieldSweep_Update,
    [ENTITY_DIE] =       ElecShieldSweep_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

void MenuExit_ShieldSweepElec(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (((&z->unk_b4)->status).element != ELEMENT_THUNDER || (z->unk_136 & (1 << 3))) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateShieldSweepElec(struct Zero* z, s32 x, s32 y) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_SABER) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SHIELD_SWEEP_ELEC);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SHIELD_SWEEP_ELEC);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
    }
    (w->s).unk_28 = &z->s;
    (w->s).coord.x = x;
    (w->s).coord.y = y;
    (w->s).work[0] = 0;
    (w->s).work[1] = 0;
  }
  return w;
}

INCASM("asm/weapon/shield_sweep_elec_pre.inc");

void ElecShieldSweep_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

void incrementShieldHitCount(struct Body* body) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    struct CollidableEntity* p = body->parent;
    if (gMission.weaponCount[WEAPON_SHIELD] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_SHIELD]++;
    }
    (p->s).work[1] = 1;
  }
}
