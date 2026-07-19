# rmz3 decomp workflow & current state

Target: SHA1 `ff7a801776dc76e6d8c7ef73a6660ae732934a3f` (Mega Man Zero 3 JP, GBA).
Compiler: agbcc (legacy GCC 2.x), Thumb-1, `-O2`.

## Current state (where I left off)

- Branch: `main`, ~165 commits ahead of `3f40d15` (counting this session).
- Build: SHA1 matches as of latest commit.
- This session decomped ~60 fns across vfx (Ghost33/68/69/70/73, Ripple, etc), boss (phantom helpers x14, copy_x), enemy (snakecord, hammer, pantheon_*, carry_arm), projectile (unk_46 routine setters), stage_gfx (missile_factory, giant_elevator), solid (actor48, base_elevator dispatcher, CielMinigameObj_Init/Update), cyberelf (Elf5/10/11 Die fns + Elf1/Elf7 helpers + BirdElf_Die + NurseB_Die + unk_0 FUN_080e1fb8 + unk_7 FUN_080e3f24).
- Key cross-session learning: `--p->s.work[N] == 0` needs `u32 w = p->s.work[N] - 1; p->s.work[N] = w; if (w == 0)` to avoid the redundant lsl extension agbcc emits otherwise.
- **In-progress, NOT committed**: 5 body.status flag-check fns from the last batch:
  - `src/enemy/petatria.c` — `FUN_080902a8`, `FUN_080906ec` (both `BODY_STATUS_B3 → mode[1]=4/5`, return TRUE; declared as `bool8`, called via `(EnemyFunc)` cast in `sUpdates1`)
  - `src/enemy/unk_63.c` — `FUN_08094bd0` (`BODY_STATUS_BINDING` → mode[1]=3) — **just fixed** wrong constant from `BINDED` to `BINDING` (1<<11, not 1<<10)
  - `src/enemy/wormer_snow_ball.c` — `FUN_0807b30c` (`BODY_STATUS_B2` → mode[1]=2)
  - `src/projectile/locomo_if.c` — `FUN_080a7dec` (`BODY_STATUS_BINDING` → mode[1]=2) — **just fixed** same constant issue
- Need to rebuild + verify SHA1, then `tools/refresh-expected.sh` + commit as one batch.
- `git status -s` will show: 5 modified `.c` files + 10 new `_p1.inc`/`_p2.inc` (+ a couple `_p3.inc` for cannon_hopper) + 4 deleted parent `.inc`s.

## The workflow (battle-tested this session)

1. **Hunt**: find a code pattern in `asm/*.inc` that recurs across files. Examples:
   - `(arr[(p->s).mode[1]])(p)` — single-array dispatcher (~10 lines)
   - `(arr1[mode[1]])(p); (arr2[mode[1]])(p)` — two-array dispatcher (~20 lines)
   - body.status `& 0x00020001` flag check → set mode[1] (~14 lines)
   - slot reset (`*(p+0xb4)`) + `SetDDP` + `IsFrozen` → mode reset (~30 lines)
   - METTAUR flag dispatch (vfx Update fns)
