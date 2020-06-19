#ifndef POKEDIAMOND_ARM9_OS_MUTEX_H
#define POKEDIAMOND_ARM9_OS_MUTEX_H

#include "OS_thread.h"
#include "OS_context.h"
#include "nitro/OS_mutex_shared.h"

void OSi_UnlockAllMutex(OSThread * thread);

#endif //POKEDIAMOND_ARM9_OS_MUTEX_H
