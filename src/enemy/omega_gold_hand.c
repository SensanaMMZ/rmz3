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

INCASM("asm/enemy/omega_gold_hand_p1_pre_p2.inc");

void OmegaGoldHand_Die(struct Enemy* p) {
  (PTR_ARRAY_08368218[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/omega_gold_hand_p1_post.inc");

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

INCASM("asm/enemy/omega_gold_hand_p2_b.inc");

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

INCASM("asm/enemy/omega_gold_hand_p6_p2.inc");

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

void FUN_08083eb0(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_083681a0[6] = {
    (EnemyFunc)FUN_080846fc,
    (EnemyFunc)FUN_080846fc,
    FUN_08083eb0,
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
