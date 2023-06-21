#ifndef POKEDIAMOND_STRING_CONTROL_CODE_H
#define POKEDIAMOND_STRING_CONTROL_CODE_H

const u16 * MsgArray_SkipControlCode(const u16 *arr);
u32 MsgArray_GetControlCode(const u16 *arr);
BOOL MsgArray_ControlCodeIsStrVar(const u16 *arr);
u32 MsgArray_ControlCodeGetField(const u16 *arr, u32 fieldno);

#endif //POKEDIAMOND_STRING_CONTROL_CODE_H
