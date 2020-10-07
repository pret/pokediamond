#include "global.h"
#include "error_handling.h"

extern u32 FUN_02031810(void);
extern void PrintErrorMessageAndReset(void);

THUMB_FUNC void ErrorHandling(void)
{
    if (FUN_02031810())
    {
        if (OS_GetProcMode() != OS_PROCMODE_IRQ)
        {
            PrintErrorMessageAndReset();
        }
    }
}
