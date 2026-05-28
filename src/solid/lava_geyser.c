#include "collision.h"
#include "global.h"
#include "solid.h"

void CreateLavaGeyserPlatform(struct Solid* s);

static const struct Collision sCollisions[];
static const struct Rect sSize;

struct LavaGeyserObject {
  OBJECT_HDR;
  // props
  u8 unk_b4[4];  // 0xB4
  s32 unk_b8_y;  // 0xB8
  s32 unk_bc_y;  // 0xBC
  s32 unk_c0_x;  // 0xC0
};
static_assert(sizeof(struct LavaGeyserObject) == sizeof(struct Solid));

// ------------------------------------------------------------------------------------------------------------------------------------

static void Solid7_Init(struct LavaGeyserObject* p);
void Solid7_Update(struct Solid* p);
void Solid7_Die(struct Solid* p);

// clang-format off
const SolidRoutine gLavaGeyserRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Solid7_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Solid7_Update,
    [ENTITY_DIE] =       (SolidFunc)Solid7_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void CreateLavaGeyser(struct Entity* e, s32 x, s32 y, s32 n) {
  s32 i;
  for (i = 0; i < 6; i++) {
    struct Entity* p = AllocEntityFirst(gSolidHeaderPtr);
    if (p != NULL) {
      register s32 r0 asm("r0");
      register s32 r1 asm("r1");

      p->taskCol = 30;
      INIT_SOLID_ROUTINE(p, SOLID_LAVA_GEYSER);
      p->tileNum = 0;
      p->palID = 0;
      p->flags2 |= WHITE_PAINTABLE;
      p->invincibleID = p->uniqueID;
      (p->work)[0] = 12;
      (p->work)[1] = i;

      r0 = abs(n - y);
      r1 = r0;
      if (r0 < 0) {  // never reached?
        r1 = r0 + ((1 << 11) - 1);
      }
      r0 = r1 >> 11;
      (p->work)[3] = r0;

      (p->coord).x = x;
      (p->coord).y = y;
      y += PIXEL(16);
      p->unk_28 = (void*)e;
    }
  }
}

static void CreateSolid7_Unused(s32 x, u8 n) {
  struct Entity* p = (struct Entity*)AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_LAVA_GEYSER);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    (p->work)[0] = n;
    (p->coord).x = x;
  }
}

bool8 FUN_080cc814(struct Entity* p) { return (p->mode)[1] == ENTITY_EXIT; }

// 0x080cc828
static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  struct Entity* enemy = (struct Entity*)(body->enemy)->parent;
  struct LavaGeyserObject* self = (struct LavaGeyserObject*)body->parent;

  if (body->hitboxFlags & BODY_STATUS_B3) {
    self->unk_bc_y = (enemy->coord).y;
  }
}

static void Solid7_Init(struct LavaGeyserObject* p) {
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  if ((p->s).work[0] == 12) {
    (p->s).mode[1] = 5;
  } else {
    (p->s).mode[1] = 0;
    INIT_BODY(p, &sCollisions[0], 1, onCollision);
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - PIXEL(14);
    p->unk_b8_y = (p->s).coord.y;
    p->unk_c0_x = (p->s).coord.x;
    (p->s).flags2 |= ENTITY_HAZARD;
    (p->s).size = &sSize;
    (p->s).hazardAttr = 0x811;
    CreateLavaGeyserPlatform((void*)p);
  }
  Solid7_Update((void*)p);
}

extern const SolidFunc sSolid7Updates1[6];
extern const SolidFunc sSolid7Updates2[6];

INCASM("asm/solid/lava_geyser_p1_p1.inc");

void Solid7_Update(struct Solid* p) {
  (sSolid7Updates1[(p->s).mode[1]])(p);
  (sSolid7Updates2[(p->s).mode[1]])(p);
}

INCASM("asm/solid/lava_geyser_p1_p2.inc");

void Solid7_Die(struct Solid* p) {}

INCASM("asm/solid/lava_geyser_p2.inc");

void nop_080cc930(struct Solid* p) {}

INCASM("asm/solid/lava_geyser_p3.inc");

// --------------------------------------------

void nop_080cc930(struct Solid* p);
void FUN_080cc934(struct Solid* p);

// clang-format off
const SolidFunc sSolid7Updates1[6] = {
    FUN_080cc934,
    FUN_080cc934,
    FUN_080cc934,
    FUN_080cc934,
    nop_080cc930,
    nop_080cc930,
};
// clang-format on

// --------------------------------------------

void FUN_080cc968(struct Solid* p);
void FUN_080cca14(struct Solid* p);
void FUN_080ccae0(struct Solid* p);
void FUN_080ccb50(struct Solid* p);
void FUN_080ccc1c(struct Solid* p);
void FUN_080ccca4(struct Solid* p);

// clang-format off
const SolidFunc sSolid7Updates2[6] = {
    FUN_080cc968,
    FUN_080cca14,
    FUN_080ccae0,
    FUN_080ccb50,
    FUN_080ccc1c,
    FUN_080ccca4,
};
// clang-format on

// --------------------------------------------

// 0x0836ffac
static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 254,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(57), PIXEL(32), PIXEL(111)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : 8,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(57), PIXEL(32), PIXEL(111)},
    },
};

// --------------------------------------------

// 0x0836ffdc
static const struct Rect sSize = {PIXEL(0), PIXEL(57), PIXEL(32), PIXEL(120)};
