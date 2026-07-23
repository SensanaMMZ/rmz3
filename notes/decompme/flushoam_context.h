typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

#define REG_DISPCNT (*(vu16*)0x4000000)
#define DISPCNT_OBJ_ON 0x1000
#define OAM 0x7000000
#define PTR_U32(p) ((u32)(void*)(p))
#define DmaCopy32(n, src, dst, size)          \
  {                                           \
    vu32* dma = (vu32*)(0x40000B0 + n * 12);  \
    dma[0] = (vu32)(src);                     \
    dma[1] = (vu32)(dst);                     \
    dma[2] = (0x84000000 | ((size) >> 2));    \
  }

struct OamData {
  u32 attr01;
  u16 attr2;
  u16 pad;
};

struct OamManager {
  struct OamData buf[128];  /* 0x000 */
  struct OamData* p;        /* 0x400 */
  u32 dispcnt;              /* 0x404 */
};
extern struct OamManager gOamManager;
