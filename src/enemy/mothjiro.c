#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "story.h"
#include "syssav.h"

static const struct Collision sCollisions[3];

void Mothjiro_Init(struct Enemy* p);
void Mothjiro_Update(struct Enemy* p);
void Mothjiro_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gMothjiroRoutine = {
    [ENTITY_INIT] =      Mothjiro_Init,
    [ENTITY_UPDATE] =    Mothjiro_Update,
    [ENTITY_DIE] =       Mothjiro_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Enemy* CreateMothjiro(struct Coord* c, u8 r1) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_MOTHJIRO);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = r1;
  }
  return p;
}

static const struct Collision sCollisions[3];
void FUN_08088b0c(struct Body* body, struct Coord* c);

// 0x08087bfc -- parked (dead-zero basin): retail ORs a zero register into
// the init flags (orrs r2, r3 with r3=0) and copies the DISPLAY constant
// before the first or; agbcc folds both in every arrangement (8 insns
// short). Mod-flag easy-HP branch, waypoint seeds, and double body.fn
// store fully decoded.
NON_MATCH void Mothjiro_Init(struct Enemy* p) {
#if MODERN
  u8 z2;
  u8 f;
  s32 z = 0;
  InitNonAffineMotion(&p->s);
  f = (p->s).flags;
  f = DISPLAY | f;
  f |= FLIPABLE;
  f |= z;
  (p->s).flags = f;
  if (gSystemSavedataManager.mods[14] & 0x10) {
    z2 = gCurStory.s.gameflags[0] & 0x40;
    if (z2 == 0) {
      f |= COLLIDABLE;
      (p->s).flags = f;
      InitBody(&p->body, &sCollisions[1], &(p->s).coord, 10);
      goto after;
    }
  }
  z2 = 0;
  (p->s).flags |= COLLIDABLE;
  InitBody(&p->body, &sCollisions[1], &(p->s).coord, 6);
after:
  (p->body).parent = (struct CollidableEntity*)p;
  (p->body).fn = (void*)(u32)z2;
  (p->body).fn = (void*)FUN_08088b0c;
  (p->s).unk_coord.x = (p->s).coord.x;
  (p->s).unk_coord.y = (p->s).coord.y;
  {
    s32 x = (p->s).coord.x;
    s32 y = (p->s).coord.y;
    (p->s).d.x = x;
    (p->s).d.y = y;
  }
  *(s32*)((u8*)p + 0xc0) = 0;
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.x - 0x4000;
  *(s32*)((u8*)p + 0xbc) = (p->s).coord.y - 0x5000;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(0x6B, 0x00));
    UpdateMotionGraphic(&p->s);
  }
  (p->s).work[1] = 0;
  Mothjiro_Update(p);
#else
  INCCODE("asm/enemy/mothjiro_init.inc");
#endif
}

extern const EnemyFunc sUpdates1[7];
extern const EnemyFunc sUpdates2[7];
bool8 mothjiro_08088a74(struct Enemy* p);
void Mothjiro_Die(struct Enemy* p);

void Mothjiro_Update(struct Enemy* p) {
  u32 dead = (p->body).status & BODY_STATUS_DEAD;
  struct Entity** slot;
  if (dead) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Mothjiro_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  mothjiro_08088a74(p);
  slot = (struct Entity**)((u8*)p + 0xc0);
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
  }
  return;

dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/mothjiro_p1_b.inc");

bool8 nop_080881d8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/mothjiro_p2.inc");

bool8 nop_080884a0(struct Enemy* p) { return TRUE; }

struct VFX* FUN_080c2f3c(struct Coord* c, u8 mode);
s32 FUN_08088ae0(struct Enemy* p);

