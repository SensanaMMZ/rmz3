# Duplicate scan over the ROM (5834 functions, 1030018 bytes)

Regenerate with `python3 tools/dup_scan.py`. A holdout in a
cluster with a matched function is a candidate free match:
reuse the matched body, then map callees/globals from the
holdout's own relocations (`tools/fnbytes.py` verifies).

## Byte-identical (3 clusters) — identical including call offsets and pool words

(1 trivial clusters under 8 bytes omitted: 2 unmatched nop-class functions)

- **solve-one-get-2** (52 B): holdouts `FUN_080e964c`*; asm `FUN_0803a5c8`
- **solve-one-get-2** (84 B): asm `FUN_08093afc`, `FUN_080950d0`
- **solve-one-get-3** (108 B): holdouts `FUN_080e58bc`*; asm `FUN_080e2510`, `FUN_080e2b78`

## Identical modulo call targets (27 clusters) — bl offset bits masked; everything else identical

- **solve-one-get-2** (56 B): asm `FUN_080939e8`, `FUN_08094fa8`
- **FREE via C twin** (72 B): asm `FUN_080c2124`; C `FUN_080b9494`
- **FREE via C twin** (76 B): asm `FUN_08068ebc`; C `FUN_08068e64`
- **FREE via C twin** (84 B): asm `FUN_0803a574`; C `CalcAngle`
- **solve-one-get-2** (84 B): asm `FUN_080b94dc`, `FUN_080c216c`
- **FREE via C twin** (84 B): asm `FUN_080c3678`; C `FUN_080b6b8c`
- **solve-one-get-2** (92 B): asm `FUN_0807d724`, `gallisni_080870bc`
- **solve-one-get-2** (96 B): asm `FUN_08093a98`, `FUN_08095014`
- **solve-one-get-2** (96 B): asm `FUN_080c182c`, `FUN_080c188c`
- **solve-one-get-2** (96 B): asm `snowyPlains_08012fec`, `snowyplains_0801320c`
- **solve-one-get-2** (96 B): asm `FUN_080ab724`, `FUN_080ab990`
- **solve-one-get-2** (104 B): asm `FUN_08013dd4`, `FUN_08016018`
- **solve-one-get-2** (112 B): asm `FUN_080c6c60`, `FUN_080c7250`
- **solve-one-get-5** (116 B): holdouts `_zeroTryAttack`*, `FUN_0802e338`*, `air1`*, `zero_wall_080303d4`*, `zero_ladder_08030ee0`*
- **solve-one-get-2** (120 B): asm `FUN_080da114`, `FUN_080da41c`
- **solve-one-get-4** (120 B): asm `FUN_080da21c`, `FUN_080da320`, `FUN_080da5e8`, `FUN_080da6f0`
- **solve-one-get-2** (124 B): asm `FUN_080da01c`, `FUN_080da500`
- **FREE via C twin** (136 B): asm `doGoldOmega1Laser1`; C `doOmega1BallLaser1`
- **FREE via C twin** (140 B): asm `FUN_080acb54`; C `FUN_0809da14`
- **solve-one-get-2** (152 B): asm `FUN_08099ce4`, `FUN_08099d88`
- **solve-one-get-2** (184 B): asm `FUN_080b9cf8`, `FUN_080b9db0`
- **solve-one-get-2** (208 B): asm `FUN_080b963c`, `FUN_080c2294`
- **solve-one-get-2** (216 B): asm `SeaOtterElf_Init`, `BirdElf_Init`
- **FREE via C twin** (232 B): holdouts `Ghost28_Init`; asm `Ghost66_Init`; C `VFX59_Init`
- **FREE via C twin** (232 B): asm `VFX46_Init`; C `VFX41_Init`
- **FREE via C twin** (232 B): asm `Ghost22_Init`; C `VFX38_Init`
- **solve-one-get-2** (244 B): asm `FUN_080c2500`, `FUN_080c25f4`

## Identical modulo calls and pool literals (47 clusters) — bl bits and address-like pool words masked

