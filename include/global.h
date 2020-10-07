#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include "config.h"

#include "MWC_string.h"
#include "function_target.h"
#include "nitro.h"
#include "global.fieldmap.h"
#include "constants/global.h"
#include "error_handling.h"

#define NELEMS(a) (sizeof(a) / sizeof(*(a)))

#define GF_ASSERT(expr) do {if (!(expr)) ErrorHandling();} while (0)

#ifndef IN_MAIN_C
extern const u8 gGameLanguage;
extern const u8 gGameVersion;
#endif //IN_MAIN_C

#endif //GUARD_GLOBAL_H
