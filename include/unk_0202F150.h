#ifndef POKEDIAMOND_UNK_0202F150_H
#define POKEDIAMOND_UNK_0202F150_H

#include "global.h"
#include "MI_memory.h"
#include "RTC_api.h"
#include "heap.h"
#include "main.h"
#include "unk_0202D858.h"
#include "unk_02031480.h"

struct UnkStruct0202F150_sub1
{
    u32 unk00;
    s16 unk04;
    s16 unk06;
    u32 unk08;
};

struct UnkStruct0202F150_sub2
{
    u32 unk00;
    void *unk04;
    u16 unk08;
    u8 unk0a;
};

struct UnkStruct0202F150
{
    u8 unk000[2][38];
    u8 unk04c[264];
    u8 unk154[2][192];
    u8 unk2D4[384];
    void *unk454;
    void *unk458;
    void *unk45C;
    void *unk460;
    struct UnkStruct0202F150_sub1 unk464;
    struct UnkStruct0202F150_sub1 unk470;
    struct UnkStruct0202F150_sub1 unk47C[8];
    struct UnkStruct0202F150_sub1 unk4DC;
    struct UnkStruct0202F150_sub1 unk4E8[8];
    u32 unk548;
    u8 unk54C[32];
    u8 unk56C[32];
    struct UnkStruct0202F150_sub2 unk58C[8];
    u32 unk5EC;
    u32 unk5F0;
    u16 unk5F4;
    u8 unk5F6;
    u8 unk5F7;
    s64 unk5F8[3];
    u16 unk610[8];
    u8 unk620[0x8];
    u16 unk628;
    u8 unk62A;
    u8 unk62B;
    u8 unk62C;
    s8 unk62D;
    u16 unk62E;
    u32 unk630;
    u32 unk634;
    u32 unk638[8];
    u32 unk658;
    u16 unk65C;
    u8 unk65E;
    u8 unk65F[8];
    u8 unk667[8];
    u8 unk66F[8];
    u8 unk677[4];
    u8 unk67B;
    u8 unk67C;
    u8 unk67D;
    u8 unk67E;
    u8 unk67F;
    u8 unk680;
    u8 unk681;
    u8 unk682;
    u8 unk683;
    u8 unk684;
    u8 unk685;
    u8 unk686;
    u8 unk687;
    u8 unk688;
    u8 unk689;
    u8 unk68A;
    u8 unk68B;
};

THUMB_FUNC u32 FUN_0202F150(u32 param0, u32 param1);
THUMB_FUNC void FUN_0202F2F0();
THUMB_FUNC void FUN_0202F5A4();
THUMB_FUNC void FUN_0202F820(int param0);
THUMB_FUNC void FUN_0202F8D4();
THUMB_FUNC void FUN_0202F910(int param0);
THUMB_FUNC u32 FUN_0202F918(u32 param0, u32 param1, u32 param2, u32 param3);
THUMB_FUNC u32 FUN_0202F950(u32 param0, u32 param1, u32 param2);
THUMB_FUNC void FUN_0202F984();
THUMB_FUNC void FUN_0202F9E0(u32 param0);
THUMB_FUNC void FUN_0202FA10();
THUMB_FUNC void FUN_0202FA1C();
THUMB_FUNC u8 FUN_0202FA28();
THUMB_FUNC u32 FUN_0202FA48();
THUMB_FUNC void FUN_0202FA5C();
THUMB_FUNC u32 FUN_0202FB18(u32 param0);
THUMB_FUNC void FUN_0202FB20();
THUMB_FUNC void FUN_0202FB58();
THUMB_FUNC u32 FUN_0202FB80();
THUMB_FUNC void FUN_0202FC60();
THUMB_FUNC void FUN_0202FC80();
THUMB_FUNC void FUN_0202FCA8();
THUMB_FUNC void FUN_0202FCCC();
THUMB_FUNC u32 FUN_0202FE2C(int param0);
THUMB_FUNC void FUN_0202FEEC();
THUMB_FUNC void FUN_02030074();
THUMB_FUNC void FUN_02030238(u32 param0, void *param1, u32 param2);
THUMB_FUNC void FUN_0203026C(u32 param0, u8 *param1, u32 param2);
THUMB_FUNC void FUN_020303BC(u32 param0, u8 *param1, u16 param2);
THUMB_FUNC void FUN_020303F4(u32 param0, u8 *param1, u16 param2);
THUMB_FUNC void FUN_020304D4(u32 param0);
THUMB_FUNC void FUN_020304F0(u32 param0);
THUMB_FUNC void FUN_0203050C();
THUMB_FUNC void FUN_02030674();
THUMB_FUNC void FUN_020307A8();
THUMB_FUNC void FUN_020307BC();
THUMB_FUNC void FUN_020307D0();
THUMB_FUNC u32 FUN_020307E4(u8 *param0, u32 param1);
THUMB_FUNC void FUN_0203086C();
THUMB_FUNC u32 FUN_02030870(u8 *param0);
THUMB_FUNC u32 FUN_02030930(u8 *param0);
THUMB_FUNC void FUN_02030A00(u8 *param0);
THUMB_FUNC u32 FUN_02030A78(u32 param0, u8 *param1, u32 param2);
THUMB_FUNC u32 FUN_02030ADC(u32 param0, u8 *param1, u32 param2);
THUMB_FUNC u32 FUN_02030B3C(u32 param0, u8 *param1, u32 param2);
THUMB_FUNC u32 FUN_02030BC4(u32 param0, u8 *param1, u32 param2);
THUMB_FUNC u32 FUN_02030C4C(u32 param0, u8 *param1);
THUMB_FUNC int FUN_02030C58();
THUMB_FUNC void FUN_02030C70(
    u32 param0, u32 param1, u32 param2, void *param3, struct UnkStruct0202F150_sub2 *param4);
