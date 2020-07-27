#include "global.h"
#include "MI_memory.h"

#pragma thumb on

struct Unk0202A398
{
    u8 b0_0 : 1;
    u8 b0_1 : 1; // used
};

struct Unk0202A3B4
{
    u16 b0; // used
};

struct Unk0202A40C
{
    u16 b0;
    u8 b2; // used
    u16 b3;
    u8 b7;
    u16 b8_0 : 4;
    u16 b8_4 : 1; // used
};

struct Unk0202A444
{
    u16 b0;
    u8 b2;
    u8 b3; // used
};

u8 FUN_0202A398(struct Unk0202A398 *unk);
void FUN_0202A3A0(struct Unk0202A398 *unk, u16 arg1);
u16 FUN_0202A3B4(struct Unk0202A3B4 *unk, u16 arg1, int arg2);
u8 FUN_0202A40C(struct Unk0202A40C *unk, int arg1);
u8 FUN_0202A444(struct Unk0202A444 *unk, int arg1);
void FUN_0202A474(void * dest, int arg1, const void * src);
void FUN_0202A498(const void * src, int arg1, void * dest);

u8 FUN_0202A398(struct Unk0202A398 *unk)
{
    return unk->b0_1;
}

void FUN_0202A3A0(struct Unk0202A398 *unk, u16 arg1)
{
    unk->b0_1 = arg1;
}

u16 FUN_0202A3B4(struct Unk0202A3B4 *unk, u16 arg1, int arg2)
{
    switch (arg2)
    {
    case 0:
        break;
    case 1:
        if (arg1 > 0x270F)
        {
            unk->b0 = 0x270F;
        }
        else
        {
            unk->b0 = arg1;
        }
        break;
    case 2:
    case 3:
    case 4:
        break;
    case 5:
        if (unk->b0 + arg1 > 0x270F)
        {
            unk->b0 = 0x270F;
        }
        else
        {
            unk->b0 += arg1;
        }
        break;
    case 6:
        if (unk->b0 < arg1)
        {
            unk->b0 = 0;
        }
        else
        {
            unk->b0 -= arg1;
        }
        break;
    }
    return unk->b0;
}

u8 FUN_0202A40C(struct Unk0202A40C *unk, int arg1)
{
    switch (arg1)
    {
    case 2:
        unk->b2 = 0;
        unk->b8_4 = 0;
        break;
    case 3:
        if (unk->b8_4 != 0)
        {
            unk->b2 += 1;
        }
        else
        {
            unk->b2 = 1;
            unk->b8_4 = 1;
        }
        break;
    }
    return unk->b2;
}

u8 FUN_0202A444(struct Unk0202A444 *unk, int arg1)
{
    switch (arg1)
    {
    case 2:
        unk->b3 = 1;
        break;
    case 3:
        if (unk->b3 < 0xa)
        {
            unk->b3++;
        }
        break;
    case 4:
        if (unk->b3 > 1)
        {
            unk->b3--;
        }
        break;
    }
    return unk->b3;
}

void FUN_0202A474(void * dest, int arg1, const void * src) {
    if (arg1 == 0) {
        MI_CpuCopy8(src, dest + 0xc0, 0xa8);
    } else {
        MI_CpuCopy8(src, dest + 0x18, 0xa8);
    }
}

void FUN_0202A498(const void * src, int arg1, void * dest) {
    if (arg1 == 0) {
        MI_CpuCopy8(src + 0xc0, dest, 0xa8);
    } else {
        MI_CpuCopy8(src + 0x18, dest, 0xa8);
    }
}

