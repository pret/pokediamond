#include "nitro/types.h"
#include "OS_terminate_proc.h"
#include "OS_system.h"
#include "code32.h"

extern void CTRDG_VibPulseEdgeUpdate(u32 param);
extern void FUN_037F8530(void); //SVC_Halt thunk

void OS_Terminate(void)
{
    CTRDG_VibPulseEdgeUpdate(0);
    while (TRUE)
    {
        (void)OS_DisableInterrupts();
        FUN_037F8530(); //SVC_Halt
    }
}
