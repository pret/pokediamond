#include "nitro.h"

struct Unk2106FA0 {
    u8 filler0[0x8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
};

extern struct Unk2106FA0 gUnknown2106FA0;

void FUN_02000DF4(void)
{
    gUnknown2106FA0.unk8 = -1;
    gUnknown2106FA0.unkC = 0;
    gUnknown2106FA0.unk10 = -1;
    gUnknown2106FA0.unk14 = 0;
}
