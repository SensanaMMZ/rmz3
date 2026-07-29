#include "global.h"
#include "stagerun.h"
#include "vfx.h"

static const VFXFunc sUpdates[1];
extern const u8 u8_ARRAY_0836f59c[2];

void Ghost65_Update(struct VFX* vfx);

void CreateGhost65(s32 x, s32 y, u8 w1, u8 w2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_065);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = w1;
    (p->s).work[2] = w2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

void Ghost65_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836f59c[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  Ghost65_Update(p);
}

void Ghost65_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}


void Ghost65_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

static const motion_t sMotions[6];

void FUN_080c4320(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8 w2;
      s32 v;
      SetMotion(&p->s, sMotions[(p->s).work[1]]);
      w2 = (p->s).work[2];
      if (w2 != 0) {
        register u8 lf asm("r1");
        register s32 vv asm("r0");
        lf = (p->s).flags;
        vv = 0x10;
        vv |= lf;
        v = vv;
      } else {
        register u8 lf2 asm("r1");
        register s32 vv2 asm("r0");
        lf2 = (p->s).flags;
        vv2 = 0xEF;
        vv2 &= lf2;
        v = vv2;
      }
      (p->s).flags = v;
      {
        register s32 x1 asm("r1");
        register s32 z8 asm("r8");
        u8* a;
        x1 = 1;
        x1 &= w2;
        a = (u8*)p + 0x4c;
        z8 = 0;
        *a = x1;
        {
          u8* a2 = (u8*)p + 0x4a;
          s32 sh = x1 << 4;
          u8 b = *a2;
          s32 msk = -0x11;
          msk &= b;
          msk |= sh;
          *a2 = msk;
        }
        {
          register s32 base asm("r6");
          base = -0x200;
          (p->s).d.y = base - (RANDOM(RNG_0202f388) & 0xFF);
          (p->s).d.x = (RANDOM(RNG_0202f388) & 0x3FF) + base;
        }
        (p->s).work[2] = z8;
      }
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      {
        register u32 one asm("r1");
        s32 t = (p->s).work[2] + 1;
        s32 v2;
        (p->s).work[2] = t;
        one = 1;
        if (t & one) {
          register s32 vf asm("r0");
          vf = (p->s).flags;
          vf |= one;
          v2 = vf;
        } else {
          register u8 lf3 asm("r1");
          register s32 vv3 asm("r0");
          lf3 = (p->s).flags;
          vv3 = 0xFE;
          vv3 &= lf3;
          v2 = vv3;
        }
        (p->s).flags = v2;
      }
      {
        struct Camera* cam = &gStageRun.vm.camera;
        if (CalcFromCamera(cam, &(p->s).coord) > 0x4000) {
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
          SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
        }
      }
      break;
  }
}



void Ghost65_Init(struct VFX* vfx);

// clang-format off
const VFXRoutine gGhost65Routine = {
    [ENTITY_INIT] =      Ghost65_Init,
    [ENTITY_UPDATE] =    Ghost65_Update,
    [ENTITY_DIE] =       Ghost65_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c4320(struct VFX* vfx);

static const VFXFunc sUpdates[1] = {
    FUN_080c4320,
};

const u8 u8_ARRAY_0836f59c[2] = {0, 0};

// clang-format off
static const motion_t sMotions[6] = {
  MOTION(SM116_DEATHLOCK, 0x09),
  MOTION(SM116_DEATHLOCK, 0x0A),
  MOTION(SM116_DEATHLOCK, 0x0B),
  MOTION(SM116_DEATHLOCK, 0x0C),
  MOTION(SM116_DEATHLOCK, 0x0D),
  MOTION(SM116_DEATHLOCK, 0x08),
};
// clang-format on
