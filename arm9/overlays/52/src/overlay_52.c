#include "overlay_52.h"

#include "global.h"

#include "heap.h"
#include "play_timer.h"
#include "unk_0205FA2C.h"

extern struct OverlayManagerTemplate UNK_020FD144;
extern struct OverlayManagerTemplate UNK_020F2B7C;
extern struct OverlayManagerTemplate UNK_020F2B8C;

extern int sub_02053678(u32 random, u32 gender, u32 param2);
extern void sub_020250C4(void *sav_ptr, HeapID heapId, const u16 param2[], u32 param3);
extern void sub_020377E0(struct SaveData *save);
extern void sub_0205ECD4(struct SaveVarsFlags *script_state);

const struct OverlayManagerTemplate ov52_021D76E8 = {
    ov52_021D74E0,
    ov52_021D74F8,
    ov52_021D750C,
    SDK_OVERLAY_INVALID_ID,
};

const struct OverlayManagerTemplate ov52_021D76D8 = {
    ov52_021D7528,
    ov52_021D7540,
    ov52_021D7560,
    SDK_OVERLAY_INVALID_ID,
};

const struct OverlayManagerTemplate ov52_021D76C8 = {
    ov52_021D757C,
    ov52_021D7594,
    ov52_021D75E8,
    SDK_OVERLAY_INVALID_ID,
};

