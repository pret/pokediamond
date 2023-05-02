#include "global.h"
#include "mod59_021D9868_src.h"
#include "heap.h"
#include "overlay_manager.h"

THUMB_FUNC BOOL MOD59_Init2(struct UnkStruct_02006234 *param0, u32 *param1) //todo find a better name
{
#pragma unused(param1)
    CreateHeap(3, 83, 0x40000);
    MOD59_OverlayData2 *data = (MOD59_OverlayData2 *)OverlayManager_CreateAndGetData(param0, sizeof(MOD59_OverlayData2), 0x53);
    (void)memset((void *)data, 0, sizeof(MOD59_OverlayData2));
    data->heap_id = 0x53;
    data->unk24 = 0;
    return TRUE;
}
