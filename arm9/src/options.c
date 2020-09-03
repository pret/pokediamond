#include "global.h"
#include "save_block_2.h"
#include "options.h"
#include "heap.h"
#include "main.h"
#include "player_data.h"
#include "MI_memory.h"

#pragma thumb on

u32 Options_GetButtonMode(struct Options * options);

struct Options * Options_new(u32 heap_id)
{
    struct Options * options = (struct Options *)AllocFromHeap(heap_id, sizeof(struct Options));
    Options_init(options);
    return options;
}

void Options_copy(const struct Options * src, struct Options * dest)
{
    MI_CpuCopy8(src, dest, sizeof(struct Options));
}

void Options_init(struct Options * options)
{
    MI_CpuFill8(options, 0, sizeof(struct Options));

    options->textSpeed = 1;
    options->soundMode = 0;
    options->battleScene = 0;
    options->battleStyle = 0;
    options->buttonMode = 0;
    options->textFrame = 0;
}

void SetButtonModeOnMain(struct SaveBlock2 * sav2, u32 mode)
{
    if (sav2 != NULL)
        mode = Options_GetButtonMode(Sav2_PlayerData_GetOptionsAddr(sav2));
    switch (mode)
    {
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

u32 Options_GetTextSpeed(struct Options * options)
{
    return options->textSpeed;
}

void Options_SetTextSpeed(struct Options * options, u32 textSpeed)
{
    options->textSpeed = textSpeed;
}

u32 Options_GetTextFrameDelay(struct Options * options)
{
    u32 textSpeed = Options_GetTextSpeed(options);
    if (textSpeed == 0)
        return 8;
    else if (textSpeed == 1)
        return 4;
    else
        return 1;
}

u32 Options_GetSoundMode(struct Options * options)
{
    return options->soundMode;
}

void Options_SetSoundMode(struct Options * options, u32 soundMode)
{
    options->soundMode = soundMode;
}

u32 Options_GetBattleStyle(struct Options * options)
{
    return options->battleStyle;
}

void Options_SetBattleStyle(struct Options * options, u32 battleStyle)
{
    options->battleStyle = battleStyle;
}

u32 Options_GetBattleScene(struct Options * options)
{
    return options->battleScene;
}

void Options_SetBattleScene(struct Options * options, u32 battleScene)
{
    options->battleScene = battleScene;
}

u32 Options_GetButtonMode(struct Options * options)
{
    return options->buttonMode;
}

void Options_SetButtonMode(struct Options * options, u32 buttonMode)
{
    options->buttonMode = buttonMode;
}

u32 Options_GetFrame(struct Options * options)
{
    return options->textFrame;
}

void Options_SetFrame(struct Options * options, u32 textFrame)
{
    options->textFrame = textFrame;
}
