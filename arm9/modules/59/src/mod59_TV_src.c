#include "global.h"
#include "mod59_TV_src.h"
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
#include "overlay_manager.h"
#include "text.h"
#include "unk_020040F4.h"

extern void FUN_0200E3A0(PMLCDTarget, s32);

extern void FUN_0200E1D0(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 heap_id);
extern u32 FUN_0200E308(void);

extern const struct GraphicsBanks MOD59_021DA0D4;
extern const struct GraphicsModes MOD59_021DA054;
extern const struct BgTemplate MOD59_021DA080;
extern const struct BgTemplate MOD59_021DA09C;
extern const struct BgTemplate MOD59_021DA064;
extern const struct BgTemplate MOD59_021DA0B8;

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

THUMB_FUNC BOOL MOD59_TVInit(struct UnkStruct_02006234 *param0, u32 *param1)
{
#pragma unused(param1)
    CreateHeap(3, 83, 0x40000);
    MOD59_TVOverlayData *data = (MOD59_TVOverlayData *)OverlayManager_CreateAndGetData(param0, sizeof(MOD59_TVOverlayData), 0x53);
    (void)memset((void *)data, 0, sizeof(MOD59_TVOverlayData));
    data->heap_id = 0x53;
    data->unk24 = 0;
    return TRUE;
}

