#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "stagerun.h"
#include "story.h"
#include "motion.h"

// Entity.work[0]
#define SEIMERAN_ROOT 0
#define SEIMERAN_CLONE 1
#define SEIMERAN_SEED 2

typedef struct EnemySeimeran {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct {
    struct Entity* elfx;  // 0xB4, Element Effect
    struct Coord c_b8;    // 0xB8
    u8 unk_c0;            // 0xC0
  } props;
} Seimeran;

static const struct Collision sCollisions[15];

void Seimeran_Die(struct Enemy* p);
extern const EnemyFunc sUpdates1[8];
extern const EnemyFunc sUpdates2[8];
extern const struct Coord sElementCoord;

struct Enemy* FUN_0808f27c(struct Entity* e, s32 x, s32 y, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 57);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).unk_coord.x = x;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    (p->s).unk_28 = e;
  }
  return p;
}

#include "entity/macros.h"

void FUN_0808f2e4(s32 x, s32 y, u8 n) {
  struct Enemy* e = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

  if (e != NULL) {
    (e->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(e, 57);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).work[0] = 2;
    (e->s).coord.x = x;
    (e->s).coord.y = y;
    (e->s).work[2] = n;
  }
}

INCASM("asm/enemy/seimeran_p1_x.inc");

static bool8 FUN_0808f348(Seimeran* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if (((p->s).work[0] != SEIMERAN_SEED) && ((p->body).status & BODY_STATUS_SLASHED) && ((p->props).unk_c0 > 9)) {
      (p->s).mode[1] = 1;
    } else {
      (p->s).mode[1] = 0;
    }
    Seimeran_Die((void*)p);
    return TRUE;
  }
  return FALSE;
}

static bool8 FUN_0808f3a8(Seimeran* p) {
  if (((p->s).work[0] != SEIMERAN_SEED) && (p->props).elfx == NULL) {
    switch ((p->s).mode[3]) {
      case 0: {
        if (IsFrozen((void*)p)) {
          (sUpdates1[(p->s).mode[1]])((void*)p);
          (sUpdates2[(p->s).mode[1]])((void*)p);
          (p->s).mode[3]++;
          UpdateMotionGraphic(&p->s);
          return TRUE;
        }
        break;
      }
      case 1: {
        if (IsFrozen((void*)p)) {
          return TRUE;
        }
        (p->s).mode[3] = 0;
        break;
      }
    }
  }
  return FALSE;
}

static void FUN_0808f424(Seimeran* p) {
  if ((p->props).elfx == NULL && ((p->s).work[0] != SEIMERAN_SEED) && ((p->s).mode[1] != 5) && ((p->s).mode[1] != 6) && ((p->body).status & BODY_STATUS_WHITE)) {
    (p->props).elfx = (void*)ApplyElementEffect(0, &p->s, &sElementCoord);
    if ((p->props).elfx != NULL) {
      (p->s).mode[1] = 0, (p->s).mode[2] = 0;
    }
  }
}

static const u8 sInitModes[4];
void Seimeran_Update(struct Enemy* p);

void Seimeran_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] == 2) {
    INIT_BODY(p, sCollisions, 4, NULL);
  } else {
    INIT_BODY(p, sCollisions, 6, NULL);
  }
  SET_BODY_INTERSECT_HANDLER(p, (void*)0x0808F345);
  ((Seimeran*)p)->props.elfx = NULL;
  if ((p->s).work[0] == 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    ((Seimeran*)p)->props.c_b8.x = 0;
    ((Seimeran*)p)->props.c_b8.y = 0;
  }
  ((Seimeran*)p)->props.unk_c0 = 0;
  Seimeran_Update(p);
}

