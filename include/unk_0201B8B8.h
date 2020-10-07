#ifndef POKEDIAMOND_UNK_0201B8B88_H
#define POKEDIAMOND_UNK_0201B8B88_H

const u16 * MsgArray_SkipControlCode(const u16 * r4);
u16 MsgArray_GetControlCode(const u16 * r4);
BOOL MsgArray_ControlCodeIsStrVar(const u16 * r4);
u16 MsgArray_ControlCodeGetField(const u16 * r5, u32 r4);

#endif //POKEDIAMOND_UNK_0201B8B88_H
