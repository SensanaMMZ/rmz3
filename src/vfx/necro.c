#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

/*
  雑魚敵が死んだあと、爆散始まるまでの状態
  雑魚敵が切断死した際の、切断された方の片方
*/

static const VFXFunc sUpdates[5];
static const u8 sInitModes[5];

static void Necro_Init(struct VFX* vfx);
static void Necro_Update(struct VFX* vfx);
static void Necro_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gNecroRoutine = {
    [ENTITY_INIT] =      Necro_Init,
    [ENTITY_UPDATE] =    Necro_Update,
    [ENTITY_DIE] =       Necro_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (vfx != NULL) {
      (vfx->s).taskCol = 1;
      INIT_VFX_ROUTINE(vfx, VFX_NECRO);
      (vfx->s).tileNum = 0;
      (vfx->s).palID = 0;
      (vfx->s).work[0] = 0;
      (vfx->s).work[1] = i;
      (vfx->s).unk_28 = e;
      (vfx->props).necro.motions = motions;
      (vfx->s).coord.x = c->x;
      (vfx->s).coord.y = c->y;
      (vfx->props).necro.unk_04 = 1;
      (vfx->props).necro.unk_05 = 0;
    }
  }
}

void FUN_080b7ffc(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (vfx != NULL) {
      (vfx->s).taskCol = 1;
      INIT_VFX_ROUTINE(vfx, VFX_NECRO);
      (vfx->s).tileNum = 0;
      (vfx->s).palID = 0;
      (vfx->s).work[0] = 0;
      (vfx->s).work[1] = i;
      (vfx->s).unk_28 = e;
      (vfx->props).necro.motions = motions;
      (vfx->s).coord.x = c->x;
      (vfx->s).coord.y = c->y;
      (vfx->props).necro.unk_04 = 0;
      (vfx->props).necro.unk_05 = 0;
    }
  }
}

void FUN_080b8080(struct Enemy* p, struct Coord* c, motion_t* motions, u8 len, u8 r4) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (vfx != NULL) {
      (vfx->s).taskCol = 1;
      INIT_VFX_ROUTINE(vfx, VFX_NECRO);
      (vfx->s).tileNum = 0;
      (vfx->s).palID = 0;
      (vfx->s).work[0] = 0;
      (vfx->s).work[1] = i;
      (vfx->s).unk_28 = &p->s;
      (vfx->props).necro.motions = motions;
      (vfx->s).coord.x = c->x;
      (vfx->s).coord.y = c->y;
      (vfx->s).palID = r4;
      (vfx->props).necro.unk_04 = 1;
      (vfx->props).necro.unk_05 = 0;
    }
  }
}

static void Unused_080b8114(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (vfx != NULL) {
      (vfx->s).taskCol = 1;
      INIT_VFX_ROUTINE(vfx, VFX_NECRO);
      (vfx->s).tileNum = 0;
      (vfx->s).palID = 0;
      (vfx->s).work[0] = 1;
      (vfx->s).work[1] = i;
      (vfx->s).unk_28 = e;
      (vfx->props).necro.motions = motions;
      (vfx->s).coord.x = c->x;
      (vfx->s).coord.y = c->y;
      (vfx->props).necro.unk_04 = 1;
      (vfx->props).necro.unk_05 = 0;
    }
  }
}

void FUN_080b81a0(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (vfx != NULL) {
      (vfx->s).taskCol = 1;
      INIT_VFX_ROUTINE(vfx, VFX_NECRO);
      (vfx->s).tileNum = 0;
      (vfx->s).palID = 0;
      (vfx->s).work[0] = 1;
      (vfx->s).work[1] = i;
      (vfx->s).unk_28 = e;
      (vfx->props).necro.motions = motions;
      (vfx->s).coord.x = c->x;
      (vfx->s).coord.y = c->y;
      (vfx->props).necro.unk_04 = 0;
      (vfx->props).necro.unk_05 = 0;
    }
  }
}

