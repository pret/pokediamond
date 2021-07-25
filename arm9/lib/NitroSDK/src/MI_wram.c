#include "MI_wram.h"

#include "global.h"
#include "registers.h"

ARM_FUNC void MI_SetWramBank(MIWram cnt)
{
    reg_GX_VRAMCNT_WRAM = (u8)cnt;
}
