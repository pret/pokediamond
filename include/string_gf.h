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
void CopyU16ArrayToStringN(String *, u16 *, u32); // copy
void String_SetEmpty(String *);                   // set empty
String *StringDup(String *, enum HeapID heapID);
void String_Delete(String *str);
void StringCopy(String *dest, String *src);
void String16_FormatInteger(String *str, int num, u32 ndigits, enum PrintingMode printingMode, BOOL whichCharset);
s64 String_atoi(String *str, BOOL *flag);
u16 StringGetLength(String *str);
int StringCountLines(volatile String *str);
void StringGetLineN(String *dest, volatile String *src, u32 n);
void CopyU16ArrayToString(String *str, u16 *buf);
void CopyStringToU16Array(String *str, u16 *buf, u32 length);
u16 *String_c_str(String *str);
void StrAddChar(String *str, u16 val);
void StringCat(String *dest, String *src);
void StrUpperFirstChar(String *str);
BOOL String_IsTrainerName(String *string);
void StringCat_HandleTrainerName(String *dest, String *src);

#endif // POKEDIAMOND_STRING16_H
