#include "global.h"
#include "player_data.h"
#include "overlay_manager.h"
#include "mod59_021D74E0.h"
#include "heap.h"


extern u32 FUN_02077A84(u32 heap_id, u32 param1, u32 param2, u32 param3, struct Options *options);

THUMB_FUNC BOOL MOD59_Init(struct UnkStruct_02006234 *param0)
{
    //note: 0xb4 is likely the overlay data struct size, once struct is padded replace with sizeof
    CreateHeap(3, 0x52, 1 << 18);
    MOD59_OverlayData *data = (MOD59_OverlayData *) OverlayManager_CreateAndGetData(param0, 0xb4, 0x52);
    (void)memset((void *)data, 0, 0xb4);

    data->heap_id = 0x52;
    int *field18 = OverlayManager_GetField18(param0);
    data->sav2 = (struct SaveBlock2 *)field18[2]; //?
    data->options = Sav2_PlayerData_GetOptionsAddr(data->sav2);
    data->Unk14 = data->Unk10 = data->Unk0C = 0;
    data->Unk70 = FUN_02077A84(0x52, 0, 0, 7, data->options);
    data->Unk74 = FUN_02077A84(0x52, 3, 0, 7, data->options);
    data->Unk88 = 0;
    data->Unk89 = 0;
    data->Unk8A = 0;
    data->Unk8B = 0;
    data->Unk90 = 0;
    return TRUE;
}
