//
// Created by red031000 on 2020-05-06.
//

#include "function_target.h"
#include "OS_reset.h"
#include "MB_mb.h"

extern u16 OSi_IsInitReset;
extern vu16 OSi_IsResetOccurred;
extern void PXI_Init();
extern u32 PXI_IsCallbackReady(u32 param1, u32 param2);
extern void PXI_SetFifoRecvCallback(u32 param1, void* callback);
extern void OS_Terminate();
extern u32 PXI_SendWordByFifo(u32 param1, u32 data, u32 param2);
extern void CARD_LockRom(u16 lockId);
extern void MI_StopDma(u32 dma);
extern void OS_SetIrqMask(u32 mask);
extern void OS_ResetRequestIrqMask(u32 mask);
extern void OSi_DoResetSystem();

ARM_FUNC void OS_InitReset() {
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
    OS_SetIrqMask(0x40000);
    OS_ResetRequestIrqMask((u32)~0);
    *(u32 *)HW_RESET_PARAMETER_BUF = parameter;
    OSi_SendToPxi(OS_PXI_COMMAND_RESET);
    OSi_DoResetSystem(); //oh boy this is in itcm, that's gonna be fun to deal with Kappa
}