2. **Split**: `python tools/split_inc_multi.py asm/<file>.inc <fn1> [<fn2> ...]` carves stubs out and produces `<file>_p1.inc`, `<file>_p2.inc`, etc. with parts between each named fn.
3. **Edit `.c`**: replace the single `INCASM(...)` with a sequence `INCASM(_p1); <C fn body>; INCASM(_p2); ...`. Add forward decls of arrays/helpers used.
4. **Build**: `& 'C:\devkitPro\msys2\usr\bin\bash.exe' -lc "cd /c/Users/SaroGamingPC/MMZ5-X8-Base/rmz3 && make 2>&1 | tail -3"` (PowerShell tool).
5. **If SHA1 fails**: `bash tools/diff.sh <fn>` to compare against `expected/`. Common failures and fixes:
   - **wrong array name** (`sUpdates` vs actual `sGhostXUpdates`/`PTR_ARRAY_xxx`): inspect `build/rmz3/src/.../<file>.s` to see the real symbol the compiler emitted.
   - **wrong sCollisions index**: compute via rmz3.map rodata start + sum of `.size` from `.s` file — see python snippet below.
   - **wrong body-status constant**: e.g. `0x80 << 4 = 0x800 = BINDING` (1<<11), not `BINDED` (1<<10). Diff shows `lsl r1, #0x4` vs `#0x3` — that's the tell.
   - **wrong flag bit**: e.g. `(gCurStory.s.gameflags, DEMO_PLAY=6)` gets the wrong byte if real flag is `METTAUR_ENABLED=38` (offset 8 not 4 in `gCurStory`).
   - **branch direction inverted**: target `beq skip` means "skip when result==0 (not frozen)" so the C is `if (IsFrozen(...))` not `if (!IsFrozen(...))`. Reading lsls#18+cmp+branch carefully is critical.
   - **u8 vs s32 param**: extra `lsl r1,#0x18; lsr r1,#0x18` in mine means I declared `u8` where target has `s32` (no narrowing).
   - **two strb → one strh fusion**: writing `mode[1]=0; mode[2]=0; mode[3]=0` can compile as `strb 0xd; strh 0xe` (target) vs `strb 0xd; strb 0xe; strb 0xf` (mine). Use `*(u16*)((u8*)p + 0xe) = 0;` for the strh half.
   - **half-word literal `.hword X` vs `.word X`**: cosmetic in objdiff but real in bytes. Hard to force; usually a sign the compiler chose a different code shape.
   - **extra `lsl r0, #0x18` after `--p->s.work[N]; if (== 0)`**: agbcc inserts a redundant byte-promotion before `cmp r0, #0`. Write `u32 w = p->s.work[N] - 1; p->s.work[N] = w; if (w == 0)` to skip it (the temp keeps the value in a register at full width). The trailing `cmp r0, #0` is safe even without the lsl because subtracting in 32-bit preserves the "is zero" property for any u8 input.
   - **load-load-store-store vs load-store-load-store for `coord.x` + `coord.y` copy**: when copying both x and y from `e->coord` to `(p->s).coord`, two explicit assignments `(p->s).coord.x = e->coord.x; (p->s).coord.y = e->coord.y;` compile to load-store-load-store. The target may use load-load-store-store (issuing both reads up front, then both writes). Replace with struct assignment `(p->s).coord = e->coord;` to fuse them into the dual-load/dual-store form.
6. **If SHA1 OK**: `bash tools/refresh-expected.sh` snapshots `build/` → `expected/` for the next diff.
7. **Commit**: descriptive one-line message, group related fns.

### Compute sCollisions[N] index from a hex address

```python
import re
m = open('build/rmz3/rmz3.map').read()
def find_start(name):
    for line in m.splitlines():
        if f'src/enemy/{name}.o' in line and '.rodata' in line:
            mm = re.search(r'0x0([0-9a-f]{7})', line)
            if mm: return int(mm.group(1),16)
def find_layout(name):
    s = open(f'build/rmz3/src/enemy/{name}.s').read()
    return [(mm.group(1), int(mm.group(2))) for mm in
            re.finditer(r'\.type\s+(\w+),object\n\s*\.size\s+\1,(\d+)', s)]
# Then walk layout, accumulating size with 4-byte align, until you hit sCollisions
```

## Patterns I've learned the hard way

- **Don't decomp byte-encoded fns** (`.byte 0x01, 0x20, 0x70, 0x47`). Target encodes them as data, mine emits proper thumb instructions — bytes match but linker/disassembler diverges. Petatria's 5 `return TRUE` stubs failed this way; hammer's `FUN_080756e8` somehow worked. Revert if it fails.
- **Don't add `static const struct Collision sCollisions[14];` forward decl in a file that already has the definition later** — agbcc may double-allocate (saw 4 bytes ROM overflow in phantom.c). Use only when truly forward.
- **`(EnemyFunc)fn` cast** is needed when the fn signature differs (e.g. `bool8(*)(struct Enemy*)` vs `void(*)(struct Enemy*)` in `sUpdates1` array).
- **`*((u8*)p + 0xb4)` is `p->props[0]`** for `struct CollidableEntity` (Entity + Body, props starts at 0xb4).
- **Entity offsets**: 0xa=flags, 0xb=flags2, 0xc-0xf=mode[0..3], 0x10-0x13=work[0..3], 0x14=onUpdate, 0x18=scriptEntity, 0x28=unk_28, 0x73=motion.state, 0x74=body (in CollidableEntity).
- **Body offsets**: 0x00=collisions, 0x04=processing, 0x08=coord, 0x0c=enemy, 0x10=bindPair, 0x14=hitboxFlags, 0x18=status, 0x2c=parent.
- **body offset from Entity start = 0x74**, so `[r0, #0x8c]` = `body.status` (0x74 + 0x18).
- **Mission struct**: weaponCount[0..3] at offsets 0x1c, 0x1e, 0x20, 0x22 of `gMission`. BUSTER=0, SABER=1, ROD=2, SHIELD=3.
- **`bool8` return values** sign-extend through `lsls r0, #0x18; lsr r0, #0x18` before compare. Spotting this in callers tells you to declare the callee as `bool8`.

