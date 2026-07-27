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
struct __attribute__((packed, aligned(2))) BgCnt {
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
struct PlttData {
  u16 r : 5;
  u16 g : 5;
  u16 b : 5;
  u16 unused_15 : 1;
} __attribute__((packed));
struct OamData {
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
struct BgAffineSrcData {
  s32 texX;
  s32 texY;
  s16 scrX;
  s16 scrY;
  s16 sx;
  s16 sy;
  u16 alpha;
};
struct BgAffineDstData {
  s16 pa;
  s16 pb;
  s16 pc;
  s16 pd;
  s32 dx;
  s32 dy;
};
struct ObjAffineSrcData {
  s16 xScale;
  s16 yScale;
  u16 rotation;
};
struct SioMultiCnt {
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
struct Coord16 {
  s16 x;
  s16 y;
};
struct Coord {
  s32 x;
  s32 y;
};
struct Border {
  s32 left;
  s32 right;
  s32 top;
  s32 bottom;
};
struct DrawPivot {
  struct Coord coord;
  struct Coord lefttop;
  struct Coord offset;
};
struct Pivot {
  struct Coord *coord;
  struct Coord *offset;
  void *_;
};
struct BgMapHeader {
  u32 unk_00;
  u16 w;
  u16 h;
};
struct Rect {
  s16 x;
  s16 y;
  s16 w;
  s16 h;
};
struct Area32 {
  s32 left;
  s32 top;
  s32 right;
  s32 bottom;
};
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
typedef char_t* str_t;
typedef u8 motion_id_t;
typedef u8 motion_sub_id_t;
typedef u16 motion_t;
typedef u8 weapon_t;
typedef u32 zero_input_t;
typedef u16 tileset_t;
typedef u8 tileset_ofs_t;
typedef s32 (*ShapeChecker)(s32 x, s32 y);
struct Coord;
void* Malloc(u32 bytesize);
s32 FUN_08009f6c(s32 x, s32 y);
void CreateFirework(s32 x, s32 y, bool8 r2);
void ResetEntityEnvironment(void);
void FUN_0802511c(void);
void clearStageDisk(void);
u32 TryDropItem(u32 table, struct Coord* c);
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
typedef long int ptrdiff_t;
typedef unsigned long int size_t;
typedef int wchar_t;
extern struct SoundInfo* SOUND_INFO_PTR;
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
enum SramHealth {
  SRAM_NEUTRAL = 0,
  DATA_OK = 0,
  DATA_BROKEN = 0xFFFF,
};
struct SaveSlotInfo {
  bool8 ok[5 + 1];
  u32 __attribute__((aligned(4))) playtime[5 + 1];
  u32 __attribute__((aligned(4))) rank[5];
  u8 __attribute__((aligned(4))) lap[5 + 1];
  u8 __attribute__((aligned(4))) gamemode[5 + 1];
  u32 _;
};
struct SaveHeader {
  u32 INTI;
  u32 checksum;
  u32 size;
  u8 unk_c;
  u8 pad_d;
  u8 idx;
  u8 unk_f;
};
struct SystemSavedataManager {
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
static inline s32 Sin(u8 index, s32 amplitude) {
  s32 val = ((amplitude * gSineTable[(u8)index]));
  if (val < 0) {
    val += 0xFF;
  }
  return (val >> 8);
}
static inline s32 Cos(u8 index, s32 amplitude) {
  s32 val = ((amplitude * gSineTable[(u8)((index) + 64)]));
  if (val < 0) {
    val += 0xFF;
  }
  return (val >> 8);
}
static inline s32 abs(s32 n) {
  s32 val = n;
  if (n < 0) {
    val = -val;
  }
  return val;
}
extern u32 RNG_0202f388;
struct Collision;
struct Body;
typedef void (*BodyFunc)(struct Body*, struct Coord*, struct Coord*);
struct Body {
  const struct Collision* collisions;
  const struct Collision* processing;
  struct Coord* coord;
  struct Body* enemy;
  struct Body* bindPair;
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
  struct CollidableEntity* parent;
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
typedef u16 metatile_id_t;
typedef u16 metatile_attr_t;
typedef u16 Metatile[4];
struct MetatileShift {
  s16 x;
  s16 y;
  s16 block;
  s16 row;
};
struct MetatilePatch {
  u16 w;
  u16 h;
};
metatile_attr_t GetMetatileAttr(s32 x, s32 y);
metatile_attr_t GetHazardMetatileAttr(s32 x, s32 y);
metatile_attr_t FUN_080098a4(s32 x, s32 y);
metatile_attr_t GetGroundMetatileAttr(s32 x, s32 y);
void ShiftMetatile(s32 x, s32 y, const struct MetatileShift* s);
void PatchMetatileMap(u32 x, u32 y, struct MetatilePatch* p);
enum MotionState {
  MOTION_STATE_0,
  MOTION_STATE_1,
  MOTION_STATE_2,
  MOTION_END,
  MOTION_NEXT,
};
struct Entity;
struct __attribute__((packed, aligned(2))) MotionCmd {
  u8 spriteIdx;
  u8 frame;
};
struct MetaspriteHeader {
  u16 ofs;
  s8 subspriteCount;
  u8 step;
};
struct Subsprite {
           u16 tileNum : 10;
           u16 xflip : 1;
           u16 yflip : 1;
           u16 size : 2;
           u16 shape : 2;
           s8 x;
           s8 y;
};
struct Motion {
  const struct MotionCmd** cmds;
  motion_sub_id_t step;
  s8 cmdIdx;
  s8 duration;
  u8 state;
};
struct MotionPltt {
  u8 len;
  u8 start;
  u8 end;
  u8 _;
};
extern const struct MotionCmd** gDynamicMotionCmdTable[200];
extern struct MotionCmd* gMotionCmd_SM000[];
extern const struct MotionCmd** gStaticMotionCmdTable[254];
extern const struct MetaspriteHeader* gStaticMotionMetaspriteTable[254];
extern struct MetaspriteHeader* gDynamicMotionMetaspriteTable[200];
extern u16 wDynamicMotionPalIDs[200 + 56];
extern u16 wStaticMotionPalIDs[254 + 2];
extern const u32 gDynamicMotionGraphicOffsets[200];
extern u16 wDynamicGraphicTilenums[200 + 56];
void ResetMotion(struct Motion* p, const struct MotionCmd* const* const cmds);
void SetMotionSubID(struct Motion* p, motion_sub_id_t step);
void SetMotion(struct Entity* p, motion_t m);
void GotoMotion(struct Entity* p, motion_t m, u16 r2, u16 r3);
void ResetDynamicMotion(struct Entity* p);
void UpdateMotionGraphic(struct Entity* p);
void InitMotionLocation(void);
void InitScalerotMotion1(struct Entity* p);
void UpdateMotionState(struct Motion* p);
void ForceEntityPalette(struct Entity* p, u8 palID);
struct ScriptEntity;
struct EntityOamData {
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
struct Sprite {
  struct Sprite* p;
  void (*fn)(struct Sprite*, struct DrawPivot*);
  struct MetaspriteHeader* sprites;
  struct Coord* c;
  struct EntityOamData oam;
  bool8 xflip;
  bool8 yflip;
  u8 spriteIdx;
  u8 angle;
  struct {
    u16 x;
    u16 y;
  } mag;
};
struct Entity {
  struct Entity* next;
  struct Entity* prev;
  s8 kind;
  u8 id;
  u8 flags;
  u8 flags2;
  u8 mode[4];
  u8 work[4];
  void* onUpdate;
  struct ScriptEntity* scriptEntity;
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
  struct Entity* unk_28;
  struct Entity* unk_2c;
  const struct Rect* size;
  struct Sprite spr;
  struct Coord coord;
  struct Coord d;
  struct Coord unk_coord;
  struct Motion motion;
};
typedef struct CollidableEntity {
  struct Entity s;
  struct Body body;
} Object;
typedef void (*EntityFunc)(struct Entity*);
struct WaveData {
  u16 type;
  u16 status;
  u32 freq;
  u32 loopStart;
  u32 size;
  s8 data[1];
};
struct ToneData {
  u8 type;
  u8 key;
  u8 length;
  u8 pan_sweep;
  struct WaveData* wav;
  u8 attack;
  u8 decay;
  u8 sustain;
  u8 release;
};
struct CgbChannel {
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
  u32* wavePointer;
  u32* currentPointer;
  struct MusicPlayerTrack* track;
  void* prevChannelPointer;
  void* nextChannelPointer;
  u8 dummy4[8];
};
struct MusicPlayerTrack;
struct SoundChannel {
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
  struct WaveData* wav;
  s8* currentPointer;
  struct MusicPlayerTrack* track;
  void* prevChannelPointer;
  void* nextChannelPointer;
  u32 dummy4;
  u16 xpi;
  u16 xpc;
};
struct MusicPlayerInfo;
typedef void (*MPlayFunc)();
typedef void (*PlyNoteFunc)(u32, struct MusicPlayerInfo*, struct MusicPlayerTrack*);
typedef void (*CgbSoundFunc)(void);
typedef void (*CgbOscOffFunc)(u8);
typedef u32 (*MidiKeyToCgbFreqFunc)(u8, u8, u8);
typedef void (*ExtVolPitFunc)(void);
typedef void (*MPlayMainFunc)(struct MusicPlayerInfo*);
struct SoundInfo {
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
  struct CgbChannel* cgbChans;
  MPlayMainFunc MPlayMainHead;
  struct MusicPlayerInfo* musicPlayerHead;
  CgbSoundFunc CgbSound;
  CgbOscOffFunc CgbOscOff;
  MidiKeyToCgbFreqFunc MidiKeyToCgbFreq;
  MPlayFunc* MPlayJumpTable;
  PlyNoteFunc plynote;
  ExtVolPitFunc ExtVolPit;
  u8 gap2[16];
  struct SoundChannel chans[12];
  s8 pcmBuffer[792 * 2];
};
struct SongHeader {
  u8 trackCount;
  u8 blockCount;
  u8 priority;
  u8 reverb;
  struct ToneData* tone;
  u8* part[1];
};
struct MusicPlayerTrack {
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
  struct SoundChannel* chan;
  struct ToneData tone;
  u8 gap[10];
  u16 unk_3A;
  u32 unk_3C;
  u8* cmdPtr;
  u8* patternStack[3];
};
struct MusicPlayerInfo {
  struct SongHeader* songHeader;
  u32 status;
  u8 trackCount;
  u8 priority;
  u8 cmd;
  u8 unk_B;
  u32 clock;
  u8 gap[8];
  u8* memAccArea;
  u16 tempoD;
  u16 tempoU;
  u16 tempoI;
  u16 tempoC;
  u16 fadeOI;
  u16 fadeOC;
  u16 fadeOV;
  struct MusicPlayerTrack* tracks;
  struct ToneData* tone;
  u32 ident;
  MPlayMainFunc MPlayMainNext;
  struct MusicPlayerInfo* musicPlayerNext;
};
struct MusicPlayer {
  struct MusicPlayerInfo* info;
  struct MusicPlayerTrack* track;
  u8 unk_8;
  u16 unk_A;
};
struct Song {
  struct SongHeader* header;
  u16 ms;
  u16 me;
};
extern const struct MusicPlayer gMPlayTable[];
extern const struct Song gSongTable[];
extern u8 gMPlayMemAccArea[];
extern char SoundMainRAM[];
extern MPlayFunc gMPlayJumpTable[];
typedef void (*XcmdFunc)(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
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
void TrackStop(struct MusicPlayerInfo* mplayInfo, struct MusicPlayerTrack* track);
void MPlayMain(struct MusicPlayerInfo*);
void RealClearChain(void* x);
void MPlayContinue(struct MusicPlayerInfo* mplayInfo);
void MPlayStart(struct MusicPlayerInfo* mplayInfo, struct SongHeader* songHeader);
void m4aMPlayStop(struct MusicPlayerInfo* mplayInfo);
void FadeOutBody(struct MusicPlayerInfo* mplayInfo);
void TrkVolPitSet(struct MusicPlayerInfo* mplayInfo, struct MusicPlayerTrack* track);
void MPlayFadeOut(struct MusicPlayerInfo* mplayInfo, u16 speed);
void ClearChain(void* x);
void Clear64byte(void* addr);
void SoundInit(struct SoundInfo* soundInfo);
void MPlayExtender(struct CgbChannel* cgbChans);
void m4aSoundMode(u32 mode);
void MPlayOpen(struct MusicPlayerInfo* mplayInfo, struct MusicPlayerTrack* track, u8 a3);
void CgbSound(void);
void CgbOscOff(u8);
void CgbModVol(struct CgbChannel* chan);
u32 MidiKeyToCgbFreq(u8, u8, u8);
void DummyFunc(void);
void MPlayJumpTableCopy(MPlayFunc* mplayJumpTable);
void SampleFreqSet(u32 freq);
void m4aSoundVSyncOn(void);
void m4aSoundVSyncOff(void);
void m4aMPlayTempoControl(struct MusicPlayerInfo* mplayInfo, u16 tempo);
void m4aMPlayVolumeControl(struct MusicPlayerInfo* mplayInfo, u16 trackBits, u16 volume);
void m4aMPlayPitchControl(struct MusicPlayerInfo* mplayInfo, u16 trackBits, s16 pitch);
void m4aMPlayPanpotControl(struct MusicPlayerInfo* mplayInfo, u16 trackBits, s8 pan);
void ClearModM(struct MusicPlayerTrack* track);
void m4aMPlayModDepthSet(struct MusicPlayerInfo* mplayInfo, u16 trackBits, u8 modDepth);
void m4aMPlayLFOSpeedSet(struct MusicPlayerInfo* mplayInfo, u16 trackBits, u8 lfoSpeed);
void ply_fine(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_goto(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_patt(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_pend(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_rept(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_memacc(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_prio(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_tempo(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_keysh(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_voice(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_vol(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_pan(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_bend(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_bendr(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_lfos(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_lfodl(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_mod(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_modt(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_tune(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_port(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xcmd(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_endtie(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_note(u32 note_cmd, struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xxx(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xwave(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xtype(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xatta(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xdeca(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xsust(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xrele(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xiecv(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xiecl(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xleng(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
void ply_xswee(struct MusicPlayerInfo*, struct MusicPlayerTrack*);
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
extern char gNumSongs[];
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
struct ChildreProps {
  struct Entity* unk_b4;
  u32 unk_b8;
  struct Coord unk_bc;
  u8 unk_c4;
  u8 unk_c5;
  bool8 shouldTurnRight;
  u8 unk_c7;
  struct Coord unk_c8;
  u8 unk_d0[20];
};
struct DeathtanzProps {
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
struct GlacierleProps {
  u32 unk_b4;
  struct VFX* unk_b8;
  s32 unk_bc;
  u8 unk_c0;
  u8 unk_c1;
  bool8 shouldRightDir;
  u8 unk_c3[5];
  struct Coord unk_c8;
  u8 unk_d0[20];
};
struct OmegaWhiteProps {
  u8 unk_b4[4];
  s32 unk_y;
  struct Entity* unk_bc;
  u16 unk_c0;
  u8 unk_c2[18];
  u32 unk_d4;
  u8 unk_d8[12];
};
struct CopyXProps {
  u8 unk_b4[16];
  u8 unk_c4;
  u8 unk_c5;
  u8 unk_c6[22];
  u8 unk_dc;
  s8 unk_dd;
  u8 unk_de[6];
};
struct HellbatProps {
  u8 unk_b4[32];
  s32 unk_d4;
  u8 unk_d8[12];
};
struct PAquaModProps {
  u8 unk_b4[6];
  u16 x;
  s32 y;
  u8 unk_c0[36];
};
struct Boss {
  struct Entity s; struct Body body;;
  union {
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
typedef void (*BossFunc)(struct Boss*);
struct Elf {
  struct Entity s; struct Body body;;
  u8 buffer[16];
};
typedef void (*ElfFunc)(struct Elf*);
struct Enemy {
  struct Entity s; struct Body body;;
  u8 props[16];
};
typedef void (*EnemyFunc)(struct Enemy*);
struct KeyState {
  KEY_INPUT input;
  KEY_INPUT last;
  KEY_INPUT pressed;
  KEY_INPUT field3_0x6;
  bool16 firstRead;
  u8 __attribute__((aligned(2))) unk_0a[10];
  u8 field6_0x14;
  u8 field7_0x15;
  u8 field8_0x16;
  u8 field9_0x17;
};
extern struct KeyState gJoypad[2];
void PollKeyInput(void);
enum MenuZeroColor {
  MZC_NORMAL,
  MZC_HARD,
  MZC_ULTIMATE,
};
enum {
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
  ZERO_CYBER = 11,
};
struct ZeroAsset {
  u8 satelites[2];
  u16 unused;
  u16 fusions;
  u16 EC;
  u8 subtankHP[4];
};
struct KeyMap {
  KEY_INPUT jump;
  KEY_INPUT dash;
  KEY_INPUT main;
  KEY_INPUT sub;
};
struct KeyConfig {
  struct KeyMap keys;
  u8 btnMode;
  u8 attackMode;
  u8 unk_a;
  u8 _;
};
struct ZeroStatus {
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
struct Zero_b4 {
  struct ZeroStatus status;
  weapon_t mainCopy;
  weapon_t subCopy;
  u16 unk_e6;
  u8 prevMode;
  u8 prevPhase;
  u8 __attribute__((aligned(4))) attackMode[4];
  u8 __attribute__((aligned(4))) unused_f0[4];
  struct Entity* shadow;
  u8 wallDustTimer;
  SoundID __attribute__((aligned(2))) sound;
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
struct Zero {
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
  struct __attribute__((packed, aligned(1))) {
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
  u8 __attribute__((aligned(1))) unk_12f[2];
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
  u8 __attribute__((aligned(1))) unk_13c[2];
  motion_t prevMotion;
  u8 motionCmdIdx;
  u8 motionDuration;
  bool8 poseFixed;
  union {
    u8 raw;
    u8 lo : 4;
    u8 hi : 4;
  } __attribute__((aligned(1))) __attribute__((packed)) unk_143;
  u8 __attribute__((aligned(1))) unk_144[3];
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
  struct PlayerInputState {
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
  union {
    u8 raw[16];
    struct {
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
    struct {
      u8 element;
      u8 life;
      u8 unk_27e;
      u8 unk_27f;
      struct Entity* unk_280[3];
    } copyx;
    struct {
      s32 x;
      struct Enemy* enemy;
      u8 unk_8;
      u8 unk_9;
      u8 unk_a;
      u8 unk_b;
      s32 y;
    } harpuia;
    struct {
      s32 x;
      u8 unk_4[12];
    } leviathan;
  } mg;
};
extern char assertion[(sizeof(struct Zero) == 652) ? 1 : -1];
typedef void (*ZeroFunc)(struct Zero*);
struct Projectile {
  struct Entity s;
  struct Body body;
  u8 work[4];
  struct Coord prevCoord;
  u32 unk_c0;
};
typedef void (*ProjectileFunc)(struct Projectile*);
struct Solid {
  struct Entity s;
  struct Body body;
  union {
    u8 raw[16];
  } props;
};
typedef void (*SolidFunc)(struct Solid*);
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
  u8 unk_0[4];
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
};
struct Weapon;
struct WeaponProps {
  struct Zero* z;
  u8 props[2][8];
  u8 unk_c8[36];
};
struct Rod_b4 {
  struct Zero* z;
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
struct Buster_b4 {
  struct Zero* z;
  struct Coord c;
  u8 unk_c0;
  u8 element;
  u8 unk_c2;
  u8 unk_c3;
  u8 unk_c4[40];
};
struct Saber_b4 {
  struct Zero* z;
  u8 props[8];
  u8 element;
  u8 atk;
  u8 nature;
  bool8 unk;
  u8 unk_c4[40];
};
struct SaberWave_b4 {
  struct Weapon* saber;
  struct Zero* z;
  u8 props[4];
  u8 element;
  u8 atk;
  u8 flags;
  bool8 unk;
  u8 unk_c4[40];
};
struct Weapon {
  struct Entity s; struct Body body;;
  union {
    u8 raw[56];
    struct WeaponProps common;
    struct Buster_b4 buster;
    struct Saber_b4 saber;
    struct SaberWave_b4 wave;
    struct Rod_b4 rod;
  } props;
};
typedef void (*WeaponFunc)(struct Weapon*);
struct Entity;
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
void InitEntityHeader(struct EntityHeader* h, s8 kind, struct Entity* arr, s16 size, s16 count);
typedef struct RenderNode {
  struct RenderNode* next;
  void (*fn)(struct RenderNode*, struct DrawPivot*);
} RenderNode;
typedef struct Renderer {
  struct RenderNode* buffer[128];
  struct RenderNode* (*tasks)[128];
  struct Pivot* pivot;
  void* _;
} Renderer;
void Renderer_Init(struct Renderer* r);
void Renderer_SetPivot(struct Renderer* r, struct Pivot* pivot);
void Renderer_PrependTask(struct Renderer* r, struct RenderNode* task);
void Renderer_SendTask(struct Renderer* r, struct RenderNode* task, s16 prio, s16 x);
void Renderer_Clear(struct Renderer* r);
void Renderer_Flush(struct Renderer* r);
void SetTaskCallback(struct RenderNode* t, void* cb);
extern struct EntityHeader* pCurEntityHeader;
extern struct EntityHeader* gZeroHeaderPtr;
extern struct EntityHeader* gWeaponHeaderPtr;
extern struct EntityHeader* gBossHeaderPtr;
extern struct EntityHeader* gSolidHeaderPtr;
extern struct EntityHeader* gVFXHeaderPtr;
extern struct EntityHeader* gProjectileHeaderPtr;
extern struct EntityHeader* gEnemyHeaderPtr;
extern struct EntityHeader* gElfHeaderPtr;
extern struct Zero gZero;
extern struct Weapon gWeapons[24];
extern struct Boss gBosses[5];
extern struct Enemy gEnemies[18];
extern struct Projectile gProjectiles[24];
extern struct VFX gVFXs[64];
extern struct Solid gSolids[22];
extern struct Elf gElfEntities[16];
extern u8 gEntityIDGenerator;
void setCurProcessedEntityHeader(struct EntityHeader* h);
struct Entity* AllocEntityLast(struct EntityHeader* h);
struct Entity* AllocEntityFirst(struct EntityHeader* h);
void DeleteEntity(struct Entity* p);
void DeleteEntityEx(struct EntityHeader* h, struct Entity* z);
void UpdateEntities(struct EntityHeader* h);
void UpdateHazardEntities(struct EntityHeader* h);
void ignoreEntityFn(struct EntityHeader* h);
void RunDamageEffect(struct EntityHeader* h);
void RegisterHitboxes(struct EntityHeader* h);
void DrawEntity(struct EntityHeader* h, struct Renderer* r1);
void DrawCollidableEntity(struct EntityHeader* h, struct Renderer* r1);
struct Entity* GetNearestEntity(struct EntityHeader* h, struct Coord* c);
void InitNonAffineMotion(struct Entity* e);
void InitRotatableMotion(struct Entity* e);
u16 countSpecificEntities1(struct EntityHeader* h, u8 id);
u16 countSpecificEntities2(struct EntityHeader* h, u8 id, u8 r2, u8 r3);
void UpdateStageEntities(struct Coord* viewport);
void InitNonAffineSprite(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);
void InitRotatableSprite(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);
void InitScalerotSprite1(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);
void InitScalerotSprite2(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);
void RotateSprite(struct Sprite* s, s32 angle);
void ScalerotSprite(struct Sprite* s, s32 angle);
void UpdateEntityPaletteID(struct Entity* p);
void PaintEntityWhite(struct Entity* p);
void FUN_0801779c(struct Entity* p);
bool32 isKilled(struct Entity* p);
struct Collision;
typedef BossFunc BossRoutine[5];
extern const BossRoutine* const gBossFnTable[25];
void DeleteBoss(struct Boss* p);
void ResetBossBody(struct Boss* p, const struct Collision* collisions, s16 hp);
struct Renderer;
struct Camera;
typedef void (*CameraFunc)(struct Camera*);
struct CameraTemplate {
  u8 mode;
  u8 chaseMode;
  u8 unk_02;
  u8 unk_03;
  struct Coord camera;
  struct Coord forceScrollSpeed;
  s16 unk_left;
  s16 unk_right;
  s16 unk_top;
  s16 unk_bottom;
  s32 left;
  s32 right;
  s32 top;
  s32 bottom;
};
struct Camera {
  struct Pivot pivot;
  const struct CameraTemplate* template;
  struct Renderer* rendererMain;
  CameraFunc callback;
  s8 mode;
  u8 chaseMode;
  s16 unk_1a;
  bool8 isCallbackOnce;
  u16 __attribute__((aligned(4))) unk_20;
  s16 unk_22;
  u8 unk_24[4];
  struct Coord base;
  struct Coord target;
  struct Coord viewport;
  struct Coord forceScrollSpeed;
  struct Coord* zero;
  s32 unk_left;
  s32 unk_right;
  s32 unk_top;
  s32 unk_bottom;
  s32 left;
  s32 right;
  s32 top;
  s32 bottom;
};
void Camera_Update(struct Camera* p);
void Camera_Render(struct Camera* p);
void Camera_Shake(struct Camera* p);
void Camera_Reset(struct Camera* camera, const struct CameraTemplate* template, struct Renderer* tm);
typedef metatile_id_t Screen[15 * 10];
struct ChunkMap {
  u8 realWidth;
  u8 skip;
  u8 width;
  u8 height;
};
enum CollisionAtkType {
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
  ATK_NONE = 0xFF,
};
enum HitboxKind {
  DDP,
  DRP,
  DRP2,
};
enum CollisionFaction {
  FACTION_ALLY,
  FACTION_ENEMY,
  FACTION_NEUTRAL,
};
struct Collision {
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
struct Hitbox {
  struct Hitbox* next;
  struct Collision* collisions;
  struct Body* body;
  struct Coord c;
  u16 w;
  u16 h;
};
struct CollisionManager {
  u8 disabled;
  u8 sweep;
  u8 hitstop;
  u8 length;
  struct Hitbox buf[64];
  struct Hitbox* list[3][3];
  struct Body* talkTo;
  struct Body* door;
  struct Body* teleportal;
  u8 _[12];
};
extern struct CollisionManager gCollisionManager;
void ResetCollisionManager(void);
void ClearAllHitboxes(void);
void SetDDP(struct Body*, const struct Collision*);
u16 CalcDamage(struct Body* a, struct Body* d);
void CheckCollision(void);
void ResisterNonAffineHitbox(struct Body* body);
void RegisterFlipableHitbox(struct Body* p, u8 flip);
void RegisterScalerotHitbox(struct Body* o, u32 r1, u32 r2);
void InitWeaponBody(struct Body* o, const struct Collision* hitbox, s16 atk, s16 elementID, s16 r4, s16 r5);
void InitBody(struct Body* p, const struct Collision* hitbox, struct Coord* coord, s16 hp);
u16 CalcPutitedSpikeDamage(struct Body* body, u8 damage);
extern u8 (*gUnlockedElfPtr)[74];
typedef ElfFunc ElfRoutine[5];
extern const ElfRoutine* const gElfFnTable[13];
struct ElfBreedInfo {
  u8 unk_0;
  u8 unk_1;
  u8 unk_2;
  u8 unk_3;
};
extern const struct ElfBreedInfo gElfBreedInfo[74];
void DeleteElf(struct Elf* p);
void clearUnlockedCyberElfData(u8* p);
void clearUnlockedCyberElfDataHard(u8* p);
void unlockAllElvesForUltimate(u8* p);
void CreateSateliteElf(struct Zero* z, cyberelf_t id, bool8 isSatelite2);
motion_t GetElfMotion(u8 category);
struct Entity* CreateElf0(struct Zero* z, u8 breed, u8 availability, u8 _);
struct Elf* CreateNurseBElf(struct Zero* z, u8 r1, u8 r2, u8 isSatelite2);
struct Elf* CreateElf3(struct Entity* r0, void* r1);
struct Elf* CreateNurseEElf(struct Zero* z, u8 r1, u8 r2, u8 isSatelite2);
struct Elf* CreateFollowerElf(struct Zero* z, u8 breed, u8 availability, bool8 isSatelite1);
struct Elf* CreateSeaotterElf(struct Zero* z, u8 breed, u8 availability, u8 _);
struct Elf* CreateBirdElf(struct Zero* z, u8 r1, u8 r2, u8 isSatelite2);
void clearSecretDiskData(u8* flagbits);
void clearSecretDiskDataHard(u8* flagbits);
void unlockAllSecretDisk(u8* flagbits);
struct VFX;
struct Entity;
struct Coord;
struct UnkElement {
  u8 unk_0;
  u8 unk_1;
  u8 unk_2;
};
extern struct UnkElement wElement;
void setWramElement(u8 elementID);
struct VFX* ApplyElementEffect(u8 idx, struct Entity* p, const struct Coord* c);
typedef EnemyFunc EnemyRoutine[5];
extern const EnemyRoutine* const gEnemyFnTable[(72 + 1)];
void DeleteEnemy(struct Entity* p);
bool32 IsFrozen(struct Entity* p);
struct BgOfs {
  u16 x;
  u16 y;
};
struct WramVideoRegister {
  u16 dispcnt;
  struct BgCnt __attribute__((aligned(4))) bgcnt[4];
  u16 bgofs[4][2];
};
struct WramBlendRegister {
  u16 bldclt;
  u16 bldalpha;
  u16 bldy;
  u16 _;
};
union WindowRegister {
  u32 word;
  u16 half[2];
};
struct WramWindowRegister {
  u16 dispcnt;
  u16 _;
  union WindowRegister winH;
  union WindowRegister winV;
  u8 winin[4];
};
extern struct WramVideoRegister gVideoRegBuffer;
extern struct WramBlendRegister gBlendRegBuffer;
extern struct WramWindowRegister gWindowRegBuffer;
extern u16 wMOSAIC;
void ResetVideoRegister(void);
void FlushVideoRegister(void);
void LoadBgMap(u8 bg16, const u32* tbl, u8 idx, s8 x, s8 y);
void loadBgMap_08004248(u16* dst, const u32* tbl, u8 idx, s8 x8, s8 y8);
void ResetOAM(void);
void FlushOAM(void);
void ClearBLDCLT_1(void);
void FlushBlendRegister(void);
void ResetWindow(void);
void FlushWinRegister(void);
void ClearMOSAIC(void);
void FlushMOSAIC(void);
struct GraphicTransfer {
  u32 type : 2;
  u32 bytesize : 30;
  void* dst;
  void* src;
};
struct GraphicTransferManager {
  s32 len;
  struct GraphicTransfer tasks[16];
  struct BG0Manager {
    u32 bytesize;
    void* buffer;
    u32 dst;
    u32 backdrop;
  } bg0;
};
struct PaletteManager {
  struct PlttData buf[512];
  u8 filter[3];
  u16 unk_404;
  u16 unk_406;
  void (*post_process)(void);
};
struct OamManager {
  struct OamData buf[128];
  struct OamData* p;
  u32 dispcnt;
};
struct GraphicV2 {
  u32 src;
  u32 size : 22;
  u32 tileId : 10;
  u16 rowsize;
  u16 map2d : 1;
  u16 lz77 : 1;
  u16 no_pal : 1;
  u16 tilesize : 8;
  u16 prop_b11 : 1;
  u16 rlu : 1;
  u16 prop_b13 : 3;
};
struct Graphic {
  s32 src;
  u32 size : 22;
  u32 ofs : 10;
  u16 chunkSize;
  u16 props;
};
struct Palette {
  u32 src;
  u16 size;
  bool8 lz77;
  u8 dst;
};
struct ColorGraphic {
  struct Graphic g;
  struct Palette pal;
};
extern struct GraphicTransferManager gGraphicTransferManager;
extern struct PaletteManager gPaletteManager;
extern struct OamManager gOamManager;
extern u16 wStaticMotionPalIDs[254 + 2];
extern u16 wStaticGraphicTilenums[254 + 2];
extern const struct ColorGraphic gStaticMotionGraphics[254];
extern const struct Graphic gGraphic_Capcom;
extern const struct Palette gPalette_Capcom;
extern const u32 gBgMapOffsets[134];
extern const u32 gStageTilesetOffsets[19];
extern const struct ColorGraphic gMiscTilesetGraphics[177];
void LoadGraphic(const struct GraphicV2* g, void* dst);
void LoadPalette(const struct Palette* p, u32 r1);
s32 RequestGraphicTransfer(const struct Graphic* g, void* dst);
s32 RequestBgMapTransfer(u16* src, void* dst, s32 bytesize);
void EnableBG0(u32* buffer, u32 dst, u32 bytesize, u16 backdrop);
void DisableBG0(void);
struct Elf;
struct Widget;
struct Zero;
struct GameState;
typedef void (*MenuLoopFunc)(struct GameState*);
typedef struct Elf* (*MenuElfFunc)(struct Zero*, u8, u8, u8);
struct ExSkillMenuState {
  struct Widget* w;
  u8 selected;
  bool8 inactive;
  u16 _;
};
struct KeyConfigMenuState {
  u8 y;
  u8 blinkID;
  u16 _;
};
struct ElfMenuState {
  cyberelf_t displayed[6];
  u8 y;
  u8 mode;
  u8 tab;
  u8 cursor;
  u8 unk_a;
  u8 unk_b;
  u8 blinkID;
  u8 unk_d;
  u8 unk_e;
  u8 unk_f;
};
struct MenuState {
  u8 unk_00[4];
  u16 frame;
  u16 unk_06;
  u16 unk_08;
  u8 unk_0a;
  u8 unk_0b;
  u8 unk_0c;
  u8 unk_0d;
  u8 unk_0e;
  u8 unk_0f;
  u32 rank;
  struct Widget* mc_14;
  struct Widget* mc_18;
  u8 unk_1c[8];
  struct ExSkillMenuState exskill;
  struct KeyConfigMenuState kc;
  struct ElfMenuState elf;
  u8 unk_40[8];
  cyberelf_t satelites[2];
  u8 unk_4a;
  u8 unk_4b;
  u8 unk_4c;
  u8 unk_4d;
  u8 unk_4e[178];
};
void MainLoop_Menu(struct GameState* p);
bool8 TrySlideMenu(struct GameState* g);
struct BgMapHeader;
void CopyBgMap(u16* dst, struct BgMapHeader* src, u8 x, u8 y);
struct MinigameState {
  u8 unk_00[4];
  s16 unk_04;
  s16 unk_06;
  s32 unk_08;
  u8 unk_0c;
  u8 unk_0d;
  u8 unk_0e;
  u8 unk_0f;
  u8 unk_10[4];
  s32 unk_14;
  u16 unk_18;
  u8 unk_1a;
  u8 unk_1b;
  u8 unk_1c[4];
  s32 unk_20;
  s32 unk_24;
  s32 unk_28;
  s32 unk_2c;
  u8 unk_30[4];
  s32 unk_34;
  u8 unk_38[4];
  s32 unk_3c;
  u8 unk_40[144];
  u8 unk_d0[4];
  u8 unk_d4;
  u8 unk_d5;
  u8 unk_d6;
  u8 unk_d7;
  u8 unk_d8[8];
  u8 unk_e0[32];
};
extern char assertion[(sizeof(struct MinigameState) == 256) ? 1 : -1];
struct GameState;
typedef bool32 (*MinigameFunc)(struct GameState*);
void PrintMinigameNumber(s32 score, u16 x, u16 y);
typedef u16 MetatileMap[2 + 89100 + 2];
struct LayerGraphic {
  struct Coord c;
  u16 bgofs[2];
  Metatile* tiledata;
  Screen* chunks;
  const struct ChunkMap* map;
};
struct BgOfs;
void UpdateBGOFS(struct LayerGraphic* p, struct BgOfs* bgofs);
void FUN_08006bb4(struct LayerGraphic* l, struct Coord* c, u32* bgmap, MetatileMap* mm);
void FUN_08006a10(struct LayerGraphic* l, struct Coord* c, u32* bgmap, MetatileMap* mm);
void FUN_08006ae0(struct LayerGraphic* l, struct Coord* c, u32* bgmap, u16* tilemap);
void FUN_080050b0(struct LayerGraphic* l, struct Coord* c, u32 mapAddr);
void FUN_08005a70(struct LayerGraphic* l, struct Coord* c, u32 mapAddr);
void ResetLayerGraphic(struct LayerGraphic* p, struct Coord* c, u16* _, Metatile* tiledata, Screen* chunks, const struct ChunkMap* map);
enum LayerRoutine {
  LAYER_UPDATE,
  LAYER_DRAW,
  LAYER_EXIT,
};
struct StageLayer;
struct Stage;
typedef void (*StageBgFunc)(struct StageLayer*, const struct Stage*);
typedef StageBgFunc StageLayerRoutine[3];
struct StageLayer {
  StageLayerRoutine fn;
  u16 type;
  u8 phase;
  u8 unk_0f;
  u16 unk_10;
  u16 unk_12;
  struct LayerGraphic gfx;
  struct Coord drawPivotOffset;
  struct Coord viewportCenterPixel;
  struct Coord prevViewportCenterPixel;
  struct Coord scrollPower;
  struct Coord scroll;
  struct Coord scrollCopy;
  u32 bgIdx;
  u32 prio;
  u32 screenBase;
  union {
    u8 raw[32];
    struct {
      u8 frameCounter;
      u8 _[3];
      u8 unk_6c[28];
    } resistanceBase;
    struct {
      u32 frameCounter;
      u8 unk_6c[28];
    } spacecraft;
    struct {
      u8 frameCounter;
      u8 _[3];
      u8 unk_6c[28];
    } ocean;
    struct {
      s32 eruptionX[3];
      u8 unk_74[20];
    } volcano;
    struct {
      s32 scrollTimer;
      struct Coord c;
      u8 unk_74[20];
    } missile;
  } work;
};
void DrawGeneralStageLayer(struct StageLayer* p, const struct Stage* _);
typedef void (*StageFunc)(struct Coord*);
struct TerrainHeader {
  s32 tiles;
  s32 attrs;
  s32 screens;
};
struct Stage {
  u32 id;
  const StageFunc* fn;
  const struct TerrainHeader* terrainHdr;
  const struct ChunkMap* maps[3];
  u32 bgIdx[3];
  u32 prio[3];
  u32 screenBase[3];
  struct Coord scrollPower[3];
  struct Coord scroll[3];
  const tileset_ofs_t* tilesetOffset;
  const StageLayerRoutine* bgFns;
  const u16* behavior;
  s32 conveyor[2];
};
extern const struct Stage gStage0Landscape;
extern const struct Stage gSpacecraftLandscape;
extern const struct Stage gVolcanoLandscape;
extern const struct Stage gOceanLandscape;
extern const struct Stage gRepairFactoryLandscape;
extern const struct Stage gOldResidentialLandscape;
extern const struct Stage gResistanceBaseLandscape;
extern const struct Stage gMissileFactoryLandscape;
extern const struct Stage gTwilightDesertLandscape;
extern const struct Stage gAnatreForestLandscape;
extern const struct Stage gFrostlineIceBaseLandscape;
extern const struct Stage gAreaX2Landscape;
extern const struct Stage gEnergyFacilityLandscape;
extern const struct Stage gSnowyPlainsLandscape;
extern const struct Stage gSunkenLibraryLandscape;
extern const struct Stage gGiantElevatorLandscape;
extern const struct Stage gSubArcadiaLandscape;
extern const struct Stage gWeilLaboLandscape;
typedef SolidFunc SolidRoutine[5];
extern const SolidRoutine* const gSolidFnTable[56];
void DeleteSolid(Object* p);
u16 FUN_080d0934(struct Entity* p, motion_t m, u8 r2);
void FUN_080cb4c0(struct Solid* p);
struct Solid* CreateLeafBurn(u8 r0);
struct Solid* CreateResistanceBaseElevator(u8 floor);
void CreateLavaRiverPlatform(u32 x, u32 y);
struct Solid;
struct AnatreForestState {
  struct Solid* leaf;
  u8 unk_004;
  struct Solid* unk_008;
  u8 unk_00c;
  u8 unk_00d;
  u16 unk_00e;
  u8 unk_010[248];
};
extern char assertion[(sizeof(struct AnatreForestState) == 264) ? 1 : -1];
struct AreaX2State {
  u16 unk_000;
  u16 unk_002;
  u8 unk_004[2];
  u8 unk_006[2];
  u16 unk_008;
  u8 unk_00a[254];
};
extern char assertion[(sizeof(struct AreaX2State) == 264) ? 1 : -1];
struct EnergyFacilityState {
  u8 unk_000[4];
  s32 unk_004;
  s32 unk_008;
  u8 unk_00c[2];
  u16 unk_00e;
  u8 unk_010[2];
  u8 unk_012[2];
  u16 unk_014;
  u16 unk_016;
  u8 unk_018[240];
};
extern char assertion[(sizeof(struct EnergyFacilityState) == 264) ? 1 : -1];
struct Solid;
struct FrostlineIceBaseState {
  u16 unk_000;
  u8 unk_002[262];
};
extern char assertion[(sizeof(struct FrostlineIceBaseState) == 264) ? 1 : -1];
struct GiantElevatorState {
  u8 unk_000[4];
  u16 unk_004;
  u16 unk_006;
  u8 unk_008[256];
};
extern char assertion[(sizeof(struct GiantElevatorState) == 264) ? 1 : -1];
struct MissileFactoryState {
  u8 unk_000;
  u8 unk_001;
  s8 unk_002;
  u8 unk_003;
  u16 unk_004;
  u16 unk_006;
  u8 unk_008;
  u8 unk_009;
  u8 unk_00a;
  u8 unk_00b;
  u32 unk_00c;
  u32 unk_010;
  struct Coord unk_014;
  u8 unk_01c[236];
};
extern char assertion[(sizeof(struct MissileFactoryState) == 264) ? 1 : -1];
struct Solid;
struct OceanState {
  u8 unk_000;
  u8 unk_001;
  s8 unk_002;
  u8 unk_003;
  struct Solid* btns[4];
  u8 unk_014[244];
};
extern char assertion[(sizeof(struct OceanState) == 264) ? 1 : -1];
struct Solid;
struct OldResidentialState {
  struct Solid* leaf;
  u8 unk_004[4];
  u16 unk_008;
  u16 unk_00a;
  u16 unk_00c;
  u16 unk_00e;
  u16 unk_010;
  u16 unk_012;
  u8 unk_014[244];
};
extern char assertion[(sizeof(struct OldResidentialState) == 264) ? 1 : -1];
struct RepairFactoryState {
  u8 unk_000;
  s8 unk_001;
  u8 unk_002;
  u8 unk_003;
  u8 unk_004[260];
};
extern char assertion[(sizeof(struct RepairFactoryState) == 264) ? 1 : -1];
struct ResistanceBaseState {
  u8 unk_000;
  u8 weather;
  u8 unk_002;
  u8 unk_003;
  u8 unk_004[260];
};
extern char assertion[(sizeof(struct ResistanceBaseState) == 264) ? 1 : -1];
struct Boss;
struct SpaceCraftState {
  struct Boss* omega;
  struct Coord omegaCoord;
  u8 unk_00c[2];
  u16 unk_00e;
  u8 unk_010[248];
};
extern char assertion[(sizeof(struct SpaceCraftState) == 264) ? 1 : -1];
struct SubArcadiaState {
  u8 unk_000;
  u8 unk_001;
  u8 unk_002;
  u8 unk_003;
  u8 unk_004[260];
};
extern char assertion[(sizeof(struct SubArcadiaState) == 264) ? 1 : -1];
struct SunkenLibraryState {
  u8 unk_000;
  u8 unk_001;
  u8 unk_002;
  u8 unk_003;
  u32 rng;
  u16 unk_008;
  u16 theta;
  u16 unk_00c;
  u8 unk_00e[250];
};
extern char assertion[(sizeof(struct SunkenLibraryState) == 264) ? 1 : -1];
struct TwilightDesertState {
  u8 unk_000;
  u8 unk_001;
  u8 unk_002;
  u8 unk_003;
  u8 unk_004;
  u8 unk_005;
  u8 unk_006[258];
};
extern char assertion[(sizeof(struct TwilightDesertState) == 264) ? 1 : -1];
struct Solid;
struct VolcanoState {
  u8 unk_000;
  u8 unk_001;
  u8 unk_002;
  u8 unk_003;
  u16 unk_004;
  u16 unk_006;
  struct Solid* coffins[2];
  u8 unk_010[248];
};
extern char assertion[(sizeof(struct VolcanoState) == 264) ? 1 : -1];
struct WeilLaboState {
  u8 unk_000;
  u8 unk_001[3];
  u32 unk_004;
  u16 unk_008;
  u16 unk_00a;
  u32 unk_00c;
  struct Coord unk_010;
  u32 unk_018;
  u32 unk_01c;
  u32 unk_020;
  struct Coord unk_024;
  struct Coord unk_02c;
  u8 unk_34[212];
};
extern char assertion[(sizeof(struct WeilLaboState) == 264) ? 1 : -1];
struct TerrainROMPointer {
  metatile_attr_t* attrs;
  Metatile* tiles;
  Screen* screens;
  const struct ChunkMap* map;
};
struct Hazard {
  u16 id;
  metatile_attr_t attr;
  u16 w;
  u16 h;
  struct Coord start;
  struct Coord unk_10;
};
extern char assertion[(sizeof(struct Hazard) == 24) ? 1 : -1];
struct Terrain {
  struct TerrainROMPointer hdr;
  struct Coord viewport;
  u16 id;
  u8 objectLen;
  u8 objectLenPrev;
  struct Hazard objects[32];
  struct Hazard objectsPrev[32];
  tileset_t tilesets[2];
  u16 enabledBg;
  struct BgCnt savedBgCnt[3];
  MetatileMap tilemap;
  bool16 tilemap_duty;
  bool16 reload_graphic;
  s32 conveyor[2];
};
struct Overworld {
  struct RenderNode task;
  struct RenderNode* p;
  u8 unk_0c[20];
  struct StageLayer layer[3];
  struct Terrain terrain;
  s32 sea;
  s32 unused_2c010;
  struct Area32 range;
  u16 bgmap[2048];
  u8 state[4];
  union {
    u8 raw[264];
    struct SpaceCraftState spacecraft;
    struct VolcanoState volcano;
    struct OceanState ocean;
    struct RepairFactoryState repairFactory;
    struct OldResidentialState oldResidential;
    struct MissileFactoryState missileFactory;
    struct TwilightDesertState twilightDesert;
    struct AnatreForestState anatreForest;
    struct FrostlineIceBaseState iceBase;
    struct AreaX2State areaX2;
    struct EnergyFacilityState energyFacility;
    struct SunkenLibraryState sunkenLib;
    struct GiantElevatorState giantElevator;
    struct SubArcadiaState subArcadia;
    struct WeilLaboState weilLabo;
    struct ResistanceBaseState resistanceBase;
  } work;
};
extern struct Overworld gOverworld;
extern const u8 gScreenY[2048];
extern const u8 gScreenX[3072];
extern const struct TerrainHeader gStageTerrains[18];
void ResetLandscape(s32 stageID, struct Coord* c);
void UpdateStageLandscape(struct Coord* c);
void DrawOverworld(struct Renderer* p);
void SaveDispRegister(void);
void RestoreBackground(void);
void ExitStageLandscape(void);
bool8 IsVoidSpace(s32 x, s32 y);
void LoadScreenIntoMetatileMap(s32 screenX, s32 screenY, u16 screenID);
void AppendHazard(u16 id, u16 attr, const struct Coord* c, const struct Rect* size);
s32 isStageBlocking(s32 start, s32 x, s32 y);
struct Quake {
  u32 power;
  struct Coord c;
};
struct QuakeManager {
  u32 rng;
  struct Quake quakes[17];
  struct Quake unk_0d0[17];
  u16 length;
  u16 frame;
  s32 power;
  u16 unk_1a4;
  u16 unk_1a6;
};
extern struct QuakeManager gQuakeManager;
void ClearQuakeManager(void);
void AppendQuake(u8 power, struct Coord* c);
void CalcQuake(struct Coord* c, struct Coord* ofs);
s32 quake_0801acdc(struct Coord* _);
struct Command {
  u8 cmd;
  u8 status;
  s16 val2;
  u32 work;
};
struct Command0D {
  u8 cmd;
  u8 entityIdx;
  union {
    s16 idx;
    u8 mask;
    u8 pad;
  } __attribute__((packed)) val;
  u32 flags;
};
struct Command12 {
  u8 cmd;
  u8 idx;
  s16 x;
  u16 kind;
  s16 y;
};
struct ScriptEntity {
  struct Entity* entity;
  struct Entity* unk_04;
  u8 unk_08;
  u8 flags;
  u16 unk_0A[3];
};
union ScriptString {
  u32 raw;
  s16 n;
  u8 x;
  u8 y;
};
struct VM {
  u8 unk_000;
  u8 unk_001;
  bool8 active;
  u8 unk_003;
  u16 unk_004;
  u16 unk_006;
  struct Command* start;
  struct Command* pc;
  struct ScriptEntity entities[12];
  u32 time;
  u32 wait;
  struct Camera camera;
  u32 transition;
  KEY_INPUT forcedKey;
  u16 unk_14a;
  u16 emergency;
  u16 magnitude;
  union ScriptString string;
  struct VFX* indicator;
  SoundID32 bgm;
  TextID zeroDeathTextIDs[2];
  struct Coord forceCoord;
};
struct ScriptEntityTemplate {
  u8 kind;
  u8 variant;
  u8 work[2];
  struct Coord coord;
  s8 xflip;
  s8 yflip;
};
typedef bool32 (*CommandHandler)(struct VM*);
extern const CommandHandler gScriptCommands[38];
extern const struct Command Script_MissionFail[];
extern const struct Command Script_MissionFail2[];
extern const TextID CielGoodluckTextIDs[];
void RenderWipeZ(struct VM* vm);
void SetScript(struct VM* vm, const struct Command* script);
void CreateScriptEntity(u8 t, struct ScriptEntityTemplate* arg);
bool32 RunVM(struct VM* vm);
void ClearVM(struct VM* vm, u32 stageID);
void FUN_08021b88(struct VM* _);
void FUN_08021cb4(struct VM* vm, const struct Command* script, struct Entity* e);
void DeleteScriptEntity(u8 n);
typedef u32 (*AreaChecker)(struct Coord*);
struct EntityTemplate {
  u8 unk_00;
  u8 kind;
  u8 id;
  u8 work0;
  u8 work1;
  u8 unk_05;
  u8 unk_06;
  u8 unk_07;
};
struct EntityTemplateCoord {
  s32 x;
  s16 y;
  u16 idx;
};
struct PreloadEntity {
  motion_id_t id;
  u8 habitat;
  u16 tileBase;
  u8 palID;
  u8 unk_05;
  u8 unk_06;
  u8 unk_07;
};
struct StageEntity {
  struct StageEntity* next;
  struct Entity* e;
  s16 idx;
  u16 flag;
};
struct StageEntityManager {
  u32 entityEnabled[32];
  void* unk_080;
  struct StageEntity unk_084[32];
  struct StageEntity* list;
  struct StageEntity* free;
  bool16 isMissionDone;
  u16 unk_20e;
  u8 stageID;
  u8 area;
  u16 remaining;
  const struct EntityTemplate* template;
  const struct EntityTemplateCoord* templateCoord;
  s32 dynamicEntityRange[2];
  u16 start;
  u8 unk_226[4];
  u16 unk_22a;
  u32 _;
};
extern const struct EntityTemplate gStage0Entity[2];
extern const struct EntityTemplate gSpaceCraftEntity[26];
extern const struct EntityTemplate gVolcanoEntity[51];
extern const struct EntityTemplate gOceanEntity[31];
extern const struct EntityTemplate gRepairFactoryEntity[38];
extern const struct EntityTemplate gOldLifeSpaceEntity[37];
extern const struct EntityTemplate gMissileFactoryEntity[35];
extern const struct EntityTemplate gTwilightDesertEntity[31];
extern const struct EntityTemplate gAnatreForestEntity[34];
extern const struct EntityTemplate gIceBaseEntity[38];
extern const struct EntityTemplate gAreaX2Entity[36];
extern const struct EntityTemplate gEnergyFacilityEntity[51];
extern const struct EntityTemplate gSnowyPlainsEntity[27];
extern const struct EntityTemplate gSunkenLibraryEntity[37];
extern const struct EntityTemplate gGiantElevatorEntity[41];
extern const struct EntityTemplate gSubArcadiaEntity[36];
extern const struct EntityTemplate gWeilLaboEntity[50];
extern const struct EntityTemplate gResistanceBaseEntity[64];
extern const struct PreloadEntity sStage0StaticTemplate[1];
extern const struct PreloadEntity gSpaceCraftStatic[8];
extern const struct PreloadEntity gVolcanoStatic[20];
extern const struct PreloadEntity gOceanStatic[17];
extern const struct PreloadEntity gRepairFactoryStatic[13];
extern const struct PreloadEntity gOldLifeSpaceStatic[15];
extern const struct PreloadEntity gMissileFactoryStatic[14];
extern const struct PreloadEntity gTwilightDesertStatic[13];
extern const struct PreloadEntity gAnatreForestStatic[16];
extern const struct PreloadEntity gIceBaseStatic[18];
extern const struct PreloadEntity gAreaX2Static[13];
extern const struct PreloadEntity gEnergyFacilityStatic[16];
extern const struct PreloadEntity gSnowyPlainsStatic[13];
extern const struct PreloadEntity gSunkenLibraryStatic[12];
extern const struct PreloadEntity gGiantElevatorStatic[19];
extern const struct PreloadEntity gSubArcadiaStatic[14];
extern const struct PreloadEntity gWeilLaboStatic[13];
extern const struct PreloadEntity gResistanceBaseStatic[41];
extern const struct EntityTemplateCoord gStage0EntityCoord[2];
extern const struct EntityTemplateCoord gSpaceCraftEntityCoord[68];
extern const struct EntityTemplateCoord gVolcanoEntityCoord[69];
extern const struct EntityTemplateCoord gOceanEntityCoord[86];
extern const struct EntityTemplateCoord gRepairFactoryEntityCoord[73];
extern const struct EntityTemplateCoord gOldLifeSpaceEntityCoord[159];
extern const struct EntityTemplateCoord gMissileFactoryEntityCoord[82];
extern const struct EntityTemplateCoord gTwilightDesertEntityCoord[59];
extern const struct EntityTemplateCoord gAnatreForestEntityCoord[56];
extern const struct EntityTemplateCoord gIceBaseEntityCoord[107];
extern const struct EntityTemplateCoord gAreaX2EntityCoord[88];
extern const struct EntityTemplateCoord gEnergyFacilityEntityCoord[118];
extern const struct EntityTemplateCoord gSnowyPlainsEntityCoord[78];
extern const struct EntityTemplateCoord gSunkenLibraryEntityCoord[99];
extern const struct EntityTemplateCoord gGiantElevatorEntityCoord[65];
extern const struct EntityTemplateCoord gSubArcadiaEntityCoord[62];
extern const struct EntityTemplateCoord gWeilLaboEntityCoord[68];
extern const struct EntityTemplateCoord gResistanceBaseEntityCoord[241];
extern struct StageEntityManager gStageEntityManager;
extern const AreaChecker gAreaCheckers[18];
void InitStageEntityManager(u8 stageID, bool8 missionDone);
struct Entity* CreateStageEntity(u8 kind, u8 id);
void DeleteStageEntity(struct CollidableEntity* e);
void FUN_080186c8(u32 top, u32 bottom);
struct StageRun {
  u16 id;
  u8 checkpoint;
  u8 checkpointBuffer;
  KEY_INPUT input;
  KEY_INPUT unk_06;
  u16 missionStatus;
  u16 unk_0a;
  u32 frame;
  struct VM vm;
  struct Renderer* rendererMain;
  u8 stageEventPhase;
  u8 unk_17d;
  u16 searchDataFlags;
  u32 searchDataIdx;
  u32 remainingTimeFrame;
  u32 unk_188;
  u32 unk_18c;
  u32 volteelRNG;
};
struct StageDiskManager {
  u8* disk;
  u8 stageDiskIDs[10];
  u8 stageDiskCount;
  u8 _;
};
extern struct StageRun gStageRun;
extern struct StageDiskManager gStageDiskManager;
extern const struct Command** gStageScriptList[18];
typedef s16 (*StageRunFunc)(struct StageRun*);
void InitStageRun(u8 stageID);
void LoadStageRun(u8 stageID, u8 checkPoint);
void ClearStageRun(struct Renderer* tm);
bool32 OverworldUpdate(bool8 paused);
void CameraUpdate(bool8 paused);
void UpdateStoryFlag(void);
void setStageCheckpoint(u8 cp);
void setStageCheckpoint2(u8 cp);
void ApplyGiantElf(struct StageRun* p);
u32 CalcFromCamera(struct Camera* p, struct Coord* c);
void Camera_SetMode(struct Camera* p, u32 mode);
void LoadCameraTemplate(struct Camera* p, const struct CameraTemplate* t);
s16 Stage0_MissionUpdate(struct StageRun* p);
s16 SpaceCraft_MissionUpdate(struct StageRun* p);
s16 Volcano_MissionUpdate(struct StageRun* p);
s16 Ocean_MissionUpdate(struct StageRun* p);
s16 RepairFactory_MissionUpdate(struct StageRun* p);
s16 OldResidential_MissionUpdate(struct StageRun* p);
s16 MissileFactory_MissionUpdate(struct StageRun* p);
s16 TwilightDesert_MissionUpdate(struct StageRun* p);
s16 AnatreForest_MissionUpdate(struct StageRun* p);
s16 IceBase_MissionUpdate(struct StageRun* p);
s16 AreaX2_MissionUpdate(struct StageRun* p);
s16 EnergyFacility_MissionUpdate(struct StageRun* p);
s16 SnowyPlains_MissionUpdate(struct StageRun* p);
s16 SunkenLib_MissionUpdate(struct StageRun* p);
s16 GiantElevator_MissionUpdate(struct StageRun* p);
s16 SubArcadia_MissionUpdate(struct StageRun* p);
s16 WeilLabo_MissionUpdate(struct StageRun* p);
s16 ResistanceBase_Update(struct StageRun* p);
s16 SpaceCraft_FreeUpdate(struct StageRun* p);
s16 Volcano_FreeUpdate(struct StageRun* p);
s16 Ocean_FreeUpdate(struct StageRun* p);
s16 RepairFactory_FreeUpdate(struct StageRun* p);
s16 OldResidential_FreeUpdate(struct StageRun* p);
s16 MissileFactory_FreeUpdate(struct StageRun* p);
s16 TwilightDesert_FreeUpdate(struct StageRun* p);
s16 AnatreForest_FreeUpdate(struct StageRun* p);
s16 IceBase_FreeUpdate(struct StageRun* p);
s16 AreaX2_FreeUpdate(struct StageRun* p);
s16 EnergyFacility_FreeUpdate(struct StageRun* p);
s16 SnowyPlains_FreeUpdate(struct StageRun* p);
s16 SunkenLib_FreeUpdate(struct StageRun* p);
s16 GiantElevator_FreeUpdate(struct StageRun* p);
s16 SubArcadia_FreeUpdate(struct StageRun* p);
struct Widget;
struct ResultState {
  u8 mode[4];
  u16 frame;
  u16 unk_06;
  u16 unk_08;
  u16 unk_0a;
  u32 unk_0c;
  u32 rank;
  void* vfx;
  u8 codenamePrefix;
  u8 codenameSuffix;
  u16 unk_1a;
  u8 unk_1c[8];
  struct Widget* w;
  u8 unk_28[216];
};
void PrepareResultScreen(struct ResultState* p);
bool32 result_0802400c(struct ResultState* p);
struct PlayInfo {
  u8 extraLife;
  u8 rank;
  u8 codenameSuffix;
  u8 pad_03;
  u8 codenamePrefix;
  u8 pad_05;
  bool8 allElfCompleted;
  u8 collectFlag;
  u8 clearCodenameSuffix;
  u8 clearCodenamePrefix;
  s16 scoreSum;
  u32 playTime;
  u8 clearCount;
  u8 unusedClearCount;
  u8 unk_12;
  u8 lastStage;
  u32 missionDones;
  u32 unusedMissionDones;
  u32 unk_1c;
  u8 unk_20[20];
  u8 suffixIdx[8];
  u8 unk_3a[16];
  u8 fusionCount;
  u8 _[3];
};
struct Story {
  u16 id;
  u16 pad_02;
  u8 gameflags[8];
  u8 counts[29 + 41 + 2];
};
struct Story96 {
  struct Story s;
  u8 unk_54;
  u8 __attribute__((aligned(1))) _[11];
};
extern struct Story96 gCurStory;
void saveCurStory(struct Story* dst);
void resetCurStory(u8 stageID, struct Story* src);
void FUN_08019678(struct Story* p);
void ClearPlayInfo(struct PlayInfo* p);
struct SaveSlot {
  u16 lap;
  u16 gamemode;
  u16 stageID;
  u16 savedRank;
  u8 unk_010[8];
  u32 rng;
  struct Story story;
  struct Story savedStory;
  u8 __attribute__((aligned(4))) disk[45];
  u8 __attribute__((aligned(4))) savedDisk[45];
  u8 __attribute__((aligned(4))) elf[74];
  u8 __attribute__((aligned(4))) savedElf[74];
  struct PlayInfo playinfo;
  struct ZeroStatus status;
  struct ZeroAsset zeroAsset;
  u8 unused_240[16];
};
struct GameState {
  u8 mode[4];
  s16 frames;
  s16 unk_006;
  s16 unk_008[2];
  bool32 unk_00c;
  u32 bg0[512];
  struct EntityHeader entityHeaders[10];
  struct Renderer rendererMain;
  struct Renderer rendererUI;
  struct Pivot unk_0db8;
  struct Coord unk_0dc4;
  union {
    u8 raw[256];
    struct MenuState menu;
    struct ResultState result;
    struct MinigameState mg;
  } sceneState;
  struct Solid* sunkinLibCursor;
  u8 unk_0ed0[8];
  u16 menuBgMap1[1024];
  u16 menuBgMap2[1024];
  u32 unk_1ed8;
  bool16 inMenu;
  u16 unk_1ede;
  struct WramBlendRegister savedBlendRegister;
  struct WramWindowRegister savedWindowRegister;
  u8 unk_1ef8[352];
  u8 savedObjVRAM[16 * 1024];
  struct PlttData savedObjPal[256];
  u32 savedColor0;
  struct SaveSlot save;
  struct Zero* z2;
  struct Zero* z3;
  u8 _[12];
};
extern struct GameState gGameState;
extern u8 gUnkSineTableIdx;
extern u16 gCyberSpaceColorHashtable[96];
extern void* PTR_0202f384;
extern struct SaveSlot SaveState_020003a8;
void SetGameMode(struct GameState* p, u32 mode);
struct Pickup;
void InitBossHeader(struct EntityHeader* h, struct Boss* p, s16 len);
void InitWeaponHeader(struct EntityHeader* h, struct Weapon* w, s16 len);
void InitEnemyHeader(struct EntityHeader* h, struct Enemy* p, s16 len);
void InitProjectileHeader(struct EntityHeader* h, struct Projectile* p, s16 len);
void InitVFXHeader(struct EntityHeader* h, struct VFX* p, s16 len);
void InitSolidHeader(struct EntityHeader* h, struct Solid* p, s16 len);
void InitPickupHeader(struct EntityHeader* h, struct Pickup* p, s16 len);
void InitElfHeader(struct EntityHeader* h, struct Elf* p, s16 len);
void InitWidgetHeader(struct EntityHeader* h, struct Widget* p, s16 len);
void UpdateVFXs(void);
void UpdateProjectiles(void);
void MainLoop_Game(struct GameState* p);
void MainLoop_Disk(struct GameState* p);
void MainLoop_Minigame(struct GameState* p);
void RunOverworldLoop(struct GameState* g);
void OverworldLoop_ManageSaveData(struct GameState* g);
void OverworldLoop_CmdRoomTalk(struct GameState* g);
u16 handleWrapTwoChoice(struct GameState* g);
void DrawHUD(struct GameState* _);
void CheckItemGain(struct GameState* p);
typedef void (*GameLoopFunc)(struct GameState*);
struct HUD {
  u16* bg0;
  u16 unk_02;
  struct Zero* z;
  struct Entity* unk_0c;
  s32* timeLeft;
  u8 _[12];
};
extern struct HUD gHUD;
void ResetHUD(u16* bg0);
void DrawStatus(void);
void DrawLeftTime(void);
struct Process;
struct Intro {
  u8 unk_00[4];
  u8 mode[4];
  s16 titleFrame;
  s16 frame;
  u32 rng;
  u16 saveOK;
  s16 demo_id;
  u8 unk_14[544];
  u8 unk_234;
  u8 unk_235;
  u8 unk_236;
  u8 unk_237;
  u8 cursor;
  u8 pad_239[3];
  u16 unk_23c;
  u16 unk_23e;
  u16 unk_240;
  u8 unk_242;
  u8 unk_243;
  u8 unk_244;
  u8 unk_245;
  u8 unk_246;
  u8 unk_247;
  u16 demoKeyIdx;
  u8 demoKeyFrame;
  u8 demoKeyFrameEnd;
  KEY_INPUT unk_24c;
  u16 unk_24e;
  u8 cardEState;
  u8 unk_251;
  u8 unk_252;
  u8 unk_253;
};
extern struct Intro gIntro;
extern const struct Graphic gGraphic_085472a8;
extern const struct Palette gPalette_085472a8;
void Process_Intro(struct Process* p);
void Process_Game(struct Process* p);
void SetIntroMode(struct Intro* intro, u32 mode);
enum {
  LINK_STATE_START0,
  LINK_STATE_START1,
  LINK_STATE_HANDSHAKE,
  LINK_STATE_INIT_TIMER,
  LINK_STATE_CONN_ESTABLISHED,
};
enum {
  QUEUE_FULL_NONE,
  QUEUE_FULL_SEND,
  QUEUE_FULL_RECV,
};
enum {
  LAG_NONE,
  LAG_MASTER,
  LAG_SLAVE,
};
struct SendQueue {
  u16 data[8][30];
  u8 pos;
  u8 count;
};
struct RecvQueue {
  u16 data[4][8][30];
  u8 pos;
  u8 count;
};
struct Link {
  u8 isMaster;
  u8 state;
  u8 localId;
  u8 playerCount;
  u16 tempRecvBuffer[4];
  bool8 receivedNothing;
  u8 serialIntrCounter;
  u16 padding_E;
  bool8 handshakeAsMaster;
  u8 link_field_11;
  bool8 hardwareError;
  bool8 badChecksum;
  u8 queueFull;
  u8 lag;
  u16 checksum;
  u16 unk_18[4];
  u16 unk_20[4];
  u8 sendCmdIndex;
  u8 recvCmdIndex;
  u8 unk_2a[4];
  struct SendQueue __attribute__((aligned(4))) sendQueue;
  struct RecvQueue __attribute__((aligned(4))) recvQueue;
};
extern char assertion[(sizeof(struct Link) == 2456) ? 1 : -1];
extern u16 gLinkSavedIme;
extern u8 sNumVBlanksWithoutSerialIntr;
extern bool8 sSendBufferEmpty;
extern u8 sHandshakePlayerCount;
extern u8 sChecksumAvailable;
extern u16 sSendNonzeroCheck;
extern u16 sRecvNonzeroCheck;
extern u8 gLastSendQueueCount;
extern u8 gLastRecvQueueCount;
extern u8 u8_ARRAY_020014fc[4];
extern u8 u8_02001500;
extern struct Link gLink;
struct Mission {
  struct PlayInfo* unk_00;
  u8 currentStageID;
  s8 currentStageScore;
  u8 unk_06;
  u8 missionPoint;
  u32 clearTime;
  u16 enemyCount;
  u16 totalDamage;
  u32 elfPenalty;
  u16 retryCount;
  u8 resultScore[6];
  u16 weaponCount[3 + 1];
  u8 _[12];
};
struct Unused_0202fe50 {
  u16 unk_00;
  u16 unk_02;
  u32 unk_04;
  u8 _[8];
};
typedef void (*Unk0834cc60Func)(struct Unused_0202fe50*);
extern struct Mission gMission;
extern struct Unused_0202fe50 gUnk_0202fe50;
void InitMissionInfo(u8 stageID, struct PlayInfo* p);
void AddMissionDamage(u16 damage);
struct Unk_02000db0 {
  u32 magic;
  u16 field1_0x4;
};
extern char assertion[(sizeof(struct Unk_02000db0) == 8) ? 1 : -1];
struct Unk_02000d50 {
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  u8 unk_04;
  u8 unk_05;
  u8 shouldAdvanceLinkState;
  u8 unk_07;
  u8 unk_08;
  u8 unk_09;
  u16 unk_0a;
  u16 unk_0c;
  u16 unk_0e;
  u16 unk_10[6];
  u32 unk_1c;
  u32 unk_20;
  u32 unk_24;
  u32 unk_28;
  u32 unk_2c;
  u32 unk_30;
  u32 unk_34;
  u32 unk_38;
  u32 unk_3c;
  u32 unk_40;
  u32 unk_44;
  u32 linkStatus;
  u32 unk_4c;
  u32 unk_50;
  u32 unk_54;
};
struct Unk_080006c8 {
  void* a;
  void* b;
  void* c;
  u8 d;
  u8 _[3];
};
extern u32 gUnkMmbn4;
extern struct Unk_02000d50 gUnk02000d50;
void SioLink_SendDisconnect(void);
void EReader_SioInitHandshake(void);
u8 EReader_SioWaitForConnect(void);
u8 EReader_SioHandshakePoll(void);
u8 EReader_SioConfirmReceipt(void);
u8 EReader_SioReadCardType(void);
void EReader_SioBeginCardRead(void);
u16 EReader_SioGetCardId(void);
void EReader_SioInitDataReceive(void);
u8 EReader_SioVerifyCardData(void);
u8 EReader_SioCheckAllPlayersConnected(void);
void EReader_SioAbortSession(void);
void FUN_08000eac(u16 recvCmd, u32 playerIdx, u32 recvCmdIndex);
enum ModID {
  MOD_00 = 0,
  MOD_01,
  MOD_02,
  MOD_03,
  MOD_04,
  MOD_05,
  MOD_06,
  MOD_07,
  MOD_PLANT,
  MOD_09,
  MOD_SABER_ATK1,
  MOD_11,
  MOD_P_GUARDIAN_HP4,
  MOD_13,
  MOD_14,
  MOD_15,
  MOD_16,
  MOD_ALOUETTE_DRESS,
  MOD_ARCHIM_ATK1,
  MOD_DAMAGE_50P,
  MOD_20,
  MOD_21,
  MOD_22,
  MOD_23,
  MOD_152EC,
  MOD_ROD_ATK1,
  MOD_26,
  MOD_ORANGE_CAT,
  MOD_28,
  MOD_29,
  MOD_SHIELD_ATK1,
  MOD_BEE_ATK1,
  MOD_32,
  MOD_PHANTOM_ELF,
  MOD_BUSTER_ATK1,
  MOD_POSTER,
  MOD_ANDREW_1UP,
  MOD_BUSTER_ATK2,
  MOD_80EC,
  MOD_39,
  MOD_40,
  MOD_FLOWER,
  MOD_42,
  MOD_ANIMAL_ELF_LOOKS,
  MOD_YOUNG_ANDREW,
  MOD_ARCHIM_ATK2,
  MOD_SEAGULLS,
  MOD_TABBY_CAT,
  MOD_BEE_ATK2,
  MOD_49,
  MOD_SHIELD_ATK2,
  MOD_51,
  MOD_GRAFFITI,
  MOD_53,
  MOD_100EC,
  MOD_ROD_ATK2,
  MOD_56,
  MOD_57,
  MOD_58,
  MOD_59,
  MOD_32EC_2B,
  MOD_61,
  MOD_52EC_2C,
  MOD_52EC_2F,
  MOD_64,
  MOD_ELPIZO_ELF,
  MOD_66,
  MOD_SHIELD_ATK3,
  MOD_68,
  MOD_69,
  MOD_70,
  MOD_BEE_ATK3,
  MOD_ARCHIM_ATK3,
  MOD_73,
  MOD_74,
  MOD_75,
  MOD_BUSTER_ATK3,
  MOD_77,
  MOD_78,
  MOD_79,
  MOD_80,
  MOD_81,
  MOD_82,
  MOD_83,
  MOD_84,
  MOD_ROD_ATK3,
  MOD_86,
  MOD_87,
  MOD_ARCHIM_ATK4,
  MOD_SABER_ATK2,
  MOD_90,
  MOD_91,
  MOD_92,
  MOD_93,
  MOD_94,
  MOD_95,
  MOD_96,
  MOD_SABER_ATK3,
  MOD_98,
  MOD_99,
  MOD_100,
  MOD_101,
  MOD_102,
  MOD_103,
  MOD_104,
  MOD_105,
  MOD_106,
  MOD_107,
  MOD_108,
  MOD_109,
  MOD_110,
  MOD_111,
  MOD_112,
  MOD_113,
  MOD_114,
  MOD_115,
  MOD_116,
  MOD_117,
  MOD_118,
  MOD_119,
  MOD_120,
  MOD_121,
  MOD_122,
  MOD_123,
  MOD_124,
  MOD_125,
  MOD_126,
  MOD_127,
  MOD_COUNT,
};
extern char assertion[(MOD_COUNT == 128) ? 1 : -1];
struct PaletteAnimation {
  struct MotionPltt *pal;
  struct MotionCmd **cmds;
  struct Motion m;
  bool16 paused;
  u16 palIdx;
};
struct PaletteAnimationManager {
  u16 ids[16];
  struct PaletteAnimation blinks[16];
};
extern struct PaletteAnimationManager gPaletteAnimationManager;
void RemovePaletteAnimation(u16 n);
void StartPaletteAnimation(u16 blinkID, u16 ofs);
u32 StepPaletteAnimation(u16 blinkID);
void RemoveAllPaletteAnimations(void);
void TransferAnimatedPalettesToPaletteBuffer(void);
void PauseAllPaletteAnimations(void);
void ResumeAllPaletteAnimations(void);
s32 PushoutToUp1(s32 x, s32 y);
s32 PushoutToUp2(s32 x, s32 y);
s32 PushoutToDown2(s32 x, s32 y);
s32 FUN_0800a134(s32 x, s32 y);
s32 FUN_0800a05c(s32 x, s32 y);
struct Zero;
struct Pickup {
  struct Entity s; struct Body body;;
  s32 y;
  struct Zero* z;
  u8 work[8];
};
extern struct Pickup gPickups[10];
struct EntityHeader;
extern struct EntityHeader* gPickupHeaderPtr;
typedef void (*PickupFunc)(struct Pickup*);
typedef PickupFunc PickupRoutine[5];
extern const PickupRoutine* const gPickupFnTable[2];
void DeletePickup(struct Entity* p);
struct Entity* CreatePickupItem(u8 itemID, struct Coord* c, u8 param_3);
struct Entity* CreateMapDisk(u8 diskNo, struct Coord* c, u8 r2);
typedef ProjectileFunc ProjectileRoutine[5];
extern const ProjectileRoutine* const gProjectileFnTable[48];
void UpdateProjectiles(void);
void DeleteProjectile(struct Projectile* p);
struct Projectile* CreateLemon(struct Coord* c, s32 r1, u8 r2);
void ResetPivot(struct Pivot *p, struct Coord *c, u32 _, void *nullVal);
void CreateDrawPivot(struct DrawPivot *c, struct Pivot *p, void *_ __attribute__((unused)));
void TaskCB_DrawNoAffineSprite(struct Sprite *s, struct DrawPivot *c);
void TaskCB_DrawRotatableSprite(struct Sprite *s, struct DrawPivot *c);
void TaskCB_SetMetaspriteTileNum1(struct Sprite *s, struct DrawPivot *tc);
void TaskCB_SetMetaspriteTileNum2(struct Sprite *s, struct DrawPivot *tc);
struct SramState {
  u8 unk_00;
  u8 slot;
  u8 status;
  u8 busStatus;
  s16 retryCount;
  u16 useBackup;
  u8* start;
  u8* wramAddr;
  u8* sramAddr;
  s32 length;
  u32 remaining;
  s16 unk_1c;
  u16 health;
};
typedef void (*saveFunc)(struct SramState* s);
extern struct SramState gSramState;
extern const saveFunc gSramRoutine[3];
void UpdateSram(void);
bool32 CheckSavedataCorrect(u8 saveIdx, s32 length);
s32 WriteSramINTI(u8 saveIdx);
s32 sram_08003330(u8 saveIdx, u8* dst, u32 length);
s32 sram_08003378(u8 saveIdx, u8* dst, u32 length);
void nop_080033d4(struct SramState* _);
void saveSram(struct SramState* s);
void loadSram(struct SramState* s);

extern const struct ChunkMap sChunkMap1;

extern const struct ChunkMap sChunkMap2;

extern const struct ChunkMap sChunkMap3;

extern const tileset_ofs_t sTilesetOffset[];

extern const u16 sScreenBehavior[];

extern const struct ChunkMap sChunkMap1;

extern const struct ChunkMap sChunkMap2;

extern const struct ChunkMap sChunkMap3;

extern const tileset_ofs_t sTilesetOffset[];

extern const u16 sScreenBehavior[];

extern const struct ChunkMap sChunkMap1;

extern const struct ChunkMap sChunkMap2;

extern const struct ChunkMap sChunkMap3;

extern const tileset_ofs_t sTilesetOffset[];

extern const u16 sScreenBehavior[];

extern const struct ChunkMap sChunkMap1;

extern const struct ChunkMap sChunkMap2;

extern const struct ChunkMap sChunkMap3;

extern const tileset_ofs_t sTilesetOffset[];

extern const u16 sScreenBehavior[];

extern const struct ChunkMap sChunkMap1;

extern const struct ChunkMap sChunkMap2;

extern const struct ChunkMap sChunkMap3;

extern const tileset_ofs_t sTilesetOffset[];

extern const u16 sScreenBehavior[];

struct Process {
  u8 status;
  bool8 doReset;
  s16 sleep;
  void* fn;
  u16* sp;
  u8 unk_0c[4];
  u8 unk_10[8];
};
struct TransferReservation {
  void* start;
  u16* dst;
  u32 count;
  u16* src;
  void* DMA0SAD;
  void* DMA0DAD;
  u32 DMA0CNT;
  s16 delta_src;
  s16 delta_dst;
  u16 remaining;
  u16 _;
};
struct InterruptManager {
  VoidFunc table[14];
  u32 main[72];
  void (*vblankCallback)(void);
  void (*hblankCallback)(void);
  u32 frame;
  vu8 frame2;
  vu8 slowGameRatio;
  u8 lyc;
  u8 intrLock;
  u32 dma0[3];
  u32 reservedDma0[3];
  struct TransferReservation tr[2];
};
struct ProcessManager {
  u8 stack[1248 + 2304 + 1280 + 32];
  u32 masterFrame;
  bool32 systemOK;
  struct Process processes[3];
  u32 procID;
  u8 _[12];
};
extern void* StackFramePointer;
extern struct InterruptManager gIntrManager;
extern u32 u32_020014e0;
extern struct ProcessManager gProcessManager;
extern const u16 gProcessStackPointerOffsets[3];
void ResetProcess(s32 i, void* fn);
void Process_SoftReset(struct Process* _);
void Process_System(struct Process* p);
void _usrHBlankCallback(void);
void LinkVSync(void);
void FUN_080044a0(void);
void disableProcess(s32 i);
void SwitchProcess(bool32 b);
void ExitProcess(void);
void FUN_08002428(struct Process* p);
void CopyMemory(void* src, void* dst, u32 bytesize);
void FillMemory(u16 fillval, u16* dst, u32 bytesize);
void exec(void* fn);
void CallProcess(struct Process* proc, void* fn, void* sp, void* pSp);
struct TextWindowText {
  u16 flag;
  u16 mode;
  u8 mugshot;
  u8 y;
  bool8 mugshotRight;
  u8 optionID;
  s32 textType;
  struct {
    u8 kind;
    u8 phase;
    bool8 prompt;
    u8 _;
  } props;
  s16 len;
  s16 done;
  s16 frame;
  s16 unk_16;
  char_t* start;
  char_t* current;
  char_t* next;
  char_t* optional_next;
};
struct TextWindow {
  u32 frame;
  tile_id_t* bg0Mask;
  struct TextWindowText text;
};
typedef void (*TextFunc)(struct TextWindowText*);
extern struct TextWindow gTextWindow;
void ClearTextWindow(void* bg0);
void UpdateTextWindow(void);
void PrintNormalMessage(TextID n);
void PrintTextWindow(TextID n, u16 kind);
void PrintOptionMessage1(TextID n);
void PrintOptionMessage2(TextID n);
void PrintResultInline(TextID t, bool16 ng);
struct CharTile {
  struct CharTile* next;
  u16 c;
  u16 tileID;
};
struct TextPrinter {
  tile_id_t* bg0;
  s16 len;
  s16 unk_002;
  str_t strings[96];
  u8 x[96];
  u8 y[96];
  s16 progress[96];
  struct CharTile tilelist[80];
  struct CharTile* cur;
  struct CharTile* used;
  struct CharTile* freelist;
  char_t* variable;
  u8 startX;
  u8 startY;
  u8 endX;
  u8 endY;
  u32 unk_598;
};
extern struct TextPrinter gTextPrinter;
extern char_t gTerminateCharCode;
extern const u8 gFontBold[][32];
extern const struct PlttData gFontPalette[96];
void LoadAsciiBold(void);
void ResetCharTiles(void);
void LoadKatakanaBold(void);
void FUN_080e981c(void);
void FUN_080e9840(void);
void PrintAllStrings(void);
void FUN_080e98ec(void);
void PrintString(const char_t* s, u32 x, u32 y);
s16 getStringLength(char_t* s);
void text_080e9b40(const char_t* s, u32 x, u32 y, u16 count);
void PrintRows(char_t* s, u32 x, u32 y, u16 count, u16 r4);
void PrintUnicodeString(const char_t* s, u32 x8, u32 y8);
char_t* SkipString(char_t* s, s32 skipBytesize);
struct SlashedEnemy {
  motion_t m;
  u8 unk_02[2];
  struct Coord16 c;
  struct Coord16 d;
  struct Coord16 unk_coord_0c;
  struct Coord16 unk_10;
  u16 unk_14[2];
  u8 _[4];
};
typedef void (*VFXFunc)(struct VFX*);
typedef VFXFunc VFXRoutine[5];
extern const VFXRoutine* const gVFXFnTable[85];
void DeleteVFX(struct Entity* p);
struct Entity* CreateSmoke(u8 kind, struct Coord* c);
struct VFX* CreateChargeEffect(struct Zero* z, struct VFX* v, u8 r2);
void CreateParticle(struct Coord* c, u8 action, bool8 isRight);
void oz_080b3820(struct Coord* omegaCoord, bool8 isRight);
void CreateWallDust(struct Coord* c, bool8 isRight);
struct VFX* CreateRipple(struct Zero* z, bool8 outOfSea);
struct VFX* CreateEmotionBubble(u8 kind, struct Coord* target, struct Coord* c);
struct VFX* CreateCopyXIcon(struct Zero* z, struct Coord* c, u8 n);
struct VFX* CreateExlifeIndicator(u8 extraLife);
struct VFX* CreateMissionAlert(u8 kind);
struct VFX* CreateSlashedEnemy(struct Coord* c, const struct SlashedEnemy* data, u8 r2, u8 r3);
struct VFX* FUN_080bfce8(struct Coord* c, u8 r1);
struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);
void CreateVFX31_1(s32 x, s32 y);
void CreateVFX31_2(s32 x, s32 y);
void FUN_080b81a0(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void FUN_080b7ffc(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
struct AfterImage {
  struct Entity s;
  struct Coord c;
  u8 unk_8[8];
};
extern char assertion[(sizeof(struct AfterImage) == sizeof(struct Entity) + 16) ? 1 : -1];
struct Entity* CreateAfterImages(struct Entity* p);
struct ElementEffect {
  struct Entity s;
  struct Coord c;
  u8 unk_8[8];
};
extern char assertion[(sizeof(struct ElementEffect) == sizeof(struct Entity) + 16) ? 1 : -1];
enum ZeroPosture {
  POSTURE_IDLE = 0,
  POSTURE_DASH = 1,
  POSTURE_WALL = 2,
  POSTURE_SHADOW = 3,
  POSTURE_DOOR_2D = 4,
  POSTURE_DOOR_3D = 5,
  POSTURE_COUNT,
};
typedef ZeroFunc ZeroRoutine[5];
extern const ZeroRoutine* const gPlayerFnTable[7];
enum ZeroGround {
  GROUND_IDLE,
  GROUND_WALK,
  GROUND_DASH,
};
extern struct Zero* pZero;
extern struct Zero* pZero2;
extern const struct Collision gZeroCollisions[POSTURE_COUNT];
extern const struct Rect gZeroRanges[POSTURE_COUNT];
void ClearZeroStatus(struct ZeroStatus* p);
void ClearZeroStatusHard(struct ZeroStatus* p);
void ClearZeroStatusUltimate(struct ZeroStatus* p);
void FUN_080321d4(struct ZeroStatus* p);
void SaveZeroStatus(struct Zero* z, struct ZeroStatus* status);
void CopyZeroStatus(struct Zero* z, struct ZeroStatus* status);
u8 GetZeroColor(struct Zero* z);
u16 FUN_080101a8(void);
void InitPlayerHeader(struct EntityHeader* h, struct Zero* p, s16 len);
struct Zero* AllocPlayer(void);
struct Zero* AllocPlayer2(void);
void RemovePlayer(struct Zero* p);
void LoadZeroPalette(struct Entity* _, u32 color);
void LoadShadowDashPalette(struct Zero* _, u32 color);
bool8 UseSubtank(struct Zero* z);
bool8 IsDoubleHP(struct Zero* z);
u8 GetMaxHP(struct Zero* z);
u8 getMaxHP1x(struct Zero* z);
bool8 AddECrystal(struct Zero* z, u16 amount);
bool8 incrementSubtankHP(struct Zero* z);
u8 makeZeroFaster(struct Zero* z, u8 val);
u8 CountRodButton(struct Zero* z, bool8 isSubWeapon);
u8 CountButtonMashing(struct Zero* z);
void ResetZeroInput(struct Zero* z);
void resetSateliteElfPosition(struct Zero* z);
u16 GetDefaultMotion(struct Zero* z);
u8 CalcBusterBonus(struct Zero* z);
s16 CalcMaxWalkSpeed(struct Zero* z);
void FUN_080322c4(struct ZeroStatus* d);
bool8 IsButtonMashed(struct Zero* z);
void zeroNeutral2(struct Zero* z);
void zeroAir2(struct Zero* z);
void zeroWall2(struct Zero* z);
void zeroLadder2(struct Zero* z);
void zeroDamaged(struct Zero* z);
void zeroKnockBack(struct Zero* z);
void FUN_0802c010(struct Zero* z);
void zeroDoor2D(struct Zero* z);
void zeroDoor3D(struct Zero* z);
void zeroMode7(struct Zero* z);
void zeroFloat(struct Zero* z);
void zeroTalk(struct Zero* z);
void zeroTeleport(struct Zero* z);
void zeroCyberDoor(struct Zero* z);
void ZeroAttack_Ground(struct Zero* z);
void zeroAttack(struct Zero* z);
void onSaber_GroundIdle(struct Zero* z);
void charge_saber_ground(struct Zero* z);
void recoilAttack(struct Zero* z);
void shieldAttack(struct Zero* z);
void shield_throw(struct Zero* z);
void shield_0802e1c8(struct Zero* z);
void zero_shield_0802e268(struct Zero* z);
void zeroAirAtk(struct Zero* z);
void ZeroAttack_Air(struct Zero* z);
void ZeroAttack_Wall(struct Zero* z);
void ZeroAttack_Ladder(struct Zero* z);
void zeroWallAtk(struct Zero* z);
void zeroLadderAtk(struct Zero* z);
bool8 zero_08026f90(struct Zero* z, const struct Rect* p);
s16 CalcDx(struct Zero* z);
metatile_attr_t PushoutByFloor1(struct Zero* z, const struct Rect* r1, bool8 r2);
metatile_attr_t PushoutByCeiling(struct Zero* z, const struct Rect* r1, bool8 r2);
metatile_attr_t PushoutByCeilingOnLadder(struct Zero* z, const struct Rect* r1, bool8 r2);
metatile_attr_t GetWallMetatileAttr(struct Zero* z, const struct Rect* r1, bool8 _ __attribute__((unused)));
u8 ladder_08026bb0(struct Zero* z, const struct Rect* range, bool8 _);
u8 TryLadderDown(struct Zero* z, const struct Rect* p, bool8 _);
u8 TryLadderUp(struct Zero* z, const struct Rect* p, bool8 r2);
metatile_attr_t IsOnSoftPlatform(struct Zero* z, const struct Rect* p, bool8 r2);
s16 getFallAcceleration(struct Zero* z);
s16 calcMaxFallSpeed(struct Zero* z);
metatile_attr_t PushoutWallX(struct Zero* z, const struct Rect* p, bool8 r2);
u8 TryContinueLadderDown(struct Zero* z, const struct Rect* p, bool8 r2);
bool8 PushoutByBorder(struct Zero* z, const struct Rect* p, bool8 r2);
bool8 CanWallSlide(struct Zero* z, const struct Rect* p, bool8 _);
bool8 IsForwardPressed(struct Zero* z, const struct Rect* p, bool8 _);
bool8 IsZeroAgainstWall(struct Zero* z, const struct Rect* p, bool8 _);
u8 RecoilFromHazards(struct Zero* z, const struct Rect* range);
u8 RecoilFromFloor(struct Zero* z, const struct Rect* range);
metatile_attr_t PushoutByFloor2(struct Zero* z, const struct Rect* p, bool8 r2);
bool8 IsElfUsed(struct Zero* z, cyberelf_t elfID);
bool8 isElfUsed_2(struct Zero* z, cyberelf_t elfID);
metatile_attr_t _pushoutHazardY(struct Zero* z, s32 x, s32 y, struct Coord* c);
s16 GetDashSpeed(struct Zero* z);
bool8 IsAttackOK(struct Zero* z, weapon_t* w);
void KeepMotion(struct Zero* z, motion_t m);
void FUN_08032504(struct Zero* z, motion_t m);
void FUN_0803267c(struct Zero* z, motion_t m);
void skipEventScene(struct Zero* z, struct ZeroStatus* status);
void InstantlyKilling(struct Zero* z);
s16 getWallFallSpeed(struct Zero* z);
void CheckZeroHazard(struct Zero* z);
void setStageElfFlags(struct Zero* z);
bool8 Is1000Slash(struct Zero* z);
void zero_08032724(struct Zero* z);
void SetDisableArea(struct Zero* z, s32 left, s32 top, s32 right, s32 bottom);
void HandlePlayerInput(struct Zero* z);
u8 zero_08026970(struct Zero* z, const struct Rect* range, bool8 _);
typedef WeaponFunc WeaponRoutine[5];
extern const WeaponRoutine* const gWeaponFnTable[16 + 1];
enum WeaponCharge {
  NO_CHARGE,
  SEMI_CHARGE,
  FULL_CHARGE,
};
extern const WeaponRoutine gBusterRoutine;
extern const WeaponRoutine gSaberRoutine;
extern const WeaponRoutine gShieldGuardRoutine;
extern const WeaponRoutine gRodRoutine;
extern const WeaponRoutine gShieldFlyRoutine;
extern const WeaponRoutine gSaberWaveRoutine;
extern const WeaponRoutine gWeapon6Routine;
extern const WeaponRoutine gReflectLaserRoutine;
extern const WeaponRoutine gSoulLauncherRoutine;
extern const WeaponRoutine gBurstShotRoutine;
extern const WeaponRoutine gBlizzardArrowRoutine;
extern const WeaponRoutine gThrowBladeRoutine;
extern const WeaponRoutine gShieldSweepRoutine;
extern const WeaponRoutine gWeapon13Routine;
extern const WeaponRoutine gSmashElecRoutine;
extern const WeaponRoutine gElecShieldSweepRoutine;
extern const WeaponRoutine gMinigameRodRoutine;
extern const struct Collision gSaberGeneralCollisions[2];
extern const struct Collision* const* const gSaberCollisions[25];
extern const u8 gSaberElements[4];
extern u16 gLastWeaponElements[3 + 1];
extern u16 gWeaponElements[3 + 1];
extern const u16 gWeaponTileNum[3 + 1];
extern const u8 gWeaponPalIDs[3 + 1];
void DrawWeapon(struct Renderer* p);
void DeleteWeapon(struct Weapon* w);
void SetWeaponElement(u16 n, u16 val);
void KillAllWeapons(WeaponFunc fn);
u8 GetWeaponCharge(struct Zero* z, bool8 isSubWeapon);
struct Weapon* CreateBlizzardArrow(struct Zero* z, struct Coord* c, u8 n, bool8 xflip);
void DeleteSaber(struct Weapon* w);
struct Weapon* CreateWeaponBuster(struct Zero* z, struct Coord* c, u8 n, bool8 xflip, bool8 yflip);
struct Weapon* CreateWeaponSaber(struct Zero* z, u8 r1);
struct Weapon* CreateBuster(struct Zero* z, s32 x, s32 y, bool8 isDirRight);
struct Weapon* CreateWeaponShieldGuard(struct Zero* z, u8 n);
struct Weapon* CreateWeaponRod(struct Zero* z);
struct Weapon* CreateWeaponShieldFly(struct Zero* z, u8 n);
struct Weapon* CreateSmashElec(struct Zero* z, struct Coord* c, u8 leftOrRight);
struct Weapon* CreateThrowBlade(struct Zero* z, struct Weapon* w, bool8 isIce);
struct Weapon* CreateSaberWave(struct Zero* z, struct Weapon* w, bool8 r2);
void CreateWeapon6(s32 x, s32 y);
u8 CalcBusterBonus(struct Zero* z);
u8 CalcSaberBonus(struct Zero* z);
u8 CalcRodBonus(struct Zero* z);
u8 CalcShieldBonus(struct Zero* z);
void MenuExit_Buster(struct Weapon* w);
void MenuExit_ShieldGuard(struct Weapon* w);
void MenuExit_ShieldFly(struct Weapon* w);
void MenuExit_ReflectLaser(struct Weapon* w);
void MenuExit_SoulLauncher(struct Weapon* w);
void MenuExit_BurstShot(struct Weapon* w);
void MenuExit_BlizzardArrow(struct Weapon* w);
void MenuExit_ThrowBlade(struct Weapon* w);
void MenuExit_ShieldSweep(struct Weapon* w);
void MenuExit_Weapon13(struct Weapon* w);
void MenuExit_SaberSmash(struct Weapon* w);
void MenuExit_ShieldSweepElec(struct Weapon* w);
struct Widget {
  struct Entity s;
  u8 props[16];
};
struct SquareCursorWidget {
  struct Entity s;
  u16 px;
  u16 py;
  bool8 dead;
  u8 pad_79[11];
};
extern struct Widget gWidgets[64];
struct EntityHeader;
extern struct EntityHeader* gWidgetHeaderPtr;
typedef void (*WidgetFunc)(struct Widget*);
typedef WidgetFunc WidgetRoutine[5];
extern const WidgetRoutine* const gWidgetFnTable[14];
struct GameState;
void DeleteWidget(struct Entity* w);
struct Widget* CreateElfIcon(struct GameState* g);
struct Widget* CreateElfMenuItem(struct GameState* g, u8 row, u8 r2);
struct ExSkillIcons {
  struct Entity s;
  u8 unk_000[4];
  u8 unk_004[12];
};
extern char assertion[(sizeof(struct ExSkillIcons) == (sizeof(struct Entity) + 16)) ? 1 : -1];
#define MOTION(id, idx) ((id << 8) | idx)
