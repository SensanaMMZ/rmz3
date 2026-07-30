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

INCASM("asm/projectile/unk_29_p2.inc");

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
