#include "global.h"

struct UnkStruct_02020AFC
{
    BOOL NeedReset;
    vu64 Timer3Counter;
};

struct UnkStruct_02020AFC UNK_021C59B0;

extern void FUN_02020B30(void);

THUMB_FUNC void FUN_02020AFC()
{
    UNK_021C59B0.Timer3Counter = 0;
    UNK_021C59B0.NeedReset = FALSE;

    reg_OS_TM3CNT_H = 0;
    reg_OS_TM3CNT_L = 0;
    reg_OS_TM3CNT_H = 0xc1; // start timer3 with f/64 and irq enable

    OS_SetIrqFunction(0x40, &FUN_02020B30);
    OS_EnableIrqMask(0x40); // irq on timer3 overflow
}


THUMB_FUNC void FUN_02020B30()
{
    UNK_021C59B0.Timer3Counter++;

    if (UNK_021C59B0.NeedReset)
    {
        reg_OS_TM3CNT_H = 0;
        reg_OS_TM3CNT_L = 0;
        reg_OS_TM3CNT_H = 0xc1;
        UNK_021C59B0.NeedReset = FALSE;
    }
    u32 *ptr = (u32 *)0x027e0000;
    u32 offset = 0xffe;
    ptr[offset] |= 0x40;

    OS_SetIrqFunction(0x40, &FUN_02020B30);
}

THUMB_FUNC u64 FUN_02020B80()
{
    OSIntrMode intr_mode = OS_DisableInterrupts();

    vu16 timer3 = reg_OS_TM3CNT_L;
    vu64 unk1 = UNK_021C59B0.Timer3Counter & 0x0000ffffffffffff;

    if (reg_OS_IF & 64 && !(timer3 & 0x8000))
    {
        unk1++;
    }

    OS_RestoreInterrupts(intr_mode);
    return (unk1 << 16) | timer3;
}

THUMB_FUNC u64 FUN_02020BF4()
{
    return FUN_02020B80();
}

THUMB_FUNC u64 FUN_02020BFC(u64 param0)
{
    return (param0 << 6) / 33514;
}

THUMB_FUNC u64 FUN_02020C14(u64 param0)
{
    return (param0 << 6) / 33514000;
}
