#include "global.h"
#include "mod59_TV.h"
#include "GX_layers.h"
#include "PAD_pad.h"
#include "constants/sndseq.h"
#include "demo/intro/intro_tv.naix"
#include "filesystem.h"
#include "font.h"
#include "game_init.h"
#include "gf_gfx_loader.h"
#include "heap.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0549.h"
#include "overlay_manager.h"
#include "text.h"
#include "unk_020040F4.h"

extern void sub_0200E3A0(PMLCDTarget, s32);

extern void BeginNormalPaletteFade(u32 pattern, u32 typeTop, u32 typeBottom, u16 colour, u32 duration, u32 framesPer, u32 heapId);
extern BOOL IsPaletteFadeFinished(void);

const struct WindowTemplate MOD59_021DA04C =
    {
        .bgId = GF_BG_LYR_MAIN_2,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 32,
        .height = 24,
        .paletteNum = 0x01,
        .baseTile = 1,
    };

const struct GraphicsModes MOD59_021DA054 =
    {
        .dispMode = GX_DISPMODE_GRAPHICS,
        .bgMode = GX_BGMODE_0,
        .subMode = GX_BGMODE_0,
        ._2d3dMode = GX_BG0_AS_2D,
    };

const struct BgTemplate MOD59_021DA080 =
    {
        .x = 0,
        .y = 0,
        .bufferSize = 2048,
        .baseTile = 0,

        .size = GF_BG_SCR_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x0000,
        .charBase = GX_BG_CHARBASE_0x18000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = GX_BG_AREAOVER_XLU,
        .unk17 = 0,
        .mosaic = FALSE
    };

const struct BgTemplate MOD59_021DA09C =
    {
        .x = 0,
        .y = 0,
        .bufferSize = 2048,
        .baseTile = 0,

        .size = GF_BG_SCR_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x0800,
        .charBase = GX_BG_CHARBASE_0x14000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = GX_BG_AREAOVER_XLU,
        .unk17 = 0,
        .mosaic = FALSE
    };

const struct BgTemplate MOD59_021DA064 =
    {
        .x = 0,
        .y = 0,
        .bufferSize = 2048,
        .baseTile = 0,

        .size = GF_BG_SCR_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x1000,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = GX_BG_AREAOVER_XLU,
        .unk17 = 0,
        .mosaic = FALSE
    };

const struct BgTemplate MOD59_021DA0B8 =
    {
        .x = 0,
        .y = 0,
        .bufferSize = 2048,
        .baseTile = 0,

        .size = GF_BG_SCR_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_256,
        .screenBase = GX_BG_SCRBASE_0x1800,
        .charBase = GX_BG_CHARBASE_0x20000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = GX_BG_AREAOVER_XLU,
        .unk17 = 0,
        .mosaic = FALSE
    };

const struct GraphicsBanks MOD59_021DA0D4 =
    {
        .bg = GX_VRAM_BG_256_AB,
        .bgextpltt = GX_VRAM_BGEXTPLTT_NONE,
        .subbg = GX_VRAM_SUB_BG_NONE,
        .subbgextpltt = GX_VRAM_SUB_BGEXTPLTT_NONE,
        .obj = GX_VRAM_OBJ_NONE,
        .objextpltt = GX_VRAM_OBJEXTPLTT_NONE,
        .subobj = GX_VRAM_SUB_OBJ_NONE,
        .subobjextpltt = GX_VRAM_SUB_OBJEXTPLTT_NONE,
        .tex = GX_VRAM_TEX_NONE,
        .texpltt = GX_VRAM_TEXPLTT_NONE
    };

BOOL MOD59_TVInit(struct OverlayManager *overlayManager, u32 *status)
{
#pragma unused(status)
    CreateHeap(3, 83, 0x40000);
    MOD59_TVOverlayData *data = (MOD59_TVOverlayData *)OverlayManager_CreateAndGetData(overlayManager, sizeof(MOD59_TVOverlayData), 0x53);
    (void)memset((void *)data, 0, sizeof(MOD59_TVOverlayData));
    data->heap_id = 0x53;
    data->unk24 = 0;
    return TRUE;
}

BOOL MOD59_TVMain(struct OverlayManager *overlayManager, u32 *status)
{
    MOD59_TVOverlayData *data = (MOD59_TVOverlayData *)OverlayManager_GetData(overlayManager);
    BOOL ret = FALSE;

    switch (*status)
    {
        case 0:
            sub_0200E3A0(PM_LCD_TOP, 0);
            sub_0200E3A0(PM_LCD_BOTTOM, 0);

            Main_SetVBlankIntrCB(NULL, NULL);
            Main_SetHBlankIntrCB(NULL, NULL);

            GX_DisableEngineALayers();
            GX_DisableEngineBLayers();

            GX_SetVisiblePlane(0);
            GXS_SetVisiblePlane(0);

            SetKeyRepeatTimers(4, 8);

            MOD59_TVSetupGraphics(data);
            MOD59_TVSetupMsg(data);

            Main_SetVBlankIntrCB((void (*)(void *))MOD59_TVDoGpuBgUpdate, data);

            GX_BothDispOn();

            data->unk24 = 60;

            *status = 1;
            break;

        case 1:
            if (data->unk24 != 0)
            {
                data->unk24--;
                break;
            }

            sub_0200414C(SEQ_TV_HOUSOU);
            sub_0200433C(4, SEQ_TV_HOUSOU, 1);

            data->unk24 = 90;

            *status = 2;
            break;

        case 2:
            if (data->unk24 != 0)
            {
                data->unk24--;
                break;
            }
            data->unk24 = 0; //??

            BeginNormalPaletteFade(0, 1, 1, GX_RGB_BLACK, 6, 1, data->heap_id);

            *status = 3;
            break;

        case 3:
            MOD59_021D9D78(data);

            if (IsPaletteFadeFinished() != TRUE)
            {
                break;
            }

            *status = 4;
            break;

        case 4:
            MOD59_021D9D78(data);

            if (MOD59_021D9C74(data, narc_0549_00000, 40, 48) != TRUE)
            {
                break;
            }

            BeginNormalPaletteFade(0, 0, 0, GX_RGB_BLACK, 6, 1, data->heap_id);

            *status = 5;
            break;

        case 5:
            MOD59_021D9D78(data);

            if (IsPaletteFadeFinished() != TRUE)
            {
                break;
            }

            MOD59_TVDestroyMsg(data);
            MOD59_TVDestroyGraphics(data);

            Main_SetVBlankIntrCB(NULL, NULL);

            ret = TRUE;
            break;
    }

    return ret;
}

