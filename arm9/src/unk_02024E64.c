#include "global.h"
#include "unk_02024E64.h"

extern void FUN_020250A4(void *param0);
extern void FUN_02025484(void *param0);

u32 FUN_02024E64()
{
    return sizeof(struct UnkStruct_02024E64);
}

void FUN_02024E6C(struct UnkStruct_02024E64 *param0)
{
    MI_CpuClearFast(param0, sizeof(struct UnkStruct_02024E64));

    FUN_020250A4(param0->unk0);

    FUN_02025484(param0->unk700);

    MI_CpuFill16(param0->rival_name_buf, EOS, sizeof(param0->rival_name_buf) / sizeof(u16));
    MI_CpuFill16(param0->unk734, EOS, sizeof(param0->unk734) / sizeof(u16));
}

struct UnkStruct_02024E64 *FUN_02024EB4(struct SaveData *save)
{
    return SaveArray_Get(save, 0xa);
}

void *FUN_02024EC0(struct SaveData *save)
{
    return FUN_02022634(save, 0xa);
}

struct UnkStruct_02024E64 *FUN_02024ECC(struct SaveData *save)
{
    return SaveArray_Get(save, 0xa);
}

void *FUN_02024ED8(struct SaveData *save)
{
    struct UnkStruct_02024E64 *res = SaveArray_Get(save, 0xa);
    return res->unk700;
}

u16 *GetRivalNamePtr(struct UnkStruct_02024E64 *unk)
{
    return unk->rival_name_buf;
}

void RivalsNameToU16Array(struct UnkStruct_02024E64 *unk, struct String *str)
{
    CopyStringToU16Array(str, unk->rival_name_buf, sizeof(unk->rival_name_buf) / sizeof(u16));
}

u16 *FUN_02024F0C(struct UnkStruct_02024E64 *unk)
{
    return unk->unk734;
}

void FUN_02024F18(struct UnkStruct_02024E64 *unk, struct String *str)
{
    CopyStringToU16Array(str, unk->unk734, sizeof(unk->unk734) / sizeof(u16));
}
