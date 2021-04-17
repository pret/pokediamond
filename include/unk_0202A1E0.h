#ifndef POKEDIAMOND_UNK_0202A1E0_H
#define POKEDIAMOND_UNK_0202A1E0_H

#include "mail_message.h"
#include "save_block_2.h"

struct Unk0202A1F0
{
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
};

struct UnkMailStruct
{
    struct MailMessage messages[4];
};

struct Unk0202A240
{
    u8 u_0_0 : 1; // used
    u8 u_0_1 : 1; // used
    u8 u_0_2 : 3; // used
    u8 u_0_5 : 3; // used
    u8 u_1;
    u8 u_2; // used
    u8 u_3; // used
    u16 u_4; // used
    u16 u_6; // used
    s32 u_8; // used, cpu copy 4 bytes
    s32 u_C[7]; // used, cpu copy 28 bytes
    u32 u_28; // used
    s32 u_2C[4]; // used, cpu copy 16 bytes
};

struct Unk0202A3B4
{
    u16 u_0; // used
    u8 filler_0[6];
    u16 filler_1 : 4;
    u16 u_8_4 : 1; // used
};

struct Unk0202A40C
{
    u16 filler_0;
    u8 u_2; // used
    u8 filler_1[5];
    u16 filler_2 : 4;
    u16 u_8_4 : 1; // used
};

struct Unk0202A444
{
    u8 filler_0[3];
    u8 u_3; // used
};

struct Unk0202A4B8
{
    u8 filler[2];
    u8 u_2; // used
    u8 u_3; // used
    u16 u_4; // used
    u16 u_6; // used
    u16 filler_1[2];
    u16 u_array_C[5]; // used
    u16 u_16; // used
    u16 u_18; // used
};

struct Unk0202A5CC
{
    u32 filler;
    u32 u_4;
};


struct UnkSaveStruct_0202A5D4
{
    u32 filler[15];
    struct Unk0202A1F0 u_3C;
    u32 filler1[89];
    struct UnkMailStruct messages;
    u32 u_1C4;
};

struct Unk0202A670
{
    u32 b0;
    u8 b4; // used
};

struct Unk0202A68C
{
    u32 b0; // used
    u32 b4; // used
    u32 b8; // used
};

struct Unk0202A744_substruct1
{
    u8 data[0x63c];
}; // total size 0x63C (1596)

struct Unk0202A744_substruct2
{
    u8 data[0x3fc];
}; // total size 0x3FC (1020)

struct Unk0202A744
{
    u8 filler[254];
    u8 u_FE;
    u8 u_FF;
    u8 u_100;
    u8 u_101;
    u8 u_102;
    u8 u_103;
    struct Unk0202A744_substruct1 u_104;
    struct Unk0202A744_substruct2 u_740;
};

struct Unk0202A784
{
    u8 u_0;
    u8 u_1;
};

s32 FUN_0202A1E0();
void FUN_0202A1E4(void *dst);
void FUN_0202A1F0(struct Unk0202A1F0 *unk);
void FUN_0202A204(struct UnkMailStruct *unk);
void FUN_0202A230(void *dst);
u32 FUN_0202A240(struct Unk0202A240 *unk, u32 arg1, void *dst);
void FUN_0202A2C4(struct Unk0202A240 *dst, u32 arg1, void *src);
void FUN_0202A36C(struct Unk0202A240 *unk, s32 arg1, s32 arg2, s32 arg3);
u8 FUN_0202A398(struct Unk0202A240 *unk);
void FUN_0202A3A0(struct Unk0202A240 *unk, u16 arg1);
u16 FUN_0202A3B4(struct Unk0202A3B4 *unk, u16 arg1, s32 arg2);
u8 FUN_0202A40C(struct Unk0202A40C *unk, s32 arg1);
u8 FUN_0202A444(struct Unk0202A444 *unk, s32 arg1);
void FUN_0202A474(void *dst, s32 arg1, const void *src);
void FUN_0202A498(const void *src, s32 arg1, void *dst);
void FUN_0202A4B8(struct Unk0202A4B8 *arg0, struct Unk0202A4B8 *arg1);
u16 FUN_0202A520(struct Unk0202A4B8 *unk);
u8 FUN_0202A524(struct Unk0202A4B8 *unk);
u16 FUN_0202A538(struct Unk0202A4B8 *unk, s32 arg1, s32 arg2);
void FUN_0202A5CC(struct Unk0202A5CC *unk, u32 arg1);
u32 FUN_0202A5D0(struct Unk0202A5CC *unk);
void FUN_0202A5D4(struct SaveBlock2 *sav2, u32 arg1, struct MailMessage *arg2);
struct MailMessage *FUN_0202A5F4(struct SaveBlock2 *sav2, u32 arg1);
void FUN_0202A60C(u32 arg0, u32 arg1, u32 arg2, u32 arg3);
void FUN_0202A670(struct Unk0202A670 *arg0);
u32 FUN_0202A68C(struct Unk0202A68C *arg0, struct Unk0202A68C *arg1);
u8 FUN_0202A744(struct Unk0202A744 *unk);
u8 FUN_0202A74C(struct Unk0202A744 *unk);
void FUN_0202A754(struct Unk0202A744 *dest, void *src, u8 arg2, u8 arg3);
void FUN_0202A784(struct Unk0202A744 *src, struct Unk0202A784 *ptr1);
void FUN_0202A798();
void FUN_0202A838(struct Unk0202A744 *dest, void *src, u8 arg2, u8 arg3);
void FUN_0202A864(struct Unk0202A744 *src, struct Unk0202A784 *dest);
struct Unk0202A744_substruct2 *FUN_0202A878(struct Unk0202A744 *src, u32 head_id);
s32 FUN_0202A89C();
void FUN_0202A8A4(struct UnkSaveStruct_0202A5D4 *savStruct);
struct UnkSaveStruct_0202A5D4 *FUN_0202A8CC(struct SaveBlock2* sav2);
void *FUN_0202A8D8(struct SaveBlock2* sav2);
void *FUN_0202A8E4(struct SaveBlock2* sav2);

#endif //POKEDIAMOND_UNK_0202A1E0_H