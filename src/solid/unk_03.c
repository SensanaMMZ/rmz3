#include "collision.h"
#include "global.h"
#include "solid.h"
#include "vfx.h"
#include "stagerun.h"

/*
  旧居住区などの蔦の燃える判定(グラフィックは別)
  他にも用途あるかも
*/

static const struct Collision sCollision;

// --------------------------------------------

void Solid3_Init(struct Solid* p);
void Solid3_Update(struct Solid* p);
void Solid3_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid3Routine = {
    [ENTITY_INIT] =      Solid3_Init,
    [ENTITY_UPDATE] =    Solid3_Update,
    [ENTITY_DIE] =       Solid3_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 旧居住区などの蔦の燃える判定部分(グラフィックは別)
struct Solid* CreateLeafBurn(u8 r0) {
  struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_UNK_003);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = r0;
    (p->s).work[1] = 0;
  }
  return p;
}

void FUN_0800e2c4(s32 x, s32 y);
void FUN_08010d20(s32 x, s32 y);
metatile_attr_t FUN_0800e284(s32 x, s32 y);
metatile_attr_t FUN_08010cd0(s32 x, s32 y);
s16 FUN_080cb528(struct Entity* p);
void FUN_080cb980(struct Body* body, struct Coord* c1, struct Coord* c2);

void FUN_080cb3b8(struct Entity* e, s32 x, s32 y) {
  struct Entity* p = NULL;
  if (gSolidHeaderPtr->remaining >= 8) {
    p = AllocEntityFirst(gSolidHeaderPtr);
    if (p != NULL) {
      p->taskCol = 30;
      INIT_SOLID_ROUTINE(p, SOLID_UNK_003);
      p->tileNum = 0;
      p->palID = 0;
      p->flags2 |= WHITE_PAINTABLE;
      p->invincibleID = p->uniqueID;
      (p->coord).x = (x & ~(PIXEL(16) - 1)) + PIXEL(8);
      (p->coord).y = (y & ~(PIXEL(16) - 1)) + PIXEL(16);
      p->work[0] = e->work[0];
      if (e->work[1] < 0xFF) {
        p->work[1] = e->work[1] + 1;
      } else {
        p->work[1] = e->work[1];
      }
    }
  }
  if (p == NULL) {
    p = AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      p->taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_029);
      p->tileNum = 0;
      p->palID = 0;
      (p->coord).x = (x & ~(PIXEL(16) - 1)) + PIXEL(8);
      (p->coord).y = (y & ~(PIXEL(16) - 1)) + PIXEL(16);
      p->work[0] = e->work[0];
      if (e->work[1] < 0xFF) {
        p->work[1] = e->work[1] + 1;
      } else {
        p->work[1] = e->work[1];
      }
    }
  }
  if (p != NULL) {
    if (e->work[0] == 0) {
      FUN_0800e2c4(x, y);
    } else {
      FUN_08010d20(x, y);
    }
  }
}

void FUN_080cb4c0(struct Entity* p) {
  s32 y, y2;
  p->flags |= DISPLAY;
  InitNonAffineMotion(p);
  SetMotion(p, MOTION(SM032_UNK, 0));
  (p->spr).oam.priority = 0;
  if (p->work[0] == 0) {
    y = (p->coord).y;
  } else {
    y = (p->coord).y - PIXEL(480);
  }
  y >>= 12;
  y2 = y;
  if (y < 0) {
    y += 31;
  }
  p->taskCol = 31 - (y2 - (y >> 5) * 32);
  p->work[2] = (p->work[1] & 3) + 5;
}

