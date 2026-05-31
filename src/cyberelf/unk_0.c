#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "stagerun.h"
#include "trig.h"
#include "zero.h"

struct CyberElf0 {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Coord coord_b4;  // 0xB4
  struct Zero* player;    // 0xBC
  u8 unk_c0;              // 0xC0
  u8 unk_c1;              // 0xC1
};
static_assert(sizeof(struct CyberElf0) == sizeof(struct Elf));

void Elf0_Init(struct CyberElf0* p);
void Elf0_Update(struct CyberElf0* p);
void Elf0_Die(struct Elf* p);

extern const ElfFunc gElf0Updates[3];

// clang-format off
const ElfRoutine gElf0Routine = {
    [ENTITY_INIT] =      (ElfFunc)Elf0_Init,
    [ENTITY_UPDATE] =    (ElfFunc)Elf0_Update,
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

void Elf0_Init(struct CyberElf0* p) {
  struct Zero* z = p->player;
  struct Rect r = gZeroRanges[z->posture];
  gPause = TRUE;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, GetElfMotion(0));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.xflip = FALSE;
  (p->s).spr.oam.xflip = FALSE;
  (p->s).flags &= ~X_FLIP;
  (p->s).spr.oam.priority = 0;
  (p->s).coord.x = (z->s).coord.x + r.x;
  (p->s).coord.y = (z->s).coord.y + r.y;
  (p->coord_b4).x = PIXEL(10);
  (p->coord_b4).y = PIXEL(80);
  if ((p->s).work[0] == 0) {
    (p->coord_b4).y -= PIXEL(getMaxHP1x(z) * 2);
  } else {
    (p->coord_b4).y -= PIXEL(getMaxHP1x(z));
  }
  (p->s).unk_coord.x = PIXEL(120) - (&gStageRun.vm.camera.viewport)->x + (p->s).coord.x;
  (p->s).unk_coord.y = PIXEL(80) - (&gStageRun.vm.camera.viewport)->y + (p->s).coord.y;
  p->unk_c1 = 32;
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  Elf0_Update(p);
}

void Elf0_Update(struct CyberElf0* p) {
  u8 idx;
  UpdateMotionGraphic(&p->s);
  (gElf0Updates[(p->s).mode[1]])((struct Elf*)p);
  if ((p->s).mode[0] == ENTITY_UPDATE) {
    (p->s).coord.x = (p->s).unk_coord.x - PIXEL(120);
    (p->s).coord.x += (&gStageRun.vm.camera.viewport)->x;
    (p->s).coord.y = (p->s).unk_coord.y - PIXEL(80);
    (p->s).coord.y += (&gStageRun.vm.camera.viewport)->y;
    idx = p->unk_c0;
    (p->s).coord.y += SIN(idx << 3) << 2;
  }
}

void Elf0_Die(struct Elf* p) {
  gPause = 0;
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

struct Entity* FUN_080bfce8(struct Coord* c, s32 r1);

INCASM("asm/cyberelf/unk_0_post_p1.inc");

void FUN_080e1fb8(struct Elf* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).unk_2c = FUN_080bfce8(&(p->s).coord, 0);
    (p->s).mode[2]++;
  }
  if (((p->s).unk_2c)->mode[0] > 1) {
    (p->s).mode[1]++;
  }
}

INCASM("asm/cyberelf/unk_0_post_p2.inc");

// --------------------------------------------

void FUN_080e1ef8(struct Elf* p);
void FUN_080e1fb8(struct Elf* p);
void FUN_080e1fe8(struct Elf* p);

const ElfFunc gElf0Updates[3] = {
    FUN_080e1ef8,
    FUN_080e1fb8,
    FUN_080e1fe8,
};
