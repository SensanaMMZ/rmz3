#include "collision.h"
#include "global.h"
#include "quake.h"
#include "solid.h"
#include "sound.h"
#include "story.h"

static const struct Collision sCollision;

static void Solid43_Init(struct Solid* p);
void Solid43_Update(struct Solid* p);
void Solid43_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid43Routine = {
    [ENTITY_INIT] =      Solid43_Init,
    [ENTITY_UPDATE] =    Solid43_Update,
    [ENTITY_DIE] =       Solid43_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid43_Init(struct Solid* p) {
  (p->s).d.x = (p->s).d.y = 0;
  if ((p->s).work[0] == 0) {
    if (FLAG(gCurStory.s.gameflags, FLAG_49)) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      EXIT_BODY(p);
      SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    } else {
      INIT_BODY(p, &sCollision, 0, NULL);
      SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
      Solid43_Update(p);
    }
    return;
  }

  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  SetMotion(&p->s, MOTION(SM156_UNK_ICE, 0));
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  Solid43_Die(p);
}

void FUN_08014b04();

void Solid43_Update(struct Solid* p) {
  u32 status = (p->body).status;
  if (status & BODY_STATUS_WHITE) {
   if (status & BODY_STATUS_RECOILED) {
    s16 i;
    s32 z;
    const SolidRoutine* const* tbl;
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    {
      u8 f = ~COLLIDABLE & (p->s).flags;
      f |= DISPLAY;
      f |= FLIPABLE;
      (p->s).flags = f;
    }
    InitNonAffineMotion(&p->s);
    SetMotion(&p->s, MOTION(SM156_UNK_ICE, 0));
    FUN_08014b04();
    AppendQuake(4, &(p->s).coord);
    PlaySound(0x11D);
    i = 0;
    z = 0;
    tbl = (const SolidRoutine* const*)&gSolidFnTable[43];
    for (; i < 3; i++) {
      struct Solid* q = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
      if (q != NULL) {
        s32 y;
        (q->s).taskCol = 30;
        (q->s).id = 43;
        (q->s).onUpdate = (void*)(**tbl)[ENTITY_INIT];
        (q->s).tileNum = z;
        (q->s).palID = z;
        (q->s).flags2 |= WHITE_PAINTABLE;
        (q->s).invincibleID = (q->s).uniqueID;
        (q->s).work[0] = 1;
        (q->s).coord.x = (p->s).coord.x;
        y = (p->s).coord.y;
        if (i == 0) {
          y += -0x1000;
        }
        (q->s).coord.y = y;
        if (i > 1) {
          (q->s).coord.y = y + (i << 12);
        }
      }
    }
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Solid43_Die(p);
   }
  }
}

INCASM("asm/solid/unk_43.inc");

static const struct Collision sCollision = {
  kind : DRP,
  faction : FACTION_ENEMY,
  damage : 0,
  LAYER(RECOIL_PUSHABLE),
  hitzone : 0xFF,
  remaining : 0,
  range : {PIXEL(0), PIXEL(8), PIXEL(16), PIXEL(64)},
};
