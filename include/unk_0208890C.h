#ifndef POKEDIAMOND_UNK_0208890C_H
#define POKEDIAMOND_UNK_0208890C_H

#include "script.h"
#include "player_data.h"

struct Bag;
struct Options;
struct SaveData;

typedef struct PoffinCaseAppData {
    u8 padding[0x4];
    u32 unk4;
    u32 unk8;
    struct SaveData* save;
    PlayerProfile* player;
    struct Bag* bag;
    struct Options* options;
    u32 *unk1C;
} PoffinCaseAppData;

struct PoffinCaseAppData* sub_0208890C(u32, struct SaveData* save, HeapID heapId, u32 *);
void sub_02088950(struct FieldSystem *fieldSystem, struct PoffinCaseAppData*);
struct PoffinCaseAppData* sub_02088960(struct FieldSystem *fieldSystem, u32, HeapID heapId);

#endif
