#include "global.h"

/**
 * @brief X と Y が作る直角三角形のなす角度を求める
 * @param x Coord X
 * @param y Coord Y
 * @return angle(gSineTable's idx)
 * @note 0x080e95cc
 */
s32 CalcAngle(s32 x, s32 y) {
  u16 angle;
  s32 tmp;
  while (TRUE) {
    if (abs(x) < 0x8000) {
      if (abs(y) < 0x8000) {
        break;
      }
    }

    // Ceiling x
    tmp = x;
    if (tmp < 0) {
      tmp += 0xF;
    }
    x = (tmp >> 4);

    // Ceiling y
    tmp = y;
    if (tmp < 0) {
      tmp += 0xF;
    }
    y = (tmp >> 4);
  }

  angle = ArcTan2(x, y);
  return (((s32)(angle) + 0x80) >> 8) & 0xFF;
}

s32 CalcAngleBetweenPoints(s32 x1, s32 y1, s32 x2, s32 y2) { return CalcAngle(x2 - x1, y2 - y1); }

s32 CalcAngleBetweenCoords(struct Coord* c1, struct Coord* c2) { return CalcAngleBetweenPoints(c1->x, c1->y, c2->x, c2->y); }

/**
 * @brief 角度aを角度bへ、最大ステップcずつ近づける (u8角度系: 256 = 360度)
 * @note b±c の範囲内なら a をそのまま返す。レジスタ割り当てが合わないため NON_MATCH
 * @note 0x080e964c
 */
NON_MATCH u8 FUN_080e964c(u32 a, s32 b, s32 c) {
#if MODERN
  if ((((a - b) + c) & 0xFF) > (u32)(c << 1)) {
    s32 dir = (((a - b) & 0xFF) > 0x7F) ? -1 : 1;
    return (b + c * dir) & 0xFF;
  }
  return a;
#else
  INCCODE("asm/math/math_080e964c.inc");
#endif
}

#if MODERN == 0
NAKED static void unused_080e9680(void* param_1, void* param_2, void* param_3, void* param_4, void* param_5, void* param_6) { INCCODE("asm/unused/unused_080e9680.inc"); }
#endif

#if MODERN == 0
NAKED static void unused_080e9698(void* param_1, void* param_2, u32 param_3, u32 param_4) { INCCODE("asm/unused/unused_080e9698.inc"); }
#endif

#if MODERN == 0
static s32 unused_080e96c8(s32 a, s32 b) {
  register s32 c asm("r2") = 0x100 - a;
  b += c;
  c = ((b & 0xFF) + 0x80);
  c &= 0xFF;
  c -= 0x80;
  return c;
}
#endif
