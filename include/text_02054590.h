#ifndef POKEDIAMOND_UNK_02054590_H
#define POKEDIAMOND_UNK_02054590_H

#include "global.h"
#include "options.h"
#include "bg_window.h"
#include "string16.h"


void FUN_02054590(u32 param0, u32 param1);
void FUN_020545B8(struct BgConfig *param0, struct Window *param1, u32 param2);
void FUN_02054608(struct Window *param0, struct Options *options);
void FUN_0205464C(struct Window *param0);
u16 FUN_02054658(struct Window * window, struct String *str, struct Options *options, u8 param3);
u16 DrawFieldMessage(struct Window * window, struct String *str, u8 fontId, u32 speed, u8 a4, s32 a5);
u8 FUN_020546C8(u8 textPrinterNumber);
void FUN_020546E0(struct BgConfig *param0, struct Window *param1, u32 param2, u32 param3);
void FUN_02054744(struct Window *param0, u32 param1, u16 param2);

#endif // POKEDIAMOND_UNK_02054590_H
