#include "PXI_init.h"
#include "function_target.h"

extern void PXI_InitFifo(void);

ARM_FUNC void PXI_Init(void)
{
    PXI_InitFifo();
}
