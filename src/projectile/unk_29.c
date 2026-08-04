#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "trig.h"

void copyx_080aa24c(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 29);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
  }
}

static const struct Collision sCollisions[2];
void Projectile29_Update(struct Projectile* p);

// 0x080aa29c -- init for the copy-X orbiting projectile.
// Blocker (allocation transposition): p and parent swap homes (mine
// p=r6/parent=r7, retail p=r7/parent=r6) while every other shape --
// routine-set web (mode-1 shared with the xflip mask in r4), fresh
// flag-or constant, staged f4/z8 zeros, oam inserts, sine reads --
// matches; pins are ghost-save-trapped and priority boosts do not
// flip the pair.
NON_MATCH void Projectile29_Init(struct Projectile* p) {
#if MODERN
  struct Entity* pa = (p->s).unk_28;
  u32 xf;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  (p->s).flags |= 3;
  SetMotion(&p->s, 0x6000);
  xf = ((pa->flags) >> 4) & 1;
  if (xf) {
    (p->s).flags |= 0x10;
  } else {
    (p->s).flags &= 0xEF;
  }
  ((p->s).spr).xflip = xf;
  *((u8*)p + 0x4a) = (*((u8*)p + 0x4a) & ~0x11) | (xf << 4);
  (p->s).flags |= 4;
  {
    struct Body* body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 0x40);
    body->parent = (struct CollidableEntity*)p;
    body->fn = NULL;
  }
  *((u8*)p + 0x49) = (*((u8*)p + 0x49) & ~0xD) | 4;
  if ((p->s).work[0] == 0) {
    if ((p->s).flags & 0x10) {
      (p->s).coord.x = (pa->coord).x + 0x1500;
      (p->s).d.x = 0x500;
    } else {
      (p->s).coord.x = (pa->coord).x - 0x1500;
      (p->s).d.x = -0x500;
    }
    (p->s).coord.y = (pa->coord).y - 0x1700;
    (p->s).d.y = 0;
  } else {
    u8* ang = (u8*)p + 0xc0;
    if ((p->s).flags & 0x10) {
      (p->s).coord.x = (pa->coord).x + 0x1100;
      *ang = 0x20;
    } else {
      (p->s).coord.x = (pa->coord).x - 0x1100;
      *ang = 0x60;
    }
    (p->s).coord.y = (pa->coord).y - 0xE00;
    (p->s).d.x = gSineTable[(u8)(*ang + 0x40)] * 5;
    (p->s).d.y = gSineTable[*ang] * 5;
  }
  (p->s).work[2] = 0x14;
  (p->s).work[3] = 0;
  Projectile29_Update(p);
#else
  INCCODE("asm/projectile/unk_29_init.inc");
#endif
}

void CreateVFX56(struct Entity* e, u8 kind1, u8 kind2);
void Projectile29_Die(struct Projectile* p);

