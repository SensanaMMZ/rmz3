#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "entity/macros.h"
#include "motion.h"
#include "script.h"

void OmegaGoldSword_Init(struct Enemy* p);
void OmegaGoldSword_Update(struct Enemy* p);
void OmegaGoldSword_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gOmegaGoldSwordRoutine = {
    [ENTITY_INIT] =      OmegaGoldSword_Init,
    [ENTITY_UPDATE] =    OmegaGoldSword_Update,
    [ENTITY_DIE] =       OmegaGoldSword_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Enemy* CreateOmegaGoldSword(struct Coord* c, u8 r1, struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_OMEGA_GOLD_SWORD);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = r1;
    (p->s).unk_28 = e;
  }
  return p;
}

static const EnemyFunc sDeads[2];

static const struct Collision sCollisions[6];
void nop_0808c384(struct Enemy* p);
void OmegaGoldSword_Update(struct Enemy* p);

// 0x0808B7FC
void OmegaGoldSword_Init(struct Enemy* p) {
  s32 z;
  s32 one;
  s32 one2;
  struct Body* body;
  InitNonAffineMotion(&p->s);
  z = 0;
  (p->s).flags &= 0xEF;
  one2 = 1;
  asm("" : "+r"(one2));
  one = 1;
  ((p->s).spr).xflip = z;
  {
    u8* oa = (u8*)p + 0x4a;
    s32 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    *oa = m11;
  }
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fv = (p->s).flags;
    fv |= one2;
    fl = FLIPABLE;
    fv |= fl;
    fl = COLLIDABLE;
    fv |= fl;
    (p->s).flags = fv;
  }
  body = &p->body;
  InitBody(body, sCollisions, &(p->s).coord, 1);
  body->parent = (struct CollidableEntity*)p;
  body->fn = (void*)nop_0808c384;
  {
    struct Coord* d = &(p->s).d;
    d->y = z;
  }
  (p->s).d.x = z;
  {
    u32 tbl = (u32)gEnemyFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
  }
  (p->s).mode[1] = z;
  (p->s).mode[2] = z;
  (p->s).mode[3] = z;
  *((u8*)p + 0x49) |= 0xC;
  *(s32*)((u8*)p + 0xb4) = -0x1300;
  *(s32*)((u8*)p + 0xb8) = -0x3A00;
  *((u8*)p + 0xc0) = z;
  (p->s).flags2 |= WHITE_PAINTABLE;
  (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
  OmegaGoldSword_Update(p);
}

extern const EnemyFunc sUpdates1[5];
extern const EnemyFunc sUpdates2[5];

