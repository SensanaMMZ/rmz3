#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[1];
void VFX63_Die(struct VFX* p);

struct Unk63Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* CreateVFX63(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_063);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk63Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk63Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

INCASM("asm/vfx/unk_63_pre_pre_p2.inc");

void VFX63_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX63_Die(vfx);
  } else {
    (sUpdates[(vfx->s).mode[1]])(vfx);
  }
}


void VFX63_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_63_post.inc");

void VFX63_Init(struct VFX* vfx);
void VFX63_Update(struct VFX* vfx);
void VFX63_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX63Routine = {
    [ENTITY_INIT] =      VFX63_Init,
    [ENTITY_UPDATE] =    VFX63_Update,
    [ENTITY_DIE] =       VFX63_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c3864(struct VFX* vfx);

static const VFXFunc sUpdates[1] = {
    FUN_080c3864,
};

static const s32 s32_ARRAY_0836f4d8[8 * 3] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

static const s32* const PTR_s32_ARRAY_0836f538[3] = {
    &s32_ARRAY_0836f4d8[0],
    &s32_ARRAY_0836f4d8[8],
    &s32_ARRAY_0836f4d8[16],
};
