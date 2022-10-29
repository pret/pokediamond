#include "global.h"
#include "GX_layers.h"
#include "bg_window.h"
#include "constants/sndseq.h"
#include "game_init.h"
#include "heap.h"
#include "mod59_021D74E0.h"
#include "module_52.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "overlay_manager.h"
#include "player_data.h"
#include "render_text.h"
#include "render_window.h"
#include "script_buffers.h"
#include "text.h"
#include "unk_020051F4.h"
#include "unk_02024E64.h"
#include "list_menu_items.h"
#include "gf_gfx_loader.h"
#include "demo/intro/intro.naix"
#include "pokemon.h"

extern void *FUN_02077A84(u32 heap_id, u32 param1, u32 param2, u32 param3, struct Options *options);

extern void FUN_0200E3A0(PMLCDTarget, int);

//todo move with the other rodata
extern struct GraphicsBanks MOD59_021D9F18;
extern struct GraphicsModes MOD59_021D9DCC;
extern struct BgTemplate MOD59_021D9EA0;
extern struct BgTemplate MOD59_021D9EBC;

extern struct WindowTemplate MOD59_021D9DB8;

extern const struct WindowTemplate MOD59_021D9DA8;
extern const struct MOD59_ListStruct021D9E0C MOD59_021D9E0C;
extern const struct WindowTemplate MOD59_021D9DB0;
extern const struct MOD59_ListStruct021D9E0C MOD59_021D9E58;
extern const struct WindowTemplate MOD59_021D9DA0;
extern const struct MOD59_ListStruct021D9E0C MOD59_021D9F40;
extern const struct MOD59_ListStruct021D9E0C MOD59_021D9F68;
extern const struct ListMenuTemplate MOD59_021D9EF8;

extern const struct MOD59_WindowTemplateGroup MOD59_021D9D90;

extern const struct MOD59_GraphicsPaletteMap021D9F90 MOD59_021D9F90;

extern const struct MOD59_UnkStruct021D9E30 MOD59_021D9E30;

extern const u8 MOD59_021D9FE8[0x64];
extern const u16 MOD59_021D9ED8[0x10];

extern u32 MOD59_021D9E1C[5];

extern u32 MOD59_021D8920(MOD59_OverlayData *data);

extern void FUN_0200E1D0(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 heap_id);
extern u32 FUN_0200E308(void);

extern u32 FUN_020142EC(u32 param0, u32 param1, u32 param2, u32 heap_id);

extern void FUN_02077AC4(void *param0);

extern void FUN_020143D0(u32 param0);
extern u32 FUN_02014590(u32 heap_id);
extern void FUN_020145A8(u32 param0);

extern u32 *FUN_0201244C(u16 param0, u16 param1, u32 heap_id);
extern u32 *FUN_02012470(u16 param0, u16 param1, u32 heap_id);

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

THUMB_FUNC BOOL MOD59_021D7A68(MOD59_OverlayData *data, u32 param1, u32 param2)
{
    BOOL var0;
    s32 var1;
    BOOL ret = FALSE;
    switch (param1)
    {
        case 0:
        case 3:
        default:
            var1 = 1;
            var0 = FALSE;
            break;
        case 1:
            var1 = 2;
            var0 = FALSE;
            break;
        case 2:
            var1 = 4;
            var0 = FALSE;
            break;
        case 4:
            var1 = 1;
            var0 = TRUE;
            break;
        case 5:
            var1 = 2;
            var0 = TRUE;
            break;
        case 6:
            var1 = 4;
            var0 = TRUE;
            break;
    }
    switch(data->unk78)
    {
        case 0:
            if (param2 == 0)
            {
                data->unk7C = 0;
                data->unk80 = 16;
                data->unk78 = 1;
                if (!var0)
                {
                    G2x_SetBlendAlpha_(&reg_G2_BLEND, var1, 14, data->unk7C, data->unk80);
                }
                else
                {
                    G2x_SetBlendAlpha_(&reg_G2S_DB_BLEND, var1, 14, data->unk7C, data->unk80);
                }
                ToggleBgLayer((u8)param1, GX_LAYER_TOGGLE_ON);
            }
            else
            {
                data->unk7C = 16;
                data->unk80 = 0;
                data->unk78 = 2;
            }
            break;
        case 1:
            if (data->unk80 != 0)
            {
                data->unk7C++;
                data->unk80--;
                if (!var0)
                {
                    G2x_SetBlendAlpha_(&reg_G2_BLEND, var1, 14, data->unk7C, data->unk80);
                }
                else
                {
                    G2x_SetBlendAlpha_(&reg_G2S_DB_BLEND, var1, 14, data->unk7C, data->unk80);
                }
            }
            else
            {
                data->unk78 = 3;
            }
            break;
        case 2:
            if (data->unk7C != 0)
            {
                data->unk7C--;
                data->unk80++;
                if (!var0)
                {
                    G2x_SetBlendAlpha_(&reg_G2_BLEND, var1, 14, data->unk7C, data->unk80);
                }
                else
                {
                    G2x_SetBlendAlpha_(&reg_G2S_DB_BLEND, var1, 14, data->unk7C, data->unk80);
                }
            }
            else
            {
                data->unk78 = 3;
                ToggleBgLayer((u8)param1, GX_LAYER_TOGGLE_OFF);
            }
            break;
        case 3:
            reg_G2_BLDCNT = 0;
            reg_G2S_DB_BLDCNT = 0;
            data->unk78 = 0;
            ret = TRUE;
            break;
    }
    return ret;
}

