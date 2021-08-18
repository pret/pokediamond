#ifndef POKEDIAMOND_UNK_0200A104_H
#define POKEDIAMOND_UNK_0200A104_H

#include "global.h"
#include "nitro/FX_types.h"

struct BrightnessData
{
    fx32 surfaceMask;
    u32 screenMask;
    u16 step_count;
    s16 target_brightness;
    u32 unk0c;
    s8 transition_direction;
    s16 brightness_diff;
    s16 step_size_integer;
    u16 step_size_fractional;
    u16 fractional_count;
    s16 current_brightness;
    BOOL transitionActive;
};

void DoBrightnessTransitionStep(struct BrightnessData *brightness);
void InitBrightnessTransition(struct BrightnessData *brightnessData,
    u16 step_count,
    s16 target_brightness,
    s16 start_brightness,
    fx32 surfaceMask,
    u32 screenMask);
void StartBrightnessTransition(
    u16 step_count, s16 target_brightness, s16 start_brightness, fx32 surfaceMask, u32 screenMask);
void SetBrightness(fx32 brightness, fx32 surfaceMask, u32 screenMask);
void InitAllScreenBrightnessData(void);
void InitScreenBrightnessData(u32 screenMask);
void DoAllScreenBrightnessTransitionStep(void);
BOOL IsBrightnessTransitionActive(u32 screenMask);

#endif // POKEDIAMOND_UNK_0200A104_H
