#include "MI_dma.h"

#include "OS_interrupt.h"
#include "OS_terminate_proc.h"
#include "code32.h"
#include "sections.h"

#pragma section ITCM begin
void MIi_DmaSetParams(u32 dmaNo, u32 src, u32 dest, u32 ctrl) {
    OSIntrMode lastIntrMode = OS_DisableInterrupts();
    vu32 *p                 = (vu32 *)((u32)REG_DMA0SAD_ADDR + dmaNo * 12);
    *p                      = (vu32)src;
    *(p + 1)                = (vu32)dest;
    *(p + 2)                = (vu32)ctrl;
    (void)OS_RestoreInterrupts(lastIntrMode);
}

void MIi_DmaSetParams_wait(u32 dmaNo, u32 src, u32 dest, u32 ctrl) {
    OSIntrMode enabled = OS_DisableInterrupts();
    vu32 *p            = (vu32 *)((u32)REG_DMA0SAD_ADDR + dmaNo * 12);
    *p                 = (vu32)src;
    *(p + 1)           = (vu32)dest;
    *(p + 2)           = (vu32)ctrl;

    // delay cycles
    {
        u32 delay = reg_MI_DMA0SAD;
    }
    {
        u32 delay = reg_MI_DMA0SAD;
    }

    if (!dmaNo) {
        *p       = (vu32)0;
        *(p + 1) = (vu32)0;
        *(p + 2) = (vu32)0x81400001;
    }

    (void)OS_RestoreInterrupts(enabled);
}

void MIi_DmaSetParams_noInt(u32 dmaNo, u32 src, u32 dest, u32 ctrl) {
    vu32 *p  = (vu32 *)((u32)REG_DMA0SAD_ADDR + dmaNo * 12);
    *p       = (vu32)src;
    *(p + 1) = (vu32)dest;
    *(p + 2) = (vu32)ctrl;
}

void MIi_DmaSetParams_wait_noInt(u32 dmaNo, u32 src, u32 dest, u32 ctrl) {
    vu32 *p  = (vu32 *)((u32)REG_DMA0SAD_ADDR + dmaNo * 12);
    *p       = (vu32)src;
    *(p + 1) = (vu32)dest;
    *(p + 2) = (vu32)ctrl;

    // delay cycles
    {
        u32 delay = reg_MI_DMA0SAD;
    }
    {
        u32 delay = reg_MI_DMA0SAD;
    }

    if (!dmaNo) {
        *p       = (vu32)0;
        *(p + 1) = (vu32)0;
        *(p + 2) = (vu32)0x81400001;
    }

    // delay cycles
    {
        u32 delay = reg_MI_DMA0SAD;
    }
    {
        u32 delay = reg_MI_DMA0SAD;
    }
}
#pragma section ITCM end

void MI_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size) {
    vu32 *dmaCntp;
    if (!size) {
        return;
    }

    MIi_WAIT_BEFOREDMA(dmaCntp, dmaNo);

    MIi_DmaSetParams_wait_src32(dmaNo, data, (u32)dest, MI_CNT_CLEAR32(size));

    do {
        while (*dmaCntp & 0x80000000) {}
    } while (0);
}

void MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size) {
    vu32 *dmaCntp;
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, MI_DMA_SRC_INC);

    if (!size) {
        return;
    }

    MIi_WAIT_BEFOREDMA(dmaCntp, dmaNo);

    MIi_DmaSetParams_wait(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32(size));

    do {
        while (*dmaCntp & 0x80000000) {}
    } while (0);
}

void MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size) {
    vu32 *dmaCntp;

    if (!size) {
        return;
    }

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, MI_DMA_SRC_INC);

    MIi_WAIT_BEFOREDMA(dmaCntp, dmaNo);

    MIi_DmaSetParams_wait(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY16(size));

    do {
        while (*dmaCntp & 0x80000000) {}
    } while (0);
}