THUMB_FUNC BOOL MOD59_021D7BEC(MOD59_OverlayData *data, s32 param1)
{
    if (data->unk90 < param1)
    {
        data->unk90++;
        return FALSE;
    }
    else
    {
        data->unk90 = 0;
        return TRUE;
    }
}

THUMB_FUNC void MOD59_TilemapChangePalette(MOD59_OverlayData *data, u32 layer, u32 paletteNum)
{
    //TODO: messy hack to trick compiler, fix
    BgTilemapRectChangePalette(data->bgConfig, layer & 0xFF, 0, 0, 32, 24, paletteNum);
    BgCommitTilemapBufferToVram(data->bgConfig, (u8)layer);
}

THUMB_FUNC BOOL MOD59_021D7C44(MOD59_OverlayData *data, u32 msgNo, u32 param2)
{
    BOOL ret = FALSE;
    switch(data->unk50)
    {
        case 0:
            AddWindow(data->bgConfig, &data->window, &MOD59_021D9DB8);
            FillWindowPixelRect(&data->window, 15, 0, 0, 216, 32);
            DrawFrameAndWindow2(&data->window, FALSE, 994, 4);

            TextFlags_SetCanABSpeedUpPrint(TRUE);
            FUN_02002B7C(0);

            struct String* string = String_ctor(1024, data->heap_id);
            data->string = String_ctor(1024, data->heap_id);
            ReadMsgDataIntoString(data->msgData, msgNo, string);
            BufferString(data->strBufs, 0, data->playerStruct->name, data->unk84, 1, 2);
            BufferString(data->strBufs, 1, data->rivalStruct->name, 0, 1, 2);
            StringExpandPlaceholders(data->strBufs, data->string, string);
            String_dtor(string);

            u32 delay = Options_GetTextFrameDelay(data->options);
            data->minTextSpacing = AddTextPrinterParameterized(&data->window, 1, data->string, 0, 0, delay, NULL);
            data->unk50 = 1;
            break;
        case 1:
            if (FUN_0201BD70((u8)data->minTextSpacing))
            {
                break;
            }
            String_dtor(data->string);
            data->unk50 = 2;
            break;
        case 2:
            if (param2 != 0 || (gMain.newKeys & 1) == 1)
            {
                RemoveWindow(&data->window);
                data->unk50 = 0;
                ret = TRUE;
                break;
            }
    }
    return ret;
}

THUMB_FUNC void MOD59_021D7D68(struct ListMenu *list, s32 index, u8 onInit)
{
    if (onInit == 0)
    {
        PlaySE(SEQ_SE_DP_SELECT);
    }
}

