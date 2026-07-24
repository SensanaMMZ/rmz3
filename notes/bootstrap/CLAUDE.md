# Bootstrap instructions for a matching-decomp Claude Code session

Drop this file at the repo root as `CLAUDE.md` (Claude Code loads it into
every session automatically), seed the memory directory from
`memory-seed/` (see README.md), and the first prompt can simply be:
"read the notes and continue the decomp."

## The mission

Byte-perfect decompilation. The only definition of done for a function:
the **full ROM rebuilds to the reference sha1** with that function as real
C. Never commit a claimed match before `make compare` passes. Partial
credit does not exist; "matches in objdiff" is evidence, not proof.

## Hard rules (each one was paid for)

1. **Read the per-file compiler overrides before touching any function.**
   The makefile's bottom section overrides compiler/flags per object.
   Probing a function with the default flags when its file uses others
   produces meaningless diffs and false "impossible" verdicts.
2. **Byte-diff is the only arbiter below ROM level.** Disassembly framing
   lies (functions stored as raw data, pool compression, truncated
   windows). Compare raw `.text` spans; classify `bl` differences as
   link-equivalent by checking relocations before calling them real.
3. **A check that can pass without doing its work is not a check.**
   Calibrate every comparator in both directions (known-identical AND
   known-different) before trusting either verdict. Detectors must print
   their own coverage.
4. **Don't assume anything is ruled out permanently.** Question
   assumptions, search the web, re-test old conclusions with new
   knowledge. Keep retractions in the notes — the reasoning error is more
   reusable than the fact.
5. **Negative results get written down** (which levers failed, plateau
   scores, wrong guesses) so nobody re-runs dead experiments.

## The working loop

1. Pick a target (duplicate-scan free candidates first, then smallest
   pure stubs; check whether a byte-identical or near-identical twin of
   the function already has matched C anywhere in the ROM).
2. Reconstruct: decompiler draft (Ghidra + m2c cross-check; distrust
   whichever disagrees), then write C.
3. Probe-TU method for any questionable codegen: reproduce the
   instruction form in a tiny standalone TU before contorting the real
   function.
4. Compile with the file's own flags; byte-diff; read the diff as
   evidence (each mismatch class maps to a source-level property — see
   the idiom catalog in the memory seed and the project's workflow notes).
5. Escalate in order: source-shape levers → per-file flag sweep
   ({-O0,-O1,-O2,-Os} × {old/new compiler} × documented -f flags) →
   community platforms (decomp.me) with a root-cause tag → park honestly
   with a write-up.
6. Ship every match; keep a session-state memory note current so the next
   session resumes without re-derivation.

## Memory conventions

Claude Code persists per-project memory. Keep:
- `MEMORY.md` — one-line index, loaded every session.
- `project_resume_state.md` — newest entry first; the pickup point.
  Update at session end with: pushed state, open PRs, next queue,
  environment traps hit, anything unpushed.
- `reference_*.md` — durable technical facts (tooling recipes, compiler
  behavior, platform quirks).
- `feedback_*.md` — process rules learned from mistakes, with the why.

The `memory-seed/` directory beside this file contains our accumulated
reference and feedback memories, scrubbed for publication. Copy them into
the new project's memory directory to start with our lessons pre-loaded.

## Repo documentation the sessions maintain

- `notes/matching-workflow.md` — the per-match procedure and byte-diff
  evidence table (procedure of record).
- `notes/backlog-truth.md` — per-function findings, retractions, parked
  functions with root causes.
- `notes/workflow-complete.md` — the full pipeline end to end.
- Research surveys and playbooks under `notes/` as they accumulate.

Claude writes these and follows them; the human prompts stay short
("continue", a goal sentence, or a one-off research directive).
