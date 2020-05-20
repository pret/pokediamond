//
// Created by red031000 on 2020-05-17.
//

#ifndef POKEDIAMOND_OS_MUTEX_H
#define POKEDIAMOND_OS_MUTEX_H

#include "types.h"
#include "OS_thread.h"

struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutexLink link;
};

#endif //POKEDIAMOND_OS_MUTEX_H
