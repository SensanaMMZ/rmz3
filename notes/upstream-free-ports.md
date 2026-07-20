# Free ports from upstream `mmzret/rmz3` — functions upstream has as C that we don't

**237 functions**, computed {by name-diff} against `upstream/dev` (fetched as the `upstream` remote). Upstream has a real (non-`NAKED`) C body for each; this fork still ships it as raw asm.

## Ported so far (retired from this list)
- `MenuLoop_OpenMenu`, `MenuLoop_BlackOut` — `63332001` (chained-assignment fix; dual-forms dropped)
- `getStageRewardExSkill` — `4df704e8` (the "confirmed wall"; needed only `gGameState.z2`)

## How to use

- Fetch a body from `https://raw.githubusercontent.com/mmzret/rmz3/dev/<upstream path>` (or `git show upstream/dev:<path>`).
- **Signature / struct drift:** upstream uses its own type names (`Player*`/`Object*`, its struct layouts). Adapt types to this fork's structs and **re-verify the ROM SHA** (`make compare` = `rmz3.gba: OK`) after each — a name match is not a guarantee.
- Matched by NAME only, so functions upstream renamed vs our `FUN_<addr>` are NOT counted (this list is a floor, conservative).
- **These are upstream _matches_, not upstream dual-forms.** Upstream DOES use the same `NON_MATCH`/`#if MODERN`/`INCCODE` dual-form escape (106 functions), but this list explicitly **excludes** them — every entry below is a function upstream *byte-matched* (plain C) that we still ship as asm (and its WIP=naked set; 4 WIP false-positives removed → 237). So the section-A entries that are `NON_MATCH` (dual-form) *here* are cases where **upstream found the matching source we gave up on** — porting their exact construction can convert our dual-form into a real match. Proven example: `MenuLoop_BlackOut` — we dual-formed it (palette RGB-fade mask tie); upstream matches it with a **chained** assignment `filter[0] = filter[1] = filter[2] = g->frames;` (assigns filter[2] first, then propagates), which is the store order our separate-statement C couldn't produce. **Ported ✓ (commit 63332001), dual-form dropped.**

- **53 are already stubbed `NAKED`/dual-form in our `src/`** (same signature & location — easiest: drop in the C, rebuild, diff). **188 are not in our `src/` yet** (carved to `asm/` or absent — place them first).


---

## A. Already stubbed `NAKED`/dual-form here (drop-in candidates)


### game (15)
- `ExMenuLoop_Init` — `src/game/menu/exskill.c`
- `GameLoop_CloseMenu` — `src/game/main.c`
- `GameLoop_GameOver` — `src/game/main.c`
- `GameLoop_NewGame` — `src/game/main.c`
- `KcMenuLoop_Init` — `src/game/menu/keyconfig.c`
- `MainMenuFocusLoop_Escape` — `src/game/menu/main.c`
- `MenuExit_ReflectLaser` — `src/game/menu.c`
- `MenuLoop_BlackOut` — `src/game/menu.c`
- `MenuLoop_OpenMenu` — `src/game/menu.c`
- `OverworldLoop_080f3044` — `src/game/main_overworld.c`
- `OverworldLoop_Save_080f3128` — `src/game/main_overworld.c`
- `RestoreGraphicState` — `src/game/main.c`
- `SaveGraphicState` — `src/game/main.c`
- `TrySlideMenu` — `src/game/menu.c`
- `save_080f32f8` — `src/game/main_overworld/manage_save_data.c`

### player (12)
- `HandlePlayerInput_Wall` — `src/player/zero/input/input.c`
- `buster_0` — `src/player/zero/attack/air.c`
- `inWalk` — `src/player/zero/input/input.c`
- `initZeroJump` — `src/player/zero/update.c`
- `setStageElfFlags` — `src/player/zero/util.c`
- `triple_slash_2nd` — `src/player/zero/attack/ground/idle.c`
- `zeroCyberDoor2` — `src/player/zero/update.c`
- `zeroFloat2` — `src/player/zero/update.c`
- `zeroTalk1` — `src/player/zero/update.c`
- `zeroTeleport1` — `src/player/zero/update.c`
- `zeroWallJumpRise` — `src/player/zero/update.c`
- `zero_dash_step1` — `src/player/zero/update.c`

