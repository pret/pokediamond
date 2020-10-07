#ifndef NITRO_CARD_BACKUP_H_
#define NITRO_CARD_BACKUP_H_

#include "nitro/types.h"
#include "MI_dma.h"
#include "CARD_common.h"

BOOL CARD_TryWaitBackupAsync(void);
BOOL CARD_WaitBackupAsync(void);
void CARD_CancelBackupAsync(void);
void CARD_UnlockBackup(u16 lock_id);
void CARD_LockBackup(u16 lock_id);
BOOL CARD_IdentifyBackup(u16 lock_id);

BOOL CARDi_RequestStreamCommand(
    u32 src,
    u32 dst,
    u32 len,
    MIDmaCallback callback,
    void * arg,
    BOOL is_async,
    CARDRequest req_type,
    int req_retry,
    CARDRequestMode req_mode
);

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

#endif //NITRO_CARD_BACKUP_H_
