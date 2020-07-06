#include "function_target.h"
#include "OS_alarm.h"
#include "OS_tick.h"
#include "pad.h"

static BOOL PADi_XYButtonAvailable;
static OSAlarm PADi_Alarm;

extern void FUN_037FB92C(void);

ARM_FUNC BOOL PAD_InitXYButton(void) {
    OSTick tick;
    if (!OS_IsTickAvailable() || !OS_IsAlarmAvailable())
        return FALSE;
    else if (PADi_XYButtonAvailable) 
        return FALSE;
    else {
        OS_CreateAlarm(&PADi_Alarm);
        tick = OS_GetTick();
        OS_SetPeriodicAlarm(&PADi_Alarm, tick + 0x82e, 0x82e, (OSAlarmHandler)FUN_037FB92C, NULL);
        PADi_XYButtonAvailable = TRUE;
        return TRUE;
    }
}
