#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "physics.h"
#include "vfx.h"

static const struct Collision sCollisions[14];

static void Projectile9_Init(struct Projectile* p);
static void Projectile9_Update(struct Projectile* p);
static void Projectile9_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gBlazinProjectileRoutine = {
    [ENTITY_INIT] =      (ProjectileFunc)Projectile9_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Projectile9_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Projectile9_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Projectile* FUN_0809e4b0(struct Entity* e, struct Coord* c) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 9);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_0809e500(struct Entity* e, struct Coord* c, struct Coord* d) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 9);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).d = *d;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_0809e55c(struct Entity* e, struct Coord* c, struct Coord* c2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 9);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).coord = *c;
    (p->s).unk_coord = *c2;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* _createBlazinEXFireBall(struct Entity* e, struct Coord* c, struct Coord* d, u8 angle) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 9);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    p->work[0] = angle;
    (p->s).coord = *c;
    (p->s).d = *d;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* blazin_0809e620(struct Entity* e, struct Coord* c, struct Coord* d) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 9);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).d = *d;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

// --------------------------------------------

NAKED static void Projectile9_Init(struct Projectile* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r5, r0, #0\n\
	bl InitNonAffineMotion\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #1\n\
	movs r4, #0\n\
	movs r6, #0\n\
	orrs r1, r0\n\
	movs r0, #2\n\
	orrs r1, r0\n\
	strb r1, [r5, #0xa]\n\
	adds r0, r5, #0\n\
	bl ResetDynamicMotion\n\
	ldrb r0, [r5, #0x10]\n\
	cmp r0, #0\n\
	bne _0809E6BC\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0809E6B8 @ =sCollisions\n\
	adds r2, r5, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0x10\n\
	b _0809E71E\n\
	.align 2, 0\n\
_0809E6B8: .4byte sCollisions\n\
_0809E6BC:\n\
	cmp r0, #1\n\
	bne _0809E6D4\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0809E6D0 @ =0x0836ADF0\n\
	b _0809E716\n\
	.align 2, 0\n\
_0809E6D0: .4byte sCollisions+(6*24)\n\
_0809E6D4:\n\
	cmp r0, #2\n\
	bne _0809E6EC\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0809E6E8 @ =0x0836ADC0\n\
	b _0809E716\n\
	.align 2, 0\n\
_0809E6E8: .4byte sCollisions+(4*24)\n\
_0809E6EC:\n\
	cmp r0, #3\n\
	bne _0809E704\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0809E700 @ =0x0836ADA8\n\
	b _0809E716\n\
	.align 2, 0\n\
_0809E700: .4byte sCollisions+(3*24)\n\
_0809E704:\n\
	cmp r0, #4\n\
	bne _0809E726\n\
	ldrb r0, [r5, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0809E750 @ =0x0836AE80\n\
_0809E716:\n\
	adds r2, r5, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #1\n\
_0809E71E:\n\
	bl InitBody\n\
	str r5, [r4, #0x2c]\n\
	str r6, [r4, #0x24]\n\
_0809E726:\n\
	movs r0, #0xff\n\
	strb r0, [r5, #0x12]\n\
	ldr r1, _0809E754 @ =gProjectileFnTable\n\
	ldrb r0, [r5, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r5, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r5, #0x14]\n\
	movs r0, #0\n\
	strb r1, [r5, #0xd]\n\
	strb r0, [r5, #0xe]\n\
	strb r0, [r5, #0xf]\n\
	adds r0, r5, #0\n\
	bl Projectile9_Update\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_0809E750: .4byte sCollisions+(12*24)\n\
_0809E754: .4byte gProjectileFnTable\n\
 .syntax divided\n");
}

// --------------------------------------------

static void FUN_0809e7b4(struct Projectile* p);
void FUN_0809e7c0(struct Projectile* p);
void FUN_0809e9b8(struct Projectile* p);
void FUN_0809e9c4(struct Projectile* p);
void FUN_0809eadc(struct Projectile* p);
void FUN_0809eae8(struct Projectile* p);
void FUN_0809ec18(struct Projectile* p);
void FUN_0809ec24(struct Projectile* p);
void FUN_0809edfc(struct Projectile* p);
void FUN_0809ee08(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_ARRAY_0836ad24[5][2] = {
    {FUN_0809e7b4, FUN_0809e7c0},
    {FUN_0809e9b8, FUN_0809e9c4},
    {FUN_0809eadc, FUN_0809eae8},
    {FUN_0809ec18, FUN_0809ec24},
    {FUN_0809edfc, FUN_0809ee08},
};
// clang-format on

static void Projectile9_Update(struct Projectile* p) {
  // clang-format off
  static const ProjectileFunc* const sUpdates[5] = {
    PTR_ARRAY_ARRAY_0836ad24[0],
    PTR_ARRAY_ARRAY_0836ad24[1],
    PTR_ARRAY_ARRAY_0836ad24[2],
    PTR_ARRAY_ARRAY_0836ad24[3],
    PTR_ARRAY_ARRAY_0836ad24[4],
  };
  // clang-format on
  ((sUpdates[(p->s).work[0]])[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void Projectile9_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void FUN_0809e7b4(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

// 0x0809e7c0
void FUN_0809e7c0(struct Projectile* p) {
  if ((p->s).unk_28->mode[0] > 1) {
    CreateSmoke(2, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else if ((p->body).status & 0x200) {
    struct Coord c;
    c = (p->s).coord;
    c.x -= 0x800;
    CreateSmoke(2, &c);
    c.x += 0x800;
    c.y -= 0x400;
    CreateSmoke(2, &c);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else if (--(p->s).work[2] == 0) {
    CreateSmoke(2, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else {
    switch ((p->s).mode[2]) {
      case 0: {
        u8 f;
        SetMotion(&p->s, 0xA304);
        f = (p->s).unk_28->flags & X_FLIP;
        if (f == 0) {
          (p->s).d.x = 0xC0;
          SET_XFLIP(p, 0);
        } else {
          (p->s).d.x = -0xC0;
          SET_XFLIP(p, 1);
        }
        (p->s).d.y = -0x400;
        (p->s).work[3] = 0x28;
        (p->s).mode[2]++;
        FALLTHROUGH;
      }
      case 1:
        if ((p->s).work[3] != 0 && --(p->s).work[3] == 0) {
          SetDDP(&p->body, &sCollisions[1]);
        }
        (p->s).d.y += 0x40;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.x += (p->s).d.x;
        (p->s).coord.y += (p->s).d.y;
        {
          s32 push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
          if (push != 0) {
            (p->s).coord.y += push;
            (p->s).d.y = -0x300;
          }
        }
        if ((p->s).d.x > 0) {
          s32 push = PushoutToLeft1((p->s).coord.x + 0x800, (p->s).coord.y);
          if (push != 0) {
            (p->s).d.x = -(p->s).d.x;
            SET_XFLIP(p, !(((p->s).flags >> 4) & 1));
            (p->s).coord.x += push;
          }
        } else {
          s32 push = PushoutToRight1((p->s).coord.x - 0x800, (p->s).coord.y);
          if (push != 0) {
            (p->s).d.x = -(p->s).d.x;
            SET_XFLIP(p, !(((p->s).flags >> 4) & 1));
            (p->s).coord.x += push;
          }
        }
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

void FUN_0809e9b8(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

void FUN_0809e9c4(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 z4;
      InitScalerotMotion1(&p->s);
      ResetDynamicMotion(&p->s);
      *(s32*)((u8*)p + 0xbc) = 0x100;
      ((p->s).spr).mag.x = 0x100;
      ((p->s).spr).mag.y = *(s32*)((u8*)p + 0xbc);
      z4 = 0;
      SetMotion(&p->s, MOTION(0xA3, 0x01));
      *(s32*)((u8*)p + 0xb8) = 0x400;
      (p->s).unk_coord.x = ((p->s).d.x << 10) >> 8;
      (p->s).unk_coord.y = ((p->s).d.y * *(s32*)((u8*)p + 0xb8)) >> 8;
      (p->s).work[2] = 0x28;
      (p->s).work[3] = z4;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      s32* pb = (s32*)((u8*)p + 0xb8);
      s32 v = *pb;
      s32* pc2;
      s32 w;
      v += (-v * 10) >> 8;
      *pb = v;
      (p->s).unk_coord.x = ((p->s).d.x * v) >> 8;
      (p->s).unk_coord.y = ((p->s).d.y * *pb) >> 8;
      pc2 = (s32*)((u8*)p + 0xbc);
      w = *pc2;
      w += ((0x1C0 - w) * 20) >> 8;
      *pc2 = w;
      ((p->s).spr).mag.x = w;
      ((p->s).spr).mag.y = *pc2;
      if (*pc2 > 0x1A0) {
        if ((p->s).work[3] == 0) {
          (p->s).work[3]++;
          SetDDP(&p->body, &sCollisions[9]);
        }
      }
      (p->s).coord.x += (p->s).unk_coord.x;
      (p->s).coord.y += (p->s).unk_coord.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
    }
  }
}

void FUN_0809eadc(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

void FUN_0809eae8(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 dx0;
      SetMotion(&p->s, 0xA302);
      dx0 = (p->s).unk_coord.x;
      (p->s).work[2] = 0x36;
      (p->s).d.x = (dx0 - (p->s).coord.x) / 0x36;
      {
        s32 k = 0x16C80;
        k -= (p->s).unk_coord.y - (p->s).coord.y;
        (p->s).d.y = -(k / 0x36);
      }
      (p->s).work[2] = 0x35;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      (p->s).d.y += 0x40;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0) {
        goto incmode;
      }
      {
        s32 t = (p->s).work[2] - 1;
        s32 z3 = 0;
        (p->s).work[2] = t;
        if ((t << 24) == 0) {
        incmode:
          (p->s).mode[2]++;
          break;
        }
        if ((p->body).status & 4) {
          (p->body).status = z3;
          (p->body).prevStatus = z3;
          (p->body).invincibleTime = z3;
          (p->s).flags &= ~COLLIDABLE;
          goto setdie;
        }
        {
          u16 a = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
          if (a == 0) {
            break;
          }
          if (a & 0x8000) {
            break;
          }
          CreateSmoke(2, &(p->s).coord);
          goto setdie;
        }
      }
    case 2:
      SetMotion(&p->s, 0xA303);
      SetDDP(&p->body, &sCollisions[5]);
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    setdie:
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}


void FUN_0809ec18(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

INCASM("asm/projectile/blazin_pre_p4.inc");

void FUN_0809edfc(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

void FUN_0809ee08(struct Projectile* p) {
  s32 po[4];
  if ((*(struct Entity* volatile*)&(p->s).unk_28)->mode[0] > 1) {
    CreateSmoke(1, &(p->s).coord);
    goto die;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      SetMotion(&p->s, 0xA305);
      {
        s32* spd = (s32*)((u8*)p + 0xb8);
        s32 k5 = 0x500;
        *spd = k5;
        (p->s).unk_coord.x = ((p->s).d.x * k5) >> 8;
        (p->s).unk_coord.y = ((p->s).d.y * *spd) >> 8;
      }
      (p->s).work[2] = 4;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 r6f;
      s32 po3v;
      (p->s).coord.x += (p->s).unk_coord.x;
      (p->s).coord.y += (p->s).unk_coord.y;
      UpdateMotionGraphic(&p->s);
      r6f = 0;
      po[0] = PushoutToUp1((p->s).coord.x, (p->s).coord.y + 0x800);
      po[1] = PushoutToDown1((p->s).coord.x, (p->s).coord.y + -0x800);
      po[2] = PushoutToLeft1((p->s).coord.x + 0x800, (p->s).coord.y);
      po3v = PushoutToRight1((p->s).coord.x + -0x800, (p->s).coord.y);
      po[3] = po3v;
      if (po[0] != 0) {
        (p->s).unk_coord.y = -(p->s).unk_coord.y;
        (p->s).coord.y += po[0];
        if (po[2] != 0) {
          (p->s).coord.x += po[2];
          (p->s).unk_coord.x = -(p->s).unk_coord.x;
        } else if (po3v != 0) {
          (p->s).coord.x += po3v;
          (p->s).unk_coord.x = -(p->s).unk_coord.x;
        }
        r6f = 1;
      } else if (po[1] != 0) {
        (p->s).unk_coord.y = -(p->s).unk_coord.y;
        (p->s).coord.y += po[1];
        if (po[2] != 0) {
          (p->s).coord.x += po[2];
          (p->s).unk_coord.x = -(p->s).unk_coord.x;
        } else if (po3v != 0) {
          (p->s).coord.x += po3v;
          (p->s).unk_coord.x = -(p->s).unk_coord.x;
        }
        r6f = 1;
      } else if (po[2] != 0) {
        (p->s).coord.x += po[2];
        (p->s).unk_coord.x = -(p->s).unk_coord.x;
        r6f = 1;
      } else if (po3v != 0) {
        (p->s).coord.x += po3v;
        (p->s).unk_coord.x = -(p->s).unk_coord.x;
        r6f = 1;
      }
      if (r6f == 1) {
        PlaySound(0);
        {
          s32 t = (p->s).work[2] - 1;
          (p->s).work[2] = t;
          if ((u32)(t << 24) != 0) {
            break;
          }
        }
        (p->s).mode[2]++;
      }
      break;
    }
    case 2: {
      s32* spd6 = (s32*)((u8*)p + 0xb8);
      struct Entity* e;
      s32 dx;
      s32 dy;
      s32 a;
      s32 b;
      s32 mag;
      *spd6 = 0x500;
      e = (struct Entity*)(p->s).unk_28;
      dx = e->coord.x - (p->s).coord.x;
      (p->s).d.x = dx;
      {
        s32 t2 = (p->s).coord.y + 0x1000;
        dy = e->coord.y - t2;
      }
      (p->s).d.y = dy;
      {
        s32 aa;
        s32 bb;
        a = dx >> 2;
        aa = a * a;
        b = dy >> 2;
        bb = b * b;
        mag = (u32)(Sqrt(aa + bb) << 16) >> 14;
      }
      if (mag != 0) {
        (p->s).d.x = ((p->s).d.x << 8) / mag;
        (p->s).d.y = ((p->s).d.y << 8) / mag;
      }
      (p->s).unk_coord.x = ((p->s).d.x * *spd6) >> 8;
      (p->s).unk_coord.y = ((p->s).d.y * *spd6) >> 8;
      *(s32*)((u8*)p + 0xbc) = mag;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3: {
      s32* t;
      s32 v;
      (p->s).coord.x += (p->s).unk_coord.x;
      (p->s).coord.y += (p->s).unk_coord.y;
      UpdateMotionGraphic(&p->s);
      t = (s32*)((u8*)p + 0xbc);
      v = *t - *(s32*)((u8*)p + 0xb8);
      *t = v;
      if (v <= 0) {
      die:
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
    }
  }
}

// --------------------------------------------

// 0x0836ad60
static const struct Collision sCollisions[14] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0100, -0x0400, 0x1A00, 0x0E00},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {0x0100, -0x0400, 0x1A00, 0x0E00},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0100, -0x0400, 0x1A00, 0x0E00},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      element : ELEMENT_FLAME,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000004,
      range : {0x0000, 0x0000, 0x0A00, 0x0A00},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      element : ELEMENT_FLAME,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000004,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      element : ELEMENT_FLAME,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000004,
      range : {0x0000, -0x0700, 0x0A00, 0x1700},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      element : ELEMENT_FLAME,
      comboLv : 0,
      remaining : 2,
      layer : 0x00000004,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [7] = {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0000, 0x0C00, 0x0C00},
    },
    [8] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0C00, 0x0C00},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      element : ELEMENT_FLAME,
      comboLv : 0,
      remaining : 2,
      layer : 0x00000004,
      range : {0x0000, 0x0000, 0x1100, 0x1100},
    },
    [10] = {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0000, 0x1600, 0x1600},
    },
    [11] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {0x0000, 0x0000, 0x1600, 0x1600},
    },
    [12] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0000, 0x1A00, 0x1400},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1A00, 0x1400},
    },
};
