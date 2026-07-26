---
name: rmz3-upstream-port-workflow
description: "Step-by-step procedure for porting rmz3 fork matches upstream to mmzret/rmz3, plus the mistakes that have cost hours — read before any upstream PR work"
metadata: 
  node_type: memory
  type: project
  originSessionId: 5d805cb6-0db5-4f16-b98a-f26a825712bb
  modified: 2026-07-26T01:14:10.248Z
---

The end-to-end procedure for getting a matched fork function into an upstream PR,
and the specific errors that have burned time. Scripts live in the session
scratchpad; recreate them from this description if absent.

## Setup (once per session)

* Work in the **worktree** `C:/Users/SaroGamingPC/MMZ5-X8-Base/rmz3-up`, never in
  the main repo. `git worktree add -f -b <branch> ../rmz3-up upstream/dev`.
  Branch from **`upstream/dev`**, never `main` — PRs target `dev`.
* Copy `baseimg.gba` in from the main repo (verification needs it); `rm` it again
  before committing.
* `tools/agbcc` is not in the worktree — reference the main repo's copy by
  **Windows-style path** (`C:/Users/.../rmz3/tools/agbcc`). msys `/c/...` paths
  do not survive Windows Python's `subprocess`.

## The pipeline (`port_file.sh <fork-src.c> <flat|nested> [oldtype newtype]`)

1. **Rebuild `~/portable.txt`** — functions that are C in the fork and still
   `thumb_func_start` upstream. **Exclude `NON_MATCH` and `INCCODE` wrappers**
   (C shells around raw asm; porting them just relocates assembly). 939 real
   candidates as of 2026-07-25.
2. **Port** — `port_to_upstream.py` carves upstream's whole-file `.inc` at
   function boundaries and interleaves `INCASM` / C / `INCASM`.
3. **Adapt** — `adapt_up.py`, scoped to the brace-range of inserted functions.
4. **Copy fork prototypes and file-local structs** the upstream file lacks.
5. **Resolve declarations** — `fixdecls.sh` loops the compiler, adding a known
   header or the fork's declaration.
6. **Byte-verify** — `verify_up.py`; every function must say MATCH.
7. **Layout-verify** — `verify_layout.py`; pieces must tile the ROM region with
   no gap or overlap.
8. **Provenance scrub**, commit as SensanaMMZ, push to
   **`SensanaMMZ/rmz3-upstream`** (see [[rmz3-upstream-decomp-policy]]), open the
   PR against `dev`.

## Mistakes that have already cost hours — do not repeat

* **NEVER `rm -rf build`** in either tree. The makefile does not recreate its
  output directories. Recovery needs `touch tools/*/*.exe`, recreating ~715
  dirs, and building every asm object by explicit target. See
  [[rmz3-upstream-build-blockers]].
* **Never patch a file with escape sequences inside a shell heredoc.** This has
  corrupted three files: `carve_inc.py` (silent no-op), the makefile (`\n` became
  real newlines), `verify_up.py` (`\b` became a backspace, so relocation masking
  never matched and 9 good functions looked broken). Use the Edit tool, or build
  the string from `chr(92)`. **Always assert the replacement was found.**
* **Scope every rewrite to the inserted functions.** A blanket
  `p->work[` → `p->buffer[` once corrupted pre-existing upstream C where `p` was
  an `Entity*` with no `buffer`. After porting, check
  `git diff upstream/dev -- src/ | grep '^-'` shows nothing outside carved INCASM lines.
* **Never `rm` an `.inc` in the same command that inspects it.** Deleting is only
  right when it holds exactly ONE `thumb_func_start`; confirm in a separate call.
* **A size mismatch is a failure, not a footnote.** Only tolerate 1-3 trailing
  ZERO bytes taking the length to a 4-boundary (the next object's `.align`).
* **Do not infer sizes.** `rom_symbols.txt` is wrong, "last pool + 4" is wrong
  when a pool sits mid-function, and functions without an `@ 0x` comment must
  have their address recovered from the `FUN_xxxxxxxx` name or the previous
  function's size spans several functions.
* **Mask relocations from `objdump -r`**, never by hand-listing pool offsets.

## Codegen traps found while porting

* **A missing prototype changes generated code.** C89 defaults an undeclared
  callee to `int`. A real `bool8` return then loses the caller's
  `lsls r0,r0,#24` truncation (phantom: 15 functions, 53→68 once declared), and a
  real `u32` return makes a comparison signed — `ble` instead of `bls`
  (`CalcFromCamera`, shellcrawler). **Always copy the fork's prototypes.**
* `INIT_ENEMY_ROUTINE` already emits renderPrio + routine + tileNum/palID +
  `WHITE_PAINTABLE` + invincibleID; the PROJECTILE/VFX/ELF variants emit the
  first four. Writing those lines out again duplicates the stores.
* On a **flattened** type the entity-local `p->work[]` (0xB4) must become
  `buffer[]` BEFORE flattening, or it aliases the entity `work[]` at 0x10.
* Prefer the DEFINITION's return type over an existing prototype's — the
  definition is the byte-verified one; correct the prototype instead.

## Keep upstream in sync — check `mmzret/rmz3` dev every 12 hours

Standing instruction from the user (2026-07-25): poll upstream `dev` twice a day
so the fork does not drift further. `git fetch upstream dev` and compare the tip;
when it moves, rebuild the portable list, check whether any open PR now
conflicts, and flag any file with an open PR that upstream has since touched.
A cron job does this in-session, but cron is session-only — **re-create it at the
start of each session**, or do the check manually before starting a batch.
