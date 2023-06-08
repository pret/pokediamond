#include "MSL_Common_rand.h"
#include "code32.h"

static u32 random_next = 1;

s32 rand(void)
{
    random_next = random_next * 1103515245 + 12345;
    return ((random_next >> 16) & 0x7fff);
}

void srand(u32 seed)
{
    random_next = seed;
}
