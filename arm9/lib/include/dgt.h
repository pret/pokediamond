#ifndef GUARD_DGT_H
#define GUARD_DGT_H

#include "types.h"

struct DGTHash1Context {
    union {
        struct {
            unsigned long a, b, c, d;
        };
        unsigned long state[4];
    };
    unsigned long long length;
    union {
        unsigned long buffer32[16];
        unsigned char buffer8[64];
    };
};

struct DGTHash2Context {
    unsigned long Intermediate_Hash[5];
    unsigned long Length_Low;
    unsigned long Length_High;
    int Message_Block_Index;
    unsigned char Message_Block[64];
    int Computed;
    int Corrupted;
};

#endif
