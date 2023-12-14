#include "global.h"
#include "ov59_TV.h"
#include "gf_gfx_planes.h"
#include "PAD_pad.h"
#include "constants/rgb.h"
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

extern void BeginNormalPaletteFade(u32 pattern, u32 typeTop, u32 typeBottom, u16 colour, u32 duration, u32 framesPer, HeapID heapId);
extern BOOL IsPaletteFadeFinished(void);

const struct WindowTemplate ov59_021DA04C =
    {
        .bgId = GF_BG_LYR_MAIN_2,
        .left = 0,
        .top = 0,
        .width = 32,
        .height = 24,
        .palette = 1,
        .baseTile = 1,
    };

const struct GraphicsModes ov59_021DA054 =
    {
        .dispMode = GX_DISPMODE_GRAPHICS,
        .bgMode = GX_BGMODE_0,
        .subMode = GX_BGMODE_0,
        ._2d3dMode = GX_BG0_AS_2D,
    };

const struct BgTemplate ov59_021DA080 =
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
        .dummy = 0,
        .mosaic = FALSE
    };

const struct BgTemplate ov59_021DA09C =
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
        .dummy = 0,
        .mosaic = FALSE
    };

const struct BgTemplate ov59_021DA064 =
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
        .dummy = 0,
        .mosaic = FALSE
    };

const struct BgTemplate ov59_021DA0B8 =
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
        .dummy = 0,
        .mosaic = FALSE
    };

const struct GraphicsBanks ov59_021DA0D4 =
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

BOOL ov59_TVInit(struct OverlayManager *overlayManager, u32 *status)
{
#pragma unused(status)
    CreateHeap(3, HEAP_ID_INTRO_TV, 0x40000);
    ov59_TVOverlayData *data = (ov59_TVOverlayData *)OverlayManager_CreateAndGetData(overlayManager, sizeof(ov59_TVOverlayData), HEAP_ID_INTRO_TV);
    memset((void *)data, 0, sizeof(ov59_TVOverlayData));
    data->heapId = HEAP_ID_INTRO_TV;
    data->unk24 = 0;
    return TRUE;
}

BOOL ov59_TVMain(struct OverlayManager *overlayManager, u32 *status)
{
    ov59_TVOverlayData *data = (ov59_TVOverlayData *)OverlayManager_GetData(overlayManager);
    BOOL ret = FALSE;

    switch (*status)
    {
        case 0:
            sub_0200E3A0(PM_LCD_TOP, 0);
            sub_0200E3A0(PM_LCD_BOTTOM, 0);

            Main_SetVBlankIntrCB(NULL, NULL);
            Main_SetHBlankIntrCB(NULL, NULL);

            GfGfx_DisableEngineAPlanes();
            GfGfx_DisableEngineBPlanes();

            GX_SetVisiblePlane(0);
            GXS_SetVisiblePlane(0);

            SetKeyRepeatTimers(4, 8);

            ov59_TVSetupGraphics(data);
            ov59_TVSetupMsg(data);

            Main_SetVBlankIntrCB((void (*)(void *))ov59_TVDoGpuBgUpdate, data);

            GfGfx_BothDispOn();

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

            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);

            *status = 3;
            break;

        case 3:
            ov59_021D9D78(data);

            if (IsPaletteFadeFinished() != TRUE)
            {
                break;
            }

            *status = 4;
            break;

        case 4:
            ov59_021D9D78(data);

            if (ov59_021D9C74(data, narc_0549_00000, 40, 48) != TRUE)
            {
                break;
            }

            BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);

            *status = 5;
            break;

        case 5:
            ov59_021D9D78(data);

            if (IsPaletteFadeFinished() != TRUE)
            {
                break;
            }

            ov59_TVDestroyMsg(data);
            ov59_TVDestroyGraphics(data);

            Main_SetVBlankIntrCB(NULL, NULL);

            ret = TRUE;
            break;
    }

    return ret;
}

BOOL ov59_TVExit(struct OverlayManager *overlayManager, u32 *status)
{
#pragma unused (status)
    HeapID heapId = ((ov59_TVOverlayData *)OverlayManager_GetData(overlayManager))->heapId;
    OverlayManager_FreeData(overlayManager);
    DestroyHeap(heapId);
    return TRUE;
}

