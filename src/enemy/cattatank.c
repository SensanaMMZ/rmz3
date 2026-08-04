#include "camera.h"
#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "physics.h"
#include "stagerun.h"
#include "zero.h"

struct Enemy* FUN_08098838(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CATTATANK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
    (p->s).work[1] = 1;
  }
  return p;
}

void FUN_08099eb4(struct Body* body0, struct Coord* c0);
void Cattatank_Update(struct Enemy* p);

// 0x0809889C
void Cattatank_Init(struct Enemy* p) {
  register u8* xf asm("r4");
  register u8* oa asm("r3");
  u8* b8;
  register s32 z asm("r8");
  register s32 v asm("r5");
  register s32 zr0 asm("r0");
  InitNonAffineMotion(&p->s);
  {
    register u8 g asm("r0");
    register u8 h asm("r1");
    h = (p->s).flags;
    g = 1;
    v = 0;
    g |= h;
    h = 2;
    g |= h;
    {
      register s32 zt asm("r1");
      zt = 0;
      asm volatile("mov %0, %1" : "=r"(z) : "l"(zt));
    }
    h = 4;
    g |= h;
    (p->s).flags = g;
  }
  {
    register struct Body* bd asm("r4");
    bd = &p->body;
    InitBody(bd, (const struct Collision*)0x0836A4D8, &(p->s).coord, 8);
    *(struct Enemy**)((u8*)bd + 0x2c) = p;
    *(void**)((u8*)bd + 0x24) = (void*)FUN_08099eb4;
    b8 = (u8*)p + 0xb8;
    *b8 = v;
    *(s32*)((u8*)p + 0xbc) = v;
    if ((p->s).work[0] == 0) {
      register u8* o2 asm("r2");
      register s32 k asm("r3");
      v = 1;
      (p->s).flags |= 0x10;
      xf = (u8*)bd - 0x28;
      *xf = v;
      o2 = (u8*)p + 0x4a;
      k = 0x10;
      {
        register s32 m asm("r0");
        register s32 ov asm("r1");
        ov = *o2;
        m = 0x11;
        m = -m;
        m &= ov;
        m |= k;
        *o2 = m;
      }
      *b8 = v;
      oa = o2;
    } else {
      register u8* o3 asm("r1");
      (p->s).flags &= 0xEF;
      oa = (u8*)p + 0x4c;
      *oa = v;
      o3 = (u8*)p + 0x4a;
      {
        register s32 m2 asm("r0");
        register s32 ov2 asm("r2");
        ov2 = *o3;
        m2 = 0x11;
        m2 = -m2;
        m2 &= ov2;
        *o3 = m2;
      }
      *b8 = v;
      xf = oa;
      oa = o3;
    }
  }
  v = (p->s).work[1];
  if (v == 1) {
    if ((pZero2->s).coord.x < (p->s).coord.x) {
      register s32 zr asm("r2");
      zr = 0;
      (p->s).flags &= 0xEF;
      *xf = zr;
      {
        register s32 m3 asm("r0");
        register s32 ov3 asm("r1");
        ov3 = *oa;
        m3 = 0x11;
        m3 = -m3;
        m3 &= ov3;
        *oa = m3;
      }
      *b8 = zr;
    } else {
      register s32 k2 asm("r2");
      (p->s).flags |= 0x10;
      *xf = v;
      k2 = 0x10;
      {
        register s32 m4 asm("r0");
        register s32 ov4 asm("r1");
        ov4 = *oa;
        m4 = 0x11;
        m4 = -m4;
        m4 &= ov4;
        m4 |= k2;
        *oa = m4;
      }
      *b8 = v;
    }
    {
      register u32 tbl asm("r1");
      register s32 one asm("r1");
      EntityFunc** rt;
      tbl = (u32)gEnemyFnTable;
      rt = (EntityFunc**)((((p->s).id) << 2) + tbl);
      one = 1;
      *(u32*)((p->s).mode) = one;
      (p->s).onUpdate = (void*)((*rt)[1]);
      zr0 = 0;
      asm volatile("strb %0, [%1, #0xd]" :: "l"(zr0), "l"(p) : "memory");
    }
  } else {
    register u32 tbl2 asm("r1");
    register s32 one2 asm("r1");
    EntityFunc** rt2;
    tbl2 = (u32)gEnemyFnTable;
    rt2 = (EntityFunc**)((((p->s).id) << 2) + tbl2);
    one2 = 1;
    *(u32*)((p->s).mode) = one2;
    (p->s).onUpdate = (void*)((*rt2)[1]);
    zr0 = 0;
    (p->s).mode[1] = one2;
  }
  (p->s).mode[2] = zr0;
  (p->s).mode[3] = zr0;
  {
    register s32 zz asm("r4");
    zz = 0;
    (p->s).d.y = zz;
    (p->s).d.x = zz;
    *((u8*)p + 0xbb) = zz;
    (p->s).d.x = zz;
    if (IsFrozen(&p->s) != 0) {
      SetMotion(&p->s, 0xD503);
      UpdateMotionGraphic(&p->s);
    }
    {
      u8* q = (u8*)p + 0xc0;
      *q = zz;
      asm("" : "+r"(q));
      q -= 6;
      asm("" : "+r"(q));
      *q = zz;
    }
  }
  Cattatank_Update(p);
}


