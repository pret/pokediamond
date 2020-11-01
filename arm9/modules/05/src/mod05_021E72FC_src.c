#include "global.h"
#include "mod05_021E72FC.h"

extern UnkStruct021E7358 *MOD05_021E74D4(u32 param0);
extern void FUN_020054C8(u32 param0);
extern MOD05_021E73B4();
extern void FUN_020463CC(u32 param0, void *func, UnkStruct021E7358 *param2);
extern void FUN_020553A0(u32 param0);
extern u32 FUN_02058720(void);
extern BOOL FUN_02054B30(u8 param0);
extern BOOL FUN_02054B3C(u8 param0);
extern BOOL FUN_02054B48(u8 param0);
extern BOOL FUN_02054B54(u8 param0);

THUMB_FUNC BOOL MOD05_021E72FC(u32 param0, u32 param1)
{
    FUN_020553A0(param1);
    u8 res = (u8)FUN_02058720();
    u32 r2;
    if (FUN_02054B30(res) == TRUE)
    {
        r2 = 3;
        goto label;
    }
    else if (FUN_02054B3C(res) == TRUE)
    {
        r2 = 2;
        goto label;
    }
    else if (FUN_02054B48(res) == TRUE)
    {
        r2 = 0;
        goto label;
    }
    else if (FUN_02054B54(res) == TRUE)
    {
        r2 = 1;
        goto label;
    }
    return FALSE;
label:
    MOD05_021E7358(param0, param1, r2);
    return TRUE;
}

THUMB_FUNC void MOD05_021E7358(u32 param0, u32 param1, u32 param2)
{
    UnkStruct021E7358 *res = MOD05_021E74D4(24);
    res->Unk0C = param0;
    res->Unk10 = param1;
    res->Unk00 = param2;
    FUN_020054C8(1624);
    FUN_020463CC(param0, MOD05_021E73B4, res);
}

THUMB_FUNC u32 MOD05_021E7388(u32 param0)
{
    switch (param0)
    {
        case 0:
            return 2;
        case 2:
            return 1;
        case 1:
            return 3;
        case 3:
            return 0;
    }
    return 0;
}