void Seimeran_Update(struct Enemy* p) {
  s32 rz;
  register u32 gf asm("r3");
  u32 k2;
  u32 fl2;
  u32 w0;
  gf = gCurStory.s.gameflags[4];
  k2 = 2;
  asm("" : "+r"(k2));
  k2 &= gf;
  asm("" : "+r"(k2));
  fl2 = (k2 << 24) >> 24;
  if (fl2 != 0) {
    u32 fa = (p->s).flags;
    u32 ka = 0xFE;
    s32 z2a;
    asm volatile("" : "+r"(ka));
    ka &= fa;
    z2a = 0;
    asm("" : "+r"(z2a));
    ka &= 0xFD;
    (p->s).flags = ka;
    *(u32*)((u8*)p + 0x8c) = z2a;
    *(u32*)((u8*)p + 0x90) = z2a;
    *((u8*)p + 0x94) = z2a;
    asm volatile("");
    goto disap;
  }
  w0 = (p->s).work[0];
  if (w0 == 0) {
    struct Entity** pb8 = (struct Entity**)((u8*)p + 0xb8);
    struct Entity* e = *pb8;
    if (e != NULL && e->mode[0] > 1) {
      *pb8 = (struct Entity*)w0;
    }
    {
      struct Entity** pbc = (struct Entity**)((u8*)p + 0xbc);
      e = *pbc;
      if (e != NULL && e->mode[0] > 1) {
        *pbc = NULL;
      }
    }
    if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000) {
      u32 fb = (p->s).flags;
      u32 kb = 0xFE;
      s32 z2b;
      asm volatile("" : "+r"(kb));
      kb &= fb;
      z2b = 0;
      asm("" : "+r"(z2b));
      kb &= 0xFD;
      (p->s).flags = kb;
      *(u32*)((u8*)p + 0x8c) = z2b;
      *(u32*)((u8*)p + 0x90) = z2b;
      *((u8*)p + 0x94) = z2b;
      asm volatile("");
      goto disap;
    }
  } else {
    u8 gf40;
    u32 k40 = 0x40;
    asm("" : "+r"(k40));
    gf40 = k40 & gf;
    if (gf40 != 0) {
      u32 fc = (p->s).flags;
      u32 kc = 0xFE;
      asm volatile("" : "+r"(kc));
      kc &= fc;
      kc &= 0xFD;
      (p->s).flags = kc;
      *(u32*)((u8*)p + 0x8c) = fl2;
      *(u32*)((u8*)p + 0x90) = fl2;
      *((u8*)p + 0x94) = fl2;
      goto disap;
    }
    if (w0 == 1) {
      rz = (s32)(p->s).unk_28;
      if (rz == 0) {
        if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) <= 0x1000) {
          goto common;
        }
        goto killD;
      } else {
        if (((struct Entity*)rz)->mode[0] > 1) {
          (p->s).unk_28 = (struct Entity*)(u32)gf40;
        }
      }
    }
  }
common:
  if ((u32)(FUN_0808f348((Seimeran*)p) << 24) != 0) {
    return;
  }
  FUN_0808f424((Seimeran*)p);
  rz = FUN_0808f3a8((Seimeran*)p);
  if (rz != 0) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
  if ((p->s).work[0] == 1) {
    if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000) {
      u32 fd;
      u32 kd;
    killD:
      fd = (p->s).flags;
      kd = 0xFE;
      asm volatile("" : "+r"(kd));
      kd &= fd;
      kd &= 0xFD;
      (p->s).flags = kd;
      *(u32*)((u8*)p + 0x8c) = rz;
      *(u32*)((u8*)p + 0x90) = rz;
      *((u8*)p + 0x94) = rz;
    disap:
      (p->s).flags &= 0xFB;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
}

static const EnemyFunc PTR_ARRAY_08369414[2];

void Seimeran_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (PTR_ARRAY_08369414[(p->s).mode[1]])(p);
}

void FUN_0808f728(struct Enemy* p) {}

INCASM("asm/enemy/seimeran_p2_p1.inc");

static const u8 sCollisionIdxs[16];

// Four instructions in the address-copy basin: retail computes the props[12]
// address into a temp, copies it into the kept pointer, and derives &p->body
// from it (subs 0x4C); agbcc coalesces the copy in every spelling tried.
NON_MATCH void FUN_0808f72c(struct Enemy* p) {
#if MODERN
  struct Entity** slot = (struct Entity**)&p->props[0];
  if (*slot == NULL || isKilled(*slot)) {
    u8* c;
    *slot = NULL;
    c = (u8*)p + 0xc0;
    if (*c == 0xC) {
      SetDDP(&p->body, &sCollisions[11]);
    } else {
      SetDDP(&p->body, &sCollisions[sCollisionIdxs[*c]]);
    }
    if (!IsFrozen(&p->s)) {
      if (*c == 0xC) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      } else {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 3;
      }
    }
  }
#else
  INCCODE("asm/enemy/seimeran_f72c.inc");
