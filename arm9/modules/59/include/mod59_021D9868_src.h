#ifndef POKEDIAMOND_MOD59_021D9868_H
#define POKEDIAMOND_MOD59_021D9868_H

#include "nitro/types.h"
#include "main.h"

typedef struct MOD59_OverlayData2
{
    u32 heap_id;
    u8 padding[0x20];
    u32 unk24;
} MOD59_OverlayData2;

BOOL MOD59_Init2(struct UnkStruct_02006234 *param0, u32 *param1);

#endif // POKEDIAMOND_MOD59_021D9868_H
