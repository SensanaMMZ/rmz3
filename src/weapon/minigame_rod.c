#include "collision.h"
#include "global.h"
#include "weapon.h"

// 多分ゼロのミニゲームの武器

static void Weapon16_Init(struct Weapon* w);
static void Weapon16_Update(struct Weapon* w);
void Weapon16_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gMinigameRodRoutine = {
    [ENTITY_INIT] =      Weapon16_Init,
    [ENTITY_UPDATE] =    Weapon16_Update,
    [ENTITY_DIE] =       Weapon16_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

struct Weapon* CreateWeaponMinigameRod(struct Entity* p, u8 r1, u8 r2) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_MINIGAME_ROD);
    (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
    (w->s).taskCol = 16;
    (w->s).tileNum = gWeaponTileNum[0];
    (w->s).palID = gWeaponPalIDs[0];
    (w->s).work[0] = r2;
    (w->s).work[1] = r1;
    (w->s).unk_28 = p;
  }
  return w;
}

// Init the minigame rod weapon: display + flippable, face by spawn direction
// (work[0]), route to Update. Retail keeps everything in one base register (r4),
// recomputing the spr pointers (+0x4a/+0x4c) per direction branch, expands the
// flag OR into three separate bit-ORs (incl. a live |0), and materializes the
// mode constant afresh; agbcc-from-clean-C caches the base in a second register
// and folds the flag OR — several instr shorter, a retail-suboptimal codegen
// quirk clean C can't reproduce. INCCODE for the byte-match.
NON_MATCH static void Weapon16_Init(struct Weapon* w) {
#if MODERN
  InitNonAffineMotion(&w->s);
  ResetDynamicMotion(&w->s);
  (w->s).flags |= DISPLAY | FLIPABLE;
  SET_XFLIP(w, (w->s).work[0]);
  SET_WEAPON_ROUTINE(w, ENTITY_UPDATE);
  (w->s).mode[1] = 0;
  (w->s).mode[2] = 0;
  (w->s).mode[3] = 0;
  Weapon16_Update(w);
#else
  INCCODE("asm/wip/Weapon16_Init.inc");
#endif
}

void weapon_0803cf84(struct Weapon* w);

static void Weapon16_Update(struct Weapon* w) {
  static const WeaponFunc sUpdates[1] = {
      weapon_0803cf84,
  };
  (sUpdates[(w->s).mode[1]])(w);
}

void Weapon16_Die(struct Weapon* w) {
  (w->s).flags &= ~DISPLAY;
  EXIT_BODY(w);
  SET_WEAPON_ROUTINE(w, ENTITY_EXIT);
}

INCASM("asm/weapon/minigame_rod_p2.inc");

const struct Collision gWeapon16Collisions[15] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000400,
      range : {-0x1A00, -0x0D00, 0x3800, 0x0D00},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 3,
      layer : 0x00000400,
      range : {-0x2900, -0x2F00, 0x1000, 0x1000},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000400,
      range : {-0x1D00, -0x2500, 0x1000, 0x1000},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000400,
      range : {-0x1200, -0x1900, 0x1000, 0x1000},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000400,
      range : {-0x0700, -0x0E00, 0x1000, 0x1000},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 3,
      layer : 0x00000400,
      range : {-0x2900, 0x0F00, 0x1000, 0x1000},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000400,
      range : {-0x1E00, 0x0500, 0x1000, 0x1000},
    },
    [7] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000400,
      range : {-0x1300, -0x0700, 0x1000, 0x1000},
    },
    [8] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000400,
      range : {-0x0800, -0x1200, 0x1000, 0x1000},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000800,
      range : {-0x2500, -0x0E00, 0x5000, 0x1500},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000800,
      range : {-0x2700, -0x0E00, 0x1300, 0x3200},
    },
    [11] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000800,
      range : {-0x0B00, -0x3400, 0x1500, 0x5000},
    },
    [12] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000800,
      range : {-0x0B00, -0x3400, 0x2A00, 0x1600},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000800,
      range : {0x0400, 0x1000, 0x1500, 0x4600},
    },
    [14] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_ROD,
      element : 0x00,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000800,
      range : {0x0300, 0x0700, 0x2A00, 0x1600},
    },
};

// clang-format off
const motion_t gWeapon16Motions[9] = {
    MOTION(0x75, 0x00),
    MOTION(0x75, 0x01),
    MOTION(0x76, 0x00),
    MOTION(0x76, 0x01),
    MOTION(0x77, 0x00),
    MOTION(0x77, 0x01),
    MOTION(0x7D, 0x00),
    MOTION(0x7E, 0x00),
    MOTION(0x7F, 0x01),
};
// clang-format on

// clang-format off
const struct Collision* const gWeapon16Hitboxes[9] = {
    &gWeapon16Collisions[0],
    &gWeapon16Collisions[0],
    &gWeapon16Collisions[1],
    &gWeapon16Collisions[1],
    &gWeapon16Collisions[5],
    &gWeapon16Collisions[5],
    &gWeapon16Collisions[9],
    &gWeapon16Collisions[11],
    &gWeapon16Collisions[13],
};
// clang-format on
