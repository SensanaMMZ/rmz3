# Published scratches

Created with `tools/scratch_up.py`. Claim links attach an anonymous scratch to
your decomp.me account (log in first, then open the link); after claiming, paste
the ask from the matching `*_ask.md` into the About tab.

| function | scratch | state |
|---|---|---|
| Beetank_Update | https://www.decomp.me/scratch/gwvlA | claimed; community fork ZBgsB reached 805 with pins+barriers (semantically invalid — `yOffset` read before assignment) |
| readKeyInput | https://www.decomp.me/scratch/DXXvK | **SOLVED** by TsilaAllaoui (fork 2076R, score 0) — the s64 live-range-split idiom; shipped as upstream PR #46 |
| childreStun | https://www.decomp.me/scratch/asMGq | anonymous — claim: `/scratch/asMGq/claim?token=eyJzbHVnIjoiYXNNR3EifQ.2pu4x4NEVwp9fs8DmaoJ-XmJVsc` |
| CopyBgMap | https://www.decomp.me/scratch/UgMGD | anonymous, score 535/4000 — claim: `/scratch/UgMGD/claim?token=eyJzbHVnIjoiVWdNR0QifQ.mS36tNFckM46SjPIs1ieMAne3Do` |

## Lessons for the publisher

- Context must be valid standalone C: no bitfield shorthand, spell out every
  typedef the source touches (a bad context silently scores 100%-unmatched).
- The source must be the complete function — slicing it out of a `#if MODERN`
  dual-form truncates the closing braces.
- `--inc` extraction only works for real project `.inc`s with
  `thumb_func_start`; `asm/wip/*.inc` bodies are bare, so prepend
  `.syntax unified` / `.thumb` / `glabel <fn>` and pass `--target`.
- Always re-fetch the scratch after publishing and check `score < max_score`;
  equality means it did not compile.
