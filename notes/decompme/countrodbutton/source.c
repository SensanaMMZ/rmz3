u8 CountRodButton(struct Zero* z, bool8 isSubWeapon) {
  u8 i, count;
  KEY_INPUT input;
  if (isSubWeapon) {
    u8 mode = (z->unk_b4).keyMap.attackMode;
    if (mode == 0)      input = (z->input).mapping.main;   /* type A */
    else if (mode == 1) input = (z->input).mapping.sub;    /* type B */
    else if (mode >= 2) input = (z->input).mapping.main;   /* type C */
    else                input = (z->input).mapping.main;   /* unreachable: blocks cross-jump */
  } else {
    input = (z->input).mapping.main;
  }
  count = 0;
  for (i = 0; i < 32; i++) {
    if (((z->input).history[i] & input) && (((z->input).history[i + 1] & input) == 0)) {
      count++;
    }
  }
  return count;
}
