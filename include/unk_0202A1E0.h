#ifndef POKEDIAMOND_UNK_0202A1E0_H
#define POKEDIAMOND_UNK_0202A1E0_H

#include "mail_message.h"
#include "save.h"

typedef enum
{
    DATA_GET = 0,
    DATA_SET,
    DATA_RESET,
    DATA_INCREMENT,
    DATA_DECREMENT,
    DATA_ADD,
    DATA_SUBSTRACT
}
DataSetMode;

typedef enum
{
    FIELD_0x0_2 = 0,
    FIELD_0x2,
    FIELD_0x3,
    FIELD_0x4,
    FIELD_0x6,
    FIELD_0x8,
    FIELD_0x2C,
    FIELD_flag0,
    FIELD_0xC,
    FIELD_0x0_5,
    FIELD_0x28,    
} 
SaveStruct23_Substruct1_Field;

struct SaveStruct23_Substruct1
{
    /* 0x000 */ u8 flag0 : 1;
                u8 flag1 : 1;
                u8 u_0_2 : 3;
                u8 u_0_5 : 3;
    /* 0x001 */ u8 u_1;
    /* 0x002 */ u8 u_2;
    /* 0x003 */ u8 u_3;
    /* 0x004 */ u16 u_4;
    /* 0x006 */ u16 u_6;
    /* 0x008 */ s32 u_8;
    /* 0x00C */ s32 u_C[7];
    /* 0x028 */ u32 u_28;
    /* 0x02C */ s32 u_2C[4];
}; // total size = 0x3C (60)

struct SaveStruct23_Substruct2
{
    /* 0x000 */ u16 u_0;
    /* 0x002 */ u8 u_2;
    /* 0x003 */ u8 u_3;
    /* 0x004 */ u32 u_4;

    union 
    {
        struct 
        {
    /* 0x008 */ u16 flag0:1;
                u16 flag1:1;
                u16 flag2:1;
                u16 flag3:1;
                u16 flag4:1;
                u16 filler_1:11;
        };
    /* 0x008 */ u16 flags;
    };
    /* 0x00A */ u8 filler_2[2];
    /* 0x00C */ u16 u_C[5];
    /* 0x016 */ u16 u_16;
    /* 0x018 */ u8 u_18[168];
    /* 0x0C0 */ u8 u_C0[168];
}; // total size 0x168 (360)

struct SaveStruct23_Messages
{
    /* 0x000 */ struct MailMessage messages[4];
}; // total size 0x020 (32)

struct SaveStruct23_Substruct4_Substruct1
{
    /* 0x000 */ u8 u_0[168];
    /* 0x0A8 */ u8 u_A8[16];
    /* 0x0B8 */ u8 filler_1[16];
    /* 0x0C8 */ u8 u_C8_0:1;
                u8 u_C8_1:1;
                u8 filler_2:6;
    /* 0x0C8 */ u8 u_C9;
    /* 0x0CA */ u16 u_CA[4];
    /* 0x0D2 */ u16 u_D2[4];
    /* 0x0DA */ u16 u_DA[4];
    /* 0x0E2 */ u8 filler_3[2];
}; // total size 0xE4 (228)

struct SaveStruct23_Substruct4_Substruct2
{
    /* 0x00 */ u8 u_0[1020];
};

struct SaveStruct23_Substruct4
{
    /* 0x000 */ u32 u_0;
    /* 0x004 */ u8 flags[250];
    /* 0x0FE */ u8 u_FE;
    /* 0x0FF */ u8 u_FF;
    /* 0x100 */ u8 u_100;
    /* 0x101 */ u8 u_101;
    /* 0x102 */ u8 u_102;
    /* 0x103 */ u8 u_103;
    /* 0x104 */ struct SaveStruct23_Substruct4_Substruct1 substruct1[7];
    /* 0x740 */ struct SaveStruct23_Substruct4_Substruct2 substruct2;
}; // total size 0xB3C (2876)

struct SaveStruct23 // Struct fetched with SaveArray_Get(save, 23)
{
    /* 0x000 */ struct SaveStruct23_Substruct1 substruct1;
    /* 0x03C */ struct SaveStruct23_Substruct2 substruct2;
    /* 0x1A4 */ struct SaveStruct23_Messages messages;
    /* 0x1C4 */ struct SaveStruct23_Substruct4 substruct4;
}; // total size = 0xD00 (3328)

struct Unk0202A4B8
{
    /* 0x000 */ u8 filler_1[2];
    /* 0x002 */ u8 u_2;
    /* 0x003 */ u8 u_3;
    /* 0x004 */ u16 u_4;
    /* 0x006 */ u16 u_6;
};

typedef struct Unk0202A68C
{
    /* 0x000 */ u32 u_0;
    /* 0x004 */ u32 u_4;
    /* 0x008 */ u32 u_8;
    /* 0x00C */ u32 u_C;
}
Unk0202A68C; // total size 0x10 (16)

struct Unk0202A784
{
    /* 0x000 */ u8 u_0;
    /* 0x001 */ u8 u_1;
};

struct Unk0202A798_substruct
{
    /* 0x000 */ u32 u_0;
    /* 0x004 */ u16 u_4;
    /* 0x006 */ u8 filler_1[2];
    /* 0x008 */ u16 u_8[8];
    /* 0x018 */ u16 u_18[4];
    /* 0x020 */ u16 u_20[4];
    /* 0x028 */ u16 u_28[4];
}; // total size 0x30 (48)

