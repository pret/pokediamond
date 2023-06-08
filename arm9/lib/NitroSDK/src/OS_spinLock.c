#include "OS_spinLock.h"

#include "OS_system.h"
#include "mmap.h"
#include "MI_exMemory.h"
#include "code32.h"

extern void MIi_CpuClear32(u32 param1, void * addr, u32 length); //not too sure about names
extern u32 MI_SwapWord(u32 data, volatile u32* destp);

void OS_InitLock(void)
{
    static BOOL isInitialized = FALSE;

    if (isInitialized)
    {
        return;
    }
    isInitialized = TRUE;

    OSLockWord* lockp = (OSLockWord *)HW_INIT_LOCK_BUF;

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

s32 OSi_DoLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void),
                                     BOOL disableFiq)
{
    s32 lastLockFlag;
    while ((lastLockFlag = OSi_DoTryLockByWord(lockId, lockp, ctrlFuncp, disableFiq)) > 0) {
        OSi_WaitByLoop();
    }

    return lastLockFlag;
}

s32 OS_TryLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void))
{
    return OSi_DoLockByWord(lockId, lockp, ctrlFuncp, FALSE);
}

s32 OSi_DoUnlockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
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

s32 OS_UnlockByWord(u16 lockID, OSLockWord* lockp, void (*ctrlFuncp) (void))
{
    return OSi_DoUnlockByWord(lockID, lockp, ctrlFuncp, FALSE);
}

s32 OSi_DoTryLockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
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

s32 OS_LockCartridge(u16 lockID)
{
    return OSi_DoLockByWord(lockID, (OSLockWord *)HW_CTRDG_LOCK_BUF, OSi_AllocateCartridgeBus, TRUE);
}

s32 OS_UnlockCartridge(u16 lockID)
{
    return OSi_DoUnlockByWord(lockID, (OSLockWord *)HW_CTRDG_LOCK_BUF, OSi_FreeCartridgeBus, TRUE);
}

s32 OS_TryLockCartridge(u16 lockID)
{
    return OSi_DoTryLockByWord(lockID, (OSLockWord *)HW_CTRDG_LOCK_BUF, OSi_AllocateCartridgeBus, TRUE);
}

void OSi_AllocateCartridgeBus(void)
{
    MIi_SetCartridgeProcessor(MI_PROCESSOR_ARM9);
}

void OSi_FreeCartridgeBus(void)
{
    MIi_SetCartridgeProcessor(MI_PROCESSOR_ARM7);
}

s32 OS_TryLockCard(u16 lockID)
{
    return OS_TryLockByWord(lockID, (OSLockWord *)HW_CARD_LOCK_BUF, OSi_AllocateCardBus);
}

s32 OS_UnlockCard(u16 lockID)
{
    return OS_UnlockByWord(lockID, (OSLockWord *)HW_CARD_LOCK_BUF, OSi_FreeCardBus);
}

void OSi_AllocateCardBus(void)
{
    MIi_SetCardProcessor(MI_PROCESSOR_ARM9);
}

void OSi_FreeCardBus(void)
{
    MIi_SetCardProcessor(MI_PROCESSOR_ARM7);
}

u16 OS_ReadOwnerOfLockWord(OSLockWord * lock)
{
    return lock->ownerID;
}

asm s32 OS_UnLockCartridge(u16 lockID)
{
    ldr r1, =OS_UnlockCartridge
    bx r1
}

asm s32 OS_GetLockID(void)
{
    ldr r3, =HW_LOCK_ID_FLAG_MAIN
    ldr r1, [r3, #0x0]
    clz r2, r1
    cmp r2, #0x20
    movne r0, #0x40
    bne _020CA0D4
    add r3, r3, #0x4
    ldr r1, [r3, #0x0]
    clz r2, r1
    cmp r2, #0x20
    ldr r0, =0xFFFFFFFD
    bxeq lr
    mov r0, #0x60
_020CA0D4:
    add r0, r0, r2
    mov r1, #0x80000000
    mov r1, r1, lsr r2
    ldr r2, [r3, #0x0]
    bic r2, r2, r1
    str r2, [r3, #0x0]
    bx lr
}

asm void OS_ReleaseLockID(register u16 lockID)
{
    ldr r3, =HW_LOCK_ID_FLAG_MAIN
    cmp r0, #0x60
    addpl r3, r3, #0x4
    subpl r0, r0, #0x60
    submi r0, r0, #0x40
    mov r1, #0x80000000
    mov r1, r1, lsr r0
    ldr r2, [r3, #0x0]
    orr r2, r2, r1
    str r2, [r3, #0x0]
    bx lr
}