void FUN_080b822c(struct Enemy* p, struct Coord* c, motion_t* motions, u8 len, u8 r4) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (vfx != NULL) {
      (vfx->s).taskCol = 1;
      INIT_VFX_ROUTINE(vfx, VFX_NECRO);
      (vfx->s).tileNum = 0;
      (vfx->s).palID = 0;
      (vfx->s).work[0] = 1;
      (vfx->s).work[1] = i;
      (vfx->s).unk_28 = &p->s;
      (vfx->props).necro.motions = motions;
      (vfx->s).coord.x = c->x;
      (vfx->s).coord.y = c->y;
      (vfx->props).necro.unk_04 = 1;
      (vfx->props).necro.unk_05 = 1;
      (vfx->s).palID = r4;
    }
  }
}

void FUN_080b82c0(struct Entity* e, struct Coord* c, motion_t* motions, u8 len) {
  s32 i;
  for (i = 0; i < len; i++) {
    struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (vfx != NULL) {
      (vfx->s).taskCol = 1;
      INIT_VFX_ROUTINE(vfx, VFX_NECRO);
      (vfx->s).tileNum = 0;
      (vfx->s).palID = 0;
      (vfx->s).work[0] = 2;
      (vfx->s).work[1] = i;
      (vfx->s).unk_28 = e;
      (vfx->props).necro.motions = motions;
      (vfx->s).coord.x = c->x;
      (vfx->s).coord.y = c->y;
      (vfx->props).necro.unk_04 = 1;
      (vfx->props).necro.unk_05 = 0;
    }
  }
}

void FUN_080b834c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = 3;
    (vfx->s).unk_28 = e;
    (vfx->props).necro.motions = motions;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
    (vfx->s).d.x = dc->x;
    (vfx->s).d.y = dc->y;
    (vfx->s).unk_coord.y = y;
    (vfx->s).work[2] = frame;
    (vfx->props).necro.unk_04 = 1;
    (vfx->props).necro.unk_05 = 0;
  }
}

void FUN_080b83d4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = 3;
    (vfx->s).unk_28 = e;
    (vfx->props).necro.motions = motions;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
    (vfx->s).d.x = dc->x;
    (vfx->s).d.y = dc->y;
    (vfx->s).unk_coord.y = y;
    (vfx->s).work[2] = frame;
    (vfx->props).necro.unk_04 = 0;
    (vfx->props).necro.unk_05 = 0;
  }
}

void FUN_080b8454(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame, u8 taskCol) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = 3;
    (vfx->s).unk_28 = e;
    (vfx->props).necro.motions = motions;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
    (vfx->s).d.x = dc->x;
    (vfx->s).d.y = dc->y;
    (vfx->s).unk_coord.y = y;
    (vfx->s).work[2] = frame;
    (vfx->s).taskCol = taskCol;
    (vfx->props).necro.unk_04 = 1;
    (vfx->props).necro.unk_05 = 0;
  }
}

void FUN_080b84f4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = 4;
    (vfx->s).unk_28 = e;
    (vfx->props).necro.motions = motions;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
    (vfx->s).d.x = dc->x;
    (vfx->s).d.y = dc->y;
    (vfx->s).unk_coord.y = y;
    (vfx->s).work[2] = frame;
    (vfx->props).necro.unk_04 = 1;
    (vfx->props).necro.unk_05 = 0;
  }
}

void FUN_080b857c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = 4;
    (vfx->s).unk_28 = e;
    (vfx->props).necro.motions = motions;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
    (vfx->s).d.x = dc->x;
    (vfx->s).d.y = dc->y;
    (vfx->s).unk_coord.y = y;
    (vfx->s).work[2] = frame;
    (vfx->props).necro.unk_04 = 0;
    (vfx->props).necro.unk_05 = 0;
  }
}

