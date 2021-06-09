#include "global.h"
#include "player_data.h"
#include "overlay_manager.h"
#include "mod59_021D74E0.h"
#include "heap.h"
#include "game_init.h"
#include "GX_layers.h"
#include "unk_02024E64.h"
#include "unk_02016B94.h"
#include "module_52.h"

extern void *FUN_02077A84(u32 heap_id, u32 param1, u32 param2, u32 param3, struct Options *options);

extern void FUN_0200E3A0(PMLCDTarget, int);

extern void MOD59_021D778C(MOD59_OverlayData *data);
extern void MOD59_021D79F8(MOD59_OverlayData *data);
extern void MOD59_021D7A34(MOD59_OverlayData *data);
extern void MOD59_021D796C(MOD59_OverlayData *data);
extern void MOD59_021D7A4C(MOD59_OverlayData *data);
extern void MOD59_021D7A5C(MOD59_OverlayData *data);
extern u32 MOD59_021D8920(MOD59_OverlayData *data);

extern void FUN_0200E1D0(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 heap_id);
extern u32 FUN_0200E308(void);

extern void FUN_02077AC4(void *param0);

FS_EXTERN_OVERLAY(MODULE_52);

THUMB_FUNC BOOL MOD59_Init(struct UnkStruct_02006234 *param0)
{
    CreateHeap(3, 0x52, 1 << 18);
    MOD59_OverlayData *data = (MOD59_OverlayData *) OverlayManager_CreateAndGetData(param0, sizeof(MOD59_OverlayData), 0x52);
    (void)memset((void *)data, 0, 0xb4);

    data->heap_id = 0x52;
    s32 *field18 = OverlayManager_GetField18(param0);
    data->sav2 = (struct SaveBlock2 *)field18[2]; //?
    data->options = Sav2_PlayerData_GetOptionsAddr(data->sav2);
    data->Unk10 = data->Unk0C = 0;
    data->Unk14 = NULL;
    data->playerStruct = (struct MOD59_UnkPlayerStruct *)FUN_02077A84(0x52, 0, 0, 7, data->options);
    data->rivalStruct = (struct MOD59_UnkPlayerStruct *)FUN_02077A84(0x52, 3, 0, 7, data->options);
    data->Unk88 = 0;
    data->Unk89 = 0;
    data->Unk8A = 0;
    data->Unk8B = 0;
    data->Unk90 = 0;
    return TRUE;
}

THUMB_FUNC BOOL MOD59_021D7564(struct UnkStruct_02006234 *param0, u32 *param1)
{
    MOD59_OverlayData *data = (MOD59_OverlayData *) OverlayManager_GetData(param0);
    BOOL ret = FALSE;

    switch (*param1)
    {
        case 0:
            FUN_0200E3A0(PM_LCD_TOP, 0);
            FUN_0200E3A0(PM_LCD_BOTTOM, 0);

            Main_SetVBlankIntrCB(NULL, NULL);

            FUN_02015F34(NULL, NULL);
            GX_DisableEngineALayers();
            GX_DisableEngineBLayers();

            reg_GX_DISPCNT = reg_GX_DISPCNT & 0xFFFFE0FF;
            reg_GXS_DB_DISPCNT = reg_GXS_DB_DISPCNT & 0xFFFFE0FF;

            SetKeyRepeatTimers(4, 8);

            MOD59_021D778C(data);
            MOD59_021D79F8(data);
            MOD59_021D7A4C(data);

            Main_SetVBlankIntrCB((void (*)(void *))MOD59_021D7724, data);

            GX_BothDispOn();

            *param1 = 1;

            break;

        case 1:
            if (MOD59_021D8920(data) == 1)
            {
                FUN_0200E1D0(0, 0, 0, 0, 6, 1, data->heap_id);
                *param1 = 2;
            }

            if (data->Unk14 == NULL)
            {
                break;
            }

            FUN_0200E1D0(0, 0, 0, 0, 6, 1, data->heap_id);
            *param1 = 3;

            break;

        case 2:
            if (FUN_0200E308() != 1)
            {
                break;
            }

            MOD59_021D7A34(data);
            MOD59_021D796C(data);
            MOD59_021D7A5C(data);

            Main_SetVBlankIntrCB(NULL, NULL);

            ret = TRUE;
            break;

        case 3:
            if (FUN_0200E308() != 1)
            {
                break;
            }

            MOD59_021D7A34(data);
            MOD59_021D796C(data);
            MOD59_021D7A5C(data);

            Main_SetVBlankIntrCB(NULL, NULL);

            *param1 = 4;

            break;

        case 4:
            if (OverlayManager_Run(data->Unk14) != TRUE)
            {
                break;
            }

            OverlayManager_delete(data->Unk14);
            data->Unk14 = NULL;

            *param1 = 5;

            break;

        case 5:
            *param1 = 0;

            break;
    }

    return ret;
}

THUMB_FUNC BOOL MOD59_021D76C0(struct UnkStruct_02006234 *param0)
{
    MOD59_OverlayData *data = (MOD59_OverlayData *) OverlayManager_GetData(param0);

    u32 heap_id = data->heap_id;
    PlayerName_StringToFlat(Sav2_PlayerData_GetProfileAddr(data->sav2), data->playerStruct->name);
    PlayerProfile_SetTrainerGender(Sav2_PlayerData_GetProfileAddr(data->sav2), data->playerStruct->gender);

    RivalsNameToU16Array(FUN_02024EB4(data->sav2), data->rivalStruct->name);

    FUN_02077AC4(data->playerStruct);
    FUN_02077AC4(data->rivalStruct);

    OverlayManager_FreeData(param0);
    DestroyHeap(heap_id);

    RegisterMainOverlay(FS_OVERLAY_ID(MODULE_52), &MOD52_021D76D8);

    return TRUE;
}

THUMB_FUNC void MOD59_021D7724(MOD59_OverlayData *data)
{
    FUN_0201AB60(data->Unk18);
}

THUMB_FUNC BOOL MOD59_021D7730(void)
{
    BOOL ret = FALSE;

    if (gMain.touchNew != 0 && gMain.touchX < 256 && gMain.touchY < 192)
    {
        s32 distanceFromXCentre = gMain.touchX < 128 ? (u16)(128 - gMain.touchX) : (u16)(gMain.touchX - 128);
        s32 distanceFromYCentre = gMain.touchY < 100 ? (u16)(100 - gMain.touchY) : (u16)(gMain.touchY - 100);

        s32 distanceXSquare = distanceFromXCentre * distanceFromXCentre;
        s32 distanceYSquare = distanceFromYCentre * distanceFromYCentre;

        if (distanceXSquare + distanceYSquare <= 256)
        {
            ret = TRUE;
        }
    }

    return ret;
}
