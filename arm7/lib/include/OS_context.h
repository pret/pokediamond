#ifndef POKEDIAMOND_ARM7_OS_CONTEXT_H
#define POKEDIAMOND_ARM7_OS_CONTEXT_H

#include "nitro/types.h"

typedef struct OSContext
{
    u32 cpsr;
    u32 r[13];
    u32 sp;
    u32 lr;
    u32 pc_plus4;
    u32 sp_svc;
} OSContext;

#endif //POKEDIAMOND_ARM7_OS_CONTEXT_H
