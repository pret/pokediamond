#ifndef POKEDIAMOND_ARM9_OS_THREAD_H
#define POKEDIAMOND_ARM9_OS_THREAD_H

#include "nitro/types.h"
#include "OS_context.h"
#include "nitro/OS_thread_shared.h"

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

#endif //POKEDIAMOND_ARM9_OS_THREAD_H
