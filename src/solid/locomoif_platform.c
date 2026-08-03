#include "collision.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "entity/macros.h"
#include "solid.h"
#include "stagerun.h"
#include "zero.h"

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

extern const SolidFunc sLocomoIFPlatformUpdates1[4];
extern const SolidFunc sLocomoIFPlatformUpdates2[4];
extern const struct Rect Rect_08370314;

// 0x080CE600
void LocomoIFPlatform_Update(struct Solid* p) {
  struct Entity* q = (p->s).unk_28;
  (sLocomoIFPlatformUpdates1[(p->s).mode[1]])(p);
  (sLocomoIFPlatformUpdates2[(p->s).mode[1]])(p);
  if (q->mode[0] > 1) {
    register s32 z4 asm("r4");
    register u8* a8c asm("r8");
    u8* a90;
    register u8* a94 asm("r6");
    register s32 cfb asm("r9");
    {
      register u8 g asm("r0");
      register u8 h asm("r1");
      h = (p->s).flags2;
      asm("" : "+r"(h));
      g = 0xF7;
      g &= h;
      z4 = 0;
      (p->s).flags2 = g;
    }
    a8c = (u8*)p + 0x8c;
    *(s32*)a8c = z4;
    a90 = (u8*)p + 0x90;
    asm("" : "+l"(a90));
    *(s32*)a90 = z4;
    a94 = (u8*)p + 0x94;
    *a94 = z4;
    {
      register u8 h2 asm("r1");
      register s32 t2 asm("r2");
      register u8 g2 asm("r0");
      h2 = (p->s).flags;
      asm("" : "+r"(h2));
      t2 = 0xFB;
      cfb = t2;
      g2 = cfb;
      g2 &= h2;
      (p->s).flags = g2;
    }
    if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
      {
        register u8 g3 asm("r0");
        register u8 h3 asm("r1");
        h3 = (p->s).flags;
        asm("" : "+r"(h3));
        g3 = 0xFE;
        g3 &= h3;
        h3 = 0xFD;
        g3 &= h3;
        (p->s).flags = g3;
      }
      *(s32*)a8c = z4;
      *(s32*)a90 = z4;
      *a94 = z4;
      {
        register u8 h4 asm("r1");
        register u8 g4 asm("r0");
        h4 = (p->s).flags;
        asm("" : "+r"(h4));
        g4 = cfb;
        g4 &= h4;
        (p->s).flags = g4;
      }
      SET_SOLID_ROUTINE(p, 3);
    }
  } else if ((pZero2->s).coord.y < (p->s).coord.y + (0xE0 << 3)) {
    {
      register u8 fl asm("r1");
      register u8 g5 asm("r0");
      fl = (p->s).flags2;
      g5 = 8;
      g5 |= fl;
      (p->s).flags2 = g5;
    }
    *(const struct Rect**)((u8*)p + 0x30) = &Rect_08370314;
    {
      register s32 hv asm("r0");
      hv = 0xA001;
      *(u16*)((u8*)p + 0x26) = hv;
    }
  } else {
    register u8 g6 asm("r0");
    register u8 h6 asm("r1");
    h6 = (p->s).flags2;
    asm("" : "+r"(h6));
    g6 = 0xF7;
    g6 &= h6;
    (p->s).flags2 = g6;
  }
}

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

void FUN_080ce7a4(struct Solid* p) {
  u8 md = (p->s).mode[2];
  switch (md) {
    case 0:
      PlaySound(0x10B);
      SetMotion(&p->s, MOTION(0x55, 0x01));
      (p->s).work[2] = 0x40;
      (p->s).d.x = md;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).d.x += 4;
      *(u16*)&(p->props).raw[0] += (p->s).d.x;
      FUN_080ce538(p);
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[2] - 1;
        register s32 sh asm("r0");
        (p->s).work[2] = t;
        sh = t << 24;
        if (sh == 0) {
          (p->s).mode[1] = 2;
          (p->s).mode[2] = 0;
        }
      }
      break;
  }
}

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
