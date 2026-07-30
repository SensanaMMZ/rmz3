#include "collision.h"
#include "global.h"
#include "story.h"
#include "projectile.h"

struct Projectile* createPantheonBomb(struct Coord* c1, struct Coord* c2, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 35);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    (p->s).work[1] = 0;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

struct Projectile* createPantheonBombBlast(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 35);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

INCASM("asm/projectile/pantheon_bomber_p3_p1.inc");

static const ProjectileFunc sUpdates[2];
void PantheonBombProjectile_Die(struct Projectile* p);

void PantheonBombProjectile_Update(struct Projectile* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    PantheonBombProjectile_Die(p);
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
}

void PantheonBombProjectile_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/pantheon_bomber_p3_p2.inc");

static const struct Collision sCollisions[4];

// Dispatch-shape basin: retail's cmp-tree (beq 1 / bgt / explicit ==0) with the
// mode load reused raw in the case-2 word store needs an SI-typed switch var
// whose u8 range is untracked; every spelling here either collapses the ==0
// test, copies the pinned reg, or extends the store operand.
NON_MATCH void pantheonBombBlastAI(struct Projectile* p) {
#if MODERN
  u32 m2 = (p->s).mode[2];
  switch (m2) {
    case 0:
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, 0x690E);
      if ((p->s).work[0] == 0) {
        (p->s).d.x = -0x280;
        (p->s).flags &= ~X_FLIP;
        (p->s).spr.xflip = m2;
        (p->s).spr.oam.xflip = 0;
      } else {
        (p->s).d.x = 0x280;
        SET_XFLIP(p, 1);
      }
      (p->s).d.y = 0x100;
      (p->s).work[3] = 0x24;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[3] != 0) {
        (p->s).work[3]--;
      }
      if ((p->s).work[3] <= 9) {
        s32 m = (p->s).d.y;
        m += ((0x10 - m) << 4) >> 8;
        (p->s).d.y = m;
        (p->s).spr.mag.x = m;
        (p->s).spr.mag.y = (p->s).d.y;
      }
      if ((p->s).work[3] == 4) {
        (p->body).status = 0;
        (p->body).prevStatus = 0;
        (p->body).invincibleTime = 0;
        (p->s).flags &= ~COLLIDABLE;
      } else {
        s32 r;
        if ((p->s).d.x < 0) {
          r = PushoutToRight1((p->s).coord.x + -0x800, (p->s).coord.y);
        } else {
          r = PushoutToLeft1((p->s).coord.x + 0x800, (p->s).coord.y);
        }
        if (r != 0) {
          if ((p->s).work[3] > 0xA) {
            (p->s).work[3] = 0xA;
          }
          (p->s).mode[2]++;
        }
      }
      if ((p->s).work[3] == 0) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
    case 2: {
      s32 m = (p->s).d.y;
      u8 w3;
      m += ((0x10 - m) << 4) >> 8;
      (p->s).d.y = m;
      (p->s).spr.mag.x = m;
      (p->s).spr.mag.y = (p->s).d.y;
      w3 = (p->s).work[3];
      if (w3 != 0) {
        s32 t = w3 - 1;
        (p->s).work[3] = t;
        if ((u32)(t << 24) != 0) {
          break;
        }
      }
      {
        u32 tbl = (u32)gProjectileFnTable;
        u32 id = (p->s).id << 2;
        EntityFunc** rt = (EntityFunc**)(tbl + id);
        *(u32*)((p->s).mode) = m2;
        (p->s).onUpdate = (void*)(*rt)[ENTITY_DIE];
      }
      break;
    }
  }
#else
  INCCODE("asm/projectile/pantheon_bomber_blast.inc");
#endif
}

void PantheonBombProjectile_Init(struct Projectile* p);
void PantheonBombProjectile_Update(struct Projectile* p);
void PantheonBombProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gPantheonBombProjectileRoutine = {
    [ENTITY_INIT] =      PantheonBombProjectile_Init,
    [ENTITY_UPDATE] =    PantheonBombProjectile_Update,
    [ENTITY_DIE] =       PantheonBombProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void _pantheonBombAI(struct Projectile* p);
void pantheonBombBlastAI(struct Projectile* p);

static const ProjectileFunc sUpdates[2] = {
    _pantheonBombAI,
    pantheonBombBlastAI,
};

// --------------------------------------------

static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : 0x80,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(28), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
};
