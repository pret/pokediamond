
#include "unk_02015E30.h"

u64 UNK_021C48B0;
u64 UNK_021C48A8;
u64 UNK_021C48A0;
struct IGT * UNK_021C489C;
u32 UNK_021C4898;

THUMB_FUNC void FUN_02015E30()
{
    UNK_021C4898 = 0;
}

THUMB_FUNC void FUN_02015E3C(struct IGT *igt)
{
    UNK_021C4898 = 1;
    UNK_021C48A8 = 0;
    UNK_021C48A0 = 0;
    UNK_021C489C = igt;

    UNK_021C48B0 = GetTimer3Count();
}

THUMB_FUNC void FUN_02015E60()
{
    if (UNK_021C4898 != 0)
    {
        u64 res = Timer3CountToSeconds(GetTimer3Count() - UNK_021C48B0);

        if (UNK_021C48A0 < res)
        {
            AddIGTSeconds(UNK_021C489C, (u32)(res - UNK_021C48A0));
            UNK_021C48A0 = res;
        }
    }
}
