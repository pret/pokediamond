#ifndef POKEDIAMOND_UNK_0206439C_H
#define POKEDIAMOND_UNK_0206439C_H

#include "heap.h"
#include "pokemon.h"
#include "save.h"

typedef struct UnkStruct_0206439C {
    Pokemon *pokemon;
    void *unk4;
} UnkStruct_0206439C;

UnkStruct_0206439C *sub_0206439C(HeapID heapId, u8 mon_idx, SaveData *save);

#endif