extern const EnemyFunc sUpdates1[10];
extern const EnemyFunc sUpdates2[10];
bool8 cattatank_08099e20(struct Enemy* p);
void Cattatank_Die(struct Enemy* p);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

void Cattatank_Update(struct Enemy* p) {
  u8 m;
  if ((p->body).status & BODY_STATUS_DEAD) {
    if ((p->s).mode[1] == 6) {
      if (!IsFrozen(&p->s)) {
        goto dispatch1;
      }
    }
    (p->s).mode[3] = 0;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Cattatank_Die(p);
    return;
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x3000) {
    if (gStageRun.vm.camera.viewport.y + 0x4FFF < (p->s).coord.y + 0x2000) {
      if ((p->s).work[1] == 1) {
        (p->s).mode[3] = 1;
        PlaySound(0x2a);
        TryDropItem(1, &(p->s).coord);
        if (gMission.enemyCount <= 0x270E) {
          gMission.enemyCount++;
        }
        TryDropZakoDisk(p, &(p->s).coord);
        (p->s).flags &= ~DISPLAY;
        SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
        return;
      }
    }
  }
dispatch1:
  (sUpdates1[(p->s).mode[1]])(p);
  cattatank_08099e20(p);
  m = (p->s).mode[1];
  if (m == 6 || m == 7) goto dispatch2;
  if (m == 9) goto dispatch2;
  if (IsFrozen(&p->s)) {
    return;
  }
dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/cattatank_p1_p2_b.inc");

bool8 nop_08099090(struct Enemy* p) { return TRUE; }

void cattatank_08099094(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags &= ~DISPLAY;
      (p->s).work[2] = 0x32;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((p->s).work[2] != 0) {
        if (--(p->s).work[2] != 0) break;
      }
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 nop_080990d4(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[18];

void FUN_080990d8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      {
        u32 fl = (p->s).flags;
        register u32 t asm("r0");
        register s32 z5 asm("r5");
        t = 1;
        asm volatile("" : "+r"(t));
        z5 = 0;
        asm volatile("" :: "r"(z5));
        t |= fl;
        (p->s).flags = t;
      }
      SetMotion(&p->s, 0xD503);
      SetDDP(&p->body, &sCollisions[1]);
      if ((pZero2->s).coord.x < (p->s).coord.x) {
        s32 z2 = 0;
        asm("" : "+r"(z2));
        (p->s).flags &= 0xEF;
        ((p->s).spr).xflip = z2;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        *((u8*)p + 0xb8) = z2;
      } else {
        s32 o3 = 1;
        (p->s).flags |= 0x10;
        ((p->s).spr).xflip = o3;
        {
          register u8* oa asm("ip");
          u32 sh4;
          s32 ov, m11;
          oa = (u8*)p + 0x4a;
          sh4 = 0x10;
          asm("" : "+r"(sh4));
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          m11 |= sh4;
          *oa = m11;
        }
        *((u8*)p + 0xb8) = o3;
      }
      (p->s).d.x >>= 1;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 ny, nx, off, push;
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      nx = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = nx;
      if ((p->s).d.x > 0) {
        off = -0x800;
        asm volatile("");
      } else {
        off = 0x800;
        asm volatile("");
      }
      push = PushoutToUp1(nx + off, ny);
      if (push != 0) {
        (p->s).d.y = 0;
        (p->s).coord.y += push;
        goto inc34;
      }
      break;
    }
    case 2:
      (*((u8*)p + 0xbb))++;
      SetMotion(&p->s, 0xD504);
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
      inc34:
        (p->s).mode[2]++;
      }
      break;
    case 4:
      SetMotion(&p->s, 0xD500);
      (p->s).work[2] = 0x14;
      (p->s).mode[2]++;
      // fallthrough
    case 5: {
      s32 t;
      u32 t8;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t8 = (u8)t;
      if (t8 == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = t8;
      }
      break;
    }
  }
}