const u16 ov52_021D76F8[] = {
    ITEM_ORAN_BERRY,
    1,
    ITEM_CHERI_BERRY,
    1,
    ITEM_CHESTO_BERRY,
    1,
    ITEM_PECHA_BERRY,
    1,
    ITEM_ORAN_BERRY,
    1,
    ITEM_PECHA_BERRY,
    1,
    ITEM_RAZZ_BERRY,
    2,
    ITEM_BLUK_BERRY,
    2,
    ITEM_CHERI_BERRY,
    1,
    ITEM_ORAN_BERRY,
    2,
    ITEM_SITRUS_BERRY,
    1,
    ITEM_WEPEAR_BERRY,
    2,
    ITEM_WEPEAR_BERRY,
    2,
    ITEM_KELPSY_BERRY,
    1,
    ITEM_CHERI_BERRY,
    1,
    ITEM_PECHA_BERRY,
    1,
    ITEM_ORAN_BERRY,
    1,
    ITEM_ORAN_BERRY,
    1,
    ITEM_RAWST_BERRY,
    1,
    ITEM_RAWST_BERRY,
    1,
    ITEM_RAZZ_BERRY,
    1,
    ITEM_RAZZ_BERRY,
    1,
    ITEM_CHERI_BERRY,
    1,
    ITEM_ORAN_BERRY,
    1,
    ITEM_ORAN_BERRY,
    1,
    ITEM_BLUK_BERRY,
    1,
    ITEM_NANAB_BERRY,
    2,
    ITEM_RAZZ_BERRY,
    2,
    ITEM_BLUK_BERRY,
    2,
    ITEM_PINAP_BERRY,
    2,
    ITEM_LEPPA_BERRY,
    1,
    ITEM_CHESTO_BERRY,
    1,
    ITEM_RAZZ_BERRY,
    1,
    ITEM_RAZZ_BERRY,
    1,
    ITEM_PERSIM_BERRY,
    1,
    ITEM_NANAB_BERRY,
    1,
    ITEM_NANAB_BERRY,
    1,
    ITEM_FIGY_BERRY,
    1,
    ITEM_ASPEAR_BERRY,
    1,
    ITEM_ASPEAR_BERRY,
    1,
    ITEM_RAZZ_BERRY,
    1,
    ITEM_PINAP_BERRY,
    1,
    ITEM_SITRUS_BERRY,
    1,
    ITEM_CHESTO_BERRY,
    1,
    ITEM_WIKI_BERRY,
    1,
    ITEM_AGUAV_BERRY,
    1,
    ITEM_PECHA_BERRY,
    1,
    ITEM_ASPEAR_BERRY,
    1,
    ITEM_IAPAPA_BERRY,
    1,
    ITEM_GREPA_BERRY,
    1,
    ITEM_SITRUS_BERRY,
    1,
    ITEM_ASPEAR_BERRY,
    1,
    ITEM_TAMATO_BERRY,
    1,
    ITEM_LUM_BERRY,
    1,
    ITEM_PECHA_BERRY,
    1,
    ITEM_PINAP_BERRY,
    1,
    ITEM_PINAP_BERRY,
    1,
    ITEM_PINAP_BERRY,
    1,
    ITEM_PERSIM_BERRY,
    1,
    ITEM_PERSIM_BERRY,
    1,
    ITEM_NANAB_BERRY,
    1,
    ITEM_NANAB_BERRY,
    1,
    ITEM_AGUAV_BERRY,
    1,
    ITEM_IAPAPA_BERRY,
    1,
    ITEM_RAWST_BERRY,
    1,
    ITEM_RAWST_BERRY,
    1,
    ITEM_CHERI_BERRY,
    1,
    ITEM_SITRUS_BERRY,
    1,
    ITEM_CHESTO_BERRY,
    1,
    ITEM_POMEG_BERRY,
    1,
    ITEM_PECHA_BERRY,
    2,
    ITEM_BLUK_BERRY,
    2,
    ITEM_WIKI_BERRY,
    1,
    ITEM_MAGO_BERRY,
    1,
    ITEM_RAWST_BERRY,
    1,
    ITEM_PERSIM_BERRY,
    1,
    ITEM_FIGY_BERRY,
    1,
    ITEM_PINAP_BERRY,
    2,
    ITEM_LEPPA_BERRY,
    1,
    ITEM_PECHA_BERRY,
    1,
    ITEM_MAGO_BERRY,
    1,
    ITEM_HONDEW_BERRY,
    1,
    ITEM_WIKI_BERRY,
    2,
    ITEM_MAGO_BERRY,
    2,
    ITEM_AGUAV_BERRY,
    2,
    ITEM_QUALOT_BERRY,
    1,
    ITEM_SITRUS_BERRY,
    2,
    ITEM_BLUK_BERRY,
    3,
    ITEM_NANAB_BERRY,
    3,
    ITEM_WEPEAR_BERRY,
    3,
    ITEM_POMEG_BERRY,
    1,
    ITEM_POMEG_BERRY,
    1,
    ITEM_HONDEW_BERRY,
    2,
    ITEM_HONDEW_BERRY,
    2,
    ITEM_KELPSY_BERRY,
    1,
    ITEM_KELPSY_BERRY,
    1,
    ITEM_TAMATO_BERRY,
    1,
    ITEM_TAMATO_BERRY,
    1,
    ITEM_QUALOT_BERRY,
    1,
    ITEM_QUALOT_BERRY,
    1,
    ITEM_POMEG_BERRY,
    1,
    ITEM_POMEG_BERRY,
    1,
    ITEM_HONDEW_BERRY,
    1,
    ITEM_HONDEW_BERRY,
    1,
    ITEM_TAMATO_BERRY,
    1,
    ITEM_TAMATO_BERRY,
    1,
    ITEM_GREPA_BERRY,
    1,
    ITEM_GREPA_BERRY,
    1,
    ITEM_QUALOT_BERRY,
    1,
    ITEM_QUALOT_BERRY,
    1,
    ITEM_LUM_BERRY,
    1,
    ITEM_LEPPA_BERRY,
    1,
    ITEM_QUALOT_BERRY,
    2,
    ITEM_GREPA_BERRY,
    2,
    ITEM_KELPSY_BERRY,
    2,
    ITEM_KELPSY_BERRY,
    2,
    ITEM_GREPA_BERRY,
    1,
    ITEM_GREPA_BERRY,
    1,
};

BOOL ov52_021D74E0(struct OverlayManager *manager, u32 *status) {
#pragma unused(manager)
#pragma unused(status)
    CreateHeap(3, 0x4d, 0x20000);
    InitializeMainRNG();

    return TRUE;
}

BOOL ov52_021D74F8(struct OverlayManager *manager, u32 *status) {
#pragma unused(status)
    struct SaveData *save = (struct SaveData *)OverlayManager_GetField18(manager)[2]; // weird

    ov52_021D769C(HEAP_ID_77, save);

    return TRUE;
}

