#include "scrcmd.h"

const u16 UNK_020F452A[19][2] = {
    { 0x00FB, 0x03E8 },
    { 0x0109, 0x03E8 },
    { 0x0114, 0x03E8 },
    { 0x0115, 0x03E8 },
    { 0x01A1, 0x07D0 },
    { 0x0181, 0x07D0 },
    { 0x0192, 0x0FA0 },
    { 0x0167, 0x0FA0 },
    { 0x0173, 0x1770 },
    { 0x01A0, 0x1770 },
    { 0x0151, 0x1770 },
    { 0x0162, 0x1F40 },
    { 0x015C, 0x1F40 },
    { 0x016A, 0x2710 },
    { 0x015F, 0x2710 },
    { 0x0154, 0x2710 },
    { 0x0164, 0x2710 },
    { 0x0191, 0x3A98 },
    { 0x018B, 0x4E20 },
};

THUMB_FUNC BOOL ScrCmd_Unk02A6(struct ScriptContext * ctx)
{
    u16 idx = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 * ret_ptr1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 * ret_ptr2 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    *ret_ptr1 = UNK_020F452A[idx][0];
    *ret_ptr2 = UNK_020F452A[idx][1];

    return FALSE;
}
