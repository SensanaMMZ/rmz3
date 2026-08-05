#include "collision.h"
#include "enemy.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "vfx.h"

struct OmegaWhiteHandObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Coord unk_b4;  // オメガ本体からの距離?
  u8 unk_bc[8];
};
static_assert(sizeof(struct OmegaWhiteHandObject) == sizeof(struct Enemy));

static const struct Collision sCollisions[];

static void OmegaWhiteHand_Init(struct OmegaWhiteHandObject* p);
static void OmegaWhiteHand_Update(Object* p);
static void OmegaWhiteHand_Die(struct Entity* p);

// clang-format off
const EnemyRoutine gOmegaWhiteHandRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)OmegaWhiteHand_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)OmegaWhiteHand_Update,
    [ENTITY_DIE] =       (EnemyFunc)OmegaWhiteHand_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateOmegaWhiteHand(struct Coord* c, bool8 isLeftHand, struct Entity* omega) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 8);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = isLeftHand;
    p->unk_28 = omega;
  }
  return p;
}

// --------------------------------------------

static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

static void OmegaWhiteHand_Init(struct OmegaWhiteHandObject* p) {
  InitScalerotMotion1(&p->s);
  (p->s).angle = 0;
  SET_XFLIP(p, FALSE);
  (p->s).flags &= ~DISPLAY;
  (p->s).flags |= FLIPABLE;
  INIT_BODY(p, &sCollisions[0], 1, onCollision);
  {
    struct Coord* d = &(p->s).d;
    d->x = d->y = 0;
  }
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 1;
  if ((p->s).work[0] == 0) {  // 右手
    (p->s).spr.oam.priority = 3;
    (p->unk_b4).x = -PIXEL(19);
    (p->unk_b4).y = -PIXEL(58);
  } else {                // 左手
    (p->s).taskCol = 23;  // 重なったら、右手の方が見えるようにする
    (p->unk_b4).x = PIXEL(21);
    (p->unk_b4).y = -PIXEL(56);
    SET_YFLIP(p, FALSE);  // 左手は上下反転させない
  }
  (p->s).flags2 |= WHITE_PAINTABLE;
  (p->s).invincibleID = ((p->s).unk_28)->uniqueID;  // オメガが白くなったら、手も白くするで

  OmegaWhiteHand_Update((void*)p);
}

// --------------------------------------------

bool8 FUN_0806aa9c(struct Enemy* p);
bool8 FUN_0806ae90(struct Enemy* p);
bool8 FUN_0806af24(struct Enemy* p);
bool8 FUN_0806b094(struct Enemy* p);
bool8 FUN_0806b120(struct Enemy* p);
bool8 FUN_0806b8cc(struct Enemy* p);

void FUN_0806aaa0(struct Enemy* p);
void FUN_0806ae94(struct Enemy* p);
void FUN_0806af40(struct Enemy* p);
void FUN_0806b098(struct Enemy* p);
void FUN_0806b124(struct Enemy* p);
void FUN_0806b8d0(struct Enemy* p);

void FUN_0806ac98(struct Enemy* p);
void FUN_0806aedc(struct Enemy* p);
void FUN_0806afdc(struct Enemy* p);
void FUN_0806b0dc(struct Enemy* p);
void FUN_0806b4cc(struct Enemy* p);
void FUN_0806bb8c(struct Enemy* p);

