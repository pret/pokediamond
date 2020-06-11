#ifndef POKEDIAMOND_OS_CONTEXT_H
#define POKEDIAMOND_OS_CONTEXT_H

#include "nitro/types.h"
#include "CP_context.h"

typedef struct OSContext
{
    u32 cpsr;
    u32 r[13];
    u32 sp;
    u32 lr;
    u32 pc_plus4;
    u32 sp_svc;
    CPContext cp_context;
} OSContext;

extern u32 OS_SaveContext(OSContext *context);
extern void OS_LoadContext(OSContext *context);
extern void OS_InitContext(OSContext *context, u32 func, u32 stack);

#endif //POKEDIAMOND_OS_CONTEXT_H
