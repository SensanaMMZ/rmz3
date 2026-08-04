#include "global.h"
#include "mission.h"
#include "weapon.h"

// ラクサイガ雷が地面につくる電撃

static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

// 0x083616e0
static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
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

void SmashElec_Init(struct Weapon* w);
void SmashElec_Update(struct Weapon* w);
void SmashElec_Die(struct Weapon* w);
void SmashElec_Disappear(struct Weapon* w);

// clang-format off
const WeaponRoutine gSmashElecRoutine = {
    [ENTITY_INIT] =      SmashElec_Init,
    [ENTITY_UPDATE] =    SmashElec_Update,
    [ENTITY_DIE] =       SmashElec_Die,
    [ENTITY_DISAPPEAR] = SmashElec_Disappear,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

void MenuExit_SaberSmash(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (((&z->unk_b4)->status).element != ELEMENT_THUNDER || (z->unk_136 & (1 << 1))) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateSmashElec(struct Zero* z, struct Coord* c, u8 leftOrRight) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_SABER) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_RAKUSAIGA);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0], (w->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_RAKUSAIGA);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1], (w->s).palID = gWeaponPalIDs[1];
    }
    (w->s).unk_28 = (struct Entity*)z;
    (w->s).coord = *c;
    (w->s).work[0] = leftOrRight, (w->s).work[1] = 0;
    z->unk_13a++;
  }
  return w;
}

// 0x0803C8C8
void SmashElec_Init(struct Weapon* w) {
  register struct Zero* z asm("r8");
  register s32 zr asm("r6");
  register s32 zr2 asm("sb");
  register struct Body* bd asm("r4");
  register const struct Collision* col asm("r5");
  z = (struct Zero*)(w->s).unk_28;
  {
    u32 tbl = (u32)gWeaponFnTable;
    EntityFunc** rt = (EntityFunc**)((((w->s).id) << 2) + tbl);
    register u32 one asm("r1");
    one = 1;
    *(u32*)((w->s).mode) = one;
    (w->s).onUpdate = (void*)((*rt)[1]);
  }
  InitNonAffineMotion(&w->s);
  ResetDynamicMotion(&w->s);
  {
    register u8 g asm("r0");
    register u8 h asm("r1");
    h = (w->s).flags2;
    asm("" : "+r"(h));
    g = 0xFB;
    g &= h;
    zr = 0;
    (w->s).flags2 = g;
  }
  {
    register s32 z0 asm("r0");
    z0 = 0;
    asm volatile("strh %0, [%1, #0x20]" :: "l"(zr), "l"(w) : "memory");
    *((u8*)w + 0x22) = z0;
  }
  {
    register u8 g2 asm("r0");
    register s32 k asm("r1");
    register s32 k0 asm("r2");
    g2 = (w->s).flags;
    k = 1;
    k0 = 0;
    asm volatile("mov %0, %1" : "=r"(zr2) : "l"(k0));
    g2 |= k;
    k = 2;
    g2 |= k;
    (w->s).flags = g2;
  }
  SetMotion(&w->s, 0x1A06);
  {
    register u8 g3 asm("r0");
    register s32 k4 asm("r1");
    g3 = (w->s).flags;
    k4 = 4;
    g3 |= k4;
    (w->s).flags = g3;
  }
  bd = &w->body;
  col = (const struct Collision*)0x083616E0;
  InitBody(bd, col, &(w->s).coord, 1);
  *(struct Weapon**)((u8*)bd + 0x2c) = w;
  *(s32*)((u8*)bd + 0x24) = zr;
  {
    register s32 atk asm("r2");
    register s32 m1 asm("r3");
    {
      register s32 rv asm("r0");
      rv = ((s32 (*)(struct Zero*))CalcSaberBonus)(z);
      asm volatile("add %0, %1, #0" : "=l"(atk) : "l"(rv));
    }
    atk += 8;
    atk = (u32)(atk << 24) >> 24;
    m1 = 1;
    m1 = -m1;
    ((void (*)(struct Body*, const struct Collision*, s32, s32, s32, s32))InitWeaponBody)(bd, col, atk, m1, m1, m1);
  }
  {
    register s32 wv asm("r2");
    register u8 g4 asm("r0");
    wv = (w->s).work[0];
    if (wv != 0) {
      register s32 k10 asm("r1");
      g4 = (w->s).flags;
      k10 = 0x10;
      g4 |= k10;
    } else {
      register u8 h4 asm("r1");
      h4 = (w->s).flags;
      asm("" : "+r"(h4));
      g4 = 0xEF;
      g4 &= h4;
    }
    (w->s).flags = g4;
    {
      register s32 v asm("r1");
      v = 1;
      v &= wv;
      *((u8*)w + 0x4c) = v;
      {
        register u8* oa asm("r3");
        register s32 sh asm("r1");
        register s32 ov asm("r2");
        register s32 m11 asm("r0");
        oa = (u8*)w + 0x4a;
        sh = v << 4;
        ov = *oa;
        m11 = 0x11;
        m11 = -m11;
        m11 &= ov;
        m11 |= sh;
        *oa = m11;
      }
    }
  }
  {
    register s32 dv asm("r0");
    if (((w->s).flags & 0x10) != 0) {
      dv = 0x80 << 3;
    } else {
      dv = 0xFFFFFC00;
    }
    (w->s).d.x = dv;
  }
  {
    register s32 gy asm("r3");
    register s32 cy asm("r1");
    register s32 d asm("r2");
    gy = FUN_08009f6c((w->s).coord.x, (w->s).coord.y);
    cy = (w->s).coord.y;
    d = gy - cy;
    if (d < 0) {
      goto neg;
    }
    {
      register s32 lim2 asm("r0");
      lim2 = 0xf0 << 4;
      if (d > lim2) {
        goto die;
      }
      goto ok;
    }
  neg:
    {
      register s32 lim asm("r0");
      cy -= gy;
      lim = 0xf0 << 4;
      if (cy <= lim) {
        goto ok;
      }
    }
  die:
    {
      register u8 g5 asm("r0");
      register u8 h5 asm("r1");
      register s32 z5 asm("r2");
      h5 = (w->s).flags;
      asm("" : "+r"(h5));
      g5 = 0xFE;
      g5 &= h5;
      z5 = 0;
      h5 = 0xFD;
      g5 &= h5;
      (w->s).flags = g5;
      {
        u8* a = (u8*)w + 0x8c;
        *(s32*)a = z5;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = z5;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z5;
      }
    }
    (w->s).flags &= 0xFB;
    {
      u32 tbl2 = (u32)gWeaponFnTable;
      EntityFunc** rt2 = (EntityFunc**)((((w->s).id) << 2) + tbl2);
      register u32 three asm("r1");
      three = 3;
      *(u32*)((w->s).mode) = three;
      (w->s).onUpdate = (void*)((*rt2)[3]);
    }
    return;
  ok:
    (w->s).coord.y = gy;
  }
  (w->s).work[2] = 0xff;
  {
    register void* f asm("r1");
    register u8* b asm("r0");
    f = (void*)onCollision;
    b = (u8*)w + 0x74;
    *(void**)(b + 0x24) = f;
  }
  SmashElec_Update(w);
}


