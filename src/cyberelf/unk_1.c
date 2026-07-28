#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "mission.h"
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

INCASM("asm/cyberelf/unk_1_p1_a.inc");

// Three instructions short of retail, which keeps the 0x121 offset in r5 and
// schedules the pool loads ahead of the index math; agbcc folds the address
// chains tighter in every spelling tried.
NON_MATCH void Elf1_Die(struct Elf* p) {
#if MODERN
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  u16* use = (u16*)((u8*)z + 0xb4);
  gPause = FALSE;
  {
    u8* flag = *gUnlockedElfPtr + *((u8*)z + 0x121);
    *flag |= 2;
  }
  use[2]++;
  if (*(u8*)((u8*)gMission.unk_00 + 0x4c) <= 0x62) {
    *(u8*)((u8*)gMission.unk_00 + 0x4c) += 1;
  }
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
#else
  INCCODE("asm/cyberelf/elf1_die.inc");
#endif
}

bool8 FUN_080e1578(struct Coord* c1, struct Coord* c2, struct Coord* c3, u8* param_4, s16 param_5);

// 0x080e2310
void FUN_080e2310(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y;
  if (FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xA0)) {
    (p->s).mode[1]++;
  }
}

void FUN_080e234c(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y + r.y;
  if (FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xA0)) {
    (p->s).mode[1]++;
  }
}

void FUN_080e23a4(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y - r.h;
  if (FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xA0)) {
    (p->s).mode[1]++;
  }
}

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
