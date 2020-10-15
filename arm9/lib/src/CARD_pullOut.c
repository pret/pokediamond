#include "function_target.h"
#include "CARD_common.h"
#include "CARD_pullOut.h"
#include "PXI_init.h"
#include "PXI_fifo.h"
#include "OS_terminate_proc.h"
#include "OS_system.h"
#include "PAD_pad.h"
#include "SPI_pm.h"
#include "syscall.h"

static CARDPulledOutCallback CARD_UserCallback;
static BOOL CARDi_IsPulledOutFlag = FALSE;

extern void PXI_SetFifoRecvCallback(u32 param1, void* callback);
extern u32 PXI_SendWordByFifo(u32 param1, u32 data, u32 param2);

static void CARDi_PulledOutCallback(PXIFifoTag tag, u32 data, BOOL err);
static void CARDi_SendtoPxi(u32 data, u32 wait);

ARM_FUNC void CARD_InitPulledOutCallback(void)
{
    PXI_Init();

    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_CARD, CARDi_PulledOutCallback);

    CARD_UserCallback = NULL;
}

ARM_FUNC static void CARDi_PulledOutCallback(PXIFifoTag tag, u32 data, BOOL err)
{
#pragma unused(tag, err)
    u32 command = data & CARD_PXI_COMMAND_MASK;

    if (command == CARD_PXI_COMMAND_PULLED_OUT)
    {
        if (!CARDi_IsPulledOutFlag)
        {
            BOOL isTerminateImm = TRUE;
            CARDi_IsPulledOutFlag = TRUE;

            if (CARD_UserCallback)
            {
                isTerminateImm = CARD_UserCallback();
            }

            if (isTerminateImm)
            {
                CARD_TerminateForPulledOut();
            }
        }
    }
    else
    {
        OS_Terminate();
    }
}

ARM_FUNC BOOL CARD_IsPulledOut(void)
{
    return CARDi_IsPulledOutFlag;
}

ARM_FUNC void CARD_TerminateForPulledOut(void)
{
    BOOL should_be_halt = TRUE;

    if (PAD_DetectFold())
    {
        u32 res;
        while ((res = PM_ForceToPowerOff()) == 0x04)
        {
            OS_SpinWait(HW_CPU_CLOCK_ARM9 / 100);
        }
        if (res == 0)
        {
            should_be_halt = FALSE;
        }
    }

    if (should_be_halt)
    {
        CARDi_SendtoPxi(CARD_PXI_COMMAND_TERMINATE, 1);
    }

    OS_Terminate();
}

ARM_FUNC void CARDi_CheckPulledOutCore(u32 id)
{
    vu32 iplCardID = *(vu32 *)((*(u16 *)HW_CHECK_DEBUGGER_SW == 0) ? HW_RED_RESERVED : HW_BOOT_CHECK_INFO_BUF);

    if (id != (u32)iplCardID)
    {
        OSIntrMode bak_cpsr = OS_DisableInterrupts();
        CARDi_PulledOutCallback(PXI_FIFO_TAG_CARD, CARD_PXI_COMMAND_PULLED_OUT, FALSE);
        (void)OS_RestoreInterrupts(bak_cpsr);
    }
}

ARM_FUNC static void CARDi_SendtoPxi(u32 data, u32 wait)
{
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_CARD, data, FALSE) != PXI_FIFO_SUCCESS)
    {
        SVC_WaitByLoop((s32)wait);
    }
}
