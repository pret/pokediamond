#ifndef POKEDIAMOND_UNK_0208890C_H
#define POKEDIAMOND_UNK_0208890C_H

struct Bag;
struct Options;
struct PlayerData;
struct SaveBlock2;

struct UnkStruct_0208890C
{
    u8 padding[0x4];
    void* unk4;
    void* unk8;
    struct SaveBlock2* sav2;
    struct PlayerData* player;
    struct Bag* bag;
    struct Options* options;
    void* unk1C;
};

struct UnkStruct_0208890C* FUN_0208890C(void*, struct SaveBlock2* sav2, u32 heap_id, void*);
void FUN_02088950(struct FieldSystem *fieldSystem, struct UnkStruct_0208890C*);
struct UnkStruct_0208890C* FUN_02088960(struct FieldSystem *fieldSystem, void*, u32 heap_id);

#endif
