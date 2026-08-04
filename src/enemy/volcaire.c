#include "zero.h"
#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "stagerun.h"
#include "motion.h"
#include "story.h"

struct Volcaire {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 unk_b4[4];
  u8 unk_b8;
  u8 unk_b9[3];
  u8 unk_bc[8];
};
static_assert(sizeof(struct Volcaire) == sizeof(struct Enemy));

void Volcaire_Init(struct Enemy* p);
void Volcaire_Update(struct Enemy* p);
void Volcaire_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gVolcaireRoutine = {
    [ENTITY_INIT] =      Volcaire_Init,
    [ENTITY_UPDATE] =    Volcaire_Update,
    [ENTITY_DIE] =       Volcaire_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

s32 FUN_08077110(struct Enemy* p, s32 x) {
  s32 dx;

  if (x != 0) {
    (p->s).coord.x += x;
    if (x < 0) {
      dx = PushoutToRight1((p->s).coord.x - PIXEL(2), (p->s).coord.y - PIXEL(8));
      if (dx > 0) {
        (p->s).coord.x += dx;
        return 1;
      }
    } else {
      dx = PushoutToLeft1((p->s).coord.x + PIXEL(2), (p->s).coord.y - PIXEL(8));
      if (dx < 0) {
        (p->s).coord.x += dx;
        return 2;
      }
    }
  }

  return 0;
}

void FUN_08077174(struct Entity* e) {
  struct Entity* p = AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_VOLCAIRE);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = 1;
    (p->coord).x = (e->coord).x, (p->coord).y = (e->coord).y;
    p->unk_28 = e;
  }
}

void FUN_080771cc(struct Volcaire* e, s32 x, s32 y, u8 n) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_VOLCAIRE);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = 2;
    p->coord.x = x, p->coord.y = y;
    if (n == 0) {
      p->coord.x = x - PIXEL(2);
      p->coord.y = y + PIXEL(8);
    } else {
      p->coord.x = x + PIXEL(2);
      p->coord.y = y + PIXEL(7);
    }
    p->work[2] = n;
    if (e != NULL) {
      e->unk_b8++;
    }
    p->unk_28 = (void*)e;
  }
}

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  // NOP
  return;
}

