#include "consts.h"
#include "OS_alarm.h"
#include "OS_interrupt.h"
#include "OS_irqTable.h"
#include "OS_terminate_proc.h"
#include "OS_system.h"
#include "code32.h"

static struct OSiAlarmQueue OSi_AlarmQueue;

static u16 OSi_UseAlarm = FALSE;

static void OSi_SetTimer(OSAlarm *alarm);
static void OSi_InsertAlarm(OSAlarm *alarm, OSTick fire);
static void OSi_ArrangeTimer(void);

static void OSi_SetTimer(OSAlarm *alarm)
{
    OSTick tick = OS_GetTick();

    OS_SetTimerControl(OS_TIMER_1, 0);

    s64 delta = (s64)(alarm->fire - tick);

    OSi_EnterTimerCallback(OS_TIMER_1, OSi_AlarmHandler, NULL);

    u16 timerCount;
    if (delta < 0)
    {
        timerCount = (u16)~1;
    }
    else if (delta < 0x10000)
    {
        timerCount = (u16)(~delta);
    }
    else
    {
        timerCount = 0;
    }

    OS_SetTimerCount((OSTimer)OS_TIMER_1, timerCount);
    OS_SetTimerControl(OS_TIMER_1, (u16)OSi_TICK_TIMERCONTROL);

    (void)OS_EnableIrqMask(OS_IE_TIMER1);
}

void OS_InitAlarm(void)
{
    if (!OSi_UseAlarm)
    {
        OSi_UseAlarm = TRUE;

        OSi_SetTimerReserved(OS_TIMER_1);

        OSi_AlarmQueue.head = NULL;
        OSi_AlarmQueue.tail = NULL;

        (void)OS_DisableIrqMask(OS_IE_TIMER1);
    }
}

BOOL OS_IsAlarmAvailable(void)
{
    return OSi_UseAlarm;
}

void OS_CreateAlarm(OSAlarm *alarm)
{
    alarm->handler = 0;
    alarm->tag = 0;
}

static void OSi_InsertAlarm(OSAlarm *alarm, OSTick fire)
{
    if (alarm->period > 0)
    {
        OSTick tick = OS_GetTick();

        fire = alarm->start;
        if (alarm->start < tick)
        {
            fire += alarm->period * ((tick - alarm->start) / alarm->period + 1);
        }
    }

    alarm->fire = fire;

    OSAlarm *prev;
    OSAlarm *next;

    for (next = OSi_AlarmQueue.head; next; next = next->next)
    {
        if ((s64)(fire - next->fire) >= 0)
        {
            continue;
        }

        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;
        if (prev)
        {
            prev->next = alarm;
        }
        else
        {
            OSi_AlarmQueue.head = alarm;
            OSi_SetTimer(alarm);
        }

        return;
    }

    alarm->next = 0;
    prev = OSi_AlarmQueue.tail;
    OSi_AlarmQueue.tail = alarm;
    alarm->prev = prev;
    if (prev)
    {
        prev->next = alarm;
    }
    else
    {
        OSi_AlarmQueue.head = OSi_AlarmQueue.tail = alarm;
        OSi_SetTimer(alarm);
    }
}

void OS_SetAlarm(OSAlarm * alarm, OSTick tick, OSAlarmHandler handler, void *arg)
{
    if (!alarm || alarm->handler)
    {
        OS_Terminate();
    }

    OSIntrMode enabled = OS_DisableInterrupts();

    alarm->period = 0;

    alarm->handler = handler;
    alarm->arg = arg;

    OSi_InsertAlarm(alarm, OS_GetTick() + tick);

    (void)OS_RestoreInterrupts(enabled);
}

void OS_CancelAlarm(OSAlarm *alarm)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    if (!alarm->handler)
    {
        (void)OS_RestoreInterrupts(enabled);
        return;
    }

    OSAlarm *next = alarm->next;

    if (!next)
    {
        OSi_AlarmQueue.tail = alarm->prev;
    }
    else
    {
        next->prev = alarm->prev;
    }

    if (alarm->prev)
    {
        alarm->prev->next = next;
    }
    else
    {
        OSi_AlarmQueue.head = next;
        if (next)
        {
            OSi_SetTimer(next);
        }
    }

    alarm->handler = NULL;
    alarm->period = 0;

    (void)OS_RestoreInterrupts(enabled);
}

asm void OSi_AlarmHandler(void *arg)
{
    stmfd sp!, {r0, lr}
    bl OSi_ArrangeTimer
    ldmfd sp!, {r0, lr}
    bx lr
}

static void OSi_ArrangeTimer(void)
{
    OS_SetTimerControl(OS_TIMER_1, 0);

    (void)OS_DisableIrqMask(OS_IE_TIMER1);

    OS_SetIrqCheckFlag(OS_IE_TIMER1);

    OSTick tick = OS_GetTick();

    OSAlarm *alarm = OSi_AlarmQueue.head;

    if (!alarm)
    {
        return;
    }

    if (tick < alarm->fire)
    {
        OSi_SetTimer(alarm);
        return;
    }

    OSAlarm *next = alarm->next;
    OSi_AlarmQueue.head = next;

    if (!next)
    {
        OSi_AlarmQueue.tail = NULL;
    }
    else
    {
        next->prev = NULL;
    }

    OSAlarmHandler handler = alarm->handler;

    if (!alarm->period)
    {
        alarm->handler = NULL;
    }

    if (handler)
    {
        (handler)(alarm->arg);
    }

    if (alarm->period > 0)
    {
        alarm->handler = handler;
        OSi_InsertAlarm(alarm, 0);
    }

    if (OSi_AlarmQueue.head)
    {
        OSi_SetTimer(OSi_AlarmQueue.head);
    }
}
