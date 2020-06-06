#ifndef NITRO_OS_PRINTF_H_
#define NITRO_OS_PRINTF_H_

#define OS_Warning( ... )  ((void)0)
#define OS_TPanic(...) OS_Terminate()
#define OS_TWarning(...) ((void)0)

#include "nitro/types.h"

s32 OS_SPrintf(s8 *buffer, const s8 *format, ...);
s32 OS_VSPrintf(s8 *buffer, const s8 *format, void *args);
s32 OS_SNPrintf(s8 *buffer, s32 bufsz, const s8 *format, ...);
s32 OS_VSNPrintf(s8 *buffer, s32 bufsz, const s8 *format, void *args);

#endif //NITRO_OS_PRINTF_H_
