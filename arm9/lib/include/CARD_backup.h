#ifndef POKEDIAMOND_CARD_BACKUP_H
#define POKEDIAMOND_CARD_BACKUP_H

#include "nitro/types.h"
#include "MI_dma.h"
#include "CARD_common.h"

BOOL CARDi_RequestStreamCommand(u32 src, u32 dst, u32 len, MIDmaCallback callback, void *arg, BOOL is_async,
                                CARDRequest req_type, int req_retry, CARDRequestMode req_mode);
u32 CARD_GetBackupSectorSize(void);
BOOL CARD_IdentifyBackup(CARDBackupType type);
BOOL CARD_WaitBackupAsync(void);
BOOL CARD_TryWaitBackupAsync(void);
void CARD_CancelBackupAsync(void);

static inline BOOL CARDi_ReadBackup(u32 src, void * dst, u32 len, MIDmaCallback callback, void * arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async, CARD_REQ_READ_BACKUP, 1, CARD_REQUEST_MODE_RECV);
}

static inline BOOL CARDi_WriteBackup(u32 dst, void * src, u32 len, MIDmaCallback callback, void * arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async, CARD_REQ_WRITE_BACKUP, CARD_RETRY_COUNT_MAX, CARD_REQUEST_MODE_SEND);
}

static inline BOOL CARDi_WriteAndVerifyBackup(u32 dst, void * src, u32 len, MIDmaCallback callback, void * arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async, CARD_REQ_WRITE_BACKUP, CARD_RETRY_COUNT_MAX, CARD_REQUEST_MODE_SEND_VERIFY);
}

#endif //POKEDIAMOND_CARD_BACKUP_H