void OmegaGoldSword_Update(struct Enemy* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    *(u8*)((u8*)p + 0x49) |= 0xc;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    OmegaGoldSword_Die(p);
  } else {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

void OmegaGoldSword_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

static const struct Coord Coord_ARRAY_08368e54[4];
static const motion_t motion_t_ARRAY_08368e74[12];
static const struct Coord Coord_ARRAY_08368e8c[4];
static const motion_t motion_t_ARRAY_08368eac[12];

struct VFX* FUN_080c1cf4(struct Coord* c, u8 a1, u16 a2, u16 a3);

// Scratch-parity basin: retail schedules the spilled &c init between the rng
// pointer and the loop counters, rotating every later scratch pick one register
// forward (movs r1/#0, movs r2/#3, ldr r1 pool). Structure, homes, spill slot,
// and both spawn loops stream-match at 22 bytes of register parity.
NON_MATCH void FUN_0808b938(struct Enemy* p) {
#if MODERN
  struct Coord c;
  struct Coord c2;
  u8 m2 = (p->s).mode[2];
  switch (m2) {
    case 0: {
      (p->body).status = m2;
      (p->body).prevStatus = m2;
      (p->body).invincibleTime = m2;
      (p->s).flags &= ~4;
      (p->s).d.x = m2;
      (p->s).d.y = m2;
      (p->s).work[2] = 0x78;
      if ((u32)(MOTION_VALUE(p) - MOTION(0x65, 6)) < 2) {
        register u32* rng asm("r10") = ({ u32* r_ = &RNG_0202f388; asm volatile("" : "+r"(r_) : "r"(&c)); r_; });
        register u32 j asm("r9") = 0;
        const struct Coord* cp = Coord_ARRAY_08368e54;
        register s32 i asm("r8") = 3;
        const motion_t* t = motion_t_ARRAY_08368e74;
        do {
          u32 a = *rng;
          u32 v = (a * 0x343FD + 0x269EC3) << 1;
          u32 k;
          const u8* mb;
          *rng = v >> 1;
          k = (v >> 0x11) & 3;
          asm volatile("" :: "r"(k));
          c.x = (p->s).coord.x + cp->x;
          c.y = (p->s).coord.y + cp->y + 0x4000;
          FUN_080c1cf4(&c, k, 0, t[0]);
          asm volatile("add %0, #2" : "=r"(mb) : "0"((const u8*)motion_t_ARRAY_08368e74));
          FUN_080c1cf4(&c, k, 0, *(const motion_t*)(mb + j));
          FUN_080c1cf4(&c, k, 0, t[2]);
          t += 3;
          j += 6;
          cp++;
          i--;
        } while (i >= 0);
      } else {
        struct Coord* pc = &c2;
        u32 j = 0;
        const struct Coord* cp = Coord_ARRAY_08368e8c;
        s32 i = 3;
        const motion_t* t = motion_t_ARRAY_08368eac;
        for (; i >= 0; i--) {
          u32 a = RNG_0202f388;
          u32 v = (a * 0x343FD + 0x269EC3) << 1;
          u32 k;
          const u8* mb;
          RNG_0202f388 = v >> 1;
          k = (v >> 0x11) & 3;
          asm volatile("" :: "r"(k));
          c2.x = (p->s).coord.x + cp->x;
          pc->y = (p->s).coord.y + cp->y + 0x4000;
          FUN_080c1cf4(pc, k, 1, t[0]);
          asm volatile("add %0, #2" : "=r"(mb) : "0"((const u8*)motion_t_ARRAY_08368eac));
          FUN_080c1cf4(pc, k, 1, *(const motion_t*)(mb + j));
          FUN_080c1cf4(pc, k, 1, t[2]);
          t += 3;
          j += 6;
          cp++;
        }
      }
      if (MOTION_VALUE(p) == MOTION(0x65, 1)) {
        (p->s).flags &= ~DISPLAY;
        (p->s).mode[2] = 2;
      } else {
        SetMotion(&p->s, MOTION(0x65, 5));
        UpdateMotionGraphic(&p->s);
        (p->s).flags &= ~DISPLAY;
        (p->s).mode[2]++;
      }
      break;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      s32 t = (p->s).work[2];
      if (t != 0) {
        t--;
        (p->s).work[2] = t;
        if ((t << 24) == 0) {
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 3: {
      s32 z = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z;
      break;
    }
  }
#else
  INCCODE("asm/enemy/omega_gold_sword_93a8.inc");
#endif
}

void FUN_0808bb58(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).flags &= ~DISPLAY;
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
  }
}

bool8 FUN_0808bb84(struct Enemy* p) { return TRUE; }

void FUN_0808bb88(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      SetMotion(&p->s, MOTION(0x65, 0));
      (p->s).coord.y = ((struct Enemy*)(p->s).unk_28)->s.coord.y - 0x4000;
      (p->s).coord.x = ((struct Enemy*)(p->s).unk_28)->s.coord.x;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if (((struct Enemy*)(p->s).unk_28)->s.scriptEntity->flags & 1) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_0808bbe4(struct Enemy* p) { return TRUE; }

static const struct Coord Coord_ARRAY_08368ec4[6];
void FUN_080c1c94(struct Coord* c, u32 k, u16 m);

// Giant sword drop-in + 6x3 shard burst. Logic verified; matches except the
// position of one reload-generated `mov r9, sp` (retail emits it right after
// the RNG base staging, agbcc after the coord-table/counter inits) - pure
// reload placement, not reachable from source (18 shapes tried).
NON_MATCH void FUN_0808bbe8(struct Enemy* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= DISPLAY;
      SetMotion(&p->s, MOTION(0x65, 0x00));
      {
        struct Entity* q = (p->s).unk_28;
        (p->s).coord.y = q->coord.y - 0x4000;
        (p->s).coord.x = q->coord.x;
      }
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    case 2: {
      s32 i;
      const struct Coord* co;
      struct Coord c;
      SetMotion(&p->s, MOTION(0x65, 0x01));
      PlaySound(0x41);
      co = Coord_ARRAY_08368ec4;
      i = 5;
      do {
        u8 k = RANDOM(RNG_0202f388) & 3;
        c.x = (p->s).coord.x + co->x;
        c.y = (p->s).coord.y + co->y + 0x4000;
        FUN_080c1c94(&c, k, MOTION(0x65, 0x0E));
        FUN_080c1c94(&c, k, MOTION(0x65, 0x0F));
        FUN_080c1c94(&c, k, MOTION(0x65, 0x10));
        co += 1;
        i -= 1;
      } while (i >= 0);
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
    }
  }
#else
  INCCODE("asm/enemy/omega_gold_sword_bbe8.inc");
#endif
}

bool8 FUN_0808bd00(struct Enemy* p) {
  if (((p->s).unk_28)->mode[1] == 6) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

void FUN_0808bd1c(struct Enemy* p) {
  struct Entity* owner;

  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
      SetMotion(&p->s, MOTION(0x65, 1));
      SET_XFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      owner = (p->s).unk_28;
      (p->s).coord.y = owner->coord.y - 0x4000;
      (p->s).coord.x = owner->coord.x;
      UpdateMotionGraphic(&p->s);
      break;
  }
}

bool8 FUN_0808bd8c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/omega_gold_sword_p3_p2.inc");

bool8 FUN_0808c330(struct Enemy* p) { return TRUE; }

void FUN_0808c334(struct Enemy* p) {
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

void nop_0808c384(struct Enemy* p) {}


// --------------------------------------------

bool8 FUN_0808bb84(struct Enemy* p);
bool8 FUN_0808bbe4(struct Enemy* p);
bool8 FUN_0808bd00(struct Enemy* p);
bool8 FUN_0808bd8c(struct Enemy* p);
bool8 FUN_0808c330(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[5] = {
    (EnemyFunc)FUN_0808bb84,
    (EnemyFunc)FUN_0808bbe4,
    (EnemyFunc)FUN_0808bd00,
    (EnemyFunc)FUN_0808bd8c,
    (EnemyFunc)FUN_0808c330,
};
// clang-format on

void FUN_0808bb88(struct Enemy* p);
void FUN_0808bbe8(struct Enemy* p);
void FUN_0808bd1c(struct Enemy* p);
void FUN_0808bd90(struct Enemy* p);
void FUN_0808c334(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[5] = {
    FUN_0808bb88,
    FUN_0808bbe8,
    FUN_0808bd1c,
    FUN_0808bd90,
    FUN_0808c334,
};
// clang-format on

// --------------------------------------------

void FUN_0808b938(struct Enemy* p);
void FUN_0808bb58(struct Enemy* p);

static const EnemyFunc sDeads[2] = {
    FUN_0808b938,
    FUN_0808bb58,
};

// --------------------------------------------

static const struct Collision sCollisions[6] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(65), PIXEL(24), PIXEL(43)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(5), -PIXEL(50), PIXEL(44), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(39), PIXEL(43), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(16), PIXEL(14), PIXEL(98)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(39), PIXEL(39), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(16), PIXEL(10), PIXEL(98)},
    },
};

static const struct Coord Coord_ARRAY_08368e54[4] = {
    {PIXEL(0), -PIXEL(107)},
    {PIXEL(0), -PIXEL(76)},
    {PIXEL(0), -PIXEL(48)},
    {PIXEL(0), -PIXEL(24)},
};

// clang-format off
static const motion_t motion_t_ARRAY_08368e74[12] = {
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0C),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0D),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0D),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x08),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x09),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0A),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0B),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x08),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x09),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0B),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0A),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x08),
};
// clang-format on

static const struct Coord Coord_ARRAY_08368e8c[4] = {
    {-PIXEL(23), -PIXEL(110)},
    {-PIXEL(2), -PIXEL(91)},
    {PIXEL(16), -PIXEL(73)},
    {PIXEL(34), -PIXEL(53)},
};

// clang-format off
static const motion_t motion_t_ARRAY_08368eac[12] = {
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0C),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0D),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0D),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x08),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x09),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0A),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0B),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x08),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x09),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0B),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x0A),
    MOTION(SM101_OMEGA_WHITE_SWORD, 0x08),
};
// clang-format on

// clang-format off
static const struct Coord Coord_ARRAY_08368ec4[6] = {
    {PIXEL(0), -PIXEL(89)},
    {PIXEL(12), -PIXEL(75)},
    {PIXEL(27), -PIXEL(61)},
    {PIXEL(41), -PIXEL(47)},
    {PIXEL(30), -PIXEL(38)},
    {PIXEL(35), -PIXEL(76)},
};
// clang-format on
