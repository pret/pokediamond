#ifndef POKEDIAMOND_UNK_02016B94_H
#define POKEDIAMOND_UNK_02016B94_H

#include "global.h"
#include "GX_layers.h"
#include "MI_uncompress.h"
#include "OS_cache.h"
#include "gx.h"
#include "heap.h"
#include "math_util.h"

struct UnkStruct1
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;

    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17; // probably paddding
    u32 unk18;
};

struct UnkStruct2
{
    u32 unk00;
    u16 unk04;
    u16 unk06;

    struct InnerStruct
    {
        void *unk08;
        u32 unk0c;
        u32 unk10;

        u32 unk14;
        u32 unk18;

        u8 unk1c;
        u8 unk1d;
        u8 unk1e;
        u8 unk1f;
        u16 unk20;
        u16 unk22; // probably padding
        u32 unk24;
        u32 unk28;
        u32 unk2c;
        u32 unk30;
    } unk08[8];
};

struct UnkStruct3
{
    void *unk00;
    u16 unk04;
    u16 unk06;
};

struct UnkStruct4
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6;
};

struct Window
{
    struct UnkStruct2 *unk00;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    u8 unk08;
    u8 unk09;
    u16 unk0a : 15;
    u16 unk0b : 1;
    void *unk0c;
};

void *FUN_02016B94(u32 heap_id);
u32 FUN_02016BB8(u32 *param0);
void FUN_02016BBC(u32 *param0);
void FUN_02016BF4(u32 *param0, u32 param1);
void FUN_02016C18(struct UnkStruct2 *param0, u8 param1, struct UnkStruct1 *param2, u8 param3);
void FUN_020170F4(struct UnkStruct2 *param0, u8 param1, u32 param2, u8 param3);
u8 FUN_020177DC(u8 param0, u32 param1);
void FUN_02017850(u32 param0, u8 *param1, u8 *param2);
void FUN_020178A0(struct UnkStruct2 *param0, u32 param1);
void FUN_020178BC(u32 param0, u32 param1);
void FUN_0201797C(u32 param0, GX_LayerToggle toggle);
void FUN_020179E0(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 val);
u32 FUN_02017B48(struct UnkStruct2 *param0, u32 param1);
u32 FUN_02017B54(struct UnkStruct2 *param0, u32 param1);
void FUN_02017B60(struct UnkStruct2 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6);
void FUN_02017B8C(struct InnerStruct *param0, u32 param1, u32 val);
void FUN_02017BD0(
    struct UnkStruct2 *param0, u32 param1, struct Mtx22 *param2, fx32 param3, fx32 param4);
void FUN_02017C6C(struct UnkStruct2 *param0, u32 param1);
void FUN_02017C98(const void *param0, void *param1, u32 param2);
void FUN_02017CD0(struct UnkStruct2 *param0, u32 param1);
void FUN_02017CE8(struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4);
void FUN_02017D68(u32 param0, void *param1, u32 offset, u32 size);
void FUN_02017DFC(struct UnkStruct2 *param0, u32 param1, void *param2, u32 param3);
void FUN_02017E14(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3, u32 param4);
void FUN_02017E40(struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4);
void FUN_02017E84(u32 param0, void *param1, u32 offset, u32 size);
void FUN_02017F18(u32 param0, u32 size, u32 offset, u32 heap_id);
void FUN_02017F48(struct UnkStruct2 *param0, u32 param1, u32 *param2, u32 param3, u32 param4);
void FUN_02017FB4(u32 param0, void *param1, u32 offset, u32 size);
void FUN_02017FE4(u32 param0, u32 param1);
u16 FUN_02017FFC(u8 param0, u8 param1, u8 param2);
u16 FUN_02018068(u8 param0, u8 param1, u8 param2, u8 param3);
void FUN_02018148(
    struct UnkStruct2 *param0, u32 param1, u32 *param2, u8 param3, u8 param4, u8 param5, u8 param6);
void FUN_02018170(struct UnkStruct2 *param0,
    u32 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u32 *param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10);
void FUN_020181EC(struct UnkStruct2 *param0,
    u32 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u32 *param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10);
void FUN_02018268(struct InnerStruct *param0,
    u8 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u16 *param5,
    u8 param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10);
void FUN_020183DC(struct InnerStruct *param0,
    u8 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 *param5,
    u8 param6,
    u8 param7,
    u8 param8,
    u8 param9,
    u8 param10);
void FUN_02018540(struct UnkStruct2 *param0,
    u32 param1,
    u16 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7);
void FUN_02018590(
    struct InnerStruct *param0, u16 param1, u8 param2, u8 param3, u8 param4, u8 param5, u8 param6);
void FUN_02018640(
    struct InnerStruct *param0, u8 param1, u8 param2, u8 param3, u8 param4, u8 param5);
void FUN_020186B4(
    struct UnkStruct2 *param0, u32 param1, u8 param2, u8 param3, u8 param4, u8 param5, u8 param6);
