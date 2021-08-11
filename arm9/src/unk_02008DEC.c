#include "global.h"
#include "unk_02008DEC.h"
#include "NNS_g2d.h"
#include "gf_gfx_loader.h"
#include "heap.h"

extern u32 FUN_02020C44(u32, u32);
extern void FUN_02020C90(u32);
extern u32 FUN_02020CB0(u32 param0, s32 param1);
extern void FUN_02020E1C(u32 param0, u32 param1);
extern void FUN_02020D68(u32 param0, u32 param1);
extern s32 FUN_02020E38(u32);
extern void *FUN_02020E0C(u32);
extern BOOL NNS_G2dGetUnpackedMultiCellBank(void *, void *);
extern BOOL NNS_G2dGetUnpackedMCAnimBank(void *, void *);
extern u32 FUN_02020D10(u32, void *, s32, u32);
extern u32 FUN_02020CD4(u32, void *, u32);
extern u32 FUN_0201D1F8(u32 *param0);
extern u32 FUN_0201D250(u32 *param0);
extern void FUN_0201D2DC(u32, u32);
extern void FUN_0201D324(u32 param0);
extern u32 FUN_0201D3B0(u32);
extern u32 FUN_0201D3D4(u32, u32);
extern u32 FUN_0201D458(u32);
extern void FUN_0201D4F0(u32);
extern u32 FUN_0201E0E4(u32 *param0);
extern u32 FUN_0201E128(u32 *param0);
extern void FUN_0201E168(u32, u32);
extern void FUN_0201E1C8(u32);
extern u32 FUN_0201E258(u32, u32);
extern u32 FUN_0201E230(u32);
extern s32 NNS_G2dGetImagePaletteLocation(u32, u32);

THUMB_FUNC struct UnkStruct1 *FUN_02008DEC(u32 param0, s32 param1, u32 heap_id)
{
    struct UnkStruct1 *ptr = AllocFromHeap(heap_id, sizeof(struct UnkStruct1));
    ptr->unk00 = FUN_02020C44(param0, heap_id);
    ptr->unk04 = AllocFromHeap(heap_id, param0 * sizeof(struct UnkStruct1_sub));
    memset(ptr->unk04, 0, param0 * sizeof(struct UnkStruct1_sub));
    ptr->unk08 = (s32)param0;
    ptr->unk0C = 0;
    ptr->unk10 = param1;

    return ptr;
}

THUMB_FUNC void FUN_02008E2C(struct UnkStruct1 *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk00);
    GF_ASSERT(param0->unk04);

    FUN_020094C4(param0);

    FUN_02020C90(param0->unk00);
    param0->unk00 = 0;

    FreeToHeap(param0->unk04);
    param0->unk04 = NULL;

    FreeToHeap(param0);
}

THUMB_FUNC struct UnkStruct1_sub *FUN_02008E6C(
    struct UnkStruct1 *param0, struct UnkStruct2 *param1, s32 param2, u32 param3)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1);
    GF_ASSERT(param1->unk04 > param2);
    GF_ASSERT(param0->unk10 == param1->unk08);

    struct UnkStruct1_sub *st1c = FUN_020097D0(param0);
    GF_ASSERT(st1c);

    if (param1->unk0C == 0)
    {
        struct UnkStruct3 *r6 = &((struct UnkStruct3 *)param1->unk00)[param2];
        GF_ASSERT(FUN_0200945C(param0, r6->unk00) == 1);

        FUN_0200994C(
            param0, st1c, r6->unk04, r6->unk00, r6->unk44, r6->unk48, param1->unk08, param3);
    }
    else
    {
        struct UnkStruct4 *r6 = &((struct UnkStruct4 *)param1->unk00)[param2];
        GF_ASSERT(FUN_0200945C(param0, r6->unk0C) == 1);

        FUN_02009978(param0,
            st1c,
            r6->unk00,
            r6->unk04,
            r6->unk08,
            r6->unk0C,
            r6->unk10,
            r6->unk14,
            param1->unk08,
            param3,
            FALSE);
    }

    param0->unk0C++;

    return st1c;
}

