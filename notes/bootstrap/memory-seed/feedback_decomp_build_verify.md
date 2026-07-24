---
name: feedback-decomp-build-verify
description: "When decompiling for the rmz3 SHA1-matching build, always force-rebuild the changed .o file before trusting \"rmz3.gba: OK\""
metadata: 
  node_type: memory
  type: feedback
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

After editing a .c file in the rmz3 decomp, force-rebuild its .o before trusting the SHA1 match.

**Why:** During the 2026-05-28 session I committed VFX44_Update, blazinMode2, and FUN_08050090 each after make showed `rmz3.gba: OK`. They appeared to match, but the next session-state rebuild produced FAILED with `487fceee...`. The "OK" had come from stale .o files: make's incremental build can skip recompilation when timestamps don't trip its rules (e.g., when only INCASM removals or include changes happen). Three broken commits in a row forced a `git reset --hard` back to commit `6b3bc71`, throwing away half a dozen decomp candidates.

**How to apply:** Before committing any new decomp:
1. `rm -f build/rmz3/src/<path>/<file>.o` (and any sibling .o whose .c you touched)
2. `make` and read the final lines — must show both `rmz3.gba: OK` AND `sha1sum rmz3.gba` returning `ff7a801776dc76e6d8c7ef73a6660ae732934a3f`
3. Only then `git add -A && git commit`

If unsure whether prior commits are clean, run `make clean && make` to verify the whole chain still produces the target SHA1.
