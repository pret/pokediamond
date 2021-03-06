#include "global.h"
#include "save_block_2.h"
#include "unk_0202C0E0.h"

THUMB_FUNC u32 FUN_0202C0E0()
{
    return sizeof(struct UnkSaveStruct0202C0E4); // 0x28
}

THUMB_FUNC void FUN_0202C0E4(struct UnkSaveStruct0202C0E4 *unkStruct)
{
    s32 j, i;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 4; j++)
        {
            unkStruct->data[i][j] = 0;
        }
    }
}

THUMB_FUNC void FUN_0202C108(struct SaveBlock2 *sav2, u32 a1, u32 a2)
{
    struct UnkSaveStruct0202C0E4 *unkSavStruct = SavArray_get(sav2, 33);
    if (unkSavStruct->data[a1][a2] < 9999)
    {
        unkSavStruct->data[a1][a2]++;
    }
}

THUMB_FUNC u16 FUN_0202C12C(struct SaveBlock2 *sav2, u32 a1, u32 a2)
{
    struct UnkSaveStruct0202C0E4 *unkSavStruct = SavArray_get(sav2, 33);
    return unkSavStruct->data[a1][a2];
}
