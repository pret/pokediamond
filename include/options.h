#ifndef POKEDIAMOND_OPTIONS_H
#define POKEDIAMOND_OPTIONS_H

#include "main.h"

struct Options {
    u16 unk0_0:4;
    u16 unk0_4:2;
    u16 unk0_6:10;
    u8 padding[2]; // TODO: finish me
};

struct Options * LoadPlayerDataAddress(struct UnkStruct_021C59C8 *);

#endif //POKEDIAMOND_OPTIONS_H
