#include "string_gf.h"

#include "global.h"

#include "heap.h"
#include "string_util.h"

#define STRING_HEADER_SIZE  (10)
#define STRING_MAGIC_NUMBER (0xB6F8D2EC)
#define STRING_INVAL        (STRING_MAGIC_NUMBER + 1)

static inline void String_Assert(const String *string) {
    GF_ASSERT(string != NULL);
    GF_ASSERT(string->integrity == STRING_MAGIC_NUMBER);
}

String *String_New(u32 maxSize, enum HeapID heapID) {
    String *string = Heap_Alloc(heapID, STRING_HEADER_SIZE + (maxSize * sizeof(u16)));
    if (string != NULL) {
        string->integrity = STRING_MAGIC_NUMBER;
        string->maxSize = maxSize;
        string->size = 0;
        string->data[0] = EOS;
    }
    return string;
}

void String_Free(String *string) {
    String_Assert(string);
    string->integrity = STRING_INVAL;
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
    if (dest->maxSize > src->size) {
        memcpy(dest->data, src->data, (src->size + 1) * sizeof(u16));
        dest->size = src->size;
        return;
    }
    GF_ASSERT(FALSE);
}

String *String_Clone(String *src, enum HeapID heapID) {
    String_Assert(src);
    String *ret = String_New(src->size + 1, heapID);
    if (ret != NULL) {
        String_Copy(ret, src);
    }
    return ret;
}

void String_FormatInt(String *dest, int num, u32 maxDigits, enum PaddingMode paddingMode, enum CharsetMode charsetMode) {
    static const u32 sPowersOfTen[] = {
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

    static const u16 sDigits_JP[] = {
        CHAR_JP_0,
        CHAR_JP_1,
        CHAR_JP_2,
        CHAR_JP_3,
        CHAR_JP_4,
        CHAR_JP_5,
        CHAR_JP_6,
        CHAR_JP_7,
        CHAR_JP_8,
        CHAR_JP_9,
    };

    static const u16 sDigits_EN[] = {
        CHAR_0,
        CHAR_1,
        CHAR_2,
        CHAR_3,
        CHAR_4,
        CHAR_5,
        CHAR_6,
        CHAR_7,
        CHAR_8,
        CHAR_9,
    };

    String_Assert(dest);

    BOOL isNegative = (num < 0);

    if (dest->maxSize > maxDigits + isNegative) {
        const u16 *digitSet = (charsetMode == CHARSET_MODE_JP) ? sDigits_JP : sDigits_EN;

        String_Clear(dest);

        if (isNegative) {
            num *= -1;
            dest->data[dest->size++] = (charsetMode == CHARSET_MODE_JP) ? 0x00F1 : 0x01BE;
        }

        u32 dividend = sPowersOfTen[maxDigits - 1];
        while (dividend != 0) {
            u16 digit = num / dividend;
            num -= dividend * digit;

            if (paddingMode == PADDING_MODE_ZEROES) {
                dest->data[dest->size++] = (digit < 10) ? digitSet[digit] : 0x00E2;
                // If we hit a non-zero digit, flip the padding mode off
            } else if (digit != 0 || dividend == 1) {
                paddingMode = PADDING_MODE_ZEROES;
                dest->data[dest->size++] = (digit < 10) ? digitSet[digit] : 0x00E2;
            } else if (paddingMode == PADDING_MODE_SPACES) {
                dest->data[dest->size++] = (charsetMode == CHARSET_MODE_JP) ? 0x0001 : 0x01E2;
            }
            dividend /= 10;
        }
        dest->data[dest->size] = EOS;
        return;
    }
    GF_ASSERT(FALSE);
}

s64 String_AtoI(String *string, BOOL *success) {
    s64 ret = 0ll;
    s64 pow = 1ll;
    if (string->size > 18) {
        return 0;
    }

    for (int i = (string->size - 1); i >= 0; i--) {
        s64 digit = string->data[i] - 0x00A2;
        if (digit >= 10ull) {
            digit = string->data[i] - 0x0121;
            if (digit >= 10ull) {
                *success = FALSE;
                return ret;
            }
        }
        digit *= pow;
        ret += digit;
        pow *= 10;
    }
    *success = TRUE;
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

    int i, count;
    for (i = 0, count = 1; i < string->size; i++) {
        if (string->data[i] == CHAR_LF) {
            count++;
        }
    }
    return count;
}

void String_CopyLine(String *dest, const String *src, u32 lineNum) {
    String_Assert(src);
    String_Assert(dest);

    int i = 0;
    if (lineNum != 0) {
        for (i = 0; i < src->size; i++) {
            if (src->data[i] == CHAR_LF && --lineNum == 0) {
                i++;
                break;
            }
        }
    }
    String_Clear(dest);
    for (; i < src->size; i++) {
        if (src->data[i] == CHAR_LF) {
            break;
        }
        String_AppendChar(dest, src->data[i]);
    }
}

void String_CopyFromChars(String *dest, u16 *src) {
    String_Assert(dest);

    for (dest->size = 0; *src != EOS;) {
        if (dest->size >= dest->maxSize - 1) {
            GF_ASSERT(FALSE);
            break;
        }
        dest->data[dest->size++] = *src++;
    }
    dest->data[dest->size] = EOS;
}

void String_CopyNumChars(String *dest, u16 *src, u32 num) {
    String_Assert(dest);

    if (num <= dest->maxSize) {
        memcpy(dest->data, src, num * sizeof(u16));

        int i;
        for (i = 0; i < num; i++) {
            if (dest->data[i] == EOS) {
                break;
            }
        }
        dest->size = i;
        if (i == num) {
            dest->data[num - 1] = EOS;
        }
        return;
    }
    GF_ASSERT(FALSE);
}

void String_CopyToChars(String *src, u16 *dest, u32 destSize) {
    String_Assert(src);

    if (src->size + 1 <= destSize) {
        memcpy(dest, src->data, (src->size + 1) * sizeof(u16));
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

    if (dest->size + src->size + 1 <= dest->maxSize) {
        memcpy(dest->data + dest->size, src->data, (src->size + 1) * sizeof(u16));
        dest->size += src->size;
        return;
    }
    GF_ASSERT(FALSE);
}

void String_AppendChar(String *string, u16 c) {
    String_Assert(string);

    if (string->size + 1 < string->maxSize) {
        string->data[string->size++] = c;
        string->data[string->size] = EOS;
        return;
    }
    GF_ASSERT(FALSE);
}

void String_UpperFirstChar(String *string) {
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
    return string->size > 0 && string->data[0] == 0xF100;
}

void String_ConcatTrainerName(String *dest, String *src) {
    // Trainer names are expressed using a format with a designating leader
    // code followed by compression algorithm that trims individual characters
    // from 16 bits to 10 bits.
    //
    // TODO: This process could do with some more documentation, i.e. why this
    // is done.
    if (String_IsTrainerName(src)) {
        u16 *dstChar = &dest->data[dest->size];
        u16 *srcChar = &src->data[1];
        s32 shift = 0;
        u32 charsAdded = 0;
        u16 curChar = 0;

        while (TRUE) {
            curChar = (*srcChar >> shift) & 0x1FF;
            shift += 9;
            if (shift >= 15) {
                srcChar++;
                shift -= 15;
                if (shift != 0) {
                    curChar |= (*srcChar << (9 - shift)) & 0x1FF;
                }
            }

            if (curChar == 0x1FF) {
                break;
            }
            *dstChar++ = curChar;
            charsAdded++;
        }
        *dstChar = EOS;
        dest->size += charsAdded;
    } else {
        String_Concat(dest, src);
    }
}
