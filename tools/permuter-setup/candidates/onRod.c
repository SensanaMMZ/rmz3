// The orig keeps &z->restriction live across the if/else AND the move bit
// set — agbcc recomputes the offset if the bitfield writes are separate
// statements. Permuter may find a phrasing that keeps the pointer live.
static void onRod(struct Zero* z) {
  struct Zero_b4* b4 = &(z->unk_b4);

  if ((b4->status).mainWeapon == 2 /* WEAPON_ROD */) {
    (z->restriction).mainCharge = 1;
  } else {
    (z->restriction).subCharge = 1;
  }
  (z->restriction).move = 1;

  (rodRoutine[(z->unk_b4).attackMode[1]])(z);
}
