#include "function_target.h"
#include "OS_init.h"

extern void OS_InitArena(void);
extern void PXI_Init(void);
extern void OS_InitLock(void);
extern void OS_InitIrqTable(void);
extern void OS_InitTick(void);
extern void OS_InitAlarm(void);
extern void OS_InitThread(void);
extern void OS_InitReset(void);
extern void CTRDG_Init(void);

ARM_FUNC void OS_Init(void)
{
    OS_InitArena();
    PXI_Init();
    OS_InitLock();
    OS_InitIrqTable();
    OS_InitTick();
    OS_InitAlarm();
    OS_InitThread();
    OS_InitReset();
    CTRDG_Init();
}
