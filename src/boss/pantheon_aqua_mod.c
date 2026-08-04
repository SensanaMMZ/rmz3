#include "boss.h"
#include "collision.h"
#include "element.h"
#include "palette_animation.h"

extern struct Zero* pZero2;
#include "gfx.h"
#include "global.h"
#include "overworld.h"

void PantheonAquaMod_Init(struct Boss* p);
void PantheonAquaMod_Update(struct Boss* p);
void PantheonAquaMod_Die(struct Boss* p);

// clang-format off
const BossRoutine gPantheonAquaModRoutine = {
    [ENTITY_INIT] =      PantheonAquaMod_Init,
    [ENTITY_UPDATE] =    PantheonAquaMod_Update,
    [ENTITY_DIE] =       PantheonAquaMod_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) { return; }

bool8 tryKillPantheonAquaMod(struct Boss* p) {
  if ((((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0)) && !(gStageRun.missionStatus & MISSION_FAIL)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    PantheonAquaMod_Die(p);
    return TRUE;
  }
  return FALSE;
}

static void paquam_080512f8(struct Boss* p) {
  (p->props.paquam).x += PIXEL(1);
  (p->s).coord.y = (p->props.paquam).y;
  (p->s).coord.y += gSineTable[COORD_TO_PIXEL((p->props.paquam).x)] << 2;
}

static const BossFunc sDeads[1];

INCASM("asm/boss/pantheon_aqua_mod_p1_pre_a.inc");

static const BossFunc sUpdates1[9];
static const BossFunc sUpdates2[9];

void PantheonAquaMod_Update(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xc0);
  if (*slot != NULL && isKilled(*slot)) {
    *slot = NULL;
  }
  if (tryKillPantheonAquaMod(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void PantheonAquaMod_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_08051620(struct Boss* p) {}

u8 GetEntityPalID(struct Entity* p);
void paquam_080512f8(struct Boss* p);

// 0x08051624
void paquamNeutral(struct Boss* p) {
  register s32 z asm("r5");
  register u8* pb asm("r6");
  register struct Body* bd asm("r8");
  z = (p->s).mode[2];
  switch (z) {
    case 0: {
      SetMotion(&p->s, 0x4D01);
      (p->s).work[2] = 0x46;
      {
        register u8* q asm("r0");
        register s32 v asm("r1");
        q = (u8*)p + 0xb8;
        v = *q;
        pb = q;
        if (v != 0) {
          RemovePaletteAnimation(*pb);
          *pb = z;
        }
      }
      {
        register s32 g asm("r1");
        register s32 k asm("r2");
        {
          register s32 rv asm("r0");
          rv = ((s32 (*)(struct Entity*))GetEntityPalID)(&p->s);
          asm volatile("add %0, %1, #0" : "=l"(g) : "l"(rv));
        }
        g <<= 24;
        g = (u32)g >> 0x13;
        k = 0x80 << 2;
        {
          register s32 k2 asm("r0");
          asm volatile("add %0, %1, #0" : "=l"(k2) : "l"(k));
          g |= k2;
        }
        ((void (*)(s32, s32))StartPaletteAnimation)(0x54, g);
      }
      *pb = 0x54;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register u8* fr asm("r1");
      register s32 fv asm("r0");
      fr = (u8*)p + 0xb9;
      fv = *fr;
      if (fv != 0) {
        goto frozen;
      }
      {
        register s32* ef asm("r5");
        register s32 v2 asm("r1");
        register u8* q2 asm("r0");
        q2 = (u8*)p + 0xc0;
        v2 = *(s32*)q2;
        ef = (s32*)q2;
        if (v2 != 0) {
          goto tick;
        }
        q2 -= 0x34;
        if ((*(s32*)q2 & 1) == 0) {
          goto tick;
        }
        {
          register s32 st asm("r1");
          register s32 e0 asm("r0");
          e0 = *((u8*)p + 0x97);
          st = 0xf0;
          st &= e0;
          if (st != 0x10 && st != 0x20 && st != 0x30) {
            goto tick;
          }
        }
        *ef = (s32)ApplyElementEffect(0x15, &p->s, (const struct Coord*)0x08363950);
        pb = (u8*)p + 0xb8;
        {
          register s32 k3 asm("r7");
          k3 = 0x74;
          asm volatile("add %0, %0, %1" : "+l"(k3) : "l"(p));
          bd = (struct Body*)k3;
        }
        goto upd;
      }
    tick: {
      register s32 t asm("r0");
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t <<= 24;
      pb = (u8*)p + 0xb8;
      {
        register s32 k4 asm("r1");
        k4 = 0x74;
        k4 += (s32)p;
        bd = (struct Body*)k4;
      }
      if (t != 0) {
        goto upd;
      }
    }
      {
        register struct Zero* zz asm("r2");
        zz = pZero2;
        if ((*(s32*)((u8*)zz + 0x8c) & (0x80 << 2)) != 0) {
          goto upd;
        }
        {
          register s32 sv asm("r0");
          register u8* q3 asm("r0");
          q3 = (u8*)zz;
          q3 += 0xa4;
          asm volatile("mov r2, #0\n\tldrsh %0, [%1, r2]" : "=l"(sv) : "l"(q3) : "r2");
          if (sv == 0) {
            goto upd;
          }
        }
      }
      {
        register u32* rp asm("r2");
        register const u8* tb asm("r5");
        register u8* cur asm("r3");
        register u32 ix asm("r1");
        rp = &RNG_0202f388;
        tb = (const u8*)0x08363958;
        cur = (u8*)p + 0xc4;
        do {
          register u32 raw asm("r0");
          raw = *rp * 0x343FD;
          raw += 0x269EC3;
          raw <<= 1;
          *rp = raw >> 1;
          ix = raw >> 0x11;
          ix &= 3;
        } while (*(const u8*)(ix + (u32)tb) == *cur && *((u8*)p + 0xc5) > 1);
        {
          register const u8* sel asm("r2");
          sel = (const u8*)(ix + (u32)tb);
          if (*sel == *cur) {
            register u8* cnt asm("r1");
            register s32 cv asm("r0");
            cnt = (u8*)p + 0xc5;
            cv = *cnt;
            cv += 1;
            *cnt = cv;
          }
          {
            register s32 v3 asm("r0");
            register s32 zr asm("r1");
            v3 = *sel;
            zr = 0;
            *cur = v3;
            (p->s).mode[1] = *sel;
            (p->s).mode[2] = zr;
          }
        }
      }
    upd:
      paquam_080512f8(p);
      StepPaletteAnimation(*pb);
      UpdateMotionGraphic(&p->s);
      goto ddp;
    frozen:
      fv -= 1;
      *fr = fv;
      bd = (struct Body*)((u8*)p + 0x74);
    ddp:
      SetDDP(bd, (const struct Collision*)0x08363664);
      break;
    }
  }
}

INCASM("asm/boss/pantheon_aqua_mod_p2a.inc");

struct Entity* CreateVFX39(struct Coord* c, u8 r1, u8 r2);

// 0x080519d0
void paquam_080519d0(struct Boss* p) {
  register struct Entity* q asm("r3");
  register s32 dx asm("r5");
  switch ((p->s).mode[2]) {
    case 0: {
      struct Coord c;
      PlaySound(0x8d << 1);
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y + -0x1000;
      q = CreateVFX39(&c, 1, 0);
      (p->s).unk_2c = q;
      if (q != NULL) {
        register s32 z asm("r1");
        u8* a = (u8*)q + 0x7c;
        z = 0;
        *a = z;
        a -= 8;
        *a = z;
        a += 1;
        *a = z;
        a += 1;
        *a = z;
        *(s32*)((u8*)q + 0x78) = z;
      }
      {
        register s32 z2 asm("r1");
        z2 = 0;
        (p->s).work[2] = 0x32;
        (p->s).d.x = z2;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 v asm("r1");
      register s32 d asm("r0");
      v = (p->s).d.x;
      d = 0x5800 - v;
      d = d / 32;
      dx = v + d;
      (p->s).d.x = dx;
      q = (struct Entity*)(p->s).unk_2c;
      if (q == NULL) {
        goto dec;
      }
      goto upd78;
    }
    case 2: {
      register s32 z3 asm("r0");
      register u8* oa asm("r2");
      register s32 ov asm("r1");
      {
        register u8* xp asm("r1");
        xp = (u8*)p + 0x4c;
        z3 = 0;
        *xp = z3;
      }
      oa = (u8*)p + 0x4a;
      ov = *oa;
      z3 -= 0x11;
      z3 &= ov;
      *oa = z3;
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xEF;
        g &= h;
        (p->s).flags = g;
      }
      (p->s).coord.y = *(s32*)((u8*)p + 0xbc);
      SetMotion(&p->s, 0x9a << 7);
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
      q = (struct Entity*)(p->s).unk_2c;
      if (q == NULL) {
        goto dec;
      }
      dx = (p->s).d.x;
    upd78: {
      register s32 h8 asm("r2");
      register s32 m asm("r0");
      register s32 w8 asm("r1");
      h8 = dx;
      if (dx < 0) {
        h8 = dx + 7;
      }
      h8 >>= 3;
      w8 = (p->s).work[2];
      m = 1;
      m &= w8;
      m = h8 * m;
      *(s32*)((u8*)q + 0x78) = dx + m;
    }
    dec: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
    }
      UpdateMotionGraphic(&p->s);
      break;
    case 4: {
      u32 g0 = GetEntityPalID(&p->s);
      u32 g = (u8)g0 << 5;
      StartPaletteAnimation(0x52, g | 0x200);
      {
        register u8* pb8 asm("r1");
        register s32 pa asm("r0");
        pb8 = (u8*)p + 0xb8;
        pa = 0x52;
        *pb8 = pa;
        StepPaletteAnimation(pa);
      }
      (p->s).work[2] = 0x60;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5: {
      s32 t;
      {
        s32 v2 = (p->s).d.x - 0xA0;
        (p->s).d.x = v2;
        if (v2 < 0) {
          (p->s).d.x = 0;
        }
      }
      q = (struct Entity*)(p->s).unk_2c;
      if (q != NULL) {
        register s32 h8b asm("r2");
        register s32 mb asm("r0");
        register s32 w8b asm("r1");
        dx = (p->s).d.x;
        h8b = dx;
        if (dx < 0) {
          h8b = dx + 7;
        }
        h8b >>= 3;
        w8b = (p->s).work[2];
        mb = 1;
        mb &= w8b;
        mb = h8b * mb;
        *(s32*)((u8*)q + 0x78) = dx + mb;
      }
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 6:
      q = (struct Entity*)(p->s).unk_2c;
      {
        register u8* w7 asm("r1");
        w7 = (u8*)q + 0x77;
        *w7 = 1;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 7: {
      register u32 r asm("r1");
      r = (u8)StepPaletteAnimation(*((u8*)p + 0xb8));
      if (r == 3) {
        (p->s).mode[1] = r;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

#include "palette_animation.h"

u8 GetEntityPalID(struct Entity* p);
void createLaserSign(struct Entity* e, s32 x, s32 y);
void createLaserSign2(struct Entity* e);

void paquam_08051b8c(struct Boss* p) {
  register s32 m asm("r6");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      PlaySound(0xE4);
      {
        s32* w = (s32*)((u8*)p + 0xb4);
        register s32 v asm("r0");
        register s32 msk asm("r1");
        v = *w;
        msk = -5;
        v &= msk;
        msk -= 4;
        v &= msk;
        *w = v;
      }
      createLaserSign(&p->s, (p->s).coord.x, (p->s).coord.y);
      {
        register u8* pb asm("r5");
        pb = (u8*)p + 0xb8;
        if (*pb != 0) {
          RemovePaletteAnimation(*pb);
          *pb = m;
        }
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x58, g | 0x200);
        }
        *pb = 0x58;
      }
      SetMotion(&p->s, 0x4D01);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      register s32* w1 asm("r2");
      register s32* w asm("r6");
      register u8* pb asm("r5");
      s32 v;
      w1 = (s32*)((u8*)p + 0xb4);
      v = *w1;
      v &= 4;
      w = w1;
      asm("" : "+r"(w1));
      pb = (u8*)p + 0xb8;
      if (v != 0) {
        if (*pb != 0) {
          RemovePaletteAnimation(*pb);
          *pb = 0;
        }
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x59, g | 0x200);
        }
        *pb = 0x59;
      }
      if (*w & 8) {
        (p->s).mode[2]++;
      }
      StepPaletteAnimation(*pb);
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      PlaySound(0xE6);
      createLaserSign2(&p->s);
      (p->s).work[2] = 0x3C;
      {
        u8* pb = (u8*)p + 0xb8;
        if (*pb != 0) {
          RemovePaletteAnimation(*pb);
          *pb = 0;
        }
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x54, g | 0x200);
        }
        *pb = 0x54;
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3: {
      s32 t = (p->s).work[2];
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 1;
      }
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x08051CDC
void FUN_08051cdc(struct Boss* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8* pb asm("r6");
      ((p->s).spr).xflip = m;
      {
        u8* oa = (u8*)&((p->s).spr).oam + 6;
        s32 ov = *oa;
        s32 m11 = -0x11;
        asm("" : "+r"(m11));
        *oa = m11 & ov;
      }
      (p->s).flags &= 0xEF;
      SetMotion(&p->s, MOTION(0x4D, 0x01));
      pb = (u8*)p + 0xb8;
      if (*pb != 0) {
        RemovePaletteAnimation(*pb);
        *pb = m;
      }
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0x54, g | 0x200);
      }
      *pb = 0x54;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[2]++;
      }
      paquam_080512f8(p);
      StepPaletteAnimation(*(u8*)((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      (p->s).mode[2] = 3;
      FALLTHROUGH;
    case 3: {
      register s32 av asm("r0");
      register s32 one asm("r2");
      register s32 t asm("r1");
      av = gStageRun.vm.active;
      one = 1;
      asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one));
      t &= av;
      if (t == 0) {
        (p->s).mode[1] = t;
        (p->s).mode[2] = one;
        (p->s).work[2] = 0x46;
      }
      paquam_080512f8(p);
      StepPaletteAnimation(*(u8*)((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void createSweepLaserSign(struct Entity* e);

// 0x08051dbc -- pantheon aqua mod: sweep-laser attack (sign, palette anims
// 0x58/0x59/0x54, then the wind-down timer).  Blocker (CSE-placement basin):
// the whole 388-byte body is byte-identical to retail EXCEPT the position of
// the hoisted `p + 0xb8` pointer pair.  Retail emits `adds r5, r4, #0 / adds
// r5, #0xb8` as the LAST two instructions of the dispatch block, immediately
// before `mov pc, r0` -- the signature of a global-CSE insertion at the end of
// the dominator block.  Writing it as an explicit statement before the switch
// always lands it between the mode load and the `cmp` (18 bytes differ, no
// size change); letting agbcc CSE it out of the per-case assignments does
// place it correctly but allocates a second pseudo and copies it into pb at
// every use, which grows the function and overflows the ROM.
NON_MATCH void paquamSweepLaser(struct Boss* p) {
#if MODERN

  register u8* pb asm("r5");
  register s32 md asm("r0");
  md = (p->s).mode[2];
  pb = (u8*)p + 0xb8;
  switch (md) {
    case 0: {
      PlaySound(0xE5);
      {
        s32* w = (s32*)((u8*)p + 0xb4);
        register s32 v asm("r0");
        register s32 msk asm("r1");
        v = *w;
        msk = -5;
        v &= msk;
        msk -= 4;
        v &= msk;
        msk -= 8;
        v &= msk;
        *w = v;
      }
      createLaserSign(&p->s, (p->s).coord.x, (p->s).coord.y);
      {
        register u8* t asm("r0");
        u8 v0;
        t = (u8*)p + 0xb8;
        asm("" : "+r"(t));
        v0 = *t;
        pb = t;
        asm("" : "+r"(pb));
        if (v0 != 0) {
          RemovePaletteAnimation(*pb);
          *pb = 0;
        }
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x58, g | 0x200);
        }
        *pb = 0x58;
      }
      SetMotion(&p->s, 0x4D01);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      register s32* w1 asm("r0");
      register s32* w asm("r6");
      register s32 v asm("r1");
      register s32 k asm("r2");
      w1 = (s32*)((u8*)p + 0xb4);
      v = *w1;
      k = 4;
      v &= k;
      w = w1;
      asm("" : "+r"(w1));
      if (v != 0) {
        if (*pb != 0) {
          RemovePaletteAnimation(*pb);
          *pb = 0;
        }
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x59, g | 0x200);
        }
        *pb = 0x59;
      }
      if (*w & 8) {
        (p->s).mode[2]++;
      }
      StepPaletteAnimation(*pb);
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      PlaySound(0xE6);
      {
        register u8* t asm("r0");
        u8 v0;
        t = (u8*)p + 0xb8;
        asm("" : "+r"(t));
        v0 = *t;
        pb = t;
        asm("" : "+r"(pb));
        if (v0 != 0) {
          RemovePaletteAnimation(*pb);
          *pb = 0;
        }
        {
          u32 g0 = GetEntityPalID(&p->s);
          u32 g = (u8)g0 << 5;
          StartPaletteAnimation(0x54, g | 0x200);
        }
        *pb = 0x54;
      }
      createSweepLaserSign(&p->s);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3:
      if (*(s32*)((u8*)p + 0xb4) & 0x10) {
        (p->s).mode[2]++;
      }
      StepPaletteAnimation(*pb);
      UpdateMotionGraphic(&p->s);
      break;
    case 4:
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      // fallthrough
    case 5: {
      s32 t = (p->s).work[2];
      u32 u;
      t -= 1;
      (p->s).work[2] = t;
      u = (u8)t;
      if (u == 0) {
        (p->s).mode[1] = u;
        (p->s).mode[2] = 1;
        (p->s).work[2] = 0x46;
      }
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/boss/paquam_sweep_laser.inc");
#endif
}



void FUN_08080858(struct Entity* e);
void createStretchedGrabArm(struct Entity* e, u8 n);

// 0x08051F44
void paquam_08051f44(struct Boss* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      PlaySound(0xE4);
      {
        register s32* w asm("r2");
        register s32 v asm("r0");
        register s32 msk asm("r1");
        w = (s32*)((u8*)p + 0xb4);
        v = *w;
        msk = 0x20;
        v |= msk;
        msk -= 0x61;
        v &= msk;
        *w = v;
      }
      if ((pZero2->s).coord.x < (p->s).coord.x) {
        SetDDP(&p->body, (const struct Collision*)0x083637E4);
        (p->s).work[3] = m;
        SetMotion(&p->s, 0x4D02);
      } else {
        SetDDP(&p->body, (const struct Collision*)0x0836385C);
        (p->s).work[3] = 1;
        SetMotion(&p->s, 0x4D07);
      }
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t = (p->s).work[2];
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      if ((p->s).work[3] == 0) {
        register s32* w asm("r2");
        w = (s32*)((u8*)p + 0xb4);
        *w |= 0x80;
        SetDDP(&p->body, (const struct Collision*)0x08363724);
        SetMotion(&p->s, 0x4D03);
      } else {
        register s32* w asm("r2");
        SetDDP(&p->body, (const struct Collision*)0x08363784);
        w = (s32*)((u8*)p + 0xb4);
        *w |= 0x80 << 1;
        SetMotion(&p->s, 0x4D08);
      }
      createStretchedGrabArm(&p->s, (p->s).work[3]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      register s32* w asm("r6");
      w = (s32*)((u8*)p + 0xb4);
      {
        register s32 v asm("r1");
        v = *w;
        if ((v & 0x40) != 0) {
          register s32 msk asm("r0");
          msk = 0x41;
          msk = -msk;
          v &= msk;
          *w = v;
          FUN_08080858(&p->s);
        }
      }
      {
        register s32 v2 asm("r5");
        v2 = *w;
        v2 &= 0xc0 << 1;
        if (v2 == 0) {
          register s32 msk2 asm("r1");
          register s32 vv asm("r0");
          SetMotion(&p->s, 0x4D01);
          vv = *w;
          msk2 = 0x21;
          msk2 = -msk2;
          vv &= msk2;
          *w = vv;
          (p->s).mode[1] = v2;
          (p->s).mode[2] = 1;
          (p->s).work[2] = 0x46;
        }
      }
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void createStretchedArms(struct Boss* p);
void createPAquaModRubble(s32 x);

// 0x080520B8
void paquqmRubble(struct Boss* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register s32* w asm("r2");
      PlaySound(0xE3);
      SetDDP(&p->body, (const struct Collision*)0x083636DC);
      (p->s).unk_coord.x = (p->s).coord.x;
      w = (s32*)((u8*)p + 0xb4);
      {
        register s32 v asm("r0");
        register s32 k asm("r1");
        v = *w;
        k = 0xFFFFFDFF;
        v &= k;
        k = 0xFFFFFBFF;
        v &= k;
        k = 0x80;
        v |= k;
        k += 0x80;
        v |= k;
        *w = v;
      }
      SetMotion(&p->s, 0x4D0E);
      createStretchedArms(p);
      asm volatile("strb %0, [%1, #0x12]" :: "l"(m), "l"(p) : "memory");
      asm volatile("strb %0, [%1, #0x13]" :: "l"(m), "l"(p) : "memory");
      (p->s).unk_coord.y = m;
      (p->s).d.x = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32* w2;
      w2 = (s32*)((u8*)p + 0xb4);
      if ((*w2 & (0x80 << 2)) == 0) {
        goto tail1;
      }
      if ((p->s).unk_coord.y == 0) {
        PlaySound(0x10D);
        (p->s).unk_coord.y = 1;
      }
      if ((p->s).d.x % 0x38 == 0) {
        register u32* rp asm("r2");
        register u32 raw asm("r0");
        rp = &RNG_0202f388;
        {
          register u32 st asm("r1");
          st = *rp;
          raw = st * 0x343FD;
          raw += 0x269EC3;
          raw <<= 1;
          *rp = raw >> 1;
        }
        raw >>= 0x11;
        raw &= 3;
        {
          register s32 o asm("r1");
          register s32 k2 asm("r2");
          o = raw << 1;
          o += raw;
          o <<= 0xc;
          k2 = 0xFFFFB800;
          o += k2;
          createPAquaModRubble((p->s).coord.x + o);
        }
      }
      (p->s).d.x = (p->s).d.x + 1;
      AppendQuake(3, &(p->s).coord);
      {
        register s32 t asm("r0");
        t = (p->s).work[2] + 8;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          goto upd;
        }
      }
      {
        register s32 t2 asm("r0");
        t2 = (p->s).work[3] + 1;
        (p->s).work[3] = t2;
        if ((u32)(t2 << 24) >> 24 <= 6) {
          goto upd;
        }
      }
      StopSound(0x10D);
      *w2 |= 0x80 << 3;
      (p->s).mode[2]++;
    upd:
      {
        register s32 bx asm("r1");
        register const s16* tb asm("r2");
        bx = (p->s).unk_coord.x;
        (p->s).coord.x = bx;
        asm volatile("" ::: "memory");
        tb = gSineTable;
        {
          register s32 o2 asm("r0");
          o2 = (p->s).work[2] << 1;
          o2 += (s32)tb;
          {
            register s32 z asm("r2");
            register s32 v2 asm("r0");
            z = 0;
            v2 = *(const s16*)(o2 + z);
            v2 <<= 3;
            bx += v2;
            (p->s).coord.x = bx;
          }
        }
      }
    tail1:
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      return;
    }
    case 2: {
      register s32 v3 asm("r5");
      {
        register s32* w3 asm("r0");
        w3 = (s32*)((u8*)p + 0xb4);
        v3 = *w3;
      }
      v3 &= 0xc0 << 1;
      if (v3 == 0) {
        SetMotion(&p->s, 0x4D01);
        (p->s).mode[1] = v3;
        (p->s).mode[2] = 1;
        (p->s).work[2] = 0x46;
      }
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

struct Entity* FUN_080a5bb4(s32 x, s32 y);
void FUN_080c0340(struct Boss* p);

// 0x08052240
void paqua_mod_08052240(struct Boss* p) {
  register s32 md asm("r0");
  md = (p->s).mode[2];
  switch (md) {
    case 0: {
      register s32* w asm("r2");
      register s32 v asm("r0");
      register s32 k asm("r1");
      SetDDP(&p->body, (const struct Collision*)0x083638D4);
      w = (s32*)((u8*)p + 0xb4);
      v = *w;
      k = 0x80 << 4;
      v |= k;
      *w = v;
      SetMotion(&p->s, 0x4D0F);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      PlaySound(0xE5);
      (p->s).work[2] = 0x28;
      FUN_080c0340(p);
      if (*((u8*)p + 0xb8) != 0) {
        RemovePaletteAnimation(*((u8*)p + 0xb8));
        *((u8*)p + 0xb8) = 0;
      }
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0x58, g | 0x200);
      }
      *((u8*)p + 0xb8) = 0x58;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
      if ((u8)--(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      break;
    case 4: {
      register s32* w asm("r2");
      register s32 v asm("r0");
      register s32 k asm("r1");
      PlaySound(0x2C);
      FUN_080a5bb4((p->s).coord.x, (p->s).coord.y);
      w = (s32*)((u8*)p + 0xb4);
      v = *w;
      k = ~0x800;
      v &= k;
      *w = v;
      if (*((u8*)p + 0xb8) != 0) {
        RemovePaletteAnimation(*((u8*)p + 0xb8));
        *((u8*)p + 0xb8) = 0;
      }
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0x59, g | 0x200);
      }
      *((u8*)p + 0xb8) = 0x59;
      SetMotion(&p->s, 0x4D11);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5:
      StepPaletteAnimation(*((u8*)p + 0xb8));
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) == 3) {
        register s32 z asm("r0");
        z = 0;
        (p->s).mode[1] = z;
        (p->s).mode[2] = z;
      }
      break;
  }
}

INCASM("asm/boss/pantheon_aqua_mod_p2b2.inc");



void nop_08051620(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[9] = {
    nop_08051620,
    nop_08051620,
    nop_08051620,
    nop_08051620,
    nop_08051620,
    nop_08051620,
    nop_08051620,
    nop_08051620,
    nop_08051620,
};
// clang-format on

void paquamNeutral(struct Boss* p);
void paquam_080517ac(struct Boss* p);
void paquam_080519d0(struct Boss* p);
void paquam_08051b8c(struct Boss* p);
void FUN_08051cdc(struct Boss* p);
void paquamSweepLaser(struct Boss* p);
void paquam_08051f44(struct Boss* p);
void paquqmRubble(struct Boss* p);
void paqua_mod_08052240(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[9] = {
    paquamNeutral,
    paquam_080517ac,
    paquam_080519d0,
    paquam_08051b8c,
    FUN_08051cdc,
    paquamSweepLaser,
    paquam_08051f44,
    paquqmRubble,
    paqua_mod_08052240,
};
// clang-format on

// --------------------------------------------

void FUN_080523b8(struct Boss* p);

static const BossFunc sDeads[1] = {
    FUN_080523b8,
};

// --------------------------------------------

// 0x0836364c
static const struct Collision sCollisions[32] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(45), PIXEL(15)},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(35)},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(27), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(27), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [5] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(12), PIXEL(12)},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(45), PIXEL(15)},
    },
    [7] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(35)},
    },
    [8] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(12), PIXEL(12)},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(45), PIXEL(15)},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(35)},
    },
    [11] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      nature : 0x04,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(27), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [12] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(12), PIXEL(12)},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(45), PIXEL(15)},
    },
    [14] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(35)},
    },
    [15] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(27), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [16] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(12), PIXEL(12)},
    },
    [17] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(45), PIXEL(15)},
    },
    [18] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(35)},
    },
    [19] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      nature : 0x04,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(30), -PIXEL(15), PIXEL(18), PIXEL(18)},
    },
    [20] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      nature : 0x04,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(27), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [21] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(12), PIXEL(12)},
    },
    [22] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(45), PIXEL(15)},
    },
    [23] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(35)},
    },
    [24] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(27), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [25] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(30), -PIXEL(15), PIXEL(18), PIXEL(18)},
    },
    [26] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(12), PIXEL(12)},
    },
    [27] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(45), PIXEL(15)},
    },
    [28] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(35)},
    },
    [29] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {-PIXEL(10), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [30] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(10), PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    [31] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(12), PIXEL(12)},
    },
};

// --------------------------------------------

static const u8 sInitModes[4] = {1, 4, 0, 0};
static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
static const u8 u8_ARRAY_08363958[4] = {5, 6, 7, 8};