static void OmegaWhiteHand_Update(Object* p) {
  // clang-format off
  static const EnemyFunc sUpdates[6] = {
      (EnemyFunc)FUN_0806aa9c,
      (EnemyFunc)FUN_0806ae90,
      (EnemyFunc)FUN_0806af24,
      (EnemyFunc)FUN_0806b094,
      (EnemyFunc)FUN_0806b120,
      (EnemyFunc)FUN_0806b8cc,
  }; // 0x083663e0
  // clang-format on

  // clang-format off
  static const EnemyFunc sUpdateRights[6] = {
      (EnemyFunc)FUN_0806aaa0,
      (EnemyFunc)FUN_0806ae94,
      (EnemyFunc)FUN_0806af40,
      (EnemyFunc)FUN_0806b098,
      (EnemyFunc)FUN_0806b124,
      (EnemyFunc)FUN_0806b8d0,
  }; // 0x083663f8
  // clang-format on

  // clang-format off
  static const EnemyFunc sUpdateLefts[6] = {
      (EnemyFunc)FUN_0806ac98,
      (EnemyFunc)FUN_0806aedc,
      (EnemyFunc)FUN_0806afdc,
      (EnemyFunc)FUN_0806b0dc,
      (EnemyFunc)FUN_0806b4cc,
      (EnemyFunc)FUN_0806bb8c,
  }; // 0x08366410
  // clang-format on

  struct Boss* omega = (struct Boss*)(p->s).unk_28;
  if ((omega->s).mode[0] >= ENTITY_DISAPPEAR) {
    // 本体が消えるときは、手も消える
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  if (((omega->props).omegaWhite.unk_d4 & 2) && ((p->s).mode[1] != 5)) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  (sUpdates[(p->s).mode[1]])((void*)p);

  if ((p->s).work[0] == 0) {  // 右手
    (sUpdateRights[(p->s).mode[1]])((void*)p);
  } else {  // 左手
    (sUpdateLefts[(p->s).mode[1]])((void*)p);
  }
}

// --------------------------------------------

void FUN_0806a8fc(struct Enemy* p);
void FUN_0806aa54(struct Enemy* p);

static void OmegaWhiteHand_Die(struct Entity* p) {
  static const EnemyFunc sDeinitializers[2] = {
      (EnemyFunc)FUN_0806a8fc,
      (EnemyFunc)FUN_0806aa54,
  };  // 0x08366428
  (sDeinitializers[(p->mode)[1]])((void*)p);
}

// --------------------------------------------

void FUN_0806a8fc(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      if ((p->s).work[0] == 1) {
        u32 fl = (p->s).flags;
        register s32 t asm("r0");
        t = 1;
        asm("" : "+r"(t));
        t |= fl;
        t &= 0xEF;
        (p->s).flags = t;
        (p->s).spr.xflip = m;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
          (p->s).flags &= 0xDF;
          *((u8*)p + 0x4d) = m;
          {
            s32 ov2 = *oa;
            s32 m21 = -0x21;
            m21 &= ov2;
            *oa = m21;
          }
        }
        (p->s).angle = m;
        SetMotion(&p->s, 0x0901);
      } else {
        u32 fl = (p->s).flags;
        s32 t = 1;
        t |= fl;
        t &= 0xEF;
        (p->s).flags = t;
        (p->s).spr.xflip = m;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
          (p->s).flags &= 0xDF;
          *((u8*)p + 0x4d) = m;
          {
            s32 ov2 = *oa;
            s32 m21 = -0x21;
            m21 &= ov2;
            *oa = m21;
          }
        }
        (p->s).angle = m;
        SetMotion(&p->s, 0x0900);
      }
      {
        u8* a = (u8*)p + 0x8c;
        register s32 z asm("r1");
        z = 0;
        asm("" : "+r"(z) : "r"(a));
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z;
        (p->s).flags &= 0xFB;
        (p->s).d.x = z;
        (p->s).d.y = z;
      }
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      if ((p->s).work[0] == 1) {
        struct Entity* q = (p->s).unk_28;
        s32 y = (p->s).coord.y;
        s32 t2 = y + 0x3800;
        s32 d = (q->coord).y;
        d -= t2;
        y += (d * 24) >> 8;
        (p->s).coord.y = y;
      } else {
        struct Entity* q = (p->s).unk_28;
        s32 x = (p->s).coord.x;
        s32 t3 = x + 0x1300;
        s32 dx = (q->coord).x;
        s32 y, dy, t4;
        dx -= t3;
        x += (dx * 24) >> 8;
        (p->s).coord.x = x;
        y = (p->s).coord.y;
        t4 = y + 0x3A00;
        dy = (q->coord).y;
        dy -= t4;
        y += (dy * 24) >> 8;
        (p->s).coord.y = y;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      s32 t;
      if ((p->s).work[2] == 0) {
        break;
      }
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 3: {
      s32 z = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z;
      break;
    }
  }
}


