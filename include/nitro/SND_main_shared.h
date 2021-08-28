/*
 * NOTE:
 * This file is shared between ARM9 and ARM7
 * DO NOT PUT PROC SPECIFIC CODE IN HERE
 * Thank You!
 */

/*
 * DO NOT INCLUDE THIS FILE DIRECTLY
 * Include SND_main.h from the specific proc's lib
 */

#ifndef POKEDIAMOND_SND_MAIN_SHARED_H
#define POKEDIAMOND_SND_MAIN_SHARED_H

#include "nitro/types.h"

struct SNDBinaryFileHeader
{
    s8 signature[4]; // 0x0
    u16 byteOrder; // 0x4
    u16 version; // 0x6
    u32 fileSize; // 0x8
    u16 headerSize; // 0xC
    u16 dataBlocks; // 0xE
}; // size = 0x10

typedef struct SNDBinaryBlockHeader
{
    u32 type; // 0x0
    u32 size; // 0x4
} SNDBinaryBlockHeader; // size = 0x8

#endif // POKEDIAMOND_SND_MAIN_SHARED_H
