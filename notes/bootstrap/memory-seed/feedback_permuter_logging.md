---
name: feedback_permuter_logging
description: Permuter background runs need a logfile AND a hard kill switch — success-only stop conditions orphan workers forever
metadata: 
  node_type: memory
  type: feedback
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

**2026-07-22 addendum — ALWAYS give background permuters a hard stop.** The
2026-07-19 beetank runs were launched detached with auto-stop only on
score ≤ 120. They plateaued ~300, so the condition never fired, and **33
orphaned processes (3 coordinators: -j12, -j12, -j6, plus 30 multiprocessing
workers) ran for 4 days** until the user reported system hitches.

**⚠ The Store Python registers processes as `python3.11`, NOT `python`.**
`Get-Process -Name python,python3,pythonw` matches NOTHING on this machine and
reported "0 python" while 33 were running — a false all-clear from a wrong
filter (the verify-the-verifier failure again, hours after writing that note).
Always filter `ProcessName -like '*python*'`, and kill coordinators
(`permuter.py` in the command line) before workers so they cannot respawn.

**Why:** a search that can plateau will plateau; a success-only stop condition
means plateau = runs forever, silently.

**How to apply:** every detached permuter/grinder launch gets BOTH a success
threshold AND a wall-clock limit (`timeout 43200 ...` or an iteration cap), and
gets recorded (PID + purpose + expected end) so the next session can find and
reap it. Check `ps` for stale python/bash from prior days at session start when
the machine feels slow — also remember each Claude session holding the rmz3
project spawns one `python -m pyghidra_mcp` + one JVM (legitimate, exits with
the session).

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
