#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "vfx.h"

// コロップ、ソロップ(つまり、画面上を飛行するエルフ？)

INCASM("asm/cyberelf/nurse_e_p1.inc");

void NurseE_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/nurse_e_p2.inc");

void NurseE_Init(struct Elf* p);
void NurseE_Update(struct Elf* p);
void NurseE_Die(struct Elf* p);

// clang-format off
const ElfRoutine gNurseERoutine = {
    [ENTITY_INIT] =      NurseE_Init,
    [ENTITY_UPDATE] =    NurseE_Update,
    [ENTITY_DIE] =       NurseE_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on
