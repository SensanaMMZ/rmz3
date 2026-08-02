#include "global.h"
#include "palette_animation.h"
#include "vfx.h"

static const VFXFunc sUpdates[4];
static const u8 sInitModes[4];

void VFX49_Update(struct VFX* vfx);

void FUN_080c025c(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

void createLaserSign(struct Entity* e, s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = e;
  }
}

void FUN_080c02f4(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}


void FUN_080c0340(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).unk_28 = e;
  }
}

void VFX49_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  VFX49_Update(p);
}

void VFX49_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}


void VFX49_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_49_post.inc");

u8 GetEntityPalID(struct Entity* p);

// 0x080C04D4
void FUN_080c04d4(struct VFX* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      u32 pid;
      register u32 k2 asm("r2");
      register u32 k0 asm("r0");
      SetMotion(&p->s, 0x4E00);
      pid = ((u32)GetEntityPalID(&p->s) << 24) >> 19;
      k2 = 0x200;
      asm volatile("add %0, %1, #0" : "=&l"(k0) : "l"(k2));
      pid |= k0;
      ((void (*)(u16, u32))StartPaletteAnimation)(0x57, pid);
      StepPaletteAnimation(0x57);
      (p->s).work[2] = 0x1e;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      s32 raw = (p->s).work[2] - 1;
      (p->s).work[2] = raw;
      if ((raw << 24) == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      u32* st;
      RemovePaletteAnimation(0x57);
      st = (u32*)((u8*)q + 0xb4);
      *st |= 4;
      SetMotion(&p->s, 0x4E01);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 3: {
      s32 m;
      UpdateMotionGraphic(&p->s);
      m = *(u8*)((u8*)p + 0x73);
      if (m == 3) {
        u32* st2 = (u32*)((u8*)q + 0xb4);
        *st2 |= 8;
        {
          register u8 fv asm("r0");
          register u8 fl asm("r1");
          fl = (p->s).flags;
          asm("" : "+r"(fl));
          fv = 0xFE;
          fv &= fl;
          fl = 0xFD;
          fv &= fl;
          (p->s).flags = fv;
        }
        {
          u32 tbl = (u32)gVFXFnTable;
          u32 id = ((p->s).id) << 2;
          EntityFunc** rt = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = m;
          (p->s).onUpdate = (void*)(*rt)[ENTITY_DISAPPEAR];
        }
      }
      break;
    }
  }
}

// 0x080c05a8
void FUN_080c05a8(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, (RANDOM(RNG_0202f388) & 1) + MOTION(0x4F, 0x03));
      (p->s).work[2] = 0x1a;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register u8 w asm("r1");
      (p->s).coord.y -= 0x100;
      w = (p->s).work[2];
      if (w <= 0xd) {
        register u8 m asm("r0");
        m = 1;
        m &= w;
        if (m != 0) {
          register u8 f asm("r0");
          register u8 t asm("r1");
          t = (p->s).flags;
          f = DISPLAY;
          f |= t;
          (p->s).flags = f;
        } else {
          register u8 f asm("r0");
          register u8 t asm("r1");
          t = (p->s).flags;
          f = 0xFE;
          f &= t;
          asm volatile("" ::"r"(t));
          (p->s).flags = f;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((u8)--(p->s).work[2] == 0) {
        register u8 f asm("r0");
        register u8 t asm("r1");
        register u8 k2 asm("r1");
        t = (p->s).flags;
        f = 0xFE;
        f &= t;
        asm volatile("" ::"r"(t));
        k2 = 0xFD;
        f &= k2;
        (p->s).flags = f;
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

u8 GetEntityPalID(struct Entity* p);

void FUN_080c065c(struct VFX* p) {
  struct Entity* e = (p->s).unk_28;
  if (e->mode[0] == 4) {
    RemovePaletteAnimation(0x57);
    {
      register u8 e1 asm("r1");
      register s32 fp asm("r0");
      e1 = (p->s).flags;
      fp = 0xFE;
      fp &= e1;
      {
        register s32 c2 asm("r1");
        c2 = 0xFD;
        fp &= c2;
      }
      (p->s).flags = fp;
    }
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x4E02);
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0x57, g | 0x200);
      }
      StepPaletteAnimation(0x57);
      (p->s).work[2] = 2;
      (p->s).coord.x = e->coord.x;
      (p->s).coord.y = e->coord.y;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((p->s).work[2] != 0) {
        if ((p->s).work[2] == 1) {
          RemovePaletteAnimation(0x57);
        }
        (p->s).work[2]--;
      }
      UpdateMotionGraphic(&p->s);
      if (e->mode[0] > 1) {
        RemovePaletteAnimation(0x57);
        {
          register u8 e1 asm("r1");
          register s32 fp asm("r0");
          e1 = (p->s).flags;
          fp = 0xFE;
          fp &= e1;
          {
            register s32 c2 asm("r1");
            c2 = 0xFD;
            fp &= c2;
          }
          (p->s).flags = fp;
        }
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
        break;
      }
      if ((*(u32*)((u8*)e + 0xb4) & 0x800) == 0) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SetMotion(&p->s, 0x4E03);
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      {
        u8 st = (p->s).motion.state;
        if (st != 3) {
          break;
        }
        {
          register u8 e1 asm("r1");
          register s32 fp asm("r0");
          e1 = (p->s).flags;
          fp = 0xFE;
          fp &= e1;
          {
            register s32 c2 asm("r1");
            c2 = 0xFD;
            fp &= c2;
          }
          (p->s).flags = fp;
        }
        {
          u32 tbl, id;
          EntityFunc** routine_table;
          tbl = (u32)gVFXFnTable;
          id = ((p->s).id) << 2;
          routine_table = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = st;
          (p->s).onUpdate = (void*)(*routine_table)[3];
        }
      }
      break;
  }
}


void VFX49_Init(struct VFX* vfx);
void VFX49_Update(struct VFX* vfx);
void VFX49_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX49Routine = {
    [ENTITY_INIT] =      VFX49_Init,
    [ENTITY_UPDATE] =    VFX49_Update,
    [ENTITY_DIE] =       VFX49_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c0400(struct VFX* vfx);
void FUN_080c04d4(struct VFX* vfx);
void FUN_080c05a8(struct VFX* vfx);
void FUN_080c065c(struct VFX* vfx);

static const VFXFunc sUpdates[4] = {
    FUN_080c0400,
    FUN_080c04d4,
    FUN_080c05a8,
    FUN_080c065c,
};

static const u8 sInitModes[4] = {0, 1, 2, 3};
