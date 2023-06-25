#ifndef POKEDIAMOND_UNK_02088DD8_H
#define POKEDIAMOND_UNK_02088DD8_H

#include "unk_020377F0.h"
#include "player_data.h"

struct Options;
struct Pokemon;

typedef struct MoveRelearner
{
    struct Pokemon* pokemon;
    PlayerProfile* player;
    struct Options* options;
    u16 *eligibleMoves;
    u8 padding[0x5];
    u8 unk15;
    u8 unk16;
    u8 padding2[1];
} MoveRelearner;

MoveRelearner *sub_02088DD8(HeapID heapId);
void sub_02088DF0(MoveRelearner *moveRelearner);
u16* GetEligibleLevelUpMoves(struct Pokemon* pokemon, HeapID heapId);
BOOL sub_02088EF8(u16 *r0);

#endif
