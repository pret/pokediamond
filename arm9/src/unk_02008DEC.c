#include "unk_02008DEC.h"

#include "global.h"

#include "NNS_g2d.h"
#include "gf_gfx_loader.h"
#include "heap.h"

extern u32 sub_02020C44(u32, u32);
extern void sub_02020C90(u32);
extern u32 sub_02020CB0(u32 param0, s32 param1);
extern void sub_02020E1C(u32 param0, u32 param1);
extern void sub_02020D68(u32 param0, u32 param1);
extern s32 sub_02020E38(u32);
extern void *sub_02020E0C(u32);
extern BOOL NNS_G2dGetUnpackedMultiCellBank(void *, void *);
extern BOOL NNS_G2dGetUnpackedMCAnimBank(void *, void *);
extern u32 sub_02020D10(u32, void *, s32, u32);
extern u32 sub_02020CD4(u32, void *, s32);
extern u32 sub_0201D1F8(u32 *param0);
extern u32 sub_0201D250(u32 *param0);
extern void sub_0201D2DC(s32, u32);
extern void sub_0201D324(s32 param0);
extern u32 sub_0201D3B0(s32);
extern u32 sub_0201D3D4(s32, u32);
extern u32 sub_0201D458(u32);
extern void sub_0201D4F0(u32);
extern u32 sub_0201E0E4(u32 *param0);
extern u32 sub_0201E128(u32 *param0);
extern void sub_0201E168(s32, u32);
extern void sub_0201E1C8(s32);
extern u32 sub_0201E258(s32, u32);
extern u32 sub_0201E230(s32);
extern s32 NNS_G2dGetImagePaletteLocation(u32, u32);

struct UnkStruct_02008DEC_1 *sub_02008DEC(u32 param0, s32 param1, HeapID heapId) {
    struct UnkStruct_02008DEC_1 *ptr = AllocFromHeap(heapId, sizeof(struct UnkStruct_02008DEC_1));
    ptr->unk00 = sub_02020C44(param0, heapId);
    ptr->unk04 = AllocFromHeap(heapId, param0 * sizeof(struct UnkStruct_02008DEC_sub));
    memset(ptr->unk04, 0, param0 * sizeof(struct UnkStruct_02008DEC_sub));
    ptr->unk08 = (s32)param0;
    ptr->unk0C = 0;
    ptr->unk10 = param1;

    return ptr;
}

void sub_02008E2C(struct UnkStruct_02008DEC_1 *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk00);
    GF_ASSERT(param0->unk04);

    sub_020094C4(param0);

    sub_02020C90(param0->unk00);
    param0->unk00 = 0;

    FreeToHeap(param0->unk04);
    param0->unk04 = NULL;

    FreeToHeap(param0);
}

struct UnkStruct_02008DEC_sub *sub_02008E6C(
    struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_2 *param1, s32 param2, HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param1);
    GF_ASSERT(param1->unk04 > param2);
    GF_ASSERT(param0->unk10 == param1->unk08);

    struct UnkStruct_02008DEC_sub *st1c = sub_020097D0(param0);
    GF_ASSERT(st1c);

    if (param1->unk0C == 0) {
        struct UnkStruct_02008DEC_3 *r6 = &param1->unk00_3[param2];
        GF_ASSERT(sub_0200945C(param0, r6->unk00) == 1);

        sub_0200994C(
            param0, st1c, r6->unk04, r6->unk00, r6->unk44, r6->unk48, param1->unk08, heapId);
    } else {
        struct UnkStruct_02008DEC_4 *r6 = &param1->unk00_4[param2];
        GF_ASSERT(sub_0200945C(param0, r6->unk0C) == 1);

        sub_02009978(param0,
            st1c,
            r6->unk00,
            r6->unk04,
            r6->unk08,
            r6->unk0C,
            r6->unk10,
            r6->unk14,
            param1->unk08,
            heapId,
            FALSE);
    }

    param0->unk0C++;

    return st1c;
}

