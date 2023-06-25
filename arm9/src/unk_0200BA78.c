#include "global.h"
#include "unk_0200BA78.h"
#include "message_format.h"

void sub_0200BA78(struct UnkStruct_0200B870 *param0,
    int param1,
    u32 value,
    u32 n,
    enum PrintingMode mode,
    struct Window *window,
    int x,
    int y)
{
    sub_0200B9A8(param0, param1, window, x, y);
    sub_0200B9EC(param0, value, n, mode, window, x + 16, y);
}

void sub_0200BAAC(
    struct UnkStruct_0200B870 *param0, u32 value, u32 n, enum PrintingMode mode, void *dest)
{
    u8 st0 = (u8)((param0->unk_28 << 4) | param0->unk_28);
    ConvertUIntToDecimalString(param0->data, value, mode, n);

    for (int i = 0; param0->data[i] != 0xffff; i++)
    {
        if (param0->data[i] >= 0xa2 && param0->data[i] <= 0xab)
        {
            MI_CpuCopy32( //UB: void * access
                &param0->unk_4->pRawData[(param0->data[i] - 0xa2) << 5], dest + i * 0x20, 0x20);
        }
        else
        {
            MI_CpuFill8(dest + i * 0x20, st0, 0x20);
        }
    }
}
