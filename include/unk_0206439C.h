#ifndef POKEDIAMOND_UNK_0206439C_H
#define POKEDIAMOND_UNK_0206439C_H

struct Pokemon;
struct SaveData;

struct UnkStruct_0206439C
{
    struct Pokemon* pokemon;
    void* unk4;
};

struct UnkStruct_0206439C* sub_0206439C(u32 heap_id, u8 mon_idx, struct SaveData* save);

#endif
