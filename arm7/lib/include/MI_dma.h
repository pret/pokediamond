#ifndef POKEDIAMOND_ARM7_MI_DMA_H
#define POKEDIAMOND_ARM7_MI_DMA_H

#include "nitro/MI_dma_shared.h"
#include "nitro/types.h"

void MI_StopDma(u32 channel);
void MI_WaitDma(u32 channel);

#endif
