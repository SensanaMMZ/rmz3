#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"
#include "mod.h"
#include "overworld_terrain.h"
#include "story.h"

struct SharksealX {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 x_b4;               // 0xB4
  u8 unk_b8[4];           // 0xB8
  u8 unk_bc;              // 0xBC
  u8 unk_bd;              // 0xBD
  u8 unk_be;              // 0xBE
  u8 unk_bf;              // 0xBF
  struct Entity* unk_c0;  // 0xC0
};
static_assert(sizeof(struct SharksealX) == sizeof(struct Enemy));

static const struct Collision sCollisions[5];

struct Enemy* CreateSharksealX(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_SHARKSEAL_X);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

void SharksealX_Update(struct Enemy* p);
void FUN_080711d8(struct Body* body, struct Coord* r1, struct Coord* r2);

// 0x08070084
void SharksealX_Init(struct SharksealX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if (FLAG(gSystemSavedataManager.mods, MOD_121) && !FLAG(gCurStory.s.gameflags, DEMO_PLAY)) {
    INIT_BODY(p, sCollisions, 10, NULL);
  } else {
    INIT_BODY(p, sCollisions, 6, NULL);
  }
  SET_BODY_INTERSECT_HANDLER(p, FUN_080711d8);

  if (gOverworld.sea > (p->s).coord.y) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  p->x_b4 = (p->s).coord.x;
  (&(p->s).d)->x = (&(p->s).d)->y = 0;
  p->unk_c0 = NULL;
  p->unk_bd = 0;
  p->x_b4 = (p->s).coord.x;
  (p->s).unk_coord.y = (p->s).coord.y;
  (&(p->s).d)->x = (&(p->s).d)->y = 0;
  p->unk_bc = 0;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(SM024_SHARKSEAL_X, 0));
    UpdateMotionGraphic(&p->s);
  }
  p->unk_bf = 0;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  SharksealX_Update((struct Enemy*)p);
}

static const EnemyFunc PTR_ARRAY_08366a04[8];
extern const EnemyFunc PTR_ARRAY_08366a24[8];
bool8 nop_080711d4(struct Enemy* p);
void sharksealx_08071030(struct Enemy* p);
void SharksealX_Die(struct Enemy* p);

// 0x080701D4
void SharksealX_Update(struct Enemy* p) {
  if ((*(u32*)((u8*)p + 0x8c) & 0x200) != 0) {
    SET_ENEMY_ROUTINE(p, 2);
    SharksealX_Die(p);
    return;
  }
  nop_080711d4(p);
  (PTR_ARRAY_08366a04[(p->s).mode[1]])(p);
  sharksealx_08071030(p);
  if ((p->s).mode[1] != 5 && (p->s).mode[1] != 7 && IsFrozen(&p->s) != 0) {
    {
      u8 mv = (p->s).mode[1];
      u8* ba = (u8*)p + 0xbe;
      *ba = mv;
    }
    return;
  }
  {
    struct Overworld* ow = &gOverworld;
    s32 sea = *(s32*)((u8*)ow + 0x2C00C);
    if (sea > (p->s).coord.y + 0x800) {
      register u8* q asm("r6");
      register s32 v asm("r5");
      s32 t;
      q = (u8*)p + 0xbd;
      v = *q;
      if (v == 0) {
        SetMotion(&p->s, MOTION(0x18, 0));
        UpdateMotionGraphic(&p->s);
        (p->s).d.y = v;
      }
      *q = 1;
      t = (p->s).d.y + 0x20;
      (p->s).d.y = t;
      if (t > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      return;
    }
  }
  {
    register u8* q2 asm("r2");
    u8 v2;
    q2 = (u8*)p + 0xbd;
    v2 = *q2;
    if (v2 == 1) {
      (p->s).mode[1] = v2;
      (p->s).mode[2] = 0;
    }
    *q2 = 0;
    (PTR_ARRAY_08366a24[(p->s).mode[1]])(p);
  }
}

INCASM("asm/enemy/sharkseal_x_p2.inc");

bool8 FUN_080707d0(struct Enemy* p) { return TRUE; }


void nop_080707d4(struct Enemy* p) {}

bool8 FUN_080707d8(struct Enemy* p) { return TRUE; }

short forceWaterLanding(struct Entity* p);

// 0x080707dc
void sharksealxMode1(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32 z;
      SetMotion(&p->s, MOTION(0x18, 0x00));
      if ((p->s).coord.x > (pZero2->s).coord.x) {
        *((u8*)p + 0xbc) = m;
      } else {
        *((u8*)p + 0xbc) = 1;
      }
      SET_XFLIP(p, *((u8*)p + 0xbc));
      z = 0;
      SetDDP(&p->body, &sCollisions[0]);
      *(s32*)((u8*)p + 0xb8) = z;
      (p->s).work[2] = z;
      (p->s).d.y = (p->s).coord.y;
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      s32 diff;
      (p->s).work[2] += 2;
      (p->s).coord.y = (p->s).d.y + gSineTable[(p->s).work[2]] * 8;
      forceWaterLanding(&p->s);
      if (*((u8*)p + 0xbc) == 0) {
        diff = (p->s).coord.x - (pZero2->s).coord.x;
      } else {
        diff = (pZero2->s).coord.x - (p->s).coord.x;
      }
      if (diff <= 0x7FFF) {
        (p->s).d.y = 0;
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
    }
  }
}

