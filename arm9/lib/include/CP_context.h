#ifndef POKEDIAMOND_CP_CONTEXT_H
#define POKEDIAMOND_CP_CONTEXT_H

#include "nitro/types.h"

typedef struct CPContext {
    u64 div_numer;
    u64 div_denom;
    u64 sqrt;
    u16 div_mode;
    u16 sqrt_mode;
} CPContext;

void CP_SaveContext(register CPContext *context);
void CPi_RestoreContext(const CPContext* context);

#endif //POKEDIAMOND_CP_CONTEXT_H