THUMB_FUNC BOOL MOD59_021D7D7C(MOD59_OverlayData *data, u32 param1, u32 param2, u32 param3)
{
    BOOL ret = FALSE;
    const struct WindowTemplate *windowTemplate;
    const struct MOD59_ListStruct021D9E0C *listStruct;
    s32 i; // must be defined here to prevent a regswap
    s32 menuItemsCount = 0;
    switch (data->unk2C)
    {
        case 0:
            switch (param1)
            {
                default:
                case 0:
                    windowTemplate = &MOD59_021D9DA8;
                    listStruct = &MOD59_021D9E0C;
                    menuItemsCount = 2;
                    break;
                case 1:
                    windowTemplate = &MOD59_021D9DB0;
                    listStruct = &MOD59_021D9E58;
                    menuItemsCount = 3;
                    break;
                case 2:
                    windowTemplate = &MOD59_021D9DA0;
                    if ((u8)gGameVersion == VERSION_DIAMOND)
                    {
                        listStruct = &MOD59_021D9F40;
                        menuItemsCount = 5;
                    }
                    else
                    {
                        listStruct = &MOD59_021D9F68;
                        menuItemsCount = 5;
                    }
                    break;
            }
            AddWindow(data->bgConfig, &data->window2, windowTemplate);
            data->listMenuItem = ListMenuItems_ctor(menuItemsCount, data->heap_id);
            for (i = 0; i < menuItemsCount; i++)
            {
                ListMenuItems_AppendFromMsgData(data->listMenuItem, data->msgData, listStruct[i].msgNo, listStruct[i].val);
            }
            struct ListMenuTemplate template = MOD59_021D9EF8;
            template.items = data->listMenuItem;
            template.totalItems = (u16)menuItemsCount;
            template.maxShowed = (u16)menuItemsCount;
            template.moveCursorFunc = MOD59_021D7D68;
            template.window = &data->window2;
            data->listMenu = ListMenuInit(&template, 0, 0, (u8)data->heap_id);
            DrawFrameAndWindow1(template.window, TRUE, 985, 3);
            CopyWindowToVram(&data->window2);
            data->unk2C = 1;
            break;
        case 1:
            data->listMenuInput = ListMenu_ProcessInput(data->listMenu);
            if(data->listMenuInput == ~0 || (data->listMenuInput == (~0 - 1) && param2 == 1))
            {
                break;
            }
            ClearFrameAndWindow1(&data->window2, FALSE);
            RemoveWindow(&data->window2);
            DestroyListMenu(data->listMenu, 0, 0);
            ListMenuItems_dtor(data->listMenuItem);
            PlaySE(SEQ_SE_DP_SELECT);
            data->unk2C = 0;
            ret = TRUE;
    }
    return ret;
}

THUMB_FUNC BOOL MOD59_021D7ECC(MOD59_OverlayData *data, u32 msgNo, u32 param2, u32 tilemapTop, u32 height)
{
    BOOL ret = 0;
    switch (data->unk54)
    {
        case 0:
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GX_LAYER_TOGGLE_OFF);
            data->string = String_ctor(1024, data->heap_id);
            ReadMsgDataIntoString(data->msgData, msgNo, data->string);
            struct WindowTemplate template;
            if (param2 == 1)
            {
                template = MOD59_021D9D90.template2;
                u32 count = FUN_02002F90(data->string);
                template.tilemapTop = 12 - count;
                template.height = count * 2;
                AddWindow(data->bgConfig, &data->window, &template);
                FillWindowPixelRect(&data->window, 0, 0, 0, 192, 192);
                AddTextPrinterParameterized2(&data->window, 0, data->string, 0, 0, 0, MakeFontColor(1, 2, 0), NULL);
            }
            else
            {
                template = MOD59_021D9D90.template1;
                template.tilemapTop = tilemapTop;
                template.height = height;
                AddWindow(data->bgConfig, &data->window, &template);
                FillWindowPixelRect(&data->window, 0, 0, 0, 192, 192);
                AddTextPrinterParameterized2(&data->window, 0, data->string, 0, 0, 0, MakeFontColor(15, 2, 0), NULL);
            }
            String_dtor(data->string);
            data->unk54 = 1;
            break;
        case 1:
            CopyWindowToVram(&data->window);
            data->unk54 = 2;
            break;
        case 2:
            if (MOD59_021D7A68(data, 0, 0) == TRUE)
            {
                data->unk54 = 3;
            }
            break;
        case 3:
            if((gMain.newKeys & 1) != 1 && (gMain.newKeys & 2) != 2)
            {
                break;
            }
            PlaySE(SEQ_SE_DP_SELECT);
            data->unk54 = 4;
            break;
        case 4:
            if (MOD59_021D7A68(data, 0, 1) == TRUE)
            {
                data->unk54 = 5;
            }
            break;
        case 5:
            RemoveWindow(&data->window);
            BgClearTilemapBufferAndCommit(data->bgConfig, 0);
            data->unk54 = 0;
            ret = TRUE;
    }
    return ret;
}

