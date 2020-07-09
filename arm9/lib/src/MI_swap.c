#include "global.h"
#include "MI_swap.h"

/*
 * Exchange 32 bits of data between register and memory.
 *
 * The SDK also defines an 8-bit version of this routine,
 * but it is not linked in pokediamond.
 */

asm
u32 MI_SwapWord(register u32 setData, register vu32 * destp)
{
    swp setData, setData, [destp]
    bx lr
}
