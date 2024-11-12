#include "unk_02006D98.h"

#include "global.h"

#include "poketool/pokegra/otherpoke.naix"

#include "MI_memory.h"
#include "NNS_g2d.h"
#include "filesystem.h"
#include "heap.h"
#include "ov63_021DB450.h"
#include "palette.h"
#include "registers.h"

const struct UnkStruct_02006D98_3 UNK_020ECCE2[] = {
    { 0x1B, 0x0F },
    { 0x1C, 0x0F },
    { 0x1D, 0x0F },
    { 0x1E, 0x0F },
    { 0x1A, 0x10 },
    { 0x1B, 0x10 },
    { 0x1C, 0x10 },
    { 0x1D, 0x10 },
    { 0x1E, 0x10 },
    { 0x1F, 0x10 },
    { 0x19, 0x11 },
    { 0x1A, 0x11 },
    { 0x1B, 0x11 },
    { 0x1C, 0x11 },
    { 0x1D, 0x11 },
    { 0x1E, 0x11 },
    { 0x1F, 0x11 },
    { 0x20, 0x11 },
    { 0x19, 0x12 },
    { 0x1A, 0x12 },
    { 0x1B, 0x12 },
    { 0x1C, 0x12 },
    { 0x1D, 0x12 },
    { 0x1E, 0x12 },
    { 0x1F, 0x12 },
    { 0x20, 0x12 },
    { 0x19, 0x13 },
    { 0x1A, 0x13 },
    { 0x1B, 0x13 },
    { 0x1C, 0x13 },
    { 0x1D, 0x13 },
    { 0x1E, 0x13 },
    { 0x1F, 0x13 },
    { 0x20, 0x13 },
    { 0x19, 0x14 },
    { 0x1A, 0x14 },
    { 0x1B, 0x14 },
    { 0x1C, 0x14 },
    { 0x1D, 0x14 },
    { 0x1E, 0x14 },
    { 0x1F, 0x14 },
    { 0x20, 0x14 },
    { 0x1A, 0x15 },
    { 0x1B, 0x15 },
    { 0x1C, 0x15 },
    { 0x1D, 0x15 },
    { 0x1E, 0x15 },
    { 0x1F, 0x15 },
    { 0x1B, 0x16 },
    { 0x1C, 0x16 },
    { 0x1D, 0x16 },
    { 0x1E, 0x16 },
    { 0xFF, 0xFF },
};

const struct UnkStruct_02006D98_3 UNK_020ECC78[] = {
    { 0x33, 0x11 },
    { 0x34, 0x11 },
    { 0x35, 0x11 },
    { 0x36, 0x11 },
    { 0x32, 0x12 },
    { 0x33, 0x12 },
    { 0x34, 0x12 },
    { 0x35, 0x12 },
    { 0x36, 0x12 },
    { 0x37, 0x12 },
    { 0x31, 0x13 },
    { 0x32, 0x13 },
    { 0x33, 0x13 },
    { 0x34, 0x13 },
    { 0x35, 0x13 },
    { 0x36, 0x13 },
    { 0x37, 0x13 },
    { 0x38, 0x13 },
    { 0x31, 0x14 },
    { 0x32, 0x14 },
    { 0x33, 0x14 },
    { 0x34, 0x14 },
    { 0x35, 0x14 },
    { 0x36, 0x14 },
    { 0x37, 0x14 },
    { 0x38, 0x14 },
    { 0x31, 0x15 },
    { 0x32, 0x15 },
    { 0x33, 0x15 },
    { 0x34, 0x15 },
    { 0x35, 0x15 },
    { 0x36, 0x15 },
    { 0x37, 0x15 },
    { 0x38, 0x15 },
    { 0x31, 0x16 },
    { 0x32, 0x16 },
    { 0x33, 0x16 },
    { 0x34, 0x16 },
    { 0x35, 0x16 },
    { 0x36, 0x16 },
    { 0x37, 0x16 },
    { 0x38, 0x16 },
    { 0x32, 0x17 },
    { 0x33, 0x17 },
    { 0x34, 0x17 },
    { 0x35, 0x17 },
    { 0x36, 0x17 },
    { 0x37, 0x17 },
    { 0x33, 0x18 },
    { 0x34, 0x18 },
    { 0x35, 0x18 },
    { 0x36, 0x18 },
    { 0xFF, 0xFF },
};

const struct UnkStruct_02006D98_3 UNK_020ECC10[] = {
    { 0x1E, 0x21 },
    { 0x1F, 0x21 },
    { 0x20, 0x21 },
    { 0x1D, 0x22 },
    { 0x1E, 0x22 },
    { 0x1F, 0x22 },
    { 0x20, 0x22 },
    { 0x21, 0x22 },
    { 0x1C, 0x23 },
    { 0x1D, 0x23 },
    { 0x1E, 0x23 },
    { 0x1F, 0x23 },
    { 0x20, 0x23 },
    { 0x21, 0x23 },
    { 0x22, 0x23 },
    { 0x1C, 0x24 },
    { 0x1D, 0x24 },
    { 0x1E, 0x24 },
    { 0x1F, 0x24 },
    { 0x20, 0x24 },
    { 0x21, 0x24 },
    { 0x22, 0x24 },
    { 0x1C, 0x25 },
    { 0x1D, 0x25 },
    { 0x1E, 0x25 },
    { 0x1F, 0x25 },
    { 0x20, 0x25 },
    { 0x21, 0x25 },
    { 0x22, 0x25 },
    { 0x1C, 0x26 },
    { 0x1D, 0x26 },
    { 0x1E, 0x26 },
    { 0x1F, 0x26 },
    { 0x20, 0x26 },
    { 0x21, 0x26 },
    { 0x22, 0x26 },
    { 0x1C, 0x27 },
    { 0x1D, 0x27 },
    { 0x1E, 0x27 },
    { 0x1F, 0x27 },
    { 0x20, 0x27 },
    { 0x21, 0x27 },
    { 0x22, 0x27 },
    { 0x1D, 0x28 },
    { 0x1E, 0x28 },
    { 0x1F, 0x28 },
    { 0x20, 0x28 },
    { 0x21, 0x28 },
    { 0x1E, 0x29 },
    { 0x1F, 0x29 },
    { 0x20, 0x29 },
    { 0xFF, 0xFF },
};

