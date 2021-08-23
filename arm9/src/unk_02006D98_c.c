#include "global.h"
#include "MI_memory.h"
#include "NNS_g2d.h"
#include "filesystem.h"
#include "heap.h"
#include "poketool/pokegra/otherpoke.naix"
#include "registers.h"
#include "mod63_021DB450.h"

struct UnkStruct3 {
    u32 unk00[8];
};

struct UnkStruct4{
    u8 unk0;
    u8 unk1;
};



static const u8 UNK_020ECCE0[] = {
	0xFF, 0xFF, 0x1B, 0x0F, 0x1C, 0x0F, 0x1D, 0x0F, 0x1E, 0x0F, 0x1A, 0x10, 0x1B, 0x10, 0x1C, 0x10, 0x1D, 0x10,
	0x1E, 0x10, 0x1F, 0x10, 0x19, 0x11, 0x1A, 0x11, 0x1B, 0x11, 0x1C, 0x11, 0x1D, 0x11, 0x1E, 0x11,
	0x1F, 0x11, 0x20, 0x11, 0x19, 0x12, 0x1A, 0x12, 0x1B, 0x12, 0x1C, 0x12, 0x1D, 0x12, 0x1E, 0x12,
	0x1F, 0x12, 0x20, 0x12, 0x19, 0x13, 0x1A, 0x13, 0x1B, 0x13, 0x1C, 0x13, 0x1D, 0x13, 0x1E, 0x13,
	0x1F, 0x13, 0x20, 0x13, 0x19, 0x14, 0x1A, 0x14, 0x1B, 0x14, 0x1C, 0x14, 0x1D, 0x14, 0x1E, 0x14,
	0x1F, 0x14, 0x20, 0x14, 0x1A, 0x15, 0x1B, 0x15, 0x1C, 0x15, 0x1D, 0x15, 0x1E, 0x15, 0x1F, 0x15,
	0x1B, 0x16, 0x1C, 0x16, 0x1D, 0x16, 0x1E, 0x16, 0xFF, 0xFF,
};




static const u8 UNK_020ECC10[] = {
	0x1E, 0x21, 0x1F, 0x21, 0x20, 0x21, 0x1D, 0x22, 0x1E, 0x22, 0x1F, 0x22, 0x20, 0x22, 0x21, 0x22,
	0x1C, 0x23, 0x1D, 0x23, 0x1E, 0x23, 0x1F, 0x23, 0x20, 0x23, 0x21, 0x23, 0x22, 0x23, 0x1C, 0x24,
	0x1D, 0x24, 0x1E, 0x24, 0x1F, 0x24, 0x20, 0x24, 0x21, 0x24, 0x22, 0x24, 0x1C, 0x25, 0x1D, 0x25,
	0x1E, 0x25, 0x1F, 0x25, 0x20, 0x25, 0x21, 0x25, 0x22, 0x25, 0x1C, 0x26, 0x1D, 0x26, 0x1E, 0x26,
	0x1F, 0x26, 0x20, 0x26, 0x21, 0x26, 0x22, 0x26, 0x1C, 0x27, 0x1D, 0x27, 0x1E, 0x27, 0x1F, 0x27,
	0x20, 0x27, 0x21, 0x27, 0x22, 0x27, 0x1D, 0x28, 0x1E, 0x28, 0x1F, 0x28, 0x20, 0x28, 0x21, 0x28,
	0x1E, 0x29, 0x1F, 0x29, 0x20, 0x29, 0xFF, 0xFF,
};


static const u8 UNK_020ECC78[] = {
	0x33, 0x11, 0x34, 0x11, 0x35, 0x11, 0x36, 0x11, 0x32, 0x12, 0x33, 0x12, 0x34, 0x12, 0x35, 0x12,
	0x36, 0x12, 0x37, 0x12, 0x31, 0x13, 0x32, 0x13, 0x33, 0x13, 0x34, 0x13, 0x35, 0x13, 0x36, 0x13,
	0x37, 0x13, 0x38, 0x13, 0x31, 0x14, 0x32, 0x14, 0x33, 0x14, 0x34, 0x14, 0x35, 0x14, 0x36, 0x14,
	0x37, 0x14, 0x38, 0x14, 0x31, 0x15, 0x32, 0x15, 0x33, 0x15, 0x34, 0x15, 0x35, 0x15, 0x36, 0x15,
	0x37, 0x15, 0x38, 0x15, 0x31, 0x16, 0x32, 0x16, 0x33, 0x16, 0x34, 0x16, 0x35, 0x16, 0x36, 0x16,
	0x37, 0x16, 0x38, 0x16, 0x32, 0x17, 0x33, 0x17, 0x34, 0x17, 0x35, 0x17, 0x36, 0x17, 0x37, 0x17,
	0x33, 0x18, 0x34, 0x18, 0x35, 0x18, 0x36, 0x18,
};

