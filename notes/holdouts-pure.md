# Holdouts that are pure INCCODE stubs (358)

No C body at all -- these need source reconstruction before any
matching work can start. This is what the Ghidra harness is for; see
`tools/ghidra/symbolize_rom.md`.

Regenerate with `python3 tools/classify_holdouts.py`.

## By file

| file | count |
|---|---|
| src/mmbn4.c | 18 |
| src/boss/omega_zero.c | 15 |
| src/player.c | 14 |
| src/overworld_layer.c | 13 |
| src/game/menu/main.c | 12 |
| src/intro.c | 9 |
| src/game/analysis.c | 7 |
| src/physics/pushout.c | 7 |
| src/game/main.c | 6 |
| src/weapon/buster.c | 6 |
| src/cyberelf.c | 5 |
| src/physics/hazard.c | 5 |
| src/player/zero/input/util.c | 5 |
| src/result.c | 5 |
| src/vfx/mission_info.c | 5 |
| src/bg0/text.c | 4 |
| src/player/zero/attack/ladder.c | 4 |
| src/projectile/omega_zero.c | 4 |
| src/sprite.c | 4 |
| src/stage/entity.c | 4 |
| src/boss/glacierle.c | 3 |
| src/boss/hellbat.c | 3 |
| src/boss/megamilpa.c | 3 |
| src/boss/omega_white.c | 3 |
| src/cyberelf/unk_6.c | 3 |
| src/enemy/batring.c | 3 |
| src/enemy/gyro_cannon.c | 3 |
| src/game/menu.c | 3 |
| src/game/menu/elf.c | 3 |
| src/game/menu/keyconfig.c | 3 |
| src/pickup/item.c | 3 |
| src/player/zero/attack/ground/dash.c | 3 |
| src/script_command.c | 3 |
| src/stage/resistance_base/landscape.c | 3 |
| src/vfx/elf_particle.c | 3 |
| src/vfx/ice_effect.c | 3 |
| src/vfx/mission_alert.c | 3 |
| src/vfx/smoke.c | 3 |
| src/bg0/hud.c | 2 |
| src/boss/blazin.c | 2 |
| src/cyberelf/follower.c | 2 |
| src/enemy/childre_obj.c | 2 |
| src/enemy/pantheon_hunter.c | 2 |
| src/enemy/shotcounter.c | 2 |
| src/enemy/shrimpolin.c | 2 |
| src/game/main_overworld/util.c | 2 |
| src/gfx.c | 2 |
| src/link.c | 2 |
| src/player/zero/attack/air.c | 2 |
| src/player/zero/attack/ground/idle.c | 2 |
| src/player/zero/update.c | 2 |
| src/solid/cyberspace_door.c | 2 |
| src/solid/door_3d.c | 2 |
| src/solid/mob_npc.c | 2 |
| src/solid/snowboard.c | 2 |
| src/sram.c | 2 |
| src/stage/anatre_forest/update.c | 2 |
| src/stage/area_x2/landscape.c | 2 |
| src/stage/energy_facility/landscape.c | 2 |
| src/stage/energy_facility/update.c | 2 |
| src/stage/ocean/update.c | 2 |
| src/stage/sunken_library/update.c | 2 |
| src/system.c | 2 |
| src/vfx/unk_78.c | 2 |
| src/vfx/unk_79.c | 2 |
| src/vfx/unk_82.c | 2 |
| src/widget/armor_icons.c | 2 |
| src/widget/unk_13.c | 2 |
| src/bg0/text_window.c | 1 |
| src/boss/copy_x.c | 1 |
| src/boss/deathtanz.c | 1 |
| src/boss/omega_zx.c | 1 |
| src/boss/tretista.c | 1 |
| src/boss/volteel.c | 1 |
| src/camera.c | 1 |
| src/collision.c | 1 |
| src/drop.c | 1 |
| src/element.c | 1 |
| src/enemy/hammer.c | 1 |
| src/enemy/lamplort.c | 1 |
| src/enemy/volcaire.c | 1 |
| src/entity_motion.c | 1 |
| src/game/main_overworld/cmd_room_talk.c | 1 |
| src/game/main_overworld/computer.c | 1 |
| src/game/main_overworld/manage_save_data.c | 1 |
| src/game/main_overworld/sunken_library_search.c | 1 |
| src/game/menu/exskill.c | 1 |
| src/game/minigame.c | 1 |
| src/game/minigame/copy_x.c | 1 |
| src/mission.c | 1 |
| src/palette_animation.c | 1 |
| src/pickup/disk.c | 1 |
| src/player/minigame/copy_x.c | 1 |
| src/player/minigame/fefnir.c | 1 |
| src/player/zero/attack/ground/walk.c | 1 |
| src/player/zero/attack/util.c | 1 |
| src/player/zero/attack/wall.c | 1 |
| src/projectile/blazin.c | 1 |
| src/projectile/lemon.c | 1 |
| src/projectile/omega_white.c | 1 |
| src/projectile/shotcounter_bullet.c | 1 |
| src/script.c | 1 |
| src/solid/actor.c | 1 |
| src/solid/childre_ship.c | 1 |
| src/solid/door_2d_blue.c | 1 |
| src/solid/door_2d_gray_h.c | 1 |
| src/solid/door_2d_gray_v.c | 1 |
| src/solid/icebon.c | 1 |
| src/solid/main_npc.c | 1 |
| src/solid/plant.c | 1 |
| src/solid/sea_level_button.c | 1 |
| src/solid/turtloid_s.c | 1 |
| src/solid/unk_10.c | 1 |
| src/solid/unk_16.c | 1 |
| src/stage/anatre_forest/landscape.c | 1 |
| src/stage/frostline_ice_base/update.c | 1 |
| src/stage/giant_elevator/update.c | 1 |
| src/stage/missile_factory/update.c | 1 |
| src/stage/ocean/landscape.c | 1 |
| src/stage/old_residential/landscape.c | 1 |
| src/stage/old_residential/update.c | 1 |
| src/stage/repair_factory/update.c | 1 |
| src/stage/resistance_base/update.c | 1 |
| src/stage/snowy_plains/update.c | 1 |
| src/stage/spacecraft/landscape.c | 1 |
| src/stage/spacecraft/update.c | 1 |
| src/stage/sub_arcadia/update.c | 1 |
| src/stage/twilight_desert/update.c | 1 |
| src/stage/volcano/update.c | 1 |
| src/stage/weil_labo/update.c | 1 |
| src/syssav.c | 1 |
| src/vfx/after_image.c | 1 |
| src/vfx/ballchain.c | 1 |
| src/vfx/boss_explosion.c | 1 |
| src/vfx/charge_effect.c | 1 |
| src/vfx/flame_effect.c | 1 |
| src/vfx/particle_icicle.c | 1 |
| src/vfx/slashed_enemy.c | 1 |
| src/vfx/small_number.c | 1 |
| src/vfx/snow.c | 1 |
| src/vfx/thunder_effect.c | 1 |
| src/vfx/unk_08.c | 1 |
| src/vfx/unk_17.c | 1 |
| src/vfx/unk_18.c | 1 |
| src/vfx/unk_19.c | 1 |
| src/vfx/unk_31.c | 1 |
| src/vfx/unk_43.c | 1 |
| src/vfx/unk_52.c | 1 |
| src/vfx/unk_83.c | 1 |
| src/vfx/unk_84.c | 1 |
| src/vfx/zero_death_effect.c | 1 |
| src/weapon/reflect_laser.c | 1 |
| src/weapon/shield.c | 1 |
| src/weapon/shield_fly.c | 1 |
| src/widget/disk_icon.c | 1 |
| src/widget/elf_icon.c | 1 |
| src/widget/elf_menu_item.c | 1 |
| src/widget/hp.c | 1 |
| src/widget/subtank.c | 1 |
| src/widget/weapon_icon.c | 1 |