BOOL ov52_021D750C(struct OverlayManager *manager, u32 *status) {
#pragma unused(manager)
#pragma unused(status)
    DestroyHeap(HEAP_ID_77);
    RegisterMainOverlay(SDK_OVERLAY_INVALID_ID, &UNK_020FD144);

    return TRUE;
}

BOOL ov52_021D7528(struct OverlayManager *manager, u32 *status) {
#pragma unused(manager)
#pragma unused(status)
    CreateHeap(3, 0x4d, 0x20000);
    InitializeMainRNG();

    return TRUE;
}

BOOL ov52_021D7540(struct OverlayManager *manager, u32 *status) {
#pragma unused(status)
    struct SaveData *save = (struct SaveData *)OverlayManager_GetField18(manager)[2]; // weird

    ov52_021D7604(HEAP_ID_77, save, 1);
    struct IGT *igt = Save_PlayerData_GetIGTAddr(save);
    PlayTimerStart(igt);

    return TRUE;
}

BOOL ov52_021D7560(struct OverlayManager *manager, u32 *status) {
#pragma unused(manager)
#pragma unused(status)
    DestroyHeap(HEAP_ID_77);
    RegisterMainOverlay(SDK_OVERLAY_INVALID_ID, &UNK_020F2B7C);

    return TRUE;
}

BOOL ov52_021D757C(struct OverlayManager *manager, u32 *status) {
#pragma unused(manager)
#pragma unused(status)
    CreateHeap(3, 0x4d, 0x20000);
    InitializeMainRNG();

    return TRUE;
}

BOOL ov52_021D7594(struct OverlayManager *manager, u32 *status) {
#pragma unused(status)
    struct SaveData *save = (struct SaveData *)OverlayManager_GetField18(manager)[2]; // weird

    struct SaveSysInfo *save_info = Save_SysInfo_Get(save);

    ov52_021D7688(0x4d, save);
    Options_SetButtonModeOnMain(save, 0);

    if (!Save_SysInfo_MacAddressIsMine(save_info) || !Save_SysInfo_RTCOffsetIsMine(save_info)) {
        sub_020238A4(Save_SysInfo_RTC_Get(save));
        Save_SysInfo_InitFromSystem(save_info);
    }

    PlayTimerStart(Save_PlayerData_GetIGTAddr(save));

    return TRUE;
}

BOOL ov52_021D75E8(struct OverlayManager *manager, u32 *status) {
#pragma unused(manager)
#pragma unused(status)
    DestroyHeap(HEAP_ID_77);
    RegisterMainOverlay(SDK_OVERLAY_INVALID_ID, &UNK_020F2B8C);

    return 1;
}

void ov52_021D7604(HeapID heapId, struct SaveData *save, BOOL set_trainerid) {
    Save_SysInfo_InitFromSystem(Save_SysInfo_Get(save));
    Save_SysInfo_RTC_Init(Save_SysInfo_RTC_Get(save));

    struct UnkSaveStruct_020286F8 *unk_save = sub_0202881C(save);

    sub_02028788(unk_save, 1, MTRandom());
    sub_0206007C(save);

    PlayerProfile *playerProfile = Save_PlayerData_GetProfileAddr(save);
    u32 trainerid                = MTRandom();

    if (set_trainerid) {
        PlayerProfile_SetTrainerID(playerProfile, trainerid);
    }

    u32 gender = PlayerProfile_GetTrainerGender(playerProfile);
    int avatar = sub_02053678(trainerid, gender, 0);

    PlayerProfile_SetAvatar(playerProfile, (u8)avatar);

    sub_020250C4(sub_02024ECC(save), heapId, ov52_021D76F8, NELEMS(ov52_021D76F8) / 2);
}

void ov52_021D7688(u32 unused, struct SaveData *save) {
#pragma unused(unused)

    if (sub_020226FC(save)) {
        return;
    }

    OS_ResetSystem(0);
}

void ov52_021D769C(u32 unused, struct SaveData *save) {
#pragma unused(unused)

    Save_InitDynamicRegion(save);
    sub_020377E0(save);
    PlayerProfile *playerProfile = Save_PlayerData_GetProfileAddr(save);
    PlayerProfile_SetMoney(playerProfile, 3000);
    sub_0205ECD4(Save_VarsFlags_Get(save));
}
