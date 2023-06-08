#include "global.h"
#include "module_52.h"
#include "heap.h"
#include "unk_0205FA2C.h"
#include "play_timer.h"


extern struct OverlayManagerTemplate UNK_020FD144;
extern struct OverlayManagerTemplate UNK_020F2B7C;
extern struct OverlayManagerTemplate UNK_020F2B8C;

extern int FUN_02053678(u32 random, u32 gender, u32 param2);
extern void FUN_020250C4(void *sav_ptr, u32 heap_id, const u16 param2[], u32 param3);
extern void FUN_020377E0(struct SaveBlock2 *sav2);
extern void FUN_0205ECD4(struct ScriptState *script_state);

const struct OverlayManagerTemplate MOD52_021D76E8 = {
    MOD52_021D74E0,
    MOD52_021D74F8,
    MOD52_021D750C,
    SDK_OVERLAY_INVALID_ID,
};

const struct OverlayManagerTemplate MOD52_021D76D8 = {
    MOD52_021D7528,
    MOD52_021D7540,
    MOD52_021D7560,
    SDK_OVERLAY_INVALID_ID,
};

const struct OverlayManagerTemplate MOD52_021D76C8 = {
    MOD52_021D757C,
    MOD52_021D7594,
    MOD52_021D75E8,
    SDK_OVERLAY_INVALID_ID,
};

