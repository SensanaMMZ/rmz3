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

#include "motion.h"

void PantheonBombProjectile_Update(struct Projectile* p);

// 0x080AD0BC
void PantheonBombProjectile_Init(struct Projectile* p) {
  register s32 w asm("r6");
  w = (p->s).work[1];
  if (w == 0) {
    struct Body* body;
    InitNonAffineMotion(&p->s);
    {
      register u8 fv asm("r0");
      register u8 k asm("r1");
      k = (p->s).flags;
      asm("" : "+r"(k));
      fv = 1;
      fv |= k;
      k = 2;
      fv |= k;
      k = 4;
      fv |= k;
      (p->s).flags = fv;
    }
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C84C, &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)w;
    SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = w;
    (p->s).mode[2] = w;
    (p->s).mode[3] = w;
  } else if (w == 1) {
    register s32 z5 asm("r5");
    register s32 z8 asm("r8");
    struct Body* body;
    InitScalerotMotion1(&p->s);
    {
      register u8* a asm("r1");
      register s32 k asm("r0");
      a = (u8*)p + 0x50;
      z5 = 0;
      {
        register s32 t0 asm("r0");
        t0 = 0;
        asm volatile("" : "+r"(t0));
        z8 = t0;
      }
      k = 0x100;
      *(u16*)a = k;
      asm("" : "+r"(a));
      a += 2;
      asm("" : "+r"(a));
      *(u16*)a = k;
    }
    (p->s).angle = z5;
    {
      register u8 fv2 asm("r0");
      register s32 k2 asm("r1");
      fv2 = (p->s).flags;
      k2 = 1;
      fv2 |= k2;
      k2 = 2;
      fv2 |= k2;
      k2 = 4;
      fv2 |= k2;
      (p->s).flags = fv2;
    }
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C84C, &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z8;
    {
      u32 tbl = (u32)gProjectileFnTable;
      u32 id = ((p->s).id) << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = w;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    (p->s).mode[1] = w;
    (p->s).mode[2] = z5;
    (p->s).mode[3] = z5;
  }
  (p->s).work[2] = 0xFF;
  PantheonBombProjectile_Update(p);
}


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

#include "physics.h"
void CreateSmoke(u8 n, struct Coord* c);

// 0x080ad240
void _pantheonBombAI(struct Projectile* p) {
  {
    register s32* st asm("r2");
    st = (s32*)((u8*)p + 0x8c);
    if ((*st & 0x200) != 0) {
      register s32 z asm("r1");
      z = 0;
      *st = z;
      {
        u8* a = (u8*)p + 0x90;
        *(s32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z;
      }
      (p->s).flags &= 0xFB;
      CreateSmoke(2, (struct Coord*)((u8*)p + 0x54));
      goto die;
    }
  }
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x690B);
      if ((p->s).work[0] == 0) {
        (p->s).d.x = -0x180;
      } else {
        (p->s).d.x = 0x180;
      }
      (p->s).d.y = 0x100;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 cx, cy, r;
      {
        s32 v = (p->s).d.y + 0x40;
        (p->s).d.y = v;
        if (v > 0x700) {
          (p->s).d.y = 0x700;
        }
      }
      cx = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = cx;
      cy = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = cy;
      r = PushoutToUp1(cx, cy + 0x500);
      if (r != 0) {
        (p->s).coord.y += r;
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      return;
    }
    case 2:
      SetMotion(&p->s, 0x690C);
      (p->s).work[3] = 0x30;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) != 3) {
        return;
      }
      goto adv;
    case 4:
      SetMotion(&p->s, 0x690D);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[3] != 0) {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) != 0) {
          return;
        }
      }
    adv:
      (p->s).mode[2]++;
      return;
    case 6: {
      register struct Coord* c asm("r4");
      (p->s).flags &= 0xFE;
      SetDDP(&p->body, (const struct Collision*)0x0836C87C);
      (p->s).work[3] = 0x14;
      c = (struct Coord*)((u8*)p + 0x54);
      CreateSmoke(1, c);
      PlaySound(0x35);
      createPantheonBombBlast(c, 0);
      createPantheonBombBlast(c, 1);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 7:
      if ((p->s).work[3] != 0) {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) != 0) {
          return;
        }
      }
      {
        register s32 z asm("r1");
        u8* a = (u8*)p + 0x8c;
        z = 0;
        *(s32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z;
      }
      (p->s).flags &= 0xFB;
      break;
    default:
      return;
  }
die:
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
}


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
