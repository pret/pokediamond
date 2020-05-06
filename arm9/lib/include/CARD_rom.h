#ifndef NITRO_CARD_ROM_H_
#define NITRO_CARD_ROM_H_

#include "MI_exMemory.h"

typedef struct
{
    u32 offset;
    u32 length;
}
CARDRomRegion;

static inline const CARDRomRegion * CARD_GetRomRegionOVT(MIProcessor target)
{
    return (target == MI_PROCESSOR_ARM9)
    ? (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x50)
    : (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x58);
}

#endif //NITRO_CARD_ROM_H_
