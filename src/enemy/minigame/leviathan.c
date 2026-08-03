#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "trig.h"
#include "text.h"
#include "minigame.h"

static const EnemyFunc sDeads[4];

#include "entity/macros.h"

void FUN_08099f54(s32 x, s32 y, s32 a, s32 b) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 68);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 6;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_coord.y = a;
    (p->s).d.x = b;
  }
}

void FUN_08099fb8(struct Entity* e, s32 y, u8 n, u8 w) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 68);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = w;
    (p->s).coord.x = n * 0x13000 + 0xD000;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    (p->s).unk_28 = e;
  }
}

// 0x0809a02c
struct Enemy* FUN_0809a02c(void* parent, u8 n) {
  struct Enemy* e = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (e != NULL) {
    s32 x;
    s32 y;
    (e->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(e, 68);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).work[0] = 4;
    x = 0x16800;
    (e->s).coord.x = x;
    y = 0x41000;
    (e->s).coord.y = y;
    (e->s).coord.y = FUN_08009f6c(x, y);
    y = (e->s).coord.x;
    y -= 0x9800;
    y += n * 0x13000;
    (e->s).coord.x = y;
    (e->s).work[2] = n;
    (e->s).unk_28 = parent;
  }
  return e;
}

void nop_0809a0b4(struct Enemy* p) {}

static const struct Collision sCollisions[6];
static const u8 u8_ARRAY_0836a764[6];
static const u8 u8_ARRAY_0836a76a[8];
static const motion_t sMotions[12];
static const EnemyFunc sUpdates1[7];
static const EnemyFunc sUpdates2[7];

void LeviathanMinigameEnemy_Die(struct Enemy* p);
void LeviathanMinigameEnemy_Update(struct Enemy* p);

bool8 FUN_0809a0b8(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    *(u8*)((u8*)(p->s).unk_28 + 0x31) = 10;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = u8_ARRAY_0836a764[(p->s).work[0]];
    LeviathanMinigameEnemy_Die(p);
    return TRUE;
  }
  return FALSE;
}

void LeviathanMinigameEnemy_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836a76a[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] != 6) {
    SetMotion(&p->s, sMotions[(p->s).work[0]]);
  }
  UpdateMotionGraphic(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_0809a0b4);
  LeviathanMinigameEnemy_Update(p);
}

void LeviathanMinigameEnemy_Update(struct Enemy* p) {
  if (!FUN_0809a0b8(p)) {
    sUpdates1[(p->s).mode[1]](p);
    sUpdates2[(p->s).mode[1]](p);
  }
}

void LeviathanMinigameEnemy_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0809a1ec(struct Enemy* p) {}

