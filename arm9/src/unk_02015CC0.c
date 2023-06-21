#include "global.h"
#include "unk_02015CC0.h"
#include "constants/map_sections.h"

const u16 UNK_020ED72C[] = {
    0,
    METLOC_DAY_CARE_COUPLE,
    METLOC_LOVELY_PLACE
};

int sub_02015CC0(u16 a0)
{
    int i;
    for (i = 0; i < (int)NELEMS(UNK_020ED72C) - 1; i++) {
        if (a0 < UNK_020ED72C[i + 1])
            return i;
    }
    return i;
}

int sub_02015CE0(u16 a0)
{
    return a0 - UNK_020ED72C[sub_02015CC0(a0)];
}

int sub_02015CF8(int a0, int a1)
{
    GF_ASSERT(a0 < (int)NELEMS(UNK_020ED72C));
    return a1 + UNK_020ED72C[a0];
}
