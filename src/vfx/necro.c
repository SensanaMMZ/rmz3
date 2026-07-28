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

INCASM("asm/vfx/necro.inc");

static const u8 sInitModes[5] = {0, 1, 2, 3, 4};
