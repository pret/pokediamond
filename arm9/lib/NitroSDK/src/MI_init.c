#include "MI_init.h"
#include "nitro/types.h"
#include "MI_dma.h"
#include "MI_wram.h"
#include "code32.h"

void MI_Init(void)
{
    MI_SetWramBank(MI_WRAM_ARM7_ALL);
    MI_StopDma(0);
}