const struct UnkStruct_02006D98_3 UNK_020ECDCC[] = {
    { 0x2B, 0x21 },
    { 0x2C, 0x21 },
    { 0x2D, 0x21 },
    { 0x29, 0x22 },
    { 0x2A, 0x22 },
    { 0x2B, 0x22 },
    { 0x2C, 0x22 },
    { 0x2D, 0x22 },
    { 0x2E, 0x22 },
    { 0x2F, 0x22 },
    { 0x28, 0x23 },
    { 0x29, 0x23 },
    { 0x2A, 0x23 },
    { 0x2B, 0x23 },
    { 0x2C, 0x23 },
    { 0x2D, 0x23 },
    { 0x2E, 0x23 },
    { 0x2F, 0x23 },
    { 0x30, 0x23 },
    { 0x28, 0x24 },
    { 0x29, 0x24 },
    { 0x2A, 0x24 },
    { 0x2B, 0x24 },
    { 0x2C, 0x24 },
    { 0x2D, 0x24 },
    { 0x2E, 0x24 },
    { 0x2F, 0x24 },
    { 0x30, 0x24 },
    { 0x28, 0x25 },
    { 0x29, 0x25 },
    { 0x2A, 0x25 },
    { 0x2B, 0x25 },
    { 0x2C, 0x25 },
    { 0x2D, 0x25 },
    { 0x2E, 0x25 },
    { 0x2F, 0x25 },
    { 0x30, 0x25 },
    { 0x28, 0x26 },
    { 0x29, 0x26 },
    { 0x2A, 0x26 },
    { 0x2B, 0x26 },
    { 0x2C, 0x26 },
    { 0x2D, 0x26 },
    { 0x2E, 0x26 },
    { 0x2F, 0x26 },
    { 0x30, 0x26 },
    { 0x28, 0x27 },
    { 0x29, 0x27 },
    { 0x2A, 0x27 },
    { 0x2B, 0x27 },
    { 0x2C, 0x27 },
    { 0x2D, 0x27 },
    { 0x2E, 0x27 },
    { 0x2F, 0x27 },
    { 0x30, 0x27 },
    { 0x28, 0x28 },
    { 0x29, 0x28 },
    { 0x2A, 0x28 },
    { 0x2B, 0x28 },
    { 0x2C, 0x28 },
    { 0x2D, 0x28 },
    { 0x2E, 0x28 },
    { 0x2F, 0x28 },
    { 0x30, 0x28 },
    { 0x29, 0x29 },
    { 0x2A, 0x29 },
    { 0x2B, 0x29 },
    { 0x2C, 0x29 },
    { 0x2D, 0x29 },
    { 0x2E, 0x29 },
    { 0x2F, 0x29 },
    { 0x2B, 0x2A },
    { 0x2C, 0x2A },
    { 0x2D, 0x2A },
    { 0xFF, 0xFF },
};

const int UNK_020ECBD0[4][4] = {
    { 160, 160, 224, 176 },
    { 160, 160, 224, 176 },
    { 160, 176, 224, 192 },
    { 160, 192, 224, 208 }
};

const int UNK_020ECD4C[4][2][4] = {
    { { 0, 0, 0x50, 0x50 },   { 0x50, 0, 0xA0, 0x50 }    },
    {

     { 0, 0x50, 0x50, 0xA0 }, { 0x50, 0x50, 0xA0, 0xA0 }

    },
    {

     { 0, 0xA0, 0x50, 0xF0 }, { 0x50, 0xA0, 0xA0, 0xF0 }

    },
    {

     { 0xA0, 0, 0xF0, 0x50 }, { 0xA0, 0x50, 0xF0, 0xA0 }

    }
};

const struct UnkStruct_02006D98_3 *UNK_02105AE8[] = {
    UNK_020ECCE2,
    UNK_020ECC78,
    UNK_020ECC10,
    UNK_020ECDCC,
};

extern void NNS_G2dSetupSoftwareSpriteCamera(void);
extern void NNS_G3dGeFlushBuffer();
extern void NNS_G2dDrawSpriteFast(s16 param0,
    s16 param1,
    int param2,
    int param3,
    int param4,
    int param5,
    int param6,
    int param7,
    int param8);

struct UnkStruct_02006D98 *sub_02006D98(HeapID heapId) {
    struct UnkStruct_02006D98 *ptr = AllocFromHeap(heapId, sizeof(struct UnkStruct_02006D98));
    ptr->heapId = heapId;
    ptr->unk2E0 = 0;
    ptr->unk29C = 0;
    ptr->unk2A0 = 0x8000;
    ptr->unk2A4 = 0;
    ptr->unk2A8 = 0x80;

    ptr->unk2AC = AllocFromHeap(heapId, 0x8000);

    ptr->unk2B0 = AllocFromHeap(heapId, 0xc0);
    MIi_CpuClearFast(0, ptr->unk2B0, 4);

    ptr->unk2B4 = AllocFromHeap(heapId, 0xc0);
    MIi_CpuClearFast(0, ptr->unk2B4, 4);

    for (int i = 0; i < 4; i++) {
        MIi_CpuClearFast(0, &ptr->unk000[i], sizeof(struct UnkStruct_02006D98_2));
    }

    NNS_G2dSetupSoftwareSpriteCamera();
    ptr->unk2E3 = 0;

    u8 *st8;
    void *st4 = AllocAndReadWholeNarcMemberByIdPair(
        NARC_POKETOOL_POKEGRA_OTHERPOKE, NARC_otherpoke_narc_0211_NCGR, ptr->heapId);
    NNSG2dCharacterData *stc;
    NNS_G2dGetUnpackedCharacterData(st4, &stc);

    ptr->unk2B8.pixelFmt = stc->pixelFmt;
    ptr->unk2B8.mapingType = stc->mapingType;
    ptr->unk2B8.characterFmt = stc->characterFmt;
    st8 = stc->pRawData;

    sub_02008A74(st8);
    MI_CpuFill8(ptr->unk2AC, *st8, 0x8000);

    for (int i = 0; i < 0x50; i++) {
        for (int j = 0; j < 0x28; j++) {
            ((u8 *)ptr->unk2AC)[0x5050 + i * 0x80 + j] = st8[i * 0x50 + j];
        }
    }

    FreeToHeap(st4);
    ptr->unk2E1 = 1;
    ptr->unk2E2 = 1;

    return ptr;
}

