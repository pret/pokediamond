#include "function_target.h"
#include "MI_memory.h"
#include "OS_thread.h"
#include "OS_mutex.h"
#include "OS_alarm.h"
#include "OS_system.h"
#include "OS_context.h"
#include "OS_terminate_proc.h"
#include "systemWork.h"
#include "mmap.h"

extern void SDK_SYS_STACKSIZE(void);
extern void SDK_IRQ_STACKSIZE(void);

extern void SDK_SECTION_ARENA_DTCM_START(void);

static s32 OSi_ThreadIdCount = 0;

u32 OSi_RescheduleCount = 0;

void *OSi_StackForDestructor = NULL;

BOOL OSi_IsThreadInitialized = FALSE;

OSThreadInfo OSi_ThreadInfo;

OSThread **OSi_CurrentThreadPtr = NULL;

void *OSi_SystemCallbackInSwitchThread = NULL;

OSThread OSi_LauncherThread;
OSThread OSi_IdleThread;

u32 OSi_IdleThreadStack[50];

static s32 OSi_GetUnusedThreadId(void);
static void OSi_InsertLinkToQueue(OSThreadQueue *queue, OSThread *thread);
static OSThread *OSi_RemoveLinkFromQueue(OSThreadQueue *queue);
static OSThread *OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue *queue, OSThread *thread);
static void OSi_InsertThreadToList(OSThread *thread);
static void OSi_RemoveThreadFromList(OSThread *thread);
static void OSi_ExitThread_ArgSpecified(OSThread *thread, void *arg);
static void OSi_ExitThread(void *arg);
static void OSi_ExitThread_Destroy(void);
static void OSi_CancelThreadAlarmForSleep(OSThread *thread);
static void OSi_SleepAlarmCallback(void *arg);
static void OSi_IdleThreadProc(void *);

ARM_FUNC static s32 OSi_GetUnusedThreadId(void)
{
    return ++OSi_ThreadIdCount;
}

ARM_FUNC static void OSi_InsertLinkToQueue(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *next = queue->head;

    while (next && next->priority <= thread->priority)
    {
        if (next == thread)
            return;
        next = next->link.next;
    }

    if (!next)
    {
        OSThread *prev = queue->tail;

        if (!prev)
        {
            queue->head = thread;
        }
        else
        {
            prev->link.next = thread;
        }

        thread->link.prev = prev;
        thread->link.next = NULL;
        queue->tail = thread;
    }
    else
    {
        OSThread *prev = next->link.prev;

        if (!prev)
        {
            queue->head = thread;
        }
        else
        {
            prev->link.next = thread;
        }

        thread->link.prev = prev;
        thread->link.next = next;
        next->link.prev = thread;
    }
}

ARM_FUNC static OSThread *OSi_RemoveLinkFromQueue(OSThreadQueue *queue)
{
    OSThread *thread = queue->head;

    if (thread)
    {
        OSThread *next = thread->link.next;

        queue->head = next;

        if (next)
        {
            next->link.prev = NULL;
        }
        else
        {
            queue->tail = NULL;
            thread->queue = NULL;
        }
    }

    return thread;
}

ARM_FUNC static OSThread *OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *queueHead = queue->head;

    while (queueHead)
    {
        OSThread *next = queueHead->link.next;

        if (queueHead == thread)
        {
            OSThread *prev = queueHead->link.prev;

            if (queue->head == queueHead)
            {
                queue->head = next;
            }
            else
            {
                prev->link.next = next;
            }

            if (queue->tail == queueHead)
            {
                queue->tail = prev;
            }
            else
            {
                next->link.prev = prev;
            }

            break;
        }

        queueHead = next;
    }

    return queueHead;
}

ARM_FUNC OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutexQueue *queue)
{
    OSMutex *mutexHead = queue->head;

    if (mutexHead)
    {
        OSMutex *next = mutexHead->link.next;

        queue->head = next;

        if (next)
        {
            next->link.prev = NULL;
        }
        else
        {
            queue->tail = NULL;
        }
    }

    return mutexHead;
}

ARM_FUNC static void OSi_InsertThreadToList(OSThread *thread)
{
    OSThread *t = OSi_ThreadInfo.list;
    OSThread *pre = NULL;

    while(t && t->priority < thread->priority)
    {
        pre = t;
        t = t->next;
    }

    if (!pre)
    {
        thread->next = OSi_ThreadInfo.list;
        OSi_ThreadInfo.list = thread;
    }
    else
    {
        thread->next = pre->next;
        pre->next = thread;
    }
}

ARM_FUNC static void OSi_RemoveThreadFromList(OSThread *thread)
{
    OSThread *t = OSi_ThreadInfo.list;
    OSThread *pre = NULL;

    while (t && t != thread)
    {
        pre = t;
        t = t-> next;
    }

    if (!pre)
    {
        OSi_ThreadInfo.list = thread->next;
    }
    else
    {
        pre->next = thread->next;
    }
}

