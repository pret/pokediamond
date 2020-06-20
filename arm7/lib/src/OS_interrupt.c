#include "function_target.h"
#include "consts.h"
#include "OS_interrupt.h"
#include "OS_thread.h"

extern OSThreadQueue OSi_IrqThreadQueue;

ARM_FUNC void OS_InitIrqTable(void)
{
    OS_InitThreadQueue(&OSi_IrqThreadQueue);

    OSi_SetVBlankCount(0);
}

ARM_FUNC void OS_SetIrqFunction(OSIrqMask intrBit, OSIrqFunction function)
{
    s32 i;
    OSIrqCallbackInfo *info;

    for (i = 0; i < 25; i++)
    {
        if (intrBit & 1)
        {
            info = NULL;

            if (8 <= i && i <= 11)
            {
                info = &OSi_IrqCallbackInfo[i - 8];
            }
            else if (3 <= i && i <= 6)
            {
                info = &OSi_IrqCallbackInfo[i - 3 + 4];
            }
            else if (0 == i)
            {
                info = &OSi_IrqCallbackInfo[8];
            }
            else
            {
                OS_IRQTable[i] = function;
            }

            if (info)
            {
                info->func = (void (*)(void *))function;
                info->arg = 0;
                info->enable = TRUE;
            }
        }
        intrBit >>= 1;
    }
}

ARM_FUNC void OSi_EnterTimerCallback(u32 timerNo, void (*callback) (void *), void *arg)
{
    OSIrqMask mask = 1UL << (timerNo + 3);
    OSi_IrqCallbackInfo[timerNo + 4].func = callback;
    OSi_IrqCallbackInfo[timerNo + 4].arg = arg;

    (void)OS_EnableIrqMask(mask);
    OSi_IrqCallbackInfo[timerNo + 4].enable = TRUE;
}

ARM_FUNC OSIrqMask OS_SetIrqMask(OSIrqMask mask)
{
    u16 regIme = reg_OS_IME;
    reg_OS_IME = 0;
    OSIrqMask regIe = reg_OS_IE;
    reg_OS_IE = mask;
    u16 unused = reg_OS_IME; //needed because otherwise it doesn't match
    reg_OS_IME = regIme;
    return regIe;
}

ARM_FUNC OSIrqMask OS_EnableIrqMask(OSIrqMask mask)
{
    u16 regIme = reg_OS_IME;
    reg_OS_IME = 0;
    OSIrqMask regIe = reg_OS_IE;
    reg_OS_IE = regIe | mask;
    u16 unused = reg_OS_IME;
    reg_OS_IME = regIme;
    return regIe;
}

ARM_FUNC OSIrqMask OS_DisableIrqMask(OSIrqMask mask)
{
    u16 regIme = reg_OS_IME;
    reg_OS_IME = 0;
    OSIrqMask regIe = reg_OS_IE;
    reg_OS_IE = regIe & ~mask;
    u16 unused = reg_OS_IME;
    reg_OS_IME = regIme;
    return regIe;
}

ARM_FUNC OSIrqMask OS_ResetRequestIrqMask(OSIrqMask mask)
{
    u16 regIme = reg_OS_IME;
    reg_OS_IME = 0;
    OSIrqMask regIf = reg_OS_IF;
    reg_OS_IF = mask;
    u16 unused = reg_OS_IME;
    reg_OS_IME = regIme;
    return regIf;
}
