#include "function_target.h"
#include "OS_reset.h"
#include "OS_interrupt.h"

static u16 OSi_IsInitReset = 0;
vu16 OSi_IsResetOccurred = 0;

extern void MI_StopDma(u32 dma);
extern OSIrqMask OS_SetIrqMask(OSIrqMask mask);
extern OSIrqMask OS_ResetRequestIrqMask(OSIrqMask mask);
extern void SND_Shutdown(void);
extern void PXI_SetFifoRecvCallback(u32 param1, void* callback);
extern void OS_Terminate(void);
extern u32 PXI_SendWordByFifo(u32 param1, u32 data, u32 param2);
extern void FUN_038073EC(void); //OSi_DoResetSystem, in wram

ARM_FUNC void OS_InitReset(void)
{
    if (OSi_IsInitReset)
        return;
    OSi_IsInitReset = TRUE;

    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_OS, OSi_CommonCallback);
}

ARM_FUNC BOOL OS_IsResetOccurred(void)
{
    return OSi_IsResetOccurred;
}

ARM_FUNC static void OSi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err)
{
#pragma unused(tag, err)
    u16 command = (u16)((data & OS_PXI_COMMAND_MASK) >> OS_PXI_COMMAND_SHIFT);
    if (command == OS_PXI_COMMAND_RESET)
    {
        OSi_IsResetOccurred = TRUE;
        return;
    }
    OS_Terminate();
}

ARM_FUNC static void OSi_SendToPxi(u16 data)
{
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_OS, (u32) data << 0x8, FALSE)) {}
}

ARM_FUNC void OS_ResetSystem(void) {
    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);

    (void)OS_SetIrqMask(0x40000);
    (void)OS_ResetRequestIrqMask((u32)~0);
    SND_Shutdown();
    OSi_SendToPxi(OS_PXI_COMMAND_RESET);
    FUN_038073EC(); //OSi_DoResetSystem, in wram
}
