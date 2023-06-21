#include "global.h"
#include "string_control_code.h"

const u16 * MsgArray_SkipControlCode(const u16 *arr)
{
    GF_ASSERT(*arr == EXT_CTRL_CODE_BEGIN);
    if (*arr == EXT_CTRL_CODE_BEGIN) {
        u16 size = arr[2];
        arr += 3;
        arr += size;
    }
    return arr;
}

u32 MsgArray_GetControlCode(const u16 *arr)
{
    GF_ASSERT(*arr == EXT_CTRL_CODE_BEGIN);
    return arr[1];
}

BOOL MsgArray_ControlCodeIsStrVar(const u16 *arr)
{
    return (MsgArray_GetControlCode(arr) & 0xFF00) == 0x100;
}

u32 MsgArray_ControlCodeGetField(const u16 *arr, u32 fieldno)
{
    GF_ASSERT(*arr == EXT_CTRL_CODE_BEGIN);
    GF_ASSERT(fieldno < arr[2]);
    return arr[3 + fieldno];
}