void ov59_TVDoGpuBgUpdate(ov59_TVOverlayData *data)
{
    DoScheduledBgGpuUpdates(data->bgConfig);
}

void ov59_TVSetupGraphics(ov59_TVOverlayData *data)
{
    const struct GraphicsBanks banks = ov59_021DA0D4; //sp #0x90
    GfGfx_SetBanks(&banks);

    data->bgConfig = BgConfig_Alloc(data->heapId);

    const struct GraphicsModes modes = ov59_021DA054; //sp #0x80
    SetBothScreensModesAndDisable(&modes);

    const struct BgTemplate bgTemplateMain2 = ov59_021DA080; //sp #0x64
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_2, &bgTemplateMain2, GF_BG_TYPE_TEXT);

    BG_ClearCharDataRange(GF_BG_LYR_MAIN_2, 0x20, 0, data->heapId);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_2);

    const struct BgTemplate bgTemplateMain0 = ov59_021DA09C; //sp #0x48
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_0, &bgTemplateMain0, GF_BG_TYPE_TEXT);

    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0001_NCGR, data->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, FALSE, data->heapId);
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0004_NSCR, data->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, FALSE, data->heapId);

    const struct BgTemplate bgTemplateMain1 = ov59_021DA064; //sp #0x2C
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_1, &bgTemplateMain1, GF_BG_TYPE_TEXT);

    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0002_NCGR, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heapId);
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0005_NSCR, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heapId);

    const struct BgTemplate bgTemplateMain3 = ov59_021DA0B8; //sp #0x10
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_3, &bgTemplateMain3, GF_BG_TYPE_TEXT);

    GfGfxLoader_LoadCharData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0000_NCGR, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heapId);
    GfGfxLoader_LoadScrnData(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0003_NSCR, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heapId);

    GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0006_NCLR, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_0, 0, data->heapId);

    LoadFontPal0(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_1, data->heapId);

    BG_SetMaskColor(GF_BG_LYR_MAIN_0, 0);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, 0);

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2), 4, 12);
}

void ov59_TVDestroyGraphics(ov59_TVOverlayData *data)
{
    ToggleBgLayer(GF_BG_LYR_MAIN_0, GX_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GX_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GX_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_0, GX_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GX_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GX_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GX_PLANE_TOGGLE_OFF);

    reg_G2_BLDCNT = 0;

    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_3);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_1);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_0);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_2);
    FreeToHeap(data->bgConfig);
}

void ov59_TVSetupMsg(ov59_TVOverlayData *data)
{
    data->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0549_bin, data->heapId);

    ResetAllTextPrinters();

    data->unk0C = 0;
}

void ov59_TVDestroyMsg(ov59_TVOverlayData *data)
{
    DestroyMsgData(data->msgData);
}

BOOL ov59_021D9C74(ov59_TVOverlayData *data, u32 msgNo, u32 param2, u32 param3)
{
    BOOL ret = FALSE;
    switch (data->unk0C)
    {
        case 0:
            ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_PLANE_TOGGLE_OFF);
            struct String *string = String_New(1024, data->heapId);
            ReadMsgDataIntoString(data->msgData, msgNo, string);
            AddWindow(data->bgConfig, &data->window, &ov59_021DA04C);
            FillWindowPixelRect(&data->window, 0, 0, 0, 256, 192);
            u32 unk0 = (u32)sub_02002F08(0, string, 0);

            unk0 = (256 - unk0 ) / 2;
            AddTextPrinterParameterized2(&data->window, 0, string, unk0, param3, 0, MakeFontColor(15, 2, 0), NULL);
            String_Delete(string);
            CopyWindowToVram(&data->window);
            ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_PLANE_TOGGLE_ON);
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

void ov59_021D9D78(ov59_TVOverlayData *data)
{
    data->unk20 += 4;
    BgSetPosTextAndCommit(data->bgConfig, GF_BG_LYR_MAIN_1, BG_POS_OP_SET_Y, data->unk20 >> 4);
}
