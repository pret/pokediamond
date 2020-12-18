#include "global.h"
#include "heap.h"
#include "main.h"
#include "MI_memory.h"
#include "options.h"
#include "player_data.h"

#pragma thumb on

struct Options * Options_new(u32 heap_id) {
    struct Options * ret = AllocFromHeap(heap_id, sizeof(struct Options));
    Options_init(ret);
    return ret;
}

void Options_copy(struct Options * src, struct Options * dest) {
    MI_CpuCopy8(src, dest, sizeof(struct Options));
}

void Options_init(struct Options * options) {
    MI_CpuFill8(options, 0, sizeof(struct Options));

    options->textSpeed = 1;   // mid speed
    options->soundMethod = 0; // stereo
    options->battleStyle = 0; // shift
    options->battleScene = 0; // on
    options->buttonMode = 0;  // normal
    options->frame = 0;       // frame 1
}

void Options_SetButtonModeOnMain(struct SaveBlock2 * sav2, u32 buttonMode) {
    if (sav2 != NULL) {
        buttonMode = Options_GetButtonMode(Sav2_PlayerData_GetOptionsAddr(sav2));
    }

    switch (buttonMode) {
        case 1:
            gMain.unk34 = 1;
            break;
        case 2:
            gMain.unk34 = 3;
            break;
        case 0:
        default:
            gMain.unk34 = 0;
            break;
    }
}

u16 Options_GetTextSpeed(struct Options * options) {
    return options->textSpeed;
}

void Options_SetTextSpeed(struct Options * options, u16 textSpeed) {
    options->textSpeed = (u16)(u32)textSpeed;
}

u32 Options_GetTextFrameDelay(struct Options * options) {
    u16 textSpeed = Options_GetTextSpeed(options);

    if (textSpeed == 0) {
        return 8;
    }

    if (textSpeed == 1) {
        return 4;
    }

    return 1;
}

u16 Options_GetSoundMethod(struct Options * options) {
    return options->soundMethod;
}

void Options_SetSoundMethod(struct Options * options, u16 soundMethod) {
    options->soundMethod = (u16)(u32)soundMethod;
}

u16 Options_GetBattleScene(struct Options * options) {
    return options->battleScene;
}

void Options_SetBattleScene(struct Options * options, u16 battleScene) {
    options->battleScene = (u16)(u32)battleScene;
}

u16 Options_GetBattleStyle(struct Options * options) {
    return options->battleStyle;
}

void Options_SetBattleStyle(struct Options * options, u16 battleStyle) {
    options->battleStyle = (u16)(u32)battleStyle;
}

u16 Options_GetButtonMode(struct Options * options) {
    return options->buttonMode;
}

void Options_SetButtonMode(struct Options * options, u16 buttonMode) {
    options->buttonMode = (u16)(u32)buttonMode;
}

u16 Options_GetFrame(struct Options * options) {
    return options->frame;
}

void Options_SetFrame(struct Options * options, u16 frame) {
    options->frame = (u16)(u32)frame;
}
