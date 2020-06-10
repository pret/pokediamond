#ifndef POKEDIAMOND_OS_THREAD_H
#define POKEDIAMOND_OS_THREAD_H

#include "nitro/types.h"
#include "OS_context.h"

typedef struct OSiAlarm OSAlarm;

typedef struct _OSThread OSThread;

typedef struct _OSThreadQueue OSThreadQueue;
typedef struct _OSThreadLink OSThreadLink;
typedef struct _OSMutexQueue OSMutexQueue;
typedef struct _OSMutexLink OSMutexLink;
typedef struct OSMutex OSMutex;

struct _OSThreadQueue
{
    OSThread *head;
    OSThread *tail;
};

struct _OSThreadLink
{
    OSThread *prev;
    OSThread *next;
};

struct _OSMutexQueue
{
    OSMutex *head;
    OSMutex *tail;
};

struct _OSMutexLink
{
    OSMutex *next;
    OSMutex *prev;
};

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread* current;
    OSThread* list;
    void* switchCallback; // type: OSSwitchThreadCallback
} OSThreadInfo;

typedef enum {
    OS_THREAD_STATE_WAITING = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_TERMINATED = 2
} OSThreadState;

typedef void (*OSSwitchThreadCallback) (OSThread *from, OSThread *to);

typedef void (*OSThreadDestructor) (void *);

struct _OSThread
{
    OSContext context;
    OSThreadState state;
    OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;

    OSThreadQueue *queue;
    OSThreadLink link;

    OSMutex *mutex;
    OSMutexQueue mutexQueue;

    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;

    OSThreadQueue joinQueue;

    void *specific[3];
    OSAlarm *alarmForSleep;
    OSThreadDestructor destructor;
    void *userParameter;

    u32 systemErrno;
};

static s32 OSi_GetUnusedThreadId(void);
static void OSi_InsertLinkToQueue(OSThreadQueue *queue, OSThread *thread);
static OSThread *OSi_RemoveLinkFromQueue(OSThreadQueue *queue);
static OSThread *OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue *queue, OSThread *thread);
OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutexQueue *queue);
static void OSi_InsertThreadToList(OSThread *thread);
static void OSi_RemoveThreadFromList(OSThread *thread);
void OS_InitThread(void);
BOOL OS_IsThreadAvailable(void);
void OS_CreateThread(OSThread *thread, void (*func) (void *), void *arg, void *stack, u32 stackSize, u32 prio);
void OS_ExitThread(void);
static void OSi_ExitThread_ArgSpecified(OSThread *thread, void *arg);
static void OSi_ExitThread(void *arg);
static void OSi_ExitThread_Destroy(void);
void OS_DestroyThread(OSThread *thread);
static void OSi_CancelThreadAlarmForSleep(OSThread *thread);
void OS_JoinThread(OSThread *thread);
BOOL OS_IsThreadTerminated(const OSThread *thread);
void OS_SleepThread(OSThreadQueue *queue);
void OS_WakeupThread(OSThreadQueue *queue);
void OS_WakeupThreadDirect(OSThread *thread);
OSThread *OS_SelectThread(void);
void OS_RescheduleThread(void);
void OS_YieldThread(void);
BOOL OS_SetThreadPriority(OSThread *thread, u32 prio);
u32 OS_GetThreadPriority(const OSThread *thread);
void OS_Sleep(u32 msec);
static void OSi_SleepAlarmCallback(void *arg);
OSSwitchThreadCallback OS_SetSwitchThreadCallback(OSSwitchThreadCallback callback);
static void OSi_IdleThreadProc(void *);
u32 OS_DisableScheduler(void);
u32 OS_EnableScheduler(void);
void OS_SetThreadDestructor(OSThread *thread, OSThreadDestructor dtor);

extern OSThreadInfo OSi_ThreadInfo;

static inline OSThreadInfo *OS_GetThreadInfo(void)
{
    return &OSi_ThreadInfo;
}

static inline BOOL OS_IsThreadRunnable(const OSThread *thread)
{
    return thread->state == OS_THREAD_STATE_READY;
}

static inline void OS_InitThreadQueue(OSThreadQueue * queue)
{
    queue->head = queue->tail = NULL;
}

static inline OSThread *OS_GetCurrentThread(void)
{
    return OS_GetThreadInfo()->current;
}

static inline void OS_SetCurrentThread(OSThread *thread)
{
    OS_GetThreadInfo()->current = thread;
}

#define OSi_GetCurrentThread()          (*OSi_CurrentThreadPtr)

#endif //POKEDIAMOND_OS_THREAD_H
