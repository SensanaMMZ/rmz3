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

INCASM("asm/vfx/unk_69_p1_pre_p1.inc");

void Ghost69_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = (p->s).work[0];
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  Ghost69_Update(p);
}

INCASM("asm/vfx/unk_69_p1_pre_p2.inc");

void Ghost69_Update(struct VFX* p) {
  (sGhost69Updates[(p->s).mode[1]])(p);
}

INCASM("asm/vfx/unk_69_p1_post_pre.inc");

void Ghost69_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_69_p1_post_post.inc");

void nop_080c552c(struct VFX* p) {}

INCASM("asm/vfx/unk_69_p2.inc");

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
