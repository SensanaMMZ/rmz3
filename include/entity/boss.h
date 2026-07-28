#ifndef GUARD_RMZ3_ENTITY_BOSS_H
#define GUARD_RMZ3_ENTITY_BOSS_H

#include "entity/entity.h"
#include "sound.h"

struct ChildreProps {
  struct Entity* unk_b4;
  u32 unk_b8;
  struct Coord unk_bc;
  u8 unk_c4;
  u8 unk_c5;
  bool8 shouldTurnRight;
  u8 unk_c7;
  struct Coord unk_c8;
  u8 unk_d0[20];
};

struct DeathtanzProps {
  struct Coord unk_b4;
  u8 unk_bc;
  u8 unk_bd;
  u8 unk_be;
  u8 unk_bf;
  u8 unk_c0;
  u8 unk_c1;
  bool8 shouldTurnRight;
  u8 unk_c3;
  u8 unk_c4;
  u8 unk_c5[3];
  struct Coord unk_c8;
  u8 unk_d0[20];
};

struct GlacierleProps {
  u32 unk_b4;
  struct VFX* unk_b8;
  s32 unk_bc;
  u8 unk_c0;
  u8 unk_c1;
  bool8 shouldRightDir;
  u8 unk_c3[5];
  struct Coord unk_c8;
  u8 unk_d0[20];
};

struct OmegaWhiteProps {
  u8 unk_b4[4];
  s32 unk_y;
  struct Entity* unk_bc;  // omegaWhite_080b91d4
  u16 unk_c0;
  u8 unk_c2[18];
  u32 unk_d4;
  u8 unk_d8[12];
};

struct CopyXProps {
  u8 unk_b4[16];
  u8 unk_c4;
  u8 unk_c5;
  u8 unk_c6[22];
  u8 unk_dc;
  s8 unk_dd;
  u8 unk_de[6];
};

struct HellbatProps {
  u8 unk_b4[32];
  s32 unk_d4;
  u8 unk_d8[12];
};

struct PAquaModProps {
  u8 unk_b4[6];
  u16 x;
  s32 y;
  u8 unk_c0[36];
};

struct MegamilpaProps {
  struct Coord c_b4;  // 0xB4
  u8 unk_bc;          // 0xBC
  u8 unk_bd;          // 0xBD
  u8 unk_be[2];       // 0xBE
  s32 unk_c0;         // 0xC0
  s32 unk_c4;         // 0xC4
  bool8 unk_c8;       // 0xC8
  u8 unk_c9[3];       // 0xC9
  u8 buffer[24];      // 0xCC
};

struct Boss {
  OBJECT_HDR;

  union {
    u8 raw[48];
    struct MegamilpaProps megamilpa;
    struct OmegaWhiteProps omegaWhite;
    struct CopyXProps copyx;
    struct GlacierleProps glacierle;
    struct ChildreProps childre;
    struct DeathtanzProps deathtanz;
    struct HellbatProps hellbat;
    struct PAquaModProps paquam;
  } props;
};  // 228 bytes

typedef void (*BossFunc)(struct Boss*);

#endif  // GUARD_RMZ3_ENTITY_BOSS_H
