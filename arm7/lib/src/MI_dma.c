#include "MI_dma.h"

#include "OS_system.h"
#include "code32.h"

void MI_WaitDma(u32 channel) {
    OSIntrMode mode = OS_DisableInterrupts();
    vu32 *addr;

    MIi_WAIT_BEFOREDMA(addr, channel);

    if (channel == 0) {
        addr    = (vu32 *)(REG_DMA0SAD_ADDR + channel * 12);
        addr[0] = 0;
        addr[1] = 0;
        addr[2] = 0x81400001;
    }
    mode = OS_RestoreInterrupts(mode);
}

void MI_StopDma(u32 channel) {
    OSIntrMode mode = OS_DisableInterrupts();
    vu16 *addr      = (vu16 *)(REG_DMA0SAD_ADDR + (channel * 6 + 5) * 2);
    addr[0] &= ~(DMA_START_MASK | DMA_REPEAT);
    addr[0] &= ~DMA_ENABLE;
    {
        s32 dummy = addr[0];
    }
    {
        s32 dummy = addr[0];
    }
    if (channel == 0) {
        vu32 *addr32 = (vu32 *)(REG_DMA0SAD_ADDR + channel * 12);
        addr32[0]    = 0;
        addr32[1]    = 0;
        addr32[2]    = 0x81400001;
    }
    mode = OS_RestoreInterrupts(mode);
}