THUMB_FUNC void FUN_02030C8C(struct UnkStruct0202F150_sub1 *param0,
    u32 param1,
    void *param2,
    u32 param3,
    struct UnkStruct0202F150_sub2 *param4);
THUMB_FUNC void FUN_02030DA4();
THUMB_FUNC void FUN_02030DFC();
THUMB_FUNC u32 FUN_02030E7C(u16 param0);
THUMB_FUNC u32 FUN_02030F20();
THUMB_FUNC u32 FUN_02030F40();
THUMB_FUNC void FUN_02030F60(u8 param0);
THUMB_FUNC u8 FUN_02030F74(u32 param0);
THUMB_FUNC u32 FUN_02030F88(u32 param0);
THUMB_FUNC void FUN_02030FA8();
THUMB_FUNC void FUN_02030FC8();
THUMB_FUNC u32 FUN_02030FE0();
THUMB_FUNC void FUN_02031000(u32 param0, u8 *param1, u32 param2);
THUMB_FUNC void FUN_0203105C(u32 param0, u8 *param1, u32 param2);
THUMB_FUNC void FUN_02031088();
THUMB_FUNC void FUN_0203110C(u32 param0, u32 param1, u8 *param2);
THUMB_FUNC void FUN_02031134(u32 param0, u32 param1, u8 *param2);
THUMB_FUNC void FUN_0203115C(u32 param0, u32 param1, u8 *param2);
THUMB_FUNC u16 FUN_02031190();
THUMB_FUNC u32 FUN_020311D0(u32 param0, u8 *param1);
THUMB_FUNC u32 FUN_020311DC(u32 param0);
THUMB_FUNC u32 FUN_020311E8();
THUMB_FUNC u32 FUN_020311F0();
THUMB_FUNC int FUN_02031228(u16 param0);
THUMB_FUNC int FUN_02031248(u32 param0);
THUMB_FUNC int FUN_02031258(u32 param0);
THUMB_FUNC void FUN_02031268(u8 param0);
THUMB_FUNC u8 FUN_02031280();
THUMB_FUNC void FUN_0203129C();
THUMB_FUNC void FUN_020312BC(s64 *param0);
THUMB_FUNC void FUN_02031354(u32 param0);
THUMB_FUNC u32 FUN_02031370();
THUMB_FUNC u32 FUN_02031388();
THUMB_FUNC void FUN_020313A0(u8 param0);
THUMB_FUNC void FUN_020313B4(u8 param0, u32 param1);
THUMB_FUNC u32 FUN_020313CC(u32 param0);
THUMB_FUNC u32 FUN_020313EC();
THUMB_FUNC void FUN_02031400(u32 param0);
THUMB_FUNC u32 FUN_02031438();
THUMB_FUNC void FUN_02031454();
THUMB_FUNC void FUN_02031468();

#endif // POKEDIAMOND_UNK_0202F150_H