## All

| location | signature |
|---|---|
| src/bg0/hud.c:55 | `NAKED static void drawZeroHPWeaponIcon(void* p)` |
| src/bg0/hud.c:305 | `NAKED static void FUN_080ea3c8(void* p)` |
| src/bg0/text.c:102 | `NAKED void FUN_080e98ec(void)` |
| src/bg0/text.c:432 | `NAKED void unused_080e9d94(s32 r0, u16 r1, u16 r2) { INCCODE("asm/unused/unused_080e9d94.inc"); };` |
| src/bg0/text.c:435 | `NAKED static s32 printStringWithLen(u8 startX, u8 startY, char_t* s, u16 len)` |
| src/bg0/text.c:688 | `NAKED static struct CharTile* getFreeCharTile(u16 styledChar)` |
| src/bg0/text_window.c:297 | `NAKED void text_080eaa7c(struct TextWindowText* t, u16 r1)` |
| src/boss/blazin.c:42 | `NAKED static void Blazin_Init(struct Boss* p)` |
| src/boss/blazin.c:331 | `NAKED static void blazinDeath1(struct Boss* p)` |
| src/boss/copy_x.c:47 | `NAKED static void CopyX_Init(struct Boss* p)` |
| src/boss/deathtanz.c:24 | `NAKED static void calcNextAction(struct Boss* p)` |
| src/boss/glacierle.c:29 | `NAKED static void calcNextGlacierleAction(struct Boss* p)` |
| src/boss/glacierle.c:172 | `NAKED static void Glacierle_Init(struct Boss* p)` |
| src/boss/glacierle.c:538 | `NAKED static void glacierle_08057e20(struct Boss* p)` |
| src/boss/hellbat.c:43 | `NAKED static void Hellbat_Init(struct Boss* p)` |
| src/boss/hellbat.c:274 | `NAKED static void hellbatDeath0(struct Boss* p)` |
| src/boss/hellbat.c:386 | `NAKED static void hellbatDeath1(struct Boss* p)` |
| src/boss/megamilpa.c:23 | `NAKED static void Megamilpa_Init(struct Boss* p)` |
| src/boss/megamilpa.c:205 | `NAKED static void Megamilpa_Die(struct Boss* p)` |
| src/boss/megamilpa.c:348 | `NAKED static void FUN_0803d454(struct Boss* p, u8 r1, u8 r2)` |
| src/boss/omega_white.c:313 | `NAKED static void omegaWhiteLaser(struct Boss* p)` |
| src/boss/omega_white.c:514 | `NAKED static void omegaWhite_0803e520(struct Boss* p)` |
| src/boss/omega_white.c:627 | `NAKED static void omegaWhite_0803e5ec(struct Boss* p)` |
| src/boss/omega_zero.c:334 | `NAKED static void ozMode1(struct Boss* p)` |
| src/boss/omega_zero.c:447 | `NAKED static void ozDash(struct Boss* p)` |
| src/boss/omega_zero.c:590 | `NAKED static void ozDoubleJump1(struct Boss* p)` |
| src/boss/omega_zero.c:837 | `NAKED static void double_charge_wave_2(struct Boss* p)` |
| src/boss/omega_zero.c:941 | `NAKED static void double_charge_wave_3(struct Boss* p)` |
| src/boss/omega_zero.c:1039 | `NAKED static void ozRyuenjin1(struct Boss* p)` |
| src/boss/omega_zero.c:1207 | `NAKED static void ozRyuenjin2(struct Boss* p)` |
| src/boss/omega_zero.c:1345 | `NAKED static void messenkou(struct Boss* p)` |
| src/boss/omega_zero.c:1440 | `NAKED static void rekkoha(struct Boss* p)` |
| src/boss/omega_zero.c:1589 | `NAKED static void arc_blade_1(struct Boss* p)` |
| src/boss/omega_zero.c:1698 | `NAKED static void arc_blade_2(struct Boss* p)` |
| src/boss/omega_zero.c:1801 | `NAKED static void flinched(struct Boss* p)` |
| src/boss/omega_zero.c:1910 | `NAKED static void ozRanbu1(struct Boss* p)` |
| src/boss/omega_zero.c:2026 | `NAKED static void ozRanbu2(struct Boss* p)` |
| src/boss/omega_zero.c:2173 | `NAKED static void ozRanbu3(struct Boss* p)` |
| src/boss/omega_zx.c:65 | `NAKED static void OmegaZX_Init(struct OmegaZX* p)` |
| src/boss/tretista.c:40 | `NAKED static void Tretista_Init(struct Boss* p)` |
| src/boss/volteel.c:43 | `NAKED static void Volteel_Init(struct Boss* p)` |
| src/camera.c:316 | `NAKED static void CameraMode4Callback(struct Camera* camera)` |
| src/collision.c:200 | `NAKED void RegisterScalerotHitbox(struct Body* o, u32 r1, u32 r2)` |
| src/cyberelf.c:57 | `NAKED static struct Entity* unused_080e14d4(u8 r0, struct Entity* e) { INCCODE("asm/unused/unused_080e14d4.inc"); }` |
| src/cyberelf.c:89 | `NAKED bool8 FUN_080e1578(struct Coord* c1, struct Coord* c2, struct Coord* c3, u8* param_4, s16 param_5)` |
| src/cyberelf.c:167 | `NAKED struct Enemy* FUN_080e1608(struct Coord* c)` |
| src/cyberelf.c:274 | `NAKED void FUN_080e16c4(struct Coord* c, struct CollidableEntity* p)` |
| src/cyberelf.c:515 | `NAKED void unlockAllElvesForUltimate(u8* p)` |
| src/cyberelf/follower.c:77 | `NAKED static void FollowerElf_Init(struct Elf* e)` |
| src/cyberelf/follower.c:202 | `NAKED static void FollowerElf_Update(struct Elf* e)` |
| src/cyberelf/unk_6.c:45 | `NAKED static void Elf6_Init(struct Elf* e)` |
| src/cyberelf/unk_6.c:142 | `NAKED static void Elf6_Update(struct Elf* e)` |
| src/cyberelf/unk_6.c:319 | `NAKED static void Elf6_Die(struct Elf* e)` |
| src/drop.c:65 | `NAKED void TryDropZakoDisk(struct Enemy* p, struct Coord* c)` |
| src/element.c:159 | `NAKED struct VFX* ApplyElementEffect(u8 idx, struct Entity* p, const struct Coord* c)` |
| src/enemy/batring.c:45 | `NAKED static void Batring_Init(struct Enemy* p)` |
| src/enemy/batring.c:335 | `NAKED static void Batring_Die(struct Enemy* p)` |
| src/enemy/batring.c:883 | `NAKED static void FUN_080676b0(struct Enemy* p)` |
| src/enemy/childre_obj.c:45 | `NAKED void ExplodeSplitMine(s32 x, s32 y)` |
| src/enemy/childre_obj.c:200 | `NAKED static void ChildreObj_Init(struct Enemy* p)` |
| src/enemy/gyro_cannon.c:111 | `NAKED static void initGyroCannonWithPropeller(struct Enemy* p)` |
| src/enemy/gyro_cannon.c:211 | `NAKED static void gyrocannon_0806d1b4(struct Enemy* p)` |
| src/enemy/gyro_cannon.c:456 | `NAKED static void FUN_0806ddfc(struct Enemy* p)` |
| src/enemy/hammer.c:60 | `NAKED static void Enemy21_Init(struct Enemy* p)` |
| src/enemy/lamplort.c:42 | `NAKED static void Lamplort_Init(struct Enemy* p)` |
| src/enemy/pantheon_hunter.c:53 | `NAKED static void PantheonHunter_Init(struct Enemy* p)` |
| src/enemy/pantheon_hunter.c:267 | `NAKED static void PantheonHunter_Update(struct Enemy* p)` |
| src/enemy/shotcounter.c:41 | `NAKED static void Shotcounter_Init(struct Enemy* p)` |
| src/enemy/shotcounter.c:283 | `NAKED static void Shotcounter_Die(struct Enemy* p)` |
| src/enemy/shrimpolin.c:76 | `NAKED static bool8 shrimporin_080698dc(struct Enemy* p)` |
| src/enemy/shrimpolin.c:197 | `NAKED static void Shrimporin_Init(struct Enemy* p)` |
| src/enemy/volcaire.c:98 | `NAKED static bool8 FUN_08077260(struct Enemy* p)` |
| src/entity_motion.c:200 | `NAKED static void unused_0801785c(struct Entity* p) { INCCODE("asm/unused/unused_0801785c.inc"); }` |
| src/game/analysis.c:33 | `NAKED static void DiskLoop_Init(struct GameState* g)` |
| src/game/analysis.c:272 | `NAKED static void DiskLoop_Run(struct GameState* g)` |
| src/game/analysis.c:672 | `NAKED static void setSecretDiskPalette(struct GameState* g)` |
| src/game/analysis.c:861 | `NAKED static void sd_analysis_080f85e0(struct GameState* g)` |
| src/game/analysis.c:1056 | `NAKED static void sd_analysis_080f875c(struct GameState* g)` |
| src/game/analysis.c:1341 | `NAKED static void sd_analysis_080f8984(struct GameState* g)` |
| src/game/analysis.c:1444 | `NAKED u16 OpenSecretDisk(struct GameState* g, u8 disk_no, bool8 is_result)` |
| src/game/main.c:48 | `NAKED void printSaveDataRowText(s32 idx, u8 rank, u32 playTime, u8 playLaps, u32 mode, u8 y) { INCCODE("asm/todo/printSaveDataRowText.inc"); }` |
| src/game/main.c:63 | `NAKED static void PostProcess_CyberSpaceColorFilter(void)` |
| src/game/main.c:194 | `NAKED static void FUN_080ee328(u32* pal, u32 length, u32 r2, u16* lut)` |
| src/game/main.c:595 | `NAKED static void GameLoop_SwitchCyberSpace(struct GameState* p) { INCCODE("asm/todo/GameLoop_SwitchCyberSpace.inc"); }` |
| src/game/main.c:848 | `NAKED static void GameLoop_UnlockMinigame(struct GameState* p) { INCCODE("asm/todo/GameLoop_UnlockMinigame.inc"); }` |
| src/game/main.c:849 | `NAKED static void GameLoop_SystemSaveScreen(struct GameState* p) { INCCODE("asm/todo/GameLoop_SystemSaveScreen.inc"); }` |
| src/game/main_overworld/cmd_room_talk.c:12 | `NAKED void OverworldLoop_CmdRoomTalk(struct GameState *p)` |
| src/game/main_overworld/computer.c:4 | `NAKED void OverworldLoop_Computer(struct GameState* p)` |
| src/game/main_overworld/manage_save_data.c:7 | `NAKED void OverworldLoop_ManageSaveData(struct GameState *p) { INCCODE("asm/wip/OverworldLoop_ManageSaveData.inc"); }` |
| src/game/main_overworld/sunken_library_search.c:9 | `NAKED void OverworldLoop_SunkenLibrarySearch(struct GameState *p)` |
| src/game/main_overworld/util.c:6 | `NAKED u16 handleWrapTwoChoice(struct GameState* p)` |
| src/game/main_overworld/util.c:140 | `NAKED void PrintSaveDataRow(s32 idx, u8 rank, u32 playTime, u8 playLaps, u32 mode, u8 y)` |
| src/game/menu.c:133 | `NAKED static void MenuLoop_ExitMenu(struct GameState* m)` |
| src/game/menu.c:319 | `NAKED void menu_080f39fc(struct GameState* m)` |
| src/game/menu.c:423 | `NAKED void menu_080f3ab0(struct GameState* m)` |
| src/game/menu/elf.c:324 | `NAKED static void ElfMenuFocusLoop_ElfSelect(struct GameState* g)` |
| src/game/menu/elf.c:858 | `NAKED void FUN_080f70d8(struct GameState* g)` |
| src/game/menu/elf.c:1341 | `NAKED static void printElfMenuDescription(struct GameState* g)` |
| src/game/menu/exskill.c:105 | `NAKED static void ExMenuLoop_Update(struct GameState* g)` |
| src/game/menu/keyconfig.c:56 | `NAKED static void KcMenuLoop_Update(struct GameState *g)` |
| src/game/menu/keyconfig.c:690 | `NAKED void FUN_080f60bc(u16 *p, KEY_INPUT key, u16 r2, u8 r3)` |
| src/game/menu/keyconfig.c:775 | `NAKED void FUN_080f614c(struct GameState *g, u16 *r1)` |
| src/game/menu/main.c:98 | `NAKED static void MainMenuLoop_Init(struct GameState* m)` |
| src/game/menu/main.c:1253 | `NAKED static void MainMenuFocusLoop_NoFocus(struct GameState* g)` |
| src/game/menu/main.c:1426 | `NAKED static void MainMenuFocusLoop_MainWeapon(struct GameState* g)` |
| src/game/menu/main.c:1610 | `NAKED static void MainMenuFocusLoop_SubWeapon(struct GameState* p)` |
| src/game/menu/main.c:1794 | `NAKED static void MainMenuFocusLoop_Subtank(struct GameState* g)` |
| src/game/menu/main.c:2101 | `NAKED static void MainMenuFocusLoop_Head(struct GameState* g)` |
| src/game/menu/main.c:2356 | `NAKED static void MainMenuFocusLoop_Body(struct GameState* g)` |
| src/game/menu/main.c:2643 | `NAKED static void MainMenuFocusLoop_Foot(struct GameState* g)` |
| src/game/menu/main.c:2930 | `NAKED void menu_080f54a0(struct GameState* g)` |
| src/game/menu/main.c:3093 | `NAKED void printMainMenuString(struct GameState* g)` |
| src/game/menu/main.c:3394 | `NAKED u8 CheckUnlockedBody(struct GameState* g, u8 r1)` |
| src/game/menu/main.c:3505 | `NAKED u8 CheckUnlockedFoot(struct GameState* g, u8 r1)` |
| src/game/minigame.c:181 | `NAKED static void MinigameLoop_Main(struct GameState* g)` |
| src/game/minigame/copy_x.c:5 | `NAKED void initCopyXMinigame(struct GameState* g)` |
| src/gfx.c:320 | `NAKED static void FadeWhite(u32* src, u32* dst, u32* fades, u32* mask)` |
| src/gfx.c:325 | `NAKED static void FadeColor(u32* src, u32* dst, u32* fades, u32* mask)` |
| src/intro.c:496 | `NAKED static void InitTitleScreen(struct Intro* p)` |
| src/intro.c:669 | `NAKED static void SelectOnTitle(struct Intro* p) { INCCODE("asm/todo/SelectOnTitle.inc"); }` |
| src/intro.c:708 | `NAKED static u8 intro_080ecd28(struct Intro* p) { INCCODE("asm/todo/intro_080ecd28.inc"); }` |
| src/intro.c:736 | `NAKED static void intro_080ed108(struct Intro* p) { INCCODE("asm/todo/intro_080ed108.inc"); }` |
| src/intro.c:749 | `NAKED static void intro_080ed2a0(struct Intro* p)` |
| src/intro.c:993 | `NAKED static void intro_080ed480(struct Intro* p, u8 step)` |
| src/intro.c:1115 | `NAKED static void FUN_080ed57c(motion_t m, s32 x, s32 y, u16 r3, u8 r4)` |
| src/intro.c:1302 | `NAKED static void intro_080ed770(struct Intro* p, u8 r1)` |
| src/intro.c:1611 | `NAKED static void minigameSelectScript(struct Intro* p)` |
| src/link.c:70 | `NAKED u32 LinkMain1(u8* shouldAdvanceLinkState, u16* sendCmd, u16 (*recvCmds)[CMD_LENGTH])` |
| src/link.c:382 | `NAKED static bool8 DoHandshake(void)` |
| src/mission.c:143 | `NAKED static void calcCodename(void)` |
| src/mmbn4.c:22 | `NAKED static void clearMemory16(void* dst, u32 bytesize)` |
| src/mmbn4.c:42 | `NAKED static void mmbn4_08000738(u32 r0, u32 r1, u32 r2, u32 r3)` |
| src/mmbn4.c:78 | `NAKED static void SioLink_SetTransmitParams(u32 r0, u16 r1, u16 r2)` |
| src/mmbn4.c:93 | `NAKED u32 SioLink_GetLocalPlayerId(void)` |
| src/mmbn4.c:113 | `NAKED bool8 SioLink_GetTransmitFlags(void)` |
| src/mmbn4.c:127 | `NAKED void EReader_CopyReceivedChunk(void)` |
| src/mmbn4.c:168 | `NAKED void EReader_SioBeginCardRead(void)` |
| src/mmbn4.c:191 | `NAKED u16 EReader_SioGetCardId(void)` |
| src/mmbn4.c:216 | `NAKED void EReader_SioInitDataReceive(void)` |
| src/mmbn4.c:245 | `NAKED u8 EReader_SioVerifyCardData(void)` |
| src/mmbn4.c:279 | `NAKED bool8 SioLink_LoadSendCmds(void)` |
| src/mmbn4.c:299 | `NAKED bool8 EReader_ValidateAndStoreCardId(void)` |
| src/mmbn4.c:324 | `NAKED u8 EReader_SioCheckAllPlayersConnected(void)` |
| src/mmbn4.c:390 | `NAKED void FUN_0800165c(u16 param_1, u16 param_2, u16 param_3)` |
| src/mmbn4.c:405 | `NAKED void FUN_08001670(u16 param_1, u16 param_2, u16 param_3)` |
| src/mmbn4.c:421 | `NAKED void* FUN_08001690(u32 r0)` |
| src/mmbn4.c:457 | `NAKED static void* mmbn4_080016c8(void* r0)` |
| src/mmbn4.c:523 | `NAKED static void sio_08001748(void)` |
| src/overworld_layer.c:16 | `NAKED void FUN_080050b0(struct LayerGraphic* l, struct Coord* c, u32 mapAddr)` |
| src/overworld_layer.c:655 | `NAKED static void unused_08005584(struct LayerGraphic* r0, struct Coord* c, u32 mapAddr) { INCCODE("asm/unused/unused_08005584.inc"); }` |
| src/overworld_layer.c:656 | `NAKED static void unused_080055e8(struct LayerGraphic* r0, struct Coord* c, u32 mapAddr) { INCCODE("asm/unused/unused_080055e8.inc"); }` |
| src/overworld_layer.c:657 | `NAKED static void unused_08005674(struct LayerGraphic* r0, struct Coord* c, u32 mapAddr) { INCCODE("asm/unused/unused_08005674.inc"); }` |
| src/overworld_layer.c:660 | `NAKED void FUN_08005a70(struct LayerGraphic* l, struct Coord* c, u32 mapAddr)` |
| src/overworld_layer.c:1036 | `NAKED static void unused_08005d34(void) { INCCODE("asm/unused/unused_08005d34.inc"); }` |
| src/overworld_layer.c:1037 | `NAKED static void unused_080061a4(void) { INCCODE("asm/unused/unused_080061a4.inc"); }` |
| src/overworld_layer.c:1038 | `NAKED static void unused_08006474(void) { INCCODE("asm/unused/unused_08006474.inc"); }` |
| src/overworld_layer.c:1039 | `NAKED static void unused_08006738(void) { INCCODE("asm/unused/unused_08006738.inc"); }` |
| src/overworld_layer.c:1062 | `NAKED void FUN_08006a10(struct LayerGraphic* l, struct Coord* c, u32* bgmap, MetatileMap* mm)` |
| src/overworld_layer.c:1201 | `NAKED void FUN_08006bb4(struct LayerGraphic* l, struct Coord* c, u32* bgmap, MetatileMap* mm)` |
| src/overworld_layer.c:1453 | `NAKED static u8 unused_08006dcc(void* p, struct Coord* c) { INCCODE("asm/unused/unused_08006dcc.inc"); }` |
| src/overworld_layer.c:1455 | `NAKED static u8 unused_08006e3c(void* p, u32 unk_x, u32 unk_y) { INCCODE("asm/unused/unused_08006e3c.inc"); }  // unk_x, unk_y の単位不明(pixel?)` |
| src/palette_animation.c:112 | `NAKED void StartPaletteAnimation(u16 blinkID, u16 ofs)` |
| src/physics/hazard.c:7 | `NAKED metatile_attr_t GetHazardMetatileAttr(s32 x, s32 y)` |
| src/physics/hazard.c:187 | `NAKED s32 FUN_0800af30(s32 x, s32 y, s32 r2)` |
| src/physics/hazard.c:191 | `NAKED s32 FUN_0800afd4(s32 x, s32 y1, s32 y2)` |
| src/physics/hazard.c:292 | `NAKED s32 FUN_0800b08c(s32 x, s32 y1, s32 y2)` |
| src/physics/hazard.c:392 | `NAKED s32 FUN_0800b144(s32 x, s32 y1, s32 y2)` |
| src/physics/pushout.c:248 | `NAKED s32 PushoutToRight2(s32 x, s32 y)` |
| src/physics/pushout.c:348 | `NAKED s32 FUN_08009f6c(s32 x, s32 y)` |
| src/physics/pushout.c:473 | `NAKED s32 FUN_0800a05c(s32 x, s32 y)` |
| src/physics/pushout.c:587 | `NAKED s32 FUN_0800a134(s32 x, s32 y)` |
| src/physics/pushout.c:717 | `NAKED s32 FUN_0800a22c(s32 x, s32 y)` |
| src/physics/pushout.c:842 | `NAKED s32 FUN_0800a31c(s32 x, s32 y)` |
| src/physics/pushout.c:1009 | `NAKED s32 isStageBlocking(s32 start, s32 x, s32 y) { INCCODE("asm/todo/isStageBlocking.inc"); }` |
| src/pickup/disk.c:93 | `NAKED static void MapDisk_Update(struct Pickup* p)` |
| src/pickup/item.c:23 | `NAKED struct Entity* CreatePickupItem(u8 itemID, struct Coord* c, u8 param_3)` |
| src/pickup/item.c:130 | `NAKED static void MapItem_Init(struct Pickup* p)` |
| src/pickup/item.c:320 | `NAKED static void MapItem_Update(struct Pickup* p)` |
| src/player.c:449 | `NAKED metatile_attr_t PushoutByFloor1(struct Zero* z, const struct Rect* p, bool8 r2)` |
| src/player.c:1082 | `NAKED metatile_attr_t PushoutByCeiling(struct Zero* z, const struct Rect* p, bool8 r2)` |
| src/player.c:1252 | `NAKED metatile_attr_t PushoutByCeilingOnLadder(struct Zero* z, const struct Rect* p, bool8 r2)` |
| src/player.c:1420 | `NAKED metatile_attr_t PushoutByFloor2(struct Zero* z, const struct Rect* p, bool8 checkOnly)` |
| src/player.c:1806 | `NAKED u8 zero_08026970(struct Zero* z, const struct Rect* p, bool8 _)` |
| src/player.c:2367 | `NAKED u8 RecoilFromHazards(struct Zero* z, const struct Rect* range)` |
| src/player.c:2373 | `NAKED static metatile_attr_t _pushoutHazardX2(struct Zero* z, s32 x, s32 y, struct Coord* c)` |
| src/player.c:3038 | `NAKED static s32 hazard_0802802c(struct Zero* z, s32 x, s32 y)` |
| src/player.c:3165 | `NAKED static s32 hazard_08028114(struct Zero* z, s32 x, s32 y)` |
| src/player.c:3339 | `NAKED static bool16 hazard_08028338(struct Zero* z, s32 x, s32 y)` |
| src/player.c:3483 | `NAKED static u8 hazard_0802855c(struct Zero* z, s32 x, s32 y)` |
| src/player.c:3605 | `NAKED u8 RecoilFromFloor(struct Zero* z, const struct Rect* range)` |
| src/player.c:4327 | `NAKED bool8 unused_08028bcc(struct Zero* z, const struct Rect* range) { INCCODE("asm/unused/unused_08028bcc.inc"); }` |
| src/player.c:4399 | `NAKED bool8 TryGroundDash(struct Zero* z, const struct Rect* range)` |
| src/player/minigame/copy_x.c:199 | `NAKED static void Update2_2(struct Zero* z)` |
| src/player/minigame/fefnir.c:150 | `NAKED static void fefnir_080347f0(struct Zero* z)` |
| src/player/zero/attack/air.c:478 | `NAKED static void handle_rod_input(struct Zero* z)` |
| src/player/zero/attack/air.c:754 | `NAKED static void handle_shield_input(struct Zero* z)` |
| src/player/zero/attack/ground/dash.c:28 | `NAKED static void dash_saber_1(struct Zero* z)` |
| src/player/zero/attack/ground/dash.c:419 | `NAKED static void gale_attack(struct Zero* z)` |
| src/player/zero/attack/ground/dash.c:604 | `NAKED static void dash_rolling_saber(struct Zero* z)` |
| src/player/zero/attack/ground/idle.c:548 | `NAKED static void handle_rod_input(struct Zero* z)` |
| src/player/zero/attack/ground/idle.c:911 | `NAKED static void shield_0(struct Zero* z)` |
| src/player/zero/attack/ground/walk.c:320 | `NAKED static void walk_shield_0(struct Zero* z)` |
| src/player/zero/attack/ladder.c:425 | `NAKED static void FUN_08031698(struct Zero* z)` |
| src/player/zero/attack/ladder.c:578 | `NAKED static void charge_rod(struct Zero* z)` |
| src/player/zero/attack/ladder.c:708 | `NAKED static void onShield(struct Zero* z)` |
| src/player/zero/attack/ladder.c:835 | `NAKED static void handle_shield_input(struct Zero* z)` |
| src/player/zero/attack/util.c:210 | `NAKED struct Weapon* CreateBuster(struct Zero* z, s32 x, s32 y, bool8 isDirRight)` |
| src/player/zero/attack/wall.c:428 | `NAKED static void handle_shield_input(struct Zero* z)` |
| src/player/zero/input/util.c:56 | `NAKED void HandlePlayerInput(struct Zero* z)` |
| src/player/zero/input/util.c:1350 | `NAKED static bool32 ultimate_command_080339a8(struct Zero* z)` |
| src/player/zero/input/util.c:1521 | `NAKED static bool32 ultimate_command_08033ad8(struct Zero* z)` |
| src/player/zero/input/util.c:1748 | `NAKED static bool32 ultimate_command_08033c8c(struct Zero* z)` |
| src/player/zero/input/util.c:1902 | `NAKED static bool32 ultimate_command_08033da0(struct Zero* z)` |
| src/player/zero/update.c:1710 | `NAKED static void zeroMode7Phase1(struct Zero* z)` |
| src/player/zero/update.c:1881 | `NAKED static void zeroMode7Phase2(struct Zero* z)` |
| src/projectile/blazin.c:100 | `NAKED static void Projectile9_Init(struct Projectile* p)` |
| src/projectile/lemon.c:45 | `NAKED static struct Projectile* unused_0809ca34(struct Coord* c, s32 r1, u8 r2) { INCCODE("asm/unused/unused_0809ca34.inc"); }` |
| src/projectile/omega_white.c:61 | `NAKED static void OmegaWhiteProjectile_Init(struct Projectile* p)` |
| src/projectile/omega_zero.c:263 | `NAKED static void Messenkou_Update(struct Projectile* p)` |
| src/projectile/omega_zero.c:268 | `NAKED static void ArcBlade_Update(struct Projectile* p)` |
| src/projectile/omega_zero.c:273 | `NAKED static void Rekkoha_Update(struct Projectile* p)` |
| src/projectile/omega_zero.c:473 | `NAKED static void DoubleChargeWave2_Update(struct Projectile* p)` |
| src/projectile/shotcounter_bullet.c:42 | `NAKED static void ShotcounterBullet_Init(struct Projectile* p)` |
| src/result.c:60 | `NAKED bool32 result_0802400c(struct ResultState* p)` |
| src/result.c:398 | `NAKED static bool32 printPlayerAllScore(struct ResultState* p)` |
| src/result.c:1061 | `NAKED static bool32 FUN_080248f0(struct ResultState* p)` |
| src/result.c:1264 | `NAKED static void printNumOnResultScreen(s32 n, u8 x, u8 y)` |
| src/result.c:1414 | `NAKED static void PrintCodeName2(struct ResultState* p)` |
| src/script.c:269 | `NAKED static void _RenderWipeZ(struct VM* vm)` |
| src/script_command.c:613 | `NAKED static bool32 Cmd_scroll(struct VM* vm)` |
| src/script_command.c:1373 | `NAKED static void FUN_080237c4(u32 r0, s32 x, s32 y, u16 r3)` |
| src/script_command.c:1484 | `NAKED static bool32 Cmd_cutscene(struct VM* vm)` |
| src/solid/actor.c:890 | `NAKED static void initActor8(struct Solid* p)` |
| src/solid/childre_ship.c:26 | `NAKED void ChildreShip_CreateBubbles(s32 x, s32 y)` |
| src/solid/cyberspace_door.c:32 | `NAKED static void CyberSpaceDoor_Init(struct Solid* p)` |
| src/solid/cyberspace_door.c:193 | `NAKED static void FUN_080dbbd4(struct Solid* p)` |
| src/solid/door_2d_blue.c:150 | `NAKED static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED)` |
| src/solid/door_2d_gray_h.c:66 | `NAKED void FUN_080d7e5c(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED)` |
| src/solid/door_2d_gray_v.c:60 | `NAKED static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED)` |
| src/solid/door_3d.c:57 | `NAKED static void Door3D_Init(struct Solid* p)` |
| src/solid/door_3d.c:357 | `NAKED static void FUN_080cd354(struct Solid* p)` |
| src/solid/icebon.c:66 | `NAKED static void Icebon_Init(struct Solid* p)` |
| src/solid/main_npc.c:111 | `NAKED static void UpdateCiel(struct Solid* p) { INCCODE("asm/wip/UpdateCiel.inc"); }` |
| src/solid/mob_npc.c:38 | `NAKED static void MobNPC_Init(struct Solid* p)` |
| src/solid/mob_npc.c:192 | `NAKED static void FUN_080d95f8(struct Solid* p)` |
| src/solid/plant.c:24 | `NAKED static void ModPlant_Init(struct Solid* p)` |
| src/solid/sea_level_button.c:60 | `NAKED static void SeaLevelButton_Update(struct Solid* p)` |
| src/solid/snowboard.c:22 | `NAKED bool8 FUN_080cf428(struct Solid* p)` |
| src/solid/snowboard.c:289 | `NAKED static void Solid18_Init(struct Solid* p)` |
| src/solid/turtloid_s.c:226 | `NAKED static void FUN_080d85b4(struct Solid* p)` |
| src/solid/unk_10.c:68 | `NAKED static void Solid10_Die(struct Solid* p)` |
| src/solid/unk_16.c:117 | `NAKED static void FUN_080cefb4(struct Body* body, struct Coord* c1, struct Coord* c2)` |
| src/sprite.c:152 | `NAKED void TaskCB_SetMetaspriteTileNum1(struct Sprite* s, struct DrawPivot* r1)` |
| src/sprite.c:406 | `NAKED void TaskCB_SetMetaspriteTileNum2(struct Sprite* s, struct DrawPivot* r1)` |
| src/sprite.c:660 | `NAKED void createPhantomIcon(struct Sprite* s, struct MetaspriteHeader* sprites, u32 r2, u16 tilenum) { INCCODE("asm/todo/createPhantomIcon.inc"); }` |
| src/sprite.c:663 | `NAKED void phantom_minigame_08004d80(struct Sprite* s, s32 param_2) { INCCODE("asm/todo/phantom_minigame_08004d80.inc"); }` |
| src/sram.c:106 | `NAKED void saveSram(struct SramState* s)` |
| src/sram.c:110 | `NAKED void loadSram(struct SramState* s)` |
| src/stage/anatre_forest/landscape.c:221 | `NAKED static void LayerDraw_AnatreForest_4(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/anatre_forest/update.c:4 | `NAKED s16 AnatreForest_MissionUpdate(struct StageRun* p)` |
| src/stage/anatre_forest/update.c:305 | `NAKED s16 AnatreForest_FreeUpdate(struct StageRun* p)` |
| src/stage/area_x2/landscape.c:220 | `NAKED static void LayerDraw_3(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/area_x2/landscape.c:502 | `NAKED static void LayerUpdate_6(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/energy_facility/landscape.c:150 | `NAKED static void FUN_08012148(struct Coord* _ UNUSED)` |
| src/stage/energy_facility/landscape.c:708 | `NAKED static void LayerDraw_3(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/energy_facility/update.c:4 | `NAKED s16 EnergyFacility_MissionUpdate(struct StageRun* p)` |
| src/stage/energy_facility/update.c:687 | `NAKED s16 EnergyFacility_FreeUpdate(struct StageRun* p)` |
| src/stage/entity.c:126 | `NAKED void UpdateStageEntities(struct Coord* viewport)` |
| src/stage/entity.c:1373 | `NAKED static void FUN_08018848(u8 stageID, u8 area)` |
| src/stage/entity.c:1898 | `NAKED static void FUN_08018e20(void)` |
| src/stage/entity.c:2100 | `NAKED static void FUN_08018fa0(void)` |
| src/stage/frostline_ice_base/update.c:4 | `NAKED s16 IceBase_MissionUpdate(struct StageRun* p)` |
| src/stage/giant_elevator/update.c:18 | `NAKED s16 GiantElevator_MissionUpdate(struct StageRun* p)` |
| src/stage/missile_factory/update.c:4 | `NAKED s16 MissileFactory_MissionUpdate(struct StageRun* p)` |
| src/stage/ocean/landscape.c:47 | `NAKED static void ocean_0800cbe8(struct Coord* _ UNUSED)` |
| src/stage/ocean/update.c:22 | `NAKED s16 Ocean_MissionUpdate(struct StageRun* p)` |
| src/stage/ocean/update.c:793 | `NAKED s16 Ocean_FreeUpdate(struct StageRun* p)` |
| src/stage/old_residential/landscape.c:263 | `NAKED static void LayerDraw_6(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/old_residential/update.c:4 | `NAKED s16 OldResidential_MissionUpdate(struct StageRun* p)` |
| src/stage/repair_factory/update.c:14 | `NAKED s16 RepairFactory_MissionUpdate(struct StageRun* p)` |
| src/stage/resistance_base/landscape.c:118 | `NAKED static void rbase_08016390(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/resistance_base/landscape.c:456 | `NAKED static void rbase_08016940(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/resistance_base/landscape.c:632 | `NAKED static void rbase_08016ab8(struct StageLayer* l, const struct Stage* _ UNUSED)` |
| src/stage/resistance_base/update.c:10 | `NAKED s16 ResistanceBase_Update(struct StageRun* p)` |
| src/stage/snowy_plains/update.c:4 | `NAKED s16 SnowyPlains_MissionUpdate(struct StageRun* p)` |
| src/stage/spacecraft/landscape.c:97 | `NAKED static void LayerDraw_OutsideScroll(struct StageLayer* p, const struct Stage* _ UNUSED)` |
| src/stage/spacecraft/update.c:4 | `NAKED s16 SpaceCraft_MissionUpdate(struct StageRun* p)` |
| src/stage/sub_arcadia/update.c:4 | `NAKED s16 SubArcadia_MissionUpdate(struct StageRun* p)` |
| src/stage/sunken_library/update.c:29 | `NAKED s16 SunkenLib_MissionUpdate(struct StageRun* p)` |
| src/stage/sunken_library/update.c:627 | `NAKED void calcSunkenLibDiskRoom(void)` |
| src/stage/twilight_desert/update.c:4 | `NAKED s16 TwilightDesert_MissionUpdate(struct StageRun* p)` |
| src/stage/volcano/update.c:22 | `NAKED s16 Volcano_MissionUpdate(struct StageRun* p)` |
| src/stage/weil_labo/update.c:4 | `NAKED s16 WeilLabo_MissionUpdate(struct StageRun* p)` |
| src/syssav.c:70 | `NAKED void ToggleMods(mod_t id)` |
| src/system.c:221 | `NAKED void InitIntrHandlers(void)` |
| src/system.c:401 | `NAKED static void runDMA0(void)` |
| src/vfx/after_image.c:97 | `NAKED static void AfterImage_Update(struct VFX* p)` |
| src/vfx/ballchain.c:95 | `NAKED static void FUN_080bbe24(struct BallChain* p)` |
| src/vfx/boss_explosion.c:127 | `NAKED static void FUN_080c7cc0(struct VFX* p)` |
| src/vfx/charge_effect.c:52 | `NAKED static void ChargeEffect_Update(struct VFX* vfx)` |
| src/vfx/elf_particle.c:45 | `NAKED struct VFX* FUN_080bfce8(struct Coord* c, u8 r1)` |
| src/vfx/elf_particle.c:139 | `NAKED struct VFX* FUN_080bfd98(struct Coord* c, u8 param2, u8 param3)` |
| src/vfx/elf_particle.c:292 | `NAKED static void ElfParticle_Init(struct VFX* vfx)` |
| src/vfx/flame_effect.c:52 | `NAKED static void FlameEffect_Update(struct VFX* p)` |
| src/vfx/ice_effect.c:34 | `NAKED static void IceEffect_Init(struct VFX* p)` |
| src/vfx/ice_effect.c:170 | `NAKED static void IceEffect_Update(struct VFX* p)` |
| src/vfx/ice_effect.c:358 | `NAKED static void IceEffect_Die(struct VFX* p)` |
| src/vfx/mission_alert.c:162 | `NAKED static void TaskCB_Unk080b5890(struct Sprite* p, struct DrawPivot* _ UNUSED)` |
| src/vfx/mission_alert.c:501 | `NAKED static void TaskCB_Unk080b5b90(struct Sprite* p, struct DrawPivot* _ UNUSED)` |
| src/vfx/mission_alert.c:1187 | `NAKED static void updateGameOverTile(struct Sprite* p, struct DrawPivot* _ UNUSED)` |
| src/vfx/mission_info.c:33 | `NAKED struct VFX* CreateStageBossMugshots(void* p)` |
| src/vfx/mission_info.c:380 | `NAKED static void updateBossMugshot(struct VFX* p)` |
| src/vfx/mission_info.c:913 | `NAKED static void FUN_080c647c(struct VFX* p)` |
| src/vfx/mission_info.c:1088 | `NAKED static void updateMissionPoint(struct VFX* p)` |
| src/vfx/mission_info.c:1259 | `NAKED static void FUN_080c6778(struct VFX* g)` |
| src/vfx/particle_icicle.c:70 | `NAKED static void FUN_080c0ff4(struct Entity* p)` |
| src/vfx/slashed_enemy.c:151 | `NAKED static void FUN_080b6744(struct Ghost16* p)` |
| src/vfx/small_number.c:20 | `NAKED bool8 CreateSmallNumber(s32 x, s32 y, u8 value)` |
| src/vfx/smoke.c:40 | `NAKED static struct Entity* unused_080b2a68(u8 kind, struct Coord* c, bool8 xflip, bool8 yflip) { INCCODE("asm/unused/unused_080b2a68.inc"); }` |
| src/vfx/smoke.c:42 | `NAKED struct Entity* FUN_080b2b40(u8 kind, struct Coord* c, u16 r2, bool16 isDirRight)` |
| src/vfx/smoke.c:162 | `NAKED struct Entity* FUN_080b2c28(motion_t m, struct Coord* c, bool8 xflip, bool8 yflip)` |
| src/vfx/snow.c:37 | `NAKED static void Snow_Init(struct VFX* p)` |
| src/vfx/thunder_effect.c:42 | `NAKED static void Ghost9_Update(struct VFX* p)` |
| src/vfx/unk_08.c:45 | `NAKED static void Ghost8_Init(struct VFX* p)` |
| src/vfx/unk_17.c:94 | `NAKED static void FUN_080b6970(struct VFX* p)` |
| src/vfx/unk_18.c:62 | `NAKED static void Ghost18_Update(struct VFX* p)` |
| src/vfx/unk_19.c:123 | `NAKED static void FUN_080b705c(struct VFX* p)` |
| src/vfx/unk_31.c:94 | `NAKED static void FUN_080ba6a4(struct VFX* p)` |
| src/vfx/unk_43.c:68 | `NAKED static void FUN_080be72c(struct Entity* p)` |
| src/vfx/unk_52.c:48 | `NAKED static void VFX52_Update(struct Entity* p)` |
| src/vfx/unk_78.c:131 | `NAKED static void FUN_080c8acc(struct VFX* p)` |
| src/vfx/unk_78.c:284 | `NAKED static void FUN_080c8c00(struct VFX* p)` |
| src/vfx/unk_79.c:21 | `NAKED void CreateGhost79_1(s32 x, s32 y, struct Entity* p, void* param_4, void* param_5, void* param_6, u8 param_7)` |
| src/vfx/unk_79.c:231 | `NAKED static void FUN_080c9044(struct VFX* p)` |
| src/vfx/unk_82.c:115 | `NAKED static void FUN_080c980c(struct VFX* p)` |
| src/vfx/unk_82.c:225 | `NAKED static void FUN_080c98e8(struct VFX* p)` |
| src/vfx/unk_83.c:103 | `NAKED static void TaskCB_080c9b4c(struct Sprite* p, struct DrawPivot* _)` |
| src/vfx/unk_84.c:94 | `NAKED static void FUN_080c9d20(struct Sprite* p, struct DrawPivot* _)` |
| src/vfx/zero_death_effect.c:25 | `NAKED void CreateFirework(s32 x, s32 y, bool8 r2)` |
| src/weapon/buster.c:24 | `NAKED void MenuExit_Buster(struct Weapon* w) { INCCODE("asm/todo/MenuExit_Buster.inc"); }` |
| src/weapon/buster.c:283 | `NAKED static void initFullBullet(struct Weapon* w)` |
| src/weapon/buster.c:442 | `NAKED static void initLaserShot(struct Weapon* w)` |
| src/weapon/buster.c:763 | `NAKED static void LaserShot_Main(struct Weapon* w)` |
| src/weapon/buster.c:1176 | `NAKED static void BurstShot_Main(struct Weapon* w)` |
| src/weapon/buster.c:1502 | `NAKED static bool8 buster_08037f78(struct Weapon* w, const struct Rect* size)` |
| src/weapon/reflect_laser.c:92 | `NAKED static struct Weapon* unused_CreateReflectLaser(struct Zero* z, struct Entity* p, void* r2, u8 r3, u8 r4) { INCCODE("asm/unused/unused_CreateReflectLaser.inc"); }` |
| src/weapon/shield.c:97 | `NAKED static void ShieldGuard_Update(struct Weapon* w)` |
| src/weapon/shield_fly.c:19 | `NAKED void MenuExit_ShieldFly(struct Weapon* w) { INCCODE("asm/todo/MenuExit_ShieldFly.inc"); }` |
| src/widget/armor_icons.c:191 | `NAKED static void FUN_080e6c94(struct Widget* w)` |
| src/widget/armor_icons.c:560 | `NAKED static void FUN_080e6f6c(struct Widget* w)` |
| src/widget/disk_icon.c:46 | `NAKED static void DiskIcon_Update(struct Widget* w)` |
| src/widget/elf_icon.c:50 | `NAKED static void ElfIcon_Update(struct Widget* w)` |
| src/widget/elf_menu_item.c:80 | `NAKED static void ElfMenuItem_Update(struct Widget* w)` |
| src/widget/hp.c:53 | `NAKED static void MenuHP_Update(struct Widget* w)` |
| src/widget/subtank.c:48 | `NAKED static void SubtankIcon_Update(struct Widget* w)` |
| src/widget/unk_13.c:66 | `NAKED static void MenuComp13_Init(struct Widget* w)` |
| src/widget/unk_13.c:553 | `NAKED static void MenuComp13_Update(struct Widget* w)` |
| src/widget/weapon_icon.c:77 | `NAKED static void MenuWeapon_Update(struct Widget* w)` |
