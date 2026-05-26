def apply(config, args):
    config["baseimg"] = "rmz3.gba"
    config["myimg"] = "build/rmz3/rmz3.gba"
    config["mapfile"] = "build/rmz3/rmz3.map"
    config["arch"] = "arm32"
    config["map_format"] = "gnu"
    config["build_dir"] = "build/rmz3/"
    config["source_directories"] = ["src", "asm", "include"]
    config["objdump_executable"] = "/opt/devkitpro/devkitARM/bin/arm-none-eabi-objdump.exe"
    config["makeflags"] = []
