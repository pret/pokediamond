#ifndef POKEDIAMOND_FONT_H
#define POKEDIAMOND_FONT_H

#include "global.h"
#include "text.h"

struct UnkStruct_02002C14
{
    const char buf[0x80];
    u8 width;
    u8 height;
    void *unk84[4];
    void *unk94[4];
};

void FUN_02002C14();
void FUN_02002C50(u32 param0, u32 param1);
void FUN_02002C84(s32 param0, u32 param1);
void FUN_02002CC0(s32 param0);
void FUN_02002CF8(s32 param0);
struct UnkStruct_02002C14 *FUN_02002D94(u32 param0, u32 param1);
u32 FontFunc(u32 fontId, struct TextPrinter *printer);
u32 FUN_02002DE0(u32 param0, u16 *str, u32 param2);
u32 FUN_02002E14(u32 param0, struct String *str, u32 param2);
s32 GetFontAttribute(u8 fontId, s32 attr);
void FUN_02002ED0(u32 layer, u32 baseAddr, u32 heap_id);
void FUN_02002EEC(u32 layer, u32 baseAddr, u32 heap_id);

#endif // POKEDIAMOND_FONT_H
