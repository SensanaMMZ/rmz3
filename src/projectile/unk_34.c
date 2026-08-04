#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "vfx.h"

static const ProjectileFunc sUpdates[4];
static const struct Collision sCollisions[5];

struct Projectile* FUN_080ac818(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 0;
    (p->s).work[1] = 0;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac880(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 1;
    (p->s).work[1] = 0;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac8e8(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 0;
    (p->s).work[1] = 1;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac950(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 1;
    (p->s).work[1] = 1;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac9b4(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 2;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

void Projectile34_Update(struct Projectile* p);

// 0x080ACA18
void Projectile34_Init(struct Projectile* p) {
  register u8 f asm("r1");
  register s32 z6 asm("r6");
  s32 w0;
  InitNonAffineMotion(&p->s);
  {
    register s32 k asm("r0");
    register s32 z2 asm("r2");
    f = (p->s).flags;
    k = 1;
    z2 = 0;
    asm volatile("" : "+r"(z2));
    z6 = 0;
    f |= k;
    k = 2;
    f |= k;
    asm volatile("" : "+r"(z2));
    f |= z2;
    (p->s).flags = f;
  }
  w0 = (p->s).work[0];
  if (w0 == 2) {
    struct Body* body;
    f |= COLLIDABLE;
    (p->s).flags = f;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C728, &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z6;
    {
      u32 tbl = (u32)gProjectileFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    (p->s).mode[1] = w0;
  } else if ((p->s).work[1] == 0) {
    struct Body* body;
    f |= COLLIDABLE;
    (p->s).flags = f;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C728, &(p->s).coord, 1);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z6;
    {
      u32 tbl = (u32)gProjectileFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    asm volatile("strb %0, [%1, #0xd]" :: "l"(z6), "l"(p) : "memory");
  } else {
    struct Body* body;
    f |= COLLIDABLE;
    (p->s).flags = f;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C728, &(p->s).coord, 1);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z6;
    {
      u32 tbl = (u32)gProjectileFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    (p->s).mode[1] = 3;
  }
  (p->s).mode[2] = z6;
  (p->s).mode[3] = z6;
  Projectile34_Update(p);
}

void Projectile34_Update(struct Projectile* p) {
  (sUpdates[(p->s).mode[1]])(p);
}

void Projectile34_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080acb54(struct Projectile* p) {
  if ((p->s).unk_28->mode[0] > 1) {
    CreateSmoke(3, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else {
    switch ((p->s).mode[2]) {
      case 0:
        if ((p->s).work[0] == 0) {
          SetMotion(&p->s, 0xa00);
        } else {
          SetMotion(&p->s, 0xa03);
        }
        (p->s).mode[2]++;
        // fallthrough
      case 1:
        UpdateMotionGraphic(&p->s);
        break;
    }
    if ((p->prevCoord).c.y == 0 || --(p->prevCoord).c.y == 0) {
      (p->s).work[2] = 0x7f;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_080acbe0(struct Projectile* p) {
  if ((p->s).unk_28->mode[0] > 1) {
    CreateSmoke(3, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else if (--(p->s).work[2] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0:
        if ((p->s).work[0] == 0) {
          SetMotion(&p->s, 0xa01);
          SetDDP(&p->body, &sCollisions[1]);
          (p->s).d.y = (p->prevCoord).c.x;
          (p->s).d.x = m;
        } else {
          SetMotion(&p->s, 0xa04);
          SetDDP(&p->body, &sCollisions[2]);
          (p->s).d.x = -(p->prevCoord).c.x;
          (p->s).d.y = m;
        }
        RNG_0202f388 = LCG(RNG_0202f388);
        (p->s).work[3] = (RNG_0202f388 >> 16) & 1;
        (p->s).mode[2]++;
        // fallthrough
      case 1:
        UpdateMotionGraphic(&p->s);
        if ((p->s).motion.state == 3) {
          (p->s).flags |= DISPLAY;
          (p->s).mode[2]++;
        }
        break;
      case 2:
        (p->s).coord.x += (p->s).d.x;
        (p->s).coord.y += (p->s).d.y;
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

// 0x080ACCF0
void FUN_080accf0(struct Projectile* p) {
  {
    register s32* st asm("r2");
    register s32 v asm("r0");
    register s32 k asm("r1");
    st = (s32*)((u8*)p + 0x8c);
    v = *st;
    k = 0x80 << 2;
    v &= k;
    if (v != 0) {
      register s32 z asm("r1");
      z = 0;
      *st = z;
      {
        register u8* a asm("r0");
        a = (u8*)p + 0x90;
        asm volatile("str %0, [%1]" ::"l"(z), "l"(a) : "memory");
        a += 4;
        asm("" : "+r"(a));
        *a = z;
      }
      {
        register u8 h asm("r1");
        register u8 g asm("r0");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFB;
        g &= h;
        (p->s).flags = g;
      }
      goto boom;
    }
  }
  if ((p->s).mode[2] != 0) {
    if ((p->s).d.y > 0) {
      register s32 h2 asm("r1");
      h2 = (u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y);
      if (h2 != 0) {
        if ((h2 & (0x80 << 8)) == 0) {
          goto boom;
        }
      }
    }
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 sd asm("r4");
      register u32 A asm("r6");
      register u32 C asm("r5");
      register const s32* row asm("r2");
      register u32* rp asm("r3");
      {
        register const s32* const* tb asm("r2");
        register s32 i asm("r0");
        register s32 three asm("r1");
        tb = (const s32* const*)0x0836C820;
        asm("" : "+r"(tb));
        i = *(s32*)((u8*)p + 0xb8);
        three = 3;
        i &= three;
        i <<= 2;
        i = i + (s32)tb;
        asm("" : "+r"(i));
        row = *(const s32* const*)i;
      }
      {
        register u32 raw asm("r1");
        register u32 t0 asm("r0");
        rp = &RNG_0202f388;
        t0 = *rp;
        asm("" : "+r"(t0));
        A = 0x343FD;
        raw = t0;
        raw = raw * A;
        C = 0x269EC3;
        raw += C;
        raw <<= 1;
        sd = raw >> 1;
        *rp = sd;
        {
          register s32 r1v asm("r1");
          register s32 msk asm("r0");
          r1v = raw >> 0x11;
          msk = 0x1f;
          r1v &= msk;
          (p->s).d.y = row[1] - r1v;
        }
        {
          register s32 base asm("r2");
          register u32 raw2 asm("r0");
          register s32 msk2 asm("r1");
          base = row[0];
          base -= 0x20;
          raw2 = sd;
          raw2 = raw2 * A;
          raw2 += C;
          raw2 <<= 1;
          {
            register u32 sd2 asm("r1");
            sd2 = raw2 >> 1;
            *rp = sd2;
          }
          raw2 >>= 0x11;
          msk2 = 0x3f;
          raw2 &= msk2;
          base += raw2;
          (p->s).d.x = base;
        }
      }
      SetMotion(&p->s, 0xC01);
      SetDDP(&p->body, (const struct Collision*)0x0836C770);
      (p->s).work[2] = 0x78;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if ((u8)(((u32)(p->s).work[2]) % 6) == 0) {
        CreateSmoke(3, &(p->s).coord);
      }
      {
        register s32 dy asm("r0");
        register s32 lim asm("r1");
        dy = (p->s).d.y;
        dy += 0x20;
        (p->s).d.y = dy;
        lim = 0xe0 << 3;
        if (dy > lim) {
          (p->s).d.y = lim;
        }
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0) {
        goto boom;
      }
      if ((u8)--(p->s).work[2] != 0) {
        break;
      }
    boom: {
      struct Coord c;
      register s32 k4 asm("r4");
      {
        register s32 kk asm("r1");
        kk = -0x900;
        c.x = (p->s).coord.x + kk;
      }
      {
        register s32 cy0 asm("r0");
        cy0 = (p->s).coord.y;
        k4 = 0x90 << 4;
        cy0 += k4;
        c.y = cy0;
      }
      CreateSmoke(3, &c);
      c.x = (p->s).coord.x + k4;
      {
        register s32 cy1 asm("r0");
        cy1 = (p->s).coord.y;
        cy1 += k4;
        c.y = cy1;
      }
      CreateSmoke(3, &c);
      {
        register s32 bx asm("r4");
        bx = (p->s).coord.x - 6;
        bx += ((u32)RANDOM(RNG_0202f388)) % 0xc;
        c.x = bx;
      }
      {
        register s32 kk2 asm("r1");
        kk2 = -0x900;
        c.y = (p->s).coord.y + kk2;
      }
      CreateSmoke(3, &c);
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
    }
  }
}


void FUN_080acea0(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8* a = (u8*)p + 0x8c;
      s32 z = 0;
      *(u32*)a = z;
      asm("" : "+r"(a));
      a += 4;
      *(u32*)a = z;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *a = z;
      (p->s).flags &= 0xFB;
      if ((p->s).work[0] == 0) {
        SetMotion(&p->s, 0xA00);
      } else {
        SetMotion(&p->s, 0xA03);
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      UpdateMotionGraphic(&p->s);
      {
        s32* w = (s32*)((u8*)p + 0xbc);
        s32 v = *w;
        if (v != 0) {
          v -= 1;
          *w = v;
          if (v != 0) {
            break;
          }
        }
      }
      (p->s).work[2] = 0x7F;
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      u8 w0 = (p->s).work[0];
      if (w0 == 0) {
        SetMotion(&p->s, 0xA01);
        SetDDP(&p->body, &sCollisions[1]);
        (p->s).d.y = *(s32*)((u8*)p + 0xb8);
        (p->s).d.x = w0;
      } else {
        SetMotion(&p->s, 0xA04);
        SetDDP(&p->body, &sCollisions[2]);
        (p->s).d.x = -*(s32*)((u8*)p + 0xb8);
        (p->s).d.y = 0;
      }
      (p->s).work[3] = RANDOM(RNG_0202f388) & 1;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).flags |= 1;
      (p->s).work[2] = 0xFF;
      (p->s).mode[2]++;
      break;
    case 4:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void Projectile34_Init(struct Projectile* p);
void Projectile34_Update(struct Projectile* p);
void Projectile34_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile34Routine = {
    [ENTITY_INIT] =      Projectile34_Init,
    [ENTITY_UPDATE] =    Projectile34_Update,
    [ENTITY_DIE] =       Projectile34_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080acb54(struct Projectile* p);
void FUN_080acbe0(struct Projectile* p);
void FUN_080accf0(struct Projectile* p);
void FUN_080acea0(struct Projectile* p);

static const ProjectileFunc sUpdates[4] = {
    FUN_080acb54,
    FUN_080acbe0,
    FUN_080accf0,
    FUN_080acea0,
};

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(48), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : 0x80,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(2), PIXEL(26), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(2), PIXEL(26), PIXEL(20)},
    },
};

static const s32 s32_ARRAY_0836c7a0[32] = {
    0x00000180, -0x00000340, -0x00000220, -0x00000260, -0x00000220, -0x00000300, 0x000002C0, -0x00000260, -0x00000180, -0x00000340, -0x00000200, -0x00000280, 0x00000160, -0x000001F0, 0x00000260, -0x00000280, 0x00000200, -0x00000440, 0x00000120, -0x000002A0, 0x00000120, -0x00000340, -0x000000B0, -0x000002A0, -0x00000200, -0x00000440, 0x00000120, -0x000002A0, 0x00000120, -0x00000340, -0x000000B0, -0x000002A0,
};

static const s32* const PTR_ARRAY_0836c820[4] = {
    &s32_ARRAY_0836c7a0[0],
    &s32_ARRAY_0836c7a0[8],
    &s32_ARRAY_0836c7a0[16],
    &s32_ARRAY_0836c7a0[24],
};
