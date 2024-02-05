#ifndef POKEDIAMOND_MOVE_RELEARNER_H
#define POKEDIAMOND_MOVE_RELEARNER_H

#include "player_data.h"
#include "pokemon.h"

typedef struct MoveRelearner {
    Pokemon *mon;
    PlayerProfile *profile;
    Options *options;
    u16 *eligibleMoves;
    u8 padding[0x5];
    u8 unk15;
    u8 unk16;
    u8 padding2[1];
} MoveRelearner;

MoveRelearner *MoveRelearner_New(HeapID heapId);
void MoveRelearner_Delete(MoveRelearner *moveRelearner);
u16 *MoveRelearner_GetEligibleLevelUpMoves(Pokemon *mon, HeapID heapId);
BOOL MoveRelearner_IsValidMove(const u16 *ptr);

#endif //POKEDIAMOND_MOVE_RELEARNER_H
