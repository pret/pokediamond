#ifndef GUARD_MI_DMA_H
#define GUARD_MI_DMA_H

#include "nitro/dma.h"
#include "nitro/types.h"

void MI_StopDma(u32 channel);
void MI_WaitDma(u32 channel);

#endif
