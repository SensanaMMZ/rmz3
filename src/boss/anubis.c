#include "boss.h"
#include "collision.h"
#include "element.h"
#include "global.h"
#include "gfx.h"
#include "constants/motion/static.h"
#include "zero.h"

static const BossFunc sDeads[2];
static const struct Coord sElementCoord;

// Does not match: agbcc holds p in ip/r12 and emits a redundant coord.y store
// that the natural C doesn't. Logic is faithful in the MODERN branch; the
// INCCODE asm body matches the ROM.
NON_MATCH void FUN_08050090(struct Boss* p) {
#if MODERN
  s32 base;
  *(u16*)((u8*)p + 0xc8) += 0x200;
  base = *(s32*)((u8*)p + 0xc4);
  (p->s).coord.y = base + (SIN(*(u16*)((u8*)p + 0xc8) >> 8) << 2);
#else
  INCCODE("asm/boss/anubis_08050090_body.inc");
#endif
}

void FUN_080500c8(struct Body* body) {
  struct Boss* atk = (struct Boss*)((body->enemy)->parent);
  struct Boss* self = (struct Boss*)body->parent;
  if (body->hitboxFlags & 1) {
    u8 r = 0;
    if ((self->s).coord.x < (atk->s).coord.x) {
      r = 1;
    }
    *(u8*)((u8*)self + 0xcc) = r;
  }
}

#include "stagerun.h"

void Anubis_Die(struct Boss* p);
void FUN_08010188(s32 n);

// 0x080500F4
NON_MATCH bool8 FUN_080500f4(struct Boss* p0) {
#if MODERN
  register struct Boss* p asm("r4");
  register u32* st asm("r7");
  p = p0;
  st = (u32*)((u8*)p + 0x8c);
  if ((*st & 0x200) == 0 && *(s16*)((u8*)p + 0xa4) != 0) {
    return 0;
  }
  {
    register u16 f asm("r6");
    { u16 ms = gStageRun.missionStatus; s32 m_ = 8; m_ &= ms; f = m_; }
    if (f != 0) {
      return 0;
    }
    {
      s16* sp = (s16*)((u8*)p + 0xd0);
      if (*sp != -1) {
        StopSound(*sp);
        *sp = -1;
      }
    }
    {
      u8* q = (u8*)p + 0xce;
      if (*q != 0) {
        *q = f;
        FUN_08010188(0);
      }
    }
    SET_BOSS_ROUTINE(p, 2);
    {
      s32 v = *st & 0x10000;
      if (v != 0) {
        (p->s).mode[1] = 1;
      } else {
        (p->s).mode[1] = v;
      }
    }
    Anubis_Die(p);
    return 1;
  }
#else
  INCCODE("asm/boss/anubis_080500f4.inc");
#endif
}

static const u8 sInitModes[4];
static const struct Collision sCollisions[3];
void Anubis_Update(struct Boss* p);