void sub_02006ED4(struct UnkStruct_02006D98 *param0) {
    s32 arg3;
    s32 arg4;

    sub_020082A8(param0);
    sub_020086F4(param0);

    NNS_G3dGeFlushBuffer();

    G3_PushMtx();

    G3_TexImageParam(param0->unk260.attr.fmt,
        GX_TEXGEN_TEXCOORD,
        param0->unk260.attr.sizeS,
        param0->unk260.attr.sizeT,
        GX_TEXREPEAT_NONE,
        GX_TEXFLIP_NONE,
        param0->unk260.attr.plttUse,
        param0->unk29C);

    for (int st18 = 0; st18 < 4; st18++) {
        if (param0->unk000[st18].unk00_0 == 0 || param0->unk000[st18].unk54_0 != 0 || param0->unk000[st18].unk54_B != 0) {
            continue;
        }

        if (param0->unk000[st18].unk68 != NULL) {
            param0->unk000[st18].unk68(&param0->unk000[st18], &param0->unk000[st18].unk24);
        }

        NNS_G3dGeFlushBuffer();

        if (param0->unk2E3 != 1) {
            G3_Identity();
        }

        sub_02007F48(&param0->unk000[st18]);

        G3_TexPlttBase(param0->unk2A4 + st18 * 0x20, param0->unk260.attr.fmt);
        G3_Translate((fx32)((param0->unk000[st18].unk24 + param0->unk000[st18].unk40) << 0xc),
            (fx32)((param0->unk000[st18].unk26 + param0->unk000[st18].unk42) << 0xc),
            (fx32)(param0->unk000[st18].unk28 << 0xc));

        s32 idx = ((s32)param0->unk000[st18].unk38) >> 4;
        G3_RotX(FX_SinCosTable_[idx * 2], FX_SinCosTable_[idx * 2 + 1]);

        s32 idy = ((s32)param0->unk000[st18].unk3A) >> 4;
        G3_RotY(FX_SinCosTable_[idy * 2], FX_SinCosTable_[idy * 2 + 1]);

        s32 idz = ((s32)param0->unk000[st18].unk3C) >> 4;
        G3_RotZ(FX_SinCosTable_[idz * 2], FX_SinCosTable_[idz * 2 + 1]);

        G3_Translate(-(fx32)((param0->unk000[st18].unk24 + param0->unk000[st18].unk40) << 0xc),
            -(fx32)((param0->unk000[st18].unk26 + param0->unk000[st18].unk42) << 0xc),
            -(fx32)(param0->unk000[st18].unk28 << 0xc));

        G3_MaterialColorDiffAmb(
            (GXRgb)(param0->unk000[st18].unk50_0 | (param0->unk000[st18].unk50_5 << 5) | (param0->unk000[st18].unk50_a << 10)),
            (GXRgb)(param0->unk000[st18].unk50_f | (param0->unk000[st18].unk50_14 << 5) | (param0->unk000[st18].unk50_19 << 10)),
            TRUE);

        G3_MaterialColorSpecEmi(0x4210, 0, FALSE);

        G3_PolygonAttr(GX_LIGHTMASK_NONE,
            GX_POLYGONMODE_MODULATE,
            GX_CULL_NONE,
            (int)param0->unk000[st18].unk00_1,
            (int)param0->unk000[st18].unk54_2,
            0);

        if (param0->unk000[st18].unk54_1 != 0) {
            int r6 = param0->unk000[st18].unk44 + UNK_020ECD4C[st18][param0->unk000[st18].unk5B][0];
            int r12 = param0->unk000[st18].unk46;
            int r1 = param0->unk000[st18].unk45 + UNK_020ECD4C[st18][param0->unk000[st18].unk5B][1];
            int r7 = param0->unk000[st18].unk47;
            int r0 = r12 + r6;

            NNS_G2dDrawSpriteFast((s16)(param0->unk000[st18].unk24 - 40 + param0->unk000[st18].unk44 + param0->unk000[st18].unk2C),
                (s16)(param0->unk000[st18].unk26 - 40 + param0->unk000[st18].unk45 + param0->unk000[st18].unk2E - param0->unk000[st18].unk6C.unk2),
                (int)(param0->unk000[st18].unk28 + param0->unk000[st18].unk30),
                r12,
                r7,
                r6,
                r1,
                r0,
                r7 + r1);
        } else {
            arg3 = (param0->unk000[st18].unk34 * 80) >> 8;
            arg4 = (param0->unk000[st18].unk36 * 80) >> 8;

            NNS_G2dDrawSpriteFast(
                (s16)(param0->unk000[st18].unk24 - (arg3 / 2) + param0->unk000[st18].unk2C),
                (s16)(param0->unk000[st18].unk26 - (arg4 / 2) + param0->unk000[st18].unk2E - param0->unk000[st18].unk6C.unk2),
                (int)(param0->unk000[st18].unk28 + param0->unk000[st18].unk30),
                arg3,
                arg4,
                UNK_020ECD4C[st18][param0->unk000[st18].unk5B][0],
                UNK_020ECD4C[st18][param0->unk000[st18].unk5B][1],
                UNK_020ECD4C[st18][param0->unk000[st18].unk5B][2],
                UNK_020ECD4C[st18][param0->unk000[st18].unk5B][3]);
        }

        if (param0->unk000[st18].unk6C.unk0_0 == 0 || param0->unk000[st18].unk6C.unk0_5 == 0 || param0->unk000[st18].unk54_1 != 0 || (param0->unk2E4 & 1) != 0) {
            continue;
        }

        if (param0->unk2E3 != 1) {
            G3_Identity();
        }

        G3_TexPlttBase(param0->unk2A4 + ((param0->unk000[st18].unk6C.unk0_0 + 3) << 5),
            param0->unk260.attr.fmt);

        if (param0->unk000[st18].unk6C.unk0_4 != 0) {
            arg3 = (param0->unk000[st18].unk34 * 64) >> 8;
            arg4 = (param0->unk000[st18].unk36 * 16) >> 8;
        } else {
            arg3 = 64;
            arg4 = 16;
        }

        if (param0->unk000[st18].unk6C.unk0_2 != 0) {
            param0->unk000[st18].unk6C.unk4 = (s16)(param0->unk000[st18].unk24 + param0->unk000[st18].unk2C + param0->unk000[st18].unk6C.unk8);
        }

        if (param0->unk000[st18].unk6C.unk0_3 != 0) {
            param0->unk000[st18].unk6C.unk6 = (s16)(param0->unk000[st18].unk26 + param0->unk000[st18].unk2E + param0->unk000[st18].unk6C.unka);
        }

        NNS_G2dDrawSpriteFast((s16)(param0->unk000[st18].unk6C.unk4 - (arg3 / 2)),
            (s16)(param0->unk000[st18].unk6C.unk6 - (arg4 / 2)),
            0xFFFFFC18,
            arg3,
            arg4,
            UNK_020ECBD0[param0->unk000[st18].unk6C.unk0_5][0],
            UNK_020ECBD0[param0->unk000[st18].unk6C.unk0_5][1],
            UNK_020ECBD0[param0->unk000[st18].unk6C.unk0_5][2],
            UNK_020ECBD0[param0->unk000[st18].unk6C.unk0_5][3]);
    }

    G3_PopMtx(1);
}

