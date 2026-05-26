void FUN_0807be20(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    (p->s).d.y = (p->s).mode[2];
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}
