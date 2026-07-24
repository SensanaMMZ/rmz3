# Holdouts with a reconstructed C body (129)

These have a `#if MODERN` body, so `tools/objdiff_rank.sh` gives a
meaningful match%% for them and the permuter has something to chew on.

Regenerate with `python3 tools/classify_holdouts.py`.

## By file

| file | count |
|---|---|
| src/player.c | 10 |
| src/terrain.c | 8 |
| src/collision.c | 6 |
| src/weapon/saber.c | 6 |
| src/entity_motion.c | 4 |
| src/sprite2.c | 4 |
| src/boss/blizzack.c | 3 |
| src/entity.c | 3 |
| src/game/main.c | 3 |
| src/physics/pushout.c | 3 |
| src/player/zero/attack/ground/idle.c | 3 |
| src/player/zero/attack/util.c | 3 |
| src/player/zero/update.c | 3 |
| src/stage/entity.c | 3 |
| src/bg0/text.c | 2 |
| src/boss/omega_zero.c | 2 |
| src/camera.c | 2 |
| src/game/menu/main.c | 2 |
| src/player/zero/attack/ladder.c | 2 |
| src/player/zero/input/input.c | 2 |
| src/player/zero/input/util.c | 2 |
| src/player/zero/zero.c | 2 |
| src/script_command.c | 2 |
| src/stage/spacecraft/landscape.c | 2 |
| src/widget/armor_icons.c | 2 |
| src/widget/unk_01.c | 2 |
| src/widget/unk_09.c | 2 |
| src/boss/anubis.c | 1 |
| src/boss/childre.c | 1 |
| src/boss/phantom.c | 1 |
| src/cyberelf/bird.c | 1 |
| src/cyberelf/sea_otter.c | 1 |
| src/enemy/beetank.c | 1 |
| src/enemy/grand_cannon.c | 1 |
| src/enemy/minigame/ciel2.c | 1 |
| src/enemy/unk_59.c | 1 |
| src/game/menu.c | 1 |
| src/game/menu/elf.c | 1 |
| src/gpu_regs.c | 1 |
| src/intro.c | 1 |
| src/main.c | 1 |
| src/math.c | 1 |
| src/mission.c | 1 |
| src/motion.c | 1 |
| src/player/zero/attack/air.c | 1 |
| src/player/zero/attack/ground/dash.c | 1 |
| src/player/zero/attack/ground/walk.c | 1 |
| src/player/zero/attack/wall.c | 1 |
| src/player/zero/util.c | 1 |
| src/result.c | 1 |
| src/solid/actor.c | 1 |
| src/solid/door_2d_blue.c | 1 |
| src/solid/ice_block.c | 1 |
| src/solid/unk_36.c | 1 |
| src/stage/anatre_forest/landscape.c | 1 |
| src/stage/area_x2/landscape.c | 1 |
| src/stage/sunken_library/update.c | 1 |
| src/stage/volcano/landscape.c | 1 |
| src/stagerun.c | 1 |
| src/system.c | 1 |
| src/vfx/elf_particle.c | 1 |
| src/vfx/exlife_indicator.c | 1 |
| src/vfx/unk_32.c | 1 |
| src/weapon/buster.c | 1 |
| src/weapon/minigame_rod.c | 1 |
| src/widget/disk_modal_border.c | 1 |
| src/widget/elf_menu_item.c | 1 |
| src/widget/exskill.c | 1 |

## All

