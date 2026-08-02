#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"

struct Enemy* CreateSwordy(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_SWORDY);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

static const struct Collision sCollisions[5];
void Swordy_Update(struct Enemy* p);

// 0x0807BF04
void Swordy_Init(struct Enemy* p) {
  struct Body* b;
  u32 z;
  u8 one;
  InitNonAffineMotion(&p->s);
  {
    register u8 t asm("r1");
    register u8 f asm("r0");
    t = (p->s).flags;
    f = 1;
    f |= t;
    f |= 2;
    z = 0;
    f &= 0xEF;
    (p->s).flags = f;
  }
  one = 1;
  ((p->s).spr).xflip = z;
  {
    u8* oa = (u8*)p + 0x4a;
    u8 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    *oa = m11;
  }
  (p->s).flags |= COLLIDABLE;
  b = &p->body;
  InitBody(b, sCollisions, &(p->s).coord, 4);
  b->parent = (struct CollidableEntity*)p;
  b->fn = (BodyFunc)z;
  {
    register u8* q asm("r0");
    q = (u8*)p + 0x5c;
    *(u32*)(q + 4) = z;
    (p->s).d.x = z;
    asm volatile("add %0, #0x60" : "+r"(q));
    *(u32*)q = z;
    asm volatile("sub %0, #4" : "+r"(q));
    *q = z;
    asm volatile("add %0, #8" : "+r"(q));
    *q = one;
  }
  SET_ENEMY_ROUTINE(p, 1);
  (p->s).mode[1] = z;
  (p->s).mode[2] = z;
  (p->s).mode[3] = z;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(0x3F, 0x00));
    UpdateMotionGraphic(&p->s);
  }
  Swordy_Update(p);
}

extern const EnemyFunc PTR_ARRAY_08367a38[4];
extern const EnemyFunc PTR_ARRAY_08367a48[4];
bool32 FUN_0807c530(struct Enemy* p);
void Swordy_Die(struct Enemy* p);

