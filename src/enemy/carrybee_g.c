#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "syssav.h"
#include "entity_manager.h"
#include "story.h"
#include "overworld_terrain.h"

void CarrybeeG_Init(struct Enemy* p);
void CarrybeeG_Update(struct Enemy* p);
void CarrybeeG_Die(struct Enemy* p);
void CarrybeeG_Disappear(struct Enemy* p);

// clang-format off
const EnemyRoutine gCarrybeeGRoutine = {
    [ENTITY_INIT] =      CarrybeeG_Init,
    [ENTITY_UPDATE] =    CarrybeeG_Update,
    [ENTITY_DIE] =       CarrybeeG_Die,
    [ENTITY_DISAPPEAR] = CarrybeeG_Disappear,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* FUN_0808a854(struct Coord* c) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CARRYBEE_G);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = 0;
  }
  return p;
}

struct Enemy* FUN_0808a8b0(struct Entity* e, s32 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CARRYBEE_G);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).unk_28 = e;
  }
  return p;
}

static const struct Collision sCollisions[9];
void nop_0808b534(struct Enemy* p);
void CarrybeeG_Update(struct Enemy* p);

void CarrybeeG_Init(struct Enemy* p) {
  u8 g40;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  {
    EnemyFunc h = nop_0808b534;
    struct Body* body = &p->body;
    body->fn = (void*)h;
  }
  if ((p->s).work[0] != 0) {
    goto alt;
  }
  FUN_0808a8b0(&p->s, 0);
  if ((p->s).work[0] != 0) {
    goto alt;
  }
  {
    u8* qa = (u8*)p + 0xc3;
    u8 k1 = 1;
    asm("" : "+r"(k1));
    *qa = k1;
  }
  {
    u8 mv = gSystemSavedataManager.mods[14];
    u32 k40 = 0x40;
    u32 t0 = k40;
    asm("" : "+r"(t0));
    t0 &= mv;
    if (t0 != 0 && (g40 = gCurStory.s.gameflags[0] & k40) == 0) {
      INIT_BODY(p, &sCollisions[1], 0x40, NULL);
    } else {
      INIT_BODY(p, &sCollisions[1], 0x30, NULL);
    }
  }
  {
    u8* q = (u8*)p + 0xbc;
    *(u32*)q = 0;
    (p->s).unk_2c = NULL;
    (p->s).unk_28 = NULL;
    {
      u8* qq = q + 4;
      *qq = 0;
      qq += 1;
      *qq = 0;
      qq += 1;
      *qq = 0;
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  (p->s).taskCol = 0x14;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, 0x6E00);
    UpdateMotionGraphic(&p->s);
  }
  goto join;
alt:
  SetDDP(&p->body, sCollisions);
  {
    u32 tbl = (u32)gEnemyFnTable;
    u32 id = (p->s).id << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    EntityFunc* t1;
    u8 m4;
    *(u32*)((p->s).mode) = ENTITY_UPDATE;
    t1 = *rt;
    m4 = 4;
    (p->s).onUpdate = (void*)t1[ENTITY_UPDATE];
    (p->s).mode[1] = m4;
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
  }
  (p->s).taskCol = 0x16;
  if (IsFrozen(&p->s)) {
    (p->s).flags2 |= 0x10;
    {
      register struct Entity* e asm("r1");
      e = (p->s).unk_28;
      *((u8*)p + 0x1d) = *((u8*)e + 0x1c);
      {
        s32 x0 = e->coord.x;
        s32 y0 = e->coord.y;
        (p->s).coord.x = x0;
        (p->s).coord.y = y0;
      }
    }
    SetMotion(&p->s, 0x6E06);
    UpdateMotionGraphic(&p->s);
  }
join:
  *((u8*)p + 0x11) = 0;
  if ((p->s).work[0] == 0) {
    u8* gb = (u8*)&gOverworld;
    asm("" : "+r"(gb));
    (*(gb + 0x2D02C))++;
  }
  *(u32*)((u8*)p + 0xb4) = (p->s).coord.y;
  CarrybeeG_Update(p);
}