bool8 FUN_080708dc(struct Enemy* p) { return TRUE; }

short forceWaterLanding(struct Entity* p);

void sharksealxMode2(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x1800);
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      SET_XFLIP(p, *(u8*)((u8*)p + 0xbc));
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0x100) {
        (p->s).d.y = 0x100;
      }
      (p->s).coord.y += (p->s).d.y;
      forceWaterLanding(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08070990(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p5.inc");

bool8 FUN_08070c68(struct Enemy* p) { return TRUE; }

// 0x08070C6C
void sharksealxMode4(struct Enemy* p) {
  register s32 nm1 asm("r0");
  register s32 nm2 asm("r1");
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 z asm("r2");
      SetMotion(&p->s, 0xc0 << 5);
      SetDDP(&p->body, &sCollisions[0]);
      z = 0;
      (p->s).d.y = z;
      (p->s).d.x = z;
      {
        register s32 tx asm("r1");
        register s32 cx asm("r0");
        tx = *(s32*)((u8*)p + 0xb4);
        cx = (p->s).coord.x;
        if (tx < cx) {
          register s32 k asm("r0");
          k = 0x20;
          k = -k;
          *(s32*)((u8*)p + 0x64) = k;
          {
            register u32 d asm("r0");
            d = *((u8*)p + 0xbc);
            if (d == 1) {
              (p->s).mode[3] = d;
              goto donedir;
            }
          }
          goto zerodir;
        } else {
          register s32 k asm("r0");
          (p->s).d.x = z;
          k = 0x20;
          *(s32*)((u8*)p + 0x64) = k;
          {
            register u32 d asm("r0");
            d = *((u8*)p + 0xbc);
            if (d == 0) {
              (p->s).mode[3] = 1;
              goto donedir;
            }
          }
        }
      zerodir:
        (p->s).mode[3] = z;
      }
    donedir:
      (p->s).d.y = (p->s).coord.y;
      {
        register s32 zz asm("r1");
        zz = 0;
        (p->s).work[2] = 0x28;
        (p->s).work[3] = zz;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register u32 w3 asm("r2");
      register s32 sv asm("r1");
      {
        register const s16* tb asm("r1");
        tb = gSineTable;
        w3 = (p->s).work[3];
        sv = tb[w3];
      }
      {
        register s32 v asm("r0");
        v = sv;
        sv = v << 1;
        sv += v;
        sv <<= 1;
      }
      w3 += 4;
      (p->s).work[3] = w3;
      (p->s).coord.y = (p->s).d.y + sv;
      forceWaterLanding(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      if ((p->s).mode[3] == 1) {
        (p->s).mode[2] += 2;
        break;
      }
      (p->s).mode[2] += 1;
      break;
    }
    case 2: {
      register u32 d asm("r2");
      d = *((u8*)p + 0xbc);
      if (d != 0) {
        u8 fl = (p->s).flags;
        u32 f = 0x10;
        f |= fl;
        (p->s).flags = f;
      } else {
        u8 fl = (p->s).flags;
        u32 f = 0xEF;
        f &= fl;
        (p->s).flags = f;
      }
      {
        register u32 xf asm("r1");
        xf = 1;
        xf &= d;
        {
          u8* x = (u8*)p + 0x4c;
          *x = xf;
        }
        {
          register u8* oa asm("r3");
          oa = (u8*)p + 0x4a;
          xf <<= 4;
          {
            s32 ov = *oa;
            s32 m11 = -0x11;
            m11 &= ov;
            m11 |= xf;
            *oa = m11;
          }
        }
      }
      goto stage10;
    }
    case 3:
      SetMotion(&p->s, 0x1801);
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).work[2] = 0xc;
      (p->s).work[3] = 2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4:
      forceWaterLanding(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          goto upd;
        }
      }
      (p->s).work[2] = 0xc;
      if ((p->s).work[3] == 0) {
        goto upd;
      }
      {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) == 0) {
        stage10:
          (p->s).mode[2] = 0xa;
          break;
        }
      }
      {
        register u8* q asm("r0");
        register u32 d asm("r2");
        q = (u8*)p + 0xbc;
        {
          register u32 v asm("r1");
          register u32 one asm("r2");
          v = *q;
          one = 1;
          v ^= one;
          *q = v;
        }
        d = *q;
        if (d != 0) {
          register u32 f asm("r0");
          register u32 m asm("r1");
          f = (p->s).flags;
          m = 0x10;
          f |= m;
          (p->s).flags = f;
        } else {
          u8 fl = (p->s).flags;
          u32 f = 0xEF;
          f &= fl;
          (p->s).flags = f;
        }
        {
          register u32 xf asm("r1");
          xf = 1;
          xf &= d;
          {
            u8* x = (u8*)p + 0x4c;
            *x = xf;
          }
          {
            register u8* oa asm("r3");
            oa = (u8*)p + 0x4a;
            xf <<= 4;
            {
              s32 ov = *oa;
              s32 m11 = -0x11;
              m11 &= ov;
              m11 |= xf;
              *oa = m11;
            }
          }
        }
      }
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, 0x1806);
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    case 10: {
      register s32 dx asm("r2");
      register s32 cx asm("r3");
      s32* pb;
      register s32 tx asm("r6");
      register s32 df asm("r5");
      {
        register s32 v asm("r1");
        register s32 lim asm("r0");
        v = (p->s).d.x;
        lim = *(s32*)((u8*)p + 0x64);
        v += lim;
        (p->s).d.x = v;
        lim = 0x80 << 2;
        if (v > lim) {
          goto clamp;
        }
        lim = -0x200;
        if (v >= lim) {
          goto noclamp;
        }
      clamp:
        (p->s).d.x = lim;
      noclamp:;
      }
      (p->s).coord.x += (p->s).d.x;
      {
        register s32 cy asm("r1");
        register s32 k asm("r2");
        cy = (p->s).coord.y;
        if (cy > (p->s).unk_coord.y) {
          k = -0x100;
        } else {
          k = 0x80 << 1;
        }
        {
          register s32 v asm("r0");
          v = cy + k;
          (p->s).coord.y = v;
        }
      }
      forceWaterLanding(&p->s);
      dx = (p->s).d.x;
      if (dx < 0) {
        dx = -dx;
      }
      {
        register s32* q asm("r0");
        register s32 cx1 asm("r1");
        q = (s32*)((u8*)p + 0xb4);
        cx1 = (p->s).coord.x;
        tx = *q;
        df = cx1 - tx;
        pb = q;
        cx = cx1;
      }
      if (df > 0) {
        if (df <= dx) {
          goto hit1;
        }
        goto second;
      } else {
        register s32 v asm("r0");
        v = tx - cx;
        if (v > dx) {
          goto second;
        }
      }
    hit1:
      nm2 = 0;
      nm1 = 1;
      goto setmode;
    second : {
      register s32 v asm("r1");
      register s32 e asm("r2");
      v = *pb;
      e = cx - v;
      if (e > 0) {
        register s32 lim asm("r0");
        lim = 0xa0 << 8;
        if (e <= lim) {
          goto ok2;
        }
        goto upd2;
      } else {
        register s32 lim asm("r0");
        v -= cx;
        lim = 0xa0 << 8;
        if (v > lim) {
          goto upd2;
        }
      }
    }
    ok2 : {
      register s32 v asm("r1");
      if (*((u8*)p + 0xbc) == 0) {
          register s32 zx asm("r0");
          zx = (pZero2->s).coord.x;
          v = cx - zx;
        } else {
          register s32 zx asm("r0");
          zx = (pZero2->s).coord.x;
          v = zx - cx;
        }
        {
          register s32 lim asm("r0");
          lim = 0x7FFF;
          if (v > lim) {
            goto upd2;
          }
        }
      }
      {
        register s32* q asm("r2");
        register s32 v asm("r1");
        register s32 t asm("r0");
        q = (s32*)((u8*)p + 0xb8);
        t = *pb;
        v = cx - t;
        if (v <= 0) {
          v = t - cx;
        }
        *q = v;
      }
      nm2 = 0;
      nm1 = 2;
    setmode:
      (p->s).mode[1] = nm1;
      (p->s).mode[2] = nm2;
    upd2:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 FUN_08070f3c(struct Enemy* p) { return TRUE; }

void sharksealxMode5(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[4]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[0]);
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_08070f8c(struct Enemy* p) { return TRUE; }


void nop_08070f90(struct Enemy* p) {}

bool8 FUN_08070f94(struct Enemy* p) { return TRUE; }

// 0x08070f98
void sharksealxMode7(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetDDP(&p->body, &sCollisions[4]);
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).d.y += 0x10;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + (p->s).d.y + PIXEL(16)) != 0) {
        (p->s).d.y = 0;
        (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - PIXEL(16);
      } else {
        (p->s).coord.y += (p->s).d.y;
      }
      break;
  }
  {
    struct Entity** slot = (struct Entity**)((u8*)p + 0xc0);
    if (isKilled(*slot)) {
      SetDDP(&p->body, &sCollisions[0]);
      *slot = NULL;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

INCASM("asm/enemy/sharkseal_x_p9.inc");

bool8 nop_080711d4(struct Enemy* p) { return TRUE; }

void FUN_080711d8(struct Body* body, struct Coord* r1, struct Coord* r2) {
  u8 atk_type = (body->enemy->processing)->atkType;
  if (atk_type == 3 || atk_type == 0xe || atk_type == 0xf) {
    struct Enemy* self = (struct Enemy*)(body->parent);
    if ((self->body).status & BODY_STATUS_DEAD) {
      if ((self->s).coord.x < r1->x) {
        *(u8*)((u8*)self + 0xbf) = 0xff;
      } else {
        *(u8*)((u8*)self + 0xbf) = 0xfe;
      }
    }
  }
}

short forceWaterLanding(struct Entity* p) {
  s32 sea = gOverworld.sea;
  if (sea > p->coord.y) {
    p->coord.y = sea;
  }
}

void SharksealX_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSharksealXRoutine = {
    [ENTITY_INIT] =      (void*)SharksealX_Init,
    [ENTITY_UPDATE] =    SharksealX_Update,
    [ENTITY_DIE] =       SharksealX_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_080707d0(struct Enemy* p);
bool8 FUN_080707d8(struct Enemy* p);
bool8 FUN_080708dc(struct Enemy* p);
bool8 FUN_08070990(struct Enemy* p);
bool8 FUN_08070c68(struct Enemy* p);
bool8 FUN_08070f3c(struct Enemy* p);
bool8 FUN_08070f8c(struct Enemy* p);
bool8 FUN_08070f94(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_08366a04[8] = {
    (EnemyFunc)FUN_080707d0,
    (EnemyFunc)FUN_080707d8,
    (EnemyFunc)FUN_080708dc,
    (EnemyFunc)FUN_08070990,
    (EnemyFunc)FUN_08070c68,
    (EnemyFunc)FUN_08070f3c,
    (EnemyFunc)FUN_08070f8c,
    (EnemyFunc)FUN_08070f94,
};
// clang-format on

void nop_080707d4(struct Enemy* p);
void sharksealxMode1(struct Enemy* p);
void sharksealxMode2(struct Enemy* p);
void sharksealxMode3(struct Enemy* p);
void sharksealxMode4(struct Enemy* p);
void sharksealxMode5(struct Enemy* p);
void nop_08070f90(struct Enemy* p);
void sharksealxMode7(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366a24[8] = {
    nop_080707d4,
    sharksealxMode1,
    sharksealxMode2,
    sharksealxMode3,
    sharksealxMode4,
    sharksealxMode5,
    nop_08070f90,
    sharksealxMode7,
};
// clang-format on

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(5), PIXEL(0), PIXEL(30), PIXEL(9)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(5), PIXEL(0), PIXEL(32), PIXEL(11)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(1), PIXEL(18), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(5), PIXEL(1), PIXEL(18), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(5), PIXEL(0), PIXEL(32), PIXEL(11)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
