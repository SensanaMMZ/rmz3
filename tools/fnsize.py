#!/usr/bin/env python3
"""Report a function's ROM address and exact byte size from its .inc.

Sizes in rom_symbols.txt are unreliable (see notes/backlog-truth.md), so measure
the .inc text directly: 2 bytes per Thumb instruction, 4 per bl, 4 per .4byte,
n per .byte list, and honour `.align 2, 0`. Cross-checks against the next
function's `@ 0x...` address comment when there is one.
"""
import re, sys, glob

def size_of(body):
    n = 0
    for ln in body.split('\n'):
        s = ln.split('@')[0].strip()
        if not s or s.startswith(('.include', '.syntax', '.text', '.thumb', '.type',
                                  '.globl', '.size', 'thumb_func_start')):
            continue
        if s.endswith(':'):
            continue
        if s.startswith('.align'):
            a = 4 if '2,' in s else 2
            n = (n + a - 1) // a * a
            continue
        m = re.match(r'\.(\d?)byte\s+(.*)', s)
        if m:
            w = 4 if m.group(1) == '4' else (2 if m.group(1) == '2' else 1)
            n += w * len(m.group(2).split(','))
            continue
        n += 4 if re.match(r'bl\s|b[a-z]*\s+_?\w+\s*$', s) and s.startswith('bl ') else 2
    return n

def main():
    want = set(sys.argv[1:])
    for f in glob.glob('asm/**/*.inc', recursive=True):
        txt = open(f, encoding='utf-8', errors='replace').read()
        parts = re.split(r'\n\s*thumb_func_start\s+(\S+)\n', txt)
        for i in range(1, len(parts), 2):
            if parts[i] not in want:
                continue
            body = parts[i + 1]
            m = re.search(r'@ (0x[0-9A-Fa-f]{8})', body)
            addr = int(m.group(1), 16) if m else 0
            nxt = None
            if i + 2 < len(parts):
                m2 = re.search(r'@ (0x[0-9A-Fa-f]{8})', parts[i + 3])
                if m2:
                    nxt = int(m2.group(1), 16)
            sz = size_of(body)
            flag = ''
            if nxt is not None and nxt - addr != sz:
                flag = '  !! next symbol says 0x%X' % (nxt - addr)
                sz = nxt - addr
            print('%-24s %08X  size 0x%X%s' % (parts[i], addr, sz, flag))

main()
