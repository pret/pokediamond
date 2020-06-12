#ifndef POKEDIAMOND_SEALS_H
#define POKEDIAMOND_SEALS_H

struct SealStruct
{
    // TODO: define
    u8 filler_00[0x38];
};

struct SealStruct * CreateNewSealsObject(u32 heap_id);

#endif //POKEDIAMOND_SEALS_H