bool8 nop_0809925c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/cattatank_p4.inc");

bool8 nop_080994e8(struct Enemy* p) { return TRUE; }

// Scratch-parity basin: the case-12 flip block wants its flags load before the
// m10 const with mask-side and/or dests, the -0x11 synth after the byte load,
// and one turn-check arm keeps re-inverting to a direct conditional. Six sites
// of pure register parity; the walker, probes, and turn logic stream-match.
NON_MATCH void FUN_080994ec(struct Enemy* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).unk_coord.x = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 v;
      SetMotion(&p->s, 0xD502);
      SetDDP(&p->body, &sCollisions[1]);
      if (!((p->s).flags & 0x10)) {
        v = 0x100;
        asm volatile("");
      } else {
        v = -0x100;
      }
      (p->s).d.x = v;
      (p->s).d.y = 0;
      (p->s).unk_coord.x = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 2: {
      s32 dx, nx, r, px, c0;
      UpdateMotionGraphic(&p->s);
      c0 = (p->s).coord.x;
      dx = (p->s).d.x;
      nx = c0 + dx;
      (p->s).coord.x = nx;
      (p->s).unk_coord.x += 0x100;
      if (dx > 0) {
        r = PushoutToLeft1(nx + 0xA00, (p->s).coord.y);
      } else {
        r = PushoutToRight1(nx + -0xA00, (p->s).coord.y);
      }
      if (r != 0) {
        (p->s).coord.x += r;
      }
      if ((p->s).d.x > 0) {
        px = (p->s).coord.x + 0xA00;
      } else {
        px = (p->s).coord.x + -0xA00;
      }
      {
        s32 r0v = FUN_08009f6c(px, (p->s).coord.y);
        s32 gr;
        asm volatile("add %0, %1, #0" : "=&l"(gr) : "l"(r0v));
        if (gr != (p->s).coord.y) {
          (p->s).coord.x -= (p->s).d.x;
        }
      }
      if ((p->s).work[1] == 1) {
        if (*((u8*)p + 0xbb) > 1) {
          struct Zero* z2 = pZero2;
          if ((p->s).coord.y >= (z2->s).coord.y) {
            if ((p->s).d.x > 0) {
              if ((z2->s).coord.x <= (p->s).coord.x) {
                goto noturn;
              }
              asm volatile("");
              goto turn;
            } else {
              if ((z2->s).coord.x < (p->s).coord.x) {
                goto turn;
              }
            }
          }
        }
      } else {
        if ((p->s).d.x > 0) {
          if ((pZero2->s).coord.x <= (p->s).coord.x) {
            goto noturn;
          }
          asm volatile("");
          goto turn;
        } else {
          if ((pZero2->s).coord.x < (p->s).coord.x) {
          turn:
            (p->s).mode[2] = 0xA;
          }
        }
      }
    noturn:
      if ((p->s).unk_coord.x > 0x1800) {
        (p->s).mode[2] = 3;
      }
      break;
    }
    case 3:
      SetMotion(&p->s, 0xD500);
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4: {
      s32 t;
      u8 t1;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t1 = t;
      if (t1 == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = t1;
      }
      break;
    }
    case 10:
      SetMotion(&p->s, 0xD511);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 11:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 12: {
      u32 m10;
      s32 mEF;
      SetMotion(&p->s, 0xD512);
      m10 = 0x10;
      asm("" : "+r"(m10));
      if (!((p->s).flags & m10)) {
        u8 one = 1;
        u8* oa;
        (p->s).flags |= 0x10;
        ((p->s).spr).xflip = one;
        oa = (u8*)p + 0x4a;
        asm volatile("mov %0, #0x11\n\tneg %0, %0" : "=l"(mEF));
        *oa = (u8)((*oa & mEF) | m10);
      } else {
        u8 z = 0;
        u8* oa;
        (p->s).flags &= ~0x10;
        ((p->s).spr).xflip = z;
        oa = (u8*)p + 0x4a;
        asm volatile("mov %0, #0x11\n\tneg %0, %0" : "=l"(mEF));
        *oa = (u8)(*oa & mEF);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 13:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2] = 1;
      }
      break;
  }
