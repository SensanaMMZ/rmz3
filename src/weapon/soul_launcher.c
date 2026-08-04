#include "collision.h"
#include "global.h"
#include "mission.h"
#include "weapon.h"
#include "physics.h"

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

void FUN_0803b4b0(struct Body* body);
void SoulLauncher_Update(struct Weapon* w);

// 0x0803B14C
void SoulLauncher_Init(struct Weapon* p) {
  struct Zero* z;
  register struct Body* b asm("r4");
  register const struct Collision* coll asm("r8");
  register s32 z5 asm("r5");
  z = (struct Zero*)(p->s).unk_28;
  SET_WEAPON_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register u8 fl asm("r1");
    register s32 f asm("r0");
    fl = (p->s).flags;
    f = 1;
    f |= fl;
    {
      register s32 k asm("r1");
      k = 2;
      f |= k;
    }
    (p->s).flags = f;
  }
  if ((p->s).work[1] == 1) {
    SetMotion(&p->s, 0xCE * 128);
  } else {
    SetMotion(&p->s, MOTION(0x67, 0x03));
  }
  {
    register s32 zz asm("r2");
    u8* oa;
    s32 m11, ov;
    zz = 0;
    {
      register u8 h asm("r1");
      register u8 g asm("r0");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g = 0xEF;
      g &= h;
      (p->s).flags = g;
    }
    *((u8*)p + 0x4c) = zz;
    oa = (u8*)p + 0x4a;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    *oa = m11;
  }
  {
    register s32 dx asm("r1");
    register s32 cx asm("r0");
    if (((z->s).flags & 0x10) != 0) {
      cx = (z->s).coord.x;
      dx = 0xB0 * 16;
    } else {
      cx = (z->s).coord.x;
      dx = -0xB00;
    }
    (p->s).coord.x = cx + dx;
  }
  (p->s).coord.y = (z->s).coord.y + -0x4800;
  {
    register const s32* tb asm("r1");
    tb = (const s32*)0x0836159C;
    asm("" : "+r"(tb));
    (p->s).d.x = tb[(p->s).work[0]];
  }
  (p->s).d.y = -0x700;
  z5 = 0;
  (p->s).mode[1] = 5;
  (p->s).work[2] = 0x40;
  {
    u8* a = (u8*)p + 0xb4;
    a[0xc] = z5;
  }
  {
    register u8 fl4 asm("r1");
    register s32 f4 asm("r0");
    fl4 = (p->s).flags;
    f4 = 4;
    f4 |= fl4;
    (p->s).flags = f4;
  }
  b = &p->body;
  coll = (const struct Collision*)0x08361558;
  ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(b, coll, &(p->s).coord, 1);
  b->parent = (struct CollidableEntity*)p;
  b->fn = (BodyFunc)z5;
  if ((p->s).work[1] == 0) {
    {
      register s32 bo asm("r0");
      register u32 bv asm("r2");
      bo = ((s32(*)(struct Zero*))CalcRodBonus)(z);
      bo += 8;
      bo <<= 24;
      bv = (u32)bo >> 24;
      ((void (*)(struct Body*, const struct Collision*, s32, s32, s32, s32))InitWeaponBody)(b, coll, bv, 0, -1, -1);
    }
  } else {
    {
      register s32 bo2 asm("r0");
      register u32 bv2 asm("r2");
      bo2 = ((s32(*)(struct Zero*))CalcRodBonus)(z);
      bo2 += 0xA;
      bo2 <<= 24;
      bv2 = (u32)bo2 >> 24;
      ((void (*)(struct Body*, const struct Collision*, s32, s32, s32, s32))InitWeaponBody)(b, coll, bv2, 2, -1, -1);
    }
  }
  b->fn = (BodyFunc)FUN_0803b4b0;
  SoulLauncher_Update(p);
  asm volatile("" ::"l"(z));
}


s32 FUN_0800a40c(s32 x, s32 y);
metatile_attr_t FUN_0803b4e8(s32 x, s32 y);
void SoulLauncher_Die(struct Weapon* p);

// 0x0803B298
void SoulLauncher_Update(struct Weapon* p) {
  s32 r, z2, zv;
  u16 atv;

  if (((struct SoulLauncherProps*)p->props.raw)->unk_c0 != 0) {
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
  }
  (p->s).coord.x += FUN_0800a40c((p->s).coord.x, (p->s).coord.y + 0x800);
  switch ((p->s).mode[1]) {
    case 0:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if ((u16)FUN_0803b4e8((p->s).coord.x, (p->s).coord.y) == 0) {
        break;
      }
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (r >= -0x800) {
        (p->s).coord.y += r;
      }
      if ((p->s).work[1] != 0) {
        (p->s).mode[1] = 1;
        break;
      }
      goto die;
    case 1:
      SetMotion(&p->s, 0x6701);
      (p->s).work[2] = 0x40;
      (p->s).mode[1] = 2;
      /* fallthrough */
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((u16)FUN_0803b4e8((p->s).coord.x, (p->s).coord.y + 1) == 0) {
        (p->s).coord.y += (p->s).d.y;
      }
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if ((u32)(r + 0x800) <= 0x7FF) {
        (p->s).coord.y += r;
      }
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0xFF) {
        (p->s).mode[1] = 3;
      }
      break;
    case 3:
      SetMotion(&p->s, 0x6702);
      (p->s).mode[1] = 4;
      /* fallthrough */
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((u16)FUN_0803b4e8((p->s).coord.x, (p->s).coord.y + 1) == 0) {
        (p->s).coord.y += (p->s).d.y;
        r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (r >= -0x800) {
          (p->s).coord.y += r;
        }
      }
      if ((p->s).motion.state != 3) {
        break;
      }
    die:
      SET_WEAPON_ROUTINE(p, ENTITY_DIE);
      SoulLauncher_Die(p);
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.y += (p->s).d.y;
      atv = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
      if (atv != 0) {
        zv = (u16)(atv & 0x8000);
        if (zv == 0) {
          r = PushoutToDown1((p->s).coord.x, (p->s).coord.y);
          if (r < -(p->s).d.y) {
            (p->s).coord.y += r;
          }
          (p->s).d.y = zv;
          (p->s).mode[1] = zv;
          break;
        }
      }
      (p->s).work[2]--;
      z2 = 0;
      if ((u8)(p->s).work[2] == 0xFF) {
        (p->s).d.y = z2;
        (p->s).mode[1] = z2;
      }
      break;
  }
}

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
