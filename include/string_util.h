//
// Created by red031000 on 2020-05-24.
//

#ifndef POKEDIAMOND_STRING_UTIL_H
#define POKEDIAMOND_STRING_UTIL_H

#include "global.h"

enum PrintingMode {
    PRINTING_MODE_LEFT_ALIGN,
    PRINTING_MODE_RIGHT_ALIGN,
    PRINTING_MODE_LEADING_ZEROS
};

void CopyU16StringArray(u16 *dest, const u16 *src);
u16 *CopyU16StringArrayN(u16 *dest, const u16 *src, u32 num);
u32 StringLength(const u16 *str);
BOOL StringNotEqual(const u16 *s1, const u16 *s2);
BOOL StringNotEqualN(const u16 *s1, const u16 *s2, u32 num);
u16 *StringFill(u16 *dest, u16 value, u32 num);
u16 *StringFillEOS(u16 *dest, u32 num);
u16 *ConvertUIntToDecimalString(u16 *dest, u32 value, enum PrintingMode mode, u32 n);

#endif //POKEDIAMOND_STRING_UTIL_H
