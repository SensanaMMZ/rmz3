#include "cyberelf.h"
#include "global.h"
#include "vfx.h"

// 敵の動きを止めるサイバーエルフ

void SeaOtterElf_Init(struct Elf* p);
void SeaOtterElf_Update(struct Elf* p);
void SeaOtterElf_Die(struct Elf* p);

// clang-format off
const ElfRoutine gSeaOtterElfRoutine = {
    [ENTITY_INIT] =      (ElfFunc)SeaOtterElf_Init,
    [ENTITY_UPDATE] =    (ElfFunc)SeaOtterElf_Update,
    [ENTITY_DIE] =       (ElfFunc)SeaOtterElf_Die,
    [ENTITY_DISAPPEAR] = (ElfFunc)DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

NON_MATCH void MenuExit_SeaOtterElf(struct Elf* e) {
#if MODERN
  struct Elf* linked = *(struct Elf**)e->buffer;
  u8 z = (e->s).work[2];
  u8 fl;
  if (z == 0) {
    if ((e->s).work[3] == linked->buffer[0]) {
      return;
    }
    fl = (e->s).flags & ~DISPLAY;
  } else {
    if ((e->s).work[3] == linked->buffer[1]) {
      return;
    }
    fl = (e->s).flags & ~DISPLAY;
    z = 0;
  }
  fl &= ~FLIPABLE;
  (e->s).flags = fl;
  (e->body).status = z;
  (e->body).prevStatus = z;
  (e->body).invincibleTime = z;
  (e->s).flags &= ~COLLIDABLE;
  SET_ELF_ROUTINE(e, ENTITY_DISAPPEAR);
  if ((e->s).unk_2c != NULL) {
    ((e->s).unk_2c)->flags2 &= 0x7f;
  }
#else
  INCCODE("asm/wip/MenuExit_SeaOtterElf.inc");
#endif
}

#include "zero.h"

struct CyberElfSeaOtter {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};

struct Elf* CreateSeaotterElf(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElfSeaOtter* p = (struct CyberElfSeaOtter*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 9);
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

INCASM("asm/cyberelf/sea_otter_p1_b.inc");

void SeaOtterElf_Die(struct Elf* p) {
  struct Entity* parent = (p->s).unk_2c;
  if (parent != NULL) {
    parent->flags2 &= 0x7f;
  }
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/sea_otter_p2.inc");

void FUN_080e4a3c(struct Elf* p);
void FUN_080e4a88(struct Elf* p);
void FUN_080e4ae8(struct Elf* p);
static void FUN_080e4b58(struct Entity* p);

// 0x08371dc0
static const ElfFunc sUpdates[4] = {
    (ElfFunc)FUN_080e4a3c,
    (ElfFunc)FUN_080e4a88,
    (ElfFunc)FUN_080e4ae8,
    (ElfFunc)FUN_080e4b58,
};

static void FUN_080e4b58(struct Entity* p) {
  if (p->mode[2] == 0) {
    p->mode[3] = 64;
    p->mode[2]++;
  }

  if ((p->d).x > 0x90) {
    p->mode[3]--;
    if (p->mode[3] != 0xFF) {
      return;
    }
  }

  p->mode[1] = 0;
  p->mode[2] = 0;
}
