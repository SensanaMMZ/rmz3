#include "collision.h"
#include "global.h"
#include "solid.h"

INCASM("asm/solid/ciel_mg_obj_pre.inc");

void CielMinigameObj_Die(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/solid/ciel_mg_obj_post.inc");

// シエルのミニゲームで使う様々なオブジェクト

void CielMinigameObj_Init(struct Solid* p);
void CielMinigameObj_Update(struct Solid* p);
void CielMinigameObj_Die(struct Solid* p);

// clang-format off
const SolidRoutine gCielMinigameObjRoutine = {
    [ENTITY_INIT] =      CielMinigameObj_Init,
    [ENTITY_UPDATE] =    CielMinigameObj_Update,
    [ENTITY_DIE] =       CielMinigameObj_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static const s32 s32_ARRAY_083716d0[10] = {
    0x00002800, 0x00006800, 0x00004800, 0x00008800, 0x00002800, 0x00006800, 0x00004800, 0x00008800, 0x00002800, 0x00006800,
};

static const s32 s32_ARRAY_083716f8[10] = {
    0x00002800, 0x00002800, 0x00003800, 0x00003800, 0x00004800, 0x00004800, 0x00005800, 0x00005800, 0x00006800, 0x00006800,
};
