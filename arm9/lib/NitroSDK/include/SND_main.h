#ifndef GUARD_SND_MAIN_H
#define GUARD_SND_MAIN_H

#include "global.h"

#include "nitro/SND_main_shared.h"

void SNDi_UnlockMutex(void);
void SNDi_LockMutex(void);
void SND_Init(void);

struct SNDBinaryFileHeader {
    s8 signature[4];    // 0x0
    u16 byteOrder;      // 0x4
    u16 version;        // 0x6
    u32 fileSize;       // 0x8
    u16 headerSize;     // 0xC
    u16 dataBlocks;     // 0xE
};  // size = 0x10

typedef struct SNDBinaryBlockHeader {
    u32 type;       // 0x0
    u32 size;       // 0x4
} SNDBinaryBlockHeader;  // size = 0x8

#endif // GUARD_SND_MAIN_H
