#include "collision.h"
#include "enemy.h"
#include "mission.h"
#include "global.h"
#include "physics.h"
#include "stagerun.h"
#include "story.h"
#include "mod.h"
#include "syssav.h"

static const EnemyFunc sDeads[4];

void FUN_0808d0b0(s32 x, s32 y, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_DEATHLOCK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = mode;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

void FUN_0808d10c(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_DEATHLOCK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 9;
    (p->s).unk_28 = e;
  }
}

// Wall probe: shifts by dx, takes three pushouts at y/-0xF00/-0x1E00,
// sorts them (descending left-arm, ascending right-arm) and applies the
// extreme. Retail keeps the sort index i in r0 (disjoint from the pj
// walker) while agbcc coalesces i into the pi register (allocation tie;
// pins/barriers shift but never split them).
NON_MATCH s32 FUN_0808d160(struct Enemy* p, s32 dx) {
#if MODERN
  s32 r[3];
  s32 i;
  (p->s).coord.x += dx;
  if (dx < 0) {
    r[0] = PushoutToRight1((p->s).coord.x - 0x1200, (p->s).coord.y);
    r[1] = PushoutToRight1((p->s).coord.x - 0x1200, (p->s).coord.y - 0xF00);
    r[2] = PushoutToRight1((p->s).coord.x - 0x1200, (p->s).coord.y - 0x1E00);
    i = 0;
    while (i <= 1) {
      s32 j0 = i + 1;
      s32 j = j0;
      if (j0 <= 2) {
        s32* pi = &r[i];
        s32* pj = &r[j0];
        for (; j <= 2; j++, pj++) {
          s32 a = *pi;
          s32 b = *pj;
          if (a < b) {
            *pi = b;
            *pj = a;
          }
        }
      }
      i = j0;
    }
    if (r[0] > 0) {
      (p->s).coord.x += r[0];
      return 1;
    }
  } else {
    r[0] = PushoutToLeft1((p->s).coord.x + 0x1200, (p->s).coord.y);
    r[1] = PushoutToLeft1((p->s).coord.x + 0x1200, (p->s).coord.y - 0xF00);
    r[2] = PushoutToLeft1((p->s).coord.x + 0x1200, (p->s).coord.y - 0x1E00);
    i = 0;
    while (i <= 1) {
      s32 j0 = i + 1;
      s32 j = j0;
      if (j0 <= 2) {
        s32* pi = &r[i];
        s32* pj = &r[j0];
        for (; j <= 2; j++, pj++) {
          s32 a = *pi;
          s32 b = *pj;
          if (a > b) {
            *pi = b;
            *pj = a;
          }
        }
      }
      i = j0;
    }
    if (r[0] < 0) {
      (p->s).coord.x += r[0];
      return 2;
    }
  }
  return 0;
#else
  INCCODE("asm/enemy/deathlock_d160.inc");
#endif
}

// 0x0808D268
NON_MATCH bool8 FUN_0808d268(struct Enemy* p, s32 dy) {
#if MODERN
  s32 y = (p->s).coord.y + dy;
  (p->s).coord.y = y;
  if (dy < 0) {
    s32 a = PushoutToDown1((p->s).coord.x - 0x1200, y - 0x1E00);
    s32 b = PushoutToDown1((p->s).coord.x + 0x1200, (p->s).coord.y - 0x1E00);
    if (a < b) {
      a = b;
    }
    if (a > 0) {
      (p->s).coord.y += a;
      return 1;
    }
  } else {
    s32 a = PushoutToUp1((p->s).coord.x - 0x1200, y);
    s32 b = PushoutToUp1((p->s).coord.x + 0x1200, (p->s).coord.y);
    if (a > b) {
      a = b;
    }
    if (a < 0) {
      (p->s).coord.y += a;
      return 2;
    }
  }
  return 0;
#else
  INCCODE("asm/enemy/deathlock_0808d268.inc");
#endif
}

