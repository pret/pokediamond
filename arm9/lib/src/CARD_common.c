#include "CARD_common.h"
#include "CARD_request.h"
#include "consts.h"
#include "function_target.h"
#include "MI_memory.h"
#include "OS_terminate_proc.h"
#include "OS_spinLock.h"
#include "OS_cache.h"
#include "MB_mb.h"
#include "PXI_fifo.h"

CARDiCommon cardi_common ALIGN(32);
static CARDiCommandArg cardi_arg ALIGN(32);

u8 cardi_thread_stack[0x400] ALIGN(4);

extern void PXI_SetFifoRecvCallback(u32 param1, void* callback);

static void CARDi_LockResource(CARDiOwner owner, CARDTargetMode target);
static void CARDi_UnlockResource(CARDiOwner owner, CARDTargetMode target);

ARM_FUNC void CARDi_SetTask(void (*task) (CARDiCommon *))
{
    CARDiCommon *const p = &cardi_common;

    (void)OS_SetThreadPriority(p->thread, p->priority);

    p->cur_th = p->thread;
    p->task_func = task;
    p->flag |= CARD_STAT_TASK;
    OS_WakeupThreadDirect(p->thread);
}

ARM_FUNC static void CARDi_LockResource(CARDiOwner owner, CARDTargetMode target)
{
    CARDiCommon *const p = &cardi_common;
    OSIntrMode bak_psr = OS_DisableInterrupts();
    if (p->lock_owner == owner)
    {
        if (p->lock_target != target)
        {
            OS_Terminate();
        }
    }
    else
    {
        while (p->lock_owner != OS_LOCK_ID_ERROR)
        {
            OS_SleepThread(p->lock_queue);
        }
        p->lock_owner = owner;
        p->lock_target = target;
    }
    ++p->lock_ref;
    p->cmd->result = CARD_RESULT_SUCCESS;
    (void)OS_RestoreInterrupts(bak_psr);
}

ARM_FUNC static void CARDi_UnlockResource(CARDiOwner owner, CARDTargetMode target)
{
    CARDiCommon *p = &cardi_common;
    OSIntrMode bak_psr = OS_DisableInterrupts();
    if ((p->lock_owner != owner) || !p->lock_ref)
    {
        OS_Terminate();
    }
    else
    {
        if (p->lock_target != target)
        {
            OS_Terminate();
        }
        if (!--p->lock_ref)
        {
            p->lock_owner = OS_LOCK_ID_ERROR;
            p->lock_target = CARD_TARGET_NONE;
            OS_WakeupThread(p->lock_queue);
        }
    }
    p->cmd->result = CARD_RESULT_SUCCESS;
    (void)OS_RestoreInterrupts(bak_psr);
}

ARM_FUNC void CARDi_InitCommon(void)
{
    CARDiCommon *p = &cardi_common;

    p->lock_owner = OS_LOCK_ID_ERROR;
    p->lock_ref = 0;
    p->lock_target = CARD_TARGET_NONE;

    p->cmd = &cardi_arg;
    MI_CpuFillFast(&cardi_arg, 0x00, sizeof(cardi_arg));
    DC_FlushRange(&cardi_arg, sizeof(cardi_arg));

    if (!MB_IsMultiBootChild())
    {
        MI_CpuCopy8((const void *)HW_ROM_HEADER_BUF, (void *)HW_CARD_ROM_HEADER, HW_CARD_ROM_HEADER_SIZE);
    }
    OS_InitThreadQueue(p->lock_queue);
    OS_InitThreadQueue(p->busy_q);
    p->priority = CARD_THREAD_PRIORITY_DEFAULT;
    OS_CreateThread(p->thread, CARDi_TaskThread, NULL, cardi_thread_stack + sizeof(cardi_thread_stack),
                    sizeof(cardi_thread_stack), p->priority);
    OS_WakeupThreadDirect(p->thread);

    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_FS, CARDi_OnFifoRecv);

    if (!MB_IsMultiBootChild())
    {
        CARD_Enable(TRUE);
    }
}

static BOOL CARDi_EnableFlag = FALSE;

ARM_FUNC BOOL CARD_IsEnabled(void)
{
    return CARDi_EnableFlag;
}

ARM_FUNC void CARD_CheckEnabled(void)
{
    if (!CARD_IsEnabled())
    {
        OS_Terminate();
    }
}

ARM_FUNC void CARD_Enable(BOOL enable)
{
    CARDi_EnableFlag = enable;
}

ARM_FUNC BOOL CARDi_WaitAsync(void)
{
    CARDiCommon *const p = &cardi_common;

    OSIntrMode bak_psr = OS_DisableInterrupts();
    while ((p->flag & CARD_STAT_BUSY) != 0)
    {
        OS_SleepThread(p->busy_q);
    }
    (void)OS_RestoreInterrupts(bak_psr);
    return (p->cmd->result == CARD_RESULT_SUCCESS);
}

ARM_FUNC BOOL CARDi_TryWaitAsync(void)
{
    CARDiCommon *const p = &cardi_common;

    return !(p->flag & CARD_STAT_BUSY);
}

ARM_FUNC CARDResult CARD_GetResultCode(void)
{
    CARDiCommon *const p = &cardi_common;

    return p->cmd->result;
}

ARM_FUNC void CARD_LockRom(u16 lock_id)
{
    CARDi_LockResource(lock_id, CARD_TARGET_ROM);
    (void)OS_TryLockCard(lock_id);
}

ARM_FUNC void CARD_UnlockRom(u16 lock_id)
{
    (void)OS_UnlockCard(lock_id);
    CARDi_UnlockResource(lock_id, CARD_TARGET_ROM);
}

ARM_FUNC void CARD_LockBackup(u16 lock_id)
{
    CARDi_LockResource(lock_id, CARD_TARGET_BACKUP);
}

ARM_FUNC void CARD_UnlockBackup(u16 lock_id)
{
    CARDi_UnlockResource(lock_id, CARD_TARGET_BACKUP);
}
