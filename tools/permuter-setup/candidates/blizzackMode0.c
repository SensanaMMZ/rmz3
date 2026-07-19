void blizzackMode0(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb4, 0));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    *(u16*)((u8*)(p->s).unk_2c + 0xbc) = 0x6400;
    (p->s).mode[2] = 0;
    (p->s).work[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  if (((struct Entity*)(p->s).scriptEntity)->id & 1) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 1;
  }
}
