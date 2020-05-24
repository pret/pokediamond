//
// Created by red031000 on 2020-05-05.
//

#include "OS_emulator.h"
#include "function_target.h"

u32 OSi_ConsoleTypeCache = -1u; //todo fix bss

ARM_FUNC BOOL OS_IsRunOnEmulator() {
    return FALSE;
}

ARM_FUNC u32 OS_GetConsoleType() {
    OSi_ConsoleTypeCache = OS_CONSOLE_NITRO | OS_CONSOLE_DEV_CARD | OS_CONSOLE_SIZE_4MB;

    return OSi_ConsoleTypeCache;
}
