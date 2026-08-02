#include "global.h"
#include "mission.h"
#include "weapon.h"

#define PROP (w->props.common)

void ShieldSweep_Init(struct Weapon* w);
void ShieldSweep_Update(struct Weapon* w);
void ShieldSweep_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gShieldSweepRoutine = {
    [ENTITY_INIT] =      ShieldSweep_Init,
    [ENTITY_UPDATE] =    ShieldSweep_Update,
    [ENTITY_DIE] =       ShieldSweep_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

void MenuExit_ShieldSweep(struct Weapon* w) {
  if ((PROP.z)->unk_136 & (1 << 3)) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateShieldSweep(struct Zero* z, struct Entity* p, u8 n) {
  struct Weapon* w;
  struct WeaponProps* b4;
  u8 element;

  w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_SHIELD) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SHIELD_SWEEP);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
      element = ((&z->unk_b4)->status).element;
      SetWeaponElement(0, element);
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SHIELD_SWEEP);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
      element = ((&z->unk_b4)->status).element;
      SetWeaponElement(1, element);
    }
    b4 = &PROP;
    b4->z = z;
    (w->s).unk_28 = p;
    (w->s).work[0] = n;
    (w->s).work[1] = 0;
  }
  return w;
}

void incrementShieldHitCount_0803c40c(struct Body* body);

// 0x0803C238 -- shield sweep spawn: inherit the owner's facing, set the sweep
// direction, pick the start motion and attach the hit handler.
// Logic verified; parked two instructions short on the facing computation.
// Retail keeps the owner's flags in r0 and shifts THREE-OPERAND into the
// result register, then materialises the mask separately
// (`ldrb r0,[r6,#0xa]; lsrs r1,r0,#0x4; movs r0,#0x1; ands r1,r0`).
// Written as one expression agbcc shifts in place and swaps the two registers;
// split into `xf = qf >> 4; xf &= one1;` it drops the mask entirely (value-range
// analysis decides the &1 is redundant for the uses that follow), losing both
// the `movs` and the `ands`. Everything else -- the transfer-asm FLIPABLE copy,
// the r3-pinned dead zero, the in-place `xf <<= 4` for the OAM insert, the
// handler-before-address store -- reproduces exactly.
NON_MATCH void ShieldSweep_Init(struct Weapon* p) {
#if MODERN
  struct Entity* q = (p->s).unk_28;
  register u8 fv asm("r2");
  register s32 z asm("r3");
  register s32 xf asm("r1");
  u8 w0;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register u8 fl asm("r1");
    u8 k2;
    fl = (p->s).flags;
    k2 = FLIPABLE;
    asm volatile("add %0, %1, #0" : "=&l"(fv) : "l"(k2));
    fv |= fl;
    {
      u8 one = DISPLAY;
      z = 0;
      asm("" : "+r"(z));
      asm volatile("" ::"r"(z));
      fv |= one;
    }
    (p->s).flags = fv;
  }
  {
    u8 qf = q->flags;
    s32 one1;
    xf = qf >> 4;
    one1 = 1;
    xf &= one1;
  }
  if (xf != 0) {
    fv |= 0x10;
  } else {
    fv &= 0xEF;
  }
  (p->s).flags = fv;
  ((p->s).spr).xflip = xf;
  {
    u8* oa = (u8*)p + 0x4a;
    s32 ov;
    s32 m11;
    xf <<= 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    m11 |= xf;
    *oa = m11;
  }
  if ((p->s).flags & X_FLIP) {
    (p->s).unk_coord.x = -0x600;
  } else {
    (p->s).unk_coord.x = 0x600;
  }
  w0 = (p->s).work[0];
  if (w0 == 0) {
    SetMotion(&p->s, MOTION(0x8D, 0x00));
    (p->s).work[2] = w0;
  } else {
    SetMotion(&p->s, MOTION(0x8D, 0x01));
    (p->s).coord = q->coord;
  }
  {
    void* h = (void*)incrementShieldHitCount_0803c40c;
    struct Body* b = &p->body;
    b->fn = h;
  }
  SET_WEAPON_ROUTINE(p, ENTITY_UPDATE);
  ShieldSweep_Update(p);
}

#else
  INCCODE("asm/weapon/shield_sweep_init.inc");
#endif
}

INCASM("asm/weapon/shield_sweep_pre.inc");

void ShieldSweep_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

void incrementShieldHitCount_0803c40c(struct Body* body) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    if (gMission.weaponCount[WEAPON_SHIELD] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_SHIELD]++;
    }
  }
}

#undef PROP
