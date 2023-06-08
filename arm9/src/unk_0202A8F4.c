#include "global.h"
#include "save_block_2.h"
#include "unk_0202A8F4.h"

u32 FUN_0202A8F4()
{
    return sizeof(struct Unk0202A8F4);
}

void FUN_0202A8F8(struct Unk0202A8F4 *unk)
{
    unk->u_0 = 0;
    unk->u_1 = 0;
    unk->u_2 = 0;
    unk->u_3 = 0;
    unk->u_4 = 0;
    unk->u_5 = 0;
    unk->u_6 = 0;
    unk->u_7 = 0;
    unk->u_8 = 0;
    unk->u_9 = 0;
    unk->u_A = 0;
    unk->u_B = 0;
    unk->u_C = 0;
    unk->u_D = 0;    
}

void *FUN_0202A918(struct SaveBlock2* sav2)
{
    return SaveArray_Get(sav2, 24);
}
