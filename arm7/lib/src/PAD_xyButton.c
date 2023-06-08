#include "OS_alarm.h"
#include "OS_tick.h"
#include "PAD_xyButton.h"
#include "registers.h"
#include "code32.h"

static BOOL PADi_XYButtonAvailable;
static OSAlarm PADi_Alarm;

void EXIi_SelectRcnt(u16);

BOOL PAD_InitXYButton(void) {
    OSTick tick;
    if (!OS_IsTickAvailable() || !OS_IsAlarmAvailable())
        return FALSE;
    else if (PADi_XYButtonAvailable) 
        return FALSE;
    else {
        OS_CreateAlarm(&PADi_Alarm);
        tick = OS_GetTick();
        OS_SetPeriodicAlarm(&PADi_Alarm, tick + 0x82e, 0x82e, (OSAlarmHandler)PADi_xyButtonAlarmHandler, NULL);
        PADi_XYButtonAvailable = TRUE;
        return TRUE;
    }
}

void PADi_xyButtonAlarmHandler(void) {
    u16 r4 = 0, r1;
    EXIi_SelectRcnt(0x8000);
    r1 = reg_EXTKEYIN;
    if(r1 & EXTKEYIN_HINGE) r4 = 0x8000;
    BUTTON_XY_BUF = (u16)(r4 | ((r1 & (EXTKEYIN_X | EXTKEYIN_Y | EXTKEYIN_DEBUG)) << 10));
}
