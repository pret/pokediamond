#include "SND_command.h"
#include "SND_work.h"
#include "OS_system.h"
#include "OS_cache.h"

#define SND_CMD_WAIT_QUEUE_COUNT 8

static struct SNDCommand sCommandArray[SND_CMD_COUNT];
static struct SNDSharedWork sSharedWork;
static struct SNDCommand *sWaitingCommandListQueue[SND_CMD_WAIT_QUEUE_COUNT + 1];   // not sure why this is one element to large
static struct SNDCommand *sReserveList;
static struct SNDCommand *sReserveListEnd;
static struct SNDCommand *sFreeListEnd;
static s32 sWaitingCommandListQueueRead;
static s32 sWaitingCommandListQueueWrite;
static s32 sWaitingCommandListCount;
static u32 sCurrentTag;
static u32 sFinishedTag;
static struct SNDCommand *sFreeList;

// TODO remove these function declarations once they are in the headers
extern s32 PXI_SendWordByFifo(u32, u32, u32);
extern void PXI_SetFifoRecvCallback(u32, void (*)(s32, s32));
extern BOOL PXI_IsCallbackReady(u32, u32);

static void InitPXI(void);
static void RequestCommandProc(void);
static struct SNDCommand *AllocCommand(void);
static BOOL IsCommandAvailable(void);

ARM_FUNC void SND_CommandInit(void) {
    InitPXI();
    sFreeList = sCommandArray;
    for (int i = 0; i < SND_CMD_COUNT - 1; i++) {
        sCommandArray[i].llNext = &sCommandArray[i+1];
    }
    sCommandArray[SND_CMD_COUNT - 1].llNext = NULL;
    sFreeListEnd = &sCommandArray[SND_CMD_COUNT - 1];
    sReserveList = NULL;
    sReserveListEnd = NULL;
    sWaitingCommandListCount = 0;
    sWaitingCommandListQueueRead = 0;
    sWaitingCommandListQueueWrite = 0;
    sCurrentTag = 1;
    sFinishedTag = 0;
    SNDi_SharedWork = &sSharedWork;
    SNDi_InitSharedWork(SNDi_SharedWork);

    struct SNDCommand *cmd = SND_AllocCommand(SND_CMD_FLAG_BLOCK);
    if (cmd == NULL)
        return;

    cmd->id = SND_CMD_SET_SHARED_WORK;
    cmd->arg[0] = (u32)SNDi_SharedWork;
    SND_PushCommand(cmd);
    (void)SND_FlushCommand(SND_CMD_FLAG_BLOCK);
}

ARM_FUNC const struct SNDCommand *SND_RecvCommandReply(u32 flags) {
    OSIntrMode oldirq = OS_DisableInterrupts();

    if (flags & SND_CMD_FLAG_BLOCK) {
        u32 tag = SNDi_GetFinishedCommandTag();
        while (sFinishedTag == tag) {
            (void)OS_RestoreInterrupts(oldirq);
            OS_SpinWait(100);
            oldirq = OS_DisableInterrupts();
            tag = SNDi_GetFinishedCommandTag();
        }
    } else {
        u32 tag = SNDi_GetFinishedCommandTag();
        if (sFinishedTag == tag) {
            (void)OS_RestoreInterrupts(oldirq);
            return NULL;
        }
    }

    struct SNDCommand *queueRead = sWaitingCommandListQueue[sWaitingCommandListQueueRead];

    if (++sWaitingCommandListQueueRead > SND_CMD_WAIT_QUEUE_COUNT)
        sWaitingCommandListQueueRead = 0;

    struct SNDCommand *cur = queueRead;
    while (cur->llNext != NULL)
        cur = cur->llNext;

    if (sFreeListEnd != NULL) {
        sFreeListEnd->llNext = queueRead;
    } else {
        sFreeList = queueRead;
    }

    sFreeListEnd = cur;
    sWaitingCommandListCount--;
    sFinishedTag++;

    (void)OS_RestoreInterrupts(oldirq);
    return queueRead;
}

ARM_FUNC struct SNDCommand *SND_AllocCommand(u32 flags) {
    struct SNDCommand *cmd;
    if (!IsCommandAvailable())
        return NULL;

    cmd = AllocCommand();
    if (cmd != NULL)
        return cmd;

    if ((flags & SND_CMD_FLAG_BLOCK) == 0)
        return NULL;

    if (SND_CountWaitingCommand() > 0) {
        while (SND_RecvCommandReply(SND_CMD_FLAG_NOBLOCK) != NULL) { }

        cmd = AllocCommand();
        if (cmd != NULL)
            return cmd;
    } else {
        (void)SND_FlushCommand(SND_CMD_FLAG_BLOCK);
    }

    RequestCommandProc();
    
    do {
        (void)SND_RecvCommandReply(SND_CMD_FLAG_BLOCK);
        cmd = AllocCommand();
    } while (cmd == NULL);
    return cmd;
}

ARM_FUNC void SND_PushCommand(struct SNDCommand *cmd) {
    OSIntrMode oldirq = OS_DisableInterrupts();

    struct SNDCommand *newend = cmd;
    if (sReserveListEnd == NULL) {
        sReserveList = cmd;
        sReserveListEnd = cmd;
    } else {
        sReserveListEnd->llNext = cmd;
        sReserveListEnd = cmd;
    }

    cmd->llNext = NULL;

    (void)OS_RestoreInterrupts(oldirq);
}

