void FUN_080d7e5c(struct Body* body, struct Coord* r1, struct Coord* r2) {
  struct CollidableEntity* self = body->parent;
  struct CollidableEntity* other = body->enemy->parent;
  if ((other->s).kind != 0) {
    return;
  }
  if ((self->s).coord.y > (other->s).coord.y) {
    if ((self->s).work[0] & 1) {
      return;
    }
    (self->s).mode[1] = 1;
  } else {
    if (!((self->s).work[0] & 1)) {
      return;
    }
    (self->s).mode[1] = 2;
  }
  (self->s).mode[2] = (other->s).kind;
  *(u8*)((u8*)other + 0x119) = 1;
  gStageRun.vm.unk_004 |= 1;
  *(struct Entity**)((u8*)self + 0xb4) = (struct Entity*)other;
}
