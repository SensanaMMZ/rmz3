# Scratch repair paste-kits (2026-07-25)

Both scratches were posted with broken context (ldwqE: empty; C3UWS:
raw ctx.c that agbcc rejects). These files compile clean under the
exact decomp.me agbcc preset flags. To repair, for each scratch:

1. Open the scratch (you own both now).
2. Context tab -> select all -> paste the matching `*-context.c`.
3. Source tab -> replace contents with the matching `*-source.c`.
4. Compile. Expected scores: ldwqE ~2 insns off (127/129);
   C3UWS 22 bytes off in the buffer block.

| scratch | context | source |
|---|---|---|
| https://www.decomp.me/scratch/ldwqE | ldwqE-context.c | ldwqE-source.c |
| https://www.decomp.me/scratch/C3UWS | C3UWS-context.c | C3UWS-source.c |
