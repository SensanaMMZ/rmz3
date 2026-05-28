#include "collision.h"
#include "global.h"
#include "mission.h"
#include "weapon.h"

// props (56bytes, offset: 0xB4..)
struct SoulLauncherProps {
  struct Zero* z;
  u8 unk_b8[8];
  u8 unk_c0;
  u8 element;
  u8 unk_c2[42];
};

static const struct Collision sCollisions[2];

void MenuExit_SoulLauncher(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  struct SoulLauncherProps* s = (struct SoulLauncherProps*)w->props.raw;
  if ((s->element != ((&z->unk_b4)->status).element) || (z->unk_136 & (1 << 2))) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateSoulLauncher(struct Zero* z, u8 r1, u8 r2) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    struct SoulLauncherProps* s;
    if ((z->unk_b4).mainCopy == WEAPON_ROD) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SOUL_LANCHER);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SOUL_LANCHER);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
    }
    (w->s).unk_28 = &z->s;
    (w->s).work[0] = r1;
    (w->s).work[1] = r2;

    s = (struct SoulLauncherProps*)w->props.raw;
    s->element = ((&z->unk_b4)->status).element;
  }
  return w;
}

INCASM("asm/weapon/soul_launcher_pre.inc");

void SoulLauncher_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

void FUN_0803b4b0(struct Body* body) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    struct Weapon* w = (struct Weapon*)body->parent;
    if (gMission.weaponCount[WEAPON_ROD] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_ROD]++;
    }
    if ((w->s).work[1] == 0) {
      ((struct SoulLauncherProps*)w->props.raw)->unk_c0 = 1;
    }
  }
}

metatile_attr_t FUN_0803b4e8(s32 x, s32 y) {
  metatile_attr_t result = FUN_080098a4(x, y);
  if (result == 0x800F) {
    result = 0;
  }
  return result;
}

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 1,
      atkType : ATK_SOUL_LAUNCHER,
      nature : ELEMENT_ENCHANTABLE,
      comboLv : 1,
      remaining : 1,
      layer : 0x00200000,
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

void SoulLauncher_Init(struct Weapon* w);
void SoulLauncher_Update(struct Weapon* w);
void SoulLauncher_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gSoulLauncherRoutine = {
    [ENTITY_INIT] =      SoulLauncher_Init,
    [ENTITY_UPDATE] =    SoulLauncher_Update,
    [ENTITY_DIE] =       SoulLauncher_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

const s32 s32_ARRAY_0836159c[4] = {-0x200, -0x100, 0x100, 0x200};