#else
  INCCODE("asm/enemy/cattatank_94ec.inc");
#endif
}

bool8 nop_0809973c(struct Enemy* p) { return TRUE; }

// Motion-index probe basin: retail loads motion.cmdIdx into the zero-index
// register with the address copy saved after the load (ldrsb r1,[r0,r1];
// adds r5,r0) and cross-merges the third SetDDP bl into case-5's; the
// cv/ci and transfer spellings land the copy before the load or duplicate it.
NON_MATCH void FUN_08099740(struct Enemy* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0xD507);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      goto tick;
    case 2:
      SetMotion(&p->s, 0xD508);
      SetDDP(&p->body, &sCollisions[4]);
      (p->s).work[2] = 0x32;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      if (((p->body).status & 4) && !((p->body).prevStatus & 4)) {
        PlaySound(0x52);
      }
      UpdateMotionGraphic(&p->s);
      {
        s8 cv = *(s8*)((u8*)p + 0x71);
        s8* ci = (s8*)((u8*)p + 0x71);
        if (cv == 4 && (p->s).work[3] == 0) {
          (p->s).work[3]++;
          SetDDP(&p->body, &sCollisions[7]);
        }
        if (*ci == 5 && (p->s).work[3] == 1) {
          (p->s).work[3]++;
          SetDDP(&p->body, &sCollisions[10]);
        }
        if (*ci == 6 && (p->s).work[3] == 2) {
          (p->s).work[3]++;
          SetDDP(&p->body, &sCollisions[13]);
        }
      }
      goto mchk;
    case 4:
      SetMotion(&p->s, 0xD509);
      SetDDP(&p->body, &sCollisions[10]);
      (p->s).work[2] = 8;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 5:
      if (((p->body).status & 4) && !((p->body).prevStatus & 4)) {
        PlaySound(0x52);
      }
      UpdateMotionGraphic(&p->s);
      {
        s8 cv = *(s8*)((u8*)p + 0x71);
        s8* ci = (s8*)((u8*)p + 0x71);
        if (cv == 1 && (p->s).work[3] == 0) {
          (p->s).work[3]++;
          SetDDP(&p->body, &sCollisions[7]);
        }
        if (*ci == 2 && (p->s).work[3] == 1) {
          (p->s).work[3]++;
          SetDDP(&p->body, &sCollisions[4]);
        }
      }
    mchk:
      if ((p->s).motion.state != 3) {
        break;
      }
    tick:
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((u32)(t << 24) == 0) {
          (p->s).mode[2]++;
        }
      }
      break;
    case 6: {
      s32 zx = pZero2->s.coord.x;
      s32 px = (p->s).coord.x;
      s32 d = zx - px;
      if (d > 0) {
        if (d > 0x39FF) {
          goto far;
        }
      } else if (px - zx > 0x39FF) {
        goto far;
      }
      (p->s).mode[1] = 3;
      (p->s).mode[2] = 0;
      break;
    far:
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
    }
  }
#else
  INCCODE("asm/enemy/cattatank_99740.inc");
#endif
}

