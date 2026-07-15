#include "gfx.h"
#include "global.h"
#include "sound.h"
#include "system.h"
#include "text.h"

static const u16* const gTextOffsetTable[20];
static const char_t* const gTextTable[20];
static const u32 sVramOffsets[2];

extern const struct ColorGraphic gDialogGraphics[];

static void resetTextWindow(struct TextWindowText* t);
static void setupTextWindow(struct TextWindowText* t);
static void _UpdateTextWindow(struct TextWindowText* t);
static bool32 isMugshotChanged(struct TextWindowText* t);

void ClearTextWindow(void* bg0) {
  struct TextWindowText* t;
  gTextPrinter.startX = 0;
  gTextPrinter.endX = 30;
  gTextPrinter.startY = 0;
  gTextPrinter.endY = 22;
  gTextWindow.frame = 0;
  gTextWindow.bg0Mask = bg0;
  *(u32*)&gTextWindow.text.props = 0;
  t = &gTextWindow.text;
  t->mode = 0;
}

void UpdateTextWindow(void) {
  gTextWindow.frame++;
  _UpdateTextWindow(&gTextWindow.text);
}

static void unused_080ea664(void) { gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN0_ON; }

static void unused_080ea678(TextID n) {
  struct TextWindowText* t;
  PrintTextWindow(n, TW_OPTION);
  t = &gTextWindow.text;
  t->flag |= 1;
}

void PrintNormalMessage(TextID n) {
  PrintTextWindow(n, TW_NORMAL);
  return;
}

void PrintTextWindow(TextID t, u16 kind) {
  u16 ofs;
  char_t* s;
  struct TextWindowText* tw = &gTextWindow.text;
  char_t** table = (char_t**)gTextTable;
  table = &table[t >> 8];
  ofs = gTextOffsetTable[t >> 8][t & 0xFF];
  s = &((*table)[ofs]);

  if ((t & 0xFF00) == 0x100) {
    if (t == 0x100) {
      PlaySound(SE_GAIN_DISK);
    } else {
      PlaySound(SE_NOTIFICATION);
    }
  }
  tw->start = s;
  tw->textType = kind;
  resetTextWindow(tw);
  setupTextWindow(tw);
  if (tw->mugshot != 0) {
    *(u32*)&tw->props = 1;
  } else {
    *(u32*)&tw->props = 2;
  }
}

void PrintOptionMessage1(TextID t) {
  u16 ofs;
  char_t* s;
  struct TextWindowText* tw = &gTextWindow.text;
  char_t** table = (char_t**)gTextTable;
  table = &table[t >> 8];
  ofs = gTextOffsetTable[t >> 8][t & 0xFF];
  s = &((*table)[ofs]);

  tw->start = s;
  tw->textType = 1;
  if (tw->props.kind == 1) {
    tw->next = s;
    tw->mode = 1;
    tw->props.phase = 5;
  } else {
    resetTextWindow(tw);
    setupTextWindow(tw);
    if (tw->mugshot != 0) {
      *(u32*)&tw->props = 1;
    } else {
      *(u32*)&tw->props = 2;
    }
  }
  tw->flag = 1;
}

void PrintOptionMessage2(TextID n) {
  struct TextWindowText* t;
  PrintOptionMessage1(n);
  t = &gTextWindow.text;
  t->textType = 0;
}

void PrintResultInline(TextID t, bool16 ng) {
  // const char_t* table = gTextTable[t >> 8];
  // const u16 ofs = gTextOffsetTable[t >> 8][t & 0xFF];
  // const char_t* s = &table[ofs];
  u16 ofs;
  char_t* s;
  struct TextWindowText* tw = &gTextWindow.text;
  char_t** table = (char_t**)gTextTable;
  table = &table[t >> 8];
  ofs = gTextOffsetTable[t >> 8][t & 0xFF];
  s = &((*table)[ofs]);

  if (!ng) {
    PlaySound(SE_NOTIFICATION);
  } else {
    PlaySound(SE_NOT_ALLOWED);
  }

  tw->start = (char_t*)s;
  tw->textType = 0;
  resetTextWindow(tw);
  setupTextWindow(tw);
  *((u32*)&tw->props) = 3;
}

static void resetTextWindow(struct TextWindowText* t) {
  t->flag = 0;
  t->mode = 1;
  t->mugshot = 0;
  t->mugshotRight = 0;
  t->optionID = 0;
  t->unk_16 = 0;
  t->y = 1;
  t->current = t->start;
  t->next = NULL;
}

/*
  t->current の文字を1つずつみていって、特殊文字があった場合に対応する
  それ以外は特に何もしてない

  - MUGSHOT: wにそのことを反映
  - SKIP:
  - OPTION:
  - TOP: w.y を 1 に
  - BOTTOM: w.y を 13
*/
static void setupTextWindow(struct TextWindowText* t) {
  char_t* s = t->current;
  char_t unk_16 = 0xFF;
  char_t c2 = 0xFF;
  t->optional_next = NULL;
  while (*s < CHAR_NEXT) {
    if (*s == CHAR_MUGSHOT) {
      char_t c = *(++s);
      t->mugshot = c >> 1;
      t->mugshotRight = c & 1;
    } else if (*s == CHAR_F5) {
      s++;
      unk_16 = *s;
    } else if (*s == CHAR_F6) {
      s++;
      c2 = *s;
    } else if (*s == CHAR_TOP) {
      t->y = 1;
    } else if (*s == CHAR_BOTTOM) {
      t->y = 13;
    }
    s++;
  }

  if (unk_16 != 0xFF) {
    t->unk_16 = unk_16;
    for (s = t->start; *s < 0xFF; s++) {
      if (s[0] == CHAR_ANSWER && s[1] == unk_16) {
        t->next = s + 2;
        break;
      }
    }
    if (*s == 0xFF) t->next = NULL;
  } else {
    t->next = (*s <= CHAR_NEXT) ? ++s : NULL;
  }
  if (c2 != 0xFF) {
    t->optionID = (t->optionID >> 4) | (1 << 4);
    for (s = t->start; *s < 0xFF; s++) {
      if (s[0] == CHAR_ANSWER && s[1] == c2) {
        t->optional_next = s + 2;
        break;
      }
    }
  }
}

// --------------------------------------------

static void doNoTextWindow(struct TextWindowText* t);
static void mugshotMessage(struct TextWindowText* t);
static void inlineMessage(struct TextWindowText* t);
static void text_080eb6e8(struct TextWindowText* t);

// 0x080ea8e8
static void _UpdateTextWindow(struct TextWindowText* t) {
  static const TextFunc routine[] = {
      doNoTextWindow,
      mugshotMessage,
      inlineMessage,
      text_080eb6e8,
  };  // 0x083767a8
  (routine[(t->props).kind])(t);
}

static bool32 isMugshotChanged(struct TextWindowText* t) {
  char_t* s = t->next;
  bool32 result = FALSE;
  for (; *s < CHAR_NEXT; s++) {
    if (*s == CHAR_MUGSHOT) {
      s++;
      if (*s != ((t->mugshot << 1) | t->mugshotRight)) {
        result = TRUE;
      }
    }
  }
  return result;
}

// 0x080ea930
// シンボル演算(&gDialogGraphics[base+n])だと agbcc が graphic/palette のベース (共有 symbol_ref) を
// CSE してしまいプール定数が1つになる。retail は別々のプール定数なので整数リテラルで書く (upstream 準拠)。
#if MODERN
#define DIALOG_GRAPHIC(base, n) ((void*)&gDialogGraphics[(base) + (n)])
#define DIALOG_PALETTE(base, n) ((void*)&gDialogGraphics[(base) + (n)].pal)
#else
#define _gDialogGraphics 0x085a7ec4
#define _gDialogPalettes (0x085a7ec4 + 12)
#define DIALOG_GRAPHIC(base, n) ((void*)(_gDialogGraphics + ((base) * sizeof(struct ColorGraphic)) + ((n) * sizeof(struct ColorGraphic))))
#define DIALOG_PALETTE(base, n) ((void*)((_gDialogPalettes + ((base) * sizeof(struct ColorGraphic))) + ((n) * sizeof(struct ColorGraphic))))
#endif

/**
 * @brief Load msgbox and mugshot tile data into VRAM
 * @note 0x080ea930
 */
static void loadMugshot(struct TextWindowText* t, u8 mugshot) {
  // msgbox
  if (gSystemSavedataManager.msgbox == 0) {
    RequestGraphicTransfer(DIALOG_GRAPHIC(0, 0), (void*)(CHAR_BASE(0) + sVramOffsets[1]));
  } else {
    // e-card: msgbox
    RequestGraphicTransfer(DIALOG_GRAPHIC(57, gSystemSavedataManager.msgbox), (void*)(CHAR_BASE(0) + sVramOffsets[1]));
    LoadPalette(DIALOG_PALETTE(57, gSystemSavedataManager.msgbox), 0);
  }
  // mugshot
  if ((t->mugshot != NO_MUGSHOT) && (mugshot != 0)) {
    RequestGraphicTransfer(DIALOG_GRAPHIC(0, mugshot), (void*)(CHAR_BASE(0) + sVramOffsets[0]));
    LoadPalette(DIALOG_PALETTE(0, mugshot), 32);
  }
}