struct UnkStruct_02008DEC_sub *sub_02008F34(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_02009978(param0, r6, param1, param2, param3, param4, param5, 0, 0, heapId, FALSE);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_02008F90(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    HeapID heapId,
    BOOL param7) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_02009978(param0, r6, param1, param2, param3, param4, param5, 0, 0, heapId, param7);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_02008FEC(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_02009978(param0, r6, param1, param2, param3, param4, param5, param6, 1, heapId, FALSE);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_0200904C(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId,
    BOOL param8) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_02009978(param0, r6, param1, param2, param3, param4, param5, param6, 1, heapId, param8);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_020090AC(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    HeapID heapId) {
    GF_ASSERT(param0);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_02009978(param0, r6, param1, param2, param3, param4, 0, 0, param5, heapId, FALSE);
    param0->unk0C++;

    return r6;
}

void sub_020090FC(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);
    GF_ASSERT(param1);
    GF_ASSERT(param1->unk04 == 0);

    s32 r6 = sub_02009530(param1);
    u32 r7 = sub_020095E4(param1);
    sub_02009490(param0, param1);

    sub_02009978(param0, param1, param2, param3, param4, r6, r7, 0, 0, heapId, FALSE);
}

void sub_02009168(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);
    GF_ASSERT(param1);
    GF_ASSERT(param1->unk04 == 1);

    s32 r6 = sub_02009530(param1);
    u32 r7 = sub_020095E4(param1);
    u32 st24 = sub_02009610(param1);
    sub_02009490(param0, param1);

    sub_02009978(param0, param1, param2, param3, param4, r6, r7, st24, 1, heapId, 0);
}

struct UnkStruct_02008DEC_sub *sub_020091E0(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_020099B0(param0, r6, param1, param2, param3, param4, param5, 0, 0, heapId, 0);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_0200923C(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    HeapID heapId,
    u32 param7) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 0);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_020099B0(param0, r6, param1, param2, param3, param4, param5, 0, 0, heapId, param7);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_02009298(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_020099B0(param0, r6, param1, param2, param3, param4, param5, param6, 1, heapId, 0);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_020092F8(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId,
    u32 param8) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk10 == 1);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_020099B0(param0, r6, param1, param2, param3, param4, param5, param6, 1, heapId, param8);
    param0->unk0C++;

    return r6;
}

struct UnkStruct_02008DEC_sub *sub_02009358(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    HeapID heapId) {
    GF_ASSERT(param0);

    struct UnkStruct_02008DEC_sub *r6 = sub_020097D0(param0);
    GF_ASSERT(r6);

    sub_020099B0(param0, r6, param1, param2, param3, param4, 0, 0, param5, heapId, 0);
    param0->unk0C++;

    return r6;
}

s32 sub_020093A8(
    struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_2 *param1, struct UnkStruct_02008DEC_5 *param2, HeapID heapId) {
    GF_ASSERT(param0);
    GF_ASSERT(param1);

    sub_020093DC(param0, param1, 0, param1->unk04, param2, heapId);

    return param1->unk04;
}

void sub_020093DC(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_2 *param1,
    s32 param2,
    s32 param3,
    struct UnkStruct_02008DEC_5 *param4,
    HeapID heapId) {
    for (int r5 = param2; r5 < param2 + param3; r5++) {
        struct UnkStruct_02008DEC_sub *r0 = sub_02008E6C(param0, param1, r5, heapId);

        if (param4 != NULL && param4->unk04 > param4->unk08) {
            param4->unk00[param4->unk08] = r0;
            param4->unk08++;
        }
    }
}

struct UnkStruct_02008DEC_5 *sub_02009424(s32 param0, HeapID heapId) {
    struct UnkStruct_02008DEC_5 *r4 = AllocFromHeap(heapId, sizeof(struct UnkStruct_02008DEC_5));
    r4->unk00 = AllocFromHeap(heapId, param0 * sizeof(struct UnkStruct_02008DEC_sub *));
    r4->unk04 = param0;
    r4->unk08 = 0;

    return r4;
}

