#include "global.h"
#include "save_block_2.h"
#include "MI_memory.h"

void *FUN_0202ABBC(struct SaveBlock2* sav);
u32 FUN_0202ABC8();
void FUN_0202ABCC(void *destp);
u16 FUN_0202ABDC(void *unkSavStruct);
void FUN_0202ABE4(void *unkSavStruct, u16 data);
void FUN_0202ABEC(void *srcp, void *destp);
void FUN_0202ABF8(void *destp, void *srcp);
u32 FUN_0202AC08(void *unkStruct);
void FUN_0202AC10(void *unkStruct, u32 data);
u16 FUN_0202AC18(void *unkStruct);

THUMB_FUNC void *FUN_0202ABBC(struct SaveBlock2* sav)
{
    return SavArray_get(sav, 26);
}

THUMB_FUNC u32 FUN_0202ABC8()
{
    return 0xf4; // 244
}

THUMB_FUNC void FUN_0202ABCC(void *destp)
{
    MIi_CpuClearFast(0, destp, 0xf4);
}

THUMB_FUNC u16 FUN_0202ABDC(void *unkSavStruct)
{
    return *(u16 *)(unkSavStruct + 0xec);
}

THUMB_FUNC void FUN_0202ABE4(void *unkSavStruct, u16 data)
{
    *(u16 *)(unkSavStruct + 0xec) = data;
}

THUMB_FUNC void FUN_0202ABEC(void *srcp, void *destp)
{
    MIi_CpuCopyFast(srcp, destp, 0xec);
}

THUMB_FUNC void FUN_0202ABF8(void *destp, void *srcp)
{
    MIi_CpuCopyFast(srcp, destp, 0xec);
}

THUMB_FUNC u32 FUN_0202AC08(void *unkStruct)
{
    return *(u32 *)(unkStruct + 0xf0);
}

THUMB_FUNC void FUN_0202AC10(void *unkStruct, u32 data)
{
    *(u32 *)(unkStruct + 0xf0) = data;
}

THUMB_FUNC u16 FUN_0202AC18(void *unkStruct)
{
    return *(u16 *)(unkStruct + 0xee);
}