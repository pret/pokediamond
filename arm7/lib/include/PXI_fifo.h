#ifndef POKEDIAMOND_ARM7_PXI_FIFO_H
#define POKEDIAMOND_ARM7_PXI_FIFO_H

#include "nitro/PXI_fifo_shared.h"

s32 PXI_SendWordByFifo(s32 fifotag, u32 data, BOOL err);
void PXI_SetFifoRecvCallback(s32 fifotag, PXIFifoCallback callback);

#endif //POKEDIAMOND_ARM7_PXI_FIFO_H
