#ifndef POKEDIAMOND_OS_CACHE_H
#define POKEDIAMOND_OS_CACHE_H

#include "nitro/types.h"

void DC_InvalidateAll(void);
void DC_StoreAll(void);
void DC_FlushAll(void);
void DC_InvalidateRange(register void *startAddr, register u32 nBytes);
void DC_StoreRange(register void *startAddr, register u32 nBytes);
void DC_FlushRange(register const void *startAddr, register u32 nBytes);
void DC_WaitWriteBufferEmpty(void);
void IC_InvalidateAll(void);
void IC_InvalidateRange(register void *startAddr, register u32 nBytes);

#endif //POKEDIAMOND_OS_CACHE_H
