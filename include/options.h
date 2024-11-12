#ifndef POKEDIAMOND_OPTIONS_H
#define POKEDIAMOND_OPTIONS_H

#include "heap.h"

struct SaveData;

typedef struct Options {
    u16 textSpeed : 4;
    u16 soundMethod : 2;
    u16 battleStyle : 1;
    u16 battleScene : 1;
    u16 buttonMode : 2;
    u16 frame : 5;
} Options;

struct Options *Options_New(HeapID heapId);
void Options_Copy(struct Options *src, struct Options *dest);
void Options_Init(struct Options *options);
void Options_SetButtonModeOnMain(struct SaveData *save, u32 buttonMode);
u16 Options_GetTextSpeed(struct Options *options);
void Options_SetTextSpeed(struct Options *options, u16 textSpeed);
u32 Options_GetTextFrameDelay(struct Options *options);
u16 Options_GetSoundMethod(struct Options *options);
void Options_SetSoundMethod(struct Options *options, u16 soundMethod);
u16 Options_GetBattleScene(struct Options *options);
void Options_SetBattleScene(struct Options *options, u16 battleScene);
u16 Options_GetBattleStyle(struct Options *options);
void Options_SetBattleStyle(struct Options *options, u16 battleStyle);
u16 Options_GetButtonMode(struct Options *options);
void Options_SetButtonMode(struct Options *options, u16 buttonMode);
u16 Options_GetFrame(struct Options *options);
void Options_SetFrame(struct Options *options, u16 frame);

#endif // POKEDIAMOND_OPTIONS_H
