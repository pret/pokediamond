#ifndef POKEDIAMOND_MI_UNCOMPRESS_H
#define POKEDIAMOND_MI_UNCOMPRESS_H

#include "nitro/types.h"

void MIi_UncompressBackward(void * bottom);
void MI_UncompressLZ8(register const void *srcp, register void *destp);

inline u32 MI_GetUncompressedSize(const void *srcp) {
    return (*(u32 *)srcp >> 8);
}

#endif //POKEDIAMOND_MI_UNCOMPRESS_H
