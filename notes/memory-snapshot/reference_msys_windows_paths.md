---
name: reference-msys-windows-paths
description: MSYS↔Windows path translation — the cygpath -m rule for any workflow that hands paths to a mix of MSYS and Windows binaries
metadata: 
  node_type: memory
  type: reference
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

This box runs MSYS2 bash + Cygwin-style tools (cpp, make, bash) alongside **native Windows** binaries (`tools/agbcc/bin/agbcc.exe`, `C:\devkitPro\devkitARM\bin\*.exe` = as/ld/objcopy/objdump, the Python313 launcher). They accept DIFFERENT path forms, and that mismatch is the #1 source of silent failures here. See the bug it caused in [[reference-decomp-tooling]] / [[project-open-todos]] (permuter compile.sh wrote its `.s` to `/tmp` → agbcc.exe couldn't resolve it → empty stub `.o` → constant score, days of confusion).

## The three path forms and who accepts them
| form | example | MSYS tools (cpp/bash/make) | Windows binaries (agbcc.exe/as.exe/objdump.exe) |
|---|---|---|---|
| MSYS unix | `/tmp/x` , `/c/Users/x` | ✅ | ❌ (reads `/tmp` as `<cwd-drive>:\tmp\..` → "No such file or directory") |
| Windows backslash | `C:\Users\x` | ⚠️ (bash can eat `\`) | ✅ |
| **mixed (forward-slash Windows)** | `C:/Users/x` | ✅ | ✅ |

**`cygpath -m <path>` → the mixed form, which BOTH worlds accept.** It also collapses backslash and `/tmp` and `/c/..` inputs to that one safe form. This is the universal fix.

## The rule (apply BEFORE any path-dependent workflow)
1. **Normalize every path that will reach a tool** at the top of the script:
   `norm() { command -v cygpath >/dev/null 2>&1 && cygpath -m "$1" || printf '%s' "$1"; }` then `INPUT="$(norm "$1")"` etc. Done in `tools/permuter-setup/compile.sh.template` and `setup_fn.sh`.
2. **Never put an intermediate file a Windows binary writes under MSYS `/tmp`** (or `$(mktemp)`); put it next to an already-Windows-resolvable output, or `cygpath -m` it.
3. **`set -o pipefail`** in any `cpp | agbcc`-style pipe, else a path failure in the first stage is masked by the second stage's success and you get a silent empty artifact.
4. **Don't rely on MSYS implicit arg conversion** (`/c/..`→`C:\..` when calling a native exe): it does NOT fire for `/tmp`, and `MSYS2_ARG_CONV_EXCL`/`MSYS_NO_PATHCONV` can disable it. Be explicit with `cygpath -m`.
5. **Python (Windows Python313) ↔ MSYS bash:** `tempfile` yields backslash Windows paths; pass them to `bash.exe`/`compile.sh` and let the script `cygpath -m`-normalize. Windows Python CANNOT open an MSYS `/tmp/..` path — give it real `C:\..` or `C:/..` paths. The permuter's `py` shebang resolves to MSYS python (no `toml`); always invoke the Python313 exe explicitly: `/c/Users/SaroGamingPC/AppData/Local/Programs/Python/Python313/python.exe`.
6. **Toolchain location:** the makefile/scripts default to `$(DEVKITARM)=/opt/devkitpro/devkitARM` which does NOT exist; the real toolchain is `/c/devkitPro/devkitARM/bin`. Pass `DEVKITARM=/c/devkitPro/devkitARM DEVKITPRO=/c/devkitPro` on the make command line (see [[reference-decomp-tooling]]).

Quick sanity check for a path-handling script: run it once with a `/tmp/out.o` target and once with a `C:\..\out.o` (backslash) target via a fresh `bash.exe`; both must produce a non-stub artifact.
