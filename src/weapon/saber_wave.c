#include "collision.h"
#include "global.h"
#include "mission.h"
#include "weapon.h"

// Saber wave by cyberelf, Cottus

static const struct Collision sCollisions[16] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x1000, 0x0000, 0x2000, 0x0800},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x1000, 0x0000, 0x2000, 0x0800},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x0F00, 0x0000, 0x1E00, 0x0800},
    },
    [3] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0F00, 0x0000, 0x1E00, 0x0800},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x0E00, 0x0000, 0x1C00, 0x0C00},
    },
    [5] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0E00, 0x0000, 0x1C00, 0x0C00},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x0D00, 0x0000, 0x1A00, 0x1000},
    },
    [7] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0D00, 0x0000, 0x1A00, 0x1000},
    },
    [8] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x0C00, 0x0000, 0x1800, 0x1400},
    },
    [9] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0C00, 0x0000, 0x1800, 0x1400},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x0B00, 0x0000, 0x1600, 0x1800},
    },
    [11] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0B00, 0x0000, 0x1600, 0x1800},
    },
    [12] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x0A00, 0x0000, 0x1400, 0x1C00},
    },
    [13] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0A00, 0x0000, 0x1400, 0x1C00},
    },
    [14] = {
      kind : DDP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 8,
      atkType : ATK_SABER,
      nature : BODY_NATURE_CUT,
      comboLv : 3,
      remaining : 1,
      layer : 0x00000020,
      range : {0x0700, 0x0000, 0x1000, 0x2000},
    },
    [15] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 0xFF,
      remaining : 0,
      range : {0x0700, 0x0000, 0x1000, 0x2000},
    },
};

void Weapon5_Init(struct Weapon* w);
void Weapon5_Update(struct Weapon* w);
void Weapon5_Die(struct Weapon* w);

// clang-format off
const WeaponRoutine gSaberWaveRoutine = {
    [ENTITY_INIT] =      Weapon5_Init,
    [ENTITY_UPDATE] =    Weapon5_Update,
    [ENTITY_DIE] =       Weapon5_Die,
    [ENTITY_DISAPPEAR] = DeleteWeapon,
    [ENTITY_EXIT] =      (WeaponFunc)DeleteEntity,    
};
// clang-format on

struct Weapon* CreateSaberWave(struct Zero* z, struct Weapon* saber, bool8 isProjectile) {
  struct Weapon* w = (struct Weapon*)AllocEntityFirst(gWeaponHeaderPtr);
  if (w != NULL) {
    struct SaberWave_b4* b4;

    if ((z->unk_b4).mainCopy == WEAPON_SABER) {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SABER_WAVE);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[0];
      (w->s).palID = gWeaponPalIDs[0];
    } else {
      INIT_WEAPON_ROUTINE(w, WEAPON_MOVE_SABER_WAVE);
      (w->s).flags2 &= ~ENTITY_FLAGS2_B6;
      (w->s).taskCol = 16;
      (w->s).tileNum = gWeaponTileNum[1];
      (w->s).palID = gWeaponPalIDs[1];
    }
    b4 = &w->props.wave;
    b4->saber = saber;
    b4->z = z;
    (w->s).work[0] = isProjectile;
    (w->s).work[1] = 0;
    if (!isProjectile) {
      CreateSaberWave(z, (struct Weapon*)w, TRUE);
    }
  }
  return (struct Weapon*)w;
}

INCASM("asm/weapon/saber_wave_p1_p1a.inc");

void Weapon5_Update(struct Weapon* w) {
  u8* pp = (u8*)w + 0xb4;
  struct Entity* sb = *(struct Entity**)pp;
  register struct Zero* z asm("r8");
  z = *(struct Zero**)(pp + 4);
  if (sb->mode[0] > 1) {
    u8 f = ~1 & (w->s).flags;
    s32 z2;
    z2 = 0;
    f = f & ~2;
    (w->s).flags = f;
    {
      u8* a = (u8*)w + 0x8c;
      *(u32*)a = z2;
      asm("" : "+r"(a));
      a += 4;
      *(u32*)a = z2;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *a = z2;
    }
    (w->s).flags &= 0xFB;
    SET_WEAPON_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }
  UpdateMotionGraphic(&w->s);
  if ((w->s).work[0] == 0) {
    if ((w->body).status & 0x1000) {
      PlaySound(0x2B);
    }
    {
      u32 t = (u8)--(w->s).work[2];
      if (t == 0) {
        goto die;
      }
      (w->s).coord.x += (w->s).d.x;
      {
        s32 mg1;
        register s32 mg2 asm("r4");
        if (t <= 0xB) {
          register s32 h asm("r5");
          s32 q;
          (w->s).d.x += (w->s).unk_coord.x;
          q = 0xC - (w->s).work[2];
          mg1 = q << 8;
          asm("" : "+r"(mg1));
          mg2 = mg1;
          mg1 = mg2 / 12;
          h = 0x100;
          mg1 += h;
          mg2 = -mg2;
          mg2 = mg2 / 12;
          asm("" : "+r"(mg2));
          mg2 += h;
        } else {
          mg2 = 0x100;
          mg1 = mg2;
        }
        {
          register u8* mp asm("r0");
          mp = (u8*)w + 0x50;
          *(u16*)mp = mg1;
          asm("" : "+r"(mp));
          mp += 2;
          asm("" : "+r"(mp));
          *(u16*)mp = mg2;
        }
        mg2 += 0x10;
        asm("" : "+r"(mg2));
        {
          register s32 tc asm("r0");
          tc = mg2;
          asm("" : "+r"(tc));
          if (mg2 < 0) {
            tc += 0x1F;
          }
          {
          s32 v = tc >> 5;
          if (v != 0) {
            u8 dmg = CalcSaberBonus(z) + 8;
            if (v > 7) {
              v = 7;
            }
            InitWeaponBody(&w->body, &sCollisions[v * 2], dmg, -1, -1, -1);
          }
          }
        }
      }
    }
  } else {
    if (sb->mode[0] <= 1) {
      (w->s).coord.x = (sb->coord).x;
      (w->s).coord.y = (sb->coord).y;
      {
        u16 m1 = *(u16*)((u8*)sb + 0x50);
        *(u16*)((u8*)w + 0x50) = m1;
      }
      {
        u16 m2 = *(u16*)((u8*)sb + 0x52);
        *(u16*)((u8*)w + 0x52) = m2;
      }
    } else {
    die:
      SET_WEAPON_ROUTINE(w, ENTITY_DIE);
      Weapon5_Die(w);
    }
  }
}

void Weapon5_Die(struct Weapon* w) {
  EXIT_BODY(w);
  (w->s).flags &= ~DISPLAY;
  SET_WEAPON_ROUTINE(w, ENTITY_EXIT);
}

static void hitZSaber(struct Body* body) {
  if (body->hitboxFlags & BODY_STATUS_B2) {
    if (gMission.weaponCount[WEAPON_SABER] <= 0xFFFE) {
      gMission.weaponCount[WEAPON_SABER]++;
    }
  }
}

