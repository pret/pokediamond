#include "global.h"
#include "heap.h"
#include "pokemon.h"
#include "unk_02088DD8.h"

THUMB_FUNC struct UnkStruct_02088DD8* FUN_02088DD8(u32 r0) {
    struct UnkStruct_02088DD8 *returnPointer = AllocFromHeap(r0, 24);
    __builtin__clear(returnPointer, 24);
    return returnPointer;
}

THUMB_FUNC void FUN_02088DF0(struct UnkStruct_02037CF0 *r0) {
    FreeToHeap(r0);
}

#define WOTBL_END           0xFFFF
#define WOTBL_MOVE_MASK     0x01FF
#define WOTBL_MOVE_SHIFT         0
#define WOTBL_LVL_MASK      0xFE00
#define WOTBL_LVL_SHIFT          9
#define WOTBL_MOVE(x) ((u16)(((x) & WOTBL_MOVE_MASK) >> WOTBL_MOVE_SHIFT))
#define WOTBL_LVL(x) (/*(u8)*/(((x) & WOTBL_LVL_MASK) >> WOTBL_LVL_SHIFT))
// i don't know why either.

THUMB_FUNC void* Maybe_GetEligibleLevelUpMoves(struct Pokemon* pokemon, u32 heap_id) {
    u16 species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, 0);
    u8 forme = (u8)GetMonData(pokemon, MON_DATA_FORME, 0);
    u8 level = (u8)GetMonData(pokemon, MON_DATA_LEVEL, 0);
    u16 moves[4];

    for (u8 i = 0; i < 4; ++i) {
        moves[i] = (u16)GetMonData(pokemon, MON_DATA_MOVE1 + i, 0);
    }

    u16 *tableFromFile = AllocFromHeap(heap_id, 44);
    u16 *returnTable = AllocFromHeap(heap_id, 44);

    LoadWotbl_HandleAlternateForme(species, forme, tableFromFile);

    for (u8 i = 0, j, k = 0; i < 22; i++) {
        if (tableFromFile[i] == WOTBL_END) {
            returnTable[k] = WOTBL_END;
            break;
        }
        else {
            if (WOTBL_LVL(tableFromFile[i]) > level) continue;

            tableFromFile[i] = WOTBL_MOVE(tableFromFile[i]);
            
            j = 0;
            for (; j < 4; j++) {
                if (tableFromFile[i] == moves[j]) break;
            }
            if (j != 4) continue;

            j = 0;
            if (k >= 0) {
                // don't know when that would be false
                for (; j < k; j++) {
                    if (returnTable[j] == tableFromFile[i]) break;
                }
            }
            if (j != k) continue;

            returnTable[k] = tableFromFile[i];
            k++;
        }
    }

    FreeToHeap(tableFromFile);
    return returnTable;
}

THUMB_FUNC BOOL FUN_02088EF8(u16 *r0) {
    return *r0 != 0xFFFF;
}