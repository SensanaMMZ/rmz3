# FUN_080e58bc — REPLACED 2026-07-25 (use uJ5Jm; ldwqE never compiled)

- scratch: https://www.decomp.me/scratch/uJ5Jm  (success=True server-side)
- claim: https://www.decomp.me/scratch/uJ5Jm/claim?token=eyJzbHVnIjoidUo1Sm0ifQ.thQ6LIxj9jDDaOx155GjEWGqM8Q
- ldwqE can be deleted/ignored — it was posted with an empty context
  and its source used the _TEST symbol name; the paste kit in
  notes/decompme/fixes/ still works if you prefer repairing it instead.

Original post below for the analysis text (still accurate):

# FUN_080e58bc — posted 2026-07-24

- scratch: https://www.decomp.me/scratch/ldwqE
- claim: https://www.decomp.me/scratch/ldwqE/claim?token=eyJzbHVnIjoibGR3cUUifQ.LM2X5UPZlpMweevDw873L7f7FpU
  (USER: open while logged in — anonymous scratches expire)
- root cause: regalloc-tie / pseudo-priority (p-copy r2 vs r3 swap; fl r1 vs r0)
- payoff: 3 byte-identical functions (FUN_080e58bc, FUN_080e2510, FUN_080e2b78), 108 B each
- best local harness: build/scratch/e58bc/v3.c