struct Unk0202A798
{
    /* 0x000 */ struct Unk0202A798_substruct u_0;
    /* 0x030 */ u8 u_30[168];
};

s32 SaveStruct23_Substruct4_Substruct1_sizeof();
void SaveStruct23_Substruct1_Init(struct SaveStruct23_Substruct1 *substruct1);
void SaveStruct23_Substruct2_Init(struct SaveStruct23_Substruct2 *substruct2);
void SaveStruct23_Messages_Init(struct SaveStruct23_Messages *mailStruct);
void SaveStruct23_Substruct4_Init(struct SaveStruct23_Substruct4 *substruct4);
u32 SaveStruct23_Substruct1_GetField(struct SaveStruct23_Substruct1 *substruct1, SaveStruct23_Substruct1_Field field, void *dst);
void SaveStruct23_Substruct1_SetField(struct SaveStruct23_Substruct1 *substruct1, SaveStruct23_Substruct1_Field field, void *value);
void sub_0202A36C(struct SaveStruct23_Substruct1 *substruct1, s32 arg1, s32 arg2, s32 arg3);
BOOL SaveStruct23_Substruct1_GetFlag1(struct SaveStruct23_Substruct1 *substruct1);
void SaveStruct23_Substruct1_SetFlag1(struct SaveStruct23_Substruct1 *substruct1, BOOL arg1);
u16 SaveStruct23_Substruct2_SetField_0x0(struct SaveStruct23_Substruct2 *substruct2, u16 value, DataSetMode mode);
u8 SaveStruct23_Substruct2_SetField_0x2(struct SaveStruct23_Substruct2 *substruct2, DataSetMode mode);
u8 SaveStruct23_Substruct2_SetField_0x3(struct SaveStruct23_Substruct2 *substruct2, DataSetMode mode);
void SaveStruct23_Substruct2_SetArray(struct SaveStruct23_Substruct2 *substruct2, s32 mode, void *src);
void SaveStruct23_Substruct2_GetArray(struct SaveStruct23_Substruct2 *substruct2, s32 mode, void *dst);
u16 SaveStruct23_Substruct2_SetField_0x16(struct SaveStruct23_Substruct2 *substruct2, struct Unk0202A4B8 *arg1);
u16 SaveStruct23_Substruct2_GetField_0x16(struct SaveStruct23_Substruct2 *substruct2);
u8 sub_0202A524(struct SaveStruct23_Substruct2 *substruct2);
u16 SaveStruct23_Substruct2_SetField_0xC(struct SaveStruct23_Substruct2 *substruct2, u16 arg1, DataSetMode mode);
BOOL SaveStruct23_Substruct2_SetFlag(struct SaveStruct23_Substruct2 *substruct2, u16 flagNumber, DataSetMode mode);
void SaveStruct23_Substruct2_SetField_0x4(struct SaveStruct23_Substruct2 *substruct2, u32 arg1);
u32 SaveStruct23_Substruct2_GetField_0x4(struct SaveStruct23_Substruct2 *substruct2);
void SaveStruct23_SetMessage(struct SaveData *save, u32 index, struct MailMessage *message);
struct MailMessage *SaveStruct23_GetMessage(struct SaveData *save, u32 index);
void SaveStruct23_Substruct4_SetArrayFlag(struct SaveStruct23_Substruct4 *substruct4, u8 arg1, u8 arg2, struct Unk0202A68C *arg3);
void SaveStruct23_Substruct4_ClearArrayFlags(struct SaveStruct23_Substruct4 *substruct4);
BOOL StructUnk0202A68C_Compare(struct Unk0202A68C *struct1, struct Unk0202A68C *struct2);
BOOL SaveStruct23_Substruct4_GetArrayFlag(struct SaveStruct23_Substruct4 *substruct4, u8 arg1, u8 arg2, struct Unk0202A68C *arg3);
u8 SaveStruct23_Substruct4_GetField_0xFE(struct SaveStruct23_Substruct4 *substruct4);
u8 SaveStruct23_Substruct4_GetField_0xFF(struct SaveStruct23_Substruct4 *substruct4);
void SaveStruct23_Substruct4_SetSubstruct1(struct SaveStruct23_Substruct4 *substruct4, struct SaveStruct23_Substruct4_Substruct1 *substruct4_substruct1, u8 arg2, u8 arg3);
void sub_0202A784(struct SaveStruct23_Substruct4 *substruct4, struct Unk0202A784 *dest);
void sub_0202A798(struct SaveStruct23_Substruct4 *substruct4, struct Unk0202A798 *arg1, u32 arg2);
void sub_0202A838(struct SaveStruct23_Substruct4 *substruct4, struct SaveStruct23_Substruct4_Substruct2 *substruct4_substruct2, u8 arg2, u8 arg3);
void sub_0202A864(struct SaveStruct23_Substruct4 *substruct4, struct Unk0202A784 *dest);
struct SaveStruct23_Substruct4_Substruct2 *sub_0202A878(struct SaveStruct23_Substruct4 *substruct4, u32 heap_id);
s32 SaveStruct23_sizeof();
void SaveStruct23_Init(struct SaveStruct23 *saveStruct23);
struct SaveStruct23_Substruct1 *SaveStruct23_GetSubstruct1(struct SaveData* save);
struct SaveStruct23_Substruct2 *SaveStruct23_GetSubstruct2(struct SaveData* save);
struct SaveStruct23_Substruct4 *SaveStruct23_GetSubstruct4(struct SaveData* save);

#endif //POKEDIAMOND_UNK_0202A1E0_H