#endif
}

void FUN_0808f7ac(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    u8* c = (u8*)p + 0xc0;
    if (*c == 0xC) {
      SetMotion(&p->s, MOTION(0x77, 0x00));
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[12]);
    } else {
      GotoMotion(&p->s, MOTION(0x77, 0x01), *c, 3);
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &(&sCollisions[1])[sCollisionIdxs[*c]]);
    }
    (p->s).mode[2]++;
  }
}

// 0x0808f824
void FUN_0808f824(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0x1e;
      SetMotion(&p->s, MOTION(0x77, 0x07));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetMotion(&p->s, MOTION(0x77, 0x01));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s8* mp;
      u8 st;
      UpdateMotionGraphic(&p->s);
      st = (p->s).motion.state;
      if (st == 3) {
        (p->s).mode[1] = st;
        (p->s).mode[2] = 0;
      }
      SetDDP(&p->body, &sCollisions[sCollisionIdxs[*(s8*)((u8*)p + 0x71)]]);
      mp = (s8*)((u8*)p + 0x71);
      {
        register u8 mv asm("r1");
        register u8* dp asm("r0");
        mv = *(u8*)mp;
        dp = (u8*)p + 0xc0;
        asm("" : "+r"(dp));
        *dp = mv;
      }
      break;
    }
  }
}

