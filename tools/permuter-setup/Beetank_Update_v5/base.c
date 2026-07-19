
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;
typedef long long int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long uint_least64_t;
typedef int int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long uint_fast64_t;
typedef int intptr_t;
typedef unsigned int uintptr_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
typedef void (*VoidFunc)(void);
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;
typedef float f32;
typedef double f64;
typedef u8 bool8;
typedef u16 bool16;
typedef u32 bool32;
struct __attribute__((packed, aligned(2))) BgCnt
{
  u16 priority : 2;
  u16 charBaseBlock : 2;
  u16 dummy : 2;
  u16 mosaic : 1;
  u16 palettes : 1;
  u16 screenBaseBlock : 5;
  u16 areaOverflowMode : 1;
  u16 screenSize : 2;
};
typedef volatile struct BgCnt vBgCnt;
struct __attribute__((packed)) PlttData
{
  u16 r : 5;
  u16 g : 5;
  u16 b : 5;
  u16 unused_15 : 1;
};
struct OamData
{
  u32 y : 8;
  u32 affineMode : 2;
  u32 objMode : 2;
  u32 mosaic : 1;
  u32 bpp : 1;
  u32 shape : 2;
  u32 x : 9;
  u32 matrixNum : 5;
  u32 size : 2;
  u16 tileNum : 10;
  u16 priority : 2;
  u16 paletteNum : 4;
  u16 affineParam;
};
struct BgAffineSrcData
{
  s32 texX;
  s32 texY;
  s16 scrX;
  s16 scrY;
  s16 sx;
  s16 sy;
  u16 alpha;
};
struct BgAffineDstData
{
  s16 pa;
  s16 pb;
  s16 pc;
  s16 pd;
  s32 dx;
  s32 dy;
};
struct ObjAffineSrcData
{
  s16 xScale;
  s16 yScale;
  u16 rotation;
};
struct SioMultiCnt
{
  u16 baudRate : 2;
  u16 si : 1;
  u16 sd : 1;
  u16 id : 2;
  u16 error : 1;
  u16 enable : 1;
  u16 unused_11_8 : 4;
  u16 mode : 2;
  u16 intrEnable : 1;
  u16 unused_15 : 1;
  u16 data;
};
struct Coord16
{
  s16 x;
  s16 y;
};
struct Coord
{
  s32 x;
  s32 y;
};
struct Border
{
  s32 left;
  s32 right;
  s32 top;
  s32 bottom;
};
struct DrawPivot
{
  struct Coord coord;
  struct Coord lefttop;
  struct Coord offset;
};
struct Pivot
{
  struct Coord *coord;
  struct Coord *offset;
  void *_;
};
struct BgMapHeader
{
  u32 unk_00;
  u16 w;
  u16 h;
};
struct Rect
{
  s16 x;
  s16 y;
  s16 w;
  s16 h;
};
struct Area32
{
  s32 left;
  s32 top;
  s32 right;
  s32 bottom;
};
typedef long int ptrdiff_t;
typedef unsigned long int size_t;
typedef int wchar_t;
extern struct SoundInfo *SOUND_INFO_PTR;
void SoftReset(u32 resetFlags);
void RegisterRamReset(u32 resetFlags);
void VBlankIntrWait(void);
u16 Sqrt(u32 num);
u16 ArcTan2(s16 x, s16 y);
void CpuSet(const void *src, void *dest, u32 control);
void CpuFastSet(const void *src, void *dest, u32 control);
void BgAffineSet(struct BgAffineSrcData *src, struct BgAffineDstData *dest, s32 count);
void ObjAffineSet(struct ObjAffineSrcData *src, void *dest, s32 count, s32 offset);
void LZ77UnCompWram(const void *src, void *dest);
void LZ77UnCompVram(const void *src, void *dest);
void RLUnCompWram(const void *src, void *dest);
void RLUnCompVram(const void *src, void *dest);
void ReadSram(const u8 *src, u8 *dst, u32 size);
u32 WriteSramEx(const u8 *src, u8 *dst, u32 size);
void WriteSram(const u8 *src, u8 *dest, u32 size);
u32 VerifySram(const u8 *src, u8 *dst, u32 size);
struct Collision;
struct Body;
typedef void (*BodyFunc)(struct Body *, struct Coord *, struct Coord *);
struct Body
{
  const struct Collision *collisions;
  const struct Collision *processing;
  struct Coord *coord;
  struct Body *enemy;
  struct Body *bindPair;
  u32 hitboxFlags;
  u32 status;
  u32 prevStatus;
  u8 invincibleTime;
  u8 unk_21;
  u8 invincibleLv;
  u8 unk_23 : 4;
  u8 elemented : 4;
  BodyFunc fn;
  u32 unk_28;
  struct CollidableEntity *parent;
  s16 hp;
  s16 unk_32[2];
  u8 forceFlags;
  u8 atk;
  u8 element;
  u8 nature;
  u8 comboLv;
  u8 hardness;
  u32 collisionLayer;
};
enum CollisionAtkType
{
  ATK_NORMAL = 0,
  ATK_SABER = 1,
  ATK_ROD = 2,
  ATK_UNK3 = 3,
  ATK_UNK4 = 4,
  ATK_UNK8 = 8,
  ATK_UNK11 = 11,
  ATK_UNK12 = 12,
  ATK_SOUL_LAUNCHER = 13,
  ATK_UNK14 = 14,
  ATK_NONE = 0xFF
};
enum HitboxKind
{
  DDP,
  DRP,
  DRP2
};
enum CollisionFaction
{
  FACTION_ALLY,
  FACTION_ENEMY,
  FACTION_NEUTRAL
};
struct Collision
{
  u8 kind;
  u8 faction;
  u8 special;
  u8 damage;
  u8 atkType;
  u8 element;
  u8 nature;
  u8 comboLv;
  u8 hitzone;
  u8 hardness;
  u8 unk_0a;
  u8 remaining;
  u32 layer;
  struct Rect range;
};
struct Hitbox
{
  struct Hitbox *next;
  struct Collision *collisions;
  struct Body *body;
  struct Coord c;
  u16 w;
  u16 h;
};
struct CollisionManager
{
  u8 disabled;
  u8 sweep;
  u8 hitstop;
  u8 length;
  struct Hitbox buf[64];
  struct Hitbox *list[3][3];
  struct Body *talkTo;
  struct Body *door;
  struct Body *teleportal;
  u8 _[12];
};
extern struct CollisionManager gCollisionManager;
void ResetCollisionManager(void);
void ClearAllHitboxes(void);
void SetDDP(struct Body *, const struct Collision *);
u16 CalcDamage(struct Body *a, struct Body *d);
void CheckCollision(void);
void ResisterNonAffineHitbox(struct Body *body);
void RegisterFlipableHitbox(struct Body *p, u8 flip);
void RegisterScalerotHitbox(struct Body *o, u32 r1, u32 r2);
void InitWeaponBody(struct Body *o, const struct Collision *hitbox, s16 atk, s16 elementID, s16 r4, s16 r5);
void InitBody(struct Body *p, const struct Collision *hitbox, struct Coord *coord, s16 hp);
u16 CalcPutitedSpikeDamage(struct Body *body, u8 damage);
typedef u16 tile_id_t;
typedef u16 KEY_INPUT;
typedef u16 SoundID;
typedef s16 SoundIDS16;
typedef u32 SoundID32;
typedef u16 TextID;
typedef u8 disk_t;
typedef u16 str_id_t;
typedef u8 mod_t;
typedef u8 cyberelf_t;
typedef u8 char_t;
typedef char_t *str_t;
typedef u8 motion_id_t;
typedef u8 motion_sub_id_t;
typedef u16 motion_t;
typedef u8 weapon_t;
typedef u32 zero_input_t;
typedef u16 tileset_t;
typedef u8 tileset_ofs_t;
typedef s32 (*ShapeChecker)(s32 x, s32 y);
struct Coord;
void *Malloc(u32 bytesize);
s32 FUN_08009f6c(s32 x, s32 y);
void CreateFirework(s32 x, s32 y, bool8 r2);
void ResetEntityEnvironment(void);
void FUN_0802511c(void);
void clearStageDisk(void);
u32 TryDropItem(u32 table, struct Coord *c);
s32 PushoutToLeft1(s32 x, s32 y);
s32 PushoutToLeft2(s32 x, s32 y);
s32 PushoutToRight1(s32 x, s32 y);
s32 PushoutToRight2(s32 x, s32 y);
s32 FUN_0800a22c(s32 x, s32 y);
s32 FUN_0800a31c(s32 x, s32 y);
s32 FUN_0800a738(s32 x, s32 y);
s32 FUN_0800a73c(s32 x, s32 y);
s32 FUN_0800a740(s32 x, s32 y);
s32 FUN_0800a760(s32 x, s32 y);
s32 FUN_0800a780(s32 x, s32 y);
s32 FUN_0800a7a0(s32 x, s32 y);
s32 FUN_0800a7c0(s32 x, s32 y);
s32 FUN_0800a7e0(s32 x, s32 y);
s32 FUN_0800a800(s32 x, s32 y);
s32 FUN_0800a814(s32 x, s32 y);
s32 FUN_0800a834(s32 x, s32 y);
s32 FUN_0800a848(s32 x, s32 y);
s32 FUN_0800a868(s32 x, s32 y);
s32 FUN_0800a888(s32 x, s32 y);
s32 FUN_0800a8a8(s32 x, s32 y);
s32 FUN_0800a8bc(s32 x, s32 y);
s32 FUN_0800a8d4(s32 x, s32 y);
s32 FUN_0800a8e8(s32 x, s32 y);
s32 FUN_0800a900(s32 x, s32 y);
s32 FUN_0800a918(s32 x, s32 y);
s32 FUN_0800a930(s32 x, s32 y);
s32 FUN_0800a94c(s32 x, s32 y);
s32 FUN_0800a968(s32 x, s32 y);
s32 FUN_0800a984(s32 x, s32 y);
s32 FUN_0800a9a0(s32 x, s32 y);
s32 FUN_0800a9bc(s32 x, s32 y);
s32 FUN_0800a9d8(s32 x, s32 y);
s32 FUN_0800aa08(s32 x, s32 y);
s32 FUN_0800aa3c(s32 x, s32 y);
s32 FUN_0800aa6c(s32 x, s32 y);
s32 FUN_0800aaac(s32 x, s32 y);
s32 FUN_0800aaec(s32 x, s32 y);
s32 FUN_0800ab20(s32 x, s32 y);
s32 FUN_0800ab48(s32 x, s32 y);
s32 FUN_0800ab68(s32 x, s32 y);
s32 FUN_0800ab90(s32 x, s32 y);
s32 FUN_0800abc4(s32 x, s32 y);
s32 FUN_0800abf8(s32 x, s32 y);
extern bool8 gIsPlayDamageSE;
extern u8 wPauseFrame;
extern u32 gWhitePaintFlags[256 / 32];
extern u32 gLifeRecoverAmount;
extern u32 gSubtankRecoverAmount;
extern u32 gECrystalGainAmount;
extern u8 gInChat;
extern bool8 gIsUsingDoor3D;
extern bool8 gInTransport;
extern u8 gMatrixCount;
extern bool8 gPause;
extern u16 gTimeElfTimer;
extern s32 s32_0202f334;
extern bool8 gIsLemonCollisionRemoved;
extern u16 INTR_CHECK;
extern const ShapeChecker gShapeCheckerUp[16];
extern const ShapeChecker gShapeCheckerDown[16];
extern const ShapeChecker gShapeCheckerLeft[16];
extern const ShapeChecker gShapeCheckerRight[16];
extern const char_t gStringData[];
extern const u16 StringOfsTable[1096];
enum SramHealth
{
  SRAM_NEUTRAL = 0,
  DATA_OK = 0,
  DATA_BROKEN = 0xFFFF
};
struct SaveSlotInfo
{
  bool8 ok[5 + 1];
  __attribute__((aligned(4))) u32 playtime[5 + 1];
  __attribute__((aligned(4))) u32 rank[5];
  __attribute__((aligned(4))) u8 lap[5 + 1];
  __attribute__((aligned(4))) u8 gamemode[5 + 1];
  u32 _;
};
struct SaveHeader
{
  u32 INTI;
  u32 checksum;
  u32 size;
  u8 unk_c;
  u8 pad_d;
  u8 idx;
  u8 unk_f;
};
struct SystemSavedataManager
{
  u8 flags[7];
  u8 mods[16];
  u8 unk_17;
  u8 hardmodeLock;
  u8 ultimateModeLock;
  u8 unlockedMinigames[7];
  u8 pad_21[3];
  u32 minigameHiscores[7];
  u32 mmbn4;
  u8 msgbox;
  u8 title;
  u8 elevator;
  u8 weather;
  u8 cielComputer;
  u8 lifeEnergy;
  u8 crystal;
  u8 disk;
  u8 extraLife;
  u8 bullet;
  u16 _;
};
extern struct SystemSavedataManager gSystemSavedataManager;
extern struct SaveSlotInfo gSaveSlotInfo;
void LoadSystemData(void);
void SaveSystemData(void);
void ToggleMods(mod_t id);
void PrintSaveDataRow(s32 idx, u8 rank, u32 playTime, u8 playLaps, u32 mode, u8 y);
extern const s16 gSineTable[256];
inline static s32 Sin(u8 index, s32 amplitude)
{
  s32 val = amplitude * gSineTable[(u8) index];
  if (val < 0)
  {
    val += 0xFF;
  }
  return val >> 8;
}

