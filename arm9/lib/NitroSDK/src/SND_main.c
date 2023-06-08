#include "SND_main.h"
#include "SND_command.h"
#include "SND_alarm.h"

#include "nitro/types.h"
#include "OS_mutex.h"
#include "code32.h"

static struct OSMutex sSndMutex;
static s32 sSndInitialized;

void SND_Init(void) {
    if (sSndInitialized)
        return;
    sSndInitialized = 1;
    OS_InitMutex(&sSndMutex);
    SND_CommandInit();
    SND_AlarmInit();
}

void SNDi_LockMutex(void) {
    OS_LockMutex(&sSndMutex);
}

void SNDi_UnlockMutex(void) {
    OS_UnlockMutex(&sSndMutex);
}