### vfx (4)
- `BatringNecro_Init` — `src/vfx/batring_necro.c`
- `FUN_080ba448` — `src/vfx/unk_30.c`
- `Ghost30_Init` — `src/vfx/unk_30.c`
- `SlashedEnemy_Init` — `src/vfx/slashed_enemy.c`

### bg0 (3)
- `PrintMinigameNumber` — `src/bg0/text.c`
- `setupTextWindow` — `src/bg0/text_window.c`

### camera.c (2)
- `CalcCameraDelta` — `src/camera.c`

### entity.c (2)
- `DrawCollidableEntity` — `src/entity.c`
- `DrawEntity` — `src/entity.c`

### enemy (2)
- `GrandCannon_Init` — `src/enemy/grand_cannon.c`
- `PantheonGuardian_Init` — `src/enemy/pantheon_guardian.c`

### gpu_regs.c (2)
- `LoadBgMap` — `src/gpu_regs.c`
- `loadBgMap_08004248` — `src/gpu_regs.c`

### weapon (2)
- `Rod_Init` — `src/weapon/rod.c`
- `saberSmash` — `src/weapon/saber.c`

### stage (2)
- `SnowyPlains_FreeUpdate` — `src/stage/snowy_plains/update.c`
- `updateSunkenLib` — `src/stage/sunken_library/landscape.c`

### pickup (1)
- `CreateMapDisk` — `src/pickup/disk.c`

### projectile (1)
- `Projectile2_Init` — `src/projectile/unk_02.c`

### terrain.c (1)
- `ShiftMetatile` — `src/terrain.c`

### result.c (1)
- `getStageRewardExSkill` — `src/result.c`

### player.c (1)
- `ladder_08026bb0` — `src/player.c`

### boss (1)
- `setBlazinDirection` — `src/boss/blazin.c`

### solid (1)
- `updatePhantomTeleporter` — `src/solid/phantom_teleporter.c`


---

## B. Not in our `src/` yet (place, then port)


### projectile (27)
- `CreateCopyXSonicBoom` — `src/projectile/copy_x_tackle.c`
- `CreateProjectile28` — `src/projectile/copy_x_28.c`
- `CreateProjectile31` — `src/projectile/blizzack_31.c`
- `CreateProjectile43` — `src/projectile/shellcrawler.c`
- `FUN_080a4f3c` — `src/projectile/unk_20.c`
- `FUN_080a84c4` — `src/projectile/copy_x_shot_normal.c`
- `FUN_080a85a0` — `src/projectile/copy_x_shot_normal.c`
- `FUN_080a8684` — `src/projectile/copy_x_shot_normal.c`
- `FUN_080a8794` — `src/projectile/copy_x_shot_normal.c`
- `FUN_080a9b90` — `src/projectile/copy_x_28.c`
- `FUN_080a9c88` — `src/projectile/copy_x_28.c`
- `FUN_080a9dcc` — `src/projectile/copy_x_28.c`
- `FUN_080aaa80` — `src/projectile/blizzack_32.c`
- `InitNovaStrikeProjectile` — `src/projectile/copy_x_tackle.c`
- `Projectile28_Init_RagingEXCharge` — `src/projectile/copy_x_28.c`
- `Projectile42_Init` — `src/projectile/shotloid.c`
- `Projectile42_Update` — `src/projectile/shotloid.c`
- `UpdateNovaStrikeProjectile` — `src/projectile/copy_x_tackle.c`
- `_Projectile42_Update` — `src/projectile/shotloid.c`
- `_Projectile43_Update` — `src/projectile/shellcrawler.c`
- `blizzack_080aaae0` — `src/projectile/blizzack_32.c`
- `deathtanz_080a0934` — `src/projectile/deathtanz_14.c`
- `deathtanz_080a09a0` — `src/projectile/deathtanz_14.c`
- `deathtanz_080a09f4` — `src/projectile/deathtanz_14.c`
- `initCopyXSlidingSonicBoom` — `src/projectile/copy_x_tackle.c`
- `moveSlidingSonicBoom` — `src/projectile/copy_x_tackle.c`
- `unused_FUN_080ada80` — `src/projectile/unk_37.c`