void nop_0808d2f4(struct Enemy* p) {}

void Deathlock_Die(struct Enemy* p);

bool8 FUN_0808d2f8(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->s).work[0] == 9) {
      (p->s).mode[1] = 0;
    } else if ((p->body).status & 0x10000) {
      p->props[7] = 1;
      (p->s).mode[1] = 2;
    } else {
      p->props[7] = 0;
      if ((p->body).status & 0x20000) {
        (p->s).mode[1] = 3;
      } else {
        (p->s).mode[1] = 1;
      }
    }
    Deathlock_Die(p);
    return TRUE;
  }
  return FALSE;
}

u32 FUN_0800a40c(s32 x, s32 y);
static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];
static const motion_t sMotions1[6];
static const u8 sCollisionIdxs1[6];
extern const struct Collision sCollisions[15];

bool8 FUN_0808d370(struct Enemy* p) {
  s32 m1;
  u32 fz;
  if ((p->s).mode[1] == 6) {
    goto rf;
  }
  if ((p->s).work[0] == 9) {
    goto rf;
  }
  if (*(s32*)&p->props[0] != 0) {
    goto rf;
  }
  switch ((p->s).mode[3]) {
    case 0:
      if (!IsFrozen(&p->s)) {
        goto rf;
      }
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
      if ((p->s).mode[1] == 3) {
        SetDDP(&p->body, &sCollisions[sCollisionIdxs1[p->props[5]]]);
        SetMotion(&p->s, sMotions1[p->props[5]]);
      }
      (p->s).mode[3]++;
      UpdateMotionGraphic(&p->s);
    rt:
      return TRUE;
    case 1:
      fz = IsFrozen(&p->s);
      if (fz == 0) {
        goto storef;
      }
      {
        s32 hit = FUN_0800a40c((p->s).coord.x - 0x1200, (p->s).coord.y + 0x400);
        if (hit == 0) {
          hit = FUN_0800a40c((p->s).coord.x + 0x1200, (p->s).coord.y + 0x400);
          if (hit == 0) {
            goto skip;
          }
        }
        FUN_0808d160(p, hit);
      }
    skip:
      m1 = (p->s).mode[1];
      asm("" : "+r"(m1));
      if (m1 == 3) {
        (p->s).unk_coord.x = (p->s).coord.x;
      }
      if ((p->s).work[0] == 8) {
        goto rt;
      }
      if (m1 == 3) {
        goto rt;
      }
      if (((p->body).status & 0x20001) != 0x20001) {
        goto rt;
      }
      (p->s).mode[3] = 0;
      return FALSE;
    default:
      goto rf;
  }
storef:
  (p->s).mode[3] = fz;
rf:
  return FALSE;
}


#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_0808d4a0(struct Enemy* p) {
  struct VFX** slot;
  u32 frozen;

  if ((p->s).work[0] != 8 && (p->s).work[0] != 9) {
    slot = (struct VFX**)&p->props[0];
    if (*slot == NULL && ((p->body).status & 1)) {
      frozen = (p->body).status & 0x20000;
      if (frozen != 0) {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      } else {
        *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
        if (*slot != NULL) {
          (p->s).mode[1] = 0;
          (p->s).mode[2] = 0;
        }
      }
    }
  }
}

void nop_0808d2f4(struct Enemy* p);
void Deathlock_Update(struct Enemy* p);
extern const struct Collision sCollisions[15];

