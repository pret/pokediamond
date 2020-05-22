//
// Created by red031000 on 2020-05-21.
//

#include "OS_spinLock.h"
#include "OS_system.h"
#include "function_target.h"
#include "consts.h"
#include "MI_exMemory.h"

extern void MIi_CpuClear32(u32 param1, void * addr, u32 length); //not too sure about names
extern u32 MI_SwapWord(u32 data, volatile u32* destp);

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

    (void)OS_UnlockByWord(0x7e, lockp, NULL);
    (void)OS_TryLockByWord(0x7f, lockp, NULL);
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

ARM_FUNC s32 OS_TryLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void))
{
    return OSi_DoLockByWord(lockId, lockp, ctrlFuncp, FALSE);
}

ARM_FUNC s32 OSi_DoUnlockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
                                        BOOL disableFIQ)
{
    if (lockID != lockp->ownerID)
    {
        return -2;
    }

    OSIntrMode lastIntrMode = (disableFIQ) ? OS_DisableInterrupts_IrqAndFiq() : OS_DisableInterrupts();
    lockp->ownerID = 0;
    if (ctrlFuncp)
    {
        ctrlFuncp();
    }
    lockp->lockFlag = 0;
    if (disableFIQ)
    {
        (void)OS_RestoreInterrupts_IrqAndFiq(lastIntrMode);
    }
    else
    {
        (void)OS_RestoreInterrupts(lastIntrMode);
    }
    return 0;
}

ARM_FUNC s32 OS_UnlockByWord(u16 lockID, OSLockWord* lockp, void (*ctrlFuncp) (void))
{
    return OSi_DoUnlockByWord(lockID, lockp, ctrlFuncp, FALSE);
}

ARM_FUNC s32 OSi_DoTryLockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
        BOOL disableFiq)
{
    OSIntrMode lastIntrMode = (disableFiq) ? OS_DisableInterrupts_IrqAndFiq() : OS_DisableInterrupts();

    s32 lastLockFlag = (s32)MI_SwapWord(lockID, &lockp->lockFlag);

    if (!lastLockFlag)
    {
        if (ctrlFuncp)
        {
            ctrlFuncp();
        }
        lockp->ownerID = lockID;
    }

    if (disableFiq)
    {
        (void)OS_RestoreInterrupts_IrqAndFiq(lastIntrMode);
    }
    else
    {
        (void)OS_RestoreInterrupts(lastIntrMode);
    }

    return lastLockFlag;
}

ARM_FUNC s32 OS_LockCartridge(u16 lockID)
{
    return OSi_DoLockByWord(lockID, (OSLockWord *)HW_CTRDG_LOCK_BUF, OSi_AllocateCartridgeBus, TRUE);
}

ARM_FUNC s32 OS_UnlockCartridge(u16 lockID)
{
    return OSi_DoUnlockByWord(lockID, (OSLockWord *)HW_CTRDG_LOCK_BUF, OSi_FreeCartridgeBus, TRUE);
}

ARM_FUNC s32 OS_TryLockCartridge(u16 lockID)
{
    return OSi_DoTryLockByWord(lockID, (OSLockWord *)HW_CTRDG_LOCK_BUF, OSi_AllocateCartridgeBus, TRUE);
}

ARM_FUNC void OSi_AllocateCartridgeBus()
{
    MIi_SetCartridgeProcessor(MI_PROCESSOR_ARM9);
}

ARM_FUNC void OSi_FreeCartridgeBus()
{
    MIi_SetCartridgeProcessor(MI_PROCESSOR_ARM7);
}
