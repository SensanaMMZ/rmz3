#include "collision.h"
#include "global.h"
#include "mission.h"
#include "weapon.h"

// ザンエイダン

// props (56bytes, offset: 0xB4..)
struct ThrowBladeProps {
  struct Weapon* saber;
  u8 unk_b8[8];
  u8 element;
  u8 unk_c1[43];
};

static const struct Collision sNormalCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 6,
      atkType : ATK_UNK11,
      nature : BODY_NATURE_CUT,
      comboLv : 1,
      remaining : 1,
      layer : 0x00000040,
      range : {PIXEL(7), PIXEL(1), PIXEL(27), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(7), PIXEL(1), PIXEL(27), PIXEL(17)},
    },
};

static const struct Collision sIceCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 6,
      atkType : ATK_UNK11,
      nature : BODY_NATURE_CUT,
      comboLv : 1,
      remaining : 1,
      layer : 0x00000040,
      range : {PIXEL(10), PIXEL(1), PIXEL(35), PIXEL(23)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(10), PIXEL(1), PIXEL(35), PIXEL(23)},
    },
};

// --------------------------------------------

void ThrowBlade_Init(struct Weapon* w);
void ThrowBlade_Update(struct Weapon* w);
void ThrowBlade_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gThrowBladeRoutine = {
    [ENTITY_INIT] =      (WeaponFunc)ThrowBlade_Init,
    [ENTITY_UPDATE] =    (WeaponFunc)ThrowBlade_Update,
    [ENTITY_DIE] =       (WeaponFunc)ThrowBlade_Die,
    [ENTITY_DISAPPEAR] = (WeaponFunc)DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

void MenuExit_ThrowBlade(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  struct ThrowBladeProps* s = (struct ThrowBladeProps*)w->props.raw;
  if ((s->element != ((&z->unk_b4)->status).element)) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

struct Weapon* CreateThrowBlade(struct Zero* z, struct Weapon* saber, bool8 isIce) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    struct ThrowBladeProps* s;

    if ((z->unk_b4).mainCopy == WEAPON_SABER) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_ZANEIDAN);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
      if (isIce) {
        const u8 element = ((&z->unk_b4)->status).element;
        SetWeaponElement(0, element);
      }
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_ZANEIDAN);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
      if (isIce) {
        const u8 element = ((&z->unk_b4)->status).element;
        SetWeaponElement(1, element);
      }
    }
    (w->s).unk_28 = &z->s;
    s = (struct ThrowBladeProps*)w->props.raw;
    s->saber = saber;
    s->element = ((&z->unk_b4)->status).element;
    (w->s).work[0] = isIce;
    (w->s).work[1] = 0;
  }
  return w;
}

void zsaber_0803c0f4(struct Body* body);
void ThrowBlade_Update(struct Weapon* w);

