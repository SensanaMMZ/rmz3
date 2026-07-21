"""Resolve ROM addresses for C-bodied holdouts (the symbol-map gap).

Holdouts whose MODERN body is C have no `Name: @ 0x08XXXXXX` label in asm, so
they are missing from the asm-harvested rom_symbols.txt. But their object file
contains them alongside siblings that ARE mapped, and link order == source
order, so:

    VMA(fn) = known_VMA(anchor) - offset(anchor) + offset(fn)

both offsets read exactly from the object's symbol table. Validated: it puts
Beetank_Update at 0x0807B9F0, and a probe at 0x0807B9F8 resolves into that same
function (the 8 bytes are its prologue).

Usage:  python3 tools/ghidra/resolve_holdout_addrs.py [more_fn=src/file.c ...]
Appends any newly resolved `NAME ADDR` lines to tools/ghidra/rom_symbols.txt.

UNANCHORED FILES (every function in them is C-matched, so no sibling has a known
address): src/game/menu.c (CopyBgMap), src/player/zero/input/util.c
(CountRodButton). To resolve those, chain across files using linker/text.txt
order: take the nearest preceding object that HAS a mapped symbol, add up the
.text sizes of the objects between it and the target object, then apply the
formula above. Alternatively probe with tools/ghidra_decompile.py and read the
function start Ghidra reports.
"""
import io, os, re, subprocess, sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MAP = os.path.join(REPO, 'tools', 'ghidra', 'rom_symbols.txt')

DEFAULT = {
    'Beetank_Update': 'src/enemy/beetank.c',
    'CopyX_Update': 'src/boss/copy_x.c',
    'Blazin_Update': 'src/boss/blazin.c',
    'tryKillChildre': 'src/boss/childre.c',
    'tryKillDeathtanz': 'src/boss/deathtanz.c',
    'tryKillGlacierle': 'src/boss/glacierle.c',
    'blizzackMode0': 'src/boss/blizzack.c',
    'blizzackMode1': 'src/boss/blizzack.c',
    'blizzackNextMode': 'src/boss/blizzack.c',
    'loadMugshot': 'src/bg0/text_window.c',
    'DrawStatus': 'src/bg0/hud.c',
}


def load_map():
    d = {}
    if os.path.exists(MAP):
        for ln in io.open(MAP):
            p = ln.split()
            if len(p) == 2:
                d[p[0]] = int(p[1], 16)
    return d


def funcs_of(obj):
    t = subprocess.run(['arm-none-eabi-objdump', '-t', obj],
                       capture_output=True, text=True).stdout
    out = []
    for l in t.split('\n'):
        m = re.match(r'^([0-9a-f]{8}) .*\bF \.text\t([0-9a-f]{8}) (\S+)', l)
        if m:
            out.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
    out.sort()
    return out


def main():
    syms = load_map()
    targets = dict(DEFAULT)
    for a in sys.argv[1:]:
        if '=' in a:
            k, v = a.split('=', 1)
            targets[k] = v
    found = []
    for fn, cf in sorted(targets.items()):
        if fn in syms:
            continue
        obj = os.path.join(REPO, 'expected', 'build', 'rmz3', cf[:-2] + '.o')
        if not os.path.exists(obj):
            print('%-20s no object (%s)' % (fn, cf)); continue
        fl = funcs_of(obj)
        base = None
        for off, sz, nm in fl:
            if nm in syms:
                base = syms[nm] - off; break
        if base is None:
            print('%-20s NO ANCHOR in %s (see module docstring)' % (fn, cf)); continue
        for off, sz, nm in fl:
            if nm == fn:
                print('%-20s 0x%08X' % (fn, base + off))
                found.append('%s %08X' % (fn, base + off)); break
        else:
            print('%-20s not in object symbols' % fn)
    if found:
        with io.open(MAP, 'a') as w:
            w.write('\n'.join(found) + '\n')
        print('appended %d symbols to %s' % (len(found), MAP))


main()
