#ifndef POKEDIAMOND_FONT_H
#define POKEDIAMOND_FONT_H

#include "global.h"

#include "text.h"

struct UnkStruct_02002C14_sub {
    const char buf[0x80];
    u8 width;
    u8 height;
};

struct UnkStruct_02002C14 {
    struct UnkStruct_02002C14_sub unk00;
    void *unk84[4];
    struct FontData *unk94[4];
};

extern struct UnkStruct_02002C14 *UNK_02106FC8;

void sub_02002C14();
void sub_02002C50(u32 font_id, HeapID heapId);
void sub_02002C84(s32 param0, HeapID heapId);
void sub_02002CC0(s32 param0);
void sub_02002CF8(int param0);
struct UnkStruct_02002C14_sub *sub_02002D94(u32 param0, u32 param1);
u32 FontFunc(u32 fontId, struct TextPrinter *printer);
u32 sub_02002DE0(u32 param0, u16 *str, u32 param2);
u32 sub_02002E14(u32 param0, struct String *str, u32 param2);
s32 GetFontAttribute(u8 fontId, s32 attr);
void LoadFontPal0(enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, HeapID heapId);
void LoadFontPal1(enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, HeapID heapId);
u32 FontID_String_GetWidthMultiline(u32 param0, struct String *str, u32 param2);
u32 sub_02002F40(u32 param0, struct String *str, u32 param2, u32 param3);
u32 sub_02002F58(const u16 *str);
u32 sub_02002F90(struct String *str);
s32 sub_02002F9C(u32 param0, struct String *str);

#endif // POKEDIAMOND_FONT_H
