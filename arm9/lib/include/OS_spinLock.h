//
// Created by red031000 on 2020-05-03.
//

#ifndef POKEDIAMOND_OS_SPINLOCK_H
#define POKEDIAMOND_OS_SPINLOCK_H

#include "types.h"
#include "syscall.h"

typedef volatile struct OSLockWord {
    u32 lockFlag;
    u16 ownerID;
    u16 extension;
} OSLockWord;

static inline void OSi_WaitByLoop()
{
    SVC_WaitByLoop(0x1000 / 4);
}

void OS_InitLock();
s32 OSi_DoLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void),
        BOOL disableFiq);
s32 OS_TryLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void));
s32 OSi_DoUnlockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
        BOOL disableFIQ);
s32 OS_GetLockID(void);

#endif //POKEDIAMOND_OS_SPINLOCK_H