bool8 nop_08099950(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[18];

void FUN_08099954(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0xD50C);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0x18;
      if ((pZero2->s).coord.x < (p->s).coord.x) {
        (p->s).d.x = 0x60;
      } else {
        (p->s).d.x = -0x60;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 ny;
      s32 v = (p->s).d.x;
      v += (-v << 4) >> 8;
      (p->s).d.x = v;
      (p->s).coord.x += v;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      {
        s32 po;
        if ((p->s).d.x > 0) {
          po = PushoutToUp1((p->s).coord.x - 0xA00, ny);
        } else {
          po = PushoutToUp1((p->s).coord.x + 0xA00, ny);
        }
        if (po != 0) {
          u8* bb = (u8*)p + 0xbb;
          u8 nv = *bb + 1;
          s32 z = 0;
          *bb = nv;
          (p->s).coord.y += po;
          (p->s).d.y = z;
        }
      }
      {
        register s32 fl asm("r3");
        s32 c10;
        fl = (p->s).flags;
        c10 = 0x10;
        asm("" : "+r"(c10));
        if (!(c10 & fl)) {
          if ((pZero2->s).coord.x > (p->s).coord.x) {
            s32 one = 1;
            u8* oa;
            s32 ov;
            {
              s32 cc = 0x10;
              asm("" : "+r"(cc));
              (p->s).flags = cc | fl;
              asm("" : "+r"(fl));
            }
            ((p->s).spr).xflip = one;
            oa = (u8*)&((p->s).spr).oam + 6;
            ov = *oa;
            {
              s32 m11 = -0x11;
              asm("" : "+r"(m11));
              *oa = (m11 & ov) | c10;
            }
            *(u8*)((u8*)p + 0xb8) = one;
          }
        } else {
          if ((pZero2->s).coord.x < (p->s).coord.x) {
            s32 zz = 0;
            u8* oa;
            s32 ov;
            {
              s32 cc = 0xEF;
              asm("" : "+r"(cc));
              (p->s).flags = cc & fl;
              asm("" : "+r"(fl));
            }
            ((p->s).spr).xflip = zz;
            oa = (u8*)&((p->s).spr).oam + 6;
            ov = *oa;
            {
              s32 m11 = -0x11;
              asm("" : "+r"(m11));
              *oa = m11 & ov;
            }
            *(u8*)((u8*)p + 0xb8) = zz;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      {
        s32 raw = (p->s).work[2] - 1;
        u8 t;
        (p->s).work[2] = raw;
        t = raw;
        if (t == 0) {
          (p->s).mode[1] = 1;
          (p->s).mode[2] = t;
        }
      }
      break;
    }
  }
}

bool8 nop_08099a94(struct Enemy* p) { return TRUE; }

void FUN_08099a98(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0xD50A);
      SetDDP(&p->body, &sCollisions[16]);
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        (p->s).d.x = -0x600;
        (p->s).unk_coord.x = -0xC0;
      } else {
        (p->s).d.x = 0x600;
        (p->s).unk_coord.x = 0xC0;
      }
      (p->s).d.y = 0;
      (p->s).work[2] = 0x1A;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (p->s).unk_coord.x - (p->s).d.x;
      s32 dx = (p->s).d.x + ((t * 28) >> 8);
      s32 g;
      s32 px;
      s32 r;
      s32 z;
      struct Entity** slot;
      (p->s).d.x = dx;
      (p->s).coord.x += dx;
      g = (p->s).d.y + 0x40;
      (p->s).d.y = g;
      if (g > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      {
        s32 t2 = (p->s).work[2] - 1;
        asm volatile("movs %0, #0" : "=l"(z) : "r"(t2));
        (p->s).work[2] = t2;
        if ((t2 << 24) == 0) {
          (p->s).mode[2]++;
        }
      }
      if ((p->s).d.x > 0) {
        px = (p->s).coord.x + -0xA00;
      } else {
        px = (p->s).coord.x + 0xA00;
      }
      r = PushoutToUp1(px, (p->s).coord.y);
      if (r != 0) {
        (*((u8*)p + 0xbb))++;
        (p->s).coord.y += r;
        (p->s).d.y = z;
      }
      slot = (struct Entity**)((u8*)p + 0xbc);
      if (isKilled(*slot)) {
        goto clear1;
      }
      break;
    clear1: {
      u8* c0 = (u8*)p + 0xc0;
      s32 zz = 0;
      *c0 = zz;
      *slot = (struct Entity*)zz;
      break;
    }
    }
    case 2:
      SetMotion(&p->s, 0xD50B);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s32 t = (p->s).unk_coord.x - (p->s).d.x;
      s32 dx = (p->s).d.x + ((t * 28) >> 8);
      s32 g;
      s32 px;
      register s32 r asm("r2");
      s32 ny;
      struct Entity** slot;
      (p->s).d.x = dx;
      (p->s).coord.x += dx;
      g = (p->s).d.y + 0x40;
      (p->s).d.y = g;
      if (g > 0x700) {
        (p->s).d.y = 0x700;
      }
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      if ((p->s).d.x > 0) {
        px = (p->s).coord.x + -0xA00;
      } else {
        px = (p->s).coord.x + 0xA00;
      }
      r = PushoutToUp1(px, ny);
      if (r != 0) {
        u8* bb = (u8*)p + 0xbb;
        u8 nv = *bb + 1;
        s32 z2 = 0;
        *bb = nv;
        (p->s).coord.y += r;
        (p->s).d.y = z2;
      }
      slot = (struct Entity**)((u8*)p + 0xbc);
      if (isKilled(*slot)) {
        u8* c0 = (u8*)p + 0xc0;
        s32 zz = 0;
        *c0 = zz;
        *slot = (struct Entity*)zz;
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      if (*slot != NULL) {
        u8 k = *((u8*)p + 0xc0);
        if (k == 1) {
          if ((p->body).hp > 1) {
            goto set7;
          }
          (p->s).mode[3] = 0;
          asm volatile("");
          goto die;
        set7:
          (p->s).mode[1] = 7;
          (p->s).mode[2] = 0;
        } else if (k == 2) {
          if ((p->body).hp > 1) {
            goto set9;
          }
          (p->s).mode[3] = 0;
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          break;
        set9:
          asm volatile("");
          (p->s).mode[1] = 9;
          (p->s).mode[2] = 0;
        } else {
          if ((p->body).hp > 1) {
            goto set1;
          }
          (p->s).mode[3] = 0;
          goto die;
        set1:
          (p->s).mode[1] = 1;
          (p->s).mode[2] = 0;
        }
      } else {
        if ((p->body).hp > 1) {
          goto set1b;
        }
        (p->s).mode[3] = 0;
      die:
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        break;
      set1b:
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
    }
  }
}

