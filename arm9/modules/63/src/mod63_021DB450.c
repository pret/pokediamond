#include "global.h"
#include "heap.h"
#include "constants/species.h"
#include "mod63_021DB450.h"

//todo resolve to static code
extern u32 (*UNK_021064B8)(u32 param0, u32 param1, u32 param2);
extern u32 (*UNK_021064C0)(u32 param0, u32 param1, u32 param2);

extern void FUN_0201327C(u32 param0);
extern void FUN_020132BC(u32 param0);

extern void * FUN_02012CDC(void *, void *, void *, u32, u32, u32);
extern u32 FUN_020073A0(u32, struct UnkStruct63_021DB49C_2 *, u32, u32, u32, u32, u32, u32);

extern u32 FUN_02006D98(u32);
extern void FUN_02068C00(struct UnkStruct63_021DB49C_2*, u16, u32, u32, u32, u32, u32);
extern void FUN_02012CC8(void);
extern void FUN_02007558(u32, u32, u32);
extern void FUN_0201EC94(u32, u32, u32);
extern u32 FUN_0201343C(void);
extern void FUN_02013194(void *, u32, u32, u32);
extern u32 FUN_0201318C(u32, u32, u32);

//todo funcs
void MOD63_021DB720();
void MOD63_021DB784();
void MOD63_021DB7D0();
void MOD63_021DB838();
void MOD63_021DB884();
void MOD63_021DB8E8();

//todo data
const u32 MOD63_021DBEC0[3] = {0x703, 0x7CE, 0x8A8};
const struct UnkStruct63_021DBEF0 MOD63_021DBEF0[3];

THUMB_FUNC u32 MOD63_021DB450(u32 param0, u32 param1)
{
    u32 res0 = (UNK_021064B8)(param0, param1, 0);
    FUN_0201327C(res0);
    GF_ASSERT(res0);
    return (u32)((u16)res0 * 8);
}

THUMB_FUNC u32 MOD63_021DB474(u32 param0, u32 param1)
{
    u32 res0 = (UNK_021064C0)(param0, param1, 1);
    GF_ASSERT(res0);
    FUN_020132BC(res0);
    return (u32)((u16)res0 * 8);
}

THUMB_FUNC u32 MOD63_021DB498(void)
{
    return 32;
}

THUMB_FUNC void Title_SetupMonAnimationSprites(struct UnkStruct63_021DB49C * arg0)
{
    struct UnkStruct63_021DB49C_2 sp1C;
    int introMonArray[3] = {SPECIES_TURTWIG, SPECIES_CHIMCHAR, SPECIES_PIPLUP};

    arg0->field_00 = FUN_02006D98(76);

    for (u8 i = 0; i < 3; i++) //some kind of animation assignment TODO: investigate further
    {
        FUN_02068C00(&sp1C, (u16)introMonArray[i], 0, 2, 0, 0, 0);
        arg0->field_04[i] = FUN_020073A0(arg0->field_00, &sp1C, MOD63_021DBEF0[i].field_00, MOD63_021DBEF0[i].field_04, 0x3FF, i, 0, 0);
        FUN_02007558(arg0->field_04[i], 6, 1);
    }
    FUN_02007558(arg0->field_04[1], 35, 1);
    arg0->field_10 = 1;
    FUN_02012CC8();
    arg0->field_14 = AllocFromHeap(0x4C, 0x4800);
    arg0->field_18 = FUN_02012CDC(MOD63_021DB450, MOD63_021DB474, arg0->field_14, 0x4800, 1, 0x4C);
    FUN_0201EC94(0x1000, 0x384000, FUN_0201343C());
    FUN_02013194(arg0->field_18, FUN_0201318C(0x3D, 4, 0x4C), 10, 1);
}

void * const MOD63_021DBED8 = MOD63_021DB720;
void * const MOD63_021DBEDC[5] = { MOD63_021DB784, MOD63_021DB7D0, MOD63_021DB838, MOD63_021DB884, MOD63_021DB8E8 };

const struct UnkStruct63_021DBEF0 MOD63_021DBEF0[3] = {
        {0x080, 0xC0},
        {0x100, 0xC0},
        {0x050, 0xC0}
};
