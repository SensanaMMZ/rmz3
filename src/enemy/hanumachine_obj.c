#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"

void FUN_080866a4(struct Entity* e, u8 mode, u8 xflip) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HANUMACHINE_OBJ);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).unk_28 = e;
    SET_XFLIP(&p->s, xflip);
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
  }
}

INCASM("asm/enemy/hanumachine_obj_pre_p2_a.inc");

extern const EnemyFunc sUpdates[8];
extern const struct Collision sCollisions[6];
void FUN_08086e34(struct Enemy* p);
void HanumachineObj_Die(struct Enemy* p);

void HanumachineObj_Update(struct Enemy* p) {
  struct Coord c1;
  struct Coord c2;
  u16* timer = (u16*)((u8*)p + 0xc0);
  s32 t;
  if (*timer == 0) {
    c1.x = (p->s).coord.x;
    c1.y = (p->s).coord.y - 0x800;
    PlaySound(0x2a);
    CreateSmoke(1, &c1);
    if (*(u8*)((u8*)p + 0xbd) != 0) {
      SetDDP(&p->body, &sCollisions[5]);
    } else {
      SetDDP(&p->body, &sCollisions[3]);
    }
    goto die;
  }
  if ((p->s).mode[1] != 7) {
    if (((p->body).status & 0x00020001) == 0x00020001) {
      (p->s).mode[1] = 7;
      (p->s).mode[2] = 0;
    }
    if ((p->s).mode[1] != 7) {
      goto cont;
    }
  }
  FUN_08086e34(p);
  return;

cont:
  if ((p->body).status & BODY_STATUS_DEAD) {
    c2.x = (p->s).coord.x;
    c2.y = (p->s).coord.y - 0x800;
    PlaySound(0x2a);
    CreateSmoke(1, &c2);
  die:
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    HanumachineObj_Die(p);
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
  t = *timer - 1;
  *timer = t;
  if ((u16)t > 0x3b) {
    return;
  }
  if ((t & 3U) <= 1) {
    PaintEntityWhite(&p->s);
  } else {
    UpdateEntityPaletteID(&p->s);
  }
}

void HanumachineObj_Die(struct Enemy* p) {
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

void FUN_0808693c(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).work[2] = ((p->s).work[0] << 3) + 2;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  {
    u8 f = (p->s).flags & X_FLIP;
    s32 off = -0xA00;
    if (f) {
      off = 0xA00;
    }
    if ((u8)--(p->s).work[2] == 0xFF || FUN_080098a4((p->s).coord.x + off, (p->s).coord.y)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_080869a0(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).d.y = -0x300;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (((p->s).spr).mag.x <= 0xFF) {
    ((p->s).spr).mag.x += 0x10;
    ((p->s).spr).mag.y += 0x10;
  }
  if ((p->s).d.y > 0) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

// 0x080869f4
void FUN_080869f4(struct Enemy* p) {
  u16 r;
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x6A, 0x02));
    (p->s).work[2] = 0x10;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  r = FUN_080098a4((p->s).coord.x, (p->s).coord.y + 1);
  if (r == 0) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = r;
  } else if ((u8)--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/hanumachine_obj_post.inc");

void FUN_08086cbc(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x6a, 0x03));
    ((p->s).spr).oam.priority = 2;
    SetDDP(&p->body, &sCollisions[2]);
    {
      u8 sh = (p->s).flags >> 4;
      u8 on = 1;
      on &= ~sh;
      SET_XFLIP(p, on);
    }
    {
      register s32 v asm("r0");
      if ((p->s).flags & X_FLIP) {
        v = 0x180;
      } else {
        v = -0x180;
      }
      (p->s).d.x = v;
    }
    (p->s).d.y = -0x300;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (FUN_080098a4((p->s).coord.x + (p->s).d.x, (p->s).coord.y) != 0) {
    (p->s).d.x = -(p->s).d.x;
    {
      u8 sh = (p->s).flags >> 4;
      u8 on = 1;
      on &= ~sh;
      SET_XFLIP(p, on);
    }
  }
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}


void FUN_08086dcc(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    InitNonAffineMotion(&p->s);
    SetMotion(&p->s, MOTION(0x6a, 0x03));
    SetDDP(&p->body, &sCollisions[1]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/hanumachine_obj_post_b.inc");

void HanumachineObj_Init(struct Enemy* p);
void HanumachineObj_Update(struct Enemy* p);
void HanumachineObj_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gHanumachineObjRoutine = {
    [ENTITY_INIT] =      HanumachineObj_Init,
    [ENTITY_UPDATE] =    HanumachineObj_Update,
    [ENTITY_DIE] =       HanumachineObj_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_0808693c(struct Enemy* p);
void FUN_080869a0(struct Enemy* p);
void FUN_080869f4(struct Enemy* p);
void FUN_08086a50(struct Enemy* p);
void FUN_08086b6c(struct Enemy* p);
void FUN_08086cbc(struct Enemy* p);
void FUN_08086dcc(struct Enemy* p);
void FUN_08086e34(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates[8] = {
    FUN_0808693c,
    FUN_080869a0,
    FUN_080869f4,
    FUN_08086a50,
    FUN_08086b6c,
    FUN_08086cbc,
    FUN_08086dcc,
    FUN_08086e34,
};
// clang-format on

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(26), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(26), PIXEL(28)},
    },
};
