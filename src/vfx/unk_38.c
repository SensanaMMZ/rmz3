#include "global.h"
#include "story.h"
#include "vfx.h"

void VFX38_Die(struct VFX* vfx);
extern const VFXFunc PTR_ARRAY_0836ee24[3];

struct VFX* FUN_080bcf68(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_038);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk38Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080bcfbc(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_038);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk38Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk38Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

INCASM("asm/vfx/unk_38_p1_pre_pre_p2_p2.inc");

void VFX38_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX38_Die(vfx);
  } else {
    (PTR_ARRAY_0836ee24[(vfx->s).mode[1]])(vfx);
  }
}

INCASM("asm/vfx/unk_38_p1_pre_post.inc");

void VFX38_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_38_p1_post.inc");

void nop_080bd17c(struct VFX* vfx) {}

INCASM("asm/vfx/unk_38_p2.inc");

void VFX38_Init(struct VFX* vfx);
void VFX38_Update(struct VFX* vfx);
void VFX38_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX38Routine = {
    [ENTITY_INIT] =      VFX38_Init,
    [ENTITY_UPDATE] =    VFX38_Update,
    [ENTITY_DIE] =       VFX38_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void nop_080bd17c(struct VFX* vfx);
void FUN_080bd180(struct VFX* vfx);
void FUN_080bd288(struct VFX* vfx);

const VFXFunc PTR_ARRAY_0836ee24[3] = {
    nop_080bd17c,
    FUN_080bd180,
    FUN_080bd288,
};

static const u8 u8_ARRAY_0836ee30[32 * 3] = {
    0x20, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0xA0, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0x00, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0xA0, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0xA0, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0x00, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0xA0, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0x00, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0xA0, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0xA0, 0xFE, 0xFF, 0xFF,
};

const u8* const PTR_ARRAY_0836ee90[3] = {
    &u8_ARRAY_0836ee30[0],
    &u8_ARRAY_0836ee30[32],
    &u8_ARRAY_0836ee30[64],
};
