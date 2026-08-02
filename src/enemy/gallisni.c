#include "zero.h"
#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "mission.h"
#include "motion.h"
#include "stagerun.h"
#include "story.h"

static const struct Collision sCollisions[5];

static const EnemyFunc sDeads[3];

bool8 gallisni_080870bc(struct Enemy* p);
bool8 gallisni_08087118(struct Enemy* p);
static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];

void CreateGallisni(s32 x, s32 y, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_GALLISNI);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
  }
}

INCASM("asm/enemy/gallisni_p1_pre_p2_a_a_x.inc");

void Gallisni_Die(struct Enemy* p);

bool8 gallisni_080870bc(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else if ((p->body).status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    Gallisni_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];

// 0x08087118
bool8 gallisni_08087118(struct Enemy* p) {
  if ((p->s).mode[1] != 7) {
    s32 v = *(s32*)((u8*)p + 0xb4);
    if (v == 0) {
      switch ((p->s).mode[3]) {
        case 0:
          if (IsFrozen(&p->s)) {
            if ((p->s).work[0] == 0) {
              (p->s).mode[1] = 1;
              (p->s).mode[2] = v;
            }
            (sUpdates1[(p->s).mode[1]])(p);
            (sUpdates2[(p->s).mode[1]])(p);
            (p->s).mode[3]++;
            UpdateMotionGraphic(&p->s);
            return 1;
          }
          break;
        case 1: {
          u32 fr = IsFrozen(&p->s);
          if (fr) {
            if ((*(u32*)((u8*)p + 0x8c) & 0x20001) == 0x20001) {
              (p->s).mode[3] = v;
            } else {
              return 1;
            }
          } else {
            (p->s).mode[3] = fr;
          }
          break;
        }
      }
    }
  }
  return 0;
}

struct GallisniObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct VFX* elementEffect;
  u8 unk_004[12];
};
static_assert(sizeof(struct GallisniObject) == sizeof(struct Enemy));

static const struct Coord sElementCoord;

void gallisni_080871b4(struct GallisniObject* p) {
  if (p->elementEffect == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    if (((p->body).status & BODY_STATUS_RECOILED)) {
      (p->s).mode[1] = 7;
      (p->s).mode[2] = 0;
    } else {
      p->elementEffect = ApplyElementEffect(0, &p->s, &sElementCoord);
      if (p->elementEffect != NULL) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
    }
  }
}

static const u8 sInitModes[2];
void Gallisni_Update(struct Enemy* p);
void FUN_08086ff0(struct Body* body, struct Coord* r1, struct Coord* r2);

// 0x08087200
void Gallisni_Init(struct Enemy* p) {
  struct Body* b;
  u32 z;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  z = 0;
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= COLLIDABLE;
  b = &p->body;
  InitBody(b, sCollisions, &(p->s).coord, 6);
  b->parent = (struct CollidableEntity*)p;
  b->fn = FUN_08086ff0;
  *(u32*)((u8*)p + 0xb4) = z;
  {
    u8 w = (p->s).work[0];
    if (w == 0) {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      *(u8*)((u8*)p + 0xb8) = w;
    }
  }
  Gallisni_Update(p);
}

void Gallisni_Update(struct Enemy* p) {
  if ((p->s).work[0] == 1) {
    u8 sf = (u8)(gCurStory.s.gameflags[4] & 2);
    if (sf) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      (p->body).status = 0;
      (p->body).prevStatus = 0;
      (p->body).invincibleTime = 0;
      goto despawn;
    }
    if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x8000) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      (p->body).status = sf;
      // do/while needed to match: forces sf into its home register here.
      do {
        (p->body).prevStatus = sf;
      } while (0);
      (p->body).invincibleTime = sf;
    despawn:
      (p->s).flags &= ~COLLIDABLE;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
  }
  if (gallisni_080870bc(p)) {
    return;
  }
  gallisni_080871b4((struct GallisniObject*)p);
  if (gallisni_08087118(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Gallisni_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0808737c(struct Enemy* p) {}


void FUN_08087380(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}


void FUN_080873a0(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[2]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

void FUN_080873fc(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x67, 3));
    UpdateMotionGraphic(&p->s);
    SetDDP(&p->body, &sCollisions[3]);
    (p->s).mode[2]++;
  }
}