const u16 MOD52_021D76F8[] = {
    ITEM_ORAN_BERRY, 1,
    ITEM_CHERI_BERRY, 1,
    ITEM_CHESTO_BERRY, 1,
    ITEM_PECHA_BERRY, 1,
    ITEM_ORAN_BERRY, 1,
    ITEM_PECHA_BERRY, 1,
    ITEM_RAZZ_BERRY, 2,
    ITEM_BLUK_BERRY, 2,
    ITEM_CHERI_BERRY, 1,
    ITEM_ORAN_BERRY, 2,
    ITEM_SITRUS_BERRY, 1,
    ITEM_WEPEAR_BERRY, 2,
    ITEM_WEPEAR_BERRY, 2,
    ITEM_KELPSY_BERRY, 1,
    ITEM_CHERI_BERRY, 1,
    ITEM_PECHA_BERRY, 1,
    ITEM_ORAN_BERRY, 1,
    ITEM_ORAN_BERRY, 1,
    ITEM_RAWST_BERRY, 1,
    ITEM_RAWST_BERRY, 1,
    ITEM_RAZZ_BERRY, 1,
    ITEM_RAZZ_BERRY, 1,
    ITEM_CHERI_BERRY, 1,
    ITEM_ORAN_BERRY, 1,
    ITEM_ORAN_BERRY, 1,
    ITEM_BLUK_BERRY, 1,
    ITEM_NANAB_BERRY, 2,
    ITEM_RAZZ_BERRY, 2,
    ITEM_BLUK_BERRY, 2,
    ITEM_PINAP_BERRY, 2,
    ITEM_LEPPA_BERRY, 1,
    ITEM_CHESTO_BERRY, 1,
    ITEM_RAZZ_BERRY, 1,
    ITEM_RAZZ_BERRY, 1,
    ITEM_PERSIM_BERRY, 1,
    ITEM_NANAB_BERRY, 1,
    ITEM_NANAB_BERRY, 1,
    ITEM_FIGY_BERRY, 1,
    ITEM_ASPEAR_BERRY, 1,
    ITEM_ASPEAR_BERRY, 1,
    ITEM_RAZZ_BERRY, 1,
    ITEM_PINAP_BERRY, 1,
    ITEM_SITRUS_BERRY, 1,
    ITEM_CHESTO_BERRY, 1,
    ITEM_WIKI_BERRY, 1,
    ITEM_AGUAV_BERRY, 1,
    ITEM_PECHA_BERRY, 1,
    ITEM_ASPEAR_BERRY, 1,
    ITEM_IAPAPA_BERRY, 1,
    ITEM_GREPA_BERRY, 1,
    ITEM_SITRUS_BERRY, 1,
    ITEM_ASPEAR_BERRY, 1,
    ITEM_TAMATO_BERRY, 1,
    ITEM_LUM_BERRY, 1,
    ITEM_PECHA_BERRY, 1,
    ITEM_PINAP_BERRY, 1,
    ITEM_PINAP_BERRY, 1,
    ITEM_PINAP_BERRY, 1,
    ITEM_PERSIM_BERRY, 1,
    ITEM_PERSIM_BERRY, 1,
    ITEM_NANAB_BERRY, 1,
    ITEM_NANAB_BERRY, 1,
    ITEM_AGUAV_BERRY, 1,
    ITEM_IAPAPA_BERRY, 1,
    ITEM_RAWST_BERRY, 1,
    ITEM_RAWST_BERRY, 1,
    ITEM_CHERI_BERRY, 1,
    ITEM_SITRUS_BERRY, 1,
    ITEM_CHESTO_BERRY, 1,
    ITEM_POMEG_BERRY, 1,
    ITEM_PECHA_BERRY, 2,
    ITEM_BLUK_BERRY, 2,
    ITEM_WIKI_BERRY, 1,
    ITEM_MAGO_BERRY, 1,
    ITEM_RAWST_BERRY, 1,
    ITEM_PERSIM_BERRY, 1,
    ITEM_FIGY_BERRY, 1,
    ITEM_PINAP_BERRY, 2,
    ITEM_LEPPA_BERRY, 1,
    ITEM_PECHA_BERRY, 1,
    ITEM_MAGO_BERRY, 1,
    ITEM_HONDEW_BERRY, 1,
    ITEM_WIKI_BERRY, 2,
    ITEM_MAGO_BERRY, 2,
    ITEM_AGUAV_BERRY, 2,
    ITEM_QUALOT_BERRY, 1,
    ITEM_SITRUS_BERRY, 2,
    ITEM_BLUK_BERRY, 3,
    ITEM_NANAB_BERRY, 3,
    ITEM_WEPEAR_BERRY, 3,
    ITEM_POMEG_BERRY, 1,
    ITEM_POMEG_BERRY, 1,
    ITEM_HONDEW_BERRY, 2,
    ITEM_HONDEW_BERRY, 2,
    ITEM_KELPSY_BERRY, 1,
    ITEM_KELPSY_BERRY, 1,
    ITEM_TAMATO_BERRY, 1,
    ITEM_TAMATO_BERRY, 1,
    ITEM_QUALOT_BERRY, 1,
    ITEM_QUALOT_BERRY, 1,
    ITEM_POMEG_BERRY, 1,
    ITEM_POMEG_BERRY, 1,
    ITEM_HONDEW_BERRY, 1,
    ITEM_HONDEW_BERRY, 1,
    ITEM_TAMATO_BERRY, 1,
    ITEM_TAMATO_BERRY, 1,
    ITEM_GREPA_BERRY, 1,
    ITEM_GREPA_BERRY, 1,
    ITEM_QUALOT_BERRY, 1,
    ITEM_QUALOT_BERRY, 1,
    ITEM_LUM_BERRY, 1,
    ITEM_LEPPA_BERRY, 1,
    ITEM_QUALOT_BERRY, 2,
    ITEM_GREPA_BERRY, 2,
    ITEM_KELPSY_BERRY, 2,
    ITEM_KELPSY_BERRY, 2,
    ITEM_GREPA_BERRY, 1,
    ITEM_GREPA_BERRY, 1,
};

BOOL MOD52_021D74E0(struct OverlayManager *manager, u32 *status)
{
#pragma unused(manager)
#pragma unused(status)
    CreateHeap(3, 0x4d, 0x20000);
    InitializeMainRNG();

    return TRUE;
}

BOOL MOD52_021D74F8(struct OverlayManager *manager, u32 *status)
{
#pragma unused(status)
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)OverlayManager_GetField18(manager)[2]; // weird

    MOD52_021D769C(0x4d, sav2);

    return TRUE;
}

BOOL MOD52_021D750C(struct OverlayManager *manager, u32 *status)
{
#pragma unused(manager)
#pragma unused(status)
    DestroyHeap(0x4d);
    RegisterMainOverlay(SDK_OVERLAY_INVALID_ID, &UNK_020FD144);

    return TRUE;
}

