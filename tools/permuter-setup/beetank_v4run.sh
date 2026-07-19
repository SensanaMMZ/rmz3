#!/bin/bash
# Long unattended beetank permuter run with match-surfacing.
# Launches the permuter with many workers and watches the best saved
# candidate; if the score drops to a verify-worthy level it copies the
# candidate aside and EXITS (so the background-task layer notifies us).
# Otherwise it grinds forever. Best candidates land in output-<score>-N/.
set -u
REPO="$(cd "$(dirname "$0")/../.." && pwd)"
SET="$REPO/tools/permuter-setup/Beetank_Update_v4"
PYEXE="python3"
export PATH="/c/devkitPro/devkitARM/bin:$PATH"
cd "$REPO"

# verify-worthy threshold: current floor is 280; anything <= this is a real
# improvement worth a manual full-ROM check (a byte match modulo link relocs
# scores only the bl-to-undefined residual, well under this).
THRESH=120

"$PYEXE" tools/decomp-permuter/permuter.py -j 12 "$SET" >> /tmp/perm_beetank_v4.log 2>&1 &
PERMPID=$!
echo "permuter pid $PERMPID launched; threshold=$THRESH; $(date)"

best=99999
while kill -0 "$PERMPID" 2>/dev/null; do
  cur=$(ls -d "$SET"/output-* 2>/dev/null | sed 's|.*/output-||; s|-[0-9]*$||' | sort -n | head -1)
  if [ -n "${cur:-}" ] && [ "$cur" -lt "$best" ] 2>/dev/null; then
    best=$cur
    echo "$(date) new best = $best"
    if [ "$best" -le "$THRESH" ]; then
      d=$(ls -d "$SET"/output-"$best"-* 2>/dev/null | head -1)
      echo "=== BEETANK CANDIDATE <= THRESH ($best): $d — stopping for verification ==="
      rm -rf "$SET/HIT"; cp -r "$d" "$SET/HIT"
      kill "$PERMPID" 2>/dev/null
      break
    fi
  fi
  sleep 90
done
echo "longrun monitor exiting; final best=$best; $(date)"