// 0x0803CA44
void SmashElec_Update(struct Weapon* p) {
  UpdateMotionGraphic(&p->s);
  if ((p->s).work[1] == 0) {
    s32 y;
    s32 cy;
    s32 d;
    (p->s).work[2]--;
    (p->s).coord.x += (p->s).d.x;
    y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    cy = (p->s).coord.y;
    d = y - cy;
    if (d >= 0) {
      if (d > 0xF00) {
        goto die;
      }
    } else {
      if (cy - y > 0xF00) {
        goto die;
      }
    }
    (p->s).coord.y = y;
    if ((u8)--(p->s).work[2] != 0xFF) {
      goto cam;
    }
  }
die:
  SET_WEAPON_ROUTINE(p, 2);
  SmashElec_Die(p);
  return;
cam:
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x3000) {
    SET_WEAPON_ROUTINE(p, 2);
    SmashElec_Die(p);
  }
}

void SmashElec_Die(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (z->unk_13a != 0) z->unk_13a--;
  {
    u8 f = ~DISPLAY & (w->s).flags;
    s32 z0 = 0;
    (w->s).flags = f;
    (w->body).status = z0;
    (w->body).prevStatus = z0;
    (w->body).invincibleTime = z0;
  }
  (w->s).flags &= ~COLLIDABLE;
  SET_WEAPON_ROUTINE(w, ENTITY_EXIT);
}

void SmashElec_Disappear(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (z->unk_13a != 0) z->unk_13a--;
  (w->s).flags &= ~DISPLAY;
  DeleteWeapon(w);
}

// 0x0803cb64
static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    struct Entity* self = (struct Entity*)body->parent;
    if (gMission.weaponCount[WEAPON_SABER] < 0xFFFF) {
      gMission.weaponCount[WEAPON_SABER]++;
    }
    self->work[1] = 1;
  }
}
