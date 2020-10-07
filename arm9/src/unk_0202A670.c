#include "global.h"
#include "MI_memory.h"

#pragma thumb on

struct Unk0202A670
{
    u32 b0;
    u8 b4; // used
};

struct Unk0202A68C
{
    u32 b0; // used
    u32 b4; // used
    u32 b8; // used
};

void FUN_0202A670(struct Unk0202A670 *arg0);
u32 FUN_0202A68C(struct Unk0202A68C *arg0, struct Unk0202A68C *arg1);

void FUN_0202A670(struct Unk0202A670 *arg0)
{

    MI_CpuFill8(&(arg0->b4), 0, 0xfa);
    MI_CpuFill8(arg0, 0, 4);
}

u32 FUN_0202A68C(struct Unk0202A68C *arg0, struct Unk0202A68C *arg1)
{
    if (arg0->b0 > arg1->b0) {
        return 1;
    } else if (arg0->b4 > arg1->b4) {
        return 1;
    } else if (arg0->b8 > arg1->b8) {
        return 1;
    }
    return 0;
}