BOOL MOD59_TVExit(struct OverlayManager *overlayManager, u32 *status)
{
#pragma unused (status)
    u32 heap_id = ((MOD59_TVOverlayData *)OverlayManager_GetData(overlayManager))->heap_id;
    OverlayManager_FreeData(overlayManager);
    DestroyHeap(heap_id);
    return TRUE;
}

void MOD59_TVDoGpuBgUpdate(MOD59_TVOverlayData *data)
{
    DoScheduledBgGpuUpdates(data->bgConfig);
}

void MOD59_TVSetupGraphics(MOD59_TVOverlayData *data)
{
    const struct GraphicsBanks banks = MOD59_021DA0D4; //sp #0x90
    GX_SetBanks(&banks);

    data->bgConfig = BgConfig_Alloc(data->heap_id);

    const struct GraphicsModes modes = MOD59_021DA054; //sp #0x80
    SetBothScreensModesAndDisable(&modes);

    const struct BgTemplate bgTemplateMain2 = MOD59_021DA080; //sp #0x64
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_2, &bgTemplateMain2, GF_BG_TYPE_TEXT);

    BG_ClearCharDataRange(GF_BG_LYR_MAIN_2, 0x20, 0, data->heap_id);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_2);

    const struct BgTemplate bgTemplateMain0 = MOD59_021DA09C; //sp #0x48
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_0, &bgTemplateMain0, GF_BG_TYPE_TEXT);

    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0001_NCGR, data->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, FALSE, data->heap_id);
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0004_NSCR, data->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, FALSE, data->heap_id);

    const struct BgTemplate bgTemplateMain1 = MOD59_021DA064; //sp #0x2C
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_1, &bgTemplateMain1, GF_BG_TYPE_TEXT);

    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0002_NCGR, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heap_id);
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0005_NSCR, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heap_id);

    const struct BgTemplate bgTemplateMain3 = MOD59_021DA0B8; //sp #0x10
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_3, &bgTemplateMain3, GF_BG_TYPE_TEXT);

    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0000_NCGR, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heap_id);
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0003_NSCR, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heap_id);

    GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0006_NCLR, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_0, 0, data->heap_id);

    LoadFontPal0(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_1, data->heap_id);

    BG_SetMaskColor(GF_BG_LYR_MAIN_0, 0);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, 0);

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2), 4, 12);
}

void MOD59_TVDestroyGraphics(MOD59_TVOverlayData *data)
{
    ToggleBgLayer(GF_BG_LYR_MAIN_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GX_LAYER_TOGGLE_OFF);

    reg_G2_BLDCNT = 0;

    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_3);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_1);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_0);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_2);
    FreeToHeap(data->bgConfig);
}

void MOD59_TVSetupMsg(MOD59_TVOverlayData *data)
{
    data->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0549_bin, data->heap_id);

    ResetAllTextPrinters();

    data->unk0C = 0;
}

void MOD59_TVDestroyMsg(MOD59_TVOverlayData *data)
{
    DestroyMsgData(data->msgData);
}

BOOL MOD59_021D9C74(MOD59_TVOverlayData *data, u32 msgNo, u32 param2, u32 param3)
{
    BOOL ret = FALSE;
    switch (data->unk0C)
    {
        case 0:
            ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_LAYER_TOGGLE_OFF);
            struct String *string = String_New(1024, data->heap_id);
            ReadMsgDataIntoString(data->msgData, msgNo, string);
            AddWindow(data->bgConfig, &data->window, &MOD59_021DA04C);
            FillWindowPixelRect(&data->window, 0, 0, 0, 256, 192);
            u32 unk0 = (u32)sub_02002F08(0, string, 0);

            unk0 = (256 - unk0 ) / 2;
            AddTextPrinterParameterized2(&data->window, 0, string, unk0, param3, 0, MakeFontColor(15, 2, 0), NULL);
            String_Delete(string);
            CopyWindowToVram(&data->window);
            ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_LAYER_TOGGLE_ON);
            data->unk24 = 240;
            data->unk0C = 1;
            break;

        case 1:
            if (data->unk24 != 0)
            {
                data->unk24--;
                break;
            }
            data->unk0C = 2;
            break;

        case 2:
            if((gSystem.newKeys & PAD_BUTTON_A) != 1 && (gSystem.newKeys & PAD_BUTTON_B) != 2)
            {
                break;
            }
            data->unk0C = 3;
            break;

        case 3:
            RemoveWindow(&data->window);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_2);
            data->unk0C = 0;
            ret = TRUE;
            break;
    }
    return ret;
}

void MOD59_021D9D78(MOD59_TVOverlayData *data)
{
    data->unk20 += 4;
    BgSetPosTextAndCommit(data->bgConfig, GF_BG_LYR_MAIN_1, BG_POS_OP_SET_Y, data->unk20 >> 4);
}
