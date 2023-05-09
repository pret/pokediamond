#ifndef POKEDIAMOND_MODULE_06_H
#define POKEDIAMOND_MODULE_06_H

enum MartType
{
    MART_ITEMS = 0,
    MART_GOODS,
    MART_SEALS,
    MART_DECORATIONS = MART_GOODS,
};

void MOD06_0223D3D0(struct TaskManager *, struct FieldSystem *, const u16 *, enum MartType, u32);

#endif //POKEDIAMOND_MODULE_06_H
