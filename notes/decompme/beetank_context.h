typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef u8 bool8;
typedef u32 bool32;

struct Coord {
  s32 x;
  s32 y;
};

struct Entity {
  u8 pad_00[9];    /* 0x00 */
  u8 id;           /* 0x09 */
  u8 pad_0a[2];    /* 0x0A */
  u8 mode[4];      /* 0x0C */
  u8 pad_10[4];    /* 0x10 */
  void* onUpdate;  /* 0x14 */
  u8 pad_18[0x3C]; /* 0x18 */
  struct Coord coord; /* 0x54 */
  struct Coord d;     /* 0x5C */
  u8 pad_64[0x10];    /* 0x64 */
}; /* 0x74 */

struct Enemy {
  struct Entity s; /* 0x00 */
  u8 pad_74[0x50]; /* 0x74: body etc. (accessed via raw casts) */
}; /* 0xC4 */

typedef void (*EntityFunc)(struct Entity*);
typedef void (*EnemyFunc)(struct Enemy*);

extern void* gEnemyFnTable[];

#define ENTITY_DIE 2

#define SET_ENEMY_ROUTINE(entity, modeID)                                 \
  {                                                                       \
    u32 tbl, id;                                                          \
    EntityFunc** routine_table;                                           \
    tbl = (u32)(gEnemyFnTable);                                           \
    id = (((struct Entity*)entity)->id) << 2;                             \
    routine_table = (EntityFunc**)(tbl + id);                             \
    *(u32*)(((struct Entity*)entity)->mode) = modeID;                     \
    ((struct Entity*)entity)->onUpdate =                                  \
        (void*)(*(EntityFunc**)routine_table)[modeID];                    \
  }

void Beetank_Die(struct Enemy* p);
void FUN_0807be50(struct Enemy* p);
s32 PushoutToLeft1(s32 x, s32 y);
s32 PushoutToRight1(s32 x, s32 y);
s32 FUN_08009f6c(s32 x, s32 y);
bool32 IsFrozen(void* enemy_entity);

extern const EnemyFunc sUpdates1[5];
extern const EnemyFunc sUpdates2[5];
