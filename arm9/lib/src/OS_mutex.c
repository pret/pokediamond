#include "nitro/types.h"
#include "function_target.h"
#include "OS_mutex.h"
#include "OS_system.h"

ARM_FUNC void OS_InitMutex(OSMutex *mutex)
{
    OS_InitThreadQueue(&mutex->queue);
    mutex->thread = NULL;
    mutex->count = 0;
}

ARM_FUNC void OS_LockMutex(OSMutex *mutex)
{
    OSIntrMode prevIntrMode = OS_DisableInterrupts();
    OSThread *currentThread = OS_GetCurrentThread();

    OSThread *ownerThread;
    for (;;)
    {
        ownerThread = ((volatile OSMutex *)mutex)->thread;

        if (ownerThread == NULL)
        {
            mutex->thread = currentThread;
            mutex->count++;
            OSi_EnqueueTail(currentThread, mutex);
            break;
        }
        else if (ownerThread == currentThread)
        {
            mutex->count++;
            break;
        }
        else
        {
            currentThread->mutex = mutex;
            OS_SleepThread(&mutex->queue);
            currentThread->mutex = NULL;
        }
    }

    (void)OS_RestoreInterrupts(prevIntrMode);
}

ARM_FUNC void OS_UnlockMutex(OSMutex *mutex)
{
    OSIntrMode prevIntrMode = OS_DisableInterrupts();
    OSThread *currentThread = OS_GetCurrentThread();

    if (mutex->thread == currentThread && --mutex->count == 0)
    {
        OSi_DequeueItem(currentThread, mutex);
        mutex->thread = NULL;

        OS_WakeupThread(&mutex->queue);
    }

    (void)OS_RestoreInterrupts(prevIntrMode);
}

ARM_FUNC void OSi_UnlockAllMutex(OSThread *thread)
{
    OSMutex *mutex;
    while (thread->mutexQueue.head)
    {
        mutex = OSi_RemoveMutexLinkFromQueue(&thread->mutexQueue);

        mutex->count = 0;
        mutex->thread = NULL;
        OS_WakeupThread(&mutex->queue);
    }
}

ARM_FUNC BOOL OS_TryLockMutex(OSMutex *mutex)
{
    OSIntrMode prevIntrMode = OS_DisableInterrupts();
    OSThread *currentThread = OS_GetCurrentThread();
    BOOL locked;

    if (mutex->thread == NULL)
    {
        mutex->thread = currentThread;
        mutex->count++;
        OSi_EnqueueTail(currentThread, mutex);
        locked = TRUE;
    }
    else if (mutex->thread == currentThread)
    {
        mutex->count++;
        locked = TRUE;
    }
    else
    {
        locked = FALSE;
    }

    (void)OS_RestoreInterrupts(prevIntrMode);
    return locked;
}

ARM_FUNC void OSi_EnqueueTail(OSThread *thread, OSMutex *mutex)
{
    OSMutex *prev = thread->mutexQueue.tail;

    if (!prev)
    {
        thread->mutexQueue.head = mutex;
    }
    else
    {
        prev->link.next = mutex;
    }

    mutex->link.prev = prev;
    mutex->link.next = NULL;
    thread->mutexQueue.tail = mutex;
}

ARM_FUNC void OSi_DequeueItem(OSThread *thread, OSMutex *mutex)
{
    OSMutex *next = mutex->link.next;
    OSMutex *prev = mutex->link.prev;

    if (!next)
    {
        thread->mutexQueue.tail = prev;
    }
    else
    {
        next->link.prev = prev;
    }

    if(!prev)
    {
        thread->mutexQueue.head = next;
    }
    else
    {
        prev->link.next = next;
    }
}
