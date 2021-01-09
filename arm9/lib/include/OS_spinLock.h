#ifndef POKEDIAMOND_ARM9_OS_SPINLOCK_H
#define POKEDIAMOND_ARM9_OS_SPINLOCK_H

#include "nitro/types.h"
#include "nitro/OS_spinLock_shared.h"
#include "syscall.h"

#define OS_ReadOwnerOfLockCartridge()  OS_ReadOwnerOfLockWord( (OSLockWord *)HW_CTRDG_LOCK_BUF )
#define OS_MAINP_LOCKED_FLAG           0x40
#define OS_LOCK_SUCCESS                0

#define OS_LOCK_ID_ERROR               (-3)

static inline void OSi_WaitByLoop(void)
{
    SVC_WaitByLoop(0x1000 / 4);
}

void OS_InitLock(void);
s32 OSi_DoLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void),
        BOOL disableFiq);
s32 OS_TryLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void));
s32 OSi_DoUnlockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
        BOOL disableFIQ);
s32 OS_UnlockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void));
s32 OSi_DoTryLockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
        BOOL disableFiq);
s32 OS_LockCartridge(u16 lockID);
s32 OS_UnlockCartridge(u16 lockID);
s32 OS_TryLockCartridge(u16 lockID);
void OSi_AllocateCartridgeBus(void);
void OSi_FreeCartridgeBus(void);
s32 OS_TryLockCard(u16 lockID);
s32 OS_UnlockCard(u16 lockID);
void OSi_AllocateCardBus(void);
void OSi_FreeCardBus(void);
u16 OS_ReadOwnerOfLockWord(OSLockWord * lock);
s32 OS_UnLockCartridge(u16 lockID);
s32 OS_GetLockID(void);
void OS_ReleaseLockID(register u16 lockID);

#endif //POKEDIAMOND_ARM9_OS_SPINLOCK_H
