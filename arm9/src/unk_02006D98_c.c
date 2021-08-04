#include "global.h"
#include "MI_memory.h"
#include "NNS_g2d.h"
#include "filesystem.h"
#include "heap.h"
#include "poketool/pokegra/otherpoke.naix"
#include "registers.h"

struct UnkStruct3 {
    u32 unk00[8];
};

struct UnkStruct4{
    u8 unk0;
    u8 unk1;
};






const struct UnkStruct4 UNK_020ECC78[] = {
	{0x33, 0x11}, {0x34, 0x11}, {0x35, 0x11}, {0x36, 0x11}, {0x32, 0x12}, {0x33, 0x12}, {0x34, 0x12}, {0x35, 0x12},
	{0x36, 0x12}, {0x37, 0x12}, {0x31, 0x13}, {0x32, 0x13}, {0x33, 0x13}, {0x34, 0x13}, {0x35, 0x13}, {0x36, 0x13},
	{0x37, 0x13}, {0x38, 0x13}, {0x31, 0x14}, {0x32, 0x14}, {0x33, 0x14}, {0x34, 0x14}, {0x35, 0x14}, {0x36, 0x14},
	{0x37, 0x14}, {0x38, 0x14}, {0x31, 0x15}, {0x32, 0x15}, {0x33, 0x15}, {0x34, 0x15}, {0x35, 0x15}, {0x36, 0x15},
	{0x37, 0x15}, {0x38, 0x15}, {0x31, 0x16}, {0x32, 0x16}, {0x33, 0x16}, {0x34, 0x16}, {0x35, 0x16}, {0x36, 0x16},
	{0x37, 0x16}, {0x38, 0x16}, {0x32, 0x17}, {0x33, 0x17}, {0x34, 0x17}, {0x35, 0x17}, {0x36, 0x17}, {0x37, 0x17},
	{0x33, 0x18}, {0x34, 0x18}, {0x35, 0x18}, {0x36, 0x18}, {0xFF, 0xFF},
};

const struct UnkStruct4 UNK_020ECCE2[] = {
	{0x1B, 0x0F}, {0x1C, 0x0F}, {0x1D, 0x0F}, {0x1E, 0x0F}, {0x1A, 0x10}, {0x1B, 0x10}, {0x1C, 0x10}, {0x1D, 0x10},
	{0x1E, 0x10}, {0x1F, 0x10}, {0x19, 0x11}, {0x1A, 0x11}, {0x1B, 0x11}, {0x1C, 0x11}, {0x1D, 0x11}, {0x1E, 0x11},
	{0x1F, 0x11}, {0x20, 0x11}, {0x19, 0x12}, {0x1A, 0x12}, {0x1B, 0x12}, {0x1C, 0x12}, {0x1D, 0x12}, {0x1E, 0x12},
	{0x1F, 0x12}, {0x20, 0x12}, {0x19, 0x13}, {0x1A, 0x13}, {0x1B, 0x13}, {0x1C, 0x13}, {0x1D, 0x13}, {0x1E, 0x13},
	{0x1F, 0x13}, {0x20, 0x13}, {0x19, 0x14}, {0x1A, 0x14}, {0x1B, 0x14}, {0x1C, 0x14}, {0x1D, 0x14}, {0x1E, 0x14},
	{0x1F, 0x14}, {0x20, 0x14}, {0x1A, 0x15}, {0x1B, 0x15}, {0x1C, 0x15}, {0x1D, 0x15}, {0x1E, 0x15}, {0x1F, 0x15},
	{0x1B, 0x16}, {0x1C, 0x16}, {0x1D, 0x16}, {0x1E, 0x16}, {0xFF, 0xFF},
};




