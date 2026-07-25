# SeaOtterElf_Init — posted 2026-07-25

- scratch: https://www.decomp.me/scratch/C3UWS
- claim: https://www.decomp.me/scratch/C3UWS/claim?token=eyJzbHVnIjoiQzNVV1MifQ.XRMQf3qfR3BX8J-RygNvKCe7tLY
  (USER: open while logged in — anonymous scratches expire; the scratch
  may need the context pasted into the Context tab from build/ctx.c —
  the source compiles locally at 216/216 with 22 diff bytes)
- earlier duplicate slugs from posting attempts (ignore): Y5YCG, 4ZXAQ
- root cause: buffer-block regalloc — target does
  `adds r2,#0x78 / movs r1,#0 / movs r0,#0x80 / lsls / strh r0,[r2]`
  (buffer[14] addressed from the dead oam byte pointer r2=p+0x4a, fresh
  zero in r1), ours always derives r1+6 from the buffer[8] pointer and
  reuses the r8 zero for buffer[12].
- payoff: 2 functions (SeaOtterElf_Init 080E4628, BirdElf_Init 080E5998),
  216 B each
- best local harness: build/scratch/elf2/m4.c; full state in
  notes/backlog-truth.md ("SeaOtterElf_Init / BirdElf_Init")

About-tab text:
  216-byte elf init. Everything matches except the last data block:
  the target stores 0x200 through a halfword pointer derived from a
  DEAD byte pointer (+0x78 in place), with a fresh movs r1,#0 wedged
  between the address and the value, then stores that r1 to buffer[12].
  Compiler is agbcc (gcc 2.9 thumb) -O2 -mthumb-interwork -fshort-enums.
  Suspect a zero temp that must allocate INTO r1 to kill the cheaper
  address base. See repo notes for the six spellings already tried.
