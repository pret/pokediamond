#include "OS_interrupt.h"
#include "OS_system.h"
#include "OS_tick.h"
#include "function_target.h"

extern void OSi_SetTimerReserved(u32);

static u16 OSi_UseTick;
static u64 OSi_TickCounter;
static BOOL OSi_NeedResetTimer;

ARM_FUNC void OS_InitTick(void) {
    if (OSi_UseTick == 0) {
        OSi_UseTick = 1;
        OSi_SetTimerReserved(0);
        OSi_TickCounter = 0;
        OS_SetTimerControl(OS_TIMER_0, 0);
        OS_SetTimerCount(OS_TIMER_0, 0);
        OS_SetTimerControl(OS_TIMER_0, 0xc1);
        OS_SetIrqFunction(8, OSi_CountUpTick);
        (void)OS_EnableIrqMask(8);
        OSi_NeedResetTimer = 0;
    }
}

ARM_FUNC u16 OS_IsTickAvailable(void) {
    return OSi_UseTick;
}

ARM_FUNC void OSi_CountUpTick(void) {
    OSi_TickCounter++;
    if (OSi_NeedResetTimer != 0) {
        OS_SetTimerControl(OS_TIMER_0, 0);
        OS_SetTimerCount(OS_TIMER_0, 0);
        OS_SetTimerControl(OS_TIMER_0, 0xc1);
        OSi_NeedResetTimer = 0;
    }
    OSi_EnterTimerCallback(0, (void(*)(void*))OSi_CountUpTick, NULL);
}

ARM_FUNC u64 OS_GetTick(void) {
    OSIntrMode prev = OS_DisableInterrupts();
    vu16 countL = *(REGType16 *)((u32)&reg_OS_TM0CNT_L + OS_TIMER_0 * 4);
    vu64 countH = OSi_TickCounter & 0xffffffffffffULL;

    if (reg_OS_IF & 8 && !(countL & 0x8000)) {
        countH++;
    }

    (void)OS_RestoreInterrupts(prev);

    return (countH << 16) | countL;
}
