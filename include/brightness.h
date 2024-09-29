#ifndef POKEDIAMOND_BRIGHTNESS_H
#define POKEDIAMOND_BRIGHTNESS_H

#include "nitro/FX_types.h"

#include "global.h"

#include "GX_g2.h"

#define SCREEN_MASK_MAIN 1
#define SCREEN_MASK_SUB  2

typedef struct BrightnessData {
    GXBlendPlaneMask surfaceMask;
    u32 screenMask;
    u16 stepCount;
    s16 targetBrightness;
    u32 unk0c;
    s8 transitionDirection;
    s16 brightnessDiff;
    s16 stepSizeInteger;
    u16 stepSizeFractional;
    u16 fractionalCount;
    fx16 currentBrightness;
    BOOL transitionActive;
} BrightnessData;

void DoBrightnessTransitionStep(BrightnessData *brightness);
void InitBrightnessTransition(BrightnessData *brightnessData, u16 stepCount, s16 targetBrightness, s16 startBrightness, GXBlendPlaneMask surfaceMask, u32 screenMask);
void StartBrightnessTransition(u16 stepCount, s16 targetBrightness, s16 startBrightness, GXBlendPlaneMask surfaceMask, u32 screenMask);
void SetBlendBrightness(fx32 brightness, GXBlendPlaneMask surfaceMask, u32 screenMask);
void ScreenBrightnessData_InitAll(void);
void InitScreenBrightnessData(u32 screenMask);
void DoAllScreenBrightnessTransitionStep(void);
BOOL IsBrightnessTransitionActive(u32 screenMask);

#endif // POKEDIAMOND_BRIGHTNESS_H
