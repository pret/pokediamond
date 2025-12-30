#include "string_gf.h"

#include "global.h"

#include "heap.h"
#include "string_util.h"

static inline void String_Assert(const String *string) {
    GF_ASSERT(string != NULL);
    GF_ASSERT(string->magic == STR16_MAGIC);
}

String *String_New(u32 length, enum HeapID heapID) {
    String *ret = Heap_Alloc(heapID, length * 2 + 10);
    if (ret != NULL) {
        ret->magic = STR16_MAGIC;
        ret->maxsize = (u16)length;
        ret->size = 0;
        ret->data[0] = EOS;
    }
    return ret;
}

void String_Free(String *string) {
    String_Assert(string);
    string->magic = STR16_MAGIC | 1;
    Heap_Free(string);
}

void String_Clear(String *string) {
    String_Assert(string);
    string->size = 0;
    string->data[0] = EOS;
}

void String_Copy(String *dest, String *src) {
    String_Assert(dest);
    String_Assert(src);
    if (dest->maxsize > src->size) {
        memcpy(dest->data, src->data, (u32)((src->size + 1) * 2));
        dest->size = src->size;
        return;
    }
    GF_ASSERT(FALSE);
}

String *String_Clone(String *src, enum HeapID heapID) {
    String_Assert(src);
    String *dest = String_New((u32)(src->size + 1), heapID);
    if (dest != NULL) {
        String_Copy(dest, src);
    }
    return dest;
}

