extern u8 (*gUnlockedElfPtr)[];
bool8 isElfUsed_2(struct Zero* z, cyberelf_t elfID) {
  cyberelf_t* satelites;
  if ((*gUnlockedElfPtr)[elfID] & 1) {
    satelites = (z->unk_b4.status).asset.satelites;
    if (z->inCyberSpace) {
      return 1;
    }
    if ((*gUnlockedElfPtr)[elfID] & 2) {
      return 1;
    }
    if (satelites[0] == elfID) {
      return 1;
    }
    if (satelites[1] == elfID) {
      return 1;
    }
  }
  return 0;
}
