//
// Created by red031000 on 2020-05-06.
//

#include "function_target.h"
#include "OS_reset.h"
#include "MB_mb.h"
#include "OS_terminate_proc.h"
#include "OS_interrupt.h"
#include "sections.h"

static u16 OSi_IsInitReset = 0;
vu16 OSi_IsResetOccurred = 0;

extern void PXI_Init(void);
extern u32 PXI_IsCallbackReady(u32 param1, u32 param2);
extern void PXI_SetFifoRecvCallback(u32 param1, void* callback);
extern u32 PXI_SendWordByFifo(u32 param1, u32 data, u32 param2);
extern void CARD_LockRom(u16 lockId);
extern void MI_StopDma(u32 dma);
extern void OSi_DoResetSystem(void); //in itcm, should technically be in this file

ARM_FUNC void OS_InitReset(void) {
    if (OSi_IsInitReset) {
        return;
    }
    OSi_IsInitReset = TRUE;
    PXI_Init();
    while (!PXI_IsCallbackReady(PXI_FIFO_TAG_OS, PXI_PROC_ARM7)) { }

    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_OS, OSi_CommonCallback);
}

ARM_FUNC static void OSi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err) {
#pragma unused(tag, err) //needed because otherwise -W all errors
    u16 command = (u16)((data & OS_PXI_COMMAND_MASK) >> OS_PXI_COMMAND_SHIFT);
    if (command == OS_PXI_COMMAND_RESET)
    {
        OSi_IsResetOccurred = TRUE;
        return;
    }
    OS_Terminate();
}

ARM_FUNC static void OSi_SendToPxi(u16 data) {
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_OS, (u32)data << 0x8, FALSE)) {}
}

ARM_FUNC void OS_ResetSystem(u32 parameter) {
    if (MB_IsMultiBootChild()) {
        OS_Terminate();
    }
    CARD_LockRom((u16)OS_GetLockID());
    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);
    (void)OS_SetIrqMask(0x40000);
    (void)OS_ResetRequestIrqMask((u32)~0);
    *(u32 *)HW_RESET_PARAMETER_BUF = parameter;
    OSi_SendToPxi(OS_PXI_COMMAND_RESET);
    OSi_DoResetSystem(); //oh boy this is in itcm, that's gonna be fun to deal with Kappa
}

#pragma section ITCM begin
ARM_FUNC asm void OSi_DoBoot(void)
{
    mov ip, #0x04000000
    str ip, [ip, #0x208]
    ldr r1, =SDK_AUTOLOAD_DTCM_START
    add r1, r1, #0x3fc0
    add r1, r1, #0x3c
    mov r0, #0x0
    str r0, [r1]
    ldr r1, =REG_SUBPINTF_ADDR
_01FF81D4:
    ldrh r0, [r1]
    and r0, r0, #0xf
    cmp r0, #0x1
    bne _01FF81D4
    mov r0, #0x100
    strh r0, [r1]
    mov r0, #0x0
    ldr r3, =HW_EXCP_VECTOR_MAIN
    ldr r4, [r3]
    ldr r1, =HW_BIOS_EXCP_STACK_MAIN
    mov r2, #0x80
    bl OSi_CpuClear32
    str r4, [r3]
    ldr r1, =HW_PXI_SIGNAL_PARAM_ARM9
    mov r2, #0x18
    bl OSi_CpuClear32
    ldr r1, =HW_WM_RSSI_POOL
    strh r0, [r1]
    ldr r1, =HW_COMPONENT_PARAM
    mov r2, #0x64
    bl OSi_CpuClear32
    ldr r1, =REG_SUBPINTF_ADDR
_01FF822C:
    ldrh r0, [r1]
    and r0, r0, #0xf
    cmp r0, #0x1
    beq _01FF822C
    mov r0, #0x0
    strh r0, [r1]
    ldr r3, =HW_ROM_HEADER_BUF
    ldr ip, [r3, #0x24]
    mov lr, ip
    ldr r11, =HW_PXI_SIGNAL_PARAM_ARM9
    ldmia r11, {r0-r10}
    mov r11, #0x0
    bx ip
}

ARM_FUNC static asm void OSi_CpuClear32(register u32 data, register void *destp, register u32 size)
{
    add ip, r1, r2
_01FF8284:
    cmp r1, ip
    stmltia r1!, {r0}
    blt _01FF8284
    bx lr
}
#pragma section ITCM end
