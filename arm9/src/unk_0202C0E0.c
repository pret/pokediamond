#include "global.h"
#include "save_block_2.h"


struct UnkSaveStruct0202C0E4
{
    u16 data[5][4];
};

u32 FUN_0202C0E0();
void FUN_0202C0E4(struct UnkSaveStruct0202C0E4 *unkStruct);
void FUN_0202C108(struct SaveBlock2 *save, u32 a1, u32 a2);
u16 FUN_0202C12C(struct SaveBlock2 *save, u32 a1, u32 a2);


THUMB_FUNC u32 FUN_0202C0E0()
{
    return sizeof(struct UnkSaveStruct0202C0E4); // 40
}


THUMB_FUNC void FUN_0202C0E4(struct UnkSaveStruct0202C0E4 *unkStruct)
{

    int j, i = 0;

    do {
        j = 0;
        do {
            unkStruct->data[i][j] = 0;
            j++;
        } while (j < 4);
        i++;
    } while (i < 5);
}

THUMB_FUNC void FUN_0202C108(struct SaveBlock2 *save, u32 a1, u32 a2)
{
    struct UnkSaveStruct0202C0E4 *unkSavStruct = SavArray_get(save, 0x21);
    if (unkSavStruct->data[a1][a2] < 9999)
    {
        unkSavStruct->data[a1][a2]++;
    }
}

THUMB_FUNC u16 FUN_0202C12C(struct SaveBlock2 *save, u32 a1, u32 a2)
{
    struct UnkSaveStruct0202C0E4 *unkSavStruct = SavArray_get(save, 0x21);
    return unkSavStruct->data[a1][a2];
}