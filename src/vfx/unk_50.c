#include "global.h"
#include "vfx.h"
#include "script.h"

// キュービットフォクスター の炎に関係

static const VFXFunc sUpdates[2];
static const motion_t sMotions[3];

struct VFX* FUN_080c078c(struct Entity* e, struct Coord* c, u8 arg2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_050);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = arg2;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Unk50Props { u8 unk_0[8]; u8 unk_8; };

struct VFX* FUN_080c07e4(struct Coord* c1, struct Coord* c2, u8 a2, u8 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_050);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    ((struct Unk50Props*)(p->props).raw)->unk_8 = a3;
    (p->s).work[1] = 1;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

void VFX50_Update(struct VFX* vfx);

// 0x080c08d0
void VFX50_Init(struct VFX* vfx) {
  InitNonAffineMotion(&vfx->s);
  (vfx->s).flags |= DISPLAY;
  (vfx->s).flags |= FLIPABLE;
  ResetDynamicMotion((void*)vfx);

  if ((vfx->s).work[0] == 0) {
    SET_XFLIP(vfx, FALSE);
    (vfx->s).d.x = PIXEL(1) / 2;
  } else {
    SET_XFLIP(vfx, TRUE);
    (vfx->s).d.x = -PIXEL(1) / 2;
  }
  (vfx->s).d.y = 0;

  if ((vfx->s).work[1] == 0) {
    SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
    (vfx->s).mode[1] = 1, (vfx->s).mode[2] = 0, (vfx->s).mode[3] = 0;
  } else {
    SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
    (vfx->s).mode[1] = 0, (vfx->s).mode[2] = 0, (vfx->s).mode[3] = 0;
  }

  (vfx->s).d.y = 0;
  (vfx->s).work[2] = 0xFF;
  VFX50_Update(vfx);
}

void VFX50_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

void VFX50_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

#include "motion.h"

void FUN_080c094c(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, sMotions[(p->props).raw[8]]);
      (p->s).taskCol = 9;
      (p->s).work[3] = 10;
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).d.y -= 0x20;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[3] == 0 || --(p->s).work[3] == 0) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

// 0x080C09C8
void FUN_080c09c8(struct VFX* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register struct Entity* q asm("r1");
      register s32 dx asm("r0");
      register s32 k asm("r2");
      SetMotion(&p->s, MOTION(0xB0, 0x1C));
      (p->s).work[2] = 0x1E;
      if ((p->s).d.x > 0) {
        q = (p->s).unk_28;
        dx = (q->coord).x;
        k = 0xC00;
      } else {
        q = (p->s).unk_28;
        dx = (q->coord).x;
        k = -0xC00;
      }
      dx += k;
      (p->s).unk_coord.x = dx;
      (p->s).d.y = 0x80;
      (p->s).unk_coord.y = (q->coord).y + 0x600;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      {
        register s32 t asm("r0");
        register s32 cx asm("r1");
        t = (p->s).unk_coord.x;
        cx = (p->s).coord.x;
        t -= cx;
        t <<= 4;
        t >>= 8;
        cx += t;
        (p->s).coord.x = cx;
      }
      {
        register s32 t2 asm("r0");
        register s32 cy asm("r1");
        t2 = (p->s).unk_coord.y;
        cy = (p->s).coord.y;
        t2 -= cy;
        t2 <<= 4;
        t2 >>= 8;
        cy += t2;
        (p->s).coord.y = cy;
      }
      UpdateMotionGraphic(&p->s);
      if (((p->s).unk_28)->flags & 1) {
        (p->s).flags |= 1;
      } else {
        (p->s).flags &= 0xFE;
      }
      break;
    }
    case 2:
      if (((p->s).unk_28)->scriptEntity->flags & 0x80) {
        CreateSmoke(1, &(p->s).coord);
        PlaySound(0x2A);
        {
          u32 tbl = (u32)gVFXFnTable;
          u32 id = ((p->s).id) << 2;
          EntityFunc** rt = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = m;
          (p->s).onUpdate = (void*)((*rt)[2]);
        }
      }
      break;
  }
}

void VFX50_Init(struct VFX* vfx);
void VFX50_Update(struct VFX* vfx);
void VFX50_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX50Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX50_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX50_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX50_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c094c(struct VFX* vfx);
void FUN_080c09c8(struct VFX* vfx);

static const VFXFunc sUpdates[2] = {
    FUN_080c094c,
    FUN_080c09c8,
};

static const motion_t sMotions[3] = {
    MOTION(DM177_CUBIT_FLAME, 9),
    MOTION(DM177_CUBIT_FLAME, 10),
    MOTION(DM177_CUBIT_FLAME, 11),
};
