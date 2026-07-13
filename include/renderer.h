#ifndef GUARD_RMZ3_RENDERER_H
#define GUARD_RMZ3_RENDERER_H

#include "common.h"
#include "constants/constants.h"
#include "types.h"

// 描画に順番を設定するための描画タスク管理

// 任意の型のポインタ + そのポインタ+pivot で呼び出すコールバック
typedef struct RenderNode {
  struct RenderNode* next;
  void (*fn)(struct RenderNode*, struct DrawPivot*);
} RenderNode;

typedef struct Renderer {
  struct RenderNode* buffer[TASK_LENGTH];    // タスク用のメモリ領域？
  struct RenderNode* (*tasks)[TASK_LENGTH];  // e.g. 0x03000380 (-> [02002200, 03007874])
  struct Pivot* pivot;                       // &camera->pivot
  void* _;                                   // Unused
} Renderer;

void Renderer_Init(struct Renderer* r);
void Renderer_SetPivot(struct Renderer* r, struct Pivot* pivot);
void Renderer_PrependTask(struct Renderer* r, struct RenderNode* task);
void Renderer_SendTask(struct Renderer* r, struct RenderNode* task, s16 prio, s16 x);
void Renderer_Clear(struct Renderer* r);
void Renderer_Flush(struct Renderer* r);

void SetTaskCallback(struct RenderNode* t, void* cb);

#endif  // GUARD_RMZ3_RENDERER_H
