#ifndef NITRO_MI_EXMEMORY_H_
#define NITRO_MI_EXMEMORY_H_

#include "consts.h"

typedef enum {
    MI_PROCESSOR_ARM9 = 0,
    MI_PROCESSOR_ARM7 = 1
} MIProcessor;

static inline void MIi_SetCardProcessor(MIProcessor proc)
{
    reg_MI_EXMEMCNT =
            (u16)((reg_MI_EXMEMCNT & ~0x0800) | (proc << 11));
}

static inline void MIi_SetCartridgeProcessor(MIProcessor proc)
{
    reg_MI_EXMEMCNT =
            (u16)((reg_MI_EXMEMCNT & ~0x0080) | (proc << 7));
}

#endif //NITRO_MI_EXMEMORY_H_
