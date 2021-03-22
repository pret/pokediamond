#include "scrcmd.h"
#include "bag.h"

extern u16 VarGet(struct UnkSavStruct80* arg, u16);
extern u16* GetVarPointer(struct UnkSavStruct80* arg, u16);

const u16 UNK_020F450C[7][2] = {
    { 0x0067, 0x008E },
    { 0x0065, 0x008A },
    { 0x0066, 0x008C },
    { 0x0063, 0x0159 },
    { 0x0064, 0x015B },
    { 0x0068, 0x019A },
    { 0x0069, 0x0198 },
};

THUMB_FUNC BOOL ScrCmd_Unk01F1(struct ScriptContext * ctx)
{
    struct UnkSavStruct80 * sav_ptr = ctx->unk80;

    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    u8 i;
    u16 total;
    for (i = 0, total = 0; i < 7; i++)
    {
        total += Bag_GetQuantity(Sav2_Bag_get(sav_ptr->saveBlock2), UNK_020F450C[i][0], 4);
    }

    *ret_ptr = total;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01F4(struct ScriptContext * ctx)
{
    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unk = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

    *ret_ptr = 0;

    for (u16 i = 0; i < 7; i++)
    {
        if (UNK_020F450C[i][0] == unk)
        {
            *ret_ptr = UNK_020F450C[i][1];
            break;
        }
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01F5(struct ScriptContext * ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    u16 * ret_ptr1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 * ret_ptr2 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 needed_amount = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

    *ret_ptr1 = 0;
    *ret_ptr2 = 0;

    u8 i = 0;
    u16 total = 0;
    for (; i < 7; i++)
    {
        total += Bag_GetQuantity(Sav2_Bag_get(sav_ptr->saveBlock2), UNK_020F450C[i][0], 4);
        if (total >= needed_amount)
        {
            *ret_ptr1 = UNK_020F450C[i][0];
            *ret_ptr2 = i;
            break;
        }
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01F2(struct ScriptContext * ctx)
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01F3(struct ScriptContext * ctx)
{
#pragma unused(ctx)
    return FALSE;
}