void FUN_0808f8e0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[11]);
      (p->s).work[2] = 0xa0;
      SetMotion(&p->s, MOTION(0x77, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (--(p->s).work[2] == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
  }
}

INCASM("asm/enemy/seimeran_p2_p2.inc");

void FUN_0808fa24(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x103);
      SetMotion(&p->s, MOTION(0x77, 4));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x0808FA70
void FUN_0808fa70(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8 w;
      u32 xf;
      SetDDP(&p->body, &sCollisions[1]);
      w = (p->s).work[2];
      if (w != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      xf = 1 & w;
      ((p->s).spr).xflip = xf;
      {
        register u8* oa asm("r3");
        u32 sh4;
        s32 ov;
        s32 m11;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      (p->s).work[3] = Sqrt(0x200);
      (p->s).d.y = -((p->s).work[3] << 6);
      SetMotion(&p->s, MOTION(0x77, 0x07));
      (p->s).mode[2]++;
    }
    case 1: {
      s32 d = (p->s).work[3] - 1;
      u8 t;
      (p->s).work[3] = d;
      t = d;
      if (t == 0) {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = t;
      }
      (p->s).d.y += 0x40;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x0808fb10
void FUN_0808fb10(struct Enemy* p) {
  s32 x;
  s32 r;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.x = ((p->s).work[2] << 9) - 0x100;
      SetMotion(&p->s, MOTION(0x77, 0x08));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SetMotion(&p->s, MOTION(0x77, 0x09));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      break;
  }
  x = (p->s).coord.x + (p->s).d.x;
  (p->s).coord.x = x;
  if ((p->s).d.x > 0) {
    r = PushoutToLeft1(x + 0x600, (p->s).coord.y);
    if (r < 0) {
      (p->s).coord.x += r;
    }
  } else {
    r = PushoutToRight1(x - 0x600, (p->s).coord.y);
    if (r > 0) {
      (p->s).coord.x += r;
    }
  }
  (p->s).d.y += 0x15;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  (p->s).coord.y += (p->s).d.y;
  r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
  if (r < 0) {
    (p->s).coord.y += r;
    (p->s).mode[1] = 1, (p->s).mode[2] = 0;
  }
  {
    s32 cx = (p->s).unk_coord.x;
    s32 b = cx - 0x2C00;
    if ((p->s).coord.x < b) {
      (p->s).coord.x = b;
    } else {
      b = cx + 0x2C00;
      if ((p->s).coord.x > b) {
        (p->s).coord.x = b;
      }
    }
  }
}

// 0x0808FC10
void FUN_0808fc10(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 w asm("r2");
      SetDDP(&p->body, (const struct Collision*)0x08369554);
      w = (p->s).work[2];
      if (w != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
      {
        register s32 xf asm("r1");
        u8* oa;
        s32 sh4, ov, m11;
        xf = 1;
        xf &= w;
        (p->s).spr.xflip = xf;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      {
        register s32 wv asm("r1");
        register s32 t asm("r0");
        wv = (p->s).work[2];
        t = wv << 1;
        t += wv;
        t <<= 8;
        wv = -0x180;
        asm("" : "+r"(wv));
        t += wv;
        (p->s).d.x = t;
      }
      (p->s).work[3] = Sqrt(0x200);
      (p->s).d.y = -((p->s).work[3] << 6);
      SetMotion(&p->s, MOTION(0x77, 0x0B));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 lim asm("r2");
      register s32 ny asm("r1");
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      lim = 0x700;
      if ((p->s).d.y > lim) {
        (p->s).d.y = lim;
      }
      {
        register s32 dv asm("r0");
        ny = (p->s).coord.y;
        dv = (p->s).d.y;
        ny += dv;
        (p->s).coord.y = ny;
      }
      if (((bool16 (*)(s32, s32))FUN_080098a4)((p->s).coord.x, ny + lim)) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = 0;
      }
      break;
    }
  }
}

#include "mission.h"
#include "vfx.h"

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x0808fcec
void maybeKillSeimeran(struct Enemy* p) {
  struct Coord c;
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    u8* q = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(q));
    z = 0;
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *q = z;
    t = (p->s).flags;
    f = 0xFB;
    f &= t;
    asm volatile("" ::"r"(t));
    k2 = 0xFE;
    f &= k2;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  if ((p->s).work[0] != 2) {
    c.y = (p->s).coord.y - 0x1000;
  }
  CreateSmoke(1, &c);
  if ((p->s).work[0] != 2) {
    struct Coord* co;
    PlaySound(0x2a);
    co = &(p->s).coord;
    TryDropItem(2, co);
    if (gMission.enemyCount <= 0x270E) {
      gMission.enemyCount++;
    }
    TryDropZakoDisk(p, co);
  } else {
    PlaySound(0x35);
  }
  SET_ENEMY_ROUTINE(p, 4);
}

INCASM("asm/enemy/seimeran_p2_p3b_b.inc");

void Seimeran_Init(struct Enemy* p);
void Seimeran_Update(struct Enemy* p);
void Seimeran_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSeimeranRoutine = {
    [ENTITY_INIT] =      Seimeran_Init,
    [ENTITY_UPDATE] =    Seimeran_Update,
    [ENTITY_DIE] =       Seimeran_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0808f728(struct Enemy* p);
void FUN_0808f72c(struct Enemy* p);

// clang-format off
const EnemyFunc sUpdates1[8] = {
    FUN_0808f72c,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
    FUN_0808f728,
};
// clang-format on

void FUN_0808f7ac(struct Enemy* p);
void FUN_0808f824(struct Enemy* p);
void FUN_0808f8e0(struct Enemy* p);
void FUN_0808f934(struct Enemy* p);
void FUN_0808fa24(struct Enemy* p);
void FUN_0808fa70(struct Enemy* p);
void FUN_0808fb10(struct Enemy* p);
void FUN_0808fc10(struct Enemy* p);

// clang-format off
const EnemyFunc sUpdates2[8] = {
    FUN_0808f7ac,
    FUN_0808f824,
    FUN_0808f8e0,
    FUN_0808f934,
    FUN_0808fa24,
    FUN_0808fa70,
    FUN_0808fb10,
    FUN_0808fc10,
};
// clang-format on

// --------------------------------------------

void maybeKillSeimeran(struct Enemy* p);
void FUN_0808fd88(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08369414[2] = {
    maybeKillSeimeran,
    FUN_0808fd88,
};

// --------------------------------------------

static const struct Collision sCollisions[15] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(15), PIXEL(17)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(9), PIXEL(18), PIXEL(21)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(9), PIXEL(15), PIXEL(21)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(11), PIXEL(18), PIXEL(25)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(11), PIXEL(15), PIXEL(25)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(13), PIXEL(18), PIXEL(29)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(13), PIXEL(15), PIXEL(29)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(18), PIXEL(35)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(15), PIXEL(35)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(17), PIXEL(18), PIXEL(38)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(17), PIXEL(15), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(15), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(15), PIXEL(15)},
    },
};

static const u8 sCollisionIdxs[16] = {1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 11, 0, 0, 0};

const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};

static const u8 sInitModes[4] = {1, 5, 7, 0};

static const motion_t sMotions[1] = {
    MOTION(SM119_SEIMERAN, 5),
};
