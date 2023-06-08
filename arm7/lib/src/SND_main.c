#include "SND_main.h"

#include "SND_alarm.h"
#include "SND_capture.h"
#include "SND_command.h"
#include "SND_exChannel.h"
#include "SND_global.h"
#include "SND_seq.h"
#include "SND_util.h"
#include "SND_work.h"

#include "OS_alarm.h"
#include "OS_message.h"
#include "OS_thread.h"
#include "OS_tick.h"
#include "code32.h"

static void FUN_037fc330(void *);
static void SndThread(void *);

u8 sThreadStack[0x400];
OSThread sThread;
OSAlarm sAlarm;
OSMessageQueue sMessageQueue;
OSMessage sMessageArray[8];
u32 sInitialized = 0;

void SND_Init(u32 priority)
{
    if (sInitialized == 0)
    {
        sInitialized = 1;
        SND_CommandInit();
        SND_CreateThread(priority);
    }
}

void SND_CreateThread(u32 priority)
{
    OS_CreateThread(&sThread,
        SndThread,
        NULL,
        &sThreadStack[sizeof(sThreadStack)],
        sizeof(sThreadStack),
        priority);
    OS_WakeupThreadDirect(&sThread);
}

void SND_InitIntervalTimer(void)
{
    OS_InitMessageQueue(&sMessageQueue, sMessageArray, 8);
    OS_CreateAlarm(&sAlarm);
}

void SND_StartIntervalTimer(void)
{
    OSTick tick = OS_GetTick();
    OS_SetPeriodicAlarm(&sAlarm, tick + 0x10000, 2728, FUN_037fc330, NULL);
}

void SND_StopIntervalTimer(void)
{
    OS_CancelAlarm(&sAlarm);
}

u32 SND_WaitForIntervalTimer(void)
{
    OSMessage result;
    (void)OS_ReceiveMessage(&sMessageQueue, &result, 1);
    return (u32)result;
}

void SND_SendWakeupMessage(void)
{
    (void)OS_SendMessage(&sMessageQueue, (OSMessage)2, 0);
}

void SNDi_LockMutex(void)
{
    // nothing
}

void SNDi_UnlockMutex(void)
{
    // nothing
}

static void FUN_037fc330(void *arg)
{
    (void)arg;
    (void)OS_SendMessage(&sMessageQueue, (OSMessage)1, 0);
}

static void SndThread(void *arg)
{
    (void)arg;

    SND_InitIntervalTimer();
    SND_ExChannelInit();
    SND_SeqInit();
    SND_AlarmInit();
    SND_Enable();
    SND_SetOutputSelector(0, 0, 0, 0);
    SND_SetMasterVolume(0x7F);
    SND_StartIntervalTimer();

    while (TRUE)
    {
        BOOL update = FALSE;

        u32 result = SND_WaitForIntervalTimer();

        switch (result)
        {
            case 2:
                update = FALSE;
                break;
            case 1:
                update = TRUE;
                break;
        }

        SND_UpdateExChannel();
        SND_CommandProc();

        SND_SeqMain(update);
        SND_ExChannelMain(update);

        SND_UpdateSharedWork();
        (void)SND_CalcRandom();
    }
}
