#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "mission.h"
#include "text_window.h"
#include "vfx.h"

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

// Pool-island basin: all five reward blocks, the doubled mission increments,
// the unlock-slot write, and the oam mask match insn-for-insn, but retail
// splits its literal pools across three mid-function islands (duplicating
// gMission and the 0x121 offset, +12 bytes) where this layout coalesces one.
NON_MATCH void Elf7_Die(struct Elf* p) {
#if MODERN
  u8* z = *(u8**)((u8*)p + 0xb4);
  gPause = 0;
  switch (*(z + 0x121) - 5) {
    case 0: {
      register u8* b asm("r1");
      u16 h2;
      u8 zz;
      b = z + 0xb4;
      h2 = *(u16*)(b + 4) + 3;
      zz = 0;
      *(u16*)(b + 4) = h2;
      *(b + 0xa) = zz;
      goto txt;
    }
    case 1: {
      register u8* b asm("r1");
      u16 h2;
      u8 zz;
      b = z + 0xb4;
      h2 = *(u16*)(b + 4) + 3;
      zz = 0;
      *(u16*)(b + 4) = h2;
      *(b + 0xb) = zz;
    }
    txt:
      PrintTextWindow(0x103, 0x5A);
      break;
    case 2:
    case 3: {
      u8* b = z + 0xb4;
      *(u16*)(b + 4) += 5;
      PlaySound(6);
      {
        u8* q = (u8*)gMission.unk_00;
        if (*q <= 8) {
          *q += 1;
          q = (u8*)gMission.unk_00;
          if (*q <= 8) {
            *q += 1;
            asm volatile("");
          }
        }
      }
      if ((p->s).work[1] != 0) {
        u8* q2 = (u8*)gMission.unk_00;
        if (*q2 <= 8) {
          *q2 += 1;
          q2 = (u8*)gMission.unk_00;
          if (*q2 <= 8) {
            *q2 += 1;
          }
        }
      }
      break;
    }
    case 22: {
      u8* b = z + 0xb4;
      *(u16*)(b + 4) += 5;
      break;
    }
    case 23:
    case 24:
    case 25:
    case 26:
    case 38:
    case 40: {
      u8* b = z + 0xb4;
      *(u16*)(b + 4) += 3;
      break;
    }
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 39:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
      break;
  }
  {
    u8* c = (u8*)gMission.unk_00 + 0x4c;
    if (*c <= 0x62) {
      *c += 1;
    }
  }
  {
    register u32 idv asm("r0");
    u8* base;
    u8* slot;
    idv = *(z + 0x121);
    base = (u8*)*gUnlockedElfPtr;
    slot = base + idv;
    *slot |= 2;
  }
  {
    u8* b5 = (u8*)p + 0x49;
    s32 m5 = -0xD;
    asm("" : "+r"(m5));
    *b5 = (*b5 & m5) | 8;
  }
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
#else
  INCCODE("asm/cyberelf/unk_7_die.inc");
#endif
}

void FUN_080e3f24(struct Elf* p) {
  s32* val = (s32*)((u8*)p + 0xc0);
  *val += 0x30;
  if (*val > 0x27FF) {
    *val = 0x2800;
    *((u8*)p + 0xbc) = 1;
    (p->s).mode[1]++;
  }
}

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
