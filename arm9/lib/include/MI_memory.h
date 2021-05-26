#ifndef POKEDIAMOND_ARM9_MI_MEMORY_H
#define POKEDIAMOND_ARM9_MI_MEMORY_H

#include "nitro/types.h"

void MIi_CpuClear16(register u16 data, register void *destp, register u32 size);
void MIi_CpuCopy16(register const void *srcp, register void *destp, register u32 size);
void MIi_CpuClear32(register u32 data, register void *destp, register u32 size);
void MIi_CpuCopy32(register const void *srcp, register void *destp, register u32 size);
void MIi_CpuSend32(register const void *srcp, volatile void *destp, u32 size);
void MIi_CpuClearFast(register u32 data, register void *destp, register u32 size);
void MIi_CpuCopyFast(register const void *srcp, register void *destp, register u32 size);
void MI_Copy32B(register const void *pSrc, register void *pDest);
void MI_Copy36B(register const void *pSrc, register void *pDest);
void MI_Copy48B(register const void *pSrc, register void *pDest);
void MI_Copy64B(register const void *pSrc, register void *pDest);
void MI_CpuFill8(register void *dstp, register u8 data, register u32 size);
void MI_CpuCopy8(register const void *srcp, register void *dstp, register u32 size);
void MI_Zero36B(register void *pDest);

static inline void MI_CpuClearFast(void *destp, u32 size) {
    MIi_CpuClearFast(0, destp, size);
}
static inline void MI_CpuClear8(void *dest, u32 size) {
    MI_CpuFill8(dest, 0, size);
}

static inline void MI_CpuFill16(void *dest, u16 data, u32 size)
{
    MIi_CpuClear16(data, dest, size);
}

static inline void MI_CpuClear16(void * destp, u32 size)
{
    MIi_CpuClear16(0, destp, size);
}

static inline void MI_CpuFill32(void *dest, u32 data, u32 size)
{
    MIi_CpuClear32(data, dest, size);
}

static inline void MI_CpuClear32(void *dest, u32 size)
{
    MI_CpuFill32(dest, 0, size);
}

static inline void MI_CpuCopy16(const void *src, void *dest, u32 size)
{
    MIi_CpuCopy16(src, dest, size);
}

static inline void MI_CpuCopy32(const void *src, void *dest, u32 size)
{
    MIi_CpuCopy32(src, dest, size);
}

static inline void MI_CpuFillFast(void *dest, u32 data, u32 size)
{
    MIi_CpuClearFast(data, dest, size);
}

static inline void MI_CpuCopyFast(const void *src, void *dest, u32 size)
{
    MIi_CpuCopyFast(src, dest, size);
}

#endif //POKEDIAMOND_ARM9_MI_MEMORY_H
