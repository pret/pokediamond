#include "module_52.h"
#include "heap.h"
#include "unk_0205FA2C.h"


extern struct Unk21DBE18 UNK_020FD144;
extern struct Unk21DBE18 UNK_020F2B7C;
extern struct Unk21DBE18 UNK_020F2B8C;

extern void FUN_02015E3C(struct IGT *igt);
extern int FUN_02053678(u32 random, u32 gender, u32 param2);
extern void FUN_020250C4(void *sav_ptr, u32 heap_id, const u16 param2[], u32 param3);
extern void FUN_020377E0(struct SaveBlock2 *sav2);
extern void FUN_0205ECD4(struct ScriptState *script_state);

THUMB_FUNC BOOL MOD52_021D74E0(struct UnkStruct_02006234 *arg1, u32 *arg2)
{
#pragma unused(arg1)
#pragma unused(arg2)
    FUN_0201681C(3, 0x4d, 2 << 16);
    InitializeMainRNG();

    return 1;
}

THUMB_FUNC BOOL MOD52_021D74F8(struct UnkStruct_02006234 *param0, u32 *unused)
{
#pragma unused(unused)
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)OverlayManager_GetField18(param0)[2]; // weird

    MOD52_021D769C(0x4d, sav2);

    return 1;
}

THUMB_FUNC BOOL MOD52_021D750C(struct UnkStruct_02006234 *arg1, u32 *arg2)
{
#pragma unused(arg1)
#pragma unused(arg2)
    FUN_020168D0(0x4d);
    RegisterMainOverlay(0XFFFFFFFF, &UNK_020FD144);

    return 1;
}

THUMB_FUNC BOOL MOD52_021D7528(struct UnkStruct_02006234 *arg1, u32 *arg2)
{
#pragma unused(arg1)
#pragma unused(arg2)
    FUN_0201681C(3, 0x4d, 2 << 16);
    InitializeMainRNG();

    return 1;
}

THUMB_FUNC BOOL MOD52_021D7540(struct UnkStruct_02006234 *param0, u32 *unused)
{
#pragma unused(unused)
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)OverlayManager_GetField18(param0)[2]; // weird

    MOD52_021D7604(0x4d, sav2, 1);
    struct IGT *igt = Sav2_PlayerData_GetIGTAddr(sav2);
    FUN_02015E3C(igt);

    return 1;
}

THUMB_FUNC BOOL MOD52_021D7560(struct UnkStruct_02006234 *arg1, u32 *arg2)
{
#pragma unused(arg1)
#pragma unused(arg2)
    FUN_020168D0(0x4d);
    RegisterMainOverlay(0xFFFFFFFF, &UNK_020F2B7C);

    return 1;
}

THUMB_FUNC BOOL MOD52_021D757C(struct UnkStruct_02006234 *arg1, u32 *arg2)
{
#pragma unused(arg1)
#pragma unused(arg2)
    FUN_0201681C(3, 0x4d, 2 << 16);
    InitializeMainRNG();

    return 1;
}

THUMB_FUNC BOOL MOD52_021D7594(struct UnkStruct_02006234 *param0, u32 *unused)
{
#pragma unused(unused)
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)OverlayManager_GetField18(param0)[2]; // weird

    struct SavSysInfo *sav2_info = Sav2_SysInfo_get(sav2);

    MOD52_021D7688(0x4d, sav2);
    Options_SetButtonModeOnMain(sav2, 0);

    if (!Sav2_SysInfo_MacAddressIsMine(sav2_info) || !Sav2_SysInfo_RTCOffsetIsMine(sav2_info))
    {
        FUN_020238A4(Sav2_SysInfo_RTC_get(sav2));
        Sav2_SysInfo_InitFromSystem(sav2_info);
    }

    FUN_02015E3C(Sav2_PlayerData_GetIGTAddr(sav2));

    return 1;
}

THUMB_FUNC BOOL MOD52_021D75E8(struct UnkStruct_02006234 *arg1, u32 *arg2)
{
#pragma unused(arg1)
#pragma unused(arg2)
    FUN_020168D0(0x4d);
    RegisterMainOverlay(0XFFFFFFFF, &UNK_020F2B8C);

    return 1;
}

THUMB_FUNC void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *sav2, BOOL set_trainerid)
{
    Sav2_SysInfo_InitFromSystem(Sav2_SysInfo_get(sav2));
    Sav2_SysInfo_RTC_init(Sav2_SysInfo_RTC_get(sav2));

    struct UnkSaveStruct_020286F8 *unk_sav2 = FUN_0202881C(sav2);

    FUN_02028788(unk_sav2, 1, MTRandom());
    FUN_0206007C(sav2);

    struct PlayerData *player_data = Sav2_PlayerData_GetProfileAddr(sav2);
    u32 trainerid = MTRandom();

    if (set_trainerid)
    {
        PlayerProfile_SetTrainerID(player_data, trainerid);
    }

    u32 gender = PlayerProfile_GetTrainerGender(player_data);
    int avatar = FUN_02053678(trainerid, gender, 0);

    PlayerProfile_SetAvatar(player_data, (u8)avatar);

    FUN_020250C4(FUN_02024ECC(sav2), heap_id, MOD52_021D76F8, 0x76);
}

THUMB_FUNC void MOD52_021D7688(u32 unused, struct SaveBlock2 *sav2)
{
#pragma unused(unused)

    if (FUN_020226FC(sav2))
    {
        return;
    }

    OS_ResetSystem(0);
}

THUMB_FUNC void MOD52_021D769C(u32 unused, struct SaveBlock2 *sav2)
{
#pragma unused(unused)

    Sav2_InitDynamicRegion(sav2);
    FUN_020377E0(sav2);
    struct PlayerData *player_data = Sav2_PlayerData_GetProfileAddr(sav2);
    PlayerProfile_SetMoney(player_data, 3000);
    FUN_0205ECD4(SavArray_Flags_get(sav2));
}

const struct Unk21DBE18 MOD52_021D76E8 = {
    MOD52_021D74E0,
    MOD52_021D74F8,
    MOD52_021D750C,
    0xFFFFFFFF,
};

const struct Unk21DBE18 MOD52_021D76D8 = {
    MOD52_021D7528,
    MOD52_021D7540,
    MOD52_021D7560,
    0xFFFFFFFF,
};

const struct Unk21DBE18 MOD52_021D76C8 = {
    MOD52_021D757C,
    MOD52_021D7594,
    MOD52_021D75E8,
    0xFFFFFFFF,
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