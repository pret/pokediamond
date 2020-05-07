#ifndef NITRO_OS_CACHE_H_
#define NITRO_OS_CACHE_H_

void IC_InvalidateRange(void *startAddr, u32 nBytes);
void IC_FlushRange(void *startAddr, u32 nBytes);
void DC_InvalidateRange(void *startAddr, u32 nBytes);
void DC_FlushRange(void *startAddr, u32 nBytes);

#endif //NITRO_OS_CACHE_H_
