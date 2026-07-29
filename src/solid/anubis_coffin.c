#include "collision.h"
#include "global.h"
#include "solid.h"
#include "zero.h"

// ------------------------------------------------------------------------------------------------------------------------------------

void AnubisCoffin_Init(struct Solid* p);
void AnubisCoffin_Update(struct Solid* p);
void AnubisCoffin_Die(struct Solid* p);

// clang-format off
const SolidRoutine gAnubisCoffinRoutine = {
    [ENTITY_INIT] =      AnubisCoffin_Init,
    [ENTITY_UPDATE] =    AnubisCoffin_Update,
    [ENTITY_DIE] =       AnubisCoffin_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void CreateAnubisCoffins(struct Entity* anubis, bool8 r1) {
  s32 i;
  struct Solid* another = NULL;
  for (i = 0; i < 2; i++) {
    struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 30;
      INIT_SOLID_ROUTINE(p, SOLID_ANUBIS_COFFIN);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).flags2 |= WHITE_PAINTABLE;
      (p->s).invincibleID = (p->s).uniqueID;
      (p->s).work[0] = 0;
      (p->s).work[2] = i;
      (p->s).work[3] = r1;
      (p->s).unk_28 = anubis;
      (p->s).unk_2c = (struct Entity*)another;
      another = p;
    }
  }
}

extern const SolidFunc sAnubisCoffinUpdates1[3];
extern const SolidFunc sAnubisCoffinUpdates2[3];
extern const struct Collision sAnubisCoffinCollisions[2];
extern const u8 u8_ARRAY_08370240[4];
extern const struct Rect Rect_08370238;

void AnubisCoffin_Update(struct Solid* p);

void FUN_080cdd64(struct Solid* p) {
  struct Solid* q = (struct Solid*)(p->s).unk_2c;
  s32 dx;
  s32 px;
  if (((p->body).status & 0x24) || ((q->body).status & 0x24)) {
    *((u8*)p + 0xbc) = 1;
  }
  dx = (p->s).coord.x;
  dx -= (q->s).coord.x;
  dx += -0x1800;
  {
    u8 lk = *((u8*)p + 0xbc);
    px = *(volatile s32*)&(p->s).coord.x;
    if (lk == 0) {
    struct Zero* z;
      if (dx > 0x1DFF) goto normal;
      z = pZero2;
      if ((z->s).coord.x < (q->s).coord.x + 0xC00) goto normal;
      if ((z->s).coord.x > px - 0xC00) goto normal;
      if ((z->s).coord.y <= (p->s).coord.y - 0x1E00) goto normal;
    }
  }
  (pZero2->s).coord.x = *(s32*)((u8*)p + 0xb8);
  SetDDP(&p->body, &sAnubisCoffinCollisions[1]);
  (p->s).flags2 &= ~ENTITY_HAZARD;
  SetDDP(&q->body, &sAnubisCoffinCollisions[1]);
  (q->s).flags2 &= ~ENTITY_HAZARD;
  return;

normal:
  SetDDP(&p->body, &sAnubisCoffinCollisions[0]);
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = (struct Rect*)&Rect_08370238;
  (p->s).hazardAttr = 1;
  SetDDP(&q->body, &sAnubisCoffinCollisions[0]);
  (q->s).flags2 |= ENTITY_HAZARD;
  (q->s).size = (struct Rect*)&Rect_08370238;
  (q->s).hazardAttr = 1;
}

void nop_080cde6c(struct Solid* p) {}

void AnubisCoffin_Init(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_08370240[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sAnubisCoffinCollisions, 1, (void*)nop_080cde6c);
  *(u8*)((u8*)p + 0xbc) = 0;
  AnubisCoffin_Update(p);
}

void AnubisCoffin_Update(struct Solid* p) {
  (sAnubisCoffinUpdates1[(p->s).mode[1]])(p);
  (sAnubisCoffinUpdates2[(p->s).mode[1]])(p);
}


void AnubisCoffin_Die(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080cdf34(struct Solid* p) {}

INCASM("asm/solid/anubis_coffin_post_p2.inc");

// --------------------------------------------

void FUN_080cdf34(struct Solid* p);

const SolidFunc sAnubisCoffinUpdates1[3] = {
    FUN_080cdf34,
    FUN_080cdf34,
    FUN_080cdf34,
};

// --------------------------------------------

void coffin_080cdf38(struct Solid* p);
void coffin_080ce0d4(struct Solid* p);
void coffin_080ce204(struct Solid* p);

const SolidFunc sAnubisCoffinUpdates2[3] = {
    coffin_080cdf38,
    coffin_080ce0d4,
    coffin_080ce204,
};

// --------------------------------------------

const struct Collision sAnubisCoffinCollisions[2] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1800, 0x3C00},
    },
};

// --------------------------------------------

const struct Rect Rect_08370238 = {0, 0, 0x1800, 0x3C00};

const u8 u8_ARRAY_08370240[4] = {0, 0, 0, 0};
