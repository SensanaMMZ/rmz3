typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;

struct BgMapHeader {
  u16 ofs;
  s8 subspriteCount;
  u8 texture;
  u8 w;
  u8 unused_5;
  u8 h;
  u8 unused_7;
};
