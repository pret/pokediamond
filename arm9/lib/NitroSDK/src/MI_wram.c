#include "MI_wram.h"

#include "nitro/types.h"
#include "registers.h"
#include "code32.h"

void MI_SetWramBank(MIWram cnt)
{
    reg_GX_VRAMCNT_WRAM = (u8)cnt;
}
