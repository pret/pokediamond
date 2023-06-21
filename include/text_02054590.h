#ifndef POKEDIAMOND_UNK_02054590_H
#define POKEDIAMOND_UNK_02054590_H

#include "global.h"
#include "options.h"
#include "bg_window.h"
#include "string16.h"


void sub_02054590(enum GFPalLoadLocation location, u32 param1);
void sub_020545B8(struct BgConfig *param0, struct Window *param1, u32 param2);
void sub_02054608(struct Window *param0, struct Options *options);
void sub_0205464C(struct Window *param0);
u16 sub_02054658(struct Window * window, struct String *str, struct Options *options, u8 param3);
u16 DrawFieldMessage(struct Window * window, struct String *str, u8 fontId, u32 speed, u8 a4, s32 a5);
u8 sub_020546C8(u8 textPrinterNumber);
void sub_020546E0(struct BgConfig *param0, struct Window *param1, u32 param2, u32 param3);
void sub_02054744(struct Window *param0, u32 param1, u16 param2);

#endif // POKEDIAMOND_UNK_02054590_H