NAKED static bool8 FUN_08077260(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, lr}\n\
	adds r2, r0, #0\n\
	adds r3, r2, #0\n\
	adds r3, #0x8c\n\
	ldr r0, [r3]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080772F0\n\
	ldrb r4, [r2, #0x10]\n\
	cmp r4, #1\n\
	bne _080772B0\n\
	ldr r1, _080772A8 @ =gEnemyFnTable\n\
	ldrb r0, [r2, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r5, #2\n\
	str r5, [r2, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r2, #0x14]\n\
	ldr r1, [r3]\n\
	movs r0, #0x80\n\
	lsls r0, r0, #9\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080772DC\n\
	movs r0, #0x80\n\
	lsls r0, r0, #0xa\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080772AC\n\
	strb r5, [r2, #0xd]\n\
	b _080772E6\n\
	.align 2, 0\n\
_080772A8: .4byte gEnemyFnTable\n\
_080772AC:\n\
	strb r0, [r2, #0xd]\n\
	b _080772E6\n\
_080772B0:\n\
	ldr r1, [r2, #0x28]\n\
	cmp r1, #0\n\
	beq _080772BE\n\
	adds r1, #0xb8\n\
	ldrb r0, [r1]\n\
	subs r0, #1\n\
	strb r0, [r1]\n\
_080772BE:\n\
	ldr r1, _080772E0 @ =gEnemyFnTable\n\
	ldrb r0, [r2, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r4, #2\n\
	str r4, [r2, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r2, #0x14]\n\
	ldr r1, [r3]\n\
	movs r0, #0x80\n\
	lsls r0, r0, #0xa\n\
	ands r1, r0\n\
	cmp r1, #0\n\
	beq _080772E4\n\
_080772DC:\n\
	strb r4, [r2, #0xd]\n\
	b _080772E6\n\
	.align 2, 0\n\
_080772E0: .4byte gEnemyFnTable\n\
_080772E4:\n\
	strb r1, [r2, #0xd]\n\
_080772E6:\n\
	adds r0, r2, #0\n\
	bl Volcaire_Die\n\
	movs r0, #1\n\
	b _080772F2\n\
_080772F0:\n\
	movs r0, #0\n\
_080772F2:\n\
	pop {r4, r5}\n\
	pop {r1}\n\
	bx r1\n\
 .syntax divided\n");
}


extern const EnemyFunc sUpdates1[];
extern const EnemyFunc sUpdates2[];

// 0x080772f8
bool8 FUN_080772f8(struct Enemy* p) {
  if ((p->s).mode[1] != 7) {
    s32 v = *(s32*)&p->props[0];
    if (v == 0) {
      switch ((p->s).mode[3]) {
        case 0:
          if (IsFrozen(&p->s)) {
            (sUpdates1[(p->s).mode[1]])(p);
            (sUpdates2[(p->s).mode[1]])(p);
            (p->s).mode[3]++;
            UpdateMotionGraphic(&p->s);
            return TRUE;
          }
          break;
        case 1:
          if (IsFrozen(&p->s)) {
            if (((p->body).status & 0x00020001) == 0x00020001) {
              (p->s).mode[3] = 0;
            } else {
              return TRUE;
            }
          } else {
            (p->s).mode[3] = 0;
          }
          break;
      }
    }
  }
  return FALSE;
}

#include "element.h"
#include "mission.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_08077388(struct Enemy* p) {
  struct VFX** slot;
  u32 frozen;

  if ((p->s).work[0] != 0) {
    slot = (struct VFX**)&p->props[0];
    if (*slot == NULL && ((p->body).status & 1)) {
      frozen = (p->body).status & 0x20000;
      if (frozen != 0) {
        (p->s).mode[1] = 7;
        (p->s).mode[2] = 0;
      } else {
        *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
        if (*slot != NULL) {
          (p->s).mode[1] = 0;
          (p->s).mode[2] = 0;
        }
      }
    }
  }
}

static const u8 sInitModes[];
static const struct Collision sCollisions[];
static void onCollision(struct Body* body, struct Coord* r1, struct Coord* r2);

// 0x080773DC
// Blocker: retail shares only the `bl InitBody` between the two InitBody
// arms -- arm 1 branches to the `bl` that physically ends arm 2, so the
// 6-instruction argument setup is duplicated. Writing the call in both arms
// leaves each with its own `bl` (+4 bytes); hoisting to one call with an
// `hp` variable also merges the argument setup (-12 bytes). 11 lever rounds.
NON_MATCH void Volcaire_Init(struct Enemy* p) {
#if MODERN
  register s32 z2 asm("r2");
  s32 w;
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  {
    u8 v = sInitModes[(p->s).work[0]];
    z2 = 0;
    (p->s).mode[1] = v;
  }
  {
    register u8 fv asm("r0");
    register u8 k asm("r1");
    fv = (p->s).flags;
    k = 2;
    fv |= k;
    (p->s).flags = fv;
  }
  w = (p->s).work[0];
  asm("" : "+r"(w));
  if (w == 0) {
    *((u8*)p + 0xb8) = z2;
    {
      register u8 g asm("r0");
      register u8 h asm("r1");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g = 0xFE;
      g &= h;
      (p->s).flags = g;
    }
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) + (0xC0 << 5);
  } else if (w < 0) {
    goto done;
  } else if (w > 2) {
    goto done;
  } else {
    register s32 z5 asm("r5");
    register struct Body* b asm("r4");
    s32 hp;
    *((u8*)p + 0xb9) = z2;
    {
      register u8 fv2 asm("r0");
      register u8 k2 asm("r1");
      fv2 = (p->s).flags;
      k2 = 1;
      fv2 |= k2;
      (p->s).flags = fv2;
    }
    InitNonAffineMotion(&p->s);
    if ((gSystemSavedataManager.mods[13] & 0x20) != 0) {
      register s32 t asm("r0");
      register u8 gf asm("r1");
      gf = gCurStory.s.gameflags[0];
      t = 0x40;
      t &= gf;
      asm("" : "+r"(t));
      t <<= 24;
      asm("" : "+r"(t));
      z5 = (u32)t >> 24;
      if (z5 != 0) {
        goto armB;
      }
      {
        register u8 g3 asm("r0");
        register u8 h3 asm("r1");
        g3 = (p->s).flags;
        h3 = 4;
        g3 |= h3;
        (p->s).flags = g3;
      }
      b = &p->body;
      InitBody(b, &sCollisions[0], &(p->s).coord, 0xA);
    } else {
    armB : {
      register u8 h4 asm("r1");
      register u8 g4 asm("r0");
      h4 = (p->s).flags;
      g4 = 4;
      z5 = 0;
      g4 |= h4;
      (p->s).flags = g4;
    }
    b = &p->body;
    InitBody(b, &sCollisions[0], &(p->s).coord, 6);
    }
    b->parent = (struct CollidableEntity*)p;
    b->fn = (void*)z5;
    asm volatile("" ::: "memory");
    b->fn = (void*)onCollision;
    *(s32*)((u8*)p + 0xb4) = 0;
  }
done:;
  Volcaire_Update(p);
#else
  INCCODE("asm/enemy/volcaire_p1_a_b.inc");
#endif
}

static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];
void FUN_08077388(struct Enemy* p);

void Volcaire_Update(struct Enemy* p) {
  u8 sf = gCurStory.s.gameflags[4] & 2;
  if (sf == 0) {
    if ((p->s).work[0] == 0) {
      goto dispatch;
    }
    {
      struct Entity* par = (p->s).unk_28;
      if (par != NULL) {
        if (par->mode[0] > 1) {
          (p->s).unk_28 = (struct Entity*)(u32)sf;
          par = NULL;
        }
      }
      if ((gCurStory.s.gameflags[4] & 0x40) == 0) {
        goto dispatch;
      }
      if (par != NULL) {
        ((struct Enemy*)par)->props[4]--;
      }
    }
  }
  (p->s).flags &= ~DISPLAY;
  (p->s).flags &= ~FLIPABLE;
  EXIT_BODY(p);
  (p->s).flags &= ~COLLIDABLE;
  SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  return;

dispatch:
  if (FUN_08077260(p)) {
    return;
  }
  FUN_08077388(p);
  if (FUN_080772f8(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

static const EnemyFunc sDeads[3];

void Volcaire_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeads[(p->s).mode[1]])(p);
}

void nop_08077608(struct Enemy* p) {}


void FUN_0807760c(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

static const struct Collision sCollisions[13];

void FUN_0807762c(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)&p->props[0];
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    if ((p->s).work[0] == 1) {
      SetDDP(&p->body, &sCollisions[1]);
    } else {
      SetDDP(&p->body, &sCollisions[7]);
    }
    if (!IsFrozen(&p->s)) {
      if ((p->s).work[0] == 1) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 2;
      } else {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

void FUN_080776ac(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[0] == 1) {
        SetDDP(&p->body, &sCollisions[2]);
        SetMotion(&p->s, MOTION(0x2E, 0x00));
      } else {
        SetDDP(&p->body, &sCollisions[8]);
        GotoMotion(&p->s, MOTION(0x2E, 0x05), 4, 1);
      }
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 hit;
      u8* flag9;
      if (IsFrozen(&p->s)) {
        goto update;
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      hit = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (hit >= 0) {
        goto update;
      }
      {
        u16 at = GetMetatileAttr((p->s).coord.x, (p->s).coord.y);
        s32 masked = at & 0x10;
        flag9 = (u8*)p + 0xb9;
        if (masked == 0 && *flag9 == 0) {
          (p->s).coord.y += hit;
          goto update;
        }
      }
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
        if ((p->s).work[0] == 2) {
          struct Entity* q = (p->s).unk_28;
          if (q != NULL) {
            *((u8*)q + 0xb8) -= 1;
          }
        }
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      *flag9 = 1;
    update:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080777cc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((p->s).work[3] != 0) {
        (p->s).work[2] = 0xC0;
      } else {
        (p->s).work[3] = 1;
        (p->s).work[2] = 0x28;
      }
      (p->s).mode[2]++;
      // fallthrough
    case 2:
      if ((u8)--(p->s).work[2] == 0) {
        if (p->props[4] <= 3) {
          FUN_08077174(&p->s);
        }
        (p->s).mode[2] = 1;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// 0x08077834
void FUN_08077834(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, (const struct Collision*)0x083672D0);
      (p->s).d.y = -0x800;
      SetMotion(&p->s, MOTION(0x2E, 0x00));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 dy = (p->s).d.y + 0x40;
      (p->s).d.y = dy;
      (p->s).coord.y += dy;
      if (dy > 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetMotion(&p->s, MOTION(0x2E, 0x01));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      register u8 st asm("r5");
      UpdateMotionGraphic(&p->s);
      st = *(u8*)((u8*)p + 0x73);
      if (st != 3) {
        break;
      }
      FUN_080771cc((struct Volcaire*)(p->s).unk_28, (p->s).coord.x, (p->s).coord.y, 0);
      FUN_080771cc((struct Volcaire*)(p->s).unk_28, (p->s).coord.x, (p->s).coord.y, 1);
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        register s32 z asm("r2");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFE;
        g &= h;
        z = 0;
        h = 0xFD;
        g &= h;
        (p->s).flags = g;
        {
          u8* a = (u8*)p + 0x8c;
          *(u32*)a = z;
          asm("" : "+r"(a));
          a += 4;
          asm("" : "+r"(a));
          *(u32*)a = z;
          asm("" : "+r"(a));
          a += 4;
          asm("" : "+r"(a));
          *a = z;
        }
      }
      (p->s).flags &= 0xFB;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
    }
  }
}

// 0x08077910
void FUN_08077910(struct Enemy* p) {
  struct Entity* e = (p->s).unk_28;
  s32 hit;
  u8* flag9;

  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[2] == 0) {
        SetMotion(&p->s, MOTION(0x2E, 0x02));
        SetDDP(&p->body, &sCollisions[3]);
      } else {
        SetMotion(&p->s, MOTION(0x2E, 0x03));
        SetDDP(&p->body, &sCollisions[5]);
      }
      (p->s).work[3] = 8;
      (p->s).d.x = ((p->s).work[2] << 15) - 0x4000;
      (p->s).d.x = (p->s).d.x / 32;
      (p->s).d.y = 0;
      goto inc;
    case 2:
      (p->s).work[3] = 8;
      SetDDP(&p->body, &sCollisions[7]);
      SetMotion(&p->s, MOTION(0x2E, 0x04));
      SET_XFLIP(p, (p->s).work[2]);
    inc:
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
    case 3:
      if ((u8)--(p->s).work[3] == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 4:
      SetMotion(&p->s, MOTION(0x2E, 0x05));
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
      break;
    case 5:
      break;
  }
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  (p->s).coord.y += (p->s).d.y;
  hit = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
  flag9 = (u8*)p + 0xb9;
  if (hit < 0) {
    u16 at = GetMetatileAttr((p->s).coord.x, (p->s).coord.y);
    if ((at & 0x10) == 0 && *flag9 == 0) {
      (p->s).coord.y += hit;
      (p->s).mode[1] = 4;
      (p->s).mode[2] = 0;
    } else {
      *flag9 = 1;
    }
  }
  if (*flag9 == 0) {
    FUN_08077110(p, (p->s).d.x);
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > (0xc0 << 7)) {
    if (e != NULL) {
      *((u8*)e + 0xb8) -= 1;
    }
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}


void FUN_08077af8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x2e, 5));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x08077B38
void FUN_08077b38(struct Enemy* p) {
  register struct Entity* e asm("r6");
  register s32 k10 asm("r5");
  register u32 fl asm("r2");
  register s32 v asm("r1");
  register u8 g asm("r0");
  e = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dx asm("r2");
      SetDDP(&p->body, (const struct Collision*)0x08367390);
      SetMotion(&p->s, 0x2E06);
      {
        register s32 k asm("r0");
        k = 0xFFFFFE80;
        (p->s).d.x = k;
        dx = k;
        if (((p->s).flags & 0x10) != 0) {
          dx = 0xc0 << 1;
        }
        (p->s).d.x = dx;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 y asm("r2");
      (p->s).coord.x = (p->s).coord.x + (p->s).d.x;
      y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      {
        register s32 d asm("r0");
        register s32 lim asm("r1");
        d = y - (p->s).coord.y;
        lim = 0x80 << 4;
        if (d <= lim) {
          goto ok;
        }
      }
      {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
        goto cam;
      }
    ok:
      (p->s).coord.y = y;
      {
        register u32 f0 asm("r1");
        register s32 t asm("r0");
        f0 = (p->s).flags;
        k10 = 0x10;
        t = 0x10;
        t &= f0;
        if (t != 0) {
          goto left;
        }
      }
      {
        if (PushoutToRight1((p->s).coord.x + 0xFFFFF600, y + 0xFFFFF800) <= 0) {
          goto cam;
        }
        (p->s).d.x = -(p->s).d.x;
        fl = (p->s).flags;
        {
          register s32 t2 asm("r0");
          t2 = fl >> 4;
          v = 1;
          v &= ~t2;
        }
        if (v == 0) {
          goto neg;
        }
        g = k10;
        g |= fl;
        goto join;
      }
    left:
      {
        if (PushoutToLeft1((p->s).coord.x + (0xa0 << 4), y + 0xFFFFF800) >= 0) {
          goto cam;
        }
        (p->s).d.x = -(p->s).d.x;
        fl = (p->s).flags;
        {
          register s32 t2 asm("r0");
          t2 = fl >> 4;
          v = 1;
          v &= ~t2;
        }
        if (v == 0) {
          goto neg;
        }
        g = fl;
        g |= k10;
        goto join;
      neg:
        g = 0xEF;
        g &= fl;
      }
    join:
      (p->s).flags = g;
      *((u8*)p + 0x4c) = v;
      {
        register u8* oa asm("r3");
        register s32 sh asm("r1");
        oa = (u8*)p + 0x4a;
        sh = v << 4;
        {
          register s32 ov asm("r2");
          register s32 m11 asm("r0");
          ov = *oa;
          m11 = 0x11;
          m11 = -m11;
          m11 &= ov;
          m11 |= sh;
          *oa = m11;
        }
      }
    cam:
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > (0xc0 << 7)) {
        if (e != NULL) {
          register u8* c asm("r1");
          c = (u8*)e;
          c += 0xb8;
          *c = *c - 1;
        }
        {
          register u8 g2 asm("r0");
          register u8 h2 asm("r1");
          register s32 z asm("r2");
          h2 = (p->s).flags;
          asm("" : "+r"(h2));
          g2 = 0xFE;
          g2 &= h2;
          z = 0;
          h2 = 0xFD;
          g2 &= h2;
          (p->s).flags = g2;
          {
            u8* a = (u8*)p + 0x8c;
            *(u32*)a = z;
            asm("" : "+r"(a));
            a += 4;
            asm("" : "+r"(a));
            *(u32*)a = z;
            asm("" : "+r"(a));
            a += 4;
            asm("" : "+r"(a));
            *a = z;
          }
        }
        (p->s).flags &= 0xFB;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x08077CA4
void FUN_08077ca4(struct Enemy* p) {
  struct Entity* q = (p->s).unk_28;
  register u8* fp asm("r6");
  register s32 r asm("r5");
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 cx;
      u8* f0 = (u8*)p + 0xb9;
      u8 fv = *f0;
      asm volatile("add %0, %1, #0" : "=&l"(fp) : "l"(f0));
      if (fv == 0) {
        cx = (p->s).coord.x + (p->s).d.x;
        (p->s).coord.x = cx;
        if (((p->s).flags & 0x10) == 0) {
          r = PushoutToRight1(cx, (p->s).coord.y + -0x800);
          if (r <= 0) {
            goto nopush;
          }
          goto push;
        } else {
          r = PushoutToLeft1(cx, (p->s).coord.y + -0x800);
          if (r < 0) {
          push:
            (p->s).coord.x += r;
          }
        }
      }
    nopush:;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0xE0 * 8) {
        (p->s).d.y = 0xE0 * 8;
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (r < 0) {
        u32 at = (u16)GetMetatileAttr((p->s).coord.x, (p->s).coord.y);
        asm("" : "+r"(at));
        if ((at & 0x10) != 0) {
          goto hit;
        }
        if (*fp != 0) {
          goto hit;
        }
        (p->s).coord.y += r;
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 1;
        goto aftr;
      hit:
        *fp = 1;
      aftr:;
      }
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0xC0 * 128) {
        s32 zero;
        u8* a;
        if (q != NULL) {
          u8* c = (u8*)q + 0xb8;
          *c = *c - 1;
        }
        (p->s).flags &= ~DISPLAY;
        zero = 0;
        (p->s).flags &= ~FLIPABLE;
        a = (u8*)p + 0x8c;
        *(u32*)a = zero;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = zero;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = zero;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void MaybeKillVolcaire(struct Enemy* p);

// 0x08077DD0
void FUN_08077dd0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 dist asm("r6");
      s32 dx, dy;
      if ((p->s).work[0] == 1) {
        SetDDP(&p->body, (const struct Collision*)0x083673C0);
        SetMotion(&p->s, MOTION(0x2E, 0x00));
      } else {
        SetDDP(&p->body, (const struct Collision*)0x083673D8);
        GotoMotion(&p->s, MOTION(0x2E, 0x05), 4, 1);
      }
      {
        struct Zero* z = pZero2;
        dx = (p->s).coord.x - (z->s).coord.x;
        (p->s).d.x = dx;
        dy = (p->s).coord.y + -0x1800;
        dy -= (z->s).coord.y;
        (p->s).d.y = dy;
      }
      dx >>= 8;
      dist = dx * dx;
      dy >>= 8;
      dist += dy * dy;
      dist = Sqrt(dist) << 8;
      if (dist == 0) {
        goto zerocase;
      }
      {
        s32 nx = ((p->s).d.x << 8) / dist;
        s32 ny;
        (p->s).d.x = nx;
        ny = ((p->s).d.y << 8) / dist;
        (p->s).d.x = (nx * 2 + nx) * 2;
        (p->s).d.y = (ny * 2 + ny) * 2;
      }
      goto donev;
    zerocase:
      (p->s).d.x = 0xC0 * 8;
      (p->s).d.y = dist;
    donev:;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register u8* fp asm("r4");
      register s32 r asm("r6");
      s32 cy;
      {
        u8* f0 = (u8*)p + 0xb9;
        u8 fv = *f0;
        asm volatile("add %0, %1, #0" : "=&l"(fp) : "l"(f0));
        if (fv == 0) {
          (p->s).coord.x += (p->s).d.x;
        }
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0xE0 * 8) {
        (p->s).d.y = 0xE0 * 8;
      }
      cy = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = cy;
      if ((p->s).d.y > 0) {
        r = PushoutToUp1((p->s).coord.x, cy);
        if (r < 0) {
          u32 at = (u16)GetMetatileAttr((p->s).coord.x, (p->s).coord.y);
          asm("" : "+r"(at));
          if ((at & 0x10) != 0) {
            goto hit;
          }
          if (*fp != 0) {
            goto hit;
          }
          (p->s).coord.y += r;
          MaybeKillVolcaire(p);
          return;
        hit:
          *fp = 1;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}


struct Entity* FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
static const motion_t sMotions[4];

// 0x08077f0c
void MaybeKillVolcaire(struct Enemy* p) {
  struct Coord c;
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  {
    u8 f = (p->s).flags & ~COLLIDABLE;
    f &= ~DISPLAY;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(16);
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080b7f70(&p->s, &c, (motion_t*)sMotions, 3);
  TryDropItem(1, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);
void FUN_080b84f4(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame);

// 0x08077FA4
void FUN_08077fa4(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0: {
      u32 d0 = 0;
      u32 dir;
      u32 xf;
      s32 sh;
      if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
        d0 = 1;
      }
      asm volatile("add %0, %1, #0" : "=&l"(dir) : "l"(d0));
      asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(dir));
      if (dir != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        u32 xf2;
        asm volatile("add %0, %1, #0" : "=&l"(xf2) : "l"(xf));
        ((p->s).spr).xflip = xf2;
        xf = xf2;
      }
      {
        u8* oa = (u8*)p + 0x4a;
        u32 sh4 = xf << 4;
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      sh = dir << 8;
      (p->s).coord.x -= sh;
      SetMotion(&p->s, MOTION(0x2E, 0x07));
      (p->body).status = 0;
      (p->body).prevStatus = 0;
      (p->body).invincibleTime = 0;
      (p->s).flags &= ~COLLIDABLE;
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y;
      ((void (*)(u8, struct Coord*, s32, u32))FUN_080b2b40)(0, &c, 0x200, dir);
      c.x = 0x80 - sh;
      c.y = 0x60;
      (p->s).d.x = c.x / 3;
      (p->s).d.y = 0;
      FUN_080b84f4(&p->s, &(p->s).coord, &c, 0x20, (motion_t*)&sMotions[3], 0x18);
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x15;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((u8)--(p->s).work[2] == 0 ||
          (u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
        MaybeKillVolcaire(p);
      }
      break;
  }
}

// --------------------------------------------

void FUN_0807762c(struct Enemy* p);
void nop_08077608(struct Enemy* p);
void FUN_0807760c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    FUN_0807762c,
    nop_08077608,
    FUN_0807760c,
    FUN_0807760c,
    FUN_0807760c,
    FUN_0807760c,
    FUN_0807760c,
    nop_08077608,
};
// clang-format on

void FUN_080776ac(struct Enemy* p);
void FUN_080777cc(struct Enemy* p);
void FUN_08077834(struct Enemy* p);
void FUN_08077910(struct Enemy* p);
void FUN_08077af8(struct Enemy* p);
void FUN_08077b38(struct Enemy* p);
void FUN_08077ca4(struct Enemy* p);
void FUN_08077dd0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    FUN_080776ac,
    FUN_080777cc,
    FUN_08077834,
    FUN_08077910,
    FUN_08077af8,
    FUN_08077b38,
    FUN_08077ca4,
    FUN_08077dd0,
};
// clang-format on

// --------------------------------------------

void MaybeKillVolcaire(struct Enemy* p);
void FUN_08077fa4(struct Enemy* p);
void FUN_08077dd0(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    MaybeKillVolcaire,
    FUN_08077fa4,
    FUN_08077dd0,
};

// --------------------------------------------

static const struct Collision sCollisions[13] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(8), PIXEL(11), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      hardness : 8,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(8), PIXEL(11), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(5), -PIXEL(8), PIXEL(11), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(5), -PIXEL(8), PIXEL(11), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(20), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(5), PIXEL(20), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(11), PIXEL(12), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(5), PIXEL(20), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(20), PIXEL(10)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(4)};

static const u8 sInitModes[4] = {1, 2, 3, 0};

static const motion_t sMotions[4] = {
    MOTION(SM046_VOLCAIRE, 9),
    MOTION(SM046_VOLCAIRE, 10),
    MOTION(SM046_VOLCAIRE, 11),
    MOTION(SM046_VOLCAIRE, 8),
};
