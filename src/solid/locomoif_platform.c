#include "collision.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "entity/macros.h"
#include "solid.h"

/*
  ロコモIF戦で出現する台座
*/

struct LocomoIFPlatformObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u16 unk_00;     // 0xB4
  u8 unk_02[14];  // 0xB6
};
static_assert(sizeof(struct LocomoIFPlatformObject) == sizeof(struct Solid));

// ------------------------------------------------------------------------------------------------------------------------------------

void LocomoIFPlatform_Init(struct Solid* p);
void LocomoIFPlatform_Update(struct Solid* p);
void LocomoIFPlatform_Die(struct Solid* p);

// clang-format off
const SolidRoutine gLocomoIFPlatformRoutine = {
    [ENTITY_INIT] =      LocomoIFPlatform_Init,
    [ENTITY_UPDATE] =    LocomoIFPlatform_Update,
    [ENTITY_DIE] =       LocomoIFPlatform_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void CreateLocomoIFPlatform(struct Boss* locomoif) {
  s32 i;
  for (i = 0; i < 2; i++) {
    struct LocomoIFPlatformObject* p = (struct LocomoIFPlatformObject*)AllocEntityFirst(gSolidHeaderPtr);
    if (p != NULL) {
      u16 val;
      (p->s).taskCol = 30;
      INIT_SOLID_ROUTINE(p, SOLID_LOCOMOIF_PLATFORM);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = (p->s).uniqueID;
      (p->s).work[0] = 0;
      p->unk_00 = (i << 15);
      (p->s).unk_28 = &locomoif->s;
    }
  }
}

void FUN_080ce538(struct Solid* p) {
  struct LocomoIFPlatformObject* obj = (struct LocomoIFPlatformObject*)p;
  struct Solid* parent = (struct Solid*)(p->s).unk_28;
  (p->s).coord.x = (parent->s).coord.x;
  (p->s).coord.x += (s16)gSineTable[(u8)((obj->unk_00 >> 8) + 0x40)] * 56;
  (p->s).coord.y = (parent->s).coord.y - 0x1000;
  (p->s).coord.y += (s16)gSineTable[obj->unk_00 >> 8] * 56;
}

void nop_080ce58c(struct Solid* p) {}

extern const u8 u8_ARRAY_08370310[4];
extern const struct Collision sLocomoIFPlatformCollision;

void LocomoIFPlatform_Init(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_08370310[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, &sLocomoIFPlatformCollision, 1, (void*)nop_080ce58c);
  LocomoIFPlatform_Update(p);
}

INCASM("asm/solid/locomoif_platform_part2_pre.inc");

void LocomoIFPlatform_Die(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

void nop_080ce70c(struct Solid* p) {}

void FUN_080ce538(struct Solid* p);

void FUN_080ce710(struct Solid* p) {
  struct Entity* owner = (p->s).unk_28;

  switch ((p->s).mode[2]) {
    case 0:
      (p->s).taskCol = 23;
      SetMotion(&p->s, MOTION(0x55, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      FUN_080ce538(p);
      UpdateMotionGraphic(&p->s);
      if (*(u8*)((u8*)owner + 0xbd) != 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x080ce760
void FUN_080ce760(struct Solid* p) {
  struct Entity* e = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      FALLTHROUGH;
    case 1:
      *(u16*)&(p->props).raw[0] += (p->s).d.x;
      FUN_080ce538(p);
      UpdateMotionGraphic(&p->s);
      break;
  }
  if (e->mode[0] > 1) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/solid/locomoif_platform_part3_b.inc");

// One mechanism apart: agbcc fuses the branch-taught zero with a u8 copy of
// the work[2] decrement (lsrs into r5) where retail materializes an
// independent r5 zero before the calls. Equal length, same behavior.
NON_MATCH void FUN_080ce80c(struct Solid* p) {
#if MODERN
  struct Entity* owner = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x40;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).d.x -= 4;
      *(u16*)&(p->props).raw[0] += (p->s).d.x;
      FUN_080ce538(p);
      UpdateMotionGraphic(&p->s);
      if (--(p->s).work[2] == 0) {
        StopSound(0x10B);
        *(u8*)((u8*)owner + 0xbd) = 0;
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
#else
  INCCODE("asm/solid/locomoif_ce80c.inc");
#endif
}

// --------------------------------------------

void nop_080ce70c(struct Solid* p);

const SolidFunc sLocomoIFPlatformUpdates1[4] = {
    nop_080ce70c,
    nop_080ce70c,
    nop_080ce70c,
    nop_080ce70c,
};

// --------------------------------------------

void FUN_080ce710(struct Solid* p);
void FUN_080ce7a4(struct Solid* p);
void FUN_080ce760(struct Solid* p);
void FUN_080ce80c(struct Solid* p);

const SolidFunc sLocomoIFPlatformUpdates2[4] = {
    FUN_080ce710,
    FUN_080ce7a4,
    FUN_080ce760,
    FUN_080ce80c,
};

// --------------------------------------------

const struct Collision sLocomoIFPlatformCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 255,
  nature : BODY_NATURE_B2,
  remaining : 0,
  layer : 0x00000001,
  range : {PIXEL(0), PIXEL(13), PIXEL(47), PIXEL(22)},
};

const u8 u8_ARRAY_08370310[4] = {0, 0, 0, 0};

const struct Rect Rect_08370314 = {PIXEL(0), PIXEL(11), PIXEL(48), PIXEL(22)};
