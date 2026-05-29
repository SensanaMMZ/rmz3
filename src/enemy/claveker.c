#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"

static const struct Coord sElementCoord;

static const struct Collision sCollisions[3];

void Claveker_Init(struct Enemy* p);
void Claveker_Update(struct Enemy* p);
void Claveker_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gClavekerRoutine = {
    [ENTITY_INIT] =      Claveker_Init,
    [ENTITY_UPDATE] =    Claveker_Update,
    [ENTITY_DIE] =       Claveker_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* CreateClaveker(struct Coord* c, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CLAVEKER);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

INCASM("asm/enemy/claveker_p1.inc");

bool8 FUN_0808eb20(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/claveker_p2.inc");

bool8 FUN_0808ebb0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/claveker_p3.inc");

bool8 FUN_0808effc(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/claveker_p4.inc");

bool8 FUN_0808f158(struct Enemy* p) { return TRUE; }

void FUN_0808f15c(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0808f198(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/claveker_p6_p1.inc");

void FUN_0808f19c(struct Enemy* p) {}

bool8 FUN_0808f1a0(struct Enemy* p) { return TRUE; }

void FUN_0808f1a4(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0808f1e0(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xbc);
  if (*slot == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *slot = e;
    if (e != NULL) {
      u8 attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      } else if (attr == 0x30) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 0;
      }
    }
  }
  return TRUE;
}

void FUN_0808f234(struct Body* body, struct Coord* c) {
  const struct Collision* col = (body->enemy)->processing;
  if (col->atkType == 3 || col->atkType == 0xe || col->atkType == 0xf) {
    struct Enemy* self = (struct Enemy*)body->parent;
    if ((self->body).status & 0x200) {
      if ((self->s).coord.x < c->x) {
        *(u8*)((u8*)self + 0xbb) = 0xff;
      } else {
        *(u8*)((u8*)self + 0xbb) = 0xfe;
      }
    }
  }
}

// --------------------------------------------

bool8 FUN_0808eb20(struct Enemy* p);
bool8 FUN_0808ebb0(struct Enemy* p);
bool8 FUN_0808effc(struct Enemy* p);
bool8 FUN_0808f158(struct Enemy* p);
bool8 FUN_0808f198(struct Enemy* p);
bool8 FUN_0808f1a0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)FUN_0808eb20,
    (EnemyFunc)FUN_0808ebb0,
    (EnemyFunc)FUN_0808effc,
    (EnemyFunc)FUN_0808f158,
    (EnemyFunc)FUN_0808f198,
    (EnemyFunc)FUN_0808f1a0,
};
// clang-format on

void FUN_0808eb24(struct Enemy* p);
void FUN_0808ebb4(struct Enemy* p);
void FUN_0808f000(struct Enemy* p);
void FUN_0808f15c(struct Enemy* p);
void FUN_0808f19c(struct Enemy* p);
void FUN_0808f1a4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    FUN_0808eb24,
    FUN_0808ebb4,
    FUN_0808f000,
    FUN_0808f15c,
    FUN_0808f19c,
    FUN_0808f1a4,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(12)};
