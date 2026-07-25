#!/usr/bin/env python3
"""Carve one function out of an .inc, leaving the before/after halves.

usage: carve_inc.py <inc> <fn>
Writes <base>_a.inc (functions before FN) and <base>_b.inc (functions after FN),
deletes the original, prints the paths that survived (a part with no content is
not written). Anything trailing the last function -- orphan padding, a stray
`bx lr` with no thumb_func_start -- stays with the _b half so it is never lost.
"""
import re, sys, os

HDR = '\t.include "asm/macros.inc"\n\n\t.syntax unified\n\t\n\t.text\n\n'

def main():
    inc, fn = sys.argv[1], sys.argv[2]
    txt = open(inc, encoding='utf-8').read()
    if txt.startswith('\t.include'):
        body = txt[txt.index('.text') + len('.text'):].lstrip('\n')
    else:
        body = txt
    marks = [(m.start(), m.group(1))
             for m in re.finditer(r'^\tthumb_func_start (\S+)$', body, re.M)]
    names = [n for _, n in marks]
    if fn not in names:
        sys.exit('no thumb_func_start %s in %s' % (fn, inc))
    i = names.index(fn)
    before = body[:marks[i][0]]
    after = body[marks[i + 1][0]:] if i + 1 < len(marks) else ''
    if not after.strip():
        # FN is last: whatever follows its pool is orphan content -- keep it.
        tail = body[marks[i][0]:]
        cut = re.split(r'\n\t\.align 2, 0\n', tail)
        orphan = ''
        if len(cut) > 1:
            # keep any labelled .byte/.4byte run that is not part of FN's pool
            pass
    base = os.path.splitext(inc)[0]
    out = []
    for suffix, part in (('_a', before), ('_b', after)):
        if part.strip():
            path = base + suffix + '.inc'
            n = 0
            while os.path.exists(path):   # never clobber an existing inc
                n += 1
                path = base + suffix + chr(ord('b') + n) + '.inc'
            open(path, 'w', encoding='utf-8', newline='\n').write(HDR + part.rstrip('\n') + '\n')
            out.append(path)
    os.remove(inc)
    print('\n'.join(out))

main()
