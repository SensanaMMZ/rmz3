---
name: feedback_permuter_logging
description: Always tee permuter stdout to a logfile so the cumulative iteration counter is captured
metadata: 
  node_type: memory
  type: feedback
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

When launching the decomp-permuter (especially long background grinder runs),
ALWAYS tee its stdout to a logfile, e.g. `... permuter.py ... 2>&1 | tee permuter_<func>_<date>.log`.
The background monitor only logged *new-best* scores, so when asked "how many
permutations did it go through?" there was no cumulative iteration counter on
disk — only an estimate from runtime × workers was possible (~20M for the 48h
beetank run).

**Why:** decomp-permuter prints the running iteration count and iters/sec to
stdout continuously; if that stream isn't captured, the exact count is lost and
you can only estimate from wall-clock runtime.

**How to apply:** every permuter launch gets `| tee <logfile>`; for background
runs, point the logfile somewhere stable (not /tmp) and grep it later for the
final iteration count. Pairs with the score-trajectory monitor, doesn't replace it.

Related: [[project_open_todos]] (beetank resolved as NON_MATCH dual-form, not via permuter), [[reference_decomp_tooling]].
