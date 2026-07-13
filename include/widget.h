#ifndef GUARD_RMZ3_WIDGET_H
#define GUARD_RMZ3_WIDGET_H

#include "entity/entity.h"
#include "types.h"

struct Widget {
  struct Entity s;
  u8 props[16];
};  // 132 bytes

// EXスキル/キーコンフィグメニューの四角いカーソル (Widget.props を px/py で解釈したもの)
struct SquareCursorWidget {
  struct Entity s;
  u16 px;         // 0x74
  u16 py;         // 0x76
  bool8 dead;     // 0x78
  u8 pad_79[11];  // 0x79
};

// --------------------------------------------

extern struct Widget gWidgets[64];

struct EntityHeader;
extern struct EntityHeader* gWidgetHeaderPtr;

typedef void (*WidgetFunc)(struct Widget*);
typedef WidgetFunc WidgetRoutine[5];
extern const WidgetRoutine* const gWidgetFnTable[14];

// --------------------------------------------

#define INIT_WIDGET_ROUTINE(entity, entityID) INIT_ENTITY_ROUTINE(gWidgetFnTable, entity, entityID)
#define SET_WIDGET_ROUTINE(entity, modeID) SET_ENTITY_ROUTINE(gWidgetFnTable, entity, modeID)

// --------------------------------------------

struct GameState;

void DeleteWidget(struct Entity* w);
struct Widget* CreateElfIcon(struct GameState* g);
struct Widget* CreateElfMenuItem(struct GameState* g, u8 row, u8 r2);

#endif  // GUARD_RMZ3_WIDGET_H
