#ifndef POKEDIAMOND_OPTIONS_H
#define POKEDIAMOND_OPTIONS_H

struct SaveBlock2;

#define OPT_BUTTON_MODE_NORMAL   0
#define OPT_BUTTON_MODE_START_X  1
#define OPT_BUTTON_MODE_L_A      2

struct Options {
    u16 textSpeed:4;   // slow/mid/fast
    u16 soundMode:2;   // stereo/mono
    u16 battleScene:1; // on/off
    u16 battleStyle:1; // shift/set
    u16 buttonMode:2;  // normal/start=x/l=a
    u16 textFrame:5;   // 20 types
};

struct Options * Options_new(u32 heap_id);
void Options_copy(const struct Options * src, struct Options * dest);
void Options_init(struct Options * options);
void SetButtonModeOnMain(struct SaveBlock2 * sav2, u32 mode);
u32 Options_GetTextSpeed(struct Options * options);
void Options_SetTextSpeed(struct Options * options, u32 textSpeed);
u32 Options_GetTextFrameDelay(struct Options * options);
u32 Options_GetBattleScene(struct Options * options);
void Options_SetBattleScene(struct Options * options, u32 battleScene);
u32 Options_GetBattleStyle(struct Options * options);
void Options_SetBattleStyle(struct Options * options, u32 battleStyle);
u32 Options_GetSoundMode(struct Options * options);
void Options_SetSoundMode(struct Options * options, u32 soundMode);
u32 Options_GetButtonMode(struct Options * options);
void Options_SetButtonMode(struct Options * options, u32 buttonMode);
u32 Options_GetFrame(struct Options * options);
void Options_SetFrame(struct Options * options, u32 textFrame);

#endif //POKEDIAMOND_OPTIONS_H
