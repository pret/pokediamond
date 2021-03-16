#include "global.h"
#include "MI_memory.h"
#include "save_block_2.h"

extern void FUN_020250A4(void *param0);
extern void FUN_02025484(void *param0);

THUMB_FUNC u32 FUN_02024E64()
{
    return 0x0000074C;
}

THUMB_FUNC void FUN_02024E6C(void *param0)
{
    MIi_CpuClearFast(0, param0, 0x0000074C);

    FUN_020250A4(param0);

    FUN_02025484(param0 + (7 << 8));

    MIi_CpuClear16(0x0000FFFF, param0 + 0x00000724, 8);
    MIi_CpuClear16(0x0000FFFF, param0 + 0x00000734, 0xb);
}

THUMB_FUNC void *FUN_02024EB4(struct SaveBlock2 *sav2)
{
    return SavArray_get(sav2, 0xa);
}

THUMB_FUNC void *FUN_02024EC0(struct SaveBlock2 *sav2)
{
    return FUN_02022634(sav2, 0xa);
}