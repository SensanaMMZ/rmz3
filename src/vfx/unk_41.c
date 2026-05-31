#include "global.h"
#include "vfx.h"

// ヘルバットシルトのレーザーに関係?

extern const VFXFunc PTR_ARRAY_0836eef8[4];

struct VFX* FUN_080bdd74(struct Entity* e, struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Unk41Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8;
  u8 unk_9[7];
};

struct VFX* FUN_080bddcc(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk41Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk41Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

struct VFX* createHellbatElectricBeam(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    ((struct Unk41Props*)(p->props).raw)->unk_8 = a3;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080bde9c(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    ((struct Unk41Props*)(p->props).raw)->unk_8 = a3;
    (p->s).work[1] = 3;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

void VFX41_Update(struct VFX* vfx);

void VFX41_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  ResetDynamicMotion(&p->s);
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
    (p->s).d.x = PIXEL(1) / 2;
  } else {
    SET_XFLIP(p, TRUE);
    (p->s).d.x = -PIXEL(1) / 2;
  }
  (p->s).d.y = 0;

  if ((p->s).work[1] == 0) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else if ((p->s).work[1] == 1) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 0, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else if ((p->s).work[1] == 2) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 2, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else if ((p->s).work[1] == 3) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 3, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  }
  VFX41_Update(p);
}

void VFX41_Update(struct VFX* vfx) {
  (PTR_ARRAY_0836eef8[(vfx->s).mode[1]])(vfx);
}

void VFX41_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_41_post.inc");

void VFX41_Init(struct VFX* vfx);
void VFX41_Update(struct VFX* vfx);
void VFX41_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX41Routine = {
    [ENTITY_INIT] =      VFX41_Init,
    [ENTITY_UPDATE] =    VFX41_Update,
    [ENTITY_DIE] =       VFX41_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080be020(struct VFX* vfx);
void FUN_080be154(struct VFX* vfx);
void FUN_080be230(struct VFX* vfx);
void FUN_080be330(struct VFX* vfx);

const VFXFunc PTR_ARRAY_0836eef8[4] = {
    FUN_080be020,
    FUN_080be154,
    FUN_080be230,
    FUN_080be330,
};

static const s32 s32_ARRAY_ARRAY_0836ef08[8 * 3] = {
    0x00000120, -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000160,
};

static const s32* const PTR_ARRAY_0836ef68[3] = {
    &s32_ARRAY_ARRAY_0836ef08[0],
    &s32_ARRAY_ARRAY_0836ef08[8],
    &s32_ARRAY_ARRAY_0836ef08[16],
};

static const motion_t motion_t_ARRAY_0836ef74[3] = {
    MOTION(DM169_HELLBAT_LASER, 9),
    MOTION(DM169_HELLBAT_LASER, 8),
    MOTION(DM169_HELLBAT_LASER, 7),
};

static const motion_t motion_t_ARRAY_0836ef7a[3] = {
    MOTION(DM169_HELLBAT_LASER, 13),
    MOTION(DM169_HELLBAT_LASER, 12),
    MOTION(DM169_HELLBAT_LASER, 11),
};