void sub_02009448(struct UnkStruct_02008DEC_5 *param0) {
    FreeToHeap(param0->unk00);
    FreeToHeap(param0);
}

u32 sub_0200945C(struct UnkStruct_02008DEC_1 *param0, s32 param1) {
    GF_ASSERT(param0);
    return sub_02020CB0(param0->unk00, param1);
}

void sub_02009474(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);

    sub_02009920(param0);
    sub_02020E1C(param0->unk00, 0);
}

void sub_02009490(struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_sub *param1) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04);

    sub_02009920(param1);
    sub_02020D68(param0->unk00, param1->unk00);
    param1->unk00 = 0;
    param0->unk0C--;
}

void sub_020094C4(struct UnkStruct_02008DEC_1 *param0) {
    for (int i = 0; i < param0->unk08; i++) {
        if (param0->unk04[i].unk00 != 0) {
            sub_02009490(param0, &param0->unk04[i]);
        }
    }
}

struct UnkStruct_02008DEC_sub *sub_020094F0(struct UnkStruct_02008DEC_1 *param0, s32 param1) {
    GF_ASSERT(param0);

    for (int i = 0; i < param0->unk08; i++) {
        if (param0->unk04[i].unk00 != 0) {
            s32 r0 = sub_02020E38(param0->unk04[i].unk00);
            if (r0 == param1) {
                return &param0->unk04[i];
            }
        }
    }

    return NULL;
}

s32 sub_02009530(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    return sub_02020E38(param0->unk00);
}

u32 sub_02009544(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0->unk04 == 0);
    return *sub_02009934(param0);
}

u32 sub_0200955C(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0->unk04 == 1);
    return *sub_02009934(param0);
}

u32 sub_02009574(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0->unk04 == 2);
    return *sub_02009934(param0);
}

u32 sub_0200958C(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0->unk04 == 3);
    return *sub_02009934(param0);
}

u32 sub_020095A4(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0->unk04 == 4);
    return *sub_02009934(param0);
}

u32 sub_020095BC(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0->unk04 == 5);
    return *sub_02009934(param0);
}

u32 sub_020095D4(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);

    return param0->unk04;
}

u32 sub_020095E4(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);

    if (param0->unk04 == 0) {
        return sub_02009934(param0)[1];
    }
    if (param0->unk04 == 1) {
        return sub_02009934(param0)[1];
    }

    return 0;
}

u32 sub_02009610(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);

    if (param0->unk04 == 1) {
        return sub_02009934(param0)[2];
    }

    return 0;
}

void sub_02009630(struct UnkStruct_02008DEC_sub *param0, u32 param1) {
    GF_ASSERT(param0);

    if (param0->unk04 == 0) {
        sub_02009934(param0)[1] = param1;
    }
    if (param0->unk04 == 1) {
        sub_02009934(param0)[1] = param1;
    }
}

u32 sub_0200965C(void) {
    return 16;
}

struct UnkStruct_02008DEC_2 *sub_02009660(struct UnkStruct_02008DEC_2 *param0, s32 param1) {
    return &param0[param1];
}

void sub_02009668(u32 *param0, struct UnkStruct_02008DEC_2 *param1, HeapID heapId) {
    GF_ASSERT(param1);

    param1->unk08 = param0[0];
    param1->unk0C = 1;

    param1->unk04 = sub_020099E8((struct UnkStruct_02008DEC_4 *)(param0 + 1));

    if (param1->unk04 > 0) {
        param1->unk00_4 = AllocFromHeap(heapId, param1->unk04 * sizeof(struct UnkStruct_02008DEC_4));
    } else {
        param1->unk00_4 = NULL;
    }

    if (param1->unk00_4 != NULL) {
        memcpy(param1->unk00_4, param0 + 1, param1->unk04 * sizeof(struct UnkStruct_02008DEC_4));
    }
}

void sub_020096B4(struct UnkStruct_02008DEC_2 *param0) {
    if (param0->unk00_4) {
        FreeToHeap(param0->unk00_4);
    }
    param0->unk00_4 = NULL;
    param0->unk04 = 0;
}