// 0x0803BED0
void ThrowBlade_Init(struct Weapon* p) {
  register struct Entity* src asm("sb");
  register s32 zero asm("sl");
  register s32 w0 asm("r8");
  u8 atk;
  register struct Body* b asm("r4");
  register struct Zero* z asm("r4");
  src = (struct Entity*)((struct ThrowBladeProps*)(p->props).raw)->saber;
  z = (struct Zero*)(p->s).unk_28;
  SET_WEAPON_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register u8 f2 asm("r1");
    register s32 g asm("r0");
    register s32 zr asm("r1");
    f2 = (p->s).flags2;
    g = 0xfb;
    g &= f2;
    zr = 0;
    zero = zr;
    (p->s).flags2 = g;
  }
  {
    register s32 z0 asm("r0");
    z0 = 0;
    *(u16*)((u8*)p + 0x20) = zero;
    *((u8*)p + 0x22) = z0;
  }
  {
    register s32 g2 asm("r0");
    register s32 k asm("r1");
    register s32 z5 asm("r5");
    g2 = (p->s).flags;
    asm("" : "+r"(g2));
    k = 1;
    z5 = 0;
    g2 |= k;
    k = 2;
    g2 |= k;
    (p->s).flags = g2;
    asm("" ::"l"(z5));
  }
  w0 = (p->s).work[0];
  if (w0 != 0) {
    register const struct Collision* col asm("r5");
    SetMotion(&p->s, 0x1e);
    ForceEntityPalette(&p->s, 1);
    (p->s).work[2] = 0x40;
    atk = CalcSaberBonus(z) + 6;
    {
      register s32 g3 asm("r0");
      register s32 k3 asm("r1");
      g3 = (p->s).flags;
      asm("" : "+r"(g3));
      k3 = 4;
      g3 |= k3;
      (p->s).flags = g3;
    }
    b = &p->body;
    col = (const struct Collision*)0x08361660;
    ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(b, col, &(p->s).coord, 1);
    b->parent = (struct CollidableEntity*)p;
    b->fn = (BodyFunc)zero;
    InitWeaponBody(b, col, atk, 3, 0x12, -1);
  } else {
    register const struct Collision* col2 asm("r5");
    SetMotion(&p->s, 0x1d);
    (p->s).work[2] = 0xd;
    atk = CalcSaberBonus(z) + 6;
    {
      register s32 g4 asm("r0");
      register s32 k4 asm("r1");
      g4 = (p->s).flags;
      asm("" : "+r"(g4));
      k4 = 4;
      g4 |= k4;
      (p->s).flags = g4;
    }
    b = &p->body;
    col2 = (const struct Collision*)0x08361630;
    ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(b, col2, &(p->s).coord, 1);
    b->parent = (struct CollidableEntity*)p;
    b->fn = (BodyFunc)w0;
    InitWeaponBody(b, col2, atk, 0, -1, -1);
  }
  {
    register s32 xf asm("r2");
    register s32 one asm("r0");
    {
      register struct Entity* sp1 asm("r1");
      register s32 fv asm("r0");
      sp1 = src;
      fv = sp1->flags;
      xf = (u32)fv >> 4;
    }
    one = 1;
    xf &= one;
    if (xf != 0) {
      register s32 g5 asm("r1");
      register s32 k5 asm("r0");
      g5 = (p->s).flags;
      asm("" : "+r"(g5));
      k5 = 0x10;
      k5 |= g5;
      (p->s).flags = k5;
    } else {
      register u8 h asm("r1");
      register u8 g6 asm("r0");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g6 = 0xEF;
      g6 &= h;
      (p->s).flags = g6;
    }
    {
      register s32 xv asm("r1");
      register u8* oa asm("r3");
      s32 sh4, ov, m11;
      xv = xf;
      *((u8*)p + 0x4c) = xv;
      oa = (u8*)p + 0x4a;
      sh4 = xv << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh4;
    }
  }
  {
    register s32 dv asm("r0");
    if (((p->s).flags & 0x10) != 0) {
      register struct Entity* s1 asm("r1");
      register s32 k asm("r1");
      s1 = src;
      dv = s1->coord.x;
      k = 0x98 << 6;
      dv += k;
      (p->s).coord.x = dv;
      dv = 0xc0 << 3;
    } else {
      register struct Entity* s2 asm("r1");
      register s32 k2 asm("r1");
      s2 = src;
      dv = s2->coord.x;
      k2 = -0x2600;
      dv += k2;
      (p->s).coord.x = dv;
      dv = -0x600;
    }
    (p->s).d.x = dv;
  }
  {
    register struct Entity* s3 asm("r1");
    register s32 k3 asm("r1");
    register s32 cy asm("r0");
    s3 = src;
    cy = s3->coord.y;
    k3 = -0x1400;
    cy += k3;
    (p->s).coord.y = cy;
  }
  b->fn = (BodyFunc)zsaber_0803c0f4;
  ThrowBlade_Update(p);
}


void ThrowBlade_Update(struct Weapon* w) {
  UpdateMotionGraphic(&w->s);
  if ((w->body).status & 0x1000) {
    PlaySound(0x2B);
  }
  if (--(w->s).work[2] != 0) {
    (w->s).coord.x += (w->s).d.x;
  } else {
    SET_WEAPON_ROUTINE(w, ENTITY_DIE);
    ThrowBlade_Die(w);
  }
}

void ThrowBlade_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

void zsaber_0803c0f4(struct Body* body) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    if (gMission.weaponCount[WEAPON_SABER] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_SABER]++;
    }
  }
}
