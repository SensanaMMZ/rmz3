# Symbol-mapped ROM ELF for the Ghidra MCP (item 1)

Goal: make the pyghidra MCP decompile any holdout **by name/address** directly,
instead of only through the standalone `tools/ghidra_decompile.py`. The MCP's
`import_binary` needs an ELF with a real `.symtab` so Ghidra creates + names the
functions on analysis.

## What's already prepared

- `tools/ghidra/rom_symbols.txt` — **2,199 `name address` pairs** harvested from
  the `Name: @ 0x08XXXXXX` comments in `asm/**/*.inc` plus the address-encoded
  `FUN_08xxxxxx` names. Covers every asm-bodied function (all the NAKED/INCASM
  holdouts). Addresses are the ROM VMA; the ELF is already based at 0x08000000
  (`C:\Users\SaroGamingPC\decomp-tools\baseimg.elf`, section `.rom`).
- **Gap:** C-matched NON_MATCH holdouts (Beetank_Update, CopyBgMap, CopyX_Update,
  Blazin_Update, tryKill*, CountRodButton…) are NOT in that list — their MODERN
  bodies are C, so their asm fragments lack the `label: @ addr` line. Get those
  addresses from the built objects: `arm-none-eabi-nm expected/build/rmz3/<file>.o`
  gives the symbol, and the linker map (build the ROM once, or
  `linker/text.txt` order + section sizes) gives the VMA. Or just look each one
  up individually with `tools/ghidra_decompile.py` (which finds them by address).

## The build recipe

Add each symbol to the ELF's `.symtab` as a FUNCTION, with the **Thumb bit**
(odd address) so Ghidra decodes Thumb, not ARM:

```sh
cd /c/Users/SaroGamingPC/MMZ5-X8-Base/rmz3
export PATH=/c/devkitPro/devkitARM/bin:$PATH
ELF=/c/Users/SaroGamingPC/decomp-tools/baseimg.elf

# build one --add-symbol arg per line: NAME=.rom:OFFSET,function,thumb
#   OFFSET = addr - 0x08000000 ; set bit0 for Thumb (all GBA game code is Thumb)
python3 - <<'PY'
import io, subprocess, shlex
base=0x08000000
args=[]
for ln in io.open('tools/ghidra/rom_symbols.txt'):
    name,addr=ln.split()
    off=int(addr,16)-base
    # 'function' type; Ghidra reads the low bit of the *value* for Thumb, but
    # objcopy add-symbol is section-relative — set the flag via a trailing ,thumb
    args.append('--add-symbol')
    args.append('%s=.rom:0x%X,function' % (name, off|1))
# objcopy chokes on huge argv on Windows; batch in chunks of 400
CHUNK=400
elf='/c/Users/SaroGamingPC/decomp-tools/baseimg.elf'
pairs=[args[i:i+2] for i in range(0,len(args),2)]
for k in range(0,len(pairs),CHUNK):
    batch=[x for p in pairs[k:k+CHUNK] for x in p]
    subprocess.run(['arm-none-eabi-objcopy']+batch+[elf], check=True)
    print('added', min(k+CHUNK,len(pairs)), 'of', len(pairs))
PY
arm-none-eabi-nm "$ELF" | grep -i beetank | head   # sanity: symbols present
```

Then in a fresh Claude Code session (MCP reloads on start):
1. `delete_project_binary` the old symbol-less `baseimg.elf`, or import the new
   one under a fresh name.
2. `import_binary C:/Users/SaroGamingPC/decomp-tools/baseimg.elf`
3. Wait for `list_project_binaries` → `analysis_complete: true`.
4. `decompile_function <binary> <FunctionName>` — now resolves by name.

## Caveat on the Thumb bit

`objcopy --add-symbol` sets a section-relative value; Ghidra's ELF loader keys
Thumb off the symbol value's low bit for ARM. If functions still decode as ARM
after import, the fallback that is already proven is `tools/ghidra_decompile.py`
(it sets the `TMode` context register = 1 explicitly). Verify one Thumb function
decompiles sanely before trusting a batch.
