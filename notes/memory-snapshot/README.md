# Memory snapshot

A point-in-time copy of the persistent memory this project's Claude sessions
use — the thing that makes week N faster than week 1. Not auto-synced; regenerate
when it drifts.

- `MEMORY.md` — the index loaded every session (one line per memory).
- `reference_agbcc_match_idioms.md` — **the idioms catalog**: every construct
  that ever cracked a match (register pins, the s64 live-range-split temp,
  chained assignments, bitfield extraction forms...).
- `reference_nonmatch_backlog.md` — every holdout ranked by closeness, with
  what has been tried and falsified on each.
- `reference_decomp_tooling.md`, `reference_agbcc_rtl_dumps.md`,
  `reference_msys_windows_paths.md`, `reference_permuter_packed_caveat.md` —
  tooling knowledge, including the traps (permuter strips packed structs;
  MSYS/Windows path normalization).
- `feedback_*.md` — workflow rules learned the hard way (force-rebuild before
  trusting a match; tee permuter logs; verify split .inc parts).
- `project_open_todos.md`, `project_resume_state.md` — the running state:
  what is proven, what is falsified, what is next.

Scrubbed of toolchain-provenance discussion before sharing.
