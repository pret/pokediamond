#ifndef POKEDIAMOND_ARM7_OS_INIT_H
#define POKEDIAMOND_ARM7_OS_INIT_H

#include "nitro/types.h"
#include "OS_system.h"
#include "OS_arena.h"
#include "OS_alloc.h"
#include "OS_reset.h"
#include "OS_terminate_proc.h"
#include "OS_spinLock.h"
#include "OS_context.h"
#include "OS_interrupt.h"

void OS_Init(void);

#endif //POKEDIAMOND_ARM7_OS_INIT_H
