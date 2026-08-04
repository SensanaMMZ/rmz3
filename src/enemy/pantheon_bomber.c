#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "mod.h"
#include "story.h"

static const struct Collision sCollisions[5];
static const struct Coord sElementCoord;

struct Enemy* CreatePantheonBomber(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_BOMBER);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

void PantheonBomber_Update(struct Enemy* p);
void FUN_0808665c(struct Body* body, struct Coord* c);

void PantheonBomber_Init(struct Enemy* p) {
  InitNonAffineMotion(&p->s);
  {
    register u8 f0 asm("r1") = (p->s).flags;
    register u8 d asm("r0") = DISPLAY;
    register s32 z asm("r3");
    s32 f;
    z = 0;
    asm("" : "+r"(z));
    f = d | f0;
    f |= FLIPABLE;
    f |= z;
    (p->s).flags = f;
  }
  if (MOD_ENABLED(gSystemSavedataManager.mods, 91) && !FLAG(gCurStory.s.gameflags, DEMO_PLAY)) {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 12);
    body->parent = (void*)p;
    body->fn = NULL;
  } else {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 8);
    body->parent = (void*)p;
    body->fn = NULL;
  }
  {
    struct Body* body = &p->body;
    body->fn = (void*)FUN_0808665c;
  }
  *(u32*)&p->props[0] = (p->s).coord.x;
  {
    s32 cx = (p->s).coord.x;
    s32 cy = (p->s).coord.y;
    (p->s).d.x = cx;
    (p->s).d.y = cy;
  }
  p->props[4] = 0;
  *(u32*)&p->props[8] = 0;
  p->props[5] = 0;
  (p->s).coord.x -= PIXEL(8);
  (p->s).coord.y += PIXEL(8);
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(0x69, 0x03));
    UpdateMotionGraphic(&p->s);
  }
  p->props[6] = 0;
  PantheonBomber_Update(p);
}

extern const EnemyFunc sUpdates1[6];
extern const EnemyFunc sUpdates2[6];
bool8 pBomber_08086628(struct Enemy* p);
void PantheonBomber_Die(struct Enemy* p);

void PantheonBomber_Update(struct Enemy* p) {
  u32 dead = (p->body).status & BODY_STATUS_DEAD;
  struct Entity** slot;
  if (dead) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    PantheonBomber_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  pBomber_08086628(p);
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (*slot == NULL) {
    if (IsFrozen(&p->s)) {
      return;
    }
    if (*slot == NULL) {
      goto dispatch2;
    }
  }
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[1]);
    *slot = (struct Entity*)dead;
  } else {
    SetDDP(&p->body, &sCollisions[2]);
  }
  return;

dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/pantheon_bomber_p1_p2_b.inc");

bool8 nop_08086338(struct Enemy* p) { return TRUE; }

void pantheon_bomber_0808633c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      GotoMotion(&p->s, MOTION(0x69, 4), 2, 1);
      SetDDP(&p->body, &sCollisions[0]);
      p->props[5] = 0;
      (p->s).work[2] = 0x30;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 nop_080863a0(struct Enemy* p) { return TRUE; }