void Anubis_Init(struct Boss* p) {
  s32 z5;
  {
    u32 tbl = (u32)gBossFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    register u32 one asm("r1");
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  {
    u8 m = sInitModes[(p->s).work[0]];
    z5 = 0;
    (p->s).mode[1] = m;
  }
  {
    u32 fl = (p->s).flags;
    fl |= 2;
    asm("" : "+r"(fl));
    fl |= 1;
    (p->s).flags = fl;
  }
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  ResetBossBody(p, sCollisions, 0x40);
  {
    void* f = (void*)FUN_080500c8;
    u8* b = (u8*)p + 0x74;
    *(void**)(b + 0x24) = f;
    asm("" : "+r"(b));
    b += 0x40;
    asm("" : "+r"(b));
    *(u32*)b = z5;
  }
  if ((p->s).work[0] != 1) {
    {
      s32* pb = (s32*)((u8*)p + 0xb8);
      s32 cx = (p->s).coord.x >> 8;
      s32 q;
      *pb = cx;
      q = cx / 0xF0;
      *pb = (((q << 4) - q) << 12) + 0x7800;
      asm("" : "+r"(pb));
      pb += 1;
      {
        s32 cy = (p->s).coord.y >> 8;
        s32 q2;
        *pb = cy;
        q2 = cy / 0xA0;
        q2 += 1;
        *pb = ((q2 << 2) + q2) << 13;
      }
    }
    {
      u8* w = (u8*)p + 0xc0;
      s32 z1;
      *(u32*)w = z5;
      asm("" : "+r"(w));
      w += 8;
      z1 = 0;
      *(u16*)w = z5;
      asm("" : "+r"(w));
      w += 2;
      *w = z1;
      asm("" : "+r"(w));
      w += 1;
      *w = z1;
      *((u8*)p + 0xcd) = 0x40;
      {
        u8* w2 = (u8*)p + 0xce;
        *w2 = z1;
        asm("" : "+r"(w2));
        w2 += 1;
        *w2 = z1;
      }
    }
    LOAD_STATIC_GRAPHIC(SM073_ANUBIS_ROD);
    LOAD_STATIC_GRAPHIC(SM074_ANUBIS_SAND);
    {
      u16* a2 = (u16*)((u8*)p + 0xd0);
      register u32 v asm("r0");
      v = 0xFFFF;
      *a2 = v;
    }
    *((u8*)p + 0xd2) = 1;
  }
  Anubis_Update(p);
}

static const BossFunc sUpdates1[11];
static const BossFunc sUpdates2[11];
bool8 FUN_080500f4(struct Boss* p);

void Anubis_Update(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  struct Entity* e;
  u8* t;
  s32 v;
  if (*slot != NULL) {
    if (!isKilled(*slot)) {
      goto next;
    }
    e = NULL;
  } else {
    if (!((p->body).status & 1)) {
      goto next;
    }
    e = (struct Entity*)ApplyElementEffect(0x14, &p->s, &sElementCoord);
  }
  *slot = e;
next:
  t = (u8*)((u8*)p + 0xca);
  if (*t != 0) {
    v = *t - 1;
  } else {
    if (!((pZero2->body).status & 1)) {
      goto skip;
    }
    v = 0x60;
  }
  *t = v;
skip:
  if (FUN_080500f4(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Anubis_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_080503c8(struct Boss* p) {}

void FUN_080bf3d8(struct Entity* p);
void FUN_080a4ef8(struct Entity* p);

void anubisMode0(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32 f0 = (p->s).flags;
      u32 t0 = 0xFE;
      t0 &= f0;
      (p->s).flags = t0;
      if ((p->s).work[0] == 0) {
        LOAD_STATIC_GRAPHIC(SM075_ANUBIS_COFFIN);
        {
          s32* c = (s32*)((u8*)p + 0xbc);
          register s32 n asm("r1");
          register s32 q asm("r0");
          (p->s).coord.y = *c + -0xC000;
          SetMotion(&p->s, 0xAF0C);
          {
            register s32 cv asm("r0");
            cv = *c;
            n = cv + -0x7600;
          }
          n -= (p->s).coord.y;
          q = n;
          if (n < 0) {
            q = n + 3;
          }
          q >>= 2;
          (p->s).d.y = ((u32)Sqrt(q) << 16) >> 13;
        }
        FUN_080bf3d8(&p->s);
        (p->s).work[2] = 0x10;
        (p->s).mode[2]++;
      } else {
        s32* c = (s32*)((u8*)p + 0xbc);
        s32 y = *c + -0x7600;
        (p->s).coord.y = y;
        *(s32*)((u8*)p + 0xc4) = y;
        (p->s).mode[2] = 6;
        break;
      }
      FALLTHROUGH;
    }
    case 1: {
      s32 dy = (p->s).d.y;
      if (dy < 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          goto upd;
        }
        (p->s).flags |= 1;
        {
          u32* a = (u32*)((u8*)p + 0xc0);
          *a |= 1;
        }
        goto inc2;
      }
      (p->s).coord.y += dy;
      (p->s).d.y = dy - 8;
      goto upd;
    }
    case 2:
      *(s32*)((u8*)p + 0xc4) = (p->s).coord.y;
      (p->s).work[2] = 0x64;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      goto inc2b;
    }
    case 4:
      SetMotion(&p->s, 0xAF0D);
      (p->s).mode[2]++;
      goto st;
    case 6:
      {
        u32 f6 = (p->s).flags;
        u32 t6 = 1;
        t6 |= f6;
        (p->s).flags = t6;
      }
      FUN_080a4ef8(&p->s);
      SetMotion(&p->s, 0xAF01);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 7:
      FUN_08050090(p);
      if (((p->s).scriptEntity->flags & 1) == 0) {
        goto upd;
      }
    inc2:
      (p->s).mode[2]++;
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    case 8:
      SetMotion(&p->s, 0xAF02);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
    case 9:
    st:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    inc2b:
      (p->s).mode[2]++;
      break;
    case 10:
      SetMotion(&p->s, 0xAF01);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 11: {
      register s32 one asm("r4");
      register s32 m asm("r0");
      register s32 g asm("r1");
      FUN_08050090(p);
      g = gStageRun.vm.active;
      one = 1;
      m = one;
      m &= g;
      if (m == 0) {
        SetDDP(&p->body, (const struct Collision*)0x08363584);
        (p->s).mode[1] = one;
        (p->s).mode[2] = one;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/boss/anubis_p2.inc");

// 0x080507E0
void anubisMode2(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 k asm("r1");
      u32* st;
      u32 v;
      *(u16*)((u8*)p + 0xd0) = PlaySound(0x54);
      st = (u32*)((u8*)p + 0xc0);
      v = *st;
      k = 2;
      v |= k;
      k -= 7;
      v &= k;
      k -= 0xc;
      v &= k;
      *st = v;
      SetMotion(&p->s, 0xAF02);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((s8)*(u8*)((u8*)p + 0x71) == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      u32* st2 = (u32*)((u8*)p + 0xc0);
      s32 dx;
      *st2 &= -3;
      {
        s32 dx0 = 0x200;
        *(volatile s32*)&(p->s).d.x = dx0;
        asm volatile("add %0, %1, #0" : "=&l"(dx) : "l"(dx0));
      }
      if ((p->s).flags & 0x10) {
        dx = -0x200;
      }
      (p->s).d.x = dx;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 3:
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x2000) {
        u8 z = 0;
        (p->s).mode[1] = 3;
        (p->s).mode[2] = z;
      }
      break;
  }
}

void FUN_08050090(struct Boss* p);

void anubisMode3(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x3C;
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 2: {
      u32 sv;
      u32 xf;
      u32 xf2;
      s32 k16;
      {
        u32* st = (u32*)((u8*)p + 0xc0);
        *st |= 4;
      }
      sv = (u16)Sqrt(0x680);
      (p->s).work[2] = sv;
      (p->s).d.x = sv << 4;
      xf = (((p->s).flags >> 4) ^ 1) & 1;
      ((p->s).spr).xflip = xf;
      xf2 = (((p->s).flags >> 4) ^ 1) & 1;
      {
        register u8* oa asm("r5");
        u32 sh4;
        s32 ov, m11;
        oa = (u8*)p + 0x4a;
        sh4 = xf2 << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      if (xf2 != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        u32 fl2 = (p->s).flags;
        register u32 res asm("r0");
        k16 = 0x10;
        asm("" : "+r"(k16));
        res = k16;
        asm volatile("" : "+r"(res));
        res &= fl2;
        if (res == 0) {
          goto arm2;
        }
      }
      if (1) {
        (p->s).coord.x = *(s32*)((u8*)p + 0xb8) - 0x9800;
        (p->s).unk_coord.x = -0x10;
      } else {
      arm2:
        (p->s).coord.x = *(s32*)((u8*)p + 0xb8) + 0x9800;
        (p->s).d.x = -(p->s).d.x;
        (p->s).unk_coord.x = k16;
      }
      SetMotion(&p->s, 0xAF01);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.x += (p->s).unk_coord.x;
      FUN_08050090(p);
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 4:
      FUN_08050090(p);
      UpdateMotionGraphic(&p->s);
      if ((*(u32*)((u8*)p + 0xc0) & 4) == 0) {
        s16* snd = (s16*)((u8*)p + 0xd0);
        register s32 v asm("r1");
        v = *snd;
        if (v != -1) {
          u32 mv;
          StopSound(v);
          mv = 0xFFFF;
          asm("" : "+r"(mv));
          *snd = mv;
        }
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 1;
      }
      break;
  }
}

// 0x08050A1C
void anubisMode4(struct Boss* p0) {
  register struct Boss* p asm("r4");
  s32 m;
  p = p0;
  switch ((p->s).mode[2]) {
    case 0: {
      s16 sv;
      u32* st;
      register u32 v asm("r0");
      register s32 k asm("r1");
      sv = PlaySound(SE_ANUBIS_BOOMERANG);
      *(s16*)((u8*)p + 0xd0) = sv;
      st = (u32*)((u8*)p + 0xc0);
      v = *st;
      k = 8;
      v |= k;
      k = 0x10;
      v |= k;
      *st = v;
      SetMotion(&p->s, 0xAF02);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if (*(u8*)((u8*)p + 0x73) != 3) {
        break;
      }
      m = (p->s).mode[2] + 1;
      goto store;
    case 2: {
      u32* st = (u32*)((u8*)p + 0xc0);
      *st &= -9;
      SetMotion(&p->s, 0xAF01);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3:
      FUN_08050090(p);
      UpdateMotionGraphic(&p->s);
      if ((*(u32*)((u8*)p + 0xc0) & 0x10) == 0) {
        s16* snd = (s16*)((u8*)p + 0xd0);
        register s32 v asm("r1");
        v = *snd;
        if (v != -1) {
          u32 mv;
          StopSound(v);
          mv = 0xFFFF;
          asm("" : "+r"(mv));
          *snd = mv;
        }
        m = 1;
        (p->s).mode[1] = m;
      store:
        (p->s).mode[2] = m;
      }
      break;
  }
}

static const struct Collision sCollisions[3];

void anubisMode5(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if (((p->props).anubis).unk_cc[2] != 0) {
        UpdateMotionGraphic(&p->s);
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 2;
        (p->s).work[2] = 2;
        break;
      }
      SetDDP(&p->body, sCollisions);
      {
        u32 v = ((p->props).anubis).unk_c0;
        v |= 0x100;
        asm("" : "+r"(v));
        v |= 0x20;
        v &= ~0x40;
        ((p->props).anubis).unk_c0 = v;
      }
      SetMotion(&p->s, MOTION(0xAF, 0x08));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        ((p->props).anubis).unk_c0 &= ~0x100;
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

static const u8 u8_ARRAY_083635c9[8];
void CreateAnubisCoffins(struct Boss* p, u8 a);

// 0x08050B74
void anubisMode6(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register const u8* tb asm("r3");
      s32 r;
      (p->s).flags &= 0xFE;
      LOAD_STATIC_GRAPHIC(SM075_ANUBIS_COFFIN);
      tb = u8_ARRAY_083635c9;
      r = RANDOM(RNG_0202f388) & 7;
      if (*(s16*)((u8*)p + 0xa4) <= 0x1F) {
        r += 8;
      }
      {
        register s32 idx asm("r1");
        register const u8* e asm("r0");
        idx = r;
        asm volatile("add %0, %1, %2" : "=l"(e) : "l"(idx), "l"(tb));
        (p->s).work[2] = *e;
      }
      (p->s).work[3] = 0x1E;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 t0 asm("r0");
      register s32 w2 asm("r1");
      if ((u8)--(p->s).work[3] != 0) {
        break;
      }
      (p->s).work[3] = 0x60;
      t0 = (p->s).work[2] - 1;
      (p->s).work[2] = t0;
      t0 <<= 24;
      w2 = (u32)t0 >> 24;
      if (w2 == 0) {
        (p->s).mode[1] = 7;
        (p->s).mode[2] = w2;
      } else {
        (p->s).mode[2] = 1;
      }
      PlaySound(0x55);
      {
        register s32 f asm("r1");
        f = 0;
        if ((p->s).work[2] == 0) {
          f = 1;
        }
        ((void (*)(struct Boss*, s32))CreateAnubisCoffins)(p, f);
      }
      break;
    }
  }
}

// 0x08050c68
void anubisMode7(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x60;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((u8)--(p->s).work[2] != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 2:
      ((p->props).anubis).unk_c0 = (((p->props).anubis).unk_c0 & ~0x20) | 0x40;
      (p->s).flags |= DISPLAY;
      SetMotion(&p->s, MOTION(0xAF, 0x0E));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u16 h = (p->body).hp;
        u8* a = &((p->props).anubis).unk_cc[1];
        s32 z = 0;
        *a = h;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      break;
  }
}

void createPantheonZombie(struct Boss* anubis, s32 x, s32 y);

// 0x08050CFC
void anubisMode8(struct Boss* p) {
  register u32* fp asm("r8");
  s32 off;
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x53);
      (p->s).work[2] = 0x3C;
      SetMotion(&p->s, MOTION(0xAF, 0x03));
      *(u32*)((u8*)p + 0xc0) |= 0x80;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).work[2];
      fp = (u32*)((u8*)p + 0xc0);
      if (t == 0) {
        goto upd;
      }
      t--;
      (p->s).work[2] = t;
      if ((u8)t != 0) {
        goto upd;
      }
      LOAD_STATIC_GRAPHIC(SM076_PANTHEON_ZOMBIE);
      {
        register s32 cnt asm("r6");
        register u32 rnd asm("r1");
        register u32 acc asm("r0");
        u32 rv;
        rnd = RNG_0202f388;
        acc = 0x343FD;
        acc *= rnd;
        acc += 0x269EC3;
        rv = acc << 1;
        asm("" : "+r"(rv));
        RNG_0202f388 = rv >> 1;
        {
          register u32 b1 asm("r1");
          register s32 n1 asm("r0");
          b1 = rv >> 0x11;
          n1 = 1;
          b1 &= n1;
          n1 = b1 + 1;
          if (n1 == 0) {
            goto snd;
          }
          off = 0;
          cnt = n1;
        }
        do {
          register s32 x asm("r4");
          register s32 b asm("r0");
          s32 y;
          {
            register struct Zero* z asm("r0");
            z = pZero2;
            x = (z->s).coord.x;
          }
          x += -0x3200;
          x += off;
          {
            register u8* bp asm("r0");
            bp = (u8*)p;
            asm("" : "+r"(bp));
            bp += 0xb8;
            b = *(s32*)bp;
          }
          {
            register s32 lo asm("r1");
            lo = b + -0x7000;
            if (x < lo) {
              x = lo;
            }
          }
          b += 0xE0 * 128;
          if (x > b) {
            x = b;
          }
          y = FUN_08009f6c(x, (p->s).coord.y);
          createPantheonZombie(p, x, y);
          off += 0xC8 * 128;
          cnt--;
        } while (cnt != 0);
      }
    snd:
      PlaySound(0x55);
    upd:
      UpdateMotionGraphic(&p->s);
      asm volatile("" ::"r"(off));
      {
        register s32 f asm("r1");
        register s32 k asm("r0");
        f = *fp;
        k = 0x80;
        f &= k;
        if (f == 0) {
          (p->s).mode[1] = 1;
          (p->s).mode[2] = f;
        }
      }
      break;
    }
  }
}


// 0x08050E44
void FUN_08050e44(struct Boss* p) {
  struct Entity* e = (p->s).unk_28;
  register s32 m asm("r1");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32 k10;
      register s32 z6 asm("r6");
      {
        register u8 f2 asm("r0");
        f2 = (p->s).flags2;
        k10 = 0x10;
        asm("" : "+r"(k10));
        z6 = 0;
        f2 |= k10;
        (p->s).flags2 = f2;
      }
      (p->s).invincibleID = e->uniqueID;
      {
        u8* a = (u8*)p + 0x8c;
        *(s32*)a = m;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = m;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = m;
      }
      (p->s).flags &= ~4;
      {
        register s32 one asm("r2");
        register s32 xv asm("r1");
        u32 t0 = e->flags;
        t0 >>= 4;
        one = 1;
        t0 &= one;
        ((p->s).spr).xflip = t0;
        xv = (u32)e->flags >> 4;
        xv &= one;
        {
          register u8* oa asm("ip");
          s32 sh4, ov, m11;
          oa = (u8*)p + 0x4a;
          sh4 = xv << 4;
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          m11 |= sh4;
          *oa = m11;
        }
        if (xv != 0) {
          register u8 g asm("r0");
          g = (p->s).flags;
          g |= k10;
          (p->s).flags = g;
        } else {
          register u8 h asm("r1");
          register u8 g2 asm("r0");
          h = (p->s).flags;
          asm("" : "+r"(h));
          g2 = 0xEF;
          g2 &= h;
          (p->s).flags = g2;
        }
      }
      SetMotion(&p->s, 0xAF07);
      (p->s).mode[2]++;
      asm volatile("" : "+l"(z6));
      FALLTHROUGH;
    }
    case 1: {
      register s32 dx asm("r1");
      {
        s32 cx = (p->s).coord.x;
        dx = (p->s).d.x;
        (p->s).coord.x = cx + dx;
      }
      {
        register s32 k asm("r0");
        if ((p->s).work[3] != 0) {
          k = 0xF6;
        } else {
          k = 0xFA;
        }
        (p->s).d.x = dx * k / 256;
      }
      FUN_0801779c(&p->s);
      if (e->mode[0] == 4) {
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
        SET_BOSS_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

// 0x08050F38
void anubis_08050f38(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x53);
      *((u8*)p + 0xcf) = 2;
      *(u32*)((u8*)p + 0xc0) |= 0x100;
      (p->s).work[2] = 0x1E;
      SetMotion(&p->s, MOTION(0xAF, 0x03));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t <<= 24;
      if (t == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      register u8* pc asm("r5");
      s32 v;
      {
        register u8* pc0 asm("r0");
        register u8 cv asm("r1");
        pc0 = (u8*)p + 0xce;
        cv = *pc0;
        asm volatile("add %0, %1, #0" : "=&l"(pc) : "l"(pc0));
        if (cv != 0) {
          v = 0;
        } else {
          v = RANDOM(RNG_0202f388) % 3 + 1;
        }
      }
      *pc = v;
      FUN_08010188(*pc);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      register u32 rv asm("r3");
      rv = FUN_080101a8();
      if (rv == 0) {
        *(u32*)((u8*)p + 0xc0) &= ~0x100;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = rv;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);

// 0x08051018
void anubis_08051018(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 one asm("r5");
      {
        u8* a = (u8*)p + 0x8c;
        s32 z = 0;
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z;
      }
      (p->s).flags &= ~COLLIDABLE;
      {
        register u16 ms asm("r2");
        register s32 t asm("r0");
        ms = gStageRun.missionStatus;
        one = 1;
        asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one));
        t &= ms;
        if (t != 0) {
          register u8 av asm("r1");
          register s32 t2 asm("r0");
          av = gStageRun.vm.active;
          asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(one));
          t2 &= av;
          if (t2 == 0) {
            gStageRun.missionStatus = (ms & 0xFFFE) | MISSION_SUCCESS;
          }
        }
      }
      (p->s).work[2] = 0x50;
      SetMotion(&p->s, MOTION(0xAF, 0x04));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if (((p->s).scriptEntity->flags & 0x80) == 0) {
        break;
      }
      goto inc;
    case 2:
      (p->s).unk_2c = CreateBossExplosion(&p->s, (struct Coord*)0x083635DC);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      if (((p->s).unk_2c)->mode[0] <= 1) {
        break;
      }
      gStageRun.vm.active |= 2;
    inc:
      (p->s).mode[2]++;
      break;
    case 4:
      break;
  }
}

