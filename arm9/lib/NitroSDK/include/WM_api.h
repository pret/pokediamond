#ifndef POKEDIAMOND_WM_API_H
#define POKEDIAMOND_WM_API_H

#include "nitro/types.h"

static inline BOOL WM_IsBssidEqual(const u8 *mac0, const u8 *mac1) {
    return (*(mac0 + 0) == *(mac1 + 0)
            && *(mac0 + 1) == *(mac1 + 1)
            && *(mac0 + 2) == *(mac1 + 2)
            && *(mac0 + 3) == *(mac1 + 3)
            && *(mac0 + 4) == *(mac1 + 4)
            && *(mac0 + 5) == *(mac1 + 5)
    );
}

#endif // POKEDIAMOND_WM_API_H
