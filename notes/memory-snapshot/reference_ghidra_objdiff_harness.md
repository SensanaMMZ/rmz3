---
name: reference_ghidra_objdiff_harness
description: Ghidra symbol-mapped ELF harness (decompile-by-name with named globals) WORKING; plus the objdiff-ranking contamination trap
metadata: 
  node_type: memory
  type: reference
  originSessionId: 7ac7f6e2-d470-478f-81da-12645bc74242
  modified: 2026-07-21T05:13:41.232Z
---

# Ghidra harness — WORKING END TO END (2026-07-21)

Ghidra 12.1.2 @ `C:\Users\SaroGamingPC\decomp-tools\ghidra_12.1.2_PUBLIC`,
JDK 21.0.11 @ `...\jdk-21.0.11+10` (12.x needs 21; system JDK 25 too new),
pyghidra 3.1.0 + pyghidra-mcp 0.2.3, registered in `.mcp.json`.

`decompile_function <bin> Beetank_Update` now works **by name**, with named
callees AND named globals (`gOamManager`, `gBeetankRoutine`,
`wStaticGraphicTilenums`) — exactly the pool literals m2c reports as
`M2C_ERROR`. Binary imported as `rmz3_sym.elf`.

## Rebuild in two commands (~12s + a few min of Ghidra analysis)

```sh
export PATH=/c/devkitPro/devkitARM/bin:$PATH
python3 tools/ghidra/map_symbols.py      # 5,835 funcs + 3,561 data globals
python3 tools/ghidra/build_sym_elf.py C:/Users/SaroGamingPC/decomp-tools/rmz3_sym.elf
```
then `import_binary` that path. Recipe: `tools/ghidra/symbolize_rom.md`.

**Use the LINKER MAP** (`expected/build/rmz3/rmz3.map`) — it exists and is
ground truth. `map_symbols.py` unions three sources: the map (globals only —
**a GNU map omits every `static`**), per-object symbol tables placed via the
map's `.text` contribution bases (recovers statics exactly), and `asm/**/*.inc`
labels. All three agreed everywhere they overlap; it WARNs on conflict.
Supersedes the old `resolve_holdout_addrs.py` anchor arithmetic (deleted).
Symbols at/above the `.rodata` base are DATA — `Camera_0834d268` in
`asm/scripts/*.s` is cutscene bytes, not code.

## ELF gotchas that cost real time

- **`objcopy --add-symbol` CANNOT set `st_size`.** Size-0 function symbols have
  no end boundary → `Flow exceeded maximum allowable instructions`. That is why
  `build_sym_elf.py` writes the ELF by hand.
- **`--rename-section .data=.rom,alloc,load,readonly,code` silently EMPTIES the
  section** — the flag list *replaces* flags, and dropping `contents` drops the
  image. Symptom: a well-formed ELF that disassembles as endless `movs r0,r0`.
- Thumb signalled twice: low bit set in `st_value` of each `STT_FUNC` (what
  Ghidra's ArmElfExtension keys on) plus a local `$t` mapping symbol.
- Validate with binutils BEFORE a multi-minute analysis pass:
  `readelf -sW | grep ' Fn$'` → value must be ODD and size non-zero.

Ghidra is for structural reconstruction, NOT register-alloc ties (that's the
instrumented agbcc). Cross-check rule: trust a reconstruction when m2c AND
Ghidra agree, then match with mdiff. See [[reference_agbcc_match_idioms]].

## ⚠ The objdiff ranking was contaminated — most of it was solved work

`tools/objdiff_rank.sh` compiles at **MODERN=1**, and MODERN swaps
`SET_ENTITY_ROUTINE` (include/entity/macros.h) for a form that stores the mode
*before* computing the routine-table address instead of after. Four
instructions — enough to drop a byte-perfect function to ~92%. So every caller
of `SET_BOSS_ROUTINE`/`SET_ENEMY_ROUTINE` ranked as a near-miss while already
matching the ROM.

**Verified already matching at MODERN=0: CopyX_Update, Blazin_Update,
tryKill{Childre,Deathtanz,Glacierle}, CreateBlazin, loadMugshot, DrawStatus.**
The entire top of `notes/objdiff-ranking.md` was noise. Do not attack these.

Mirror-image trap: a *declared* holdout emits its `INCCODE`'d asm verbatim at
MODERN=0, so "matches expected" is trivially true there and proves nothing.
Neither config answers alone → `tools/verify_rank.sh` labels both populations.

**Rule: trust the ranking's match% only for functions actually declared
`NON_MATCH`/`NAKED`.**

## True backlog — reconstruction dominates

`python3 tools/classify_holdouts.py` → 491 declared holdouts =
**129 with a `#if MODERN` C body** (permuter/objdiff targets) +
**362 pure INCCODE stubs** (need source reconstruction — the Ghidra harness).
Reconstruction is the bulk of what is left, not register-tie cracking.
Lists: `notes/holdouts-{withc,pure}.md`; writeup: `notes/backlog-truth.md`.
Most stubs: mmbn4.c 18, omega_zero.c 15, overworld_layer.c 14, player.c 14.
