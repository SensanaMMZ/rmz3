#include "palette_animation.h"

#include "gba/gba.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"

/**
 * @brief wBlinks(0x02001fe0 から 0x02001ff0 まで)をゼロクリアする
 * @note 0x08003d84
 */
void RemoveAllPaletteAnimations(void) {
  u16* start = (u16*)&gPaletteAnimationManager;
  u16 fill = 0;
  u16* id = &start[MAX_PLTT_ANIM - 1];
  do {
    *id = fill;
    id--;
  } while ((s32)id >= (s32)start);
}

/**
 * @brief CMD室の世界地図のような時間経過で色が変わるオブジェクトの色を変える処理(つまり点滅処理)を行う
 * @note 0x08003df4
 */
static inline void TransferPalettes(struct PaletteAnimation* b) {
  struct MotionPltt* pal = b->pal;
  s16 len = (pal->end - pal->start) + 1;  // number of colors (len*2 = bytes)
  if ((b->palIdx & 0x1FF) == 0) {
    s16 idx = (b->m).cmds[(b->m).step][(b->m).cmdIdx].spriteIdx;  // palette index to transfer
    u16* src = (u16*)(pal + 1) + (idx * len);
    s32 dst_byte_offset = b->palIdx + (pal->start << 1);
    CpuCopy16(src, ((u8*)gPaletteManager.buf + dst_byte_offset), (len << 1));
  } else {
    s16 idx = (b->m).cmds[(b->m).step][(b->m).cmdIdx].spriteIdx;  // palette index to transfer
    u16* src = (u16*)(pal + 1) + (idx * len);
    s32 dst_byte_offset = b->palIdx + ((pal->start << 1) & 0x1F);
    CpuCopy16(src, ((u8*)gPaletteManager.buf + dst_byte_offset), (len << 1));
  }
}

void TransferAnimatedPalettesToPaletteBuffer(void) {
  s32 i;
  for (i = 0; i < MAX_PLTT_ANIM; i++) {
    if (gPaletteAnimationManager.ids[i] != 0) {
      struct PaletteAnimation* b = &gPaletteAnimationManager.blinks[i];
      if (!b->paused) TransferPalettes(b);
    }
  }
}

/**
 * @brief Blinkingを一時停止させる？ メニュー画面に入る時とか
 * @note 0x08003ecc
 */
void PauseAllPaletteAnimations(void) {
  s32 i;
  for (i = 0; i < MAX_PLTT_ANIM; i++) {
    if ((gPaletteAnimationManager.ids)[i] != 0) {
      (gPaletteAnimationManager.blinks)[i].paused = TRUE;
    }
  }
}

/**
 * @brief メニュー画面から出る時
 */
void ResumeAllPaletteAnimations(void) {
  s32 i;
  for (i = 0; i < MAX_PLTT_ANIM; i++) {
    if ((gPaletteAnimationManager.ids)[i] != 0) {
      if ((gPaletteAnimationManager.blinks)[i].paused) {
        (gPaletteAnimationManager.blinks)[i].paused = FALSE;
      } else {
        (gPaletteAnimationManager.ids)[i] = 0;
      }
    }
  }
}

/**
 * @brief wBlinks で最初に0のエントリiを探して、wBlinks[i] と wFilms[i] に新たなBlinkをセットする
 * @param blinkID BlinkのID 0x085be764 のidx
 * @param ofs Paletteオフセット (詳細はTODO)
 * @note 0x08003f2c
 */
#if MODERN
void StartPaletteAnimation(u16 blinkID, u16 ofs) {
  s32 i;

  for (i = 0; i < MAX_PLTT_ANIM; i++) {
    if (gPaletteAnimationManager.ids[i] == (blinkID + 1)) {
      return;
    }
  }
  for (i = 0; i < MAX_PLTT_ANIM; i++) {
    if (gPaletteAnimationManager.ids[i] == 0) break;
  }
  if (i != MAX_PLTT_ANIM) {
    struct PaletteAnimation* b = &gPaletteAnimationManager.blinks[i];
    b->pal = SELF_REL_PTR(&gBlinkMotionColorOffsets[blinkID]);  // NOTE: ここのレジスタ割り当てだけが合わない (NON_MATCH の原因)
    b->cmds = (struct MotionCmd**)gBlinkMotionCmdTable[blinkID];
    b->paused = FALSE;
    b->palIdx = ofs;
    ResetMotion(&b->m, (const struct MotionCmd* const*)b->cmds);
    SetMotionSubID(&b->m, 0);
    TransferPalettes(b);
    gPaletteAnimationManager.ids[i] = (blinkID + 1);  // 0 は空きエントリを意味するので blinkID+1
  }
}
#else
NAKED void StartPaletteAnimation(u16 blinkID, u16 ofs) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	lsls r0, r0, #0x10\n\
	lsrs r4, r0, #0x10\n\
	lsls r1, r1, #0x10\n\
	lsrs r7, r1, #0x10\n\
	movs r6, #0\n\
	ldr r3, _08003FF4 @ =gPaletteAnimationManager\n\
	adds r0, r4, #1\n\
	mov r8, r0\n\
	mov r2, r8\n\
	adds r1, r3, #0\n\
_08003F46:\n\
	ldrh r0, [r1]\n\
	cmp r0, r2\n\
	bne _08003F4E\n\
	b _08004050\n\
_08003F4E:\n\
	adds r1, #2\n\
	adds r6, #1\n\
	cmp r6, #0xf\n\
	ble _08003F46\n\
	movs r6, #0\n\
	ldrh r0, [r3]\n\
	cmp r0, #0\n\
	beq _08003F6E\n\
	adds r1, r3, #0\n\
_08003F60:\n\
	adds r1, #2\n\
	adds r6, #1\n\
	cmp r6, #0xf\n\
	bgt _08003F6E\n\
	ldrh r0, [r1]\n\
	cmp r0, #0\n\
	bne _08003F60\n\
