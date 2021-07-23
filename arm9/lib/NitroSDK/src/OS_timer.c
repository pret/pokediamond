#include "OS_timer.h"
#include "function_target.h"

static u16 OSi_TimerReserved = 0;

ARM_FUNC void OSi_SetTimerReserved(s32 timerNum)
{
    OSi_TimerReserved |= (1 << timerNum);
}