void MI_DmaFill32Async(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback, void *arg) {
    if (!size) {
        MIi_CallCallback(callback, arg);
    } else {
        MI_WaitDma(dmaNo);

        if (callback) {
            OSi_EnterDmaCallback(dmaNo, callback, arg);
            MIi_DmaSetParams_src32(dmaNo, data, (u32)dest, MI_CNT_CLEAR32_IF(size));
        } else {
            MIi_DmaSetParams_src32(dmaNo, data, (u32)dest, MI_CNT_CLEAR32(size));
        }
    }
}

void MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback, void *arg) {
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, MI_DMA_SRC_INC);

    if (!size) {
        MIi_CallCallback(callback, arg);
    } else {
        MI_WaitDma(dmaNo);

        if (callback) {
            OSi_EnterDmaCallback(dmaNo, callback, arg);
            MIi_DmaSetParams(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32_IF(size));
        } else {
            MIi_DmaSetParams(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32(size));
        }
    }
}

void MI_WaitDma(u32 dmaNo) {
    OSIntrMode lastIntrMode = OS_DisableInterrupts();
    vu32 *dmaCntp;
    MIi_WAIT_BEFOREDMA(dmaCntp, dmaNo);

    if (!dmaNo) {
        vu32 *p  = (vu32 *)((u32)REG_DMA0SAD_ADDR + dmaNo * 12);
        *p       = (vu32)0;
        *(p + 1) = (vu32)0;
        *(p + 2) = (vu32)0x81400001;
    }

    (void)OS_RestoreInterrupts(lastIntrMode);
}

void MI_StopDma(u32 dmaNo) {
    OSIntrMode lastIntrMode = OS_DisableInterrupts();
    vu16 *dmaCntp           = &((vu16 *)REG_DMA0SAD_ADDR)[dmaNo * 6 + 5];

    *dmaCntp &= ~0x3a00;
    *dmaCntp &= ~0x8000;

    // delay cycles
    {
        s32 delay = dmaCntp[0];
    }
    {
        s32 delay = dmaCntp[0];
    }

    if (!dmaNo) {
        vu32 *p  = (vu32 *)((u32)REG_DMA0SAD_ADDR + dmaNo * 12);
        *p       = (vu32)0;
        *(p + 1) = (vu32)0;
        *(p + 2) = (vu32)0x81400001;
    }

    (void)OS_RestoreInterrupts(lastIntrMode);
}

void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType) {
    u32 dmaCnt;
    u32 timing;
    for (int i = 0; i < 3; i++) {
        if (i == dmaNo) {
            continue;
        }

        dmaCnt = *(REGType32v *)(REG_ADDR_DMA0CNT + i * 12);

        if (!(dmaCnt & 0x80000000)) {
            continue;
        }

        timing = dmaCnt & 0x38000000;

        if (timing == dmaType
            || (timing == 0x8000000 && dmaType == MI_DMA_TIMING_H_BLANK)
            || (timing == MI_DMA_TIMING_H_BLANK && dmaType == 0x8000000)) {
            continue;
        }

        if (timing == 0x18000000
            || timing == 0x20000000
            || timing == 0x28000000
            || timing == 0x30000000
            || timing == 0x38000000
            || timing == 0x8000000
            || timing == 0x10000000) {
            OS_Terminate();
        }
    }
}

void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir) {
    if (!dmaNo) {
        u32 addStart = src & 0xff000000;
        u32 addEnd;

        switch (dir) {
        case 0: // dma_src_inc
            addEnd = src + size;
            break;
        case 0x800000: // dma_src_dec
            addEnd = src - size;
            break;
        default:
            addEnd = src;
            break;
        }
        addEnd &= 0xff000000;

        if (addStart == 0x04000000 || addStart >= 0x08000000 || addEnd == 0x04000000 || addEnd >= 0x08000000) {
            OS_Terminate();
        }
    }
}
