#include "global.h"
#include "mod63_021DB450.h"

extern u32 (*UNK_021064B8)(u32 param0, u32 param1, u32 param2);
extern void FUN_0201327C(u32 param0);

THUMB_FUNC u32 MOD63_021DB450(u32 param0, u32 param1)
{
    u32 res0 = (UNK_021064B8)(param0, param1, 0);
    FUN_0201327C(res0);
    GF_ASSERT(res0);
    return (u32)((u16)res0 * 8);
}