THUMB_FUNC struct UnkStruct1_sub *FUN_02008F34(struct UnkStruct1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    struct UnkStruct1_sub *r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_02009978(param0, r6, param1, param2, param3, param4, param5, 0, 0, param6, FALSE);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC struct UnkStruct1_sub *FUN_02008F90(struct UnkStruct1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    BOOL param7)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    struct UnkStruct1_sub *r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_02009978(param0, r6, param1, param2, param3, param4, param5, 0, 0, param6, param7);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC struct UnkStruct1_sub *FUN_02008FEC(struct UnkStruct1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    struct UnkStruct1_sub *r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_02009978(param0, r6, param1, param2, param3, param4, param5, param6, 1, param7, FALSE);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC struct UnkStruct1_sub *FUN_0200904C(struct UnkStruct1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    BOOL param8)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    struct UnkStruct1_sub *r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_02009978(param0, r6, param1, param2, param3, param4, param5, param6, 1, param7, param8);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC struct UnkStruct1_sub *FUN_020090AC(struct UnkStruct1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6)
{
    GF_ASSERT(param0);

    struct UnkStruct1_sub *r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_02009978(param0, r6, param1, param2, param3, param4, 0, 0, param5, param6, FALSE);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC void FUN_020090FC(struct UnkStruct1 *param0,
    struct UnkStruct1_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);
    GF_ASSERT(param1);
    GF_ASSERT(param1->unk04 == 0);

    s32 r6 = FUN_02009530(param1);
    u32 r7 = FUN_020095E4(param1);
    FUN_02009490(param0, param1);

    FUN_02009978(param0, param1, param2, param3, param4, r6, r7, 0, 0, param5, FALSE);
}

THUMB_FUNC void FUN_02009168(struct UnkStruct1 *param0,
    struct UnkStruct1_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);
    GF_ASSERT(param1);
    GF_ASSERT(param1->unk04 == 1);

    s32 r6 = FUN_02009530(param1);
    u32 r7 = FUN_020095E4(param1);
    u32 st24 = FUN_02009610(param1);
    FUN_02009490(param0, param1);

    FUN_02009978(param0, param1, param2, param3, param4, r6, r7, st24, 1, param5, 0);
}

THUMB_FUNC u32 FUN_020091E0(struct UnkStruct1 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    u32 r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_020099B0(param0, r6, param1, param2, param3, param4, param5, 0, 0, param6, 0);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC u32 FUN_0200923C(struct UnkStruct1 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    u32 r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_020099B0(param0, r6, param1, param2, param3, param4, param5, 0, 0, param6, param7);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC u32 FUN_02009298(struct UnkStruct1 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    u32 r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_020099B0(param0, r6, param1, param2, param3, param4, param5, param6, 1, param7, 0);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC u32 FUN_020092F8(struct UnkStruct1 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    u32 r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_020099B0(param0, r6, param1, param2, param3, param4, param5, param6, 1, param7, param8);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC u32 FUN_02009358(struct UnkStruct1 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6)
{
    GF_ASSERT(param0);

    u32 r6 = FUN_020097D0(param0);
    GF_ASSERT(r6);

    FUN_020099B0(param0, r6, param1, param2, param3, param4, 0, 0, param5, param6, 0);
    param0->unk0C++;

    return r6;
}

THUMB_FUNC u32 FUN_020093A8(
    struct UnkStruct1 *param0, struct UnkStruct2 *param1, u32 *param2, u32 param3)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1);

    FUN_020093DC(param0, param1, 0, param1->unk04, param2, param3);

    return param1->unk04;
}

THUMB_FUNC void FUN_020093DC(struct UnkStruct1 *param0,
    struct UnkStruct2 *param1,
    s32 param2,
    s32 param3,
    s32 *param4,
    u32 param5)
{
    for (int r5 = param2; r5 < param2 + param3; r5++)
    {
        u32 r0 = FUN_02008E6C(param0, param1, r5, param5);

        if (param4 != NULL && param4[1] > param4[2])
        {
            ((u32 *)param4[0])[param4[2]] = r0;
            param4[2]++;
        }
    }
}

THUMB_FUNC struct UnkStruct5 *FUN_02009424(u32 param0, u32 param1)
{
    struct UnkStruct5 *r4 = AllocFromHeap(param1, sizeof(struct UnkStruct5));
    r4->unk00 = AllocFromHeap(param1, param0 * sizeof(u32));
    r4->unk04 = param0;
    r4->unk08 = 0;

    return r4;
}

THUMB_FUNC void FUN_02009448(struct UnkStruct5 *param0)
{
    FreeToHeap(param0->unk00);
    FreeToHeap(param0);
}

THUMB_FUNC u32 FUN_0200945C(struct UnkStruct1 *param0, s32 param1)
{
    GF_ASSERT(param0);
    return FUN_02020CB0(param0->unk00, param1);
}

THUMB_FUNC void FUN_02009474(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);

    FUN_02009920(param0);
    FUN_02020E1C(param0->unk00, 0);
}

THUMB_FUNC void FUN_02009490(struct UnkStruct1 *param0, struct UnkStruct1_sub *param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04);

    FUN_02009920(param1);
    FUN_02020D68(param0->unk00, param1->unk00);
    param1->unk00 = 0;
    param0->unk0C--;
}

THUMB_FUNC void FUN_020094C4(struct UnkStruct1 *param0)
{
    for (int i = 0; i < param0->unk08; i++)
    {
        if (param0->unk04[i].unk00 != 0)
        {
            FUN_02009490(param0, &param0->unk04[i]);
        }
    }
}

THUMB_FUNC struct UnkStruct1_sub *FUN_020094F0(struct UnkStruct1 *param0, u32 param1)
{
    GF_ASSERT(param0);

    for (int i = 0; i < param0->unk08; i++)
    {
        if (param0->unk04[i].unk00 != 0)
        {
            u32 r0 = FUN_02020E38(param0->unk04[i].unk00);
            if (r0 == param1)
            {
                return &param0->unk04[i];
            }
        }
    }

    return NULL;
}

THUMB_FUNC s32 FUN_02009530(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    return FUN_02020E38(param0->unk00);
}

THUMB_FUNC u32 FUN_02009544(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0->unk04 == 0);
    return *FUN_02009934(param0);
}

