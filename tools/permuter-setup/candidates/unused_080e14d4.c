// Speculative — searches a doubly-linked-list of Entity for one with
// .field_9 == id, starting from `e` or a global sentinel.
// gOverworld + 20 is the sentinel (head of a circular list).
#ifndef NULL
#define NULL ((void*)0)
#endif
static struct Entity* unused_080e14d4(u8 id, struct Entity* e) {
  struct Entity* head = (struct Entity*)((u8*)&gOverworld + 20);
  struct Entity* p;
  if (e == NULL) e = head;
  do {
    p = *(struct Entity**)((u8*)e + 4);  // e->next
    e = p;
    if (p == head) return NULL;
  } while (*((u8*)p + 9) != id);
  if (p == head) return NULL;
  return p;
}
