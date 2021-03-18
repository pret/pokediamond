#include "unk_02024E64.h"

extern void FUN_020250A4(void *param0);
extern void FUN_02025484(void *param0);

THUMB_FUNC u32 FUN_02024E64()
{
    return sizeof(struct UnkStruct_02024E64);
}

THUMB_FUNC void FUN_02024E6C(struct UnkStruct_02024E64 *param0)
{
    MIi_CpuClearFast(0, param0, sizeof(struct UnkStruct_02024E64));

    FUN_020250A4(param0->unk0);

    FUN_02025484(param0->unk700);

    MIi_CpuClear16(0xFFFF, param0->rival_name_buf, sizeof(param0->rival_name_buf) / sizeof(u16));
    MIi_CpuClear16(0xFFFF, param0->unk734, sizeof(param0->unk734) / sizeof(u16));
}

THUMB_FUNC struct UnkStruct_02024E64 *FUN_02024EB4(struct SaveBlock2 *sav2)
{
    return SavArray_get(sav2, 0xa);
}

THUMB_FUNC void *FUN_02024EC0(struct SaveBlock2 *sav2)
{
    return FUN_02022634(sav2, 0xa);
}

THUMB_FUNC struct UnkStruct_02024E64 *FUN_02024ECC(struct SaveBlock2 *sav2)
{
    return SavArray_get(sav2, 0xa);
}

THUMB_FUNC void *FUN_02024ED8(struct SaveBlock2 *sav2)
{
    struct UnkStruct_02024E64 *res = SavArray_get(sav2, 0xa);
    return res->unk700;
}

THUMB_FUNC u16 *GetRivalNamePtr(struct UnkStruct_02024E64 *unk)
{
    return unk->rival_name_buf;
}

THUMB_FUNC void RivalsNameToU16Array(struct UnkStruct_02024E64 *unk, struct String *str)
{
    CopyStringToU16Array(str, unk->rival_name_buf, sizeof(unk->rival_name_buf) / sizeof(u16));
}

THUMB_FUNC u16 *FUN_02024F0C(struct UnkStruct_02024E64 *unk)
{
    return unk->unk734;
}

THUMB_FUNC void FUN_02024F18(struct UnkStruct_02024E64 *unk, struct String *str)
{
    CopyStringToU16Array(str, unk->unk734, sizeof(unk->unk734) / sizeof(u16));
}