void FUN_02018744(struct UnkStruct2 *param0, u32 param1);
void FUN_02018768(struct UnkStruct2 *param0, u32 param1, u16 param2);
void FUN_0201878C(struct UnkStruct2 *param0, u32 param1, u16 param2);
void *FUN_020187B0(u32 param0);
void FUN_02018808(u8 *param0, u32 param1, u8 (*param2)[2], u8 param3);
u8 (*FUN_02018848(u8 *param0, u32 param1, u8 param2, u32 heap_id))[2];
void *FUN_0201886C(struct UnkStruct2 *param0, u32 param1);
u16 FUN_02018878(struct UnkStruct2 *param0, u32 param1);
u8 FUN_02018884(struct UnkStruct2 *param0, u32 param1);
void FUN_02018A60(struct UnkStruct3 *param0,
    struct UnkStruct3 *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8);
void FUN_02018CA0(struct UnkStruct3 *param0,
    struct UnkStruct3 *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8);
void FUN_02018E88(
    struct UnkStruct3 *param0, u16 param1, u16 param2, u16 param3, u16 param4, u8 param5);
void FUN_02018F4C(
    struct UnkStruct3 *param0, u16 param1, u16 param2, u16 param3, u16 param4, u8 param5);
void *FUN_02018FF4(u32 heap_id, s32 size);
void FUN_0201901C(struct Window *param0);
BOOL FUN_02019048(struct Window *param0);
void FUN_02019064(struct UnkStruct2 *param0,
    struct Window *param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7,
    u16 param8);
void FUN_020190EC(
    struct UnkStruct2 *param0, struct Window *param1, u8 param2, u8 param3, u16 param4, u8 param5);
void FUN_02019150(struct UnkStruct2 *param0, struct Window *param1, struct UnkStruct4 *param2);
void FUN_02019178(struct Window *param0);
void FUN_020191A4(struct Window *param0, int param1);
void CopyWindowToVram(struct Window *param0);
void FUN_02019220(struct Window *param0);
void FUN_02019270(struct Window *param0);
void FUN_0201928C(struct Window *param0, u8 param1, u8 param2);
void FUN_020192B8(struct Window *param0);
void FUN_020192D4(struct Window *param0);
void FUN_02019358(struct Window *param0);
void FUN_020193B4(struct Window *param0);
void FUN_02019444(struct Window *param0);
void FUN_0201949C(struct Window *window);
void FUN_020194C8(struct Window *window);
void FUN_020194E0(struct Window *window);
void FUN_0201951C(struct Window *window);
void FUN_02019548(struct Window *window);
void FUN_02019570(struct Window *window);
void FUN_0201958C(struct Window *window);
void FUN_020195A8(struct Window *window);
void FUN_020195D0(struct Window *window);
void FUN_020195E4(struct Window *window);
void FUN_0201960C(struct Window *window);
void FUN_02019620(struct Window *window, u8 param1);
void FUN_02019658(struct Window *window,
    void *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8,
    u16 param9);
void FUN_02019684(struct Window *window,
    void *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8,
    u16 param9,
    u16 param10);
void FUN_020196F4(struct Window *window, u8 param1, u16 param2, u16 param3, u16 param4, u16 param5);
void FUN_0201974C(
    struct Window *window, u32 *param1, u32 param2, u32 param3, u16 param4, u16 param5, u32 param6);
void FUN_0201A8C8(struct Window *window, u32 param1, u8 param2, u8 param3);
void FUN_0201A8E8(struct Window *window, u32 param1, u8 param2, u8 param3);
void FUN_0201A9D4(struct Window *window, u32 param1, u8 param2, u8 param3);
u8 FUN_0201AB08(struct Window *window);
u8 FUN_0201AB0C(struct Window *window);
u8 FUN_0201AB10(struct Window *window);
u8 FUN_0201AB14(struct Window *window);
u8 FUN_0201AB18(struct Window *window);
void FUN_0201AB1C(struct Window *window, u8 param1);
void FUN_0201AB20(struct Window *window, u8 param1);
void FUN_0201AB24(struct Window *window, u8 param1);
u32 FUN_0201AB28(struct Window *window, u32 heap_id, const char *path);
u32 FUN_0201AB44(struct Window *window, u32 heap_id, const char *path);
void FUN_0201AB60(struct UnkStruct2 *param0);
void FUN_0201AB78(struct UnkStruct2 *param0);
void FUN_0201AC68(struct UnkStruct2 *param0, u32 param1);
void FUN_0201AC78(struct UnkStruct2 *param0);
void FUN_0201AEE4(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3);
void FUN_0201AF08(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3);
void FUN_0201AF2C(struct InnerStruct *param0, u32 param1, u32 val);
void FUN_0201AF50(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3);
void FUN_0201AF74(struct InnerStruct *param0, u32 param1, u32 val);
u32 FUN_0201AFBC(struct UnkStruct2 *param0, u8 param1, u8 param2, u8 param3, u16 *param4);
void FUN_0201B118(struct UnkStruct2 *param0, u8 param1, u8 *param2);

#endif // POKEDIAMOND_UNK_02016B94_H
