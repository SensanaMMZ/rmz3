#include "collision.h"
#include "global.h"
#include "zero.h"
#include "projectile.h"
#include "vfx.h"

static const ProjectileFunc sUpdates1[5];
static const ProjectileFunc sUpdates2[5];

void FUN_080a0888(s32 x, s32 y, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
    (p->s).work[3] = a3;
  }
}

void FUN_080a08e0(struct Entity* e, s32 x, s32 y, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a3;
    (p->s).unk_28 = e;
  }
}

struct DeathtanzProjectile {
  OBJECT_HDR;
  u8 work[4];    // 0xB4
  u8 unk_b8[4];  // 0xB8
  u8 unk_bc;     // 0xBC
};

void deathtanz_080a0934(struct Entity* e, s32 x, s32 y, u8 a3, u8 a4) {
  struct DeathtanzProjectile* p = (struct DeathtanzProjectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a3;
    (p->s).unk_28 = e;
    p->unk_bc = a4;
  }
}

#include "entity/macros.h"

void deathtanz_080a09a0(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    (p->s).unk_28 = parent;
  }
}

void deathtanz_080a09f4(struct Entity* e, s32 x, s32 y, u8 a3, u8 a4) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a3;
    (p->s).work[3] = a4;
    (p->s).unk_28 = e;
  }
}

static const u8 u8_ARRAY_0836b20c[5];
static const struct Collision sCollisions[10];
void Projectile14_Update(struct Projectile* p);

static void nop_080a0a5c(struct Body* body, struct Coord* c) {}

void Projectile14_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836b20c[(p->s).work[0]];
  {
    u8 f = (p->s).flags;
    f |= FLIPABLE;
    f |= DISPLAY;
    (p->s).flags = f;
  }
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_080a0a5c);
  {
    u8* src = (u8*)(p->s).unk_28;
    s32* dst = (s32*)&p->work[0];
    *dst = *(s32*)(src + 0xb4);
  }
  {
    s32* q = (s32*)((u8*)&p->body + 0x44);
    *q = (p->s).coord.y >> 8;
    *q = *q / 0xA0 * 5 << 13;
  }
  Projectile14_Update(p);
}

