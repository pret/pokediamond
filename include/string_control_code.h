#ifndef POKEDIAMOND_STRING_CONTROL_CODE_H
#define POKEDIAMOND_STRING_CONTROL_CODE_H

const u16 * MsgArray_SkipControlCode(const u16 * r4);
u32 MsgArray_GetControlCode(const u16 * r4);
BOOL MsgArray_ControlCodeIsStrVar(const u16 * r4);
u32 MsgArray_ControlCodeGetField(const u16 * r5, u32 r4);

#endif //POKEDIAMOND_STRING_CONTROL_CODE_H
