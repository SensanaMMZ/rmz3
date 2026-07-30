#include "collision.h"
#include "global.h"
#include "weapon.h"

#define PROP (w->props.common)

static const motion_t sMotions[4];
static const struct Collision sCollisions[2];

void Weapon13_Init(struct Weapon* w);
void Weapon13_Update(struct Weapon* w);
void Weapon13_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gWeapon13Routine = {
    [ENTITY_INIT] =      Weapon13_Init,
    [ENTITY_UPDATE] =    Weapon13_Update,
    [ENTITY_DIE] =       Weapon13_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

void MenuExit_Weapon13(struct Weapon* w) {
  if ((PROP.z)->unk_136 & (1 << 2)) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateWeapon13(struct Zero* z, u8 n) {
  u8 element;
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_ROD) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_13);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
      element = ((&z->unk_b4)->status).element;
      SetWeaponElement(0, element);
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_13);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
      element = ((&z->unk_b4)->status).element;
      SetWeaponElement(1, element);
    }
    (&PROP)->z = z;
    (w->s).work[0] = n;
    (w->s).work[1] = ++z->unk_137;
  }
  return w;
}

extern const s8 s8_ARRAY_ARRAY_083616cc[2][4];
extern const u8 u8_ARRAY_083616d4[4];

// Register-home transposition basin: retail unifies the flags load with its
// or-result web (r1) while keeping the store's RMW staged zero (movs r4,#0),
// and the xflip/index temps cascade from it; every fl-var/pin/barrier spelling
// tried either loses the staged zero or splits the web with a copy.
NON_MATCH void Weapon13_Init(struct Weapon* w) {
#if MODERN

  struct Zero* z = (w->props.common).z;
  u8 w0;
  u8 ang;
  register u32 zf2v asm("r2");
  InitNonAffineMotion(&w->s);
  ResetDynamicMotion(&w->s);
  (w->s).flags |= FLIPABLE;
  SetMotion(&w->s, sMotions[(w->s).work[0]]);
  {
    register u8 fl asm("r1");
    u32 xf;
    fl = (w->s).flags;
    fl |= DISPLAY;
    (w->s).flags = fl;
    xf = (z->s.flags >> 4) & 1;
    if (xf) {
      fl |= X_FLIP;
    } else {
      fl &= ~X_FLIP;
    }
    (w->s).flags = fl;
    (w->s).spr.xflip = xf & 1;
    (w->s).spr.oam.xflip = xf;
  }
  {
    u8 w0a = *(volatile u8*)((u8*)w + 0x10);
    if (w0a == 0 || w0a == 3) {
      u8 zfl = z->s.flags;
      u32 t = zfl & 0x10;
      zf2v = zfl & 0xFF;
      if (t != 0) {
        ang = u8_ARRAY_083616d4[0] + 0x80;
        w0 = (w->s).work[0];
      } else {
        ang = u8_ARRAY_083616d4[0];
        w0 = (w->s).work[0];
      }
    } else {
      w0 = (w->s).work[0];
      ang = u8_ARRAY_083616d4[w0];
      zf2v = z->s.flags;
    }
  }
  if (zf2v & 0x10) {
    (w->s).coord.x = z->s.coord.x - (s8_ARRAY_ARRAY_083616cc[0][w0] << 8);
  } else {
    (w->s).coord.x = z->s.coord.x + (s8_ARRAY_ARRAY_083616cc[0][w0] << 8);
  }
  {
    const s8* row1 = &s8_ARRAY_ARRAY_083616cc[1][0];
    asm("" : "+r"(row1));
    (w->s).coord.y = z->s.coord.y + (row1[z->s.work[0]] << 8);
  }
  {
    s32 dx;
    s32 dy;
    dx = gSineTable[(u8)(ang + 0x40)] << 2;
    (w->s).d.x = dx;
    if ((w->s).work[0] == 3) {
      (w->s).d.x = -dx;
      {
        u32 sh = z->s.flags >> 4;
        u32 nf = 1;
        nf &= ~sh;
        if (nf) {
          (w->s).flags |= X_FLIP;
        } else {
          (w->s).flags &= ~X_FLIP;
        }
        (w->s).spr.xflip = nf & 1;
        (w->s).spr.oam.xflip = nf;
      }
    }
    dy = gSineTable[ang] << 2;
    (w->s).d.y = dy;
    (w->s).unk_coord.x = (w->s).d.x / 0x1A;
    (w->s).unk_coord.y = dy / 0x1A;
  }
  SET_WEAPON_ROUTINE(w, ENTITY_UPDATE);
  Weapon13_Update(w);

#else
  INCCODE("asm/weapon/unk_13_init.inc");
#endif
}

void Weapon13_Update(struct Weapon* w) {
  if ((w->s).work[1] != (w->props.common).z->unk_137) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }
  UpdateMotionGraphic(&w->s);
  (w->s).coord.x += (w->s).d.x;
  (w->s).coord.y += (w->s).d.y;
  (w->s).d.x = (w->s).d.x - (w->s).unk_coord.x;
  (w->s).d.y = (w->s).d.y - (w->s).unk_coord.y;
  if ((w->s).motion.state == 3) {
    SET_WEAPON_ROUTINE(w, ENTITY_DIE);
    Weapon13_Die(w);
  }
}

void Weapon13_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}


const s8 s8_ARRAY_ARRAY_083616cc[2][4] = {
    {0xEA, 0xF5, 0x03, 0x16},
    {0xF2, 0xD8, 0x02, 0xF3},
};

const u8 u8_ARRAY_083616d4[4] = {0x80, 0xC0, 0x40, 0x00};

static const motion_t sMotions[4] = {
    MOTION(DM104_UNK, 0),
    MOTION(DM104_UNK, 1),
    MOTION(DM104_UNK, 1),
    MOTION(DM104_UNK, 0),
};

#undef PROP
