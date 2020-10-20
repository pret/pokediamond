#include "function_target.h"
#include "CARD_request.h"
#include "OS_cache.h"
#include "OS_system.h"
#include "OS_thread.h"

extern CARDiCommon cardi_common;

extern u32 PXI_IsCallbackReady(u32 param1, u32 param2);

ARM_FUNC void CARDi_OnFifoRecv(PXIFifoTag tag, u32 data, BOOL err)
{
#pragma unused (data)
    if ((tag == PXI_FIFO_TAG_FS) && err)
    {
        CARDiCommon *const p = &cardi_common;
        p->flag &= ~CARD_STAT_REQ;
        OS_WakeupThreadDirect(p->cur_th);
    }
}

ARM_FUNC void CARDi_TaskThread(void *arg)
{
#pragma unused (arg)
    CARDiCommon *const p = &cardi_common;

    while (TRUE)
    {
        OSIntrMode bak_psr = OS_DisableInterrupts();
        while ((p->flag & CARD_STAT_TASK) == 0)
        {
            p->cur_th = p->thread;
            OS_SleepThread(NULL);
        }
        (void)OS_RestoreInterrupts(bak_psr);
        (*p->task_func)(p);
    }
}

ARM_FUNC BOOL CARDi_Request(CARDiCommon *p, s32 req_type, s32 retry_count)
{
    if ((p->flag & CARD_STAT_INIT_CMD) == 0)
    {
        p->flag |= CARD_STAT_INIT_CMD;
        while (!PXI_IsCallbackReady(PXI_FIFO_TAG_FS, PXI_PROC_ARM7))
        {
            OS_SpinWait(100);
        }

        (void)CARDi_Request(p, CARD_REQ_INIT, 1);
    }
    DC_FlushRange(p->cmd, sizeof(*p->cmd));
    DC_WaitWriteBufferEmpty();

    do
    {
        p->command = req_type;
        p->flag |= CARD_STAT_REQ;
        CARDi_SendPxi((u32)req_type);

        switch (req_type)
        {
            case CARD_REQ_INIT:
                CARDi_SendPxi((u32)p->cmd);
                break;
        }
        OSIntrMode bak_psr = OS_DisableInterrupts();
        while ((p->flag & CARD_STAT_REQ) != 0)
        {
            OS_SleepThread(NULL);
        }
        (void)OS_RestoreInterrupts(bak_psr);
        DC_InvalidateRange(p->cmd, sizeof(*p->cmd));
    }
    while ((p->cmd->result == CARD_RESULT_TIMEOUT) && (--retry_count > 0));

    return (p->cmd->result == CARD_RESULT_SUCCESS);
}