THUMB_FUNC u32 FUN_0200955C(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0->unk04 == 1);
    return *FUN_02009934(param0);
}

THUMB_FUNC u32 FUN_02009574(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0->unk04 == 2);
    return *FUN_02009934(param0);
}

THUMB_FUNC u32 FUN_0200958C(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0->unk04 == 3);
    return *FUN_02009934(param0);
}

THUMB_FUNC u32 FUN_020095A4(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0->unk04 == 4);
    return *FUN_02009934(param0);
}

THUMB_FUNC u32 FUN_020095BC(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0->unk04 == 5);
    return *FUN_02009934(param0);
}

THUMB_FUNC u32 FUN_020095D4(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);

    return param0->unk04;
}

THUMB_FUNC u32 FUN_020095E4(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);

    if (param0->unk04 == 0)
    {
        return FUN_02009934(param0)[1];
    }
    if (param0->unk04 == 1)
    {
        return FUN_02009934(param0)[1];
    }

    return 0;
}

THUMB_FUNC u32 FUN_02009610(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);

    if (param0->unk04 == 1)
    {
        return FUN_02009934(param0)[2];
    }

    return 0;
}

THUMB_FUNC void FUN_02009630(struct UnkStruct1_sub *param0, u32 param1)
{
    GF_ASSERT(param0);

    if (param0->unk04 == 0)
    {
        FUN_02009934(param0)[1] = param1;
    }
    if (param0->unk04 == 1)
    {
        FUN_02009934(param0)[1] = param1;
    }
}

THUMB_FUNC u32 FUN_0200965C(void)
{
    return 16;
}

THUMB_FUNC u32 *FUN_02009660(u32 *param0, s32 param1)
{
    return &param0[param1 * 4];
}

THUMB_FUNC void FUN_02009668(u32 *param0, struct UnkStruct2 *param1, u32 param2)
{
    GF_ASSERT(param1);

    param1->unk08 = param0[0];
    param1->unk0C = 1;

    param1->unk04 = FUN_020099E8((struct UnkStruct4 *)(param0 + 1));

    void *ptr;
    if (param1->unk04 > 0)
    {
        ptr = AllocFromHeap(param2, param1->unk04 * sizeof(struct UnkStruct4));
    }
    else
    {
        ptr = NULL;
    }

    param1->unk00 = ptr;
    // use volatile to force a reload here
    void *r0 = *((void *volatile *)param1);
    if (r0 != NULL)
    {
        memcpy(r0, param0 + 1, param1->unk04 * sizeof(struct UnkStruct4));
    }
}

THUMB_FUNC void FUN_020096B4(struct UnkStruct2 *param0)
{
    if (param0->unk00)
    {
        FreeToHeap(param0->unk00);
    }
    param0->unk00 = NULL;
    param0->unk04 = 0;
}

