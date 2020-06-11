#ifndef POKEDIAMOND_OS_TICK_H
#define POKEDIAMOND_OS_TICK_H

#include "consts.h"

typedef u64 OSTick;

#define OS_SYSTEM_CLOCK HW_SYSTEM_CLOCK

#define OS_MilliSecondsToTicks(msec) ((OSTick)(((OS_SYSTEM_CLOCK/1000) * (u64)(msec)) / 64))

#endif //POKEDIAMOND_OS_TICK_H
