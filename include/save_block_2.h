#ifndef POKEDIAMOND_SAVE_BLOCK_2_H
#define POKEDIAMOND_SAVE_BLOCK_2_H

#include "MATH_crc.h"

struct Options {
    u16 unk0_0:4;
    u16 unk0_4:2;
    u16 unk0_6:10;
    u8 padding[2]; // TODO: finish me
};

struct SavArrayHeader
{
    u32 id;
    u32 size;
    u32 offset;
    u16 field_C;
    u16 field_E;
};

struct PlayerData
{
    /* 0x00 */ u16 playerName[OT_NAME_LENGTH + 1];
    /* 0x10 */ u32 playerId;
    /* 0x14 */ u32 money;
    /* 0x18 */ u8 gender;
    /* 0x19 */ u8 language;
    /* 0x1A */ u8 badges;
    /* 0x1B */ u8 avatar;
    /* 0x1C */ u8 field_1C;
    /* 0x1D */ u8 field_1D_0:1;
               u8 field_1D_1:1;
               u8 field_1D_pad:6;
    /* 0x1E */ u8 padding_1E[2];
};

struct PlayerDataSav
{
    struct Options options;
    struct PlayerData data;
    u16 field_24;
    u16 field_26;
    u32 field_28;
};

struct SaveBlock2_Sub_20464 {
    u8 unk_0;
    u8 padding[3];
    int unk_4;
    int unk_8;
    u8 unk_C;
    u8 unk_D;
    u8 unk_E;
    u8 padding2;
};

struct SaveBlock2
{
    /* 0x00000 */ int unk_00000;
    /* 0x00004 */ int unk_00004;
    /* 0x00008 */ int unk_00008;
    /* 0x0000C */ int unk_0000C;
    /* 0x00010 */ int unk_00010;
    /* 0x00014 */ struct MATHCRC16Table unk_00014;
    /* 0x00214 */ u8 dynamic_region[0x20000];
    /* 0x20214 */ int unk_20214;
    /* 0x20218 */ u8 unk_20218[8];
    /* 0x20220 */ int unk_20220;
    /* 0x20224 */ struct SavArrayHeader arrayHeaders[36];
    /* 0x20464 */ struct SaveBlock2_Sub_20464 unk_20464[4];
    /* 0x204A4 */ int unk_204A4;
    // TODO: finish this struct
}; // size: 0x204A8

struct String * PlayerData_GetPlayerName_NewString(struct PlayerData *, u32 heap_id);
u32 PlayerData_GetTrainerID(struct PlayerData *);
u32 PlayerData_GetTrainerGender(struct PlayerData *);
void * SavArray_get(struct SaveBlock2 *, int);

struct Options * LoadPlayerDataAddress(struct SaveBlock2 *);

#endif //POKEDIAMOND_SAVE_BLOCK_2_H
