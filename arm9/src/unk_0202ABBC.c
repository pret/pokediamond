#include "global.h"
#include "save_block_2.h"
#include "MI_memory.h"
#include "unk_0202ABBC.h"

THUMB_FUNC void *FUN_0202ABBC(struct SaveBlock2* sav2)
{
    return SavArray_get(sav2, 26);
}

THUMB_FUNC u32 FUN_0202ABC8()
{
    return sizeof(struct Unk0202ABBC); // 0xF4
}

THUMB_FUNC void FUN_0202ABCC(struct Unk0202ABBC* unk)
{
    MI_CpuClearFast(unk, sizeof(struct Unk0202ABBC));
}

THUMB_FUNC u16 FUN_0202ABDC(struct Unk0202ABBC* unk)
{
    return unk->unk_EC;
}

THUMB_FUNC void FUN_0202ABE4(struct Unk0202ABBC* unk, u16 data)
{
    unk->unk_EC = data;
}

THUMB_FUNC void FUN_0202ABEC(void *srcp, void *destp)
{
    MI_CpuCopyFast(srcp, destp, 0xec);
}

THUMB_FUNC void FUN_0202ABF8(void *destp, void *srcp)
{
    MI_CpuCopyFast(srcp, destp, 0xec);
}

THUMB_FUNC u32 FUN_0202AC08(struct Unk0202ABBC* unk)
{
    return unk->unk_F0;
}

THUMB_FUNC void FUN_0202AC10(struct Unk0202ABBC* unk, u32 data)
{
    unk->unk_F0 = data;
}

THUMB_FUNC u16 FUN_0202AC18(struct Unk0202ABBC* unk)
{
    return unk->unk_EE;
}