bool8 nop_08099ce0(struct Enemy* p) { return TRUE; }

static const struct Collision sCollisions[18];

// 0x08099ce4
void FUN_08099ce4(struct Enemy* p) {
  s32 r;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[6]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if ((r = PushoutToUp1((p->s).coord.x - PIXEL(10), (p->s).coord.y)) != 0 ||
          (r = PushoutToUp1((p->s).coord.x + PIXEL(10), (p->s).coord.y)) != 0) {
        (p->s).coord.y += r;
        (p->s).d.y = 0;
      }
      break;
  }
  if (isKilled(*(struct Entity**)&p->props[8])) {
    p->props[12] = 0;
    *(struct Entity**)&p->props[8] = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 nop_08099d7c(struct Enemy* p) { return TRUE; }


void nop_08099d80(struct Enemy* p) {}

bool8 nop_08099d84(struct Enemy* p) { return TRUE; }

// 0x08099d88
void FUN_08099d88(struct Enemy* p) {
  s32 r;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[6]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if ((r = PushoutToUp1((p->s).coord.x - PIXEL(10), (p->s).coord.y)) != 0 ||
          (r = PushoutToUp1((p->s).coord.x + PIXEL(10), (p->s).coord.y)) != 0) {
        (p->s).coord.y += r;
        (p->s).d.y = 0;
      }
      break;
  }
  if (isKilled(*(struct Entity**)&p->props[8])) {
    p->props[12] = 0;
    *(struct Entity**)&p->props[8] = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoords[1];

bool8 cattatank_08099e20(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)&p->props[8];
  struct VFX* e;
  u8 attr;

  if (*slot == NULL && ((p->body).status & 1)) {
    e = ApplyElementEffect(0, &p->s, sElementCoords);
    *slot = e;
    if ((p->s).mode[1] != 6) {
      if (e != NULL) {
        attr = *(u8*)((u8*)p + 0x97) & 0xf0;
        if (attr == 0x10) {
          p->props[12] = 1;
          (p->s).mode[1] = 7;
          (p->s).mode[2] = 0;
        } else if (attr == 0x30) {
          p->props[12] = 2;
          (p->s).mode[1] = 9;
          (p->s).mode[2] = 0;
        }
      }
    } else if (e != NULL) {
      attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        p->props[12] = 1;
      } else if (attr == 0x30) {
        p->props[12] = 2;
      }
    }
  }
  return TRUE;
}

