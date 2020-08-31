#include "nitro/types.h"
#include "function_target.h"
#include "MI_dma.h"

extern void MI_SetWramBank(u32 param0);

ARM_FUNC void MI_Init(void)
{
    MI_SetWramBank(3);
    MI_StopDma(0);
}
