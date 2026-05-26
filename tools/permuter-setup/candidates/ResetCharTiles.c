// Walk tilelist backward via pointer (matches `subs r1, #8` pattern).
// u32 id (not u16) avoids per-iter mask on the decrement.
#ifndef NULL
#define NULL ((void*)0)
#endif
void ResetCharTiles(void) {
  struct TextPrinter* p = &gTextPrinter;
  struct CharTile* tile = &p->tilelist[79];
  u32 id = 894;
  s32 i = 79;
  p->freelist = NULL;
  do {
    tile->tileID = id;
    tile->next = p->freelist;
    p->freelist = tile;
    tile--;
    id -= 2;
    i--;
  } while (i >= 0);
  p->used = NULL;
  p->cur = NULL;
  p->len = 0;
}
