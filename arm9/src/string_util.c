#include "string_util.h"

const u16 gDigitTable[] = {
    0xA2,
    0xA3,
    0xA4,
    0xA5,
    0xA6,
    0xA7,
    0xA8,
    0xA9,
    0xAA,
    0xAB,
    0xAC,
    0xAD,
    0xAE,
    0xAF,
    0xB0,
    0xB1
};

const s32 gPowersOfTen[] = {
             1,
            10,
           100,
          1000,
         10000,
        100000,
       1000000,
      10000000,
     100000000,
    1000000000,
};

THUMB_FUNC void CopyU16StringArray(u16 *dest, const u16 *src)
{
    u16 c = *src;
    while (c != EOS) {
        src++;
        *dest = c;
        c = *src;
        dest++;
    }
    *dest = EOS;
}

THUMB_FUNC u16 *CopyU16StringArrayN(u16 *dest, const u16 *src, u32 num)
{
    u32 copied = 0;
    if (num > copied) {
        u16 *p = dest;
        do {
            u16 c = *src;
            copied++;
            src++;
            *p = c;
            p++;
        } while (num > copied);
    }
    return dest + num;
}

THUMB_FUNC u32 StringLength(const u16 *s)
{
    u16 c = *s;
    u32 len = 0;
    while (c != EOS) {
        s++;
        c = *s;
        len++;
    }
    return len;
}

THUMB_FUNC BOOL StringNotEqual(const u16 *s1, const u16 *s2)
{
    for (; *s1 == *s2; s1++, s2++) {
        if (*s1 == EOS)
            return FALSE;
    }
    return TRUE;
}

THUMB_FUNC BOOL StringNotEqualN(const u16 *s1, const u16 *s2, u32 num)
{
    u16 c1, c2;
    c2 = *s2;
    c1 = *s1;
    while (c1 == c2) {
        if (num == 0) {
            return FALSE;
        }
        if (*s1 == EOS && *s2 == EOS) {
            return FALSE;
        }
        s1++;
        s2++;
        c2 = *s2;
        c1 = *s1;
        num--;
    }
    return TRUE;
}

THUMB_FUNC u16 *StringFill(u16 *dest, u16 value, u32 num)
{
    u32 copied = 0;
    if (num > copied) {
        u16 *p = dest;
        do {
            copied++;
            *p = value;
            p++;
        } while (copied < num);
    }
    return dest + copied;
}

THUMB_FUNC u16 *StringFillEOS(u16 *dest, u32 num)
{
    return StringFill(dest, EOS, num);
}

THUMB_FUNC u16 *ConvertUIntToDecimalString(u16 *dest, u32 value, enum PrintingMode mode, u32 n)
{
    for (u32 x = (u32)gPowersOfTen[n - 1]; x != 0; x = x / 10) {
        u16 res = (u16)(value / x);
        value = value - x * res;
        if (mode == PRINTING_MODE_LEADING_ZEROS) {
            *dest = res >= 10 ? (u16)NON_DIGIT : gDigitTable[res];
            dest++;
        } else if (res != 0 || x == 1) {
            mode = PRINTING_MODE_LEADING_ZEROS;
            *dest = res >= 10 ? (u16)NON_DIGIT : gDigitTable[res];
            dest++;
        } else if (mode == PRINTING_MODE_RIGHT_ALIGN) {
            *dest = 1;
            dest++;
        }
    }
    *dest = EOS;
    return dest;
}