#ifdef NONMATCHING
THUMB_FUNC BOOL MOD59_TVMain(struct UnkStruct_02006234 *overlayStruct, u32 *param1)
{
    MOD59_TVOverlayData *data = (MOD59_TVOverlayData *)OverlayManager_GetData(overlayStruct);
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

            MOD59_TVSetupGraphics(data);
            MOD59_TVSetupMsg(data);

            Main_SetVBlankIntrCB((void (*)(void *))MOD59_TVDoGpuBgUpdate, data);

            GX_BothDispOn();

            data->unk24 = 60;

            *param1 = 1;
            break;

        case 1:
            if (data->unk24 != 0)
            {
                data->unk24--;
                break;
            }

            FUN_0200414C(SEQ_TV_HOUSOU);
            FUN_0200433C(4, SEQ_TV_HOUSOU, 1);

            data->unk24 = 90;

            *param1 = 2;
            break;

        case 2:
            if (data->unk24 != 0)
            {
                data->unk24--;
                break;
            }
            data->unk24 = 0; //??

            FUN_0200E1D0(0, 1, 1, 0, 6, 1, data->heap_id);

            *param1 = 3;
            break;

        case 3:
            MOD59_021D9D78(data);

            if (FUN_0200E308() != 1)
            {
                break;
            }

            *param1 = 4;
            break;

        case 4:
            MOD59_021D9D78(data);

            if (MOD59_021D9C74(data, 0, 40, 48) != TRUE)
            {
                break;
            }

            FUN_0200E1D0(0, 0, 0, 0, 6, 1, data->heap_id);

            *param1 = 5;
            break;

        case 5:
            MOD59_021D9D78(data);

            if (FUN_0200E308() != 1)
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
#else
THUMB_FUNC asm BOOL MOD59_TVMain(struct UnkStruct_02006234 *overlayStruct, u32 *param1)
{
    push {r3, r4, r5, r6, lr}
    sub sp, #0xc
    add r5, r1, #0
    bl OverlayManager_GetData
    ldr r1, [r5, #0]
    add r4, r0, #0
    mov r6, #0
    cmp r1, #5
    bls _021D98AE
    b _021D99E2
_021D98AE:
    add r1, r1, r1
    add r1, pc
    ldrh r1, [r1, #6]
    lsl r1, r1, #0x10
    asr r1, r1, #0x10
    add pc, r1
_021D98BA: // jump table
    dcd 0x0070000a //compiler really hates movs in inline asm
    //movs r2, r1 //case 0
    //lsl r0, r6, #1 //case 1
    lsl r6, r2, #2 //case 2
    lsl r0, r0, #3 //case 3
    lsl r2, r2, #3 //case 4
    lsl r4, r0, #4 //case 5
    //.short _021D98C6 - _021D98BA - 2 // case 0
    //.short _021D992C - _021D98BA - 2 // case 1
    //.short _021D9952 - _021D98BA - 2 // case 2
    //.short _021D997C - _021D98BA - 2 // case 3
    //.short _021D998E - _021D98BA - 2 // case 4
    //.short _021D99C0 - _021D98BA - 2 ; case 5
_021D98C6:
    add r0, r6, #0
    add r1, r6, #0
    bl FUN_0200E3A0
    mov r0, #1
    add r1, r6, #0
    bl FUN_0200E3A0
    add r0, r6, #0
    add r1, r0, #0
    bl Main_SetVBlankIntrCB
    add r0, r6, #0
    add r1, r0, #0
    bl FUN_02015F34
    bl GX_DisableEngineALayers
    bl GX_DisableEngineBLayers
    mov r2, #1
    lsl r2, r2, #0x1a
    ldr r1, [r2, #0]
    ldr r0, =0xFFFFE0FF
    and r1, r0
    str r1, [r2, #0]
    ldr r2, =0x04001000
    ldr r1, [r2, #0]
    and r0, r1
    str r0, [r2]
    mov r0, #4
    mov r1, #8
    bl SetKeyRepeatTimers
    add r0, r4, #0
    bl MOD59_TVSetupGraphics
    add r0, r4, #0
    bl MOD59_TVSetupMsg
    ldr r0, =MOD59_TVDoGpuBgUpdate
    add r1, r4, #0
    bl Main_SetVBlankIntrCB
    bl GX_BothDispOn
    mov r0, #0x3c
    str r0, [r4, #0x24]
    mov r0, #1
    str r0, [r5]
    b _021D99E2
_021D992C:
    ldr r0, [r4, #0x24]
    cmp r0, #0
    beq _021D9938
    sub r0, r0, #1
    str r0, [r4, #0x24]
    b _021D99E2
_021D9938:
    ldr r0, =0x00000406
    bl FUN_0200414C
    ldr r1, =0x00000406
    mov r0, #4
    mov r2, #1
    bl FUN_0200433C
    mov r0, #0x5a
    str r0, [r4, #0x24]
    mov r0, #2
    str r0, [r5]
    b _021D99E2
_021D9952:
    ldr r0, [r4, #0x24]
    cmp r0, #0
    beq _021D995E
    sub r0, r0, #1
    str r0, [r4, #0x24]
    b _021D99E2
_021D995E:
    str r6, [r4, #0x24]
    mov r0, #6
    mov r1, #1
    str r0, [sp]
    str r1, [sp, #4]
    ldr r0, [r4, #0]
    add r2, r1, #0
    str r0, [sp, #8]
    add r0, r6, #0
    add r3, r6, #0
    bl FUN_0200E1D0
    mov r0, #3
    str r0, [r5]
    b _021D99E2
_021D997C:
    bl MOD59_021D9D78
    bl FUN_0200E308
    cmp r0, #1
    bne _021D99E2
    mov r0, #4
    str r0, [r5]
    b _021D99E2
_021D998E:
    bl MOD59_021D9D78
    add r0, r4, #0
    add r1, r6, #0
    mov r2, #0x28
    mov r3, #0x30
    bl MOD59_021D9C74
    cmp r0, #1
    bne _021D99E2
    mov r0, #6
    str r0, [sp]
    mov r0, #1
    str r0, [sp, #4]
    ldr r0, [r4, #0]
    str r0, [sp, #8]
    add r0, r6, #0
    add r1, r0, #0
    add r2, r0, #0
    add r3, r0, #0
    bl FUN_0200E1D0
    mov r0, #5
    str r0, [r5]
    b _021D99E2
_021D99C0:
    bl MOD59_021D9D78
    bl FUN_0200E308
    cmp r0, #1
    bne _021D99E2
    add r0, r4, #0
    bl MOD59_TVDestroyMsg
    add r0, r4, #0
    bl MOD59_TVDestroyGraphics
    add r0, r6, #0
    add r1, r0, #0
    bl Main_SetVBlankIntrCB
    mov r6, #1
_021D99E2:
    add r0, r6, #0
    add sp, #0xc
    pop {r3, r4, r5, r6, pc}
}
#endif

THUMB_FUNC BOOL MOD59_TVExit(struct UnkStruct_02006234 *overlayStruct, u32 *param1)
{
#pragma unused (param1)
    u32 heap_id = ((MOD59_TVOverlayData *)OverlayManager_GetData(overlayStruct))->heap_id;
    OverlayManager_FreeData(overlayStruct);
    DestroyHeap(heap_id);
    return TRUE;
}

THUMB_FUNC void MOD59_TVDoGpuBgUpdate(MOD59_TVOverlayData *data)
{
    DoScheduledBgGpuUpdates(data->bgConfig);
}

THUMB_FUNC void MOD59_TVSetupGraphics(MOD59_TVOverlayData *data)
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

    GfGfxLoader_GXLoadPal(NARC_DEMO_INTRO_INTRO_TV, NARC_intro_tv_narc_0006_NCLR, GF_BG_LYR_MAIN_0, 0, 0, data->heap_id);

    FUN_02002ED0(GF_BG_LYR_MAIN_0, 0x20, data->heap_id);

    BG_SetMaskColor(GF_BG_LYR_MAIN_0, 0);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, 0);

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2, 4, 12);
}

THUMB_FUNC void MOD59_TVDestroyGraphics(MOD59_TVOverlayData *data)
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

THUMB_FUNC void MOD59_TVSetupMsg(MOD59_TVOverlayData *data)
{
    data->msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, NARC_msg_narc_0549_bin, data->heap_id);

    FUN_0201BD5C();

    data->unk0C = 0;
}

THUMB_FUNC void MOD59_TVDestroyMsg(MOD59_TVOverlayData *data)
{
    DestroyMsgData(data->msgData);
}

THUMB_FUNC BOOL MOD59_021D9C74(MOD59_TVOverlayData *data, u32 msgNo, u32 param2, u32 param3)
{
    BOOL ret = FALSE;
    switch (data->unk0C)
    {
        case 0:
            ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_LAYER_TOGGLE_OFF);
            struct String *string = String_ctor(1024, data->heap_id);
            ReadMsgDataIntoString(data->msgData, msgNo, string);
            AddWindow(data->bgConfig, &data->window, &MOD59_021DA04C);
            FillWindowPixelRect(&data->window, 0, 0, 0, 256, 192);
            u32 unk0 = (u32)FUN_02002F08(0, string, 0);

            unk0 = (256 - unk0 ) / 2;
            AddTextPrinterParameterized2(&data->window, 0, string, unk0, param3, 0, MakeFontColor(15, 2, 0), NULL);
            String_dtor(string);
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
            if((gMain.newKeys & PAD_BUTTON_A) != 1 && (gMain.newKeys & PAD_BUTTON_B) != 2)
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

THUMB_FUNC void MOD59_021D9D78(MOD59_TVOverlayData *data)
{
    data->unk20 += 4;
    BgSetPosTextAndCommit(data->bgConfig, GF_BG_LYR_MAIN_1, BG_POS_OP_SET_Y, data->unk20 >> 4);
}