extern const EnemyFunc sUpdates1[5];
extern const EnemyFunc sUpdates2[5];
void CarrybeeG_Die(struct Enemy* p);

void CarrybeeG_Update(struct Enemy* p) {
  struct Entity* par;
  u8* t;
  if (((p->body).status & BODY_STATUS_DEAD) && (p->s).work[0] == 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    CarrybeeG_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  if ((p->s).work[0] != 0) {
    if (IsFrozen(&p->s)) {
      par = (p->s).unk_28;
      if (par->mode[0] > 2) {
        (p->body).status = 0;
        (p->body).prevStatus = 0;
        (p->body).invincibleTime = 0;
        (p->s).flags &= ~COLLIDABLE;
        (p->s).flags &= ~DISPLAY;
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).work[1] = 1;
        return;
      } else if (par->mode[0] > 1) {
        s32 blink;
        (p->s).coord = par->coord;
        blink = (p->s).work[2] + 1;
        (p->s).work[2] = blink;
        blink &= 0xff;
        if (blink & 1) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
        (p->body).status = 0;
        (p->body).prevStatus = 0;
        (p->body).invincibleTime = 0;
        (p->s).flags &= ~COLLIDABLE;
        UpdateMotionGraphic(&p->s);
      }
    }
  }
  if (IsFrozen(&p->s)) {
    return;
  }
  if ((p->s).work[0] != 0) {
    goto dispatch2;
  }
  {
    struct Entity** s = (struct Entity**)((u8*)p + 0xbc);
    if (*s != NULL) {
      if ((*s)->mode[0] > 1) {
        *s = NULL;
      }
      t = (u8*)((u8*)p + 0xc0);
      if (*t == 0 || --*t == 0) {
        *(u8*)((u8*)*s + 0x25) = 0x18;
      }
    }
  }
  if ((p->s).unk_2c != NULL) {
    if (((p->s).unk_2c)->mode[0] > 1) {
      (p->s).unk_2c = NULL;
    }
    t = (u8*)((u8*)p + 0xc1);
    if (*t == 0 || --*t == 0) {
      *(u8*)((u8*)(p->s).unk_2c + 0x25) = 0x18;
    }
  }
  if ((p->s).unk_28 != NULL) {
    if (((p->s).unk_28)->mode[0] > 1) {
      (p->s).unk_28 = NULL;
    }
    t = (u8*)((u8*)p + 0xc2);
    if (*t == 0 || --*t == 0) {
      *(u8*)((u8*)(p->s).unk_28 + 0x25) = 0x18;
    }
  }
dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/carrybee_g_p1_p1_b_p1.inc");

void CarrybeeG_Disappear(struct Enemy* p) {
  if ((p->s).work[0] == 0 && *(u8*)((u8*)p + 0xc3) == 1) {
    gOverworld.work.raw[4]--;
  }
  DeleteEnemy(&p->s);
}

bool8 FUN_0808af78(struct Enemy* p) { return TRUE; }

#include "stagerun.h"
#include "camera.h"
#include "zero.h"

// 0x0808AF7C
void FUN_0808af7c(struct Enemy* p) {
  u8 m;
  {
    s32* pb4 = (s32*)((u8*)p + 0xb4);
    struct Camera* cam = &gStageRun.vm.camera;
    *pb4 = cam->viewport.y - 0x4000;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      *(s32*)((u8*)p + 0xb8) = m;
      (p->s).unk_coord.x = (pZero2->s).coord.x;
      (p->s).d.x = 0x4600;
      SetMotion(&p->s, 0x6E00);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = m;
      (p->s).mode[2]++;
    case 1: {
      s32 y = (p->s).coord.y + 0x200;
      (p->s).coord.y = y;
      if (y > *(s32*)((u8*)p + 0xb4)) {
        u8 z;
        (p->s).unk_coord.y = y;
        z = 0;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 FUN_0808b008(struct Enemy* p) { return TRUE; }

// 0x0808B00C
void carrybeeg_0808b00c(struct Enemy* p) {
  {
    s32* dst = (s32*)((u8*)p + 0xb4);
    struct Camera* cam = &gStageRun.vm.camera;
    *dst = cam->viewport.y - 0x4000;
  }
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[3] = 0x40;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register s32 w2 asm("r4");
      {
        register s32 t asm("r0");
        t = (p->s).work[2];
        asm volatile("add %0, %1, #1" : "=&l"(w2) : "l"(t));
      }
      (p->s).work[2] = w2;
      {
        s32 tgt = *(s32*)((u8*)p + 0xb4);
        s32 uy = (p->s).unk_coord.y;
        uy += ((tgt - uy) << 3) >> 8;
        (p->s).unk_coord.y = uy;
        {
          s32 sv = gSineTable[(p->s).work[2]];
          (p->s).coord.y = uy + ((sv << 4) - sv);
        }
      }
      if ((p->s).work[3] != 0) {
        s32 nw = (p->s).work[3] - 1;
        (p->s).work[3] = nw;
        if ((u8)nw != 0) {
          goto tick;
        }
      }
      if (*(u32*)((u8*)p + 0xbc) != 0 && (p->s).unk_2c != NULL && (p->s).unk_28 != NULL) {
        goto reset;
      }
      if (gEnemyHeaderPtr->length - gEnemyHeaderPtr->remaining > 5) {
        goto reset;
      }
      if (gCurStory.s.gameflags[4] & 0x42) {
        goto reset;
      }
      if (gCurStory.s.gameflags[0] & 0x10) {
        u32 v = gSystemSavedataManager.mmbn4;
        if (v != 0x32DA && v != 0) {
          goto reset;
        }
      }
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      goto upd;
    reset:
      (p->s).work[3] = 0x40;
      goto upd;
    tick:
      {
        register s32 c asm("r0");
        c = w2 << 24;
        c = (s32)((u32)c >> 24);
        if (c != 0x40) {
          goto upd;
        }
      }
      {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 FUN_0808b108(struct Enemy* p) { return TRUE; }

struct Enemy* CreatePantheonHunter(struct Coord* c, u8 a1, u8 a2);

// 0x0808B10C
void FUN_0808b10c(struct Enemy* p) {
  {
    register struct Camera* cam asm("r0");
    register s32 k asm("r2");
    register s32* tp asm("r1");
    tp = (s32*)((u8*)p + 0xb4);
    cam = &gStageRun.vm.camera;
    k = -0x4000;
    *tp = cam->viewport.y + k;
  }
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x6E01);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).work[2]++;
      {
        register s32 y asm("r1");
        register s32 d asm("r0");
        d = *(s32*)((u8*)p + 0xb4);
        y = (p->s).unk_coord.y;
        d -= y;
        d <<= 3;
        d >>= 8;
        y += d;
        (p->s).unk_coord.y = y;
        {
          register const s16* tb asm("r2");
          register s32 o asm("r0");
          register s32 sv asm("r2");
          tb = gSineTable;
          o = (p->s).work[2];
          o <<= 1;
          o += (s32)tb;
          {
            register s32 zi asm("r3");
            zi = 0;
            sv = *(const s16*)(o + zi);
          }
          o = sv << 4;
          o -= sv;
          y += o;
          (p->s).coord.y = y;
        }
      }
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) == 3) {
        goto tramp;
      }
      break;
    tramp:
      asm volatile("");
      goto bump;
    case 2:
      (p->s).work[3] = 0xa;
      goto bump2;
    case 4: {
      struct Coord c;
      register struct Enemy** slot asm("r5");
      (p->s).work[3] = 0xa;
      {
        register s32 a0 asm("r0");
        register s32 b0 asm("r1");
        a0 = (p->s).coord.x;
        asm("" : "+r"(a0));
        b0 = (p->s).coord.y;
        c.x = a0;
        c.y = b0;
      }
      asm("" ::: "memory");
      {
        register s32 k asm("r1");
        k = -0xa00;
        c.x += k;
      }
      asm("" ::: "memory");
      {
        register s32 k2 asm("r2");
        k2 = 0xd8 << 5;
        c.y += k2;
      }
      asm("" ::: "memory");
      slot = (struct Enemy**)((u8*)p + 0xbc);
      if (*slot == NULL) {
        register struct Enemy* e asm("r0");
        register u8* tc asm("r0");
        register u8* fp asm("r1");
        e = CreatePantheonHunter(&c, 2, 0);
        *slot = e;
        tc = (u8*)e + 0x25;
        *tc = 0x15;
        fp = (u8*)p + 0xc0;
        goto mark;
      } else if ((p->s).unk_2c == NULL) {
        register struct Enemy* e asm("r0");
        register u8* tc asm("r0");
        register u8* fp asm("r1");
        e = CreatePantheonHunter(&c, 2, 0);
        (p->s).unk_2c = (struct Entity*)e;
        tc = (u8*)e + 0x25;
        *tc = 0x15;
        fp = (u8*)p + 0xc1;
      mark:
        *fp = 0x20;
      } else if ((p->s).unk_28 == NULL) {
        register struct Enemy* e asm("r0");
        register u8* tc asm("r0");
        register u8* fp asm("r1");
        e = CreatePantheonHunter(&c, 2, 0);
        (p->s).unk_28 = (struct Entity*)e;
        tc = (u8*)e + 0x25;
        *tc = 0x15;
        fp = (u8*)p + 0xc2;
        *fp = 0x20;
      }
      SetMotion(&p->s, 0x6E03);
    bump2:
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
    case 5:
      (p->s).work[2]++;
      {
        register s32 y asm("r1");
        register s32 d asm("r0");
        d = *(s32*)((u8*)p + 0xb4);
        y = (p->s).unk_coord.y;
        d -= y;
        d <<= 3;
        d >>= 8;
        y += d;
        (p->s).unk_coord.y = y;
        {
          register const s16* tb asm("r2");
          register s32 o asm("r0");
          register s32 sv asm("r2");
          tb = gSineTable;
          o = (p->s).work[2];
          o <<= 1;
          o += (s32)tb;
          {
            register s32 zi asm("r3");
            zi = 0;
            sv = *(const s16*)(o + zi);
          }
          o = sv << 4;
          o -= sv;
          y += o;
          (p->s).coord.y = y;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[3] != 0) {
        if ((u8)--(p->s).work[3] != 0) {
          break;
        }
      }
    bump:
      (p->s).mode[2]++;
      break;
    case 6: {
      register s32 z asm("r1");
      z = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z;
      break;
    }
  }
}


bool8 FUN_0808b2b0(struct Enemy* p) { return TRUE; }

#include "stagerun.h"
#include "camera.h"
#include "trig.h"

struct Projectile* FUN_080adad0(struct Coord* c, u8 a1);

void FUN_0808b2b4(struct Enemy* p) {
  {
    s32* pb4 = (s32*)((u8*)p + 0xb4);
    struct Camera* cam = &gStageRun.vm.camera;
    *pb4 = cam->viewport.y - 0x4000;
  }
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x6E04);
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 t = *(s32*)((u8*)p + 0xb4);
      s32 acc = (p->s).unk_coord.y;
      acc += ((t - acc) << 3) >> 8;
      (p->s).unk_coord.y = acc;
      (p->s).coord.y = acc + gSineTable[(p->s).work[2]] * 15;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2:
      (p->s).work[3] = 0xA;
      goto inc2;
    case 4: {
      struct Coord c;
      (p->s).work[3] = 0xA;
      {
        s32 xv = (p->s).coord.x;
        s32 yv = (p->s).coord.y;
        *(volatile s32*)&c.x = xv;
        *(volatile s32*)&c.y = yv;
      }
      *(volatile s32*)&c.x = *(volatile s32*)&c.x + 0x2B00;
      *(volatile s32*)&c.y = *(volatile s32*)&c.y + 0x300;
      FUN_080adad0(&c, 0);
      SetMotion(&p->s, 0x6E05);
    }
    inc2:
      (p->s).mode[2]++;
      // fallthrough
    case 3:
    case 5: {
      s32 t = *(s32*)((u8*)p + 0xb4);
      s32 acc = (p->s).unk_coord.y;
      s32 w3;
      acc += ((t - acc) << 3) >> 8;
      (p->s).unk_coord.y = acc;
      (p->s).coord.y = acc + gSineTable[(p->s).work[2]] * 15;
      UpdateMotionGraphic(&p->s);
      w3 = (p->s).work[3];
      if (w3 != 0) {
        w3 -= 1;
        (p->s).work[3] = w3;
        if ((w3 << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    }
    case 6: {
      s32 t = *(s32*)((u8*)p + 0xb4);
      s32 acc = (p->s).unk_coord.y;
      s32 z;
      acc += ((t - acc) << 3) >> 8;
      (p->s).unk_coord.y = acc;
      (p->s).coord.y = acc + gSineTable[(p->s).work[2]] * 15;
      z = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z;
      break;
    }
  }
}

bool8 FUN_0808b418(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[9];

void FUN_0808b41c(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  if (q->mode[0] > 2) {
    EXIT_BODY(p);
    (p->s).flags &= ~DISPLAY;
    goto tail;
  } else if (FLAG(gCurStory.s.gameflags, 38)) {
    (p->s).flags &= ~DISPLAY;
    EXIT_BODY(p);
  tail:
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).work[1] = 1;
    CarrybeeG_Die(p);
  } else {
    s32 md = (p->s).mode[2];
    switch (md) {
      case 0:
        (p->s).flags2 |= 0x10;
        (p->s).invincibleID = q->uniqueID;
        SetMotion(&p->s, MOTION(0x6E, 0x06));
        SetDDP(&p->body, sCollisions);
        (p->s).work[2] = md;
        (p->s).mode[2]++;
        /* fallthrough */
      case 1: {
        struct Entity* q2 = (p->s).unk_28;
        s32 qy = q2->coord.y;
        (p->s).coord.x = q2->coord.x;
        (p->s).coord.y = qy;
      }
        UpdateMotionGraphic(&p->s);
        if ((p->s).unk_28->mode[0] > 1) {
          (p->s).mode[2]++;
        }
        return;
      case 2: {
        s32 t;
        s32 qx = q->coord.x;
        s32 qy = q->coord.y;
        (p->s).coord.x = qx;
        (p->s).coord.y = qy;
        t = (p->s).work[2] + 1;
        (p->s).work[2] = t;
        t &= 0xFF;
        if (t & 1) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
        (p->s).flags &= ~DISPLAY;
        UpdateMotionGraphic(&p->s);
        return;
      }
      default:
        return;
    }
  }
}

void nop_0808b534(struct Enemy* p) {}


bool8 FUN_0808af78(struct Enemy* p);
bool8 FUN_0808b008(struct Enemy* p);
bool8 FUN_0808b108(struct Enemy* p);
bool8 FUN_0808b2b0(struct Enemy* p);
bool8 FUN_0808b418(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[5] = {
    (EnemyFunc)FUN_0808af78,
    (EnemyFunc)FUN_0808b008,
    (EnemyFunc)FUN_0808b108,
    (EnemyFunc)FUN_0808b2b0,
    (EnemyFunc)FUN_0808b418,
};
// clang-format on

void FUN_0808af7c(struct Enemy* p);
void carrybeeg_0808b00c(struct Enemy* p);
void FUN_0808b10c(struct Enemy* p);
void FUN_0808b2b4(struct Enemy* p);
void FUN_0808b41c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[5] = {
    FUN_0808af7c,
    carrybeeg_0808b00c,
    FUN_0808b10c,
    FUN_0808b2b4,
    FUN_0808b41c,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[9] = {
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
      remaining : 7,
      layer : 0x00000001,
      range : {PIXEL(30), -PIXEL(4), PIXEL(69), PIXEL(39)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 6,
      range : {PIXEL(30), -PIXEL(4), PIXEL(69), PIXEL(39)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 5,
      layer : 0x00000001,
      range : {-PIXEL(36), -PIXEL(7), PIXEL(62), PIXEL(22)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 4,
      range : {-PIXEL(36), -PIXEL(7), PIXEL(62), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {-PIXEL(18), PIXEL(10), PIXEL(26), PIXEL(11)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 2,
      range : {-PIXEL(18), PIXEL(10), PIXEL(26), PIXEL(11)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(6), PIXEL(23), PIXEL(57), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(6), PIXEL(23), PIXEL(57), PIXEL(16)},
    },
};
