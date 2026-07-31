# Ghidra + pyghidra-mcp — the second decompiler (Linux/macOS)

A free second opinion for the functions m2c can't finish: PC-relative
literal pools (m2c emits `M2C_ERROR`) and gnarly control flow. Ghidra
recovers *semantics*; it does not predict agbcc's register allocation —
use it to get correct structure, then match with the lever library.

## Install (scripts/setup.sh does all of this)

- **JDK 21** (Temurin). Ghidra 12.x requires 21; newer JDKs are rejected.
  - Debian/Ubuntu: `sudo apt install temurin-21-jdk` (Adoptium repo) or
    `sdk install java 21-tem` via SDKMAN.
  - macOS: `brew install --cask temurin@21`.
- **Ghidra 12.x** — download the release zip from
  `https://github.com/NationalSecurityAgency/ghidra/releases`, unzip
  anywhere, export `GHIDRA_INSTALL_DIR=/path/to/ghidra_12.x`.
- **pyghidra-mcp** — `pipx install pyghidra-mcp` (or pip in a venv).

## MCP wiring (`.mcp.json` in the repo root)

```json
{
  "mcpServers": {
    "pyghidra": {
      "command": "python3",
      "args": ["-m", "pyghidra_mcp", "-t", "stdio", "ROM_PATH.gba"],
      "env": {
        "GHIDRA_INSTALL_DIR": "/opt/ghidra_12.1",
        "JAVA_HOME": "/usr/lib/jvm/temurin-21-jdk-amd64"
      }
    }
  }
}
```

Replace `ROM_PATH.gba` with the reference ROM. **First start is slow** —
the 8 MB image gets a full analysis pass (several minutes); the project
is cached so later starts are fast. Restart the session to pick the
server up.

## Loading a GBA ROM correctly

A raw `.gba` is not an ELF. If you drive Ghidra manually instead of
through pyghidra-mcp:

- language `ARM:LE:32:v4t` (the GBA CPU, little-endian),
- rebase the image to `0x08000000`,
- for Thumb functions set the `TMode` context register to 1 at the entry
  before creating the function, or it decodes as ARM.

## Usage pattern

- `decompile_function` at the target address for structure; compare with
  m2c's output. **Trust a reconstruction most when m2c and Ghidra agree
  on the structure** — then byte-match it with the diff loop.
- `list_xrefs` / `search_code` to find callers and sibling functions
  that may already be decompiled (the sibling-first rule).
- Apply the repo's symbols so output names things: most functions encode
  their address in the `FUN_08xxxxxx` name already; a `sym.txt` from the
  linker map resolves data globals.
