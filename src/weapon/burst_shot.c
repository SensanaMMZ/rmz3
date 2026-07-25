#include "collision.h"
#include "global.h"
#include "mission.h"
#include "motion.h"
#include "weapon.h"
#include "zero.h"
#include "entity/macros.h"

// A firework of Burst shot

static const struct Collision sCollision = {
  kind : DDP,
  faction : FACTION_ALLY,
  special : HALFABLE,
  damage : 2,
  atkType : 6,
  nature : ELEMENT_ENCHANTABLE,
  comboLv : 2,
  remaining : 0,
  layer : 0x00000008,
  range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
};

// --------------------------------------------

void BurstShot_Init(struct Weapon* w);
void BurstShot_Update(struct Weapon* w);
void BurstShot_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gBurstShotRoutine = {
    [ENTITY_INIT] =      BurstShot_Init,
    [ENTITY_UPDATE] =    BurstShot_Update,
    [ENTITY_DIE] =       BurstShot_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

// --------------------------------------------

void MenuExit_BurstShot(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (((&z->unk_b4)->status).element != ELEMENT_FLAME || (z->unk_136 & (1 << 0))) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateBurstShot(struct Zero* z, struct Weapon* p, u8 n, s32 x, s32 y) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_BUSTER) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_BURST_SHOT);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_BURST_SHOT);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
    }
    (w->s).unk_28 = &z->s;
    (w->s).unk_2c = &p->s;
    (w->s).coord = (p->s).coord;
    (w->s).work[0] = n;
    (w->s).work[1] = 0;
    (w->s).coord.x += x;
    (w->s).coord.y += y;
  }
  return w;
}

static const motion_t sMotions[3];
void FUN_0803b73c(struct Body* body, struct Coord* c1, struct Coord* c2);

void BurstShot_Init(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  struct Entity* q = (w->s).unk_2c;

  SET_WEAPON_ROUTINE(w, ENTITY_UPDATE);
  InitNonAffineMotion(&w->s);
  ResetDynamicMotion(&w->s);
  (w->s).flags |= DISPLAY;
  (w->s).flags |= FLIPABLE;
  SetMotion(&w->s, sMotions[(w->s).work[0]]);
  INIT_BODY(w, &sCollision, 1, NULL);
  InitWeaponBody(&w->body, &sCollision, (u8)(CalcBusterBonus(z) + 2), 2, 2, (q->work[3] >> 2) + 2);
  SET_BODY_INTERSECT_HANDLER(w, FUN_0803b73c);
  BurstShot_Update(w);
}

void BurstShot_Update(struct Weapon* w) {
  UpdateMotionGraphic(&w->s);
  if ((w->s).motion.state == MOTION_END) {
    SET_WEAPON_ROUTINE(w, ENTITY_DIE);
    BurstShot_Die(w);
  }
}

void BurstShot_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

void FUN_0803b73c(struct Body* body, struct Coord* c1, struct Coord* c2) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    if (gMission.weaponCount[WEAPON_BUSTER] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_BUSTER]++;
    }
  }
}

static const motion_t sMotions[3] = {
    MOTION(DM083_BURST_SHOT_FIREWORK, 0x00),
    MOTION(DM083_BURST_SHOT_FIREWORK, 0x01),
    MOTION(DM083_BURST_SHOT_FIREWORK, 0x02),
};
