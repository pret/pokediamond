#include "global.h"
#include "brightness.h"
#include "GX_g2.h"
#include "MI_memory.h"

struct BrightnessData mainScreenBrightnessData;

struct BrightnessData subScreenBrightnessData;

void DoBrightnessTransitionStep(struct BrightnessData *brightness)
{
    BOOL transitionFinished = FALSE;

    if (brightness->target_brightness !=
            brightness->current_brightness +
                brightness->transition_direction * brightness->step_size_integer &&
        brightness->current_brightness != brightness->target_brightness)
    {
        brightness->current_brightness +=
            brightness->transition_direction * brightness->step_size_integer;
        brightness->fractional_count += brightness->step_size_fractional;

        if (brightness->fractional_count >= brightness->step_count)
        {
            brightness->current_brightness += brightness->transition_direction;
            if (brightness->current_brightness != brightness->target_brightness)
            {
                brightness->fractional_count -= brightness->step_count;
            }
            else
            {
                transitionFinished = TRUE;
            }
        }
    }
    else
    {
        brightness->current_brightness = brightness->target_brightness;
        transitionFinished = TRUE;
    }

    if ((brightness->screenMask & 1) != 0)
    {
        G2x_SetBlendBrightness_(
            &reg_G2_BLDCNT, brightness->surfaceMask, brightness->current_brightness);
    }
    else if ((brightness->screenMask & 2) != 0)
    {
        G2x_SetBlendBrightness_(
            &reg_G2S_DB_BLDCNT, brightness->surfaceMask, brightness->current_brightness);
    }

    if (transitionFinished == TRUE)
    {
        brightness->transitionActive = FALSE;
    }
}

void InitBrightnessTransition(struct BrightnessData *brightnessData,
    u16 step_count,
    s16 target_brightness,
    s16 start_brightness,
    fx32 surfaceMask,
    u32 screenMask)
{
    GF_ASSERT(!brightnessData->transitionActive);

    brightnessData->transitionActive = TRUE;
    brightnessData->surfaceMask = (u8)surfaceMask;
    brightnessData->screenMask = (u8)screenMask;
    brightnessData->step_count = step_count;
    brightnessData->target_brightness = target_brightness;
    brightnessData->current_brightness = start_brightness;
    brightnessData->brightness_diff = (s16)(start_brightness - target_brightness);

    if (brightnessData->brightness_diff > 0)
    {
        brightnessData->transition_direction = -1;
    }
    else
    {
        brightnessData->transition_direction = 1;
        brightnessData->brightness_diff *= -1;
    }

    brightnessData->step_size_integer = (s16)(brightnessData->brightness_diff / step_count);
    brightnessData->step_size_fractional = (u16)(brightnessData->brightness_diff % step_count);
    brightnessData->fractional_count = 0;
}

void StartBrightnessTransition(
    u16 step_count, s16 target_brightness, s16 start_brightness, fx32 surfaceMask, u32 screenMask)
{
    if (step_count != 0)
    {
        if ((screenMask & 1) != 0)
        {
            G2x_SetBlendBrightness_(&reg_G2_BLDCNT, surfaceMask, start_brightness);
            InitBrightnessTransition(&mainScreenBrightnessData,
                step_count,
                target_brightness,
                start_brightness,
                surfaceMask,
                1);
        }

        if ((screenMask & 2) != 0)
        {
            G2x_SetBlendBrightness_(&reg_G2S_DB_BLDCNT, surfaceMask, start_brightness);
            InitBrightnessTransition(&subScreenBrightnessData,
                step_count,
                target_brightness,
                start_brightness,
                surfaceMask,
                2);
        }
    }
}

void SetBlendBrightness(fx32 brightness, fx32 surfaceMask, u32 screenMask)
{

    if ((screenMask & 1) != 0)
    {
        G2x_SetBlendBrightness_(&reg_G2_BLDCNT, surfaceMask, brightness);
    }

    if ((screenMask & 2) != 0)
    {
        G2x_SetBlendBrightness_(&reg_G2S_DB_BLDCNT, surfaceMask, brightness);
    }

    InitScreenBrightnessData(screenMask);
}

void InitAllScreenBrightnessData(void)
{
    MI_CpuFill8(&mainScreenBrightnessData, 0, sizeof(struct BrightnessData));
    MI_CpuFill8(&subScreenBrightnessData, 0, sizeof(struct BrightnessData));

    mainScreenBrightnessData.transitionActive = FALSE;
    subScreenBrightnessData.transitionActive = FALSE;
}

void InitScreenBrightnessData(u32 screenMask)
{
    if (screenMask & 1)
    {
        MI_CpuFill8(&mainScreenBrightnessData, 0, sizeof(struct BrightnessData));
        mainScreenBrightnessData.transitionActive = FALSE;
    }

    if (screenMask & 2)
    {
        MI_CpuFill8(&subScreenBrightnessData, 0, sizeof(struct BrightnessData));
        subScreenBrightnessData.transitionActive = FALSE;
    }
}

void DoAllScreenBrightnessTransitionStep(void)
{
    if (mainScreenBrightnessData.transitionActive)
    {
        DoBrightnessTransitionStep(&mainScreenBrightnessData);
    }

    if (subScreenBrightnessData.transitionActive)
    {
        DoBrightnessTransitionStep(&subScreenBrightnessData);
    }
}

BOOL IsBrightnessTransitionActive(u32 screenMask)
{
    if (screenMask == 3)
    {
        if (!mainScreenBrightnessData.transitionActive && !subScreenBrightnessData.transitionActive)
        {
            return TRUE;
        }
    }
    else if (screenMask == 1)
    {
        if (!mainScreenBrightnessData.transitionActive)
        {
            return TRUE;
        }
    }
    else if (screenMask == 2)
    {
        if (!subScreenBrightnessData.transitionActive)
        {
            return TRUE;
        }
    }

    return FALSE;
}