static const u8 UNK_020ECDCC[] = {
	0x2B, 0x21, 0x2C, 0x21, 0x2D, 0x21, 0x29, 0x22, 0x2A, 0x22, 0x2B, 0x22, 0x2C, 0x22, 0x2D, 0x22,
	0x2E, 0x22, 0x2F, 0x22, 0x28, 0x23, 0x29, 0x23, 0x2A, 0x23, 0x2B, 0x23, 0x2C, 0x23, 0x2D, 0x23,
	0x2E, 0x23, 0x2F, 0x23, 0x30, 0x23, 0x28, 0x24, 0x29, 0x24, 0x2A, 0x24, 0x2B, 0x24, 0x2C, 0x24,
	0x2D, 0x24, 0x2E, 0x24, 0x2F, 0x24, 0x30, 0x24, 0x28, 0x25, 0x29, 0x25, 0x2A, 0x25, 0x2B, 0x25,
	0x2C, 0x25, 0x2D, 0x25, 0x2E, 0x25, 0x2F, 0x25, 0x30, 0x25, 0x28, 0x26, 0x29, 0x26, 0x2A, 0x26,
	0x2B, 0x26, 0x2C, 0x26, 0x2D, 0x26, 0x2E, 0x26, 0x2F, 0x26, 0x30, 0x26, 0x28, 0x27, 0x29, 0x27,
	0x2A, 0x27, 0x2B, 0x27, 0x2C, 0x27, 0x2D, 0x27, 0x2E, 0x27, 0x2F, 0x27, 0x30, 0x27, 0x28, 0x28,
	0x29, 0x28, 0x2A, 0x28, 0x2B, 0x28, 0x2C, 0x28, 0x2D, 0x28, 0x2E, 0x28, 0x2F, 0x28, 0x30, 0x28,
	0x29, 0x29, 0x2A, 0x29, 0x2B, 0x29, 0x2C, 0x29, 0x2D, 0x29, 0x2E, 0x29, 0x2F, 0x29, 0x2B, 0x2A,
	0x2C, 0x2A, 0x2D, 0x2A, 0xFF, 0xFF
};




static const int UNK_020ECBD0[4][4] = {
    {160, 160, 224, 176}, {160, 160, 224, 176}, {160, 176, 224, 192}, {160, 192, 224, 208}
};



// static const int UNK_020ECD4C[4][2][4] = {
//     {
//             {0, 0, 0x50, 0x50}, {0x50, 0, 0xA0, 0x50}
//     }, {
    
//             {0, 0x50, 0x50, 0xA0}, {0x50, 0x50, 0xA0, 0xA0}
    
//     }, {

    
//         {0, 0xA0, 0x50, 0xF0}, {0x50, 0xA0, 0xA0, 0xF0}
    
//     }, {
    
//             {0xA0, 0, 0xF0, 0x50}, {0xA0, 0x50, 0xF0, 0xA0}
    
//     }
// };


const u8 UNK_020ECD4C[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00,
	0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00,
	0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00,
	0x50, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00,
	0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00,
	0xA0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00,
};



const struct UnkStruct4 *UNK_02105AE8[] = {
    (struct UnkStruct4 *)(UNK_020ECCE0+2),
    (struct UnkStruct4 *)UNK_020ECC78,
    (struct UnkStruct4 *)UNK_020ECC10,
    (struct UnkStruct4 *)UNK_020ECDCC,
};

