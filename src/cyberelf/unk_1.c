#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "zero.h"

struct Zero;

struct CyberElf1 {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;    // 0xB4
  u8 unk_b8;              // 0xB8
  u8 unk_b9;              // 0xB9
  struct Coord coord_bc;  // 0xBC
};
static_assert(sizeof(struct CyberElf1) == sizeof(struct Elf));

void Elf1_Init(struct CyberElf1* p);
void Elf1_Update(struct CyberElf1* p);
void Elf1_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf1Routine = {
    [ENTITY_INIT] =      (ElfFunc)Elf1_Init,
    [ENTITY_UPDATE] =    (ElfFunc)Elf1_Update,
    [ENTITY_DIE] =       Elf1_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Entity* CreateElf1(struct Zero* p, u8 breed, u8 availability, u8 _) {
  struct CyberElf1* e = (struct CyberElf1*)AllocEntityFirst(gElfHeaderPtr);
  if (e != NULL) {
    (e->s).taskCol = 16;
    INIT_ELF_ROUTINE(e, 1);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    e->player = p;
    (e->s).work[0] = breed;
    (e->s).work[1] = availability;
  }
  return (struct Entity*)e;
}

void Elf1_Init(struct CyberElf1* p) {
  struct Zero* z = p->player;
  struct Rect r = gZeroRanges[z->posture];
  gPause = TRUE;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, GetElfMotion(0));
  (p->s).spr.xflip = FALSE;
  (p->s).spr.oam.xflip = FALSE;
  (p->s).flags &= ~X_FLIP;
  (p->s).coord.x = (z->s).coord.x + r.x;
  (p->s).coord.y = (z->s).coord.y + r.y;
  (&p->coord_bc)->x = 0;
  (&p->coord_bc)->y = 0;
  p->unk_b8 = 0;
  p->unk_b9 = 32;
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  Elf1_Update(p);
}

INCASM("asm/cyberelf/unk_1_p1.inc");

void FUN_080e23fc(struct Elf* p) {
  if (((struct CyberElf1*)p)->unk_b8 == 0) {
    (p->s).mode[1]++;
  }
}

struct Entity* FUN_080bfce8(struct Coord* c, s32 r1);

void FUN_080e2414(struct Elf* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).unk_2c = FUN_080bfce8(&(p->s).coord, 0);
    (p->s).flags &= ~DISPLAY;
    (p->s).mode[2]++;
  }
  if (((p->s).unk_2c)->mode[0] > 1) {
    (p->s).mode[1]++;
  }
}

INCASM("asm/cyberelf/unk_1_p2_p2.inc");

// --------------------------------------------

void FUN_080e2310(struct Elf* p);
void FUN_080e234c(struct Elf* p);
void FUN_080e23a4(struct Elf* p);
void FUN_080e23fc(struct Elf* p);
void FUN_080e2414(struct Elf* p);
void FUN_080e244c(struct Elf* p);

// clang-format off
// 0x08371ca0
const ElfFunc sElf1Updates[6] = {
    FUN_080e2310,
    FUN_080e234c,
    FUN_080e23a4,
    FUN_080e23fc,
    FUN_080e2414,
    FUN_080e244c,
};
// clang-format on
