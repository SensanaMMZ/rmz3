#include "global.h"
#include "vfx.h"

void Ghost69_Init(struct VFX* p);
void Ghost69_Update(struct VFX* p);
void Ghost69_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost69Routine = {
    [ENTITY_INIT] =      Ghost69_Init,
    [ENTITY_UPDATE] =    Ghost69_Update,
    [ENTITY_DIE] =       Ghost69_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080c4e58(struct Coord* c, void* _, struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c4eac(struct Entity* e, struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[1] = n;
    (p->s).unk_coord.x = c->x;
    (p->s).unk_coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c4f04(struct Entity* e, struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c4f60(struct Entity* e, struct Coord* c1, struct Coord* c2, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = n;
    (p->s).unk_coord.x = c1->x;
    (p->s).unk_coord.y = c1->y;
    (p->props).unk69.c.x = c2->x;
    (p->props).unk69.c.y = c2->y;
    (p->s).unk_28 = e;
  }
  return p;
}

extern const VFXFunc sGhost69Updates[7];

struct VFX* FUN_080c4fc8(struct Coord* c) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk69PropsV2 { u8 unk_0[12]; u16 unk_c; u16 unk_e; };

struct VFX* FUN_080c5018(struct Coord* c, u8 a1, u16 a2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk69PropsV2*)(p->props).raw)->unk_c = a2;
  }
  return p;
}

struct VFX* FUN_080c5078(struct Coord* c, u8 a1, u16 a2, u16 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk69PropsV2*)(p->props).raw)->unk_e = a2;
    ((struct Unk69PropsV2*)(p->props).raw)->unk_c = a3;
  }
  return p;
}

void Ghost69_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = (p->s).work[0];
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  Ghost69_Update(p);
}


void Ghost69_Update(struct VFX* p) {
  (sGhost69Updates[(p->s).mode[1]])(p);
}


void Ghost69_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_69_p1_post_post.inc");

void FUN_080c5328(struct VFX* p) {
  u8 md;
  if (((p->s).unk_28)->mode[0] > 1) {
    goto die;
  }
  md = (p->s).mode[2];
  switch (md) {
    case 0:
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      {
        u8 f = DISPLAY | (p->s).flags;
        f |= FLIPABLE;
        (p->s).flags = f;
      }
      (p->props).unk69.c.x = md;
      (p->props).unk69.c.y = md;
      SetMotion(&p->s, MOTION(0xB9, 0x03));
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).coord.x = ((p->s).unk_28)->coord.x + (p->props).unk69.c.x;
      (p->s).coord.y = ((p->s).unk_28)->coord.y + (p->props).unk69.c.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
    die:
      SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

INCASM("asm/vfx/unk_69_p1_post_post_b.inc");

void nop_080c552c(struct VFX* p) {}

INCASM("asm/vfx/unk_69_p2_a.inc");

void FUN_080c55bc(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x50;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

// --------------------------------------------

void FUN_080c5144(struct VFX* p);
void FUN_080c521c(struct VFX* p);
void FUN_080c5328(struct VFX* p);
void FUN_080c53b8(struct VFX* p);
void nop_080c552c(struct VFX* p);
void FUN_080c5530(struct VFX* p);
void FUN_080c55bc(struct VFX* p);

// clang-format off
const VFXFunc sGhost69Updates[7] = {
    FUN_080c5144,
    FUN_080c521c,
    FUN_080c5328,
    FUN_080c53b8,
    nop_080c552c,
    FUN_080c5530,
    FUN_080c55bc,
};
// clang-format on
