#ifndef POKEDIAMOND_UNK_0208890C_H
#define POKEDIAMOND_UNK_0208890C_H

#include "script.h"

struct Bag;
struct Options;
struct PlayerData;
struct SaveBlock2;

typedef struct PoffinCaseAppData {
    u8 padding[0x4];
    u32 unk4;
    u32 unk8;
    struct SaveBlock2* sav2;
    struct PlayerData* player;
    struct Bag* bag;
    struct Options* options;
    u32 *unk1C;
} PoffinCaseAppData;

struct PoffinCaseAppData* FUN_0208890C(u32, struct SaveBlock2* sav2, u32 heap_id, u32 *);
void FUN_02088950(struct FieldSystem *fieldSystem, struct PoffinCaseAppData*);
struct PoffinCaseAppData* FUN_02088960(struct FieldSystem *fieldSystem, u32, u32 heap_id);

#endif