void Swordy_Update(struct Enemy* p) {
  struct Entity** slot;
  struct Entity* e;
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Swordy_Die(p);
    return;
  }
  (PTR_ARRAY_08367a38[(p->s).mode[1]])(p);
  FUN_0807c530(p);
  if (IsFrozen(&p->s)) {
    slot = (struct Entity**)((u8*)p + 0xbc);
    e = *slot;
    if (e != NULL) {
      return;
    }
    p->props[6] = (p->s).mode[1];
    (p->s).mode[1] = (s32)e;
    (p->s).mode[2] = (s32)e;
    if (isKilled(*slot)) {
      *slot = e;
    }
    return;
  }
  (PTR_ARRAY_08367a48[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/swordy_p1_p2_b.inc");

bool8 FUN_0807c230(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[5];

void FUN_0807c234(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      SetMotion(&p->s, 0x3F00);
      SetDDP(&p->body, sCollisions);
      if ((pZero2->s).coord.y + -0x800 > (p->s).coord.y) {
        (p->s).work[3] = 0;
      } else {
        (p->s).work[3] = 1;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 zy;
      if ((p->s).work[3] == 0) {
        s32 ny = (p->s).coord.y + 0x180;
        (p->s).coord.y = ny;
        zy = (pZero2->s).coord.y + -0x800;
        if (zy >= ny) {
          goto nosnap;
        }
        goto snap;
      } else {
        s32 ny = (p->s).coord.y + -0x180;
        (p->s).coord.y = ny;
        zy = (pZero2->s).coord.y + -0x800;
        if (zy > ny) {
        snap:
          (p->s).coord.y = zy;
          (p->s).mode[2]++;
        }
      }
    }
    nosnap:
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        if (!((p->s).flags & 0x10)) {
          u8 sh = (p->s).flags >> 4;
          u8 on = 1;
          on &= ~sh;
          SET_XFLIP(p, on);
        }
      } else {
        if ((p->s).flags & 0x10) {
          u8 sh = (p->s).flags >> 4;
          u8 on = 1;
          on &= ~sh;
          SET_XFLIP(p, on);
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2: {
      register s32 v asm("r0");
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        if (!((p->s).flags & 0x10)) {
          u8 sh = (p->s).flags >> 4;
          u8 on = 1;
          on &= ~sh;
          SET_XFLIP(p, on);
        }
        v = 0x180;
      } else {
        if ((p->s).flags & 0x10) {
          u8 sh = (p->s).flags >> 4;
          u8 on = 1;
          on &= ~sh;
          SET_XFLIP(p, on);
        }
        v = -0x180;
      }
      (p->s).d.x = v;
      (p->s).unk_coord.x = 0;
      (p->s).d.y = 0;
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t != 0) {
        t--;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    }
    case 4:
      SetMotion(&p->s, 0x3F01);
      PlaySound(0);
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5: {
      s32 d, a;
      (p->s).coord.x += (p->s).d.x;
      d = (p->s).unk_coord.x + (p->s).d.x;
      (p->s).unk_coord.x = d;
      a = d;
      if (a < 0) {
        a = -a;
      }
      if (a > 0x1E000) {
        s32 g = (p->s).d.y + 0x80;
        (p->s).d.y = g;
        (p->s).coord.y -= g;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 FUN_0807c47c(struct Enemy* p) { return TRUE; }

void FUN_0807c480(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) (p->s).mode[2] = 1;
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0807c4ac(struct Enemy* p) { return TRUE; }


void nop_0807c4b0(struct Enemy* p) {}

bool8 FUN_0807c4b4(struct Enemy* p) { return TRUE; }

void FUN_0807c4b8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + (p->s).d.y + PIXEL(16))) {
        (p->s).d.y = 0;
        (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - PIXEL(16);
      } else {
        (p->s).coord.y += (p->s).d.y;
      }
      break;
  }
  {
    struct Entity** slot = (struct Entity**)&p->props[8];
    if (isKilled(*slot)) {
      *slot = NULL;
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
  }
}

static const struct Coord sElementCoord;

bool32 FUN_0807c530(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xBC);
  struct VFX* e = *slot;
  if (e == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    struct VFX* n = ApplyElementEffect(0, &p->s, &sElementCoord);
    *slot = n;
    if (n != NULL) {
      u8 b = *((u8*)p + 0x97) & 0xF0;
      if (b == 0x10) {
        // e is provably NULL here; stored through it to keep the register
        (p->s).mode[1] = 1, (p->s).mode[2] = (u32)e;
      } else if (b == 0x30) {
        (p->s).mode[1] = 3, (p->s).mode[2] = (u32)e;
      }
    }
  }
  return TRUE;
}

void Swordy_Init(struct Enemy* p);
void Swordy_Update(struct Enemy* p);
void Swordy_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSwordyRoutine = {
    [ENTITY_INIT] =      Swordy_Init,
    [ENTITY_UPDATE] =    Swordy_Update,
    [ENTITY_DIE] =       Swordy_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_0807c230(struct Enemy* p);
bool8 FUN_0807c47c(struct Enemy* p);
bool8 FUN_0807c4ac(struct Enemy* p);
bool8 FUN_0807c4b4(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08367a38[4] = {
    (EnemyFunc)FUN_0807c230,
    (EnemyFunc)FUN_0807c47c,
    (EnemyFunc)FUN_0807c4ac,
    (EnemyFunc)FUN_0807c4b4,
};

void FUN_0807c234(struct Enemy* p);
void FUN_0807c480(struct Enemy* p);
void nop_0807c4b0(struct Enemy* p);
void FUN_0807c4b8(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08367a48[4] = {
    FUN_0807c234,
    FUN_0807c480,
    nop_0807c4b0,
    FUN_0807c4b8,
};

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(13), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(13), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(24), -PIXEL(14), PIXEL(28), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(20), PIXEL(20)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(12)};
