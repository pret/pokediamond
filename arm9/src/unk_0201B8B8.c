#include "global.h"
#include "unk_0201B8B8.h"

#pragma thumb on

const u16 * MsgArray_SkipControlCode(const u16 * r4)
{
    GF_ASSERT(*r4 == 0xFFFE);
    if (*r4 == 0xFFFE) {
        u16 r0 = r4[2];
        r4 += 3;
        r4 += r0;
    }
    return r4;
}

u32 MsgArray_GetControlCode(const u16 * r4)
{
    GF_ASSERT(*r4 == 0xFFFE);
    return r4[1];
}

BOOL MsgArray_ControlCodeIsStrVar(const u16 * r4)
{
    return (MsgArray_GetControlCode(r4) & 0xFF00) == 0x100;
}

u32 MsgArray_ControlCodeGetField(const u16 * r5, u32 r4)
{
    GF_ASSERT(*r5 == 0xFFFE);
    GF_ASSERT(r4 < r5[2]);
    return r5[3 + r4];
}
