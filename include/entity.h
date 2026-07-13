#ifndef GUARD_RMZ3_ENTITY_H
#define GUARD_RMZ3_ENTITY_H

#include "entity/macros.h"
//
#include "entity/boss.h"
#include "entity/elf.h"
#include "entity/enemy.h"
#include "entity/entity.h"
#include "entity/player.h"
#include "entity/projectile.h"
#include "entity/solid.h"
#include "entity/vfx.h"
#include "entity/weapon.h"
#include "entity_manager.h"
#include "renderer.h"

extern struct EntityHeader* pCurEntityHeader;
extern struct EntityHeader* gZeroHeaderPtr;
extern struct EntityHeader* gWeaponHeaderPtr;
extern struct EntityHeader* gBossHeaderPtr;
extern struct EntityHeader* gSolidHeaderPtr;
extern struct EntityHeader* gVFXHeaderPtr;
extern struct EntityHeader* gProjectileHeaderPtr;
extern struct EntityHeader* gEnemyHeaderPtr;
extern struct EntityHeader* gElfHeaderPtr;

extern struct Zero gZero;
extern struct Weapon gWeapons[24];
extern struct Boss gBosses[5];
extern struct Enemy gEnemies[18];
extern struct Projectile gProjectiles[24];
extern struct VFX gVFXs[64];
extern struct Solid gSolids[22];
extern struct Elf gElfEntities[16];
extern u8 gEntityIDGenerator;

void setCurProcessedEntityHeader(struct EntityHeader* h);
struct Entity* AllocEntityLast(struct EntityHeader* h);
struct Entity* AllocEntityFirst(struct EntityHeader* h);
void DeleteEntity(struct Entity* p);
void DeleteEntityEx(struct EntityHeader* h, struct Entity* z);
void UpdateEntities(struct EntityHeader* h);
void UpdateHazardEntities(struct EntityHeader* h);
void ignoreEntityFn(struct EntityHeader* h);
void RunDamageEffect(struct EntityHeader* h);
void RegisterHitboxes(struct EntityHeader* h);

void DrawEntity(struct EntityHeader* h, struct Renderer* r1);
void DrawCollidableEntity(struct EntityHeader* h, struct Renderer* r1);
struct Entity* GetNearestEntity(struct EntityHeader* h, struct Coord* c);
void InitNonAffineMotion(struct Entity* e);
void InitRotatableMotion(struct Entity* e);
u16 countSpecificEntities1(struct EntityHeader* h, u8 id);
u16 countSpecificEntities2(struct EntityHeader* h, u8 id, u8 r2, u8 r3);

// おそらく画面内かどうかを判断してEntityを生成(or削除)する処理
void UpdateStageEntities(struct Coord* viewport);

void InitNonAffineSprite(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);
void InitRotatableSprite(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);
void InitScalerotSprite1(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);
void InitScalerotSprite2(struct Sprite* s, struct MetaspriteHeader* sprites, struct Coord* c);

void RotateSprite(struct Sprite* s, s32 angle);
void ScalerotSprite(struct Sprite* s, s32 angle);
void UpdateEntityPaletteID(struct Entity* p);
void PaintEntityWhite(struct Entity* p);
void FUN_0801779c(struct Entity* p);

bool32 isKilled(struct Entity* p);

#endif  // GUARD_RMZ3_ENTITY_H
