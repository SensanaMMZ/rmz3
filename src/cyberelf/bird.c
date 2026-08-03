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

#include "zero.h"

struct CyberElfBird {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};

struct Elf* CreateBirdElf(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElfBird* p = (struct CyberElfBird*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 12);
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

void BirdElf_Update(struct Elf* p);

// 0x080E5998
void BirdElf_Init(struct Elf* p) {
  struct Zero* z = ((struct CyberElfBird*)p)->player;
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
      *(s32*)&((struct CyberElfBird*)p)->unk_b8[0] = nx;
      *(s32*)&((struct CyberElfBird*)p)->unk_b8[4] = (p->s).coord.y;
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
      ((struct CyberElfBird*)p)->unk_b8[8] = zz;
    }
  }
  ((struct CyberElfBird*)p)->unk_b8[9] = 0x20;
  {
    register s32 u2 asm("r2");
    u2 = z8;
    (p->s).unk_2c = (struct Entity*)u2;
  }
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  BirdElf_Update(p);
}


struct Entity* FUN_080bfc94(struct Coord* c, u8 r1);

// 0x080E5A70
void BirdElf_Update(struct Elf* p) {
  struct Zero* z = *(struct Zero**)((u8*)p + 0xb4);
  s32 pz;
  UpdateMotionGraphic(&p->s);
  pz = gPause;
  if (pz != 0) {
    return;
  }
  if (*(u8*)((u8*)z + 0x232) != 0) {
    {
      register u8 fv asm("r0");
      register u8 fl asm("r1");
      fl = (p->s).flags;
      asm("" : "+r"(fl));
      fv = 0xFE;
      fv &= fl;
      fl = 0xFD;
      fv &= fl;
      (p->s).flags = fv;
    }
    {
      u8* a = (u8*)p + 0x8c;
      *(u32*)a = pz;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *(u32*)a = pz;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *a = pz;
    }
    (p->s).flags &= 0xFB;
    SET_ELF_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if ((*(u32*)((u8*)z + 0x8c) & 0x200) == 0) {
    if (*(s16*)((u8*)z + 0xa4) != 0) {
      goto run;
    }
  }
  SET_ELF_ROUTINE(p, ENTITY_DIE);
  return;
run:
  (sUpdates[(p->s).mode[1]])(p);
  {
    u8* q = (u8*)p + 0xc1;
    s32 v = *q - 1;
    *q = v;
    if ((u8)v == 0xFF) {
      FUN_080bfc94((struct Coord*)((u8*)p + 0x54), 2);
      *q = 0x20;
    }
  }
}

void BirdElf_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/cyberelf/bird_p2.inc");