_08003F6E:\n\
	cmp r6, #0x10\n\
	beq _08004050\n\
	lsls r0, r6, #2\n\
	adds r0, r0, r6\n\
	lsls r0, r0, #2\n\
	ldr r1, _08003FF8 @ =gPaletteAnimationManager+32\n\
	adds r5, r0, r1\n\
	lsls r1, r4, #2\n\
	ldr r0, _08003FFC @ =gBlinkMotionColorOffsets\n\
	adds r2, r1, r0\n\
	ldr r0, [r2]\n\
	adds r0, r0, r2\n\
	str r0, [r5]\n\
	ldr r0, _08004000 @ =gBlinkMotionCmdTable\n\
	adds r1, r1, r0\n\
	ldr r1, [r1]\n\
	str r1, [r5, #4]\n\
	movs r0, #0\n\
	strh r0, [r5, #0x10]\n\
	strh r7, [r5, #0x12]\n\
	adds r4, r5, #0\n\
	adds r4, #8\n\
	adds r0, r4, #0\n\
	bl ResetMotion\n\
	adds r0, r4, #0\n\
	movs r1, #0\n\
	bl SetMotionSubID\n\
	ldr r2, [r5]\n\
	ldrb r0, [r2, #2]\n\
	ldrb r4, [r2, #1]\n\
	subs r0, r0, r4\n\
	adds r0, #1\n\
	lsls r0, r0, #0x10\n\
	lsrs r3, r0, #0x10\n\
	ldrh r1, [r5, #0x12]\n\
	ldr r0, _08004004 @ =0x000001FF\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _08004010\n\
	ldrb r1, [r5, #0xc]\n\
	ldr r0, [r5, #8]\n\
	lsls r1, r1, #2\n\
	adds r1, r1, r0\n\
	movs r0, #0xd\n\
	ldrsb r0, [r5, r0]\n\
	ldr r1, [r1]\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrb r0, [r0]\n\
	lsls r3, r3, #0x10\n\
	asrs r3, r3, #0x10\n\
	muls r0, r3, r0\n\
	lsls r0, r0, #1\n\
	adds r0, #4\n\
	adds r0, r2, r0\n\
	lsls r1, r4, #1\n\
	ldrh r5, [r5, #0x12]\n\
	adds r1, r1, r5\n\
	ldr r2, _08004008 @ =gPaletteManager\n\
	adds r1, r1, r2\n\
	ldr r2, _0800400C @ =0x001FFFFF\n\
	ands r2, r3\n\
	bl CpuSet\n\
	b _08004046\n\
	.align 2, 0\n\
_08003FF4: .4byte gPaletteAnimationManager\n\
_08003FF8: .4byte gPaletteAnimationManager+32\n\
_08003FFC: .4byte gBlinkMotionColorOffsets\n\
_08004000: .4byte gBlinkMotionCmdTable\n\
_08004004: .4byte 0x000001FF\n\
_08004008: .4byte gPaletteManager\n\
_0800400C: .4byte 0x001FFFFF\n\
_08004010:\n\
	ldrb r1, [r5, #0xc]\n\
	ldr r0, [r5, #8]\n\
	lsls r1, r1, #2\n\
	adds r1, r1, r0\n\
	movs r0, #0xd\n\
	ldrsb r0, [r5, r0]\n\
	ldr r1, [r1]\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r1\n\
	ldrb r0, [r0]\n\
	lsls r3, r3, #0x10\n\
	asrs r3, r3, #0x10\n\
	muls r0, r3, r0\n\
	lsls r0, r0, #1\n\
	adds r0, #4\n\
	adds r0, r2, r0\n\
	lsls r1, r4, #1\n\
	movs r2, #0x1f\n\
	ands r1, r2\n\
	ldrh r5, [r5, #0x12]\n\
	adds r1, r1, r5\n\
	ldr r2, _0800405C @ =gPaletteManager\n\
	adds r1, r1, r2\n\
	ldr r2, _08004060 @ =0x001FFFFF\n\
	ands r2, r3\n\
	bl CpuSet\n\
_08004046:\n\
	ldr r1, _08004064 @ =gPaletteAnimationManager\n\
	lsls r0, r6, #1\n\
	adds r0, r0, r1\n\
	mov r1, r8\n\
	strh r1, [r0]\n\
_08004050:\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_0800405C: .4byte gPaletteManager\n\
_08004060: .4byte 0x001FFFFF\n\
_08004064: .4byte gPaletteAnimationManager\n\
	 .syntax divided\n");
}
#endif

/**
 * @note 0x08004068
 */
u32 StepPaletteAnimation(u16 blinkID) {
  struct PaletteAnimation* b;
  s32 i;

  blinkID++;
  for (i = 0; i < MAX_PLTT_ANIM; i++) {
    if ((gPaletteAnimationManager.ids)[i] == blinkID) {
      break;
    }
  }
  if (i == MAX_PLTT_ANIM) {
    return MOTION_END;
  }
  b = &gPaletteAnimationManager.blinks[i];
  UpdateMotionState(&b->m);
  return b->m.state;
}

/**
 * @brief wBlinks の該当エントリ(wBlinks[i] = (n+1)) を0クリアする
 * @param n BlinkのID 0x085be764 のidx
 * @note 0x080040b4
 */
void RemovePaletteAnimation(u16 blinkID) {
  s32 i;

  blinkID++;
  for (i = 0; i < MAX_PLTT_ANIM; i++) {
    if ((gPaletteAnimationManager.ids)[i] == blinkID) {
      break;
    }
  }
  if (i != MAX_PLTT_ANIM) {
    (gPaletteAnimationManager.ids)[i] = 0;
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

const u32 gBlinkMotionColorOffsets[BLINK_NUM] = {
    0x00000460, 0x00000484, 0x000004A8, 0x000004CC, 0x000004E0, 0x00000514, 0x00000600, 0x0000060C, 0x00000708, 0x000007C8, 0x000008C4, 0x000008D0, 0x00000A50, 0x00000B10, 0x00000BD0, 0x00000C70, 0x00000DB0, 0x00000E50, 0x00000EF0, 0x00000F90, 0x00001030, 0x00001170, 0x00001210, 0x000012B0, 0x00001350, 0x00001490, 0x000014D0, 0x000015B0, 0x00001630, 0x000016B0, 0x00001770, 0x000019F0, 0x00001AB0, 0x00001C68, 0x00002138, 0x00002144, 0x00002154, 0x00002164, 0x0000217C, 0x00002180, 0x0000218C, 0x00002228, 0x00002348, 0x00002408, 0x00002414, 0x00002474, 0x00002564, 0x00002588, 0x00002594, 0x00002634, 0x00002670, 0x000026A0, 0x000026D0, 0x000026D4, 0x00002704, 0x00002724, 0x00002730, 0x00002750, 0x000027D4, 0x000027E0, 0x00002804, 0x00002840, 0x000028C0, 0x000028F4, 0x00002934, 0x000029B4, 0x00002A34, 0x00002A44, 0x00002A54, 0x00002A88,
    0x00002B28, 0x00002BE8, 0x00002CA8, 0x00002D28, 0x00002DA8, 0x00002F48, 0x00002FC8, 0x00003168, 0x000032E8, 0x00003468, 0x000034E0, 0x00003518, 0x0000354C, 0x000035CC, 0x0000364C, 0x000036AC, 0x000037CC, 0x0000390C, 0x0000394C, 0x000039CC, 0x00003A4C, 0x00003ACC, 0x00003AEC, 0x00003B0C, 0x00003B2C, 0x00003B4C, 0x00003B6C, 0x00003DCC, 0x00003FCC, 0x0000404C, 0x0000416C, 0x00003B58, 0x00004208, 0x000042C8, 0x00004388, 0x00004390, 0x000043B4, 0x000043C8, 0x000044A8, 0x000044B4, 0x000044C0, 0x000044E0, 0x00004560, 0x00004710, 0x00004714, 0x00004730, 0x0000474C, 0x00004764, 0x00004770, 0x0000477C, 0x000047CC, 0x000048BC, 0x000048DC, 0x00004984, 0x00004B44, 0x00004D3C, 0x00004D50, 0x00004D5C, 0x00004E28, 0x00004EB4, 0x00004EEC, 0x00004F00, 0x00004F8C, 0x00004FA4, 0x00004FB4, 0x00004FD4, 0x00004FEC, 0x0000500C, 0x0000502C, 0x00005044,
    0x00005048, 0x00005054, 0x00005064, 0x00005148, 0x00005304, 0x00005484, 0x000054AC, 0x000054D4, 0x000054EC, 0x00005500, 0x00005514, 0x00005578, 0x0000557C, 0x00005584, 0x000055C0, 0x000055CC, 0x000055D8, 0x000055E4, 0x000055F0, 0x000055FC, 0x000056C4, 0x000056D8, 0x000056EC, 0x00005770, 0x0000577C, 0x0000578C, 0x00005794, 0x000057A4, 0x00005924, 0x000059E4, 0x00005AE4, 0x00005C24, 0x00005C48, 0x00005C6C, 0x00005C90, 0x00005CB4, 0x00005CD8, 0x00005CFC, 0x00005D04, 0x00005D10, 0x00005D34, 0x00005D58, 0x00005D7C, 0x00005DA0, 0x00005DC4, 0x0000017C, 0x00000178, 0x00005DE0, 0x00005E60, 0x00005EE0, 0x00005FA0, 0x00006120, 0x00006144, 0x00006148, 0x000061C8, 0x00006248, 0x00006338, 0x00006348, 0x000063A8, 0x000063BC, 0x000063C4, 0x000063E4, 0x000063F8, 0x000064A0, 0x00006520, 0x00006540, 0x000065CC, 0x00006658, 0x000066B4, 0x00006710,
    0x000067B0, 0x000067F8, 0x0000687C, 0x00006894, 0x000068B4, 0x000068D4, 0x000068E0, 0x00006908, 0x00006924, 0x00006944, 0x00006950, 0x000069D0, 0x00006A30, 0x00006A94, 0x00006AE4, 0x00006BE8, 0x00006C88, 0x00006CA8, 0x00006D08, 0x00006DC0, 0x00006DD0, 0x00006E0C, 0x00006E1C, 0x00006E2C, 0x00006E3C, 0x00006FA8, 0x00006FB8, 0x00006FC8, 0x00006FD8, 0x00007004, 0x00007030, 0x000072F0, 0x00007330, 0x00007530, 0x00007554, 0x00007574, 0x00007594, 0x000075B4, 0x000075D4, 0x00007614, 0x00007654, 0x000076D4, 0x000077B4, 0x00007894, 0x00007974, 0x00007A54, 0x00007B34, 0x00007C14, 0x00007CF4, 0x00007DD4, 0x00007DEC, 0x00007E04, 0x00007E1C, 0x00007EAC, 0x00007EC4, 0x00007F84, 0x000080B4, 0x000080D8, 0x000080E0, 0x000080E8, 0x00008198, 0x000081B8, 0x000081D8, 0x00008258, 0x00008294, 0x000082B4, 0x000082D4, 0x00008434, 0x00008454, 0x000085B4,
};

// ./tools/dumper/bin.ts baserom.gba 0x085b6130 0x085be764 data/blink_pal.bin
INCBIN("data/blink_pal.bin");

// clang-format off
struct BlinkCmds2 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[2];
};
struct BlinkCmds4 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[4];
};
struct BlinkCmds6 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[6];
};
struct BlinkCmds8 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[8];
};
struct BlinkCmds10 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[10];
};
struct BlinkCmds12 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[12];
};
struct BlinkCmds14 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[14];
};
struct BlinkCmds16 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[16];
};
struct BlinkCmds18 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[18];
};
struct BlinkCmds20 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[20];
};
struct BlinkCmds22 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[22];
};
struct BlinkCmds24 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[24];
};
struct BlinkCmds26 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[26];
};
struct BlinkCmds28 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[28];
};
struct BlinkCmds34 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[34];
};
struct BlinkCmds50 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[50];
};
struct BlinkCmds66 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[66];
};
struct BlinkCmds72 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[72];
};
struct BlinkCmds100 {
  const struct MotionCmd* p;
  struct MotionCmd cmds[100];
};

