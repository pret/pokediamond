#ifndef GUARD_MWC_STRING_H
#define GUARD_MWC_STRING_H

#include "nitro/types.h"

void * memset(void *, int, u32);
void * memcpy(void *, const void *, u32);
u32 strlen(const s8 *);
void strcpy(s8 * dest, const s8 * src);

#endif //GUARD_MWC_STRING_H