void FUN_0806aa54(struct Enemy* p) {
  struct Coord c;
  if ((p->s).mode[2] == 0) {
    c.x = (p->s).coord.x;
    c.y = (p->s).coord.y;
    CreateSmoke(1, &c);
    PlaySound(0x2a);
    (p->s).flags &= ~DISPLAY;
    SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
  }
}

bool8 FUN_0806aa9c(struct Enemy* p) { return TRUE; }


// 0x0806AAA0
// 2 bytes off.  The instruction stream is now the same length as retail and every
// opcode matches; what is left is three register-number ties that agbcc gives no
// pin for (§6.169): the parent entity is r2 where retail uses r1 (case 2), the
// cached work[2] is r4 where retail uses r3 (case 4), and case 4's running x
// lands in r0 where retail uses r1.
// Levers already applied and required to get this far: `u32 w2` + an
// `asm("" : "+l"(w2))` barrier so `(w2 << 24) >> 27` survives in the else arm
// while `w2 >> 3` stays a bare `lsrs` in the if arm (§6.177); an opaque `one`
// for the `& 1` test so it is not CSE'd with another literal (§6.178); unsigned
// `%` for `__umodsi3`; the `u8* d = p + 0x5c; *(s32*)(d + 4) = z;` pointer form;
// a `num` temp so work[3] is loaded before work[2]; and a `pb` props pointer
// computed before `q = (p->s).unk_28`.
NON_MATCH void FUN_0806aaa0(struct Enemy* p) {
#if MODERN
  struct Entity* q;
  s32 z, nx, ny;
  s32* pb;
  u32 w2, one, num;

  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((*(s32*)((u8*)(p->s).unk_28 + 0xd4) & 1) == 0) {
        break;
      }
      goto bump;
    case 2:
      (p->s).flags |= DISPLAY;
      z = 0;
      q = (p->s).unk_28;
      (p->s).coord.y = (q->coord).y - 0x1800;
      (p->s).coord.x = (q->coord).x;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + (q->coord).x;
      SetMotion(&p->s, MOTION(0x09, 0x00));
      {
        u8* d = (u8*)p + 0x5c;
        *(s32*)(d + 4) = z;
      }
      (p->s).d.x = z;
      (p->s).unk_coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y - 0x400);
      (p->s).coord.y = (p->s).unk_coord.y - 0x1800;
      (p->s).unk_coord.x = (p->s).coord.x;
      (p->s).d.x = 0x2000;
      if ((p->s).mode[3] == 1) {
        (p->s).work[2] = 0x80;
        (p->s).work[3] = z;
        (p->s).flags &= 0xEF;
        (p->s).spr.xflip = z;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        (p->s).mode[2] += 2;
      } else {
        (p->s).work[2] = 0x3C;
        (p->s).work[3] = RANDOM(RNG_0202f388) % 20;
        (p->s).flags &= 0xEF;
        (p->s).spr.xflip = z;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        (p->s).work[3] = z;
        (p->s).mode[2]++;
      }
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      (p->s).work[3]++;
      num = (p->s).work[3];
      w2 = (p->s).work[2];
      if ((u8)((u32)num % w2) == 0) {
        (p->s).work[2] = w2 - 10;
        (p->s).coord.x += ((s32)(RANDOM(RNG_0202f388) % 6) - 3) << 8;
      }
      if ((p->s).work[2] == 0) {
        (p->s).work[2] = 0x80;
        (p->s).work[3] = 0;
        goto bump;
      }
      break;
    case 4:
      w2 = (p->s).work[2];
      asm("" : "+l"(w2));
      one = 1;
      asm("" : "+l"(one));
      if (w2 & one) {
        pb = (s32*)((u8*)p + 0xb4);
        q = (p->s).unk_28;
        nx = *pb + (q->coord).x + ((w2 >> 3) << 8);
      } else {
        pb = (s32*)((u8*)p + 0xb4);
        q = (p->s).unk_28;
        nx = *pb + (q->coord).x - (((w2 << 24) >> 27) << 8);
      }
      (p->s).coord.x = nx;
      ny = *(s32*)((u8*)p + 0xb8) + (q->coord).y;
      (p->s).coord.y += ((ny - (p->s).coord.y) << 3) >> 8;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
    bump:
      (p->s).mode[2]++;
      break;
    case 5: {
      s32 z2;
      (p->s).flags |= DISPLAY;
      z2 = 0;
      (p->s).mode[1] = 2;
      (p->s).mode[2] = z2;
      break;
    }
  }