void mothjiro_080884a4(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      SetMotion(&p->s, 0x6B00);
      {
        s32 dx = *(s32*)((u8*)p + 0xb8) - (p->s).coord.x;
        s32 dy, q1, q2, sq1, sq2, dist;
        (p->s).d.x = dx;
        dy = *(s32*)((u8*)p + 0xbc) - (p->s).coord.y;
        (p->s).d.y = dy;
        q1 = dx >> 2;
        sq1 = q1;
        sq1 = sq1 * q1;
        q2 = dy >> 2;
        sq2 = q2;
        sq2 = sq2 * q2;
        dist = (u16)Sqrt(sq1 + sq2) << 2;
        if (dist != 0) {
          (p->s).d.x = ((p->s).d.x << 8) / dist;
          (p->s).d.y = ((p->s).d.y << 8) / dist;
        }
        (p->s).d.x = ((p->s).d.x << 9) >> 8;
        (p->s).d.y = ((p->s).d.y << 9) >> 8;
        if ((p->s).d.x > 0) {
          s32 o = 1;
          (p->s).flags |= 0x10;
          (p->s).spr.xflip = o;
          {
            u8* oa = (u8*)p + 0x4a;
            s32 c16 = 0x10;
            s32 ov, m11;
            asm("" : "+r"(c16));
            ov = *oa;
            m11 = -0x11;
            m11 &= ov;
            *oa = m11 | c16;
          }
        } else {
          (p->s).flags &= 0xEF;
          (p->s).spr.xflip = m;
          {
            u8* oa = (u8*)p + 0x4a;
            s32 ov = *oa;
            s32 m11 = -0x11;
            m11 &= ov;
            *oa = m11;
          }
        }
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((u8)(++(p->s).mode[3]) % 0xC == 0) {
        FUN_080c2f3c(&(p->s).coord, ((p->s).flags >> 4) & 1);
      }
      {
        s32 t = *(s32*)((u8*)p + 0xb8);
        s32 cx = (p->s).coord.x;
        s32 d = t - cx;
        if (d <= 0) {
          d = cx - t;
        }
        if (d <= 0x4FFF) {
          s32 t2 = *(s32*)((u8*)p + 0xbc);
          s32 cy = (p->s).coord.y;
          s32 d2 = t2 - cy;
          if (d2 <= 0) {
            d2 = cy - t2;
          }
          if (d2 <= 0x17FF) {
            (p->s).mode[1] = 2;
            (p->s).mode[2] = 0;
          }
        }
      }
      {
        s32 r = FUN_08088ae0(p);
        if (r == 0) {
          (p->s).mode[1] = 3;
          (p->s).mode[2] = r;
        }
      }
      break;
    }
  }
}

bool8 nop_080885f8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/mothjiro_p4.inc");

bool8 nop_0808889c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/mothjiro_p5.inc");

bool8 nop_08088a1c(struct Enemy* p) { return TRUE; }

void mothjiro_08088a20(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}

bool8 nop_08088a44(struct Enemy* p) { return TRUE; }


void nop_08088a48(struct Enemy* p) {}

bool8 nop_08088a4c(struct Enemy* p) { return TRUE; }


void mothjiro_08088a50(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

bool8 mothjiro_08088a74(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xc0);

  if (*slot == NULL && ((p->body).status & 1)) {
    *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
    if (*slot != NULL) {
      u8 attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        SetDDP(&p->body, &sCollisions[2]);
      } else if (attr == 0x30) {
        SetDDP(&p->body, &sCollisions[2]);
      }
    }
  }
  return TRUE;
}

struct Coord* FUN_08012a64(struct Coord* c);

s32 FUN_08088ae0(struct Enemy* p) {
  struct Coord* r = FUN_08012a64(&(p->s).coord);
  if (r != NULL) {
    *(s32*)((u8*)p + 0xb8) = r->x;
    *(s32*)((u8*)p + 0xbc) = r->y;
    return TRUE;
  }
  return FALSE;
}

void FUN_08088b0c(struct Body* body, struct Coord* c) {
  u8 atkType = (body->enemy->processing)->atkType;
  if (atkType == 3 || atkType == 0xe || atkType == 0xf) {
    struct Enemy* self = (struct Enemy*)body->parent;
    if (*(u32*)((u8*)self + 0x8c) & 0x200) {
      if ((self->s).coord.x < c->x) {
        *(u8*)((u8*)self + 0x11) = 0xff;
      } else {
        *(u8*)((u8*)self + 0x11) = 0xfe;
      }
    }
  }
}

// --------------------------------------------

bool8 nop_080881d8(struct Enemy* p);
bool8 nop_080884a0(struct Enemy* p);
bool8 nop_080885f8(struct Enemy* p);
bool8 nop_0808889c(struct Enemy* p);
bool8 nop_08088a1c(struct Enemy* p);
bool8 nop_08088a44(struct Enemy* p);
bool8 nop_08088a4c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    (EnemyFunc)nop_080881d8,
    (EnemyFunc)nop_080884a0,
    (EnemyFunc)nop_080885f8,
    (EnemyFunc)nop_0808889c,
    (EnemyFunc)nop_08088a1c,
    (EnemyFunc)nop_08088a44,
    (EnemyFunc)nop_08088a4c,
};
// clang-format on

void mothjiro_080881dc(struct Enemy* p);
void mothjiro_080884a4(struct Enemy* p);
void mothjiro_080885fc(struct Enemy* p);
void mothjiro_080888a0(struct Enemy* p);
void mothjiro_08088a20(struct Enemy* p);
void nop_08088a48(struct Enemy* p);
void mothjiro_08088a50(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    mothjiro_080881dc,
    mothjiro_080884a4,
    mothjiro_080885fc,
    mothjiro_080888a0,
    mothjiro_08088a20,
    nop_08088a48,
    mothjiro_08088a50,
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
      range : {PIXEL(0), -PIXEL(5), PIXEL(26), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(26), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(5), PIXEL(26), PIXEL(20)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(4)};