### enemy (26)
- `CreateClone` — `src/enemy/seimeran.c`
- `CreateOmega1gSword` — `src/enemy/omega1g_sword.c`
- `Enemy14_Update` — `src/enemy/top_gabyoall.c`
- `Enemy59_Init` — `src/enemy/unk_59.c`
- `Enemy63_onCollision` — `src/enemy/unk_63.c`
- `FUN_08073ea8` — `src/enemy/snakecord.c`
- `FUN_08073ef0` — `src/enemy/snakecord.c`
- `FUN_080740e4` — `src/enemy/snakecord.c`
- `FUN_0807415c` — `src/enemy/snakecord.c`
- `FUN_08080c64` — `src/enemy/pantheon_aqua_mod_obj.c`
- `FUN_0808f2e4` — `src/enemy/seimeran.c`
- `FUN_080913c0` — `src/enemy/unk_59.c`
- `FUN_080949d4` — `src/enemy/unk_63.c`
- `FUN_08094a54` — `src/enemy/unk_63.c`
- `FUN_08094bf0` — `src/enemy/unk_63.c`
- `FUN_08094e0c` — `src/enemy/unk_63.c`
- `FUN_08094ea0` — `src/enemy/unk_63.c`
- `Omega1wHand_OnCollision` — `src/enemy/omega1w_hand.c`
- `SnakeCord_onCollision` — `src/enemy/snakecord.c`
- `clr_unk143_hi` — `src/enemy/unk_63.c`
- `createStretchedArms` — `src/enemy/pantheon_aqua_mod_obj.c`
- `createStretchedGrabArm` — `src/enemy/pantheon_aqua_mod_obj.c`
- `initGyroCannonMainBody` — `src/enemy/gyro_cannon.c`
- `initGyroCannonPropeller` — `src/enemy/gyro_cannon.c`
- `set_unk143_lo` — `src/enemy/unk_63.c`

### vfx (20)
- `FUN_080b8804` — `src/vfx/necro.c`
- `FUN_080babac` — `src/vfx/pantheon_aqua.c`
- `FUN_080bac14` — `src/vfx/pantheon_aqua.c`
- `FUN_080baca4` — `src/vfx/pantheon_aqua.c`
- `FUN_080bacec` — `src/vfx/pantheon_aqua.c`
- `FUN_080bad34` — `src/vfx/pantheon_aqua.c`
- `Ghost66_Init` — `src/vfx/unk_66.c`
- `VFX22_Init` — `src/vfx/unk_22.c`
- `VFX67_Update` — `src/vfx/unk_67.c`
- `VFX70_Die` — `src/vfx/unk_70.c`
- `VFX70_Init` — `src/vfx/unk_70.c`
- `VFX70_Update` — `src/vfx/unk_70.c`
- `VFX71_Die` — `src/vfx/mission_info.c`
- `VFX71_Init` — `src/vfx/mission_info.c`
- `VFX71_Update` — `src/vfx/mission_info.c`
- `_VFX70_Die` — `src/vfx/unk_70.c`
- `_VFX70_Init` — `src/vfx/unk_70.c`
- `_ZeroDeathEffect_Init` — `src/vfx/zero_death_effect.c`
- `unused_FUN_080c1bec` — `src/vfx/unk_58.c`
- `unused_FUN_080c1c44` — `src/vfx/unk_58.c`

