#include "function_target.h"
#include "OS_mutex.h"

ARM_FUNC void OS_InitMutex(OSMutex* mutex) {
    OS_InitThreadQueue(&mutex->queue);
    mutex->thread = NULL;
    mutex->count = 0;
}
