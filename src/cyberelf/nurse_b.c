#include "cyberelf.h"
#include "entity.h"
#include "global.h"
#include "zero.h"

void FUN_080bfce8(struct Coord* c, s32 r1);

struct CyberElfNurseB {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Zero* player;  // 0xB4
  u8 unk_b8[12];        // 0xB8
};

struct Elf* CreateNurseBElf(struct Zero* z, u8 breed, u8 availability, u8 satelite_slot) {
  struct CyberElfNurseB* p = (struct CyberElfNurseB*)AllocEntityFirst(gElfHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 16;
    INIT_ELF_ROUTINE(p, 2);
    (p->s).tileNum = 0, (p->s).palID = 0;
    p->player = z;
    (p->s).work[0] = breed, (p->s).work[1] = availability, (p->s).work[2] = satelite_slot;
    if (satelite_slot == 0) {
      (p->s).work[3] = SATELITE_1;
    } else {
      (p->s).work[3] = SATELITE_2;
    }
  }
  return (struct Elf*)p;
}

struct Entity* FUN_080bfc94(struct Coord* c, u8 r1);
extern const s16 gSineTable[256];
extern const ElfFunc sNurseBUpdates[4];

void NurseB_Update(struct Elf* p);

void NurseB_Init(struct Elf* p) {
  struct Zero* z = ((struct CyberElfNurseB*)p)->player;
  struct Rect rr = gZeroRanges[*((u8*)z + 0x147)];
  s32 z8;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register s32 c1 asm("r0");
    register s32 f1 asm("r1");
    f1 = (p->s).flags;
    c1 = 1;
    asm("" : "+r"(c1));
    z8 = 0;
    c1 = c1 | f1;
    c1 |= 2;
    (p->s).flags = c1;
  }
  SetMotion(&p->s, GetElfMotion(0));
  UpdateMotionGraphic(&p->s);
  ((p->s).spr).xflip = z8;
  {
    u8* oa = (u8*)&((p->s).spr).oam + 6;
    s32 ov = *oa;
    s32 m11 = -0x11;
    asm("" : "+r"(m11));
    *oa = m11 & ov;
    (p->s).flags &= 0xEF;
  }
  (p->s).coord.x = (z->s).coord.x + rr.x;
  (p->s).coord.y = (z->s).coord.y + rr.y;
  {
    s32* b = (s32*)&((struct CyberElfNurseB*)p)->unk_b8[4];
    b[0] = z8;
    b[1] = z8;
  }
  if ((p->s).work[2] != 0) {
    ((struct CyberElfNurseB*)p)->unk_b8[0] = z8;
  } else {
    ((struct CyberElfNurseB*)p)->unk_b8[0] = 8;
  }
  ((struct CyberElfNurseB*)p)->unk_b8[1] = 0x20;
  CreateElf3(&p->s, z);
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  NurseB_Update(p);
}

void NurseB_Update(struct Elf* p) {
  struct CyberElfNurseB* q = (struct CyberElfNurseB*)p;
  struct Zero* z = q->player;
  struct Rect rr = gZeroRanges[*((u8*)z + 0x147)];
  UpdateMotionGraphic(&p->s);
  {
    u8 v = gPause;
    if (v == 0) {
      if (*((u8*)z + 0x232) != 0) {
        u8 f = ~DISPLAY & (p->s).flags;
        f = f & ~FLIPABLE;
        (p->s).flags = f;
        (p->body).status = v;
        (p->body).prevStatus = v;
        (p->body).invincibleTime = v;
        (p->s).flags &= ~COLLIDABLE;
        SET_ELF_ROUTINE(p, ENTITY_DISAPPEAR);
      } else if (((z->body).status & 0x200) || ((z->body).hp == 0)) {
        SET_ELF_ROUTINE(p, ENTITY_DIE);
      } else {
        (p->s).unk_coord.x = (z->s).coord.x + rr.x;
        (p->s).unk_coord.y = (z->s).coord.y + rr.y;
        (sNurseBUpdates[(p->s).mode[1]])(p);
        {
          u8* a8 = &q->unk_b8[0];
          s32* b;
          register s32 t asm("r3");
          s32 d, idx, s;
          t = *a8 + 1;
          d = t;
          asm("" : "+r"(d));
          d >>= 4;
          d <<= 4;
          t -= d;
          idx = t;
          *a8 = t;
          t <<= 4;
          s = gSineTable[(u8)(idx << 4)] << 4;
          b = (s32*)&q->unk_b8[4];
          (p->s).coord.x = (b[0] + s) + (p->s).unk_coord.x;
          (p->s).coord.y = b[1] + (p->s).unk_coord.y;
          {
            register s32 u asm("r0");
            s32 k;
            u = t + 0x40;
            u &= 0xFF;
            k = 0x10;
            if (u > 0x7F) {
              k = 0x11;
            }
            (p->s).taskCol = k;
          }
          {
            u8* a9 = &q->unk_b8[1];
            s32 raw = *a9 - 1;
            *a9 = raw;
            if ((u8)raw == 0xFF) {
              FUN_080bfc94(&(p->s).coord, 2);
              *a9 = 0x20;
            }
          }
        }
      }
    }
  }
}

void NurseB_Die(struct Elf* p) {
  FUN_080bfce8(&(p->s).coord, 0);
  (p->s).flags &= ~DISPLAY;
  SET_ELF_ROUTINE(p, ENTITY_EXIT);
}

bool8 FUN_080e1578(struct Coord* c1, struct Coord* c2, struct Coord* c3, u8* param_4, s16 param_5);

void FUN_080e284c(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y;
  {
    bool8 hit;
    if ((p->s).work[2] != 0) {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0x180);
    } else {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xC0);
    }
    if (hit) {
      (p->s).mode[1] = ((p->s).mode[1] + 1) & 3;
    }
  }
}

void FUN_080e28a8(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y + r.y;
  {
    bool8 hit;
    if ((p->s).work[2] != 0) {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0x180);
    } else {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xC0);
    }
    if (hit) {
      (p->s).mode[1] = ((p->s).mode[1] + 1) & 3;
    }
  }
}

void FUN_080e2920(struct Elf* p) {
  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  c.x = (z->s).coord.x;
  c.y = (z->s).coord.y - r.h;
  {
    bool8 hit;
    if ((p->s).work[2] != 0) {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0x180);
    } else {
      hit = FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c, &p->buffer[6], 0xC0);
    }
    if (hit) {
      (p->s).mode[1] = ((p->s).mode[1] + 1) & 3;
    }
  }
}


// ------------------------------------------------------------------------------------------------------------------------------------

void NurseB_Init(struct Elf* p);
void NurseB_Update(struct Elf* p);
void NurseB_Die(struct Elf* p);

// clang-format off
const ElfRoutine gNurseBRoutine = {
    [ENTITY_INIT] =      NurseB_Init,
    [ENTITY_UPDATE] =    NurseB_Update,
    [ENTITY_DIE] =       NurseB_Die,
    [ENTITY_DISAPPEAR] = DeleteElf,
    [ENTITY_EXIT] =      (ElfFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080e284c(struct Elf* p);
void FUN_080e28a8(struct Elf* p);
void FUN_080e2920(struct Elf* p);
void FUN_080e28a8(struct Elf* p);

const ElfFunc sNurseBUpdates[4] = {
    FUN_080e284c,
    FUN_080e28a8,
    FUN_080e2920,
    FUN_080e28a8,
};
