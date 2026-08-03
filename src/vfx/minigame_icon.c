#include "entity.h"
#include "global.h"
#include "vfx.h"

void Ghost77_Init(struct VFX* p);
void Ghost77_Update(struct VFX* p);
void Ghost77_Die(struct VFX* p);

// clang-format off
const VFXRoutine gMinigameIconRoutine = {
    [ENTITY_INIT] =      Ghost77_Init,
    [ENTITY_UPDATE] =    Ghost77_Update,
    [ENTITY_DIE] =       Ghost77_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* CreateMinigameIcon_1(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_MINIGAME_ICON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

static const VFXFunc sUpdates[5];

struct VFX* CreateCopyXIcon(struct Zero* z, struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_MINIGAME_ICON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = (struct Entity*)z;
  }
  return p;
}

struct VFX* FUN_080c8204(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_MINIGAME_ICON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080c825c(struct Entity* e, struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_MINIGAME_ICON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Unk77Props { u32 unk_0; u8 unk_4[4]; u8 unk_8; };

struct VFX* FUN_080c82b8(struct Entity* e, struct Coord* c, u8 a2, u32 a3, u8 a4) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_MINIGAME_ICON);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).work[1] = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
    ((struct Unk77Props*)(p->props).raw)->unk_0 = a3;
    ((struct Unk77Props*)(p->props).raw)->unk_8 = a4;
  }
  return p;
}

void Ghost77_Update(struct VFX* p);

// 0x080C8330
void Ghost77_Init(struct VFX* p0) {
  struct VFX* p = p0;
  register s32 w asm("r5");
  register s32 z asm("r2");
  w = (p->s).work[0];
  if (w == 0) {
    register s32 one asm("r2");
    (p->s).flags &= ~X_FLIP;
    one = 1;
    ((p->s).spr).xflip = w;
    {
      u8* oa = (u8*)p + 0x4a;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      *oa = m11;
    }
    {
      u32 tbl = (u32)gVFXFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = one;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    (p->s).mode[1] = w;
    (p->s).mode[2] = w;
    (p->s).mode[3] = w;
  } else if (w == 1) {
    u32 tbl;
    EntityFunc** rt;
    z = 0;
    (p->s).flags &= ~X_FLIP;
    ((p->s).spr).xflip = z;
    {
      u8* oa = (u8*)p + 0x4a;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      *oa = m11;
    }
    tbl = (u32)gVFXFnTable;
    rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
    *(u32*)((p->s).mode) = w;
    (p->s).onUpdate = (void*)((*rt)[1]);
    (p->s).mode[1] = w;
    (p->s).mode[2] = z;
    (p->s).mode[3] = z;
  } else {
    u32 tbl;
    EntityFunc** rt;
    register s32 one2 asm("r3");
    if (w == 2) {
      goto arm3;
    }
    if (w == 3) {
      goto arm3;
    }
    if (w != 4) {
      goto done;
    }
  arm3:
    z = 0;
    (p->s).flags &= ~X_FLIP;
    one2 = 1;
    ((p->s).spr).xflip = z;
    {
      u8* oa = (u8*)p + 0x4a;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      *oa = m11;
    }
    tbl = (u32)gVFXFnTable;
    rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
    *(u32*)((p->s).mode) = one2;
    (p->s).onUpdate = (void*)((*rt)[1]);
    (p->s).mode[1] = w;
    (p->s).mode[2] = z;
    (p->s).mode[3] = z;
  }
done:
  Ghost77_Update(p);
}

void Ghost77_Update(struct VFX* p) {
  (sUpdates[(p->s).mode[1]])(p);
}


void Ghost77_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080c843c
void FUN_080c843c(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register u8 fv asm("r0");
      u8 t;
      InitNonAffineMotion(&p->s);
      t = (p->s).flags;
      fv = DISPLAY;
      fv |= t;
      fv |= FLIPABLE;
      (p->s).flags = fv;
      (p->s).coord.x = 0xF000;
      (p->s).coord.y = 0xA000;
      SetMotion(&p->s, MOTION(0xF4, 0x00));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/vfx/minigame_icon_post.inc");

// 0x080c8628
void FUN_080c8628(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register u8 fv asm("r0");
      u8 t;
      InitNonAffineMotion(&p->s);
      t = (p->s).flags;
      fv = DISPLAY;
      fv |= t;
      fv |= FLIPABLE;
      (p->s).flags = fv;
      SetMotion(&p->s, 9);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

// 0x080C8684
void FUN_080c8684(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      InitNonAffineMotion(&p->s);
      (p->s).flags = DISPLAY | (p->s).flags;
      (p->s).flags |= FLIPABLE;
      if ((p->s).work[1] == 0) {
        SetMotion(&p->s, 8);
      } else {
        SetMotion(&p->s, 0x12);
      }
      ForceEntityPalette(&p->s, 0xE);
      (p->s).work[2] = 0;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 w;
      s32 two;
      (p->s).coord = ((p->s).unk_28)->coord;
      (p->s).coord.y -= 0x1000;
      w = (p->s).work[2] + 1;
      (p->s).work[2] = w;
      if ((u8)w > 0x5A) {
        (p->s).work[2] = 0x5A;
      }
      if ((p->s).work[2] > 0x24 && (p->s).work[3] == 0) {
        (p->s).work[3] = 1;
        ForceEntityPalette(&p->s, 0xF);
      }
      UpdateMotionGraphic(&p->s);
      {
        s32 inp = gJoypad[0].input;
        s32 t;
        two = 2;
        asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(two));
        t &= inp;
        if (t == 0) {
          u32 tbl = (u32)gVFXFnTable;
          u32 id = ((p->s).id) << 2;
          EntityFunc** rt = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = two;
          (p->s).onUpdate = (void*)(*rt)[ENTITY_DIE];
        }
      }
      break;
    }
  }
}

INCASM("asm/vfx/minigame_icon_post_b.inc");

// --------------------------------------------

void FUN_080c843c(struct VFX* p);
void FUN_080c8488(struct VFX* p);
void FUN_080c8628(struct VFX* p);
void FUN_080c8684(struct VFX* p);
void FUN_080c8744(struct VFX* p);

// clang-format off
static const VFXFunc sUpdates[5] = {
    FUN_080c843c,
    FUN_080c8488,
    FUN_080c8628,
    FUN_080c8684,
    FUN_080c8744,
};
// clang-format on

// --------------------------------------------

const motion_t motion_t_ARRAY_0836f998[3] = {
    MOTION(0x0E, 0x08),
    MOTION(0x0E, 0x07),
    MOTION(0x0E, 0x09),
};
