#include "cyberelf.h"
#include "entity.h"
#include "global.h"

void Elf5_Die(struct Elf* p);

struct CyberElf5 {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Entity* player;  // 0xB4
  u8 unk_b8[12];          // 0xB8
};
static_assert(sizeof(struct CyberElf5) == sizeof(struct Elf));

struct Elf* CreateElf5(struct Entity* e, u8 a1, u8 a2) {
  struct CyberElf5* p = (struct CyberElf5*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 5);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    p->player = e;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
  }
  return (struct Elf*)p;
}

INCASM("asm/cyberelf/unk_5_p1_p2.inc");

void Elf5_Update(struct Elf* p) {
  UpdateMotionGraphic(&p->s);
  SET_ELF_ROUTINE(p, ENTITY_DIE);
  Elf5_Die(p);
}

INCASM("asm/cyberelf/unk_5_p2.inc");

void Elf5_Init(struct Elf* p);
void Elf5_Update(struct Elf* p);
void Elf5_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf5Routine = {
    [ENTITY_INIT] =      Elf5_Init,
    [ENTITY_UPDATE] =    Elf5_Update,
    [ENTITY_DIE] =       Elf5_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on
