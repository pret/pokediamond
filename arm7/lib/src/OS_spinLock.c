#include "function_target.h"
#include "OS_spinLock.h"
#include "OS_system.h"
#include "MI_swap.h"

ARM_FUNC void OS_InitLock(void)
{
    static BOOL isInitialized = FALSE;

    if (isInitialized)
        return;
    isInitialized = TRUE;

    OSLockWord *lockp = (OSLockWord *)HW_INIT_LOCK_BUF;

    lockp->extension = 0;
    while (lockp->ownerID != 0x7f)
    {
        OSi_WaitByLoop();
    }

    ((u32 *)HW_LOCK_ID_FLAG_SUB)[0] = 0xffffffff;
    ((u32 *)HW_LOCK_ID_FLAG_SUB)[1] = 0xffff0000;

    lockp->extension = 0xbf;
}

ARM_FUNC void FUN_037F8CB4(s32 ct)
{
    SVC_WaitByLoop((u32)ct); //todo this should be linker generated, figure out why it broke
}

ARM_FUNC s32 OSi_DoLockByWord(u16 lockId, OSLockWord *lockp, void (*ctrlFuncp) (void),
                              BOOL disableFiq)
{
    s32 lastLockFlag;
    while ((lastLockFlag = OSi_DoTryLockByWord(lockId, lockp, ctrlFuncp, disableFiq)) > 0) {
        OSi_WaitByLoop();
    }

    return lastLockFlag;
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

ARM_FUNC s32 OSi_DoTryLockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void),
                                 BOOL disableFiq)
{
    OSIntrMode lastIntrMode = (disableFiq) ? OS_DisableInterrupts_IrqAndFiq() : OS_DisableInterrupts();

    s32 lastLockFlag = (s32)MI_SwapWord(lockID, (u32 *)&lockp->lockFlag);

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

ARM_FUNC void OSi_AllocateCartridgeBus(void)
{
    //noop
}

ARM_FUNC void OSi_FreeCartridgeBus(void)
{
    //noop
}

ARM_FUNC u16 OS_ReadOwnerOfLockWord(OSLockWord * lock)
{
    return lock->ownerID;
}

ARM_FUNC asm s32 OS_UnLockCartridge(u16 lockID)
{
    ldr r1, =OS_UnlockCartridge
    bx r1
}

ARM_FUNC asm s32 OS_GetLockID(void)
{
    ldr	r3, =HW_LOCK_ID_FLAG_SUB
    ldr	r1, [r3]
    mov	r2, #0
    mov	r0, #0x80000000
_037F8A34:
    tst	r1, r0
    bne	_037F8A50
    add	r2, r2, #1
    cmp	r2, #32
    beq	_037F8A50
    mov	r0, r0, lsr #1
    b	_037F8A34
_037F8A50:
    cmp	r2, #32
    movne	r0, #0x80
    bne	_037F8A98
    add	r3, r3, #4
    ldr	r1, [r3]
    mov	r2, #0
    mov	r0, #0x80000000
_037F8A6C:
    tst	r1, r0
    bne	_037F8A88
    add	r2, r2, #1
    cmp	r2, #32
    beq	_037F8A88
    mov	r0, r0, lsr #1
    b	_037F8A6C
_037F8A88:
    cmp	r2, #32
    ldr	r0, =0xFFFFFFFD
    bxeq	lr
    mov	r0, #160
_037F8A98:
    add	r0, r0, r2
    mov	r1, #0x80000000
    mov	r1, r1, lsr r2
    ldr	r2, [r3]
    bic	r2, r2, r1
    str	r2, [r3]
    bx	lr
}

ARM_FUNC asm void OS_ReleaseLockID(register u16 lockID)
{
    ldr r3, =HW_LOCK_ID_FLAG_SUB
    cmp r0, #0xa0
    addpl r3, r3, #0x4
    subpl r0, r0, #0xa0
    submi r0, r0, #0x80
    mov r1, #0x80000000
    mov r1, r1, lsr r0
    ldr r2, [r3, #0x0]
    orr r2, r2, r1
    str r2, [r3, #0x0]
    bx lr
}
