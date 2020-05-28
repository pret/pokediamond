#include "function_target.h"
#include "OS_irqHandler.h"
#include "OS_system.h"
#include "OS_thread.h"
#include "sections.h"

#pragma section DTCM begin
OSThreadQueue OSi_IrqThreadQueue = { NULL, NULL };
#pragma section DTCM end

ARM_FUNC void OS_WaitIrq(BOOL clear, OSIrqMask irqFlags)
{
    OSIntrMode lastIntrMode = OS_DisableInterrupts();
    if (clear)
    {
        OS_ClearIrqCheckFlag(irqFlags);
    }
    (void)OS_RestoreInterrupts(lastIntrMode);

    while (!(OS_GetIrqCheckFlag() & irqFlags))
    {
        OS_SleepThread(&OSi_IrqThreadQueue);
    }
}
