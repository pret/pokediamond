#include "nitro.h"

struct Unk2106FA0 {
    u8 filler0[0x8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
};

extern struct Unk2106FA0 gBacklightTop;

void FUN_02000DF4(void)
{
    gBacklightTop.unk8 = -1;
    gBacklightTop.unkC = 0;
    gBacklightTop.unk10 = -1;
    gBacklightTop.unk14 = 0;
}