struct Entity* FUN_080b2b40(u8 kind, struct Coord* c, s32 r2, u8 r3);

// 0x080510F0
void anubis_080510f0(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dir asm("r6");
      struct Entity* e;
      PlaySound(0x2f);
      dir = *((u8*)p + 0xcc);
      e = AllocEntityFirst(gBossHeaderPtr);
      if (e != NULL) {
        register s32 z asm("r2");
        register s32 z0 asm("r0");
        {
          register u8* tc asm("r1");
          tc = (u8*)e + 0x25;
          z = 0;
          z0 = 0x18;
          *tc = z0;
        }
        {
          register const BossFunc** tb asm("r1");
          tb = (const BossFunc**)gBossFnTable;
          e->id = 0xb;
          e->onUpdate = (void*)tb[0xb][0];
        }
        z0 = 0;
        *(u16*)((u8*)e + 0x20) = z;
        *((u8*)e + 0x22) = z0;
        {
          register s32 h asm("r1");
          register s32 g asm("r0");
          h = e->flags2;
          asm("" : "+r"(h));
          g = 0x10;
          g |= h;
          e->flags2 = g;
        }
        *((u8*)e + 0x1d) = *((u8*)e + 0x1c);
        e->coord.x = (p->s).coord.x;
        e->coord.y = (p->s).coord.y;
        {
          register s32 v asm("r0");
          register s32 sh asm("r1");
          v = 0x80 << 1;
          sh = dir << 9;
          v -= sh;
          e->d.x = v;
        }
        e->unk_28 = &p->s;
        {
          register s32 one asm("r1");
          register s32 fv asm("r0");
          one = 1;
          *((u8*)e + 0x10) = one;
          fv = (u32)(p->s).flags >> 4;
          fv &= one;
          fv ^= dir;
          *((u8*)e + 0x13) = fv;
        }
      }
      SetMotion(&p->s, 0xAF06);
      {
        register u8* a asm("r0");
        register s32 z1 asm("r1");
        a = (u8*)p + 0x8c;
        z1 = 0;
        asm volatile("str %0, [%1]" ::"l"(z1), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        asm volatile("str %0, [%1]" ::"l"(z1), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        *a = z1;
      }
      {
        register u8 h2 asm("r1");
        register u8 g2 asm("r0");
        h2 = (p->s).flags;
        asm("" : "+r"(h2));
        g2 = 0xFB;
        g2 &= h2;
        (p->s).flags = g2;
      }
      {
        if ((gStageRun.missionStatus & 1) != 0) {
          if ((*((u8*)&gStageRun + 0x12) & 1) == 0) {
            gStageRun.missionStatus = (gStageRun.missionStatus & 0xFFFE) | 0x10;
          }
        }
      }
      {
        register s32 v2 asm("r0");
        register s32 sh2 asm("r1");
        v2 = 0x80 << 1;
        sh2 = dir << 9;
        v2 -= sh2;
        (p->s).d.x = v2;
      }
      {
        struct Coord c;
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y;
        ((void (*)(s32, struct Coord*, s32, s32))FUN_080b2b40)(0, &c, 0x80 << 2, dir);
      }
      (p->s).work[2] = 0x32;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 dv asm("r2");
      register s32 dir2 asm("r3");
      (p->s).coord.x += (p->s).d.x;
      dv = (p->s).d.x;
      dir2 = *((u8*)p + 0xcc);
      {
        register s32 m asm("r0");
        if (((p->s).flags & 0x10) != 0) {
          if (dir2 != 1) {
            goto fast;
          }
          goto slow;
        } else {
          if (dir2 == 0) {
            goto slow;
          }
        fast:
          m = 0xfa;
          goto mul;
        }
      slow:
        m = 0xf6;
      mul:
        m = dv * m;
        if (m < 0) {
          m += 0xff;
        }
        (p->s).d.x = m >> 8;
      }
      (p->s).work[2]--;
      if (((p->s).scriptEntity->flags & 0x80) != 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).unk_2c = (struct Entity*)CreateBossExplosion(&p->s, (struct Coord*)0x083635E4);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      if (((p->s).unk_2c)->mode[0] <= 1) {
        break;
      }
      {
        register struct StageRun* sr2 asm("r2");
        register s32 g3 asm("r0");
        register s32 h3 asm("r1");
        sr2 = &gStageRun;
        h3 = *((u8*)sr2 + 0x12);
        asm("" : "+r"(h3));
        g3 = 2;
        g3 |= h3;
        *((u8*)sr2 + 0x12) = g3;
      }
      (p->s).mode[2]++;
      break;
    case 4:
      break;
  }
}


void Anubis_Init(struct Boss* p);
void Anubis_Update(struct Boss* p);
void Anubis_Die(struct Boss* p);

// clang-format off
const BossRoutine gAnubisRoutine = {
    [ENTITY_INIT] =      Anubis_Init,
    [ENTITY_UPDATE] =    Anubis_Update,
    [ENTITY_DIE] =       Anubis_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080503c8(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[11] = {
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
    nop_080503c8,
};
// clang-format on

void anubisMode0(struct Boss* p);
void anubisNeutral(struct Boss* p);
void anubisMode2(struct Boss* p);
void anubisMode3(struct Boss* p);
void anubisMode4(struct Boss* p);
void anubisMode5(struct Boss* p);
void anubisMode6(struct Boss* p);
void anubisMode7(struct Boss* p);
void anubisMode8(struct Boss* p);
void FUN_08050e44(struct Boss* p);
void anubis_08050f38(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[11] = {
    anubisMode0,
    anubisNeutral,
    anubisMode2,
    anubisMode3,
    anubisMode4,
    anubisMode5,
    anubisMode6,
    anubisMode7,
    anubisMode8,
    FUN_08050e44,
    anubis_08050f38,
};
// clang-format on

// --------------------------------------------

void anubis_08051018(struct Boss* p);
void anubis_080510f0(struct Boss* p);

static const BossFunc sDeads[2] = {
    anubis_08051018,
    anubis_080510f0,
};

// --------------------------------------------

// 0x0836356c
static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(52)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 6,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(52)},
    },
};

static const u8 sInitModes[4] = {0, 9, 0, 0};
static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};

static const u8 u8_ARRAY_083635c0[9] = {5, 2, 10, 4, 5, 8, 2, 10, 4};
static const u8 u8_ARRAY_083635c9[8] = {2, 2, 2, 2, 3, 3, 3, 3};
static const u8 u8_ARRAY_083635d1[8] = {2, 2, 3, 3, 3, 4, 4, 4};

static const struct Coord sExplosionCoords[2] = {
    {PIXEL(2), -PIXEL(8)},
    {PIXEL(4), -PIXEL(6)},
};
