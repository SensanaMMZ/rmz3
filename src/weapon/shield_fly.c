#include "collision.h"
#include "global.h"
#include "mission.h"
#include "weapon.h"

#define PROP (w->props.common)

static const u8 sElements[4];
static const motion_t sShieldFlyMotions[3][4];
static const WeaponFunc sShieldFlyUpdates[5];
extern const u8 u8_ARRAY_08361334[4];

bool32 shield_0803a5fc(struct Weapon* w);
static void onHit(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

static void ShieldFly_Init(struct Weapon* w);
static void ShieldFly_Update(struct Weapon* w);
static void ShieldFly_Die(struct Weapon* w);

void MenuExit_ShieldFly(struct Weapon* w) {
  struct WeaponProps* b4 = &PROP;
  struct Zero* z;
  struct Zero_b4* zb4;
  z = b4->z;
  zb4 = &z->unk_b4;
  if (z->elfMotion != 0) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    EXIT_BODY(w);
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }
  if ((zb4->status).element == b4->props[1][1]) {
    if (!(z->unk_136 & (1 << WEAPON_SHIELD))) {
      return;
    }
  }
  (w->s).flags &= ~DISPLAY;
  (w->s).flags &= ~FLIPABLE;
  EXIT_BODY(w);
  SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
}

struct Weapon* CreateWeaponShieldFly(struct Zero* z, u8 r1) {
  struct Weapon* w;

  KillAllWeapons(DeleteSaber);
  w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    u8 element;

    if ((z->unk_b4).mainCopy == WEAPON_SHIELD) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SHIELD_FLY);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
      element = sElements[((&z->unk_b4)->status).element];
      SetWeaponElement(0, element);

    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SHIELD_FLY);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
      element = sElements[((&z->unk_b4)->status).element];
      SetWeaponElement(1, element);
    }

    (&PROP)->z = z;
    (w->s).work[0] = z->unk_127;
    (w->s).work[1] = r1;
    (&PROP)->props[1][1] = ((&z->unk_b4)->status).element;
  }
  return w;
}

static void ShieldFly_Init(struct Weapon* w) {
  struct WeaponProps* b4;
  SET_WEAPON_ROUTINE(w, ENTITY_UPDATE);
  InitNonAffineMotion(&w->s);
  ResetDynamicMotion(&w->s);
  (w->s).flags |= DISPLAY;
  (w->s).flags |= FLIPABLE;
  SetMotion(&w->s, sShieldFlyMotions[(w->s).work[1]][(w->s).work[0]]);
  PlaySound(SE_CHARGE_SHIELD_VOICE);
  b4 = &PROP;
  b4->props[1][2] = 1;
  ShieldFly_Update(w);
}

static void ShieldFly_Update(struct Weapon* w) {
  struct WeaponProps* b4 = &PROP;
  struct Zero* z = b4->z;
  if (z->elfMotion != 0) {
    SET_WEAPON_ROUTINE(w, ENTITY_DIE);
    return;
  }
  if (((z->body).status & BODY_STATUS_DEAD) || ((z->body).hp == 0)) {
    SET_WEAPON_ROUTINE(w, ENTITY_DIE);
    return;
  }
  if ((b4->props[1][2] != 0) && ((w->body).status & BODY_STATUS_BLOCKED)) {
    PlaySound(SE_BLOCKED);
    b4->props[1][2] = 0;
  }

  {
    struct Zero_b4* b4 = &z->unk_b4;
    if ((b4->status).mainWeapon == WEAPON_SHIELD) {
      (z->restriction).mainCharge = TRUE;
    } else {
      (z->restriction).subCharge = TRUE;
    }
  }
  (sShieldFlyUpdates[(w->s).mode[1]])(w);
  UpdateMotionGraphic(&w->s);

  if (((w->s).mode[1] == 2) && shield_0803a5fc(w)) {
    SET_WEAPON_ROUTINE(w, ENTITY_DIE);
  }
}