void sub_020072E8(struct UnkStruct_02006D98 *param0) {
    FreeToHeap(param0->unk2AC);
    FreeToHeap(param0->unk2B0);
    FreeToHeap(param0->unk2B4);
    FreeToHeap(param0);
}

void sub_02007314(struct UnkStruct_02006D98_2 *param0) {
    param0->unk59 = 0;
    for (s32 i = 0; i < 10; i++) {
        param0->unk5C[i] = 0;
    }
    if (param0->unk84[param0->unk59].unk0 == -1) {
        param0->unk5B = 0;
        return;
    }

    param0->unk58 = 1;
    param0->unk5B = (u8)param0->unk84[param0->unk59].unk0;
    param0->unk5A = param0->unk84[param0->unk59].unk1;
}

void sub_0200737C(
    struct UnkStruct_02006D98_2 *param0, struct UnkStruct_02006D98_sub *param1) {
    MI_CpuCopy8(param1, param0->unk84, sizeof(struct UnkStruct_02006D98_sub) * 10);
}

BOOL sub_02007390(struct UnkStruct_02006D98_2 *param0) {
    if (param0->unk58 != 0) {
        return TRUE;
    }
    return FALSE;
}

struct UnkStruct_02006D98_2 *sub_020073A0(struct UnkStruct_02006D98 *param0,
    struct UnkStruct_02006D98_4 *param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    const void *param6,
    void (*param7)(struct UnkStruct_02006D98_2 *, void *)) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (param0->unk000[i].unk00_0 == 0) {
            break;
        }
    }
    GF_ASSERT(i != 4);

    return sub_020073E8(param0, param1, param2, param3, param4, param5, i, param6, param7);
}

struct UnkStruct_02006D98_2 *sub_020073E8(struct UnkStruct_02006D98 *param0,
    struct UnkStruct_02006D98_4 *param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    s32 param6,
    const void *param7,
    void (*param8)(struct UnkStruct_02006D98_2 *, void *)) {
    GF_ASSERT(param0->unk000[param6].unk00_0 == 0);

    MIi_CpuClearFast(0, &param0->unk000[param6], sizeof(struct UnkStruct_02006D98_2));
    param0->unk000[param6].unk00_0 = 1;
    param0->unk000[param6].unk00_7 = 1;
    param0->unk000[param6].unk00_8 = 1;
    param0->unk000[param6].unk00_1 = param5;

    param0->unk000[param6].unk04 = *param1;
    param0->unk000[param6].unk14 = *param1;
    param0->unk000[param6].unk24 = (s16)param2;
    param0->unk000[param6].unk26 = (s16)param3;
    param0->unk000[param6].unk28 = param4;
    param0->unk000[param6].unk34 = 0x100;
    param0->unk000[param6].unk36 = 0x100;
    param0->unk000[param6].unk54_2 = 0x1f;
    param0->unk000[param6].unk50_0 = 0x1f;
    param0->unk000[param6].unk50_5 = 0x1f;
    param0->unk000[param6].unk50_a = 0x1f;
    param0->unk000[param6].unk50_f = 0x10;
    param0->unk000[param6].unk50_14 = 0x10;
    param0->unk000[param6].unk50_19 = 0x10;
    param0->unk000[param6].unk68 = param8;
    param0->unk000[param6].unk6C.unk4 = (s16)param2;
    param0->unk000[param6].unk6C.unk6 = (s16)param3;
    param0->unk000[param6].unk6C.unk0_2 = 1;
    param0->unk000[param6].unk6C.unk0_3 = 1;
    param0->unk000[param6].unk6C.unk0_4 = 1;

    if (param7 != NULL) {
        MI_CpuCopy8(param7, param0->unk000[param6].unk84, 0x14);
    }

    return &param0->unk000[param6];
}

void sub_02007534(struct UnkStruct_02006D98_2 *param0) {
    param0->unk00_0 = 0;
}

void sub_02007540(struct UnkStruct_02006D98 *param0) {
    for (s32 i = 0; i < 4; i++) {
        sub_02007534(&param0->unk000[i]);
    }
}

void sub_02007558(struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2) {
    switch (param1) {
    case 0:
        param0->unk24 = (s16)param2;
        break;
    case 1:
        param0->unk26 = (s16)param2;
        break;
    case 2:
        param0->unk28 = param2;
        break;
    case 3:
        param0->unk2C = (s16)param2;
        break;
    case 4:
        param0->unk2E = (s16)param2;
        break;
    case 5:
        param0->unk30 = param2;
        break;
    case 6:
        param0->unk54_0 = param2;
        break;
    case 7:
        param0->unk38 = (u16)param2;
        break;
    case 8:
        param0->unk3A = (u16)param2;
        break;
    case 9:
        param0->unk3C = (u16)param2;
        break;
    case 10:
        param0->unk40 = (s16)param2;
        break;
    case 11:
        param0->unk42 = (s16)param2;
        break;
    case 12:
        param0->unk34 = (s16)param2;
        break;
    case 13:
        param0->unk36 = (s16)param2;
        break;
    case 14:
        param0->unk54_1 = param2;
        break;
    case 15:
        param0->unk44 = (u8)param2;
        break;
    case 16:
        param0->unk45 = (u8)param2;
        break;
    case 17:
        param0->unk46 = (u8)param2;
        break;
    case 18:
        param0->unk47 = (u8)param2;
        break;
    case 19:
        param0->unk6C.unk4 = (s16)param2;
        break;
    case 20:
        param0->unk6C.unk6 = (s16)param2;
        break;
    case 21:
        param0->unk6C.unk8 = (s16)param2;
        break;
    case 22:
        param0->unk6C.unka = (s16)param2;
        break;
    case 23:
        param0->unk54_2 = param2;
        break;
    case 24:
        param0->unk50_0 = param2;
        break;
    case 25:
        param0->unk50_5 = param2;
        break;
    case 26:
        param0->unk50_a = param2;
        break;
    case 27:
        param0->unk50_f = param2;
        break;
    case 28:
        param0->unk50_14 = param2;
        break;
    case 29:
        param0->unk50_19 = param2;
        break;
    case 30:
        param0->unk54_C = param2;
        param0->unk00_8 = 1;
        break;
    case 31:
        param0->unk4C = param2;
        param0->unk00_8 = 1;
        break;
    case 32:
        param0->unk48 = (u8)param2;
        param0->unk00_8 = 1;
        break;
    case 33:
        param0->unk49 = (u8)param2;
        param0->unk00_8 = 1;
        break;
    case 34:
        param0->unk4A = (u8)param2;
        break;
    case 35:
        param0->unk54_9 = param2;
        param0->unk00_7 = 1;
        break;
    case 36:
        param0->unk54_A = param2;
        param0->unk00_7 = 1;
        break;
    case 37:
        param0->unk54_B = param2;
        break;
    case 38:
        param0->unk5B = (u8)param2;
        break;
    case 40:
        param0->unk54_D = param2;
        param0->unk00_7 = 1;
        break;
    case 41:
        param0->unk6C.unk2 = (s8)param2;
        break;
    case 42:
        param0->unk6C.unk0_0 = (u16)param2;
        param0->unk00_8 = 1;
        break;
    case 43:
        param0->unk6C.unk0_2 = (u16)param2;
        break;
    case 44:
        param0->unk6C.unk0_3 = (u16)param2;
        break;
    case 45:
        param0->unk6C.unk0_4 = (u16)param2;
        break;
    case 46:
        param0->unk6C.unk0_5 = (u16)param2;
        break;
    }
}

