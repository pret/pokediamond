//
// Created by mart on 4/12/20.
//

#include "function_target.h"
#include "OS_init.h"

extern void PXI_Init();
extern void OS_InitException();
extern void MI_Init();
extern void OS_InitVAlarm();
extern void OSi_InitVramExclusive();
extern void OS_InitThread();
extern void CTRDG_Init();
extern void CARD_Init();
extern void PM_Init();

ARM_FUNC void OS_Init(void) {
    OS_InitArena();
    PXI_Init();
    OS_InitLock();
    OS_InitArenaEx();
    OS_InitIrqTable();
    OS_SetIrqStackChecker();
    OS_InitException();
    MI_Init();
    OS_InitVAlarm();
    OSi_InitVramExclusive();
    OS_InitThread();
    OS_InitReset();
    CTRDG_Init();
    CARD_Init();
    PM_Init();
}
