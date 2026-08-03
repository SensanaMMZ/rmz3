#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"
#include "palette_animation.h"

void createPAquaModRubble(s32 x) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA_MOD_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 8;
    (p->s).coord.x = x;
  }
}

void FUN_08080858(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA_MOD_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 6;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y;
    (p->s).unk_28 = e;
  }
}

void FUN_080808b4(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA_MOD_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 3;
    (p->s).unk_28 = e;
  }
}

void FUN_08080908(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA_MOD_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y;
    (p->s).unk_28 = e;
  }
}

void FUN_08080964(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA_MOD_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y;
    (p->s).unk_28 = e;
  }
}

void createLaserSign2(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA_MOD_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).work[1] = 1;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y - PIXEL(12);
    (p->s).unk_28 = e;
  }
}

void createSweepLaserSign(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA_MOD_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).work[1] = 1;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y - PIXEL(12);
    (p->s).unk_28 = e;
  }
}

#include "entity/macros.h"

void createStretchedGrabArm(struct Entity* e, u8 n) {
  struct Enemy* arm = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);
  s32 i;
  s32 base;

  if (arm != NULL) {
    (arm->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(arm, 38);
    (arm->s).tileNum = 0;
    (arm->s).palID = 0;
    (arm->s).flags2 |= WHITE_PAINTABLE;
    (arm->s).invincibleID = (arm->s).uniqueID;
    (arm->s).work[0] = 5;
    (arm->s).work[1] = n;
    base = e->coord.x - 0x1700;
    (arm->s).coord.x = base + n * 0x2E00;
    (arm->s).coord.y = e->coord.y - 0x400;
    (arm->s).unk_28 = e;
  }

  for (i = 0; i <= 5; i++) {
    struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

    if (p != NULL) {
      (p->s).taskCol = 24;
      INIT_ENEMY_ROUTINE(p, 38);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = (p->s).uniqueID;
      (p->s).work[0] = 4;
      (p->s).work[1] = n;
      (p->s).unk_28 = e;
      (p->s).unk_2c = (struct Entity*)arm;
      (p->s).work[2] = i + 1;
    }
  }
}

void createStretchedArms(struct Entity* e) {
  s32 n;
  s32 i;
  s32 base;

  for (n = 0; n <= 1; n++) {
    struct Enemy* arm = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);

    if (arm != NULL) {
      (arm->s).taskCol = 24;
      INIT_ENEMY_ROUTINE(arm, 38);
      (arm->s).tileNum = 0;
      (arm->s).palID = 0;
      (arm->s).flags2 |= WHITE_PAINTABLE;
      (arm->s).invincibleID = (arm->s).uniqueID;
      (arm->s).work[0] = 7;
      (arm->s).work[1] = n;
      base = e->coord.x - 0x1700;
      (arm->s).coord.x = base + n * 0x2E00;
      (arm->s).coord.y = e->coord.y + 0x400;
      (arm->s).unk_28 = e;
    }

    for (i = 0; i <= 5; i++) {
      struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

      if (p != NULL) {
        (p->s).taskCol = 24;
        INIT_ENEMY_ROUTINE(p, 38);
        (p->s).tileNum = 0;
        (p->s).palID = 0;
        (p->s).flags2 |= WHITE_PAINTABLE;
        (p->s).invincibleID = (p->s).uniqueID;
        (p->s).work[0] = 4;
        (p->s).work[1] = n;
        (p->s).unk_28 = e;
        (p->s).unk_2c = (struct Entity*)arm;
        (p->s).work[2] = i + 1;
      }
    }
  }
}

#include "entity/macros.h"

void FUN_08080c64(s32 x, s32 y) {
  struct Enemy* e = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (e != NULL) {
    (e->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(e, 38);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).work[0] = 9;
    (e->s).coord.x = x;
    (e->s).coord.y = y;
  }
}

INCASM("asm/enemy/pantheon_aqua_mod_obj_p1_p5_x.inc");

void nop_08080eb8(struct Enemy* p) {}

static const u8 sInitModes[10];
static const struct Collision sCollisions[10];
void nop_08080eb8(struct Enemy* p);
void PantheonAquaModObj_Update(struct Enemy* p);

