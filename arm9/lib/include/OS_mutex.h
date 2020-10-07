#ifndef POKEDIAMOND_ARM9_OS_MUTEX_H
#define POKEDIAMOND_ARM9_OS_MUTEX_H

#include "OS_thread.h"
#include "OS_context.h"
#include "nitro/OS_mutex_shared.h"
#include "nitro/types.h"

void OS_InitMutex(OSMutex *mutex);
void OS_LockMutex(OSMutex *mutex);
void OS_UnlockMutex(OSMutex *mutex);
void OSi_UnlockAllMutex(OSThread * thread);
BOOL OS_TryLockMutex(OSMutex *mutex);
void OSi_EnqueueTail(OSThread *thread, OSMutex *mutex);
void OSi_DequeueItem(OSThread *thread, OSMutex *mutex);

#endif //POKEDIAMOND_ARM9_OS_MUTEX_H