void Projectile14_Update(struct Projectile* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Projectile14_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(1, &(p->s).coord);
  PlaySound(0x2a);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void nop_080a0b6c(struct Projectile* p) {}

void FUN_080a0b70(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).unk_coord.y = (p->s).coord.y;
      SetDDP(&p->body, sCollisions);
      (p->s).d.x = 0x80;
      SetMotion(&p->s, 0x3701);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 lim;
      if ((p->s).work[2] != 0) {
        s32 nx = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + 0x6800;
        if (nx > lim) {
          asm volatile("");
          goto clampx1;
        }
      } else {
        s32 nx = (p->s).coord.x - (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + -0x6800;
        if (nx < lim) {
        clampx1:
          (p->s).coord.x = lim;
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 2: {
      u8 t2 = 0;
      if ((pZero2->s).coord.y > (p->s).coord.y) {
        t2 = 1;
      }
      (p->s).work[3] = t2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 lim;
      if ((p->s).work[3] != 0) {
        s32 ny = (p->s).coord.y + (p->s).d.x;
        (p->s).coord.y = ny;
        lim = *(s32*)((u8*)p + 0xb8) + 0x9000;
        if (ny > lim) {
          (p->s).coord.y = lim;
          asm volatile("");
          goto inc3;
        }
      } else {
        s32 ny = (p->s).coord.y - (p->s).d.x;
        (p->s).coord.y = ny;
        lim = *(s32*)((u8*)p + 0xb8) + -0x9000;
        if (ny < lim) {
          (p->s).coord.y = lim;
        inc3:
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 4: {
      u32 v = (RNG_0202f388 * 0x343FD + 0x269EC3) << 1;
      RNG_0202f388 = v >> 1;
      (p->s).d.x = ((v >> 0x11) & 1) * (p->s).d.x;
      (p->s).work[2] ^= 1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5: {
      s32 lim;
      if ((p->s).work[2] != 0) {
        s32 nx = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + 0x5800;
        if (nx <= lim) {
          break;
        }
        goto clampx5;
      } else {
        s32 nx = (p->s).coord.x - (p->s).d.x;
        (p->s).coord.x = nx;
        lim = *(s32*)((u8*)p + 0xb4) + -0x5800;
        if (nx < lim) {
        clampx5:
          (p->s).coord.x = lim;
          (p->s).mode[2]++;
        }
      }
      break;
    }
    case 6:
      (p->s).work[3] ^= 1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 7:
      if ((p->s).work[3] != 0) {
        s32 ny = (p->s).coord.y + (p->s).d.x;
        (p->s).coord.y = ny;
        if (ny <= (p->s).unk_coord.y) {
          break;
        }
        goto hitset;
      } else {
        s32 ny = (p->s).coord.y - (p->s).d.x;
        (p->s).coord.y = ny;
        if (ny < (p->s).unk_coord.y) {
        hitset:
          (p->s).mode[2]++;
          *((u8*)q + 0xbe) = 1;
        }
      }
      break;
    case 8:
      (p->s).work[2] = 2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 9: {
      s32 t = (p->s).work[2] - 1;
      u8 t2;
      (p->s).work[2] = t;
      t2 = t;
      if (t2 == 0) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
      break;
    }
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 d = (p->s).d.x + 0x30;
    (p->s).d.x = d;
    if (d > 0x800) {
      (p->s).d.x = 0x800;
    }
  }
  if (q->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}


// 0x080A0DC0
// 8 bytes short: agbcc hoists the shared `-0x800` (case 4) and `+0x1000`
// (case 5) pool constants into a register above the if/else, where retail loads
// each from its own pool entry inside each arm.  Writing the offset as an
// in-place two-statement accumulation (`k = v << 11; k -= 0x800;`) gets retail's
// `adds r0, r0, r1` shape but not the per-arm pool load; folding it back into one
// expression re-associates the constant into the comparison instead (476 bytes).
// A barrier on the temp does not inhibit the hoist.  Everything else, including
// the whole 8-case dispatch and the shared `bump:`/`str r0,[r4,#0x14]` tails,
// is identical.
NON_MATCH void FUN_080a0dc0(struct Projectile* p) {
#if MODERN
  struct Entity* q = (p->s).unk_28;
  s32 lim, k, z;

  switch ((p->s).mode[2]) {
    case 0:
      (p->s).unk_coord.y = (p->s).coord.y;
      SetDDP(&p->body, sCollisions);
      (p->s).d.x = 0x80;
      SetMotion(&p->s, 0x3701);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((p->s).work[2] != 0) {
        (p->s).coord.x += (p->s).d.x;
        if ((p->s).coord.x > *(s32*)((u8*)p + 0xb4) + 0x6800) {
          goto bump;
        }
      } else {
        (p->s).coord.x -= (p->s).d.x;
        if ((p->s).coord.x < *(s32*)((u8*)p + 0xb4) - 0x6800) {
          goto bump;
        }
      }
      break;
    case 2:
      (p->s).coord.y -= (p->s).d.x;
      lim = *(s32*)((u8*)p + 0xb8) - 0x9000;
      if ((p->s).coord.y >= lim) {
        break;
      }
      (p->s).coord.y = lim;
      goto bump;
    case 3:
      (p->s).work[2] ^= 1;
      (p->s).mode[2]++;
      /* fallthrough */
    case 4:
      if ((p->s).work[2] != 0) {
        (p->s).coord.x += (p->s).d.x;
        k = *((u8*)p + 0xbc) << 11;
        k -= 0x800;
        lim = (q->coord).x - k;
        if ((p->s).coord.x <= lim) {
          break;
        }
      } else {
        (p->s).coord.x -= (p->s).d.x;
        k = *((u8*)p + 0xbc) << 11;
        k -= 0x800;
        lim = (q->coord).x + k;
        if ((p->s).coord.x >= lim) {
          break;
        }
      }
      (p->s).coord.x = lim;
    bump:
      (p->s).mode[2]++;
      break;
    case 5:
      (p->s).coord.y += (p->s).d.x;
      k = *((u8*)p + 0xbc);
      k = k * 3 << 11;
      k += 0x1000;
      lim = (p->s).unk_coord.y - k;
      if ((p->s).coord.y > lim) {
        (p->s).mode[2]++;
        *((u8*)q + 0xbe) = 1;
      }
      break;
    case 6:
      (p->s).work[2] = 2;
      (p->s).mode[2]++;
      /* fallthrough */
    case 7:
      lim = (p->s).work[2] - 1;
      (p->s).work[2] = lim;
      z = (u8)lim;
      if (z != 0) {
        break;
      }
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      (p->body).status = z;
      (p->body).prevStatus = z;
      (p->body).invincibleTime = z;
      (p->s).flags &= ~COLLIDABLE;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).d.x += 0x30;
  if ((p->s).d.x > 0xA00) {
    (p->s).d.x = 0xA00;
  }
  if (q->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
#else
  INCCODE("asm/projectile/unk_14_a0dc0.inc");
#endif
}

// 0x080A0FA8
void FUN_080a0fa8(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 lim;
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 one asm("r4");
      register u32 w asm("r2");
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).unk_coord.x = (p->s).coord.x;
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      SetMotion(&p->s, 0xA71C);
      w = (p->s).work[2];
      asm("" : "+l"(w));
      if (w != 0) {
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
      one = 1;
      {
        register u32 xf asm("r1");
        xf = one;
        xf &= w;
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
      {
        register s32 base asm("r2");
        u32 b;
        base = -0x280;
        {
          u32* rng = &RNG_0202f388;
          register u32 t asm("r0");
          {
            register u32 sd asm("r1");
            sd = *rng;
            t = 0x343FD;
            t *= sd;
          }
          {
            register u32 c asm("r1");
            c = 0x269EC3;
            t += c;
          }
          t <<= 1;
          {
            register u32 h asm("r1");
            h = t >> 1;
            *rng = h;
          }
          t >>= 0x11;
          t &= one;
          asm("" : "+l"(t));
          b = t;
        }
        {
          register s32 m asm("r1");
          m = b * 2 + b;
          m <<= 7;
          base -= m;
        }
        {
          register s32 nb asm("r1");
          register s32 wv asm("r0");
          nb = -base;
          wv = (p->s).work[2] << 1;
          wv *= nb;
          base += wv;
        }
        (p->s).d.x = base;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 cx asm("r1");
      register s32 lim1 asm("r0");
      cx = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = cx;
      if ((p->s).work[2] != 0) {
        register s32 k asm("r2");
        lim1 = *(s32*)((u8*)p + 0xb4);
        k = 0xa0 << 7;
        lim1 += k;
        if (cx <= lim1) {
          goto upd;
        }
      } else {
        register s32 k asm("r2");
        lim1 = *(s32*)((u8*)p + 0xb4);
        k = -0x5000;
        lim1 += k;
        if (cx >= lim1) {
          goto upd;
        }
      }
      (p->s).coord.x = lim1;
      goto bump;
    }
    case 2: {
      u32 b;
      {
        u32* rng = &RNG_0202f388;
        register u32 t asm("r1");
        {
          register u32 k asm("r0");
          t = *rng;
          k = 0x343FD;
          t *= k;
        }
        {
          register u32 c asm("r0");
          c = 0x269EC3;
          t += c;
        }
        t <<= 1;
        {
          register u32 h asm("r0");
          h = t >> 1;
          *rng = h;
        }
        t >>= 0x11;
        {
          register u32 one asm("r0");
          one = 1;
          t &= one;
        }
        b = t;
      }
      (p->s).work[2] = ((b * 2 + b) << 2) + 8;
      SetMotion(&p->s, 0xA71D);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 t;
      FUN_0801779c(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      goto bump2;
    }
    case 4:
      SetDDP(&p->body, &sCollisions[4]);
      SetMotion(&p->s, 0xA71E);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      FUN_0801779c(&p->s);
      if (*((u8*)p + 0x73) != 3) {
        break;
      }
    bump2:
      (p->s).mode[2]++;
      break;
    case 6: {
      register s32 dv asm("r2");
      u32 b;
      SetMotion(&p->s, 0xA71F);
      {
        u32* rng = &RNG_0202f388;
        register u32 t asm("r0");
        {
          register u32 sd asm("r1");
          sd = *rng;
          t = 0x343FD;
          t *= sd;
        }
        {
          register u32 c asm("r1");
          c = 0x269EC3;
          t += c;
        }
        t <<= 1;
        {
          register u32 h asm("r1");
          h = t >> 1;
          *rng = h;
        }
        t >>= 0x11;
        {
          register u32 one asm("r1");
          one = 1;
          t &= one;
        }
        b = t;
      }
      dv = b << 7;
      (p->s).d.x = dv;
      {
        register s32 nv asm("r0");
        if (((p->s).flags & 0x10) != 0) {
          nv = -dv;
          nv <<= 1;
        } else {
          nv = 0;
        }
        (p->s).d.x = nv;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 7: {
      register s32 dv asm("r2");
      register s32 lim7 asm("r1");
      {
        register s32 cx0 asm("r0");
        cx0 = (p->s).coord.x;
        dv = (p->s).d.x;
        cx0 += dv;
        (p->s).coord.x = cx0;
      }
      if (((p->s).flags & 0x10) != 0) {
        register s32 nd asm("r0");
        register s32 k asm("r1");
        nd = dv;
        nd -= 0x30;
        (p->s).d.x = nd;
        k = -0x600;
        if (nd < k) {
          (p->s).d.x = k;
        }
        {
          register s32 cx2 asm("r0");
          cx2 = (p->s).coord.x;
          lim7 = (p->s).unk_coord.x;
          if (cx2 >= lim7) {
            goto upd;
          }
        }
      } else {
        register s32 nd asm("r0");
        register s32 k asm("r1");
        nd = dv;
        nd += 0x30;
        (p->s).d.x = nd;
        k = 0xc0 << 3;
        if (nd > k) {
          (p->s).d.x = k;
        }
        {
          register s32 cx2 asm("r0");
          cx2 = (p->s).coord.x;
          lim7 = (p->s).unk_coord.x;
          if (cx2 <= lim7) {
            goto upd;
          }
        }
      }
      (p->s).coord.x = lim7;
      *((u8*)q + 0xbe) = 1;
    bump:
      (p->s).mode[2]++;
    upd:
      FUN_0801779c(&p->s);
      break;
    }
    case 8:
      (p->s).work[2] = 2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 9: {
      register u32 z asm("r2");
      register s32 t asm("r0");
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      z = (u32)(t << 24) >> 24;
      if (z != 0) {
        FUN_0801779c(&p->s);
        break;
      }
      {
        u8 fl = (p->s).flags;
        u32 f = 0xFE;
        f &= fl;
        {
          u32 m = 0xFD;
          f &= m;
        }
        (p->s).flags = f;
      }
      {
        register u8* a asm("r0");
        a = (u8*)p + 0x8c;
        asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("strb %0, [%1]" ::"l"(z), "l"(a) : "memory");
      }
      {
        u8 fl = (p->s).flags;
        u32 f = 0xFB;
        f &= fl;
        (p->s).flags = f;
      }
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
  }
  if (q->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void CreateDeathtanzRock(struct Entity* e, s32 x, s32 y, u8 n);

// 0x080A1280
void FUN_080a1280(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[5]);
      SetMotion(&p->s, MOTION(0x37, 0x04));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 y;
      UpdateMotionGraphic(&p->s);
      y = (p->s).coord.y - 0x700;
      (p->s).coord.y = y;
      if (y < *(s32*)((u8*)p + 0xb8) - 0xC000) {
        if ((p->s).work[2] == 2) {
          u8 w3 = (p->s).work[3];
          s32 t = (w3 * 59) << 9;
          t -= 0x3B00;
          CreateDeathtanzRock(q, (p->s).coord.x + t, y, w3);
        }
        {
          register u8 f asm("r0");
          register u8 t1 asm("r1");
          register u8 k2 asm("r1");
          register s32 z asm("r2");
          t1 = (p->s).flags;
          f = 0xFE;
          f &= t1;
          asm volatile("" ::"r"(t1));
          z = 0;
          k2 = 0xFD;
          f &= k2;
          (p->s).flags = f;
          *(u32*)((u8*)p + 0x8c) = z;
          *(u32*)((u8*)p + 0x90) = z;
          *(u8*)((u8*)p + 0x94) = z;
        }
        (p->s).flags &= ~COLLIDABLE;
        SET_PROJECTILE_ROUTINE(p, 3);
      }
      break;
    }
  }
}

// 0x080A133C
void FUN_080a133c(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 w3 asm("r2");
      (p->s).taskCol = 0x18;
      {
        register s32 base0 asm("r0");
        register s32 base asm("r1");
        register s32 mv asm("r0");
        base0 = 0x3702;
        asm volatile("add %0, %1, #0" : "=&l"(base) : "l"(base0));
        mv = (p->s).work[2];
        asm volatile("add %0, %0, %1" : "+l"(base) : "l"(mv));
        ((void (*)(struct Entity*, s32))SetMotion)(&p->s, base);
      }
      w3 = (p->s).work[3];
      if (w3 != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
      {
        register s32 xf asm("r1");
        u8* oa;
        s32 sh4, ov, m11;
        xf = 1;
        xf &= w3;
        ((p->s).spr).xflip = xf;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 st asm("r3");
      UpdateMotionGraphic(&p->s);
      {
        register struct Body* bd asm("r0");
        register const u8* tb asm("r3");
        register s32 ix asm("r1");
        register s32 k asm("r2");
        bd = &p->body;
        tb = (const u8*)0x0836B211;
        asm volatile("" : "+r"(bd));
        asm volatile("" : "+r"(tb));
        ix = (s8)(p->s).motion.cmdIdx;
        k = (p->s).work[2];
        ix ^= k;
        asm volatile("add %0, %0, %1" : "+l"(ix) : "l"(tb));
        k = *(const u8*)ix;
        ix = k << 1;
        ix += k;
        ix <<= 3;
        {
          register s32 cb asm("r2");
          cb = 0x0836B11C;
          asm volatile("add %0, %0, %1" : "+l"(ix) : "l"(cb));
        }
        SetDDP(bd, (const struct Collision*)ix);
      }
      st = (p->s).motion.state;
      if (st != 3) {
        break;
      }
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        register s32 zz asm("r2");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFE;
        g &= h;
        zz = 0;
        h = 0xFD;
        g &= h;
        (p->s).flags = g;
        {
          u8* a = (u8*)p + 0x8c;
          *(u32*)a = zz;
          asm("" : "+r"(a));
          a += 4;
          asm("" : "+r"(a));
          *(u32*)a = zz;
          asm("" : "+r"(a));
          a += 4;
          asm("" : "+r"(a));
          *a = zz;
        }
      }
      (p->s).flags &= 0xFB;
      {
        u32 tbl = (u32)gProjectileFnTable;
        EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
        *(u32*)((p->s).mode) = st;
        (p->s).onUpdate = (void*)((*rt)[3]);
      }
      break;
    }
  }
}

void Projectile14_Init(struct Projectile* p);
void Projectile14_Update(struct Projectile* p);
void Projectile14_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile14Routine = {
    [ENTITY_INIT] =      Projectile14_Init,
    [ENTITY_UPDATE] =    Projectile14_Update,
    [ENTITY_DIE] =       Projectile14_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080a0b6c(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates1[5] = {
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
};
// clang-format on

// --------------------------------------------

void FUN_080a0b70(struct Projectile* p);
void FUN_080a0dc0(struct Projectile* p);
void FUN_080a0fa8(struct Projectile* p);
void FUN_080a1280(struct Projectile* p);
void FUN_080a133c(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates2[5] = {
    FUN_080a0b70,
    FUN_080a0dc0,
    FUN_080a0fa8,
    FUN_080a1280,
    FUN_080a133c,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[10] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(40), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(50), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(26), PIXEL(50)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(2), PIXEL(40), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(20), PIXEL(19), PIXEL(8), PIXEL(51)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(60)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(57), -PIXEL(24), PIXEL(36), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(35), -PIXEL(11), PIXEL(37), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(57), -PIXEL(39), PIXEL(36), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(35), -PIXEL(53), PIXEL(37), PIXEL(13)},
    },
};

static const u8 u8_ARRAY_0836b20c[5] = {0, 1, 2, 3, 4};
static const u8 u8_ARRAY_0836b211[2] = {6, 8};
