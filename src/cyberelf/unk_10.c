#include "cyberelf.h"
#include "global.h"

void FUN_080bfce8(struct Coord* c, s32 r1);

INCASM("asm/cyberelf/unk_10_p1.inc");

void Elf10_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/unk_10_p2.inc");

void Elf10_Init(struct Elf* p);
void Elf10_Update(struct Elf* p);
void Elf10_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf10Routine = {
    [ENTITY_INIT] =      Elf10_Init,
    [ENTITY_UPDATE] =    Elf10_Update,
    [ENTITY_DIE] =       Elf10_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on
