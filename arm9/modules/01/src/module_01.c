#include "global.h"

u32 UNK_021D7500[8];

void MOD01_021D74E0(void)
{
    UNK_021D7500[1]++;
}

void (*UNK_021D74F0[4])(void) = {
    MOD01_021D74E0
};
