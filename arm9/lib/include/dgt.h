#ifndef GUARD_DGT_H
#define GUARD_DGT_H

#include "nitro/types.h"

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

void DGT_Hash1Reset(struct DGTHash1Context *context);
void DGT_Hash1SetSource(struct DGTHash1Context *context, u8 *input, u32 length);
void DGT_Hash1GetDigest_R(u8 *digest, struct DGTHash1Context *context);
void DGT_Hash2Reset(struct DGTHash2Context *context);
void DGT_Hash2SetSource(struct DGTHash2Context *context, u8 *input, u32 length);
void DGT_Hash2GetDigest(struct DGTHash2Context *context, u8 *digest);

#endif
