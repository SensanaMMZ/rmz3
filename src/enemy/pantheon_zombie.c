#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "metatile.h"
#include "physics.h"
#include "stagerun.h"
#include "motion.h"
#include "boss.h"
#include "zero.h"

static const struct Collision sCollisions[8];

static const EnemyFunc sDeads[3];

static const struct Coord sElementCoord;

static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];

void createPantheonZombie(struct Boss* anubis, s32 x, s32 y) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (anubis->props).anubis.pzombieCount++;
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_ZOMBIE);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).unk_28 = (void*)anubis;
    ((p->s).coord).x = x, ((p->s).coord).y = y;
  }
}

void FUN_0807fd84(struct Body* body) {
  struct Enemy* self = (struct Enemy*)body->parent;
  if ((body->hitboxFlags & 0x800) && (self->s).mode[1] != 4) {
    (self->s).mode[1] = 4;
    (self->s).mode[2] = 0;
  }
}

void PantheonZombie_Die(struct Enemy* p);

bool8 FUN_0807fda8(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & 0x20000) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    PantheonZombie_Die(p);
    return TRUE;
  }
  return FALSE;
}

void FUN_0807fdf8(struct Enemy* p) {
  if (*(struct VFX**)&p->props[0] == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *(struct VFX**)&p->props[0] = e;
    if (e != NULL) {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
  }
}

void PantheonZombie_Update(struct Enemy* p);
extern const u8 sInitModes[4];

void PantheonZombie_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 20, (void*)FUN_0807fd84);
  *(u32*)&p->props[0] = 0;
  p->props[4] = 0;
  PantheonZombie_Update(p);
}

