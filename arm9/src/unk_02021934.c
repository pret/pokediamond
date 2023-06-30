#include "global.h"
#include "string16.h"
#include "heap.h"
#include "string_util.h"

#define ASSERT_STR16(_str) ({ GF_ASSERT(_str != NULL); GF_ASSERT(_str->magic == STR16_MAGIC); })

struct String * String_New(u32 length, HeapID heapId)
{
    struct String * ret = AllocFromHeap(heapId, length * 2 + 10);
    if (ret != NULL)
    {
        ret->magic = STR16_MAGIC;
        ret->maxsize = (u16)length;
        ret->size = 0;
        ret->data[0] = EOS;
    }
    return ret;
}

void String_Delete(struct String * str)
{
    ASSERT_STR16(str);
    str->magic = STR16_MAGIC | 1;
    FreeToHeap(str);
}

void StringSetEmpty(struct String * str)
{
    ASSERT_STR16(str);
    str->size = 0;
    str->data[0] = EOS;
}

void StringCopy(struct String * dest, struct String * src)
{
    ASSERT_STR16(dest);
    ASSERT_STR16(src);
    if (dest->maxsize > src->size)
    {
        memcpy(dest->data, src->data, (u32)((src->size + 1) * 2));
        dest->size = src->size;
        return;
    }
    GF_ASSERT(0);
}

struct String * StringDup(struct String * src, HeapID heapId)
{
    ASSERT_STR16(src);
    struct String * dest = String_New((u32)(src->size + 1), heapId);
    if (dest != NULL)
        StringCopy(dest, src);
    return dest;
}

void String16_FormatInteger(struct String * str, int num, u32 ndigits, enum PrintingMode printingMode, BOOL whichCharset)
{
    static const u16 sCharset_EN[10] = {
        0x121, 0x122, 0x123, 0x124, 0x125,
        0x126, 0x127, 0x128, 0x129, 0x12A
    };

    static const u16 sCharset_JP[10] = {
        0xA2, 0xA3, 0xA4, 0xA5, 0xA6,
        0xA7, 0xA8, 0xA9, 0xAA, 0xAB
    };

    static const u32 sPowersOfTen[10] = {
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000
    };

    ASSERT_STR16(str);

    const u16 * charbase;
    BOOL isNegative = (num < 0);

    if (str->maxsize > ndigits + isNegative)
    {
        charbase = (whichCharset == 0) ? sCharset_JP : sCharset_EN;
        StringSetEmpty(str);
        if (isNegative)
        {
            num *= -1;
            u16 hyphen = (u16)((whichCharset == 0) ? 0x00F1 : 0x01BE);
            str->data[str->size++] = hyphen;
        }
        u32 dividend = sPowersOfTen[ndigits - 1];
        while (dividend != 0)
        {
            u16 digit = (u16)(num / dividend);
            num -= dividend * digit;
            if (printingMode == PRINTING_MODE_LEADING_ZEROS)
            {
                u16 value = (u16)((digit < 10) ? charbase[digit] : 0x00E2);
                str->data[str->size++] = value;
            }
            else if (digit != 0 || dividend == 1)
            {
                printingMode = PRINTING_MODE_LEADING_ZEROS;
                u16 value = (u16)((digit < 10) ? charbase[digit] : 0x00E2);
                str->data[str->size++] = value;
            }
            else if (printingMode == PRINTING_MODE_RIGHT_ALIGN)
            {
                u16 value = (u16)((whichCharset == 0) ? 0x0001 : 0x01E2);
                str->data[str->size++] = value;
            }
            dividend /= 10;
        }
        str->data[str->size] = EOS;
        return;
    }
    GF_ASSERT(FALSE);
}

s64 String_atoi(struct String * str, BOOL * flag)
{
    s64 ret = 0;
    s64 pow10 = 1;
    if (str->size > 18)
    {
        return 0;
    }
    int ndigits = str->size - 1;
    while (ndigits >= 0) {
        //                               ０
        s64 digit = str->data[ndigits] - 0x00A2;
        if (digit >= 10ull)
        {
            //                           0
            digit = str->data[ndigits] - 0x0121;
            if (digit >= 10ull)
            {
                *flag = FALSE;
                return ret;
            }
        }
        digit *= pow10;
        ret += digit;
        pow10 *= 10;
        ndigits--;
    }
    *flag = TRUE;
    return ret;
}

