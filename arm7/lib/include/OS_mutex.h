#ifndef POKEDIAMOND_ARM7_OS_MUTEX_H
#define POKEDIAMOND_ARM7_OS_MUTEX_H

#include "OS_context.h"
#include "nitro/OS_mutex_shared.h"

void OS_InitMutex(OSMutex* mutex);
void OSi_UnlockAllMutex(OSThread * thread);

#endif //POKEDIAMOND_ARM7_OS_MUTEX_H
