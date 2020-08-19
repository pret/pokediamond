#ifndef NITRO_MI_MEMORY_H_
#define NITRO_MI_MEMORY_H_

#include "nitro/types.h"

void MI_CpuFill8(void *dest, u8 data, u32 size);
void MI_CpuCopy8(void const *src, void *dest, u32 size);
void MIi_CpuClearFast(u32 data, void *destp, u32 size);
static inline void MI_CpuClearFast(void *destp, u32 size) {
    MIi_CpuClearFast(0, destp, size);
}
static inline void MI_CpuClear8(void *dest, u32 size) {
    MI_CpuFill8(dest, 0, size);
}
void MIi_CpuCopy16(const void *src, void *dst, u32 size);

void MIi_CpuClear32(u32 data, void *destp, u32 size);

void MIi_CpuClear16(u16 data, void *destp, u32 size);

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

void MIi_CpuClearFast(u32 data, void *destp, u32 size);

#endif //NITRO_MI_MEMORY_H_