void String_FormatInt(String *string, int num, u32 ndigits, enum PrintingMode printingMode, BOOL whichCharset) {
    static const u16 sCharset_EN[10] = {
        0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 0x128, 0x129, 0x12A
    };

    static const u16 sCharset_JP[10] = {
        0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB
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

    String_Assert(string);

    const u16 *charbase;
    BOOL isNegative = (num < 0);

    if (string->maxsize > ndigits + isNegative) {
        charbase = (whichCharset == 0) ? sCharset_JP : sCharset_EN;
        String_Clear(string);
        if (isNegative) {
            num *= -1;
            u16 hyphen = (u16)((whichCharset == 0) ? 0x00F1 : 0x01BE);
            string->data[string->size++] = hyphen;
        }
        u32 dividend = sPowersOfTen[ndigits - 1];
        while (dividend != 0) {
            u16 digit = (u16)(num / dividend);
            num -= dividend * digit;
            if (printingMode == PRINTING_MODE_LEADING_ZEROS) {
                u16 value = (u16)((digit < 10) ? charbase[digit] : 0x00E2);
                string->data[string->size++] = value;
            } else if (digit != 0 || dividend == 1) {
                printingMode = PRINTING_MODE_LEADING_ZEROS;
                u16 value = (u16)((digit < 10) ? charbase[digit] : 0x00E2);
                string->data[string->size++] = value;
            } else if (printingMode == PRINTING_MODE_RIGHT_ALIGN) {
                u16 value = (u16)((whichCharset == 0) ? 0x0001 : 0x01E2);
                string->data[string->size++] = value;
            }
            dividend /= 10;
        }
        string->data[string->size] = EOS;
        return;
    }
    GF_ASSERT(FALSE);
}

s64 String_AtoI(String *string, BOOL *flag) {
    s64 ret = 0;
    s64 pow10 = 1;
    if (string->size > 18) {
        return 0;
    }
    int ndigits = string->size - 1;
    while (ndigits >= 0) {
        //                               ０
        s64 digit = string->data[ndigits] - 0x00A2;
        if (digit >= 10ull) {
            //                           0
            digit = string->data[ndigits] - 0x0121;
            if (digit >= 10ull) {
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

BOOL String_Compare(String *str1, String *str2) {
    String_Assert(str1);
    String_Assert(str2);

    for (int i = 0; str1->data[i] == str2->data[i]; i++) {
        if (str1->data[i] == EOS) {
            return FALSE;
        }
    }
    return TRUE;
}

u16 String_GetLength(String *string) {
    String_Assert(string);
    return string->size;
}

int String_CountLines(const String *string) {
    String_Assert(string);

    int i, nline;
    for (i = 0, nline = 1; i < string->size; i++) {
        if (string->data[i] == CHAR_LF) {
            nline++;
        }
    }
    return nline;
}

void String_CopyLine(String *dest, const String *src, u32 n) {
    String_Assert(src);
    String_Assert(dest);

    int i = 0;
    if (n != 0) {
        for (i = 0; i < src->size; i++) {
            if (src->data[i] == CHAR_LF && --n == 0) {
                i++;
                break;
            }
        }
    }
    String_Clear(dest);
    for (; i < src->size; i++) {
        u16 c = src->data[i];
        if (c == CHAR_LF) {
            break;
        }
        String_AppendChar(dest, c);
    }
}

void String_CopyFromChars(String *string, u16 *buf) {
    String_Assert(string);

    for (string->size = 0; *buf != EOS;) {
        if (string->size >= string->maxsize - 1) {
            GF_ASSERT(FALSE);
            break;
        }
        string->data[string->size++] = *buf++;
    }
    string->data[string->size] = EOS;
}

void String_CopyNumChars(String *string, u16 *buf, u32 length) {
    String_Assert(string);

    if (length <= string->maxsize) {
        memcpy(string->data, buf, length * 2);
        int i;
        for (i = 0; i < length; i++) {
            if (string->data[i] == EOS) {
                break;
            }
        }
        string->size = (u16)i;
        if (i == length) {
            string->data[length - 1] = EOS;
        }
        return;
    }
    GF_ASSERT(FALSE);
}

void String_CopyToChars(String *string, u16 *buf, u32 length) {
    String_Assert(string);

    if (string->size + 1 <= length) {
        memcpy(buf, string->data, (u32)((string->size + 1) * 2));
        return;
    }
    GF_ASSERT(FALSE);
}

u16 *String_GetChars(String *string) {
    String_Assert(string);

    return string->data;
}

void String_Concat(String *dest, String *src) {
    String_Assert(dest);
    String_Assert(src);

    if (dest->size + src->size + 1 <= dest->maxsize) {
        memcpy(dest->data + dest->size, src->data, (u32)(2 * (src->size + 1)));
        dest->size += src->size;
        return;
    }
    GF_ASSERT(FALSE);
}

void String_AppendChar(String *string, u16 val) {
    String_Assert(string);

    if (string->size + 1 < string->maxsize) {
        string->data[string->size++] = val;
        string->data[string->size] = EOS;
        return;
    }
    GF_ASSERT(FALSE);
}

void StrUpperFirstChar(String *string) {
    String_Assert(string);

    if (string->size != 0) {
        //                       a                         z
        if (string->data[0] >= 0x0145 && string->data[0] <= 0x015E) {
            //              (a - A)
            string->data[0] -= 26;
        }
    }
}

BOOL String_IsTrainerName(String *string) {
    return string->size != 0 && string->data[0] == 0xF100;
}

void String_ConcatTrainerName(String *dest, String *src) {
    if (String_IsTrainerName(src)) {
        u16 *dest_p = &dest->data[dest->size];
        u16 *src_p = &src->data[1];
        s32 bit = 0;
        u32 outsize = 0;
        u16 cur_char = 0;

        while (1) {
            cur_char = (u16)((*src_p >> bit) & 0x1FF);
            bit += 9;
            if (bit >= 15) {
                src_p++;
                bit -= 15;
                if (bit != 0) {
                    cur_char |= (*src_p << (9 - bit)) & 0x1FF;
                }
            }
            if (cur_char == 0x1FF) {
                break;
            }
            *dest_p++ = cur_char;
            outsize++;
        }
        *dest_p = EOS;
        dest->size += outsize;
    } else {
        String_Concat(dest, src);
    }
}