ARM_FUNC static void OSi_RescheduleThread(void)
{
    if (OSi_RescheduleCount <= 0)
    {
        OSThreadInfo *info = &OSi_ThreadInfo;
        if (info->irqDepth > 0 || OS_GetProcMode() == OS_PROCMODE_IRQ)
        {
            info->isNeedRescheduling = TRUE;
        }
        else
        {
            OSThread *currentThread = OSi_GetCurrentThread();
            OSThread *nextThread = OS_SelectThread();

            if (currentThread == nextThread || !nextThread)
                return;

            if (currentThread->state != OS_THREAD_STATE_TERMINATED
                && OS_SaveContext(&currentThread->context))
                return;

            if (OSi_SystemCallbackInSwitchThread)
            {
                ((OSSwitchThreadCallback)OSi_SystemCallbackInSwitchThread) (currentThread, nextThread);
            }

            if (info->switchCallback)
            {
                ((OSSwitchThreadCallback)info->switchCallback) (currentThread, nextThread);
            }

            OS_SetCurrentThread(nextThread);

            OS_LoadContext(&nextThread->context);
        }
    }
}

ARM_FUNC void OS_InitThread(void)
{
    if (OSi_IsThreadInitialized)
        return;
    OSi_IsThreadInitialized = TRUE;

    OSi_CurrentThreadPtr = &(OSi_ThreadInfo.current);

    OSi_LauncherThread.priority = OS_THREAD_LAUNCHER_PRIORITY;
    OSi_LauncherThread.id = 0;
    OSi_LauncherThread.state = OS_THREAD_STATE_READY;
    OSi_LauncherThread.next = NULL;

    OSi_LauncherThread.profiler = NULL;

    OSi_ThreadInfo.list = &OSi_LauncherThread;

    OS_SetCurrentThread(&OSi_LauncherThread);

    void *stackLo = (((s32)SDK_SYS_STACKSIZE) <= 0) ?
              (void *)((u32)SDK_SECTION_ARENA_DTCM_START - (s32)SDK_SYS_STACKSIZE) :
              (void *)((u32)(HW_DTCM_SVC_STACK - (s32)SDK_IRQ_STACKSIZE) - (s32)SDK_SYS_STACKSIZE);

    OSi_LauncherThread.stackBottom = (u32)(HW_DTCM_SVC_STACK - (s32)SDK_IRQ_STACKSIZE);
    OSi_LauncherThread.stackTop = (u32)stackLo;
    OSi_LauncherThread.stackWarningOffset = 0;

    //checksums
    *(u32 *)(OSi_LauncherThread.stackBottom - sizeof(u32)) = 0xfddb597dUL;
    *(u32 *)OSi_LauncherThread.stackTop = 0x7bf9dd5bUL;

    OS_InitThreadQueue(&OSi_LauncherThread.joinQueue);

    OSi_ThreadInfo.isNeedRescheduling = FALSE;
    OSi_ThreadInfo.irqDepth = 0;

    OS_GetSystemWork()->threadinfo_mainp = &OSi_ThreadInfo;

    (void)OS_SetSwitchThreadCallback(NULL);

    OS_CreateThread(&OSi_IdleThread, OSi_IdleThreadProc, NULL,
            OSi_IdleThreadStack + 50, 200, OS_THREAD_PRIORITY_MAX);

    OSi_IdleThread.priority = OS_THREAD_PRIORITY_MAX + 1;
    OSi_IdleThread.state = OS_THREAD_STATE_READY;
}

