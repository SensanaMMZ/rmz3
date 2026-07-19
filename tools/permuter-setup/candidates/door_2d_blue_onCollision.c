// door_2d_blue onCollision near-miss seed. Macros pre-expanded (appended
// post-cpp): ENTITY_PLAYER=0, PIXEL(8)=0x800, FLAG(gameflags,FLAG_2)=
// (gameflags[0]&4), TRUE=1. Off by a z<->flag2 r4/r5 allocation tie that
// couples with whether agbcc cross-jumps the duplicated mode[2]=story store.
static void onCollision(struct Body* body, struct Coord* r1, struct Coord* r2) {
  u8 flag2;
  struct Solid* door = (struct Solid*)body->parent;
  struct Zero* z = (struct Zero*)(body->enemy)->parent;
  if ((z->s).kind != 0) {
    return;
  }
  if ((door->s).coord.y < (z->s).coord.y) {
    return;
  }
  if ((door->s).coord.y - (z->s).coord.y > 0x800) {
    return;
  }
  flag2 = (door->s).work[0] & 2;
  if (flag2) {
    u8 story = (gCurStory.s.gameflags[0] & 4);
    if (story) {
      return;
    }
    if ((door->s).coord.x > (z->s).coord.x) {
      (door->s).mode[1] = 1;
    } else {
      (door->s).mode[1] = 2;
    }
    (door->s).mode[2] = story;
  } else {
    if ((door->s).coord.x > (z->s).coord.x) {
      if ((door->s).work[0] & 1) {
        return;
      }
      (door->s).mode[1] = 1;
    } else {
      if (!((door->s).work[0] & 1)) {
        return;
      }
      (door->s).mode[1] = 2;
    }
    (door->s).mode[2] = flag2;
  }
  z->isAreaChange = 1;
  gStageRun.vm.unk_004 |= 1;
  *(struct Zero**)door->props.raw = z;
}
