#include "function_target.h"
#include "OS_init.h"

extern void PXI_Init(void);
extern void OS_InitException(void);
extern void MI_Init(void);
extern void OS_InitVAlarm(void);
extern void OSi_InitVramExclusive(void);
extern void CTRDG_Init(void);
extern void CARD_Init(void);
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
