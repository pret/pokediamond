#include "global.h"
#include "unk_0201C6B4.h"

s32 sub_0201C6B4(s8 * r0)
{
    s32 r2 = 0;
    while(r0[r2] != 0)
    {
        r2++;
    }
    return r2;
}

s8 * sub_0201C6C8(s8 * r0, s8 * r1, s8 r2)
{
    for(int r3 = 0; r3 < 0x100; r3++)
    {
        r1[r3] = r0[r3];
        if(r2 == r0[r3] || r0[r3] == 0)
        {
            r1[r3] = 0;
            if(r2 == 0xd && r0[r3 + 1] == 0xa)
            {
                return &r0[r3 + 2];
            }
            return &r0[r3 + 1];
        }
    }
    return NULL;
}

s32 sub_0201C70C(s8 * r4)
{
    s32 unk0 = sub_0201C6B4(r4);
    s32 r3;
    s32 r5 = 1;
    s32 r6 = 0;
    for(r3 = unk0 - 1; r3 >= 0; r3--)
    {
        if(r4[r3] >= 0x30 && r4[r3] <= 0x39)
        {
            r6 += (r4[r3] - 0x30) * r5;
        }
        else
        {
            if(r3 == 0)
            {
                if(r4[r3] == 0x2d)
                {
                    r6 *= -1;
                }
            }
            else
            {
                return -1;
            }
        }
        r5 *= 0xa;
    }
    return r6;
}

void sub_0201C750(s8 * r5, s8 * r4)
{
    for(u8 r2 = 0; r2 < 4; r2++)
    {
        s32 * unk5 = (s32 *)r5;
        unk5[r2] = 0;
    }
    u8 r0 = (u8)(sub_0201C6B4(r4));
    for(u8 r2 = 0; r2 < r0; r2++)
    {
        r5[r2] = r4[r2];
    }
}

BOOL sub_0201C78C(u32 r0)
{
    return r0 < 0x121;
}