s16 FUN_080cb528(struct Entity* p) {
  s32 x, y;
  u8 count = 0;
  u8 ldru = 0;
  UpdateMotionGraphic(p);
  if (p->work[2] != 0) {
    p->work[2]--;
    return TRUE;
  }
  x = (p->coord).x;
  y = (p->coord).y - PIXEL(8);
  if (p->work[0] == 0) {
    if (FUN_0800e284(x, y - PIXEL(16))) {
      count++;
      ldru |= (1 << 0);
    }
    if (FUN_0800e284(x + PIXEL(16), y)) {
      count++;
      ldru |= (1 << 1);
    }
    if (FUN_0800e284(x, y + PIXEL(16))) {
      count++;
      ldru |= (1 << 2);
    }
    if (FUN_0800e284(x - PIXEL(16), y)) {
      count++;
      ldru |= (1 << 3);
    }
  } else {
    if (FUN_08010cd0(x, y - PIXEL(16))) {
      count++;
      ldru |= (1 << 0);
    }
    if (FUN_08010cd0(x + PIXEL(16), y)) {
      count++;
      ldru |= (1 << 1);
    }
    if (FUN_08010cd0(x, y + PIXEL(16))) {
      count++;
      ldru |= (1 << 2);
    }
    if (FUN_08010cd0(x - PIXEL(16), y)) {
      count++;
      ldru |= (1 << 3);
    }
  }
  if (count == 0) {
    return FALSE;
  }
  if (gSolidHeaderPtr->remaining + gVFXHeaderPtr->remaining < ((s32)count - 1)) {
    return TRUE;
  }

  if (ldru & (1 << 0)) {
    (p->coord).y -= PIXEL(16);
    ldru ^= (1 << 0);
  } else if (ldru & (1 << 1)) {
    (p->coord).x += PIXEL(16);
    ldru ^= (1 << 1);
  } else if (ldru & (1 << 2)) {
    (p->coord).y += PIXEL(16);
    ldru ^= (1 << 2);
  } else if (ldru & (1 << 3)) {
    (p->coord).x -= PIXEL(16);
    ldru ^= (1 << 3);
  }

  if (p->work[0] == 0) {
    FUN_0800e2c4((p->coord).x, (p->coord).y - PIXEL(8));
  } else {
    FUN_08010d20((p->coord).x, (p->coord).y - PIXEL(8));
  }
  if (ldru & (1 << 0)) FUN_080cb3b8(p, x, y - PIXEL(16));
  if (ldru & (1 << 1)) FUN_080cb3b8(p, x + PIXEL(16), y);
  if (ldru & (1 << 2)) FUN_080cb3b8(p, x, y + PIXEL(16));
  if (ldru & (1 << 3)) FUN_080cb3b8(p, x - PIXEL(16), y);
  FUN_080cb4c0(p);
  return TRUE;
}

void FUN_080cb980(struct Body* body, struct Coord* r1, struct Coord* r2);

void Solid3_Init(struct Solid* p) {
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[1] == 0) {
    INIT_BODY(p, &sCollision, 0, FUN_080cb980);
    (p->s).flags2 &= ~WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
  } else {
    FUN_080cb4c0(&p->s);
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid3_Update(p);
}