BOOL String_Compare(struct String * str1, struct String * str2)
{
    ASSERT_STR16(str1);
    ASSERT_STR16(str2);

    for (int i = 0; str1->data[i] == str2->data[i]; i++)
    {
        if (str1->data[i] == EOS)
            return FALSE;
    }
    return TRUE;
}

u16 StringGetLength(struct String * str)
{
    ASSERT_STR16(str);
    return str->size;
}

int StringCountLines(volatile struct String * str)
{
    ASSERT_STR16(str);

    int i, nline;
    for (i = 0, nline = 1; i < str->size; i++)
    {
        if (str->data[i] == CHAR_LF)
            nline++;
    }
    return nline;
}

void StringGetLineN(struct String * dest, volatile struct String * src, u32 n)
{
    ASSERT_STR16(src);
    ASSERT_STR16(dest);

    int i = 0;
    if (n != 0)
    {
        for (i = 0; i < src->size; i++)
        {
            if (src->data[i] == CHAR_LF && --n == 0)
            {
                i++;
                break;
            }
        }
    }
    StringSetEmpty(dest);
    for (; i < src->size; i++)
    {
        u16 c = src->data[i];
        if (c == CHAR_LF)
            break;
        StrAddChar(dest, c);
    }
}

void CopyU16ArrayToString(struct String * str, u16 * buf)
{
    ASSERT_STR16(str);

    for (str->size = 0; *buf != EOS;)
    {
        if (str->size >= str->maxsize - 1)
        {
            GF_ASSERT(0);
            break;
        }
        str->data[str->size++] = *buf++;
    }
    str->data[str->size] = EOS;
}

void CopyU16ArrayToStringN(struct String * str, u16 * buf, u32 length)
{
    ASSERT_STR16(str);

    if (length <= str->maxsize)
    {
        memcpy(str->data, buf, length * 2);
        int i;
        for (i = 0; i < length; i++)
        {
            if (str->data[i] == EOS)
                break;
        }
        str->size = (u16)i;
        if (i == length)
        {
            str->data[length - 1] = EOS;
        }
        return;
    }
    GF_ASSERT(0);
}

void CopyStringToU16Array(struct String * str, u16 * buf, u32 length)
{
    ASSERT_STR16(str);

    if (str->size + 1 <= length)
    {
        memcpy(buf, str->data, (u32)((str->size + 1) * 2));
        return;
    }
    GF_ASSERT(0);
}

u16 * String_c_str(struct String * str)
{
    ASSERT_STR16(str);

    return str->data;
}

void StringCat(struct String * dest, struct String * src)
{
    ASSERT_STR16(dest);
    ASSERT_STR16(src);

    if (dest->size + src->size + 1 <= dest->maxsize)
    {
        memcpy(dest->data + dest->size, src->data, (u32)(2 * (src->size + 1)));
        dest->size += src->size;
        return;
    }
    GF_ASSERT(0);
}

void StrAddChar(struct String * str, u16 val)
{
    ASSERT_STR16(str);

    if (str->size + 1 < str->maxsize)
    {
        str->data[str->size++] = val;
        str->data[str->size] = EOS;
        return;
    }
    GF_ASSERT(0);
}

void StrUpperFirstChar(struct String * str)
{
    ASSERT_STR16(str);

    if (str->size != 0)
    {
        //                       a                         z
        if (str->data[0] >= 0x0145 && str->data[0] <= 0x015E)
            //              (a - A)
            str->data[0] -= 26;
    }
}

BOOL String_IsTrainerName(struct String * string)
{
    return string->size != 0 && string->data[0] == 0xF100;
}

void StringCat_HandleTrainerName(struct String * dest, struct String * src)
{
    if (String_IsTrainerName(src))
    {
        u16 * dest_p = &dest->data[dest->size];
        u16 * src_p = &src->data[1];
        s32 bit = 0;
        u32 outsize = 0;
        u16 cur_char = 0;

        while (1)
        {
            cur_char = (u16)((*src_p >> bit) & 0x1FF);
            bit += 9;
            if (bit >= 15)
            {
                src_p++;
                bit -= 15;
                if (bit != 0)
                {
                    cur_char |= (*src_p << (9 - bit)) & 0x1FF;
                }
            }
            if (cur_char == 0x1FF)
                break;
            *dest_p++ = cur_char;
            outsize++;
        }
        *dest_p = EOS;
        dest->size += outsize;
    }
    else
        StringCat(dest, src);
}
