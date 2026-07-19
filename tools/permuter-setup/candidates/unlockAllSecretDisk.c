void unlockAllSecretDisk(u8* flagbits) {
  u8 i;
  gStageDiskManager.disk = flagbits;
  {
    vu32 tmp = 0;
    CpuFastSet((void*)&tmp, flagbits, 0x01000008);
  }
  {
    vu32 tmp = 0;
    CpuSet((void*)&tmp, flagbits + 0x20, 0x05000004);
  }
  for (i = 0; i <= 0xb3; i++) {
    gStageDiskManager.disk[i >> 2] |= 1 << (i & 3);
    gStageDiskManager.disk[i >> 2] |= 0x10 << (i & 3);
  }
  clearStageDisk();
}
