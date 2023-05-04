#include "global.h"
#include "mod59_TV_src.h"
#include "GX_layers.h"
#include "bg_window.h"
#include "constants/sndseq.h"
#include "game_init.h"
#include "heap.h"
#include "overlay_manager.h"
#include "unk_020040F4.h"

extern void FUN_0200E3A0(PMLCDTarget, s32);

extern void FUN_0200E1D0(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 heap_id);
extern u32 FUN_0200E308(void);

extern void MOD59_021D9A20(MOD59_TVOverlayData *data); //setup func
extern void MOD59_021D9C48(MOD59_TVOverlayData *data); //setup func
extern void MOD59_021D9D78(void);
extern BOOL MOD59_021D9C74(MOD59_TVOverlayData *data, u32 param1, u32 param2, u32 param3);
extern void MOD59_021D9C68(MOD59_TVOverlayData *data);
extern void MOD59_021D9BD0(MOD59_TVOverlayData *data);

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

            MOD59_021D9A20(data);
            MOD59_021D9C48(data);

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
            MOD59_021D9D78();

            if (FUN_0200E308() != 1)
            {
                break;
            }

            *param1 = 4;
            break;

        case 4:
            MOD59_021D9D78();

            if (MOD59_021D9C74(data, 0, 40, 48) != TRUE)
            {
                break;
            }

            FUN_0200E1D0(0, 0, 0, 0, 6, 1, data->heap_id);

            *param1 = 5;
            break;

        case 5:
            MOD59_021D9D78();

            if (FUN_0200E308() != 1)
            {
                break;
            }

            MOD59_021D9C68(data);
            MOD59_021D9BD0(data);

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
    bl MOD59_021D9A20
    add r0, r4, #0
    bl MOD59_021D9C48
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
    bl MOD59_021D9C68
    add r0, r4, #0
    bl MOD59_021D9BD0
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
