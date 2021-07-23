#ifndef POKEDIAMOND_CARD_REQUEST_H
#define POKEDIAMOND_CARD_REQUEST_H

#include "nitro/types.h"
#include "PXI_fifo.h"
#include "CARD_common.h"

void CARDi_OnFifoRecv(PXIFifoTag tag, u32 data, BOOL err);
void CARDi_TaskThread(void *arg);
BOOL CARDi_Request(CARDiCommon *p, s32 req_type, s32 retry_count);

#endif //POKEDIAMOND_CARD_REQUEST_H
