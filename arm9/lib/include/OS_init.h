#ifndef POKEDIAMOND_ARM9_OS_INIT_H
#define POKEDIAMOND_ARM9_OS_INIT_H

#include "nitro/types.h"
#include "consts.h"
#include "OS_tcm.h"
#include "OS_spinLock.h"
#include "OS_context.h"
#include "OS_timer.h"
#include "OS_tick.h"
#include "OS_alarm.h"
#include "OS_mutex.h"
#include "OS_thread.h"
#include "OS_protectionRegion.h"
#include "OS_protectionUnit.h"
#include "OS_entropy.h"
#include "OS_emulator.h"
#include "OS_arena.h"
#include "OS_alloc.h"
#include "OS_system.h"
#include "OS_terminate_proc.h"
#include "OS_irqHandler.h"
#include "OS_irqTable.h"
#include "OS_interrupt.h"
#include "OS_reset.h"
#include "OS_exception.h"
#include "OS_message.h"
#include "OS_valarm.h"
#include "OS_vramExclusive.h"

void OS_Init(void);

#endif //POKEDIAMOND_ARM9_OS_INIT_H