#else
  INCCODE("asm/enemy/omega_white_hand_6aaa0.inc");
#endif
}


// 0x0806AC98
// Twin of FUN_0806aaa0 and blocked identically: instruction stream the same
// length as retail with every opcode matching, 2 bytes off from the same three
// register-number ties (§6.169).  Differences from the twin: motion 0x0901, the
// FUN_08009f6c probe is 0x1000 above instead of 0x400, the drift is
// `(RANDOM & 7) - 4`, and the else arm does not re-zero work[3].
NON_MATCH void FUN_0806ac98(struct Enemy* p) {
#if MODERN
  struct Entity* q;
  s32 z, nx, ny;
  s32* pb;
  u32 w2, one, num;

  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((*(s32*)((u8*)(p->s).unk_28 + 0xd4) & 1) == 0) {
        break;
      }
      goto bump;
    case 2:
      (p->s).flags |= DISPLAY;
      z = 0;
      q = (p->s).unk_28;
      (p->s).coord.y = (q->coord).y - 0x1800;
      (p->s).coord.x = (q->coord).x;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + (q->coord).x;
      SetMotion(&p->s, MOTION(0x09, 0x01));
      {
        u8* d = (u8*)p + 0x5c;
        *(s32*)(d + 4) = z;
      }
      (p->s).d.x = z;
      (p->s).unk_coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y - 0x1000);
      (p->s).coord.y = (p->s).unk_coord.y - 0x1800;
      (p->s).unk_coord.x = (p->s).coord.x;
      (p->s).d.x = 0x2000;
      if ((p->s).mode[3] == 1) {
        (p->s).work[2] = 0x80;
        (p->s).work[3] = z;
        (p->s).flags &= 0xEF;
        (p->s).spr.xflip = z;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        (p->s).mode[2] += 2;
      } else {
        (p->s).work[2] = 0x3C;
        (p->s).work[3] = RANDOM(RNG_0202f388) % 20;
        (p->s).flags &= 0xEF;
        (p->s).spr.xflip = z;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m11 = -0x11;
          m11 &= ov;
          *oa = m11;
        }
        (p->s).mode[2]++;
      }
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      (p->s).work[3]++;
      num = (p->s).work[3];
      w2 = (p->s).work[2];
      if ((u8)((u32)num % w2) == 0) {
        (p->s).work[2] = w2 - 10;
        (p->s).coord.x += ((s32)(RANDOM(RNG_0202f388) & 7) - 4) << 8;
      }
      if ((p->s).work[2] == 0) {
        (p->s).work[2] = 0x80;
        (p->s).work[3] = 0;
        goto bump;
      }
      break;
    case 4:
      w2 = (p->s).work[2];
      asm("" : "+l"(w2));
      one = 1;
      asm("" : "+l"(one));
      if (w2 & one) {
        pb = (s32*)((u8*)p + 0xb4);
        q = (p->s).unk_28;
        nx = *pb + (q->coord).x + ((w2 >> 3) << 8);
      } else {
        pb = (s32*)((u8*)p + 0xb4);
        q = (p->s).unk_28;
        nx = *pb + (q->coord).x - (((w2 << 24) >> 27) << 8);
      }
      (p->s).coord.x = nx;
      ny = *(s32*)((u8*)p + 0xb8) + (q->coord).y;
      (p->s).coord.y += ((ny - (p->s).coord.y) << 3) >> 8;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
    bump:
      (p->s).mode[2]++;
      break;
    case 5: {
      s32 z2;
      (p->s).flags |= DISPLAY;
      z2 = 0;
      (p->s).mode[1] = 2;
      (p->s).mode[2] = z2;
      break;
    }
  }