void Deathlock_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).work[1] = 1;
  if ((p->s).work[0] == 8) {
    (p->s).mode[1] = 7;
    (p->s).coord.y += -0x800;
  } else if ((p->s).work[0] == 9) {
    (p->s).mode[1] = 5;
  } else {
    (p->s).mode[1] = 1;
  }
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  {
    if ((p->s).work[0] <= 7) {
      s32 sf;
      s32 c40;
      if (!MOD_ENABLED(gSystemSavedataManager.mods, MOD_119)) goto arm2;
      sf = gCurStory.s.gameflags[0];
      c40 = 0x40;
      asm("" : "+r"(c40));
      if (c40 & sf) goto arm2;
      {
        struct Body* body;
        (p->s).flags |= COLLIDABLE;
        body = &p->body;
        InitBody(body, sCollisions, &(p->s).coord, 0xE);
        body->parent = (void*)p;
        {
          register s32 z0 asm("r0");
          z0 = 0;
          asm("" : "+r"(z0));
          body->fn = (void*)z0;
        }
      }
      goto setnop;
    arm2:
      {
        struct Body* body;
        s32 z;
        register s32 c4 asm("r0");
        register s32 f asm("r1");
        f = (p->s).flags;
        c4 = 4;
        asm("" : "+r"(c4));
        z = 0;
        (p->s).flags = c4 | f;
        body = &p->body;
        InitBody(body, sCollisions, &(p->s).coord, 0xA);
        body->parent = (void*)p;
        body->fn = (void*)z;
      }
    setnop:
      {
        struct Body* body = &p->body;
        body->fn = (void*)nop_0808d2f4;
      }
    } else if ((p->s).work[0] == 9) {
      struct Body* body;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 4);
      body->parent = (void*)p;
      body->fn = (void*)nop_0808d2f4;
    }
  }
  *(s32*)&p->props[0] = 0;
  {
    u8 w = (p->s).work[0];
    if (w <= 3) {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      goto pw;
    }
    {
      u32 w2 = w - 4;
      if ((u8)w2 <= 3) {
        (p->s).work[0] = w2;
        (p->s).work[1] = 1;
      }
    }
  }
pw:
  p->props[4] = 0;
  p->props[5] = 0;
  p->props[6] = 0;
  p->props[8] = 0;
  Deathlock_Update(p);
}

static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];
bool8 FUN_0808d2f8(struct Enemy* p);
void FUN_0808d4a0(struct Enemy* p);
bool8 FUN_0808d370(struct Enemy* p);

