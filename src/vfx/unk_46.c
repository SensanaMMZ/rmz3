#include "global.h"
#include "vfx.h"

// トレテスタ・ケルベリアン関連
// - トレテスタ・ケルベリアンが死んだ際のパーティクル
// - コンテナが壊れる時のパーティクル

struct VFX46 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  motion_t unk_74;  // 0xAD01 とか
  u32 unk_78;
  u8 unk_7c;
  u32 pad_80;
};
static_assert(sizeof(struct VFX46) == sizeof(struct VFX));

void VFX46_Init(struct VFX* vfx);
void VFX46_Update(struct VFX* vfx);
void VFX46_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX46Routine = {
    [ENTITY_INIT] =      VFX46_Init,
    [ENTITY_UPDATE] =    VFX46_Update,
    [ENTITY_DIE] =       VFX46_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

// 0x080bec34
struct Entity* FUN_080bec34(struct Entity* e, struct Coord* c, u8 kind) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = kind;
    p->work[1] = 0;
    p->coord.x = c->x;
    p->coord.y = c->y;
    p->unk_28 = (void*)e;
  }
  return p;
}

// 0x080bec8c
struct Entity* FUN_080bec8c(struct Coord* c, u8 kind, motion_t m, u32 n) {
  struct VFX46* p = (struct VFX46*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = kind;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    p->unk_74 = m;
    p->unk_78 = n;
  }
  return (void*)p;
}

// 0x080becf8
struct Entity* FUN_080becf8(struct Coord* c, u8 kind, motion_t m, u32 n) {
  struct VFX46* p = (struct VFX46*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = kind;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    p->unk_74 = m;
    p->unk_78 = n;
  }
  return (void*)p;
}

// 0x080bed5c
struct Entity* FUN_080bed5c(struct Entity* e, struct Coord* c, u8 kind, u8 param_4) {
  struct VFX46* p = (struct VFX46*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = kind;
    p->unk_7c = param_4;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = (void*)e;
  }
  return (void*)p;
}

static const VFXFunc sUpdates[4];

INCASM("asm/vfx/unk_46_pre_pre.inc");

void VFX46_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

INCASM("asm/vfx/unk_46_pre_post.inc");

void VFX46_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_46_post.inc");

void FUN_080bef44(struct VFX* vfx);
void FUN_080bf0a0(struct VFX* vfx);
void FUN_080bf17c(struct VFX* vfx);
void FUN_080bf2f0(struct VFX* vfx);

static const VFXFunc sUpdates[4] = {
    FUN_080bef44,
    FUN_080bf0a0,
    FUN_080bf17c,
    FUN_080bf2f0,
};

// clang-format off
static const s32 s32_ARRAY_ARRAY_0836f02c[5][8] = {
    {0x00000120, -0x00000400, -0x000000B0, -0x00000360, -0x000000B0, -0x00000400, 0x00000120, -0x00000260},
    {-0x000000B0, -0x00000260, -0x000000B0, -0x00000400, 0x00000120, -0x00000260, 0x00000120, -0x00000400},
    {-0x000000B0, -0x00000400, 0x00000120, -0x00000360, 0x00000120, -0x00000400, -0x000000B0, -0x00000360},
    {0x00000160, -0x00000260, -0x000000C0, -0x00000400, 0x00000160, -0x00000400, -0x000000C0, -0x00000260},
    {-0x000000E0, -0x00000400, 0x00000180, -0x00000360, -0x000000E0, -0x00000360, 0x00000180, -0x00000400},
};
// clang-format on

static const s32* const PTR_ARRAY_0836f0cc[5] = {
    s32_ARRAY_ARRAY_0836f02c[0], s32_ARRAY_ARRAY_0836f02c[1], s32_ARRAY_ARRAY_0836f02c[2], s32_ARRAY_ARRAY_0836f02c[3], s32_ARRAY_ARRAY_0836f02c[4],
};
