#include "timer3.h"

struct Timer3Data timer3_data;


THUMB_FUNC void Init_Timer3()
{
    timer3_data.Timer3Counter = 0;
    timer3_data.NeedReset = FALSE;

    reg_OS_TM3CNT_H = 0;
    reg_OS_TM3CNT_L = 0;
    reg_OS_TM3CNT_H = 0xc1; // start timer3 with f/64 and irq enable

    OS_SetIrqFunction(0x40, &CountUpTimer3);
    OS_EnableIrqMask(0x40); // irq on timer3 overflow
}


THUMB_FUNC void CountUpTimer3()
{
    timer3_data.Timer3Counter++;

    if (timer3_data.NeedReset)
    {
        reg_OS_TM3CNT_H = 0;
        reg_OS_TM3CNT_L = 0;
        reg_OS_TM3CNT_H = 0xc1;
        timer3_data.NeedReset = FALSE;
    }

    *(vu32 *)HW_INTR_CHECK_BUF |= 0x40;

    OS_SetIrqFunction(0x40, &CountUpTimer3);
}

THUMB_FUNC u64 internal_GetTimer3Count()
{
    OSIntrMode intr_mode = OS_DisableInterrupts();

    vu16 timer3 = reg_OS_TM3CNT_L;
    vu64 timer3_counter = timer3_data.Timer3Counter & 0x0000ffffffffffff;

    if (reg_OS_IF & 64 && !(timer3 & 0x8000))
    {
        timer3_counter++;
    }

    OS_RestoreInterrupts(intr_mode);
    return (timer3_counter << 16) | timer3;
}

THUMB_FUNC u64 GetTimer3Count()
{
    return internal_GetTimer3Count();
}

THUMB_FUNC u64 Timer3CountToMilliSeconds(u64 count)
{
    return (count *64) / 33514;
}

THUMB_FUNC u64 Timer3CountToSeconds(u64 count)
{
    return (count *64) / HW_SYSTEM_CLOCK;
}
