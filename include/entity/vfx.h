#ifndef GUARD_RMZ3_ENTITY_VFX_H
#define GUARD_RMZ3_ENTITY_VFX_H

#include "entity/entity.h"

// VFX: プレイヤーと干渉しない、グラフィックエフェクト的な存在
// 例: ダッシュの残像, パーティクル, ミッションアラート, ハンマー振り子のボールチェーン, エネミーが死んで飛び散った残骸, etc...
// NOTE: Ghost から VFX にリネームしたけど、まだ変数名や関数名に Ghost が残っているものがある
// NOTE: エネミーが死んで飛び散る残骸 も パーティクルと呼ぶかは検討中

struct TempProps {
  struct Coord c;
  u8* unk_7c;
  u8 work[4];
};

struct Unk25Props {
  struct Coord c;
  u8 unk_7c[4];
  u16 unk_80;
  u16 unk_82;
};

struct Unk28Props {
  u16 unk_0;
  u16 unk_2;
  s32 unk_4;
  u8 unk_8[8];
};

struct Unk32Props {
  s16 unk_0;
  u8 unk_2[2];
  u32 unk_4;
  u32 unk_8;
  u16 unk_c;
  u16 unk_e;
};

struct Unk69Props {
  struct Coord c;
  u8 unk_8[8];
};

struct SnowProps {
  u32 unk_0;
  u8 unk_4[12];
};

struct NecroProps {
  motion_t* motions;
  u8 unk_04;
  u8 unk_05;
  u8 unk_06[10];
};

struct BubbleProps {
  s32 unk_0;
  s32 unk_4;
  u8 unk_8[8];
};

struct Unk83Props {
  s32 unk_0;
  s32 unk_4[2];
  u8 unk_c[4];
};

struct VFX {
  struct Entity s;

  // 0x74
  union {
    u8 raw[16];
    struct BubbleProps bubble;
    struct NecroProps necro;
    struct SnowProps snow;
    struct Unk25Props unk25;
    struct Unk28Props unk28;
    struct Unk32Props unk32;
    struct Unk69Props unk69;
    struct Unk83Props unk83;
    struct TempProps tmp;
  } props;
};  // 132 bytes

#endif  // GUARD_RMZ3_ENTITY_VFX_H
