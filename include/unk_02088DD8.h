#ifndef POKEDIAMOND_UNK_02088DD8_H
#define POKEDIAMOND_UNK_02088DD8_H

#include "unk_020377F0.h"

extern void LoadWotbl_HandleAlternateForme(int species, int forme, u16 * wotbl);

struct Options;
struct PlayerData;
struct Pokemon;

struct UnkStruct_02088DD8
{
    struct Pokemon* pokemon;
    struct PlayerData* player;
    struct Options* options;
    void* unkC;
    u8 padding[0x5];
    u8 unk15;
    u8 padding2[0x2];
};

struct UnkStruct_02088DD8* FUN_02088DD8(u32 r0);
void FUN_02088DF0(struct UnkStruct_02037CF0 *r0);
void* GetEligibleLevelUpMoves(struct Pokemon* pokemon, u32 heap_id);
BOOL FUN_02088EF8(u16 *r0);

#endif