BOOL MOD52_021D7528(struct OverlayManager *manager, u32 *status)
{
#pragma unused(manager)
#pragma unused(status)
    CreateHeap(3, 0x4d, 0x20000);
    InitializeMainRNG();

    return TRUE;
}

BOOL MOD52_021D7540(struct OverlayManager *manager, u32 *status)
{
#pragma unused(status)
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)OverlayManager_GetField18(manager)[2]; // weird

    MOD52_021D7604(0x4d, sav2, 1);
    struct IGT *igt = Save_PlayerData_GetIGTAddr(sav2);
    PlayTimerStart(igt);

    return TRUE;
}

BOOL MOD52_021D7560(struct OverlayManager *manager, u32 *status)
{
#pragma unused(manager)
#pragma unused(status)
    DestroyHeap(0x4d);
    RegisterMainOverlay(SDK_OVERLAY_INVALID_ID, &UNK_020F2B7C);

    return TRUE;
}

BOOL MOD52_021D757C(struct OverlayManager *manager, u32 *status)
{
#pragma unused(manager)
#pragma unused(status)
    CreateHeap(3, 0x4d, 0x20000);
    InitializeMainRNG();

    return TRUE;
}

BOOL MOD52_021D7594(struct OverlayManager *manager, u32 *status)
{
#pragma unused(status)
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)OverlayManager_GetField18(manager)[2]; // weird

    struct SavSysInfo *sav2_info = Save_SysInfo_Get(sav2);

    MOD52_021D7688(0x4d, sav2);
    Options_SetButtonModeOnMain(sav2, 0);

    if (!Save_SysInfo_MacAddressIsMine(sav2_info) || !Save_SysInfo_RTCOffsetIsMine(sav2_info))
    {
        FUN_020238A4(Save_SysInfo_RTC_Get(sav2));
        Save_SysInfo_InitFromSystem(sav2_info);
    }

    PlayTimerStart(Save_PlayerData_GetIGTAddr(sav2));

    return TRUE;
}

BOOL MOD52_021D75E8(struct OverlayManager *manager, u32 *status)
{
#pragma unused(manager)
#pragma unused(status)
    DestroyHeap(0x4d);
    RegisterMainOverlay(SDK_OVERLAY_INVALID_ID, &UNK_020F2B8C);

    return 1;
}

void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *sav2, BOOL set_trainerid)
{
    Save_SysInfo_InitFromSystem(Save_SysInfo_Get(sav2));
    Save_SysInfo_RTC_Init(Save_SysInfo_RTC_Get(sav2));

    struct UnkSaveStruct_020286F8 *unk_sav2 = FUN_0202881C(sav2);

    FUN_02028788(unk_sav2, 1, MTRandom());
    FUN_0206007C(sav2);

    struct PlayerData *player_data = Save_PlayerData_GetProfileAddr(sav2);
    u32 trainerid = MTRandom();

    if (set_trainerid)
    {
        PlayerProfile_SetTrainerID(player_data, trainerid);
    }

    u32 gender = PlayerProfile_GetTrainerGender(player_data);
    int avatar = FUN_02053678(trainerid, gender, 0);

    PlayerProfile_SetAvatar(player_data, (u8)avatar);

    FUN_020250C4(FUN_02024ECC(sav2), heap_id, MOD52_021D76F8, NELEMS(MOD52_021D76F8) / 2);
}

void MOD52_021D7688(u32 unused, struct SaveBlock2 *sav2)
{
#pragma unused(unused)

    if (FUN_020226FC(sav2))
    {
        return;
    }

    OS_ResetSystem(0);
}

void MOD52_021D769C(u32 unused, struct SaveBlock2 *sav2)
{
#pragma unused(unused)

    Save_InitDynamicRegion(sav2);
    FUN_020377E0(sav2);
    struct PlayerData *player_data = Save_PlayerData_GetProfileAddr(sav2);
    PlayerProfile_SetMoney(player_data, 3000);
    FUN_0205ECD4(SaveArray_Flags_Get(sav2));
}
