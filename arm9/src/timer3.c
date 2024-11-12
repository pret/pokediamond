#include "timer3.h"

#include "global.h"

#include "OS_interrupt.h"
#include "OS_irqTable.h"
#include "OS_system.h"
#include "OS_timer.h"
#include "registers.h"

static BOOL timer3_needReset;
static vu64 timer3_counter;

void Init_Timer3() {
    timer3_counter = 0;
    timer3_needReset = FALSE;

    OS_SetTimerControl(OS_TIMER_3, 0);
    OS_SetTimerCount(OS_TIMER_3, 0);
    OS_SetTimerControl(OS_TIMER_3, REG_OS_TM3CNT_H_E_MASK | REG_OS_TM3CNT_H_I_MASK | OS_TIMER_PRESCALER_64); // start timer3 with f/64 and irq enable

    OS_SetIrqFunction(OS_IE_TIMER3, &CountUpTimer3);
    OS_EnableIrqMask(OS_IE_TIMER3); // irq on timer3 overflow
}

void CountUpTimer3() {
    timer3_counter++;

    if (timer3_needReset) {
        OS_SetTimerControl(OS_TIMER_3, 0);
        OS_SetTimerCount(OS_TIMER_3, 0);
        OS_SetTimerControl(OS_TIMER_3, REG_OS_TM3CNT_H_E_MASK | REG_OS_TM3CNT_H_I_MASK | OS_TIMER_PRESCALER_64);
        timer3_needReset = FALSE;
    }

    OS_SetIrqCheckFlag(OS_IE_TIMER3);
    OS_SetIrqFunction(OS_IE_TIMER3, &CountUpTimer3);
}

u64 internal_GetTimer3Count() {
    OSIntrMode intr_mode = OS_DisableInterrupts();

    vu16 timer3 = reg_OS_TM3CNT_L;
    vu64 counter = timer3_counter & 0x0000ffffffffffff;

    if (reg_OS_IF & OS_IE_TIMER3 && !(timer3 & 0x8000)) {
        counter++;
    }

    OS_RestoreInterrupts(intr_mode);
    return (counter << 16) | timer3;
}

u64 GetTimer3Count() {
    return internal_GetTimer3Count();
}

u64 Timer3CountToMilliSeconds(u64 count) {
    return (count * 64) / (HW_SYSTEM_CLOCK / 1000);
}

u64 Timer3CountToSeconds(u64 count) {
    return (count * 64) / HW_SYSTEM_CLOCK;
}