extern const struct BlinkCmds8 gBlinkCmd_000;
extern const struct BlinkCmds8 gBlinkCmd_001;
extern const struct BlinkCmds8 gBlinkCmd_002;
extern const struct BlinkCmds2 gBlinkCmd_003;
extern const struct BlinkCmds10 gBlinkCmd_Menu;
extern const struct BlinkCmds18 gBlinkCmd_005;
extern const struct BlinkCmds10 gBlinkCmd_006;
extern const struct BlinkCmds18 gBlinkCmd_007;
extern const struct BlinkCmds14 gBlinkCmd_008;
extern const struct BlinkCmds18 gBlinkCmd_009;
extern const struct BlinkCmds12 gBlinkCmd_010;
extern const struct BlinkCmds14 gBlinkCmd_011;
extern const struct BlinkCmds8 gBlinkCmd_012;
extern const struct BlinkCmds8 gBlinkCmd_013;
extern const struct BlinkCmds6 gBlinkCmd_014;
extern const struct BlinkCmds12 gBlinkCmd_015;
extern const struct BlinkCmds6 gBlinkCmd_016;
extern const struct BlinkCmds6 gBlinkCmd_017;
extern const struct BlinkCmds6 gBlinkCmd_018;
extern const struct BlinkCmds6 gBlinkCmd_019;
extern const struct BlinkCmds12 gBlinkCmd_020;
extern const struct BlinkCmds6 gBlinkCmd_021;
extern const struct BlinkCmds6 gBlinkCmd_022;
extern const struct BlinkCmds6 gBlinkCmd_023;
extern const struct BlinkCmds14 gBlinkCmd_024;
extern const struct BlinkCmds4 gBlinkCmd_025;
extern const struct BlinkCmds10 gBlinkCmd_026;
extern const struct BlinkCmds6 gBlinkCmd_027;
extern const struct BlinkCmds6 gBlinkCmd_028;
extern const struct BlinkCmds8 gBlinkCmd_029;
extern const struct BlinkCmds22 gBlinkCmd_030;
extern const struct BlinkCmds6 gBlinkCmd_031;
extern const struct BlinkCmds66 gBlinkCmd_032;
extern const struct BlinkCmds100 gBlinkCmd_033;
extern const struct BlinkCmds10 gBlinkCmd_034;
extern const struct BlinkCmds8 gBlinkCmd_035;
extern const struct BlinkCmds18 gBlinkCmd_036;
extern const struct BlinkCmds12 gBlinkCmd_037;
extern const struct BlinkCmds4 gBlinkCmd_038;
extern const struct BlinkCmds10 gBlinkCmd_039;
extern const struct BlinkCmds28 gBlinkCmd_040;
extern const struct BlinkCmds10 gBlinkCmd_041;
extern const struct BlinkCmds8 gBlinkCmd_042;
extern const struct BlinkCmds12 gBlinkCmd_043;
extern const struct BlinkCmds14 gBlinkCmd_044;
extern const struct BlinkCmds22 gBlinkCmd_045;
extern const struct BlinkCmds12 gBlinkCmd_046;
extern const struct BlinkCmds12 gBlinkCmd_047;
extern const struct BlinkCmds18 gBlinkCmd_048;
extern const struct BlinkCmds12 gBlinkCmd_049;
extern const struct BlinkCmds12 gBlinkCmd_050;
extern const struct BlinkCmds12 gBlinkCmd_051;
extern const struct BlinkCmds8 gBlinkCmd_052;
extern const struct BlinkCmds12 gBlinkCmd_053;
extern const struct BlinkCmds6 gBlinkCmd_054;
extern const struct BlinkCmds12 gBlinkCmd_055;
extern const struct BlinkCmds6 gBlinkCmd_056;
extern const struct BlinkCmds12 gBlinkCmd_057;
extern const struct BlinkCmds12 gBlinkCmd_058;
extern const struct BlinkCmds12 gBlinkCmd_059;
extern const struct BlinkCmds12 gBlinkCmd_060;
extern const struct BlinkCmds8 gBlinkCmd_061;
extern const struct BlinkCmds10 gBlinkCmd_062;
extern const struct BlinkCmds8 gBlinkCmd_063;
extern const struct BlinkCmds10 gBlinkCmd_064;
extern const struct BlinkCmds10 gBlinkCmd_065;
extern const struct BlinkCmds2 gBlinkCmd_066;
extern const struct BlinkCmds2 gBlinkCmd_067;
extern const struct BlinkCmds10 gBlinkCmd_068;
extern const struct BlinkCmds10 gBlinkCmd_069;
extern const struct BlinkCmds8 gBlinkCmd_070;
extern const struct BlinkCmds8 gBlinkCmd_071;
extern const struct BlinkCmds6 gBlinkCmd_072;
extern const struct BlinkCmds6 gBlinkCmd_073;
extern const struct BlinkCmds14 gBlinkCmd_074;
extern const struct BlinkCmds6 gBlinkCmd_075;
extern const struct BlinkCmds14 gBlinkCmd_076;
extern const struct BlinkCmds18 gBlinkCmd_077;
extern const struct BlinkCmds16 gBlinkCmd_078;
extern const struct BlinkCmds6 gBlinkCmd_079;
extern const struct BlinkCmds14 gBlinkCmd_080;
extern const struct BlinkCmds10 gBlinkCmd_081;
extern const struct BlinkCmds6 gBlinkCmd_082;
extern const struct BlinkCmds6 gBlinkCmd_083;
extern const struct BlinkCmds6 gBlinkCmd_084;
extern const struct BlinkCmds28 gBlinkCmd_085;
extern const struct BlinkCmds28 gBlinkCmd_086;
extern const struct BlinkCmds4 gBlinkCmd_087;
extern const struct BlinkCmds6 gBlinkCmd_088;
extern const struct BlinkCmds4 gBlinkCmd_089;
extern const struct BlinkCmds4 gBlinkCmd_090;
extern const struct BlinkCmds6 gBlinkCmd_091;
extern const struct BlinkCmds2 gBlinkCmd_092;
extern const struct BlinkCmds2 gBlinkCmd_093;
extern const struct BlinkCmds2 gBlinkCmd_094;
extern const struct BlinkCmds2 gBlinkCmd_095;
extern const struct BlinkCmds20 gBlinkCmd_096;
extern const struct BlinkCmds18 gBlinkCmd_097;
extern const struct BlinkCmds6 gBlinkCmd_098;
extern const struct BlinkCmds26 gBlinkCmd_099;
extern const struct BlinkCmds6 gBlinkCmd_100;
extern const struct BlinkCmds8 gBlinkCmd_102;
extern const struct BlinkCmds8 gBlinkCmd_103;
extern const struct BlinkCmds4 gBlinkCmd_104;
extern const struct BlinkCmds12 gBlinkCmd_105;
extern const struct BlinkCmds10 gBlinkCmd_106;
extern const struct BlinkCmds16 gBlinkCmd_107;
extern const struct BlinkCmds4 gBlinkCmd_108;
extern const struct BlinkCmds4 gBlinkCmd_109;
extern const struct BlinkCmds6 gBlinkCmd_110;
extern const struct BlinkCmds10 gBlinkCmd_111;
extern const struct BlinkCmds20 gBlinkCmd_112;
extern const struct BlinkCmds2 gBlinkCmd_113;
extern const struct BlinkCmds8 gBlinkCmd_114;
extern const struct BlinkCmds8 gBlinkCmd_115;
extern const struct BlinkCmds12 gBlinkCmd_116;
extern const struct BlinkCmds12 gBlinkCmd_117;
extern const struct BlinkCmds12 gBlinkCmd_118;
extern const struct BlinkCmds10 gBlinkCmd_119;
extern const struct BlinkCmds10 gBlinkCmd_120;
extern const struct BlinkCmds2 gBlinkCmd_121;
extern const struct BlinkCmds12 gBlinkCmd_122;
extern const struct BlinkCmds18 gBlinkCmd_123;
extern const struct BlinkCmds20 gBlinkCmd_124;
extern const struct BlinkCmds10 gBlinkCmd_125;
extern const struct BlinkCmds12 gBlinkCmd_126;
extern const struct BlinkCmds18 gBlinkCmd_127;
extern const struct BlinkCmds16 gBlinkCmd_128;
extern const struct BlinkCmds14 gBlinkCmd_129;
extern const struct BlinkCmds6 gBlinkCmd_130;
extern const struct BlinkCmds4 gBlinkCmd_131;
extern const struct BlinkCmds4 gBlinkCmd_132;
extern const struct BlinkCmds16 gBlinkCmd_133;
extern const struct BlinkCmds16 gBlinkCmd_134;
extern const struct BlinkCmds4 gBlinkCmd_135;
extern const struct BlinkCmds16 gBlinkCmd_136;
extern const struct BlinkCmds6 gBlinkCmd_137;
extern const struct BlinkCmds6 gBlinkCmd_138;
extern const struct BlinkCmds4 gBlinkCmd_139;
extern const struct BlinkCmds4 gBlinkCmd_140;
extern const struct BlinkCmds4 gBlinkCmd_141;
extern const struct BlinkCmds20 gBlinkCmd_142;
extern const struct BlinkCmds72 gBlinkCmd_143;
extern const struct BlinkCmds26 gBlinkCmd_144;
extern const struct BlinkCmds20 gBlinkCmd_145;
extern const struct BlinkCmds20 gBlinkCmd_146;
extern const struct BlinkCmds22 gBlinkCmd_147;
extern const struct BlinkCmds4 gBlinkCmd_148;
extern const struct BlinkCmds16 gBlinkCmd_149;
extern const struct BlinkCmds8 gBlinkCmd_150;
extern const struct BlinkCmds4 gBlinkCmd_151;
extern const struct BlinkCmds8 gBlinkCmd_152;
extern const struct BlinkCmds10 gBlinkCmd_153;
extern const struct BlinkCmds12 gBlinkCmd_154;
extern const struct BlinkCmds8 gBlinkCmd_155;
extern const struct BlinkCmds12 gBlinkCmd_156;
extern const struct BlinkCmds8 gBlinkCmd_157;
extern const struct BlinkCmds8 gBlinkCmd_158;
extern const struct BlinkCmds12 gBlinkCmd_159;
extern const struct BlinkCmds6 gBlinkCmd_160;
extern const struct BlinkCmds10 gBlinkCmd_161;
extern const struct BlinkCmds14 gBlinkCmd_162;
extern const struct BlinkCmds10 gBlinkCmd_163;
extern const struct BlinkCmds6 gBlinkCmd_164;
extern const struct BlinkCmds4 gBlinkCmd_165;
extern const struct BlinkCmds4 gBlinkCmd_166;
extern const struct BlinkCmds14 gBlinkCmd_167;
extern const struct BlinkCmds8 gBlinkCmd_168;
extern const struct BlinkCmds10 gBlinkCmd_169;
extern const struct BlinkCmds12 gBlinkCmd_170;
extern const struct BlinkCmds8 gBlinkCmd_171;
extern const struct BlinkCmds8 gBlinkCmd_172;
extern const struct BlinkCmds8 gBlinkCmd_173;
extern const struct BlinkCmds8 gBlinkCmd_174;
extern const struct BlinkCmds8 gBlinkCmd_175;
extern const struct BlinkCmds8 gBlinkCmd_176;
extern const struct BlinkCmds2 gBlinkCmd_177;
extern const struct BlinkCmds2 gBlinkCmd_178;
extern const struct BlinkCmds8 gBlinkCmd_179;
extern const struct BlinkCmds8 gBlinkCmd_180;
extern const struct BlinkCmds8 gBlinkCmd_181;
extern const struct BlinkCmds8 gBlinkCmd_182;
extern const struct BlinkCmds8 gBlinkCmd_183;
extern const struct BlinkCmds8 gBlinkCmd_184;
extern const struct BlinkCmds2 gBlinkCmd_187;
extern const struct BlinkCmds6 gBlinkCmd_188;
extern const struct BlinkCmds8 gBlinkCmd_189;
extern const struct BlinkCmds14 gBlinkCmd_190;
extern const struct BlinkCmds8 gBlinkCmd_191;
extern const struct BlinkCmds6 gBlinkCmd_192;
extern const struct BlinkCmds14 gBlinkCmd_193;
extern const struct BlinkCmds14 gBlinkCmd_194;
extern const struct BlinkCmds18 gBlinkCmd_195;
extern const struct BlinkCmds14 gBlinkCmd_196;
extern const struct BlinkCmds16 gBlinkCmd_197;
extern const struct BlinkCmds2 gBlinkCmd_198;
extern const struct BlinkCmds2 gBlinkCmd_199;
extern const struct BlinkCmds2 gBlinkCmd_200;
extern const struct BlinkCmds2 gBlinkCmd_201;
extern const struct BlinkCmds12 gBlinkCmd_202;
extern const struct BlinkCmds8 gBlinkCmd_203;
extern const struct BlinkCmds2 gBlinkCmd_204;
extern const struct BlinkCmds12 gBlinkCmd_205;
extern const struct BlinkCmds12 gBlinkCmd_206;
extern const struct BlinkCmds4 gBlinkCmd_207;
extern const struct BlinkCmds4 gBlinkCmd_208;
extern const struct BlinkCmds10 gBlinkCmd_209;
extern const struct BlinkCmds12 gBlinkCmd_210;
extern const struct BlinkCmds16 gBlinkCmd_211;
extern const struct BlinkCmds8 gBlinkCmd_212;
extern const struct BlinkCmds2 gBlinkCmd_213;
extern const struct BlinkCmds6 gBlinkCmd_214;
extern const struct BlinkCmds10 gBlinkCmd_215;
extern const struct BlinkCmds8 gBlinkCmd_216;
extern const struct BlinkCmds14 gBlinkCmd_217;
extern const struct BlinkCmds10 gBlinkCmd_218;
extern const struct BlinkCmds12 gBlinkCmd_219;
extern const struct BlinkCmds18 gBlinkCmd_220;
extern const struct BlinkCmds18 gBlinkCmd_221;
extern const struct BlinkCmds6 gBlinkCmd_222;
extern const struct BlinkCmds6 gBlinkCmd_223;
extern const struct BlinkCmds14 gBlinkCmd_224;
extern const struct BlinkCmds12 gBlinkCmd_225;
extern const struct BlinkCmds16 gBlinkCmd_226;
extern const struct BlinkCmds18 gBlinkCmd_227;
extern const struct BlinkCmds14 gBlinkCmd_228;
extern const struct BlinkCmds16 gBlinkCmd_229;
extern const struct BlinkCmds16 gBlinkCmd_230;
extern const struct BlinkCmds16 gBlinkCmd_231;
extern const struct BlinkCmds16 gBlinkCmd_232;
extern const struct BlinkCmds16 gBlinkCmd_233;
extern const struct BlinkCmds16 gBlinkCmd_234;
extern const struct BlinkCmds16 gBlinkCmd_235;
extern const struct BlinkCmds16 gBlinkCmd_236;
extern const struct BlinkCmds16 gBlinkCmd_237;
extern const struct BlinkCmds8 gBlinkCmd_238;
extern const struct BlinkCmds8 gBlinkCmd_239;
extern const struct BlinkCmds24 gBlinkCmd_240;
extern const struct BlinkCmds4 gBlinkCmd_241;
extern const struct BlinkCmds18 gBlinkCmd_242;
extern const struct BlinkCmds6 gBlinkCmd_243;
extern const struct BlinkCmds2 gBlinkCmd_244;
extern const struct BlinkCmds2 gBlinkCmd_245;
extern const struct BlinkCmds2 gBlinkCmd_246;
extern const struct BlinkCmds2 gBlinkCmd_247;
extern const struct BlinkCmds4 gBlinkCmd_248;
extern const struct BlinkCmds4 gBlinkCmd_249;
extern const struct BlinkCmds6 gBlinkCmd_250;
extern const struct BlinkCmds8 gBlinkCmd_251;
extern const struct BlinkCmds8 gBlinkCmd_252;
extern const struct BlinkCmds8 gBlinkCmd_253;
extern const struct BlinkCmds8 gBlinkCmd_254;
extern const struct BlinkCmds8 gBlinkCmd_255;
extern const struct BlinkCmds8 gBlinkCmd_256;
extern const struct BlinkCmds8 gBlinkCmd_257;
extern const struct BlinkCmds8 gBlinkCmd_258;
extern const struct BlinkCmds50 gBlinkCmd_259;
extern const struct BlinkCmds50 gBlinkCmd_260;
extern const struct BlinkCmds50 gBlinkCmd_261;
extern const struct BlinkCmds14 gBlinkCmd_262;
extern const struct BlinkCmds50 gBlinkCmd_263;
extern const struct BlinkCmds34 gBlinkCmd_264;
extern const struct BlinkCmds20 gBlinkCmd_265;
extern const struct BlinkCmds18 gBlinkCmd_266;
extern const struct BlinkCmds4 gBlinkCmd_267;
extern const struct BlinkCmds4 gBlinkCmd_268;
extern const struct BlinkCmds12 gBlinkCmd_269;
extern const struct BlinkCmds4 gBlinkCmd_270;
extern const struct BlinkCmds2 gBlinkCmd_271;
extern const struct BlinkCmds6 gBlinkCmd_272;
extern const struct BlinkCmds4 gBlinkCmd_273;
extern const struct BlinkCmds2 gBlinkCmd_274;
extern const struct BlinkCmds2 gBlinkCmd_275;
extern const struct BlinkCmds12 gBlinkCmd_276;
extern const struct BlinkCmds2 gBlinkCmd_277;
extern const struct BlinkCmds12 gBlinkCmd_278;
extern const struct BlinkCmds6 gBlinkCmd_279;