#else
  INCCODE("asm/enemy/omega_white_hand_6ac98.inc");
#endif
}


bool8 FUN_0806ae90(struct Enemy* p) { return TRUE; }

void FUN_0806ae94(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      (p->s).coord.y = ((struct Enemy*)(p->s).unk_28)->s.coord.y;
      (p->s).coord.x = ((struct Enemy*)(p->s).unk_28)->s.coord.x;
      SetMotion(&p->s, MOTION(0x9, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

void FUN_0806aedc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      (p->s).coord.y = ((struct Enemy*)(p->s).unk_28)->s.coord.y;
      (p->s).coord.x = ((struct Enemy*)(p->s).unk_28)->s.coord.x;
      SetMotion(&p->s, MOTION(0x9, 1));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_0806af24(struct Enemy* p) {
  if (((p->s).unk_28)->mode[1] == 5) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

void FUN_0806af40(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
      SetMotion(&p->s, 0x900);
      SET_XFLIP(p, FALSE);
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 wob;
      (p->s).work[2] += 2;
      wob = gSineTable[(p->s).work[2]];
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + ((p->s).unk_28)->coord.y + wob;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + ((p->s).unk_28)->coord.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_0806afdc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = ((p->s).unk_28)->uniqueID;
      SetMotion(&p->s, 0x901);
      SET_XFLIP(p, FALSE);
      SET_YFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 wob;
      (p->s).work[2] += 2;
      wob = gSineTable[(p->s).work[2]] << 1;
      (p->s).coord.y = *(s32*)((u8*)p + 0xb8) + ((p->s).unk_28)->coord.y + wob;
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + ((p->s).unk_28)->coord.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 FUN_0806b094(struct Enemy* p) { return TRUE; }

void FUN_0806b098(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_0806b0dc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SET_XFLIP(p, FALSE);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

bool8 FUN_0806b120(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/omega_white_hand_p5.inc");

bool8 FUN_0806b8cc(struct Enemy* p) { return TRUE; }

s32 PushoutToUp1(s32 x, s32 y);
void AppendQuake(u8 kind, struct Coord* c);

// 0x0806B8D0
void FUN_0806b8d0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 z asm("r4");
      register u8* oa asm("r2");
      {
        u8 fl = (p->s).flags;
        u32 f = 1;
        f |= fl;
        z = 0;
        {
          u32 m = 0xEF;
          f &= m;
          (p->s).flags = f;
        }
      }
      {
        u8* q = (u8*)p + 0x4c;
        *q = z;
      }
      oa = (u8*)p + 0x4a;
      {
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        *oa = m11;
      }
      {
        u8 fl = (p->s).flags;
        u32 f = 0xDF;
        f &= fl;
        (p->s).flags = f;
      }
      {
        u8* q = (u8*)p + 0x4d;
        *q = z;
      }
      {
        s32 ov = *oa;
        s32 m21 = -0x21;
        m21 &= ov;
        *oa = m21;
      }
      {
        u8* q = (u8*)p + 0x24;
        *q = z;
      }
      SetMotion(&p->s, 0x90 << 4);
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
      (p->s).d.x = z;
      (p->s).d.y = z;
      RNG_0202f388 = ((RNG_0202f388 * 0x343FD + 0x269EC3) << 1) >> 1;
      (p->s).work[2] = z;
      (p->s).mode[2] += 2;
      break;
    }
    case 1: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      {
        struct Entity* e = (p->s).unk_28;
        {
          s32 cx = (p->s).coord.x;
          s32 k = 0x98 << 5;
          s32 base = cx + k;
          s32 d = (e->coord).x - base;
          (p->s).coord.x = cx + (((d * 2 + d) << 3) >> 8);
        }
        {
          s32 cy = (p->s).coord.y;
          s32 k = 0xe8 << 6;
          s32 base = cy + k;
          s32 d = (e->coord).y - base;
          (p->s).coord.y = cy + (((d * 2 + d) << 3) >> 8);
        }
      }
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      s32 dy;
      s32 r;
      dy = (p->s).d.y + 0x20;
      (p->s).d.y = dy;
      if (dy > (0xe0 << 2)) {
        (p->s).d.y = 0xe0 << 2;
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y + (0xc0 << 5));
      if (r != 0) {
        AppendQuake(4, &(p->s).coord);
        PlaySound(0x91);
        (p->s).coord.y += r;
        {
          s32 t = (p->s).work[2];
          if (t == 0) {
            asm volatile("" : "+l"(t));
            t += 1;
            (p->s).work[2] = t;
            (p->s).d.y = -0xe8;
          } else {
            (p->s).mode[2]++;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 3:
      (p->s).work[2] = 0x1E;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 5: {
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
      (p->s).work[2] = (t >> 0x11) % 5 + 5;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 6: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      {
        u32* rng = &RNG_0202f388;
        register u32 v asm("r0");
        {
          register u32 sd asm("r1");
          sd = *rng;
          v = 0x343FD;
          v *= sd;
        }
        {
          register u32 c asm("r1");
          c = 0x269EC3;
          v += c;
        }
        v <<= 1;
        {
          register u32 h asm("r1");
          h = v >> 1;
          *rng = h;
        }
        (p->s).work[2] = (v >> 0x11) % 0xA + 0x28;
      }
      (p->s).mode[2]++;
      break;
    }
    case 7: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      {
        s32* b = (s32*)((u8*)p + 0xb4);
        struct Entity* e = (p->s).unk_28;
        s32 lim;
        s32 cx;
        {
          register s32 bv asm("r0");
          register s32 ex asm("r1");
          bv = *b;
          ex = (e->coord).x;
          bv += ex;
          lim = bv;
        }
        cx = (p->s).coord.x;
        if (cx > lim) {
          cx += -0x300;
          (p->s).coord.x = cx;
          {
            register s32 bv asm("r1");
            register s32 ex asm("r0");
            bv = *b;
            ex = (e->coord).x;
            ex = bv + ex;
            lim = ex;
          }
          if (cx >= lim) {
            goto upd;
          }
        } else {
          cx += (0xc0 << 2);
          (p->s).coord.x = cx;
          {
            register s32 bv asm("r1");
            register s32 ex asm("r0");
            bv = *b;
            ex = (e->coord).x;
            ex = bv + ex;
            lim = ex;
          }
          if (cx <= lim) {
            goto upd;
          }
        }
        (p->s).coord.x = lim;
        (p->s).mode[2]++;
      }
    upd:
      UpdateMotionGraphic(&p->s);
      if ((p->s).mode[2] == 8) {
        break;
      }
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2] = 4;
      break;
    }
    case 8:
      break;
  }
  {
    struct Entity* e = (p->s).unk_28;
    if ((*(u32*)((u8*)e + 0xd4) & 8) != 0) {
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + (e->coord).x;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y + -0x800) + -0x1800;
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
      (p->s).mode[3] = 0;
    }
  }
}

// 0x0806BB8C
void FUN_0806bb8c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 z asm("r4");
      register u8* oa asm("r2");
      {
        u8 fl = (p->s).flags;
        u32 f = 1;
        f |= fl;
        z = 0;
        {
          u32 m = 0xEF;
          f &= m;
          (p->s).flags = f;
        }
      }
      {
        u8* q = (u8*)p + 0x4c;
        *q = z;
      }
      oa = (u8*)p + 0x4a;
      {
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        *oa = m11;
      }
      {
        u8 fl = (p->s).flags;
        u32 f = 0xDF;
        f &= fl;
        (p->s).flags = f;
      }
      {
        u8* q = (u8*)p + 0x4d;
        *q = z;
      }
      {
        s32 ov = *oa;
        s32 m21 = -0x21;
        m21 &= ov;
        *oa = m21;
      }
      {
        u8* q = (u8*)p + 0x24;
        *q = z;
      }
      SetMotion(&p->s, 0x0901);
      (p->s).d.x = z;
      (p->s).d.y = z;
      RNG_0202f388 = ((RNG_0202f388 * 0x343FD + 0x269EC3) << 1) >> 1;
      (p->s).work[2] = z;
      (p->s).mode[2] += 2;
      break;
    }
    case 1: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      {
        struct Entity* e = (p->s).unk_28;
        s32 cy = (p->s).coord.y;
        s32 k = 0xe0 << 6;
        s32 base = cy + k;
        s32 d = (e->coord).y - base;
        (p->s).coord.y = cy + (((d * 2 + d) << 3) >> 8);
      }
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      s32 dy;
      s32 r;
      dy = (p->s).d.y + 0x20;
      (p->s).d.y = dy;
      if (dy > (0xe0 << 2)) {
        (p->s).d.y = 0xe0 << 2;
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y + (0xc0 << 5));
      if (r != 0) {
        AppendQuake(4, &(p->s).coord);
        PlaySound(0x91);
        (p->s).coord.y += r;
        {
          s32 t = (p->s).work[2];
          if (t == 0) {
            asm volatile("" : "+l"(t));
            t += 1;
            (p->s).work[2] = t;
            (p->s).d.y = -0xe8;
          } else {
            (p->s).mode[2]++;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 3:
      (p->s).work[2] = 0xA;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2]++;
      break;
    }
    case 5:
      RNG_0202f388 = ((RNG_0202f388 * 0x343FD + 0x269EC3) << 1) >> 1;
      (p->s).work[2] = 5;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 6: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      RNG_0202f388 = ((RNG_0202f388 * 0x343FD + 0x269EC3) << 1) >> 1;
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      break;
    }
    case 7: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      {
        s32* b = (s32*)((u8*)p + 0xb4);
        struct Entity* e = (p->s).unk_28;
        s32 lim;
        s32 cx;
        {
          register s32 bv asm("r0");
          register s32 ex asm("r1");
          bv = *b;
          ex = (e->coord).x;
          bv += ex;
          lim = bv;
        }
        cx = (p->s).coord.x;
        if (cx > lim) {
          cx += -0x380;
          (p->s).coord.x = cx;
          {
            register s32 bv asm("r1");
            register s32 ex asm("r0");
            bv = *b;
            ex = (e->coord).x;
            ex = bv + ex;
            lim = ex;
          }
          if (cx >= lim) {
            goto upd;
          }
        } else {
          cx += (0xe0 << 2);
          (p->s).coord.x = cx;
          {
            register s32 bv asm("r1");
            register s32 ex asm("r0");
            bv = *b;
            ex = (e->coord).x;
            ex = bv + ex;
            lim = ex;
          }
          if (cx <= lim) {
            goto upd;
          }
        }
        (p->s).coord.x = lim;
        (p->s).mode[2]++;
      }
    upd:
      UpdateMotionGraphic(&p->s);
      if ((p->s).mode[2] == 8) {
        break;
      }
      t = (p->s).work[2];
      if (t == 0) {
        break;
      }
      t -= 1;
      (p->s).work[2] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).mode[2] = 4;
      break;
    }
    case 8:
      break;
  }
  {
    struct Entity* e = (p->s).unk_28;
    if ((*(u32*)((u8*)e + 0xd4) & 8) != 0) {
      (p->s).coord.x = *(s32*)((u8*)p + 0xb4) + (e->coord).x;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y + -0x800) + -0x1800;
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
      (p->s).mode[3] = 0;
    }
  }
}

// 0x0806be0c
static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {}

// 0x08366430
static const struct Collision sCollisions[7] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0100, 0x1800, 0x2B00},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0100, 0x1600, 0x2900},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0100, 0x1800, 0x2B00},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0100, 0x1600, 0x2900},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0100, 0x1800, 0x2B00},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0400, 0x0200, 0x1E00, 0x2800},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0400, 0x0200, 0x2000, 0x2A00},
    },
};
