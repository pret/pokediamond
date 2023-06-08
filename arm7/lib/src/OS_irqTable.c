#include "nitro/types.h"
#include "OS_irqTable.h"
#include "code32.h"

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

void OS_IrqDummy(void)
{
    //do nothing
}

void OSi_IrqCallback(s32 index)
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

void OSi_IrqDma0(void)
{
    OSi_IrqCallback(0);
}

void OSi_IrqDma1(void)
{
    OSi_IrqCallback(1);
}

void OSi_IrqDma2(void)
{
    OSi_IrqCallback(2);
}
void OSi_IrqDma3(void)
{
    OSi_IrqCallback(3);
}

void OSi_IrqTimer0(void)
{
    OSi_IrqCallback(4);
}

void OSi_IrqTimer1(void)
{
    OSi_IrqCallback(5);
}

void OSi_IrqTimer2(void)
{
    OSi_IrqCallback(6);
}

void OSi_IrqTimer3(void)
{
    OSi_IrqCallback(7);
}

void OSi_IrqVBlank(void)
{
    void (*callback) (void) = (void (*)(void))OSi_IrqCallbackInfo[8].func;

    (*(u32 *)HW_VBLANK_COUNT_BUF)++;

    if (callback)
    {
        (callback)();
    }

    OS_SetIrqCheckFlag(1UL << 0);
}