const struct MotionCmd* const * const gBlinkMotionCmdTable[BLINK_NUM] = {
    [0] =  (const struct MotionCmd* const*)&gBlinkCmd_000,
    [1] =  (const struct MotionCmd* const*)&gBlinkCmd_001,
    [2] =  (const struct MotionCmd* const*)&gBlinkCmd_002,
    [3] =  (const struct MotionCmd* const*)&gBlinkCmd_003,
    [4] =  (const struct MotionCmd* const*)&gBlinkCmd_Menu, // メニュー画面の点滅
    [5] =  (const struct MotionCmd* const*)&gBlinkCmd_005,
    [6] =  (const struct MotionCmd* const*)&gBlinkCmd_006,
    [7] =  (const struct MotionCmd* const*)&gBlinkCmd_007,
    [8] =  (const struct MotionCmd* const*)&gBlinkCmd_008,
    [9] =  (const struct MotionCmd* const*)&gBlinkCmd_009,
    [10] =  (const struct MotionCmd* const*)&gBlinkCmd_010,
    [11] =  (const struct MotionCmd* const*)&gBlinkCmd_011,
    [12] =  (const struct MotionCmd* const*)&gBlinkCmd_012,
    [13] =  (const struct MotionCmd* const*)&gBlinkCmd_013,
    [14] =  (const struct MotionCmd* const*)&gBlinkCmd_014,
    [15] =  (const struct MotionCmd* const*)&gBlinkCmd_015,
    [16] =  (const struct MotionCmd* const*)&gBlinkCmd_016,
    [17] =  (const struct MotionCmd* const*)&gBlinkCmd_017,
    [18] =  (const struct MotionCmd* const*)&gBlinkCmd_018,
    [19] =  (const struct MotionCmd* const*)&gBlinkCmd_019,
    [20] =  (const struct MotionCmd* const*)&gBlinkCmd_020,
    [21] =  (const struct MotionCmd* const*)&gBlinkCmd_021,
    [22] =  (const struct MotionCmd* const*)&gBlinkCmd_022,
    [23] =  (const struct MotionCmd* const*)&gBlinkCmd_023,
    [24] =  (const struct MotionCmd* const*)&gBlinkCmd_024,
    [25] =  (const struct MotionCmd* const*)&gBlinkCmd_025,
    [26] =  (const struct MotionCmd* const*)&gBlinkCmd_026,
    [27] =  (const struct MotionCmd* const*)&gBlinkCmd_027,
    [28] =  (const struct MotionCmd* const*)&gBlinkCmd_028,
    [29] =  (const struct MotionCmd* const*)&gBlinkCmd_029,
    [30] =  (const struct MotionCmd* const*)&gBlinkCmd_030,
    [31] =  (const struct MotionCmd* const*)&gBlinkCmd_031,
    [32] =  (const struct MotionCmd* const*)&gBlinkCmd_032,
    [33] =  (const struct MotionCmd* const*)&gBlinkCmd_033,
    [34] =  (const struct MotionCmd* const*)&gBlinkCmd_034,
    [35] =  (const struct MotionCmd* const*)&gBlinkCmd_035,
    [36] =  (const struct MotionCmd* const*)&gBlinkCmd_036,
    [37] =  (const struct MotionCmd* const*)&gBlinkCmd_037,
    [38] =  (const struct MotionCmd* const*)&gBlinkCmd_038,
    [39] =  (const struct MotionCmd* const*)&gBlinkCmd_039,
    [40] =  (const struct MotionCmd* const*)&gBlinkCmd_040,
    [41] =  (const struct MotionCmd* const*)&gBlinkCmd_041,
    [42] =  (const struct MotionCmd* const*)&gBlinkCmd_042,
    [43] =  (const struct MotionCmd* const*)&gBlinkCmd_043,
    [44] =  (const struct MotionCmd* const*)&gBlinkCmd_044,
    [45] =  (const struct MotionCmd* const*)&gBlinkCmd_045,
    [46] =  (const struct MotionCmd* const*)&gBlinkCmd_046,
    [47] =  (const struct MotionCmd* const*)&gBlinkCmd_047,
    [48] =  (const struct MotionCmd* const*)&gBlinkCmd_048,
    [49] =  (const struct MotionCmd* const*)&gBlinkCmd_049,
    [50] =  (const struct MotionCmd* const*)&gBlinkCmd_050,
    [51] =  (const struct MotionCmd* const*)&gBlinkCmd_051,
    [52] =  (const struct MotionCmd* const*)&gBlinkCmd_052,
    [53] =  (const struct MotionCmd* const*)&gBlinkCmd_053,
    [54] =  (const struct MotionCmd* const*)&gBlinkCmd_054,
    [55] =  (const struct MotionCmd* const*)&gBlinkCmd_055,
    [56] =  (const struct MotionCmd* const*)&gBlinkCmd_056,
    [57] =  (const struct MotionCmd* const*)&gBlinkCmd_057,
    [58] =  (const struct MotionCmd* const*)&gBlinkCmd_058,
    [59] =  (const struct MotionCmd* const*)&gBlinkCmd_059,
    [60] =  (const struct MotionCmd* const*)&gBlinkCmd_060,
    [61] =  (const struct MotionCmd* const*)&gBlinkCmd_061,
    [62] =  (const struct MotionCmd* const*)&gBlinkCmd_062,
    [63] =  (const struct MotionCmd* const*)&gBlinkCmd_063,
    [64] =  (const struct MotionCmd* const*)&gBlinkCmd_064,
    [65] =  (const struct MotionCmd* const*)&gBlinkCmd_065,
    [66] =  (const struct MotionCmd* const*)&gBlinkCmd_066,
    [67] =  (const struct MotionCmd* const*)&gBlinkCmd_067,
    [68] =  (const struct MotionCmd* const*)&gBlinkCmd_068,
    [69] =  (const struct MotionCmd* const*)&gBlinkCmd_069,
    [70] =  (const struct MotionCmd* const*)&gBlinkCmd_070,
    [71] =  (const struct MotionCmd* const*)&gBlinkCmd_071,
    [72] =  (const struct MotionCmd* const*)&gBlinkCmd_072,
    [73] =  (const struct MotionCmd* const*)&gBlinkCmd_073,
    [74] =  (const struct MotionCmd* const*)&gBlinkCmd_074,
    [75] =  (const struct MotionCmd* const*)&gBlinkCmd_075,
    [76] =  (const struct MotionCmd* const*)&gBlinkCmd_076,
    [77] =  (const struct MotionCmd* const*)&gBlinkCmd_077,
    [78] =  (const struct MotionCmd* const*)&gBlinkCmd_078,
    [79] =  (const struct MotionCmd* const*)&gBlinkCmd_079,
    [80] =  (const struct MotionCmd* const*)&gBlinkCmd_080,
    [81] =  (const struct MotionCmd* const*)&gBlinkCmd_081,
    [82] =  (const struct MotionCmd* const*)&gBlinkCmd_082,
    [83] =  (const struct MotionCmd* const*)&gBlinkCmd_083,
    [84] =  (const struct MotionCmd* const*)&gBlinkCmd_084,
    [85] =  (const struct MotionCmd* const*)&gBlinkCmd_085,
    [86] =  (const struct MotionCmd* const*)&gBlinkCmd_086,
    [87] =  (const struct MotionCmd* const*)&gBlinkCmd_087,
    [88] =  (const struct MotionCmd* const*)&gBlinkCmd_088,
    [89] =  (const struct MotionCmd* const*)&gBlinkCmd_089,
    [90] =  (const struct MotionCmd* const*)&gBlinkCmd_090,
    [91] =  (const struct MotionCmd* const*)&gBlinkCmd_091,
    [92] =  (const struct MotionCmd* const*)&gBlinkCmd_092,
    [93] =  (const struct MotionCmd* const*)&gBlinkCmd_093,
    [94] =  (const struct MotionCmd* const*)&gBlinkCmd_094,
    [95] =  (const struct MotionCmd* const*)&gBlinkCmd_095,
    [96] =  (const struct MotionCmd* const*)&gBlinkCmd_096,
    [97] =  (const struct MotionCmd* const*)&gBlinkCmd_097,
    [98] =  (const struct MotionCmd* const*)&gBlinkCmd_098,
    [99] =  (const struct MotionCmd* const*)&gBlinkCmd_099,
    [100] =  (const struct MotionCmd* const*)&gBlinkCmd_100,
    [101] =  (const struct MotionCmd* const*)&gBlinkCmd_096,
    [102] =  (const struct MotionCmd* const*)&gBlinkCmd_102,
    [103] =  (const struct MotionCmd* const*)&gBlinkCmd_103,
    [104] =  (const struct MotionCmd* const*)&gBlinkCmd_104,
    [105] =  (const struct MotionCmd* const*)&gBlinkCmd_105,
    [106] =  (const struct MotionCmd* const*)&gBlinkCmd_106,
    [107] =  (const struct MotionCmd* const*)&gBlinkCmd_107,
    [108] =  (const struct MotionCmd* const*)&gBlinkCmd_108,
    [109] =  (const struct MotionCmd* const*)&gBlinkCmd_109,
    [110] =  (const struct MotionCmd* const*)&gBlinkCmd_110,
    [111] =  (const struct MotionCmd* const*)&gBlinkCmd_111,
    [112] =  (const struct MotionCmd* const*)&gBlinkCmd_112,
    [113] =  (const struct MotionCmd* const*)&gBlinkCmd_113,
    [114] =  (const struct MotionCmd* const*)&gBlinkCmd_114,
    [115] =  (const struct MotionCmd* const*)&gBlinkCmd_115,
    [116] =  (const struct MotionCmd* const*)&gBlinkCmd_116,
    [117] =  (const struct MotionCmd* const*)&gBlinkCmd_117,
    [118] =  (const struct MotionCmd* const*)&gBlinkCmd_118,
    [119] =  (const struct MotionCmd* const*)&gBlinkCmd_119,
    [120] =  (const struct MotionCmd* const*)&gBlinkCmd_120,
    [121] =  (const struct MotionCmd* const*)&gBlinkCmd_121,
    [122] =  (const struct MotionCmd* const*)&gBlinkCmd_122,
    [123] =  (const struct MotionCmd* const*)&gBlinkCmd_123,
    [124] =  (const struct MotionCmd* const*)&gBlinkCmd_124,
    [125] =  (const struct MotionCmd* const*)&gBlinkCmd_125,
    [126] =  (const struct MotionCmd* const*)&gBlinkCmd_126,
    [127] =  (const struct MotionCmd* const*)&gBlinkCmd_127,
    [128] =  (const struct MotionCmd* const*)&gBlinkCmd_128,
    [129] =  (const struct MotionCmd* const*)&gBlinkCmd_129,
    [130] =  (const struct MotionCmd* const*)&gBlinkCmd_130,
    [131] =  (const struct MotionCmd* const*)&gBlinkCmd_131,
    [132] =  (const struct MotionCmd* const*)&gBlinkCmd_132,
    [133] =  (const struct MotionCmd* const*)&gBlinkCmd_133,
    [134] =  (const struct MotionCmd* const*)&gBlinkCmd_134,
    [135] =  (const struct MotionCmd* const*)&gBlinkCmd_135,
    [136] =  (const struct MotionCmd* const*)&gBlinkCmd_136,
    [137] =  (const struct MotionCmd* const*)&gBlinkCmd_137,
    [138] =  (const struct MotionCmd* const*)&gBlinkCmd_138,
    [139] =  (const struct MotionCmd* const*)&gBlinkCmd_139,
    [140] =  (const struct MotionCmd* const*)&gBlinkCmd_140,
    [141] =  (const struct MotionCmd* const*)&gBlinkCmd_141,
    [142] =  (const struct MotionCmd* const*)&gBlinkCmd_142,
    [143] =  (const struct MotionCmd* const*)&gBlinkCmd_143,
    [144] =  (const struct MotionCmd* const*)&gBlinkCmd_144,
    [145] =  (const struct MotionCmd* const*)&gBlinkCmd_145,
    [146] =  (const struct MotionCmd* const*)&gBlinkCmd_146,
    [147] =  (const struct MotionCmd* const*)&gBlinkCmd_147,
    [148] =  (const struct MotionCmd* const*)&gBlinkCmd_148,
    [149] =  (const struct MotionCmd* const*)&gBlinkCmd_149,
    [150] =  (const struct MotionCmd* const*)&gBlinkCmd_150,
    [151] =  (const struct MotionCmd* const*)&gBlinkCmd_151,
    [152] =  (const struct MotionCmd* const*)&gBlinkCmd_152,
    [153] =  (const struct MotionCmd* const*)&gBlinkCmd_153,
    [154] =  (const struct MotionCmd* const*)&gBlinkCmd_154,
    [155] =  (const struct MotionCmd* const*)&gBlinkCmd_155,
    [156] =  (const struct MotionCmd* const*)&gBlinkCmd_156,
    [157] =  (const struct MotionCmd* const*)&gBlinkCmd_157,
    [158] =  (const struct MotionCmd* const*)&gBlinkCmd_158,
    [159] =  (const struct MotionCmd* const*)&gBlinkCmd_159,
    [160] =  (const struct MotionCmd* const*)&gBlinkCmd_160,
    [161] =  (const struct MotionCmd* const*)&gBlinkCmd_161,
    [162] =  (const struct MotionCmd* const*)&gBlinkCmd_162,
    [163] =  (const struct MotionCmd* const*)&gBlinkCmd_163,
    [164] =  (const struct MotionCmd* const*)&gBlinkCmd_164,
    [165] =  (const struct MotionCmd* const*)&gBlinkCmd_165,
    [166] =  (const struct MotionCmd* const*)&gBlinkCmd_166,
    [167] =  (const struct MotionCmd* const*)&gBlinkCmd_167,
    [168] =  (const struct MotionCmd* const*)&gBlinkCmd_168,
    [169] =  (const struct MotionCmd* const*)&gBlinkCmd_169,
    [170] =  (const struct MotionCmd* const*)&gBlinkCmd_170,
    [171] =  (const struct MotionCmd* const*)&gBlinkCmd_171,
    [172] =  (const struct MotionCmd* const*)&gBlinkCmd_172,
    [173] =  (const struct MotionCmd* const*)&gBlinkCmd_173,
    [174] =  (const struct MotionCmd* const*)&gBlinkCmd_174,
    [175] =  (const struct MotionCmd* const*)&gBlinkCmd_175,
    [176] =  (const struct MotionCmd* const*)&gBlinkCmd_176,
    [177] =  (const struct MotionCmd* const*)&gBlinkCmd_177,
    [178] =  (const struct MotionCmd* const*)&gBlinkCmd_178,
    [179] =  (const struct MotionCmd* const*)&gBlinkCmd_179,
    [180] =  (const struct MotionCmd* const*)&gBlinkCmd_180,
    [181] =  (const struct MotionCmd* const*)&gBlinkCmd_181,
    [182] =  (const struct MotionCmd* const*)&gBlinkCmd_182,
    [183] =  (const struct MotionCmd* const*)&gBlinkCmd_183,
    [184] =  (const struct MotionCmd* const*)&gBlinkCmd_184,
    [185] =  (const struct MotionCmd* const*)&gBlinkCmd_000,
    [186] =  (const struct MotionCmd* const*)&gBlinkCmd_000,
    [187] =  (const struct MotionCmd* const*)&gBlinkCmd_187,
    [188] =  (const struct MotionCmd* const*)&gBlinkCmd_188,
    [189] =  (const struct MotionCmd* const*)&gBlinkCmd_189,
    [190] =  (const struct MotionCmd* const*)&gBlinkCmd_190,
    [191] =  (const struct MotionCmd* const*)&gBlinkCmd_191,
    [192] =  (const struct MotionCmd* const*)&gBlinkCmd_192,
    [193] =  (const struct MotionCmd* const*)&gBlinkCmd_193,
    [194] =  (const struct MotionCmd* const*)&gBlinkCmd_194,
    [195] =  (const struct MotionCmd* const*)&gBlinkCmd_195,
    [196] =  (const struct MotionCmd* const*)&gBlinkCmd_196,
    [197] =  (const struct MotionCmd* const*)&gBlinkCmd_197,
    [198] =  (const struct MotionCmd* const*)&gBlinkCmd_198,
    [199] =  (const struct MotionCmd* const*)&gBlinkCmd_199,
    [200] =  (const struct MotionCmd* const*)&gBlinkCmd_200,
    [201] =  (const struct MotionCmd* const*)&gBlinkCmd_201,
    [202] =  (const struct MotionCmd* const*)&gBlinkCmd_202,
    [203] =  (const struct MotionCmd* const*)&gBlinkCmd_203,
    [204] =  (const struct MotionCmd* const*)&gBlinkCmd_204,
    [205] =  (const struct MotionCmd* const*)&gBlinkCmd_205,
    [206] =  (const struct MotionCmd* const*)&gBlinkCmd_206,
    [207] =  (const struct MotionCmd* const*)&gBlinkCmd_207,
    [208] =  (const struct MotionCmd* const*)&gBlinkCmd_208,
    [209] =  (const struct MotionCmd* const*)&gBlinkCmd_209,
    [210] =  (const struct MotionCmd* const*)&gBlinkCmd_210,
    [211] =  (const struct MotionCmd* const*)&gBlinkCmd_211,
    [212] =  (const struct MotionCmd* const*)&gBlinkCmd_212,
    [213] =  (const struct MotionCmd* const*)&gBlinkCmd_213,
    [214] =  (const struct MotionCmd* const*)&gBlinkCmd_214,
    [215] =  (const struct MotionCmd* const*)&gBlinkCmd_215,
    [216] =  (const struct MotionCmd* const*)&gBlinkCmd_216,
    [217] =  (const struct MotionCmd* const*)&gBlinkCmd_217,
    [218] =  (const struct MotionCmd* const*)&gBlinkCmd_218,
    [219] =  (const struct MotionCmd* const*)&gBlinkCmd_219,
    [220] =  (const struct MotionCmd* const*)&gBlinkCmd_220,
    [221] =  (const struct MotionCmd* const*)&gBlinkCmd_221,
    [222] =  (const struct MotionCmd* const*)&gBlinkCmd_222,
    [223] =  (const struct MotionCmd* const*)&gBlinkCmd_223,
    [224] =  (const struct MotionCmd* const*)&gBlinkCmd_224,
    [225] =  (const struct MotionCmd* const*)&gBlinkCmd_225,
    [226] =  (const struct MotionCmd* const*)&gBlinkCmd_226,
    [227] =  (const struct MotionCmd* const*)&gBlinkCmd_227,
    [228] =  (const struct MotionCmd* const*)&gBlinkCmd_228,
    [229] =  (const struct MotionCmd* const*)&gBlinkCmd_229,
    [230] =  (const struct MotionCmd* const*)&gBlinkCmd_230,
    [231] =  (const struct MotionCmd* const*)&gBlinkCmd_231,
    [232] =  (const struct MotionCmd* const*)&gBlinkCmd_232,
    [233] =  (const struct MotionCmd* const*)&gBlinkCmd_233,
    [234] =  (const struct MotionCmd* const*)&gBlinkCmd_234,
    [235] =  (const struct MotionCmd* const*)&gBlinkCmd_235,
    [236] =  (const struct MotionCmd* const*)&gBlinkCmd_236,
    [237] =  (const struct MotionCmd* const*)&gBlinkCmd_237,
    [238] =  (const struct MotionCmd* const*)&gBlinkCmd_238,
    [239] =  (const struct MotionCmd* const*)&gBlinkCmd_239,
    [240] =  (const struct MotionCmd* const*)&gBlinkCmd_240,
    [241] =  (const struct MotionCmd* const*)&gBlinkCmd_241,
    [242] =  (const struct MotionCmd* const*)&gBlinkCmd_242,
    [243] =  (const struct MotionCmd* const*)&gBlinkCmd_243,
    [244] =  (const struct MotionCmd* const*)&gBlinkCmd_244,
    [245] =  (const struct MotionCmd* const*)&gBlinkCmd_245,
    [246] =  (const struct MotionCmd* const*)&gBlinkCmd_246,
    [247] =  (const struct MotionCmd* const*)&gBlinkCmd_247,
    [248] =  (const struct MotionCmd* const*)&gBlinkCmd_248,
    [249] =  (const struct MotionCmd* const*)&gBlinkCmd_249,
    [250] =  (const struct MotionCmd* const*)&gBlinkCmd_250,
    [251] =  (const struct MotionCmd* const*)&gBlinkCmd_251,
    [252] =  (const struct MotionCmd* const*)&gBlinkCmd_252,
    [253] =  (const struct MotionCmd* const*)&gBlinkCmd_253,
    [254] =  (const struct MotionCmd* const*)&gBlinkCmd_254,
    [255] =  (const struct MotionCmd* const*)&gBlinkCmd_255,
    [256] =  (const struct MotionCmd* const*)&gBlinkCmd_256,
    [257] =  (const struct MotionCmd* const*)&gBlinkCmd_257,
    [258] =  (const struct MotionCmd* const*)&gBlinkCmd_258,
    [259] =  (const struct MotionCmd* const*)&gBlinkCmd_259,
    [260] =  (const struct MotionCmd* const*)&gBlinkCmd_260,
    [261] =  (const struct MotionCmd* const*)&gBlinkCmd_261,
    [262] =  (const struct MotionCmd* const*)&gBlinkCmd_262,
    [263] =  (const struct MotionCmd* const*)&gBlinkCmd_263,
    [264] =  (const struct MotionCmd* const*)&gBlinkCmd_264,
    [265] =  (const struct MotionCmd* const*)&gBlinkCmd_265,
    [266] =  (const struct MotionCmd* const*)&gBlinkCmd_266,
    [267] =  (const struct MotionCmd* const*)&gBlinkCmd_267,
    [268] =  (const struct MotionCmd* const*)&gBlinkCmd_268,
    [269] =  (const struct MotionCmd* const*)&gBlinkCmd_269,
    [270] =  (const struct MotionCmd* const*)&gBlinkCmd_270,
    [271] =  (const struct MotionCmd* const*)&gBlinkCmd_271,
    [272] =  (const struct MotionCmd* const*)&gBlinkCmd_272,
    [273] =  (const struct MotionCmd* const*)&gBlinkCmd_273,
    [274] =  (const struct MotionCmd* const*)&gBlinkCmd_274,
    [275] =  (const struct MotionCmd* const*)&gBlinkCmd_275,
    [276] =  (const struct MotionCmd* const*)&gBlinkCmd_276,
    [277] =  (const struct MotionCmd* const*)&gBlinkCmd_277,
    [278] =  (const struct MotionCmd* const*)&gBlinkCmd_278,
    [279] =  (const struct MotionCmd* const*)&gBlinkCmd_279,
};
// clang-format on

