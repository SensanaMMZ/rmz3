#include "cyberelf.h"
#include "global.h"

static const ElfFunc sUpdates[2];

void BirdElf_Init(struct Elf* p);
void BirdElf_Update(struct Elf* p);
void BirdElf_Die(struct Elf* p);

// clang-format off
const ElfRoutine gBirdElfRoutine = {
    [ENTITY_INIT] =      BirdElf_Init,
    [ENTITY_UPDATE] =    BirdElf_Update,
    [ENTITY_DIE] =       BirdElf_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

NON_MATCH void FUN_080e58bc(struct Elf* p) {
#if MODERN
  struct Elf* e = *(struct Elf**)p->buffer;
  u8 z = (p->s).work[2];
  u8 fl;
  if (z == 0) {
    if ((p->s).work[3] == e->buffer[0]) {
      return;
    }
    fl = (p->s).flags & ~DISPLAY;
  } else {
    if ((p->s).work[3] == e->buffer[1]) {
      return;
    }
    fl = (p->s).flags & ~DISPLAY;
    z = 0;
  }
  fl &= ~FLIPABLE;
  (p->s).flags = fl;
  (p->body).status = z;
  (p->body).prevStatus = z;
  (p->body).invincibleTime = z;
  (p->s).flags &= ~COLLIDABLE;
  SET_ELF_ROUTINE(p, ENTITY_DISAPPEAR);
#else
  INCCODE("asm/wip/FUN_080e58bc.inc");
#endif
}

void FUN_080e5b74(struct Elf* p);
void FUN_080e5d68(struct Elf* p);

static const ElfFunc sUpdates[2] = {
    FUN_080e5b74,
    FUN_080e5d68,
};

void FUN_080bfce8(struct Coord* c, s32 r1);

INCASM("asm/cyberelf/bird_p1.inc");

void BirdElf_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/bird_p2.inc");
