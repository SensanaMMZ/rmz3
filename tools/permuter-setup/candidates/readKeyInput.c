static void readKeyInput(struct KeyState *j, s32 retry) {
  s16 i;

  j->last = j->input;
  if (retry != 0) {
    j->firstRead = 0;
    return;
  }
  j->firstRead = 1;
  j->input = ~REG_KEYINPUT;
  j->pressed = j->input & ~j->last;
  j->field3_0x6 = 0;
  for (i = 0; i < 10; i++) {
    if ((j->input >> i) & 1) {
      if ((s8)j->unk_0a[i] == 0) {
        j->field3_0x6 |= 1 << i;
        j->unk_0a[i] = ((j->pressed >> i) & 1) ? j->field6_0x14 : j->field7_0x15;
      }
      j->unk_0a[i]--;
    } else {
      j->unk_0a[i] = 0;
    }
  }
}
