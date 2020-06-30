#include "MI_dma_gxcommand.h"
#include "function_target.h"
#include "OS_interrupt.h"
#include "OS_reset.h"
#include "sections.h"

static MIiGXDmaParams MIi_GXDmaParams = { FALSE };

#pragma section ITCM begin
ARM_FUNC void MI_SendGXCommand(u32 dmaNo, const void *src, u32 commandLength)
{
    vu32 *dmaCntp;
    u32 leftLength = commandLength;
    u32 currentSrc = (u32)src;
    if (!leftLength)
    {
        return;
    }

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, commandLength, DMA_SRC_INC);

    do
    {
        dmaCntp = &((vu32 *)REG_ADDR_DMA0SAD)[dmaNo * 3 + 2];
        while (*dmaCntp & 0x80000000) {}
    } while(0);

    while (leftLength > 0)
    {
        u32 length = (leftLength > MIi_GX_LENGTH_ONCE) ? MIi_GX_LENGTH_ONCE : leftLength;
        MIi_DmaSetParams(dmaNo, currentSrc, (u32)REG_GXFIFO_ADDR, MI_CNT_SEND32(length));
        leftLength -= length;
        currentSrc += length;
    }

    do
    {
        while (*dmaCntp & 0x80000000) {}
    } while(0);
}
#pragma section ITCM end

ARM_FUNC void MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 commandLength, MIDmaCallback callback, void *arg)
{
    if (!commandLength)
    {
        MIi_CallCallback(callback, arg);
        return;
    }

    while (MIi_GXDmaParams.isBusy) {}

    while (!(G3X_GetCommandFifoStatus() & GX_FIFOSTAT_UNDERHALF)) {}

    MIi_GXDmaParams.isBusy = TRUE;
    MIi_GXDmaParams.dmaNo = dmaNo;
    MIi_GXDmaParams.src = (u32)src;
    MIi_GXDmaParams.length = commandLength;
    MIi_GXDmaParams.callback = callback;
    MIi_GXDmaParams.arg = arg;

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, commandLength, DMA_SRC_INC);

    MI_WaitDma(dmaNo);
    {
        OSIntrMode lastIntrMode = OS_DisableInterrupts();

        MIi_GXDmaParams.fifoCond = (GXFifoIntrCond)((reg_G3X_GXSTAT & 0xc0000000) >> 30);
        MIi_GXDmaParams.fifoFunc = OS_GetIrqFunction(OS_IE_GXFIFO);

        G3X_SetFifoIntrCond(GX_FIFOINTR_COND_UNDERHALF);
        OS_SetIrqFunction(OS_IE_GXFIFO, MIi_FIFOCallback);
        (void)OS_EnableIrqMask(OS_IE_GXFIFO);

        MIi_FIFOCallback();

        (void)OS_RestoreInterrupts(lastIntrMode);
    }
}

ARM_FUNC static void MIi_FIFOCallback(void)
{
    if (!MIi_GXDmaParams.length)
    {
        return;
    }

    u32 length = (MIi_GXDmaParams.length >= MIi_GX_LENGTH_ONCE) ? MIi_GX_LENGTH_ONCE : MIi_GXDmaParams.length;
    u32 src = MIi_GXDmaParams.src;

    MIi_GXDmaParams.length -= length;
    MIi_GXDmaParams.src += length;

    if (!MIi_GXDmaParams.length)
    {
        OSi_EnterDmaCallback(MIi_GXDmaParams.dmaNo, MIi_DMACallback, NULL);
        MIi_DmaSetParams(MIi_GXDmaParams.dmaNo, src, (u32)REG_GXFIFO_ADDR, MI_CNT_SEND32_IF(length));
        (void)OS_ResetRequestIrqMask(OS_IE_GXFIFO);
    }
    else
    {
        MIi_DmaSetParams(MIi_GXDmaParams.dmaNo, src, (u32)REG_GXFIFO_ADDR, MI_CNT_SEND32(length));
        (void)OS_ResetRequestIrqMask(OS_IE_GXFIFO);
    }
}

ARM_FUNC static void MIi_DMACallback(void *)
{
    (void)OS_DisableIrqMask(OS_IE_GXFIFO);

    G3X_SetFifoIntrCond(MIi_GXDmaParams.fifoCond);
    OS_SetIrqFunction(OS_IE_GXFIFO, MIi_GXDmaParams.fifoFunc);

    MIi_GXDmaParams.isBusy = FALSE;

    MIi_CallCallback(MIi_GXDmaParams.callback, MIi_GXDmaParams.arg);
}

ARM_FUNC void MI_SendGXCommandAsyncFast(u32 dmaNo, const void *src, u32 commandLength, MIDmaCallback callback, void *arg)
{
    if (!commandLength)
    {
        MIi_CallCallback(callback, arg);
        return;
    }

    while (MIi_GXDmaParams.isBusy) {}

    MIi_GXDmaParams.isBusy = TRUE;
    MIi_GXDmaParams.dmaNo = dmaNo;
    MIi_GXDmaParams.callback = callback;
    MIi_GXDmaParams.arg = arg;

    MIi_CheckAnotherAutoDMA(dmaNo, 0x38000000);

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, commandLength, DMA_SRC_INC);

    MI_WaitDma(dmaNo);

    OSi_EnterDmaCallback(dmaNo, MIi_DMAFastCallback, NULL);
    MIi_DmaSetParams(dmaNo, (u32)src, (u32)REG_GXFIFO_ADDR, MI_CNT_GXCOPY_IF(commandLength));
}

ARM_FUNC static void MIi_DMAFastCallback(void *)
{
    MIi_GXDmaParams.isBusy = FALSE;

    MIi_CallCallback(MIi_GXDmaParams.callback, MIi_GXDmaParams.arg);
}