// 0x085d4cf4: PaletteAnimation コマンドデータ (旧 asm/blink.inc)
// clang-format off
const struct BlinkCmds8 gBlinkCmd_000 = {gBlinkCmd_000.cmds, {{0, 10}, {1, 5}, {2, 5}, {3, 3}, {4, 3}, {5, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_001 = {gBlinkCmd_001.cmds, {{0, 10}, {1, 5}, {2, 5}, {3, 3}, {4, 3}, {5, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_002 = {gBlinkCmd_002.cmds, {{0, 10}, {1, 5}, {2, 5}, {3, 3}, {4, 3}, {5, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_003 = {gBlinkCmd_003.cmds, {{0, 10}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_Menu = {gBlinkCmd_Menu.cmds, {{0, 30}, {1, 10}, {2, 10}, {3, 10}, {4, 30}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_005 = {gBlinkCmd_005.cmds, {{0, 75}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}, {7, 9}, {8, 80}, {7, 9}, {6, 9}, {5, 9}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_006 = {gBlinkCmd_006.cmds, {{0, 54}, {1, 6}, {2, 9}, {3, 15}, {4, 30}, {3, 15}, {2, 9}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_007 = {gBlinkCmd_007.cmds, {{0, 80}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}, {7, 9}, {8, 80}, {7, 9}, {6, 9}, {5, 9}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_008 = {gBlinkCmd_008.cmds, {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}, {7, 9}, {8, 80}, {9, 9}, {10, 9}, {11, 9}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_009 = {gBlinkCmd_009.cmds, {{0, 45}, {1, 12}, {2, 12}, {3, 12}, {4, 12}, {5, 12}, {6, 12}, {7, 12}, {8, 75}, {7, 12}, {6, 12}, {5, 12}, {4, 12}, {3, 12}, {2, 12}, {1, 12}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_010 = {gBlinkCmd_010.cmds, {{0, 60}, {1, 12}, {2, 12}, {3, 12}, {4, 12}, {5, 75}, {4, 12}, {3, 12}, {2, 12}, {1, 12}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_011 = {gBlinkCmd_011.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_012 = {gBlinkCmd_012.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_013 = {gBlinkCmd_013.cmds, {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, {0, 255}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_014 = {gBlinkCmd_014.cmds, {{0, 10}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {0, 255}}};
const struct BlinkCmds12 gBlinkCmd_015 = {gBlinkCmd_015.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_016 = {gBlinkCmd_016.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_017 = {gBlinkCmd_017.cmds, {{4, 10}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_018 = {gBlinkCmd_018.cmds, {{4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 10}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_019 = {gBlinkCmd_019.cmds, {{0, 10}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {0, 255}}};
const struct BlinkCmds12 gBlinkCmd_020 = {gBlinkCmd_020.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_021 = {gBlinkCmd_021.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_022 = {gBlinkCmd_022.cmds, {{4, 10}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_023 = {gBlinkCmd_023.cmds, {{4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 10}, {0, 255}}};
const struct BlinkCmds14 gBlinkCmd_024 = {gBlinkCmd_024.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {0, 255}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_025 = {gBlinkCmd_025.cmds, {{0, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_026 = {gBlinkCmd_026.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 4}, {5, 4}, {6, 4}, {7, 254}}};
const struct BlinkCmds6 gBlinkCmd_027 = {gBlinkCmd_027.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {0, 255}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_028 = {gBlinkCmd_028.cmds, {{3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_029 = {gBlinkCmd_029.cmds, {{0, 10}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {0, 255}, {0, 0}}};
const struct BlinkCmds22 gBlinkCmd_030 = {gBlinkCmd_030.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {16, 3}, {17, 3}, {18, 3}, {19, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_031 = {gBlinkCmd_031.cmds, {{4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, {0, 255}}};
const struct BlinkCmds66 gBlinkCmd_032 = {gBlinkCmd_032.cmds, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, {18, 1}, {19, 1}, {20, 30}, {21, 6}, {22, 6}, {23, 3}, {24, 3}, {23, 3}, {22, 3}, {21, 6}, {20, 8}, {21, 6}, {22, 3}, {23, 3}, {24, 3}, {23, 3}, {22, 3}, {21, 6}, {20, 8}, {21, 6}, {22, 3}, {23, 3}, {24, 3}, {23, 3}, {22, 3}, {21, 6}, {20, 20}, {25, 2}, {26, 2}, {27, 2}, {28, 7}, {29, 2}, {30, 2}, {31, 2}, {32, 7}, {33, 2}, {34, 2}, {35, 2}, {36, 7}, {37, 2}, {38, 2}, {39, 2}, {40, 7}, {41, 2}, {42, 2}, {43, 2}, {0, 50}, {0, 254}}};
const struct BlinkCmds100 gBlinkCmd_033 = {gBlinkCmd_033.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 2}, {13, 2}, {14, 2}, {15, 2}, {17, 2}, {18, 2}, {19, 32}, {20, 2}, {21, 2}, {22, 2}, {23, 2}, {24, 2}, {25, 2}, {26, 2}, {27, 6}, {26, 2}, {25, 2}, {24, 2}, {23, 2}, {22, 1}, {21, 1}, {20, 1}, {19, 8}, {20, 2}, {21, 2}, {22, 2}, {23, 2}, {24, 2}, {25, 2}, {26, 2}, {27, 6}, {26, 2}, {25, 2}, {24, 2}, {23, 2}, {22, 1}, {21, 1}, {20, 1}, {19, 32}, {20, 5}, {21, 5}, {22, 5}, {23, 5}, {24, 5}, {25, 5}, {26, 5}, {27, 32}, {28, 3}, {29, 3}, {30, 2}, {31, 20}, {32, 3}, {33, 3}, {34, 3}, {35, 20}, {36, 3}, {37, 3}, {38, 3}, {39, 20}, {40, 3}, {41, 3}, {42, 3}, {43, 50}, {42, 3}, {41, 3}, {40, 3}, {39, 3}, {38, 3}, {37, 3}, {36, 3}, {35, 3}, {34, 3}, {33, 3}, {32, 3}, {31, 20}, {30, 3}, {29, 3}, {28, 20}, {27, 3}, {26, 3}, {25, 3}, {24, 3}, {23, 3}, {22, 3}, {21, 3}, {20, 3}, {19, 32}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_034 = {gBlinkCmd_034.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 20}, {3, 12}, {2, 12}, {1, 12}, {0, 12}, {0, 254}}};
const struct BlinkCmds8 gBlinkCmd_035 = {gBlinkCmd_035.cmds, {{0, 10}, {1, 8}, {2, 6}, {3, 3}, {4, 3}, {5, 2}, {6, 15}, {0, 254}}};
const struct BlinkCmds18 gBlinkCmd_036 = {gBlinkCmd_036.cmds, {{0, 3}, {1, 3}, {2, 6}, {1, 3}, {0, 3}, {1, 3}, {2, 6}, {1, 3}, {0, 20}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 30}, {2, 10}, {1, 10}, {0, 30}, {0, 254}}};
const struct BlinkCmds12 gBlinkCmd_037 = {gBlinkCmd_037.cmds, {{0, 7}, {1, 5}, {2, 3}, {3, 2}, {4, 1}, {5, 25}, {6, 1}, {7, 2}, {8, 3}, {9, 5}, {10, 7}, {0, 254}}};
const struct BlinkCmds4 gBlinkCmd_038 = {gBlinkCmd_038.cmds, {{0, 1}, {1, 2}, {0, 1}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_039 = {gBlinkCmd_039.cmds, {{0, 15}, {1, 12}, {2, 8}, {3, 5}, {4, 3}, {3, 5}, {2, 8}, {1, 12}, {0, 15}, {0, 254}}};
const struct BlinkCmds28 gBlinkCmd_040 = {gBlinkCmd_040.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 50}, {8, 8}, {9, 8}, {10, 8}, {11, 8}, {12, 8}, {13, 8}, {14, 8}, {15, 8}, {16, 4}, {17, 4}, {18, 4}, {19, 4}, {20, 4}, {21, 50}, {22, 10}, {23, 8}, {24, 6}, {25, 4}, {0, 32}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_041 = {gBlinkCmd_041.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {0, 255}}};
const struct BlinkCmds8 gBlinkCmd_042 = {gBlinkCmd_042.cmds, {{0, 4}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {0, 255}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_043 = {gBlinkCmd_043.cmds, {{0, 60}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_044 = {gBlinkCmd_044.cmds, {{0, 9}, {1, 9}, {2, 9}, {3, 45}, {4, 9}, {5, 9}, {6, 9}, {7, 9}, {8, 9}, {9, 60}, {10, 9}, {11, 9}, {0, 254}, {0, 0}}};
const struct BlinkCmds22 gBlinkCmd_045 = {gBlinkCmd_045.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 60}, {6, 6}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6}, {15, 45}, {16, 6}, {17, 6}, {18, 6}, {19, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_046 = {gBlinkCmd_046.cmds, {{0, 60}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 27}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_047 = {gBlinkCmd_047.cmds, {{0, 45}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 21}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_048 = {gBlinkCmd_048.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 60}, {5, 6}, {6, 6}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {11, 6}, {12, 45}, {13, 6}, {14, 6}, {15, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_049 = {gBlinkCmd_049.cmds, {{0, 20}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 10}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_050 = {gBlinkCmd_050.cmds, {{0, 20}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 10}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_051 = {gBlinkCmd_051.cmds, {{0, 20}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 10}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_052 = {gBlinkCmd_052.cmds, {{0, 30}, {1, 6}, {0, 10}, {1, 4}, {0, 20}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_053 = {gBlinkCmd_053.cmds, {{0, 20}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 10}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_054 = {gBlinkCmd_054.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_055 = {gBlinkCmd_055.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_056 = {gBlinkCmd_056.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_057 = {gBlinkCmd_057.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_058 = {gBlinkCmd_058.cmds, {{0, 15}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 15}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_059 = {gBlinkCmd_059.cmds, {{0, 60}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 60}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_060 = {gBlinkCmd_060.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_061 = {gBlinkCmd_061.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_062 = {gBlinkCmd_062.cmds, {{0, 30}, {1, 10}, {2, 10}, {3, 10}, {4, 30}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_063 = {gBlinkCmd_063.cmds, {{0, 20}, {1, 4}, {2, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_064 = {gBlinkCmd_064.cmds, {{0, 20}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_065 = {gBlinkCmd_065.cmds, {{0, 20}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_066 = {gBlinkCmd_066.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_067 = {gBlinkCmd_067.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_068 = {gBlinkCmd_068.cmds, {{0, 30}, {1, 10}, {2, 10}, {3, 10}, {4, 30}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_069 = {gBlinkCmd_069.cmds, {{4, 8}, {3, 4}, {2, 4}, {1, 4}, {0, 8}, {1, 4}, {2, 4}, {3, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_070 = {gBlinkCmd_070.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_071 = {gBlinkCmd_071.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_072 = {gBlinkCmd_072.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {0, 255}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_073 = {gBlinkCmd_073.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {0, 255}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_074 = {gBlinkCmd_074.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {0, 254}}};
const struct BlinkCmds6 gBlinkCmd_075 = {gBlinkCmd_075.cmds, {{3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 255}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_076 = {gBlinkCmd_076.cmds, {{12, 2}, {11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}, {0, 254}}};
const struct BlinkCmds18 gBlinkCmd_077 = {gBlinkCmd_077.cmds, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 1}, {15, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_078 = {gBlinkCmd_078.cmds, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 1}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_079 = {gBlinkCmd_079.cmds, {{0, 10}, {1, 4}, {2, 4}, {3, 4}, {4, 10}, {0, 254}}};
const struct BlinkCmds14 gBlinkCmd_080 = {gBlinkCmd_080.cmds, {{0, 5}, {1, 5}, {2, 5}, {3, 6}, {2, 5}, {1, 5}, {0, 5}, {4, 5}, {5, 5}, {6, 10}, {5, 5}, {4, 5}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_081 = {gBlinkCmd_081.cmds, {{0, 30}, {1, 10}, {2, 10}, {3, 10}, {4, 30}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_082 = {gBlinkCmd_082.cmds, {{0, 30}, {1, 8}, {2, 8}, {3, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_083 = {gBlinkCmd_083.cmds, {{0, 20}, {1, 8}, {2, 8}, {3, 20}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_084 = {gBlinkCmd_084.cmds, {{0, 8}, {1, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds28 gBlinkCmd_085 = {gBlinkCmd_085.cmds, {{0, 2}, {1, 2}, {8, 4}, {2, 2}, {3, 2}, {8, 2}, {2, 2}, {3, 2}, {8, 4}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {6, 2}, {7, 2}, {4, 2}, {5, 2}, {8, 4}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds28 gBlinkCmd_086 = {gBlinkCmd_086.cmds, {{0, 3}, {1, 3}, {8, 3}, {2, 3}, {3, 3}, {8, 4}, {2, 3}, {3, 3}, {8, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {6, 3}, {7, 3}, {4, 3}, {5, 3}, {8, 8}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_087 = {gBlinkCmd_087.cmds, {{0, 3}, {1, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_088 = {gBlinkCmd_088.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {2, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_089 = {gBlinkCmd_089.cmds, {{2, 3}, {1, 3}, {0, 3}, {0, 255}}};
const struct BlinkCmds4 gBlinkCmd_090 = {gBlinkCmd_090.cmds, {{2, 3}, {1, 3}, {0, 3}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_091 = {gBlinkCmd_091.cmds, {{0, 16}, {1, 8}, {2, 8}, {3, 8}, {4, 16}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_092 = {gBlinkCmd_092.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_093 = {gBlinkCmd_093.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_094 = {gBlinkCmd_094.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_095 = {gBlinkCmd_095.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds20 gBlinkCmd_096 = {gBlinkCmd_096.cmds, {{1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {16, 3}, {17, 3}, {18, 3}, {0, 1}, {0, 255}}};
const struct BlinkCmds18 gBlinkCmd_097 = {gBlinkCmd_097.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {0, 255}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_098 = {gBlinkCmd_098.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {0, 255}, {0, 0}}};
const struct BlinkCmds26 gBlinkCmd_099 = {gBlinkCmd_099.cmds, {{1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {8, 3}, {6, 3}, {7, 3}, {8, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_100 = {gBlinkCmd_100.cmds, {{1, 3}, {2, 3}, {3, 3}, {4, 3}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_102 = {gBlinkCmd_102.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_103 = {gBlinkCmd_103.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_104 = {gBlinkCmd_104.cmds, {{0, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_105 = {gBlinkCmd_105.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_106 = {gBlinkCmd_106.cmds, {{0, 30}, {1, 8}, {2, 8}, {3, 8}, {4, 30}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_107 = {gBlinkCmd_107.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_108 = {gBlinkCmd_108.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_109 = {gBlinkCmd_109.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_110 = {gBlinkCmd_110.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_111 = {gBlinkCmd_111.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds20 gBlinkCmd_112 = {gBlinkCmd_112.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}, {16, 4}, {17, 24}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_113 = {gBlinkCmd_113.cmds, {{0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_114 = {gBlinkCmd_114.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {5, 254}}};
const struct BlinkCmds8 gBlinkCmd_115 = {gBlinkCmd_115.cmds, {{0, 30}, {1, 4}, {2, 3}, {3, 2}, {4, 2}, {5, 2}, {0, 255}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_116 = {gBlinkCmd_116.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_117 = {gBlinkCmd_117.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_118 = {gBlinkCmd_118.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_119 = {gBlinkCmd_119.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_120 = {gBlinkCmd_120.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_121 = {gBlinkCmd_121.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds12 gBlinkCmd_122 = {gBlinkCmd_122.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_123 = {gBlinkCmd_123.cmds, {{0, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 4}, {11, 4}, {12, 4}, {13, 6}, {14, 8}, {15, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds20 gBlinkCmd_124 = {gBlinkCmd_124.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}, {16, 4}, {17, 80}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_125 = {gBlinkCmd_125.cmds, {{0, 24}, {1, 4}, {2, 20}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 80}, {0, 254}}};
const struct BlinkCmds12 gBlinkCmd_126 = {gBlinkCmd_126.cmds, {{0, 20}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 20}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_127 = {gBlinkCmd_127.cmds, {{0, 60}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 60}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {13, 2}, {14, 2}, {15, 2}, {16, 2}, {0, 254}}};
const struct BlinkCmds16 gBlinkCmd_128 = {gBlinkCmd_128.cmds, {{7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {0, 57}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 57}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_129 = {gBlinkCmd_129.cmds, {{0, 30}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 30}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_130 = {gBlinkCmd_130.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {0, 254}}};
const struct BlinkCmds4 gBlinkCmd_131 = {gBlinkCmd_131.cmds, {{0, 4}, {1, 4}, {2, 4}, {0, 254}}};
const struct BlinkCmds4 gBlinkCmd_132 = {gBlinkCmd_132.cmds, {{0, 4}, {1, 4}, {2, 4}, {0, 254}}};
const struct BlinkCmds16 gBlinkCmd_133 = {gBlinkCmd_133.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {6, 8}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_134 = {gBlinkCmd_134.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {6, 8}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_135 = {gBlinkCmd_135.cmds, {{1, 2}, {0, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_136 = {gBlinkCmd_136.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {6, 8}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_137 = {gBlinkCmd_137.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_138 = {gBlinkCmd_138.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_139 = {gBlinkCmd_139.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_140 = {gBlinkCmd_140.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_141 = {gBlinkCmd_141.cmds, {{1, 2}, {0, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds20 gBlinkCmd_142 = {gBlinkCmd_142.cmds, {{0, 2}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 8}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {13, 4}, {14, 4}, {15, 4}, {16, 4}, {17, 4}, {18, 4}, {0, 32}, {0, 254}}};
const struct BlinkCmds72 gBlinkCmd_143 = {gBlinkCmd_143.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}, {16, 4}, {17, 4}, {18, 4}, {19, 4}, {20, 4}, {21, 4}, {22, 4}, {23, 4}, {24, 4}, {25, 4}, {26, 4}, {27, 4}, {28, 4}, {29, 4}, {30, 4}, {31, 4}, {32, 4}, {33, 4}, {34, 4}, {35, 4}, {36, 4}, {35, 4}, {34, 4}, {33, 4}, {32, 4}, {31, 4}, {30, 2}, {29, 2}, {28, 2}, {27, 2}, {26, 2}, {24, 2}, {23, 2}, {22, 2}, {21, 2}, {20, 2}, {19, 2}, {18, 2}, {17, 2}, {16, 2}, {15, 2}, {14, 2}, {13, 2}, {12, 2}, {11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 32}, {0, 254}}};
const struct BlinkCmds26 gBlinkCmd_144 = {gBlinkCmd_144.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {16, 3}, {17, 3}, {18, 3}, {19, 3}, {20, 3}, {21, 3}, {22, 3}, {23, 32}, {0, 254}, {0, 0}}};
const struct BlinkCmds20 gBlinkCmd_145 = {gBlinkCmd_145.cmds, {{0, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 8}, {8, 4}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 2}, {2, 2}, {1, 2}, {0, 10}, {0, 254}}};
const struct BlinkCmds20 gBlinkCmd_146 = {gBlinkCmd_146.cmds, {{0, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 8}, {8, 4}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 2}, {2, 2}, {1, 2}, {0, 10}, {0, 254}}};
const struct BlinkCmds22 gBlinkCmd_147 = {gBlinkCmd_147.cmds, {{0, 5}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 30}, {6, 7}, {7, 7}, {8, 7}, {9, 7}, {10, 15}, {9, 7}, {8, 7}, {7, 7}, {6, 7}, {5, 30}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 10}, {0, 254}}};
const struct BlinkCmds4 gBlinkCmd_148 = {gBlinkCmd_148.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_149 = {gBlinkCmd_149.cmds, {{0, 127}, {1, 2}, {0, 80}, {1, 2}, {0, 2}, {1, 2}, {0, 2}, {1, 80}, {0, 2}, {1, 2}, {0, 2}, {1, 2}, {0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_150 = {gBlinkCmd_150.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {0, 254}}};
const struct BlinkCmds4 gBlinkCmd_151 = {gBlinkCmd_151.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_152 = {gBlinkCmd_152.cmds, {{3, 8}, {2, 8}, {1, 8}, {0, 8}, {1, 8}, {2, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_153 = {gBlinkCmd_153.cmds, {{0, 16}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_154 = {gBlinkCmd_154.cmds, {{0, 30}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 30}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_155 = {gBlinkCmd_155.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_156 = {gBlinkCmd_156.cmds, {{0, 20}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 20}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_157 = {gBlinkCmd_157.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_158 = {gBlinkCmd_158.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_159 = {gBlinkCmd_159.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_160 = {gBlinkCmd_160.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_161 = {gBlinkCmd_161.cmds, {{0, 20}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_162 = {gBlinkCmd_162.cmds, {{0, 60}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 8}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_163 = {gBlinkCmd_163.cmds, {{0, 30}, {1, 4}, {2, 4}, {3, 4}, {4, 12}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_164 = {gBlinkCmd_164.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_165 = {gBlinkCmd_165.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_166 = {gBlinkCmd_166.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_167 = {gBlinkCmd_167.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_168 = {gBlinkCmd_168.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_169 = {gBlinkCmd_169.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_170 = {gBlinkCmd_170.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_171 = {gBlinkCmd_171.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_172 = {gBlinkCmd_172.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_173 = {gBlinkCmd_173.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_174 = {gBlinkCmd_174.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_175 = {gBlinkCmd_175.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_176 = {gBlinkCmd_176.cmds, {{0, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_177 = {gBlinkCmd_177.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds2 gBlinkCmd_178 = {gBlinkCmd_178.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds8 gBlinkCmd_179 = {gBlinkCmd_179.cmds, {{5, 1}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_180 = {gBlinkCmd_180.cmds, {{5, 1}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_181 = {gBlinkCmd_181.cmds, {{5, 1}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_182 = {gBlinkCmd_182.cmds, {{5, 1}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_183 = {gBlinkCmd_183.cmds, {{5, 1}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_184 = {gBlinkCmd_184.cmds, {{5, 1}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_187 = {gBlinkCmd_187.cmds, {{3, 1}, {0, 254}}};
const struct BlinkCmds6 gBlinkCmd_188 = {gBlinkCmd_188.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 12}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_189 = {gBlinkCmd_189.cmds, {{0, 12}, {1, 8}, {2, 6}, {3, 4}, {4, 4}, {5, 8}, {2, 4}, {0, 254}}};
const struct BlinkCmds14 gBlinkCmd_190 = {gBlinkCmd_190.cmds, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6}, {8, 30}, {9, 6}, {10, 6}, {11, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_191 = {gBlinkCmd_191.cmds, {{1, 15}, {0, 15}, {1, 4}, {0, 4}, {1, 4}, {0, 4}, {0, 255}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_192 = {gBlinkCmd_192.cmds, {{0, 36}, {1, 6}, {0, 6}, {1, 6}, {0, 6}, {0, 255}}};
const struct BlinkCmds14 gBlinkCmd_193 = {gBlinkCmd_193.cmds, {{0, 12}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 15}, {5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 255}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_194 = {gBlinkCmd_194.cmds, {{0, 12}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 15}, {5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_195 = {gBlinkCmd_195.cmds, {{0, 30}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 45}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {11, 6}, {10, 6}, {9, 6}, {8, 6}, {7, 6}, {6, 30}, {7, 254}}};
const struct BlinkCmds14 gBlinkCmd_196 = {gBlinkCmd_196.cmds, {{0, 27}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_197 = {gBlinkCmd_197.cmds, {{0, 10}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 15}, {6, 6}, {5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_198 = {gBlinkCmd_198.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds2 gBlinkCmd_199 = {gBlinkCmd_199.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_200 = {gBlinkCmd_200.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_201 = {gBlinkCmd_201.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds12 gBlinkCmd_202 = {gBlinkCmd_202.cmds, {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_203 = {gBlinkCmd_203.cmds, {{0, 8}, {1, 6}, {2, 6}, {3, 8}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_204 = {gBlinkCmd_204.cmds, {{0, 1}, {0, 254}}};
const struct BlinkCmds12 gBlinkCmd_205 = {gBlinkCmd_205.cmds, {{0, 2}, {1, 3}, {2, 2}, {3, 30}, {4, 1}, {5, 3}, {6, 1}, {8, 3}, {7, 1}, {9, 127}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_206 = {gBlinkCmd_206.cmds, {{0, 2}, {1, 3}, {2, 2}, {3, 30}, {4, 1}, {5, 3}, {6, 1}, {8, 3}, {7, 1}, {9, 127}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_207 = {gBlinkCmd_207.cmds, {{0, 3}, {1, 3}, {2, 3}, {0, 254}}};
const struct BlinkCmds4 gBlinkCmd_208 = {gBlinkCmd_208.cmds, {{0, 6}, {1, 3}, {2, 3}, {1, 254}}};
const struct BlinkCmds10 gBlinkCmd_209 = {gBlinkCmd_209.cmds, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_210 = {gBlinkCmd_210.cmds, {{0, 20}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 12}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_211 = {gBlinkCmd_211.cmds, {{0, 30}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 30}, {0, 30}, {6, 30}, {0, 30}, {6, 30}, {7, 5}, {8, 5}, {9, 5}, {10, 5}, {0, 254}}};
const struct BlinkCmds8 gBlinkCmd_212 = {gBlinkCmd_212.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_213 = {gBlinkCmd_213.cmds, {{0, 3}, {0, 254}}};
const struct BlinkCmds6 gBlinkCmd_214 = {gBlinkCmd_214.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds10 gBlinkCmd_215 = {gBlinkCmd_215.cmds, {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 32}, {0, 254}}};
const struct BlinkCmds8 gBlinkCmd_216 = {gBlinkCmd_216.cmds, {{0, 20}, {1, 20}, {2, 20}, {3, 20}, {2, 20}, {1, 20}, {0, 20}, {0, 254}}};
const struct BlinkCmds14 gBlinkCmd_217 = {gBlinkCmd_217.cmds, {{0, 15}, {1, 15}, {2, 15}, {3, 15}, {4, 15}, {5, 15}, {6, 50}, {7, 15}, {8, 15}, {9, 15}, {10, 15}, {11, 15}, {12, 15}, {0, 254}}};
const struct BlinkCmds10 gBlinkCmd_218 = {gBlinkCmd_218.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_219 = {gBlinkCmd_219.cmds, {{0, 32}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 16}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_220 = {gBlinkCmd_220.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_221 = {gBlinkCmd_221.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_222 = {gBlinkCmd_222.cmds, {{0, 1}, {1, 8}, {2, 4}, {3, 4}, {4, 4}, {0, 254}}};
const struct BlinkCmds6 gBlinkCmd_223 = {gBlinkCmd_223.cmds, {{0, 8}, {1, 4}, {2, 4}, {3, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_224 = {gBlinkCmd_224.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {0, 254}}};
const struct BlinkCmds12 gBlinkCmd_225 = {gBlinkCmd_225.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_226 = {gBlinkCmd_226.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_227 = {gBlinkCmd_227.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {11, 8}, {12, 8}, {13, 8}, {14, 8}, {15, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_228 = {gBlinkCmd_228.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {0, 254}}};
const struct BlinkCmds16 gBlinkCmd_229 = {gBlinkCmd_229.cmds, {{0, 32}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 32}, {6, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_230 = {gBlinkCmd_230.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {0, 254}}};
const struct BlinkCmds16 gBlinkCmd_231 = {gBlinkCmd_231.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_232 = {gBlinkCmd_232.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_233 = {gBlinkCmd_233.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 32}, {6, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_234 = {gBlinkCmd_234.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {11, 8}, {12, 8}, {13, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_235 = {gBlinkCmd_235.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {6, 8}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_236 = {gBlinkCmd_236.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {6, 8}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds16 gBlinkCmd_237 = {gBlinkCmd_237.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {6, 8}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 254}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_238 = {gBlinkCmd_238.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 16}, {4, 4}, {5, 4}, {6, 4}, {0, 254}}};
const struct BlinkCmds8 gBlinkCmd_239 = {gBlinkCmd_239.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 16}, {4, 4}, {5, 4}, {6, 4}, {0, 254}}};
const struct BlinkCmds24 gBlinkCmd_240 = {gBlinkCmd_240.cmds, {{0, 66}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}, {16, 4}, {17, 6}, {18, 6}, {19, 6}, {20, 6}, {21, 6}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_241 = {gBlinkCmd_241.cmds, {{0, 2}, {1, 2}, {0, 254}, {0, 0}}};
const struct BlinkCmds18 gBlinkCmd_242 = {gBlinkCmd_242.cmds, {{0, 2}, {1, 1}, {2, 2}, {3, 1}, {4, 2}, {5, 1}, {6, 2}, {7, 1}, {8, 2}, {9, 1}, {10, 2}, {11, 1}, {12, 2}, {13, 1}, {14, 2}, {15, 1}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_243 = {gBlinkCmd_243.cmds, {{0, 36}, {1, 4}, {0, 15}, {1, 4}, {0, 255}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_244 = {gBlinkCmd_244.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds2 gBlinkCmd_245 = {gBlinkCmd_245.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds2 gBlinkCmd_246 = {gBlinkCmd_246.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds2 gBlinkCmd_247 = {gBlinkCmd_247.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds4 gBlinkCmd_248 = {gBlinkCmd_248.cmds, {{0, 8}, {1, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_249 = {gBlinkCmd_249.cmds, {{1, 4}, {0, 4}, {0, 254}, {0, 0}}};
const struct BlinkCmds6 gBlinkCmd_250 = {gBlinkCmd_250.cmds, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_251 = {gBlinkCmd_251.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_252 = {gBlinkCmd_252.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_253 = {gBlinkCmd_253.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_254 = {gBlinkCmd_254.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_255 = {gBlinkCmd_255.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_256 = {gBlinkCmd_256.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_257 = {gBlinkCmd_257.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds8 gBlinkCmd_258 = {gBlinkCmd_258.cmds, {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 1}, {0, 255}, {0, 0}}};
const struct BlinkCmds50 gBlinkCmd_259 = {gBlinkCmd_259.cmds, {{0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds50 gBlinkCmd_260 = {gBlinkCmd_260.cmds, {{0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds50 gBlinkCmd_261 = {gBlinkCmd_261.cmds, {{0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds14 gBlinkCmd_262 = {gBlinkCmd_262.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 32}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds50 gBlinkCmd_263 = {gBlinkCmd_263.cmds, {{0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {1, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {2, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 3}, {3, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds34 gBlinkCmd_264 = {gBlinkCmd_264.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {16, 3}, {17, 3}, {18, 3}, {19, 3}, {20, 3}, {21, 3}, {22, 3}, {23, 3}, {24, 3}, {25, 3}, {26, 3}, {27, 3}, {28, 3}, {29, 3}, {30, 3}, {31, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds20 gBlinkCmd_265 = {gBlinkCmd_265.cmds, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 16}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {16, 3}, {17, 3}, {18, 64}, {0, 254}}};
const struct BlinkCmds18 gBlinkCmd_266 = {gBlinkCmd_266.cmds, {{0, 16}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 32}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_267 = {gBlinkCmd_267.cmds, {{0, 3}, {1, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_268 = {gBlinkCmd_268.cmds, {{0, 3}, {1, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds12 gBlinkCmd_269 = {gBlinkCmd_269.cmds, {{0, 1}, {1, 3}, {2, 16}, {3, 3}, {7, 3}, {4, 3}, {8, 3}, {5, 3}, {9, 3}, {6, 3}, {10, 3}, {0, 254}}};
const struct BlinkCmds4 gBlinkCmd_270 = {gBlinkCmd_270.cmds, {{0, 3}, {1, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_271 = {gBlinkCmd_271.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds6 gBlinkCmd_272 = {gBlinkCmd_272.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {0, 255}, {0, 0}}};
const struct BlinkCmds4 gBlinkCmd_273 = {gBlinkCmd_273.cmds, {{0, 3}, {1, 3}, {0, 254}, {0, 0}}};
const struct BlinkCmds2 gBlinkCmd_274 = {gBlinkCmd_274.cmds, {{0, 127}, {0, 254}}};
const struct BlinkCmds2 gBlinkCmd_275 = {gBlinkCmd_275.cmds, {{0, 127}, {0, 254}}};
const struct BlinkCmds12 gBlinkCmd_276 = {gBlinkCmd_276.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {3, 254}}};
const struct BlinkCmds2 gBlinkCmd_277 = {gBlinkCmd_277.cmds, {{0, 1}, {0, 255}}};
const struct BlinkCmds12 gBlinkCmd_278 = {gBlinkCmd_278.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {3, 254}}};
const struct BlinkCmds6 gBlinkCmd_279 = {gBlinkCmd_279.cmds, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {0, 255}, {0, 0}}};
// clang-format on
