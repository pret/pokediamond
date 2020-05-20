//
// Created by mart on 4/12/20.
//

#ifndef POKEDIAMOND_OS_INIT_H
#define POKEDIAMOND_OS_INIT_H

#include "types.h"
#include "consts.h"
#include "OS_tcm.h"
#include "OS_spinLock.h"
#include "OS_context.h"
#include "OS_tick.h"
#include "OS_alarm.h"
#include "OS_mutex.h"
#include "OS_thread.h"
#include "OS_protectionRegion.h"
#include "OS_entropy.h"
#include "OS_emulator.h"
#include "OS_arena.h"
#include "OS_alloc.h"
#include "OS_system.h"
#include "OS_terminate_proc.h"
#include "OS_interrupt.h"
#include "OS_reset.h"

void OS_Init();

#endif //POKEDIAMOND_OS_INIT_H