const struct UnkStruct4 UNK_020ECC10[] = {
	{0x1E, 0x21}, {0x1F, 0x21}, {0x20, 0x21}, {0x1D, 0x22}, {0x1E, 0x22}, {0x1F, 0x22}, {0x20, 0x22}, {0x21, 0x22},
	{0x1C, 0x23}, {0x1D, 0x23}, {0x1E, 0x23}, {0x1F, 0x23}, {0x20, 0x23}, {0x21, 0x23}, {0x22, 0x23}, {0x1C, 0x24},
	{0x1D, 0x24}, {0x1E, 0x24}, {0x1F, 0x24}, {0x20, 0x24}, {0x21, 0x24}, {0x22, 0x24}, {0x1C, 0x25}, {0x1D, 0x25},
	{0x1E, 0x25}, {0x1F, 0x25}, {0x20, 0x25}, {0x21, 0x25}, {0x22, 0x25}, {0x1C, 0x26}, {0x1D, 0x26}, {0x1E, 0x26},
	{0x1F, 0x26}, {0x20, 0x26}, {0x21, 0x26}, {0x22, 0x26}, {0x1C, 0x27}, {0x1D, 0x27}, {0x1E, 0x27}, {0x1F, 0x27},
	{0x20, 0x27}, {0x21, 0x27}, {0x22, 0x27}, {0x1D, 0x28}, {0x1E, 0x28}, {0x1F, 0x28}, {0x20, 0x28}, {0x21, 0x28},
	{0x1E, 0x29}, {0x1F, 0x29}, {0x20, 0x29}, {0xFF, 0xFF},
};


const struct UnkStruct4 UNK_020ECD4C[] = {
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00},
	{0x50, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00},
	{0x00, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00},
	{0x50, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00},
	{0x00, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00}, {0xF0, 0x00}, {0x00, 0x00},
	{0x50, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00}, {0xF0, 0x00}, {0x00, 0x00},
	{0xA0, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0xF0, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00},
	{0xA0, 0x00}, {0x00, 0x00}, {0x50, 0x00}, {0x00, 0x00}, {0xF0, 0x00}, {0x00, 0x00}, {0xA0, 0x00}, {0x00, 0x00}, 
};



const struct UnkStruct4 UNK_020ECDCC[] = {
	{0x2B, 0x21}, {0x2C, 0x21}, {0x2D, 0x21}, {0x29, 0x22}, {0x2A, 0x22}, {0x2B, 0x22}, {0x2C, 0x22}, {0x2D, 0x22},
	{0x2E, 0x22}, {0x2F, 0x22}, {0x28, 0x23}, {0x29, 0x23}, {0x2A, 0x23}, {0x2B, 0x23}, {0x2C, 0x23}, {0x2D, 0x23},
	{0x2E, 0x23}, {0x2F, 0x23}, {0x30, 0x23}, {0x28, 0x24}, {0x29, 0x24}, {0x2A, 0x24}, {0x2B, 0x24}, {0x2C, 0x24},
	{0x2D, 0x24}, {0x2E, 0x24}, {0x2F, 0x24}, {0x30, 0x24}, {0x28, 0x25}, {0x29, 0x25}, {0x2A, 0x25}, {0x2B, 0x25},
	{0x2C, 0x25}, {0x2D, 0x25}, {0x2E, 0x25}, {0x2F, 0x25}, {0x30, 0x25}, {0x28, 0x26}, {0x29, 0x26}, {0x2A, 0x26},
	{0x2B, 0x26}, {0x2C, 0x26}, {0x2D, 0x26}, {0x2E, 0x26}, {0x2F, 0x26}, {0x30, 0x26}, {0x28, 0x27}, {0x29, 0x27},
	{0x2A, 0x27}, {0x2B, 0x27}, {0x2C, 0x27}, {0x2D, 0x27}, {0x2E, 0x27}, {0x2F, 0x27}, {0x30, 0x27}, {0x28, 0x28},
	{0x29, 0x28}, {0x2A, 0x28}, {0x2B, 0x28}, {0x2C, 0x28}, {0x2D, 0x28}, {0x2E, 0x28}, {0x2F, 0x28}, {0x30, 0x28},
	{0x29, 0x29}, {0x2A, 0x29}, {0x2B, 0x29}, {0x2C, 0x29}, {0x2D, 0x29}, {0x2E, 0x29}, {0x2F, 0x29}, {0x2B, 0x2A},
	{0x2C, 0x2A}, {0x2D, 0x2A}, {0xFF, 0xFF}
};


// const int UNK_020ECD4C[4][2][4] = {
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

const int UNK_020ECBD0[4][4] = {
    {160, 160, 224, 176}, {160, 160, 224, 176}, {160, 176, 224, 192}, {160, 192, 224, 208}
};



