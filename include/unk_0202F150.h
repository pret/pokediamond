#ifndef POKEDIAMOND_UNK_0202F150_H
#define POKEDIAMOND_UNK_0202F150_H

#include "global.h"

#include "MI_memory.h"
#include "RTC_api.h"
#include "heap.h"
#include "main.h"
#include "unk_0202D858.h"
#include "unk_02031480.h"

struct UnkStruct0202F150_sub1 {
    u32 unk00;
    s16 unk04;
    s16 unk06;
    u32 unk08;
};

struct UnkStruct0202F150_sub2 {
    u32 unk00;
    void *unk04;
    u16 unk08;
    u8 unk0a;
};

struct UnkStruct0202F150 {
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

u32 sub_0202F150(u32 param0, u32 param1);
void sub_0202F2F0();
void sub_0202F5A4();
void sub_0202F820(int param0);
void sub_0202F8D4();
void sub_0202F910(int param0);
BOOL sub_0202F918(u32 param0, u32 param1, u32 param2, u32 param3);
u32 sub_0202F950(u32 param0, u32 param1, u32 param2);
void sub_0202F984();
void sub_0202F9E0(u32 param0);
void sub_0202FA10();
void sub_0202FA1C();
u8 sub_0202FA28();
u32 sub_0202FA48();
void sub_0202FA5C();
u32 sub_0202FB18(u32 param0);
void sub_0202FB20();
void sub_0202FB58();
BOOL sub_0202FB80();
void sub_0202FC60();
void sub_0202FC80();
void sub_0202FCA8();
void sub_0202FCCC();
BOOL sub_0202FE2C(int param0);
void sub_0202FEEC();
void sub_02030074();
void sub_02030238(u32 param0, u8 *param1, u32 param2);
void sub_0203026C(u32 param0, u8 *param1, u32 param2);
void sub_020303BC(u32 param0, u8 *param1, u32 param2);
void sub_020303F4(u32 param0, u8 *param1, u32 param2);
void sub_020304D4(u32 param0);
void sub_020304F0(u32 param0);
void sub_0203050C();
void sub_02030674();
void sub_020307A8();
void sub_020307BC();
void sub_020307D0();
u32 sub_020307E4(u8 *param0, u32 param1);
void sub_0203086C();
u32 sub_02030870(u8 *param0);
u32 sub_02030930(u8 *param0);
void sub_02030A00(u8 *param0);
u32 sub_02030A78(u32 param0, u8 *param1, u32 param2);
u32 sub_02030ADC(u32 param0, u8 *param1, u32 param2);
u32 sub_02030B3C(u32 param0, u8 *param1, u32 param2);
u32 sub_02030BC4(u32 param0, u8 *param1, u32 param2);
u32 sub_02030C4C(u32 param0, u8 *param1);
int sub_02030C58();
void sub_02030C70(
    u32 param0, u32 param1, u32 param2, void *param3, struct UnkStruct0202F150_sub2 *param4);
void sub_02030C8C(struct UnkStruct0202F150_sub1 *param0,
    u32 param1,
    void *param2,
    u32 param3,
    struct UnkStruct0202F150_sub2 *param4);
void sub_02030DA4();
void sub_02030DFC();
BOOL sub_02030E7C(u16 param0);
s32 sub_02030F20();
BOOL sub_02030F40();
void sub_02030F60(u8 param0);
u8 sub_02030F74(u32 param0);
u32 sub_02030F88(u32 param0);
void sub_02030FA8();
void sub_02030FC8();
u32 sub_02030FE0();
void sub_02031000(u32 param0, u8 *param1, u32 param2);
void sub_0203105C(u32 param0, u8 *param1, u32 param2);
void sub_02031088();
void sub_0203110C(u32 param0, u32 param1, u8 *param2);
void sub_02031134(u32 param0, u32 param1, u8 *param2);
void sub_0203115C(u32 param0, u32 param1, u8 *param2);
u16 sub_02031190();
u32 sub_020311D0(u32 param0, u8 *param1);
u32 sub_020311DC(u32 param0);
u32 sub_020311E8();
BOOL sub_020311F0();
int sub_02031228(u16 param0);
int sub_02031248(u32 param0);
int sub_02031258(u32 param0);
void sub_02031268(u8 param0);
u8 sub_02031280();
void sub_0203129C();
void sub_020312BC(s64 *param0);
void sub_02031354(u32 param0);
u32 sub_02031370();
u32 sub_02031388();
void sub_020313A0(u8 param0);
void sub_020313B4(u8 param0, u32 param1);
u32 sub_020313CC(u32 param0);
u32 sub_020313EC();
void sub_02031400(u32 param0);
u32 sub_02031438();
void sub_02031454();
void sub_02031468();

#endif // POKEDIAMOND_UNK_0202F150_H