THUMB_FUNC s32 FUN_020096CC(struct UnkStruct2 *param0)
{
    GF_ASSERT(param0);

    return param0->unk04;
}

THUMB_FUNC u32 FUN_020096DC(struct UnkStruct2 *param0, s32 param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    if (param0->unk0C == 0)
    {
        return ((struct UnkStruct3 *)param0->unk00)[param1].unk00;
    }

    return ((struct UnkStruct4 *)param0->unk00)[param1].unk0C;
}

THUMB_FUNC u32 FUN_02009710(struct UnkStruct2 *param0, s32 param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    u32 r6;
    if (param0->unk0C == 1)
    {
        r6 = ((struct UnkStruct4 *)param0->unk00)[param1].unk04;
    }

    // oops, UB here
    return r6;
}

THUMB_FUNC u32 FUN_0200973C(struct UnkStruct2 *param0, s32 param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    u32 r6;
    if (param0->unk0C == 1)
    {
        r6 = ((struct UnkStruct4 *)param0->unk00)[param1].unk08;
    }

    // oops, UB here
    return r6;
}

THUMB_FUNC u32 FUN_02009768(struct UnkStruct2 *param0, s32 param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    if (param0->unk0C == 0)
    {
        return ((struct UnkStruct3 *)param0->unk00)[param1].unk44;
    }

    return ((struct UnkStruct4 *)param0->unk00)[param1].unk10;
}

THUMB_FUNC u32 FUN_0200979C(struct UnkStruct2 *param0, s32 param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    if (param0->unk0C == 0)
    {
        return ((struct UnkStruct3 *)param0->unk00)[param1].unk48;
    }

    return ((struct UnkStruct4 *)param0->unk00)[param1].unk14;
}

THUMB_FUNC struct UnkStruct1_sub *FUN_020097D0(struct UnkStruct1 *param0)
{
    for (int i = 0; i < param0->unk08; i++)
    {
        if (param0->unk04[i].unk00 == 0)
        {
            return &param0->unk04[i];
        }
    }

    return NULL;
}

struct CharacterData_02008DEC
{
    NNSG2dCharacterData *chData;
    u32 unk04;
};

struct PaletteData_02008DEC
{
    NNSG2dPaletteData *plttData;
    u32 unk04;
    u32 unk08;
};

struct CellDataBank_02008DEC
{
    NNSG2dCellDataBank *cellBank;
};

struct AnimBank_02008DEC
{
    NNSG2dAnimBankData *bankData;
};

THUMB_FUNC void FUN_020097FC(
    struct UnkStruct1_sub *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    void *r0 = FUN_02020E0C(param0->unk00);

    switch (param1)
    {
        case 0:
            param0->unk08 = FUN_0200986C(r0, param2, param4);
            break;
        case 1:
            param0->unk08 = FUN_0200988C(r0, param2, param3, param4);
            break;
        case 2:
            param0->unk08 = FUN_020098B0(r0, param4);
            break;
        case 3:
            param0->unk08 = FUN_020098CC(r0, param4);
            break;
        case 4:
            param0->unk08 = FUN_020098E8(r0, param4);
            break;
        case 5:
            param0->unk08 = FUN_02009904(r0, param4);
            break;
    }
}

THUMB_FUNC struct CharacterData_02008DEC *FUN_0200986C(void *param0, u32 param1, u32 param2)
{
    struct CharacterData_02008DEC *ptr =
        AllocFromHeap(param2, sizeof(struct CharacterData_02008DEC));

    NNS_G2dGetUnpackedCharacterData(param0, &ptr->chData);
    ptr->unk04 = param1;

    return ptr;
}

THUMB_FUNC struct PaletteData_02008DEC *FUN_0200988C(
    void *param0, u32 param1, u32 param2, u32 param3)
{
    struct PaletteData_02008DEC *ptr = AllocFromHeap(param3, sizeof(struct PaletteData_02008DEC));

    NNS_G2dGetUnpackedPaletteData(param0, &ptr->plttData);
    ptr->unk04 = param1;
    ptr->unk08 = param2;

    return ptr;
}

THUMB_FUNC struct CellDataBank_02008DEC *FUN_020098B0(void *param0, u32 param1)
{
    struct CellDataBank_02008DEC *ptr = AllocFromHeap(param1, sizeof(struct CellDataBank_02008DEC));

    NNS_G2dGetUnpackedCellBank(param0, &ptr->cellBank);

    return ptr;
}

