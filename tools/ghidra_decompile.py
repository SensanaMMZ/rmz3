"""Decompile a retail ROM function by address with Ghidra (harness-roadmap #2).

Usage: python3 tools/ghidra_decompile.py 0x08050090
Loads baseimg.gba as ARM:LE:32:v4t rebased to 0x08000000, sets Thumb at the
address, creates the function, analyzes, and prints the pseudo-C. Second-opinion
decompiler for structural holdouts m2c can't decode (PC-relative literals, etc).
"""
import os, sys
os.environ['GHIDRA_INSTALL_DIR'] = r'C:\Users\SaroGamingPC\decomp-tools\ghidra_12.1.2_PUBLIC'
os.environ['JAVA_HOME'] = r'C:\Users\SaroGamingPC\decomp-tools\jdk-21.0.11+10'

import pyghidra
pyghidra.start()

rom = r'C:\Users\SaroGamingPC\MMZ5-X8-Base\rmz3\baseimg.gba'
addr_hex = sys.argv[1] if len(sys.argv) > 1 else '0x08050090'  # FUN_08050090 (anubis holdout)
thumb = True

with pyghidra.open_program(rom, language='ARM:LE:32:v4t', analyze=False) as flat:
    prog = flat.getCurrentProgram()
    space = prog.getAddressFactory().getDefaultAddressSpace()
    # rebase raw ROM to 0x08000000
    base = space.getAddress(0x08000000)
    try:
        prog.withTransaction("rebase", lambda: prog.setImageBase(base, True))
    except Exception:
        txid = prog.startTransaction("rebase")
        prog.setImageBase(base, True)
        prog.endTransaction(txid, True)

    a = space.getAddress(int(addr_hex, 16))

    # set Thumb (TMode=1) at the address, create a function, then analyze locally
    from ghidra.program.model.lang import Register
    txid = prog.startTransaction("thumb+func")
    try:
        tmode = prog.getProgramContext().getRegister("TMode")
        if tmode is not None and thumb:
            prog.getProgramContext().setValue(tmode, a, a, __import__('java').math.BigInteger.ONE)
    except Exception as e:
        print("tmode set skipped:", e)
    from ghidra.app.cmd.function import CreateFunctionCmd
    CreateFunctionCmd(a).applyTo(prog)
    prog.endTransaction(txid, True)

    flat.analyzeChanges(prog)

    fn = prog.getFunctionManager().getFunctionContaining(a)
    if fn is None:
        print("NO FUNCTION created at", addr_hex); sys.exit(2)

    from ghidra.app.decompiler import DecompInterface
    di = DecompInterface()
    di.openProgram(prog)
    res = di.decompileFunction(fn, 90, None)
    print("=== decompiled", fn.getName(), "@", addr_hex, "===")
    if res.decompileCompleted():
        print(res.getDecompiledFunction().getC())
    else:
        print("DECOMPILE FAILED:", res.getErrorMessage())
