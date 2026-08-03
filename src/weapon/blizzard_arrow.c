#include "collision.h"
#include "global.h"
#include "mission.h"
#include "weapon.h"

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 4,
      atkType : 7,
      element : ELEMENT_ICE,
      comboLv : 1,
      remaining : 1,
      layer : 0x00000010,
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

void BlizzardArrow_Init(struct Weapon* w);
void BlizzardArrow_Update(struct Weapon* w);
void BlizzardArrow_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gBlizzardArrowRoutine = {
    [ENTITY_INIT] =      BlizzardArrow_Init,
    [ENTITY_UPDATE] =    BlizzardArrow_Update,
    [ENTITY_DIE] =       BlizzardArrow_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

// --------------------------------------------

void MenuExit_BlizzardArrow(struct Weapon* w) {
  struct Zero* z = (struct Zero*)(w->s).unk_28;
  if (((&z->unk_b4)->status).element != ELEMENT_ICE) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }
  if (z->unk_136 & (1 << 0)) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
  }
}

#include "zero.h"
#include "entity/macros.h"

struct Weapon* CreateBlizzardArrow(struct Zero* z, struct Coord* c, u8 n, bool8 xflip) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);

  if (w != NULL) {
    if ((z->unk_b4).mainCopy == WEAPON_BUSTER) {
      INIT_WEAPON_ROUTINE(w, 10);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(w, 10);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
    }
    (w->s).unk_28 = (struct Entity*)z;
    SET_XFLIP(w, xflip);
    (w->s).coord = *c;
    (w->s).work[0] = n;
    (w->s).work[1] = 0;
  }
  return w;
}

void hitBlizzardArrow(struct Body* body);
void BlizzardArrow_Update(struct Weapon* p);

// 0x0803B8EC
void BlizzardArrow_Init(struct Weapon* p) {
  struct Zero* z = (struct Zero*)(p->s).unk_28;
  s32 z5;
  struct Body* body;
  const struct Collision* coll;
  {
    u32 tbl = (u32)gWeaponFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = 1;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    asm("" : "+r"(fl));
    fv = 1;
    fv |= fl;
    fl = 2;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0x52, 0x02));
  {
    s32 cx;
    s32 dx;
    if ((p->s).flags & X_FLIP) {
      cx = (p->s).coord.x;
      dx = 0xD00;
    } else {
      cx = (p->s).coord.x;
      dx = -0xD00;
    }
    cx += dx;
    (p->s).coord.x = cx;
  }
  {
    register const s32* tb asm("r0");
    register u32 ix asm("r1");
    s32 v;
    tb = (const s32*)0x08361624;
    asm volatile("" : "+r"(tb));
    ix = (p->s).work[0];
    ix <<= 2;
    {
      register const s32* e asm("r1");
      asm volatile("add %0, %1, %2" : "=l"(e) : "l"(ix), "l"(tb));
      v = *e;
    }
    (p->s).d.y = v;
    (p->s).unk_coord.y = -(v / 8);
  }
  z5 = 0;
  (p->s).work[3] = z5;
  (p->s).flags |= COLLIDABLE;
  body = &p->body;
  coll = (const struct Collision*)0x083615E0;
  InitBody(body, coll, &(p->s).coord, 1);
  body->parent = (struct CollidableEntity*)p;
  body->fn = (BodyFunc)z5;
  InitWeaponBody(body, coll, (u8)(CalcBusterBonus(z) + 4), -1, -1, (p->s).work[0] + 2);
  body->fn = (BodyFunc)hitBlizzardArrow;
  BlizzardArrow_Update(p);
}

INCASM("asm/weapon/blizzard_arrow_pre_b.inc");

void BlizzardArrow_Die(struct Weapon* p) {
  (p->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(p, ENTITY_EXIT);
}

void hitBlizzardArrow(struct Body* body) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    struct CollidableEntity* p = body->parent;
    if (gMission.weaponCount[WEAPON_BUSTER] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_BUSTER]++;
    }
    if (!(body->enemy->status & BODY_STATUS_DEAD) || (p->s).work[0] == 0) {
      (p->s).work[3] = 1;
    }
  }
}

// --------------------------------------------

static const s32 sBulletYCoords[3] = {0x000, -0x400, 0x400};
