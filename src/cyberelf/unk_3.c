#include "collision.h"
#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "mission.h"

// ------------------------------------------------------------------------------------------------------------------------------------

void Elf3_Init(Object *p);
void Elf3_Update(struct Elf *p);
void Elf3_Die(struct Elf *p);

extern const struct Collision sElf3Collisions[2];
void FUN_080e2af0(struct Body* body, struct Coord* r1, struct Coord* r2);

// clang-format off
const ElfRoutine gElf3Routine = {
    [ENTITY_INIT] =      (ElfFunc)Elf3_Init,
    [ENTITY_UPDATE] =    Elf3_Update,
    [ENTITY_DIE] =       Elf3_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

struct Elf *CreateElf3(struct Entity *r0, void *r1) {
  struct Elf *p = (struct Elf *)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 3);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = r0;
    (p->s).unk_2c = r1;
    (p->s).work[0] = 0;
    (p->s).work[1] = r0->work[1];
  }
  return p;
}

void Elf3_Init(Object* p) {
  (p->s).flags |= FLIPABLE;
  (p->s).spr.xflip = FALSE;
  (p->s).spr.oam.xflip = FALSE;
  (p->s).flags &= ~X_FLIP;
  INIT_BODY(p, sElf3Collisions, 1, FUN_080e2af0);
  (p->s).work[2] = 0;
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  Elf3_Update((void*)p);
}

void Elf3_Update(struct Elf* p) {
  struct CollidableEntity* t = (struct CollidableEntity*)(p->s).unk_2c;
  if ((p->s).unk_28->mode[0] > 1 || t->body.hp == 0) {
    SET_ELF_ROUTINE(p, ENTITY_DIE);
    Elf3_Die(p);
  } else {
    s32 x = (t->s).coord.x;
    s32 y = (t->s).coord.y;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    if (!(t->body.status & 0x200) && t->body.hp != 0 && (p->s).work[2] != 0) {
      gLifeRecoverAmount += (p->s).work[2] << 2;
      (p->s).work[2] = 0;
    }
  }
}

void Elf3_Die(struct Elf* p) {
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

// 0x080e2af0
void FUN_080e2af0(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  struct Elf* p = (struct Elf*)body->parent;
  struct Entity* atk = (struct Entity*)(body->enemy)->parent;
  struct Entity* q = (p->s).unk_28;
  struct Enemy* z = (struct Enemy*)(p->s).unk_2c;
  if (!((z->body).status & BODY_STATUS_DEAD) && (z->body).hp != 0 &&
      (body->hitboxFlags & 0x800000) && atk->kind == 4) {
    u8 idx;
    if (atk->id != 0) {
      return;
    }
    if (q->work[2] == 0) {
      u8* pr = (u8*)z + 0xb4;
      idx = pr[0];
    } else {
      u8* pr = (u8*)z + 0xb4;
      idx = pr[1];
    }
    if (ELF_AVABILITY(idx) & 4) {
      (p->s).work[2] += 2;
    } else {
      (p->s).work[2] += 1;
    }
    AddMissionDamage(2);
  }
}

// 0x080E2B78
void FUN_080e2b78(struct Elf* p0) {
  register struct Elf* p asm("r3");
  register u8 w asm("r2");
  struct Entity* q;
  p = p0;
  q = *(struct Entity**)((u8*)p + 0xb4);
  w = (p->s).work[2];
  {
    register u8 fl asm("r0");
    u32 z;
    register u8* r asm("r0");
  if (w == 0) {
    if ((p->s).work[3] == *(u8*)((u8*)q + 0xb4)) {
      return;
    }
    {
      register u8 t asm("r1");
      t = (p->s).flags;
      fl = 0xFE;
      fl &= t;
      asm volatile("" :: "r"(t));
    }
    z = w;
  } else {
    register u8* b asm("r1");
    b = (u8*)q + 0xb4;
    asm("" : "+r"(b));
    if ((p->s).work[3] == b[1]) {
      return;
    }
    {
      register u8 t asm("r1");
      t = (p->s).flags;
      fl = 0xFE;
      fl &= t;
      asm volatile("" :: "r"(t));
    }
    z = 0;
  }
  fl &= 0xFD;
  (p->s).flags = fl;
  r = (u8*)p + 0x8c;
  *(u32*)r = z;
  asm volatile("add %0, #4" : "+r"(r));
  *(u32*)r = z;
  asm volatile("add %0, #4" : "+r"(r));
  *r = z;
  (p->s).flags &= 0xFB;
  SET_ELF_ROUTINE(p, 3);
  }
}

const struct Collision sElf3Collisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      special : 0,
      damage : 255,
      atkType : 0x00,
      element : 0x00,
      nature : 0x40,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0100, -0x0E00, 0x3400, 0x3200},
    },
    {
      kind : DRP,
      faction : FACTION_ALLY,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {-0x0100, -0x0E00, 0x3400, 0x3200},
    },
};
