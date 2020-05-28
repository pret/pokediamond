#ifndef NITRO_MI_MEMORY_H_
#define NITRO_MI_MEMORY_H_

void MI_CpuFill8(void *dest, u8 data, u32 size);
void MI_CpuCopy8(void const *src, void *dest, u32 size);
static inline void MI_CpuClear8(void *dest, u32 size) {
    MI_CpuFill8(dest, 0, size);
}
void MIi_CpuCopy16(const void *src, void *dst, u32 size);

#endif //NITRO_MI_MEMORY_H_
