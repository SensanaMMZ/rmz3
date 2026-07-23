// 46 of 52 bytes. The loop matches exactly; the target keeps a dead
// `cmp r1, r2 / bne` after the loop that agbcc threads away from every
// arrangement tried (break, duplicated return NULL, compound while,
// ternary, assign-then-return).
struct Entity* unused_080e14d4(u8 id, struct Entity* e) {
  struct EntityHeader* h = gElfHeaderPtr;
  struct Entity* sentinel = (struct Entity*)&h->next;

  if (e == NULL) {
    e = sentinel;
  }
  do {
    e = e->prev;
  } while (e != sentinel && e->id != id);

  if (e == sentinel) {
    return NULL;
  }
  return e;
}