struct UnkStruct2 {
    u32 unk00_0:1;
    u32 unk00_1:6;
    u8 unk04[0x20];
    s16 unk24;
    s16 unk26;
    u32 unk28;
    s16 unk2C;
    s16 unk2E;
    u32 unk30;
    s16 unk34;
    s16 unk36;
    u16 unk38;
    u16 unk3A;
    u16 unk3C;
    u16 unk3E;
    s16 unk40;
    s16 unk42;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48[0x8];
    u32 unk50_0:5;
    u32 unk50_5:5;
    u32 unk50_a:5;
    u32 unk50_f:5;
    u32 unk50_14:5;
    u32 unk50_19:5;
    u32 unk50_1E:2;
    u32 unk54_0:1;
    u32 unk54_1:1;
    u32 unk54_2:5;
    u32 unk54_7:4;
    u32 unk54_B:1;
    u8 unk58;
    u8 unk59;
    u8 unk5A;
    u8 unk5B;
    u8 unk5C[10];
    void (*unk68)(struct UnkStruct2 *, void *);
    u16 unk6C_0:2;
    u16 unk6C_2:1;
    u16 unk6C_3:1;
    u16 unk6C_4:1;
    u16 unk6C_5:2;
    s8 unk6E;
    u8 unk6F;
    s16 unk70;
    s16 unk72;
    s16 unk74;
    s16 unk76;
    u8 unk78[0xc];
    struct UnkStruct2_sub {
        s8 unk0;
        u8 unk1;
    } unk84[10];
};


struct UnkStruct1
{
    struct UnkStruct2 unk000[4];
    u8 unk260[0xc];
    u32 unk26C;
    u32 unk270;
    u32 unk274;
    u32 unk278;
    u32 unk27C;
    u8 unk280[0x18];
    u32 unk298;
    u32 unk29C;
    u32 unk2A0;
    u32 unk2A4;
    u32 unk2A8;
    void *unk2AC;
    void *unk2B0;
    void *unk2B4;
    u32 unk2B8;
    u32 unk2BC;
    u32 unk2C0;
    u32 unk2C4;
    u8 unk2C8[0x18];
    u8 unk2E0;
    u8 unk2E1;
    u8 unk2E2;
    u8 unk2E3;
    u32 unk2E4;
};

extern void NNS_G2dSetupSoftwareSpriteCamera(void);
extern void FUN_02008A74(void *);

THUMB_FUNC struct UnkStruct1 *FUN_02006D98(u32 heap_id)
{
    struct UnkStruct1 *ptr = AllocFromHeap(heap_id, sizeof(struct UnkStruct1));
    ptr->unk298 = heap_id;
    ptr->unk2E0 = 0;
    ptr->unk29C = 0;
    ptr->unk2A0 = 0x8000;
    ptr->unk2A4 = 0;
    ptr->unk2A8 = 0x80;

    ptr->unk2AC = AllocFromHeap(heap_id, 0x8000);

    ptr->unk2B0 = AllocFromHeap(heap_id, 0xc0);
    MIi_CpuClearFast(0, ptr->unk2B0, 4);

    ptr->unk2B4 = AllocFromHeap(heap_id, 0xc0);
    MIi_CpuClearFast(0, ptr->unk2B4, 4);

    for (int i = 0; i < 4; i++)
    {
        MIi_CpuClearFast(0, &ptr->unk000[i], sizeof(struct UnkStruct2));
    }

    NNS_G2dSetupSoftwareSpriteCamera();
    ptr->unk2E3 = 0;

    u8 *st8;
    void *st4 = AllocAndReadWholeNarcMemberByIdPair(
        NARC_POKETOOL_POKEGRA_OTHERPOKE, NARC_otherpoke_narc_0211_NCGR, ptr->unk298);
    NNSG2dCharacterData *stc;
    NNS_G2dGetUnpackedCharacterData(st4, &stc);

    ptr->unk2BC = stc->pixelFmt;
    ptr->unk2C0 = stc->mapingType;
    ptr->unk2C4 = stc->characterFmt;
    st8 = stc->pRawData;

    FUN_02008A74(st8);
    MI_CpuFill8(ptr->unk2AC, *st8, 0x8000);

    for (int i = 0; i < 0x50; i++)
    {
        for (int j = 0; j < 0x28; j++)
        {
            ((u8 *)ptr->unk2AC)[0x5050 + i * 0x80 + j] = st8[i * 0x50 + j];
        }
    }

    FreeToHeap(st4);
    ptr->unk2E1 = 1;
    ptr->unk2E2 = 1;

    return ptr;
}


extern void FUN_020082A8(struct UnkStruct1 *);
extern void FUN_020086F4(struct UnkStruct1 *);
extern void NNS_G3dGeFlushBuffer();
extern void FUN_02007F48(struct UnkStruct2 *);



extern void NNS_G2dDrawSpriteFast(s16 param0, s16 param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8);

#ifdef NONMATCHING

