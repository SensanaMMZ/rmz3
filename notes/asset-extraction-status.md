# Asset extraction status (audit 2026-06-21)

Quick audit of how complete asset decompilation/extraction is. ROM is byte-perfect
(`make compare` OK) and the build has **no `baserom`/raw-ROM incbin** — every asset
is present as a source file in the tree. The gaps below are about converting assets
to *decompiled / editable / named* form, not about missing data.

## Sprites — DONE
- 1278 sprite sheets, **every one has an editable PNG**:
  `png=1278 = 4bpp(1140 uncompressed) + lz(138 compressed)` + `.gbapal` palettes.
- `graphics/` and `data/` tiles are the same shape (PNG + `.4bpp`/`.pal`/`.lz`).
- Nothing left as an opaque sprite/graphics blob.

## Sounds — ~80%, two gaps remain

### Gap 1: RESOLVED (2026-07-04) — all song `.bin` migrated to `.inc`
- All 46 raw `.bin` are now `.inc` byte-dumps `.include`'d in `sound/song_data.inc`
  (byte-identical, ROM stays byte-perfect). Original raw-`.bin` note below, kept for context.

### Gap 1 (original): 46 song/SFX sequences still RAW `.bin` (not decompiled)
- `sound/songs/` has **196 decompiled `.inc`** (readable m4a macro sequence data)
  vs **46 raw `.bin`** that are still opaque binary sequence bytes.
- Examples: `bgm_energy_factory.bin`, `bgm_library.bin`, `bgm_last_stage.bin`,
  `bgm_forest.bin`, `bgm_neoarcadia3.bin`, `se_blazin_*.bin`, `se_childre_*.bin`.
- They build correctly (bytes are original) but aren't in editable form.
- TODO: convert these to `.inc` m4a sequence data (see the `.inc` ones as the format;
  mid2agb / a sequence disassembler, or the upstream tooling).

### Gap 2: all 256 PCM voice samples are UNIDENTIFIED
- `sound/direct_sound_samples/` = **256 `.bin`, all named `unk_<romaddr>`** (0 named).
- incbin'd as e.g. `DirectSoundWaveData_unk_08110294` in `sound/direct_sound_data.inc`.
- Raw PCM can't be "decompiled" (it's sampled audio) but in a finished decomp they'd
  be named by instrument/voice, and possibly carried as `.aif`/`.wav`.
- TODO: name the voicegroups / samples (cross-ref `voicegroup*` tables in sound data).

## Untracked WIP extraction scripts (in repo root, NOT committed)
Someone (user) has been actively working on sound/sprite extraction after the last
decomp session — review/finish or remove these:
- `_extract_all_sfx.py` (Jun 17) — SFX extraction
- `_extract_charge_effect.py` (Jun 20)
- `_assemble_all_sprites.py`, `_assemble_static_lz.py` (Jun 15)
- `_rmz3_index_{1..4}.png` — index/overview images

## Net
Sprites: done. Sounds: 46 raw song `.bin` + 256 unnamed PCM samples to go.
Everything else (code is a separate effort) builds byte-perfect from source.