void Deathlock_Update(struct Enemy* p) {
  if ((p->s).work[0] != 8 && (gCurStory.s.gameflags[4] & 2)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    (p->s).flags &= ~COLLIDABLE;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (FUN_0808d2f8(p)) {
    return;
  }
  FUN_0808d4a0(p);
  if (FUN_0808d370(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Deathlock_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_0808d6f4(struct Enemy* p) {}

extern const struct Collision sCollisions[15];
extern const u8 sCollisionIdxs1[6];
extern const u8 sCollisionIdxs2[6];

void FUN_0808d6f8(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[sCollisionIdxs1[*(u8*)((u8*)p + 0xb9)]]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x20001) == 0x20001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

void FUN_0808d76c(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

// 0x0808D78C
void FUN_0808d78c(struct Enemy* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8* k asm("r6");
      const u16* tb = sMotions1;
      k = (u8*)&p->props[5];
      SetMotion(&p->s, tb[*k]);
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[sCollisionIdxs2[*k]]);
      (p->s).d.y = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 hit asm("r5");
      register u32 fz asm("r6");
      hit = FUN_0800a40c((p->s).coord.x - 0x1200, (p->s).coord.y + 0x400);
      if (hit == 0) {
        hit = FUN_0800a40c((p->s).coord.x + 0x1200, (p->s).coord.y + 0x400);
        if (hit == 0) {
          goto skip;
        }
      }
      FUN_0808d160(p, hit);
    skip:
      fz = IsFrozen(&p->s);
      if (fz != 0) {
        break;
      }
      if (((u8)FUN_0808d268(p, 1)) == 0) {
        (p->s).d.y += 0x40;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        FUN_0808d268(p, 1);
      } else {
        (p->s).d.y = fz;
        if ((p->s).work[1] != 0 && hit == 0) {
          register s32 one asm("r2");
          register u8* a asm("r0");
          a = (u8*)p + 0xbb;
          *a = hit;
          asm volatile("add %0, #1" : "+r"(a));
          one = 1;
          *a = one;
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          (p->s).mode[1] = one;
        }
      }
      break;
    }
  }
}

INCASM("asm/enemy/deathlock_post_p2a.inc");

bool8 FUN_0808d268(struct Enemy* p, s32 dy);
void FUN_0808da24(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[sCollisionIdxs1[*(u8*)((u8*)p + 0xb9)]]);
      (p->s).d.y = 0;
      if (*(u8*)((u8*)p + 0xb9) != 0) {
        SetMotion(&p->s, sMotions1[*(u8*)((u8*)p + 0xb9)]);
      } else {
        SetMotion(&p->s, MOTION(SM116_DEATHLOCK, 0));
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (FUN_0808d268(p, (p->s).d.y)) {
        (*(u8*)((u8*)p + 0xb8))++;
        if (FUN_0800a40c((p->s).coord.x - 0x1200, (p->s).coord.y + 0x400) != 0 ||
            FUN_0800a40c((p->s).coord.x + 0x1200, (p->s).coord.y + 0x400) != 0) {
          (p->s).mode[1] = 1;
          {
            u32 zz = 0;
            asm("" : "+r"(zz));
            (p->s).mode[2] = zz;
          }
        } else {
          u8* q;
          *(u8*)((u8*)p + 0xbb) = 0;
          q = (u8*)p + 0xbc;
          asm("" : "+r"(q));
          {
            register s32 one asm("r2");
            one = 1;
            asm("" : "+r"(one));
            *q = one;
            SET_ENEMY_ROUTINE(p, ENTITY_DIE);
            (p->s).mode[1] = one;
          }
        }
      }
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000) {
        u32 f = (p->s).flags & 0xFE;
        s32 z = 0;
        asm("" : "+r"(f));
        (p->s).flags = f & 0xFD;
        (p->body).status = z;
        (p->body).prevStatus = z;
        (p->body).invincibleTime = z;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

INCASM("asm/enemy/deathlock_post_p2b.inc");

// 0x0808DD7C
void FUN_0808dd7c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x18;
      SetMotion(&p->s, 0x7402);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        FUN_0808d10c(&p->s);
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetMotion(&p->s, 0x7403);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u8* a = (u8*)p + 0xba;
        s32 z = 0;
        s32 k = 0x20;
        *a = k;
        k = 1;
        (p->s).mode[1] = k;
        (p->s).mode[2] = z;
      }
      break;
  }
  {
    s32 hit = FUN_0800a40c((p->s).coord.x - 0x1200, (p->s).coord.y + 0x400);
    if (hit == 0) {
      hit = FUN_0800a40c((p->s).coord.x + 0x1200, (p->s).coord.y + 0x400);
      if (hit == 0) {
        goto skip;
      }
    }
    if ((u8)FUN_0808d160(p, hit) != 0) {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = 0;
    }
  }
skip:
  {
    u8 r = (u8)FUN_0808d268(p, 1);
    if (r == 0) {
      (p->s).mode[1] = 2;
      (p->s).mode[2] = r;
    }
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000) {
    register u8 g asm("r0");
    register u8 h asm("r1");
    register s32 zr asm("r2");
    u8* a;
    h = (p->s).flags;
    asm("" : "+r"(h));
    g = 0xFE;
    g &= h;
    zr = 0;
    h = 0xFD;
    g &= h;
    (p->s).flags = g;
    a = (u8*)p + 0x8c;
    *(s32*)a = zr;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *(s32*)a = zr;
    asm("" : "+r"(a));
    a += 4;
    asm("" : "+r"(a));
    *a = zr;
    (p->s).flags &= ~4;
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

extern struct Zero* pZero2;

// 0x0808DEB8
void FUN_0808deb8(struct Enemy* p) {
  register struct Entity* q asm("r5");
  q = (p->s).unk_28;
  if (q != NULL) {
    if (q->mode[0] > 1) {
      q = NULL;
      (p->s).unk_28 = q;
    }
  }
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x83 * 2);
      SetDDP(&p->body, (const struct Collision*)0x083691B0);
      {
        register u8* a asm("r1");
        register s32 v asm("r0");
        a = (u8*)p + 0x25;
        v = 0x19;
        *a = v;
      }
      (p->s).unk_coord.y = -0x1C00;
      (p->s).work[2] = 0x20;
      SetMotion(&p->s, MOTION(0x74, 0x10));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t;
      {
        register s32 cx asm("r2");
        register u32* rp asm("r3");
        register u32 rnd asm("r1");
        register u32 acc asm("r0");
        u32 rv;
        cx = q->coord.x + -0x200;
        rp = &RNG_0202f388;
        asm("" : "+r"(rp));
        rnd = *rp;
        acc = 0x343FD;
        acc *= rnd;
        acc += 0x269EC3;
        rv = acc << 1;
        asm("" : "+r"(rv));
        *rp = rv >> 1;
        rv <<= 5;
        rv >>= 0x16;
        cx += rv;
        (p->s).coord.x = cx;
      }
      {
        register s32 uy asm("r1");
        register s32 qy asm("r0");
        qy = q->coord.y;
        uy = (p->s).unk_coord.y;
        qy += uy;
        (p->s).coord.y = qy;
        uy -= 0x80;
        (p->s).unk_coord.y = uy;
      }
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        goto adv;
      }
      if (q != NULL) {
        goto upd;
      }
    adv:
      (p->s).mode[2]++;
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      register s32 dx asm("r2");
      SetDDP(&p->body, sCollisions);
      {
        register s32 k asm("r0");
        k = -0x200;
        (p->s).d.x = k;
        dx = k;
        if ((p->s).coord.x < pZero2->s.coord.x) {
          dx = 0x80 * 4;
        }
        (p->s).d.x = dx;
      }
      {
        register s32 sq asm("r0");
        sq = ((s32(*)(u32))Sqrt)(0xC0 * 2);
        (p->s).work[2] = sq;
      }
      (p->s).d.y = -((p->s).work[2] << 6);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0xE0 * 8) {
        (p->s).d.y = 0xE0 * 8;
      }
      {
        register s32 cy asm("r1");
        register s32 dyv asm("r0");
        cy = (p->s).coord.y;
        dyv = (p->s).d.y;
        cy += dyv;
        (p->s).coord.y = cy;
        if (((u16)FUN_080098a4((p->s).coord.x, cy) << 16) == 0) {
          break;
        }
      }
      {
        register u8* a2 asm("r1");
        register s32 zz asm("r2");
        register s32 one asm("r0");
        a2 = (u8*)p + 0xbc;
        zz = 0;
        one = 1;
        *a2 = one;
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = zz;
      }
      break;
  }
}