ARM_FUNC asm BOOL OS_IsThreadAvailable(void)
{
    ldr r0, =OSi_IsThreadInitialized
    ldr r0, [r0, #0]
    bx lr
}

ARM_FUNC void OS_CreateThread(OSThread *thread, void (*func) (void *), void *arg, void *stack, u32 stackSize, u32 prio)
{
    OSIntrMode enable = OS_DisableInterrupts();

    s32 index = OSi_GetUnusedThreadId();

    thread->priority = prio;
    thread->id = (u32)index;
    thread->state = OS_THREAD_STATE_WAITING;

    thread->profiler = NULL;

    OSi_InsertThreadToList(thread);

    thread->stackBottom = (u32)stack;
    thread->stackTop = (u32)stack - stackSize;
    thread->stackWarningOffset = 0;

    *(u32 *)(thread->stackBottom - sizeof(u32)) = 0xfddb597dUL;
    *(u32 *)thread->stackTop = 0x7bf9dd5bUL;

    OS_InitThreadQueue(&thread->joinQueue);

    OS_InitContext(&thread->context, (u32)func, (u32)stack - 4);

    thread->context.r[0] = (u32)arg;
    thread->context.lr = (u32)OS_ExitThread;

    MI_CpuClear32((void *)((u32)stack - stackSize + 4), stackSize - 8);

    thread->mutex = NULL;
    thread->mutexQueue.head = NULL;
    thread->mutexQueue.tail = NULL;

    OS_SetThreadDestructor(thread, NULL);

    thread->queue = NULL;
    thread->link.prev = thread->link.next = NULL;

    MI_CpuClear32(&thread->specific[0], sizeof(void *) * OS_THREAD_SPECIFIC_MAX);

    thread->alarmForSleep = NULL;

    (void)OS_RestoreInterrupts(enable);
}

ARM_FUNC void OS_ExitThread(void)
{
    (void)OS_DisableInterrupts();
    OSi_ExitThread_ArgSpecified(OS_GetCurrentThread(), 0);
}

ARM_FUNC static void OSi_ExitThread_ArgSpecified(OSThread *thread, void *arg)
{
    if (OSi_StackForDestructor)
    {
        OS_InitContext(&thread->context, (u32)OSi_ExitThread, (u32)OSi_StackForDestructor);
        thread->context.r[0] = (u32)arg;
        thread->context.cpsr |= HW_PSR_DISABLE_IRQ;
        thread->state = OS_THREAD_STATE_READY;
        OS_LoadContext(&thread->context);
    }
    else
    {
        OSi_ExitThread(arg);
    }
}

ARM_FUNC static void OSi_ExitThread(void *arg)
{
    OSThread *currentThread = OSi_GetCurrentThread();
    OSThreadDestructor destructor = currentThread->destructor;

    if (destructor)
    {
        currentThread->destructor = NULL;
        destructor(arg);
        (void)OS_DisableInterrupts();
    }

    OSi_ExitThread_Destroy();
}

ARM_FUNC static void OSi_ExitThread_Destroy(void)
{
    OSThread *currentThread = OSi_GetCurrentThread();
    (void)OS_DisableScheduler();

    OSi_UnlockAllMutex(currentThread);

    if (currentThread->queue)
    {
        (void)OSi_RemoveSpecifiedLinkFromQueue(currentThread->queue, currentThread);
    }

    OSi_RemoveThreadFromList(currentThread);

    currentThread->state = OS_THREAD_STATE_TERMINATED;

    OS_WakeupThread(&currentThread->joinQueue);

    (void)OS_EnableScheduler();

    OS_RescheduleThread();

    OS_Terminate();
}

ARM_FUNC void OS_DestroyThread(OSThread *thread)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    if (OS_GetCurrentThread() == thread)
    {
        OSi_ExitThread_Destroy();
    }

    (void)OS_DisableScheduler();

    OSi_UnlockAllMutex(thread);

    OSi_CancelThreadAlarmForSleep(thread);

    if (thread->queue)
    {
        (void)OSi_RemoveSpecifiedLinkFromQueue(thread->queue, thread);
    }

    OSi_RemoveThreadFromList(thread);

    thread->state = OS_THREAD_STATE_TERMINATED;

    OS_WakeupThread(&thread->joinQueue);

    (void)OS_EnableScheduler();
    (void)OS_RestoreInterrupts(enabled);

    OS_RescheduleThread();
}

ARM_FUNC static void OSi_CancelThreadAlarmForSleep(OSThread *thread)
{
    OSAlarm *alarm = thread->alarmForSleep;

    if (alarm)
    {
        OS_CancelAlarm(alarm);
    }
}

ARM_FUNC void OS_JoinThread(OSThread *thread)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    if (thread->state != OS_THREAD_STATE_TERMINATED)
    {
        OS_SleepThread(&thread->joinQueue);
    }

    (void)OS_RestoreInterrupts(enabled);
}

ARM_FUNC BOOL OS_IsThreadTerminated(const OSThread *thread)
{
    return (thread->state == OS_THREAD_STATE_TERMINATED) ? TRUE : FALSE;
}

ARM_FUNC void OS_SleepThread(OSThreadQueue *queue)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    OSThread *currentThread = OSi_GetCurrentThread();

    if (queue)
    {
        currentThread->queue = queue;
        OSi_InsertLinkToQueue(queue, currentThread);
    }

    currentThread->state = OS_THREAD_STATE_WAITING;
    OSi_RescheduleThread();

    (void)OS_RestoreInterrupts(enabled);
}

ARM_FUNC void OS_WakeupThread(OSThreadQueue *queue)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    if (queue->head)
    {
        while (queue->head)
        {
            OSThread *thread = OSi_RemoveLinkFromQueue(queue);

            thread->state = OS_THREAD_STATE_READY;
            thread->queue = NULL;
            thread->link.prev = thread->link.next = NULL;
        }

        OS_InitThreadQueue(queue);
        OSi_RescheduleThread();
    }

    (void)OS_RestoreInterrupts(enabled);
}

