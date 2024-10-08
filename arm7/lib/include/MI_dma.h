#ifndef NITRO_MI_DMA_H
#define NITRO_MI_DMA_H

#include "nitro/MI_dma_shared.h"
#include "nitro/types.h"

#include "registers.h"

#define MI_DMA_TIMING_MASK (3UL << 28)
#define MI_DMA_TIMING_CARD (2UL << 28)

void MI_StopDma(u32 channel);
void MI_WaitDma(u32 channel);

#define MIi_WAIT_BEFOREDMA(dmaCntp, dmaNo)                    \
    do {                                                      \
        dmaCntp = &((vu32 *)REG_DMA0SAD_ADDR)[dmaNo * 3 + 2]; \
        while (*dmaCntp & REG_MI_DMA0CNT_E_MASK) {}           \
    } while (0)

#endif // NITRO_MI_DMA_H