static const u16 MugshotLeftTileMasks[];
static const u16 MugshotRightTileMasks[];

/**
 * @brief Draw mugshot tilemap (タイルデータは loadMugshot でVRAMにロード)
 * @note 0x080ea9f0
 */
void transferMugshotTileMap(struct TextWindowText* t) {
  s16 i;
  u16* bgmap = gTextWindow.bg0Mask;

  if (gTextWindow.text.props.kind == 1 && (t->mugshot != NO_MUGSHOT)) {
    if (t->mugshotRight == 0) {
      bgmap += 1 + (t->y * 32);
      for (i = 0; i < 6; i++, bgmap += 32) {
        CopyMemory((void*)&MugshotLeftTileMasks[6 * i], bgmap, 6 * sizeof(u16));
      }
    } else {
      bgmap += 23 + (t->y * 32);
      for (i = 0; i < 6; i++, bgmap += 32) {
        CopyMemory((void*)&MugshotRightTileMasks[6 * i], bgmap, 6 * sizeof(u16));
      }
    }
  }
}

NAKED void text_080eaa7c(struct TextWindowText* t, u16 r1) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	sub sp, #0x10\n\
	mov sl, r0\n\
	lsls r1, r1, #0x10\n\
	lsrs r2, r1, #0x10\n\
	ldrb r0, [r0, #5]\n\
	str r0, [sp, #8]\n\
	ldr r0, _080EAAC8 @ =0x020308D0\n\
	ldr r7, [r0, #4]\n\
	mov r1, sl\n\
	ldrb r0, [r1, #4]\n\
	cmp r0, #1\n\
	beq _080EAAA0\n\
	b _080EABF0\n\
_080EAAA0:\n\
	ldr r1, _080EAACC @ =gSineTable\n\
	lsls r0, r2, #0x18\n\
	lsrs r0, r0, #0x17\n\
	adds r0, r0, r1\n\
	movs r2, #0\n\
	ldrsh r1, [r0, r2]\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	lsls r0, r0, #0xa\n\
	lsrs r0, r0, #0x10\n\
	str r0, [sp]\n\
	mov r3, sl\n\
	ldrb r0, [r3, #6]\n\
	cmp r0, #0\n\
	bne _080EAAD0\n\
	movs r6, #1\n\
	str r6, [sp, #4]\n\
	ldr r1, [sp]\n\
	lsls r0, r1, #0x10\n\
	b _080EAAE2\n\
	.align 2, 0\n\
_080EAAC8: .4byte 0x020308D0\n\
_080EAACC: .4byte gSineTable\n\
_080EAAD0:\n\
	movs r0, #0x1d\n\
	ldr r3, [sp]\n\
	lsls r2, r3, #0x10\n\
	asrs r1, r2, #0x10\n\
	subs r0, r0, r1\n\
	lsls r0, r0, #0x10\n\
	lsrs r0, r0, #0x10\n\
	str r0, [sp, #4]\n\
	adds r0, r2, #0\n\
_080EAAE2:\n\
	ldr r2, _080EABC8 @ =gWindowRegBuffer\n\
	ldr r6, [sp, #4]\n\
	lsls r5, r6, #0x10\n\
	asrs r5, r5, #0x10\n\
	asrs r0, r0, #0x10\n\
	mov r8, r0\n\
	adds r1, r5, r0\n\
	lsls r1, r1, #3\n\
	adds r1, #3\n\
	movs r0, #0xff\n\
	ands r1, r0\n\
	lsls r0, r5, #0xb\n\
	ldr r3, _080EABCC @ =0xFFFFFD00\n\
	adds r0, r0, r3\n\
	orrs r1, r0\n\
	strh r1, [r2, #4]\n\
	ldr r0, _080EABD0 @ =0x000002C5\n\
	ldr r6, [sp, #8]\n\
	subs r4, r6, #1\n\
	lsls r4, r4, #5\n\
	adds r4, r5, r4\n\
	lsls r4, r4, #1\n\
	subs r4, #2\n\
	adds r4, r7, r4\n\
	mov r3, r8\n\
	adds r3, #2\n\
	lsls r3, r3, #1\n\
	adds r1, r4, #0\n\
	adds r2, r3, #0\n\
	str r3, [sp, #0xc]\n\
	bl FillMemory\n\
	ldr r0, _080EABD4 @ =0x000002C6\n\
	adds r6, #6\n\
	lsls r6, r6, #5\n\
	adds r5, r5, r6\n\
	lsls r5, r5, #1\n\
	subs r5, #2\n\
	adds r5, r7, r5\n\
	adds r1, r5, #0\n\
	ldr r3, [sp, #0xc]\n\
	adds r2, r3, #0\n\
	bl FillMemory\n\
	adds r7, r4, #0\n\
	ldr r6, _080EABD8 @ =0x000002C1\n\
	adds r0, r6, #0\n\
	strh r0, [r7]\n\
	adds r1, r7, #0\n\
	adds r1, #0x40\n\
	ldr r2, _080EABDC @ =0x000002C2\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0x80\n\
	ldr r3, _080EABE0 @ =0x000002C7\n\
	adds r1, r3, #0\n\
	strh r1, [r0]\n\
	adds r0, #0x40\n\
	strh r1, [r0]\n\
	movs r5, #0x80\n\
	lsls r5, r5, #1\n\
	adds r0, r7, r5\n\
	strh r1, [r0]\n\
	movs r3, #0xa0\n\
	lsls r3, r3, #1\n\
	adds r0, r7, r3\n\
	strh r1, [r0]\n\
	movs r4, #0xc0\n\
	lsls r4, r4, #1\n\
	adds r1, r7, r4\n\
	adds r6, #2\n\
	adds r0, r6, #0\n\
	strh r0, [r1]\n\
	movs r2, #0xe0\n\
	lsls r2, r2, #1\n\
	adds r1, r7, r2\n\
	adds r6, #1\n\
	adds r0, r6, #0\n\
	strh r0, [r1]\n\
	mov r0, r8\n\
	lsls r0, r0, #1\n\
	mov r8, r0\n\
	movs r1, #2\n\
	add r8, r1\n\
	add r7, r8\n\
	ldr r6, _080EABE4 @ =0x000006C1\n\
	adds r0, r6, #0\n\
	strh r0, [r7]\n\
	adds r1, r7, #0\n\
	adds r1, #0x40\n\
	adds r6, #1\n\
	adds r0, r6, #0\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0x80\n\
	adds r6, #5\n\
	adds r1, r6, #0\n\
	strh r1, [r0]\n\
	adds r0, #0x40\n\
	strh r1, [r0]\n\
	adds r5, r7, r5\n\
	strh r1, [r5]\n\
	adds r3, r7, r3\n\
	strh r1, [r3]\n\
	adds r4, r7, r4\n\
	ldr r1, _080EABE8 @ =0x000006C3\n\
	adds r0, r1, #0\n\
	strh r0, [r4]\n\
	adds r2, r7, r2\n\
	ldr r3, _080EABEC @ =0x000006C4\n\
	adds r0, r3, #0\n\
	strh r0, [r2]\n\
	b _080EAE8E\n\
	.align 2, 0\n\
_080EABC8: .4byte gWindowRegBuffer\n\
_080EABCC: .4byte 0xFFFFFD00\n\
_080EABD0: .4byte 0x000002C5\n\
_080EABD4: .4byte 0x000002C6\n\
_080EABD8: .4byte 0x000002C1\n\
_080EABDC: .4byte 0x000002C2\n\
_080EABE0: .4byte 0x000002C7\n\
_080EABE4: .4byte 0x000006C1\n\
_080EABE8: .4byte 0x000006C3\n\
_080EABEC: .4byte 0x000006C4\n\
_080EABF0:\n\
	ldr r1, _080EAC1C @ =gSineTable\n\
	lsls r0, r2, #0x18\n\
	lsrs r0, r0, #0x17\n\
	adds r0, r0, r1\n\
	movs r6, #0\n\
	ldrsh r1, [r0, r6]\n\
	movs r0, #0xb0\n\
	muls r0, r1, r0\n\
	asrs r0, r0, #8\n\
	adds r0, #0x37\n\
	lsls r0, r0, #0xd\n\
	lsrs r0, r0, #0x10\n\
	str r0, [sp]\n\
	mov r1, sl\n\
	ldrb r0, [r1, #6]\n\
	cmp r0, #0\n\
	bne _080EAC20\n\
	movs r2, #1\n\
	str r2, [sp, #4]\n\
	ldr r3, [sp]\n\
	lsls r0, r3, #0x10\n\
	b _080EAC32\n\
	.align 2, 0\n\
_080EAC1C: .4byte gSineTable\n\
_080EAC20:\n\
	movs r0, #0x1d\n\
	ldr r6, [sp]\n\
	lsls r2, r6, #0x10\n\
	asrs r1, r2, #0x10\n\
	subs r0, r0, r1\n\
	lsls r0, r0, #0x10\n\
	lsrs r0, r0, #0x10\n\
	str r0, [sp, #4]\n\
	adds r0, r2, #0\n\
_080EAC32:\n\
	ldr r2, _080EAD70 @ =gWindowRegBuffer\n\
	ldr r1, [sp, #4]\n\
	lsls r5, r1, #0x10\n\
	asrs r5, r5, #0x10\n\
	asrs r0, r0, #0x10\n\
	mov sb, r0\n\
	adds r1, r5, r0\n\
	lsls r1, r1, #3\n\
	adds r1, #3\n\
	movs r0, #0xff\n\
	ands r1, r0\n\
	lsls r0, r5, #0xb\n\
	ldr r3, _080EAD74 @ =0xFFFFFD00\n\
	adds r0, r0, r3\n\
	orrs r1, r0\n\
	strh r1, [r2, #4]\n\
	ldr r0, _080EAD78 @ =0x000002C5\n\
	ldr r6, [sp, #8]\n\
	subs r4, r6, #1\n\
	lsls r4, r4, #5\n\
	adds r4, r5, r4\n\
	lsls r4, r4, #1\n\
	subs r4, #2\n\
	adds r4, r7, r4\n\
	mov r3, sb\n\
	adds r3, #2\n\
	lsls r3, r3, #1\n\
	adds r1, r4, #0\n\
	adds r2, r3, #0\n\
	str r3, [sp, #0xc]\n\
	bl FillMemory\n\
	ldr r0, _080EAD7C @ =0x000002C6\n\
	adds r6, #6\n\
	lsls r6, r6, #5\n\
	adds r5, r5, r6\n\
	lsls r5, r5, #1\n\
	subs r5, #2\n\
	adds r5, r7, r5\n\
	adds r1, r5, #0\n\
	ldr r3, [sp, #0xc]\n\
	adds r2, r3, #0\n\
	bl FillMemory\n\
	adds r7, r4, #0\n\
	mov r6, sl\n\
	ldrb r0, [r6, #6]\n\
	cmp r0, #0\n\
	beq _080EAC96\n\
	b _080EADA8\n\
_080EAC96:\n\
	movs r1, #0xb2\n\
	lsls r1, r1, #2\n\
	adds r0, r1, #0\n\
	strh r0, [r7]\n\
	adds r1, r7, #0\n\
	adds r1, #0x40\n\
	ldr r2, _080EAD80 @ =0x000002C9\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0x80\n\
	movs r3, #0xb3\n\
	lsls r3, r3, #2\n\
	adds r1, r3, #0\n\
	strh r1, [r0]\n\
	adds r0, #0x40\n\
	strh r1, [r0]\n\
	movs r6, #0x80\n\
	lsls r6, r6, #1\n\
	mov r8, r6\n\
	adds r0, r7, r6\n\
	strh r1, [r0]\n\
	movs r5, #0xa0\n\
	lsls r5, r5, #1\n\
	adds r0, r7, r5\n\
	strh r1, [r0]\n\
	adds r6, #0x80\n\
	adds r1, r7, r6\n\
	adds r2, #1\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	movs r4, #0xe0\n\
	lsls r4, r4, #1\n\
	adds r1, r7, r4\n\
	subs r3, #1\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	ldr r0, _080EAD84 @ =0x000002D2\n\
	adds r1, r7, #2\n\
	movs r2, #0xc\n\
	bl FillMemory\n\
	ldr r0, _080EAD88 @ =0x000002D3\n\
	movs r2, #0xe1\n\
	lsls r2, r2, #1\n\
	adds r1, r7, r2\n\
	movs r2, #0xc\n\
	bl FillMemory\n\
	ldr r3, _080EAD8C @ =0x000002CD\n\
	adds r0, r3, #0\n\
	strh r0, [r7, #0xe]\n\
	adds r1, r7, #0\n\
	adds r1, #0x4e\n\
	ldr r2, _080EAD90 @ =0x000002CE\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	adds r1, #0x40\n\
	adds r3, #4\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	adds r1, #0x40\n\
	strh r0, [r1]\n\
	movs r2, #0x87\n\
	lsls r2, r2, #1\n\
	adds r1, r7, r2\n\
	strh r0, [r1]\n\
	movs r3, #0xa7\n\
	lsls r3, r3, #1\n\
	adds r1, r7, r3\n\
	strh r0, [r1]\n\
	movs r0, #0xc7\n\
	lsls r0, r0, #1\n\
	adds r1, r7, r0\n\
	ldr r2, _080EAD94 @ =0x000002CF\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	adds r3, #0x80\n\
	adds r1, r7, r3\n\
	adds r2, #1\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	mov r3, sb\n\
	lsls r0, r3, #1\n\
	adds r0, #2\n\
	adds r7, r7, r0\n\
	ldr r1, _080EAD98 @ =0x000006C1\n\
	adds r0, r1, #0\n\
	strh r0, [r7]\n\
	adds r1, r7, #0\n\
	adds r1, #0x40\n\
	ldr r2, _080EAD9C @ =0x000006C2\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0x80\n\
	ldr r3, _080EADA0 @ =0x000006C7\n\
	adds r1, r3, #0\n\
	strh r1, [r0]\n\
	adds r0, #0x40\n\
	strh r1, [r0]\n\
	add r8, r7\n\
	mov r0, r8\n\
	strh r1, [r0]\n\
	adds r5, r7, r5\n\
	strh r1, [r5]\n\
	adds r6, r7, r6\n\
	ldr r1, _080EADA4 @ =0x000006C3\n\
	b _080EAE7C\n\
	.align 2, 0\n\
_080EAD70: .4byte gWindowRegBuffer\n\
_080EAD74: .4byte 0xFFFFFD00\n\
_080EAD78: .4byte 0x000002C5\n\
_080EAD7C: .4byte 0x000002C6\n\
_080EAD80: .4byte 0x000002C9\n\
_080EAD84: .4byte 0x000002D2\n\
_080EAD88: .4byte 0x000002D3\n\
_080EAD8C: .4byte 0x000002CD\n\
_080EAD90: .4byte 0x000002CE\n\
_080EAD94: .4byte 0x000002CF\n\
_080EAD98: .4byte 0x000006C1\n\
_080EAD9C: .4byte 0x000006C2\n\
_080EADA0: .4byte 0x000006C7\n\
_080EADA4: .4byte 0x000006C3\n\
_080EADA8:\n\
	mov r3, sb\n\
	lsls r2, r3, #1\n\
	subs r2, #0xc\n\
	adds r7, r7, r2\n\
	ldr r6, _080EAEC8 @ =0x000006CD\n\
	adds r0, r6, #0\n\
	strh r0, [r7]\n\
	adds r1, r7, #0\n\
	adds r1, #0x40\n\
	ldr r3, _080EAECC @ =0x000006CE\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0x80\n\
	adds r6, #4\n\
	adds r1, r6, #0\n\
	strh r1, [r0]\n\
	adds r0, #0x40\n\
	strh r1, [r0]\n\
	movs r0, #0x80\n\
	lsls r0, r0, #1\n\
	mov r8, r0\n\
	adds r0, r7, r0\n\
	strh r1, [r0]\n\
	movs r5, #0xa0\n\
	lsls r5, r5, #1\n\
	adds r0, r7, r5\n\
	strh r1, [r0]\n\
	movs r6, #0xc0\n\
	lsls r6, r6, #1\n\
	adds r1, r7, r6\n\
	adds r3, #1\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	movs r4, #0xe0\n\
	lsls r4, r4, #1\n\
	adds r1, r7, r4\n\
	adds r3, #1\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	subs r7, r7, r2\n\
	ldr r1, _080EAED0 @ =0x000002C1\n\
	adds r0, r1, #0\n\
	strh r0, [r7]\n\
	adds r1, r7, #0\n\
	adds r1, #0x40\n\
	ldr r3, _080EAED4 @ =0x000002C2\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0x80\n\
	adds r3, #5\n\
	adds r1, r3, #0\n\
	strh r1, [r0]\n\
	adds r0, #0x40\n\
	strh r1, [r0]\n\
	mov r3, r8\n\
	adds r0, r7, r3\n\
	strh r1, [r0]\n\
	adds r0, r7, r5\n\
	strh r1, [r0]\n\
	adds r1, r7, r6\n\
	ldr r3, _080EAED8 @ =0x000002C3\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	adds r1, r7, r4\n\
	adds r3, #1\n\
	adds r0, r3, #0\n\
	strh r0, [r1]\n\
	adds r7, r7, r2\n\
	ldr r0, _080EAEDC @ =0x000006D2\n\
	adds r1, r7, #2\n\
	movs r2, #0xc\n\
	bl FillMemory\n\
	ldr r0, _080EAEE0 @ =0x000006D3\n\
	movs r2, #0xe1\n\
	lsls r2, r2, #1\n\
	adds r1, r7, r2\n\
	movs r2, #0xc\n\
	bl FillMemory\n\
	adds r7, #0xe\n\
	movs r3, #0xd9\n\
	lsls r3, r3, #3\n\
	adds r0, r3, #0\n\
	strh r0, [r7]\n\
	adds r1, r7, #0\n\
	adds r1, #0x40\n\
	ldr r2, _080EAEE4 @ =0x000006C9\n\
	adds r0, r2, #0\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0x80\n\
	adds r3, #4\n\
	adds r1, r3, #0\n\
	strh r1, [r0]\n\
	adds r0, #0x40\n\
	strh r1, [r0]\n\
	add r8, r7\n\
	mov r0, r8\n\
	strh r1, [r0]\n\
	adds r5, r7, r5\n\
	strh r1, [r5]\n\
	adds r6, r7, r6\n\
	ldr r1, _080EAEE8 @ =0x000006CA\n\
_080EAE7C:\n\
	adds r0, r1, #0\n\
	strh r0, [r6]\n\
	adds r4, r7, r4\n\
	adds r2, #2\n\
	adds r0, r2, #0\n\
	strh r0, [r4]\n\
	mov r0, sl\n\
	bl transferMugshotTileMap\n\
_080EAE8E:\n\
	ldr r1, _080EAEEC @ =gTextPrinter\n\
	movs r3, #0xb3\n\
	lsls r3, r3, #3\n\
	adds r0, r1, r3\n\
	mov r6, sp\n\
	ldrb r6, [r6, #4]\n\
	strb r6, [r0]\n\
	ldr r2, _080EAEF0 @ =0x0000059A\n\
	adds r0, r1, r2\n\
	mov r3, sp\n\
	ldrb r3, [r3]\n\
	strb r3, [r0]\n\
	ldr r6, _080EAEF4 @ =0x00000599\n\
	adds r0, r1, r6\n\
	mov r2, sp\n\
	ldrb r2, [r2, #8]\n\
	strb r2, [r0]\n\
	ldr r3, _080EAEF8 @ =0x0000059B\n\
	adds r1, r1, r3\n\
	movs r0, #6\n\
	strb r0, [r1]\n\
	add sp, #0x10\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080EAEC8: .4byte 0x000006CD\n\
_080EAECC: .4byte 0x000006CE\n\
_080EAED0: .4byte 0x000002C1\n\
_080EAED4: .4byte 0x000002C2\n\
_080EAED8: .4byte 0x000002C3\n\
_080EAEDC: .4byte 0x000006D2\n\
_080EAEE0: .4byte 0x000006D3\n\
_080EAEE4: .4byte 0x000006C9\n\
_080EAEE8: .4byte 0x000006CA\n\
_080EAEEC: .4byte gTextPrinter\n\
_080EAEF0: .4byte 0x0000059A\n\
_080EAEF4: .4byte 0x00000599\n\
_080EAEF8: .4byte 0x0000059B\n\
 .syntax divided\n");
}

void text_080eaefc(struct TextWindowText* t, u32 len) {
  tile_id_t* bgmap;
  s32 size;
  struct WramWindowRegister* win;
  s32 sin = ((gSineTable[(u8)len] * 7) >> 3) + 7;
  bgmap = gTextWindow.bg0Mask;

  win = &gWindowRegBuffer;
  size = sin >> 3;
  *(u16*)&win->winH.word = 0x400 | (((size << 3) + 12) & 0xFF);
  if (size != 0) {
    FillMemory(709, &bgmap[513], size << 1);
    FillMemory(710, &bgmap[609], size << 1);
  }
  bgmap[512] = 0x2c1;
  bgmap[544] = 0x2c2;
  bgmap[576] = 0x2c3;
  bgmap[608] = 0x2c4;
  bgmap[513 + size] = 0x6c1;
  bgmap[545 + size] = 0x6c2;
  bgmap[577 + size] = 0x6c3;
  bgmap[609 + size] = 0x6c4;
}

static void doNoTextWindow(struct TextWindowText* t) {
  t->mode = 0;
  return;
}

NAKED static void mugshotMessage(struct TextWindowText* t) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r5, r0, #0\n\
	ldrb r0, [r5, #0xd]\n\
	cmp r0, #8\n\
	bls _080EAFEC\n\
	b _080EB45A\n\
_080EAFEC:\n\
	lsls r0, r0, #2\n\
	ldr r1, _080EAFF8 @ =_080EAFFC\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	mov pc, r0\n\
	.align 2, 0\n\
_080EAFF8: .4byte _080EAFFC\n\
_080EAFFC: @ jump table\n\
	.4byte _080EB020 @ case 0\n\
	.4byte _080EB066 @ case 1\n\
	.4byte _080EB0C6 @ case 2\n\
	.4byte _080EB0E0 @ case 3\n\
	.4byte _080EB19A @ case 4\n\
	.4byte _080EB2E8 @ case 5\n\
	.4byte _080EB3A4 @ case 6\n\
	.4byte _080EB3EE @ case 7\n\
	.4byte _080EB41C @ case 8\n\
_080EB020:\n\
	ldrb r1, [r5, #4]\n\
	adds r0, r5, #0\n\
	bl loadMugshot\n\
	ldr r1, _080EB0A8 @ =gVideoRegBuffer\n\
	ldrh r2, [r1]\n\
	movs r3, #0x80\n\
	lsls r3, r3, #1\n\
	adds r0, r3, #0\n\
	movs r3, #0\n\
	orrs r0, r2\n\
	strh r0, [r1]\n\
	str r3, [r1, #0xc]\n\
	ldr r0, _080EB0AC @ =gPaletteManager\n\
	strh r3, [r0]\n\
	ldr r1, _080EB0B0 @ =gWindowRegBuffer\n\
	ldrh r2, [r1]\n\
	movs r4, #0x80\n\
	lsls r4, r4, #6\n\
	adds r0, r4, #0\n\
	orrs r0, r2\n\
	strh r0, [r1]\n\
	movs r2, #1\n\
	movs r0, #1\n\
	strb r0, [r1, #0xc]\n\
	ldrb r0, [r1, #0xe]\n\
	orrs r0, r2\n\
	strb r0, [r1, #0xe]\n\
	ldrb r0, [r1, #0xd]\n\
	orrs r2, r0\n\
	strb r2, [r1, #0xd]\n\
	strh r3, [r5, #0x10]\n\
	ldrb r0, [r5, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r5, #0xd]\n\
_080EB066:\n\
	movs r6, #0\n\
	movs r0, #1\n\
	strh r0, [r5, #2]\n\
	ldr r4, _080EB0B0 @ =gWindowRegBuffer\n\
	ldrb r2, [r5, #5]\n\
	adds r0, r2, #6\n\
	lsls r0, r0, #3\n\
	adds r0, #2\n\
	movs r1, #0xff\n\
	ands r0, r1\n\
	lsls r2, r2, #0xb\n\
	ldr r1, _080EB0B4 @ =0xFFFFFE00\n\
	adds r2, r2, r1\n\
	orrs r0, r2\n\
	strh r0, [r4, #8]\n\
	ldrh r1, [r5, #0x10]\n\
	adds r0, r5, #0\n\
	bl text_080eaa7c\n\
	ldrh r0, [r5, #0x10]\n\
	adds r0, #4\n\
	strh r0, [r5, #0x10]\n\
	lsls r0, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #0x3f\n\
	bgt _080EB09C\n\
	b _080EB45A\n\
_080EB09C:\n\
	ldrb r0, [r5, #6]\n\
	cmp r0, #0\n\
	bne _080EB0BC\n\
	ldr r0, _080EB0B8 @ =0x000009E8\n\
	b _080EB0BE\n\
	.align 2, 0\n\
_080EB0A8: .4byte gVideoRegBuffer\n\
_080EB0AC: .4byte gPaletteManager\n\
_080EB0B0: .4byte gWindowRegBuffer\n\
_080EB0B4: .4byte 0xFFFFFE00\n\
_080EB0B8: .4byte 0x000009E8\n\
_080EB0BC:\n\
	ldr r0, _080EB184 @ =0x000007E7\n\
_080EB0BE:\n\
	strh r0, [r4, #4]\n\
	ldrb r0, [r5, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r5, #0xd]\n\
_080EB0C6:\n\
	ldr r0, [r5, #0x1c]\n\
	bl getStringLength\n\
	movs r1, #0\n\
	strh r0, [r5, #0x10]\n\
	movs r0, #1\n\
	strh r0, [r5, #0x12]\n\
	movs r0, #4\n\
	strh r0, [r5, #0x14]\n\
	strb r1, [r5, #0xe]\n\
	ldrb r0, [r5, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r5, #0xd]\n\
_080EB0E0:\n\
	adds r0, r5, #0\n\
	movs r1, #0x40\n\
	bl text_080eaa7c\n\
	ldr r0, [r5, #8]\n\
	cmp r0, #0\n\
	beq _080EB0F8\n\
	ldrh r1, [r5]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB108\n\
_080EB0F8:\n\
	ldr r0, _080EB188 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB108\n\
	movs r0, #1\n\
	strb r0, [r5, #0xe]\n\
_080EB108:\n\
	ldrb r0, [r5, #0xe]\n\
	cmp r0, #0\n\
	bne _080EB11A\n\
	ldr r0, _080EB18C @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB11E\n\
_080EB11A:\n\
	movs r0, #0\n\
	strh r0, [r5, #0x14]\n\
_080EB11E:\n\
	ldr r4, [r5, #0x1c]\n\
	movs r1, #0\n\
	ldrb r0, [r5, #6]\n\
	cmp r0, #0\n\
	bne _080EB12E\n\
	ldrb r0, [r5, #4]\n\
	cmp r0, #1\n\
	bne _080EB130\n\
_080EB12E:\n\
	movs r1, #1\n\
_080EB130:\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r5, #5]\n\
	ldrh r3, [r5, #0x12]\n\
	adds r0, r4, #0\n\
	bl text_080e9b40\n\
	ldr r0, [r5, #0x1c]\n\
	movs r2, #0x12\n\
	ldrsh r1, [r5, r2]\n\
	subs r1, #1\n\
	bl SkipString\n\
	ldrh r0, [r5, #0x14]\n\
	subs r0, #1\n\
	strh r0, [r5, #0x14]\n\
	lsls r0, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	movs r1, #1\n\
	rsbs r1, r1, #0\n\
	cmp r0, r1\n\
	beq _080EB162\n\
	b _080EB45A\n\
_080EB162:\n\
	ldrh r1, [r5, #0x12]\n\
	adds r0, r1, #1\n\
	strh r0, [r5, #0x12]\n\
	ldrb r0, [r5, #0xe]\n\
	cmp r0, #0\n\
	beq _080EB172\n\
	adds r0, r1, #4\n\
	strh r0, [r5, #0x12]\n\
_080EB172:\n\
	movs r3, #0x12\n\
	ldrsh r1, [r5, r3]\n\
	movs r4, #0x10\n\
	ldrsh r0, [r5, r4]\n\
	cmp r1, r0\n\
	bge _080EB190\n\
	movs r0, #3\n\
	strh r0, [r5, #0x14]\n\
	b _080EB45A\n\
	.align 2, 0\n\
_080EB184: .4byte 0x000007E7\n\
_080EB188: .4byte gJoypad\n\
_080EB18C: .4byte gTextWindow+8\n\
_080EB190:\n\
	movs r0, #0\n\
	strh r0, [r5, #0x14]\n\
	movs r0, #2\n\
	strh r0, [r5, #2]\n\
	b _080EB414\n\
_080EB19A:\n\
	adds r0, r5, #0\n\
	movs r1, #0x40\n\
	bl text_080eaa7c\n\
	ldr r0, _080EB1EC @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
	movs r0, #8\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB1D0\n\
	ldr r3, [r5, #0x1c]\n\
	movs r1, #0\n\
	ldrb r0, [r5, #6]\n\
	cmp r0, #0\n\
	bne _080EB1BE\n\
	ldrb r0, [r5, #4]\n\
	cmp r0, #1\n\
	bne _080EB1C0\n\
_080EB1BE:\n\
	movs r1, #1\n\
_080EB1C0:\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r5, #5]\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
_080EB1D0:\n\
	ldrh r0, [r5, #0x14]\n\
	adds r1, r0, #1\n\
	strh r1, [r5, #0x14]\n\
	ldr r2, [r5, #8]\n\
	cmp r2, #0\n\
	beq _080EB1F0\n\
	movs r1, #0x14\n\
	ldrsh r0, [r5, r1]\n\
	cmp r0, r2\n\
	ble _080EB1E6\n\
	b _080EB414\n\
_080EB1E6:\n\
	ldrh r1, [r5]\n\
	b _080EB2CE\n\
	.align 2, 0\n\
_080EB1EC: .4byte gTextWindow+8\n\
_080EB1F0:\n\
	ldr r0, [r5, #0x24]\n\
	cmp r0, #0\n\
	beq _080EB2A0\n\
	movs r0, #3\n\
	strh r0, [r5, #2]\n\
	ldr r0, _080EB220 @ =gJoypad\n\
	ldrh r1, [r0, #6]\n\
	movs r0, #0xc0\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB22E\n\
	movs r0, #1\n\
	bl PlaySound\n\
	ldrb r1, [r5, #7]\n\
	movs r0, #0xf0\n\
	ands r0, r1\n\
	cmp r0, #0x20\n\
	bne _080EB224\n\
	movs r0, #0xf\n\
	ands r0, r1\n\
	movs r1, #0x10\n\
	b _080EB22A\n\
	.align 2, 0\n\
_080EB220: .4byte gJoypad\n\
_080EB224:\n\
	movs r0, #0xf\n\
	ands r0, r1\n\
	movs r1, #0x20\n\
_080EB22A:\n\
	orrs r0, r1\n\
	strb r0, [r5, #7]\n\
_080EB22E:\n\
	ldr r0, _080EB278 @ =StringOfsTable\n\
	ldrh r1, [r0]\n\
	ldr r0, _080EB27C @ =gStringData\n\
	adds r4, r1, r0\n\
	movs r1, #0\n\
	ldrb r0, [r5, #6]\n\
	cmp r0, #0\n\
	bne _080EB244\n\
	ldrb r0, [r5, #4]\n\
	cmp r0, #1\n\
	bne _080EB246\n\
_080EB244:\n\
	movs r1, #1\n\
_080EB246:\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	movs r1, #8\n\
	subs r3, r1, r0\n\
	ldrb r0, [r5, #5]\n\
	adds r2, r0, #2\n\
	ldrb r1, [r5, #7]\n\
	movs r0, #0xf0\n\
	ands r0, r1\n\
	cmp r0, #0x20\n\
	bne _080EB25E\n\
	adds r2, #2\n\
_080EB25E:\n\
	adds r0, r4, #0\n\
	adds r1, r3, #0\n\
	bl PrintString\n\
	ldrh r1, [r5]\n\
	movs r0, #4\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB280\n\
	movs r0, #3\n\
	bl PlaySound\n\
	b _080EB414\n\
	.align 2, 0\n\
_080EB278: .4byte StringOfsTable\n\
_080EB27C: .4byte gStringData\n\
_080EB280:\n\
	ldr r0, _080EB29C @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB28E\n\
	b _080EB45A\n\
_080EB28E:\n\
	ldrb r0, [r5, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r5, #0xd]\n\
	movs r0, #2\n\
	bl PlaySound\n\
	b _080EB45A\n\
	.align 2, 0\n\
_080EB29C: .4byte gJoypad\n\
_080EB2A0:\n\
	movs r0, #0x10\n\
	ands r1, r0\n\
	cmp r1, #0\n\
	bne _080EB2BC\n\
	ldr r0, _080EB2DC @ =Unicode_Prompt\n\
	ldrb r1, [r5, #6]\n\
	lsls r2, r1, #3\n\
	subs r2, r2, r1\n\
	movs r1, #0x1c\n\
	subs r1, r1, r2\n\
	ldrb r2, [r5, #5]\n\
	adds r2, #5\n\
	bl PrintUnicodeString\n\
_080EB2BC:\n\
	ldr r0, _080EB2E0 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB2CA\n\
	b _080EB414\n\
_080EB2CA:\n\
	ldr r0, _080EB2E4 @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
_080EB2CE:\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB2D8\n\
	b _080EB45A\n\
_080EB2D8:\n\
	b _080EB414\n\
	.align 2, 0\n\
_080EB2DC: .4byte Unicode_Prompt\n\
_080EB2E0: .4byte gJoypad\n\
_080EB2E4: .4byte gTextWindow+8\n\
_080EB2E8:\n\
	ldrh r1, [r5]\n\
	movs r0, #2\n\
	ands r0, r1\n\
	lsls r0, r0, #0x10\n\
	lsrs r2, r0, #0x10\n\
	cmp r2, #0\n\
	bne _080EB396\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB358\n\
	ldr r0, [r5, #0x24]\n\
	cmp r0, #0\n\
	beq _080EB310\n\
	movs r0, #4\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB310\n\
	str r2, [r5, #0x20]\n\
	str r2, [r5, #0x24]\n\
_080EB310:\n\
	ldr r0, [r5, #0x20]\n\
	cmp r0, #0\n\
	bne _080EB358\n\
	adds r0, r5, #0\n\
	movs r1, #0x40\n\
	bl text_080eaa7c\n\
	ldr r0, _080EB354 @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
	movs r0, #8\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB34C\n\
	ldr r3, [r5, #0x1c]\n\
	movs r1, #0\n\
	ldrb r0, [r5, #6]\n\
	cmp r0, #0\n\
	bne _080EB33A\n\
	ldrb r0, [r5, #4]\n\
	cmp r0, #1\n\
	bne _080EB33C\n\
_080EB33A:\n\
	movs r1, #1\n\
_080EB33C:\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r5, #5]\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
_080EB34C:\n\
	movs r0, #4\n\
	strh r0, [r5, #2]\n\
	b _080EB45A\n\
	.align 2, 0\n\
_080EB354: .4byte gTextWindow+8\n\
_080EB358:\n\
	ldr r2, [r5, #0x24]\n\
	cmp r2, #0\n\
	beq _080EB36A\n\
	ldrb r1, [r5, #7]\n\
	movs r0, #0xf0\n\
	ands r0, r1\n\
	cmp r0, #0x20\n\
	bne _080EB36A\n\
	str r2, [r5, #0x20]\n\
_080EB36A:\n\
	ldr r0, [r5, #0x20]\n\
	cmp r0, #0\n\
	beq _080EB396\n\
	adds r0, r5, #0\n\
	bl isMugshotChanged\n\
	cmp r0, #0\n\
	bne _080EB396\n\
	adds r0, r5, #0\n\
	movs r1, #0x40\n\
	bl text_080eaa7c\n\
	ldr r0, [r5, #0x20]\n\
	str r0, [r5, #0x1c]\n\
	adds r0, r5, #0\n\
	bl setupTextWindow\n\
	movs r0, #1\n\
	strh r0, [r5, #2]\n\
	movs r0, #2\n\
	strb r0, [r5, #0xd]\n\
	b _080EB45A\n\
_080EB396:\n\
	movs r0, #5\n\
	strh r0, [r5, #2]\n\
	movs r0, #0x40\n\
	strh r0, [r5, #0x10]\n\
	ldrb r0, [r5, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r5, #0xd]\n\
_080EB3A4:\n\
	ldrh r0, [r5, #0x10]\n\
	subs r0, #4\n\
	strh r0, [r5, #0x10]\n\
	ldr r0, _080EB410 @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
	movs r0, #8\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB3D8\n\
	ldr r3, [r5, #0x1c]\n\
	movs r1, #0\n\
	ldrb r0, [r5, #6]\n\
	cmp r0, #0\n\
	bne _080EB3C6\n\
	ldrb r0, [r5, #4]\n\
	cmp r0, #1\n\
	bne _080EB3C8\n\
_080EB3C6:\n\
	movs r1, #1\n\
_080EB3C8:\n\
	lsls r0, r1, #3\n\
	subs r0, r0, r1\n\
	movs r1, #8\n\
	subs r1, r1, r0\n\
	ldrb r2, [r5, #5]\n\
	adds r0, r3, #0\n\
	bl PrintString\n\
_080EB3D8:\n\
	ldrh r1, [r5, #0x10]\n\
	adds r0, r5, #0\n\
	bl text_080eaa7c\n\
	movs r2, #0x10\n\
	ldrsh r0, [r5, r2]\n\
	cmp r0, #0\n\
	bne _080EB45A\n\
	ldrb r0, [r5, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r5, #0xd]\n\
_080EB3EE:\n\
	ldr r2, [r5, #0x20]\n\
	cmp r2, #0\n\
	beq _080EB414\n\
	ldrh r1, [r5]\n\
	movs r0, #2\n\
	ands r0, r1\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	cmp r4, #0\n\
	bne _080EB414\n\
	str r2, [r5, #0x1c]\n\
	adds r0, r5, #0\n\
	bl setupTextWindow\n\
	strb r4, [r5, #0xd]\n\
	b _080EB45A\n\
	.align 2, 0\n\
_080EB410: .4byte gTextWindow+8\n\
_080EB414:\n\
	ldrb r0, [r5, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r5, #0xd]\n\
	b _080EB45A\n\
_080EB41C:\n\
	ldr r2, _080EB460 @ =gWindowRegBuffer\n\
	ldrh r1, [r2]\n\
	ldr r0, _080EB464 @ =0x0000DFFF\n\
	ands r0, r1\n\
	movs r4, #0\n\
	movs r3, #0\n\
	strh r0, [r2]\n\
	ldrb r1, [r2, #0xe]\n\
	movs r0, #1\n\
	orrs r1, r0\n\
	strb r1, [r2, #0xe]\n\
	ldrb r1, [r2, #0xd]\n\
	orrs r0, r1\n\
	strb r0, [r2, #0xd]\n\
	str r3, [r5, #0xc]\n\
	ldr r1, _080EB468 @ =gTextPrinter\n\
	movs r3, #0xb3\n\
	lsls r3, r3, #3\n\
	adds r0, r1, r3\n\
	strb r4, [r0]\n\
	ldr r0, _080EB46C @ =0x0000059A\n\
	adds r2, r1, r0\n\
	movs r0, #0x1e\n\
	strb r0, [r2]\n\
	ldr r2, _080EB470 @ =0x00000599\n\
	adds r0, r1, r2\n\
	strb r4, [r0]\n\
	adds r3, #3\n\
	adds r1, r1, r3\n\
	movs r0, #0x16\n\
	strb r0, [r1]\n\
_080EB45A:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080EB460: .4byte gWindowRegBuffer\n\
_080EB464: .4byte 0x0000DFFF\n\
_080EB468: .4byte gTextPrinter\n\
_080EB46C: .4byte 0x0000059A\n\
_080EB470: .4byte 0x00000599\n\
 .syntax divided\n");
}

NAKED static void inlineMessage(struct TextWindowText* t) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	ldrb r0, [r6, #0xd]\n\
	cmp r0, #6\n\
	bls _080EB480\n\
	b _080EB6E0\n\
_080EB480:\n\
	lsls r0, r0, #2\n\
	ldr r1, _080EB48C @ =_080EB490\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	mov pc, r0\n\
	.align 2, 0\n\
_080EB48C: .4byte _080EB490\n\
_080EB490: @ jump table\n\
	.4byte _080EB4AC @ case 0\n\
	.4byte _080EB4F6 @ case 1\n\
	.4byte _080EB51C @ case 2\n\
	.4byte _080EB538 @ case 3\n\
	.4byte _080EB5E6 @ case 4\n\
	.4byte _080EB650 @ case 5\n\
	.4byte _080EB6A6 @ case 6\n\
_080EB4AC:\n\
	ldrb r1, [r6, #4]\n\
	adds r0, r6, #0\n\
	bl loadMugshot\n\
	ldr r1, _080EB5C4 @ =gVideoRegBuffer\n\
	ldrh r2, [r1]\n\
	movs r3, #0x80\n\
	lsls r3, r3, #1\n\
	adds r0, r3, #0\n\
	movs r3, #0\n\
	orrs r0, r2\n\
	strh r0, [r1]\n\
	str r3, [r1, #0xc]\n\
	ldr r0, _080EB5C8 @ =gPaletteManager\n\
	strh r3, [r0]\n\
	ldr r2, _080EB5CC @ =gWindowRegBuffer\n\
	ldrh r0, [r2]\n\
	movs r4, #0x80\n\
	lsls r4, r4, #6\n\
	adds r1, r4, #0\n\
	orrs r0, r1\n\
	strh r0, [r2]\n\
	movs r1, #1\n\
	movs r0, #1\n\
	strb r0, [r2, #0xc]\n\
	ldrb r0, [r2, #0xe]\n\
	orrs r0, r1\n\
	strb r0, [r2, #0xe]\n\
	ldrb r0, [r2, #0xd]\n\
	orrs r1, r0\n\
	strb r1, [r2, #0xd]\n\
	ldr r0, _080EB5D0 @ =0x0000869A\n\
	strh r0, [r2, #8]\n\
	strh r3, [r6, #0x10]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB4F6:\n\
	ldrh r1, [r6, #0x10]\n\
	adds r0, r6, #0\n\
	bl text_080eaefc\n\
	ldrh r0, [r6, #0x10]\n\
	adds r0, #4\n\
	strh r0, [r6, #0x10]\n\
	lsls r0, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #0x3f\n\
	bgt _080EB50E\n\
	b _080EB6E0\n\
_080EB50E:\n\
	ldr r1, _080EB5CC @ =gWindowRegBuffer\n\
	movs r0, #0x87\n\
	lsls r0, r0, #5\n\
	strh r0, [r1, #4]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB51C:\n\
	movs r5, #0\n\
	movs r4, #1\n\
	strh r4, [r6, #2]\n\
	ldr r0, [r6, #0x1c]\n\
	bl getStringLength\n\
	strh r0, [r6, #0x10]\n\
	strh r4, [r6, #0x12]\n\
	movs r0, #4\n\
	strh r0, [r6, #0x14]\n\
	strb r5, [r6, #0xe]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB538:\n\
	adds r0, r6, #0\n\
	movs r1, #0x40\n\
	bl text_080eaefc\n\
	ldr r0, [r6, #8]\n\
	cmp r0, #0\n\
	beq _080EB550\n\
	ldrh r1, [r6]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB560\n\
_080EB550:\n\
	ldr r0, _080EB5D4 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB560\n\
	movs r0, #1\n\
	strb r0, [r6, #0xe]\n\
_080EB560:\n\
	ldrb r0, [r6, #0xe]\n\
	cmp r0, #0\n\
	bne _080EB572\n\
	ldr r0, _080EB5D8 @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB576\n\
_080EB572:\n\
	movs r0, #0\n\
	strh r0, [r6, #0x14]\n\
_080EB576:\n\
	ldr r0, [r6, #0x1c]\n\
	ldrh r3, [r6, #0x12]\n\
	movs r1, #1\n\
	movs r2, #0x11\n\
	bl text_080e9b40\n\
	ldr r0, [r6, #0x1c]\n\
	movs r2, #0x12\n\
	ldrsh r1, [r6, r2]\n\
	subs r1, #1\n\
	bl SkipString\n\
	ldrh r0, [r6, #0x14]\n\
	subs r0, #1\n\
	strh r0, [r6, #0x14]\n\
	lsls r0, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	movs r1, #1\n\
	rsbs r1, r1, #0\n\
	cmp r0, r1\n\
	beq _080EB5A2\n\
	b _080EB6E0\n\
_080EB5A2:\n\
	ldrh r1, [r6, #0x12]\n\
	adds r0, r1, #1\n\
	strh r0, [r6, #0x12]\n\
	ldrb r0, [r6, #0xe]\n\
	cmp r0, #0\n\
	beq _080EB5B2\n\
	adds r0, r1, #4\n\
	strh r0, [r6, #0x12]\n\
_080EB5B2:\n\
	movs r3, #0x12\n\
	ldrsh r1, [r6, r3]\n\
	movs r4, #0x10\n\
	ldrsh r0, [r6, r4]\n\
	cmp r1, r0\n\
	bge _080EB5DC\n\
	movs r0, #3\n\
	strh r0, [r6, #0x14]\n\
	b _080EB6E0\n\
	.align 2, 0\n\
_080EB5C4: .4byte gVideoRegBuffer\n\
_080EB5C8: .4byte gPaletteManager\n\
_080EB5CC: .4byte gWindowRegBuffer\n\
_080EB5D0: .4byte 0x0000869A\n\
_080EB5D4: .4byte gJoypad\n\
_080EB5D8: .4byte gTextWindow+8\n\
_080EB5DC:\n\
	movs r0, #0\n\
	strh r0, [r6, #0x14]\n\
	movs r0, #2\n\
	strh r0, [r6, #2]\n\
	b _080EB63A\n\
_080EB5E6:\n\
	adds r0, r6, #0\n\
	movs r1, #0x40\n\
	bl text_080eaefc\n\
	ldr r0, [r6, #0x1c]\n\
	movs r1, #1\n\
	movs r2, #0x11\n\
	bl PrintString\n\
	ldrh r0, [r6, #0x14]\n\
	adds r1, r0, #1\n\
	strh r1, [r6, #0x14]\n\
	ldr r2, [r6, #8]\n\
	cmp r2, #0\n\
	beq _080EB610\n\
	movs r1, #0x14\n\
	ldrsh r0, [r6, r1]\n\
	cmp r0, r2\n\
	bgt _080EB63A\n\
	ldrh r1, [r6]\n\
	b _080EB632\n\
_080EB610:\n\
	movs r0, #0x10\n\
	ands r1, r0\n\
	cmp r1, #0\n\
	bne _080EB622\n\
	ldr r0, _080EB644 @ =Unicode_Prompt\n\
	movs r1, #0x1c\n\
	movs r2, #0x12\n\
	bl PrintUnicodeString\n\
_080EB622:\n\
	ldr r0, _080EB648 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB63A\n\
	ldr r0, _080EB64C @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
_080EB632:\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB6E0\n\
_080EB63A:\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
	b _080EB6E0\n\
	.align 2, 0\n\
_080EB644: .4byte Unicode_Prompt\n\
_080EB648: .4byte gJoypad\n\
_080EB64C: .4byte gTextWindow+8\n\
_080EB650:\n\
	adds r0, r6, #0\n\
	movs r1, #0x40\n\
	bl text_080eaefc\n\
	ldrh r1, [r6]\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB698\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB680\n\
	ldr r0, [r6, #0x20]\n\
	cmp r0, #0\n\
	bne _080EB686\n\
	ldr r0, [r6, #0x1c]\n\
	movs r1, #1\n\
	movs r2, #0x11\n\
	bl PrintString\n\
	movs r0, #4\n\
	strh r0, [r6, #2]\n\
	b _080EB6E0\n\
_080EB680:\n\
	ldr r0, [r6, #0x20]\n\
	cmp r0, #0\n\
	beq _080EB698\n\
_080EB686:\n\
	str r0, [r6, #0x1c]\n\
	adds r0, r6, #0\n\
	bl setupTextWindow\n\
	movs r0, #1\n\
	strh r0, [r6, #2]\n\
	movs r0, #2\n\
	strb r0, [r6, #0xd]\n\
	b _080EB6E0\n\
_080EB698:\n\
	movs r0, #5\n\
	strh r0, [r6, #2]\n\
	movs r0, #0x40\n\
	strh r0, [r6, #0x10]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB6A6:\n\
	ldrh r0, [r6, #0x10]\n\
	subs r0, #4\n\
	strh r0, [r6, #0x10]\n\
	lsls r0, r0, #0x10\n\
	asrs r3, r0, #0x10\n\
	cmp r3, #0\n\
	bne _080EB6D8\n\
	ldr r2, _080EB6D0 @ =gWindowRegBuffer\n\
	ldrh r1, [r2]\n\
	ldr r0, _080EB6D4 @ =0x0000DFFF\n\
	ands r0, r1\n\
	strh r0, [r2]\n\
	ldrb r1, [r2, #0xe]\n\
	movs r0, #1\n\
	orrs r1, r0\n\
	strb r1, [r2, #0xe]\n\
	ldrb r1, [r2, #0xd]\n\
	orrs r0, r1\n\
	strb r0, [r2, #0xd]\n\
	str r3, [r6, #0xc]\n\
	b _080EB6E0\n\
	.align 2, 0\n\
_080EB6D0: .4byte gWindowRegBuffer\n\
_080EB6D4: .4byte 0x0000DFFF\n\
_080EB6D8:\n\
	ldrh r1, [r6, #0x10]\n\
	adds r0, r6, #0\n\
	bl text_080eaefc\n\
_080EB6E0:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
 .syntax divided\n");
}

NAKED static void text_080eb6e8(struct TextWindowText* t) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	ldrb r0, [r6, #0xd]\n\
	cmp r0, #6\n\
	bls _080EB6F4\n\
	b _080EB8B2\n\
_080EB6F4:\n\
	lsls r0, r0, #2\n\
	ldr r1, _080EB700 @ =_080EB704\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	mov pc, r0\n\
	.align 2, 0\n\
_080EB700: .4byte _080EB704\n\
_080EB704: @ jump table\n\
	.4byte _080EB720 @ case 0\n\
	.4byte _080EB744 @ case 1\n\
	.4byte _080EB74A @ case 2\n\
	.4byte _080EB766 @ case 3\n\
	.4byte _080EB802 @ case 4\n\
	.4byte _080EB864 @ case 5\n\
	.4byte _080EB8AE @ case 6\n\
_080EB720:\n\
	ldrb r1, [r6, #4]\n\
	adds r0, r6, #0\n\
	bl loadMugshot\n\
	ldr r1, _080EB7E8 @ =gVideoRegBuffer\n\
	ldrh r2, [r1]\n\
	movs r3, #0x80\n\
	lsls r3, r3, #1\n\
	adds r0, r3, #0\n\
	movs r3, #0\n\
	orrs r0, r2\n\
	strh r0, [r1]\n\
	str r3, [r1, #0xc]\n\
	ldr r0, _080EB7EC @ =gPaletteManager\n\
	strh r3, [r0]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB744:\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB74A:\n\
	movs r5, #0\n\
	movs r4, #1\n\
	strh r4, [r6, #2]\n\
	ldr r0, [r6, #0x1c]\n\
	bl getStringLength\n\
	strh r0, [r6, #0x10]\n\
	strh r4, [r6, #0x12]\n\
	movs r0, #4\n\
	strh r0, [r6, #0x14]\n\
	strb r5, [r6, #0xe]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB766:\n\
	ldr r0, [r6, #8]\n\
	cmp r0, #0\n\
	beq _080EB776\n\
	ldrh r1, [r6]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB786\n\
_080EB776:\n\
	ldr r0, _080EB7F0 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB786\n\
	movs r0, #1\n\
	strb r0, [r6, #0xe]\n\
_080EB786:\n\
	ldrb r0, [r6, #0xe]\n\
	cmp r0, #0\n\
	bne _080EB798\n\
	ldr r0, _080EB7F4 @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB79C\n\
_080EB798:\n\
	movs r0, #0\n\
	strh r0, [r6, #0x14]\n\
_080EB79C:\n\
	ldr r0, [r6, #0x1c]\n\
	ldrh r3, [r6, #0x12]\n\
	movs r1, #1\n\
	movs r2, #0x12\n\
	bl text_080e9b40\n\
	ldr r0, [r6, #0x1c]\n\
	movs r2, #0x12\n\
	ldrsh r1, [r6, r2]\n\
	subs r1, #1\n\
	bl SkipString\n\
	ldrh r0, [r6, #0x14]\n\
	subs r0, #1\n\
	strh r0, [r6, #0x14]\n\
	lsls r0, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	movs r1, #1\n\
	rsbs r1, r1, #0\n\
	cmp r0, r1\n\
	bne _080EB8B2\n\
	ldrh r1, [r6, #0x12]\n\
	adds r0, r1, #1\n\
	strh r0, [r6, #0x12]\n\
	ldrb r0, [r6, #0xe]\n\
	cmp r0, #0\n\
	beq _080EB7D6\n\
	adds r0, r1, #4\n\
	strh r0, [r6, #0x12]\n\
_080EB7D6:\n\
	movs r3, #0x12\n\
	ldrsh r1, [r6, r3]\n\
	movs r2, #0x10\n\
	ldrsh r0, [r6, r2]\n\
	cmp r1, r0\n\
	bge _080EB7F8\n\
	movs r0, #3\n\
	strh r0, [r6, #0x14]\n\
	b _080EB8B2\n\
	.align 2, 0\n\
_080EB7E8: .4byte gVideoRegBuffer\n\
_080EB7EC: .4byte gPaletteManager\n\
_080EB7F0: .4byte gJoypad\n\
_080EB7F4: .4byte gTextWindow+8\n\
_080EB7F8:\n\
	movs r0, #0\n\
	strh r0, [r6, #0x14]\n\
	movs r0, #2\n\
	strh r0, [r6, #2]\n\
	b _080EB84E\n\
_080EB802:\n\
	ldr r0, [r6, #0x1c]\n\
	movs r1, #1\n\
	movs r2, #0x12\n\
	bl PrintString\n\
	ldrh r0, [r6, #0x14]\n\
	adds r1, r0, #1\n\
	strh r1, [r6, #0x14]\n\
	ldr r2, [r6, #8]\n\
	cmp r2, #0\n\
	beq _080EB824\n\
	movs r3, #0x14\n\
	ldrsh r0, [r6, r3]\n\
	cmp r0, r2\n\
	bgt _080EB84E\n\
	ldrh r1, [r6]\n\
	b _080EB846\n\
_080EB824:\n\
	movs r0, #0x10\n\
	ands r1, r0\n\
	cmp r1, #0\n\
	bne _080EB836\n\
	ldr r0, _080EB858 @ =Unicode_Prompt\n\
	movs r1, #0x1c\n\
	movs r2, #0x13\n\
	bl PrintUnicodeString\n\
_080EB836:\n\
	ldr r0, _080EB85C @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r0, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB84E\n\
	ldr r0, _080EB860 @ =gTextWindow+8\n\
	ldrh r1, [r0]\n\
_080EB846:\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB8B2\n\
_080EB84E:\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
	b _080EB8B2\n\
	.align 2, 0\n\
_080EB858: .4byte Unicode_Prompt\n\
_080EB85C: .4byte gJoypad\n\
_080EB860: .4byte gTextWindow+8\n\
_080EB864:\n\
	ldrh r1, [r6]\n\
	movs r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _080EB8A4\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080EB88C\n\
	ldr r0, [r6, #0x20]\n\
	cmp r0, #0\n\
	bne _080EB892\n\
	ldr r0, [r6, #0x1c]\n\
	movs r1, #1\n\
	movs r2, #0x12\n\
	bl PrintString\n\
	movs r0, #4\n\
	strh r0, [r6, #2]\n\
	b _080EB8B2\n\
_080EB88C:\n\
	ldr r0, [r6, #0x20]\n\
	cmp r0, #0\n\
	beq _080EB8A4\n\
_080EB892:\n\
	str r0, [r6, #0x1c]\n\
	adds r0, r6, #0\n\
	bl setupTextWindow\n\
	movs r0, #1\n\
	strh r0, [r6, #2]\n\
	movs r0, #2\n\
	strb r0, [r6, #0xd]\n\
	b _080EB8B2\n\
_080EB8A4:\n\
	movs r0, #5\n\
	strh r0, [r6, #2]\n\
	ldrb r0, [r6, #0xd]\n\
	adds r0, #1\n\
	strb r0, [r6, #0xd]\n\
_080EB8AE:\n\
	movs r0, #0\n\
	str r0, [r6, #0xc]\n\
_080EB8B2:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
 .syntax divided\n");
}

// --------------------------------------------

extern const u16 TextOfs_System[];
extern const u16 TextOfs_083789ac[];
extern const u16 TextOfs_CielChats[];
extern const u16 TextOfs_SpaceCraft[];
extern const u16 TextOfs_Volcano[];
extern const u16 TextOfs_OceanHighwayRuins[];
extern const u16 TextOfs_WeaponRepairFactory[];
extern const u16 TextOfs_OldLifeSpace[];
extern const u16 TextOfs_MissileFactory[];
extern const u16 TextOfs_TwilightDesert[];
extern const u16 TextOfs_AnatreForest[];
extern const u16 TextOfs_IceBase[];
extern const u16 TextOfs_AreaX2[];
extern const u16 TextOfs_EnergyFactory[];
extern const u16 TextOfs_SnowyPlains[];
extern const u16 TextOfs_SunkenLibrary[];
extern const u16 TextOfs_GiantElevator[];
extern const u16 TextOfs_SubArcadia[];
extern const u16 TextOfs_WeilLabo[];
extern const u16 TextOfs_Others[];

// clang-format off
// 0x083767b8
static const u16* const gTextOffsetTable[20] = {
  TextOfs_System,
  TextOfs_083789ac,
  TextOfs_CielChats,
  TextOfs_SpaceCraft,
  TextOfs_Volcano,
  TextOfs_OceanHighwayRuins,
  TextOfs_WeaponRepairFactory,
  TextOfs_OldLifeSpace,
  TextOfs_MissileFactory,
  TextOfs_TwilightDesert,
  TextOfs_AnatreForest,
  TextOfs_IceBase,
  TextOfs_AreaX2,
  TextOfs_EnergyFactory,
  TextOfs_SnowyPlains,
  TextOfs_SunkenLibrary,
  TextOfs_GiantElevator,
  TextOfs_SubArcadia,
  TextOfs_WeilLabo,
  TextOfs_Others,
};
// clang-format on

extern const char_t Text_System[];
extern const char_t Text_ResultNotifications[];
extern const char_t Text_CielChats[];
extern const char_t Text_SpaceCraft[];
extern const char_t Text_Volcano[];
extern const char_t Text_OceanHighwayRuins[];
extern const char_t Text_WeaponRepairFactory[];
extern const char_t Text_OldLifeSpace[];
extern const char_t Text_MissileFactory[];
extern const char_t Text_TwilightDesert[];
extern const char_t Texts_AnatreForest[];
extern const char_t Texts_IceBase[];
extern const char_t Texts_AreaX2[];
extern const char_t Texts_EnergyFactory[];
extern const char_t Texts_SnowyPlains[];
extern const char_t Text_SunkenLibrary[];
extern const char_t Texts_GiantElevator[];
extern const char_t Text_SubArcadia[];
extern const char_t Text_WeilLabo[];
extern const char_t Text_Others[];

// clang-format off
// 0x08376808
static const char_t* const gTextTable[20] = {
    Text_System,
    Text_ResultNotifications,
    Text_CielChats,
    Text_SpaceCraft,
    Text_Volcano,
    Text_OceanHighwayRuins,
    Text_WeaponRepairFactory,
    Text_OldLifeSpace,
    Text_MissileFactory,
    Text_TwilightDesert,
    Texts_AnatreForest,
    Texts_IceBase,
    Texts_AreaX2,
    Texts_EnergyFactory,
    Texts_SnowyPlains,
    Text_SunkenLibrary,
    Texts_GiantElevator,
    Text_SubArcadia,
    Text_WeilLabo,
    Text_Others,
};
// clang-format on

// 0x08376858
static const u32 sVramOffsets[2] = {0x4C00, 0x5800};

// 0x08376860
static const u16 MugshotLeftTileMasks[] = {
    0x1260, 0x1261, 0x1262, 0x1263, 0x1264, 0x1265, 0x1266, 0x1267, 0x1268, 0x1269, 0x126A, 0x126B, 0x126C, 0x126D, 0x126E, 0x126F, 0x1270, 0x1271, 0x1272, 0x1273, 0x1274, 0x1275, 0x1276, 0x1277, 0x1278, 0x1279, 0x127A, 0x127B, 0x127C, 0x127D, 0x127E, 0x127F, 0x1280, 0x1281, 0x1282, 0x1283, 0x1284, 0x1285, 0x1286, 0x1287, 0x1288, 0x1289, 0x128A, 0x128B, 0x128C, 0x128D, 0x128E, 0x128F,
};

// 0x083768c0
static const u16 MugshotRightTileMasks[] = {
    0x1665, 0x1664, 0x1663, 0x1662, 0x1661, 0x1660, 0x166B, 0x166A, 0x1669, 0x1668, 0x1667, 0x1666, 0x1671, 0x1670, 0x166F, 0x166E, 0x166D, 0x166C, 0x1677, 0x1676, 0x1675, 0x1674, 0x1673, 0x1672, 0x167D, 0x167C, 0x167B, 0x167A, 0x1679, 0x1678, 0x1683, 0x1682, 0x1681, 0x1680, 0x167F, 0x167E, 0x1689, 0x1688, 0x1687, 0x1686, 0x1685, 0x1684, 0x168F, 0x168E, 0x168D, 0x168C, 0x168B, 0x168A,
};
