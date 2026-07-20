typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef volatile u16 vu16;
typedef u16 bool16;

struct KeyState {
  u16 input;      /* 0x00 */
  u16 last;       /* 0x02 */
  u16 pressed;    /* 0x04 */
  u16 field3_0x6; /* 0x06 */
  bool16 firstRead; /* 0x08 */
  u8 unk_0a[10];  /* 0x0A */
  u8 field6_0x14; /* 0x14 */
  u8 field7_0x15; /* 0x15 */
  u8 field8_0x16;
  u8 field9_0x17;
};

#define REG_KEYINPUT (*(vu16*)0x4000130)
