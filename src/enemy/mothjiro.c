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

// 0x080885FC
void mothjiro_080885fc(struct Enemy* p0) {
  register struct Enemy* p asm("r6");
  s32 m;
  p = p0;
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, 0xd6 << 7);
      SetDDP(&p->body, (const struct Collision*)0x083687C8);
      (p->s).d = (p->s).unk_coord;
      (p->s).unk_coord.x = (p->s).coord.x;
      (p->s).unk_coord.y = (p->s).coord.y;
      {
        register u32* rng asm("r5");
        register u32 K asm("r3");
        register u32 C asm("r2");
        register u32 t asm("r0");
        register u32 h asm("r4");
        register s32 acc asm("r1");
        {
          register s32* q asm("r0");
          acc = *(s32*)((u8*)p + 0xb8);
          {
            register s32 k asm("r0");
            k = -0x1000;
            acc += k;
          }
          (void)q;
        }
        rng = &RNG_0202f388;
        t = *rng;
        K = 0x343FD;
        t = K * t;
        C = 0x269EC3;
        t += C;
        t <<= 1;
        h = t >> 1;
        t <<= 2;
        t >>= 0x13;
        acc += t;
        (p->s).unk_coord.x = acc;
        {
          register s32* q asm("r1");
          q = (s32*)((u8*)p + 0xbc);
          t = h;
          t = t * K;
          t += C;
          t <<= 1;
          h = t >> 1;
          t <<= 3;
          t >>= 0x14;
          {
            register s32 v asm("r1");
            v = *q;
            v += t;
            (p->s).unk_coord.y = v;
          }
        }
        t = h;
        t = t * K;
        t += C;
        t <<= 1;
        {
          register u32 v asm("r1");
          v = t >> 1;
          *rng = v;
          t >>= 0x11;
          v = 1;
          t &= v;
          (p->s).work[2] = t;
        }
      }
      asm volatile("" : "+l"(m));
      (p->s).work[3] = m;
      (p->s).mode[3] = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register u32 r4v asm("r4");
      register u32 fl asm("r3");
      register u32 v asm("r1");
      register u32 m0 asm("r0");
      register u32 nw asm("r0");
      if ((p->s).work[0] == 0) {
        fl = (p->s).flags;
        r4v = 0x10;
        m0 = 0x10;
        m0 &= fl;
        if (m0 == 0) {
          register s32 cx asm("r0");
          register s32 ux asm("r2");
          register s32 k asm("r1");
          cx = (p->s).coord.x;
          k = -0x180;
          cx += k;
          (p->s).coord.x = cx;
          ux = (p->s).unk_coord.x;
          cx = ux - cx;
          k = 0xc0;
          k <<= 6;
          if (cx <= k) {
            goto xdone;
          }
          k = -0x3000;
          cx = ux + k;
          (p->s).coord.x = cx;
          {
            register u32 sh asm("r0");
            sh = fl << 24;
            asm("" : "+l"(sh));
            sh >>= 28;
            v = 1;
            v &= ~sh;
            if (v == 0) {
              goto clr;
            }
          }
          {
            register u32 nf asm("r0");
            nf = r4v;
            nf |= fl;
            (p->s).flags = nf;
          }
          goto setfl;
        } else {
          register s32 cx asm("r0");
          register s32 ux asm("r2");
          register s32 k asm("r1");
          cx = (p->s).coord.x;
          k = 0xc0;
          k <<= 1;
          cx += k;
          (p->s).coord.x = cx;
          ux = (p->s).unk_coord.x;
          cx = cx - ux;
          k = 0xc0;
          k <<= 6;
          if (cx <= k) {
            goto xdone;
          }
          cx = ux + k;
          (p->s).coord.x = cx;
          {
            register u32 sh asm("r0");
            sh = fl << 24;
            asm("" : "+l"(sh));
            sh >>= 28;
            v = 1;
            v &= ~sh;
            if (v == 0) {
              goto clr;
            }
          }
          {
            register u32 nf asm("r0");
            nf = fl;
            nf |= r4v;
            (p->s).flags = nf;
          }
          goto setfl;
        }
      } else {
        fl = (p->s).flags;
        r4v = 0x10;
        m0 = 0x10;
        m0 &= fl;
        if (m0 == 0) {
          register s32 cx asm("r0");
          register s32 ux asm("r2");
          register s32 k asm("r1");
          cx = (p->s).coord.x;
          k = -0x180;
          cx += k;
          (p->s).coord.x = cx;
          ux = (p->s).unk_coord.x;
          cx = ux - cx;
          k = 0xc0;
          k <<= 6;
          if (cx <= k) {
            goto xdone;
          }
          k = -0x3000;
          cx = ux + k;
          (p->s).coord.x = cx;
          {
            register u32 sh asm("r0");
            sh = fl << 24;
            asm("" : "+l"(sh));
            sh >>= 28;
            v = 1;
            v &= ~sh;
            if (v == 0) {
              goto clr;
            }
          }
          {
            register u32 nf asm("r0");
            nf = r4v;
            nf |= fl;
            (p->s).flags = nf;
          }
          goto setfl;
        } else {
          register s32 cx asm("r0");
          register s32 ux asm("r2");
          register s32 k asm("r1");
          cx = (p->s).coord.x;
          k = 0xc0;
          k <<= 1;
          cx += k;
          (p->s).coord.x = cx;
          ux = (p->s).unk_coord.x;
          cx = cx - ux;
          k = 0xc0;
          k <<= 6;
          if (cx <= k) {
            goto xdone;
          }
          cx = ux + k;
          (p->s).coord.x = cx;
          {
            register u32 sh asm("r0");
            sh = fl << 24;
            asm("" : "+l"(sh));
            sh >>= 28;
            v = 1;
            v &= ~sh;
            if (v == 0) {
              goto clr;
            }
          }
          {
            register u32 nf asm("r0");
            nf = fl;
            nf |= r4v;
            (p->s).flags = nf;
          }
          goto setfl;
        }
      }
      clr : {
        u32 nf = 0xef;
        nf &= fl;
        (p->s).flags = nf;
      }
      setfl : {
        register u8* xf asm("r0");
        register u8* oa asm("r3");
        register s32 sh asm("r1");
        register s32 ov asm("r2");
        register s32 m11 asm("r0");
        xf = (u8*)p + 0x4c;
        *xf = v;
        oa = (u8*)p + 0x4a;
        sh = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh;
      }
    xdone:
      r4v = (p->s).work[3];
      if (r4v <= 7) {
        register u32 t2 asm("r3");
        t2 = (p->s).work[2];
        if (t2 == 0) {
          register s32 cy asm("r0");
          register s32 uy asm("r2");
          register s32 k asm("r1");
          cy = (p->s).coord.y;
          k = -0x500;
          cy += k;
          (p->s).coord.y = cy;
          uy = (p->s).unk_coord.y;
          cy = uy - cy;
          k = 0xc0;
          k <<= 4;
          if (cy <= k) {
            goto ydone;
          }
          k = -0xc00;
          cy = uy + k;
          (p->s).coord.y = cy;
          {
            register u32 nv asm("r0");
            nv = 1;
            nv ^= t2;
            (p->s).work[2] = nv;
          }
          nw = r4v + 1;
          asm volatile("");
          goto setw3;
        } else {
          register s32 cy asm("r0");
          register s32 uy asm("r2");
          register s32 k asm("r1");
          cy = (p->s).coord.y;
          k = 0xa0;
          k <<= 3;
          cy += k;
          (p->s).coord.y = cy;
          uy = (p->s).unk_coord.y;
          cy = cy - uy;
          k = 0xc0;
          k <<= 4;
          if (cy <= k) {
            goto ydone;
          }
          cy = uy + k;
          (p->s).coord.y = cy;
          {
            register u32 nv asm("r0");
            nv = 1;
            nv ^= t2;
            (p->s).work[2] = nv;
          }
          nw = r4v + 1;
          asm volatile("");
          goto setw3;
        }
      } else {
        register u32 t2 asm("r3");
        register s32 k asm("r1");
        register s32 uy asm("r2");
        t2 = (p->s).work[2];
        if (t2 == 0) {
          register s32 cy asm("r0");
          cy = (p->s).coord.y;
          k = -0x500;
          cy += k;
          (p->s).coord.y = cy;
          uy = (p->s).unk_coord.y;
          cy = uy - cy;
          k = 0xc0;
          k <<= 5;
          if (cy <= k) {
            goto chk;
          }
          k = -0x1800;
        } else {
          register s32 cy asm("r0");
          cy = (p->s).coord.y;
          k = 0xa0;
          k <<= 3;
          cy += k;
          (p->s).coord.y = cy;
          uy = (p->s).unk_coord.y;
          cy = cy - uy;
          k = 0xc0;
          k <<= 5;
          if (cy <= k) {
            goto chk;
          }
        }
        {
          register s32 cy asm("r0");
          cy = uy + k;
          (p->s).coord.y = cy;
        }
        {
          register u32 nv asm("r0");
          nv = 1;
          nv ^= t2;
          (p->s).work[2] = nv;
        }
        {
          register u32 nv2 asm("r0");
          nv2 = r4v + 1;
          (p->s).work[3] = nv2;
        }
      chk:
        if ((p->s).work[3] <= 0xa) {
          goto ydone;
        }
        nw = 0;
      setw3:
        (p->s).work[3] = nw;
      }
    ydone:
      {
        register u32 md asm("r0");
        md = (p->s).mode[3] + 1;
        (p->s).mode[3] = md;
        md = (u32)(md << 24) >> 24;
        md = md % 12;
        md <<= 24;
        if (md == 0) {
          FUN_080c2f3c(&(p->s).coord, ((p->s).flags >> 4) & 1);
        }
      }
      UpdateMotionGraphic(&p->s);
      {
        register u32 r asm("r2");
        r = FUN_08088ae0(p);
        if (r == 0) {
          register s32 dx asm("r0");
          register s32 dy asm("r1");
          dx = (p->s).d.x;
          dy = (p->s).d.y;
          (p->s).unk_coord.x = dx;
          (p->s).unk_coord.y = dy;
          {
            register u32 three asm("r0");
            three = 3;
            (p->s).mode[1] = three;
          }
          (p->s).mode[2] = r;
        }
      }
      break;
    }
  }
}