u32 sub_0200782C(struct UnkStruct_02006D98_2 *param0, u32 param1) {
    switch (param1) {
    case 0:
        return param0->unk24;

    case 1:
        return param0->unk26;

    case 2:
        return param0->unk28;

    case 3:
        return param0->unk2C;

    case 4:
        return param0->unk2E;

    case 5:
        return param0->unk30;

    case 6:
        return param0->unk54_0;

    case 7:
        return param0->unk38;

    case 8:
        return param0->unk3A;

    case 9:
        return param0->unk3C;

    case 10:
        return param0->unk40;

    case 11:
        return param0->unk42;

    case 12:
        return param0->unk34;

    case 13:
        return param0->unk36;

    case 14:
        return param0->unk54_1;

    case 15:
        return param0->unk44;

    case 16:
        return param0->unk45;

    case 17:
        return param0->unk46;

    case 18:
        return param0->unk47;

    case 19:
        return param0->unk6C.unk4;

    case 20:
        return param0->unk6C.unk6;

    case 21:
        return param0->unk6C.unk8;

    case 22:
        return param0->unk6C.unka;

    case 23:
        return param0->unk54_2;

    case 24:
        return param0->unk50_0;

    case 25:
        return param0->unk50_5;

    case 26:
        return param0->unk50_a;

    case 27:
        return param0->unk50_f;

    case 28:
        return param0->unk50_14;

    case 29:
        return param0->unk50_19;

    case 30:
        return param0->unk54_C;

    case 31:
        return param0->unk4C;

    case 32:
        return param0->unk48;

    case 33:
        return param0->unk49;

    case 34:
        return param0->unk4A;

    case 35:
        return param0->unk54_9;

    case 36:
        return param0->unk54_A;

    case 37:
        return param0->unk54_B;

    case 38:
        return param0->unk5B;

    case 40:
        return param0->unk54_D;

    case 41:
        return param0->unk6C.unk2;

    case 42:
        return param0->unk6C.unk0_0;

    case 43:
        return param0->unk6C.unk0_2;

    case 44:
        return param0->unk6C.unk0_3;

    case 45:
        return param0->unk6C.unk0_4;

    case 46:
        return param0->unk6C.unk0_5;
    }

    GF_AssertFail();

    return 0;
}

void sub_020079E0(struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2) {
    switch (param1) {
    case 0:
        param0->unk24 += param2;
        break;
    case 1:
        param0->unk26 += param2;
        break;
    case 2:
        param0->unk28 += param2;
        break;
    case 3:
        param0->unk2C += param2;
        break;
    case 4:
        param0->unk2E += param2;
        break;
    case 5:
        param0->unk30 += param2;
        break;
    case 6:
        param0->unk54_0 += param2;
        break;
    case 7:
        param0->unk38 += param2;
        break;
    case 8:
        param0->unk3A += param2;
        break;
    case 9:
        param0->unk3C += param2;
        break;
    case 10:
        param0->unk40 += param2;
        break;
    case 11:
        param0->unk42 += param2;
        break;
    case 12:
        param0->unk34 += param2;
        break;
    case 13:
        param0->unk36 += param2;
        break;
    case 14:
        param0->unk54_1 += param2;
        break;
    case 15:
        param0->unk44 += param2;
        break;
    case 16:
        param0->unk45 += param2;
        break;
    case 17:
        param0->unk46 += param2;
        break;
    case 18:
        param0->unk47 += param2;
        break;
    case 19:
        param0->unk6C.unk4 += param2;
        break;
    case 20:
        param0->unk6C.unk6 += param2;
        break;
    case 21:
        param0->unk6C.unk8 += param2;
        break;
    case 22:
        param0->unk6C.unka += param2;
        break;
    case 23:
        param0->unk54_2 += param2;
        break;
    case 24:
        param0->unk50_0 += param2;
        break;
    case 25:
        param0->unk50_5 += param2;
        break;
    case 26:
        param0->unk50_a += param2;
        break;
    case 27:
        param0->unk50_f += param2;
        break;
    case 28:
        param0->unk50_14 += param2;
        break;
    case 29:
        param0->unk50_19 += param2;
        break;
    case 30:
        param0->unk54_C += param2;
        param0->unk00_8 = 1;
        break;
    case 31:
        param0->unk4C += param2;
        param0->unk00_8 = 1;
        break;
    case 32:
        param0->unk48 += param2;
        param0->unk00_8 = 1;
        break;
    case 33:
        param0->unk49 += param2;
        param0->unk00_8 = 1;
        break;
    case 34:
        param0->unk4A += param2;
        break;
    case 35:
        param0->unk54_9 += param2;
        param0->unk00_7 = 1;
        break;
    case 36:
        param0->unk54_A += param2;
        param0->unk00_7 = 1;
        break;
    case 37:
        param0->unk54_B += param2;
        break;
    case 38:
        param0->unk5B += param2;
        break;
    case 40:
        param0->unk54_D += param2;
        param0->unk00_7 = 1;
        break;
    case 41:
        param0->unk6C.unk2 += param2;
        break;
    case 42:
        param0->unk6C.unk0_0 += param2;
        param0->unk00_8 = 1;
        break;
    case 43:
        param0->unk6C.unk0_2 += param2;
        break;
    case 44:
        param0->unk6C.unk0_3 += param2;
        break;
    case 45:
        param0->unk6C.unk0_4 += param2;
        break;
    case 46:
        param0->unk6C.unk0_5 += param2;
        break;
    }
}