ARM_FUNC BOOL SND_FlushCommand(u32 flags) {
    OSIntrMode oldirq = OS_DisableInterrupts();

    if (sReserveList == NULL) {
        (void)OS_RestoreInterrupts(oldirq);
        return TRUE;
    }

    if (sWaitingCommandListCount >= SND_CMD_WAIT_QUEUE_COUNT) {
        if ((flags & SND_CMD_FLAG_BLOCK) == 0) {
            (void)OS_RestoreInterrupts(oldirq);
            return FALSE;
        }

        do {
            (void)SND_RecvCommandReply(SND_CMD_FLAG_BLOCK);
        } while (sWaitingCommandListCount >= SND_CMD_WAIT_QUEUE_COUNT);
    }

    DC_FlushRange(sCommandArray, sizeof(sCommandArray));

    s32 result = PXI_SendWordByFifo(7, (u32)sReserveList, 0);
    if (result < 0) {
        if ((flags & SND_CMD_FLAG_BLOCK) == 0) {
            (void)OS_RestoreInterrupts(oldirq);
            return FALSE;
        }

        result = PXI_SendWordByFifo(7, (u32)sReserveList, 0);
        while (result < 0) {
            (void)OS_RestoreInterrupts(oldirq);
            OS_SpinWait(100);
            oldirq = OS_DisableInterrupts();
            result = PXI_SendWordByFifo(7, (u32)sReserveList, 0);
        }
    }

    if ((flags & SND_CMD_FLAG_IMMEDIATE) != 0) {
        RequestCommandProc();
    }

    sWaitingCommandListQueue[sWaitingCommandListQueueWrite] = sReserveList;

    if (++sWaitingCommandListQueueWrite > SND_CMD_WAIT_QUEUE_COUNT) {
        sWaitingCommandListQueueWrite = 0;
    }

    sReserveList = NULL;
    sReserveListEnd = NULL;
    sWaitingCommandListCount++;
    sCurrentTag++;

    (void)OS_RestoreInterrupts(oldirq);
    return TRUE;
}

ARM_FUNC void SND_WaitForCommandProc(u32 tag) {
    if (SND_IsFinishedCommandTag(tag))
        return;

    while (SND_RecvCommandReply(SND_CMD_FLAG_NOBLOCK) != NULL) { }

    if (SND_IsFinishedCommandTag(tag))
        return;

    RequestCommandProc();

    if (SND_IsFinishedCommandTag(tag))
        return;

    do {
        (void)SND_RecvCommandReply(SND_CMD_FLAG_BLOCK);
    } while (SND_IsFinishedCommandTag(tag) == 0);
}

ARM_FUNC u32 SND_GetCurrentCommandTag(void) {
    OSIntrMode oldirq = OS_DisableInterrupts();

    u32 retval;
    if (sReserveList == NULL)
        retval = sFinishedTag;
    else
        retval = sCurrentTag;

    (void)OS_RestoreInterrupts(oldirq);
    return retval;
}

ARM_FUNC BOOL SND_IsFinishedCommandTag(u32 tag) {
    OSIntrMode oldirq = OS_DisableInterrupts();

    BOOL result;
    if (tag > sFinishedTag) {
        if (tag - sFinishedTag < 0x80000000)
            result = FALSE;
        else
            result = TRUE;
    } else {
        if (sFinishedTag - tag < 0x80000000)
            result = TRUE;
        else
            result = FALSE;
    }

    (void)OS_RestoreInterrupts(oldirq);
    return result;
}

ARM_FUNC s32 SND_CountFreeCommand(void) {
    OSIntrMode oldirq = OS_DisableInterrupts();
    
    s32 count = 0;
    for (struct SNDCommand *cmd = sFreeList; cmd != NULL; cmd = cmd->llNext)
        count++;

    (void)OS_RestoreInterrupts(oldirq);
    return count;
}

ARM_FUNC s32 SND_CountReservedCommand(void) {
    OSIntrMode oldirq = OS_DisableInterrupts();
    
    s32 count = 0;
    for (struct SNDCommand *cmd = sReserveList; cmd != NULL; cmd = cmd->llNext)
        count++;

    (void)OS_RestoreInterrupts(oldirq);
    return count;
}

ARM_FUNC s32 SND_CountWaitingCommand(void) {
    return SND_CMD_COUNT - SND_CountFreeCommand() - SND_CountReservedCommand();
}

ARM_FUNC static void PxiFifoCallback(s32 a, s32 b) {
#pragma unused (a)
    OSIntrMode oldirq = OS_DisableInterrupts();
    SNDi_CallAlarmHandler(b);
    (void)OS_RestoreInterrupts(oldirq);
}

ARM_FUNC static void InitPXI(void) {
    PXI_SetFifoRecvCallback(7, PxiFifoCallback);

    if (!IsCommandAvailable())
        return;

    if (PXI_IsCallbackReady(7, 1))
        return;

    do {
        OS_SpinWait(100);
    } while (!PXI_IsCallbackReady(7, 1));
}

ARM_FUNC static void RequestCommandProc(void) {
    while (PXI_SendWordByFifo(7, 0, 0) < 0) { }
}

ARM_FUNC static struct SNDCommand *AllocCommand(void) {
    OSIntrMode oldirq = OS_DisableInterrupts();
    if (sFreeList == NULL) {
        (void)OS_RestoreInterrupts(oldirq);
        return NULL;
    }

    struct SNDCommand *retval = sFreeList;

    sFreeList = sFreeList->llNext;
    if (sFreeList == NULL)
        sFreeListEnd = NULL;
    (void)OS_RestoreInterrupts(oldirq);
    return retval;
}

ARM_FUNC static BOOL IsCommandAvailable(void) {
    if (!OS_IsRunOnEmulator())
        return TRUE;

    OSIntrMode oldirq = OS_DisableInterrupts();
    // TODO use proper register names here
    // is this some kind of debug or ensata register?
    *(vu32 *)0x4FFF200 = 0x10;
    u32 resp = *(vu32 *)0x4FFF200;
    (void)OS_RestoreInterrupts(oldirq);
    return resp != 0;
}