void FUN_08087434(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).work[2] = 0x80;
      (p->s).taskCol = 0xf;
      SetMotion(&p->s, MOTION(0x67, 1));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).work[2]--;
      if ((p->s).work[2] == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      if ((s8)(p->s).motion.cmdIdx == 8) {
        SetDDP(&p->body, &sCollisions[1]);
      }
      break;
  }
}

void FUN_080874ac(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x18;
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, MOTION(0x67, 2));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (p->props[4] != 0) p->props[4]--;
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        if (p->props[4] == 0) {
          (p->s).mode[1] = 1;
          (p->s).mode[2] = 0;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/enemy/gallisni_p2_post_a1.inc");

void FUN_080875c8(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      (p->s).unk_coord.x = (p->s).coord.x;
      {
        s32 y = (p->s).coord.y + 0xC00;
        s32 h = (p->s).work[2] >> 1;
        s32 c1 = 1;
        s32 f4;
        h &= c1;
        y -= (h * 3) << 11;
        (p->s).unk_coord.y = y;
        (p->s).d.x = m;
        f4 = (p->s).flags >> 4;
        f4 ^= c1;
        asm("" : "+r"(f4));
        f4 &= c1;
        (p->s).work[3] = f4;
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      register s32 cx asm("r5");
      register s32 ang asm("r3");
      register const s16* st asm("r2");
      register s32 w2a asm("r1");
      register s32 w2v asm("r6");
      s32 t1, cy;
      cx = (p->s).unk_coord.x;
      (p->s).coord.x = cx;
      w2a = (p->s).work[2];
      t1 = 1;
      t1 &= w2a;
      w2v = w2a;
      asm("" : "+r"(w2a));
      if (t1 == 0) {
        register s32 rx asm("r0");
        st = gSineTable;
        ang = *(volatile s32*)((u8*)p + 0x5c);
        rx = cx - st[(u8)(ang >> 8)] * 12;
        (p->s).coord.x = rx;
      } else {
        register s32 rx asm("r0");
        st = gSineTable;
        ang = (p->s).d.x;
        rx = cx + st[(u8)(ang >> 8)] * 12;
        (p->s).coord.x = rx;
      }
      cy = (p->s).unk_coord.y;
      (p->s).coord.y = cy;
      {
        register u32 t2 asm("r0");
        s32 c1b;
        t2 = (u32)w2v << 24;
        asm("" : "+r"(t2));
        t2 >>= 25;
        c1b = 1;
        t2 &= c1b;
        if (t2 == 0) {
          register s32 t3 asm("r0");
          t3 = ang >> 8;
          asm("" : "+r"(t3));
          t3 += 0x40;
          (p->s).coord.y = cy - st[(u8)t3] * 12;
        } else {
          register s32 t3 asm("r0");
          t3 = ang >> 8;
          asm("" : "+r"(t3));
          t3 += 0x40;
          (p->s).coord.y = cy + st[(u8)t3] * 12;
        }
      }
      {
        s32 a2 = (p->s).d.x + 0xC00;
        (p->s).d.x = a2;
        if (a2 > 0x7FFF) {
          s32 z = 0;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = z;
        }
      }
      if ((p->s).d.x <= 0x29FF) {
        SetMotion(&p->s, 0x6704);
      } else if ((p->s).d.x <= 0x53FF) {
        SetMotion(&p->s, 0x6705);
      } else {
        u8 w3 = (p->s).work[3];
        if (w3 != 0) {
          (p->s).flags |= 0x10;
        } else {
          (p->s).flags &= 0xEF;
        }
        {
          s32 v = 1;
          u8* oa;
          s32 sh4, ov, m11;
          v &= w3;
          (p->s).spr.xflip = v;
          oa = (u8*)p + 0x4a;
          sh4 = v << 4;
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          *oa = m11 | sh4;
        }
        SetMotion(&p->s, 0x6704);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_0808772c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 speed = 0x400;

      (p->s).d.x = speed - ((p->s).work[2] & 1) * 0x800;
      (p->s).work[3] = 4;
      SetMotion(&p->s, MOTION(0x67, 0x03));
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).work[3]--;
      if ((p->s).work[3] == 0) {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

void FUN_0808778c(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      (p->s).unk_coord.x = (p->s).coord.x;
      {
        s32 y = (p->s).coord.y + 0xC00;
        s32 h = (p->s).work[2] >> 1;
        s32 c1 = 1;
        s32 f4;
        h &= c1;
        y -= (h * 3) << 11;
        (p->s).unk_coord.y = y;
        (p->s).d.x = m;
        f4 = (p->s).flags >> 4;
        f4 ^= c1;
        asm("" : "+r"(f4));
        f4 &= c1;
        (p->s).work[3] = f4;
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      register s32 cx asm("r5");
      register s32 ang asm("r3");
      register const s16* st asm("r2");
      register s32 w2a asm("r1");
      register s32 w2v asm("r6");
      s32 t1, cy;
      cx = (p->s).unk_coord.x;
      (p->s).coord.x = cx;
      w2a = (p->s).work[2];
      t1 = 1;
      t1 &= w2a;
      w2v = w2a;
      asm("" : "+r"(w2a));
      if (t1 == 0) {
        register s32 rx asm("r0");
        st = gSineTable;
        ang = *(volatile s32*)((u8*)p + 0x5c);
        rx = cx + st[(u8)(ang >> 8)] * 12;
        (p->s).coord.x = rx;
      } else {
        register s32 rx asm("r0");
        st = gSineTable;
        ang = (p->s).d.x;
        rx = cx - st[(u8)(ang >> 8)] * 12;
        (p->s).coord.x = rx;
      }
      cy = (p->s).unk_coord.y;
      (p->s).coord.y = cy;
      {
        register u32 t2 asm("r0");
        s32 c1b;
        t2 = (u32)w2v << 24;
        asm("" : "+r"(t2));
        t2 >>= 25;
        c1b = 1;
        t2 &= c1b;
        if (t2 == 0) {
          register s32 t3 asm("r0");
          t3 = ang >> 8;
          asm("" : "+r"(t3));
          t3 += 0x40;
          (p->s).coord.y = cy - st[(u8)t3] * 12;
        } else {
          register s32 t3 asm("r0");
          t3 = ang >> 8;
          asm("" : "+r"(t3));
          t3 += 0x40;
          (p->s).coord.y = cy + st[(u8)t3] * 12;
        }
      }
      {
        s32 a2 = (p->s).d.x + 0xC00;
        (p->s).d.x = a2;
        if (a2 > 0x7FFF) {
          s32 z = 0;
          (p->s).mode[1] = 3;
          (p->s).mode[2] = z;
        }
      }
      if ((p->s).d.x <= 0x29FF) {
        SetMotion(&p->s, 0x6704);
      } else if ((p->s).d.x <= 0x53FF) {
        SetMotion(&p->s, 0x6705);
      } else {
        u8 w3 = (p->s).work[3];
        if (w3 != 0) {
          (p->s).flags |= 0x10;
        } else {
          (p->s).flags &= 0xEF;
        }
        {
          s32 v = 1;
          u8* oa;
          s32 sh4, ov, m11;
          v &= w3;
          (p->s).spr.xflip = v;
          oa = (u8*)p + 0x4a;
          sh4 = v << 4;
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          *oa = m11 | sh4;
        }
        SetMotion(&p->s, 0x6704);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}



void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
static const motion_t sMotions[4];

// 0x080878f0
void FUN_080878f0(struct Enemy* p) {
  struct Coord c;
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  {
    u8 f = (p->s).flags & ~COLLIDABLE;
    f &= ~DISPLAY;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(16);
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7ffc(&p->s, &c, (motion_t*)sMotions, 3);
  TryDropItem(4, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);
void FUN_080b857c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);

// 0x08087988
void FUN_08087988(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0: {
      u32 d0 = 0;
      u32 dir;
      u32 xf;
      s32 sh;
      s32 z;
      if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
        d0 = 1;
      }
      asm volatile("add %0, %1, #0" : "=&l"(dir) : "l"(d0));
      asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(dir));
      if (dir != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        u32 xf2;
        asm volatile("add %0, %1, #0" : "=&l"(xf2) : "l"(xf));
        ((p->s).spr).xflip = xf2;
        z = 0;
        xf = xf2;
      }
      {
        u8* oa = (u8*)p + 0x4a;
        u32 sh4 = xf << 4;
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      sh = dir << 8;
      (p->s).coord.x -= sh;
      SetMotion(&p->s, MOTION(0x67, 0x07));
      (p->body).status = z;
      (p->body).prevStatus = z;
      (p->body).invincibleTime = z;
      (p->s).flags &= ~COLLIDABLE;
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y;
      ((void (*)(u8, struct Coord*, s32, u32))FUN_080b2b40)(0, &c, 0x200, dir);
      {
        s32 h = 0x60;
        c.x = h - ((dir * 3) << 6);
        c.y = h;
      }
      FUN_080b857c(&p->s, &(p->s).coord, &c, 0x40, (motion_t*)&sMotions[3], 0x18);
      (p->s).d.x = c.x / 2;
      (p->s).d.y = z;
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((u8)--(p->s).work[2] == 0 ||
          (u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
        FUN_080878f0(p);
      }
      break;
  }
}

INCASM("asm/enemy/gallisni_p2_post_c2.inc");

void Gallisni_Init(struct Enemy* p);
void Gallisni_Update(struct Enemy* p);
void Gallisni_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gGallisniRoutine = {
    [ENTITY_INIT] =      Gallisni_Init,
    [ENTITY_UPDATE] =    Gallisni_Update,
    [ENTITY_DIE] =       Gallisni_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_080873a0(struct Enemy* p);
void nop_0808737c(struct Enemy* p);
void FUN_08087380(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    FUN_080873a0,
    nop_0808737c,
    nop_0808737c,
    FUN_08087380,
    FUN_08087380,
    FUN_08087380,
    FUN_08087380,
    nop_0808737c,
};
// clang-format on

void FUN_080873fc(struct Enemy* p);
void FUN_08087434(struct Enemy* p);
void FUN_080874ac(struct Enemy* p);
void FUN_08087518(struct Enemy* p);
void FUN_080875c8(struct Enemy* p);
void FUN_0808772c(struct Enemy* p);
void FUN_0808778c(struct Enemy* p);
void FUN_08087ab0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    FUN_080873fc,
    FUN_08087434,
    FUN_080874ac,
    FUN_08087518,
    FUN_080875c8,
    FUN_0808772c,
    FUN_0808778c,
    FUN_08087ab0,
};
// clang-format on

void FUN_080878f0(struct Enemy* p);
void FUN_08087988(struct Enemy* p);
void FUN_08087ab0(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_080878f0,
    FUN_08087988,
    FUN_08087ab0,
};

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(30), PIXEL(14), PIXEL(58)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(2), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(2), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(2), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
static const u8 sInitModes[2] = {1, 3};

static const motion_t sMotions[4] = {
    MOTION(103, 8),
    MOTION(103, 9),
    MOTION(103, 10),
    MOTION(103, 6),
};