void PantheonAquaModObj_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  {
    register u8 f asm("r0");
    register s32 v asm("r1");
    register s32 z asm("r4");
    f = (p->s).flags;
    f |= FLIPABLE;
    v = DISPLAY;
    z = 0;
    asm volatile("" : "+r"(z));
    f |= v;
    (p->s).flags = f;
  }
  if ((p->s).work[0] != 2) {
    InitNonAffineMotion(&p->s);
    INIT_BODY(p, sCollisions, 6, (void*)nop_08080eb8);
  }
  PantheonAquaModObj_Update(p);
}

extern const EnemyFunc sUpdates1[10];
extern const EnemyFunc sUpdates2[10];
void PantheonAquaModObj_Die(struct Enemy* p);

void PantheonAquaModObj_Update(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    PantheonAquaModObj_Die(p);
  } else {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

static const motion_t sMotions[8];

void PantheonAquaModObj_Die(struct Enemy* p) {
  struct Coord c;
  *(u32*)((u8*)p + 0x8c) = 0;
  *(u32*)((u8*)p + 0x90) = 0;
  *(u8*)((u8*)p + 0x94) = 0;
  (p->s).flags &= ~COLLIDABLE;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  FUN_080b81a0(&p->s, &c, (motion_t*)sMotions, 3);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_08080fe8(struct Enemy* p) {}

INCASM("asm/enemy/pantheon_aqua_mod_obj_p3.inc");

void FUN_080c025c(s32 x, s32 y);

void FUN_08081208(struct Enemy* p) {
  struct Enemy* q = (struct Enemy*)(p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x20;
      SetMotion(&p->s, 0x5100);
      (p->s).coord.x >>= 8;
      (p->s).coord.x = ((p->s).coord.x / 0xF0) * 0xF000 + 0xB600;
      (p->s).coord.y >>= 8;
      (p->s).coord.y = ((p->s).coord.y / 0xA0) * 0xA000 + 0x3800;
      (p->s).unk_coord.y = (p->s).coord.y;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).work[2] += 2;
      (p->s).coord.y = (p->s).unk_coord.y;
      (p->s).coord.y = (p->s).unk_coord.y + gSineTable[(p->s).work[2]] * 4;
      UpdateMotionGraphic(&p->s);
      if (*((u8*)(q->s).scriptEntity + 9) & 4) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      (p->s).unk_coord.x = (p->s).coord.x + -0x5400;
      (p->s).unk_coord.y = (p->s).coord.y + -0x3000;
      (p->s).work[2] = 0x64;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      s32 t = (p->s).work[2] - 1;
      s32 dx, dy;
      (p->s).work[2] = t;
      dx = (p->s).unk_coord.x - (p->s).coord.x;
      dy = (p->s).unk_coord.y - (p->s).coord.y;
      (p->s).coord.x += (dx * 3) / 256;
      (p->s).coord.y += dy / 16;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 4:
      *(u32*)((u8*)q + 0xb4) |= 1;
      (p->s).work[2] = 0xA0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      (p->s).work[2]--;
      {
        register u32 w asm("r0") = *(volatile u8*)((u8*)p + 0x12);
        w &= 3;
        if (w == 0) {
        u32 v = (RNG_0202f388 * 0x343FD + 0x269EC3) << 1;
        s32 off;
        RNG_0202f388 = v >> 1;
        off = (v >> 0x11) % 0x1400u + -0xA00;
        FUN_080c025c((p->s).coord.x + off, (p->s).coord.y);
        }
      }
      if ((p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 6:
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 7: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 8:
      (p->s).d.y = -0x80;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 9:
      (p->s).coord.x += 0x200;
      (p->s).d.y += 4;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

INCASM("asm/enemy/pantheon_aqua_mod_obj_p3_mid.inc");

void FUN_080817a8(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  if (q->mode[0] == 4) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags &= ~DISPLAY;
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      struct Zero* z = pZero2;
      s32 qx;
      s32 qy2;
      s32 dy;
      u32 ang;
      register s32 c asm("r8");
      register s32 sn asm("r2");
      register s32 tt asm("r0");
      {
        register s32 dx asm("r3");
        register s32 zx asm("r0");
        zx = (z->s).coord.x;
        asm("" : "+r"(zx));
        qx = q->coord.x;
        dx = zx - qx;
        qy2 = q->coord.y + 0x1800;
        dy = (z->s).coord.y - qy2;
        ang = *((u8*)q + 0xb4) + *((u8*)q + 0xb5);
        ang >>= 1;
        {
          register s32 cl asm("r0");
          cl = gSineTable[(u8)(ang + 0x40)];
          c = cl;
        }
        sn = gSineTable[ang];
        tt = c;
        asm("" : "+r"(tt));
        tt *= dx;
      }
      {
        register s32 t asm("r3");
        t = tt / 256;
        t += (sn * dy) / 256;
        if (t < 0) {
          t = 0;
        }
        (p->s).coord.x = qx;
        (p->s).coord.x = qx + (t * c) / 256;
        {
          s32 qy = q->coord.y;
          (p->s).coord.y = qy;
          (p->s).coord.y = qy + (sn * t) / 256;
        }
      }
      break;
    }
  }
}

// 0x080818B8
void FUN_080818b8(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  struct Entity* r;
  if (q->mode[0] <= 1) {
    r = (p->s).unk_2c;
    if (r->mode[0] != 4) {
      goto body;
    }
  }
  {
    register u8 g asm("r0");
    register u8 h asm("r1");
    register s32 z asm("r2");
    h = (p->s).flags;
    asm("" : "+r"(h));
    g = 0xFE;
    g &= h;
    z = 0;
    h = 0xFD;
    g &= h;
    (p->s).flags = g;
    {
      u8* a = (u8*)p + 0x8c;
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
  }
  (p->s).flags &= 0xFB;
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  return;
body:
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).taskCol = 0xF;
      (p->s).flags2 |= 0x10;
      (p->s).invincibleID = q->uniqueID;
      SetMotion(&p->s, MOTION(0x4D, 0x04));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register s32 dx asm("r1");
      register s32 dy asm("r5");
      register s32 b asm("r4");
      register s32 off asm("r0");
      {
        register s32 wv asm("r1");
        wv = (p->s).work[1];
        off = wv << 2;
        off += wv;
        off <<= 11;
        wv = -0x1400;
        asm("" : "+r"(wv));
        off += wv;
      }
      dx = q->coord.x + off;
      b = r->coord.x;
      dx -= b;
      dy = q->coord.y - 0x500;
      dy -= r->coord.y;
      (p->s).coord.x = b;
      b += (dx * (p->s).work[2]) / 6;
      (p->s).coord.x = b;
      b = r->coord.y;
      (p->s).coord.y = b;
      b += (dy * (p->s).work[2]) / 6;
      (p->s).coord.y = b;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/enemy/pantheon_aqua_mod_obj_p3_b.inc");

u8 GetEntityPalID(struct Entity* p);

// 0x08081D2C
void FUN_08081d2c(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      PlaySound(0x49);
      *((u8*)p + 0x25) = 0xE;
      SetMotion(&p->s, 0x5000);
      StartPaletteAnimation(0x55, ((u32)GetEntityPalID(&p->s) << 5) | 0x200);
      (p->s).work[2] = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register s32 z asm("r5");
      register u8 w asm("r1");
      register s32 w2 asm("r2");
      register u8 f asm("r0");
      w = (p->s).work[2];
      f = 3;
      f &= w;
      asm volatile("add %0, %1, #0" : "=&l"(w2) : "l"(w));
      if (f == 0) {
        register u8 fl asm("r1");
        fl = (p->s).flags;
        asm("" : "+r"(fl));
        f = 0xFE;
        f &= fl;
      } else {
        register u8 fl2 asm("r1");
        fl2 = (p->s).flags;
        asm("" : "+r"(fl2));
        f = 1;
        f |= fl2;
      }
      (p->s).flags = f;
      {
        register s32 nw asm("r0");
        nw = w2 + 1;
        z = 0;
        (p->s).work[2] = nw;
      }
      StepPaletteAnimation(0x55);
      UpdateMotionGraphic(&p->s);
      if (*(u32*)((u8*)q + 0xb4) & 0x20) {
        if (q->mode[0] <= 1) {
          break;
        }
      }
      RemovePaletteAnimation(0x55);
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
      {
        u8* a = (u8*)p + 0x8c;
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
      (p->s).flags &= 0xFB;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
    }
  }
}

INCASM("asm/enemy/pantheon_aqua_mod_obj_p3_b2.inc");

extern void __umodsi3();
struct VFX* FUN_080ba9a0(struct Coord* c);

// 0x080820B8
void FUN_080820b8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 one asm("r2");
      (p->s).work[2] = 0;
      (p->s).taskCol = 0x1B;
      one = 1;
      (p->s).flags |= X_FLIP;
      ((p->s).spr).xflip = one;
      {
        register u8* oa asm("r3");
        register s32 sh4 asm("r2");
        s32 ov;
        s32 m11;
        oa = (u8*)p + 0x4a;
        sh4 = 0x10;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
      SetMotion(&p->s, MOTION(0x27, 0x0B));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 z asm("r5");
      s32 t;
      if ((p->s).work[2] == 0) {
        struct Coord c;
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y;
        FUN_080ba9a0(&c);
      }
      {
        s32 w = (p->s).work[2] + 1;
        z = 0;
        (p->s).work[2] = w;
      }
      t = ((s32 (*)(s32, s32))__umodsi3)((p->s).work[2], 10);
      (p->s).work[2] = t;
      (p->s).coord.x += 0x240;
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x2000) {
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
        {
          u8* a = (u8*)p + 0x8c;
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
        (p->s).flags &= 0xFB;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

void PantheonAquaModObj_Init(struct Enemy* p);
void PantheonAquaModObj_Update(struct Enemy* p);
void PantheonAquaModObj_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonAquaModObjRoutine = {
    [ENTITY_INIT] =      PantheonAquaModObj_Init,
    [ENTITY_UPDATE] =    PantheonAquaModObj_Update,
    [ENTITY_DIE] =       PantheonAquaModObj_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_08080fe8(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
    FUN_08080fe8,
};
// clang-format on

void FUN_08080fec(struct Enemy* p);
void FUN_08081208(struct Enemy* p);
void FUN_08081438(struct Enemy* p);
void FUN_080817a8(struct Enemy* p);
void FUN_080818b8(struct Enemy* p);
void FUN_08081990(struct Enemy* p);
void FUN_08081d2c(struct Enemy* p);
void FUN_08081e00(struct Enemy* p);
void FUN_08081fc4(struct Enemy* p);
void FUN_080820b8(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    FUN_08080fec,
    FUN_08081208,
    FUN_08081438,
    FUN_080817a8,
    FUN_080818b8,
    FUN_08081990,
    FUN_08081d2c,
    FUN_08081e00,
    FUN_08081fc4,
    FUN_080820b8,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[10] = {
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
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      unk_0a : 0x41,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      unk_0a : 0x41,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(64), PIXEL(64)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(22), PIXEL(22)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(22), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      unk_0a : 0x41,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), -PIXEL(128), -PIXEL(128)},
    },
};

static const u8 sInitModes[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// clang-format off
static const motion_t sMotions[8] = {
    MOTION(SM079_PANTHEON_AQUA_MOD_ROCK, 1),
    MOTION(SM079_PANTHEON_AQUA_MOD_ROCK, 2),
    MOTION(SM079_PANTHEON_AQUA_MOD_ROCK, 2),
    MOTION(SM039_PANTHEON_AQUA, 10),
    MOTION(SM039_PANTHEON_AQUA, 19),
    MOTION(SM039_PANTHEON_AQUA, 20),
    MOTION(SM039_PANTHEON_AQUA, 21),
    MOTION(SM039_PANTHEON_AQUA, 22),
};
// clang-format on

static const u8 u8_ARRAY_ARRAY_0836810a[3][3] = {
    {0x3F, 0x3F, 0x3F},
    {0x3F, 0x0A, 0x3F},
    {0x3F, 0x0A, 0x3F},
};
