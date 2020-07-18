#ifndef POKEDIAMOND_OS_EXCEPTION_H
#define POKEDIAMOND_OS_EXCEPTION_H

#include "consts.h"
#include "OS_context.h"

typedef struct
{
    OSContext   context;
    u32         cp15;
    u32         spsr;
    u32         exinfo;
    u32         debug[4];
} OSiExContext;

typedef void (*OSExceptionHandler) (u32, void *);

static void OSi_ExceptionHandler(void);

void OS_InitException(void);
void OSi_ExceptionHandler(void);
static void OSi_GetAndDisplayContext(void);
static void OSi_SetExContext(void);
static void OSi_DisplayExContext(void);

#endif //POKEDIAMOND_OS_EXCEPTION_H