THUMB_FUNC struct AnimBank_02008DEC *FUN_020098CC(void *param0, u32 param1)
{
    struct AnimBank_02008DEC *ptr = AllocFromHeap(param1, sizeof(struct AnimBank_02008DEC));

    NNS_G2dGetUnpackedAnimBank(param0, &ptr->bankData);

    return ptr;
}

THUMB_FUNC void *FUN_020098E8(void *param0, u32 param1)
{
    void *ptr = AllocFromHeap(param1, 4);

    NNS_G2dGetUnpackedMultiCellBank(param0, ptr);

    return ptr;
}

THUMB_FUNC void *FUN_02009904(void *param0, u32 param1)
{
    void *ptr = AllocFromHeap(param1, 4);

    NNS_G2dGetUnpackedMCAnimBank(param0, ptr);

    return ptr;
}

THUMB_FUNC void FUN_02009920(struct UnkStruct1_sub *param0)
{
    if (param0->unk08 != NULL)
    {
        FreeToHeap(param0->unk08);
    }

    param0->unk08 = NULL;
}

THUMB_FUNC u32 *FUN_02009934(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk08);

    return param0->unk08;
}

THUMB_FUNC void FUN_0200994C(struct UnkStruct1 *param0,
    struct UnkStruct1_sub *param1,
    void *param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7)
{
    param1->unk00 = FUN_02020D10(param0->unk00, param2, param3, param7);
    param1->unk04 = param6;
    FUN_020097FC(param1, param6, param4, param5, param7);
}

THUMB_FUNC void FUN_02009978(struct UnkStruct1 *param0,
    struct UnkStruct1_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    s32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    u32 param9,
    BOOL param10)
{
    void *r1 = GfGfxLoader_LoadFromNarc(param2, param3, param4, param9, param10);
    param1->unk00 = FUN_02020CD4(param0->unk00, r1, param5);
    param1->unk04 = param8;

    FUN_020097FC(param1, param8, param6, param7, param9);
}

THUMB_FUNC void FUN_020099B0(struct UnkStruct1 *param0,
    struct UnkStruct1_sub *param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    u32 param9,
    u32 param10)
{
    param1->unk00 =
        FUN_02020CD4(param0->unk00, FUN_02009A04(param2, param3, param4, param9, param10), param5);
    param1->unk04 = param8;

    FUN_020097FC(param1, param8, param6, param7, param9);
}

THUMB_FUNC s32 FUN_020099E8(struct UnkStruct4 *param0)
{
    s32 r3 = 0;
    while (param0[r3].unk00 != -2)
    {
        r3++;
    }

    return r3;
}

THUMB_FUNC void *FUN_02009A04(NARC *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    void *r4 = NARC_AllocAndReadWholeMember(param0, param1, param3);

    if (r4 != NULL && param2 != 0)
    {
        void *ptr;
        if (param4 == 0)
        {
            ptr = AllocFromHeap(param3, (*(u32 *)r4) >> 8);
        }
        else
        {
            ptr = AllocFromHeapAtEnd(param3, (*(u32 *)r4) >> 8);
        }

        if (ptr != NULL)
        {
            MI_UncompressLZ8(r4, ptr);
            FreeToHeap(r4);
        }

        r4 = ptr;
    }

    return r4;
}

THUMB_FUNC u32 FUN_02009A50(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = FUN_02009544(param0);
    st0[1] = FUN_020095E4(param0);
    st0[2] = FUN_02009530(param0);
    st0[3] = 0;

    return FUN_0201D1F8(st0);
}

THUMB_FUNC void FUN_02009A90(struct UnkStruct5 *param0)
{
    GF_ASSERT(param0);

    for (int i = 0; i < param0->unk04; i++)
    {
        GF_ASSERT(param0->unk00[i] == 0 || FUN_02009A50(param0->unk00[i]) != 0);
    }
}

THUMB_FUNC u32 FUN_02009AC4(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = FUN_02009544(param0);
    st0[1] = FUN_020095E4(param0);
    st0[2] = FUN_02009530(param0);
    st0[3] = 0;

    return FUN_0201D250(st0);
}

THUMB_FUNC u32 FUN_02009B04(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = FUN_02009544(param0);
    st0[1] = FUN_020095E4(param0);
    st0[2] = FUN_02009530(param0);
    st0[3] = 1;

    return FUN_0201D1F8(st0);
}

