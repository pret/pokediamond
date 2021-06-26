#ifndef GUARD_SND_BANK_SHARED_H
#define GUARD_SND_BANK_SHARED_H

#include "nitro/types.h"

#define SND_INST_MAX_KEYSPLIT 8

struct SNDInstParam {
    u16 wave[2];    // 0x0
    u8 rootKey;     // 0x4
    u8 envAttack;   // 0x5
    u8 envDecay;    // 0x6
    u8 envSustain;  // 0x7
    u8 envRelease;  // 0x8
    u8 pan;         // 0x9
};  // size = 0xA

struct SNDInstData {
    u8 type;                    // 0x0
    u8 unk_1;                   // 0x1
    struct SNDInstParam param;  // 0x2
};  // size = 0xC

struct SNDKeySplit {
    u8 key[SND_INST_MAX_KEYSPLIT];      // 0x0
    struct SNDInstData instruments[];   // 0x8
};  // size = 0x8

struct SNDDrumSet {
    u8 minKey;
    u8 maxKey;
    struct SNDInstData instruments[];
};  // size = 0x2

#endif //GUARD_SND_BANK_SHARED_H
