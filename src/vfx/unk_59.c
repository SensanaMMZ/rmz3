#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[3];
void VFX59_Die(struct VFX* p);

struct VFX* FUN_080c26e8(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_059);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk59Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080c273c(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_059);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk59Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk59Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

INCASM("asm/vfx/unk_59_p1_pre_pre_p2_p2.inc");

void VFX59_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX59_Die(vfx);
  } else {
    (sUpdates[(vfx->s).mode[1]])(vfx);
  }
}

INCASM("asm/vfx/unk_59_p1_pre_post.inc");

void VFX59_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_59_p1_post.inc");

void nop_080c28fc(struct VFX* vfx) {}

INCASM("asm/vfx/unk_59_p2.inc");

void VFX59_Init(struct VFX* vfx);
void VFX59_Update(struct VFX* vfx);
void VFX59_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX59Routine = {
    [ENTITY_INIT] =      VFX59_Init,
    [ENTITY_UPDATE] =    VFX59_Update,
    [ENTITY_DIE] =       VFX59_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080c28fc(struct VFX* vfx);
void FUN_080c2900(struct VFX* vfx);
void FUN_080c2a78(struct VFX* vfx);

static const VFXFunc sUpdates[3] = {
    nop_080c28fc,
    FUN_080c2900,
    FUN_080c2a78,
};

static const s32 s32_ARRAY_0836f31c[8 * 3] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

const s32* const PTR_s32_ARRAY_0836f37c[3] = {
    &s32_ARRAY_0836f31c[0],
    &s32_ARRAY_0836f31c[8],
    &s32_ARRAY_0836f31c[16],
};
