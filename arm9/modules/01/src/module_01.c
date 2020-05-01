#include "global.h"

u32 UNK_021D7500[8];

THUMB_FUNC void MOD01_021D74E0(void)
{
    UNK_021D7500[1]++;
}

THUMB_FUNC void (*UNK_021D74F0[4])(void) = {
    MOD01_021D74E0
};
