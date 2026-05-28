#include "cyberelf.h"
#include "entity.h"
#include "global.h"

void FUN_080bfce8(struct Coord* c, s32 r1);

INCASM("asm/cyberelf/nurse_b_p1.inc");

void NurseB_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/nurse_b_p2.inc");

// ------------------------------------------------------------------------------------------------------------------------------------

void NurseB_Init(struct Elf* p);
void NurseB_Update(struct Elf* p);
void NurseB_Die(struct Elf* p);

// clang-format off
const ElfRoutine gNurseBRoutine = {
    [ENTITY_INIT] =      NurseB_Init,
    [ENTITY_UPDATE] =    NurseB_Update,
    [ENTITY_DIE] =       NurseB_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080e284c(struct Elf* p);
void FUN_080e28a8(struct Elf* p);
void FUN_080e2920(struct Elf* p);
void FUN_080e28a8(struct Elf* p);

const ElfFunc sNurseBUpdates[4] = {
    FUN_080e284c,
    FUN_080e28a8,
    FUN_080e2920,
    FUN_080e28a8,
};
