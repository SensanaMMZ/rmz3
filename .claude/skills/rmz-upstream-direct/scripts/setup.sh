#!/bin/sh
# One-shot environment bootstrap for upstream-direct rmz3 decomp work.
# Linux (apt) and macOS (brew). Idempotent — safe to re-run.
#
#   setup.sh [--dir WORK] [--corpus] [--ghidra] [--rom PATH]
#
#   --dir WORK   parent directory for checkouts   (default: ~/decomp)
#   --corpus     also shallow-clone the 17-repo GBA decomp corpus
#   --ghidra     also install JDK21 + Ghidra + pyghidra-mcp and write .mcp.json
#   --rom PATH   copy this reference ROM into the repo (you must supply
#                your own legal dump; nothing is downloaded)
set -eu

WORK="$HOME/decomp"; CORPUS=0; GHIDRA=0; ROM=""
while [ $# -gt 0 ]; do
  case "$1" in
    --dir) WORK="$2"; shift 2;;
    --corpus) CORPUS=1; shift;;
    --ghidra) GHIDRA=1; shift;;
    --rom) ROM="$2"; shift 2;;
    *) echo "unknown arg $1"; exit 2;;
  esac
done
mkdir -p "$WORK"; cd "$WORK"

OS="$(uname -s)"
say() { printf '\n== %s\n' "$*"; }

say "dependencies"
if [ "$OS" = "Linux" ]; then
  sudo apt-get update -qq
  sudo apt-get install -y build-essential git python3 python3-pip pipx \
    libpng-dev binutils-arm-none-eabi
elif [ "$OS" = "Darwin" ]; then
  command -v brew >/dev/null || { echo "install Homebrew first"; exit 1; }
  brew install libpng arm-none-eabi-binutils python3 pipx || true
fi

say "agbcc"
[ -d agbcc ] || git clone --depth 1 https://github.com/pret/agbcc
( cd agbcc && ./build.sh )

say "rmz3 (upstream)"
[ -d rmz3 ] || git clone https://github.com/mmzret/rmz3
( cd agbcc && ./install.sh ../rmz3 )

if [ -n "$ROM" ]; then
  say "reference ROM"
  cp "$ROM" rmz3/
fi

say "first build + gate"
( cd rmz3 && make -j"$(getconf _NPROCESSORS_ONLN)" compare ) \
  && echo "GATE OK — environment verified" \
  || echo "gate not green yet — check the ROM placement (see repo README)"

if [ "$CORPUS" = 1 ]; then
  say "decomp corpus (shallow clones into $WORK/corpus)"
  mkdir -p corpus; cd corpus
  for r in jellees/bkgr Normmatt/bof FireEmblemUniverse/fireemblem6j \
           FireEmblemUniverse/fireemblem8u laqieer/fireemblem8j \
           gsret/goldensun StanHash/fomt jiangzhengwenjz/katam \
           metroidret/mzm pret/pokeemerald pret/pokefirered pret/pmd-red \
           pret/pokepinballrs pret/pokeruby SAT-R/sa2 \
           jiangzhengwenjz/csm3 atasro2/sma2 zeldaret/tmc; do
    d="$(basename "$r")"
    [ -d "$d" ] || git clone --depth 1 "https://github.com/$r" || true
  done
  cd ..
fi

if [ "$GHIDRA" = 1 ]; then
  say "JDK 21 + Ghidra + pyghidra-mcp"
  if [ "$OS" = "Linux" ]; then
    sudo apt-get install -y temurin-21-jdk 2>/dev/null \
      || sudo apt-get install -y openjdk-21-jdk
    JAVA_HOME="$(dirname "$(dirname "$(readlink -f "$(command -v java)")")")"
  else
    brew install --cask temurin@21 || true
    JAVA_HOME="$(/usr/libexec/java_home -v 21)"
  fi
  if [ ! -d "$WORK/ghidra" ]; then
    echo "fetching latest Ghidra release..."
    URL="$(python3 -c 'import json,urllib.request;r=json.load(urllib.request.urlopen("https://api.github.com/repos/NationalSecurityAgency/ghidra/releases/latest"));print([a["browser_download_url"] for a in r["assets"] if a["name"].endswith(".zip")][0])')"
    curl -L -o /tmp/ghidra.zip "$URL"
    mkdir -p "$WORK/ghidra" && unzip -q /tmp/ghidra.zip -d "$WORK/ghidra"
  fi
  GID="$(find "$WORK/ghidra" -maxdepth 1 -type d -name 'ghidra_*' | head -1)"
  pipx install pyghidra-mcp || pipx upgrade pyghidra-mcp || true
  ROMFILE="$(cd rmz3 && ls *.gba 2>/dev/null | head -1 || true)"
  cat > rmz3/.mcp.json <<JSON
{
  "mcpServers": {
    "pyghidra": {
      "command": "python3",
      "args": ["-m", "pyghidra_mcp", "-t", "stdio", "${ROMFILE:-rmz3.gba}"],
      "env": {
        "GHIDRA_INSTALL_DIR": "$GID",
        "JAVA_HOME": "$JAVA_HOME"
      }
    }
  }
}
JSON
  echo "wrote rmz3/.mcp.json (first MCP start analyzes the ROM — slow once)"
fi

say "done"
echo "Repo:    $WORK/rmz3   (gate: scripts/gate.sh)"
[ "$CORPUS" = 1 ] && echo "Corpus:  $WORK/corpus (search: scripts/corpus-grep.sh)"
[ "$GHIDRA" = 1 ] && echo "Ghidra:  $GID (MCP: restart your session inside the repo)"
