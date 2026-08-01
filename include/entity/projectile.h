#ifndef GUARD_RMZ3_ENTITY_PROJECTILE_H
#define GUARD_RMZ3_ENTITY_PROJECTILE_H

#include "entity/entity.h"

// TODO: Solid などの Object と 16バイトのバッファ をもつ 196バイトの 構造体　として共通化する

// 飛び道具だと思ってたけど、特定のエンティティに従属しているエンティティのことを指すかも？
struct Projectile {
  struct Entity s;
  struct Body body;
  // 0xB4 ..
  u8 work[4];  // general purpose buffer
  union {
    struct Coord c;
    struct {
      s32 x;
      s16 ylo;
      s16 yhi;
    } h;
  } prevCoord;
  s16 soundID;
  u16 unk_c2;
};  // 196 bytes

typedef void (*ProjectileFunc)(struct Projectile*);

#endif  // GUARD_RMZ3_ENTITY_PROJECTILE_H
