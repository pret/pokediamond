#include "global.h"
#include "unk_0201B8B88.h"

#pragma thumb on

const u16 * FUN_0201B8B8(const u16 * r4)
{
    GF_ASSERT(*r4 == 0xFFFE);
    if (*r4 == 0xFFFE) {
        u16 r0 = r4[2];
        r4 += 3;
        r4 += r0;
    }
    return r4;
}

u16 FUN_0201B8E0(const u16 * r4)
{
    GF_ASSERT(*r4 == 0xFFFE);
    return r4[1];
}

BOOL FUN_0201B8F8(const u16 * r4)
{
    return (FUN_0201B8E0(r4) & 0xFF00) == 0x100;
}

u16 FUN_0201B914(const u16 * r5, u32 r4)
{
    GF_ASSERT(*r5 == 0xFFFE);
    GF_ASSERT(r4 < r5[2]);
    return r5[3 + r4];
}
