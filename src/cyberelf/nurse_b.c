#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "zero.h"

void FUN_080bfce8(struct Coord* c, s32 r1);

struct CyberElfNurseB {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};

struct Elf* CreateNurseBElf(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElfNurseB* p = (struct CyberElfNurseB*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 2);
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

INCASM("asm/cyberelf/nurse_b_p1.inc");

void NurseB_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

bool8 FUN_080e1578(struct Coord* c1, struct Coord* c2, struct Coord* c3, u8* param_4, s16 param_5);

void FUN_080e284c(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y;
  {
    bool8 hit;
    if ((p->s).work[2] != 0) {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0x180);
    } else {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xC0);
    }
    if (hit) {
      (p->s).mode[1] = ((p->s).mode[1] + 1) & 3;
    }
  }
}

void FUN_080e28a8(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y + r.y;
  {
    bool8 hit;
    if ((p->s).work[2] != 0) {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0x180);
    } else {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xC0);
    }
    if (hit) {
      (p->s).mode[1] = ((p->s).mode[1] + 1) & 3;
    }
  }
}

void FUN_080e2920(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y - r.h;
  {
    bool8 hit;
    if ((p->s).work[2] != 0) {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0x180);
    } else {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xC0);
    }
    if (hit) {
      (p->s).mode[1] = ((p->s).mode[1] + 1) & 3;
    }
  }
}


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
