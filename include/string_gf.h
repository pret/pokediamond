#ifndef POKEDIAMOND_STRING16_H
#define POKEDIAMOND_STRING16_H

#include "string_util.h"
#include "unk_02021590.h"

typedef struct String {
    u16 maxSize;
    u16 size;
    u32 integrity;
    u16 data[1];
    u8 padding[2];
} String;

enum CharsetMode {
    CHARSET_MODE_JP,
    CHARSET_MODE_EN,
};

String *String_New(u32 maxSize, enum HeapID heapID);
BOOL String_Compare(String *, String *);
void String_CopyNumChars(String *dest, u16 *src, u32 num);
void String_Clear(String *);                   // set empty
String *String_Clone(String *, enum HeapID heapID);
void String_Free(String *string);
void String_Copy(String *dest, String *src);
void String_FormatInt(String *string, int num, u32 maxDigits, enum PaddingMode paddingMode, enum CharsetMode charsetMode);
s64 String_AtoI(String *string, BOOL *success);
u16 String_GetLength(String *string);
int String_CountLines(const String *string);
void String_CopyLine(String *dest, const String *src, u32 lineNum);
void String_CopyFromChars(String *dest, u16 *src);
void String_CopyToChars(String *src, u16 *dest, u32 destSize);
u16 *String_GetChars(String *string);
void String_AppendChar(String *string, u16 c);
void String_Concat(String *dest, String *src);
void String_UpperFirstChar(String *string);
BOOL String_IsTrainerName(String *string);
void String_ConcatTrainerName(String *dest, String *src);

#endif // POKEDIAMOND_STRING16_H
