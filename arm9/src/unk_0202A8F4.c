#include "global.h"
#include "save_block_2.h"

struct Unk0202A8F4
{
    u8 u_0;
    u8 u_1;
    u8 u_2;
    u8 u_3;
    u8 u_4;
    u8 u_5;
    u8 u_6;
    u8 u_7;
    u8 u_8;
    u8 u_9;
    u8 u_A;
    u8 u_B;
    u8 u_C;
    u8 u_D;
};

u32 FUN_0202A8F4();
void FUN_0202A8F8(struct Unk0202A8F4 *unk);
void *FUN_0202A918(void *arg0);

THUMB_FUNC u32 FUN_0202A8F4()
{
    return sizeof(struct Unk0202A8F4);
}

THUMB_FUNC void FUN_0202A8F8(struct Unk0202A8F4 *unk)
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

THUMB_FUNC void *FUN_0202A918(void *arg0)
{
    return SavArray_get(arg0, 24);
}
