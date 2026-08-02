#include "zero.h"
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

void Elf5_Update(struct Elf* p);

// 0x080E34BC
void Elf5_Init(struct Elf* p) {
  struct Zero* z = (struct Zero*)((struct CyberElf5*)p)->player;
  struct Rect r = gZeroRanges[z->posture];
  s32 one;
  s32 zero;
  u8* gp = (u8*)&gPause;
  asm volatile("movs %0, #1" : "=l"(one));
  *gp = one;
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    u8 fl = (p->s).flags;
    zero = 0;
    one |= fl;
    one |= FLIPABLE;
    (p->s).flags = one;
  }
  SetMotion(&p->s, 0x9000);
  ((p->s).spr).xflip = zero;
  {
    u8* oa = (u8*)p + 0x4a;
    s32 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    *oa = m11;
  }
  (p->s).flags &= 0xEF;
  {
    u8* b = (u8*)p + 0x49;
    s32 bv = *b;
    s32 md = -0xD;
    md &= bv;
    *b = md;
  }
  (p->s).coord.x = (z->s).coord.x + r.x;
  (p->s).coord.y = (z->s).coord.y + r.y;
  Elf5_Update(p);
}

void Elf5_Update(struct Elf* p) {
  UpdateMotionGraphic(&p->s);
  SET_ELF_ROUTINE(p, ENTITY_DIE);
  Elf5_Die(p);
}

#include "mission.h"

struct Entity* FUN_080bfce8(struct Coord* c, s32 n);

// 0x080E35A8
void Elf5_Die(struct Elf* p0) {
  register struct Elf* p asm("r4");
  struct Entity* q;
  register u16* h asm("r3");
  register u8 (**tbl)[CYBERELF_LENGTH] asm("r1");
  register s32 k asm("r5");
  p = p0;
  q = *(struct Entity**)((u8*)p + 0xb4);
  gPause = FALSE;
  tbl = &gUnlockedElfPtr;
  h = (u16*)((u8*)q + 0xb4);
  k = 0x121;
  {
    u8* e = (**tbl) + *((u8*)q + k);
    *e |= 2;
  }
  h[2] += 3;
  {
    struct PlayInfo* pi = gMission.unk_00;
    if (pi->fusionCount <= 0x62) {
      pi->fusionCount++;
    }
  }
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

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