## What's left (~52% to go)

| dir | files | fns |
|-----|------:|----:|
| enemy | 354 | 871 |
| boss | 140 | 494 |
| projectile | 97 | 360 |
| vfx | 107 | 272 |
| solid | 60 | 221 |
| stage_gfx | 12 | 95 |
| cyberelf | 13 | 72 |
| weapon | 16 | 41 |
| minigame | 7 | 33 |
| player | 8 | 27 |

**Total**: 991 .inc files, 2488 fns, ~5.9 MB asm.

## High-yield patterns still to mine

- `body.status & 0x00020001` flag-check fns — found 1 last scan, may be more with looser regex (varying register, e.g. `r3` instead of `r2`).
- `body.status & (1 << N)` for various N=2,3,11 — `BODY_STATUS_B2/B3/BINDING` checks. Scan for `lsls r1, #2`/`#3`/`#4` after `movs r1, #0x80` or `movs r1, #X`.
- Slot reset + SetDDP variants with conditional sCollisions index (deathlock's `FUN_0808d6f8` uses a `u8` lookup table — needs a fwd-declared byte array).
- More vfx `*_Update` with the `IS_METTAUR ? SET_ROUTINE(DIE) : (sUpdates[mode[1]])(p)` shape.
- Two-call dispatcher pattern (`(sUpdates1[mode[1]])(p); (sUpdates2[mode[1]])(p);`) — most done; rest need `extern const sUpdates1/2` forward decls.
- Boss helpers in phantom that just call `FUN_xxx` and set a mode byte conditionally — many still in `phantom_p2_pre_pre_p*` and `phantom_p1_pre_p*`.

## Hard remainders (skip for now)

- `wip/` folder (135 files) — looks deliberately deferred upstream.
- Long Update state machines with switch+fallthrough — hammer/cattatank/petatria fall here; per-fn effort.
- Anything with `0x0002D025` hardcoded (gOverworld+0x2D025 unnamed flag) — needs a struct field name first.
- Minigame dispatchers reading `*(s16*)(p+0xdd0)` — needs a Minigame struct definition.

## Tools I rely on

- `tools/split_inc_multi.py <inc> <fn1> [<fn2>...]` — splits asm around named fns
- `tools/diff.sh <symbol>` — per-fn objdiff vs `expected/`
- `tools/diff.sh -f <c-file>` — diff every changed fn in a file
- `tools/refresh-expected.sh` — snapshot build/ to expected/ after SHA1 match
- `bash.exe -lc "cd ... && make"` — Windows PowerShell wrapper for the agbcc build
- `objdiff-cli.exe` (in tools/) — actual ELF-level diff engine

## How to resume

1. Run `make` from `/c/Users/SaroGamingPC/MMZ5-X8-Base/rmz3` to confirm current state (should be SHA1 OK on latest commit; 5 fns mid-stream as noted above need a build+refresh+commit).
2. If the in-progress 5 fns build OK, `bash tools/refresh-expected.sh && git add -A && git commit -m "Decompile 5 body.status flag-check fns (petatria x2, unk_63, wormer_snow_ball, locomo_if proj)"`.
3. Continue hunting with the python regex scanners under "High-yield patterns" above.
4. User wants continuous progress with milestone updates only — no pausing for confirmation.
