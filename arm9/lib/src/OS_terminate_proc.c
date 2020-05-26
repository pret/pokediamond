//
// Created by red031000 on 2020-05-07.
//

#include "types.h"
#include "OS_terminate_proc.h"
#include "function_target.h"
#include "OS_system.h"

ARM_FUNC void OS_Terminate(void) {
    while (TRUE) {
        (void)OS_DisableInterrupts();
        OS_Halt();
    }
}

ARM_FUNC asm void OS_Halt(void) {
    mov r0, #0x0
    mcr p15, 0x0, r0, c7, c0, 0x4
    bx lr
}
