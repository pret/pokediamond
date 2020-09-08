#include "global.h"
#include "unk_0201C6B4.h"

#pragma thumb on

// strlen
s32 CStringLength(const s8 * x)
{
    s32 len;
    for (len = 0; x[len]; len++) ;
    return len;
}

// tokenize string. copies token to dest.
// returns pointer past token, or NULL if not found.
// for CRLF newline, pass '\r' to the tok parameter
// max token size 256 (including NUL)
// potential UB: if tok is '\r', may read one byte
// beyond the end of the string
const s8 * TokenizeCString(const s8 * src, s8 * dest, s32 tok)
{
    int i;
    for (i = 0; i < 0x100; i++)
    {
        dest[i] = src[i];
        if (tok == src[i] || src[i] == '\0')
        {
            dest[i] = '\0';
            if (tok == '\r' && src[i + 1] == '\n')
            {
                return src + (i + 2);
            }
            else
            {
                return src + (i + 1);
            }
        }
    }
    return NULL;
}

// atoi
s32 CStringToInt(const s8 * str)
{
    s32 siz = CStringLength(str);
    s32 pow10 = 1;
    s32 ret = 0;
    while (--siz >= 0)
    {
        if (str[siz] >= '0' && str[siz] <= '9')
            ret += pow10 * (str[siz] - '0');
        else if (siz == 0)
        {
            if (str[siz] == '-')
                ret *= -1;
        }
        else
            return -1;
        pow10 *= 10;
    }
    return ret;
}

// copies string into a 16-byte buffer
void Copy16ByteCString(s8 * a0, const s8 * a1)
{
    u8 i;
    u8 siz;
    for (i = 0; i < 4; i++)
        ((u32 *)a0)[i] = 0;
    siz = (u8)CStringLength(a1);
    for (i = 0; i < siz; i++)
    {
        a0[i] = a1[i];
    }
}

// ???
BOOL Unknown_IsLessThan289(u32 a0)
{
    return a0 < 289;
}
