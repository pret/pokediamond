#ifndef POKEDIAMOND_FONT_H
#define POKEDIAMOND_FONT_H

#include "global.h"
#include "text.h"

static inline u32 MakeFontColor(u32 fgPal, u32 shdwPal, u32 bgPal)
{
    return (u32)(
        ((u32)(fgPal << 24) >> 8)
        | ((u32)(shdwPal << 24) >> 16)
        | ((u32)(bgPal << 24) >> 24)
    );
}

struct UnkStruct_02002C14_sub
{
    const char buf[0x80];
    u8 width;
    u8 height;
};

struct UnkStruct_02002C14
{
    struct UnkStruct_02002C14_sub unk00;
    void *unk84[4];
    struct FontData *unk94[4];
};

extern struct UnkStruct_02002C14 *UNK_02106FC8;

void FUN_02002C14();
void FUN_02002C50(u32 font_id, u32 heap_id);
void FUN_02002C84(s32 param0, u32 param1);
void FUN_02002CC0(s32 param0);
void FUN_02002CF8(int param0);
struct UnkStruct_02002C14_sub *FUN_02002D94(u32 param0, u32 param1);
u32 FontFunc(u32 fontId, struct TextPrinter *printer);
u32 FUN_02002DE0(u32 param0, u16 *str, u32 param2);
u32 FUN_02002E14(u32 param0, struct String *str, u32 param2);
s32 GetFontAttribute(u8 fontId, s32 attr);
void LoadFontPal0(enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, u32 heap_id);
void FUN_02002EEC(enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, u32 heap_id);
s32 FUN_02002F08(u32 param0, struct String *str, u32 param2);
u32 FUN_02002F40(u32 param0, struct String *str, u32 param2, u32 param3);
u32 FUN_02002F58(const u16 *str);
u32 FUN_02002F90(struct String *str);
s32 FUN_02002F9C(u32 param0, struct String *str);

#endif // POKEDIAMOND_FONT_H
