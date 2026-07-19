void Beetank_Update(struct Enemy* p) {
  if (*(u32*)((u8*)p + 0x8c) & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Beetank_Die(p);
  } else {
    s32 push, a, b;

    (sUpdates1[(p->s).mode[1]])(p);
    FUN_0807be50(p);

    push = PushoutToLeft1((p->s).coord.x + 0x400, (p->s).coord.y - 0x400);
    if (push != 0) (p->s).coord.x += push;
    push = PushoutToRight1((p->s).coord.x - 0x400, (p->s).coord.y - 0x400);
    if (push != 0) (p->s).coord.x += push;

    a = FUN_08009f6c((p->s).coord.x - 0x1000, (p->s).coord.y - 0x600);
    b = FUN_08009f6c((p->s).coord.x + 0x1000, (p->s).coord.y - 0x600);
    (p->s).coord.y = (a < b) ? a : b;

    if (IsFrozen(&p->s)) {
      *(u8*)((u8*)p + 0xba) = (p->s).mode[1];
    } else {
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
}
