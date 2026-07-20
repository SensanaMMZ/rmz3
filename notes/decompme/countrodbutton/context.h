typedef unsigned char u8;  typedef unsigned short u16;  typedef unsigned int u32;
typedef signed char s8;    typedef short s16;           typedef int s32;
typedef u8 bool8;
typedef u16 KEY_INPUT;

/* Only the fields CountRodButton touches, at the ROM offsets it uses. */
struct KeyMap { KEY_INPUT jump, dash, main, sub; };   /* main @ +4, sub @ +6 */

struct Zero {
  u8 pad_0[0xb4];
  struct { u8 pad0[0x25]; struct { u8 attackMode; } keyMap; } unk_b4;  /* attackMode @ 0xD9 */
  u8 pad_da[0x146];
  struct { struct KeyMap mapping; KEY_INPUT history[33]; } input;      /* mapping.main @ 0x220 */
};
