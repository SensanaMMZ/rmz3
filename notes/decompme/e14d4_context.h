typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
#define NULL ((void*)0)

struct Entity {
  struct Entity* next;
  struct Entity* prev;
  s8 kind;
  u8 id;
  u8 flags;
  u8 flags2;
  /* ... rest irrelevant to this function ... */
};

struct EntityHeader {
  struct Entity* arr;
  s16 type;
  s16 size;
  s16 length;
  s16 remaining;
  struct Entity* last;
  struct Entity* free;
  struct Entity* next;
  struct Entity* prev;
  u32 unk[3];
};

extern struct EntityHeader* gElfHeaderPtr;