// 0x080AA40C
void Projectile29_Update(struct Projectile* p) {
  register struct Entity* q asm("r5");
  q = (p->s).unk_28;
  UpdateMotionGraphic(&p->s);
  if ((p->s).mode[1] != 0) {
    if ((u8)++(p->s).work[2] > 2) {
      CreateVFX56(&p->s, 0, 0);
      (p->s).work[2] = 0;
    }
  }
  switch ((p->s).mode[1]) {
    case 0:
      if ((u8)--(p->s).work[2] == 0xff) {
        PlaySound(0x4d);
        {
          register s32 mv asm("r0");
          register s32 w0 asm("r1");
          mv = (p->s).mode[1];
          mv += 1;
          w0 = (p->s).work[0];
          mv += w0;
          (p->s).mode[1] = mv;
        }
        break;
      }
      if ((p->s).work[0] == 0) {
        register s32 mo asm("r0");
        register s32 k asm("r1");
        mo = *((u8*)q + 0x1e) << 8;
        {
          register u8* mp asm("r1");
          mp = (u8*)q + 0x70;
          k = *mp;
        }
        mo |= k;
        k = 0xB31B;
        if (mo == k) {
          break;
        }
        PlaySound(0x4d);
        goto bump;
      } else {
        register s32 mo2 asm("r0");
        register s32 k2 asm("r1");
        mo2 = *((u8*)q + 0x1e) << 8;
        {
          register u8* mp2 asm("r1");
          mp2 = (u8*)q + 0x70;
          k2 = *mp2;
        }
        mo2 |= k2;
        k2 = 0xB31C;
        if (mo2 == k2) {
          break;
        }
        PlaySound(0x4d);
        (p->s).mode[1] += 2;
        break;
      }
    case 1: {
      register s32 dx asm("r1");
      register s32 cx asm("r0");
      cx = (p->s).coord.x;
      dx = (p->s).d.x;
      cx += dx;
      (p->s).coord.x = cx;
      dx = (p->s).coord.y;
      if ((u16)FUN_080098a4(cx, dx) == 0) {
        break;
      }
      cx = (p->s).coord.x;
      dx = (p->s).d.x;
      cx -= dx;
      (p->s).coord.x = cx;
      {
        register u8* ap asm("r1");
        register s32 a asm("r0");
        if (dx < 0) {
          ap = (u8*)p + 0xc0;
          a = 0x20;
        } else {
          ap = (u8*)p + 0xc0;
          a = 0x60;
        }
        *ap = a;
        {
          register u8* ap2 asm("r3");
          register const s16* tb asm("r2");
          register s32 t asm("r0");
          register s32 sv asm("r1");
          ap2 = ap;
          tb = gSineTable;
          t = *ap2;
          t += 0x40;
          t <<= 24;
          t = ((u32)t) >> 23;
          t += (s32)tb;
          {
            register s32 zi asm("r5");
            zi = 0;
            sv = *(const s16*)(t + zi);
          }
          t = sv << 2;
          t += sv;
          (p->s).d.x = t;
          t = *ap2;
          t <<= 1;
          t += (s32)tb;
          {
            register s32 zi2 asm("r2");
            zi2 = 0;
            sv = *(const s16*)(t + zi2);
          }
          t = sv << 2;
          t += sv;
          (p->s).d.y = t;
        }
      }
      (p->s).work[3]++;
    bump:
      (p->s).mode[1]++;
      break;
    }
    case 2: {
      register s32 dx2 asm("r1");
      register s32 cx2 asm("r0");
      cx2 = (p->s).coord.x;
      dx2 = (p->s).d.x;
      cx2 += dx2;
      (p->s).coord.x = cx2;
      dx2 = (p->s).coord.y;
      if ((u16)FUN_080098a4(cx2, dx2) != 0) {
        cx2 = (p->s).coord.x;
        dx2 = (p->s).d.x;
        cx2 -= dx2;
        (p->s).coord.x = cx2;
        dx2 = -dx2;
        (p->s).d.x = dx2;
        goto hit;
      }
      {
        register s32 cy asm("r1");
        register s32 dy asm("r0");
        cy = (p->s).coord.y;
        dy = (p->s).d.y;
        cy += dy;
        (p->s).coord.y = cy;
        if ((u16)FUN_080098a4((p->s).coord.x, cy) == 0) {
          break;
        }
        {
          register s32 cy2 asm("r0");
          register s32 dy2 asm("r1");
          cy2 = (p->s).coord.y;
          dy2 = (p->s).d.y;
          cy2 -= dy2;
          (p->s).coord.y = cy2;
          dy2 = -dy2;
          (p->s).d.y = dy2;
        }
      }
    hit:
      (p->s).work[3]++;
      break;
    }
  }
  if ((p->s).work[3] > 2) {
    CreateVFX56(&p->s, 1, 0);
    CreateVFX56(&p->s, 1, 0x20);
    CreateVFX56(&p->s, 1, 0x40);
    CreateVFX56(&p->s, 1, 0x60);
    CreateVFX56(&p->s, 1, 0x80);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Projectile29_Die(p);
  }
}


void Projectile29_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void Projectile29_Init(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile29Routine = {
    [ENTITY_INIT] =      Projectile29_Init,
    [ENTITY_UPDATE] =    Projectile29_Update,
    [ENTITY_DIE] =       Projectile29_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 5,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
};