THUMB_FUNC void MOD59_021D8058(MOD59_OverlayData *data)
{
    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO, NARC_intro_narc_0000_NCGR, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heap_id);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, data->heap_id);
    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO, NARC_intro_narc_0023_NCGR, data->bgConfig, GF_BG_LYR_SUB_3, 0, 0, FALSE, data->heap_id);

    u32 pal1;
    u32 pal2;
    if ((u8)gGameVersion == VERSION_DIAMOND)
    {
        pal1 = NARC_intro_narc_0001_NCLR;
        pal2 = NARC_intro_narc_0024_NCLR;
    }
    else
    {
        pal1 = NARC_intro_narc_0002_NCLR;
        pal2 = NARC_intro_narc_0025_NCLR;
    }
    GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO, pal1, GF_BG_LYR_MAIN_0, 0, 0x60, data->heap_id);
    GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO, pal2, GF_BG_LYR_SUB_0, 0, 0xa0, data->heap_id);
    MOD59_021D80FC(data);
    MOD59_021D8140(data);
    MOD59_021D8234(data);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, 0);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, 0);
}

THUMB_FUNC void MOD59_021D80FC(MOD59_OverlayData *data)
{
#ifdef __MWERKS__
    u32 arr[5];
    arr = MOD59_021D9E1C; // required for matching? this shouldn't be valid
#else
    u32 arr[5] = {};
    for (int i = 0; i < 5; i++)
    {
        arr[i] = MOD59_021D9E1C[i];
    }
#endif
    if (data->unk88 >= 5)
    {
        return;
    }
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO, arr[data->unk88], data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heap_id);
}

THUMB_FUNC void MOD59_021D8140(MOD59_OverlayData *data)
{
    struct MOD59_GraphicsPaletteMap021D9F90 graphicsPaletteMap = MOD59_021D9F90;
    if (data->unk89 != 0 && data->unk89 < 12)
    {
        GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO, graphicsPaletteMap.map[data->unk89].charNum, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heap_id);
        GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO, graphicsPaletteMap.map[data->unk89].palNum, GF_BG_LYR_MAIN_0, 0xE0, 0x20, data->heap_id);
        GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO, NARC_intro_narc_0022_NSCR, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heap_id);
        MOD59_TilemapChangePalette(data, GF_BG_LYR_MAIN_1, 7);
    }
    if (data->unk8A != 0 && data->unk8A < 12)
    {
        GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO, graphicsPaletteMap.map[data->unk8A].charNum, data->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, FALSE, data->heap_id);
        GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO, graphicsPaletteMap.map[data->unk8A].palNum, GF_BG_LYR_MAIN_0, 0x100, 0x20, data->heap_id);
        GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO, NARC_intro_narc_0022_NSCR, data->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, FALSE, data->heap_id);
        MOD59_TilemapChangePalette(data, GF_BG_LYR_MAIN_2, 8);
    }
}

THUMB_FUNC void MOD59_021D8234(MOD59_OverlayData *data)
{
    struct MOD59_UnkStruct021D9E30 scrnData = MOD59_021D9E30;
    if (data->unk8B >= 5)
    {
        return;
    }
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO, scrnData.scrnIds[data->unk8B], data->bgConfig, GF_BG_LYR_SUB_3, 0, 0, FALSE, data->heap_id);
    if (data->unk8B == 1)
    {
        MOD59_TilemapChangePalette(data, GF_BG_LYR_SUB_3, 3);
    }
    else if (data->unk8B == 2)
    {
        MOD59_TilemapChangePalette(data, GF_BG_LYR_SUB_3, 2);
    }
}