| location | signature |
|---|---|
| src/bg0/text.c:36 | `NON_MATCH void ResetCharTiles(void)` |
| src/bg0/text.c:78 | `NON_MATCH void PrintAllStrings(void)` |
| src/boss/anubis.c:13 | `NON_MATCH void FUN_08050090(struct Boss* p)` |
| src/boss/blizzack.c:47 | `NON_MATCH void blizzackMode0(struct Boss* p)` |
| src/boss/blizzack.c:66 | `NON_MATCH void blizzackMode1(struct Boss* p)` |
| src/boss/blizzack.c:91 | `NON_MATCH void blizzackNextMode(struct Boss* p)` |
| src/boss/childre.c:33 | `NON_MATCH void childre_08040428(struct Boss* p)` |
| src/boss/omega_zero.c:64 | `NON_MATCH static void calcNextOmegaZeroAction(struct BossOmegaZero* p)` |
| src/boss/omega_zero.c:151 | `NON_MATCH static void OmegaZero_Init(struct BossOmegaZero* p)` |
| src/boss/phantom.c:647 | `NON_MATCH void FUN_080607f0(struct Boss* p)` |
| src/camera.c:103 | `NON_MATCH static void focus(struct Camera* camera, u8 chaseMode)` |
| src/camera.c:250 | `NON_MATCH static void CameraMode3Callback(struct Camera* camera)` |
| src/collision.c:116 | `NON_MATCH void ResisterNonAffineHitbox(struct Body* body)` |
| src/collision.c:157 | `NON_MATCH void RegisterFlipableHitbox(struct Body* body, u8 flip)` |
| src/collision.c:392 | `NON_MATCH u16 CalcDamage(struct Body* a, struct Body* d)` |
| src/collision.c:428 | `NON_MATCH void hitbox_08007674(struct Body* a, struct Body* d)` |
| src/collision.c:814 | `NON_MATCH static void tryOverlapCallback1(struct Hitbox* ah, struct Hitbox* dh)` |
| src/collision.c:905 | `NON_MATCH static void tryOverlapCallback2(struct Hitbox* ah, struct Hitbox* dh)` |
| src/cyberelf/bird.c:20 | `NON_MATCH void FUN_080e58bc(struct Elf* p)` |
| src/cyberelf/sea_otter.c:21 | `NON_MATCH void MenuExit_SeaOtterElf(struct Elf* e)` |
| src/enemy/beetank.c:45 | `NON_MATCH void Beetank_Update(struct Enemy* p)` |
| src/enemy/grand_cannon.c:192 | `NON_MATCH static void GrandCannon_Update(struct Enemy* p)` |
| src/enemy/minigame/ciel2.c:47 | `NON_MATCH static void CielMinigameEnemy2_Init(struct Enemy* p)` |
| src/enemy/unk_59.c:104 | `NON_MATCH void FUN_080922e0(struct Enemy* p)` |
| src/entity.c:90 | `NON_MATCH void RunDamageEffect(struct EntityHeader* h)` |
| src/entity.c:116 | `NON_MATCH void DrawEntity(struct EntityHeader* h, struct Renderer* tm)` |
| src/entity.c:159 | `NON_MATCH void DrawCollidableEntity(struct EntityHeader* h, struct Renderer* tm)` |
| src/entity_motion.c:96 | `NON_MATCH void SetMotion(struct Entity* p, motion_t m)` |
| src/entity_motion.c:134 | `NON_MATCH void UpdateMotionGraphic(struct Entity* p)` |
| src/entity_motion.c:171 | `NON_MATCH void FUN_0801779c(struct Entity* p)` |
| src/entity_motion.c:238 | `NON_MATCH void InitMotionLocation(void)` |
| src/game/main.c:270 | `NON_MATCH static void GameLoop_NewGame(struct GameState* g)` |
| src/game/main.c:359 | `NON_MATCH static void GameLoop_Overworld(struct GameState* p)` |
| src/game/main.c:603 | `NON_MATCH static void GameLoop_ChangeMap(struct GameState* p)` |
| src/game/menu.c:628 | `NON_MATCH void CopyBgMap(u16* dst, struct BgMapHeader* src, u8 x, u8 y)` |
| src/game/menu/elf.c:266 | `NON_MATCH static void ElfMenuFocusLoop_TabSelect(struct GameState* g)` |
| src/game/menu/main.c:1179 | `NON_MATCH static void MainMenuLoop_Update(struct GameState* m)` |
| src/game/menu/main.c:3359 | `NON_MATCH u8 CheckUnlockedHead(struct GameState* g, u8 idx)` |
| src/gpu_regs.c:89 | `NON_MATCH void FlushOAM(void)` |
| src/intro.c:405 | `NON_MATCH static void updateTitleAnimation(struct Intro* p)` |
| src/main.c:23 | `NON_MATCH void AgbMain(void)` |
| src/math.c:48 | `NON_MATCH u32 FUN_080e964c(u32 a, s32 b, s32 c)` |
| src/mission.c:54 | `NON_MATCH void calcStageScore(void)` |
| src/motion.c:48 | `NON_MATCH void UpdateMotionState(struct Motion* m)` |
| src/physics/pushout.c:133 | `NON_MATCH s32 PushoutToDown2(s32 x, s32 y)` |
| src/physics/pushout.c:968 | `NON_MATCH s32 FUN_0800a40c(s32 x, s32 y)` |
| src/physics/pushout.c:1011 | `NON_MATCH void AppendHazard(u16 id, u16 attr, const struct Coord* c, const struct Rect* size)` |
| src/player.c:177 | `NON_MATCH u8 GetMaxHP(struct Zero* z)` |
| src/player.c:324 | `NON_MATCH metatile_attr_t PushoutWallX(struct Zero* z, const struct Rect* p, u8 r2)` |
| src/player.c:1690 | `NON_MATCH metatile_attr_t IsOnSoftPlatform(struct Zero* z, const struct Rect* p, bool8 r2)` |
| src/player.c:1761 | `NON_MATCH bool8 IsZeroAgainstWall(struct Zero* z, const struct Rect* p, bool8 _)` |
| src/player.c:2169 | `NON_MATCH u8 TryContinueLadderDown(struct Zero* z, const struct Rect* range, bool8 _)` |
| src/player.c:2195 | `NON_MATCH u8 TryLadderDown(struct Zero* z, const struct Rect* range, bool8 _)` |
| src/player.c:2241 | `NON_MATCH bool8 PushoutByBorder(struct Zero* z, const struct Rect* range, bool8 checkHazard)` |
| src/player.c:2344 | `NON_MATCH void CheckZeroHazard(struct Zero* z)` |
| src/player.c:3434 | `NON_MATCH static metatile_attr_t IsInHazard(struct Zero* z, s32 x, s32 y)` |
| src/player.c:3454 | `NON_MATCH static bool8 IsAgainstHazard(struct Zero* z, s32 x, s32 y)` |
| src/player/zero/attack/air.c:30 | `NON_MATCH static void air1(struct Zero* z)` |
| src/player/zero/attack/ground/dash.c:332 | `NON_MATCH static void dash_saber(struct Zero* z)` |
| src/player/zero/attack/ground/idle.c:29 | `NON_MATCH static void _zeroTryAttack(struct Zero* z)` |
| src/player/zero/attack/ground/idle.c:238 | `NON_MATCH static void handle_saber_input(struct Zero* z)` |
| src/player/zero/attack/ground/idle.c:840 | `NON_MATCH static void rod_1000slash(struct Zero* z)` |
| src/player/zero/attack/ground/walk.c:39 | `NON_MATCH static void FUN_0802e338(struct Zero* z)` |
| src/player/zero/attack/ladder.c:33 | `NON_MATCH static void zero_ladder_08030ee0(struct Zero* z)` |
| src/player/zero/attack/ladder.c:368 | `NON_MATCH static void onRod(struct Zero* z)` |
| src/player/zero/attack/util.c:33 | `NON_MATCH bool8 IsAttackOK(struct Zero* z, weapon_t* w)` |
| src/player/zero/attack/util.c:451 | `NON_MATCH u8 GetWeaponCharge(struct Zero* z, bool8 isSubWeapon)` |
| src/player/zero/attack/util.c:560 | `NON_MATCH bool8 isElfUsed_2(struct Zero* z, cyberelf_t elfID)` |
| src/player/zero/attack/wall.c:35 | `NON_MATCH static void zero_wall_080303d4(struct Zero* z)` |
| src/player/zero/input/input.c:41 | `NON_MATCH static void inIdle(struct Zero* z)` |
| src/player/zero/input/input.c:215 | `NON_MATCH void HandlePlayerInput_Air(struct Zero* z)` |
| src/player/zero/input/util.c:1230 | `NON_MATCH static void tryCommandDash(struct Zero* z)` |
| src/player/zero/input/util.c:1302 | `NON_MATCH u8 CountRodButton(struct Zero* z, bool8 isSubWeapon)` |
| src/player/zero/update.c:552 | `NON_MATCH static void zeroNormalJumpRise(struct Zero* z)` |
| src/player/zero/update.c:956 | `NON_MATCH static void zeroWallSeq1(struct Zero* z)` |
| src/player/zero/update.c:1331 | `NON_MATCH static void zeroInitKnockBack(struct Zero* z)` |
| src/player/zero/util.c:166 | `NON_MATCH void FUN_080322dc(struct Zero* z, motion_t m, u8 r2)` |
| src/player/zero/zero.c:29 | `NON_MATCH static void Zero_Init(struct Zero* z)` |
| src/player/zero/zero.c:123 | `NON_MATCH static void Zero_Update(struct Zero* z)` |
| src/result.c:1521 | `NON_MATCH static bool32 CountUpResultScore(s32 score, s16 step, u8 se_interval, u8 x, u8 y)` |
| src/script_command.c:269 | `NON_MATCH static bool32 Cmd_cmd06(struct VM* vm)` |
| src/script_command.c:519 | `NON_MATCH static bool32 Cmd_flag(struct VM* vm)` |
| src/solid/actor.c:437 | `NON_MATCH u16 FUN_080d0aa0(struct Entity* p, motion_t m, u8 r2)` |
| src/solid/door_2d_blue.c:25 | `NON_MATCH static void Door2DBlue_Init(struct Solid* p)` |
| src/solid/ice_block.c:28 | `NON_MATCH static void IceBlock_Init(struct Solid* p)` |
| src/solid/unk_36.c:40 | `NON_MATCH static void Solid36_Update(struct Solid* p)` |
| src/sprite2.c:30 | `NON_MATCH void TaskCB_DrawNoAffineSprite(struct Sprite* s, struct DrawPivot* tc)` |
| src/sprite2.c:78 | `NON_MATCH void TaskCB_DrawRotatableSprite(struct Sprite* s, struct DrawPivot* tc)` |
| src/sprite2.c:143 | `NON_MATCH void RotateSprite(struct Sprite* s, s32 angle)` |
| src/sprite2.c:169 | `NON_MATCH void ScalerotSprite(struct Sprite* s, s32 angle)` |
| src/stage/anatre_forest/landscape.c:107 | `NON_MATCH static void FUN_08010444(struct Coord* _ UNUSED)` |
| src/stage/area_x2/landscape.c:182 | `NON_MATCH static void LayerDraw_AreaX2_2(struct StageLayer* l, const struct Stage* stage)` |
| src/stage/entity.c:99 | `NON_MATCH void InitStageEntityManager(u8 stageID, bool8 missionDone)` |
| src/stage/entity.c:1834 | `NON_MATCH static void FUN_08018c00(u8 stageID, u8 area)` |
| src/stage/entity.c:1865 | `NON_MATCH static void FUN_08018d10(u8 stageID, u8 area)` |
| src/stage/spacecraft/landscape.c:679 | `NON_MATCH static void LayerUpdate_SpaceCraft_3(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/spacecraft/landscape.c:696 | `NON_MATCH static void LayerDraw_FixOmegaWhiteCoord(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/sunken_library/update.c:588 | `NON_MATCH struct Coord* getSunkenLibRoomCoord(u8 idx)` |
| src/stage/volcano/landscape.c:344 | `NON_MATCH static void LayerUpdate_VolcanoEruption(struct StageLayer* l, const struct Stage* stage)` |
| src/stagerun.c:136 | `NON_MATCH bool32 OverworldUpdate(bool8 paused)` |
| src/system.c:98 | `NON_MATCH NORETURN void Process_System(struct Process* p)` |
| src/terrain.c:45 | `NON_MATCH void ResetLandscape(s32 stageID, struct Coord* viewport)` |
| src/terrain.c:152 | `NON_MATCH void RestoreBackground(void)` |
| src/terrain.c:336 | `NON_MATCH static void loadStageLandscape(const struct Stage* p, const struct ChunkMap* layout)` |
| src/terrain.c:398 | `NON_MATCH void PatchMetatileMap(u32 x16, u32 y16, struct MetatilePatch* p)` |
| src/terrain.c:428 | `NON_MATCH void LoadScreenIntoMetatileMap(s32 chunkX, s32 chunkY, u16 chunkID)` |
| src/terrain.c:460 | `NON_MATCH void ResetStageLayer(s32 n, const struct Stage* p)` |
| src/terrain.c:564 | `NON_MATCH static const struct Stage* UpdateStageTileset(struct Coord* c)` |
| src/terrain.c:637 | `NON_MATCH static void UpdateStageLayer(struct StageLayer* l, const struct Stage* s, struct Coord* c)` |
| src/vfx/elf_particle.c:600 | `NON_MATCH void FUN_080c021c(struct VFX* vfx)` |
| src/vfx/exlife_indicator.c:55 | `NON_MATCH static void ExlifeIndicator_Update(struct VFX* vfx)` |
| src/vfx/unk_32.c:204 | `NON_MATCH void FUN_080bac5c(struct VFX* p)` |
| src/weapon/buster.c:151 | `NON_MATCH static void initLemonBullet(struct Weapon* w)` |
| src/weapon/minigame_rod.c:43 | `NON_MATCH static void Weapon16_Init(struct Weapon* w)` |
| src/weapon/saber.c:33 | `NON_MATCH struct Weapon* CreateWeaponSaber(struct Zero* z, u8 r1)` |
| src/weapon/saber.c:72 | `NON_MATCH static void Saber_Init(struct Weapon* w)` |
| src/weapon/saber.c:138 | `NON_MATCH static void Saber_Update(struct Weapon* w)` |
| src/weapon/saber.c:220 | `NON_MATCH static void saberAirSlash(struct Weapon* w)` |
| src/weapon/saber.c:276 | `NON_MATCH static void saberChargeAtk(struct Weapon* w)` |
| src/weapon/saber.c:432 | `NON_MATCH static void saberJumpRolling(struct Weapon* w)` |
| src/widget/armor_icons.c:117 | `NON_MATCH static void FUN_080e6ab8(struct Widget* w)` |
| src/widget/armor_icons.c:160 | `NON_MATCH static void FUN_080e6bb8(struct Widget* w)` |
| src/widget/disk_modal_border.c:48 | `NON_MATCH static void DiskModalBorder_Init(struct Widget* w)` |
| src/widget/elf_menu_item.c:51 | `NON_MATCH static void ElfMenuItem_Init(struct Widget* w)` |
| src/widget/exskill.c:39 | `NON_MATCH static void ExIcon_Init(struct Widget* w)` |
| src/widget/unk_01.c:33 | `NON_MATCH static void MenuComp1_Init(struct Widget* p)` |
| src/widget/unk_01.c:60 | `NON_MATCH static void MenuComp1_Update(struct Widget* p)` |
| src/widget/unk_09.c:115 | `NON_MATCH static void FUN_080e7ab0(struct Widget* w)` |
| src/widget/unk_09.c:170 | `NON_MATCH static void FUN_080e7b9c(struct Widget* w)` |
