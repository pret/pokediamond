#ifndef POKEDIAMOND_ARM9_PXI_FIFO_H
#define POKEDIAMOND_ARM9_PXI_FIFO_H

#include "nitro/PXI_fifo_shared.h"
#include "nitro/types.h"

void PXI_InitFifo(void);
void PXI_SetFifoRecvCallback(s32 fifotag, PXIFifoCallback callback);
BOOL PXI_IsCallbackReady(s32 fifotag, PXIProc proc);
s32 PXI_SendWordByFifo(s32 fifotag, u32 data, BOOL err);
void PXIi_HandlerRecvFifoNotEmpty(void);

#endif //POKEDIAMOND_ARM9_PXI_FIFO_H
