#include "global.h"
#include "mod05_021E72FC.h"
#include "constants/sndseq.h"
#include "heap.h"
#include "unk_020051F4.h"

extern void FUN_020463CC(u32 param0, void *func, UnkStruct021E7358 *param2);
extern u32 FUN_020553A0(u32 param0);
extern u32 FUN_02058720(u32 param0);
extern BOOL FUN_02054B30(u8 param0);
extern BOOL FUN_02054B3C(u8 param0);
extern BOOL FUN_02054B48(u8 param0);
extern BOOL FUN_02054B54(u8 param0);
extern UnkStruct021E7358 *FUN_0204652C(UnkStruct021E7358 *param0);
extern void FUN_02058410(u32 param0, u32 param1);
extern BOOL FUN_02057254(u32 param0);
extern u32 FUN_0205AFDC(u32 param0, u32 param1);
extern void FUN_02057260(u32 param0, u32 param1);
extern void FUN_02055304(u32 param0, u32 param1);
extern BOOL FUN_02056B74(u32 param0, u32 param1, u32 param2);
extern void FUN_02058418(u32 param0, u32 param1);

THUMB_FUNC BOOL MOD05_021E72FC(u32 param0, u32 param1)
{
    u8 res = (u8)FUN_02058720(FUN_020553A0(param1));
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
    PlaySE(SEQ_SE_DP_F209);
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

THUMB_FUNC BOOL MOD05_021E73B4(UnkStruct021E7358 *param0)
{
    UnkStruct021E7358 *strct = FUN_0204652C(param0);
    u32 res = FUN_020553A0(strct->Unk10);
    u8 res2 = (u8)FUN_02058720(res);
    switch (strct->Unk08)
    {
        case 0:
            FUN_02058410(res, 1 << 8);
            strct->Unk08++;
            break;
        case 1:
            if (!FUN_02057254(strct->Unk10))
            {
                break;
            }
            FUN_02057260(strct->Unk10, FUN_0205AFDC(strct->Unk00, 12));
            FUN_02055304(strct->Unk10, strct->Unk00);
            strct->Unk08++;
            strct->Unk04 = 7;
            break;
        case 2:
            if (strct->Unk04 == 2 || strct->Unk04 == 4 || strct->Unk04 == 6)
            {
                strct->Unk00 = MOD05_021E7388(strct->Unk00);
                FUN_02055304(strct->Unk10, strct->Unk00);
            }
            if (--(strct->Unk04))
            {
                break;
            }
            if (FUN_02054B30(res2) == TRUE)
            {
                strct->Unk00 = 3;
            }
            else if (FUN_02054B3C(res2) == TRUE)
            {
                strct->Unk00 = 2;
            }
            else if (FUN_02054B48(res2) == TRUE)
            {
                strct->Unk00 = 0;
            }
            else if (FUN_02054B54(res2) == TRUE)
            {
                strct->Unk00 = 1;
            }
            else
            {
                strct->Unk00 = MOD05_021E7388(strct->Unk00);
            }
            if (FUN_02056B74(strct->Unk10, res, strct->Unk00) == FALSE)
            {
                strct->Unk08 = 1;
                break;
            }
            FUN_02058418(res, 0x80);
            FUN_02058418(res, 1 << 8);
            FUN_02055304(strct->Unk10, strct->Unk00);
            MOD05_021E74F8(strct);
            FUN_020054F0(1624, 0);
            return TRUE;
    }
    return FALSE;
}

THUMB_FUNC UnkStruct021E7358 *MOD05_021E74D4(u32 param0)
{
    UnkStruct021E7358 *res = (UnkStruct021E7358 *)AllocFromHeapAtEnd(4, param0);
    if (res == NULL)
    {
        GF_AssertFail();
    }
    memset((void *)res, 0, param0);
    return res;
}

THUMB_FUNC void MOD05_021E74F8(UnkStruct021E7358 *param0)
{
    FreeToHeapExplicit(4, param0);
}
