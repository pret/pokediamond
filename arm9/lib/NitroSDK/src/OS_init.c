#include "function_target.h"
#include "OS_init.h"
#include "MI_init.h"
#include "PXI_init.h"
#include "CARD_rom.h"

extern void CTRDG_Init(void);
extern void PM_Init(void);

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
