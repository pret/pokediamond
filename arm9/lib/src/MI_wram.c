#include "function_target.h"
#include "consts.h"
#include "MI_wram.h"

ARM_FUNC void MI_SetWramBank(MIWram cnt)
{
    reg_GX_VRAMCNT_WRAM = (u8)cnt;
}
