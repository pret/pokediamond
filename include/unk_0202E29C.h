#ifndef POKEDIAMOND_UNK_0202E29C_H
#define POKEDIAMOND_UNK_0202E29C_H

#include "global.h"
#include "mail_message.h"
#include "player_data.h"

struct UnkStruct_0202E29C_sub4
{
    u32 unk00;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    u8 unk08[8];
    PlayerProfile unk10;
    u8 unk30[0x40];
};

struct UnkStruct_0202E29C_sub
{
    u32 unk00;
    u8 unk04[6];
    u8 unk0A[0x2C];
    u16 unk36;
    u8 unk38[0x18];
    struct UnkStruct_0202E29C_sub4 unk50;
};

struct UnkStruct_0202E29C_sub3
{
    struct MailMessage unk00;
    PlayerProfile unk08;
    u8 unk28[0x20];
    u8 unk48[0x4];
    u8 unk4C;
    u8 unk4D[7];
};

struct UnkStruct_0202E29C_sub2
{
    u32 unk00;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    struct UnkStruct_0202E29C_sub3 unk08;
};

struct UnkStruct_0202E29C
{
    struct UnkStruct_0202E29C_sub3 unk000;
    struct UnkStruct_0202E29C_sub unk054[16];
    u8 unkC54[8][6];
    u16 unkC84[16];
    void *unkCA4;
    struct MailMessage unkCA8;
    u32 unkCB0;
    u8 unkCB4;
    PlayerProfile *unkCB8;
    void *unkCBC;
    u32 unkCC0;
    struct UnkStruct_0202E29C_sub2 unkCC4;
    u8 unkD20[0x84];
    u16 unkDA4;
    u16 unkDA6;
    u8 unkDA8;
    u8 unkDA9;
    u8 unkDAA;
    u8 unkDAB;
    u8 unkDAC;
    u8 unkDAD_0:1;
    u8 unkDAD_1:1;
    u8 unkDAD_2:1;
    u8 unkDAD_3:1;
    u8 unkDAD_4:1;
    u8 unkDAD_5:1;
    u8 unkDAE[0x2];
};

void sub_0202E29C(PlayerProfile *player_data);
BOOL sub_0202E344();
BOOL sub_0202E358(u8 *param0, u8 *param1, s32 param2);
void sub_0202E380(struct UnkStruct_0202E29C_sub *param0, u32 param1);
void sub_0202E470(u32 param0, u32 param1);
void sub_0202E488();
void sub_0202E49C();
BOOL sub_0202E4C8();
BOOL sub_0202E4DC();
void sub_0202E4F0();
void sub_0202E500();
void sub_0202E538();
void sub_0202E56C(u32 param0);
void sub_0202E594();
BOOL sub_0202E5F8(u32 param0, u32 param1, u32 param2);
u32 sub_0202E66C(u32 param0, u32 param1);
u32 sub_0202E6F0();
BOOL sub_0202E784();
void sub_0202E7B0(u32 param0);
void sub_0202E7D8();
u32 sub_0202E810();
s32 sub_0202E844(u32 param0);
u8 sub_0202E878();
void sub_0202E88C();
s32 sub_0202E8A0(s32 param0);
s32 sub_0202E8D0(s32 param0);
s32 sub_0202E8F4();
s32 sub_0202E950();
void sub_0202E9AC(u32 param0, PlayerProfile *player_data);
u32 sub_0202E9E8(u32 param0);
void sub_0202EA54();
void sub_0202EA9C();
void sub_0202EB7C();
void sub_0202EBD0(u16 param0);
void sub_0202ED70(u16 param0);
u32 sub_0202ED84(u16 param0);
u32 sub_0202EDB8();
BOOL sub_0202EDD8();
BOOL sub_0202EDF8();
u32 sub_0202EE0C();
u32 sub_0202EE24();
BOOL sub_0202EE44();
BOOL sub_0202EE60();
void sub_0202EE84(u32 param0);
void sub_0202EEB0(u32 param0);
u16 sub_0202EEE8(u16 param0);
struct UnkStruct_0202E29C_sub *sub_0202EF18(u32 param0);
struct UnkStruct_0202E29C_sub4 *sub_0202EF44(s32 param0);
PlayerProfile *sub_0202EF70();
PlayerProfile *sub_0202EF84(int param0);
void sub_0202EFAC(u8 *param0, s32 param1);
BOOL sub_0202EFE4(u8 *param0);
u32 sub_0202F03C();
void sub_0202F05C();
void sub_0202F078(struct MailMessage *mail_message);
void sub_0202F094(void *param0);
void sub_0202F0B8();
u32 sub_0202F0DC(u8 param0);
BOOL sub_0202F104();
void sub_0202F10C(struct UnkStruct_0202E29C_sub3 *param0);
u8 *sub_0202F124(u32 param0);

#endif // POKEDIAMOND_UNK_0202E29C_H