static void ShieldFly_Die(struct Weapon* w) {
  (w->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(w, ENTITY_EXIT);
}

static void onHit(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if ((body->hitboxFlags & BODY_STATUS_B2) && (gMission.weaponCount[WEAPON_SHIELD] < 0xFFFF)) {
    gMission.weaponCount[WEAPON_SHIELD]++;
  }
}

// 0x08039D3C
void shield_08039d3c(struct Weapon* w) {
  struct Zero* z = (&PROP)->z;
  register u8 v asm("r2");
  u8 c;
  v = z->unk_127;
  c = v;
  if (c == 0xff) {
    register u8 g asm("r0");
    register u8 h asm("r1");
    register s32 zr asm("r2");
    u8* a;
    h = (w->s).flags;
    asm("" : "+r"(h));
    g = 0xFE;
    g &= h;
    zr = 0;
    h = 0xFD;
    g &= h;
    (w->s).flags = g;
    a = (u8*)w + 0x8c;
    *(s32*)a = zr;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *(s32*)a = zr;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *a = zr;
    (w->s).flags &= ~4;
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }
  if ((w->s).work[0] != c) {
    (w->s).work[0] = v;
    GotoMotion(&w->s, sShieldFlyMotions[(w->s).work[1]][(w->s).work[0]], (w->s).motion.cmdIdx, (w->s).motion.duration);
  }
  (w->s).coord.x = (z->s).coord.x;
  (w->s).coord.y = (z->s).coord.y;
  SET_XFLIP(w, ((z->s).flags >> 4) & 1);
  if ((w->s).motion.state == 3) {
    (w->s).mode[1] = u8_ARRAY_08361334[(w->s).work[1]];
    (w->s).mode[2] = 0;
  }
}

INCASM("asm/weapon/shield_fly_a.inc");

s32 FUN_0803a574(s32 x, s32 y) {
  u16 angle;
  s32 tmp;
  while (TRUE) {
    if (abs(x) < 0x8000) {
      if (abs(y) < 0x8000) {
        break;
      }
    }

    tmp = x;
    if (tmp < 0) {
      tmp += 0xF;
    }
    x = (tmp >> 4);

    tmp = y;
    if (tmp < 0) {
      tmp += 0xF;
    }
    y = (tmp >> 4);
  }

  angle = ArcTan2(x, y);
  return (((s32)(angle) + 0x80) >> 8) & 0xFF;
}

// 0x0803A5C8: a verbatim copy of FUN_080e964c (math.c)
u32 FUN_0803a5c8(u32 a, s32 b, s32 c) {
  s32 diff = a - b;
  if ((u32)((diff + c) & 0xFF) <= (u32)(c << 1)) {
    b = a;
  } else {
    s32 masked = diff & 0xFF;
    s32 dir = -1;
    if (masked <= 0x7F) {
      dir = 1;
    }
    b += c * dir;
    b &= 0xFF;
  }
  return b;
}

// 0x0803A5FC
bool32 shield_0803a5fc(struct Weapon* p) {
  register struct Zero* z asm("ip");
  register const struct Rect* tbl asm("r2");
  register u8* q asm("r3");
  s32 dx;
  register s32 dy asm("r1");
  register s32 rv asm("r1");
  s32 cv;
  register struct Zero* za asm("r4");
  register struct Zero* zb asm("r3");
  u32 lim;
  register u32 k asm("r2");
  register u32 k2 asm("r3");
  u32 t;
  s32 a;
  s32 b;
  z = *(struct Zero**)((u8*)p + 0xb4);
  if (((z->s).flags & 0x10) != 0) {
    tbl = gZeroRanges;
    asm("" : "+r"(tbl));
    q = (u8*)z + 0x147;
    rv = tbl[*q].x;
    za = z;
    asm("" : "+r"(za));
    cv = (za->s).coord.x;
    dx = cv - rv;
  } else {
    tbl = gZeroRanges;
    asm("" : "+r"(tbl));
    q = (u8*)z + 0x147;
    rv = tbl[*q].x;
    za = z;
    asm("" : "+r"(za));
    cv = (za->s).coord.x;
    dx = cv + rv;
  }
  rv = tbl[*q].y;
  zb = z;
  asm("" : "+r"(zb));
  cv = (zb->s).coord.y;
  dy = cv + rv;
  dx -= (p->s).coord.x;
  dy -= (p->s).coord.y;
  k = 0x1000;
  asm("" : "+r"(k));
  t = dx + k;
  lim = 0x2000;
  if (t > lim) {
    return 0;
  }
  k2 = 0x1000;
  asm("" : "+r"(k2));
  t = dy + k2;
  if (t > lim) {
    return 0;
  }
  a = dx;
  a *= dx;
  b = dy;
  b *= dy;
  if (a + b > 0x1000000) {
    return 0;
  }
  return 1;
}

static const motion_t sShieldFlyMotions[3][4] = {
    {
        MOTION(0x6D, 0x00),
        MOTION(0x70, 0x00),
        MOTION(0x72, 0x00),
        MOTION(0x74, 0x00),
    },
    {
        MOTION(0x6D, 0x03),
        MOTION(0x70, 0x01),
        MOTION(0x72, 0x01),
        MOTION(0x74, 0x01),
    },
    {
        MOTION(0x6D, 0x03),
        MOTION(0x70, 0x01),
        MOTION(0x72, 0x01),
        MOTION(0x74, 0x01),
    },
};

static const u8 sElements[4] = {0, 1, 2, 3};
const u8 u8_ARRAY_08361288[4] = {5, 8, 11, 0};

const s16 s16_ARRAY_0836128c[8] = {
    0x1C00, -0x1300, 0x1A00, -0x1500, 0x1800, -0x1400, 0x1A00, -0x1000,
};

const s16 s16_ARRAY_0836129c[8] = {
    0x1C00, -0x1200, 0x1C00, -0x1500, 0x1600, -0x1400, 0x1B00, -0x0F00,
};

const struct Collision Collision_ARRAY_083612ac[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_UNK3,
      nature : (BODY_NATURE_CUT | ELEMENT_ENCHANTABLE),
      comboLv : 1,
      remaining : 1,
      layer : 0x00010000,
      range : {PIXEL(0), PIXEL(0), PIXEL(38), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(38), PIXEL(16)},
    },
};

const struct Collision Collision_ARRAY_083612dc[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_UNK3,
      nature : (BODY_NATURE_CUT | ELEMENT_ENCHANTABLE),
      comboLv : 1,
      remaining : 1,
      layer : 0x00010000,
      range : {PIXEL(0), PIXEL(0), PIXEL(34), PIXEL(34)},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(34), PIXEL(34)},
    },
};

// --------------------------------------------

void shield_08039d3c(struct Weapon* w);
void shield_08039e28(struct Weapon* w);
void shield_08039ffc(struct Weapon* w);
void shield_0803a108(struct Weapon* w);
void shield_0803a3b4(struct Weapon* w);

// clang-format off
static const WeaponFunc sShieldFlyUpdates[5] = {
    shield_08039d3c,
    shield_08039e28,
    shield_08039ffc,
    shield_0803a108,
    shield_0803a3b4,
};
// clang-format on

// --------------------------------------------

// clang-format off
const WeaponRoutine gShieldFlyRoutine = {
    [ENTITY_INIT] =      ShieldFly_Init,
    [ENTITY_UPDATE] =    ShieldFly_Update,
    [ENTITY_DIE] =       ShieldFly_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

const u8 u8_ARRAY_08361334[4] = {1, 3, 4, 0};

#undef PROP
