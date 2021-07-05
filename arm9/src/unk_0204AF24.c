#include "global.h"
#include "unk_0204AF24.h"

extern void FUN_02037394(struct UnkSavStruct80 *);
extern u32 FUN_0200E308(void);
extern void FUN_0200E1D0(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 heap_id);
extern void MOD05_021E331C(struct UnkSavStruct80 *);

THUMB_FUNC BOOL FUN_0204AF24(struct UnkStruct_0204639C * arg0)
{
    if(!FUN_0203739C(FUN_02046528(arg0)))
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC void FUN_0204AF3C(struct UnkStruct_0204639C * r5)
{
    struct UnkSavStruct80 * r4 = FUN_02046528(r5);
    if(!FUN_0203739C(r4))
    {
        GF_ASSERT(0);
        return;
    }
    FUN_02037394(r4);
    FUN_0204640C(r5, &FUN_0204AF24, NULL);
}

THUMB_FUNC BOOL FUN_0204AF6C(struct UnkStruct_0204639C * arg0)
{
    if(FUN_020464A4(FUN_02046528(arg0)))
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC void FUN_0204AF84(struct UnkStruct_0204639C * r5)
{
    struct UnkSavStruct80 * r4 = FUN_02046528(r5);
    if(FUN_0203739C(r4))
    {
        GF_ASSERT(0);
        return;
    }
    FUN_0204649C(r4);
    FUN_0204640C(r5, &FUN_0204AF6C, NULL);
}

THUMB_FUNC BOOL FUN_0204AFB4(struct UnkStruct_0204639C * arg0)
{
#pragma unused(arg0)
    if(FUN_0200E308())
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC void FUN_0204AFC8(struct UnkStruct_0204639C * r4)
{
    if(!FUN_0203739C(FUN_02046528(r4)))
    {
        GF_ASSERT(0);
        return;
    }
    FUN_0200E1D0(0, 0, 0, 0, 6, 1, 4);
    FUN_0204640C(r4, &FUN_0204AFB4, 0);
}

THUMB_FUNC void FUN_0204B00C(struct UnkStruct_0204639C * r4)
{
    if(!FUN_0203739C(FUN_02046528(r4)))
    {
        GF_ASSERT(0);
        return;
    }
    FUN_0200E1D0(0, 1, 1, 0, 6, 1, 4);
    FUN_0204640C(r4, FUN_0204AFB4, 0);
}

THUMB_FUNC BOOL FUN_0204B050(struct UnkStruct_0204639C * r5)
{
    u32 * r4 = FUN_02046530(r5);
    switch(r4[0])
    {
        case 0:
            FUN_0204AFC8(r5);
            r4[0]++;
            break;
        case 1:
            FUN_0204AF3C(r5);
            r4[0]++;
            break;
        case 2:
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

THUMB_FUNC void FUN_0204B090(struct UnkStruct_0204639C * r0)
{
    FUN_0204640C(r0, &FUN_0204B050, 0);
}

THUMB_FUNC BOOL FUN_0204B0A0(struct UnkStruct_0204639C * r5)
{
    u32 * r4 = FUN_02046530(r5);
    struct UnkSavStruct80 * r0 = FUN_02046528(r5);
    switch(r4[0])
    {
        case 0:
            FUN_0204AF84(r5);
            r4[0]++;
            break;
        case 1:
            MOD05_021E331C(r0);
            FUN_0204B00C(r5);
            r4[0]++;
            break;
        case 2:
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

THUMB_FUNC void FUN_0204B0E8(struct UnkStruct_0204639C * r0)
{
    FUN_0204640C(r0, &FUN_0204B0A0, 0);
}
