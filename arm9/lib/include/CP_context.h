//
// Created by red031000 on 2020-05-17.
//

#ifndef POKEDIAMOND_CP_CONTEXT_H
#define POKEDIAMOND_CP_CONTEXT_H

#include "types.h"

typedef struct CPContext {
    u64 div_numer;
    u64 div_denom;
    u64 sqrt;
    u16 div_mode;
    u16 sqrt_mode;
} CPContext;

#endif //POKEDIAMOND_CP_CONTEXT_H
