#ifndef GUARD_OS_SHARED_MUTEX_H
#define GUARD_OS_SHARED_MUTEX_H

#include "nitro/types.h"
#include "nitro/OS_thread_shared.h"

struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutexLink link;
};

#endif
