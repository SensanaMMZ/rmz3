// Original asm doesn't CSE the two z->slow loads — both load via ldrb.
// agbcc on the natural C does CSE. Permuter may find a rephrasing that
// suppresses the optimization.
s16 GetSplitHeavenSpeed(struct Zero* z) {
  if (z->slow != 0) {
    return 0x100 - z->slow;
  }
  return 0x100;
}
