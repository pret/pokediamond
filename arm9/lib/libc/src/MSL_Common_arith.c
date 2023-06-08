#include "MSL_Common_arith.h"
#include "nitro/types.h"
#include "code32.h"

s32 abs(s32 val)
{
    return val < 0 ? -val : val;
}
