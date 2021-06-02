#ifndef POKEDIAMOND_UNK_0206439C_H
#define POKEDIAMOND_UNK_0206439C_H

struct Pokemon;
struct SaveBlock2;

struct UnkStruct_0206439C
{
    struct Pokemon* pokemon;
    void* unk4;
};

struct UnkStruct_0206439C* FUN_0206439C(u32 heap_id, u8 mon_idx, struct SaveBlock2* sav2);

#endif