### bg0 (15)
- `AllocateGlyph` — `src/bg0/text.c`
- `DrawInlineMessageWindow` — `src/bg0/text_window.c`
- `DrawMugshot` — `src/bg0/text_window.c`
- `GetText` — `src/bg0/text_window.c`
- `LoadJISKana` — `src/bg0/text.c`
- `LoadWindowTileData` — `src/bg0/text_window.c`
- `PrintJISString` — `src/bg0/text.c`
- `Unused_GetLineCount` — `src/bg0/text.c`
- `_DrawLeftTime` — `src/bg0/hud.c`
- `_UpdateTextWindow_0_Nop` — `src/bg0/text_window.c`
- `_UpdateTextWindow_1_MugshotMessage` — `src/bg0/text_window.c`
- `_UpdateTextWindow_2_InlineMessage` — `src/bg0/text_window.c`
- `_UpdateTextWindow_3_Unk3` — `src/bg0/text_window.c`
- `shit1` — `src/bg0/text_window.c`
- `shit2` — `src/bg0/text_window.c`

### solid (10)
- `CreateFlyingFish` — `src/solid/flying_fish.c`
- `FUN_080cb3b8` — `src/solid/burning_flame.c`
- `FUN_080cb4c0` — `src/solid/burning_flame.c`
- `FUN_080cb528` — `src/solid/burning_flame.c`
- `FUN_080dc81c` — `src/solid/flying_fish.c`
- `GetWarpDestination1` — `src/solid/phantom_teleporter.c`
- `GetWarpDestination2` — `src/solid/door_3d.c`
- `RenderTask_CyberSpaceDoor` — `src/solid/cyberspace_door.c`
- `Solid3_Init` — `src/solid/burning_flame.c`
- `Solid3_Update` — `src/solid/burning_flame.c`

### weapon (7)
- `BurstShot_Init` — `src/weapon/burst_shot.c`
- `BurstShot_OnCollision` — `src/weapon/burst_shot.c`
- `DeleteFlyingShield` — `src/weapon/shield_fly.c`
- `ElecShieldSweep_OnCollision` — `src/weapon/shield_sweep_elec.c`
- `ElecShieldSweep_Update` — `src/weapon/shield_sweep_elec.c`
- `ReflectLaser_Update` — `src/weapon/reflect_laser.c`
- `Rod_OnCollision` — `src/weapon/rod.c`

### camera.c (7)
- `Camera_GetDistance` — `src/camera.c`
- `Camera_LoadTemplate` — `src/camera.c`
- `Camera_Render` — `src/camera.c`
- `Camera_Reset` — `src/camera.c`
- `Camera_SetMode` — `src/camera.c`
- `Camera_Shake` — `src/camera.c`
- `Camera_Update` — `src/camera.c`

### palette_animation.c (7)
- `PauseAllPaletteAnimations` — `src/palette_animation.c`
- `RemoveAllPaletteAnimations` — `src/palette_animation.c`
- `RemovePaletteAnimation` — `src/palette_animation.c`
- `ResumeAllPaletteAnimations` — `src/palette_animation.c`
- `StepPaletteAnimation` — `src/palette_animation.c`
- `TransferAnimatedPalettesToPaletteBuffer` — `src/palette_animation.c`
- `TransferPalettes` — `src/palette_animation.c`

### cyberelf (6)
- `Elf10_Init` — `src/cyberelf/unk_10.c`
- `Elf11_Init` — `src/cyberelf/unk_11.c`
- `Elf5_Die` — `src/cyberelf/unk_5.c`
- `Elf5_Init` — `src/cyberelf/unk_5.c`
- `MenuExit_CyberElf10` — `src/cyberelf/unk_10.c`
- `elf_080e4bf4` — `src/cyberelf/unk_10.c`

### renderer.c (6)
- `Renderer_Clear` — `src/renderer.c`
- `Renderer_Flush` — `src/renderer.c`
- `Renderer_Init` — `src/renderer.c`
- `Renderer_PrependTask` — `src/renderer.c`
- `Renderer_SendTask` — `src/renderer.c`
- `Renderer_SetPivot` — `src/renderer.c`