s32 sub_020096CC(struct UnkStruct_02008DEC_2 *param0) {
    GF_ASSERT(param0);

    return param0->unk04;
}

s32 sub_020096DC(struct UnkStruct_02008DEC_2 *param0, s32 param1) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    if (param0->unk0C == 0) {
        return param0->unk00_3[param1].unk00;
    }

    return param0->unk00_4[param1].unk0C;
}

s32 sub_02009710(struct UnkStruct_02008DEC_2 *param0, s32 param1) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    s32 r6;
    if (param0->unk0C == 1) {
        r6 = param0->unk00_4[param1].unk04;
    }

    // oops, UB here
    return r6;
}

BOOL sub_0200973C(struct UnkStruct_02008DEC_2 *param0, s32 param1) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    BOOL r6;
    if (param0->unk0C == 1) {
        r6 = param0->unk00_4[param1].unk08;
    }

    // oops, UB here
    return r6;
}

u32 sub_02009768(struct UnkStruct_02008DEC_2 *param0, s32 param1) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    if (param0->unk0C == 0) {
        return param0->unk00_3[param1].unk44;
    }

    return param0->unk00_4[param1].unk10;
}

u32 sub_0200979C(struct UnkStruct_02008DEC_2 *param0, s32 param1) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk04 > param1);

    if (param0->unk0C == 0) {
        return param0->unk00_3[param1].unk48;
    }

    return param0->unk00_4[param1].unk14;
}

struct UnkStruct_02008DEC_sub *sub_020097D0(struct UnkStruct_02008DEC_1 *param0) {
    for (int i = 0; i < param0->unk08; i++) {
        if (param0->unk04[i].unk00 == 0) {
            return &param0->unk04[i];
        }
    }

    return NULL;
}

void sub_020097FC(
    struct UnkStruct_02008DEC_sub *param0, u32 param1, u32 param2, u32 param3, HeapID heapId) {
    void *r0 = sub_02020E0C(param0->unk00);

    switch (param1) {
    case 0:
        param0->unk08 = sub_0200986C(r0, param2, heapId);
        break;
    case 1:
        param0->unk08 = sub_0200988C(r0, param2, param3, heapId);
        break;
    case 2:
        param0->unk08 = sub_020098B0(r0, heapId);
        break;
    case 3:
        param0->unk08 = sub_020098CC(r0, heapId);
        break;
    case 4:
        param0->unk08 = sub_020098E8(r0, heapId);
        break;
    case 5:
        param0->unk08 = sub_02009904(r0, heapId);
        break;
    }
}

struct CharacterData_02008DEC *sub_0200986C(void *param0, u32 param1, HeapID heapId) {
    struct CharacterData_02008DEC *ptr = AllocFromHeap(heapId, sizeof(struct CharacterData_02008DEC));

    NNS_G2dGetUnpackedCharacterData(param0, &ptr->chData);
    ptr->unk04 = param1;

    return ptr;
}

struct PaletteData_02008DEC *sub_0200988C(
    void *param0, u32 param1, u32 param2, HeapID heapId) {
    struct PaletteData_02008DEC *ptr = AllocFromHeap(heapId, sizeof(struct PaletteData_02008DEC));

    NNS_G2dGetUnpackedPaletteData(param0, &ptr->plttData);
    ptr->unk04 = param1;
    ptr->unk08 = param2;

    return ptr;
}

struct CellDataBank_02008DEC *sub_020098B0(void *param0, HeapID heapId) {
    struct CellDataBank_02008DEC *ptr = AllocFromHeap(heapId, sizeof(struct CellDataBank_02008DEC));

    NNS_G2dGetUnpackedCellBank(param0, &ptr->cellBank);

    return ptr;
}

struct AnimBank_02008DEC *sub_020098CC(void *param0, HeapID heapId) {
    struct AnimBank_02008DEC *ptr = AllocFromHeap(heapId, sizeof(struct AnimBank_02008DEC));

    NNS_G2dGetUnpackedAnimBank(param0, &ptr->bankData);