// 0x080CB7C8
void Solid3_Update(struct Solid* p) {
  s32 x0;
  register s32 y0 asm("r5");
  register s32 dx asm("sl");
  register s32 dy asm("r8");
  register s32 xr asm("r6");
  register s32 yd asm("sb");
  if ((p->s).work[1] == 0) {
    {
      register struct Camera* cam asm("r1");
      cam = &gStageRun.vm.camera;
      (p->s).coord.x = cam->viewport.x;
      (p->s).coord.y = cam->viewport.y;
    }
    if ((p->s).mode[1] == 0) {
      return;
    }
    x0 = (p->s).unk_coord.x;
    y0 = (p->s).unk_coord.y;
    dx = (p->s).d.x;
    dy = (p->s).d.y;
    if ((p->s).work[0] == 0) {
      if ((u16)FUN_0800e284(x0, y0)) {
        FUN_080cb3b8(&p->s, x0, y0);
      }
      xr = x0 + dx;
      yd = y0 + dy;
      if ((u16)FUN_0800e284(xr, yd)) {
        FUN_080cb3b8(&p->s, xr, yd);
      }
      dy = y0 - dy;
      if ((u16)FUN_0800e284(xr, dy)) {
        FUN_080cb3b8(&p->s, xr, dy);
      }
      y0 = x0 - dx;
      if ((u16)FUN_0800e284(y0, yd)) {
        FUN_080cb3b8(&p->s, y0, yd);
      }
      if ((u16)FUN_0800e284(y0, dy)) {
        FUN_080cb3b8(&p->s, y0, dy);
      }
    } else {
      if ((u16)FUN_08010cd0(x0, y0)) {
        FUN_080cb3b8(&p->s, x0, y0);
      }
      xr = x0 + dx;
      yd = y0 + dy;
      if ((u16)FUN_08010cd0(xr, yd)) {
        FUN_080cb3b8(&p->s, xr, yd);
      }
      dy = y0 - dy;
      if ((u16)FUN_08010cd0(xr, dy)) {
        FUN_080cb3b8(&p->s, xr, dy);
      }
      y0 = x0 - dx;
      if ((u16)FUN_08010cd0(y0, yd)) {
        FUN_080cb3b8(&p->s, y0, yd);
      }
      if ((u16)FUN_08010cd0(y0, dy)) {
        FUN_080cb3b8(&p->s, y0, dy);
      }
    }
    (p->s).mode[1] = 0;
    return;
  }
  {
    register s32 r asm("r2");
    r = (s16)FUN_080cb528(&p->s);
    if (r != 0) {
      return;
    }
    {
      register s32 h asm("r1");
      register s32 g asm("r0");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g = 0xFE;
      g &= h;
      {
        register s32 m asm("r1");
        m = 0xFD;
        g &= m;
      }
      (p->s).flags = g;
    }
    {
      register u8* a asm("r0");
      a = (u8*)p + 0x8c;
      asm volatile("str %0, [%1]" ::"l"(r), "l"(a) : "memory");
      a += 4;
      asm("" : "+r"(a));
      asm volatile("str %0, [%1]" ::"l"(r), "l"(a) : "memory");
      a += 4;
      asm("" : "+r"(a));
      *a = r;
    }
    {
      register s32 h2 asm("r1");
      register s32 g2 asm("r0");
      h2 = (p->s).flags;
      asm("" : "+r"(h2));
      g2 = 0xFB;
      g2 &= h2;
      (p->s).flags = g2;
    }
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}


void Solid3_Die(struct Solid* p) {}

void FUN_080cb980(struct Body* body, struct Coord* c1 UNUSED, struct Coord* c2 UNUSED) {
  struct Entity* p = (struct Entity*)body->parent;
  if (p->mode[1] == 0) {
    s32 x, y;
    s32 dx, dy;
    const struct Collision* collisions = (body->enemy)->processing;
    struct Coord* c = (body->enemy)->coord;
    const struct Rect* range = &collisions->range;
    if ((((struct Entity*)(body->enemy)->parent)->flags & X_FLIP) == 0) {
      x = c->x + range->x;
    } else {
      x = c->x - range->x;
    }
    y = c->y + range->y;
    dx = (u16)range->w >> 1;
    dy = (u16)range->h >> 1;
    if (p->work[0] == 0) {
      if (FUN_0800e284(x, y) || FUN_0800e284(x + dx, y + dy) || FUN_0800e284(x + dx, y - dy) || FUN_0800e284(x - dx, y + dy) || FUN_0800e284(x - dx, y - dy)) {
        (p->unk_coord).x = x, (p->unk_coord).y = y;
        (p->d).x = dx, (p->d).y = dy;
        if (!isSoundPlaying(SE_FLAME)) PlaySound(SE_FLAME);
        p->mode[1] = 1;
      }
    } else {
      if (FUN_08010cd0(x, y) || FUN_08010cd0(x + dx, y + dy) || FUN_08010cd0(x + dx, y - dy) || FUN_08010cd0(x - dx, y + dy) || FUN_08010cd0(x - dx, y - dy)) {
        (p->unk_coord).x = x, (p->unk_coord).y = y;
        (p->d).x = dx, (p->d).y = dy;
        if (!isSoundPlaying(SE_FLAME)) PlaySound(SE_FLAME);
        p->mode[1] = 1;
      }
    }
    (body->status) &= ~BODY_STATUS_WHITE;
  }
}

// --------------------------------------------

static const struct Collision sCollision = {
  kind : DRP,
  faction : FACTION_ENEMY,
  damage : 0,
  LAYER(0x442108),
  hitzone : 0xFF,
  remaining : 0,
  range : {PIXEL(0), PIXEL(0), -PIXEL(1), -PIXEL(1)},
};