void maybeKillDeathlock(struct Enemy* p);

// 0x0808E01C
void FUN_0808e01c(struct Enemy* p) {
  register s32 z asm("r4");
  register u32* st asm("r6");
  switch ((p->s).mode[2]) {
    case 0: {
      register u8* ix asm("r4");
      register s32 d asm("r6");
      {
        register const u16* tb asm("r1");
        tb = (const u16*)0x08369300;
        asm("" : "+r"(tb));
        ix = (u8*)p + 0xb9;
        SetMotion(&p->s, tb[*ix]);
      }
      {
        register struct Body* bd asm("r0");
        register const u8* tb2 asm("r2");
        register u32 k asm("r1");
        bd = &p->body;
        tb2 = (const u8*)0x0836930C;
        asm("" : "+r"(tb2));
        k = *ix;
        k += (u32)tb2;
        {
          register u8 kk asm("r2");
          register s32 off asm("r1");
          kk = *(const u8*)k;
          off = kk << 1;
          off += kk;
          off <<= 3;
          {
            register u32 base asm("r2");
            base = (u32)sCollisions;
            off += base;
          }
          SetDDP(bd, (const struct Collision*)off);
        }
      }
      UpdateMotionGraphic(&p->s);
      {
        register struct Zero* zz asm("r2");
        register s32 dx asm("r1");
        register s32 t0 asm("r0");
        register s32 dy asm("r0");
        zz = pZero2;
        dx = (p->s).coord.x;
        t0 = (zz->s).coord.x;
        dx -= t0;
        (p->s).d.x = dx;
        dy = (p->s).coord.y;
        {
          register s32 kk2 asm("r3");
          kk2 = 0xFFFFE800;
          dy += kk2;
        }
        {
          register s32 zy asm("r2");
          zy = (zz->s).coord.y;
          dy -= zy;
        }
        (p->s).d.y = dy;
        dx >>= 8;
        d = dx * dx;
        dy >>= 8;
        d += dy * dy;
      }
      d = (u16)Sqrt(d) << 8;
      if (d != 0) {
        register s32 q asm("r4");
        q = ((p->s).d.x << 8) / d;
        (p->s).d.x = q;
        {
          register s32 q2 asm("r0");
          q2 = ((p->s).d.y << 8) / d;
          (p->s).d.x = ((q << 1) + q) << 1;
          (p->s).d.y = ((q2 << 1) + q2) << 1;
        }
      } else {
        (p->s).d.x = 0xc0 << 3;
        (p->s).d.y = d;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if (((u8)FUN_0808d160(p, (p->s).d.x) << 24) != 0) {
        goto kill;
      }
      st = (u32*)((u8*)p + 0x8c);
      z = *st & 4;
      if (z != 0) {
      kill:
        *((u8*)p + 0xbb) = 0;
        maybeKillDeathlock(p);
        break;
      }
      {
        register s32 dy asm("r0");
        register s32 lim asm("r1");
        dy = (p->s).d.y + 0x40;
        (p->s).d.y = dy;
        lim = 0xe0 << 3;
        if (dy > lim) {
          (p->s).d.y = lim;
        }
      }
      if (((u8)FUN_0808d268(p, (p->s).d.y) << 24) != 0) {
        *((u8*)p + 0xbb) = z;
        maybeKillDeathlock(p);
      }
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) <= (0xc0 << 7)) {
        break;
      }
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFE;
        g &= h;
        h = 0xFD;
        g &= h;
        (p->s).flags = g;
      }
      *st = z;
      {
        u8* a = (u8*)p + 0x90;
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z;
      }
      (p->s).flags &= 0xFB;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
  }
}