    return ptr;
}

void *sub_020098E8(void *param0, HeapID heapId) {
    void *ptr = AllocFromHeap(heapId, 4);

    NNS_G2dGetUnpackedMultiCellBank(param0, ptr);

    return ptr;
}

void *sub_02009904(void *param0, HeapID heapId) {
    void *ptr = AllocFromHeap(heapId, 4);

    NNS_G2dGetUnpackedMCAnimBank(param0, ptr);

    return ptr;
}

void sub_02009920(struct UnkStruct_02008DEC_sub *param0) {
    if (param0->unk08 != NULL) {
        FreeToHeap(param0->unk08);
    }

    param0->unk08 = NULL;
}

u32 *sub_02009934(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(param0->unk08);

    return param0->unk08;
}

void sub_0200994C(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    void *param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId) {
    param1->unk00 = sub_02020D10(param0->unk00, param2, param3, heapId);
    param1->unk04 = param6;
    sub_020097FC(param1, param6, param4, param5, heapId);
}

void sub_02009978(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    s32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    HeapID heapId,
    BOOL param10) {
    void *r1 = GfGfxLoader_LoadFromNarc(param2, param3, param4, heapId, param10);
    param1->unk00 = sub_02020CD4(param0->unk00, r1, param5);
    param1->unk04 = param8;

    sub_020097FC(param1, param8, param6, param7, heapId);
}

void sub_020099B0(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NARC *param2,
    u32 param3,
    u32 param4,
    s32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    HeapID heapId,
    u32 param10) {
    param1->unk00 = sub_02020CD4(param0->unk00, sub_02009A04(param2, param3, param4, heapId, param10), param5);
    param1->unk04 = param8;

    sub_020097FC(param1, param8, param6, param7, heapId);
}

s32 sub_020099E8(struct UnkStruct_02008DEC_4 *param0) {
    s32 r3 = 0;
    while (param0[r3].unk00 != -2) {
        r3++;
    }

    return r3;
}

void *sub_02009A04(NARC *param0, u32 param1, u32 param2, HeapID heapId, u32 param4) {
    void *r4 = NARC_AllocAndReadWholeMember(param0, param1, heapId);

    if (r4 != NULL && param2 != 0) {
        void *ptr;
        if (param4 == 0) {
            ptr = AllocFromHeap(heapId, (*(u32 *)r4) >> 8);
        } else {
            ptr = AllocFromHeapAtEnd(heapId, (*(u32 *)r4) >> 8);
        }

        if (ptr != NULL) {
            MI_UncompressLZ8(r4, ptr);
            FreeToHeap(r4);
        }

        r4 = ptr;
    }

    return r4;
}

u32 sub_02009A50(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = sub_02009544(param0);
    st0[1] = sub_020095E4(param0);
    st0[2] = (u32)sub_02009530(param0);
    st0[3] = 0;

    return sub_0201D1F8(st0);
}

void sub_02009A90(struct UnkStruct_02008DEC_5 *param0) {
    GF_ASSERT(param0);

    for (int i = 0; i < param0->unk04; i++) {
        GF_ASSERT(param0->unk00[i] == NULL || sub_02009A50(param0->unk00[i]) != 0);
    }
}

u32 sub_02009AC4(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = sub_02009544(param0);
    st0[1] = sub_020095E4(param0);
    st0[2] = (u32)sub_02009530(param0);
    st0[3] = 0;

    return sub_0201D250(st0);
}

u32 sub_02009B04(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = sub_02009544(param0);
    st0[1] = sub_020095E4(param0);
    st0[2] = (u32)sub_02009530(param0);
    st0[3] = 1;

    return sub_0201D1F8(st0);
}

void sub_02009B44(struct UnkStruct_02008DEC_5 *param0) {
    GF_ASSERT(param0);

    for (int i = 0; i < param0->unk04; i++) {
        GF_ASSERT(param0->unk00[i] == NULL || sub_02009B04(param0->unk00[i]) != 0);
    }
}