void PantheonZombie_Update(struct Enemy* p) {
  if (*(u32*)((u8*)(p->s).unk_28 + 0xc0) & 0x100) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 1;
    PantheonZombie_Die(p);
  } else {
    if (FUN_0807fda8(p)) return;
    FUN_0807fdf8(p);
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

void PantheonZombie_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0807ff3c(struct Enemy* p) {}


void FUN_0807ff40(struct Enemy* p) {
  u32 status = (p->body).status;
  if (status & BODY_STATUS_WHITE) {
    if (status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 7;
    } else {
      (p->s).mode[1] = 6;
    }
    (p->s).mode[2] = 0;
  }
}

void FUN_0807ff6c(struct Enemy* p) {
  u32 status = (p->body).status;
  if (status & BODY_STATUS_WHITE) {
    if (status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 7;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_0807ff94(struct Enemy* p) {
  if (!((p->body).status & BODY_STATUS_BINDING)) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
}

void FUN_0807ffb0(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

// 0x0807FFD8
void FUN_0807ffd8(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(0x4C, 0x02));
      (p->s).d.y = m;
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
    case 1:
      if (*(u8*)((u8*)p + 0xb8) != 0) {
        (p->s).coord.y += 0x20;
      } else {
        s32 hit;
        (p->s).d.y += 0x40;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        hit = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (hit < 0) {
          (p->s).coord.y += hit;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_08080054(struct Enemy* p) {
  struct Boss* anubis = (struct Boss*)(p->s).unk_28;
  u8* pb;
  s32 dx;
  s32 wv;
  u8 m2;
  if ((anubis->props).anubis.unk_c4[6] != 0) {
    SetDDP(&p->body, &sCollisions[1]);
  } else {
    SetDDP(&p->body, &sCollisions[3]);
  }
  {
    u8 first = *((u8*)p + 0xb8);
    pb = (u8*)p + 0xb8;
    if (first == 0) {
      u32 attr = ((u32(*)(s32, s32))GetMetatileAttr)((p->s).coord.x, (p->s).coord.y + 0x800);
      u8 v = 0;
      if ((0xFFF0 & attr) == 0x400) {
        v = 1;
      }
      *pb = v;
    }
  }
  m2 = (p->s).mode[2];
  switch (m2) {
    case 0:
      (p->s).taskCol = 0x18;
      (p->s).flags |= DISPLAY;
      SetMotion(&p->s, 0x4C00);
      (p->s).work[2] = m2;
      (p->s).work[3] = m2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      if (*pb != 0) {
        (p->s).work[3] = 1;
      }
      dx = (pZero2->s).coord.x - (p->s).coord.x;
      if (dx < 0) {
        (p->s).flags &= ~X_FLIP;
        {
          bool8 zf = 0;
          ((p->s).spr).xflip = zf & 1;
          ((p->s).spr).oam.xflip = zf;
        }
        if ((FUN_080098a4((p->s).coord.x + -0x800, (p->s).coord.y + -0x1000) << 0x10) != 0 && *pb == 0) {
          goto walk;
        }
        (p->s).coord.x -= 0x40;
        wv = 0;
        asm volatile("");
        goto store;
      } else {
        SET_XFLIP(p, 1);
        if ((FUN_080098a4((p->s).coord.x + 0x800, (p->s).coord.y + -0x1000) << 0x10) != 0 && *pb == 0) {
          goto walk;
        }
        (p->s).coord.x += 0x40;
        wv = 0;
        goto store;
      walk:
        wv = (p->s).work[2] + 1;
      store:
        (p->s).work[2] = wv;
      }
      if ((u32)(dx + 0xA00) <= 0x13FF) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      dx = (pZero2->s).coord.x - (p->s).coord.x;
      if ((u32)(dx + 0xA00) > 0x1400) {
        (p->s).mode[2] = 0;
      }
      break;
  }
  dx = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  {
    s32 oy = (p->s).coord.y;
    if (dx - oy > 0xDFF) {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = 0;
    } else if (*pb != 0) {
      s32 ny2 = oy + 0x20;
      (p->s).coord.y = ny2;
      if (dx - ny2 < -0x6000) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        (anubis->props).anubis.pzombieCount--;
      }
    } else {
      (p->s).coord.y = dx;
    }
  }
}

void FUN_080bf48c(s32 x, s32 y, u8 n);
void FUN_080bf438(s32 x, s32 y, u8 n);

// 0x0808027c
void FUN_0808027c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 v asm("r2");
      {
        register u8 f asm("r0");
        register u8 t asm("r1");
        t = (p->s).flags;
        f = 0xFE;
        f &= t;
        (p->s).flags = f;
        asm volatile("" ::"r"(t));
      }
      FUN_080bf48c((p->s).coord.x, (p->s).coord.y + 0x1000, 0);
      FUN_080bf438((p->s).coord.x, (p->s).coord.y, 0);
      v = 0;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        v = 1;
      }
      if (v != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
      {
        register s32 xf asm("r1");
        u8* oa;
        s32 sh4, ov, m11;
        xf = v;
        (p->s).spr.xflip = xf;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      (p->s).coord.y -= 0x1000;
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      u8 t2 = --(p->s).work[2];
      if (t2 == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = t2;
      }
      break;
    }
  }
}

// 0x08080324
void FUN_08080324(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8 fv asm("r0");
      u8 t = (p->s).flags;
      fv = DISPLAY;
      fv |= t;
      (p->s).flags = fv;
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).d.y = m;
      SetMotion(&p->s, MOTION(0x4C, 0x02));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 v = (p->s).d.y + 0x40;
      s32 y;
      s32 r;
      (p->s).d.y = v;
      if (v > 0x700) {
        (p->s).d.y = 0x700;
      }
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      r = PushoutToUp1((p->s).coord.x, y);
      if (r < 0) {
        (p->s).coord.y += r;
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetMotion(&p->s, MOTION(0x4C, 0x04));
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      u8 t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = t;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080803DC
void FUN_080803dc(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32 dx;
      SetDDP(&p->body, &sCollisions[5]);
      (p->s).taskCol = 0xF;
      if ((p->s).coord.x > (pZero2->s).coord.x) {
        (p->s).flags &= 0xEF;
        ((p->s).spr).xflip = m;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        dx = 0x800;
      } else {
        s32 one = 1;
        (p->s).flags |= 0x10;
        ((p->s).spr).xflip = one;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 sh = 0x10;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          m11 |= sh;
          *oa = m11;
        }
        dx = -0x800;
      }
      (p->s).unk_coord.x = dx;
      SetMotion(&p->s, 0x4C03);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      struct Zero* z;
      if (*(u8*)((u8*)p + 0xb8) != 0) {
        (p->s).coord.y += 0x20;
      }
      z = pZero2;
      (p->s).coord.x = (z->s).coord.x + (p->s).unk_coord.x;
      if ((z->s).coord.y > (p->s).coord.y) {
        (z->s).coord.y = (p->s).coord.y;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}


void FUN_080804a8(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32 v;
      SetDDP(&p->body, &sCollisions[1]);
      *((u8*)p + 0x25) = 0x18;
      (p->s).work[3] = m;
      if (*((u8*)p + 0xb8) != 0) {
        (p->s).work[3] = 1;
        (p->s).mode[2] = 2;
        break;
      }
      (p->s).d.y = -0x180;
      {
        s32 t = 0x280;
        (p->s).d.x = t;
        v = t;
        asm("" : "+r"(t));
      }
      if ((p->s).flags & 0x10) {
        v = -0x280;
      }
      (p->s).d.x = v;
      SetMotion(&p->s, MOTION(0x4c, 1));
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 x = (p->s).coord.x;
      s32 tx = x + 0x800;
      s32 ny;
      s32 push;
      if ((p->s).flags & 0x10) {
        tx = x + -0x800;
      }
      if (FUN_080098a4(tx, (p->s).coord.y + -0x1000) == 0) {
        (p->s).coord.x += (p->s).d.x;
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      {
        struct Camera* cam = &gStageRun.vm.camera;
        s32 lim = cam->viewport.x + 0x77FF;
        if ((p->s).coord.x > lim) {
          (p->s).coord.x = lim;
        }
        lim = cam->viewport.x + -0x7800;
        if ((p->s).coord.x < lim) {
          (p->s).coord.x = lim;
        }
      }
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      push = PushoutToUp1((p->s).coord.x, ny);
      if (push < 0) {
        (p->s).coord.y += push;
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetMotion(&p->s, MOTION(0x4c, 4));
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
      // fallthrough
    case 3: {
      s32 t = (p->s).work[2] - 1;
      u32 u;
      (p->s).work[2] = t;
      u = (u8)t;
      if (u == 0) {
        s32 one = 1;
        u8 b;
        (p->s).mode[1] = one;
        b = *((u8*)p + 0xb8);
        if (b != 0) {
          (p->s).work[2] = u;
          (p->s).mode[2] = one;
        } else {
          (p->s).mode[2] = b;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_08080610(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0x10;
      SetMotion(&p->s, MOTION(0x4c, 2));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (--(p->s).work[2] == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      if (p->props[4] != 0) {
        (p->s).coord.y += 0x20;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

struct Entity* CreateSmoke(u8 kind, struct Coord* c);
void FUN_080bf52c(s32 x, s32 y);

// 0x08080674
void FUN_08080674(struct Enemy* p) {
  struct Coord c;
  register u8* q asm("r0");
  u32 z;
  u8* w;
  q = (u8*)p + 0x8c;
  z = 0;
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *(u32*)q = z;
  asm volatile("add %0, #4" : "+r"(q));
  *q = z;
  (p->s).flags &= 0xFB;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x56);
  FUN_080bf52c(c.x, c.y);
  SET_ENEMY_ROUTINE(p, 4);
  w = (u8*)(p->s).unk_28 + 0xcb;
  *w = *w - 1;
}

void FUN_080bf48c(s32 x, s32 y, u8 n);

void FUN_080806e0(struct Enemy* p) {
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  (p->s).flags &= ~COLLIDABLE;
  FUN_080bf48c((p->s).coord.x, (p->s).coord.y - PIXEL(16), 1);
  *(u8*)((u8*)(p->s).unk_28 + 0xcb) -= 1;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x08080734
void FUN_08080734(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 dx;
      s32 cy;
      s32 dy;
      s32 a;
      s32 b;
      register s32 sq1 asm("r6");
      s32 sq2;
      s32 len;
      s32 vx;
      s32 vy;
      SetDDP(&p->body, &sCollisions[7]);
      SetMotion(&p->s, 0x4C02);
      dx = (p->s).coord.x - (pZero2->s).coord.x;
      (p->s).d.x = dx;
      cy = (p->s).coord.y - 0x1800;
      dy = cy - (pZero2->s).coord.y;
      (p->s).d.y = dy;
      a = dx >> 8;
      sq1 = a * a;
      b = dy >> 8;
      sq2 = b * b;
      sq1 += sq2;
      len = sq1;
      len = (u32)Sqrt(len) << 8;
      vx = ((p->s).d.x << 8) / len;
      (p->s).d.x = vx;
      vy = ((p->s).d.y << 8) / len;
      (p->s).d.x = vx * 6;
      (p->s).d.y = vy * 6;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if (((bool16 (*)(s32, s32))FUN_080098a4)((p->s).coord.x, (p->s).coord.y)) {
        FUN_08080674(p);
      }
      break;
  }
}

void PantheonZombie_Init(struct Enemy* p);
void PantheonZombie_Update(struct Enemy* p);
void PantheonZombie_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonZombieRoutine = {
    [ENTITY_INIT] =      PantheonZombie_Init,
    [ENTITY_UPDATE] =    PantheonZombie_Update,
    [ENTITY_DIE] =       PantheonZombie_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0807ffb0(struct Enemy* p);
void FUN_0807ff40(struct Enemy* p);
void nop_0807ff3c(struct Enemy* p);
void FUN_0807ff6c(struct Enemy* p);
void FUN_0807ff94(struct Enemy* p);
void FUN_0807ff6c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    FUN_0807ffb0,
    FUN_0807ff40,
    nop_0807ff3c,
    FUN_0807ff6c,
    FUN_0807ff94,
    FUN_0807ff6c,
    nop_0807ff3c,
    nop_0807ff3c,
};
// clang-format on

void FUN_0807ffd8(struct Enemy* p);
void FUN_08080054(struct Enemy* p);
void FUN_0808027c(struct Enemy* p);
void FUN_08080324(struct Enemy* p);
void FUN_080803dc(struct Enemy* p);
void FUN_080804a8(struct Enemy* p);
void FUN_08080610(struct Enemy* p);
void FUN_08080734(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    FUN_0807ffd8,
    FUN_08080054,
    FUN_0808027c,
    FUN_08080324,
    FUN_080803dc,
    FUN_080804a8,
    FUN_08080610,
    FUN_08080734,
};
// clang-format on

void FUN_08080674(struct Enemy* p);
void FUN_080806e0(struct Enemy* p);
void FUN_08080734(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_08080674,
    FUN_080806e0,
    FUN_08080734,
};

// --------------------------------------------

static const struct Collision sCollisions[8] = {
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
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(4), -PIXEL(16), PIXEL(14), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(4), -PIXEL(16), PIXEL(14), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      unk_0a : 0x21,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(2), -PIXEL(16), PIXEL(22), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(2), -PIXEL(16), PIXEL(22), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      unk_0a : 0x21,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(2), -PIXEL(16), PIXEL(64), PIXEL(64)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(2), -PIXEL(16), PIXEL(22), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(4), -PIXEL(16), PIXEL(14), PIXEL(32)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(16)};
static const u8 sInitModes[4] = {2, 0, 0, 0};