#include "zero.h"

// 0x0808e18c
void FUN_0808e18c(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).work[2] = 0x40;
      (p->s).work[3] = m;
      SetMotion(&p->s, MOTION(0x76, 0x00));
      (p->s).taskCol = 0x17;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        s32 x;
        struct Zero* z;
        (p->s).work[2] = 0xc0;
        z = pZero2;
        x = (p->s).coord.x;
        if (x < (z->s).coord.x) {
          s32 y = (p->s).coord.y + 0x1700;
          u8 w3 = (p->s).work[3];
          s32 a = 7;
          if (w3 == 1) {
            a = 5;
          }
          FUN_0808d0b0(x, y, a);
        } else {
          s32 y = (p->s).coord.y + 0x1700;
          u8 w3 = (p->s).work[3];
          s32 a = 6;
          if (w3 == 1) {
            a = 4;
          }
          FUN_0808d0b0(x, y, a);
        }
        (p->s).work[3]++;
        (p->s).work[3] = (p->s).work[3] % 3;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

extern void FUN_080b7f70(struct Enemy* p, struct Coord* c, const motion_t* m, s32 n);
static const motion_t sMotions2[4];

// 0x0808e228
void FUN_0808e228(struct Enemy* p) {
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
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  FUN_080b7f70(p, &c, sMotions2, 3);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void CreateGhost65(s32 x, s32 y, u8 w1, u8 w2);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x0808E294
void maybeKillDeathlock(struct Enemy* p) {
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
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  if (*(u8*)((u8*)p + 0xbb) == 0) {
    s32 i = *(u8*)((u8*)p + 0xb9);
    if (i <= 5) {
      do {
        CreateGhost65((p->s).coord.x, (p->s).coord.y, i, ((p->s).flags >> 4) & 1);
        i++;
      } while (i <= 5);
    }
  }
  if (*(u8*)((u8*)p + 0xbc) == 0) {
    u8 w0 = (p->s).work[0];
    struct Coord* pc = &(p->s).coord;
    if (w0 != 9) {
      TryDropItem(0, pc);
    }
    if (gMission.enemyCount <= 0x270E) {
      gMission.enemyCount++;
    }
    TryDropZakoDisk(p, pc);
  }
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/deathlock_post_p2b_b.inc");

void Deathlock_Init(struct Enemy* p);
void Deathlock_Update(struct Enemy* p);
void Deathlock_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gDeathlockRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Deathlock_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Deathlock_Update,
    [ENTITY_DIE] =       (EnemyFunc)Deathlock_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_0808d6f8(struct Enemy* p);
void FUN_0808d76c(struct Enemy* p);
void FUN_0808d6f4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    FUN_0808d6f8,
    FUN_0808d76c,
    FUN_0808d76c,
    FUN_0808d6f4,
    FUN_0808d76c,
    FUN_0808d6f4,
    FUN_0808d6f4,
    FUN_0808d6f4,
};
// clang-format on

void FUN_0808d78c(struct Enemy* p);
void FUN_0808d898(struct Enemy* p);
void FUN_0808da24(struct Enemy* p);
void FUN_0808db64(struct Enemy* p);
void FUN_0808dd7c(struct Enemy* p);
void FUN_0808deb8(struct Enemy* p);
void FUN_0808e01c(struct Enemy* p);
void FUN_0808e18c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    FUN_0808d78c,
    FUN_0808d898,
    FUN_0808da24,
    FUN_0808db64,
    FUN_0808dd7c,
    FUN_0808deb8,
    FUN_0808e01c,
    FUN_0808e18c,
};
// clang-format on

