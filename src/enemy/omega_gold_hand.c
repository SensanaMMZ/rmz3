#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "script.h"

static const struct Collision sCollisions[7];

void OmegaGoldHand_Init(struct Enemy* p);
void OmegaGoldHand_Update(struct Enemy* p);
void OmegaGoldHand_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gOmegaGoldHandRoutine = {
    [ENTITY_INIT] =      OmegaGoldHand_Init,
    [ENTITY_UPDATE] =    OmegaGoldHand_Update,
    [ENTITY_DIE] =       OmegaGoldHand_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* FUN_08082b58(struct Coord* c, bool8 isLeftHand, struct Boss* omega) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_OMEGA_GOLD_HAND);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = isLeftHand;
    (p->s).work[1] = 0;
    (p->s).unk_28 = &omega->s;
  }
  return p;
}

static const EnemyFunc PTR_ARRAY_08368218[2];

struct Enemy* FUN_08082bbc(struct Entity* e, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_OMEGA_GOLD_HAND);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = mode;
    (p->s).work[1] = 1;
    (p->s).unk_28 = e;
  }
  return p;
}

void nop_08083eac(struct Enemy* p);

// 0x08082c18 -- parked (dual-zero basin): retail keeps TWO independent
// zero registers in one extended basic block (r6: angle + else-arm body
// zeros, r7: xflip + d pair + if-arm mode zeros) with two separate
// movs #0; every C shape (two vars, barriers, pins, staged inits)
// either unifies them into one register or materializes the second as
// a copy of the first. Logic fully decoded and verified.
NON_MATCH void OmegaGoldHand_Init(struct Enemy* p) {
#if MODERN
  s32 z6, z7;
  register s32 one8 asm("r8");
  struct Body* bd;
  InitScalerotMotion1(&p->s);
  z6 = 0;
  (p->s).angle = z6;
  {
    register u32 f1 asm("r1");
    register s32 t0 asm("r0");
    f1 = (p->s).flags;
    t0 = 0xEF;
    t0 &= f1;
    z7 = 0;
    asm("" : "+r"(z7) : "r"(t0));
    (p->s).flags = t0;
  }
  {
    register s32 c2 asm("r2");
    c2 = 1;
    asm("" : "+r"(c2));
    one8 = 1;
    (p->s).spr.xflip = z7;
    {
      u8* oa = (u8*)p + 0x4a;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      *oa = m11;
    }
    {
      u32 fl2 = (p->s).flags;
      fl2 |= c2;
      fl2 |= 2;
      fl2 |= 4;
      (p->s).flags = fl2;
    }
  }
  bd = &p->body;
  InitBody(bd, &sCollisions[0], &(p->s).coord, 1);
  bd->parent = (struct CollidableEntity*)p;
  bd->fn = (void*)nop_08083eac;
  {
    u8* a = (u8*)p + 0x5c;
    *(s32*)(a + 4) = z7;
    (p->s).d.x = z7;
  }
  if ((p->s).work[1] == 0) {
    u32 tbl = (u32)(gEnemyFnTable);
    u32 id;
    EntityFunc** rt;
    id = ((p->s).id) << 2;
    rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = one8;
    (p->s).onUpdate = (void*)(*rt)[1];
    (p->s).mode[1] = z7;
    (p->s).mode[2] = z7;
    (p->s).mode[3] = z7;
  } else {
    u32 tbl;
    u32 id;
    EntityFunc** rt;
    {
      u8* a2 = (u8*)p + 0x8c;
      *(u32*)a2 = z6;
      asm("" : "+r"(a2));
      a2 += 4;
      *(u32*)a2 = z6;
      asm("" : "+r"(a2));
      a2 += 4;
      asm("" : "+r"(a2));
      *a2 = z6;
    }
    (p->s).flags &= 0xFB;
    *((u8*)p + 0xc1) = z6;
    tbl = (u32)(gEnemyFnTable);
    id = ((p->s).id) << 2;
    rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = one8;
    (p->s).onUpdate = (void*)(*rt)[1];
    {
      s32 m2 = 2;
      asm("" : "+r"(m2));
      (p->s).mode[1] = m2;
    }
    (p->s).mode[2] = z6;
    (p->s).mode[3] = z6;
  }
  if ((p->s).work[0] == 0) {
    {
      u8* pr = (u8*)p + 0x49;
      *pr |= 0xC;
    }
    {
      u8* a1 = (u8*)p + 0xb4;
      *(s32*)a1 = -0x1300;
      asm("" : "+r"(a1));
      a1 += 4;
      *(s32*)a1 = -0x3A00;
      asm("" : "+r"(a1));
      a1 += 8;
      asm("" : "+r"(a1));
      *a1 = 1;
    }
  } else {
    u8* a2 = (u8*)p + 0x25;
    *a2 = 0x17;
    asm("" : "+r"(a2));
    a2 += 0x8F;
    *(s32*)a2 = 0x1500;
    asm("" : "+r"(a2));
    a2 += 4;
    asm("" : "+r"(a2));
    *(s32*)a2 = -0x3800;
    {
      s32 z2 = 0;
      (p->s).flags &= 0xDF;
      *((u8*)p + 0x4d) = z2;
      {
        u8* oa = (u8*)p + 0x4a;
        s32 ov = *oa;
        s32 m21 = -0x21;
        m21 &= ov;
        *oa = m21;
      }
    }
  }
  (p->s).flags2 |= 0x10;
  (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
  OmegaGoldHand_Update(p);
#else
  INCCODE("asm/enemy/omega_gold_hand_init.inc");
#endif
}

extern const EnemyFunc PTR_ARRAY_08368188[6];
extern const EnemyFunc PTR_ARRAY_083681a0[6];
extern const EnemyFunc PTR_ARRAY_083681b8[6];
extern const EnemyFunc PTR_ARRAY_083681d0[6];
extern const EnemyFunc PTR_ARRAY_083681e8[6];
extern const EnemyFunc PTR_ARRAY_08368200[6];
void OmegaGoldHand_Die(struct Enemy* p);

// 0x08082D70
void OmegaGoldHand_Update(struct Enemy* p) {
  if (((struct Entity*)(p->s).unk_28)->mode[0] > 1) {
    SET_ENEMY_ROUTINE(p, 2);
    OmegaGoldHand_Die(p);
    return;
  }
  if ((p->s).work[1] == 0) {
    (PTR_ARRAY_08368188[(p->s).mode[1]])(p);
  } else {
    (PTR_ARRAY_083681a0[(p->s).mode[1]])(p);
  }
  {
    register const EnemyFunc* t asm("r0");
    if ((p->s).work[0] != 0) {
      goto b;
    }
    if ((p->s).work[1] == 0) {
      t = PTR_ARRAY_083681b8;
      asm("" : "+r"(t));
    } else {
      t = PTR_ARRAY_083681e8;
      asm("" : "+r"(t) : "r"(p));
    }
    goto shared;
  b:
    if ((p->s).work[1] != 0) {
      goto c;
    }
    t = PTR_ARRAY_083681d0;
  shared:
    (t[(p->s).mode[1]])(p);
    return;
  c:
    (PTR_ARRAY_08368200[(p->s).mode[1]])(p);
  }
}

void OmegaGoldHand_Die(struct Enemy* p) {
  (PTR_ARRAY_08368218[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/omega_gold_hand_p1_post_a.inc");

void FUN_08083258(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).flags &= ~DISPLAY;
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
  }
}

bool8 FUN_08083284(struct Enemy* p) { return TRUE; }

void FUN_08083288(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
      SetMotion(&p->s, 0x900);
      SET_XFLIP(p, FALSE);
      SET_YFLIP(p, FALSE);
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + ((p->s).unk_28)->coord.y;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + ((p->s).unk_28)->coord.x;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if (((p->s).unk_28)->scriptEntity->flags & 1) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

void FUN_08083328(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
      SetMotion(&p->s, MOTION(SM009_OMEGA_HAND, 1));
      SET_XFLIP(p, FALSE);
      SET_YFLIP(p, FALSE);
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + ((p->s).unk_28)->coord.y;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + ((p->s).unk_28)->coord.x;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if (((p->s).unk_28)->scriptEntity->flags & 1) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_080833c8(struct Enemy* p) { return TRUE; }

void FUN_080833cc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      // fallthrough
    case 1:
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

void FUN_080833ec(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      // fallthrough
    case 1:
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_0808340c(struct Enemy* p) {
  if (((struct Entity*)(p->s).unk_28)->mode[1] == 5) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

INCASM("asm/enemy/omega_gold_hand_p3_post_a.inc");

void FUN_080834fc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
      SetMotion(&p->s, 0x901);
      SET_XFLIP(p, FALSE);
      SET_YFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 wob;
      (p->s).work[2] += 2;
      wob = gSineTable[(p->s).work[2]] << 1;
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + ((p->s).unk_28)->coord.y + wob;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + ((p->s).unk_28)->coord.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 FUN_080835b4(struct Enemy* p) { return TRUE; }

void FUN_080835b8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, 0);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_080835fc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, 0);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

bool8 FUN_08083640(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/omega_gold_hand_p5.inc");

bool8 FUN_08083e14(struct Enemy* p) { return TRUE; }

void FUN_08083e18(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      EXIT_BODY(p);
      (p->s).d.x = 0;
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x40) {
        (p->s).d.y = 0x40;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_08083e68(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, 0);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void nop_08083eac(struct Enemy* p) {}

bool8 FUN_08083eb0(struct Enemy* p) {
  (p->props)[0xd] = 1;
  (p->s).mode[1] = 4;
  (p->s).mode[2] = 0;
  return TRUE;
}

void FUN_08083ec4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(SM009_OMEGA_HAND, 0));
      SET_XFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 0;
      (p->props)[0xd] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 wob;
      (p->s).work[2] += 2;
      wob = gSineTable[(p->s).work[2]];
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + ((p->s).unk_28)->coord.y + wob;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + ((p->s).unk_28)->coord.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_08083f4c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(SM009_OMEGA_HAND, 1));
      SET_XFLIP(p, FALSE);
      SET_YFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 0;
      (p->props)[0xd] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 wob;
      (p->s).work[2] += 2;
      wob = gSineTable[(p->s).work[2]] << 1;
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + ((p->s).unk_28)->coord.y + wob;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + ((p->s).unk_28)->coord.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 FUN_08083ff0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/omega_gold_hand_p7.inc");

bool8 FUN_080846fc(struct Enemy* p) { return TRUE; }

void FUN_08084700(struct Enemy* p) {}

bool8 FUN_0808340c(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_08368188[6] = {
    (EnemyFunc)FUN_08083284,
    (EnemyFunc)FUN_080833c8,
    (EnemyFunc)FUN_0808340c,
    (EnemyFunc)FUN_080835b4,
    (EnemyFunc)FUN_08083640,
    (EnemyFunc)FUN_08083e14,
};
// clang-format on

bool8 FUN_08083eb0(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_083681a0[6] = {
    (EnemyFunc)FUN_080846fc,
    (EnemyFunc)FUN_080846fc,
    (EnemyFunc)FUN_08083eb0,
    (EnemyFunc)FUN_080846fc,
    (EnemyFunc)FUN_08083ff0,
    (EnemyFunc)FUN_080846fc,
};
// clang-format on

void FUN_08083288(struct Enemy* p);
void FUN_080833cc(struct Enemy* p);
void FUN_08083428(struct Enemy* p);
void FUN_080835b8(struct Enemy* p);
void FUN_08083644(struct Enemy* p);
void FUN_08083e18(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_083681b8[6] = {
    FUN_08083288,
    FUN_080833cc,
    FUN_08083428,
    FUN_080835b8,
    FUN_08083644,
    FUN_08083e18,
};
// clang-format on

void FUN_08083328(struct Enemy* p);
void FUN_080833ec(struct Enemy* p);
void FUN_080834fc(struct Enemy* p);
void FUN_080835fc(struct Enemy* p);
void FUN_08083a04(struct Enemy* p);
void FUN_08083e68(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_083681d0[6] = {
    FUN_08083328,
    FUN_080833ec,
    FUN_080834fc,
    FUN_080835fc,
    FUN_08083a04,
    FUN_08083e68,
};
// clang-format on

void FUN_08083ec4(struct Enemy* p);
void FUN_08083ff4(struct Enemy* p);
void FUN_08084700(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_083681e8[6] = {
    FUN_08084700,
    FUN_08084700,
    FUN_08083ec4,
    FUN_08084700,
    FUN_08083ff4,
    FUN_08084700,
};
// clang-format on

void FUN_08083f4c(struct Enemy* p);
void FUN_08084348(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_08368200[6] = {
    FUN_08084700,
    FUN_08084700,
    FUN_08083f4c,
    FUN_08084700,
    FUN_08084348,
    FUN_08084700,
};
// clang-format on

void FUN_08082e38(struct Enemy* p);
void FUN_08083258(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08368218[2] = {
    FUN_08082e38,
    FUN_08083258,
};

// --------------------------------------------

static const struct Collision sCollisions[7] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(1), PIXEL(24), PIXEL(43)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(1), PIXEL(22), PIXEL(41)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(1), PIXEL(24), PIXEL(43)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(1), PIXEL(22), PIXEL(41)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(1), PIXEL(24), PIXEL(43)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(4), PIXEL(2), PIXEL(30), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(4), PIXEL(2), PIXEL(32), PIXEL(42)},
    },
};
