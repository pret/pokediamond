#include "nitro/types.h"
#include "function_target.h"
#include "OS_irqTable.h"

OSIrqFunction OS_IRQTable[25] = {
        OSi_IrqVBlank,
        OS_IrqDummy,
        OS_IrqDummy,
        OSi_IrqTimer0,
        OSi_IrqTimer1,
        OSi_IrqTimer2,
        OSi_IrqTimer3,
        OS_IrqDummy,
        OSi_IrqDma0,
        OSi_IrqDma1,
        OSi_IrqDma2,
        OSi_IrqDma3,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy,
        OS_IrqDummy
};

OSIrqCallbackInfo OSi_IrqCallbackInfo[9] = {
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0}
};

static u16 OSi_IrqCallbackInfoIndex[9] = {
        8, 9, 10, 11, 3, 4, 5, 6, 0
};

ARM_FUNC void OS_IrqDummy(void)
{
    //do nothing
}

ARM_FUNC void OSi_IrqCallback(s32 index)
{
    OSIrqMask imask = (1UL << OSi_IrqCallbackInfoIndex[index]);
    void (*callback) (void *) = OSi_IrqCallbackInfo[index].func;

    OSi_IrqCallbackInfo[index].func = NULL;

    if (callback)
    {
        (callback)(OSi_IrqCallbackInfo[index].arg);
    }

    OS_SetIrqCheckFlag(imask);

    if (!OSi_IrqCallbackInfo[index].enable)
    {
        (void)OS_DisableIrqMask(imask);
    }
}

ARM_FUNC void OSi_IrqDma0(void)
{
    OSi_IrqCallback(0);
}

ARM_FUNC void OSi_IrqDma1(void)
{
    OSi_IrqCallback(1);
}

ARM_FUNC void OSi_IrqDma2(void)
{
    OSi_IrqCallback(2);
}
ARM_FUNC void OSi_IrqDma3(void)
{
    OSi_IrqCallback(3);
}

ARM_FUNC void OSi_IrqTimer0(void)
{
    OSi_IrqCallback(4);
}

ARM_FUNC void OSi_IrqTimer1(void)
{
    OSi_IrqCallback(5);
}

ARM_FUNC void OSi_IrqTimer2(void)
{
    OSi_IrqCallback(6);
}

ARM_FUNC void OSi_IrqTimer3(void)
{
    OSi_IrqCallback(7);
}

ARM_FUNC void OSi_IrqVBlank(void)
{
    void (*callback) (void) = (void (*)(void))OSi_IrqCallbackInfo[8].func;

    (*(u32 *)HW_VBLANK_COUNT_BUF)++;

    if (callback)
    {
        (callback)();
    }

    OS_SetIrqCheckFlag(1UL << 0);
}
