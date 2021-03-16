#include "unk_02024E64.h"

extern void FUN_020250A4(void *param0);
extern void FUN_02025484(void *param0);

THUMB_FUNC u32 FUN_02024E64()
{
    return 0x74C;
}

THUMB_FUNC void FUN_02024E6C(void *param0)
{
    MIi_CpuClearFast(0, param0, 0x74C);

    FUN_020250A4(param0);

    FUN_02025484(param0 + (7 << 8));

    MIi_CpuClear16(0xFFFF, param0 + 0x724, 8);
    MIi_CpuClear16(0xFFFF, param0 + 0x734, 0xb);
}

THUMB_FUNC void *FUN_02024EB4(struct SaveBlock2 *sav2)
{
    return SavArray_get(sav2, 0xa);
}

THUMB_FUNC void *FUN_02024EC0(struct SaveBlock2 *sav2)
{
    return FUN_02022634(sav2, 0xa);
}

THUMB_FUNC void *FUN_02024ECC(struct SaveBlock2 *sav2)
{
    return SavArray_get(sav2, 0xa);
}

THUMB_FUNC void *FUN_02024ED8(struct SaveBlock2 *sav2)
{
    void *res = SavArray_get(sav2, 0xa);
    return res + (7 << 8);
}

THUMB_FUNC u16 *FUN_02024EE8(void *buf)
{
    return buf + 0x724;
}

THUMB_FUNC void FUN_02024EF4(u16 *buf, struct String *str)
{
    CopyStringToU16Array(str, buf + 0x392, 8);
}

THUMB_FUNC u16 *FUN_02024F0C(void *buf)
{
    return buf + 0x734;
}

THUMB_FUNC void FUN_02024F18(u16 *buf, struct String *str)
{
    CopyStringToU16Array(str, buf + 0x39A, 0xb);
}
