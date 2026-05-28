#include "cyberelf.h"
#include "entity.h"
#include "global.h"

struct CyberElf7 {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};
static_assert(sizeof(struct CyberElf7) == sizeof(struct Elf));

void Elf7_Init(struct Elf* p);
void Elf7_Update(struct Elf* p);
void Elf7_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf7Routine = {
    [ENTITY_INIT] =      Elf7_Init,
    [ENTITY_UPDATE] =    Elf7_Update,
    [ENTITY_DIE] =       Elf7_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateElf7(struct Zero* z, u8 breed, u8 availability, u8 _) {
  struct CyberElf7* p = (struct CyberElf7*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 7);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    p->player = z;
    (p->s).work[0] = breed;
    (p->s).work[1] = availability;
  }
  return (struct Entity*)p;
}

INCASM("asm/cyberelf/unk_7_p1_p1.inc");

void FUN_080e3f24(struct Elf* p) {
  s32* val = (s32*)((u8*)p + 0xc0);
  *val += 0x30;
  if (*val > 0x27FF) {
    *val = 0x2800;
    *((u8*)p + 0xbc) = 1;
    (p->s).mode[1]++;
  }
}

INCASM("asm/cyberelf/unk_7_p1_p2.inc");

void FUN_080e3f54(struct Elf* p) {
  u32 w = ((struct CyberElf7*)p)->unk_b8[4] - 1;
  ((struct CyberElf7*)p)->unk_b8[4] = w;
  if (w == 0) {
    (p->s).mode[1]++;
  }
}

INCASM("asm/cyberelf/unk_7_p2.inc");

void FUN_080e3f24(struct Elf* p);
void FUN_080e3f54(struct Elf* p);
void FUN_080e3f70(struct Elf* p);

// 0x08371d88
static const ElfFunc sUpdates[3] = {
    (ElfFunc)FUN_080e3f24,
    (ElfFunc)FUN_080e3f54,
    (ElfFunc)FUN_080e3f70,
};

// 0x08371d94
const u8 u8_ARRAY_08371d94[3] = {0, 1, 2};
