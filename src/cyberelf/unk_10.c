#include "cyberelf.h"
#include "global.h"

void FUN_080bfce8(struct Coord* c, s32 r1);

// 0x080E4B88
void FUN_080e4b88(struct Elf* p0) {
  register struct Elf* p asm("r3");
  register s32 w asm("r2");
  struct Entity* q;
  p = p0;
  q = *(struct Entity**)((u8*)p + 0xb4);
  w = (p->s).unk_coord.x;
  {
    register u8 fl asm("r0");
    u32 z;
    register u8* r asm("r0");
  if (w == 0) {
    if ((p->s).work[3] == *(u8*)((u8*)q + 0xb4)) {
      return;
    }
    {
      register u8 t asm("r1");
      t = (p->s).flags;
      fl = 0xFE;
      fl &= t;
      asm volatile("" :: "r"(t));
    }
    z = w;
  } else {
    register u8* b asm("r1");
    b = (u8*)q + 0xb4;
    asm("" : "+r"(b));
    if ((p->s).work[3] == b[1]) {
      return;
    }
    {
      register u8 t asm("r1");
      t = (p->s).flags;
      fl = 0xFE;
      fl &= t;
      asm volatile("" :: "r"(t));
    }
    z = 0;
  }
  fl &= 0xFD;
  (p->s).flags = fl;
  r = (u8*)p + 0x8c;
  *(u32*)r = z;
  asm volatile("add %0, #4" : "+r"(r));
  *(u32*)r = z;
  asm volatile("add %0, #4" : "+r"(r));
  *r = z;
  (p->s).flags &= 0xFB;
  SET_ELF_ROUTINE(p, 3);
  }
}

#include "zero.h"

struct CyberElf10 {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};

struct Elf* elf_080e4bf4(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElf10* p = (struct CyberElf10*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 10);
    (p->s).tileNum = 0, (p->s).palID = 0;
    p->player = z;
    (p->s).work[0] = breed, (p->s).work[1] = availability;
    (p->s).unk_coord.x = satelite_slot;
    if (satelite_slot == 0) {
      (p->s).work[3] = SATELITE_1;
    } else {
      (p->s).work[3] = SATELITE_2;
    }
  }
  return (struct Elf*)p;
}

void Elf10_Update(struct Elf* p);

// 0x080E4C64
void Elf10_Init(struct Elf* p) {
  struct Zero* z = ((struct CyberElf10*)p)->player;
  struct Rect rr = gZeroRanges[*((u8*)z + 0x147)];
  register s32 z8 asm("r8");
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register s32 c1 asm("r0");
    register s32 f1 asm("r1");
    f1 = (p->s).flags;
    c1 = 1;
    {
      register s32 t2 asm("r2");
      t2 = 0;
      z8 = t2;
    }
    c1 = c1 | f1;
    c1 |= 2;
    (p->s).flags = c1;
  }
  SetMotion(&p->s, GetElfMotion(1));
  UpdateMotionGraphic(&p->s);
  {
    register u8* xa asm("r0");
    register s32 xv asm("r1");
    xa = (u8*)p + 0x4c;
    xv = z8;
    *xa = xv;
  }
  {
    u8* oa = (u8*)&((p->s).spr).oam + 6;
    s32 ov = *oa;
    s32 m11 = -0x11;
    asm("" : "+r"(m11));
    *oa = m11 & ov;
    (p->s).flags &= 0xEF;
    {
      s32 nx = (z->s).coord.x + rr.x;
      (p->s).coord.x = nx;
      (p->s).coord.y = (z->s).coord.y + rr.y;
      *(s32*)&((struct CyberElf10*)p)->unk_b8[0] = nx;
      *(s32*)&((struct CyberElf10*)p)->unk_b8[4] = (p->s).coord.y;
    }
    asm("" : "+r"(oa));
    oa += 0x78;
    asm("" : "+r"(oa));
    {
      s32 zz = 0;
      asm volatile("" : "+r"(zz));
      {
        register s32 k2 asm("r0");
        k2 = 0x200;
        *(u16*)oa = k2;
      }
      ((struct CyberElf10*)p)->unk_b8[8] = zz;
    }
  }
  ((struct CyberElf10*)p)->unk_b8[9] = 0x20;
  (p->s).work[2] = 0x3C;
  asm volatile("" ::"r"(z8));
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  Elf10_Update(p);
}

INCASM("asm/cyberelf/unk_10_p1_b.inc");

void Elf10_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

void Elf10_Init(struct Elf* p);
void Elf10_Update(struct Elf* p);
void Elf10_Die(struct Elf* p);

// clang-format off
const ElfRoutine gElf10Routine = {
    [ENTITY_INIT] =      Elf10_Init,
    [ENTITY_UPDATE] =    Elf10_Update,
    [ENTITY_DIE] =       Elf10_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on
