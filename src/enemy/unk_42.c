#include "collision.h"
#include "enemy.h"
#include "global.h"

// ブリザック・スタグロフ関連？

static void Enemy42_Init(struct Entity* p);
static void Enemy42_Update(struct Entity* p);
static void Enemy42_Die(struct Entity* p);

// clang-format off
const EnemyRoutine gEnemy42Routine = {
    [ENTITY_INIT] =      (EnemyFunc)Enemy42_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Enemy42_Update,
    [ENTITY_DIE] =       (EnemyFunc)Enemy42_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateEnemy42(struct Entity* e, u8 type, u8 param_3) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_42);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = type, p->work[1] = param_3;
    p->unk_28 = e;
    p->coord = *(&e->coord);
    return p;
  } else {
    return NULL;
  }
}

// --------------------------------------------

void FUN_08084e7c(struct Enemy* p);
void FUN_08084f18(struct Enemy* p);
void FUN_08084fb4(struct Enemy* p);

static void Enemy42_Init(struct Entity* p) {
  static const EnemyFunc sInitializers[3] = {
      (EnemyFunc)FUN_08084e7c,
      (EnemyFunc)FUN_08084f18,
      (EnemyFunc)FUN_08084fb4,
  };
  (sInitializers[(p->work)[0]])((void*)p);
}

void FUN_08085060(struct Enemy* p);
void FUN_08085124(struct Enemy* p);
void FUN_080852f4(struct Enemy* p);

static void Enemy42_Update(struct Entity* p) {
  static const EnemyFunc sUpdates[3] = {
      (EnemyFunc)FUN_08085060,
      (EnemyFunc)FUN_08085124,
      (EnemyFunc)FUN_080852f4,
  };
  (sUpdates[(p->work)[0]])((void*)p);
}

void FUN_0808534c(struct Enemy* p);
void FUN_0808537c(struct Enemy* p);
static void FUN_08085578(struct Entity* p);

static void Enemy42_Die(struct Entity* p) {
  static const EnemyFunc sDeads[3] = {
      (EnemyFunc)FUN_0808534c,
      (EnemyFunc)FUN_0808537c,
      (EnemyFunc)FUN_08085578,
  };
  (sDeads[(p->work)[0]])((void*)p);
}

// 0x08084e7c
void FUN_08084e7c(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  s32 one;
  s32 z;
  {
    u32 tbl, id;
    EntityFunc** routine_table;
    tbl = (u32)gEnemyFnTable;
    id = ((p->s).id) << 2;
    routine_table = (EntityFunc**)(tbl + id);
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*routine_table)[ENTITY_UPDATE];
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    u8 t = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    asm("" : "+l"(z));
    fv |= t;
    fv |= FLIPABLE;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, *(u16*)((u8*)p + 0xbc));
  (p->s).flags2 |= WHITE_PAINTABLE;
  (p->s).invincibleID = q->uniqueID;
  SET_XFLIP(&p->s, (q->flags >> 4) & one);
  (p->s).coord = q->coord;
  (p->s).taskCol = 0x17;
  (p->s).mode[2] = 1;
  asm volatile("" ::"l"(z));
  Enemy42_Update(&p->s);
}

s32 FUN_0800a22c(s32 x, s32 y);
s32 FUN_0800a31c(s32 x, s32 y);

// 0x08084f18
void FUN_08084f18(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register s32 dz asm("r5");
    u8 t = (p->s).flags;
    fv = FLIPABLE;
    dz = 0;
    asm("" : "+r"(dz));
    asm volatile("" ::"r"(dz));
    fv |= t;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0x62, 0x09));
  SET_XFLIP(&p->s, (p->s).work[1]);
  if (((p->s).flags & X_FLIP) != 0) {
    (p->s).coord.x = FUN_0800a22c((p->s).coord.x, (p->s).coord.y);
  } else {
    (p->s).coord.x = FUN_0800a31c((p->s).coord.x, (p->s).coord.y);
  }
  {
    s32 z = 0;
    (p->s).work[2] = z;
    (p->s).work[3] = z;
    (p->s).d.y = z;
  }
  Enemy42_Update(&p->s);
}