void FUN_080b85fc(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame, u8 taskCol) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = 4;
    (vfx->s).unk_28 = e;
    (vfx->props).necro.motions = motions;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
    (vfx->s).d.x = dc->x;
    (vfx->s).d.y = dc->y;
    (vfx->s).unk_coord.y = y;
    (vfx->s).work[2] = frame;
    (vfx->s).taskCol = taskCol;
    (vfx->props).necro.unk_04 = 1;
    (vfx->props).necro.unk_05 = 0;
  }
}

void FUN_080b869c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame, u8 taskCol, u8 palID) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = 4;
    (vfx->s).unk_28 = e;
    (vfx->props).necro.motions = motions;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
    (vfx->s).d.x = dc->x;
    (vfx->s).d.y = dc->y;
    (vfx->s).unk_coord.y = y;
    (vfx->s).work[2] = frame;
    (vfx->s).taskCol = taskCol;
    (vfx->s).palID = palID;
    (vfx->props).necro.unk_04 = 1;
    (vfx->props).necro.unk_05 = 0;
  }
}

// --------------------------------------------

static void Necro_Init(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
  (vfx->s).mode[1] = sInitModes[(vfx->s).work[0]];
  (vfx->s).flags |= FLIPABLE;
  (vfx->s).flags |= DISPLAY;
  InitNonAffineMotion(&vfx->s);
  Necro_Update(vfx);
}

// --------------------------------------------

void FUN_080b8804(struct VFX* p);
void FUN_080b8984(struct VFX* p);
void FUN_080b8af8(struct VFX* p);
void FUN_080b8c74(struct VFX* p);
void FUN_080b8d4c(struct VFX* p);

