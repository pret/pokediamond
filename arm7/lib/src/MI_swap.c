#include "MI_swap.h"
#include "code32.h"

asm u32 MI_SwapWord(register u32 data, register u32 * dst) {
    swp	r0, r0, [r1]
    bx	lr
}
