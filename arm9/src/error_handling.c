#include "global.h"
#include "error_handling.h"
#include "error_message_reset.h"
#include "unk_02031734.h"



void GF_AssertFail(void)
{
    if (sub_02031810())
    {
        if (OS_GetProcMode() != OS_PROCMODE_IRQ)
        {
            PrintErrorMessageAndReset();
        }
    }
}
