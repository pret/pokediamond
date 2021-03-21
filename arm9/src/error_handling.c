#include "global.h"
#include "error_handling.h"
#include "error_message_reset.h"

extern u32 FUN_02031810(void);

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
