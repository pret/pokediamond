
#include "unk_02015E30.h"

struct UnkStruct_02015E30 UNK_021C4898;

THUMB_FUNC void FUN_02015E30()
{
    UNK_021C4898.unk00 = 0;
}

THUMB_FUNC void FUN_02015E3C(struct IGT *igt)
{
    struct UnkStruct_02015E30 *unk1 = &UNK_021C4898;
    UNK_021C4898.unk00 = 1;
    UNK_021C4898.unk10 = 0;
    UNK_021C4898.unk14 = 0;
    UNK_021C4898.unk08 = 0;
    UNK_021C4898.unk04 = igt;

    UNK_021C4898.unk18 = GetTimer3Count();
}

THUMB_FUNC void FUN_02015E60()
{
    if (UNK_021C4898.unk00 != 0)
    {
        u64 res = Timer3CountToSeconds(GetTimer3Count() - UNK_021C4898.unk18);

        if (UNK_021C4898.unk08 < res)
        {
            AddIGTSeconds(UNK_021C4898.unk04, (u32)(res - UNK_021C4898.unk08));
            UNK_021C4898.unk08 = res;
        }
    }
}
