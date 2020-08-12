#ifndef POKEDIAMOND_SAVE_BLOCK_2_H
#define POKEDIAMOND_SAVE_BLOCK_2_H

#include "pokemon.h"

struct SaveBlock2
{
    /* 0x00000 */ u16 playerName[OT_NAME_LENGTH + 1];
    /* 0x00010 */ u32 playerId;
    /* 0x00014 */ u32 money;
    /* 0x00018 */ u8 gender;
    /* 0x00019 */ u8 origin;
    /* 0x0001A */ u8 badges;
    /* 0x0001B */ u8 avatar;
    /* 0x0001C */ u8 filler_0001C[0x14];
    /* 0x00030 */ struct PlayerParty party;
    // TODO: finish this st ruct
};

struct String * FUN_020239A0(struct SaveBlock2 *, u32 heap_id);
u32 FUN_020239BC(struct SaveBlock2 *);
u32 FUN_020239CC(struct SaveBlock2 *);
void * SavArray_get(struct SaveBlock2 *, int);

#endif //POKEDIAMOND_SAVE_BLOCK_2_H
