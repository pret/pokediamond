#ifndef POKEDIAMOND_STRING16_H
#define POKEDIAMOND_STRING16_H

#include "string_util.h"
#include "unk_02021590.h"

typedef struct String {
    u16 maxsize;
    u16 size;
    u32 magic;
    u16 data[1];
    u8 padding[2];
} String;

#define STR16_MAGIC 0xB6F8D2EC

String *String_New(u32 count, enum HeapID heapID);
BOOL String_Compare(String *, String *);
void String_CopyNumChars(String *, u16 *, u32); // copy
void String_Clear(String *);                   // set empty
String *String_Clone(String *, enum HeapID heapID);
void String_Free(String *string);
void String_Copy(String *dest, String *src);
void String_FormatInt(String *string, int num, u32 ndigits, enum PrintingMode printingMode, BOOL whichCharset);
s64 String_AtoI(String *string, BOOL *flag);
u16 String_GetLength(String *string);
int String_CountLines(const String *string);
void String_CopyLine(String *dest, const String *src, u32 n);
void String_CopyFromChars(String *string, u16 *buf);
void String_CopyToChars(String *string, u16 *buf, u32 length);
u16 *String_GetChars(String *string);
void String_AppendChar(String *string, u16 val);
void String_Concat(String *dest, String *src);
void StrUpperFirstChar(String *string);
BOOL String_IsTrainerName(String *string);
void String_ConcatTrainerName(String *dest, String *src);

#endif // POKEDIAMOND_STRING16_H
