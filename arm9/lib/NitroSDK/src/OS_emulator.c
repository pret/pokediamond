#include "OS_emulator.h"
#include "code32.h"

u32 OSi_ConsoleTypeCache = -1u;

BOOL OS_IsRunOnEmulator(void) {
    return FALSE;
}

u32 OS_GetConsoleType(void) {
    OSi_ConsoleTypeCache = OS_CONSOLE_NITRO | OS_CONSOLE_DEV_CARD | OS_CONSOLE_SIZE_4MB;

    return OSi_ConsoleTypeCache;
}
