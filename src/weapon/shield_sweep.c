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

void CreateParticle(struct Coord* c, u8 action, bool8 isRight);

// 0x0803C2FC
void ShieldSweep_Update(struct Weapon* p) {
  struct Entity* z = (p->s).unk_28;
  register s32 w0 asm("r2");
  UpdateMotionGraphic(&p->s);
  w0 = (p->s).work[0];
  if (w0 != 0) {
    goto late;
  }
  if (z->mode[0] > 1) {
    goto kill;
  }
  if (z->mode[1] == 3) {
    goto main;
  }
kill : {
  {
    register u8 g2 asm("r0");
    register u8 h2 asm("r1");
    h2 = (p->s).flags;
    asm("" : "+r"(h2));
    g2 = 0xFE;
    g2 &= h2;
    h2 = 0xFD;
    g2 &= h2;
    (p->s).flags = g2;
  }
  {
    u8* a2 = (u8*)p + 0x8c;
    *(s32*)a2 = w0;
    asm("" : "+r"(a2));
    a2 += 4;
    asm("" : "+r"(a2));
    *(s32*)a2 = w0;
    asm("" : "+r"(a2));
    a2 += 4;
    asm("" : "+r"(a2));
    *a2 = w0;
  }
  {
    register u8 g3 asm("r0");
    register u8 h3 asm("r1");
    h3 = (p->s).flags;
    asm("" : "+r"(h3));
    g3 = 0xFB;
    g3 &= h3;
    (p->s).flags = g3;
  }
  SET_WEAPON_ROUTINE(p, 3);
  goto end;
}
main:
  if (*(s32*)((u8*)z + 0x60) != 0) {
    goto clearbit;
  }
  {
    register s32 one asm("r6");
    register u32 fv asm("r2");
    register s32 one5 asm("r5");
    register s32 t asm("r1");
    register s32 t1 asm("r3");
    {
      register u8 f0 asm("r0");
      f0 = (p->s).flags;
      one = 1;
      fv = one;
      fv |= f0;
      (p->s).flags = fv;
    }
    (p->s).coord.x = z->coord.x + (p->s).unk_coord.x;
    (p->s).coord.y = z->coord.y + (0xD0 << 4);
    t = (p->s).work[2];
    t1 = t + 1;
    (p->s).work[2] = t1;
    one5 = 1;
    {
      register s32 a asm("r0");
      a = one5;
      a &= t;
      if (a == 0) {
        goto end;
      }
    }
    {
      register s32 k asm("r0");
      k = (u8)t1;
      k >>= 1;
      k &= one;
      if (k == 0) {
        goto low;
      }
      {
        register struct Coord* cp asm("r0");
        register s32 sh asm("r1");
        register s32 r2v asm("r2");
        cp = &(p->s).coord;
        asm("" : "+r"(cp));
        sh = fv >> 4;
        r2v = one5;
        r2v &= ~sh;
        ((void (*)(struct Coord*, s32, s32))CreateParticle)(cp, 4, r2v);
        goto end;
      }
    low : {
      register struct Coord* cp2 asm("r0");
      register s32 sh2 asm("r1");
      register s32 r2w asm("r2");
      cp2 = &(p->s).coord;
      asm("" : "+r"(cp2));
      sh2 = fv >> 4;
      r2w = one5;
      r2w &= ~sh2;
      ((void (*)(struct Coord*, s32, s32))CreateParticle)(cp2, 5, r2w);
      goto end;
    }
    }
  }
clearbit : {
  register u8 g asm("r0");
  register u8 h asm("r1");
  h = (p->s).flags;
  asm("" : "+r"(h));
  g = 0xFE;
  g &= h;
  (p->s).flags = g;
  goto end;
}
late:
  if (*((u8*)p + 0x73) == 3) {
    SET_WEAPON_ROUTINE(p, 2);
    ShieldSweep_Die(p);
  }
end:;
}

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
