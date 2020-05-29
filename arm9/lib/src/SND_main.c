#include "SND_main.h"
#include "SND_command.h"
#include "SND_alarm.h"

#include "global.h"
#include "OS_mutex.h"

static struct OSMutex sSndMutex;
static s32 sSndInitialized;

// TODO remove these declarations once we have the functions in the headers
void OS_InitMutex(struct OSMutex *);
void OS_UnlockMutex(struct OSMutex *);
void OS_LockMutex(struct OSMutex *);

ARM_FUNC void SND_Init(void) {
    if (sSndInitialized)
        return;
    sSndInitialized = 1;
    OS_InitMutex(&sSndMutex);
    SND_CommandInit();
    SND_AlarmInit();
}

ARM_FUNC void SNDi_LockMutex(void) {
    OS_LockMutex(&sSndMutex);
}

ARM_FUNC void SNDi_UnlockMutex(void) {
    OS_UnlockMutex(&sSndMutex);
}
