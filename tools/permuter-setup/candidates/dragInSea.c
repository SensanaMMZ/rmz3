struct SeaOW { u8 _pad[0x2c00c]; s32 sea; };
extern struct SeaOW gOverworld;
void dragInSea(struct Entity* p) {
  s32 sea = gOverworld.sea;
  if (sea > p->coord.y) {
    p->coord.y = sea;
  }
}
