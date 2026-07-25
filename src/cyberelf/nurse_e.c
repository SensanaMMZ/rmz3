#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "vfx.h"

// コロップ、ソロップ(つまり、画面上を飛行するエルフ？)

#include "zero.h"

struct CyberElfNurseE {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};

struct Elf* CreateNurseEElf(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElfNurseE* p = (struct CyberElfNurseE*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 4);
    (p->s).tileNum = 0, (p->s).palID = 0;
    p->player = z;
    (p->s).work[0] = breed, (p->s).work[1] = availability, (p->s).work[2] = satelite_slot;
    if (satelite_slot == 0) {
      (p->s).work[3] = SATELITE_1;
    } else {
      (p->s).work[3] = SATELITE_2;
    }
  }
  return (struct Elf*)p;
}

INCASM("asm/cyberelf/nurse_e_p1_b.inc");

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
