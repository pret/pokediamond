#include "global.h"
#include "save_block_2.h"
#include "MI_memory.h"
#include "seal.h"

#pragma thumb on

u32 Save_SealCase_sizeof(void)
{
    return sizeof(struct SealCase);
}

void Save_SealCase_Init(struct SealCase * sealCase)
{
    MI_CpuClear8(sealCase, Save_SealCase_sizeof());
}

void CapsuleArray_Copy(const CapsuleArray * a0, CapsuleArray * a1)
{
    MI_CpuCopy8(a0, a1, sizeof(CapsuleArray));
}

struct SealCase * Save_SealCase_Get(struct SaveBlock2 * sav2)
{
    return (struct SealCase *)SaveArray_Get(sav2, 21);
}

CapsuleArray * SealCase_GetCapsuleI(struct SealCase * sealCase, s32 idx)
{
    GF_ASSERT(idx < 12);
    return &sealCase->coords[idx];
}

void SealCase_SetCapsuleI(struct SealCase * sealCase, const CapsuleArray * src, s32 idx)
{
    GF_ASSERT(idx < 12);
    CapsuleArray_Copy(src, SealCase_GetCapsuleI(sealCase, idx));
}

Coords8 * Capsule_GetSealI(CapsuleArray * a0, s32 a1)
{
    GF_ASSERT(a1 < 8);
    return &(*a0)[a1];
}

s32 Seal_GetId(Coords8 * a0)
{
    return (*a0)[0];
}

s32 Seal_GetXCoord(Coords8 * a0)
{
    return (*a0)[1];
}

s32 Seal_GetYCoord(Coords8 * a0)
{
    return (*a0)[2];
}
