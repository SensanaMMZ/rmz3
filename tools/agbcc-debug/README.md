# Instrumented agbcc (analysis only)

Not part of the build. These are the two patched GCC 2.9 sources that make
agbcc explain its register-allocation decisions; see
`notes/agbcc-allocator-instrumented.md` for what they revealed.

## Rebuild

```sh
git clone --depth 1 https://github.com/pret/agbcc agbcc-src
cd agbcc-src
cp <this dir>/global.c.instrumented       gcc/global.c
cp <this dir>/local-alloc.c.instrumented  gcc/local-alloc.c
export DEVKITARM=/c/devkitPro/devkitARM
make -C gcc -j1          # MUST be serial: -j races the genrtl.h generator
```

The binary lands at `gcc/agbcc`. Keep it out of `tools/agbcc/` — the shipping
compiler must stay stock.

## Use

```sh
AGBCC_TRACE_ALLOC=1 ./agbcc -mthumb-interwork -O2 -fshort-enums \
    -fhex-asm -o out.s < preprocessed.i 2> trace.txt
```

Tracing is off unless the env var is set, and it does not change codegen
(verified byte-identical with tracing on and off).
