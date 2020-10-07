#include "global.h"

#pragma thumb on

struct Unk0202A520
{
    u16 filler[11];
    u16 b22; // used
};

struct Unk0202A538
{
    u32 filler[3];
    u16 data[16]; // 16 is a guess
};

u16 FUN_0202A520(struct Unk0202A520 *unk);
u8 FUN_0202A524(struct Unk0202A520 *unk);
u16 FUN_0202A538(struct Unk0202A538 *unk, int arg1, int arg2);

u16 FUN_0202A520(struct Unk0202A520 *unk)
{
    return unk->b22;
}

u8 FUN_0202A524(struct Unk0202A520 *unk)
{
    return (u8)(unk->b22 / (0xfa << 2));
}

u16 FUN_0202A538(struct Unk0202A538 *unk, int arg1, int arg2)
{
    if (arg1 == 5)
    {
        return 0;
    }

    switch(arg2) {
        case 2:
            unk->data[arg1] = 0;
            break;
        case 3:
            if (unk->data[arg1] < 0xfffe) {
                unk->data[arg1]++;
            }
            break;
    }
    return unk->data[arg1];    
}
