#include "entity.h"
#include "global.h"
#include "vfx.h"

// アイスボンの氷のキラキラ

static const u8 sInitModes[4];

void ice_080b996c(struct VFX* p);
void ice_080b9a0c(struct VFX* p);

static const VFXFunc sUpdates[2];

INCASM("asm/vfx/icebon_icedust_p1.inc");

void IcebonIcedust_Update(struct VFX* p) {
  (sUpdates[(p->s).mode[1]])(p);
}

void IcebonIcedust_Die(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/icebon_icedust_p3.inc");

void IcebonIcedust_Init(struct VFX* p);

// clang-format off
const VFXRoutine gIcebonIcedustRoutine = {
    [ENTITY_INIT] =      IcebonIcedust_Init,
    [ENTITY_UPDATE] =    IcebonIcedust_Update,
    [ENTITY_DIE] =       IcebonIcedust_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void ice_080b996c(struct VFX* p);
void ice_080b9a0c(struct VFX* p);

static const VFXFunc sUpdates[2] = {
    ice_080b996c,
    ice_080b9a0c,
};

static const u8 sInitModes[4] = {0, 1, 0, 0};
