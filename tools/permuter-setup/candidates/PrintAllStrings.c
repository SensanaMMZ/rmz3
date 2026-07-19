void PrintAllStrings(void) {
  s32 i;
  struct CharTile* node = gTextPrinter.cur;
  if (node != 0) {
    struct CharTile* prev = gTextPrinter.used;
    do {
      struct CharTile* next = node->next;
      node->next = prev;
      prev = node;
      node = next;
    } while (node != 0);
    gTextPrinter.used = prev;
  }
  gTextPrinter.cur = 0;
  for (i = 0; i < gTextPrinter.len; i++) {
    printStringWithLen(gTextPrinter.x[i], gTextPrinter.y[i], gTextPrinter.strings[i],
                       gTextPrinter.progress[i]);
  }
}
