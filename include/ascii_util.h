#ifndef POKEDIAMOND_ASCII_UTIL_H
#define POKEDIAMOND_ASCII_UTIL_H

#include "nitro/types.h"

#include "NNS_G3D_res_struct.h"

s32 Ascii_StrLen(const s8 *str);
const s8 *Ascii_GetDelim(const s8 *src, s8 *dst, s32 c);
s32 Ascii_StrToL(const s8 *str);
void sub_0201C750(NNSG3dResName *resName, const s8 *input);
BOOL sub_0201C78C(u16 c);

#endif // POKEDIAMOND_ASCII_UTIL_H