u32 sub_02009B78(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 0);

    u32 st0[4];
    st0[0] = sub_02009544(param0);
    st0[1] = sub_020095E4(param0);
    st0[2] = (u32)sub_02009530(param0);
    st0[3] = 1;

    return sub_0201D250(st0);
}

void sub_02009BB8(struct UnkStruct_02008DEC_sub *param0, struct UnkStruct_02008DEC_sub *param1) {
    GF_ASSERT(param0);
    GF_ASSERT(param1);

    sub_0201D2DC(sub_02009530(param0), sub_02009544(param1));
}

void sub_02009BE8(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);

    sub_0201D2DC(sub_02009530(param0), sub_02009544(param0));
}

void sub_02009C0C(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 0);

    sub_0201D324(sub_02009530(param0));
}

void sub_02009C30(struct UnkStruct_02008DEC_5 *param0) {
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++) {
        if (param0->unk00[i] != NULL) {
            sub_02009C0C(param0->unk00[i]);
        }
    }
}

u32 sub_02009C5C(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 0);

    return sub_0201D3B0(sub_02009530(param0));
}

u32 sub_02009C80(struct UnkStruct_02008DEC_sub *param0, struct UnkStruct_02008DEC_sub *param1) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 0);
    GF_ASSERT(param1);
    GF_ASSERT(sub_020095D4(param1) == 2);

    s32 r4 = sub_02009530(param0);

    u32 r0 = sub_0201D3D4(r4, ((u32 **)sub_02009574(param1))[3][0]);
    if (r0 == 0) {
        return sub_0201D458(sub_0201D3B0(r4));
    }

    return r0;
}

void sub_02009CDC(u32 param0) {
    GF_ASSERT(param0);

    sub_0201D4F0(param0);
}

u32 sub_02009CF0(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 1);

    u32 st0[4];
    st0[0] = sub_0200955C(param0);
    st0[1] = sub_020095E4(param0);
    st0[3] = (u32)sub_02009530(param0);
    st0[2] = sub_02009610(param0);

    return sub_0201E0E4(st0);
}

void sub_02009D34(struct UnkStruct_02008DEC_5 *param0) {
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++) {
        if (param0->unk00[i] != NULL) {
            GF_ASSERT(sub_02009CF0(param0->unk00[i]) != 0);
        }
    }
}

u32 sub_02009D68(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 1);

    u32 st0[4];
    st0[0] = sub_0200955C(param0);
    st0[1] = sub_020095E4(param0);
    st0[3] = (u32)sub_02009530(param0);
    st0[2] = sub_02009610(param0);

    return sub_0201E128(st0);
}

void sub_02009DAC(struct UnkStruct_02008DEC_5 *param0) {
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++) {
        if (param0->unk00[i] != NULL) {
            GF_ASSERT(sub_02009D68(param0->unk00[i]) != 0);
        }
    }
}

void sub_02009DE0(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);

    sub_0201E168(sub_02009530(param0), sub_0200955C(param0));
}

void sub_02009E04(struct UnkStruct_02008DEC_sub *param0) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 1);

    sub_0201E1C8(sub_02009530(param0));
}

void sub_02009E28(struct UnkStruct_02008DEC_5 *param0) {
    GF_ASSERT(param0);
    for (int i = 0; i < param0->unk04; i++) {
        if (param0->unk00[i] != NULL) {
            sub_02009E04(param0->unk00[i]);
        }
    }
}

u32 sub_02009E54(struct UnkStruct_02008DEC_sub *param0, u32 param1) {
    GF_ASSERT(param0);
    GF_ASSERT(sub_020095D4(param0) == 1);

    s32 r0 = sub_02009530(param0);
    if (param1 != 0) {
        return sub_0201E258(r0, param1);
    }

    return sub_0201E230(r0);
}

s32 sub_02009E88(struct UnkStruct_02008DEC_sub *param0, u32 param1) {
    s32 ret = NNS_G2dGetImagePaletteLocation(sub_02009E54(param0, 0), param1);
    if (ret != -1) {
        return ret / 32;
    }

    return ret;
}