ARM_FUNC void OS_WakeupThreadDirect(OSThread *thread)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    thread->state = OS_THREAD_STATE_READY;
    OSi_RescheduleThread();

    (void)OS_RestoreInterrupts(enabled);
}

ARM_FUNC OSThread *OS_SelectThread(void)
{
    OSThread *thread = OSi_ThreadInfo.list;

    while (thread && !OS_IsThreadRunnable(thread))
    {
        thread = thread->next;
    }

    return thread;
}

ARM_FUNC void OS_RescheduleThread(void)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    OSi_RescheduleThread();
    (void)OS_RestoreInterrupts(enabled);
}

ARM_FUNC void OS_YieldThread(void)
{
    OSThread *current = OS_GetCurrentThread();
    OSThread *pre = NULL;
    OSThread *lastThread = NULL;
    s32 samePriorityThread = 0;
    OSIntrMode enabled = OS_DisableInterrupts();

    OSThread *t = OSi_ThreadInfo.list;
    OSThread *tPre = NULL;

    while (t)
    {
        if (t == current)
        {
            pre = tPre;
        }

        if (current->priority == t->priority)
        {
            lastThread = t;
            samePriorityThread++;
        }

        tPre = t;
        t = t->next;
    }

    if (samePriorityThread <= 1 || lastThread == current)
    {
        (void)OS_RestoreInterrupts(enabled);
        return;
    }

    if (!pre)
    {
        OSi_ThreadInfo.list = current->next;
    }
    else
    {
        pre->next = current->next;
    }

    current->next = lastThread->next;
    lastThread->next = current;

    OSi_RescheduleThread();

    (void)OS_RestoreInterrupts(enabled);
}

ARM_FUNC BOOL OS_SetThreadPriority(OSThread *thread, u32 prio)
{
    OSThread *t = OSi_ThreadInfo.list;
    OSThread *pre = NULL;
    OSIntrMode enabled = OS_DisableInterrupts();

    while (t && t != thread)
    {
        pre = t;
        t = t->next;
    }

    if (!t || t == &OSi_IdleThread)
    {
        (void)OS_RestoreInterrupts(enabled);
        return FALSE;
    }

    if (t->priority != prio)
    {
        if (!pre)
        {
            OSi_ThreadInfo.list = thread->next;
        }
        else
        {
            pre->next = thread->next;
        }

        thread->priority = prio;
        OSi_InsertThreadToList(thread);

        OSi_RescheduleThread();
    }

    (void)OS_RestoreInterrupts(enabled);

    return TRUE;
}

ARM_FUNC u32 OS_GetThreadPriority(const OSThread *thread)
{
    return thread->priority;
}

ARM_FUNC void OS_Sleep(u32 msec)
{
    OSAlarm alarm;

    OS_CreateAlarm(&alarm);
    OSThread *volatile p_thread = OSi_GetCurrentThread();
    OSIntrMode enabled = OS_DisableInterrupts();

    p_thread->alarmForSleep = &alarm;

    OS_SetAlarm(&alarm, OS_MilliSecondsToTicks(msec), &OSi_SleepAlarmCallback,
                (void*)&p_thread);
    while (p_thread != NULL)
    {
        OS_SleepThread(NULL);
    }
    (void)OS_RestoreInterrupts(enabled);
}

ARM_FUNC static void OSi_SleepAlarmCallback(void *arg)
{
    OSThread **pp_thread = (OSThread **)arg;
    OSThread *p_thread = *pp_thread;
    *pp_thread = NULL;

    p_thread->alarmForSleep = NULL;

    OS_WakeupThreadDirect(p_thread);
}

ARM_FUNC OSSwitchThreadCallback OS_SetSwitchThreadCallback(OSSwitchThreadCallback callback)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    OSSwitchThreadCallback prev = OSi_ThreadInfo.switchCallback;
    OSi_ThreadInfo.switchCallback = callback;

    (void)OS_RestoreInterrupts(enabled);
    return prev;
}

ARM_FUNC static void OSi_IdleThreadProc(void *)
{
    (void)OS_EnableInterrupts();
    while (1)
    {
        OS_Halt();
    }
}

ARM_FUNC u32 OS_DisableScheduler(void)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    u32 count;

    if (OSi_RescheduleCount < (u32)-1)
    {
        count = OSi_RescheduleCount++;
    }
    (void)OS_RestoreInterrupts(enabled);

    return count;
}

ARM_FUNC u32 OS_EnableScheduler(void)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    u32 count = 0;

    if (OSi_RescheduleCount > 0)
    {
        count = OSi_RescheduleCount--;
    }
    (void)OS_RestoreInterrupts(enabled);

    return count;
}

ARM_FUNC void OS_SetThreadDestructor(OSThread *thread, OSThreadDestructor dtor)
{
    thread->destructor = dtor;
}
