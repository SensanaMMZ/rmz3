#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "mission.h"
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

s32 CalcAngle(s32 x, s32 y);
struct Entity* FUN_080bfc94(struct Coord* c, u8 r1);

// 0x080E1EF8 -- parked (scratch-register tie): 92/92 insns, every instruction
// and every other register home matches retail. The single divergence is the
// zero index register of the SECOND ldrsh into gSineTable: retail reuses r7
// (freed by the 0x200 range constant) where agbcc picks r2. Both are free at
// that point, so it is a pure allocation-order preference. Six keep-alive /
// pin placements were tried (on the constant, on dy, on the first sine value,
// on the entity pointer); each either left r2 in place or scrambled an
// upstream home that was already correct.
NON_MATCH void FUN_080e1ef8(struct Elf* p0) {
#if MODERN

  register struct Elf* p asm("r4");
  s32* tx;
  s32* ty;
  s32 dx;
  s32 dy;
  p = p0;
  {
    u8* cp = (u8*)p + 0xc0;
    s32 t = *cp + 1;
    *cp = t % 32;
  }
  tx = (s32*)((u8*)p + 0xb4);
  dx = *tx - (p->s).unk_coord.x;
  ty = (s32*)((u8*)p + 0xb8);
  dy = *ty - (p->s).unk_coord.y;
  asm volatile("" ::"r"(tx));
  asm volatile("" ::"r"(ty));
  {
    register s32 k200 asm("r1");
    register s32 k400 asm("r1");
    s32 k200b;
    s32 sum1;
    s32 sum2;
    k200 = 0x200;
    asm("" : "+r"(k200));
    sum1 = dx + k200;
    k400 = 0x400;
    asm("" : "+r"(k400));
    if ((u32)sum1 > (u32)k400) {
      goto move;
    }
    k200b = 0x200;
    asm("" : "+r"(k200b));
    sum2 = dy + k200b;
    if ((u32)sum2 > (u32)k400) {
      goto move;
    }
    if ((dx * dx) + (dy * dy) <= 0x40000) {
      asm volatile("" ::"r"(k200b));
      (p->s).mode[1]++;
      (p->s).unk_coord.x = *tx;
      (p->s).unk_coord.y = *ty;
      return;
    }
  }
move:
  {
    s32 a = CalcAngle(dx, dy);
    const s16* st = gSineTable;
    u32 a2;
    asm("" : "+r"(st));
    asm volatile("add %0, %1, #0" : "=&l"(a2) : "l"(a));
    a2 += 0x40;
    (p->s).unk_coord.x += st[(u8)a2] << 1;
    (p->s).unk_coord.y += st[(u8)a] << 1;
    {
      u8* r = (u8*)p + 0xc1;
      s32 v = *r - 1;
      *r = v;
      if ((u8)v == 0xFF) {
        FUN_080bfc94((struct Coord*)((u8*)p + 0x54), 0);
        *r = 0x20;
      }
    }
  }
#else
  INCCODE("asm/cyberelf/unk_0_1ef8.inc");
#endif
}

void FUN_080e1fb8(struct Elf* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).unk_2c = FUN_080bfce8(&(p->s).coord, 0);
    (p->s).mode[2]++;
  }
  if (((p->s).unk_2c)->mode[0] > 1) {
    (p->s).mode[1]++;
  }
}

// 0x080E1FE8
void FUN_080e1fe8(struct Elf* p) {
  struct Zero* q = ((struct CyberElf0*)p)->player;
  u8 n;
  if ((p->s).work[0] == 0) {
    struct ZeroAsset* a = &(q->unk_b4).status.asset;
    s32 r;
    a->fusions += 3;
    r = (u8)IsDoubleHP(q) << 24;
    n = 4;
    if (r != 0) {
      n = 8;
    }
  } else {
    struct ZeroAsset* a = &(q->unk_b4).status.asset;
    a->fusions += 5;
    n = GetMaxHP(q);
  }
  {
    struct PlayInfo* m = gMission.unk_00;
    if (m->fusionCount <= 0x62) {
      m->fusionCount++;
    }
  }
  {
    u8(**pp)[CYBERELF_LENGTH] = &gUnlockedElfPtr;
    u8 id = q->unk_121;
    (**pp)[id] |= 2;
  }
  {
    s16* h = &(q->body).hp;
    *h += n;
    if (GetMaxHP(q) < *h) {
      *h = GetMaxHP(q);
    }
  }
  SET_ELF_ROUTINE(p, ENTITY_DIE);
  Elf0_Die(p);
}

// --------------------------------------------

void FUN_080e1ef8(struct Elf* p);
void FUN_080e1fb8(struct Elf* p);
void FUN_080e1fe8(struct Elf* p);

const ElfFunc gElf0Updates[3] = {
    FUN_080e1ef8,
    FUN_080e1fb8,
    FUN_080e1fe8,
};
