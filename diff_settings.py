def apply(config, args):
    # Primary diff tool is now objdiff-cli (tools/objdiff-cli.exe + tools/diff.sh).
    # This file is kept for the rare case where asm-differ's rendered output
    # is preferred; it has known _post_process_data_pools crashes on some
    # functions so don't rely on it as truth. baseimg.gba is a snapshot of
    # the matching ROM kept aside (see tools/refresh-expected.sh).
    config["baseimg"] = "baseimg.gba"
    config["myimg"] = "rmz3.gba"
    config["mapfile"] = "build/rmz3/rmz3.map"
    config["arch"] = "arm32"
    config["map_format"] = "gnu"
    config["build_dir"] = "build/rmz3/"
    config["source_directories"] = ["src", "asm", "include"]
    config["objdump_executable"] = "C:/devkitPro/devkitARM/bin/arm-none-eabi-objdump.exe"
    config["makeflags"] = []
