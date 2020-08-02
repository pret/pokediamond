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

void OS_InitContext(register OSContext *context, register u32 newpc, register u32 newsp);
BOOL OS_SaveContext(OSContext *context);
void OS_LoadContext(OSContext *context);

#endif //POKEDIAMOND_OS_CONTEXT_H
