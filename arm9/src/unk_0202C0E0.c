#include "global.h"
#include "save.h"
#include "unk_0202C0E0.h"

u32 FUN_0202C0E0()
{
    return sizeof(struct UnkSaveStruct0202C0E4); // 0x28
}

void FUN_0202C0E4(struct UnkSaveStruct0202C0E4 *unkStruct)
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

void FUN_0202C108(struct SaveData *save, u32 a1, u32 a2)
{
    struct UnkSaveStruct0202C0E4 *unkSavStruct = SaveArray_Get(save, 33);
    if (unkSavStruct->data[a1][a2] < 9999)
    {
        unkSavStruct->data[a1][a2]++;
    }
}

u16 FUN_0202C12C(struct SaveData *save, u32 a1, u32 a2)
{
    struct UnkSaveStruct0202C0E4 *unkSavStruct = SaveArray_Get(save, 33);
    return unkSavStruct->data[a1][a2];
}
