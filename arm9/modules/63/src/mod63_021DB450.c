#include "global.h"
#include "mod63_021DB450.h"

//todo resolve to static code
extern u32 (*UNK_021064B8)(u32 param0, u32 param1, u32 param2);
extern u32 (*UNK_021064C0)(u32 param0, u32 param1, u32 param2);

extern void FUN_0201327C(u32 param0);
extern void FUN_020132BC(u32 param0);

THUMB_FUNC u32 MOD63_021DB450(u32 param0, u32 param1)
{
    u32 res0 = (UNK_021064B8)(param0, param1, 0);
    FUN_0201327C(res0);
    GF_ASSERT(res0);
    return (u32)((u16)res0 * 8);
}

THUMB_FUNC u32 MOD63_021DB474(u32 param0, u32 param1)
{
    u32 res0 = (UNK_021064C0)(param0, param1, 1);
    GF_ASSERT(res0);
    FUN_020132BC(res0);
    return (u32)((u16)res0 * 8);
}

THUMB_FUNC u32 MOD63_021DB498(void)
{
    return 32;
}
