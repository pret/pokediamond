#include "MI_init.h"
#include "nitro/types.h"
#include "function_target.h"
#include "MI_dma.h"
#include "MI_wram.h"

ARM_FUNC void MI_Init(void)
{
    MI_SetWramBank(MI_WRAM_ARM7_ALL);
    MI_StopDma(0);
}
