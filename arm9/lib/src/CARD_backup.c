#include "CARD_backup.h"
#include "function_target.h"
#include "CARD_common.h"
#include "CARD_request.h"
#include "CARD_spi.h"
#include "OS_cache.h"
#include "MI_memory.h"
#include "OS_terminate_proc.h"
#include "OS_system.h"

extern void OSi_ReferSymbol(void *symbol);
extern char _SDK_NintendoBackup[];

extern CARDiCommon cardi_common;

static void CARDi_RequestStreamCommandCore(CARDiCommon *p);

ARM_FUNC static void CARDi_RequestStreamCommandCore(CARDiCommon *p)
{
    const int req_type = p->req_type;
    const int req_mode = p->req_mode;
    const int retry_count = p->req_retry;
    u32 size = sizeof(p->backup_cache_page_buf);

    OSi_ReferSymbol((void *)_SDK_NintendoBackup);

    if (req_type == CARD_REQ_ERASE_SECTOR_BACKUP)
    {
        size = CARD_GetBackupSectorSize();
    }
    do
    {
        const u32 len = (size < p->len) ? size : p->len;
        p->cmd->len = len;

        if ((p->flag & CARD_STAT_CANCEL) != 0)
        {
            p->flag &= ~CARD_STAT_CANCEL;
            p->cmd->result = CARD_RESULT_CANCELED;
            break;
        }
        switch (req_mode)
        {
            case CARD_REQUEST_MODE_RECV:
                DC_InvalidateRange(p->backup_cache_page_buf, len);
                p->cmd->src = (u32)p->src;
                p->cmd->dest = (u32)p->backup_cache_page_buf;
                break;
            case CARD_REQUEST_MODE_SEND:
            case CARD_REQUEST_MODE_SEND_VERIFY:
                MI_CpuCopy8((const void *)p->src, p->backup_cache_page_buf, len);
                DC_FlushRange(p->backup_cache_page_buf, len);
                DC_WaitWriteBufferEmpty();
                p->cmd->src = (u32)p->backup_cache_page_buf;
                p->cmd->dest = (u32)p->dst;
                break;
            case CARD_REQUEST_MODE_SPECIAL:
                p->cmd->src = (u32)p->src;
                p->cmd->dest = (u32)p->dst;
                break;
        }

        if (!CARDi_Request(p, req_type, retry_count))
        {
            break;
        }

        if (req_mode == CARD_REQUEST_MODE_SEND_VERIFY)
        {
            if (!CARDi_Request(p, CARD_REQ_VERIFY_BACKUP, 1))
            {
                break;
            }
        }
        else if (req_mode == CARD_REQUEST_MODE_RECV)
        {
            MI_CpuCopy8(p->backup_cache_page_buf, (void *)p->dst, len);
        }
        p->src += len;
        p->dst += len;
        p->len -= len;
    }
    while (p->len > 0);
    CARDi_EndTask(p, TRUE);
}

ARM_FUNC BOOL CARDi_RequestStreamCommand(u32 src, u32 dst, u32 len, MIDmaCallback callback, void *arg, BOOL is_async,
                                         CARDRequest req_type, int req_retry, CARDRequestMode req_mode)
{
    CARDiCommon *const p = &cardi_common;

    OSi_ReferSymbol((void *)_SDK_NintendoBackup);

    CARDi_WaitTask(p, callback, arg);
    p->src = src;
    p->dst = dst;
    p->len = len;
    p->req_type = req_type;
    p->req_retry = req_retry;
    p->req_mode = req_mode;
    if (is_async)
    {
        CARDi_SetTask(CARDi_RequestStreamCommandCore);
        return TRUE;
    }
    else
    {
        cardi_common.cur_th = OS_GetCurrentThread();
        CARDi_RequestStreamCommandCore(p);
        return (p->cmd->result == CARD_RESULT_SUCCESS);
    }
}

ARM_FUNC u32 CARD_GetBackupSectorSize(void)
{
    return cardi_common.cmd->spec.sect_size;
}

ARM_FUNC BOOL CARD_IdentifyBackup(CARDBackupType type)
{
    CARDiCommon *const p = &cardi_common;

    OSi_ReferSymbol((void *)_SDK_NintendoBackup);
    if (type == CARD_BACKUP_TYPE_NOT_USE)
    {
        OS_Terminate();
    }

    CARD_CheckEnabled();

    CARDi_WaitTask(p, NULL, NULL);
    CARDi_IdentifyBackupCore(type);
    cardi_common.cur_th = OS_GetCurrentThread();
    (void)CARDi_Request(p, CARD_REQ_IDENTIFY, 1);

    p->cmd->src = 0;
    p->cmd->dest = (u32)p->backup_cache_page_buf;
    p->cmd->len = 1;
    (void)CARDi_Request(p, CARD_REQ_READ_BACKUP, 1);
    CARDi_EndTask(p, TRUE);
    return (p->cmd->result == CARD_RESULT_SUCCESS);
}

ARM_FUNC BOOL CARD_WaitBackupAsync(void)
{
    return CARDi_WaitAsync();
}

ARM_FUNC BOOL CARD_TryWaitBackupAsync(void)
{
    return CARDi_TryWaitAsync();
}

ARM_FUNC void CARD_CancelBackupAsync(void)
{
    OSIntrMode bak_cpsr = OS_DisableInterrupts();
    cardi_common.flag |= CARD_STAT_CANCEL;
    (void)OS_RestoreInterrupts(bak_cpsr);
}
