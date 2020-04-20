#include "nitro.h"

extern u32 gPowersOfTen[]; // at 0x20ECB24
extern u16 gDigitTable[]; // at 0x20ECB08

static const u16 EOS = 0xFFFF;

void StringCopy(u16 *dest, const u16 *src)
{
    u16 c = *src;
    while (c != EOS)
    {
        src++;
        *dest = c;
        c = *src;
        dest++;
    }
    *dest = EOS;
}

u16 *StringCopyN(u16 *dest, const u16 *src, u32 num)
{
    u32 copied = 0;
    if (num > copied)
    {
        u16 *p = dest;
        do
        {
            u16 c = *src;
            copied++;
            src++;
            *p = c;
            p++;
        } while (num > copied);
    }
    return dest + num;
}

u32 StringLength(const u16 *s)
{
    u16 c = *s;
    u32 len = 0;
    while (c != EOS)
    {
        s++;
        c = *s;
        len++;
    }
    return len;
}

BOOL StringNotEqual(const u16 *s1, const u16 *s2)
{
    for (; *s1 == *s2; s1++, s2++)
    {
        if (*s1 == EOS)
            return FALSE;
    }
    return TRUE;
}

BOOL StringNotEqualN(const u16 *s1, const u16 *s2, u32 num)
{
    u16 c1, c2;
    c2 = *s2;
    c1 = *s1;
    while (c1 == c2)
    {
        if (num == 0)
        {
            return FALSE;
        }
        if (*s1 == EOS && *s2 == EOS)
        {
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

u16 *StringFill(u16 *dest, u16 value, u32 num)
{
    u32 copied = 0;
    if (num > copied)
    {
        u16 *p = dest;
        do
        {
            copied++;
            *p = value;
            p++;
        } while (copied < num);
    }
    return dest + copied;
}

u16 *StringFillEOS(u16 *dest, u32 num)
{
    return StringFill(dest, EOS, num);
}

enum PrintingMode
{
    NORMAL,
    PAD_SPACE,
    PAD_ZEROES
};

const u16 NON_DIGIT = 0xE2;

u16 *ConvertUIntToDecimalString(u16 *dest, u32 value, enum PrintingMode mode, u32 n)
{
    for (u32 x = gPowersOfTen[n];
         x != 0;
         x = x / 10)
    {
        u16 res = value / x;
        value = value - x * res;
        if (mode == PAD_ZEROES)
        {
            *dest = res >= 10 ? NON_DIGIT : gDigitTable[res];
            dest++;
        }
        else if (res != 0 || x == 1)
        {
            mode = PAD_ZEROES;
            *dest = res >= 10 ? NON_DIGIT : gDigitTable[res];
            dest++;
        }
        else if (mode == PAD_SPACE)
        {
            *dest = 1;
            dest++;
        }
    }
    *dest = EOS;
    return dest;
}
