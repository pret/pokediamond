#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov32_02254854();
extern void ov32_0225495C();

static void ov32_02254840(void)
{
    Poketch_InitApp(ov32_02254854, ov32_0225495C);
}

#define NitroStaticInit ov32_02254840
#include "sinit.h"
