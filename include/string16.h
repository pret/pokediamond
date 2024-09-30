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

struct String *String_New(u32 count, HeapID heapId);
BOOL String_Compare(struct String *, struct String *);
void CopyU16ArrayToStringN(struct String *, u16 *, u32); // copy
void String_SetEmpty(struct String *);                   // set empty
struct String *StringDup(struct String *, HeapID heapId);
void String_Delete(struct String *str);
void StringCopy(struct String *dest, struct String *src);
void String16_FormatInteger(struct String *str, int num, u32 ndigits, enum PrintingMode printingMode, BOOL whichCharset);
s64 String_atoi(struct String *str, BOOL *flag);
u16 StringGetLength(struct String *str);
int StringCountLines(volatile struct String *str);
void StringGetLineN(struct String *dest, volatile struct String *src, u32 n);
void CopyU16ArrayToString(struct String *str, u16 *buf);
void CopyStringToU16Array(struct String *str, u16 *buf, u32 length);
u16 *String_c_str(struct String *str);
void StrAddChar(struct String *str, u16 val);
void StringCat(struct String *dest, struct String *src);
void StrUpperFirstChar(struct String *str);
BOOL String_IsTrainerName(struct String *string);
void StringCat_HandleTrainerName(struct String *dest, struct String *src);

#endif // POKEDIAMOND_STRING16_H