void sub_02007E40(
    struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2, u32 param3, u32 param4) {
    param0->unk54_1 = 1;
    param0->unk44 = (u8)param1;
    param0->unk45 = (u8)param2;
    param0->unk46 = (u8)param3;
    param0->unk47 = (u8)param4;
}

void sub_02007E68(
    struct UnkStruct_02006D98_2 *param0, u32 param1, u32 param2, u32 param3, u32 param4) {
    param0->unk54_C = 1;
    param0->unk48 = (u8)param1;
    param0->unk49 = (u8)param2;
    param0->unk4A = 0;
    param0->unk4B = (u8)param3;
    param0->unk4C = param4;
}

void sub_02007E98(
    struct UnkStruct_02006D98 *param0, u32 param1, u32 param2, u32 param3, u32 param4) {
    for (s32 i = 0; i < 4; i++) {
        if (param0->unk000[i].unk00_0 == 0) {
            continue;
        }

        param0->unk000[i].unk54_C = 1;
        param0->unk000[i].unk48 = (u8)param1;
        param0->unk000[i].unk49 = (u8)param2;
        param0->unk000[i].unk4A = 0;
        param0->unk000[i].unk4B = (u8)param3;
        param0->unk000[i].unk4C = param4;
    }
}

void sub_02007EEC(struct UnkStruct_02006D98_2 *param0) {
    param0->unk54_C = 0;
    param0->unk48 = 0;
    param0->unk49 = 0;
    param0->unk4A = 0;
    param0->unk4B = 0;
    param0->unk4C = 0;
    param0->unk00_8 = 1;
}

BOOL sub_02007F20(struct UnkStruct_02006D98_2 *param0) {
    return param0->unk54_C == 1;
}

void sub_02007F34(struct UnkStruct_02006D98_2 *param0, s32 param1) {
    param0->unk2E = (s16)((40 - param1) - (((40 - param1) * param0->unk36) >> 8));
}

static inline void inlineLoop(u8 *unk58,
    u8 *unk59,
    u8 *unk5A,
    u8 *unk5B,
    u8 *unk5C,
    const struct UnkStruct_02006D98_sub *unk84) {
    if (*unk58 == 0) {
        return;
    }

    if (*unk5A == 0) {
        (*unk59)++;

        while (unk84[*unk59].unk0 < -1) {
            unk5C[*unk59]++;

            if (unk84[*unk59].unk1 == unk5C[*unk59] || unk84[*unk59].unk1 == 0) {
                unk5C[*unk59] = 0;
                unk59++;
            } else {
                *unk59 = (u8)(-2 - unk84[*unk59].unk0);
            }
        }

        if (unk84[*unk59].unk0 == -1 || *unk59 >= 10) {
            *unk5B = 0;
            *unk58 = 0;

            return;
        }

        *unk5B = (u8)unk84[*unk59].unk0;
        *unk5A = unk84[*unk59].unk1;
    } else {
        (*unk5A)--;
    }
}

void sub_02007F48(struct UnkStruct_02006D98_2 *param0) {
    inlineLoop(&param0->unk58,
        &param0->unk59,
        &param0->unk5A,
        &param0->unk5B,
        param0->unk5C,
        param0->unk84);
}

void sub_02008010(
    struct UnkStruct_02006D98_5 *param0, struct UnkStruct_02006D98_sub *param1) {
    param0->unk00 = 1;
    param0->unk02 = 0;
    param0->unk01 = (u8)param1->unk0;
    param0->unk03 = param1->unk1;
    param0->unk10 = param1;

    for (s32 i = 0; i < 10; i++) {
        param0->unk04[i] = 0;
    }
}

s32 sub_02008030(struct UnkStruct_02006D98_5 *param0) {
    if (param0->unk00 != 0) {
        inlineLoop(&param0->unk00,
            &param0->unk02,
            &param0->unk03,
            &param0->unk01,
            param0->unk04,
            param0->unk10);
        return param0->unk01;
    }

    return -1;
}

void sub_020080D0(struct UnkStruct_02006D98_2 *param0) {
    param0->unk00_7 = 1;
    param0->unk00_8 = 1;
}

void sub_020080E0(struct UnkStruct_02006D98_2 *param0) {
    param0->unk14 = param0->unk04;
    param0->unk78 = param0->unk6C;
}

void sub_0200813C(struct UnkStruct_02006D98_2 *param0) {
    param0->unk04 = param0->unk14;
    param0->unk6C = param0->unk78;
    param0->unk00_7 = 1;
    param0->unk00_8 = 1;
}

void sub_020081A8(struct UnkStruct_02006D98 *param0, u32 param1, u32 param2) {
    param0->unk29C = param1;
    param0->unk2A0 = param2;
}

void sub_020081B4(struct UnkStruct_02006D98 *param0, u32 param1, u32 param2) {
    param0->unk2A4 = param1;
    param0->unk2A8 = param2;
}

u32 sub_020081C0(u32 param0) {
    return param0 + 4;
}

void sub_020081C4(struct UnkStruct_02006D98 *param0) {
    if (param0->unk2E1 != 0) {
        param0->unk2E1 = 0;
        NNS_G2dInitImageProxy(&param0->unk260);

        param0->unk2B8.H = 0x20;
        param0->unk2B8.W = 0x20;
        param0->unk2B8.szByte = param0->unk2A0;
        param0->unk2B8.pRawData = param0->unk2AC;

        NNS_G2dLoadImage2DMapping(
            &param0->unk2B8, param0->unk29C, NNS_G2D_VRAM_TYPE_3DMAIN, &param0->unk260);
    }

    if (param0->unk2E2 != 0) {
        param0->unk2E2 = 0;
        NNS_G2dInitImagePaletteProxy(&param0->unk284);

        param0->unk2D0.szByte = param0->unk2A8;
        param0->unk2D0.pRawData = param0->unk2B0;

        NNS_G2dLoadPalette(
            &param0->unk2D0, param0->unk2A4, NNS_G2D_VRAM_TYPE_3DMAIN, &param0->unk284);
    }
}

