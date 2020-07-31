#include "global.h"
#include "heap.h"
#include "constants/species.h"
#include "gx.h"
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

extern void FUN_02012DE4(u32);
extern void FUN_020072E8(u32);

extern void FUN_020081C4(u32);

extern void FUN_020222AC(void);
extern void FUN_020B02C8(void);
extern u32 FUN_02006ED4(u32 param0);
extern void FUN_020222B4(u32, u32);

extern void FUN_02013440(u32, u32);
extern void FUN_020133AC(u32, u32, const void *, u32);
extern BOOL FUN_020133C8(u32);

extern void FUN_020079E0(u32, u32, s32);

extern void FUN_02013364(void);
extern void FUN_02013388(void);

void * FUN_0201341C(struct UnkStruct_02090A58 *);
int FUN_0200782C(void *, int);

const s32 MOD63_021DBEC0[3] = {0x703, 0x7CE, 0x8A8};
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

THUMB_FUNC void MOD63_021DB580(UnkStruct63_021DB580 *param0)
{
    FUN_02012DE4(param0->field_24);
    FreeToHeap(param0->field_20);
    FUN_020072E8(param0->field_00);
}

THUMB_FUNC void MOD63_021DB598(UnkStruct63_021DB598 *param0)
{
    if (param0 == NULL)
    {
        return;
    }
    FUN_020081C4(param0->field_00);
}

THUMB_FUNC void MOD63_021DB5A8(UnkStruct63_021DB5A8 *param0)
{
    if (param0 == NULL)
    {
        return;
    }
    FUN_020222AC();
    FUN_020B02C8();
    (void)FUN_02006ED4(param0->field_00);
    MOD63_021DB934();
    FUN_020222B4(1, 0);
}

const struct UnkStruct63_021DBED8 MOD63_021DBED8[3] = {
        {MOD63_021DB720, MOD63_021DB784},
        {MOD63_021DB7D0, MOD63_021DB838},
        {MOD63_021DB884, MOD63_021DB8E8}
};

const struct UnkStruct63_021DBEF0 MOD63_021DBEF0[3] = {
        {0x080, 0xC0},
        {0x100, 0xC0},
        {0x050, 0xC0}
};

const struct UnkStruct63_021DBEF0 MOD63_021DBF08[3] = { //no idea if this is the right type
        {4, 5},
        {2, 3},
        {0, 1}
};

THUMB_FUNC BOOL MOD63_021DB5CC(UnkStruct63_021DB5CC *param0, u32 param1, s32 param2)
{
    u8 * state = &param0->field_1C;
    switch(*state)
    {
        case 0:
            G2_SetWndOutsidePlane(GX_WND_PLANEMASK_OBJ | GX_WND_PLANEMASK_BG0, TRUE);
            FUN_02007558(param0->field_04[param1], 12, 0x400);
            FUN_02007558(param0->field_04[param1], 13, 0x400);
            FUN_02007558(param0->field_04[param1], 6, 0);
            (*state)++;
            // fallthrough
        case 1:
            if (MOD63_021DBED8[param1].unk_00(param0, param1))
            {
                param0->field_1D = 0;
                (*state)++;
            }
            break;
        case 2:
            FUN_02013440(param0->field_18, 1);
            FUN_020133AC(param0->field_18, MOD63_021DBF08[param1].field_00, MOD63_021DB940, param0->field_04[param1]);
            FUN_020133AC(param0->field_18, MOD63_021DBF08[param1].field_04, MOD63_021DB940, param0->field_04[param1]);
            (*state)++;
            break;
        case 3:
            if (!FUN_020133C8(param0->field_18) && param2 >= MOD63_021DBEC0[param1])
            {
                G2_SetWndOutsidePlane(GX_WND_PLANEMASK_OBJ, TRUE);
                (*state)++;
            }
            break;
        case 4:
            if (MOD63_021DBED8[param1].unk_04(param0, param1))
            {
                FUN_02007558(param0->field_04[param1], 6, 1);
                param0->field_1D = 0;
                (*state)++;
            }
            break;
        case 5:
            param0->field_1D++;
            if (param0->field_1D >= 20)
            {
                param0->field_1D = 0;
                *state = 0;
                return TRUE;
            }
            break;
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD63_021DB720(UnkStruct63_021DB5CC *param0, u32 param1)
{
    u32 field = param0->field_04[param1];
    FUN_020079E0(field, 0x0, 0x6);
    FUN_020079E0(field, 0x1, -0x10);
    FUN_020079E0(field, 0xC, -0x80);
    FUN_020079E0(field, 0xD, -0x80);
    param0->field_1D++;
    if (param0->field_1D >= 6)
    {
        FUN_02007558(field, 0xC, 0x100);
        FUN_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD63_021DB784(UnkStruct63_021DB5CC *param0, u32 param1)
{
    u32 field = param0->field_04[param1];
    FUN_020079E0(field, 0x0, -0x3);
    FUN_020079E0(field, 0x1, -0x12);
    param0->field_1D++;
    if (param0->field_1D >= 6)
    {
        FUN_02007558(field, 0xC, 0x100);
        FUN_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD63_021DB7D0(UnkStruct63_021DB5CC *param0, u32 param1)
{
    u32 field = param0->field_04[param1];
    FUN_020079E0(field, 0x0, -0x10);
    FUN_020079E0(field, 0x1, -0x10);
    FUN_020079E0(field, 0xC, -0x80);
    FUN_020079E0(field, 0xD, -0x80);
    param0->field_1D++;
    if (param0->field_1D >= 6)
    {
        FUN_02007558(field, 0xC, 0x100);
        FUN_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD63_021DB838(UnkStruct63_021DB5CC *param0, u32 param1)
{
    u32 field = param0->field_04[param1];
    FUN_020079E0(field, 0, -0x6);
    FUN_020079E0(field, 1, -0x10);
    param0->field_1D++;
    if (param0->field_1D >= 6)
    {
        FUN_02007558(field, 0xC, 0x100);
        FUN_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD63_021DB884(UnkStruct63_021DB5CC *param0, u32 param1)
{
    u32 field = param0->field_04[param1];
    FUN_020079E0(field, 0, 0x8);
    FUN_020079E0(field, 1, -0x10);
    FUN_020079E0(field, 0xC, -0x80);
    FUN_020079E0(field, 0xD, -0x80);
    param0->field_1D++;
    if (param0->field_1D >= 6)
    {
        FUN_02007558(field, 0xC, 0x100);
        FUN_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL MOD63_021DB8E8(UnkStruct63_021DB5CC *param0, u32 param1)
{
    u32 field = param0->field_04[param1];
    FUN_020079E0(field, 0, 0x6);
    FUN_020079E0(field, 1, -0x14);
    param0->field_1D++;
    if (param0->field_1D >= 6)
    {
        FUN_02007558(field, 0xC, 0x100);
        FUN_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC void MOD63_021DB934(void)
{
    FUN_02013364();
    FUN_02013388();
}

THUMB_FUNC void MOD63_021DB940(struct UnkStruct_02090A58 * a0)
{
    void * r4 = FUN_0201341C(a0);
    int sp0[3] = {0, 0, 0};
    sp0[0] = (FUN_0200782C(r4, 0) - 0x80) * 0xAC;
    sp0[1] = (FUN_0200782C(r4, 1) - 0x60) * 0xAC;
    sp0[2] = 0x40;
    a0->unk_28 = sp0[0] + (*a0->unk_20)[1];
    a0->unk_2C = sp0[1] + (*a0->unk_20)[2];
    a0->unk_30 = sp0[2] + (*a0->unk_20)[3];
}
