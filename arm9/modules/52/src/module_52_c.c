#include "global.h"
#include "main.h"
#include "options.h"
#include "overlay_manager.h"
#include "player_data.h"
#include "sav_system_info.h"
#include "unk_020286F8.h"
#include "math_util.h"


extern void FUN_0201681C(u32 param0, u32 heap_id, u32 param2);
extern int FUN_020168D0(u32 heap_id);
extern void MOD52_021D769C(u32 heap_id, struct SaveBlock2 *save);
extern struct Unk21DBE18 UNK_020FD144;
extern struct Unk21DBE18 UNK_020F2B7C;
extern struct Unk21DBE18 UNK_020F2B8C;

void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *save, u32 param2);
extern void FUN_02015E3C(struct IGT *igt);

extern void MOD52_021D7688(u32 heap_id, struct SaveBlock2 *save);

extern void FUN_0206007C(struct SaveBlock2 *save);
extern int FUN_02053678(u32 random, u32 gender, u32 param2);
extern void FUN_02024ECC(struct SaveBlock2 *save);
extern void FUN_020250C4(struct SaveBlock2 *save, u32 heap_id, u32 **param2, u32 param3);

extern u32 *MOD52_021D76F8;

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

THUMB_FUNC int MOD52_021D75E8()
{
    FUN_020168D0(0x4d);
    RegisterMainOverlay(-1, &UNK_020F2B8C);

    return 1;
}


// 	thumb_func_start MOD52_021D7604
// MOD52_021D7604: ; 0x021D7604
// 	push {r3, r4, r5, r6, r7, lr}
// 	add r5, r1, #0
// 	str r0, [sp]
// 	add r0, r5, #0
// 	add r6, r2, #0
// 	bl Sav2_SysInfo_get
// 	bl Sav2_SysInfo_InitFromSystem
// 	add r0, r5, #0
// 	bl Sav2_SysInfo_RTC_get
// 	bl Sav2_SysInfo_RTC_init
// 	add r0, r5, #0
// 	bl FUN_0202881C
// 	add r4, r0, #0
// 	bl MTRandom
// 	add r2, r0, #0
// 	add r0, r4, #0
// 	mov r1, #1
// 	bl FUN_02028788
// 	add r0, r5, #0
// 	bl FUN_0206007C
// 	add r0, r5, #0
// 	bl Sav2_PlayerData_GetProfileAddr
// 	add r4, r0, #0
// 	bl MTRandom
// 	add r7, r0, #0
// 	cmp r6, #0
// 	beq _021D7656
// 	add r0, r4, #0
// 	add r1, r7, #0
// 	bl PlayerProfile_SetTrainerID
// _021D7656:
// 	add r0, r4, #0
// 	bl PlayerProfile_GetTrainerGender
// 	add r1, r0, #0
// 	add r0, r7, #0
// 	mov r2, #0
// 	bl FUN_02053678
// 	add r1, r0, #0
// 	lsl r1, r1, #0x18
// 	add r0, r4, #0
// 	lsr r1, r1, #0x18
// 	bl PlayerProfile_SetAvatar
// 	add r0, r5, #0
// 	bl FUN_02024ECC
// 	ldr r1, [sp]
// 	ldr r2, _021D7684 ; =0x021D76F8
// 	mov r3, #0x76
// 	bl FUN_020250C4
// 	pop {r3, r4, r5, r6, r7, pc}
// 	.align 2, 0
// _021D7684: .word MOD52_021D76F8
// 	thumb_func_end MOD52_021D7604
THUMB_FUNC void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *save, u32 param2) {
    Sav2_SysInfo_InitFromSystem(Sav2_SysInfo_get(save));
    Sav2_SysInfo_RTC_init(Sav2_SysInfo_RTC_get(save));

    struct UnkSaveStruct_020286F8 *unk_save = FUN_0202881C(save);
    u32 rand = MTRandom();

    FUN_02028788(unk_save, 1, rand);
    FUN_0206007C(save);

    struct PlayerData *player_data = Sav2_PlayerData_GetProfileAddr(save);
    u32 rand2 = MTRandom();

    if (param2 != 0) {
        PlayerProfile_SetTrainerID(player_data, rand2);
    }

    u32 gender = PlayerProfile_GetTrainerGender(player_data);
    u32 avatar = FUN_02053678(rand2, gender, 0);
    avatar = avatar << 0x18;
    avatar = avatar >> 0x18;

    PlayerProfile_SetAvatar(player_data, avatar);

    FUN_02024ECC(save);
    FUN_020250C4(save, heap_id, &MOD52_021D76F8, 0x76);
}