// 0x0809A1F0
void FUN_0809a1f0(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  if (*((u8*)q + 0x31) != 0) {
    SetDDP(&p->body, (const struct Collision*)0x0836A6D4);
    return;
  }
  SetDDP(&p->body, (const struct Collision*)0x0836A6EC);
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 xf asm("r4");
      register s32 zero asm("r3");
      s32 w;
      {
        u8* pp = (u8*)p + 0x22;
        xf = 1;
        *pp = 1;
      }
      SetMotion(&p->s, MOTION(0x18, 0x00));
      xf ^= (p->s).work[2];
      if (xf != 0) {
        register u8 fv asm("r0");
        register s32 k10 asm("r1");
        fv = (p->s).flags;
        k10 = 0x10;
        fv |= k10;
        (p->s).flags = fv;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        register s32 v asm("r1");
        register u8* oa asm("r4");
        u8* xp;
        s32 sh4, ov, m11;
        v = 1;
        v &= xf;
        xp = (u8*)p + 0x4c;
        zero = 0;
        *xp = v;
        oa = (u8*)p + 0x4a;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      {
        register s32 k asm("r2");
        k = 0xB0 * 2;
        w = (p->s).work[2];
        k -= ((w * 3 * 4) - w) << 6;
        (p->s).d.x = k;
      }
      (p->s).work[3] = zero;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 zero2 asm("r4");
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += gSineTable[(p->s).work[3]] / 2;
      {
        s32 t = (p->s).work[3] + 4;
        zero2 = 0;
        (p->s).work[3] = t;
      }
      UpdateMotionGraphic(&p->s);
      if ((u32)((p->s).coord.x + -0xD000) > 0x98 * 512) {
        u8* a;
        *(u32*)((u8*)q + 0x1c) = zero2;
        *((u8*)q + 0x32) = zero2;
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        a = (u8*)p + 0x8c;
        *(u32*)a = zero2;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = zero2;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = zero2;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

INCASM("asm/enemy/minigame_leviathan_p3.inc");

void FUN_0809a4bc(struct Enemy* p) {
  if (*((u8*)(p->s).unk_28 + 0x31) != 0) {
    SetDDP(&p->body, sCollisions);
    return;
  }
  SetDDP(&p->body, &sCollisions[3]);
  switch ((p->s).mode[2]) {
    case 0: {
      s32 on2;
      SetMotion(&p->s, MOTION(0xF0, 0x00));
      on2 = (p->s).work[2] ^ 1;
      if (on2) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        register s32 m1 asm("r1");
        m1 = 1;
        m1 &= on2;
        ((p->s).spr).xflip = m1;
        {
          u8* a = (u8*)p + 0x4a;
          register s32 sh asm("r1");
          register u8 b2 asm("r2");
          s32 msk;
          sh = m1 << 4;
          b2 = *a;
          msk = -0x11;
          msk &= b2;
          msk |= sh;
          *a = msk;
        }
      }
      {
        register s32 e0 asm("r2");
        e0 = 0x160;
        asm("" : "+r"(e0));
        e0 -= (p->s).work[2] * 0x2C0;
        (p->s).d.x = e0;
      }
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += gSineTable[(p->s).work[3]] / 2;
      (p->s).work[3] += 3;
      UpdateMotionGraphic(&p->s);
      if ((u32)((p->s).coord.x - 0xD000) > 0x13000) {
        register u8 f1 asm("r1");
        register s32 f2 asm("r0");
        f1 = (p->s).flags;
        f2 = 0xFE;
        f2 &= f1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f2 &= c2;
        }
        (p->s).flags = f2;
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

void FUN_0809a5e0(struct Enemy* p) {
  if (*((u8*)(p->s).unk_28 + 0x31) != 0) {
    SetDDP(&p->body, sCollisions);
    return;
  }
  SetDDP(&p->body, &sCollisions[4]);
  switch ((p->s).mode[2]) {
    case 0: {
      s32 on2;
      SetMotion(&p->s, MOTION(0xEF, 0x00));
      on2 = (p->s).work[2] ^ 1;
      if (on2) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        register s32 m1 asm("r1");
        m1 = 1;
        m1 &= on2;
        ((p->s).spr).xflip = m1;
        {
          u8* a = (u8*)p + 0x4a;
          register s32 sh asm("r1");
          register u8 b2 asm("r2");
          s32 msk;
          sh = m1 << 4;
          b2 = *a;
          msk = -0x11;
          msk &= b2;
          msk |= sh;
          *a = msk;
        }
      }
      {
        register s32 e0 asm("r2");
        e0 = 0xE0;
        asm("" : "+r"(e0));
        e0 -= (p->s).work[2] * 448;
        (p->s).d.x = e0;
      }
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += gSineTable[(p->s).work[3]] / 4;
      (p->s).work[3] += 3;
      UpdateMotionGraphic(&p->s);
      if ((u32)((p->s).coord.x - 0xD000) > 0x13000) {
        register u8 f1 asm("r1");
        register s32 f2 asm("r0");
        f1 = (p->s).flags;
        f2 = 0xFE;
        f2 &= f1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f2 &= c2;
        }
        (p->s).flags = f2;
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

INCASM("asm/enemy/minigame_leviathan_p3_c.inc");

void FUN_0809a90c(struct Enemy* p) {
  if (*(u8*)((u8*)(p->s).unk_28 + 0x31) == 0) {
    switch ((p->s).mode[2]) {
      case 0: {
        s32 amp, on;
        (p->s).taskCol = 0x19;
        amp = -0x80;
        amp -= RANDOM(RNG_0202f388) & 0x7F;
        (p->s).d.x = amp * (1 - (((p->s).work[2] ^ 1) * 2));
        on = 0;
        if ((p->s).d.x > 0) {
          on = 1;
        }
        SET_XFLIP(p, on);
        SetMotion(&p->s, MOTION(0xF2, 0x00));
        (p->s).mode[2]++;
      }
        /* fallthrough */
      case 1:
        (p->s).coord.x += (p->s).d.x;
        if ((u32)((p->s).coord.x - PIXEL(0xD0)) > 0x13000) {
          u8 f = ~DISPLAY & (p->s).flags;
          s32 z = 0;
          f &= ~FLIPABLE;
          (p->s).flags = f;
          (p->body).status = z;
          (p->body).prevStatus = z;
          (p->body).invincibleTime = z;
          (p->s).flags &= ~COLLIDABLE;
          SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        }
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

extern const u8 StrMISS[];
extern const u8 StrSEC[];

// One register from a match: retail truncates the row argument in place
// (lsls/lsrs on the variable's register plus a copy to r2) where agbcc
// shifts directly into the argument register in every spelling tried.
NON_MATCH void FUN_0809aa10(struct Sprite* spr, struct DrawPivot* pivot) {
#if MODERN
  struct Entity* e = (struct Entity*)spr->sprites;
  s32 x = (e->coord.x - pivot->lefttop.x) >> 8;
  s32 y = (e->coord.y - pivot->lefttop.y) >> 8;
  x -= 0x10;
  x /= 8;
  if (x < 0) {
    x = 0;
  } else if (x + 4 > 0x1E) {
    x = 0x1A;
  }
  y += 0x10;
  y /= 8;
  if (y <= 0) {
    y = 1;
  } else if (y > 0x11) {
    y = 0x11;
  }
  PrintUnicodeString((const char_t*)StrMISS, x, y);
  PrintUnicodeString((const char_t*)StrSEC, x + 2, ++y);
  PrintMinigameNumber(e->d.x, (u16)x, (u16)y);
#else
  INCCODE("asm/enemy/leviathan_aa10.inc");
#endif
}

INCASM("asm/enemy/minigame_leviathan_p3b.inc");

extern const u8 StrCOMBO[];
extern const u8 StrPlusSEC[];

// 0x0809aa90 -- parked (same trunc-reg basin as FUN_0809aa10 above):
// retail truncates the final row argument in place then copies to r2;
// agbcc truncates into r2 directly in every spelling and pin tried.
NON_MATCH void FUN_0809aa90(struct Sprite* spr, struct DrawPivot* pivot) {
#if MODERN
  struct Entity* e = (struct Entity*)spr->sprites;
  s32 x = (e->coord.x - pivot->lefttop.x) >> 8;
  s32 y = (e->coord.y - pivot->lefttop.y) >> 8;
  x -= 0x10;
  x /= 8;
  {
    u8 lim = e->work[3];
    if (x - lim + 1 < 0) {
      x = lim - 1;
    } else if (x + 7 > 0x1E) {
      x = 0x17;
    }
  }
  y += 0x10;
  y /= 8;
  if (y <= 0) {
    y = 1;
  } else if (y > 0x11) {
    y = 0x11;
  }
  if (e->unk_coord.y > 1) {
    PrintMinigameNumber(e->unk_coord.y, (u16)x, (u16)y);
    PrintUnicodeString((const char_t*)StrCOMBO, x + 2, y);
  }
  PrintUnicodeString((const char_t*)StrPlusSEC, x, ++y);
  PrintMinigameNumber(e->d.x, (u16)(x + 1), (u16)y);
#else
  INCCODE("asm/enemy/leviathan_aa90.inc");
#endif
}

void FUN_0809aa10(struct Sprite* spr, struct DrawPivot* pivot);

// 0x0809ab28
void FUN_0809ab28(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      if ((p->s).unk_coord.y == -1) {
        SetTaskCallback((struct RenderNode*)&(p->s).spr, FUN_0809aa10);
        (p->s).spr.sprites = (struct MetaspriteHeader*)p;
        (p->s).flags &= ~8;
      } else {
        s32 v;
        SetTaskCallback((struct RenderNode*)&(p->s).spr, FUN_0809aa90);
        (p->s).spr.sprites = (struct MetaspriteHeader*)p;
        (p->s).flags &= ~8;
        (p->s).work[3] = m;
        v = (p->s).unk_coord.y;
        while (v != 0) {
          v = v / 10;
          (p->s).work[3]++;
        }
      }
      (p->s).unk_coord.x = 0x1E;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if (--(p->s).unk_coord.x != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 2:
      (p->s).unk_coord.x = 0x18;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      s32 c = --(p->s).unk_coord.x;
      if (c & 1) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
      if ((p->s).unk_coord.x == 0) {
        u8 f = ~DISPLAY & (p->s).flags;
        f = f & ~FLIPABLE;
        (p->s).flags = f;
        (p->body).status = 0;
        (p->body).prevStatus = 0;
        (p->body).invincibleTime = 0;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

#include "vfx.h"

void FUN_080b822c(struct Enemy* p, struct Coord* c, motion_t* motions, u8 len, u8 r4);
static const motion_t sMotions[12];

// 0x0809AC28
void FUN_0809ac28(struct Enemy* p) {
  struct Coord c;
  u8* q = (u8*)(p->s).unk_28;
  if (*(q + 0x34) == 0) {
    u8* n;
    s32 k;
    *(s32*)(q + 0x20) += 0x3C;
    n = q + 0x35;
    (*n)++;
    *(s32*)(q + 0x1c) += 1;
    (*(q + 0x32))++;
    FUN_08099f54((p->s).coord.x, (p->s).coord.y, *(s32*)(q + 0x1c), 1);
    k = *(s32*)(q + 0x1c);
    k += 1;
    if (k > 4) {
      k = 4;
    }
    *(s32*)(q + 0x24) += *n * k;
  }
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    u8* qq = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(qq));
    z = 0;
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *qq = z;
    t = (p->s).flags;
    f = 0xFB;
    f &= t;
    (p->s).flags = f;
    asm volatile("" ::"r"(t));
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  CreateSmoke(1, &c);
  PlaySound(0x31);
  FUN_080b822c(p, &c, (motion_t*)&sMotions[6], 3, 1);
  SET_ENEMY_ROUTINE(p, 4);
}

// 0x0809acdc
void FUN_0809acdc(struct Enemy* p) {
  struct Coord c;
  u8* q = (u8*)(p->s).unk_28;
  if (*(q + 0x34) == 0) {
    u8* n;
    *(s32*)(q + 0x20) += 0x12C;
    n = q + 0x35;
    (*n)++;
    *(s32*)(q + 0x1c) += 1;
    (*(q + 0x32))++;
    FUN_08099f54((p->s).coord.x, (p->s).coord.y, *(s32*)(q + 0x1c), 5);
    *(s32*)(q + 0x24) += *n * 5;
  }
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    u8* qq = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(qq));
    z = 0;
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *qq = z;
    t = (p->s).flags;
    f = 0xFB;
    f &= t;
    (p->s).flags = f;
    asm volatile("" ::"r"(t));
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  CreateSmoke(1, &c);
  PlaySound(0x31);
  FUN_080b822c(p, &c, (motion_t*)&sMotions[9], 3, 1);
  SET_ENEMY_ROUTINE(p, 4);
}

// 0x0809AD8C
void FUN_0809ad8c(struct Enemy* p) {
  u8* q = (u8*)(p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      s32 z = 0;
      if (*(q + 0x34) == 0) {
        u8* a = q + 0x35;
        *a = z;
        *(s32*)(q + 0x1c) = z;
        a -= 3;
        *a = z;
        FUN_08099f54((p->s).coord.x, (p->s).coord.y, -1, -5);
        *(s32*)(q + 0x20) += -0x12C;
      }
      {
        register u8 f asm("r0");
        register u8 t asm("r1");
        u8* qq = (u8*)p + 0x8c;
        asm("" : "+r"(qq));
        *(s32*)qq = z;
        asm("" : "+r"(qq));
        qq += 4;
        asm("" : "+r"(qq));
        *(s32*)qq = z;
        asm("" : "+r"(qq));
        qq += 4;
        asm("" : "+r"(qq));
        *qq = z;
        t = (p->s).flags;
        asm("" : "+r"(t));
        f = 0xFB;
        f &= t;
        (p->s).flags = f;
      }
      (p->s).d.y = z;
      (p->s).work[2] = 0x18;
      (p->s).work[3] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register u8 v asm("r0");
      register s32 one asm("r1");
      s32 t2 = (p->s).work[3] + 1;
      (p->s).work[3] = t2;
      one = 1;
      if ((t2 & one) != 0) {
        v = (p->s).flags;
        v |= one;
      } else {
        register u8 fl asm("r1");
        fl = (p->s).flags;
        asm("" : "+r"(fl));
        v = 0xFE;
        v &= fl;
      }
      (p->s).flags = v;
      if (*(q + 0x31) != 0) {
        break;
      }
      if (--(p->s).work[2] == 0) {
        SET_ENEMY_ROUTINE(p, 4);
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.x = (p->s).d.x * 248 / 256;
      (p->s).coord.y += (p->s).d.y;
      (p->s).d.y += 0x10;
      break;
    }
  }
}

// 0x0809AE68
void FUN_0809ae68(struct Enemy* p) {
  u8* q = (u8*)(p->s).unk_28;
  s32 z;
  switch ((p->s).mode[2]) {
    case 0:
      z = 0;
      if (*(q + 0x34) == 0) {
        u8* n = q + 0x35;
        *n = z;
        *(s32*)(q + 0x1c) = z;
        *(n - 3) = z;
        FUN_08099f54((p->s).coord.x, (p->s).coord.y, -1, -5);
        *(s32*)(q + 0x20) += -0x12C;
      }
      *(u32*)((u8*)p + 0x8c) = z;
      *(u32*)((u8*)p + 0x90) = z;
      *(u8*)((u8*)p + 0x94) = z;
      (p->s).flags &= ~COLLIDABLE;
      (p->s).work[2] = 0x18;
      (p->s).work[3] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 w3 = (p->s).work[3] + 1;
      u32 one;
      (p->s).work[3] = w3;
      one = 1;
      if ((w3 & one) != 0) {
        (p->s).flags |= one;
      } else {
        (p->s).flags &= 0xFE;
      }
      if (*(q + 0x31) == 0) {
        if ((u8)--(p->s).work[2] == 0) {
          SET_ENEMY_ROUTINE(p, 4);
        }
      }
      break;
    }
  }
}

void LeviathanMinigameEnemy_Init(struct Enemy* p);
void LeviathanMinigameEnemy_Update(struct Enemy* p);
void LeviathanMinigameEnemy_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gLeviathanMinigameEnemyRoutine = {
    [ENTITY_INIT] =      LeviathanMinigameEnemy_Init,
    [ENTITY_UPDATE] =    LeviathanMinigameEnemy_Update,
    [ENTITY_DIE] =       LeviathanMinigameEnemy_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void nop_0809a1ec(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
};
// clang-format on

void FUN_0809a1f0(struct Enemy* p);
void FUN_0809a31c(struct Enemy* p);
void FUN_0809a4bc(struct Enemy* p);
void FUN_0809a5e0(struct Enemy* p);
void FUN_0809a700(struct Enemy* p);
void FUN_0809a90c(struct Enemy* p);
void FUN_0809ab28(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    FUN_0809a1f0,
    FUN_0809a31c,
    FUN_0809a4bc,
    FUN_0809a5e0,
    FUN_0809a700,
    FUN_0809a90c,
    FUN_0809ab28,
};
// clang-format on

// --------------------------------------------

void FUN_0809ac28(struct Enemy* p);
void FUN_0809acdc(struct Enemy* p);
void FUN_0809ad8c(struct Enemy* p);
void FUN_0809ae68(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_0809ac28,
    FUN_0809acdc,
    FUN_0809ad8c,
    FUN_0809ae68,
};

// --------------------------------------------

static const struct Collision sCollisions[6] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(6), PIXEL(1), PIXEL(20), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(12), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(4), PIXEL(1), PIXEL(33), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(11), PIXEL(11)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(2), -PIXEL(2), PIXEL(18), PIXEL(16)},
    },
};

static const u8 u8_ARRAY_0836a764[6] = {
    0, 1, 2, 2, 3, 3,
};

static const u8 u8_ARRAY_0836a76a[8] = {
    0, 1, 2, 3, 4, 5, 6, 0,
};

// clang-format off
static const motion_t sMotions[12] = {
    MOTION(SM024_SHARKSEAL_X, 0),
    MOTION(SM053_SHELLUNO, 1),
    MOTION(SM240_SEA_BREAM, 0),
    MOTION(SM239_ANGEL_FISH, 0),
    MOTION(SM241_CRAB, 1),
    MOTION(SM242_FISH_SCHOOL, 0),
    MOTION(SM024_SHARKSEAL_X, 4),
    MOTION(SM024_SHARKSEAL_X, 5),
    MOTION(SM024_SHARKSEAL_X, 5),
    MOTION(SM053_SHELLUNO, 6),
    MOTION(SM053_SHELLUNO, 7),
    MOTION(SM053_SHELLUNO, 8),
};


