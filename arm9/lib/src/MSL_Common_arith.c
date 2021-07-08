#include "MSL_Common_arith.h"
#include "function_target.h"

ARM_FUNC s32 abs(s32 val)
{
    return val < 0 ? -val : val;
}