void pantheon_bomber_080863a4(struct Enemy* p) {
  u8 md = (p->s).mode[2];
  switch (md) {
    case 0:
      SetMotion(&p->s, MOTION(0x69, 0x04));
      p->props[5] = md;
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((*(u32*)&(p->s).motion.step & 0x00FFFF00) == 0x10200) {
        SetDDP(&p->body, sCollisions);
      }
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 nop_08086414(struct Enemy* p) { return TRUE; }

struct Projectile* createPantheonBomb(struct Coord* a, struct Coord* b, u8 n);

// 0x08086418
void pantheon_bomber_08086418(struct Enemy* p) {
  register s32 w asm("r0");
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x6903);
      *((u8*)p + 0xb9) = 0;
      SetDDP(&p->body, (const struct Collision*)0x08368534);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      {
        register s32 m asm("r0");
        register s32 k asm("r1");
        m = *(s32*)((u8*)p + 0x70);
        k = 0x00FFFF00;
        m &= k;
        k = 0x81 << 9;
        if (m == k) {
          SetDDP(&p->body, (const struct Collision*)0x0836854C);
        }
      }
    state3:
      if (*((u8*)p + 0x73) != 3) {
        break;
      }
      goto tramp;
    case 2:
      SetMotion(&p->s, 0xd2 << 7);
      *((u8*)p + 0xb9) = 1;
      w = 0x10;
      goto setw;
    case 4:
      SetMotion(&p->s, 0x6905);
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5: {
      struct Coord c;
      UpdateMotionGraphic(&p->s);
      if ((s8)*((u8*)p + 0x71) != 3) {
        goto state3;
      }
      if ((p->s).work[2] != 0) {
        goto state3;
      }
      c.x = (p->s).coord.x + -0x800;
      c.y = (p->s).coord.y + -0xE00;
      createPantheonBomb(&c, &c, RANDOM(RNG_0202f388) & 1);
      (p->s).work[2] = 1;
      goto state3;
    }
    case 6:
      w = 0x12;
      goto setw;
    case 8:
      if ((RANDOM(RNG_0202f388) & 1) != 0) {
        SetMotion(&p->s, 0x6901);
      } else {
        SetMotion(&p->s, 0x6902);
      }
      w = 0x40;
    setw:
      (p->s).work[2] = w;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
    case 7:
    case 9:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
    tramp:
      (p->s).mode[2]++;
      break;
    case 10: {
      register s32 z asm("r1");
      z = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z;
      break;
    }
  }
}


bool8 nop_080865d0(struct Enemy* p) { return TRUE; }

void FUN_080865d4(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}

bool8 nop_080865f8(struct Enemy* p) { return TRUE; }


void nop_080865fc(struct Enemy* p) {}

bool8 nop_08086600(struct Enemy* p) { return TRUE; }


void FUN_08086604(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}

bool8 pBomber_08086628(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xbc);
  if (*slot == NULL && ((p->body).status & 1)) {
    *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
  }
  return TRUE;
}

void FUN_0808665c(struct Body* body, struct Coord* c) {
  const struct Collision* col = (body->enemy)->processing;
  if (col->atkType == 3 || col->atkType == 0xe || col->atkType == 0xf) {
    struct Enemy* self = (struct Enemy*)body->parent;
    if ((self->body).status & 0x200) {
      if ((self->s).coord.x < c->x) {
        *(u8*)((u8*)self + 0xba) = 0xff;
      } else {
        *(u8*)((u8*)self + 0xba) = 0xfe;
      }
    }
  }
}

void PantheonBomber_Init(struct Enemy* p);
void PantheonBomber_Update(struct Enemy* p);
void PantheonBomber_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonBomberRoutine = {
    [ENTITY_INIT] =      PantheonBomber_Init,
    [ENTITY_UPDATE] =    PantheonBomber_Update,
    [ENTITY_DIE] =       PantheonBomber_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_08086338(struct Enemy* p);
bool8 nop_080863a0(struct Enemy* p);
bool8 nop_08086414(struct Enemy* p);
bool8 nop_080865d0(struct Enemy* p);
bool8 nop_080865f8(struct Enemy* p);
bool8 nop_08086600(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)nop_08086338,
    (EnemyFunc)nop_080863a0,
    (EnemyFunc)nop_08086414,
    (EnemyFunc)nop_080865d0,
    (EnemyFunc)nop_080865f8,
    (EnemyFunc)nop_08086600,
};
// clang-format on

void pantheon_bomber_0808633c(struct Enemy* p);
void pantheon_bomber_080863a4(struct Enemy* p);
void pantheon_bomber_08086418(struct Enemy* p);
void FUN_080865d4(struct Enemy* p);
void nop_080865fc(struct Enemy* p);
void FUN_08086604(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    pantheon_bomber_0808633c,
    pantheon_bomber_080863a4,
    pantheon_bomber_08086418,
    FUN_080865d4,
    nop_080865fc,
    FUN_08086604,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