- **solve-one-get-2** (36 B): asm `FUN_08000994`, `FUN_08000c64`
- **FREE via C twin** (36 B): asm `zeroMinigame`, `harpuiaMinigame`; C `copyXMinigame`
- **FREE via C twin** (56 B): asm `tilecannon_08078210`, `pBase_0808a210`; C `FUN_0807fdf8`, `FUN_080847b8`
- **FREE via C twin** (72 B): asm `FUN_080c2124`; C `FUN_080b9494`
- **FREE via C twin** (76 B): asm `FUN_08068ebc`; C `FUN_08068e64`
- **solve-one-get-2** (76 B): asm `FUN_0806e704`, `FUN_0807d810`
- **FREE via C twin** (76 B): asm `gallisni_080871b4`, `FUN_08093be0`, `FUN_080951b4`; C `shrimporin_08069994`
- **solve-one-get-2** (84 B): asm `FUN_080b94dc`, `FUN_080c216c`
- **FREE via C twin** (84 B): asm `FUN_080c3678`; C `FUN_080b6b8c`
- **solve-one-get-2** (84 B): asm `FUN_08093afc`, `FUN_080950d0`
- **FREE via C twin** (84 B): asm `FUN_0803a574`; C `CalcAngle`
- **solve-one-get-2** (84 B): asm `FUN_0807c530`, `FUN_0807cb50`
- **FREE via C twin** (88 B): asm `tretista_0804fecc`; C `FUN_0804cccc`
- **solve-one-get-2** (92 B): asm `FUN_0807d724`, `gallisni_080870bc`
- **solve-one-get-2** (96 B): asm `FUN_08093a98`, `FUN_08095014`
- **solve-one-get-2** (96 B): asm `FUN_080ab724`, `FUN_080ab990`
- **FREE via C twin** (96 B): asm `snowyPlains_08012b9c`, `snowyPlains_08012fec`, `snowyplains_0801320c`; C `LayerUpdate_TwilightDesert_2`
- **solve-one-get-2** (96 B): asm `FUN_080c182c`, `FUN_080c188c`
- **FREE via C twin** (104 B): asm `Lemmingles_Die`, `Snakecord_Die`, `Volcaire_Die`, `GeneratorCannon_Die`, `Seimeran_Die`, `Shellcrawler_Die`, `Projectile17_Update`; C `GrandCannon_Die`, `Shrimporin_Die`, `CannonHopper_Die`, `GrandCannonBomb_Update`, `Projectile16_Update`, `Projectile43_Update`
- **solve-one-get-2** (104 B): asm `FUN_08013dd4`, `FUN_08016018`
- **solve-one-get-3** (108 B): holdouts `FUN_080e58bc`*; asm `FUN_080e2510`, `FUN_080e2b78`
- **FREE via C twin** (108 B): asm `PantheonBombProjectile_Update`, `Projectile37_Update`; C `ShotcounterBullet_Update`, `Projectile2_Update`, `ClavekerYellowBalls_Update`
- **solve-one-get-2** (108 B): asm `Shotloid_Die`, `PantheonFist_Die`
- **solve-one-get-2** (112 B): asm `FUN_080c6c60`, `FUN_080c7250`
- **FREE via C twin** (112 B): asm `Projectile42_Init`, `LocomoIFPlatform_Init`; C `Projectile13_Init`, `Projectile18_Init`, `Projectile20_Init`, `PantheonAquaModProjectile_Init`, `Projectile23_Init`, `Projectile30_Init` (+2 more)
- **FREE via C twin** (116 B): asm `FUN_08084744`; C `FUN_08069098`
- **solve-one-get-4** (120 B): asm `FUN_080da21c`, `FUN_080da320`, `FUN_080da5e8`, `FUN_080da6f0`
- **solve-one-get-2** (120 B): asm `FUN_080da114`, `FUN_080da41c`
- **solve-one-get-2** (124 B): asm `FUN_080da01c`, `FUN_080da500`
- **FREE via C twin** (136 B): asm `doGoldOmega1Laser1`; C `doOmega1BallLaser1`
- **FREE via C twin** (140 B): asm `FUN_080acb54`; C `FUN_0809da14`
- **solve-one-get-3** (144 B): asm `FUN_080772f8`, `FUN_08093b50`, `FUN_08095124`
- **FREE via C twin** (144 B): asm `icebase_080111dc`; C `ocean_0800d28c`, `ocean_0800d488`
- **solve-one-get-2** (144 B): asm `FUN_0806e674`, `FUN_0807d780`
- **solve-one-get-2** (152 B): asm `FUN_08099ce4`, `FUN_08099d88`
- **solve-one-get-2** (184 B): asm `FUN_080b9cf8`, `FUN_080b9db0`
- **solve-one-get-2** (208 B): asm `FUN_080b963c`, `FUN_080c2294`
- **solve-one-get-2** (216 B): asm `SeaOtterElf_Init`, `BirdElf_Init`
- **FREE via C twin** (232 B): holdouts `Ghost28_Init`; asm `Ghost66_Init`; C `VFX59_Init`
- **FREE via C twin** (232 B): asm `Ghost22_Init`; C `VFX38_Init`
- **FREE via C twin** (232 B): asm `VFX46_Init`; C `VFX41_Init`
- **solve-one-get-2** (244 B): asm `FUN_080c2500`, `FUN_080c25f4`
- **FREE via C twin** (272 B): asm `FUN_080acbe0`; C `FUN_0809daa0`
- **solve-one-get-2** (284 B): asm `doOmega1BallLaser2`, `doGoldOmega1Laser2`
- **solve-one-get-9** (308 B): asm `FUN_080b754c`, `FUN_080b7a04`, `FUN_080ba16c`, `FUN_080be020`, `FUN_080c2a78`, `FUN_080c2d48`, `FUN_080c338c`, `FUN_080c47e0`, `FUN_080c4aac`
- **solve-one-get-2** (308 B): asm `FUN_080b7e3c`, `FUN_080bd288`
- **solve-one-get-2** (504 B): asm `FUN_0809c664`, `FUN_0809e7c0`

`*` = holdout already has a C body (withc list).

4 holdout names were AMBIGUOUS (static name reused across files or renamed in the map) and were excluded from the scan — check these by address by hand:
- LayerDraw_3 (2 decls, 1 map entries)
- handle_rod_input (2 decls, 1 map entries)
- handle_shield_input (3 decls, 1 map entries)
- onCollision (2 decls, 1 map entries)
