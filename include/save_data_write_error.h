#ifndef POKEDIAMOND_SAVE_DATA_WRITE_ERROR_H
#define POKEDIAMOND_SAVE_DATA_WRITE_ERROR_H

#include "nitro/types.h"

#include "heap.h"

void ShowSaveDataWriteError(enum HeapID heapID, u32 err_no);

#endif