void sub_0200825C(struct UnkStruct_02006D98 *param0, u8 param1) {
    param0->unk2E3 = param1;
}

BOOL sub_02008268(struct UnkStruct_02006D98_2 *param0) {
    GF_ASSERT(param0);
    return param0->unk00_0 != 0;
}

void sub_02008284(struct UnkStruct_02006D98 *param0, u32 param1) {
    param0->unk2E4 |= param1;
}

void sub_02008290(struct UnkStruct_02006D98 *param0, u32 param1) {
    param0->unk2E4 &= (param1 ^ ~0);
}

void sub_020082A8(struct UnkStruct_02006D98 *param0) {
    NNSG2dCharacterData *st58;
    int st54;
    int r4;
    int st14;
    u8 *st50;
    void *st4c;
    u8 st48 = 0;

    for (st54 = 0; st54 < 4; st54++) {
        if (param0->unk000[st54].unk00_0 != 0 && param0->unk000[st54].unk00_7 != 0) {
            param0->unk000[st54].unk00_7 = 0;
            st48 = 1;
            st4c = AllocAndReadWholeNarcMemberByIdPair((NarcId)param0->unk000[st54].unk04.field_00,
                param0->unk000[st54].unk04.field_02,
                param0->heapId);
            NNS_G2dGetUnpackedCharacterData(st4c, &st58);
            param0->unk2B8.pixelFmt = st58->pixelFmt;
            param0->unk2B8.mapingType = st58->mapingType;
            param0->unk2B8.characterFmt = st58->characterFmt;

            st50 = st58->pRawData;
            sub_02008A74(st50);
            sub_020088EC(&param0->unk000[st54], st50);

            if (st54 == 3) {
                for (st14 = 0; st14 < 0x50; st14++) {
                    for (r4 = 0; r4 < 0x50; r4++) {
                        if (r4 < 0x28) {
                            if (param0->unk000[st54].unk54_9 != 0 && param0->unk000[st54].unk54_A != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x50] = sub_020088D8(st50[(0x4f - st14) * 0x50 + (0x27 - r4)]);
                            } else if (param0->unk000[st54].unk54_9 != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x50] = sub_020088D8(st50[st14 * 0x50 + (0x27 - r4)]);
                            } else if (param0->unk000[st54].unk54_A != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x50] = st50[(0x4f - st14) * 0x50 + r4];
                            } else if (param0->unk000[st54].unk54_D != 0) {
                                if (st14 % (param0->unk000[st54].unk54_D * 2) != 0) {
                                    param0->unk2AC[st14 * 0x80 + r4 + 0x50] = param0->unk2AC[(st14 - 1) * 0x80 + r4 + 0x50];
                                } else if (r4 % param0->unk000[st54].unk54_D != 0) {
                                    param0->unk2AC[st14 * 0x80 + r4 + 0x50] = param0->unk2AC[st14 * 0x80 + r4 + 0x4f];
                                } else {
                                    param0->unk2AC[st14 * 0x80 + r4 + 0x50] = (u8)((st50[st14 * 0x50 + r4] & 0xf) | ((st50[st14 * 0x50 + r4] & 0xf) << 4));
                                }
                            } else {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x50] = st50[st14 * 0x50 + r4];
                            }
                        } else {
                            //_02008442
                            if (param0->unk000[st54].unk54_9 != 0 && param0->unk000[st54].unk54_A != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x2828] = sub_020088D8(st50[(0x4f - st14) * 0x50 + (0x4f - (r4 - 0x28))]);
                            } else if (param0->unk000[st54].unk54_9 != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x2828] = sub_020088D8(st50[st14 * 0x50 + (0x4f - (r4 - 0x28))]);
                            } else if (param0->unk000[st54].unk54_A != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x2828] = st50[(0x4f - st14) * 0x50 + r4];
                            } else if (param0->unk000[st54].unk54_D != 0) {
                                if (st14 % (param0->unk000[st54].unk54_D * 2) != 0) {
                                    param0->unk2AC[st14 * 0x80 + r4 + 0x2828] = param0->unk2AC[(st14 - 1) * 0x80 + r4 + 0x2828];
                                } else if (r4 % param0->unk000[st54].unk54_D != 0) {
                                    param0->unk2AC[st14 * 0x80 + r4 + 0x2828] = param0->unk2AC[st14 * 0x80 + (r4 - 1) + 0x2828];
                                } else {
                                    param0->unk2AC[st14 * 0x80 + r4 + 0x2828] = (u8)((st50[st14 * 0x50 + r4] & 0xf) | ((st50[st14 * 0x50 + r4] & 0xf) << 4));
                                }
                            } else {
                                param0->unk2AC[st14 * 0x80 + r4 + 0x2828] = st50[st14 * 0x50 + r4];
                            }
                        }
                    }
                }
            } else {
                //_02008554
                for (st14 = 0; st14 < 0x50; st14++) {
                    for (r4 = 0; r4 < 0x50; r4++) {
                        if (param0->unk000[st54].unk54_9 != 0 && param0->unk000[st54].unk54_A != 0) {
                            if (r4 < 0x28) {
                                param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = sub_020088D8(st50[(0x4f - st14) * 0x50 + (0x27 - r4)]);
                            } else {
                                param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = sub_020088D8(st50[(0x4f - st14) * 0x50 + (0x4f - (r4 - 0x28))]);
                            }
                        } else if (param0->unk000[st54].unk54_9 != 0) {
                            if (r4 < 0x28) {
                                param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = sub_020088D8(st50[st14 * 0x50 + (0x27 - r4)]);
                            } else {
                                param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = sub_020088D8(st50[st14 * 0x50 + (0x4f - (r4 - 0x28))]);
                            }
                        } else if (param0->unk000[st54].unk54_A != 0) {
                            param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = st50[(0x4f - st14) * 0x50 + r4];
                        } else if (param0->unk000[st54].unk54_D != 0) {
                            if (st14 % (param0->unk000[st54].unk54_D * 2) != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = param0->unk2AC[(st14 - 1) * 0x80 + r4 + st54 * 0x2800];
                            } else if (r4 % (param0->unk000[st54].unk54_D) != 0) {
                                param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = param0->unk2AC[st14 * 0x80 + (r4 - 1) + st54 * 0x2800];
                            } else {
                                param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = (u8)((st50[st14 * 0x50 + r4] & 0xf) | ((st50[st14 * 0x50 + r4] & 0xf) << 4));
                            }
                        } else {
                            param0->unk2AC[st14 * 0x80 + r4 + st54 * 0x2800] = st50[st14 * 0x50 + r4];
                        }
                    }
                }
            }

            FreeToHeap(st4c);
        }
        //_020086C2
    }

    param0->unk2E1 = st48;
}