static void Necro_Update(struct VFX* vfx) {
  // clang-format off
  static const VFXFunc sUpdates[5] = {
      FUN_080b8804,
      FUN_080b8984,
      FUN_080b8af8,
      FUN_080b8c74,
      FUN_080b8d4c,
  };
  // clang-format on

  if (IS_METTAUR && (vfx->props).necro.unk_04 != 0) {
    (vfx->s).flags &= ~DISPLAY;
    (vfx->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
    return;
  }
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

// --------------------------------------------

static void Necro_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
  return;
}

// --------------------------------------------

void FUN_080b8804(struct VFX* p) {
  bool8 xflip = (((p->s).unk_28)->flags & X_FLIP) != 0;
  bool8 yflip = (((p->s).unk_28)->flags & Y_FLIP) != 0;
  u32 idx = (p->s).work[1];
  switch ((p->s).mode[2]) {
    case 0: {
      (p->s).flags |= DISPLAY;
      SET_XFLIP(p, xflip);
      SET_YFLIP(p, yflip);
      SetMotion(&p->s, (p->props).necro.motions[idx]);
      if (xflip) idx = 2 - idx;
      ((p->s).d).x = PIXEL(idx - 1) + (RANDOM(RNG_0202f388) & 0x1FF) - PIXEL(1);
      ((p->s).d).y = -(RANDOM(RNG_0202f388) & 0x1FF) - PIXEL(2);
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      (p->s).work[2]++;
      if ((p->s).work[2] & 1) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
      ((p->s).coord).x += ((p->s).d).x;
      ((p->s).coord).y += ((p->s).d).y;
      ((p->s).d).y += PIXEL(1) / 4;
      FUN_0801779c(&p->s);
      if (FUN_080098a4(((p->s).coord).x, ((p->s).coord).y) && ((p->s).d).y > 0) {
        if ((p->props).necro.unk_05 == 0) {
          CreateSmoke(3, &(p->s).coord);
        } else {
          CreateSmoke(2, &(p->s).coord);
        }
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
    }
  }
}

void FUN_080b8984(struct VFX* p) {
  u32 pf = (u32)(((p->s).unk_28)->flags) << 24;
  u32 xf = (pf >> 0x1c) & 1;
  u32 yf = (pf >> 0x1d) & 1;
  u32 w1 = (p->s).work[1];
  switch ((p->s).mode[2]) {
    case 0: {
      register u32 xfc asm("r1");
      u32 yfc;
      u8* oa;
      {
        u32 fl = (p->s).flags;
        register u32 t asm("r0");
        register u32 z asm("r3");
        u32 v;
        t = 1;
        asm volatile("" : "+r"(t));
        z = 0;
        asm volatile("" :: "r"(z));
        v = t;
        asm volatile("" : "+r"(v));
        v |= fl;
        (p->s).flags = v;
        xfc = xf;
        if (xf != 0) {
          v |= 0x10;
        } else {
          v &= 0xEF;
        }
        (p->s).flags = v;
      }
      *((u8*)p + 0x4c) = xfc;
      {
        u8* oa0 = (u8*)p + 0x4a;
        u32 sh4 = xfc << 4;
        s32 ov, m11;
        ov = *oa0;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa0 = m11;
        yfc = yf;
        oa = oa0;
      }
      if (yf != 0) {
        (p->s).flags |= 0x20;
      } else {
        (p->s).flags &= 0xDF;
      }
      {
        register u32 yfc2 asm("r1");
        yfc2 = yfc;
        asm volatile("" : "+r"(yfc2));
        {
          register u8* a4d asm("r2");
          a4d = (u8*)p + 0x4d;
          *a4d = yfc2;
        }
        {
        u32 sh5 = yfc2 << 5;
        s32 ov2, m21;
        ov2 = *oa;
        m21 = -0x21;
        m21 &= ov2;
        m21 |= sh5;
        *oa = m21;
        }
      }
      SetMotion(&p->s, ((p->props).necro.motions)[w1]);
      if (xf != 0) {
        w1 = 2 - w1;
      }
      {
        s32 b8 = (w1 - 1) << 8;
        (p->s).d.x = b8 + (RANDOM(RNG_0202f388) & 0x1FF) - 0x100;
        (p->s).d.y = -0x200 - (RANDOM(RNG_0202f388) & 0x100);
      }
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 t = (p->s).work[2] + 1;
      (p->s).work[2] = t;
      if (t & 1) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
      ((p->s).coord).x += ((p->s).d).x;
      ((p->s).coord).y += ((p->s).d).y;
      ((p->s).d).y += 0x20;
      FUN_0801779c(&p->s);
      if (FUN_080098a4(((p->s).coord).x, ((p->s).coord).y)) {
        if ((p->props).necro.unk_05 == 0) {
          CreateSmoke(3, &(p->s).coord);
        } else {
          CreateSmoke(2, &(p->s).coord);
        }
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
    }
  }
}

// 0x080B8AF8
void FUN_080b8af8(struct VFX* p) {
  u32 pf = (u32)(((p->s).unk_28)->flags) << 24;
  u32 xf = (pf >> 0x1c) & 1;
  u32 yf = (pf >> 0x1d) & 1;
  u32 w1 = (p->s).work[1];
  switch ((p->s).mode[2]) {
    case 0: {
      register u32 xfc asm("r1");
      u32 yfc;
      u8* oa;
      {
        u32 fl = (p->s).flags;
        register u32 t asm("r0");
        register u32 z asm("r3");
        u32 v;
        t = 1;
        asm volatile("" : "+r"(t));
        z = 0;
        asm volatile("" :: "r"(z));
        v = t;
        asm volatile("" : "+r"(v));
        v |= fl;
        (p->s).flags = v;
        xfc = xf;
        if (xf != 0) {
          v |= 0x10;
        } else {
          v &= 0xEF;
        }
        (p->s).flags = v;
      }
      *((u8*)p + 0x4c) = xfc;
      {
        u8* oa0 = (u8*)p + 0x4a;
        u32 sh4 = xfc << 4;
        s32 ov, m11;
        ov = *oa0;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa0 = m11;
        yfc = yf;
        oa = oa0;
      }
      if (yf != 0) {
        (p->s).flags |= 0x20;
      } else {
        (p->s).flags &= 0xDF;
      }
      {
        register u32 yfc2 asm("r1");
        yfc2 = yfc;
        asm volatile("" : "+r"(yfc2));
        {
          register u8* a4d asm("r2");
          a4d = (u8*)p + 0x4d;
          *a4d = yfc2;
        }
        {
        u32 sh5 = yfc2 << 5;
        s32 ov2, m21;
        ov2 = *oa;
        m21 = -0x21;
        m21 &= ov2;
        m21 |= sh5;
        *oa = m21;
        }
      }
      SetMotion(&p->s, ((p->props).necro.motions)[w1]);
      if (xf != 0) {
        w1 = 2 - w1;
      }
      {
        s32 b8 = (w1 - 1) << 8;
        (p->s).d.x = b8 + (RANDOM(RNG_0202f388) & 0x1FF) - 0x100;
        (p->s).d.y = -0x200 - (RANDOM(RNG_0202f388) & 0x100);
      }
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      s32 t = (p->s).work[2] + 1;
      (p->s).work[2] = t;
      if (t & 1) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
      ((p->s).coord).x += ((p->s).d).x;
      {
        register s32 cy asm("r0");
        register s32 dy asm("r1");
        cy = ((p->s).coord).y;
        dy = ((p->s).d).y;
        cy += dy;
        ((p->s).coord).y = cy;
        dy += 0x40;
        ((p->s).d).y = dy;
      }
      FUN_0801779c(&p->s);
      if ((p->s).work[2] > 0x18 && FUN_080098a4(((p->s).coord).x, ((p->s).coord).y)) {
        if ((p->props).necro.unk_05 == 0) {
          CreateSmoke(3, &(p->s).coord);
        } else {
          CreateSmoke(2, &(p->s).coord);
        }
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
    }
  }
}

// 0x080B8C74
void FUN_080b8c74(struct VFX* p) {
  register s32 xf asm("r3");
  register s32 yf asm("r5");
  {
    register s32 t asm("r0");
    register s32 one asm("r1");
    t = ((p->s).unk_28)->flags;
    t <<= 24;
    xf = (u32)t >> 28;
    one = 1;
    xf &= one;
    yf = (u32)t >> 29;
    yf &= one;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register u8 f asm("r2");
      register s32 z6 asm("r6");
      register s32 v asm("r1");
      {
        register u8 fl asm("r1");
        register s32 one2 asm("r0");
        fl = (p->s).flags;
        one2 = 1;
        z6 = 0;
        asm volatile("" : "+r"(z6));
        asm volatile("add %0, %1, #0" : "=&l"(f) : "l"(one2));
        f |= fl;
        (p->s).flags = f;
      }
      asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(xf));
      if (v != 0) {
        register s32 k asm("r0");
        k = 0x10;
        f |= k;
      } else {
        register s32 k2 asm("r0");
        k2 = 0xEF;
        f &= k2;
      }
      (p->s).flags = f;
      *((u8*)p + 0x4c) = v;
      {
        register u8* oa asm("r2");
        s32 sh4, ov, m11;
        oa = (u8*)p + 0x4a;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
        asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(yf));
        asm volatile("add %0, %1, #0" : "=&l"(yf) : "l"(oa));
      }
      if (xf != 0) {
        register u8 g asm("r0");
        register s32 k3 asm("r1");
        g = (p->s).flags;
        k3 = 0x20;
        g |= k3;
        (p->s).flags = g;
      } else {
        register u8 h asm("r1");
        register u8 g2 asm("r0");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g2 = 0xDF;
        g2 &= h;
        (p->s).flags = g2;
      }
      {
        register s32 v2 asm("r1");
        register u8* oa2 asm("r2");
        s32 sh5, ov2, m21;
        asm volatile("add %0, %1, #0" : "=&l"(v2) : "l"(xf));
        oa2 = (u8*)p + 0x4d;
        *oa2 = v2;
        sh5 = v2 << 5;
        ov2 = *(u8*)yf;
        m21 = -0x21;
        m21 &= ov2;
        *(u8*)yf = m21 | sh5;
      }
      asm volatile("" ::"r"(z6));
      SetMotion(&p->s, **(u16**)((u8*)p + 0x74));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t;
      (p->s).coord.x += (p->s).d.x;
      {
        register s32 dy asm("r1");
        register s32 cy asm("r0");
        cy = (p->s).coord.y;
        dy = (p->s).d.y;
        cy += dy;
        (p->s).coord.y = cy;
        {
          register s32 uy asm("r0");
          uy = (p->s).unk_coord.y;
          dy += uy;
          (p->s).d.y = dy;
        }
      }
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t <<= 24;
      if (t == 0) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080B8D4C
void FUN_080b8d4c(struct VFX* p) {
  register s32 xf asm("r3");
  register s32 yf asm("r5");
  {
    register s32 t asm("r0");
    register s32 one asm("r1");
    t = ((p->s).unk_28)->flags;
    t <<= 24;
    xf = (u32)t >> 28;
    one = 1;
    xf &= one;
    yf = (u32)t >> 29;
    yf &= one;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register u8 f asm("r2");
      register s32 z6 asm("r6");
      register s32 v asm("r1");
      {
        register u8 fl asm("r1");
        register s32 one2 asm("r0");
        fl = (p->s).flags;
        one2 = 1;
        z6 = 0;
        asm volatile("" : "+r"(z6));
        asm volatile("add %0, %1, #0" : "=&l"(f) : "l"(one2));
        f |= fl;
        (p->s).flags = f;
      }
      asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(xf));
      if (v != 0) {
        register s32 k asm("r0");
        k = 0x10;
        f |= k;
      } else {
        register s32 k2 asm("r0");
        k2 = 0xEF;
        f &= k2;
      }
      (p->s).flags = f;
      *((u8*)p + 0x4c) = v;
      {
        register u8* oa asm("r2");
        s32 sh4, ov, m11;
        oa = (u8*)p + 0x4a;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
        asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(yf));
        asm volatile("add %0, %1, #0" : "=&l"(yf) : "l"(oa));
      }
      if (xf != 0) {
        register u8 g asm("r0");
        register s32 k3 asm("r1");
        g = (p->s).flags;
        k3 = 0x20;
        g |= k3;
        (p->s).flags = g;
      } else {
        register u8 h asm("r1");
        register u8 g2 asm("r0");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g2 = 0xDF;
        g2 &= h;
        (p->s).flags = g2;
      }
      {
        register s32 v2 asm("r1");
        register u8* oa2 asm("r2");
        s32 sh5, ov2, m21;
        asm volatile("add %0, %1, #0" : "=&l"(v2) : "l"(xf));
        oa2 = (u8*)p + 0x4d;
        *oa2 = v2;
        sh5 = v2 << 5;
        ov2 = *(u8*)yf;
        m21 = -0x21;
        m21 &= ov2;
        *(u8*)yf = m21 | sh5;
      }
      asm volatile("" ::"r"(z6));
      SetMotion(&p->s, **(u16**)((u8*)p + 0x74));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 cx, cy, t;
      {
        register s32 a asm("r1");
        register s32 b asm("r0");
        a = (p->s).coord.x;
        b = (p->s).d.x;
        cx = a + b;
        (p->s).coord.x = cx;
        a = (p->s).coord.y;
        b = (p->s).d.y;
        cy = a + b;
        (p->s).coord.y = cy;
        a = (p->s).unk_coord.y;
        b += a;
        (p->s).d.y = b;
      }
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t <<= 24;
      if (t != 0) {
        if (FUN_080098a4(cx, cy) == 0) {
          goto skip;
        }
      }
      CreateSmoke(1, &(p->s).coord);
      SET_VFX_ROUTINE(p, ENTITY_DIE);
    skip:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

static const u8 sInitModes[5] = {0, 1, 2, 3, 4};
