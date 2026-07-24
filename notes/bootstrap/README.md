# Bootstrapping a Claude Code session the way this project runs

This directory is the answer to "what prompts do you give Claude?" in
reusable form. There is no elaborate prompt engineering: the standing
instructions live in a repo file + persistent memory, and the per-session
prompts are one-liners. This kit packages both.

## Contents

- `CLAUDE.md` — the distilled standing instructions. Claude Code
  automatically loads a repo-root `CLAUDE.md` into every session, so
  copying this file to the repo root is the whole "system prompt".
- `memory-seed/` — our accumulated durable memories (reference facts and
  process rules), scrubbed for publication. These are the files Claude
  Code's per-project memory would contain after months of sessions;
  seeding them means a fresh setup starts with the lessons pre-learned.

## How to bootstrap

1. Copy `CLAUDE.md` to the repo root of the project.
2. Find the project's memory directory. Claude Code keeps it at
   `~/.claude/projects/<project-slug>/memory/` where the slug is the
   repo's absolute path with separators replaced by dashes (it is created
   on first session; check the path Claude reports in its system prompt).
3. Copy the contents of `memory-seed/` into that memory directory.
4. Write a fresh `MEMORY.md` index there: one line per file, format
   `- [Title](file.md) — one-line hook`. (Ours indexes each reference and
   feedback file; regenerate rather than copying, since yours may differ.)
5. Create an initial `project_resume_state.md` with a single entry:
   the goal, the reference sha1, the build command, and "nothing started
   yet". Claude maintains it from then on.
6. First prompt: `read CLAUDE.md and the notes, then continue the decomp`
   — or just state a goal. Subsequent sessions: `continue` or
   `pick up where you left off`.

## What the per-session prompts actually look like

Verbatim style from this project's history:

- `continue`
- `ok so lets pickup from where you left off`
- `When a match occurs push a pr to the rmz3 upstream for the dev to review`
  (a standing directive, given once — Claude records it in memory)
- `dont assume anything is ruled out permanetly, question assumptions and
  search the web for answers` (ditto)
- `search each and every link in notes/urls-of-gba-decomps/list-of-decomps.md
  I want you to extract best practices better attempts and any and all
  solutions ... do not ignore or de prioritize the current workflow, this
  should be additive.` (a one-off research directive; produced the survey
  under notes/urls-of-gba-decomps/)

The division of labor: the human sets goals, reviews results, makes
judgment calls (what to ship upstream, what to park); Claude does the
reconstruction, verification, tooling, and documentation, and carries
state across sessions through the memory files.
