#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include "config.h"

#include "MWC_string.h"
#include "function_target.h"
#include "nitro.h"
#include "global.fieldmap.h"
#include "constants/global.h"

#define NELEMS(a) (sizeof(a) / sizeof(*(a)))

extern void ErrorHandling(void);

#define GF_ASSERT(expr) do {if (!(expr)) ErrorHandling();} while (0)

extern const int gGameLanguage;
extern const u8 gGameVersion;

#endif //GUARD_GLOBAL_H