inline static s32 Cos(u8 index, s32 amplitude)
{
  s32 val = amplitude * gSineTable[(u8) (index + 64)];
  if (val < 0)
  {
    val += 0xFF;
  }
  return val >> 8;
}

inline static s32 abs(s32 n)
{
  s32 val = n;
  if (n < 0)
  {
    val = -val;
  }
  return val;
}

extern u32 RNG_0202f388;
typedef u16 metatile_id_t;
typedef u16 metatile_attr_t;
typedef u16 Metatile[4];
struct MetatileShift
{
  s16 x;
  s16 y;
  s16 block;
  s16 row;
};
struct MetatilePatch
{
  u16 w;
  u16 h;
};
metatile_attr_t GetMetatileAttr(s32 x, s32 y);
metatile_attr_t GetHazardMetatileAttr(s32 x, s32 y);
metatile_attr_t FUN_080098a4(s32 x, s32 y);
metatile_attr_t GetGroundMetatileAttr(s32 x, s32 y);
void ShiftMetatile(s32 x, s32 y, const struct MetatileShift *s);
void PatchMetatileMap(u32 x, u32 y, struct MetatilePatch *p);
enum MotionState
{
  MOTION_STATE_0,
  MOTION_STATE_1,
  MOTION_STATE_2,
  MOTION_END,
  MOTION_NEXT
};
struct Entity;
struct __attribute__((packed, aligned(2))) MotionCmd
{
  u8 spriteIdx;
  u8 frame;
};
struct MetaspriteHeader
{
  u16 ofs;
  s8 subspriteCount;
  u8 step;
};
struct Subsprite
{
  u16 tileNum : 10;
  u16 xflip : 1;
  u16 yflip : 1;
  u16 size : 2;
  u16 shape : 2;
  s8 x;
  s8 y;
};
struct Motion
{
  const struct MotionCmd **cmds;
  motion_sub_id_t step;
  s8 cmdIdx;
  s8 duration;
  u8 state;
};
struct MotionPltt
{
  u8 len;
  u8 start;
  u8 end;
  u8 _;
};
extern const struct MotionCmd **gDynamicMotionCmdTable[200];
extern struct MotionCmd *gMotionCmd_SM000[];
extern const struct MotionCmd **gStaticMotionCmdTable[254];
extern const struct MetaspriteHeader *gStaticMotionMetaspriteTable[254];
extern struct MetaspriteHeader *gDynamicMotionMetaspriteTable[200];
extern u16 wDynamicMotionPalIDs[200 + 56];
extern u16 wStaticMotionPalIDs[254 + 2];
extern const u32 gDynamicMotionGraphicOffsets[200];
extern u16 wDynamicGraphicTilenums[200 + 56];
void ResetMotion(struct Motion *p, const struct MotionCmd * const * const cmds);
void SetMotionSubID(struct Motion *p, motion_sub_id_t step);
void SetMotion(struct Entity *p, motion_t m);
void GotoMotion(struct Entity *p, motion_t m, u16 r2, u16 r3);
void ResetDynamicMotion(struct Entity *p);
void UpdateMotionGraphic(struct Entity *p);
void InitMotionLocation(void);
void InitScalerotMotion1(struct Entity *p);
void UpdateMotionState(struct Motion *p);
void ForceEntityPalette(struct Entity *p, u8 palID);
struct ScriptEntity;
struct EntityOamData
{
  u32 y : 8;
  u32 affineMode : 2;
  u32 objMode : 2;
  u32 mosaic : 1;
  u32 bpp : 1;
  u32 shape : 2;
  u32 x : 9;
  u32 matrixNum : 5;
  u32 size_affine : 2;
  u16 tileNum : 10;
  u16 priority : 2;
  u16 paletteNum : 4;
  u8 unused : 4;
  u8 xflip : 1;
  u8 yflip : 1;
  u8 size : 2;
  u8 : 8;
};
struct Sprite
{
  struct Sprite *p;
  void (*fn)(struct Sprite *, struct DrawPivot *);
  struct MetaspriteHeader *sprites;
  struct Coord *c;
  struct EntityOamData oam;
  bool8 xflip;
  bool8 yflip;
  u8 spriteIdx;
  u8 angle;
  struct 
  {
    u16 x;
    u16 y;
  } mag;
};
struct Entity
{
  struct Entity *next;
  struct Entity *prev;
  s8 kind;
  u8 id;
  u8 flags;
  u8 flags2;
  u8 mode[4];
  u8 work[4];
  void *onUpdate;
  struct ScriptEntity *scriptEntity;
  u8 uniqueID;
  u8 invincibleID;
  motion_id_t motionID;
  motion_sub_id_t motionSubID;
  u16 tileNum;
  u8 palID;
  u8 savedPalID;
  u8 angle;
  u8 taskCol;
  metatile_attr_t hazardAttr;
  struct Entity *unk_28;
  struct Entity *unk_2c;
  const struct Rect *size;
  struct Sprite spr;
  struct Coord coord;
  struct Coord d;
  struct Coord unk_coord;
  struct Motion motion;
};
typedef struct CollidableEntity
{
  struct Entity s;
  struct Body body;
} Object;
typedef void (*EntityFunc)(struct Entity *);
struct WaveData
{
  u16 type;
  u16 status;
  u32 freq;
  u32 loopStart;
  u32 size;
  s8 data[1];
};
struct ToneData
{
  u8 type;
  u8 key;
  u8 length;
  u8 pan_sweep;
  struct WaveData *wav;
  u8 attack;
  u8 decay;
  u8 sustain;
  u8 release;
};
struct CgbChannel
{
  u8 statusFlags;
  u8 type;
  u8 rightVolume;
  u8 leftVolume;
  u8 attack;
  u8 decay;
  u8 sustain;
  u8 release;
  u8 key;
  u8 envelopeVolume;
  u8 envelopeGoal;
  u8 envelopeCounter;
  u8 pseudoEchoVolume;
  u8 pseudoEchoLength;
  u8 dummy1;
  u8 dummy2;
  u8 gateTime;
  u8 midiKey;
  u8 velocity;
  u8 priority;
  u8 rhythmPan;
  u8 dummy3[3];
  u8 dummy5;
  u8 sustainGoal;
  u8 n4;
  u8 pan;
  u8 panMask;
  u8 modify;
  u8 length;
  u8 sweep;
  u32 frequency;
  u32 *wavePointer;
  u32 *currentPointer;
  struct MusicPlayerTrack *track;
  void *prevChannelPointer;
  void *nextChannelPointer;
  u8 dummy4[8];
};
struct MusicPlayerTrack;
struct SoundChannel
{
  u8 statusFlags;
  u8 type;
  u8 rightVolume;
  u8 leftVolume;
  u8 attack;
  u8 decay;
  u8 sustain;
  u8 release;
  u8 key;
  u8 envelopeVolume;
  u8 envelopeVolumeRight;
  u8 envelopeVolumeLeft;
  u8 pseudoEchoVolume;
  u8 pseudoEchoLength;
  u8 dummy1;
  u8 dummy2;
  u8 gateTime;
  u8 midiKey;
  u8 velocity;
  u8 priority;
  u8 rhythmPan;
  u8 dummy3[3];
  u32 count;
  u32 fw;
  u32 frequency;
  struct WaveData *wav;
  s8 *currentPointer;
  struct MusicPlayerTrack *track;
  void *prevChannelPointer;
  void *nextChannelPointer;
  u32 dummy4;
  u16 xpi;
  u16 xpc;
};
struct MusicPlayerInfo;
typedef void (*MPlayFunc)();
typedef void (*PlyNoteFunc)(u32, struct MusicPlayerInfo *, struct MusicPlayerTrack *);
typedef void (*CgbSoundFunc)(void);
typedef void (*CgbOscOffFunc)(u8);
typedef u32 (*MidiKeyToCgbFreqFunc)(u8, u8, u8);
typedef void (*ExtVolPitFunc)(void);
typedef void (*MPlayMainFunc)(struct MusicPlayerInfo *);
struct SoundInfo
{
  u32 ident;
  vu8 pcmDmaCounter;
  u8 reverb;
  u8 maxChans;
  u8 masterVolume;
  u8 freq;
  u8 mode;
  u8 c15;
  u8 pcmDmaPeriod;
  u8 maxLines;
  u8 gap[3];
  s32 pcmSamplesPerVBlank;
  s32 pcmFreq;
  s32 divFreq;
  struct CgbChannel *cgbChans;
  MPlayMainFunc MPlayMainHead;
  struct MusicPlayerInfo *musicPlayerHead;
  CgbSoundFunc CgbSound;
  CgbOscOffFunc CgbOscOff;
  MidiKeyToCgbFreqFunc MidiKeyToCgbFreq;
  MPlayFunc *MPlayJumpTable;
  PlyNoteFunc plynote;
  ExtVolPitFunc ExtVolPit;
  u8 gap2[16];
  struct SoundChannel chans[12];
  s8 pcmBuffer[792 * 2];
};
struct SongHeader
{
  u8 trackCount;
  u8 blockCount;
  u8 priority;
  u8 reverb;
  struct ToneData *tone;
  u8 *part[1];
};
struct MusicPlayerTrack
{
  u8 flags;
  u8 wait;
  u8 patternLevel;
  u8 repN;
  u8 gateTime;
  u8 key;
  u8 velocity;
  u8 runningStatus;
  u8 keyM;
  u8 pitM;
  s8 keyShift;
  s8 keyShiftX;
  s8 tune;
  u8 pitX;
  s8 bend;
  u8 bendRange;
  u8 volMR;
  u8 volML;
  u8 vol;
  u8 volX;
  s8 pan;
  s8 panX;
  s8 modM;
  u8 mod;
  u8 modT;
  u8 lfoSpeed;
  u8 lfoSpeedC;
  u8 lfoDelay;
  u8 lfoDelayC;
  u8 priority;
  u8 pseudoEchoVolume;
  u8 pseudoEchoLength;
  struct SoundChannel *chan;
  struct ToneData tone;
  u8 gap[10];
  u16 unk_3A;
  u32 unk_3C;
  u8 *cmdPtr;
  u8 *patternStack[3];
};
struct MusicPlayerInfo
{
  struct SongHeader *songHeader;
  u32 status;
  u8 trackCount;
  u8 priority;
  u8 cmd;
  u8 unk_B;
  u32 clock;
  u8 gap[8];
  u8 *memAccArea;
  u16 tempoD;
  u16 tempoU;
  u16 tempoI;
  u16 tempoC;
  u16 fadeOI;
  u16 fadeOC;
  u16 fadeOV;
  struct MusicPlayerTrack *tracks;
  struct ToneData *tone;
  u32 ident;
  MPlayMainFunc MPlayMainNext;
  struct MusicPlayerInfo *musicPlayerNext;
};
struct MusicPlayer
{
  struct MusicPlayerInfo *info;
  struct MusicPlayerTrack *track;
  u8 unk_8;
  u16 unk_A;
};
struct Song
{
  struct SongHeader *header;
  u16 ms;
  u16 me;
};
extern const struct MusicPlayer gMPlayTable[];
extern const struct Song gSongTable[];
extern u8 gMPlayMemAccArea[];
extern char SoundMainRAM[];
extern MPlayFunc gMPlayJumpTable[];
typedef void (*XcmdFunc)(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
extern const XcmdFunc gXcmdTable[];
extern struct CgbChannel gCgbChans[];
extern const u8 gScaleTable[];
extern const u32 gFreqTable[];
extern const u16 gPcmSamplesPerVBlankTable[];
extern const u8 gCgbScaleTable[];
extern const s16 gCgbFreqTable[];
extern const u8 gNoiseTable[];
extern char gNumMusicPlayers[];
extern char gMaxLines[];
u32 umul3232H32(u32 multiplier, u32 multiplicand);
void SoundMain(void);
void SoundMainBTM(void);
void TrackStop(struct MusicPlayerInfo *mplayInfo, struct MusicPlayerTrack *track);
void MPlayMain(struct MusicPlayerInfo *);
void RealClearChain(void *x);
void MPlayContinue(struct MusicPlayerInfo *mplayInfo);
void MPlayStart(struct MusicPlayerInfo *mplayInfo, struct SongHeader *songHeader);
void m4aMPlayStop(struct MusicPlayerInfo *mplayInfo);
void FadeOutBody(struct MusicPlayerInfo *mplayInfo);
void TrkVolPitSet(struct MusicPlayerInfo *mplayInfo, struct MusicPlayerTrack *track);
void MPlayFadeOut(struct MusicPlayerInfo *mplayInfo, u16 speed);
void ClearChain(void *x);
void Clear64byte(void *addr);
void SoundInit(struct SoundInfo *soundInfo);
void MPlayExtender(struct CgbChannel *cgbChans);
void m4aSoundMode(u32 mode);
void MPlayOpen(struct MusicPlayerInfo *mplayInfo, struct MusicPlayerTrack *track, u8 a3);
void CgbSound(void);
void CgbOscOff(u8);
void CgbModVol(struct CgbChannel *chan);
u32 MidiKeyToCgbFreq(u8, u8, u8);
void DummyFunc(void);
void MPlayJumpTableCopy(MPlayFunc *mplayJumpTable);
void SampleFreqSet(u32 freq);
void m4aSoundVSyncOn(void);
void m4aSoundVSyncOff(void);
void m4aMPlayTempoControl(struct MusicPlayerInfo *mplayInfo, u16 tempo);
void m4aMPlayVolumeControl(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u16 volume);
void m4aMPlayPitchControl(struct MusicPlayerInfo *mplayInfo, u16 trackBits, s16 pitch);
void m4aMPlayPanpotControl(struct MusicPlayerInfo *mplayInfo, u16 trackBits, s8 pan);
void ClearModM(struct MusicPlayerTrack *track);
void m4aMPlayModDepthSet(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u8 modDepth);
void m4aMPlayLFOSpeedSet(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u8 lfoSpeed);
void ply_fine(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_goto(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_patt(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_pend(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_rept(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_memacc(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_prio(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_tempo(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_keysh(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_voice(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_vol(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_pan(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_bend(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_bendr(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_lfos(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_lfodl(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_mod(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_modt(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_tune(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_port(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xcmd(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_endtie(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_note(u32 note_cmd, struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xxx(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xwave(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xtype(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xatta(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xdeca(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xsust(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xrele(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xiecv(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xiecl(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xleng(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xswee(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void m4aSoundInit(void);
void m4aMPlayAllStop(void);
void m4aSoundMain(void);
void m4aSongNumStart(u16);
void m4aSoundVSync(void);
void m4aMPlayFadeOut(struct MusicPlayerInfo *, u16);
void m4aSongNumStop(u16);
extern struct WaveData DirectSoundWaveData_unk_08110294;
extern struct WaveData DirectSoundWaveData_unk_08110c24;
extern struct WaveData DirectSoundWaveData_unk_08110e88;
extern struct WaveData DirectSoundWaveData_unk_08113154;
extern struct WaveData DirectSoundWaveData_unk_08113840;
extern struct WaveData DirectSoundWaveData_unk_08114c1c;
extern struct WaveData DirectSoundWaveData_unk_08115430;
extern struct WaveData DirectSoundWaveData_unk_08117e68;
extern struct WaveData DirectSoundWaveData_unk_081182f4;
extern struct WaveData DirectSoundWaveData_unk_08119ae8;
extern struct WaveData DirectSoundWaveData_unk_0811a730;
extern struct WaveData DirectSoundWaveData_unk_0811b9ac;
extern struct WaveData DirectSoundWaveData_unk_08122690;
extern struct WaveData DirectSoundWaveData_unk_081233b0;
extern struct WaveData DirectSoundWaveData_unk_081239a8;
extern struct WaveData DirectSoundWaveData_unk_0812548c;
extern struct WaveData DirectSoundWaveData_unk_08126dc4;
extern struct WaveData DirectSoundWaveData_unk_08128358;
extern struct WaveData DirectSoundWaveData_unk_0812944c;
extern struct WaveData DirectSoundWaveData_unk_0812a598;
extern struct WaveData DirectSoundWaveData_unk_0812d018;
extern struct WaveData DirectSoundWaveData_unk_0812e01c;
extern struct WaveData DirectSoundWaveData_unk_0812fa98;
extern struct WaveData DirectSoundWaveData_unk_081314ac;
extern struct WaveData DirectSoundWaveData_unk_08132a30;
extern struct WaveData DirectSoundWaveData_unk_08134538;
extern struct WaveData DirectSoundWaveData_unk_08135460;
extern struct WaveData DirectSoundWaveData_unk_08135df4;
extern struct WaveData DirectSoundWaveData_unk_081371c4;
extern struct WaveData DirectSoundWaveData_unk_08137d38;
extern struct WaveData DirectSoundWaveData_unk_08139c10;
extern struct WaveData DirectSoundWaveData_unk_0813a868;
extern struct WaveData DirectSoundWaveData_unk_0813acb8;
extern struct WaveData DirectSoundWaveData_unk_0813b20c;
extern struct WaveData DirectSoundWaveData_unk_0813c44c;
extern struct WaveData DirectSoundWaveData_unk_0813dabc;
extern struct WaveData DirectSoundWaveData_unk_08141fa0;
extern struct WaveData DirectSoundWaveData_unk_08143110;
extern struct WaveData DirectSoundWaveData_unk_08143d90;
extern struct WaveData DirectSoundWaveData_unk_0814508c;
extern struct WaveData DirectSoundWaveData_unk_08145da4;
extern struct WaveData DirectSoundWaveData_unk_08148eb8;
extern struct WaveData DirectSoundWaveData_unk_0814c8a0;
extern struct WaveData DirectSoundWaveData_unk_081501c8;
extern struct WaveData DirectSoundWaveData_unk_0815a450;
extern struct WaveData DirectSoundWaveData_unk_0815ace4;
extern struct WaveData DirectSoundWaveData_unk_0815b6c4;
extern struct WaveData DirectSoundWaveData_unk_0815d274;
extern struct WaveData DirectSoundWaveData_unk_0815e2cc;
extern struct WaveData DirectSoundWaveData_unk_0815f970;
extern struct WaveData DirectSoundWaveData_unk_08160ea4;
extern struct WaveData DirectSoundWaveData_unk_08161738;
extern struct WaveData DirectSoundWaveData_unk_0816390c;
extern struct WaveData DirectSoundWaveData_unk_08166950;
extern struct WaveData DirectSoundWaveData_unk_081683d0;
extern struct WaveData DirectSoundWaveData_unk_08169a80;
extern struct WaveData DirectSoundWaveData_unk_0816a764;
extern struct WaveData DirectSoundWaveData_unk_0816b794;
extern struct WaveData DirectSoundWaveData_unk_0816e040;
extern struct WaveData DirectSoundWaveData_unk_081702e8;
extern struct WaveData DirectSoundWaveData_unk_081735f0;
extern struct WaveData DirectSoundWaveData_unk_08174ca0;
extern struct WaveData DirectSoundWaveData_unk_0817595c;
extern struct WaveData DirectSoundWaveData_unk_08176c20;
extern struct WaveData DirectSoundWaveData_unk_08178940;
extern struct WaveData DirectSoundWaveData_unk_0817b640;
extern struct WaveData DirectSoundWaveData_unk_0817c708;
extern struct WaveData DirectSoundWaveData_unk_0817dae8;
extern struct WaveData DirectSoundWaveData_unk_0817f1bc;
extern struct WaveData DirectSoundWaveData_unk_0818343c;
extern struct WaveData DirectSoundWaveData_unk_0818508c;
extern struct WaveData DirectSoundWaveData_unk_08187bf0;
extern struct WaveData DirectSoundWaveData_unk_08189378;
extern struct WaveData DirectSoundWaveData_unk_0818ac48;
extern struct WaveData DirectSoundWaveData_unk_0818e210;
extern struct WaveData DirectSoundWaveData_unk_0818f1f4;
extern struct WaveData DirectSoundWaveData_unk_08190f1c;
extern struct WaveData DirectSoundWaveData_unk_081924bc;
extern struct WaveData DirectSoundWaveData_unk_081969c0;
extern struct WaveData DirectSoundWaveData_unk_08197938;
extern struct WaveData DirectSoundWaveData_unk_08198864;
extern struct WaveData DirectSoundWaveData_unk_0819a3c8;
extern struct WaveData DirectSoundWaveData_unk_0819c514;
extern struct WaveData DirectSoundWaveData_unk_0819d6d8;
extern struct WaveData DirectSoundWaveData_unk_081a04c8;
extern struct WaveData DirectSoundWaveData_unk_081a12e4;
extern struct WaveData DirectSoundWaveData_unk_081a2ee4;
extern struct WaveData DirectSoundWaveData_unk_081a4af0;
extern struct WaveData DirectSoundWaveData_unk_081a71f8;
extern struct WaveData DirectSoundWaveData_unk_081a91ac;
extern struct WaveData DirectSoundWaveData_unk_081a9e24;
extern struct WaveData DirectSoundWaveData_unk_081aafc4;
extern struct WaveData DirectSoundWaveData_unk_081ac48c;
extern struct WaveData DirectSoundWaveData_unk_081ade90;
extern struct WaveData DirectSoundWaveData_unk_081b23c4;
extern struct WaveData DirectSoundWaveData_unk_081b4a2c;
extern struct WaveData DirectSoundWaveData_unk_081b57f0;
extern struct WaveData DirectSoundWaveData_unk_081b66d8;
extern struct WaveData DirectSoundWaveData_unk_081b9144;
extern struct WaveData DirectSoundWaveData_unk_081bb7bc;
extern struct WaveData DirectSoundWaveData_unk_081be04c;
extern struct WaveData DirectSoundWaveData_unk_081c1a30;
extern struct WaveData DirectSoundWaveData_unk_081c320c;
extern struct WaveData DirectSoundWaveData_unk_081c3e54;
extern struct WaveData DirectSoundWaveData_unk_081c7a64;
extern struct WaveData DirectSoundWaveData_unk_081c97e0;
extern struct WaveData DirectSoundWaveData_unk_081cbd58;
extern struct WaveData DirectSoundWaveData_unk_081cdfa8;
extern struct WaveData DirectSoundWaveData_unk_081d1640;
extern struct WaveData DirectSoundWaveData_unk_081d550c;
extern struct WaveData DirectSoundWaveData_unk_081d6540;
extern struct WaveData DirectSoundWaveData_unk_081d6c70;
extern struct WaveData DirectSoundWaveData_unk_081d9f1c;
extern struct WaveData DirectSoundWaveData_unk_081de3ec;
extern struct WaveData DirectSoundWaveData_unk_081e2060;
extern struct WaveData DirectSoundWaveData_unk_081e3bf0;
extern struct WaveData DirectSoundWaveData_unk_081e87e8;
extern struct WaveData DirectSoundWaveData_unk_081ed10c;
extern struct WaveData DirectSoundWaveData_unk_081f1bf0;
extern struct WaveData DirectSoundWaveData_unk_081f3220;
extern struct WaveData DirectSoundWaveData_unk_081f4cb8;
extern struct WaveData DirectSoundWaveData_unk_081f675c;
extern struct WaveData DirectSoundWaveData_unk_081fbaf0;
extern struct WaveData DirectSoundWaveData_unk_081fcc90;
extern struct WaveData DirectSoundWaveData_unk_08200260;
extern struct WaveData DirectSoundWaveData_unk_0820195c;
extern struct WaveData DirectSoundWaveData_unk_082066d8;
extern struct WaveData DirectSoundWaveData_unk_0820b9dc;
extern struct WaveData DirectSoundWaveData_unk_08212ca4;
extern struct WaveData DirectSoundWaveData_unk_08216898;
extern struct WaveData DirectSoundWaveData_unk_0821a5ac;
extern struct WaveData DirectSoundWaveData_unk_08220d20;
extern struct WaveData DirectSoundWaveData_unk_0822171c;
extern struct WaveData DirectSoundWaveData_unk_08222680;
extern struct WaveData DirectSoundWaveData_unk_08223c34;
extern struct WaveData DirectSoundWaveData_unk_082245c4;
extern struct WaveData DirectSoundWaveData_unk_0822a250;
extern struct WaveData DirectSoundWaveData_unk_0822e24c;
extern struct WaveData DirectSoundWaveData_unk_08231c60;
extern struct WaveData DirectSoundWaveData_unk_0823856c;
extern struct WaveData DirectSoundWaveData_unk_08238d74;
extern struct WaveData DirectSoundWaveData_unk_0823c4d4;
extern struct WaveData DirectSoundWaveData_unk_0823e9f8;
extern struct WaveData DirectSoundWaveData_unk_082410fc;
extern struct WaveData DirectSoundWaveData_unk_08245c38;
extern struct WaveData DirectSoundWaveData_unk_0824c608;
extern struct WaveData DirectSoundWaveData_unk_0824e3cc;
extern struct WaveData DirectSoundWaveData_unk_08250490;
extern struct WaveData DirectSoundWaveData_unk_0825403c;
extern struct WaveData DirectSoundWaveData_unk_08255ac0;
extern struct WaveData DirectSoundWaveData_unk_08257794;
extern struct WaveData DirectSoundWaveData_unk_0825b8d8;
extern struct WaveData DirectSoundWaveData_unk_0825dbbc;
extern struct WaveData DirectSoundWaveData_unk_08261a54;
extern struct WaveData DirectSoundWaveData_unk_08264088;
extern struct WaveData DirectSoundWaveData_unk_0826602c;
extern struct WaveData DirectSoundWaveData_unk_0826908c;
extern struct WaveData DirectSoundWaveData_unk_082695cc;
extern struct WaveData DirectSoundWaveData_unk_0826b4f8;
extern struct WaveData DirectSoundWaveData_unk_0826e5ec;
extern struct WaveData DirectSoundWaveData_unk_08271668;
extern struct WaveData DirectSoundWaveData_unk_082732e4;
extern struct WaveData DirectSoundWaveData_unk_08276988;
extern struct WaveData DirectSoundWaveData_unk_08278b44;
extern struct WaveData DirectSoundWaveData_unk_082795d8;
extern struct WaveData DirectSoundWaveData_unk_0827aa18;
extern struct WaveData DirectSoundWaveData_unk_0827bf30;
extern struct WaveData DirectSoundWaveData_unk_0827dd14;
extern struct WaveData DirectSoundWaveData_unk_0827f8ac;
extern struct WaveData DirectSoundWaveData_unk_0828220c;
extern struct WaveData DirectSoundWaveData_unk_08283898;
extern struct WaveData DirectSoundWaveData_unk_08285014;
extern struct WaveData DirectSoundWaveData_unk_08286ec8;
extern struct WaveData DirectSoundWaveData_unk_082890b8;
extern struct WaveData DirectSoundWaveData_unk_0828bc88;
extern struct WaveData DirectSoundWaveData_unk_0828cde0;
extern struct WaveData DirectSoundWaveData_unk_0828e6d8;
extern struct WaveData DirectSoundWaveData_unk_08290124;
extern struct WaveData DirectSoundWaveData_unk_08290cbc;
extern struct WaveData DirectSoundWaveData_unk_08291b24;
extern struct WaveData DirectSoundWaveData_unk_08293e94;
extern struct WaveData DirectSoundWaveData_unk_0829706c;
extern struct WaveData DirectSoundWaveData_unk_0829d180;
extern struct WaveData DirectSoundWaveData_unk_082a0a44;
extern struct WaveData DirectSoundWaveData_unk_082a2424;
extern struct WaveData DirectSoundWaveData_unk_082a4dd8;
extern struct WaveData DirectSoundWaveData_unk_082a6f40;
extern struct WaveData DirectSoundWaveData_unk_082a7ef4;
extern struct WaveData DirectSoundWaveData_unk_082a8a6c;
extern struct WaveData DirectSoundWaveData_unk_082ab314;
extern struct WaveData DirectSoundWaveData_unk_082ada38;
extern struct WaveData DirectSoundWaveData_unk_082aff20;
extern struct WaveData DirectSoundWaveData_unk_082b24ac;
extern struct WaveData DirectSoundWaveData_unk_082b4314;
extern struct WaveData DirectSoundWaveData_unk_082b7874;
extern struct WaveData DirectSoundWaveData_unk_082b94c4;
extern struct WaveData DirectSoundWaveData_unk_082ba04c;
extern struct WaveData DirectSoundWaveData_unk_082badcc;
extern struct WaveData DirectSoundWaveData_unk_082bbf8c;
extern struct WaveData DirectSoundWaveData_unk_082bd6f8;
extern struct WaveData DirectSoundWaveData_unk_082be9fc;
extern struct WaveData DirectSoundWaveData_unk_082c0e1c;
extern struct WaveData DirectSoundWaveData_unk_082c2494;
extern struct WaveData DirectSoundWaveData_unk_082c5820;
extern struct WaveData DirectSoundWaveData_unk_082c8c64;
extern struct WaveData DirectSoundWaveData_unk_082c8dbc;
extern struct WaveData DirectSoundWaveData_unk_082ca484;
extern struct WaveData DirectSoundWaveData_unk_082cc434;
extern struct WaveData DirectSoundWaveData_unk_082ce0c4;
extern struct WaveData DirectSoundWaveData_unk_082d03e4;
extern struct WaveData DirectSoundWaveData_unk_082d33d4;
extern struct WaveData DirectSoundWaveData_unk_082d6444;
extern struct WaveData DirectSoundWaveData_unk_082d7b98;
extern struct WaveData DirectSoundWaveData_unk_082d9060;
extern struct WaveData DirectSoundWaveData_unk_082d9ee8;
extern struct WaveData DirectSoundWaveData_unk_082db714;
extern struct WaveData DirectSoundWaveData_unk_082dcee0;
extern struct WaveData DirectSoundWaveData_unk_082ded00;
extern struct WaveData DirectSoundWaveData_unk_082e0dfc;
extern struct WaveData DirectSoundWaveData_unk_082e3a38;
extern struct WaveData DirectSoundWaveData_unk_082e5ddc;
extern struct WaveData DirectSoundWaveData_unk_082e682c;
extern struct WaveData DirectSoundWaveData_unk_082e8da0;
extern struct WaveData DirectSoundWaveData_unk_082e97d0;
extern struct WaveData DirectSoundWaveData_unk_082eaa24;
extern struct WaveData DirectSoundWaveData_unk_082eba40;
extern struct WaveData DirectSoundWaveData_unk_082ed794;
extern struct WaveData DirectSoundWaveData_unk_082ee0c4;
extern struct WaveData DirectSoundWaveData_unk_082f082c;
extern struct WaveData DirectSoundWaveData_unk_082f21d8;
extern struct WaveData DirectSoundWaveData_unk_082f41a8;
extern struct WaveData DirectSoundWaveData_unk_082f50c0;
extern struct WaveData DirectSoundWaveData_unk_082f73dc;
extern struct WaveData DirectSoundWaveData_unk_082f8634;
extern struct WaveData DirectSoundWaveData_unk_082f9214;
extern struct WaveData DirectSoundWaveData_unk_082fa094;
extern struct WaveData DirectSoundWaveData_unk_082fc464;
extern struct WaveData DirectSoundWaveData_unk_082fe94c;
extern struct WaveData DirectSoundWaveData_unk_082ff658;
extern struct WaveData DirectSoundWaveData_unk_0830017c;
extern struct WaveData DirectSoundWaveData_unk_083010a4;
extern struct WaveData DirectSoundWaveData_unk_08302ba8;
extern struct WaveData DirectSoundWaveData_unk_08304d4c;
extern struct WaveData DirectSoundWaveData_unk_08305e30;
extern struct WaveData DirectSoundWaveData_unk_083077d8;
extern struct WaveData DirectSoundWaveData_unk_08309a84;
extern struct WaveData DirectSoundWaveData_unk_0830a800;
extern struct WaveData DirectSoundWaveData_unk_08312b68;
extern struct WaveData DirectSoundWaveData_unk_08314f1c;
extern struct WaveData DirectSoundWaveData_unk_08316548;
extern struct WaveData DirectSoundWaveData_unk_08318644;
extern struct WaveData DirectSoundWaveData_unk_08319f40;
extern struct WaveData DirectSoundWaveData_unk_0831c184;
extern struct WaveData DirectSoundWaveData_unk_0831d4fc;
extern struct WaveData DirectSoundWaveData_unk_0831e9dc;
extern struct WaveData DirectSoundWaveData_unk_08322e60;
extern SoundID SoundID1;
extern SoundID SoundID2;
extern u32 gSongCount;
extern struct MusicPlayerTrack gMPlayTracks[21];
extern const struct Song gSongTable[336];
extern const struct ToneData voicegroup000[128];
extern const struct ToneData voicegroup001[128];
extern const struct ToneData voicegroup002[122];
void InitSound(void);
void StopAllMusics(void);
void TurnDownBGM(void);
void TurnUpBGM(void);
void playBGM(SoundID n);
void fadeoutBGM(SoundID n);
bool32 _isSoundPlaying(SoundID n);
s16 PlaySound(SoundID id);
void StopSound(s16 n);
void fadeoutSound(s16 r0, u16 r1);
bool32 isSoundPlaying(SoundID n);
void SetStageNoiseVolume(SoundID n);
struct ChildreProps
{
  struct Entity *unk_b4;
  u32 unk_b8;
  struct Coord unk_bc;
  u8 unk_c4;
  u8 unk_c5;
  bool8 shouldTurnRight;
  u8 unk_c7;
  struct Coord unk_c8;
  u8 unk_d0[20];
};
struct DeathtanzProps
{
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
struct GlacierleProps
{
  u32 unk_b4;
  struct VFX *unk_b8;
  s32 unk_bc;
  u8 unk_c0;
  u8 unk_c1;
  bool8 shouldRightDir;
  u8 unk_c3[5];
  struct Coord unk_c8;
  u8 unk_d0[20];
};
struct OmegaWhiteProps
{
  u8 unk_b4[4];
  s32 unk_y;
  struct Entity *unk_bc;
  u16 unk_c0;
  u8 unk_c2[18];
  u32 unk_d4;
  u8 unk_d8[12];
};
struct CopyXProps
{
  u8 unk_b4[16];
  u8 unk_c4;
  u8 unk_c5;
  u8 unk_c6[22];
  u8 unk_dc;
  s8 unk_dd;
  u8 unk_de[6];
};
struct HellbatProps
{
  u8 unk_b4[32];
  s32 unk_d4;
  u8 unk_d8[12];
};
struct PAquaModProps
{
  u8 unk_b4[6];
  u16 x;
  s32 y;
  u8 unk_c0[36];
};
struct Boss
{
  struct Entity s;
  struct Body body;
  union 
  {
    u8 raw[48];
    struct OmegaWhiteProps omegaWhite;
    struct CopyXProps copyx;
    struct GlacierleProps glacierle;
    struct ChildreProps childre;
    struct DeathtanzProps deathtanz;
    struct HellbatProps hellbat;
    struct PAquaModProps paquam;
  } props;
};
typedef void (*BossFunc)(struct Boss *);
struct Elf
{
  struct Entity s;
  struct Body body;
  u8 buffer[16];
};
typedef void (*ElfFunc)(struct Elf *);
struct Enemy
{
  struct Entity s;
  struct Body body;
  u8 props[16];
};
typedef void (*EnemyFunc)(struct Enemy *);
struct KeyState
{
  KEY_INPUT input;
  KEY_INPUT last;
  KEY_INPUT pressed;
  KEY_INPUT field3_0x6;
  bool16 firstRead;
  __attribute__((aligned(2))) u8 unk_0a[10];
  u8 field6_0x14;
  u8 field7_0x15;
  u8 field8_0x16;
  u8 field9_0x17;
};
extern struct KeyState gJoypad[2];
void PollKeyInput(void);
enum MenuZeroColor
{
  MZC_NORMAL,
  MZC_HARD,
  MZC_ULTIMATE
};
enum 
{
  ZERO_GROUND = 0,
  ZERO_AIR = 1,
  ZERO_WALL = 2,
  ZERO_LADDER = 3,
  ZERO_DAMAGED = 4,
  ZERO_DOOR_2D = 5,
  ZERO_DOOR_3D = 6,
  ZERO_BINDED = 7,
  ZERO_FLOAT = 8,
  ZERO_TALK = 9,
  ZERO_TELEPORT = 10,
  ZERO_CYBER = 11
};
struct ZeroAsset
{
  u8 satelites[2];
  u16 unused;
  u16 fusions;
  u16 EC;
  u8 subtankHP[4];
};
struct KeyMap
{
  KEY_INPUT jump;
  KEY_INPUT dash;
  KEY_INPUT main;
  KEY_INPUT sub;
};
struct KeyConfig
{
  struct KeyMap keys;
  u8 btnMode;
  u8 attackMode;
  u8 unk_a;
  u8 _;
};
struct ZeroStatus
{
  struct ZeroAsset asset;
  weapon_t mainWeapon;
  weapon_t subWeapon;
  u8 element;
  u8 head;
  u8 body;
  u8 foot;
  u16 exSkill;
  u16 unlockedExSkill;
  u8 unlockedWeapon;
  u8 unlockedHead;
  u8 unlockedBody;
  u8 unlockedFoot;
  u8 menuZeroColor;
  u8 unk_1b;
  struct KeyConfig keyMap;
  u8 charge[2];
  u16 unk_2a;
  u8 maxHP;
  u8 dying;
  u16 pad_2e;
};
struct Zero_b4
{
  struct ZeroStatus status;
  weapon_t mainCopy;
  weapon_t subCopy;
  u16 unk_e6;
  u8 prevMode;
  u8 prevPhase;
  __attribute__((aligned(4))) u8 attackMode[4];
  __attribute__((aligned(4))) u8 unused_f0[4];
  struct Entity *shadow;
  u8 wallDustTimer;
  __attribute__((aligned(2))) SoundID sound;
  u8 unk_fc[4];
  struct Coord prevCoord;
  s32 blownSpeed;
  s32 deltaX;
  u8 dashTimer;
  u8 unk_111;
  bool8 dashable;
  bool8 softPlatform;
  s32 softPlatformY;
};
struct Zero
{
  struct Entity s;
  struct Body body;
  struct Zero_b4 unk_b4;
  bool8 isRightDir;
  bool8 isAreaChange;
  bool8 airJumpped;
  bool8 ripple;
  bool8 canSplashJump;
  u8 slow;
  u8 idleFrame;
  bool8 slip;
  u8 floatTimer;
  cyberelf_t unk_121;
  bool8 blown;
  u8 dashDustTimer;
  struct __attribute__((packed, aligned(1))) 
  {
    u8 move : 1;
    u8 dash : 1;
    u8 shield : 1;
    u8 b3 : 1;
    u8 mainCharge : 1;
    u8 subCharge : 1;
    u8 b6 : 1;
    u8 b7 : 1;
  } restriction;
  u8 chargeSaber;
  u8 rodID;
  u8 unk_127;
  u8 usingWeapon;
  u8 atkCooltime;
  u8 tripleSlashCounter;
  u8 forceWeapon;
  u8 bulletCount;
  u8 saberAction;
  u8 unk_12e;
  __attribute__((aligned(1))) u8 unk_12f[2];
  u8 mainChargeFrame;
  u8 subChargeFrame;
  u8 unk_rod_133;
  u8 splitHeavensWait;
  u8 unk_135;
  u8 unk_136;
  u8 unk_137;
  s16 recoilJumpDx;
  u8 unk_13a;
  u8 rodToggle;
  __attribute__((aligned(1))) u8 unk_13c[2];
  motion_t prevMotion;
  u8 motionCmdIdx;
  u8 motionDuration;
  bool8 poseFixed;
  union __attribute__((aligned(1), packed)) 
  {
    u8 raw;
    u8 lo : 4;
    u8 hi : 4;
  } unk_143;
  __attribute__((aligned(1))) u8 unk_144[3];
  u8 posture;
  u8 prevPosture;
  u8 unk_149;
  struct Border border;
  u8 hazard[16];
  u16 hazardIDs[16];
  u8 hazardCount;
  bool8 isGround;
  bool8 antlion;
  bool8 pushedOut;
  u8 horizontalSlide;
  struct PlayerInputState
  {
    KEY_INPUT history[64];
    KEY_INPUT pressed;
    KEY_INPUT raw;
    zero_input_t val;
    struct KeyMap mapping;
    u8 ultimateCommand_224[3];
    u8 ultimateCommand_227[3];
    u8 ultimateCommand_22a[2];
    u8 ultimateCommand_22c[3];
    u8 commandDashTimer;
  } input;
  bool8 globbed;
  bool8 inCyberSpace;
  u8 elfMotion;
  u8 subtankFilledFrame;
  u8 unk_234;
  s32 door3d_x;
  u8 unk_23c[64];
  union 
  {
    u8 raw[16];
    struct 
    {
      u8 unk_27c;
      u8 unk_27d;
      u16 unk_27e;
      u8 unk_280[4];
      u8 unk_284;
      u8 unk_285;
      u8 unk_286;
      u8 unk_287;
      u8 unk_288[4];
    } zero;
    struct 
    {
      u8 element;
      u8 life;
      u8 unk_27e;
      u8 unk_27f;
      struct Entity *unk_280[3];
    } copyx;
    struct 
    {
      s32 x;
      struct Enemy *enemy;
      u8 unk_8;
      u8 unk_9;
      u8 unk_a;
      u8 unk_b;
      s32 y;
    } harpuia;
    struct 
    {
      s32 x;
      u8 unk_4[12];
    } leviathan;
  } mg;
};
typedef void (*ZeroFunc)(struct Zero *);
struct Projectile
{
  struct Entity s;
  struct Body body;
  u8 work[4];
  struct Coord prevCoord;
  u32 unk_c0;
};
typedef void (*ProjectileFunc)(struct Projectile *);
struct Solid
{
  struct Entity s;
  struct Body body;
  union 
  {
    u8 raw[16];
  } props;
};
typedef void (*SolidFunc)(struct Solid *);
struct TempProps
{
  struct Coord c;
  u8 *unk_7c;
  u8 work[4];
};
struct Unk25Props
{
  struct Coord c;
  u8 unk_7c[4];
  u16 unk_80;
  u16 unk_82;
};
struct Unk28Props
{
  u16 unk_0;
  u16 unk_2;
  s32 unk_4;
  u8 unk_8[8];
};
struct Unk32Props
{
  s16 unk_0;
  u8 unk_2[2];
  u32 unk_4;
  u32 unk_8;
  u16 unk_c;
  u16 unk_e;
};
struct Unk69Props
{
  struct Coord c;
  u8 unk_8[8];
};
struct SnowProps
{
  u32 unk_0;
  u8 unk_4[12];
};
struct NecroProps
{
  motion_t *motions;
  u8 unk_04;
  u8 unk_05;
  u8 unk_06[10];
};
struct BubbleProps
{
  u8 unk_0[4];
  s32 unk_4;
  u8 unk_8[8];
};
struct Unk83Props
{
  s32 unk_0;
  s32 unk_4[2];
  u8 unk_c[4];
};
struct VFX
{
  struct Entity s;
  union 
  {
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
};
struct Weapon;
struct WeaponProps
{
  struct Zero *z;
  u8 props[2][8];
  u8 unk_c8[36];
};
struct Rod_b4
{
  struct Zero *z;
  u8 element;
  u8 atk;
  u8 unk_06;
  u8 comboLv;
  u8 unk_08;
  u8 unk_09;
  u8 unk_0a;
  u8 unk_0b;
  u8 unk_0c[8];
  u8 unk_c8[36];
};
struct Buster_b4
{
  struct Zero *z;
  struct Coord c;
  u8 unk_c0;
  u8 element;
  u8 unk_c2;
  u8 unk_c3;
  u8 unk_c4[40];
};
struct Saber_b4
{
  struct Zero *z;
  u8 props[8];
  u8 element;
  u8 atk;
  u8 nature;
  bool8 unk;
  u8 unk_c4[40];
};
struct SaberWave_b4
{
  struct Weapon *saber;
  struct Zero *z;
  u8 props[4];
  u8 element;
  u8 atk;
  u8 flags;
  bool8 unk;
  u8 unk_c4[40];
};
struct Weapon
{
  struct Entity s;
  struct Body body;
  union 
  {
    u8 raw[56];
    struct WeaponProps common;
    struct Buster_b4 buster;
    struct Saber_b4 saber;
    struct SaberWave_b4 wave;
    struct Rod_b4 rod;
  } props;
};
typedef void (*WeaponFunc)(struct Weapon *);
struct Entity;
struct EntityHeader
{
  struct Entity *arr;
  s16 type;
  s16 size;
  s16 length;
  s16 remaining;
  struct Entity *last;
  struct Entity *free;
  struct Entity *next;
  struct Entity *prev;
  u32 unk[3];
};
void InitEntityHeader(struct EntityHeader *h, s8 kind, struct Entity *arr, s16 size, s16 count);
struct Task
{
  struct Task *next;
  void (*fn)(struct Task *, struct DrawPivot *);
};
struct TaskManager
{
  struct Task *buffer[128];
  struct Task *(*tasks)[128];
  struct Pivot *pivot;
  void *_;
};
void ResetTaskManager(struct TaskManager *tm);
void SetTaskPivot(struct TaskManager *tm, struct Pivot *pivot);
void PrependTask(struct TaskManager *tm, struct Task *task);
void AppendTask(struct TaskManager *tm, struct Task *task, s16 prio, s16 x);
void ClearTaskBuffer(struct TaskManager *tm);
void RunAllTasks(struct TaskManager *tm);
void SetTaskCallback(struct Task *t, void *cb);
extern struct EntityHeader *pCurEntityHeader;
extern struct EntityHeader *gZeroHeaderPtr;
extern struct EntityHeader *gWeaponHeaderPtr;
extern struct EntityHeader *gBossHeaderPtr;
extern struct EntityHeader *gSolidHeaderPtr;
extern struct EntityHeader *gVFXHeaderPtr;
extern struct EntityHeader *gProjectileHeaderPtr;
extern struct EntityHeader *gEnemyHeaderPtr;
extern struct EntityHeader *gElfHeaderPtr;
extern struct Zero gZero;
extern struct Weapon gWeapons[24];
extern struct Boss gBosses[5];
extern struct Enemy gEnemies[18];
extern struct Projectile gProjectiles[24];
extern struct VFX gVFXs[64];
extern struct Solid gSolids[22];
extern struct Elf gElfEntities[16];
extern u8 gEntityIDGenerator;
void setCurProcessedEntityHeader(struct EntityHeader *h);
struct Entity *AllocEntityLast(struct EntityHeader *h);
struct Entity *AllocEntityFirst(struct EntityHeader *h);
void DeleteEntity(struct Entity *p);
void DeleteEntityEx(struct EntityHeader *h, struct Entity *z);
void UpdateEntities(struct EntityHeader *h);
void UpdateHazardEntities(struct EntityHeader *h);
void ignoreEntityFn(struct EntityHeader *h);
void RunDamageEffect(struct EntityHeader *h);
void RegisterHitboxes(struct EntityHeader *h);
void DrawEntity(struct EntityHeader *h, struct TaskManager *r1);
void DrawCollidableEntity(struct EntityHeader *h, struct TaskManager *r1);
struct Entity *GetNearestEntity(struct EntityHeader *h, struct Coord *c);
void InitNonAffineMotion(struct Entity *e);
void InitRotatableMotion(struct Entity *e);
u16 countSpecificEntities1(struct EntityHeader *h, u8 id);
u16 countSpecificEntities2(struct EntityHeader *h, u8 id, u8 r2, u8 r3);
void UpdateStageEntities(struct Coord *viewport);
void InitNonAffineSprite(struct Sprite *s, struct MetaspriteHeader *sprites, struct Coord *c);
void InitRotatableSprite(struct Sprite *s, struct MetaspriteHeader *sprites, struct Coord *c);
void InitScalerotSprite1(struct Sprite *s, struct MetaspriteHeader *sprites, struct Coord *c);
void InitScalerotSprite2(struct Sprite *s, struct MetaspriteHeader *sprites, struct Coord *c);
void RotateSprite(struct Sprite *s, s32 angle);
void ScalerotSprite(struct Sprite *s, s32 angle);
void UpdateEntityPaletteID(struct Entity *p);
void PaintEntityWhite(struct Entity *p);
void FUN_0801779c(struct Entity *p);
bool32 isKilled(struct Entity *p);
typedef EnemyFunc EnemyRoutine[5];
extern const EnemyRoutine * const gEnemyFnTable[72 + 1];
void DeleteEnemy(struct Entity *p);
bool32 IsFrozen(struct Entity *p);
void Beetank_Init(struct Enemy *p);
void Beetank_Update(struct Enemy *p);
void Beetank_Die(struct Enemy *p);
const EnemyRoutine gBeetankRoutine = {[0] = Beetank_Init, [1] = Beetank_Update, [2] = Beetank_Die, [3] = (void *) DeleteEnemy, [4] = (EnemyFunc) DeleteEntity};
struct Enemy *CreateBeetank(struct Coord *c, u8 n);
bool8 nop_0807bc8c(struct Enemy *p);
bool8 nop_0807bd3c(struct Enemy *p);
bool8 nop_0807bde4(struct Enemy *p);
void FUN_0807bde8(struct Enemy *p);
bool8 FUN_0807be14(struct Enemy *p);
void nop_0807be18(struct Enemy *p);
bool8 FUN_0807be1c(struct Enemy *p);
void nop_0807bea4(struct Enemy *p);
bool8 nop_0807bc8c(struct Enemy *p);
bool8 nop_0807bd3c(struct Enemy *p);
bool8 nop_0807bde4(struct Enemy *p);
bool8 FUN_0807be14(struct Enemy *p);
bool8 FUN_0807be1c(struct Enemy *p);
static const EnemyFunc sUpdates1[5] = {(EnemyFunc) nop_0807bc8c, (EnemyFunc) nop_0807bd3c, (EnemyFunc) nop_0807bde4, (EnemyFunc) FUN_0807be14, (EnemyFunc) FUN_0807be1c};
void FUN_0807bc90(struct Enemy *p);
void FUN_0807bd40(struct Enemy *p);
void FUN_0807bde8(struct Enemy *p);
void nop_0807be18(struct Enemy *p);
void FUN_0807be20(struct Enemy *p);
static const EnemyFunc sUpdates2[5] = {FUN_0807bc90, FUN_0807bd40, FUN_0807bde8, nop_0807be18, FUN_0807be20};
static const struct Collision sCollisions[2] = {{.kind = DDP, .faction = FACTION_ENEMY, .damage = 2, .atkType = 0x00, .element = 0x00, .nature = 0x00, .comboLv = 0, .remaining = 1, .layer = 0x00000001, .range = {0 << 8, -(10 << 8), 24 << 8, 24 << 8}}, {.kind = DRP, .faction = FACTION_ENEMY, .atkType = (0xFFFFFFFF >> 0) & 0xFF, .element = (0xFFFFFFFF >> 8) & 0xFF, .nature = (0xFFFFFFFF >> 16) & 0xFF, .comboLv = (0xFFFFFFFF >> 24) & 0xFF, .hitzone = 1, .remaining = 0, .range = {0 << 8, -(10 << 8), 24 << 8, 24 << 8}}};
static const struct Coord sElementCoord = {0 << 8, -(8 << 8)};
struct Beetank
{
  struct Entity s;
  struct Body body;
  u8 unk_b4[6];
  u8 unk_ba;
};
void FUN_0807be50(struct Enemy *p);
void Beetank_Update(struct Enemy *p)
{
  if (p->body.status & 0x200)
  {
    {
      u32 tbl;
      u32 id;
      EntityFunc **routine_table;
      tbl = (u32) gEnemyFnTable;
      id = ((struct Entity *) p)->id << 2;
      routine_table = (EntityFunc **) (tbl + id);
      *((u32 *) ((struct Entity *) p)->mode) = 2;
      ((struct Entity *) p)->onUpdate = (void *) (*routine_table)[2];
    }
    Beetank_Die(p);
    return;
  }
  {
    register struct Enemy *pp asm("r5") = p;
    sUpdates1[pp->s.mode[1]](pp);
    FUN_0807be50(pp);
    {
      register s32 push asm("r0") = PushoutToLeft1(pp->s.coord.x + (4 << 8), pp->s.coord.y - (4 << 8));
      register s32 pushc asm("r6") = push;
      if (push != 0) pp->s.coord.x += pushc;
    }
    {
      register s32 push asm("r0") = PushoutToRight1(pp->s.coord.x - (4 << 8), pp->s.coord.y - (4 << 8));
      register s32 pushc asm("r6") = push;
      if (push != 0) pp->s.coord.x += pushc;
    }
    {
      s32 a, b, ca, cb;
      a = FUN_08009f6c(pp->s.coord.x - (16 << 8), pp->s.coord.y - (6 << 8));
      ca = a - 0x40;
      b = FUN_08009f6c(pp->s.coord.x + (16 << 8), pp->s.coord.y - (6 << 8));
      cb = b - 0x40;
      pp->s.coord.y = (ca < cb) ? a : b;
    }
    if (IsFrozen(&pp->s))
    {
      ((struct Beetank *) pp)->unk_ba = pp->s.mode[1];
    }
    else
    {
      sUpdates2[pp->s.mode[1]](pp);
    }
  }
}
