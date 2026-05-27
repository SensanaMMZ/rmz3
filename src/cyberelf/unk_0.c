#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "zero.h"

struct CyberElf0 {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 unk_b4[8];         // 0xB4
  struct Zero* player;  // 0xBC
  u8 unk_c0[4];         // 0xC0
};
static_assert(sizeof(struct CyberElf0) == sizeof(struct Elf));

void Elf0_Init(struct Elf* p);
void Elf0_Update(struct Elf* p);
void Elf0_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf0Routine = {
    [ENTITY_INIT] =      Elf0_Init,
    [ENTITY_UPDATE] =    Elf0_Update,
    [ENTITY_DIE] =       Elf0_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateElf0(struct Zero* z, u8 breed, u8 availability, u8 _) {
  struct CyberElf0* p = (struct CyberElf0*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 0);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    p->player = z;
    (p->s).work[0] = breed;
    (p->s).work[1] = availability;
  }
  return (struct Entity*)p;
}

INCASM("asm/cyberelf/unk_0_pre.inc");

void Elf0_Die(struct Elf* p) {
  gPause = 0;
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/unk_0_post.inc");

// --------------------------------------------

void FUN_080e1ef8(struct Elf* p);
void FUN_080e1fb8(struct Elf* p);
void FUN_080e1fe8(struct Elf* p);

const ElfFunc gElf0Updates[3] = {
    FUN_080e1ef8,
    FUN_080e1fb8,
    FUN_080e1fe8,
};
