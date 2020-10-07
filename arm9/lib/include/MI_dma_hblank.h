#ifndef POKEDIAMOND_MI_DMA_HBLANK_H
#define POKEDIAMOND_MI_DMA_HBLANK_H

#include "nitro/types.h"

void MI_HBlankDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
void MI_HBlankDmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);

#endif //POKEDIAMOND_MI_DMA_HBLANK_H
