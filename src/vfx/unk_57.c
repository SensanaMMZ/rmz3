#include "global.h"
#include "vfx.h"

void FUN_080c19b4(struct VFX* p);
void FUN_080c1a3c(struct VFX* p);
void FUN_080c1aec(struct VFX* p);
void FUN_080c1b34(struct VFX* p);

void CreateVFX57(struct Coord* c, u8 a1, u8 a2, s16 dx, s16 dy) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_057);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).d.x = dx;
    (p->s).d.y = dy;
    (p->s).coord = *c;
  }
}

void VFX57_Init(struct VFX* p) {
  if ((p->s).work[0] == 0) {
    FUN_080c19b4(p);
  } else {
    FUN_080c1a3c(p);
  }
}

INCASM("asm/vfx/unk_57_pre_p2.inc");

void VFX57_Update(struct VFX* p) {
  if ((p->s).work[0] == 0) {
    FUN_080c1aec(p);
  } else {
    FUN_080c1b34(p);
  }
}

INCASM("asm/vfx/unk_57_pre_p3.inc");

void VFX57_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_57_post.inc");

void VFX57_Init(struct VFX* vfx);
void VFX57_Update(struct VFX* vfx);
void VFX57_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX57Routine = {
    [ENTITY_INIT] =      VFX57_Init,
    [ENTITY_UPDATE] =    VFX57_Update,
    [ENTITY_DIE] =       VFX57_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on
