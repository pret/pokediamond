//
// Created by red031000 on 2020-05-05.
//

#include "OS_tcm.h"
#include "function_target.h"

ARM_FUNC asm u32 OS_GetDTCMAddress() {
    mrc p15, 0x0, r0, c9, c1, 0x0
    ldr r1, =OSi_TCM_REGION_BASE_MASK
    and r0, r0, r1
    bx lr
}