// 0x08099EB4
void FUN_08099eb4(struct Body* body0, struct Coord* c0) {
  register struct Body* body asm("r2");
  register const struct Collision* pr asm("r3");
  register struct Coord* c asm("r5");
  struct Entity* e;
  register u8 m asm("r0");
  register s32 z asm("r1");
  body = body0;
  c = c0;
  pr = (body->enemy)->processing;
  {
    u8 k = pr->atkType;
    if (k == 3 || k == 0xE || k == 0xF) {
      e = (struct Entity*)body->parent;
      if (*(u32*)((u8*)e + 0x8c) & 0x200) {
        if (e->coord.x < c->x) {
          register u8* w asm("r1");
          w = (u8*)e + 0xba;
          asm("" : "+r"(w));
          *w = 0xFF;
        } else {
          register u8* w asm("r1");
          w = (u8*)e + 0xba;
          asm("" : "+r"(w) : "r"(pr));
          *w = 0xFE;
        }
      }
    }
  }
  if ((*(u32*)&pr->atkType & 0x200FF) == 0x20002) {
    e = (struct Entity*)body->parent;
    if (e->mode[1] == 6) {
      return;
    }
    if (*(u32*)((u8*)e + 0x8c) & 0x200) {
      IsFrozen(e);
    }
    z = 0;
    m = 6;
    goto set;
  }
  e = (struct Entity*)body->parent;
  if ((body->processing)->kind != 2) {
    return;
  }
  if (pr->nature == 0x40) {
    return;
  }
  z = IsFrozen(e);
  if (z != 0) {
    return;
  }
  m = 5;
set:
  e->mode[1] = m;
  e->mode[2] = z;
}

void Cattatank_Init(struct Enemy* p);
void Cattatank_Update(struct Enemy* p);
void Cattatank_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gCattatankRoutine = {
    [ENTITY_INIT] =      Cattatank_Init,
    [ENTITY_UPDATE] =    Cattatank_Update,
    [ENTITY_DIE] =       Cattatank_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

bool8 nop_08099090(struct Enemy* p);
bool8 nop_080990d4(struct Enemy* p);
bool8 nop_0809925c(struct Enemy* p);
bool8 nop_080994e8(struct Enemy* p);
bool8 nop_0809973c(struct Enemy* p);
bool8 nop_08099950(struct Enemy* p);
bool8 nop_08099a94(struct Enemy* p);
bool8 nop_08099ce0(struct Enemy* p);
bool8 nop_08099d7c(struct Enemy* p);
bool8 nop_08099d84(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    (EnemyFunc)nop_08099090,
    (EnemyFunc)nop_080990d4,
    (EnemyFunc)nop_0809925c,
    (EnemyFunc)nop_080994e8,
    (EnemyFunc)nop_0809973c,
    (EnemyFunc)nop_08099950,
    (EnemyFunc)nop_08099a94,
    (EnemyFunc)nop_08099ce0,
    (EnemyFunc)nop_08099d7c,
    (EnemyFunc)nop_08099d84,
};
// clang-format on

void cattatank_08099094(struct Enemy* p);
void FUN_080990d8(struct Enemy* p);
void FUN_08099260(struct Enemy* p);
void FUN_080994ec(struct Enemy* p);
void FUN_08099740(struct Enemy* p);
void FUN_08099954(struct Enemy* p);
void FUN_08099a98(struct Enemy* p);
void FUN_08099ce4(struct Enemy* p);
void nop_08099d80(struct Enemy* p);
void FUN_08099d88(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    cattatank_08099094,
    FUN_080990d8,
    FUN_08099260,
    FUN_080994ec,
    FUN_08099740,
    FUN_08099954,
    FUN_08099a98,
    FUN_08099ce4,
    nop_08099d80,
    FUN_08099d88,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[18] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 1,
      priorityLayer : 0xFFFFFFFF,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(12), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(16), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(37), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(49), -PIXEL(21), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(3), -PIXEL(19), PIXEL(27), PIXEL(40)},
    },
};

static const struct Coord sElementCoords[1] = {
    {PIXEL(0), -PIXEL(18)},
};
