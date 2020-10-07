#include "function_target.h"
#include "OS_tick.h"
#include "OS_interrupt.h"
#include "OS_timer.h"
#include "OS_system.h"

static u16 OSi_UseTick = FALSE;
vu64 OSi_TickCounter;
BOOL OSi_NeedResetTimer = FALSE;

static void OSi_CountUpTick(void);

ARM_FUNC void OS_InitTick(void)
{
    if (OSi_UseTick)
    {
        return;
    }
    OSi_UseTick = 1;
    OSi_SetTimerReserved(0);
    OSi_TickCounter = 0;
    reg_OS_TM0CNT_H = 0;
    reg_OS_TM0CNT_L = 0;
    reg_OS_TM0CNT_H = 0xc1;
    OS_SetIrqFunction(8, OSi_CountUpTick);
    (void)OS_EnableIrqMask(8);
    OSi_NeedResetTimer = FALSE;
}

ARM_FUNC BOOL OS_IsTickAvailable(void)
{
    return OSi_UseTick;
}

ARM_FUNC static void OSi_CountUpTick(void)
{
    OSi_TickCounter++;

    if (OSi_NeedResetTimer)
    {
        OS_SetTimerControl(OS_TIMER_0, 0);
        OS_SetTimerCount(OS_TIMER_0, 0);
        OS_SetTimerControl(OS_TIMER_0, OSi_TICK_TIMERCONTROL);

        OSi_NeedResetTimer = FALSE;
    }

    OSi_EnterTimerCallback(OS_TIMER_0, (void (*)(void *))OSi_CountUpTick, 0);
}

ARM_FUNC OSTick OS_GetTick(void)
{
    OSIntrMode prev = OS_DisableInterrupts();
    vu16 countL = *(REGType16 *)((u32)&reg_OS_TM0CNT_L + OS_TIMER_0 * 4);
    vu64 countH = OSi_TickCounter & 0xffffffffffffULL;

    if (reg_OS_IF & OS_IE_TIMER0 && !(countL & 0x8000))
    {
        countH++;
    }

    (void)OS_RestoreInterrupts(prev);

    return (countH << 16) | countL;
}

ARM_FUNC u16 OS_GetTickLo(void)
{
    return reg_OS_TM0CNT_L;
}
