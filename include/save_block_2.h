#ifndef POKEDIAMOND_SAVE_BLOCK_2_H
#define POKEDIAMOND_SAVE_BLOCK_2_H

#include "pokemon.h"

struct SavArrayHeader
{
    u32 id;
    u32 size;
    u32 offset;
    u16 field_C;
    u16 field_E;
};

struct SaveBlock2
{
    /* 0x00000 */ u16 playerName[OT_NAME_LENGTH + 1];
    /* 0x00010 */ u32 playerId;
    /* 0x00014 */ u32 money;
    /* 0x00018 */ u8 gender;
    /* 0x00019 */ u8 origin;
    /* 0x0001A */ u8 badges;
    /* 0x0001B */ u8 avatar;
    /* 0x0001C */ u8 filler_0001C[0x1F8];
    /* 0x00214 */ u8 dynamic_region[0x20000];
    /* 0x20214 */ u8 filler_20214[16];
    /* 0x20224 */ struct SavArrayHeader arrayHeaders[36];
    /* 0x20464 */ u8 filler_20464[0x44];
    // TODO: finish this struct
}; // size: 0x204A8

struct String * FUN_020239A0(struct SaveBlock2 *, u32 heap_id);
u32 FUN_020239BC(struct SaveBlock2 *);
u32 FUN_020239CC(struct SaveBlock2 *);
void * SavArray_get(struct SaveBlock2 *, int);

#endif //POKEDIAMOND_SAVE_BLOCK_2_H
