#ifndef POKEDIAMOND_MI_DMA_GXCOMMAND_H
#define POKEDIAMOND_MI_DMA_GXCOMMAND_H

#include "consts.h"
#include "MI_dma.h"
#include "GX_g3x.h"

#define MIi_GX_LENGTH_ONCE       (118 * sizeof(u32))
#define REG_GXFIFO_ADDR          0x4000400
#define MI_CNT_SEND32(size)      (0x84400000 | (size/4))
#define MI_CNT_SEND32_IF(size)   (0xc4400000 | (size/4))
#define MI_CNT_GXCOPY_IF(size)   (0xfc400000 | (size/4))

#define OS_IE_GXFIFO             0x200000

typedef struct
{
    volatile BOOL isBusy;

    u32 dmaNo;
    u32 src;
    u32 length;
    MIDmaCallback callback;
    void *arg;

    GXFifoIntrCond fifoCond;
    void (*fifoFunc) (void);
} MIiGXDmaParams;

void MI_SendGXCommand(u32 dmaNo, const void *src, u32 commandLength);
void MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 commandLength, MIDmaCallback callback, void *arg);
void MI_SendGXCommandAsyncFast(u32 dmaNo, const void *src, u32 commandLength, MIDmaCallback callback, void *arg);

#endif //POKEDIAMOND_MI_DMA_GXCOMMAND_H