THUMB_FUNC void FUN_02009B44(struct UnkStruct5 *param0)
{
    GF_ASSERT(param0);

    for (int i = 0; i < param0->unk04; i++)
    {
        GF_ASSERT(param0->unk00[i] == 0 || FUN_02009B04(param0->unk00[i]) != 0);
    }
}

THUMB_FUNC u32 FUN_02009B78(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = FUN_02009544(param0);
    st0[1] = FUN_020095E4(param0);
    st0[2] = FUN_02009530(param0);
    st0[3] = 1;

    return FUN_0201D250(st0);
}

THUMB_FUNC void FUN_02009BB8(struct UnkStruct1_sub *param0, struct UnkStruct1_sub *param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1);

    FUN_0201D2DC(FUN_02009530(param0), FUN_02009544(param1));
}

THUMB_FUNC void FUN_02009BE8(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);

    FUN_0201D2DC(FUN_02009530(param0), FUN_02009544(param0));
}

THUMB_FUNC void FUN_02009C0C(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 0);

    FUN_0201D324(FUN_02009530(param0));
}

THUMB_FUNC void FUN_02009C30(struct UnkStruct5 *param0)
{
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++)
    {
        if (param0->unk00[i] != 0)
        {
            FUN_02009C0C(param0->unk00[i]);
        }
    }
}

THUMB_FUNC u32 FUN_02009C5C(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 0);

    return FUN_0201D3B0(FUN_02009530(param0));
}

THUMB_FUNC void FUN_02009C80(struct UnkStruct1_sub *param0, struct UnkStruct1_sub *param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 0);
    GF_ASSERT(param1);
    GF_ASSERT(FUN_020095D4(param1) == 2);

    u32 r4 = FUN_02009530(param0);
    if (FUN_0201D3D4(r4, ((u32 **)FUN_02009574(param1))[3][0]) == 0)
    {
        FUN_0201D458(FUN_0201D3B0(r4));
    }
}

THUMB_FUNC void FUN_02009CDC(u32 param0)
{
    GF_ASSERT(param0);

    FUN_0201D4F0(param0);
}

THUMB_FUNC u32 FUN_02009CF0(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 1);

    u32 st0[4];
    st0[0] = FUN_0200955C(param0);
    st0[1] = FUN_020095E4(param0);
    st0[3] = FUN_02009530(param0);
    st0[2] = FUN_02009610(param0);

    return FUN_0201E0E4(st0);
}

THUMB_FUNC void FUN_02009D34(struct UnkStruct5 *param0)
{
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++)
    {
        if (param0->unk00[i] != 0)
        {
            GF_ASSERT(FUN_02009CF0(param0->unk00[i]) != 0);
        }
    }
}

THUMB_FUNC u32 FUN_02009D68(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 1);

    u32 st0[4];
    st0[0] = FUN_0200955C(param0);
    st0[1] = FUN_020095E4(param0);
    st0[3] = FUN_02009530(param0);
    st0[2] = FUN_02009610(param0);

    return FUN_0201E128(st0);
}

THUMB_FUNC void FUN_02009DAC(struct UnkStruct5 *param0)
{
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++)
    {
        if (param0->unk00[i] != 0)
        {
            GF_ASSERT(FUN_02009D68(param0->unk00[i]) != 0);
        }
    }
}

THUMB_FUNC void FUN_02009DE0(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);

    FUN_0201E168(FUN_02009530(param0), FUN_0200955C(param0));
}

THUMB_FUNC void FUN_02009E04(struct UnkStruct1_sub *param0)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 1);

    FUN_0201E1C8(FUN_02009530(param0));
}

THUMB_FUNC void FUN_02009E28(struct UnkStruct5 *param0)
{
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++)
    {
        if (param0->unk00[i] != 0)
        {
            FUN_02009E04(param0->unk00[i]);
        }
    }
}

THUMB_FUNC u32 FUN_02009E54(struct UnkStruct1_sub *param0, u32 param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(FUN_020095D4(param0) == 1);

    u32 r0 = FUN_02009530(param0);
    if (param1 != 0)
    {
        return FUN_0201E258(r0, param1);
    }

    return FUN_0201E230(r0);
}

THUMB_FUNC s32 FUN_02009E88(struct UnkStruct1_sub *param0, u32 param1)
{
    s32 ret = NNS_G2dGetImagePaletteLocation(FUN_02009E54(param0, 0), param1);
    if (ret != -1)
    {
        return ret / 32;
    }

    return ret;
}
