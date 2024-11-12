#include "ov63_021DB450.h"

#include "global.h"

#include "constants/species.h"

#include "camera.h"
#include "gx.h"
#include "heap.h"
#include "unk_02006D98.h"

// todo resolve to static code
extern u32 (*NNS_GfdDefaultFuncAllocTexVram)(u32 param0, u32 param1, u32 param2);
extern u32 (*NNS_GfdDefaultFuncAllocPlttVram)(u32 param0, u32 param1, u32 param2);

extern void sub_0201327C(u32 param0);
extern void sub_020132BC(u32 param0);

extern void *sub_02012CDC(void *, void *, void *, u32, u32, HeapID);

extern void sub_02068C00(struct UnkStruct_02006D98_4 *, u16, u32, u32, u32, u32, u32);
extern void sub_02012CC8(void);
extern struct Camera *sub_0201343C(void);
extern void sub_02013194(void *, u32, u32, u32);
extern u32 sub_0201318C(u32, u32, HeapID);

extern void sub_02012DE4(void *);

extern void sub_020222AC(void);
extern void NNS_G2dSetupSoftwareSpriteCamera(void);
extern void sub_020222B4(u32, u32);

extern void sub_02013440(void *, u32);
extern void sub_020133AC(void *, u32, const void *, struct UnkStruct_02006D98_2 *);
extern BOOL sub_020133C8(void *);

extern void sub_02013364(void);
extern void sub_02013388(void);

struct UnkStruct_02006D98_2 *sub_0201341C(struct UnkStruct63_021DB450 *);

const s32 ov63_021DBEC0[3] = { 0x703, 0x7CE, 0x8A8 };
const struct UnkStruct63_021DBEF0 ov63_021DBEF0[3];

u32 ov63_021DB450(u32 param0, u32 param1) {
    u32 res0 = (NNS_GfdDefaultFuncAllocTexVram)(param0, param1, 0);
    sub_0201327C(res0);
    GF_ASSERT(res0);
    return (u32)((u16)res0 * 8);
}

u32 ov63_021DB474(u32 param0, u32 param1) {
    u32 res0 = (NNS_GfdDefaultFuncAllocPlttVram)(param0, param1, 1);
    GF_ASSERT(res0);
    sub_020132BC(res0);
    return (u32)((u16)res0 * 8);
}

u32 ov63_021DB498(void) {
    return 32;
}

void Title_SetupMonAnimationSprites(struct UnkStruct63_021DB450 *arg0) // TODO: this does a lot more than setup anim sprites
{
    struct UnkStruct_02006D98_4 sp1C;
    int introMonArray[3] = { SPECIES_TURTWIG, SPECIES_CHIMCHAR, SPECIES_PIPLUP };

    arg0->field_00 = sub_02006D98(HEAP_ID_76); // this is needed to get into the world view, otherwise it is just black

    for (u8 i = 0; i < 3; i++) // some kind of animation assignment TODO: investigate further
    {
        sub_02068C00(&sp1C, (u16)introMonArray[i], 0, 2, 0, 0, 0);
        arg0->field_04[i] = sub_020073A0(arg0->field_00, &sp1C, ov63_021DBEF0[i].field_00, ov63_021DBEF0[i].field_04, 0x3FF, i, 0, 0);
        sub_02007558(arg0->field_04[i], 6, 1);
    }
    sub_02007558(arg0->field_04[1], 35, 1);
    arg0->field_10 = 1;
    sub_02012CC8();
    arg0->field_14 = AllocFromHeap(HEAP_ID_76, 0x4800);
    arg0->field_18 = sub_02012CDC(ov63_021DB450, ov63_021DB474, arg0->field_14, 0x4800, 1, HEAP_ID_76);
    Camera_SetPerspectiveClippingPlane(0x1000, 0x384000, sub_0201343C());
    sub_02013194(arg0->field_18, sub_0201318C(0x3D, 4, HEAP_ID_76), 10, 1);
}

void ov63_021DB580(UnkStruct63_021DB450 *param0) {
    sub_02012DE4(param0->field_18);
    FreeToHeap(param0->field_14);
    sub_020072E8(param0->field_00);
}

void ov63_021DB598(UnkStruct63_021DB450 *param0) {
    if (param0 == NULL) {
        return;
    }
    sub_020081C4(param0->field_00);
}

void ov63_021DB5A8(UnkStruct63_021DB450 *param0) {
    if (param0 == NULL) {
        return;
    }
    sub_020222AC();
    NNS_G2dSetupSoftwareSpriteCamera();
    sub_02006ED4(param0->field_00);
    ov63_021DB934();
    sub_020222B4(1, 0);
}

const struct UnkStruct63_021DBED8 ov63_021DBED8[3] = {
    { ov63_021DB720, ov63_021DB784 },
    { ov63_021DB7D0, ov63_021DB838 },
    { ov63_021DB884, ov63_021DB8E8 }
};

const struct UnkStruct63_021DBEF0 ov63_021DBEF0[3] = {
    { 0x080, 0xC0 },
    { 0x100, 0xC0 },
    { 0x050, 0xC0 }
};

const struct UnkStruct63_021DBEF0 ov63_021DBF08[3] = {
    //  no idea if this is the right type
    { 4, 5 },
    { 2, 3 },
    { 0, 1 }
};