// 0x08084fb4
void FUN_08084fb4(struct Enemy* p) {
  register struct Entity* q asm("r6");
  s32 z;
  q = (p->s).unk_28;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register u8 fv asm("r0");
    u8 t = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    asm("" : "+l"(z));
    fv |= t;
    fv |= FLIPABLE;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0xB4, 0x0D));
  SET_XFLIP(&p->s, (p->s).work[1]);
  (p->s).flags2 |= WHITE_PAINTABLE;
  (p->s).invincibleID = q->uniqueID;
  if (((p->s).flags & X_FLIP) != 0) {
    (p->s).d.x = -0x80;
    (p->s).unk_coord.x = 2;
  } else {
    (p->s).d.x = 0x80;
    (p->s).unk_coord.x = -2;
  }
  (p->s).work[2] = 0;
  asm volatile("" ::"l"(z));
  Enemy42_Update(&p->s);
}

// 0x08085060
void FUN_08085060(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  u8 f;
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, *(u16*)((u8*)p + 0xbc));
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  {
    s8* c = (s8*)((u8*)q + 0xe0);
    s32 cv = *(u8*)c;
    if (*c == 0) {
      register u8 fl asm("r1");
      register u8 fv asm("r0");
      fl = (p->s).flags;
      fv = 1;
      fv |= fl;
      (p->s).flags = fv;
      goto fdone;
    }
    cv--;
    *(u8*)c = cv;
    if ((s8)cv <= 0x1f) {
      if ((cv & 3) > 1) {
        register s32 k1 asm("r1");
        register u8 fv2 asm("r0");
        fv2 = (p->s).flags;
        k1 = 1;
        fv2 |= k1;
        (p->s).flags = fv2;
        goto fdone;
      }
    }
    {
      register u8 fl2 asm("r1");
      register u8 fv3 asm("r0");
      fl2 = (p->s).flags;
      asm("" : "+r"(fl2));
      fv3 = 0xFE;
      fv3 &= fl2;
      (p->s).flags = fv3;
    }
  fdone:;
  }
  {
    register s32 xf2 asm("r2");
    register s32 xfc asm("r1");
    {
      u32 qf = q->flags;
      register s32 one asm("r0");
      asm volatile("lsr %0, %1, #0x4" : "=l"(xf2) : "l"(qf));
      one = 1;
      xf2 &= one;
    }
    if (xf2 != 0) {
      register u8 fl3 asm("r1");
      register u8 fv3 asm("r0");
      fl3 = (p->s).flags;
      fv3 = 0x10;
      fv3 |= fl3;
      (p->s).flags = fv3;
    } else {
      register u8 fl4 asm("r1");
      register u8 fv4 asm("r0");
      fl4 = (p->s).flags;
      asm("" : "+r"(fl4));
      fv4 = 0xEF;
      fv4 &= fl4;
      (p->s).flags = fv4;
    }
    xfc = xf2;
    asm("" : "+r"(xfc));
    ((p->s).spr).xflip = xfc;
    {
      u8* oa = (u8*)p + 0x4a;
      s32 sh = xfc << 4;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh;
    }
  }
  (p->s).coord = q->coord;
  if ((p->s).mode[3] != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Enemy42_Die(&p->s);
  }
}

INCASM("asm/enemy/unk_42_p1_a_b.inc");

void FUN_080852f4(struct Enemy* p) {
  UpdateMotionGraphic(&p->s);
  if ((p->s).mode[3] == 0) {
    (p->s).coord.x += (p->s).d.x;
    (p->s).d.x += (p->s).unk_coord.x;
    if ((p->s).work[2]++ > 0x40) {
      (p->s).mode[3]++;
      (p->s).work[2] = 0;
    }
  } else {
    if (((p->s).unk_28)->mode[3] > 3) {
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
}

void FUN_0808534c(struct Enemy* p) {
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/unk_42_p2.inc");

// --------------------------------------------

static void FUN_08085578(struct Entity* p) { SET_ENEMY_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(4), -PIXEL(30), PIXEL(8), PIXEL(60)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {PIXEL(4), -PIXEL(30), PIXEL(8), PIXEL(60)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(29), PIXEL(16), PIXEL(62)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {PIXEL(8), -PIXEL(29), PIXEL(16), PIXEL(62)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(11), -PIXEL(28), PIXEL(22), PIXEL(64)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {PIXEL(11), -PIXEL(28), PIXEL(22), PIXEL(64)},
    },
};