#ifdef NONMATCHING
THUMB_FUNC void MOD59_021D82A0(MOD59_OverlayData *data)
{
    struct SomeDrawPokemonStruct drawStruct;
    FUN_02068C00(&drawStruct, SPECIES_MUNCHLAX, MON_MALE, 2, FALSE, 0, 0);
    u16 *src = (u16 *)AllocFromHeap(data->heap_id, 0x64 * sizeof(u16));
    for (s32 i = 0; i < 0x64; i++)
    {
        src[i] = MOD59_021D9FE8[i] + 1;
    }
    u32 *charData = FUN_0201244C(drawStruct.unk0, drawStruct.unk2, data->heap_id);
    u32 *plttData = FUN_02012470(drawStruct.unk0, drawStruct.unk4, data->heap_id);

    FillBgTilemapRect(data->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, 9);
    LoadRectToBgTilemapRect(data->bgConfig, GF_BG_LYR_MAIN_2, src, 11, 11, 10, 10);
    MOD59_TilemapChangePalette(data, GF_BG_LYR_MAIN_2, 9);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_2, 32, 0, data->heap_id);
    BG_LoadCharTilesData(data->bgConfig, GF_BG_LYR_MAIN_2, charData, 0xc80, 1);
    BG_LoadPlttData(GF_BG_LYR_MAIN_2, plttData, 32, 0x100); //r2 and r3 regswap
    BG_LoadPlttData(GF_BG_LYR_MAIN_2, MOD59_021D9ED8, 32, 0x120);

    FillBgTilemapRect(data->bgConfig, GF_BG_LYR_SUB_1, 0, 0, 0, 32, 24, 10);
    LoadRectToBgTilemapRect(data->bgConfig, GF_BG_LYR_SUB_1, src, 11, 7, 10, 10);
    MOD59_TilemapChangePalette(data, GF_BG_LYR_SUB_1, 10);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_1, 32, 0, data->heap_id);
    BG_LoadCharTilesData(data->bgConfig, GF_BG_LYR_SUB_1, charData, 0xc80, 1);
    BG_LoadPlttData(GF_BG_LYR_SUB_1, plttData, 32, 0x140);
    BG_LoadPlttData(GF_BG_LYR_SUB_1, MOD59_021D9ED8, 32, 0x140);
    FreeToHeap(plttData);
    FreeToHeap(charData);
    FreeToHeap(src);
}
#else
THUMB_FUNC asm void MOD59_021D82A0(MOD59_OverlayData *data)
{
    //clang-tidy off
    push {r3, r4, r5, r6, r7, lr}
    sub sp, #0x20
    mov r2, #0
    str r2, [sp]
    str r2, [sp, #4]
    add r5, r0, #0
    ldr r1, =0x000001BE
    str r2, [sp, #8]
    add r0, sp, #0x10
    mov r3, #2
    bl FUN_02068C00
    ldr r0, [r5, #0]
    mov r1, #0xc8
    bl AllocFromHeap
    add r7, r0, #0
    ldr r2, =MOD59_021D9FE8
    mov r1, #0
    add r3, r7, #0
_021D82C8:
    ldrb r0, [r2]
    add r1, r1, #1
    add r2, r2, #1
    add r0, r0, #1
    strh r0, [r3]
    add r3, r3, #2
    cmp r1, #0x64
    blt _021D82C8
    add r1, sp, #0x10
    ldrh r0, [r1]
    ldrh r1, [r1, #2]
    ldr r2, [r5, #0]
    bl FUN_0201244C
    add r1, sp, #0x10
    add r4, r0, #0
    ldrh r0, [r1]
    ldrh r1, [r1, #4]
    ldr r2, [r5, #0]
    bl FUN_02012470
    mov r2, #0
    add r6, r0, #0
    str r2, [sp]
    mov r0, #0x20
    str r0, [sp, #4]
    mov r0, #0x18
    str r0, [sp, #8]
    mov r0, #9
    str r0, [sp, #0xc]
    ldr r0, [r5, #0x18]
    mov r1, #2
    add r3, r2, #0
    bl FillBgTilemapRect
    mov r3, #0xb
    str r3, [sp]
    mov r0, #0xa
    str r0, [sp, #4]
    str r0, [sp, #8]
    ldr r0, [r5, #0x18]
    mov r1, #2
    add r2, r7, #0
    bl LoadRectToBgTilemapRect
    add r0, r5, #0
    mov r1, #2
    mov r2, #9
    bl MOD59_TilemapChangePalette
    ldr r3, [r5, #0]
    mov r0, #2
    mov r1, #0x20
    mov r2, #0
    bl BG_ClearCharDataRange
    mov r0, #1
    str r0, [sp]
    mov r3, #0x32
    ldr r0, [r5, #0x18]
    mov r1, #2
    add r2, r4, #0
    lsl r3, r3, #6
    bl BG_LoadCharTilesData
    mov r3, #0x20
    add r2, r3, #0
    mov r0, #2
    add r1, r6, #0
    add r3, #0xe0
    bl BG_LoadPlttData
    mov r3, #0x12
    ldr r1, =MOD59_021D9ED8
    mov r0, #2
    mov r2, #0x20
    lsl r3, r3, #4
    bl BG_LoadPlttData
    mov r2, #0
    str r2, [sp]
    mov r0, #0x20
    str r0, [sp, #4]
    mov r0, #0x18
    str r0, [sp, #8]
    mov r0, #0xa
    str r0, [sp, #0xc]
    ldr r0, [r5, #0x18]
    mov r1, #5
    add r3, r2, #0
    bl FillBgTilemapRect
    mov r0, #7
    str r0, [sp]
    mov r0, #0xa
    str r0, [sp, #4]
    str r0, [sp, #8]
    ldr r0, [r5, #0x18]
    mov r1, #5
    add r2, r7, #0
    mov r3, #0xb
    bl LoadRectToBgTilemapRect
    add r0, r5, #0
    mov r1, #5
    mov r2, #0xa
    bl MOD59_TilemapChangePalette
    ldr r3, [r5, #0]
    mov r0, #5
    mov r1, #0x20
    mov r2, #0
    bl BG_ClearCharDataRange
    mov r0, #1
    str r0, [sp]
    mov r3, #0x32
    ldr r0, [r5, #0x18]
    mov r1, #5
    add r2, r4, #0
    lsl r3, r3, #6
    bl BG_LoadCharTilesData
    mov r0, #5
    add r1, r6, #0
    mov r2, #0x20
    lsl r3, r0, #6
    bl BG_LoadPlttData
    mov r0, #5
    ldr r1, =MOD59_021D9ED8
    mov r2, #0x20
    lsl r3, r0, #6
    bl BG_LoadPlttData
    add r0, r6, #0
    bl FreeToHeap
    add r0, r4, #0
    bl FreeToHeap
    add r0, r7, #0
    bl FreeToHeap
    add sp, #0x20
    pop {r3, r4, r5, r6, r7, pc}
}
#endif

THUMB_FUNC void MOD59_021D83F8(MOD59_OverlayData *data)
{
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO, NARC_intro_narc_0038_NSCR, data->bgConfig, GF_BG_LYR_SUB_2, 0, 0, FALSE, data->heap_id);
    MOD59_TilemapChangePalette(data, GF_BG_LYR_SUB_2, 9);
    GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO, NARC_intro_narc_0039_NCLR, GF_BG_LYR_SUB_0, 0xe0, 0x60, data->heap_id);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_2, 0x20, 0, data->heap_id);
    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO, NARC_intro_narc_0030_NCGR, data->bgConfig, GF_BG_LYR_SUB_2, 0x20, 0, FALSE, data->heap_id);
}

THUMB_FUNC BOOL MOD59_021D8460(MOD59_OverlayData *data, u32 layer, u32 param2)
{
    BOOL ret = FALSE;
    if (param2 == 0)
    {
        fx32 xPos = Bg_GetXpos(data->bgConfig, layer);
        if (xPos != 0)
        {
            if (xPos > 0)
            {
                BgSetPosTextAndCommit(data->bgConfig, (u8)layer, 2, 4);
            }
            else
            {
                BgSetPosTextAndCommit(data->bgConfig, (u8)layer, 1, 4);
            }
        }
        else
        {
            ret = TRUE;
        }
    }
    else if (param2 == 1)
    {
        fx32 xPos = Bg_GetXpos(data->bgConfig, layer);
        if (xPos != -48)
        {
            BgSetPosTextAndCommit(data->bgConfig, (u8)layer, 2, 4);
        }
        else
        {
            ret = TRUE;
        }
    }
    else if (param2 == 2)
    {
        fx32 xPos = Bg_GetXpos(data->bgConfig, layer);
        if (xPos != 0)
        {
            BgSetPosTextAndCommit(data->bgConfig, (u8)layer, 1, 4);
        }
        else
        {
            ret = TRUE;
        }
    }
    return ret;
}

THUMB_FUNC void MOD59_021D84E8(MOD59_OverlayData *data)
{
    data->unk8C = 0;
    data->unk8D = 0;
    data->unk8E = 0;
    data->unk8F = 0;
}
