#include "MI_dma_card.h"
#include "MI_dma.h"
#include "code32.h"

void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size)
{
    MIi_CheckAnotherAutoDMA(dmaNo, MIi_DMA_TIMING_ANY);
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, MI_DMA_SRC_FIX);

    if (size == 0)
    {
        return;
    }

    vu32 *dmaCntp;

    do
    {
        dmaCntp = &((vu32 *)REG_ADDR_DMA0SAD)[dmaNo * 3 + 2];
        while (*dmaCntp & 0x80000000) {}
    } while(0);

    MIi_DmaSetParams(dmaNo, (u32)src, (u32)dest, (u32)(0xaf000001));
}
