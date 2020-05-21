//
// Created by red031000 on 2020-05-21.
//

#include "OS_spinLock.h"
#include "function_target.h"
#include "consts.h"
#include "MI_exMemory.h"

extern void OS_TryLockByWord(u16 param1, OSLockWord* lockp, void* func);
extern void OS_UnlockByWord(u16 param1, OSLockWord* lockp, void* func);
extern void MIi_CpuClear32(u32 param1, void * addr, u32 length); //not too sure about names
extern s32 OSi_DoTryLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void),
                               BOOL disableFiq);

ARM_FUNC void OS_InitLock()
{
    static BOOL isInitialized = FALSE;

    if (isInitialized)
    {
        return;
    }
    isInitialized = TRUE;

    OSLockWord* lockp = (OSLockWord *)0x027FFFF0;

    lockp->lockFlag = 0;

    (void)OS_TryLockByWord(0x7e, lockp, NULL);

    while (lockp->extension)
    {
        OSi_WaitByLoop();
    }

    ((u32 *)HW_LOCK_ID_FLAG_MAIN)[0] = 0xffffffff;
    ((u32 *)HW_LOCK_ID_FLAG_MAIN)[1] = 0xffff0000;

    MIi_CpuClear32(0x0, (void *)HW_SHARED_LOCK_BUF, 0x28);

    MIi_SetCardProcessor(MI_PROCESSOR_ARM7);

    MIi_SetCartridgeProcessor(MI_PROCESSOR_ARM7);

    OS_UnlockByWord(0x7e, lockp, NULL);
    OS_TryLockByWord(0x7f, lockp, NULL);
}

ARM_FUNC s32 OSi_DoLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void), //should be static
                                     BOOL disableFiq)
{
    s32 lastLockFlag;
    while ((lastLockFlag = OSi_DoTryLockByWord(lockId, lockp, ctrlFuncp, disableFiq)) > 0) {
        OSi_WaitByLoop();
    }

    return lastLockFlag;
}
