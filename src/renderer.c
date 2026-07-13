#include "renderer.h"

#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "sprite.h"
#include "story.h"

void Renderer_Init(struct Renderer* tm) {
  CpuFastFill(0, tm->buffer, TASK_LENGTH * 4);
  {
    vu32 _;
  }
  tm->tasks = &tm->buffer;
  tm->pivot = NULL;
  tm->_ = NULL;
}

void Renderer_SetPivot(struct Renderer* tm, struct Pivot* pivot) {
  tm->pivot = pivot;
  return;
}

static void unused_08004e58(struct Renderer* tm, void* r1) {
  tm->_ = r1;
  return;
}

void Renderer_PrependTask(struct Renderer* tm, struct RenderNode* task) {
  task->next = (*tm->tasks)[0];
  (*tm->tasks)[0] = task;
}

static void unused_08004e74(struct Renderer* tm, struct RenderNode* task, s16 row) {
  struct RenderNode* cur = (*tm->tasks)[row * 32];
  task->next = cur;
  (*tm->tasks)[row * 32] = task;
}

/*
Tasks
        Col0  Col1 .. Col30  Col31
Row 0    t0    t1
Row 1
Row 2
Row 3

tn は タスク1つではなくタスクのリンクリスト (t0なら t0 -> t0' -> t0'' -> ...)

(row*32) + col が　0 に近いものが先に描画され、後から描画するものがそれを上書きしていく
*/
void Renderer_SendTask(struct Renderer* tm, struct RenderNode* task, s16 row, s16 col) {
  struct RenderNode* cur = (&((*tm->tasks)[row * 32]))[col];
  task->next = cur;
  (&((*tm->tasks)[row * 32]))[col] = task;
}

void Renderer_Flush(struct Renderer* tm) {
  s32 i;
  struct RenderNode** list;
  struct DrawPivot c;

  if (tm->pivot != NULL) {
    CreateDrawPivot(&c, tm->pivot, tm->_);
    list = (struct RenderNode**)(*tm->tasks);

    for (i = 0; i < TASK_LENGTH; i++) {
      struct RenderNode* task = list[0];
      list = &list[1];
      for (; task != NULL; task = task->next) {
        (task->fn)(task, &c);
      }
    }
  }
}

void Renderer_Clear(struct Renderer* tm) {
  struct RenderNode*(*heap)[TASK_LENGTH] = Malloc(TASK_LENGTH * 4);

  tm->tasks = heap;
  if (heap == NULL) {
    tm->tasks = &tm->buffer;
  }

  {
    const u32 fill = 0;
    void* dst = *tm->tasks;
    CpuFastFill(fill, dst, TASK_LENGTH * 4);
    {
      vu32 _;
    }
  }
}
