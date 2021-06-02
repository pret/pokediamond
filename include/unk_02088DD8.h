#ifndef POKEDIAMOND_UNK_02088DD8_H
#define POKEDIAMOND_UNK_02088DD8_H

struct Options;
struct PlayerData;
struct Pokemon;

struct UnkStruct_02088DD8
{
    struct Pokemon* pokemon;
    struct PlayerData* player;
    struct Options* options;
    void* unkC;
    u8 padding[0x5];
    u8 unk15;
    u8 padding2[0x2];
};

#endif