// mostly matching, only 2 register writes messed up
THUMB_FUNC void FUN_02006ED4(struct UnkStruct1 *param0) {
            s32 arg3;
        s32 arg4;

    FUN_020082A8(param0);
    FUN_020086F4(param0);

    NNS_G3dGeFlushBuffer();

    reg_G3_MTX_PUSH = 0;

    // this is all shuffled however I try
    reg_G3_TEXIMAGE_PARAM = (param0->unk29C >> 3) | (param0->unk274 << 26) | (1 << 30) | (param0->unk26C << 20) | (param0->unk270 << 23) | (param0->unk27C << 29);

    for (int st18 = 0; st18 < 4; st18++) {
        if (param0->unk000[st18].unk00_0 == 0 || param0->unk000[st18].unk54_0 != 0 || param0->unk000[st18].unk54_B != 0) {
            continue;
        }

        if (param0->unk000[st18].unk68 != NULL) {
            param0->unk000[st18].unk68(&param0->unk000[st18], &param0->unk000[st18].unk24);
        }

        NNS_G3dGeFlushBuffer();

        if (param0->unk2E3 != 1) {
            reg_G3_MTX_IDENTITY = 0;
        }

        FUN_02007F48(&param0->unk000[st18]);
        
        u32 shift;
        if (param0->unk274 == 2) {
            shift = 1;
        } else {
            shift = 0;
        }

        reg_G3_TEXPLTT_BASE = (param0->unk2A4 + st18*0x20)>>(4-shift);

        u32 r1 = param0->unk000[st18].unk28<<0xc;
        u32 r0 = (param0->unk000[st18].unk26 + param0->unk000[st18].unk42)<<0xc;
        u32 r3 = (param0->unk000[st18].unk24 + param0->unk000[st18].unk40)<<0xc;

        reg_G3_MTX_TRANS = r3;
        reg_G3_MTX_TRANS = r0;
        reg_G3_MTX_TRANS = r1;


        s32 idx = ((s32)param0->unk000[st18].unk38)>>4;
        G3_RotX(FX_SinCosTable_[idx*2], FX_SinCosTable_[idx*2+1]);

        s32 idy = ((s32)param0->unk000[st18].unk3A)>>4;
        G3_RotY(FX_SinCosTable_[idy*2], FX_SinCosTable_[idy*2+1]);

        s32 idz = ((s32)param0->unk000[st18].unk3C)>>4;
        G3_RotZ(FX_SinCosTable_[idz*2], FX_SinCosTable_[idz*2+1]);


        r1 = -(param0->unk000[st18].unk28<<0xc);
        r0 = -((param0->unk000[st18].unk26 + param0->unk000[st18].unk42)<<0xc);
        r3 = -((param0->unk000[st18].unk24 + param0->unk000[st18].unk40)<<0xc);

        reg_G3_MTX_TRANS = r3;
        reg_G3_MTX_TRANS = r0;
        reg_G3_MTX_TRANS = r1;

        reg_G3_DIF_AMB =
            ((u16)(param0->unk000[st18].unk50_0 | (param0->unk000[st18].unk50_5<<5) | (param0->unk000[st18].unk50_a<<10))) |
            (((u16)(param0->unk000[st18].unk50_f | (param0->unk000[st18].unk50_14<<5) | (param0->unk000[st18].unk50_19<<10)))<<16) |
            0x8000;


        reg_G3_SPE_EMI = 0x4210;


        {
            // shuffled there as well
            u32 r1 = param0->unk000[st18].unk00_1;
            u32 r0 = param0->unk000[st18].unk54_2;
            reg_G3_POLYGON_ATTR = 0xc0 | (r1<<24) | (r0<<16);
        }

        if (param0->unk000[st18].unk54_1 != 0) {
            u32 r6 = param0->unk000[st18].unk44 + (*((int(*)[4][2][4])&UNK_020ECD4C))[st18][param0->unk000[st18].unk5B][0];
            u32 r12 = param0->unk000[st18].unk46;
            u32 r1 = param0->unk000[st18].unk45 + (*((int(*)[4][2][4])&UNK_020ECD4C))[st18][param0->unk000[st18].unk5B][1];
            u32 r7 = param0->unk000[st18].unk47;
            u32 r0 = r12 + r6;


            NNS_G2dDrawSpriteFast(
                param0->unk000[st18].unk24-40 + param0->unk000[st18].unk44 + param0->unk000[st18].unk2C,
                param0->unk000[st18].unk26-40 + param0->unk000[st18].unk45 + param0->unk000[st18].unk2E - param0->unk000[st18].unk6E,
                param0->unk000[st18].unk28 + param0->unk000[st18].unk30,
                r12,
                r7,
                r6,
                r1,
                r0,
                r7 + r1
            );

        } else {
            arg3 = (param0->unk000[st18].unk34*80)>>8;
            arg4 = (param0->unk000[st18].unk36*80)>>8;

            NNS_G2dDrawSpriteFast(
                param0->unk000[st18].unk24-(arg3/2)+param0->unk000[st18].unk2C,
                param0->unk000[st18].unk26-(arg4/2)+ param0->unk000[st18].unk2E - param0->unk000[st18].unk6E,
                param0->unk000[st18].unk28 + param0->unk000[st18].unk30,
                arg3,
                arg4,
                (*((int(*)[4][2][4])&UNK_020ECD4C))[st18][param0->unk000[st18].unk5B][0],
                (*((int(*)[4][2][4])&UNK_020ECD4C))[st18][param0->unk000[st18].unk5B][1],
                (*((int(*)[4][2][4])&UNK_020ECD4C))[st18][param0->unk000[st18].unk5B][2],
                (*((int(*)[4][2][4])&UNK_020ECD4C))[st18][param0->unk000[st18].unk5B][3]
            );
        }


        if (param0->unk000[st18].unk6C_0 == 0 || param0->unk000[st18].unk6C_5 == 0 || param0->unk000[st18].unk54_1 != 0 || (param0->unk2E4 & 1) != 0) {
            continue;
        }

        if (param0->unk2E3 != 1) {
            reg_G3_MTX_IDENTITY = 0;
        }

        u32 shift2;
        if (param0->unk274 == 2) {
            shift2 = 1;
        } else {
            shift2 = 0;
        }
        reg_G3_TEXPLTT_BASE = (param0->unk2A4 + ((param0->unk000[st18].unk6C_0+3)<<5))>>(4-shift2);



        if (param0->unk000[st18].unk6C_4 != 0) {
            arg3 = (param0->unk000[st18].unk34*64)>>8;
            arg4 = (param0->unk000[st18].unk36*16)>>8;
        } else {
            arg3 = 64;
            arg4 = 16;
        }

        if (param0->unk000[st18].unk6C_2 != 0) {
            param0->unk000[st18].unk70 = param0->unk000[st18].unk24+ param0->unk000[st18].unk2C + param0->unk000[st18].unk74;
        }

        if (param0->unk000[st18].unk6C_3 != 0) {
            param0->unk000[st18].unk72 = param0->unk000[st18].unk26 + param0->unk000[st18].unk2E + param0->unk000[st18].unk76;
        }


        NNS_G2dDrawSpriteFast(
            param0->unk000[st18].unk70 - (arg3/2),
            param0->unk000[st18].unk72 - (arg4/2),
            0xFFFFFC18,
            arg3,
            arg4,
            UNK_020ECBD0[param0->unk000[st18].unk6C_5][0],
            UNK_020ECBD0[param0->unk000[st18].unk6C_5][1],
            UNK_020ECBD0[param0->unk000[st18].unk6C_5][2],
            UNK_020ECBD0[param0->unk000[st18].unk6C_5][3]
        );

    }


    reg_G3_MTX_POP = 1;
}
#else
asm void FUN_02006ED4(struct UnkStruct1 *param0) {
    // clang-format off
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	bl FUN_020082A8
	add r0, r5, #0x0
	bl FUN_020086F4
	bl NNS_G3dGeFlushBuffer
	mov r6, #0x9f
	mov r0, #0x0
	ldr r4, =0x04000444
	lsl r6, r6, #0x2
	str r0, [r4, #0x0]
	str r0, [sp, #0x18]
	add r0, r6, #0x0
	sub r0, #0xc
	ldr r1, [r5, r0]
	add r3, r6, #0x0
	ldr r2, [r5, r6]
	add r0, r6, #0x0
	sub r3, #0x8
	add r6, #0x20
	ldr r3, [r5, r3]
	ldr r6, [r5, r6]
	sub r0, #0x10
	ldr r0, [r5, r0]
	lsr r6, r6, #0x3
	lsl r3, r3, #0x1a
	orr r6, r3
	mov r3, #0x1
	lsl r3, r3, #0x1e
	lsl r0, r0, #0x14
	orr r3, r6
	lsl r1, r1, #0x17
	orr r0, r3
	lsl r2, r2, #0x1d
	orr r0, r1
	orr r0, r2
	str r0, [r4, #0x64]
	ldr r0, [sp, #0x18]
	add r4, r5, #0x0
	str r0, [sp, #0x14]
	ldr r0, =UNK_020ECD4C
	str r0, [sp, #0x1c]
_02006F30:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _02006F46
	ldr r0, [r4, #0x54]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	bne _02006F46
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1f
	beq _02006F48
_02006F46:
	b _020072BC
_02006F48:
	ldr r2, [r4, #0x68]
	cmp r2, #0x0
	beq _02006F56
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0x24
	blx r2
_02006F56:
	bl NNS_G3dGeFlushBuffer
	ldr r0, =0x000002E3
	ldrb r0, [r5, r0]
	cmp r0, #0x1
	beq _02006F68
	ldr r0, =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
_02006F68:
	add r0, r4, #0x0
	bl FUN_02007F48
	mov r0, #0x9d
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	cmp r0, #0x2
	bne _02006F7C
	mov r0, #0x1
	b _02006F7E
_02006F7C:
	mov r0, #0x0
_02006F7E:
	mov r1, #0xa9
	lsl r1, r1, #0x2
	ldr r2, [r5, r1]
	ldr r1, [sp, #0x14]
	add r2, r2, r1
	mov r1, #0x4
	sub r0, r1, r0
	add r1, r2, #0x0
	lsr r1, r0
	ldr r0, =0x040004AC
	str r1, [r0, #0x0]
	ldr r0, [r4, #0x28]
	lsl r1, r0, #0xc
	mov r0, #0x26
	ldrsh r2, [r4, r0]
	mov r0, #0x42
	ldrsh r0, [r4, r0]
	add r0, r2, r0
	mov r2, #0x24
	ldrsh r3, [r4, r2]
	mov r2, #0x40
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0xc
	add r2, r3, r2
	lsl r3, r2, #0xc
	ldr r2, =0x04000470
	str r3, [r2, #0x0]
	str r0, [r2, #0x0]
	add r0, r2, #0x0
	str r1, [r0, #0x0]
	ldrh r0, [r4, #0x38]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, =FX_SinCosTable_
	add r2, r0, r1
	ldrsh r0, [r0, r1]
	mov r1, #0x2
	ldrsh r1, [r2, r1]
	bl G3_RotX
	ldrh r0, [r4, #0x3a]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, =FX_SinCosTable_
	add r2, r0, r1
	ldrsh r0, [r0, r1]
	mov r1, #0x2
	ldrsh r1, [r2, r1]
	bl G3_RotY
	ldrh r0, [r4, #0x3c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, =FX_SinCosTable_
	add r2, r0, r1
	ldrsh r0, [r0, r1]
	mov r1, #0x2
	ldrsh r1, [r2, r1]
	bl G3_RotZ
	ldr r0, [r4, #0x28]
	lsl r0, r0, #0xc
	neg r1, r0
	mov r0, #0x26
	ldrsh r2, [r4, r0]
	mov r0, #0x42
	ldrsh r0, [r4, r0]
	add r0, r2, r0
	mov r2, #0x24
	ldrsh r3, [r4, r2]
	mov r2, #0x40
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0xc
	neg r0, r0
	add r2, r3, r2
	lsl r2, r2, #0xc
	neg r3, r2
	ldr r2, =0x04000470
	str r3, [r2, #0x0]
	str r0, [r2, #0x0]
	add r0, r2, #0x0
	str r1, [r0, #0x0]
	ldr r3, [r4, #0x50]
	lsl r0, r3, #0x11
	lsr r0, r0, #0x1b
	lsl r2, r3, #0x16
	lsl r1, r0, #0xa
	lsl r0, r3, #0x1b
	lsr r2, r2, #0x1b
	lsr r0, r0, #0x1b
	lsl r2, r2, #0x5
	orr r0, r2
	orr r0, r1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	lsl r0, r3, #0x2
	lsr r0, r0, #0x1b
	lsl r1, r0, #0xa
	lsl r0, r3, #0xc
	lsl r3, r3, #0x7
	lsr r3, r3, #0x1b
	lsr r0, r0, #0x1b
	lsl r3, r3, #0x5
	orr r0, r3
	orr r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	add r1, r2, #0x0
	orr r1, r0
	mov r0, #0x2
	lsl r0, r0, #0xe
	orr r1, r0
	ldr r0, =0x040004C0
	str r1, [r0, #0x0]
	ldr r1, =0x00004210
	add r0, r0, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x0]
	ldr r0, [r4, #0x54]
	lsl r1, r1, #0x19
	lsl r0, r0, #0x19
	lsr r1, r1, #0x1a
	lsr r0, r0, #0x1b
	lsl r2, r1, #0x18
	mov r1, #0xc0
	lsl r0, r0, #0x10
	orr r1, r2
	orr r1, r0
	ldr r0, =0x040004A4
	str r1, [r0, #0x0]
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _02007104
	add r0, r4, #0x0
	add r0, #0x5b
	ldrb r0, [r0, #0x0]
	add r2, r4, #0x0
	add r2, #0x44
	lsl r1, r0, #0x4
	ldr r0, [sp, #0x1c]
	ldrb r3, [r2, #0x0]
	add r0, r0, r1
	ldr r2, [sp, #0x1c]
	ldr r0, [r0, #0x4]
	ldr r1, [r2, r1]
	add r6, r3, r1
	add r1, r4, #0x0
	add r1, #0x46
	ldrb r1, [r1, #0x0]
	mov r12, r1
	add r1, r4, #0x0
	add r1, #0x45
	ldrb r2, [r1, #0x0]
	add r1, r2, r0
	add r0, r4, #0x0
	add r0, #0x47
	ldrb r7, [r0, #0x0]
	mov r0, r12
	add r0, r0, r6
	str r7, [sp, #0x0]
	str r6, [sp, #0x4]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r7, r1
	str r0, [sp, #0x10]
	mov r1, #0x24
	ldrsh r1, [r4, r1]
	mov r0, #0x2c
	ldrsh r0, [r4, r0]
	sub r1, #0x28
	add r1, r1, r3
	add r0, r0, r1
	mov r3, #0x26
	ldrsh r3, [r4, r3]
	mov r1, #0x2e
	lsl r0, r0, #0x10
	sub r3, #0x28
	add r2, r3, r2
	ldrsh r1, [r4, r1]
	ldr r3, [r4, #0x28]
	asr r0, r0, #0x10
	add r2, r1, r2
	mov r1, #0x6e
	ldrsb r1, [r4, r1]
	sub r1, r2, r1
	ldr r2, [r4, #0x30]
	lsl r1, r1, #0x10
	add r2, r3, r2
	asr r1, r1, #0x10
	mov r3, r12
	bl NNS_G2dDrawSpriteFast
	b _02007174
_02007104:
	mov r0, #0x34
	ldrsh r1, [r4, r0]
	mov r0, #0x50
	ldr r2, [sp, #0x1c]
	mul r0, r1
	asr r3, r0, #0x8
	mov r0, #0x36
	ldrsh r1, [r4, r0]
	mov r0, #0x50
	ldr r6, [sp, #0x1c]
	mul r0, r1
	asr r1, r0, #0x8
	add r0, r4, #0x0
	add r0, #0x5b
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x4
	str r1, [sp, #0x0]
	add r2, r2, r0
	ldr r0, [r6, r0]
	lsr r6, r1, #0x1f
	str r0, [sp, #0x4]
	ldr r0, [r2, #0x4]
	add r6, r1, r6
	str r0, [sp, #0x8]
	ldr r0, [r2, #0x8]
	asr r1, r6, #0x1
	str r0, [sp, #0xc]
	ldr r0, [r2, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x24
	ldrsh r2, [r4, r0]
	lsr r0, r3, #0x1f
	add r0, r3, r0
	asr r0, r0, #0x1
	sub r2, r2, r0
	mov r0, #0x2c
	ldrsh r0, [r4, r0]
	ldr r6, [r4, #0x28]
	add r0, r2, r0
	mov r2, #0x26
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	sub r2, r2, r1
	mov r1, #0x2e
	ldrsh r1, [r4, r1]
	add r2, r2, r1
	mov r1, #0x6e
	ldrsb r1, [r4, r1]
	sub r1, r2, r1
	ldr r2, [r4, #0x30]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r6, r2
	bl NNS_G2dDrawSpriteFast
_02007174:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r1, r0, #0x1e
	lsr r1, r1, #0x1e
	beq _0200719A
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1e
	beq _0200719A
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _0200719A
	mov r0, #0xb9
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	mov r0, #0x1
	tst r0, r1
	beq _0200719C
_0200719A:
	b _020072BC
_0200719C:
	ldr r0, =0x000002E3
	ldrb r0, [r5, r0]
	cmp r0, #0x1
	beq _020071AA
	ldr r0, =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
_020071AA:
	mov r0, #0x9d
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	cmp r0, #0x2
	bne _020071B8
	mov r1, #0x1
	b _020071BA
_020071B8:
	mov r1, #0x0
_020071BA:
	add r2, r4, #0x0
	add r2, #0x6c
	ldrh r2, [r2, #0x0]
	mov r0, #0xa9
	lsl r0, r0, #0x2
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1e
	add r2, r2, #0x3
	ldr r0, [r5, r0]
	lsl r2, r2, #0x5
	add r2, r0, r2
	mov r0, #0x4
	sub r0, r0, r1
	add r1, r2, #0x0
	lsr r1, r0
	ldr r0, =0x040004AC
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _020071FA
	mov r0, #0x34
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0x6
	asr r3, r0, #0x8
	mov r0, #0x36
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0x4
	asr r1, r0, #0x8
	b _020071FE
_020071FA:
	mov r3, #0x40
	mov r1, #0x10
_020071FE:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _02007220
	mov r0, #0x74
	ldrsh r2, [r4, r0]
	mov r0, #0x24
	mov r6, #0x2c
	ldrsh r0, [r4, r0]
	ldrsh r6, [r4, r6]
	add r0, r0, r6
	add r2, r2, r0
	add r0, r4, #0x0
	add r0, #0x70
	strh r2, [r0, #0x0]
_02007220:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _02007242
	mov r0, #0x76
	ldrsh r2, [r4, r0]
	mov r0, #0x26
	mov r6, #0x2e
	ldrsh r0, [r4, r0]
	ldrsh r6, [r4, r6]
	add r0, r0, r6
	add r2, r2, r0
	add r0, r4, #0x0
	add r0, #0x72
	strh r2, [r0, #0x0]
_02007242:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	ldr r2, =UNK_020ECBD0
	ldr r6, =UNK_020ECBD0
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x4
	str r1, [sp, #0x0]
	add r2, r2, r0
	ldr r0, [r6, r0]
	lsr r6, r1, #0x1f
	str r0, [sp, #0x4]
	ldr r0, [r2, #0x4]
	add r6, r1, r6
	str r0, [sp, #0x8]
	ldr r0, [r2, #0x8]
	asr r1, r6, #0x1
	str r0, [sp, #0xc]
	ldr r0, [r2, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x70
	ldrsh r2, [r4, r0]
	lsr r0, r3, #0x1f
	add r0, r3, r0
	asr r0, r0, #0x1
	sub r0, r2, r0
	mov r2, #0x72
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	sub r1, r2, r1
	lsl r1, r1, #0x10
	ldr r2, =0xFFFFFC18
	asr r1, r1, #0x10
	bl NNS_G2dDrawSpriteFast
_020072BC:
	ldr r0, [sp, #0x14]
	add r4, #0x98
	add r0, #0x20
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	add r0, #0x20
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
	cmp r0, #0x4
	bge _020072D6
	b _02006F30
_020072D6:
	ldr r0, =0x04000448
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, #0x20
	pop {r3-r7, pc}
    // clang-format on
}
#endif



THUMB_FUNC void FUN_020072E8(struct UnkStruct1 *param0) {
    FreeToHeap(param0->unk2AC);
    FreeToHeap(param0->unk2B0);
    FreeToHeap(param0->unk2B4);
    FreeToHeap(param0);
}


THUMB_FUNC void FUN_02007314(struct UnkStruct2 *param0) {
    param0->unk59 = 0;
    for (s32 i = 0; i < 10; i++) {
        param0->unk5C[i] = 0;
    }
    if (param0->unk84[param0->unk59].unk0 == -1) {
        param0->unk5B = 0;
        return;
    }

    param0->unk58 = 1;
    param0->unk5B = param0->unk84[param0->unk59].unk0;
    param0->unk5A = param0->unk84[param0->unk59].unk1;

}


THUMB_FUNC void FUN_0200737C(struct UnkStruct2 *param0, struct UnkStruct2_sub *param1) {
    MI_CpuCopy8(param1, param0->unk84, sizeof(struct UnkStruct2_sub)*10);
}

THUMB_FUNC BOOL FUN_02007390(struct UnkStruct2 *param0) {
    if (param0->unk58 != 0) {
        return TRUE;
    }
    return FALSE;
}

extern u32  FUN_020073E8(struct UnkStruct1 *param0, struct UnkStruct63_021DB49C *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);

THUMB_FUNC u32 FUN_020073A0(struct UnkStruct1 *param0, struct UnkStruct63_021DB49C *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (param0->unk000[i].unk00_0 == 0) {
            break;
        }
    }
    GF_ASSERT(i != 4);

    return FUN_020073E8(param0, param1, param2, param3, param4, param5, i, param6, param7);
}
