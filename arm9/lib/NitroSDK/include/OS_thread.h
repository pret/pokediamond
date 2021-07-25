#ifndef POKEDIAMOND_ARM9_OS_THREAD_H
#define POKEDIAMOND_ARM9_OS_THREAD_H

#include "nitro/types.h"
#include "OS_context.h"
#include "nitro/OS_thread_shared.h"

OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutexQueue *queue);
void OS_InitThread(void);
BOOL OS_IsThreadAvailable(void);
void OS_CreateThread(OSThread *thread, void (*func) (void *), void *arg, void *stack, u32 stackSize, u32 prio);
void OS_ExitThread(void);
void OS_DestroyThread(OSThread *thread);
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
OSSwitchThreadCallback OS_SetSwitchThreadCallback(OSSwitchThreadCallback callback);
u32 OS_DisableScheduler(void);
u32 OS_EnableScheduler(void);
void OS_SetThreadDestructor(OSThread *thread, OSThreadDestructor dtor);

#endif //POKEDIAMOND_ARM9_OS_THREAD_H
