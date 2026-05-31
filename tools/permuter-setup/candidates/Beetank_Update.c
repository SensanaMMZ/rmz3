struct Beetank {
  struct Entity s;
  struct Body body;
  u8 unk_b4[6];
  u8 unk_ba;
};

void FUN_0807be50(struct Enemy* p);

void Beetank_Update(struct Enemy* p) {
  s32 v, a, b;
  if ((p->body).status & 0x200) {
    {
      u32 tbl, id;
      EntityFunc** routine_table;
      tbl = (u32)gEnemyFnTable;
      id = (((struct Entity*)p)->id) << 2;
      routine_table = (EntityFunc**)(tbl + id);
      *(u32*)(((struct Entity*)p)->mode) = 2;
      ((struct Entity*)p)->onUpdate = (void*)(*routine_table)[2];
    }
    Beetank_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  FUN_0807be50(p);
  v = PushoutToLeft1((p->s).coord.x + (4 << 8), (p->s).coord.y - (4 << 8));
  if (v != 0) (p->s).coord.x += v;
  v = PushoutToRight1((p->s).coord.x - (4 << 8), (p->s).coord.y - (4 << 8));
  if (v != 0) (p->s).coord.x += v;
  a = FUN_08009f6c((p->s).coord.x - (16 << 8), (p->s).coord.y - (6 << 8));
  b = FUN_08009f6c((p->s).coord.x + (16 << 8), (p->s).coord.y - (6 << 8));
  if (a < b) {
    (p->s).coord.y = a;
  } else {
    (p->s).coord.y = b;
  }
  if (IsFrozen(&p->s)) {
    ((struct Beetank*)p)->unk_ba = (p->s).mode[1];
  } else {
    (sUpdates2[(p->s).mode[1]])(p);
  }
}
