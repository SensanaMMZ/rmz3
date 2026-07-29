#include "collision.h"
#include "global.h"
#include "weapon.h"

#define PROP (w->props.common)

static const struct Collision sCollisions[2];
static const motion_t sMotions[8];

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 10,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 1,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
};

void ReflectLaser_Init(struct Weapon* w);
void ReflectLaser_Update(struct Weapon* w);
void ReflectLaser_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gReflectLaserRoutine = {
    [ENTITY_INIT] =      ReflectLaser_Init,
    [ENTITY_UPDATE] =    ReflectLaser_Update,
    [ENTITY_DIE] =       ReflectLaser_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

void MenuExit_ReflectLaser(struct Weapon* p) {
  struct Zero* z = (struct Zero*)(p->s).unk_28;
  if (((&z->unk_b4)->status).element != 0) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_WEAPON_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (z->unk_136 & (1 << WEAPON_BUSTER)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_WEAPON_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateReflectLaser(struct Zero* z, struct Entity* p, u8 n) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_BUSTER) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_REFLECT_LASER);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_REFLECT_LASER);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
    }
    (w->s).unk_28 = &z->s;
    (&PROP)->z = (struct Zero*)p;
    (w->s).work[0] = n;
    (w->s).work[1] = 0;
  }
  return w;
}

NAKED static struct Weapon* unused_CreateReflectLaser(struct Zero* z, struct Entity* p, void* r2, u8 r3, u8 r4) { INCCODE("asm/unused/unused_CreateReflectLaser.inc"); }

void ReflectLaser_Init(struct Weapon* w) {
  register struct Entity* pz asm("r8");
  register struct Entity* zz asm("sl");
  register s32 zb asm("r9");
  struct ReflectLaser_b4* pr = &w->props.reflect;
  pz = pr->q;
  zz = (w->s).unk_28;
  SET_WEAPON_ROUTINE(w, ENTITY_UPDATE);
  InitNonAffineMotion(&w->s);
  ResetDynamicMotion(&w->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    register s32 z4 asm("r4");
    f0 = (w->s).flags;
    d0 = DISPLAY;
    asm("" : "+r"(d0));
    z4 = 0;
    d0 |= f0;
    {
      register s32 c2 asm("r1");
      c2 = FLIPABLE;
      d0 |= c2;
    }
    (w->s).flags = d0;
    asm volatile("" :: "r"(z4));
  }
  {
    const motion_t* tbl = sMotions;
    SetMotion(&w->s, tbl[(w->s).work[0]]);
  }
  {
    register u8 f1 asm("r1");
    register s32 m0 asm("r0");
    f1 = (w->s).flags;
    m0 = 0xEF;
    m0 &= f1;
    zb = 0;
    (w->s).flags = m0;
  }
  {
    register s32 v1 asm("r1");
    u8* a = (u8*)w + 0x4c;
    asm("" : "+r"(a));
    asm("" : "+r"(zb));
    v1 = zb;
    *a = v1;
  }
  {
    u8* a = (u8*)w + 0x4a;
    register u8 b asm("r1");
    s32 msk;
    b = *a;
    msk = -0x11;
    msk &= b;
    *a = msk;
  }
  if ((((u32)(w->s).work[0] % 3) << 24) == 0) {
    (w->s).flags |= COLLIDABLE;
    {
      struct Body* body = &w->body;
      const struct Collision* col = sCollisions;
      InitBody(body, col, &(w->s).coord, 1);
      body->parent = (struct CollidableEntity*)w;
      body->fn = (BodyFunc)zb;
      InitWeaponBody(body, col, (u8)(CalcBusterBonus((struct Zero*)zz) + 10), -1, -1, -1);
    }
  }
  {
    register struct Entity* e0 asm("r1");
    e0 = pz;
    pr->c_b8.x = e0->coord.x;
    pr->c_b8.y = e0->coord.y;
  }
  (w->s).work[2] = 0;
  {
    u8 wk = (w->s).work[0];
    if (wk <= 5) {
      struct Entity* e1 = (w->s).unk_28;
      register s32 m1 asm("r0");
      m1 = 1;
      m1 &= wk;
      if (m1) {
        CreateReflectLaser((struct Zero*)e1, (struct Entity*)w, (u8)(wk + 1));
      } else {
        CreateReflectLaser((struct Zero*)e1, pz, (u8)(wk + 1));
      }
    }
  }
  ReflectLaser_Update(w);
}


void ReflectLaser_Update(struct Weapon* w) {
  struct ReflectLaser_b4* b4 = &(w->props).reflect;
  struct Entity* q = b4->q;
  if (q->mode[0] >= ENTITY_DIE) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }

  UpdateMotionGraphic(&w->s);
  if ((w->s).work[0] & 1) {
    (w->s).coord.x = (b4->c_b8).x;
    (w->s).coord.y = (b4->c_b8).y;
  } else {
    (w->s).coord.x = (q->coord).x + (((b4->c_b8).x - (q->coord).x) >> 1);
    (w->s).coord.y = (q->coord).y + (((b4->c_b8).y - (q->coord).y) >> 1);
  }
  ((&(w->props).reflect)->c_b8).x = (q->coord).x;
  ((&(w->props).reflect)->c_b8).y = (q->coord).y;
}

void ReflectLaser_Die(struct Weapon* w) {
  EXIT_BODY(w);
  (w->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(w, ENTITY_EXIT);
}

// clang-format off
static const motion_t sMotions[8] = {
    MOTION(DM080_SEMI_BUSTER, 0x00),
    MOTION(DM080_SEMI_BUSTER, 0x00),
    MOTION(DM080_SEMI_BUSTER, 0x00),
    MOTION(DM080_SEMI_BUSTER, 0x01),
    MOTION(DM080_SEMI_BUSTER, 0x01),
    MOTION(DM080_SEMI_BUSTER, 0x02),
    MOTION(DM080_SEMI_BUSTER, 0x02),
    MOTION(DM080_SEMI_BUSTER, 0x02),
};
// clang-format on

#undef PROP