### spawn.c (5)
- `ClipSpawnRange` — `src/spawn.c`
- `InitSpawnManager` — `src/spawn.c`
- `RemoveMMBN4Entities` — `src/spawn.c`
- `RemoveZ3EnemyChildEntityForSwapMMBN4Virus` — `src/spawn.c`

### terrain.c (5)
- `LoadChunk` — `src/terrain.c`
- `RenderTask_Overworld` — `src/terrain.c`
- `RestoreTileset` — `src/terrain.c`
- `Unused_GetMetatileID` — `src/terrain.c`
- `getchunk` — `src/terrain.c`

### player (4)
- `CopyPlayerMaxHPChargeOnSkipEventScene` — `src/player/zero/util.c`
- `IsCyberElfUsed` — `src/player/zero/util.c`
- `LoadZeroStatus` — `src/player/zero/util.c`
- `StoreZeroStatus` — `src/player/zero/util.c`

### sound.c (4)
- `FadeOutBGM` — `src/sound.c`
- `PlayBGM` — `src/sound.c`
- `SoundHBlank` — `src/sound.c`
- `SoundVBlank` — `src/sound.c`

### element.c (4)
- `InitElFxManager` — `src/element.c`
- `ReloadElementEffectGraphic` — `src/element.c`
- `RequestElementEffectGraphic` — `src/element.c`
- `UpdateElFxManager` — `src/element.c`

### stage (3)
- `FUN_0800e308` — `src/stage/old_residential/landscape.c`
- `LayerUpdate_SnowyPlains_4` — `src/stage/snowy_plains/landscape.c`
- `nop_08011100` — `src/stage/frostline_ice_base/landscape.c`

### animation.c (3)
- `ResetAnimState` — `src/animation.c`
- `SetAnimSubID` — `src/animation.c`
- `StepAnimState` — `src/animation.c`

### result.c (3)
- `ResultScreen_Init` — `src/result.c`
- `ResultScreen_InitWidget` — `src/result.c`
- `ResultScreen_UpdateAndRenderWidget` — `src/result.c`

### entity_manager.c (3)
- `Unused_ResetEntityHeader` — `src/entity_manager.c`
- `_GetEntityList` — `src/entity_manager.c`
- `_StartEntityListIteration` — `src/entity_manager.c`

### script_command.c (2)
- `Cmd_result_screen` — `src/script_command.c`
- `Cmd_transition` — `src/script_command.c`

### widget (2)
- `CreateSquareCursor` — `src/widget/cursor_square.c`
- `CreateTriangleCursor` — `src/widget/cursor_triangle.c`

### sram.c (2)
- `DeleteSector` — `src/sram.c`
- `ValidateSector` — `src/sram.c`

### story.c (2)
- `LoadStoryData` — `src/story.c`
- `StoreStoryData` — `src/story.c`

### score.c (2)
- `ResetMissionScore` — `src/score.c`
- `unused_08019790` — `src/score.c`

### stagerun.c (2)
- `StageRun_Render` — `src/stagerun.c`
- `StageRun_Update` — `src/stagerun.c`

### sprite.c (2)
- `unused_08004730` — `src/sprite.c`
- `unused_ClearTaskCallback` — `src/sprite.c`

### boss (1)
- `CreateOmega1wHand` — `src/boss/omega1w.c`

### phantom_icon.c (1)
- `CreatePhantomIcon` — `src/phantom_icon.c`

### gpu_regs.c (1)
- `GetHdr` — `src/gpu_regs.c`

### pickup (1)
- `PickupDisk_OnCollision` — `src/pickup/disk.c`

### gfx.c (1)
- `RequestVRAMFill` — `src/gfx.c`

### overworld_layer.c (1)
- `ResetTerrainMapTemplate` — `src/overworld_layer.c`

### script.c (1)
- `RunScript` — `src/script.c`

### enemy.c (1)
- `Unused_08063690` — `src/enemy.c`

### player.c (1)
- `_AppendHazardID` — `src/player.c`
