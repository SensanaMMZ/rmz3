void saveSram(struct SramState* s) {
  struct SaveHeader header;
  u32 n = 0x820;
  switch (s->busStatus) {
    case 0:
      s->retryCount = 3;
      s->useBackup = 0;
      s->busStatus = 1;
      // fallthrough
    case 1:
      s->wramAddr = s->start;
      s->sramAddr = (u8*)(0x0E000000 + (s->useBackup * 6 + s->slot) * 0xAAA);
      s->remaining = s->length;
      header.INTI = *(u32*)sINTI;
      header.checksum = 0;
      {
        s32 i = s->length;
        if (i != 0) {
          do {
            header.checksum += *s->wramAddr;
            s->wramAddr++;
            i--;
          } while (i != 0);
        }
      }
      header.size = s->length;
      header.unk_c = 0xb;
      header.pad_d = 6;
      header.idx = s->slot;
      header.unk_f = 1;
      if (WriteSramEx((u8*)&header, s->sramAddr, 0x10) != 0) {
        s32 mask = 0xFFFF;
        if (--s->retryCount != 0) {
          return;
        }
        gSramState.unk_1c |= mask;
        s->busStatus = 3;
        break;
      }
      s->wramAddr = s->start;
      s->sramAddr += 0x10;
      s->busStatus = 2;
      break;
    case 2:
      n = 0x820;
      if (s->remaining <= n) {
        n = s->remaining;
        s->busStatus = 3;
      }
      if (WriteSramEx(s->wramAddr, s->sramAddr, n) != 0) {
        s32 mask = 0xFFFF;
        if (--s->retryCount == 0) {
          gSramState.unk_1c |= mask;
          s->busStatus = 3;
          break;
        }
        s->busStatus = 1;
        break;
      }
      s->wramAddr += 0x820;
      s->sramAddr += 0x820;
      s->remaining -= n;
      break;
    case 3:
      if (s->useBackup == 0) {
        s->retryCount = 3;
        s->useBackup = 1;
        s->busStatus = 1;
      } else {
        if (gSramState.unk_1c == 0) {
          gSramState.unk_1c = 1;
        }
        s->unk_00 = 0;
        *(u16*)&s->status = 0;
      }
      break;
  }
}
