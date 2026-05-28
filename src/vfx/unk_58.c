#include "global.h"
#include "vfx.h"

static const VFXFunc sUpdates[9];

struct VFX* FUN_080c1b98(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080c1bec(struct Coord* c, u8 mode, struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c1c44(struct Coord* c) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk58Props { u8 unk_0[12]; u16 unk_c; u16 unk_e; };

struct VFX* FUN_080c1c94(struct Coord* c, u8 a1, u16 a2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk58Props*)(p->props).raw)->unk_c = a2;
  }
  return p;
}

struct VFX* FUN_080c1cf4(struct Coord* c, u8 a1, u16 a2, u16 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 7;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk58Props*)(p->props).raw)->unk_e = a2;
    ((struct Unk58Props*)(p->props).raw)->unk_c = a3;
  }
  return p;
}

INCASM("asm/vfx/unk_58_pre_pre_p4_post.inc");

void VFX58_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

INCASM("asm/vfx/unk_58_pre_post.inc");

void VFX58_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_58_post_p1.inc");

void FUN_080c2364(struct VFX* p) {
  if (--(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/vfx/unk_58_post_p2.inc");

void VFX58_Init(struct VFX* vfx);
void VFX58_Update(struct VFX* vfx);
void VFX58_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX58Routine = {
    [ENTITY_INIT] =      VFX58_Init,
    [ENTITY_UPDATE] =    VFX58_Update,
    [ENTITY_DIE] =       VFX58_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c2124(struct VFX* vfx);
void FUN_080c216c(struct VFX* vfx);
void FUN_080c21c0(struct VFX* vfx);
void FUN_080c2294(struct VFX* vfx);
void FUN_080c2364(struct VFX* vfx);
void FUN_080c2390(struct VFX* vfx);
void FUN_080c248c(struct VFX* vfx);
void FUN_080c2500(struct VFX* vfx);
void FUN_080c25f4(struct VFX* vfx);

// clang-format off
static const VFXFunc sUpdates[9] = {
    FUN_080c2124,
    FUN_080c216c,
    FUN_080c21c0,
    FUN_080c2294,
    FUN_080c2364,
    FUN_080c2390,
    FUN_080c248c,
    FUN_080c2500,
    FUN_080c25f4,
};
// clang-format on

static const s32 s32_ARRAY_0836f290[8 * 3] = {
    0x000002C0, -0x00000300, -0x00000220, -0x00000260, -0x00000220, -0x00000300, 0x000002C0, -0x00000260, -0x00000100, -0x000001F0, -0x00000200, -0x00000280, 0x00000160, -0x000001F0, 0x00000260, -0x00000280, -0x000000B0, -0x00000340, 0x00000120, -0x000002A0, 0x00000120, -0x00000340, -0x000000B0, -0x000002A0,
};

const s32* const PTR_s32_ARRAY_0836f2f0[3] = {
    &s32_ARRAY_0836f290[0],
    &s32_ARRAY_0836f290[8],
    &s32_ARRAY_0836f290[16],
};
