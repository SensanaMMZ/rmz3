# Symbol-mapped ROM ELF for the Ghidra MCP

Goal: make the pyghidra MCP decompile any holdout **by name**, with real names
for its callees and globals, instead of `FUN_08xxxxxx` soup reached by address.

Two commands, ~15 seconds:

```sh
export PATH=/c/devkitPro/devkitARM/bin:$PATH        # needs arm-none-eabi-objdump
python3 tools/ghidra/map_symbols.py                 # -> rom_symbols.txt, rom_data_symbols.txt
python3 tools/ghidra/build_sym_elf.py C:/Users/SaroGamingPC/decomp-tools/rmz3_sym.elf
```

Then `import_binary C:/Users/SaroGamingPC/decomp-tools/rmz3_sym.elf`, wait for
`list_project_binaries` to report `analysis_complete: true` (a few minutes for
8 MB), and `decompile_function <binary> Beetank_Update`.

## Where the symbols come from

`map_symbols.py` unions three sources into `rom_symbols.txt` (code) and
`rom_data_symbols.txt` (data), each `NAME ADDR SIZE` in hex:

1. **`expected/build/rmz3/rmz3.map`** — the linker map from the build that
   produced the matching ROM. Ground truth, but a GNU map lists only *globals*,
   so every `static` function is missing from it.
2. **Per-object symbol tables.** The map's section-contribution lines give each
   object's `.text` base; `objdump -t` on that object lists its locals too, so
   `VMA(fn) = objbase + offset(fn)` recovers every static exactly.
3. **`Name: @ 0x08XXXXXX` comments in `asm/**/*.inc`** — labels in hand-written
   asm that never became object-file symbols.

Anything at or above the `.rodata` base is emitted as **data**, not code — the
`Camera_0834d268`-style labels in `asm/scripts/*.s` are cutscene script bytes,
and marking them `FUNC` would make Ghidra disassemble data as Thumb.

Result: **5,835 functions + 3,561 data globals**, vs 2,208 from the old
asm-comment-only harvest.

### Why this is trustworthy

The three sources overlap heavily and are derived completely independently, so
they cross-check each other. When this was built:

- linker map, anchor arithmetic, and asm harvest **all** put `Beetank_Update` at
  `0x0807b9f0`;
- the asm harvest and the linker map share 1,868 names and agree on **all** of
  them — zero address conflicts;
- the merged run reports zero conflicts across all three.

`map_symbols.py` prints a `WARNING:` block listing any conflict. A clean run
means the sources are consistent; treat a warning as a real bug.

This supersedes the old `resolve_holdout_addrs.py`, which inferred a C-bodied
holdout's address from a mapped sibling in the same object. Same formula, but
the base now comes from the linker instead of being inferred, and it covers
every function rather than only those with a mapped sibling. All four addresses
that script could not anchor are resolved: `CopyBgMap 080F3C90`,
`CountRodButton 080338CC`, `DrawStatus 080EA0A8`, `loadMugshot 080EA930`.

## Why the ELF is written by hand

`build_sym_elf.py` emits the ELF directly rather than going through
`objcopy --add-symbol`, for three reasons found the hard way:

- **`objcopy --add-symbol` cannot set `st_size`.** A Ghidra function symbol with
  size 0 has no end boundary, so the decompiler follows flow off the end of the
  function and fails with `Low-level Error: Flow exceeded maximum allowable
  instructions`. Sizes are the entire point.
- **`--rename-section .data=.rom,alloc,load,readonly,code` silently empties the
  section.** The flag list *replaces* the section flags, and dropping `contents`
  drops the ROM image — you get a correctly-shaped ELF full of zeros, which
  disassembles as a plausible-looking run of `movs r0,r0`. If a symbolized ELF
  ever decodes as all-zero instructions, check this first.
- Writing it directly also lets us map the **GBA memory regions**
  (ewram/iwram/io/palram/vram/oam as NOBITS blocks), so RAM globals like
  `gGameState` land in named mapped memory instead of nowhere.

Thumb is signalled two ways at once: the **low bit set in `st_value`** of each
`STT_FUNC` (what Ghidra's `ArmElfExtension` keys on) and a **local `$t` mapping
symbol** at each function start.

### Validating the ELF without Ghidra

binutils is an independent parser — use it before spending a multi-minute
analysis pass:

```sh
arm-none-eabi-readelf -sW rmz3_sym.elf | grep ' Beetank_Update$'
#   -> 0807b9f1   248 FUNC    GLOBAL DEFAULT    7 Beetank_Update
#      odd value = Thumb, non-zero size = bounded body
arm-none-eabi-objdump -d --start-address=0x0807b9f0 --stop-address=0x0807ba1c rmz3_sym.elf
#   -> real Thumb, with branch targets shown as <Beetank_Update+0x34>
```