BOOL ov63_021DB5CC(UnkStruct63_021DB450 *param0, u32 param1, s32 param2) {
    u8 *state = &param0->field_1C;
    switch (*state) {
    case 0:
        G2_SetWndOutsidePlane(GX_WND_PLANEMASK_OBJ | GX_WND_PLANEMASK_BG0, TRUE);
        sub_02007558(param0->field_04[param1], 12, 0x400);
        sub_02007558(param0->field_04[param1], 13, 0x400);
        sub_02007558(param0->field_04[param1], 6, 0);
        (*state)++;
        // fallthrough
    case 1:
        if (ov63_021DBED8[param1].unk_00(param0, param1)) {
            param0->field_1D = 0;
            (*state)++;
        }
        break;
    case 2:
        sub_02013440(param0->field_18, 1);
        sub_020133AC(param0->field_18, ov63_021DBF08[param1].field_00, ov63_021DB940, param0->field_04[param1]);
        sub_020133AC(param0->field_18, ov63_021DBF08[param1].field_04, ov63_021DB940, param0->field_04[param1]);
        (*state)++;
        break;
    case 3:
        if (!sub_020133C8(param0->field_18) && param2 >= ov63_021DBEC0[param1]) {
            G2_SetWndOutsidePlane(GX_WND_PLANEMASK_OBJ, TRUE);
            (*state)++;
        }
        break;
    case 4:
        if (ov63_021DBED8[param1].unk_04(param0, param1)) {
            sub_02007558(param0->field_04[param1], 6, 1);
            param0->field_1D = 0;
            (*state)++;
        }
        break;
    case 5:
        param0->field_1D++;
        if (param0->field_1D >= 20) {
            param0->field_1D = 0;
            *state = 0;
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL ov63_021DB720(UnkStruct63_021DB450 *param0, u32 param1) {
    struct UnkStruct_02006D98_2 *field = param0->field_04[param1];
    sub_020079E0(field, 0x0, 0x6);
    sub_020079E0(field, 0x1, -0x10);
    sub_020079E0(field, 0xC, -0x80);
    sub_020079E0(field, 0xD, -0x80);
    param0->field_1D++;
    if (param0->field_1D >= 6) {
        sub_02007558(field, 0xC, 0x100);
        sub_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

BOOL ov63_021DB784(UnkStruct63_021DB450 *param0, u32 param1) {
    struct UnkStruct_02006D98_2 *field = param0->field_04[param1];
    sub_020079E0(field, 0x0, -0x3);
    sub_020079E0(field, 0x1, -0x12);
    param0->field_1D++;
    if (param0->field_1D >= 6) {
        sub_02007558(field, 0xC, 0x100);
        sub_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

BOOL ov63_021DB7D0(UnkStruct63_021DB450 *param0, u32 param1) {
    struct UnkStruct_02006D98_2 *field = param0->field_04[param1];
    sub_020079E0(field, 0x0, -0x10);
    sub_020079E0(field, 0x1, -0x10);
    sub_020079E0(field, 0xC, -0x80);
    sub_020079E0(field, 0xD, -0x80);
    param0->field_1D++;
    if (param0->field_1D >= 6) {
        sub_02007558(field, 0xC, 0x100);
        sub_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

BOOL ov63_021DB838(UnkStruct63_021DB450 *param0, u32 param1) {
    struct UnkStruct_02006D98_2 *field = param0->field_04[param1];
    sub_020079E0(field, 0, -0x6);
    sub_020079E0(field, 1, -0x10);
    param0->field_1D++;
    if (param0->field_1D >= 6) {
        sub_02007558(field, 0xC, 0x100);
        sub_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

BOOL ov63_021DB884(UnkStruct63_021DB450 *param0, u32 param1) {
    struct UnkStruct_02006D98_2 *field = param0->field_04[param1];
    sub_020079E0(field, 0, 0x8);
    sub_020079E0(field, 1, -0x10);
    sub_020079E0(field, 0xC, -0x80);
    sub_020079E0(field, 0xD, -0x80);
    param0->field_1D++;
    if (param0->field_1D >= 6) {
        sub_02007558(field, 0xC, 0x100);
        sub_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

BOOL ov63_021DB8E8(UnkStruct63_021DB450 *param0, u32 param1) {
    struct UnkStruct_02006D98_2 *field = param0->field_04[param1];
    sub_020079E0(field, 0, 0x6);
    sub_020079E0(field, 1, -0x14);
    param0->field_1D++;
    if (param0->field_1D >= 6) {
        sub_02007558(field, 0xC, 0x100);
        sub_02007558(field, 0xD, 0x100);
        return TRUE;
    }
    return FALSE;
}

void ov63_021DB934(void) {
    sub_02013364();
    sub_02013388();
}

void ov63_021DB940(struct UnkStruct63_021DB450 *a0) {
    struct UnkStruct_02006D98_2 *r4 = sub_0201341C(a0);
    int sp0[3] = { 0, 0, 0 };
    sp0[0] = (sub_0200782C(r4, 0) - 0x80) * 0xAC;
    sp0[1] = (sub_0200782C(r4, 1) - 0x60) * 0xAC;
    sp0[2] = 0x40;
    a0->field_28 = sp0[0] + (*a0->field_20)[1];
    a0->field_2C = sp0[1] + (*a0->field_20)[2];
    a0->field_30 = sp0[2] + (*a0->field_20)[3];
}