const struct UnkStruct4 *UNK_02105AE8[] = {
    UNK_020ECCE2,
    UNK_020ECC78,
    UNK_020ECC10,
    UNK_020ECDCC,
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
    u8 unk5C[0xC];
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
    u8 unk78[0x20];
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




// extern struct UnkStruct3 UNK_020ECD4C[4];
extern void NNS_G2dDrawSpriteFast(s16 param0, s16 param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8);


// THUMB_FUNC void FUN_02006ED4(struct UnkStruct1 *param0) {
//             s32 arg3;
//         s32 arg4;

//     FUN_020082A8(param0);
//     FUN_020086F4(param0);

//     NNS_G3dGeFlushBuffer();

//     reg_G3_MTX_PUSH = 0;

//     reg_G3_TEXIMAGE_PARAM = (param0->unk29C >> 3) | (param0->unk274 << 26) | (1 << 30) | (param0->unk26C << 20) | (param0->unk270 << 23) | (param0->unk27C << 29);

//     for (int st18 = 0; st18 < 4; st18++) {
//         if (param0->unk000[st18].unk00_0 == 0 || param0->unk000[st18].unk54_0 != 0 || param0->unk000[st18].unk54_B != 0) {
//             continue;
//         }

//         if (param0->unk000[st18].unk68 != NULL) {
//             param0->unk000[st18].unk68(&param0->unk000[st18], &param0->unk000[st18].unk24);
//         }

//         NNS_G3dGeFlushBuffer();

//         if (param0->unk2E3 != 1) {
//             reg_G3_MTX_IDENTITY = 0;
//         }

//         FUN_02007F48(&param0->unk000[st18]);
        
//         u32 shift;
//         if (param0->unk274 == 2) {
//             shift = 1;
//         } else {
//             shift = 0;
//         }

//         reg_G3_TEXPLTT_BASE = (param0->unk2A4 + st18*0x20)>>(4-shift);

//         u32 r1 = param0->unk000[st18].unk28<<0xc;
//         u32 r0 = (param0->unk000[st18].unk26 + param0->unk000[st18].unk42)<<0xc;
//         u32 r3 = (param0->unk000[st18].unk24 + param0->unk000[st18].unk40)<<0xc;

//         reg_G3_MTX_TRANS = r3;
//         reg_G3_MTX_TRANS = r0;
//         reg_G3_MTX_TRANS = r1;


//         s32 idx = ((s32)param0->unk000[st18].unk38)>>4;
//         G3_RotX(FX_SinCosTable_[idx*2], FX_SinCosTable_[idx*2+1]);

//         s32 idy = ((s32)param0->unk000[st18].unk3A)>>4;
//         G3_RotY(FX_SinCosTable_[idy*2], FX_SinCosTable_[idy*2+1]);

//         s32 idz = ((s32)param0->unk000[st18].unk3C)>>4;
//         G3_RotZ(FX_SinCosTable_[idz*2], FX_SinCosTable_[idz*2+1]);


//         r1 = -(param0->unk000[st18].unk28<<0xc);
//         r0 = -((param0->unk000[st18].unk26 + param0->unk000[st18].unk42)<<0xc);
//         r3 = -((param0->unk000[st18].unk24 + param0->unk000[st18].unk40)<<0xc);

//         reg_G3_MTX_TRANS = r3;
//         reg_G3_MTX_TRANS = r0;
//         reg_G3_MTX_TRANS = r1;

//         reg_G3_DIF_AMB =
//             ((u16)(param0->unk000[st18].unk50_0 | (param0->unk000[st18].unk50_5<<5) | (param0->unk000[st18].unk50_a<<10))) |
//             (((u16)(param0->unk000[st18].unk50_f | (param0->unk000[st18].unk50_14<<5) | (param0->unk000[st18].unk50_19<<10)))<<16) |
//             0x8000;


//         reg_G3_SPE_EMI = 0x4210;

//         {
//             u32 r1 = param0->unk000[st18].unk00_1;
//             u32 r0 = param0->unk000[st18].unk54_2;
//             reg_G3_POLYGON_ATTR = 0xc0 | (r1<<24) | (r0<<16);
//         }

//         if (param0->unk000[st18].unk54_1 != 0) {
//             u32 r6 = param0->unk000[st18].unk44 + UNK_020ECD4C[st18].unk00[param0->unk000[st18].unk5B*4];
//             u32 r12 = param0->unk000[st18].unk46;
//             u32 r1 = param0->unk000[st18].unk45 + UNK_020ECD4C[st18].unk00[param0->unk000[st18].unk5B*4 + 1];
//             u32 r7 = param0->unk000[st18].unk47;
//             u32 r0 = r12 + r6;


//             NNS_G2dDrawSpriteFast(
//                 param0->unk000[st18].unk24-40 + param0->unk000[st18].unk44 + param0->unk000[st18].unk2C,
//                 param0->unk000[st18].unk26-40 + param0->unk000[st18].unk45 + param0->unk000[st18].unk2E - param0->unk000[st18].unk6E,
//                 param0->unk000[st18].unk28 + param0->unk000[st18].unk30,
//                 r12,
//                 r7,
//                 r6,
//                 r1,
//                 r0,
//                 r7 + r1
//             );

//         } else {
//             arg3 = (param0->unk000[st18].unk34*80)>>8;
//             arg4 = (param0->unk000[st18].unk36*80)>>8;

//             NNS_G2dDrawSpriteFast(
//                 param0->unk000[st18].unk24-(arg3/2)+param0->unk000[st18].unk2C,
//                 param0->unk000[st18].unk26-(arg4/2)+ param0->unk000[st18].unk2E - param0->unk000[st18].unk6E,
//                 param0->unk000[st18].unk28 + param0->unk000[st18].unk30,
//                 arg3,
//                 arg4,
//                 UNK_020ECD4C[st18].unk00[param0->unk000[st18].unk5B*4],
//                 UNK_020ECD4C[st18].unk00[param0->unk000[st18].unk5B*4+1],
//                 UNK_020ECD4C[st18].unk00[param0->unk000[st18].unk5B*4+2],
//                 UNK_020ECD4C[st18].unk00[param0->unk000[st18].unk5B*4+3]
//             );
//         }


//         if (param0->unk000[st18].unk6C_0 == 0 || param0->unk000[st18].unk6C_5 == 0 || param0->unk000[st18].unk54_1 != 0 || (param0->unk2E4 & 1) != 0) {
//             continue;
//         }

//         if (param0->unk2E3 != 1) {
//             reg_G3_MTX_IDENTITY = 0;
//         }

//         u32 shift2;
//         if (param0->unk274 == 2) {
//             shift2 = 1;
//         } else {
//             shift2 = 0;
//         }
//         reg_G3_TEXPLTT_BASE = (param0->unk2A4 + ((param0->unk000[st18].unk6C_0+3)<<5))>>(4-shift2);



//         if (param0->unk000[st18].unk6C_4 != 0) {
//             arg3 = (param0->unk000[st18].unk34*64)>>8;
//             arg4 = (param0->unk000[st18].unk36*16)>>8;
//         } else {
//             arg3 = 64;
//             arg4 = 16;
//         }

//         if (param0->unk000[st18].unk6C_2 != 0) {
//             param0->unk000[st18].unk70 = param0->unk000[st18].unk24+ param0->unk000[st18].unk2C + param0->unk000[st18].unk74;
//         }

//         if (param0->unk000[st18].unk6C_3 != 0) {
//             param0->unk000[st18].unk72 = param0->unk000[st18].unk26 + param0->unk000[st18].unk2E + param0->unk000[st18].unk76;
//         }


//         NNS_G2dDrawSpriteFast(
//             param0->unk000[st18].unk70 - (arg3/2),
//             param0->unk000[st18].unk72 - (arg4/2),
//             0xFFFFFC18,
//             arg3,
//             arg4,
//             UNK_020ECBD0[param0->unk000[st18].unk6C_5*4],
//             UNK_020ECBD0[param0->unk000[st18].unk6C_5*4 + 1],
//             UNK_020ECBD0[param0->unk000[st18].unk6C_5*4 + 2],
//             UNK_020ECBD0[param0->unk000[st18].unk6C_5*4 + 3]
//         );

//     }


//     reg_G3_MTX_POP = 1;
// }
