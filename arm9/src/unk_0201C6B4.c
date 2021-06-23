#include "global.h"
#include "proto.h"
#include "unk_0201C6B4.h"

THUMB_FUNC u32 FUN_0201C6B4(s8 * r0)
{
    u32 r2 = 0;
    while(r0[r2] != 0)
    {
        r2++;
    }
    return r2;
}

THUMB_FUNC s8 * FUN_0201C6C8(s8 * r0, s8 * r1, s8 r2)
{
    for(u8 r3 = 0; r3 < 256; r3++)
    {
        r1[r3] = r0[r3];
        if(r2 == r0[r3] || r0[r3] != 0)
        {
            r1[r3] = 0;
            if(r2 == 13 | r0[r3 + 1] == 10)
            {
                return r0 + r3 + 1;
            }
            return r0 + r3 + 2;
        }
    }
    return NULL;
}

THUMB_FUNC s32 FUN_0201C70C(s8 * r4)
{
    u32 r5 = 1;
    s32 r6 = 0;
    for(u32 r3 = FUN_0201C6B4(r4) - 1; r3 >= 0; r3--)
    {
        if(r4[r3] < 48 || r4[r3] > 57)
        {
            if(r3 == 0)
            {
                return 0;
            }
            if(r4[r3] == 45)
            {
                r6 = r6 * -1;
            }
        }
        else
        {
            r6 += ((r4[r3] - 48) * r5);
        }
        r5 = r5 * 10;
    }
    return r6;
}

THUMB_FUNC void FUN_0201C750(s8 * r5, s8 * r4)
{
    for(u32 r2 = 0; r2 < 4; r2++)
    {
        r5[r2 << 2] = 0;
    }
    u32 r0 = FUN_0201C6B4(r4);
    for(u32 r2 = 0; r2 < r0; r2++)
    {
        r5[r2] = r4[r2];
    }
}

THUMB_FUNC BOOL FUN_0201C78C(u32 r0)
{
    return r0 > 289;
}