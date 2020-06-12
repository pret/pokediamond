#include "function_target.h"
#include "sections.h"
#include "OS_irqTable.h"

#pragma section DTCM begin
OSIrqFunction OS_IRQTable[22] = {
        OS_IrqDummy,
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
        OS_IrqDummy
};
#pragma section DTCM end

OSIrqCallbackInfo OSi_IrqCallbackInfo[8] = {
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
        {NULL, 0, 0},
};

static u16 OSi_IrqCallbackInfoIndex[8] = {
        8, 9, 10, 11, 3, 4, 5, 6
};

ARM_FUNC void OS_IrqDummy(void)
{
    //noop
}

ARM_FUNC void OSi_IrqCallback(s32 index)
{
    OSIrqMask mask = (1UL << OSi_IrqCallbackInfoIndex[index]);
    void (*callback)(void *) = OSi_IrqCallbackInfo[index].func;

    OSi_IrqCallbackInfo[index].func = NULL;

    if (callback)
    {
        (callback)(OSi_IrqCallbackInfo[index].arg);
    }

    OS_SetIrqCheckFlag(mask);

    if (!OSi_IrqCallbackInfo[index].enable)
    {
        (void)OS_DisableIrqMask(mask);
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
