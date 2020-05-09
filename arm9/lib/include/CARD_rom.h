#ifndef NITRO_CARD_ROM_H_
#define NITRO_CARD_ROM_H_

#include "MI_exMemory.h"
#include "MI_dma.h"

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

void CARDi_ReadRom(u32 dma, const void * src, void * dst, u32 len, MIDmaCallback done_cb, void * arg, BOOL is_async);

static inline void CARD_ReadRomAsync(u32 dma, const void * src, void * dst, u32 len, MIDmaCallback callback, void * arg)
{
    CARDi_ReadRom(dma, src, dst, len, callback, arg, TRUE);
}

void CARD_LockRom(u16 lock_id);
void CARD_UnlockRom(u16 lock_id);

static inline const CARDRomRegion * CARD_GetRomRegionFNT() {
    return (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x40);
}

static inline const CARDRomRegion * CARD_GetRomRegionFAT() {
    return (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x48);
}

#endif //NITRO_CARD_ROM_H_