// --------------------------------------------

void FUN_0808e228(struct Enemy* p);
void maybeKillDeathlock(struct Enemy* p);
void FUN_0808e358(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_0808e228,
    maybeKillDeathlock,
    FUN_0808e358,
    FUN_0808e01c,
};

// --------------------------------------------

// 0x08369198
static const struct Collision sCollisions[15] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(14), PIXEL(34), PIXEL(33)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(14), PIXEL(34), PIXEL(33)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(9), -PIXEL(24), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 1,
      range : {PIXEL(9), -PIXEL(24), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(4), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(4), -PIXEL(8), PIXEL(34), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(8), PIXEL(19), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(8), -PIXEL(8), PIXEL(19), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(14), PIXEL(34), PIXEL(33)},
    },
};

// clang-format off
static const motion_t sMotions1[6] = {
    MOTION(SM116_DEATHLOCK, 1),
    MOTION(SM116_DEATHLOCK, 4),
    MOTION(SM116_DEATHLOCK, 5),
    MOTION(SM116_DEATHLOCK, 6),
    MOTION(SM116_DEATHLOCK, 7),
    MOTION(SM116_DEATHLOCK, 8),
};
// clang-format on

static const u8 sCollisionIdxs1[6] = {2, 4, 8, 10, 10, 12};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(12)};

static const u8 sCollisionIdxs2[6] = {3, 6, 9, 11, 11, 13};

static const motion_t sMotions2[4] = {
    MOTION(SM116_DEATHLOCK, 17),
    MOTION(SM116_DEATHLOCK, 18),
    MOTION(SM116_DEATHLOCK, 19),
    MOTION(SM116_DEATHLOCK, 14),
};
