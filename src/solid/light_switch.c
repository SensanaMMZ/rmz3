#include "palette_animation.h"
#include "collision.h"
#include "element.h"
#include "global.h"
#include "solid.h"
#include "story.h"

static const struct Collision sCollision;
static const struct Rect sSize;

u8 GetEntityPalID(struct Entity* p);
static void Solid32_Init(struct Solid* p);
void Solid32_Update(struct Solid* p);
void Solid32_Die(struct Solid* p);
void Solid32_Disappear(struct Solid* p);

// clang-format off
const SolidRoutine gLightSwitchRoutine = {
    [ENTITY_INIT] =      Solid32_Init,
    [ENTITY_UPDATE] =    Solid32_Update,
    [ENTITY_DIE] =       Solid32_Die,
    [ENTITY_DISAPPEAR] = Solid32_Disappear,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid32_Init(struct Solid* p) {
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  SetMotion(&p->s, MOTION(SM223_LIGHT_SWITCH, 0));
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = &sSize;
  (p->s).hazardAttr = METATILE_GROUND;
  (p->s).flags2 &= ~WHITE_PAINTABLE;
  (p->s).invincibleID = (p->s).uniqueID;
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  if ((gCurStory.unk_54 >> (p->s).work[0]) & 1) {
    (p->s).mode[3] = 2;
  } else {
    (p->s).mode[3] = 0;
  }
  Solid32_Update(p);
}

extern const struct Coord Coord_083714bc;

void Solid32_Update(struct Solid* p) {
  s32 m = (p->s).mode[3];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(SM223_LIGHT_SWITCH, 0));
      (p->s).flags |= COLLIDABLE;
      {
        struct Body* b = &p->body;
        InitBody(b, &sCollision, &(p->s).coord, 0);
        b->parent = (struct CollidableEntity*)p;
        b->fn = (void*)m;
      }
      RemovePaletteAnimation(0xbd);
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0xbe, g | 0x200);
      }
      (p->s).mode[3]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->body).status & 1) {
        PlaySound(0x3c);
        ApplyElementEffect(0, &p->s, &Coord_083714bc);
        gCurStory.unk_54 |= 1 << (p->s).work[0];
        (p->s).mode[3]++;
      }
      break;
    case 2:
      SetMotion(&p->s, MOTION(SM223_LIGHT_SWITCH, 1));
      {
        u32* sp0 = &(p->body).status;
        s32 z = 0;
        asm("" : "+r"(z));
        *sp0 = z;
        (p->body).prevStatus = z;
        (p->body).invincibleTime = z;
      }
      (p->s).flags &= ~COLLIDABLE;
      RemovePaletteAnimation(0xbe);
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0xbd, g | 0x200);
      }
      (p->s).mode[3]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      {
        u8 sv = gCurStory.unk_54;
        u8 w = (p->s).work[0];
        u32 b = (sv >> w) & 1;
        if (b == 0) {
          gCurStory.unk_54 = sv ^ (1 << w);
          (p->s).mode[3] = b;
        }
      }
      break;
  }
  StepPaletteAnimation(0xbd);
  StepPaletteAnimation(0xbe);
}

void Solid32_Die(struct Solid* p) {}

void Solid32_Disappear(struct Solid* p) {
  RemovePaletteAnimation(0xbd);
  RemovePaletteAnimation(0xbe);
  DeleteSolid((Object*)p);
}

static const struct Collision sCollision = {
  kind : DRP,
  faction : FACTION_ENEMY,
  LAYER(0xFFFFFFFF),
  hitzone : 0xFF,
  remaining : 0,
  priorityLayer : 0xFFFDEF7B,
  range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
};

static const struct Rect sSize = {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)};
const struct Coord Coord_083714bc = {PIXEL(0), -PIXEL(16)};