bool8 nop_0808889c(struct Enemy* p) { return TRUE; }

// 0x080888A0 -- home in on unk_coord, then re-target once close enough.
// Everything matches except one register pair: retail keeps the 0xb8 delta in
// r6 and the 0xbc delta in r7, ours has them swapped. The prologue/epilogue
// were fixed by 6.133 (extend both deltas to the end of the function with
// zero-cost `asm("" ::"l"(..))` keep-alives so they are ALLOCATED, not pinned,
// which is what puts r7 in `push {r4,r5,r6,r7,lr}`). agbcc then always gives
// the FIRST-computed of the two the HIGHER register; declaration order, asm
// operand order, splitting the keep-alives, and renaming the variables all
// leave the pairing unchanged, and pinning either one drops it back out of
// the save list.
NON_MATCH void mothjiro_080888a0(struct Enemy* p) {
#if MODERN
  register s32 m asm("r8");
  s32 dxk;
  s32 dyk;
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      SetMotion(&p->s, 0x6B00);
      {
        register s32 dist asm("r5");
        s32 dx = (p->s).unk_coord.x - (p->s).coord.x;
        s32 dy, q1, q2, sq1, sq2;
        (p->s).d.x = dx;
        dy = (p->s).unk_coord.y - (p->s).coord.y;
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
        *(s32*)((u8*)p + 0xb4) = dist;
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
      {
        register s32 t asm("r0");
        t = (p->s).mode[3];
        t += 1;
        m = 0;
        (p->s).mode[3] = t;
        if ((u8)t % 0xC == 0) {
          FUN_080c2f3c(&(p->s).coord, ((p->s).flags >> 4) & 1);
        }
      }
      {
        s32* q;
        s32 v;
        q = (s32*)((u8*)p + 0xb4);
        v = *q + -0x200;
        *q = v;
        if (v <= 0) {
          register s32 zz asm("r2");
          zz = m;
          (p->s).mode[1] = zz;
          (p->s).mode[2] = zz;
        }
        if (FUN_08088ae0(p) != 0) {
          s32 dist;
#define dx dxk
#define dy dyk
          {
            register s32 u asm("r1");
            register s32 w asm("r0");
            u = *(s32*)((u8*)p + 0xb8);
            w = (p->s).coord.x;
            dx = u - w;
            u = *(s32*)((u8*)p + 0xbc);
            w = (p->s).coord.y;
            dy = u - w;
          }
          {
            register s32 a0 asm("r0");
            register s32 a1 asm("r1");
            register s32 a2 asm("r2");
            a0 = dx >> 2;
            asm volatile("add %0, %1, #0" : "=&l"(a1) : "l"(a0));
            a1 = a1 * a0;
            asm volatile("add %0, %1, #0" : "=&l"(a0) : "l"(a1));
            a1 = dy >> 2;
            asm volatile("add %0, %1, #0" : "=&l"(a2) : "l"(a1));
            a2 = a2 * a1;
            asm volatile("add %0, %1, #0" : "=&l"(a1) : "l"(a2));
            a0 += a1;
            dist = (u16)Sqrt(a0) << 2;
          }
#undef dx
#undef dy
          if (dist <= 0x77FF) {
            register s32 zr asm("r0");
            *q = dist;
            (p->s).mode[1] = 1;
            zr = m;
            (p->s).mode[2] = zr;
          }
        }
      }
      break;
    }
  }
  asm("" ::"l"(dxk));
  asm("" ::"l"(dyk));
#else
  INCCODE("asm/enemy/mothjiro_888a0.inc");
#endif
}


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