void sub_020086F4(struct UnkStruct_02006D98 *param0) {
    NNSG2dPaletteData *st18;
    int st14, r7;
    u16 *r1;
    void *st10;
    u8 stc = 0;

    for (st14 = 0; st14 < 4; st14++) {
        if (param0->unk000[st14].unk00_0 != 0 && param0->unk000[st14].unk00_8 != 0) {
            param0->unk000[st14].unk00_8 = 0;
            stc = 1;
            st10 = AllocAndReadWholeNarcMemberByIdPair((NarcId)param0->unk000[st14].unk04.field_00,
                param0->unk000[st14].unk04.field_04,
                param0->heapId);
            NNS_G2dGetUnpackedPaletteData(st10, &st18);
            param0->unk2D0.fmt = st18->fmt;
            r1 = st18->pRawData;
            for (r7 = 0; r7 < 0x10; r7++) {
                param0->unk2B0[st14 * 0x10 + r7] = r1[r7];
                param0->unk2B4[st14 * 0x10 + r7] = r1[r7];
            }
            FreeToHeap(st10);

            if (param0->unk000[st14].unk6C.unk0_0 != 0) {
                st10 = AllocAndReadWholeNarcMemberByIdPair(
                    NARC_POKETOOL_POKEGRA_OTHERPOKE, NARC_otherpoke_narc_0212_NCLR, param0->heapId);
                NNS_G2dGetUnpackedPaletteData(st10, &st18);
                r1 = st18->pRawData;
                for (r7 = 0; r7 < 0x10; r7++) {
                    param0->unk2B0[(param0->unk000[st14].unk6C.unk0_0 + 3) * 0x10 + r7] = r1[r7];
                    param0->unk2B4[(param0->unk000[st14].unk6C.unk0_0 + 3) * 0x10 + r7] = r1[r7];
                }
                FreeToHeap(st10);
            }
        }
        //_020087E0

        if (param0->unk000[st14].unk00_0 != 0 && param0->unk000[st14].unk54_C != 0) {
            if (param0->unk000[st14].unk4A == 0) {
                stc = 1;
                param0->unk000[st14].unk4A = param0->unk000[st14].unk4B;
                BlendPalette(param0->unk2B4 + st14 * 0x10,
                    param0->unk2B0 + st14 * 0x10,
                    0x10,
                    param0->unk000[st14].unk48,
                    (u16)param0->unk000[st14].unk4C);

                if (param0->unk000[st14].unk6C.unk0_0 != 0) {
                    BlendPalette(param0->unk2B4 + (param0->unk000[st14].unk6C.unk0_0 + 3) * 0x10,
                        param0->unk2B0 + (param0->unk000[st14].unk6C.unk0_0 + 3) * 0x10,
                        0x10,
                        param0->unk000[st14].unk48,
                        (u16)param0->unk000[st14].unk4C);
                }

                if (param0->unk000[st14].unk48 == param0->unk000[st14].unk49) {
                    param0->unk000[st14].unk54_C = 0;
                } else if (param0->unk000[st14].unk48 > param0->unk000[st14].unk49) {
                    param0->unk000[st14].unk48--;
                } else {
                    param0->unk000[st14].unk48++;
                }
            } else {
                param0->unk000[st14].unk4A--;
            }
        }
    }

    param0->unk2E2 = stc;
}

u8 sub_020088D8(u8 param0) {
    return (u8)(((u8)((param0 & 0xf0) >> 4)) | ((u8)(param0 << 4)));
}

void sub_020088EC(struct UnkStruct_02006D98_2 *param0, u8 *param1) {
    if (param0->unk04.field_06 != 0) {
        sub_02008904(param1, param0->unk04.field_0C, 1);
    }
}

void sub_02008904(u8 *param0, u32 param1, u32 param2) {
    const struct UnkStruct_02006D98_3 *st10;
    s32 i;
    u32 r2;
    u8 r0;
    u8 r4;
    u8 r1;
    u32 st0 = param1;

    for (i = 0; i < 4; i++) {
        st10 = UNK_02105AE8[i];
        r1 = 0;
        while (st10[r1].unk0 != 0xff) {
            r0 = (u8)(st10[r1].unk0 + ((param1 & 0xf) - 8));
            r4 = (u8)(st10[r1].unk1 + (((param1 & 0xf0) >> 4) - 8));
            r2 = (u32)(r0 / 2 + r4 * 0x50);
            if ((r0 & 1) != 0) {
                if ((param0[r2] & 0xf0) >= 0x10 && (param0[r2] & 0xf0) <= 0x30) {
                    param0[r2] += 0x50;
                }
            } else {
                if ((param0[r2] & 0xf) >= 1 && (param0[r2] & 0xf) <= 3) {
                    param0[r2] += 5;
                }
            }

            r1++;
        }
        param1 >>= 8;
    }

    param1 = st0;

    if (param2 != 0) {
        for (i = 0; i < 4; i++) {
            st10 = UNK_02105AE8[i];
            r1 = 0;
            while (st10[r1].unk0 != 0xff) {
                r0 = (u8)(st10[r1].unk0 - 14 + ((param1 & 0xf) - 8) + 0x50);
                r4 = (u8)(st10[r1].unk1 + (((param1 & 0xf0) >> 4) - 8));
                r2 = (u32)(r0 / 2 + r4 * 0x50);
                if ((r0 & 1) != 0) {
                    if ((param0[r2] & 0xf0) >= 0x10 && (param0[r2] & 0xf0) <= 0x30) {
                        param0[r2] += 0x50;
                    }
                } else {
                    if ((param0[r2] & 0xf) >= 1 && (param0[r2] & 0xf) <= 3) {
                        param0[r2] += 5;
                    }
                }
                r1++;
            }
            param1 >>= 8;
        }
    }
}

u16 sub_02008A54(u32 *param0) {
    *param0 = (*param0) * 0x41C64E6D + 0x6073;

    return (u16)(*param0 >> 16);
}

void sub_02008A74(u8 *param0) {
    u32 st0 = ((u16 *)param0)[0xc7f];
    for (s32 r4 = 0xc7f; r4 > -1; r4--) {
        ((u16 *)param0)[r4] ^= st0;
        sub_02008A54(&st0);
    }
}
