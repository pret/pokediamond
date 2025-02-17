#ifndef POKEDIAMOND_OVERLAY_06_H
#define POKEDIAMOND_OVERLAY_06_H

#include "field_system.h"

typedef struct FieldMoveTaskEnvironment FieldMoveTaskEnvironment;

enum MartType {
    MART_ITEMS = 0,
    MART_GOODS,
    MART_SEALS,
    MART_DECORATIONS = MART_GOODS,
};

void ov06_0223D3D0(struct TaskManager *, struct FieldSystem *, const u16 *, enum MartType, u32);

#endif // POKEDIAMOND_OVERLAY_06_H
