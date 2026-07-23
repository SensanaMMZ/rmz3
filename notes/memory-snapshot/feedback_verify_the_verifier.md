---
name: feedback_verify_the_verifier
description: A check that can pass without doing its work is not a check — calibrate every comparison in both directions before believing it
metadata:
  type: feedback
---

In one rmz3 session, four separate verifications passed while checking nothing:

- a byte comparison that piped `objcopy` to `/dev/stdout`, got back nothing, and
  printed **BYTE-IDENTICAL** — it was comparing two empty strings, on functions
  whose sizes differed by 6 bytes;
- a hand-written-asm detector that skipped monolithic `.inc` files, so it
  scanned a handful of functions instead of 2,409 and reported a clean result;
- a build-liveness check whose pattern matched `bash` processes, so a dead build
  read as alive for 10 minutes;
- two build-error greps that fired on the literal `-Werror` inside a compile
  command and on a benign line beginning with `make`.

**Why:** a broken check fails *silently and optimistically*. "0 differences",
"nothing found", "still running" are exactly what success looks like, so nothing
prompts a second look. This is the same failure as the older silent-fake-match
lesson (empty disassembly on both sides → bogus "0 diffs") and it keeps
recurring in new forms.

**How to apply:**
- Calibrate in both directions before trusting a comparison: confirm it says
  IDENTICAL for a known match **and** DIFFERS for a known mismatch. Plant a
  probe if you have to — that is how `tools/check_shared_branch.sh` was found to
  be missing untracked files.
- Make detectors report their own coverage. `tools/detect_handwritten_asm.py`
  prints how many segments it scanned and warns when too many parse empty, so a
  regex regression can't masquerade as "nothing found".
- Prefer a check that cannot lie. For rmz3 that is the ROM sha1
  (`ff7a801776dc76e6d8c7ef73a6660ae732934a3f`); don't commit a match until it
  passes. See [[reference_agbcc_match_idioms]] and [[project_resume_state]].
- Sanity-check the magnitude, not just the verdict: two objects that differ in
  size cannot be "identical", and a zero-byte read is not agreement.
