#ifndef POKEDIAMOND_OS_MUTEX_H
#define POKEDIAMOND_OS_MUTEX_H

#include "nitro/types.h"
#include "OS_thread.h"

struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutexLink link;
};

void OSi_UnlockAllMutex(OSThread * thread);

#endif //POKEDIAMOND_OS_MUTEX_H
