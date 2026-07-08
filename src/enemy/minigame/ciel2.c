#include "collision.h"
#include "enemy.h"
#include "global.h"

static void CielMinigameEnemy2_Init(struct Enemy* p);
static void CielMinigameEnemy2_Update(struct Enemy* p);
static void CielMinigameEnemy2_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gCielMinigameEnemy2Routine = {
    [ENTITY_INIT] =      CielMinigameEnemy2_Init,
    [ENTITY_UPDATE] =    CielMinigameEnemy2_Update,
    [ENTITY_DIE] =       CielMinigameEnemy2_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Enemy* FUN_0809c1cc(struct Entity* e, u8 a, u8 b) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CIEL_MG_2);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).unk_28 = e;
    (p->s).work[0] = a;
    (p->s).work[1] = b;
  }
  return p;
}

// --------------------------------------------

// Spawn one falling minigame enemy. Route to Update, set display/flippable,
// motion 0xE900, clear flip, priority 3; pick its palette from the parent
// object's per-slot table (work[0]); place it along the top by slot (x 0xD800,
// or 0xE800 for slot 3; y stepping down 0x10 px/slot) and give it a downward
// velocity (slots 0/3 also drift left). Retail expands `flags |= DISPLAY |
// FLIPABLE` into two separate bit-ORs in one RMW where agbcc-from-clean-C folds
// them to a single |3 (retail-suboptimal, as in Weapon16_Init). INCCODE for the
// byte-match.
NON_MATCH static void CielMinigameEnemy2_Init(struct Enemy* p) {
#if MODERN
  struct Entity* e = (p->s).unk_28;
  u8* tbl;

  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY | FLIPABLE;
  SetMotion(&p->s, 0xE900);
  UpdateMotionGraphic(&p->s);
  SET_XFLIP(p, 0);
  (p->s).spr.oam.priority = 3;

  tbl = (u8*)e + 0xDE0;
  (p->s).work[2] = tbl[(p->s).work[0]];
  ForceEntityPalette(&p->s, (p->s).work[2] + 5);

  (p->s).coord.x = 0xD800;
  (p->s).coord.y = (0x30 - (p->s).work[0] * 0x10) << 8;
  if ((p->s).work[0] == 3) {
    (p->s).coord.x = 0xE800;
  }
  if ((p->s).work[0] == 0 || (p->s).work[0] == 3) {
    (p->s).d.x = -0x100;
  } else {
    (p->s).d.x = 0;
  }
  *(s32*)&p->props[0] = (p->s).coord.x;
  *(s32*)&p->props[4] = (p->s).coord.y;
  (p->s).d.y = 0x100;
  CielMinigameEnemy2_Update(p);
#else
  INCCODE("asm/wip/CielMinigameEnemy2_Init.inc");
#endif
}

static void CielMinigameEnemy2_Update(struct Enemy* p) {
  struct Entity* e = (p->s).unk_28;

  switch ((p->s).mode[1]) {
    case 0:
      if (*((u8*)e + 0xE0F) <= gEnemyHeaderPtr->remaining && *((u8*)e + 0xE12) == 0) {
        u8* tbl = (u8*)e + 0xDE0;
        (p->s).work[2] = tbl[(p->s).work[0]];
        (p->s).mode[1]++;
      }
      break;
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      if ((p->s).coord.y >= *(s32*)&p->props[4] + 0x1000) {
        ForceEntityPalette(&p->s, (p->s).work[2] + 5);
        (p->s).coord.x = *(s32*)&p->props[0];
        (p->s).coord.y = *(s32*)&p->props[4];
        (p->s).mode[1] = 0;
      }
      break;
  }
  UpdateMotionGraphic(&p->s);
}

static void CielMinigameEnemy2_Die(struct Enemy* p) { SET_ENEMY_ROUTINE(p, ENTITY_EXIT); }
