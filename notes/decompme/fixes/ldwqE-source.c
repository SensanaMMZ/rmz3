void FUN_080e58bc(struct Elf* p) {

  struct Elf* e = *(struct Elf**)p->buffer;
  u8 z = (p->s).work[2];
  u8 fl;
  if (z == 0) {
    u8* buf = e->buffer;
    if ((p->s).work[3] == buf[0]) {
      return;
    }
    fl = (p->s).flags & ~(1 << 0);
  } else {
    u8* buf = e->buffer;
    if ((p->s).work[3] == buf[1]) {
      return;
    }
    fl = (p->s).flags & ~(1 << 0);
    z = 0;
  }
  fl &= ~(1 << 1);
  (p->s).flags = fl;
  (p->body).status = z;
  (p->body).prevStatus = z;
  (p->body).invincibleTime = z;
  (p->s).flags &= ~(1 << 2);
  { u32 tbl, id; EntityFunc** routine_table; tbl = (u32)(gElfFnTable); id = (((struct Entity*)p)->id) << 2; routine_table = (EntityFunc**)(tbl + id); *(u32*)(((struct Entity*)p)->mode) = 3; ((struct Entity*)p)->onUpdate = (void*)(*routine_table)[3]; };


}
