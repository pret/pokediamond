#include "global.h"
#include "main.h"
#include "options.h"
#include "overlay_manager.h"
#include "player_data.h"
#include "sav_system_info.h"

extern void FUN_0201681C(u32 param0, u32 heap_id, u32 param2);
extern int FUN_020168D0(u32 heap_id);
extern void MOD52_021D769C(u32 heap_id, struct SaveBlock2 *save);
extern struct Unk21DBE18 UNK_020FD144;
extern struct Unk21DBE18 UNK_020F2B7C;

extern void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *save, u32 param2);
extern void FUN_02015E3C(struct IGT *igt);

extern void MOD52_021D7688(u32 heap_id, struct SaveBlock2 *save);

THUMB_FUNC int MOD52_021D74E0()
{
    FUN_0201681C(3, 0x4d, 2 << 16);
    InitializeMainRNG();

    return 1;
}

THUMB_FUNC int MOD52_021D74F8(struct UnkStruct_02006234 *param0)
{
    struct SaveBlock2 *save = OverlayManager_GetField18(param0)[2];

    MOD52_021D769C(0x4d, save);

    return 1;
}

THUMB_FUNC int MOD52_021D750C()
{
    FUN_020168D0(0x4d);
    RegisterMainOverlay(-1, &UNK_020FD144);

    return 1;
}

THUMB_FUNC int MOD52_021D7528()
{
    FUN_0201681C(3, 0x4d, 2 << 16);
    InitializeMainRNG();

    return 1;
}

THUMB_FUNC int MOD52_021D7540(struct UnkStruct_02006234 *param0)
{
    struct SaveBlock2 *save = OverlayManager_GetField18(param0)[2];
    MOD52_021D7604(0x4d, save, 1);
    struct IGT *igt = Sav2_PlayerData_GetIGTAddr(save);
    FUN_02015E3C(igt);

    return 1;
}

THUMB_FUNC int MOD52_021D7560()
{
    FUN_020168D0(0x4d);
    RegisterMainOverlay(-1, &UNK_020F2B7C);

    return 1;
}

THUMB_FUNC int MOD52_021D757C()
{
    FUN_0201681C(3, 0x4d, 2 << 16);
    InitializeMainRNG();

    return 1;
}

THUMB_FUNC int MOD52_021D7594(struct UnkStruct_02006234 *param0)
{
    struct SaveBlock2 *save = OverlayManager_GetField18(param0)[2];
    struct SavSysInfo *save_info = Sav2_SysInfo_get(save);

    MOD52_021D7688(0x4d, save);
    Options_SetButtonModeOnMain(save, 0);

    if (!Sav2_SysInfo_MacAddressIsMine(save_info) || !Sav2_SysInfo_RTCOffsetIsMine(save_info))
    {
        FUN_020238A4(Sav2_SysInfo_RTC_get(save));
        Sav2_SysInfo_InitFromSystem(save_info);
    }

    FUN_02015E3C(Sav2_PlayerData_GetIGTAddr(save));

    return 1;
}
