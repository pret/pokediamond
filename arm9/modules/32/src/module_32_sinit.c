#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD32_02254854();
extern void MOD32_0225495C();

static void MOD32_02254840(void)
{
    Poketch_InitApp(MOD32_02254854, MOD32_0225495C);
}

#define NitroStaticInit MOD32_02254840
#include "sinit.h"
