#ifndef POKEDIAMOND_MI_DMA_H
#define POKEDIAMOND_MI_DMA_H

#include "nitro/MI_dma_shared.h"
#include "nitro/types.h"

#include "registers.h"

void MI_StopDma(u32 channel);
void MI_WaitDma(u32 channel);

#define MIi_WAIT_BEFOREDMA(dmaCntp, dmaNo)                    \
    do {                                                      \
        dmaCntp = &((vu32 *)REG_DMA0SAD_ADDR)[dmaNo * 3 + 2]; \
        while (*dmaCntp & REG_MI_DMA0CNT_E_MASK) {}           \
    } while (0)

#endif // POKEDIAMOND_MI_DMA_H
