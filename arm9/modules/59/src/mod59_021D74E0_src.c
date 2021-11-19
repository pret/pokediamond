#include "global.h"
#include "player_data.h"
#include "overlay_manager.h"
#include "mod59_021D74E0.h"
#include "heap.h"
#include "game_init.h"
#include "GX_layers.h"
#include "unk_02024E64.h"
#include "bg_window.h"
#include "render_window.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "text.h"
#include "script_buffers.h"
#include "module_52.h"

extern void *FUN_02077A84(u32 heap_id, u32 param1, u32 param2, u32 param3, struct Options *options);

extern void FUN_0200E3A0(PMLCDTarget, int);

//todo move with the other rodata
extern struct GraphicsBanks MOD59_021D9F18;
extern struct GraphicsModes MOD59_021D9DCC;
extern struct BgTemplate MOD59_021D9EA0;
extern struct BgTemplate MOD59_021D9EBC;

extern void MOD59_021D8058(MOD59_OverlayData *data);
extern u32 MOD59_021D8920(MOD59_OverlayData *data);

extern void FUN_0200E1D0(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 heap_id);
extern u32 FUN_0200E308(void);

extern u32 FUN_020142EC(u32 param0, u32 param1, u32 param2, u32 heap_id);

extern void FUN_02077AC4(void *param0);

extern void FUN_020143D0(u32 param0);
extern u32 FUN_02014590(u32 heap_id);
extern void FUN_020145A8(u32 param0);

FS_EXTERN_OVERLAY(MODULE_52);

THUMB_FUNC BOOL MOD59_Init(struct UnkStruct_02006234 *param0)
{
    CreateHeap(3, 0x52, 1 << 18);
    MOD59_OverlayData *data = (MOD59_OverlayData *) OverlayManager_CreateAndGetData(param0, sizeof(MOD59_OverlayData), 0x52);
    (void)memset((void *)data, 0, sizeof(MOD59_OverlayData));

    data->heap_id = 0x52;
    s32 *field18 = OverlayManager_GetField18(param0);
    data->sav2 = (struct SaveBlock2 *)field18[2]; //?
    data->options = Sav2_PlayerData_GetOptionsAddr(data->sav2);
    data->unk10 = data->unk0C = 0;
    data->unk14 = NULL;
    data->playerStruct = (struct MOD59_UnkPlayerStruct *)FUN_02077A84(0x52, 0, 0, 7, data->options);
    data->rivalStruct = (struct MOD59_UnkPlayerStruct *)FUN_02077A84(0x52, 3, 0, 7, data->options);
    data->unk88 = 0;
    data->unk89 = 0;
    data->unk8A = 0;
    data->unk8B = 0;
    data->unk90 = 0;
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

            MOD59_SetupBg(data);
            MOD59_SetupMsg(data);
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

            if (data->unk14 == NULL)
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

            MOD59_DestroyMsg(data);
            MOD59_DestroyBg(data);
            MOD59_021D7A5C(data);

            Main_SetVBlankIntrCB(NULL, NULL);

            ret = TRUE;
            break;

        case 3:
            if (FUN_0200E308() != 1)
            {
                break;
            }

            MOD59_DestroyMsg(data);
            MOD59_DestroyBg(data);
            MOD59_021D7A5C(data);

            Main_SetVBlankIntrCB(NULL, NULL);

            *param1 = 4;

            break;

        case 4:
            if (OverlayManager_Run(data->unk14) != TRUE)
            {
                break;
            }

            OverlayManager_delete(data->unk14);
            data->unk14 = NULL;

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
    DoScheduledBgGpuUpdates(data->bgConfig);
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

THUMB_FUNC void MOD59_SetupBg(MOD59_OverlayData *data)
{
    struct GraphicsBanks graphicsBanks = MOD59_021D9F18;
    GX_SetBanks(&graphicsBanks);
    data->bgConfig = BgConfig_Alloc(data->heap_id);

    struct GraphicsModes graphicsModes = MOD59_021D9DCC;
    SetBothScreensModesAndDisable(&graphicsModes);

    struct BgTemplate bgTemplateMain = MOD59_021D9EA0;
    bgTemplateMain.screenBase = 15;
    bgTemplateMain.charBase = 6;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_0, &bgTemplateMain, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_0);

    bgTemplateMain.screenBase = 14;
    bgTemplateMain.charBase = 5;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_1, &bgTemplateMain, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_1);

    bgTemplateMain.screenBase = 13;
    bgTemplateMain.charBase = 4;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_2, &bgTemplateMain, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_2);

    bgTemplateMain.screenBase = 12;
    bgTemplateMain.charBase = 3;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_3, &bgTemplateMain, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_3);

    FUN_0200CD68(data->bgConfig, 0, 994, 4, 0, data->heap_id);
    FUN_0200CB00(data->bgConfig, 0, 985, 3, 0, data->heap_id);
    FUN_02002ED0(GF_BG_LYR_MAIN_0, 160, data->heap_id);
    FUN_02002EEC(GF_BG_LYR_MAIN_0, 192, data->heap_id);

    struct BgTemplate bgTemplateSub = MOD59_021D9EBC;
    bgTemplateSub.screenBase = 15;
    bgTemplateSub.charBase = 6;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_0, &bgTemplateSub, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);

    bgTemplateSub.screenBase = 14;
    bgTemplateSub.charBase = 5;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_1, &bgTemplateSub, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_1);

    bgTemplateSub.screenBase = 13;
    bgTemplateSub.charBase = 4;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_2, &bgTemplateSub, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_2);

    bgTemplateSub.screenBase = 12;
    bgTemplateSub.charBase = 3;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_3, &bgTemplateSub, 0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_3);

    ToggleBgLayer(GF_BG_LYR_MAIN_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GX_LAYER_TOGGLE_OFF);

    ToggleBgLayer(GF_BG_LYR_SUB_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GX_LAYER_TOGGLE_OFF);

    MOD59_021D8058(data);
    data->unk78 = 0;
}

THUMB_FUNC void MOD59_DestroyBg(MOD59_OverlayData *data)
{
    ToggleBgLayer(GF_BG_LYR_MAIN_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GX_LAYER_TOGGLE_OFF);

    ToggleBgLayer(GF_BG_LYR_SUB_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GX_LAYER_TOGGLE_OFF);

    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_0);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_1);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_2);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_3);

    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_0);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_1);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_2);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_3);

    FreeToHeap(data->bgConfig);
}

THUMB_FUNC void MOD59_SetupMsg(MOD59_OverlayData *data)
{
    data->msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, NARC_msg_narc_0341_bin, data->heap_id);

    FUN_0201BD5C();

    data->unk60 = FUN_020142EC(0, 0, 6, data->heap_id);

    data->strBufs = ScrStrBufs_new(data->heap_id);

    data->unk50 = 0;
    data->unk54 = 0;
    data->unk2C = 0;
}

THUMB_FUNC void MOD59_DestroyMsg(MOD59_OverlayData *data)
{
    ScrStrBufs_delete(data->strBufs);
    FUN_020143D0(data->unk60);
    DestroyMsgData(data->msgData);
}

THUMB_FUNC void MOD59_021D7A4C(MOD59_OverlayData *data) //MOD59_Setup... something?
{
    data->unk68 = FUN_02014590(data->heap_id);
}

THUMB_FUNC void MOD59_021D7A5C(MOD59_OverlayData *data) //MOD59_Destroy... something?
{
    FUN_020145A8(data->unk68);
}
